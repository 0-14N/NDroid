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
	void hookJniNewString(CPUState* env, int isStart);
	//void hookJniGetStringLength(CPUState* env, int isStart);
	void hookJniGetStringChars(CPUState* env, int isStart);
	void hookJniReleaseStringChars(CPUState* env, int isStart);
	void hookJniNewStringUTF(CPUState* env, int isStart);
	//void hookJniGetStringUTFLength(CPUState* env, int isStart);
	void hookJniGetStringUTFChars(CPUState* env, int isStart);
	void hookJniReleaseStringUTFChars(CPUState* env, int isStart);
	void hookJniGetStringRegion(CPUState* env, int isStart);
	void hookJniGetStringUTFRegion(CPUState* env, int isStart);
	void hookJniGetStringCritical(CPUState* env, int isStart);
	void hookJniReleaseStringCritical(CPUState* env, int isStart);

	//methods called by JNI interfaces relevant to string operations
	void hookDvmCreateStringFromCstr(CPUState* env, int isStart);
	void hookDvmCreateStringFromUnicode(CPUState* env, int isStart);
	void hookDvmStringObjectChars(CPUState* env, int isStart);
	void hookDvmCreateCstrFromString(CPUState* env, int isStart);
	void hookDvmGetStringUtfRegion(CPUState* env, int isStart);

#ifdef __cplusplus
}
#endif

#endif
