/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-10-2
 */

#include "DECAF_shared/utils/OutputWrapper.h"
#include "DECAF_shared/DroidScope/NDroid/ND_instrument.h"
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
int hookStringOperations(int curPC, int dvmStartAddr, CPUState* env){
	switch(curPC - dvmStartAddr){
		case NewString_OFFSET:
			jniNewString(env);
			break;
		case GetStringLength_OFFSET:
			jniGetStringLength(env);
			break;
		case GetStringChars_OFFSET:
			jniGetStringChars(env);
			break;
		case ReleaseStringChars_OFFSET:
			jniReleaseStringChars(env);
			break;
		case NewStringUTF_OFFSET:
			jniNewStringUTF(env);
			break;
		case GetStringUTFLength_OFFSET:
			jniGetStringUTFLength(env);
			break;
		case GetStringUTFChars_OFFSET:
			jniGetStringUTFChars(env);
			break;
		case ReleaseStringUTFChars_OFFSET:
			jniReleaseStringUTFChars(env);
			break;
		case GetStringRegion_OFFSET:
			jniGetStringRegion(env);
			break;
		case GetStringUTFRegion_OFFSET:
			jniGetStringUTFRegion(env);
			break;
		case GetStringCritical_OFFSET:
			jniGetStringCritical(env);
			break;
		case ReleaseStringCritical_OFFSET:
			jniReleaseStringCritical(env);
			break;
	}
	return (0);
}


void jniNewString(CPUState* env){
	DECAF_printf("NewString\n");
}

void jniGetStringLength(CPUState* env){
	DECAF_printf("GetStringLength\n");
}

void jniGetStringChars(CPUState* env){
	DECAF_printf("GetStringChars\n");
}

void jniReleaseStringChars(CPUState* env){
	DECAF_printf("ReleaseStringChars\n");
}

void jniNewStringUTF(CPUState* env){
	DECAF_printf("NewStringUTF\n");
}

void jniGetStringUTFLength(CPUState* env){
	DECAF_printf("GetStringUTFLength\n");
}

void jniGetStringUTFChars(CPUState* env){
	DECAF_printf("GetStringUTFChars\n");
}

void jniReleaseStringUTFChars(CPUState* env){
	DECAF_printf("ReleaseStringUTFChars\n");
}

void jniGetStringRegion(CPUState* env){
	DECAF_printf("GetStringRegion\n");
}

void jniGetStringUTFRegion(CPUState* env){
	DECAF_printf("GetStringUTFRegion\n");
}

void jniGetStringCritical(CPUState* env){
	DECAF_printf("GetStringCritical\n");
}

void jniReleaseStringCritical(CPUState* env){
	DECAF_printf("ReleaseStringCritical\n");
}
