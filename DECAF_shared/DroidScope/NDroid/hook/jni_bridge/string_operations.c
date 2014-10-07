/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-10-2
 */

#include "DECAF_shared/utils/OutputWrapper.h"
#include "string_operations.h"
#include "jni_api_hook.h"

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
			hookJniNewString(env, 1);
			return hookJniNewString;
		case GetStringLength_OFFSET:
			hookJniGetStringLength(env, 1);
			return hookJniGetStringLength;
		case GetStringChars_OFFSET:
			hookJniGetStringChars(env, 1);
			return hookJniGetStringChars;
		case ReleaseStringChars_OFFSET:
			hookJniReleaseStringChars(env, 1);
			return hookJniReleaseStringChars;
		case NewStringUTF_OFFSET:
			hookJniNewStringUTF(env, 1);
			return hookJniNewStringUTF;
		case GetStringUTFLength_OFFSET:
			hookJniGetStringUTFLength(env, 1);
			return hookJniGetStringUTFLength;
		case GetStringUTFChars_OFFSET:
			hookJniGetStringUTFChars(env, 1);
			return hookJniGetStringUTFChars;
		case ReleaseStringUTFChars_OFFSET:
			hookJniReleaseStringUTFChars(env, 1);
			return hookJniReleaseStringUTFChars;
		case GetStringRegion_OFFSET:
			hookJniGetStringRegion(env, 1);
			return hookJniGetStringRegion;
		case GetStringUTFRegion_OFFSET:
			hookJniGetStringUTFRegion(env, 1);
			return hookJniGetStringUTFRegion;
		case GetStringCritical_OFFSET:
			hookJniGetStringCritical(env, 1);
			return hookJniGetStringCritical;
		case ReleaseStringCritical_OFFSET:
			hookJniReleaseStringCritical(env, 1);
			return hookJniReleaseStringCritical;
	}
	return NULL;
}


void hookJniNewString(CPUState* env, int isStart){
	DECAF_printf("NewString[%d]\n", isStart);
}

void hookJniGetStringLength(CPUState* env, int isStart){
	DECAF_printf("GetStringLength[%d]\n", isStart);
}

void hookJniGetStringChars(CPUState* env, int isStart){
	DECAF_printf("GetStringChars[%d]\n", isStart);
}

void hookJniReleaseStringChars(CPUState* env, int isStart){
	DECAF_printf("ReleaseStringChars[%d]\n", isStart);
}

/**
 * jstring NewStringUTF(JNIEnv *env, const char *bytes)
 */
int taintNewStringUTF = 0;
int addressNewStringUTF = -1;
void hookJniNewStringUTF(CPUState* env, int isStart){
	DECAF_printf("NewStringUTF[%d]\n", isStart);
	if(isStart){
		taintNewStringUTF = getTaint(env->regs[1]);
		if(taintNewStringUTF > 0){
			DECAF_printf("gTaint[%x]: %x\n", env->regs[1], taintNewStringUTF);
		}
		addressNewStringUTF = env->regs[1];
	}else{
		if(taintNewStringUTF > 0){
			addTaint(env->regs[0], taintNewStringUTF);
			DECAF_printf("sTaint[%x]: %x\n", env->regs[0], taintNewStringUTF);
			taintNewStringUTF = 0;
		}
		addressNewStringUTF = -1;
	}
}

void hookJniGetStringUTFLength(CPUState* env, int isStart){
	DECAF_printf("GetStringUTFLength[%d]\n", isStart);
}

/**
 * const char * GetStringUTFChars(JNIEnv *env, jstring string,
 * jboolean *isCopy);
 */
int taintGetStringUTFChars = 0;
void hookJniGetStringUTFChars(CPUState* env, int isStart){
	DECAF_printf("GetStringUTFChars[%d]\n", isStart);
	if(isStart){
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

void hookJniReleaseStringUTFChars(CPUState* env, int isStart){
	DECAF_printf("ReleaseStringUTFChars[%d]\n", isStart);
}

void hookJniGetStringRegion(CPUState* env, int isStart){
	DECAF_printf("GetStringRegion[%d]\n", isStart);
}

void hookJniGetStringUTFRegion(CPUState* env, int isStart){
	DECAF_printf("GetStringUTFRegion[%d]\n", isStart);
}

void hookJniGetStringCritical(CPUState* env, int isStart){
	DECAF_printf("GetStringCritical[%d]\n", isStart);
}

void hookJniReleaseStringCritical(CPUState* env, int isStart){
	DECAF_printf("ReleaseStringCritical[%d]\n", isStart);
}

/**
 * StringObject* dvmCreateStringFromCstr(const char* utf8Str)
 */
int addressDvmCreateStringFromCstr = -1;
void hookDvmCreateStringFromCstr(CPUState* env, int isStart){
	if(isStart){
		if((addressNewStringUTF != -1) && (addressNewStringUTF == env->regs[0])){
			addressDvmCreateStringFromCstr = addressNewStringUTF;
		}
	}else{
		if((addressDvmCreateStringFromCstr != -1) &&
				(taintNewStringUTF > 0)){
			//add taintNewStringUTF to string@env->regs[0]
			int charArrayAddr = -1;
			if(DECAF_read_mem(env, env->regs[0] + STRING_INSTANCE_DATA_OFFSET
						, &charArrayAddr, 4) != -1){
				DECAF_printf("dvmCreateStringFromCstr: add taint %x to %x\n", 
						taintNewStringUTF, charArrayAddr + STRING_TAINT_OFFSET);
				assert(DECAF_write_mem(env, charArrayAddr + STRING_TAINT_OFFSET, 
							&taintNewStringUTF, 4) != -1);
			}

			addressDvmCreateStringFromCstr = -1;
		}
	}
}















