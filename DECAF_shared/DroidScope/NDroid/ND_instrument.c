/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-7-9
 */

#include "ND_instrument.h"
#include "DECAF_shared/DECAF_main.h"
#include "DECAF_shared/DECAF_callback.h"
#include "DECAF_shared/utils/OutputWrapper.h"
#include "DECAF_shared/DroidScope/NDroid/darm/darm.h"
#include "NativeLibraryWhitelist.h"

DECAF_Handle nd_ib_handle = DECAF_NULL_HANDLE;
DECAF_Handle nd_be_handle = DECAF_NULL_HANDLE;

StringHashtable* whitelistLibs = NULL;
StringHashtable* blacklistLibs = NULL;


/*
 * Instruction Begin callback condition function.
 *
 * Since we cannot get process id at translation phase, it 
 */
int nd_instruction_begin_callback_cond(DECAF_callback_type_t cbType, gva_t curPC, gva_t nextPC){
	char moduleName[128];
	moduleName[0] = '\0';
	gva_t startAddr = -1;
	gva_t endAddr = -1;

	if(ND_GLOBAL_TRACING_PID >= 0){
		getModuleInfo(ND_GLOBAL_TRACING_PID, moduleName, 128, &startAddr, &endAddr, curPC);
		if('\0' != moduleName[0]){
			if(!StringHashtable_exist(whitelistLibs, moduleName)){
				DECAF_printf("module name: %s\n", moduleName);
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
	CPUState* env = params->ib.env;
	gva_t cur_pc = params->ib.cur_pc;
	union _tmpARMInsn{
		target_ulong insn;
		char chars[4];
	} tmpARMInsn;
	union _tmpTHUMBInsn{
		unsigned short insn;
		char chars[2];
	} tmpTHUMBInsn;

	//undefined instruction
	if(cur_pc == -1){
		return;
	}
	//THUMB instruction
	if(env->thumb == 1){
		if(DECAF_read_mem(env, cur_pc & 0xfffffffe, tmpTHUMBInsn.chars, 2) != -1){
		}
	}else{
		//ARM instruction
		if(DECAF_read_mem(env, cur_pc, tmpARMInsn.chars, 4) != -1){
			darm_t d;
			darm_str_t str;
			if(darm_armv7_disasm(&d, tmpARMInsn.insn) == 0){
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
}

void nd_instrument_stop(){

}
