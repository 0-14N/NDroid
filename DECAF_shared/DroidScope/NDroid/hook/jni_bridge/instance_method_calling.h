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
	
	jniHookHandler hookInstanceMethodCalling(int curPC, int dvmStartAddr, CPUState* env);

	//JNI interfaces
	void hookCallVoidMethod(CPUState* env, int isStart);
	void hookCallVoidMethodA(CPUState* env, int isStart);
	void hookCallVoidMethodV(CPUState* env, int isStart);
	void hookCallObjectMethod(CPUState* env, int isStart);
	void hookCallObjectMethodA(CPUState* env, int isStart);
	void hookCallObjectMethodV(CPUState* env, int isStart);
	void hookCallBooleanMethod(CPUState* env, int isStart);
	void hookCallBooleanMethodA(CPUState* env, int isStart);
	void hookCallBooleanMethodV(CPUState* env, int isStart);
	void hookCallByteMethod(CPUState* env, int isStart);
	void hookCallByteMethodA(CPUState* env, int isStart);
	void hookCallByteMethodV(CPUState* env, int isStart);
	void hookCallCharMethod(CPUState* env, int isStart);
	void hookCallCharMethodA(CPUState* env, int isStart);
	void hookCallCharMethodV(CPUState* env, int isStart);
	void hookCallShortMethod(CPUState* env, int isStart);
	void hookCallShortMethodA(CPUState* env, int isStart);
	void hookCallShortMethodV(CPUState* env, int isStart);
	void hookCallIntMethod(CPUState* env, int isStart);
	void hookCallIntMethodA(CPUState* env, int isStart);
	void hookCallIntMethodV(CPUState* env, int isStart);
	void hookCallLongMethod(CPUState* env, int isStart);
	void hookCallLongMethodA(CPUState* env, int isStart);
	void hookCallLongMethodV(CPUState* env, int isStart);
	void hookCallFloatMethod(CPUState* env, int isStart);
	void hookCallFloatMethodA(CPUState* env, int isStart);
	void hookCallFloatMethodV(CPUState* env, int isStart);
	void hookCallDoubleMethod(CPUState* env, int isStart);
	void hookCallDoubleMethodA(CPUState* env, int isStart);
	void hookCallDoubleMethodV(CPUState* env, int isStart);

	//dvm methods
	void hookDvmCallMethodV(CPUState* env, int isStart);
	void hookDvmCallMethodA(CPUState* env, int isStart);
	void hookDvmGetVirtulizedMethod(CPUState* env, int isStart);
	void hookDvmInterpret(CPUState* env, int isStart);

#ifdef __cplusplus
}
#endif

#endif
