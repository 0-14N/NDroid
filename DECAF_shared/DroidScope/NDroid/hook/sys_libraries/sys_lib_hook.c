/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-10-4
 */
#include "sys_lib_hook.h"
#include "lib_c.h"
#include "lib_m.h"

//modules' start addresses and end addresses
gva_t LIBC_START_ADDR = -1;
gva_t LIBC_END_ADDR = -1;
gva_t LIBM_START_ADDR = -1;
gva_t LIBM_END_ADDR = -1;

/*
int startOfSysLibCalls(int curPC){
	//libc.so calls
	if(startOfLibCCalls(curPC, LIBC_START_ADDR)){
		return (1);
	}

	//libm.so calls
	if(startOfLibMCalls(curPC, LIBM_START_ADDR)){
		return (1);
	}

	return (0);
}
*/

sysLibHookHandler hookSysLibCalls(int curPC, CPUState* env){
	//libc.so calls
	sysLibHookHandler hookHandler = hookLibCCalls(curPC, LIBC_START_ADDR, env);
	if(hookHandler != NULL){
		return (hookHandler);
	}

	//libm.so calls
	hookHandler = hookLibMCalls(curPC, LIBM_START_ADDR, env);
	if(hookHandler != NULL){
		return (hookHandler);
	}

	return (NULL);
}
