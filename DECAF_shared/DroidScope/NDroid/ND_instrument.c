/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-7-9
 */

#include "ND_instrument.h"
#include "DECAF_shared/DECAF_main.h"
#include "DECAF_shared/DECAF_callback.h"
#include "DECAF_shared/utils/OutputWrapper.h"
#include "DECAF_shared/DroidScope/NDroid/darm/darm.h"
#include "DECAF_shared/DroidScope/linuxAPI/ProcessInfo.h"
#include "NativeLibraryWhitelist.h"

DECAF_Handle nd_ib_handle = DECAF_NULL_HANDLE;
DECAF_Handle nd_be_handle = DECAF_NULL_HANDLE;

/*
 * we maintain 'whitelistLibs' referring to the system libraries (e.g., libc.so, libm.so)
 * and 'blacklistLibs' referring to 3rd party libraries.
 */
StringHashtable* whitelistLibs = NULL;
StringHashtable* blacklistLibs = NULL;

//"libdvm.so" start address and end address
gva_t DVM_START_ADDR = -1;
gva_t DVM_END_ADDR = -1;


/*
 * Instruction Begin callback condition function.
 *
 * Since we cannot get process id at translation phase, in order to reduce the performance
 * overhead, we first lookup 'curPC' in the traced process to get in which module the current
 * instruction locates. Then, if the returned module is in 'blacklistLibs', we perform 
 * instrumentation; or if it isn't in 'whitelistLibs', we perform instrumentation too.
 */
int nd_instruction_begin_callback_cond(DECAF_callback_type_t cbType, gva_t curPC, gva_t nextPC){
	char moduleName[128];
	moduleName[0] = '\0';
	gva_t startAddr = -1;
	gva_t endAddr = -1;

	//check current pc
	if(curPC < 0 || curPC >= 0xC0000000){
		return (0);
	}

	if(ND_GLOBAL_TRACING_PID >= 0){
	//if(ND_GLOBAL_TRACING_PID == getCurrentPID()){ //Note that during translation phase, getCurrentPID() returns 
	//process running rather than process being translated
		getExecutableModuleInfo(ND_GLOBAL_TRACING_PID, moduleName, 128, &startAddr, &endAddr, curPC);
		if('\0' != moduleName[0]){
			//in blacklist
			if(StringHashtable_exist(blacklistLibs, moduleName)){
				return (1);
			}

			//not in whitelist
			if(!StringHashtable_exist(whitelistLibs, moduleName)){
				DECAF_printf("Add %s to blacklist\n", moduleName);
				StringHashtable_add(blacklistLibs, moduleName);
				return (1);
			}
		}
	}
	
	return (0);
}

/**
 * Instruction Begin callback.
 */
void nd_instruction_begin_callback(DECAF_Callback_Params* params){
	DEFENSIVE_CHECK0(params == NULL);
	DEFENSIVE_CHECK0(getCurrentPID() != ND_GLOBAL_TRACING_PID);

	CPUState* env = params->ib.env;
	gva_t cur_pc = params->ib.cur_pc;

	//ARM Instruction
	union _tmpARMInsn{
		target_ulong insn;
		char chars[4];
	} tmpARMInsn;
	//Thumb Instruction
	union _tmpThumbInsn{
		unsigned short insn;
		char chars[2];
	} tmpThumbInsn;
	//Thumb2 Instruction
	union _tmpThumb2Insn{
		target_ulong insn;
		char chars[4];
	} tmpThumb2Insn;

	//undefined instruction
	if(cur_pc == -1){
		return;
	}
	//Thumb instruction
	if(env->thumb == 1){
		if(DECAF_read_mem(env, cur_pc & 0xfffffffe, tmpThumbInsn.chars, 2) != -1){
			darm_t d;
			darm_str_t str;
    	// magic table constructed based on section A6.1 of the ARM manual
    	static uint8_t is_thumb2[0x20] = {
        [0x01d] = 1,
        [0x01e] = 1,
        [0x01f] = 1,
    	};

			if(is_thumb2[tmpThumbInsn.insn >> 11]){
				//Thumb2 instruction
				if(DECAF_read_mem(env, cur_pc & 0xfffffffe, tmpThumb2Insn.chars, 4) != -1){
					if(darm_thumb2_disasm(&d, tmpThumb2Insn.insn >> 16, tmpThumb2Insn.insn & 0x0000ffff) == 0){
						if(darm_str(&d, &str) == 0){
							DECAF_printf("%x: %s\n", cur_pc, str.total);
						}
					}
				}
			}else{
				//Thumb instruction
				if(darm_thumb_disasm(&d, tmpThumbInsn.insn) == 0){
					if(darm_str(&d, &str) == 0){
						DECAF_printf("%x: %s\n", cur_pc, str.total);
					}
				}
			}
		}
	}else{
		//ARM instruction
		if(DECAF_read_mem(env, cur_pc, tmpARMInsn.chars, 4) != -1){
			darm_t d;
			darm_str_t str;
			if(darm_armv7_disasm(&d, tmpARMInsn.insn) == 0){
				if(darm_str(&d, &str) == 0){
					DECAF_printf("%x: %s\n", cur_pc, str.total);
				}
			}
		}
	}

}


/**
 * Block end callback condition function.
 */
int nd_block_end_callback_cond(DECAF_callback_type_t cbType, gva_t curPC, gva_t nextPC){
	return (0);
}

int is_empty(const char* str){
	int i = 0;
	char c = str[i];
	for(; c != '\0'; c = str[++i]){
		if(c != ' ' && c != '\t' && c != '\r' && c != '\n' && c != '\x0b'){
			return (0);
		}
	}
	return (1);
}
/**
 * Block end callback.
 */
void nd_block_end_callback(DECAF_Callback_Params* params){
}

void nd_instrument_init(){
	nd_ib_handle = DECAF_register_callback(DECAF_INSN_BEGIN_CB, 
																				&nd_instruction_begin_callback, 
																				&nd_instruction_begin_callback_cond);
	nd_be_handle = DECAF_register_callback(DECAF_BLOCK_END_CB,
																				&nd_block_end_callback,
																				&nd_block_end_callback_cond);
	
	whitelistLibs = NativeLibraryWhitelist_new();

  blacklistLibs = StringHashtable_new();

	ModuleNode* node = getModulesByName(ND_GLOBAL_TRACING_PID, "/lib/libdvm.so");
	if(node != NULL){
		ModuleNode* i = node;
		DECAF_printf("libdvm.so's address space: \n");
		for(; i != NULL; i = i->next){
			char* moduleName = getModuleNodeName(i);
			if((!is_empty(moduleName)) && (strcmp(moduleName, "/lib/libdvm.so") != 0)){
				break;
			}else{
				if(i->flags & 0x04){
					DVM_START_ADDR = i->startAddr;
					DVM_END_ADDR = i->endAddr;
					DECAF_printf("libdvm.so: [%x, %x]\n", DVM_START_ADDR, DVM_END_ADDR);
				}
			}
		}
	}else{
		DECAF_printf("Cannot get start address and end address of libdvm.so\n");
	}
	/*	
	if(getModuleInfoByName(ND_GLOBAL_TRACING_PID, &DVM_START_ADDR, &DVM_END_ADDR, "/lib/libdvm.so") != 0){
		DECAF_printf("Cannot get start address and end address of libdvm.so\n");
	}else{
		DECAF_printf("libdvm.so: [%x, %x]\n", DVM_START_ADDR, DVM_END_ADDR);
	}
	*/
}


//TODO
void nd_instrument_stop(){
	NativeLibraryWhitelist_free(whitelistLibs);

	StringHashtable_free(blacklistLibs);
}
