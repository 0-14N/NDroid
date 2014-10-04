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
#include "jni_api_hook.h"

	int isStringOperations(int curPC, int dvmStartAddr);

	jniHookHandler hookStringOperations(int curPC, int dvmStartAddr, CPUState* env);


  /**
   * NewString, GetStringLength, GetStringChars, ReleaseStringChars
   * NewStringUTF, GetStringUTFLength, GetStringUTFChars, ReleaseStringUTFChars
   * GetStringRegion, GetStringUTFRegion, GetStringCritical, ReleaseStringCritical
   */
	void jniNewString(CPUState* env, int isBefore);
	void jniGetStringLength(CPUState* env, int isBefore);
	void jniGetStringChars(CPUState* env, int isBefore);
	void jniReleaseStringChars(CPUState* env, int isBefore);
	void jniNewStringUTF(CPUState* env, int isBefore);
	void jniGetStringUTFLength(CPUState* env, int isBefore);
	void jniGetStringUTFChars(CPUState* env, int isBefore);
	void jniReleaseStringUTFChars(CPUState* env, int isBefore);
	void jniGetStringRegion(CPUState* env, int isBefore);
	void jniGetStringUTFRegion(CPUState* env, int isBefore);
	void jniGetStringCritical(CPUState* env, int isBefore);
	void jniReleaseStringCritical(CPUState* env, int isBefore);

#ifdef __cplusplus
}
#endif

#endif
