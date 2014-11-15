/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-11-15
 */
#ifndef _JNI_OBJECT_OPERATIONS_
#define _JNI_OBJECT_OPERATIONS_

#ifdef __cplusplus

extern "C"
{
#endif

#include "JNI_APIS_OFFSETS.h"
#include "jni_api_hook.h"

	jniHookHandler hookObjectOperations(int curPC, int dvmStartAddr, CPUState* env);

	//JNI interfaces
	void hookNewObject(CPUState* env, int isStart);
	void hookNewObjectA(CPUState* env, int isStart);
	void hookNewObjectV(CPUState* env, int isStart);

#ifdef __cplusplus
}
#endif

#endif
