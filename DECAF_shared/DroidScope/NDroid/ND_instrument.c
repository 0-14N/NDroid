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
#include "hook/dvm_hook.h"
#include "hook/SourcePolicy.h"
#include "hook/jni_bridge/jni_api_hook.h"
#include "hook/sys_libraries/sys_lib_hook.h"

DECAF_Handle nd_ib_handle = DECAF_NULL_HANDLE;
DECAF_Handle nd_be_handle = DECAF_NULL_HANDLE;
DECAF_Handle nd_bb_handle = DECAF_NULL_HANDLE;

/*
 * we maintain 'whitelistLibs' referring to the system libraries (e.g., libc.so, libm.so)
 * and 'blacklistLibs' referring to 3rd party libraries.
 */
StringHashtable* whitelistLibs = NULL;
StringHashtable* blacklistLibs = NULL;

//modules' start addresses and end addresses
gva_t DVM_START_ADDR = -1;
gva_t DVM_END_ADDR = -1;

//special case: when an app loads native libraries like:
//static {
//	System.loadLibrary("libnet.so");
//	call ...
//}
//the modules are not updated immediately, the start/end address of the "libnet.so" 
//has to be given. (0x4a3cd000 0x4a3d0000)
gva_t GIVEN_LIB_START_ADDR = -1;
gva_t GIVEN_LIB_END_ADDR = -1;

//last call JNI API address
gva_t lastCallJNIAddrRet = -1;
//last call system library address
gva_t lastCallSysLibAddrRet = -1;
//last JNI call hooking handler
jniHookHandler lastJniHandler = NULL;
//last system library call hooking handler
sysLibHookHandler lastSysLibHandler = NULL;

/*
 * Since we cannot get process id at translation phase, in order to reduce the performance
 * overhead, we first lookup 'curPC' in the traced process to get in which module the current
 * instruction locates. Then, if the returned module is in 'blacklistLibs', we perform 
 * instrumentation; or if it isn't in 'whitelistLibs', we perform instrumentation too.
 */
int nd_in_blacklist(gva_t addr){
	char moduleName[128];
	moduleName[0] = '\0';
	gva_t startAddr = -1;
	gva_t endAddr = -1;

	//check current pc
	if(addr < 0 || addr >= 0xC0000000){
		return (0);
	}

	//if(ND_GLOBAL_TRACING_PID == getCurrentPID()){ //Note that during translation phase, getCurrentPID() returns 
	//process running rather than process being translated
	getExecutableModuleInfo(ND_GLOBAL_TRACING_PID, moduleName, 128, &startAddr, &endAddr, addr);
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
	else{
		if(addr != -1 && addr >= GIVEN_LIB_START_ADDR && addr <= GIVEN_LIB_END_ADDR){
			return (1);
		}
	}

	return (0);
}

/*
 * Instruction Begin callback condition function.
 */
int nd_instruction_begin_callback_cond(DECAF_callback_type_t cbType, gva_t curPC, gva_t nextPC){
	if(ND_GLOBAL_TRACING_PID >= 0){
		if(nd_in_blacklist(curPC)){
			return (1);
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
	//since for thumb instruction, the last bit is '1'	
	gva_t cur_pc_even = cur_pc & 0xfffffffe;


	if(!nd_in_blacklist(cur_pc_even)){
		return;
	}

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

	//the first instruction of target native method
	SourcePolicy* sourcePolicy = findSourcePolicy(cur_pc_even);
	if(sourcePolicy != NULL){
		DECAF_printf("Step into Native\n");
		sourcePolicy->handler(sourcePolicy, env);
	}

	//return from JNI API calls/system library calls
	if(cur_pc_even == lastCallJNIAddrRet){
		if(lastJniHandler != NULL){
			lastJniHandler(env, 0);
			lastJniHandler = NULL;
			lastCallJNIAddrRet = -1;
		}
	}
	
	if(cur_pc_even == lastCallSysLibAddrRet){
		if(lastSysLibHandler != NULL){
			lastSysLibHandler(env, 0);
			lastSysLibHandler = NULL;
			lastCallSysLibAddrRet = -1;
		}
	}
	
	//Thumb instruction
	if(env->thumb == 1){
		if(DECAF_read_mem(env, cur_pc_even, tmpThumbInsn.chars, 2) != -1){
			darm_t d;
			//darm_str_t str;
    	// magic table constructed based on section A6.1 of the ARM manual
    	static uint8_t is_thumb2[0x20] = {
        [0x01d] = 1,
        [0x01e] = 1,
        [0x01f] = 1,
    	};

			if(is_thumb2[tmpThumbInsn.insn >> 11]){
				//Thumb2 instruction
				if(DECAF_read_mem(env, cur_pc_even, tmpThumb2Insn.chars, 4) != -1){
					if(darm_thumb2_disasm(&d, tmpThumb2Insn.insn >> 16, 
								tmpThumb2Insn.insn & 0x0000ffff, env) == 0){
						//if(darm_str(&d, &str, env) == 0){
							//DECAF_printf("T2  %x: %s\n", cur_pc, str.total);
						//}
					}
				}
			}else{
				//Thumb instruction
				if(darm_thumb_disasm(&d, tmpThumbInsn.insn, env) == 0){
					//if(darm_str(&d, &str, env) == 0){
						//DECAF_printf("T   %x: %s\n", cur_pc, str.total);
					//}
				}
			}
		}
	}else{
		//ARM instruction
		if(DECAF_read_mem(env, cur_pc_even, tmpARMInsn.chars, 4) != -1){
			darm_t d;
			//darm_str_t str;
			if(darm_armv7_disasm(&d, tmpARMInsn.insn, env) == 0){
				//if(darm_str(&d, &str, env) == 0){
					//DECAF_printf("A   %x: %s\n", cur_pc_even, str.total);
				//}
			}
		}
	}

}


/**
 * Block end callback condition function.
 */
int nd_block_end_callback_cond(DECAF_callback_type_t cbType, gva_t curPC, gva_t nextPC){
	DEFENSIVE_CHECK1(ND_GLOBAL_TRACING_PID == -1, 0);
	DEFENSIVE_CHECK1(ND_GLOBAL_TRACING_PROCESS == NULL, 0);
	DEFENSIVE_CHECK1(curPC < 0 || curPC >= 0xC0000000, 0);

	gva_t tmpNextPC = nextPC & 0xfffffffe;
	gva_t tmpCurPC = curPC & 0xfffffffe;

	//JNI API call/system library call
	if(nd_in_blacklist(tmpCurPC) && !nd_in_blacklist(tmpNextPC)){
		return (1);
	}

	//end of dvm hooks (e.g. dvmGetVirtulizedMethod, ...)
	if(isEndOfDvmHooks(tmpCurPC, DVM_START_ADDR)){
		return(1);
	}
	
	return (0);
}

/**
 * Block end callback.
 */
void nd_block_end_callback(DECAF_Callback_Params* params){
	CPUState* env = params->be.env;
	gva_t cur_pc = params->be.cur_pc & 0xfffffffe;
	gva_t next_pc = params->be.next_pc & 0xfffffffe;

	if(getCurrentPID() != ND_GLOBAL_TRACING_PID){
		return;
	}

	//JNI API/system library call
	if(nd_in_blacklist(cur_pc) && !nd_in_blacklist(next_pc)){
		//DECAF_printf("=================JUMP FROM %x TO %x\n", cur_pc, next_pc);
		lastJniHandler = hookJniApis(next_pc, DVM_START_ADDR, env);
		if(lastJniHandler != NULL){
			lastCallJNIAddrRet = env->regs[14];
			return;
		}
		lastSysLibHandler = hookSysLibCalls(next_pc, env);
		if(lastSysLibHandler != NULL){
			lastCallSysLibAddrRet = env->regs[14];
			return;
		}
	}

	//end of dvm hooks (e.g. dvmGetVirtulizedMethod, ...)
	if(isEndOfDvmHooks(cur_pc, DVM_START_ADDR)){
		dvmHooksEnd(env, cur_pc, DVM_START_ADDR);
		return;
	}

}

/**
 * block begin callback cond
 */
int nd_block_begin_callback_cond(DECAF_callback_type_t cbType, gva_t curPC, gva_t nextPC){
	DEFENSIVE_CHECK1(ND_GLOBAL_TRACING_PID == -1, 0);
	DEFENSIVE_CHECK1(ND_GLOBAL_TRACING_PROCESS == NULL, 0);
	DEFENSIVE_CHECK1(curPC < 0 || curPC >= 0xC0000000, 0);

	gva_t tmpCurPC = curPC & 0xfffffffe;

	//start of dvm hooks (e.g. dvmGetVirtulizedMethod, )
	if(isStartOfDvmHooks(tmpCurPC, DVM_START_ADDR)){
		return (1);
	}

	return (0);
}

/**
 * block end callback
 */
void nd_block_begin_callback(DECAF_Callback_Params* params){
	CPUState* env = params->be.env;
	gva_t cur_pc = params->be.cur_pc & 0xfffffffe;

	if(getCurrentPID() != ND_GLOBAL_TRACING_PID){
		return;
	}

	//start of dvm hooks (e.g. dvmGetVirtulizedMethod, )
	if(isStartOfDvmHooks(cur_pc, DVM_START_ADDR)){
		dvmHooksBegin(env, cur_pc, DVM_START_ADDR);
		return;
	}
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

void getModuleBoundry(const char* moduleName, gva_t* startAddr, gva_t* endAddr){
	ModuleNode* node = getModulesByName(ND_GLOBAL_TRACING_PID, moduleName);
	if(node != NULL){
		ModuleNode* i = node;
		DECAF_printf("%s's address space: \n", moduleName);
		for(; i != NULL; i = i->next){
			const char* tmpModuleName = getModuleNodeName(i);
			if((!is_empty(tmpModuleName)) && (strcmp(tmpModuleName, moduleName) != 0)){
				break;
			}else{
				if(i->flags & 0x04){
					*startAddr = i->startAddr;
					*endAddr = i->endAddr;
					DECAF_printf("%s: [%x, %x]\n", moduleName, *startAddr, *endAddr);
				}
			}
		}
	}else{
		DECAF_printf("Cannot get start address and end address of %s\n", moduleName);
	}
}

void nd_instrument_init(){
	//register instruction begin
	nd_ib_handle = DECAF_register_callback(DECAF_INSN_BEGIN_CB, 
																				&nd_instruction_begin_callback, 
																				&nd_instruction_begin_callback_cond);

	//register block end
	nd_be_handle = DECAF_register_callback(DECAF_BLOCK_END_CB,
																				&nd_block_end_callback,
																				&nd_block_end_callback_cond);

	//register block begin
	nd_bb_handle = DECAF_register_callback(DECAF_BLOCK_BEGIN_CB,
																				&nd_block_begin_callback,
																				&nd_block_begin_callback_cond);
	
	whitelistLibs = NativeLibraryWhitelist_new();

  blacklistLibs = StringHashtable_new();

	getModuleBoundry("/lib/libdvm.so", &DVM_START_ADDR, &DVM_END_ADDR);

	getModuleBoundry("/lib/libc.so", &LIBC_START_ADDR, &LIBC_END_ADDR);

	getModuleBoundry("/lib/libm.so", &LIBM_START_ADDR, &LIBM_END_ADDR);
	
	DECAF_printf("GLOBAL_TRACING_PID: %d == %d\n", ND_GLOBAL_TRACING_PID, getCurrentPID());
}


//TODO
void nd_instrument_stop(){
	NativeLibraryWhitelist_free(whitelistLibs);

	StringHashtable_free(blacklistLibs);

	//unregister instruction begin callback
	if(nd_ib_handle != DECAF_NULL_HANDLE){
		DECAF_unregister_callback(DECAF_INSN_BEGIN_CB, nd_ib_handle);
		nd_ib_handle = DECAF_NULL_HANDLE;
	}

	//unregister block begin callback
	if(nd_bb_handle != DECAF_NULL_HANDLE){
		DECAF_unregister_callback(DECAF_BLOCK_BEGIN_CB, nd_bb_handle);
		nd_bb_handle = DECAF_NULL_HANDLE;
	}

	//unregister block end callback
	if(nd_be_handle != DECAF_NULL_HANDLE){
		DECAF_unregister_callback(DECAF_BLOCK_END_CB, nd_be_handle);
		nd_be_handle = DECAF_NULL_HANDLE;
	}
}
