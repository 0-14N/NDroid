/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-11-16
 */
#ifndef _JNI_STATIC_METHOD_CALLING_
#define _JNI_STATIC_METHOD_CALLING_

#ifdef __cplusplus

extern "C"
{
#endif

#include "JNI_APIS_OFFSETS.h"
#include "jni_api_hook.h"

	jniHookHandler hookStaticMethodCalling(int curPC, int dvmStartAddr, CPUState* env);

	//JNI interfaces
	void hookCallStaticVoidMethod(CPUState* env, int isStart);
	void hookCallStaticVoidMethodA(CPUState* env, int isStart);
	void hookCallStaticVoidMethodV(CPUState* env, int isStart);
	void hookCallStaticObjectMethod(CPUState* env, int isStart);
	void hookCallStaticObjectMethodA(CPUState* env, int isStart);
	void hookCallStaticObjectMethodV(CPUState* env, int isStart);
	void hookCallStaticBooleanMethod(CPUState* env, int isStart);
	void hookCallStaticBooleanMethodA(CPUState* env, int isStart);
	void hookCallStaticBooleanMethodV(CPUState* env, int isStart);
	void hookCallStaticByteMethod(CPUState* env, int isStart);
	void hookCallStaticByteMethodA(CPUState* env, int isStart);
	void hookCallStaticByteMethodV(CPUState* env, int isStart);
	void hookCallStaticCharMethod(CPUState* env, int isStart);
	void hookCallStaticCharMethodA(CPUState* env, int isStart);
	void hookCallStaticCharMethodV(CPUState* env, int isStart);
	void hookCallStaticShortMethod(CPUState* env, int isStart);
	void hookCallStaticShortMethodA(CPUState* env, int isStart);
	void hookCallStaticShortMethodV(CPUState* env, int isStart);
	void hookCallStaticIntMethod(CPUState* env, int isStart);
	void hookCallStaticIntMethodA(CPUState* env, int isStart);
	void hookCallStaticIntMethodV(CPUState* env, int isStart);
	void hookCallStaticLongMethod(CPUState* env, int isStart);
	void hookCallStaticLongMethodA(CPUState* env, int isStart);
	void hookCallStaticLongMethodV(CPUState* env, int isStart);
	void hookCallStaticFloatMethod(CPUState* env, int isStart);
	void hookCallStaticFloatMethodA(CPUState* env, int isStart);
	void hookCallStaticFloatMethodV(CPUState* env, int isStart);
	void hookCallStaticDoubleMethod(CPUState* env, int isStart);
	void hookCallStaticDoubleMethodA(CPUState* env, int isStart);
	void hookCallStaticDoubleMethodV(CPUState* env, int isStart);

#ifdef __cplusplus
}
#endif

#endif
