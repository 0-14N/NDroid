/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-11-17
 */
#ifndef _JNI_ARRAY_OPERATIONS_
#define _JNI_ARRAY_OPERATIONS_

#ifdef __cplusplus

extern "C"
{
#endif

#include "JNI_APIS_OFFSETS.h"
#include "jni_api_hook.h"

	jniHookHandler hookArrayOperations(int curPC, int dvmStartAddr, CPUState* env);

	//JNI interfaces
	void hookNewObjectArray(CPUState* env, int isStart);

	void hookGetObjectArrayElement(CPUState* env, int isStart);
	void hookSetObjectArrayElement(CPUState* env, int isStart);

	void hookGetBooleanArrayElements(CPUState* env, int isStart);
	void hookGetByteArrayElements(CPUState* env, int isStart);
	void hookGetCharArrayElements(CPUState* env, int isStart);
	void hookGetShortArrayElements(CPUState* env, int isStart);
	void hookGetIntArrayElements(CPUState* env, int isStart);
	void hookGetLongArrayElements(CPUState* env, int isStart);
	void hookGetFloatArrayElements(CPUState* env, int isStart);
	void hookGetDoubleArrayElements(CPUState* env, int isStart);

	void hookReleaseBooleanArrayElements(CPUState* env, int isStart);
	void hookReleaseByteArrayElements(CPUState* env, int isStart);
	void hookReleaseCharArrayElements(CPUState* env, int isStart);
	void hookReleaseShortArrayElements(CPUState* env, int isStart);
	void hookReleaseIntArrayElements(CPUState* env, int isStart);
	void hookReleaseLongArrayElements(CPUState* env, int isStart);
	void hookReleaseFloatArrayElements(CPUState* env, int isStart);
	void hookReleaseDoubleArrayElements(CPUState* env, int isStart);

	void hookGetBooleanArrayRegion(CPUState* env, int isStart);
	void hookGetByteArrayRegion(CPUState* env, int isStart);
	void hookGetCharArrayRegion(CPUState* env, int isStart);
	void hookGetShortArrayRegion(CPUState* env, int isStart);
	void hookGetIntArrayRegion(CPUState* env, int isStart);
	void hookGetLongArrayRegion(CPUState* env, int isStart);
	void hookGetFloatArrayRegion(CPUState* env, int isStart);
	void hookGetDoubleArrayRegion(CPUState* env, int isStart);

	void hookSetBooleanArrayRegion(CPUState* env, int isStart);
	void hookSetByteArrayRegion(CPUState* env, int isStart);
	void hookSetCharArrayRegion(CPUState* env, int isStart);
	void hookSetShortArrayRegion(CPUState* env, int isStart);
	void hookSetIntArrayRegion(CPUState* env, int isStart);
	void hookSetLongArrayRegion(CPUState* env, int isStart);
	void hookSetFloatArrayRegion(CPUState* env, int isStart);
	void hookSetDoubleArrayRegion(CPUState* env, int isStart);
	
	void hookGetPrimitiveArrayCritical(CPUState* env, int isStart);
	void hookReleasePrimitiveArrayCritical(CPUState* env, int isStart);
#ifdef __cplusplus
}
#endif

#endif

