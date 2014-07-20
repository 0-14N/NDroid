/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-7-9
 */

#include "ND_instrument.h"
#include "DECAF_shared/DECAF_main.h"
#include "DECAF_shared/DECAF_callback.h"
#include "DECAF_shared/utils/OutputWrapper.h"
#include "DECAF_shared/DroidScope/NDroid/darm/darm.h"

DECAF_Handle nd_ib_handle = DECAF_NULL_HANDLE;
DECAF_Handle nd_be_handle = DECAF_NULL_HANDLE;

int nd_instruction_begin_callback_cond(DECAF_callback_type_t cbType, gva_t curPC, gva_t nextPC){
	/*
	gva_t task = DECAF_get_current_process(env);
	gpid_t pid = DECAF_get_pid(env, task);
	if(pid == ND_GLOBAL_TRACING_PROCESS->pid){
		return (1);
	}
	*/

	return (0);
}

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
	if(cur_pc & 0x01){
		assert(env->thumb == 1);
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

void nd_instrument_init(){
	nd_ib_handle = DECAF_register_callback(DECAF_INSN_BEGIN_CB, 
																				&nd_instruction_begin_callback, 
																				&nd_instruction_begin_callback_cond);
}

