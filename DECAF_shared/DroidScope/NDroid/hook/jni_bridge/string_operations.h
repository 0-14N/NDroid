/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-10-2
 */
#ifndef _JNI_STRING_OPERATIONS_
#define _JNI_STRING_OPERATIONS_

#ifdef __cplusplus

extern "C"
{
#endif

#include "JNI_APIS_OFFSETS.h"
#include "cpu.h"
#include "jni_api_hook.h"

	int isStringOperations(int curPC, int dvmStartAddr);

	jniHookHandler hookStringOperations(int curPC, int dvmStartAddr, CPUState* env);

  /**
   * NewString, GetStringLength, GetStringChars, ReleaseStringChars
   * NewStringUTF, GetStringUTFLength, GetStringUTFChars, ReleaseStringUTFChars
   * GetStringRegion, GetStringUTFRegion, GetStringCritical, ReleaseStringCritical
   */
	void jniNewString(CPUState* env, int isStart);
	void jniGetStringLength(CPUState* env, int isStart);
	void jniGetStringChars(CPUState* env, int isStart);
	void jniReleaseStringChars(CPUState* env, int isStart);
	void jniNewStringUTF(CPUState* env, int isStart);
	void jniGetStringUTFLength(CPUState* env, int isStart);
	void jniGetStringUTFChars(CPUState* env, int isStart);
	void jniReleaseStringUTFChars(CPUState* env, int isStart);
	void jniGetStringRegion(CPUState* env, int isStart);
	void jniGetStringUTFRegion(CPUState* env, int isStart);
	void jniGetStringCritical(CPUState* env, int isStart);
	void jniReleaseStringCritical(CPUState* env, int isStart);

#ifdef __cplusplus
}
#endif

#endif
