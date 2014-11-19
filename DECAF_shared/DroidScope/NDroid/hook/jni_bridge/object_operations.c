/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-11-15
 */
#include "DECAF_shared/utils/OutputWrapper.h"
#include "object_operations.h"

extern int addrRetVirtulizedMethod;

jniHookHandler hookObjectOperations(int curPC, int dvmStartAddr, CPUState* env){
	switch (curPC - dvmStartAddr){
		case NewObject_OFFSET:
			hookNewObject(env, 1);
			return hookNewObject;
		case NewObjectA_OFFSET:
			hookNewObjectA(env, 1);
			return hookNewObjectA;
		case NewObjectV_OFFSET:
			hookNewObjectV(env, 1);
			return hookNewObjectV;
	}
	return NULL;
}

//taint for new allocated object,
//set by dvmCallMethod*
int taintNewObjectGeneral = 0;

/*
 * jobject NewObject(JNIEnv* env, jclass jclazz, jmethodID methodID, ...)
 */
int flagNewObject = 0;
void hookNewObject(CPUState* env, int isStart){
	if (isStart && flagNewObject == 0){
		DECAF_printf("NewObject[1]\n");
		addrRetVirtulizedMethod = env->regs[2];
		flagNewObject = 1;
	}else{
		if (flagNewObject){
			if (taintNewObjectGeneral > 0){
				addTaint(env->regs[0], taintNewObjectGeneral);
				DECAF_printf("	add taint: %x to new created object@%x\n", 
						taintNewObjectGeneral, env->regs[0]);
				taintNewObjectGeneral = 0;
			}
			flagNewObject = 0;
			DECAF_printf("NewObject[0]\n");
		}
	}
}

/*
 * jobject NewObjectA(JNIEnv* env, jclass jclazz, jmethodID methodID, jvalue* args)
 */
int flagNewObjectA = 0;
void hookNewObjectA(CPUState* env, int isStart){
	if (isStart && flagNewObjectA == 0){
		DECAF_printf("NewObjectA[1]\n");
		addrRetVirtulizedMethod = env->regs[2];
		flagNewObjectA = 1;
	}else{
		if (flagNewObjectA){
			if (taintNewObjectGeneral > 0){
				addTaint(env->regs[0], taintNewObjectGeneral);
				DECAF_printf("	add taint: %x to new created object@%x\n", 
						taintNewObjectGeneral, env->regs[0]);
				taintNewObjectGeneral = 0;
			}
			flagNewObjectA = 0;
			DECAF_printf("NewObjectA[0]\n");
		}
	}
}

/*
 * jobject NewObjectV(JNIEnv* env, jclass jclazz, jmethodID methodID, va_list args)
 */
int flagNewObjectV = 0;
void hookNewObjectV(CPUState* env, int isStart){
	if (isStart && flagNewObjectV == 0){
		DECAF_printf("NewObjectV[1]\n");
		addrRetVirtulizedMethod = env->regs[2];
		flagNewObjectV = 1;
	}else{
		if (flagNewObjectV){
			if (taintNewObjectGeneral > 0){
				addTaint(env->regs[0], taintNewObjectGeneral);
				DECAF_printf("	add taint: %x to new created object@%x\n", 
						taintNewObjectGeneral, env->regs[0]);
				taintNewObjectGeneral = 0;
			}
			flagNewObjectV = 0;
			DECAF_printf("NewObjectV[0]\n");
		}
	}
}

