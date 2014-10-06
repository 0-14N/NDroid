/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-10-4
 */

#include "DECAF_shared/utils/OutputWrapper.h"
#include "instance_method_calling.h"

int isInstanceMethodCalling(int curPC, int dvmStartAddr){
	switch(curPC - dvmStartAddr){
		case CallVoidMethod_OFFSET:
			return (1);
	}
	return (0);
}

jniHookHandler hookInstanceMethodCalling(int curPC, int dvmStartAddr, CPUState* env){
	switch(curPC - dvmStartAddr){
		case CallVoidMethod_OFFSET:
			callVoidMethod(env, 1);
			return callVoidMethod;
	}
	return NULL;
}

/**
 * void CallVoidMethod(JNIEnv *env, jobject obj,
 * jmethodID methodID, ...)
 */
int addressCallVoidMethod = -1;
void callVoidMethod(CPUState* env, int isStart){
	DECAF_printf("CallVoidMethod[%d]\n", isStart);
	if(isStart){
		addressCallVoidMethod = env->regs[2];
		DECAF_printf("CallVoidMethod@%x\n", addressCallVoidMethod);
	}else{
		addressCallVoidMethod = -1;
	}
}

/**
 * const Method* dvmGetVirtualizedMethod(const ClassObject* clazz, const Method* meth)
 */
int addressGetVirtulizedMethod = -1;
void dvmGetVirtulizedMethod(CPUState* env, int isStart){
	if(isStart){
		if((addressCallVoidMethod != -1) && (env->regs[1] == addressCallVoidMethod)){
			addressGetVirtulizedMethod = env->regs[1];
		}
	}else{
		if(addressGetVirtulizedMethod != -1){
			DECAF_printf("dvmGetVirtulizedMethod: @%x --> @%x\n", addressGetVirtulizedMethod, env->regs[0]);
			addressCallVoidMethod = env->regs[0];
			addressGetVirtulizedMethod = -1;
		}
	}
}

/**
 * void dvmInterpret(Thread* self, const Method* method, JValue* pResult, u4* rtaint)
 */
void dvmInterpret(CPUState* env, int isStart){
	if(isStart){
		if(env->regs[1] == addressCallVoidMethod){
			DECAF_printf("dvmInterpret: @%x\n", env->regs[1]);
		}
	}
}
