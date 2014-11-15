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
/*
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
*/

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
				DECAF_printf("	add taint %x to %x\n", taintNewString, env->regs[0]);
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
	if (isStart && addrDvmCreateStringFromUnicode == -1){
		if ((addrNewString != -1) &&
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
 *  TODO: Currently, we cannot get the length of jchar*,
 *  maybe API like DECAF_get_string_length is required.
 */
int addrGetStringChars = -1;
int taintGetStringChars = 0;
void hookJniGetStringChars(CPUState* env, int isStart){
	DECAF_printf("GetStringChars[%d]\n", isStart);
	if (isStart && addrGetStringChars == -1){
		addrGetStringChars = env->regs[1];
		addrJObjDvmDecodeIndirectRef = env->regs[1];
		taintGetStringChars = getTaint(env->regs[1]);
	}else{
		if (addrGetStringChars != -1){
			assert(addrObjectDvmDecodeIndirectRef != -1);
			//get taint of StringObject@addrObjectDvmDecodeIndirectRef
			int charArrayAddr = 0;
			int tmpTaint = 0;
			assert(DECAF_read_mem(env, 
						addrObjectDvmDecodeIndirectRef + STRING_INSTANCE_DATA_OFFSET, 
						&charArrayAddr, 4) != -1);
			assert(DECAF_read_mem(env, charArrayAddr + STRING_TAINT_OFFSET, &tmpTaint, 4) != -1);
			taintGetStringChars |= tmpTaint;
			if (taintGetStringChars > 0){
				addTaint(env->regs[0], taintGetStringChars);
				taintGetStringChars = 0;
			}

			addrObjectDvmDecodeIndirectRef = -1;
			addrGetStringChars = -1;
		}
	}
}

/*
 * void ReleaseStringChars(JNIEnv* env, jstring jstr, const jchar* chars)
 * -- None
 */
void hookJniReleaseStringChars(CPUState* env, int isStart){
	DECAF_printf("ReleaseStringChars[%d]\n", isStart);
	if (isStart){
		clearTaint(env->regs[1]);		
	}
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
	if(isStart && addrDvmCreateStringFromCstr == -1){
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
 *  TODO: get string length of char*
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
			assert(addrObjectDvmDecodeIndirectRef != -1);
			//get taint of StringObject@addrObjectDvmDecodeIndirectRef
			int charArrayAddr = 0;
			int tmpTaint = 0;
			assert(DECAF_read_mem(env, 
						addrObjectDvmDecodeIndirectRef + STRING_INSTANCE_DATA_OFFSET, 
						&charArrayAddr, 4) != -1);
			assert(DECAF_read_mem(env, charArrayAddr + STRING_TAINT_OFFSET, &tmpTaint, 4) != -1);
			taintGetStringUTFChars |= tmpTaint;

			if(taintGetStringUTFChars > 0){
				addTaint(env->regs[0], taintGetStringUTFChars);
				DECAF_printf("sTaint[%x]: %x\n", env->regs[0], taintGetStringUTFChars);
				taintGetStringUTFChars = 0;
			}

			addrGetStringUTFChars = -1;
			addrObjectDvmDecodeIndirectRef = -1;
		}
	}
}

/*
 * void ReleaseStringUTFChars(JNIEnv* env, jstring jstr, const char* utf)
 * -- None
 */
void hookJniReleaseStringUTFChars(CPUState* env, int isStart){
	DECAF_printf("ReleaseStringUTFChars[%d]\n", isStart);
	if (isStart){
		clearTaint(env->regs[2]);
	}
}

/*
 * void GetStringRegion(JNIEnv* env, jstring jstr, jsize start, jsize len, jchar* buf)
 * -- dvmDecodeIndirectRef
 */
int addrGetStringRegion = -1;
int lenGetStringRegion = 0;
int bufGetStringRegion = 0;
int taintGetStringRegion = 0;
void hookJniGetStringRegion(CPUState* env, int isStart){
	DECAF_printf("GetStringRegion[%d]\n", isStart);
	if (isStart && addrGetStringRegion == -1){
		addrGetStringRegion = env->regs[1];
		lenGetStringRegion = env->regs[3];
		assert(DECAF_read_mem(env, env->regs[13], &bufGetStringRegion, 4) != -1);
		taintGetStringRegion = getTaint(env->regs[1]);
		//set dvmDecodeIndirectRef's argument
		addrJObjDvmDecodeIndirectRef = env->regs[1];
	}else{
		if (addrGetStringRegion != -1){
			assert(addrObjectDvmDecodeIndirectRef != -1);
			//get taint of StringObject@addrObjectDvmDecodeIndirectRef
			int charArrayAddr = 0;
			int tmpTaint = 0;
			assert(DECAF_read_mem(env, 
						addrObjectDvmDecodeIndirectRef + STRING_INSTANCE_DATA_OFFSET, 
						&charArrayAddr, 4) != -1);
			assert(DECAF_read_mem(env, charArrayAddr + STRING_TAINT_OFFSET, &tmpTaint, 4) != -1);
			taintGetStringRegion |= tmpTaint;

			if(taintGetStringRegion > 0){
				int i = 0;
				for(; i < lenGetStringRegion * 2; i++){
					addTaint(bufGetStringRegion + i, taintGetStringRegion);
				}
				taintGetStringRegion = 0;
			}

			addrGetStringRegion = -1;
			lenGetStringRegion = 0;
			bufGetStringRegion = 0;
			addrObjectDvmDecodeIndirectRef = -1;
		}
	}
}

/*
 * void GetStringUTFRegion(JNIEnv* env, jstring jstr, jsize start, jsize len, char* buf)
 *  -- dvmDecodeIndirectRef
 */
int addrGetStringUTFRegion = -1;
int lenGetStringUTFRegion = 0;
int bufGetStringUTFRegion = 0;
int taintGetStringUTFRegion = 0;
void hookJniGetStringUTFRegion(CPUState* env, int isStart){
	DECAF_printf("GetStringUTFRegion[%d]\n", isStart);
	if (isStart && addrGetStringUTFRegion == -1){
		addrGetStringUTFRegion = env->regs[1];
		lenGetStringUTFRegion = env->regs[3];
		assert(DECAF_read_mem(env, env->regs[13], &bufGetStringUTFRegion, 4) != -1);
		taintGetStringUTFRegion = getTaint(env->regs[1]);
		addrJObjDvmDecodeIndirectRef = env->regs[1];
	}else{
		if (addrGetStringUTFRegion != -1){
			assert(addrObjectDvmDecodeIndirectRef != -1);
			//get taint of StringObject@addrObjectDvmDecodeIndirectRef
			int charArrayAddr = 0;
			int tmpTaint = 0;
			assert(DECAF_read_mem(env, 
						addrObjectDvmDecodeIndirectRef + STRING_INSTANCE_DATA_OFFSET, 
						&charArrayAddr, 4) != -1);
			assert(DECAF_read_mem(env, charArrayAddr + STRING_TAINT_OFFSET, &tmpTaint, 4) != -1);
			taintGetStringUTFRegion |= tmpTaint;

			if(taintGetStringUTFRegion > 0){
				int i = 0;
				for(; i < lenGetStringUTFRegion; i++){
					addTaint(bufGetStringUTFRegion + i, taintGetStringUTFRegion);
				}
				taintGetStringUTFRegion = 0;
			}

			addrGetStringUTFRegion = -1;
			lenGetStringUTFRegion = 0;
			taintGetStringUTFRegion = 0;
			addrObjectDvmDecodeIndirectRef = -1;
		}
	}
}

/*
 * jchar* GetStringCritical(JNIEnv* env, jstring jstr, jboolean* isCopy)
 * -- dvmDecodeIndirectRef
 *  TODO: get length of jchar*
 */
int addrGetStringCritical = -1;
int taintGetStringCritical = 0;
void hookJniGetStringCritical(CPUState* env, int isStart){
	DECAF_printf("GetStringCritical[%d]\n", isStart);
	if (isStart && addrGetStringCritical == -1){
		addrGetStringCritical = env->regs[1];
		taintGetStringCritical = getTaint(env->regs[1]);
		addrJObjDvmDecodeIndirectRef = env->regs[1];
	}else{
		if (addrGetStringCritical != -1){
			assert(addrObjectDvmDecodeIndirectRef != -1);
			//get taint of StringObject@addrObjectDvmDecodeIndirectRef
			int charArrayAddr = 0;
			int tmpTaint = 0;
			assert(DECAF_read_mem(env, 
						addrObjectDvmDecodeIndirectRef + STRING_INSTANCE_DATA_OFFSET, 
						&charArrayAddr, 4) != -1);
			assert(DECAF_read_mem(env, charArrayAddr + STRING_TAINT_OFFSET, &tmpTaint, 4) != -1);
			taintGetStringCritical |= tmpTaint;
			if (taintGetStringCritical > 0){
				addTaint(env->regs[0], taintGetStringCritical);
				taintGetStringCritical = 0;
			}

			addrGetStringCritical = -1;
			addrObjectDvmDecodeIndirectRef = -1;
		}
	}
}

/*
 * void ReleaseStringCritical(JNIEnv* env, jstring jstr, const jchar* carray)
 * -- None
 */
void hookJniReleaseStringCritical(CPUState* env, int isStart){
	DECAF_printf("ReleaseStringCritical[%d]\n", isStart);
	if (isStart){
		clearTaint(env->regs[1]);
	}
}

