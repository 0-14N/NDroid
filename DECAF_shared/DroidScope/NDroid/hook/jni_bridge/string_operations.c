/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-10-2
 */

#include "DECAF_shared/utils/OutputWrapper.h"
#include "string_operations.h"
#include "jni_api_hook.h"

extern int addrJObjDvmDecodeIndirectRef;
extern int addrObjectDvmDecodeIndirectRef;

/**
 * NewString, GetStringLength, GetStringChars, ReleaseStringChars
 * NewStringUTF, GetStringUTFLength, GetStringUTFChars, ReleaseStringUTFChars
 * GetStringRegion, GetStringUTFRegion, GetStringCritical, ReleaseStringCritical
 */
int isStringOperations(int curPC, int dvmStartAddr){
	switch(curPC - dvmStartAddr){
		case NewString_OFFSET:
		//case GetStringLength_OFFSET:
		case GetStringChars_OFFSET:
		case ReleaseStringChars_OFFSET:
		case NewStringUTF_OFFSET:
		//case GetStringUTFLength_OFFSET:
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
			/*
		case GetStringLength_OFFSET:
			hookJniGetStringLength(env, 1);
			return hookJniGetStringLength;
			*/
		case GetStringChars_OFFSET:
			hookJniGetStringChars(env, 1);
			return hookJniGetStringChars;
		case ReleaseStringChars_OFFSET:
			hookJniReleaseStringChars(env, 1);
			return hookJniReleaseStringChars;
		case NewStringUTF_OFFSET:
			hookJniNewStringUTF(env, 1);
			return hookJniNewStringUTF;
			/*
		case GetStringUTFLength_OFFSET:
			hookJniGetStringUTFLength(env, 1);
			return hookJniGetStringUTFLength;
			*/
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

/*
 * jstring NewString(JNIEnv *env, const jchar *unicodeChars, jsize len)
 * -- dvmCreateStringFromUnicode
 */
int addrNewString = -1;
int taintNewString = 0;
void hookJniNewString(CPUState* env, int isStart){
	DECAF_printf("NewString[%d]\n", isStart);
	if (isStart && addrNewString == -1){
		addrNewString = env->regs[1];
		//jchar --> u2
		int i = 0;
		for(; i < env->regs[2] * 2; i++){
			taintNewString |= getTaint(addrNewString + i);
		}
	}else{
		if (addrNewString != -1){
			if (taintNewString > 0){
				addTaint(env->regs[0], taintNewString);
				taintNewString = 0;
			}
			addrNewString = -1;
		}
	}
}

/*
 * StringObject* dvmCreateStringFromUnicode(const u2* unichars, int len)
 */
int addrDvmCreateStringFromUnicode = -1;
void hookDvmCreateStringFromUnicode(CPUState* env, int isStart){
	if (isStart){
		if ((addrDvmCreateStringFromUnicode == -1) &&
				(env->regs[0] == addrNewString)){
			addrDvmCreateStringFromUnicode = env->regs[0];
		}
	}else{
		if (addrDvmCreateStringFromUnicode != -1){
			if (taintNewString > 0) {
				//add taintNewString to StringObject@env->regs[0]
				int charArrayAddr = -1;
				if(DECAF_read_mem(env, env->regs[0] + STRING_INSTANCE_DATA_OFFSET
							, &charArrayAddr, 4) != -1){
					DECAF_printf("dvmCreateStringFromUnicode: add taint %x to %x\n", 
							taintNewString, charArrayAddr + STRING_TAINT_OFFSET);
					assert(DECAF_write_mem(env, charArrayAddr + STRING_TAINT_OFFSET, 
								&taintNewString, 4) != -1);
				}
			}
			addrDvmCreateStringFromUnicode = -1;
		}
	}
}

/*
 * jchar* GetStringChars(JNIEnv* env, jstring jstr, jboolean* isCopy)
 * -- dvmDecodeIndirectRef
 */
void hookJniGetStringChars(CPUState* env, int isStart){
	DECAF_printf("GetStringChars[%d]\n", isStart);
	if (isStart){
	}else{
	}
}

/*
 * void ReleaseStringChars(JNIEnv* env, jstring jstr, const jchar* chars)
 * -- None
 */
void hookJniReleaseStringChars(CPUState* env, int isStart){
	DECAF_printf("ReleaseStringChars[%d]\n", isStart);
}

/**
 * jstring NewStringUTF(JNIEnv *env, const char *bytes)
 * -- dvmCreateStringFromCstr
 */
int taintNewStringUTF = 0;
int addrNewStringUTF = -1;
void hookJniNewStringUTF(CPUState* env, int isStart){
	DECAF_printf("NewStringUTF[%d]\n", isStart);
	if(isStart && addrNewStringUTF == -1){
		taintNewStringUTF = getTaint(env->regs[1]);
		if(taintNewStringUTF > 0){
			DECAF_printf("gTaint[%x]: %x\n", env->regs[1], taintNewStringUTF);
		}
		addrNewStringUTF = env->regs[1];
	}else{
		if (addrNewStringUTF != -1){
			if(taintNewStringUTF > 0){
				addTaint(env->regs[0], taintNewStringUTF);
				DECAF_printf("sTaint[%x]: %x\n", env->regs[0], taintNewStringUTF);
				taintNewStringUTF = 0;
			}
			addrNewStringUTF = -1;
		}
	}
}

/*
 * StringObject* dvmCreateStringFromCstr(const char* utf8Str)
 */
int addrDvmCreateStringFromCstr = -1;
void hookDvmCreateStringFromCstr(CPUState* env, int isStart){
	if(isStart){
		if((addrNewStringUTF != -1) && (addrNewStringUTF == env->regs[0])){
			addrDvmCreateStringFromCstr = addrNewStringUTF;
		}
	}else{
		if(addrDvmCreateStringFromCstr != -1){
			if (taintNewStringUTF > 0) {
				//add taintNewStringUTF to string@env->regs[0]
				int charArrayAddr = -1;
				if(DECAF_read_mem(env, env->regs[0] + STRING_INSTANCE_DATA_OFFSET
							, &charArrayAddr, 4) != -1){
					DECAF_printf("dvmCreateStringFromCstr: add taint %x to %x\n", 
							taintNewStringUTF, charArrayAddr + STRING_TAINT_OFFSET);
					assert(DECAF_write_mem(env, charArrayAddr + STRING_TAINT_OFFSET, 
								&taintNewStringUTF, 4) != -1);
				}
			}
			addrDvmCreateStringFromCstr = -1;
		}
	}
}

/**
 * const char * GetStringUTFChars(JNIEnv *env, jstring string, jboolean *isCopy);
 * -- dvmDecodeIndirectRef
 * -- dvmCreateCstrFromString
 */
int taintGetStringUTFChars = 0;
int addrGetStringUTFChars = -1;
void hookJniGetStringUTFChars(CPUState* env, int isStart){
	DECAF_printf("GetStringUTFChars[%d]\n", isStart);
	if(isStart && addrGetStringUTFChars == -1){
		taintGetStringUTFChars = getTaint(env->regs[1]);
		if(taintGetStringUTFChars > 0){
			DECAF_printf("gTaint[%x]: %x\n", env->regs[1], taintGetStringUTFChars);
		}
		addrGetStringUTFChars = env->regs[1];
		addrJObjDvmDecodeIndirectRef = env->regs[1];
	}else{
		if (addrGetStringUTFChars != -1){
			if(taintGetStringUTFChars > 0){
				addTaint(env->regs[0], taintGetStringUTFChars);
				DECAF_printf("sTaint[%x]: %x\n", env->regs[0], taintGetStringUTFChars);
				taintGetStringUTFChars = 0;

				//if jstring is not tainted, but the StringObject is tainted
				if (getTaint(addrGetStringUTFChars) <= 0){
					addTaint(addrGetStringUTFChars, taintGetStringUTFChars);
				}
			}
			addrGetStringUTFChars = -1;
			addrObjectDvmDecodeIndirectRef = -1;
		}
	}
}

/*
 * char* dvmCreateCstrFromString(const StringObject* jstr)
 */
int addrDvmCreateCstrFromString = -1;
void hookDvmCreateCstrFromString(CPUState* env, int isStart){
	if (isStart) {
		if ((addrGetStringUTFChars != -1) &&
				(addrObjectDvmDecodeIndirectRef == env->regs[0])){
			addrDvmCreateCstrFromString = env->regs[0];
			//get taint of StringObject, set it to taintGetStringUTFChars
			int charArrayAddr = 0;
			int tmpTaint = 0;
			assert(DECAF_read_mem(env, env->regs[0] + STRING_INSTANCE_DATA_OFFSET, 
						&charArrayAddr, 4) != -1);
			assert(DECAF_read_mem(env, charArrayAddr + STRING_TAINT_OFFSET, &tmpTaint, 4) != -1);
			if (tmpTaint > 0){
				taintGetStringUTFChars = tmpTaint;
			}
		}
	}else {
		if (addrDvmCreateCstrFromString != -1){
			addrDvmCreateCstrFromString = -1;
		}
	}
}

/*
 * void ReleaseStringUTFChars(JNIEnv* env, jstring jstr, const char* utf)
 * -- None
 */
void hookJniReleaseStringUTFChars(CPUState* env, int isStart){
	DECAF_printf("ReleaseStringUTFChars[%d]\n", isStart);
}

/*
 * void GetStringRegion(JNIEnv* env, jstring jstr, jsize start, jsize len, jchar* buf)
 * -- StringObject::chars()
 */
void hookJniGetStringRegion(CPUState* env, int isStart){
	DECAF_printf("GetStringRegion[%d]\n", isStart);
}

/*
 * void GetStringUTFRegion(JNIEnv* env, jstring jstr, jsize start, jsize len, char* buf)
 * -- dvmGetStringUtfRegion
 *  -- StringObject::chars()
 */
void hookJniGetStringUTFRegion(CPUState* env, int isStart){
	DECAF_printf("GetStringUTFRegion[%d]\n", isStart);
}

/*
 * jchar* GetStringCritical(JNIEnv* env, jstring jstr, jboolean* isCopy)
 * -- StringObject::chars()
 */
void hookJniGetStringCritical(CPUState* env, int isStart){
	DECAF_printf("GetStringCritical[%d]\n", isStart);
}

/*
 * void ReleaseStringCritical(JNIEnv* env, jstring jstr, const jchar* carray)
 * -- None
 */
void hookJniReleaseStringCritical(CPUState* env, int isStart){
	DECAF_printf("ReleaseStringCritical[%d]\n", isStart);
}

/*
 * void dvmGetStringUtfRegion(const StringObject* jstr, int start, int len, char* buf)
 */
void hookDvmGetStringUtfRegion(CPUState* env, int isStart){
}
