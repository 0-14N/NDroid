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

	int isStringOperations(int curPC, int dvmStartAddr);

	int hookStringOperations(int curPC, int dvmStartAddr, CPUState* env);

  /**
   * NewString, GetStringLength, GetStringChars, ReleaseStringChars
   * NewStringUTF, GetStringUTFLength, GetStringUTFChars, ReleaseStringUTFChars
   * GetStringRegion, GetStringUTFRegion, GetStringCritical, ReleaseStringCritical
   */
	void jniNewString(CPUState* env);
	void jniGetStringLength(CPUState* env);
	void jniGetStringChars(CPUState* env);
	void jniReleaseStringChars(CPUState* env);
	void jniNewStringUTF(CPUState* env);
	void jniGetStringUTFLength(CPUState* env);
	void jniGetStringUTFChars(CPUState* env);
	void jniReleaseStringUTFChars(CPUState* env);
	void jniGetStringRegion(CPUState* env);
	void jniGetStringUTFRegion(CPUState* env);
	void jniGetStringCritical(CPUState* env);
	void jniReleaseStringCritical(CPUState* env);

#ifdef __cplusplus
}
#endif

#endif
