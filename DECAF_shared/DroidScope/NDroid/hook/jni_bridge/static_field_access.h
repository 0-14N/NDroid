/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-11-16
 */
#ifndef _JNI_STATIC_FIELD_ACCESS_
#define _JNI_STATIC_FIELD_ACCESS_

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
	 * struct StaticField : Field {
	 * 		JValue			value;
	 * 		Taint				taint;
	 * }
	 *
	 */

#define OFFSET_STATIC_FIELD_TAINT 20

	jniHookHandler hookStaticFieldAccess(int curPC, int dvmStartAddr, CPUState* env);

	//JNI interfaces
	void hookGetStaticObjectField(CPUState* env, int isStart);
	void hookGetStaticBooleanField(CPUState* env, int isStart);
	void hookGetStaticByteField(CPUState* env, int isStart);
	void hookGetStaticCharField(CPUState* env, int isStart);
	void hookGetStaticShortField(CPUState* env, int isStart);
	void hookGetStaticIntField(CPUState* env, int isStart);
	void hookGetStaticLongField(CPUState* env, int isStart);
	void hookGetStaticFloatField(CPUState* env, int isStart);
	void hookGetStaticDoubleField(CPUState* env, int isStart);

	void hookSetStaticObjectField(CPUState* env, int isStart);
	void hookSetStaticBooleanField(CPUState* env, int isStart);
	void hookSetStaticByteField(CPUState* env, int isStart);
	void hookSetStaticCharField(CPUState* env, int isStart);
	void hookSetStaticShortField(CPUState* env, int isStart);
	void hookSetStaticIntField(CPUState* env, int isStart);
	void hookSetStaticLongField(CPUState* env, int isStart);
	void hookSetStaticFloatField(CPUState* env, int isStart);
	void hookSetStaticDoubleField(CPUState* env, int isStart);

#ifdef __cplusplus
}
#endif

#endif
