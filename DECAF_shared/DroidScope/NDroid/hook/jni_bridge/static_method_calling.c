/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-11-16
 */

#include "DECAF_shared/utils/OutputWrapper.h"
#include "static_method_calling.h"
#include "../dvm_hook.h"

extern int addrRetVirtulizedMethod;

jniHookHandler hookStaticMethodCalling(int curPC, int dvmStartAddr, CPUState* env){
	switch (curPC - dvmStartAddr){
		case CallStaticVoidMethod_OFFSET:
			hookCallStaticVoidMethod(env, 1);
			return hookCallStaticVoidMethod;
		case CallStaticVoidMethodA_OFFSET:
			hookCallStaticVoidMethodA(env, 1);
			return hookCallStaticVoidMethodA;
		case CallStaticVoidMethodV_OFFSET:
			hookCallStaticVoidMethodV(env, 1);
			return hookCallStaticVoidMethodV;
		case CallStaticObjectMethod_OFFSET:
			hookCallStaticObjectMethod(env, 1);
			return hookCallStaticObjectMethod;
		case CallStaticObjectMethodA_OFFSET:
			hookCallStaticObjectMethodA(env, 1);
			return hookCallStaticObjectMethodA;
		case CallStaticObjectMethodV_OFFSET:
			hookCallStaticObjectMethodV(env, 1);
			return hookCallStaticObjectMethodV;
		case CallStaticBooleanMethod_OFFSET:
			hookCallStaticBooleanMethod(env, 1);
			return hookCallStaticBooleanMethod;
		case CallStaticBooleanMethodA_OFFSET:
			hookCallStaticBooleanMethodA(env, 1);
			return hookCallStaticBooleanMethodA;
		case CallStaticBooleanMethodV_OFFSET:
			hookCallStaticBooleanMethodV(env, 1);
			return hookCallStaticBooleanMethodV;
		case CallStaticByteMethod_OFFSET:
			hookCallStaticByteMethod(env, 1);
			return hookCallStaticByteMethod;
		case CallStaticByteMethodA_OFFSET:
			hookCallStaticByteMethodA(env, 1);
			return hookCallStaticByteMethodA;
		case CallStaticByteMethodV_OFFSET:
			hookCallStaticByteMethodV(env, 1);
			return hookCallStaticByteMethodV;
		case CallStaticCharMethod_OFFSET:
			hookCallStaticCharMethod(env, 1);
			return hookCallStaticCharMethod;
		case CallStaticCharMethodA_OFFSET:
			hookCallStaticCharMethodA(env, 1);
			return hookCallStaticCharMethodA;
		case CallStaticCharMethodV_OFFSET:
			hookCallStaticCharMethodV(env, 1);
			return hookCallStaticCharMethodV;
		case CallStaticShortMethod_OFFSET:
			hookCallStaticShortMethod(env, 1);
			return hookCallStaticShortMethod;
		case CallStaticShortMethodA_OFFSET:
			hookCallStaticShortMethodA(env, 1);
			return hookCallStaticShortMethodA;
		case CallStaticShortMethodV_OFFSET:
			hookCallStaticShortMethodV(env, 1);
			return hookCallStaticShortMethodV;
		case CallStaticIntMethod_OFFSET:
			hookCallStaticIntMethod(env, 1);
			return hookCallStaticIntMethod;
		case CallStaticIntMethodA_OFFSET:
			hookCallStaticIntMethodA(env, 1);
			return hookCallStaticIntMethodA;
		case CallStaticIntMethodV_OFFSET:
			hookCallStaticIntMethodV(env, 1);
			return hookCallStaticIntMethodV;
		case CallStaticLongMethod_OFFSET:
			hookCallStaticLongMethod(env, 1);
			return hookCallStaticLongMethod;
		case CallStaticLongMethodA_OFFSET:
			hookCallStaticLongMethodA(env, 1);
			return hookCallStaticLongMethodA;
		case CallStaticLongMethodV_OFFSET:
			hookCallStaticLongMethodV(env, 1);
			return hookCallStaticLongMethodV;
		case CallStaticFloatMethod_OFFSET:
			hookCallStaticFloatMethod(env, 1);
			return hookCallStaticFloatMethod;
		case CallStaticFloatMethodA_OFFSET:
			hookCallStaticFloatMethodA(env, 1);
			return hookCallStaticFloatMethodA;
		case CallStaticFloatMethodV_OFFSET:
			hookCallStaticFloatMethodV(env, 1);
			return hookCallStaticFloatMethodV;
		case CallStaticDoubleMethod_OFFSET:
			hookCallStaticDoubleMethod(env, 1);
			return hookCallStaticDoubleMethod;
		case CallStaticDoubleMethodA_OFFSET:
			hookCallStaticDoubleMethodA(env, 1);
			return hookCallStaticDoubleMethodA;
		case CallStaticDoubleMethodV_OFFSET:
			hookCallStaticDoubleMethodV(env, 1);
			return hookCallStaticDoubleMethodV;
	}
	return NULL;
}

/*
 *_ctype CallStatic##_jname##Method(JNIEnv* env, jclass jclazz,
 *  	jmethodID methodID, ...)
 */
int addrCallStaticVoidMethod = -1;
void hookCallStaticVoidMethod(CPUState* env, int isStart){
	DECAF_printf("CallStaticVoidMethod[%d]\n", isStart);
	if (isStart && addrCallStaticVoidMethod == -1){
		addrCallStaticVoidMethod = env->regs[2];
		addrRetVirtulizedMethod = env->regs[2];
		DECAF_printf("	CallStaticVoidMethod@%x\n", addrCallStaticVoidMethod);
	}else{
		if (addrCallStaticVoidMethod != -1){
			addrCallStaticVoidMethod = -1;
		}
	}
}

int addrCallStaticVoidMethodA = -1;
void hookCallStaticVoidMethodA(CPUState* env, int isStart){
	DECAF_printf("CallStaticVoidMethodA[%d]\n", isStart);
	if (isStart && addrCallStaticVoidMethodA == -1){
		addrCallStaticVoidMethodA = env->regs[2];
		addrRetVirtulizedMethod = env->regs[2];
		DECAF_printf("	CallStaticVoidMethodA@%x\n", addrCallStaticVoidMethodA);
	}else{
		if (addrCallStaticVoidMethodA != -1){
			addrCallStaticVoidMethodA = -1;
		}
	}
}

int addrCallStaticVoidMethodV = -1;
void hookCallStaticVoidMethodV(CPUState* env, int isStart){
	DECAF_printf("CallStaticVoidMethodV[%d]\n", isStart);
	if (isStart && addrCallStaticVoidMethodV == -1){
		addrCallStaticVoidMethodV = env->regs[2];
		addrRetVirtulizedMethod = env->regs[2];
		DECAF_printf("	CallStaticVoidMethodV@%x\n", addrCallStaticVoidMethodV);
	}else{
		if (addrCallStaticVoidMethodV != -1){
			addrCallStaticVoidMethodV = -1;
		}
	}
}

void hookCallStaticObjectMethod(CPUState* env, int isStart){
	hookCallStaticVoidMethod(env, isStart);
}

void hookCallStaticObjectMethodA(CPUState* env, int isStart){
	hookCallStaticVoidMethodA(env, isStart);
}

void hookCallStaticObjectMethodV(CPUState* env, int isStart){
	hookCallStaticVoidMethodV(env, isStart);
}

void hookCallStaticBooleanMethod(CPUState* env, int isStart){
	hookCallStaticVoidMethod(env, isStart);
}

void hookCallStaticBooleanMethodA(CPUState* env, int isStart){
	hookCallStaticVoidMethodA(env, isStart);
}

void hookCallStaticBooleanMethodV(CPUState* env, int isStart){
	hookCallStaticVoidMethodV(env, isStart);
}

void hookCallStaticByteMethod(CPUState* env, int isStart){
	hookCallStaticVoidMethod(env, isStart);
}

void hookCallStaticByteMethodA(CPUState* env, int isStart){
	hookCallStaticVoidMethodA(env, isStart);
}

void hookCallStaticByteMethodV(CPUState* env, int isStart){
	hookCallStaticVoidMethodV(env, isStart);
}

void hookCallStaticCharMethod(CPUState* env, int isStart){
	hookCallStaticVoidMethod(env, isStart);
}

void hookCallStaticCharMethodA(CPUState* env, int isStart){
	hookCallStaticVoidMethodA(env, isStart);
}

void hookCallStaticCharMethodV(CPUState* env, int isStart){
	hookCallStaticVoidMethodV(env, isStart);
}

void hookCallStaticShortMethod(CPUState* env, int isStart){
	hookCallStaticVoidMethod(env, isStart);
}

void hookCallStaticShortMethodA(CPUState* env, int isStart){
	hookCallStaticVoidMethodA(env, isStart);
}

void hookCallStaticShortMethodV(CPUState* env, int isStart){
	hookCallStaticVoidMethodV(env, isStart);
}

void hookCallStaticIntMethod(CPUState* env, int isStart){
	hookCallStaticVoidMethod(env, isStart);
}

void hookCallStaticIntMethodA(CPUState* env, int isStart){
	hookCallStaticVoidMethodA(env, isStart);
}

void hookCallStaticIntMethodV(CPUState* env, int isStart){
	hookCallStaticVoidMethodV(env, isStart);
}

void hookCallStaticLongMethod(CPUState* env, int isStart){
	hookCallStaticVoidMethod(env, isStart);
}

void hookCallStaticLongMethodA(CPUState* env, int isStart){
	hookCallStaticVoidMethodA(env, isStart);
}

void hookCallStaticLongMethodV(CPUState* env, int isStart){
	hookCallStaticVoidMethodV(env, isStart);
}

void hookCallStaticFloatMethod(CPUState* env, int isStart){
	hookCallStaticVoidMethod(env, isStart);
}

void hookCallStaticFloatMethodA(CPUState* env, int isStart){
	hookCallStaticVoidMethodA(env, isStart);
}

void hookCallStaticFloatMethodV(CPUState* env, int isStart){
	hookCallStaticVoidMethodV(env, isStart);
}

void hookCallStaticDoubleMethod(CPUState* env, int isStart){
	hookCallStaticVoidMethod(env, isStart);
}

void hookCallStaticDoubleMethodA(CPUState* env, int isStart){
	hookCallStaticVoidMethodA(env, isStart);
}

void hookCallStaticDoubleMethodV(CPUState* env, int isStart){
	hookCallStaticVoidMethodV(env, isStart);
}
