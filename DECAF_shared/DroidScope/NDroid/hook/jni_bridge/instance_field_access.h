/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-11-15
 */
#ifndef _JNI_INSTANCE_FIELD_ACCESS_
#define _JNI_INSTANCE_FIELD_ACCESS_

#ifdef __cplusplus

extern "C"
{
#endif

#include "JNI_APIS_OFFSETS.h"
#include "jni_api_hook.h"

	/**
	 * struct Field {
	 * 		ClassObject* clazz;
	 * 		const char*  name;
	 * 		const char*  signature;
	 * 		u4 					 accessFlags;
	 * }
	 *
	 * struct InstField : Field {
	 * 		int 		byteOffset;
	 * }
	 *
	 */
	
#define OFFSET_INSTANCE_FIELD_BYTEOFFSET 16

	jniHookHandler hookInstanceFieldAccess(int curPC, int dvmStartAddr, CPUState* env);

	//JNI interfaces
	void hookGetObjectField(CPUState* env, int isStart);
	void hookGetBooleanField(CPUState* env, int isStart);
	void hookGetByteField(CPUState* env, int isStart);
	void hookGetCharField(CPUState* env, int isStart);
	void hookGetShortField(CPUState* env, int isStart);
	void hookGetIntField(CPUState* env, int isStart);
	void hookGetLongField(CPUState* env, int isStart);
	void hookGetFloatField(CPUState* env, int isStart);
	void hookGetDoubleField(CPUState* env, int isStart);

	void hookSetObjectField(CPUState* env, int isStart);
	void hookSetBooleanField(CPUState* env, int isStart);
	void hookSetByteField(CPUState* env, int isStart);
	void hookSetCharField(CPUState* env, int isStart);
	void hookSetShortField(CPUState* env, int isStart);
	void hookSetIntField(CPUState* env, int isStart);
	void hookSetLongField(CPUState* env, int isStart);
	void hookSetFloatField(CPUState* env, int isStart);
	void hookSetDoubleField(CPUState* env, int isStart);
#ifdef __cplusplus
}
#endif

#endif
