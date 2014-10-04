/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-10-4
 */
#ifndef _SYS_LIB_HOOK_H
#define _SYS_LIB_HOOK_H

#ifdef __cplusplus

extern "C"
{
#endif

	#include "cpu.h"
	#include "DECAF_types.h"

	//modules' start addresses and end addresses
	extern gva_t LIBC_START_ADDR;
	extern gva_t LIBC_END_ADDR;
	extern gva_t LIBM_START_ADDR;
	extern gva_t LIBM_END_ADDR;

	typedef void (*sysLibHookHandler)(CPUState*, int);
	
	int startOfSysLibCalls(int curPC);

	sysLibHookHandler hookSysLibCalls(int curPC, CPUState* env);

#ifdef __cplusplus
}
#endif

#endif
