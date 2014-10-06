/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-10-2
 */
#ifndef _JNI_INSTANCE_METHOD_CALLING_
#define _JNI_INSTANCE_METHOD_CALLING_

#ifdef __cplusplus

extern "C"
{
#endif

#include "JNI_APIS_OFFSETS.h"
#include "jni_api_hook.h"
	
	int isInstanceMethodCalling(int curPC, int dvmStartAddr);

	jniHookHandler hookInstanceMethodCalling(int curPC, int dvmStartAddr, CPUState* env);

	void callVoidMethod(CPUState* env, int isStart);

	void dvmGetVirtulizedMethod(CPUState* env, int isStart);

	void dvmInterpret(CPUState* env, int isStart);

#ifdef __cplusplus
}
#endif

#endif
