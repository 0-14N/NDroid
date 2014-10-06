/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-10-2
 */

#include "DECAF_shared/utils/OutputWrapper.h"
#include "string_operations.h"

/**
 * NewString, GetStringLength, GetStringChars, ReleaseStringChars
 * NewStringUTF, GetStringUTFLength, GetStringUTFChars, ReleaseStringUTFChars
 * GetStringRegion, GetStringUTFRegion, GetStringCritical, ReleaseStringCritical
 */
int isStringOperations(int curPC, int dvmStartAddr){
	switch(curPC - dvmStartAddr){
		case NewString_OFFSET:
		case GetStringLength_OFFSET:
		case GetStringChars_OFFSET:
		case ReleaseStringChars_OFFSET:
		case NewStringUTF_OFFSET:
		case GetStringUTFLength_OFFSET:
		case GetStringUTFChars_OFFSET:
		case ReleaseStringUTFChars_OFFSET:
		case GetStringRegion_OFFSET:
		case GetStringUTFRegion_OFFSET:
		case GetStringCritical_OFFSET:
		case ReleaseStringCritical_OFFSET:
			return (1);
		default:
			return (0);
	}
	return (0);
}

/**
 * NewString, GetStringLength, GetStringChars, ReleaseStringChars
 * NewStringUTF, GetStringUTFLength, GetStringUTFChars, ReleaseStringUTFChars
 * GetStringRegion, GetStringUTFRegion, GetStringCritical, ReleaseStringCritical
 */
jniHookHandler hookStringOperations(int curPC, int dvmStartAddr, CPUState* env){
	switch(curPC - dvmStartAddr){
		case NewString_OFFSET:
			jniNewString(env, 1);
			return jniNewString;
		case GetStringLength_OFFSET:
			jniGetStringLength(env, 1);
			return jniGetStringLength;
		case GetStringChars_OFFSET:
			jniGetStringChars(env, 1);
			return jniGetStringChars;
		case ReleaseStringChars_OFFSET:
			jniReleaseStringChars(env, 1);
			return jniReleaseStringChars;
		case NewStringUTF_OFFSET:
			jniNewStringUTF(env, 1);
			return jniNewStringUTF;
		case GetStringUTFLength_OFFSET:
			jniGetStringUTFLength(env, 1);
			return jniGetStringUTFLength;
		case GetStringUTFChars_OFFSET:
			jniGetStringUTFChars(env, 1);
			return jniGetStringUTFChars;
		case ReleaseStringUTFChars_OFFSET:
			jniReleaseStringUTFChars(env, 1);
			return jniReleaseStringUTFChars;
		case GetStringRegion_OFFSET:
			jniGetStringRegion(env, 1);
			return jniGetStringRegion;
		case GetStringUTFRegion_OFFSET:
			jniGetStringUTFRegion(env, 1);
			return jniGetStringUTFRegion;
		case GetStringCritical_OFFSET:
			jniGetStringCritical(env, 1);
			return jniGetStringCritical;
		case ReleaseStringCritical_OFFSET:
			jniReleaseStringCritical(env, 1);
			return jniReleaseStringCritical;
	}
	return NULL;
}


void jniNewString(CPUState* env, int isBefore){
	DECAF_printf("NewString[%d]\n", isBefore);
}

void jniGetStringLength(CPUState* env, int isBefore){
	DECAF_printf("GetStringLength[%d]\n", isBefore);
}

void jniGetStringChars(CPUState* env, int isBefore){
	DECAF_printf("GetStringChars[%d]\n", isBefore);
}

void jniReleaseStringChars(CPUState* env, int isBefore){
	DECAF_printf("ReleaseStringChars[%d]\n", isBefore);
}

/**
 * jstring NewStringUTF(JNIEnv *env, const char *bytes)
 */
int taintNewStringUTF = 0;
void jniNewStringUTF(CPUState* env, int isBefore){
	DECAF_printf("NewStringUTF[%d]\n", isBefore);
	if(isBefore){
		taintNewStringUTF = getTaint(env->regs[1]);
		if(taintNewStringUTF > 0){
			DECAF_printf("gTaint[%x]: %x\n", env->regs[1], taintNewStringUTF);
		}
	}else{
		if(taintNewStringUTF > 0){
			addTaint(env->regs[0], taintNewStringUTF);
			DECAF_printf("sTaint[%x]: %x\n", env->regs[0], taintNewStringUTF);
			taintNewStringUTF = 0;
		}
	}
}

void jniGetStringUTFLength(CPUState* env, int isBefore){
	DECAF_printf("GetStringUTFLength[%d]\n", isBefore);
}

/**
 * const char * GetStringUTFChars(JNIEnv *env, jstring string,
 * jboolean *isCopy);
 */
int taintGetStringUTFChars = 0;
void jniGetStringUTFChars(CPUState* env, int isBefore){
	DECAF_printf("GetStringUTFChars[%d]\n", isBefore);
	if(isBefore){
		taintGetStringUTFChars = getTaint(env->regs[1]);
		if(taintGetStringUTFChars > 0){
			DECAF_printf("gTaint[%x]: %x\n", env->regs[1], taintGetStringUTFChars);
		}
	}else{
		if(taintGetStringUTFChars > 0){
			addTaint(env->regs[0], taintGetStringUTFChars);
			DECAF_printf("sTaint[%x]: %x\n", env->regs[0], taintGetStringUTFChars);
			taintGetStringUTFChars = 0;
		}
	}
}

void jniReleaseStringUTFChars(CPUState* env, int isBefore){
	DECAF_printf("ReleaseStringUTFChars[%d]\n", isBefore);
}

void jniGetStringRegion(CPUState* env, int isBefore){
	DECAF_printf("GetStringRegion[%d]\n", isBefore);
}

void jniGetStringUTFRegion(CPUState* env, int isBefore){
	DECAF_printf("GetStringUTFRegion[%d]\n", isBefore);
}

void jniGetStringCritical(CPUState* env, int isBefore){
	DECAF_printf("GetStringCritical[%d]\n", isBefore);
}

void jniReleaseStringCritical(CPUState* env, int isBefore){
	DECAF_printf("ReleaseStringCritical[%d]\n", isBefore);
}
