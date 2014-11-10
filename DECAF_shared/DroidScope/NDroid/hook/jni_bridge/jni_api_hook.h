/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-10-3
 */
#ifndef _JNI_API_HOOK_H
#define _JNI_API_HOOK_H

#ifdef __cplusplus

extern "C"
{
#endif
	#include "cpu.h"
	#include "TaintEngine.h"
  #include "dvm_hook.h"
  #include "DECAF_main.h"

	typedef void (*jniHookHandler)(CPUState*, int);

	//int startOfJniApis(int curPC, int dvmStartAddr);

	jniHookHandler hookJniApis(int curPC, int dvmStartAddr, CPUState* env);

#ifdef __cplusplus
}
#endif

#endif
