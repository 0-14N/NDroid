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
			hookCallVoidMethod(env, 1);
			return hookCallVoidMethod;
	}
	return NULL;
}

/**
 * void CallVoidMethod(JNIEnv *env, jobject obj,
 * jmethodID methodID, ...)
 */
int addressCallVoidMethod = -1;
void hookCallVoidMethod(CPUState* env, int isStart){
	DECAF_printf("CallVoidMethod[%d]\n", isStart);
	if (isStart && addressCallVoidMethod == -1){
		addressCallVoidMethod = env->regs[2];
		DECAF_printf("CallVoidMethod@%x\n", addressCallVoidMethod);
	}else{
		if (addressCallVoidMethod != -1){
			addressCallVoidMethod = -1;
		}
	}
}

/**
 * const Method* dvmGetVirtualizedMethod(const ClassObject* clazz, const Method* meth)
 */
int addressGetVirtulizedMethod = -1;
//int dvmGetVirtulizedMethodHitNum = 0;
void hookDvmGetVirtulizedMethod(CPUState* env, int isStart){
	if(isStart && addressGetVirtulizedMethod == -1){
		if (env->regs[1] == addressCallVoidMethod){
			addressGetVirtulizedMethod = env->regs[1];
			DECAF_printf("	getVirtulizedMethod: 1\n");
		}
		/*
		if(addressGetVirtulizedMethod != -1){
			dvmGetVirtulizedMethodHitNum++;
			return;
		}else if((addressCallVoidMethod != -1) && (env->regs[1] == addressCallVoidMethod)){
			addressGetVirtulizedMethod = env->regs[1];
			DECAF_printf("	getVirtulizedMethod: 1\n");
			return;
		}
		*/
	}else{
		if(addressGetVirtulizedMethod != -1){
			DECAF_printf("		dvmGetVirtulizedMethod: @%x --> @%x\n", 
					addressGetVirtulizedMethod, env->regs[0]);
			DECAF_printf("	getVirtulizedMethod: 0\n");
			addressGetVirtulizedMethod = -1;
			addressCallVoidMethod = env->regs[0];
			/*
			if(--dvmGetVirtulizedMethodHitNum == -1){
				DECAF_printf("		dvmGetVirtulizedMethod: @%x --> @%x\n", addressGetVirtulizedMethod, env->regs[0]);
				DECAF_printf("	getVirtulizedMethod: 0\n");
				addressCallVoidMethod = env->regs[0];
				addressGetVirtulizedMethod = -1;
				dvmGetVirtulizedMethodHitNum = 0;
			}
			*/
		}
	}
}

/**
 * void dvmInterpret(Thread* self, const Method* method, JValue* pResult, u4* rtaint)
 * TODO
 */
int addressDvmInterpret = -1;
//int dvmInterpretHitNum = 0;
void hookDvmInterpret(CPUState* env, int isStart){
	if(isStart && addressDvmInterpret == -1){
		if (env->regs[1] == addressCallVoidMethod){
			DECAF_printf("	dvmInterpret: 1\n");
			DECAF_printf("		dvmInterpret: @%x\n", env->regs[1]);
			addressDvmInterpret = env->regs[1];
		}
		/*
		if(addressDvmInterpret != -1){
			dvmInterpretHitNum++;
			return;
		}else if((env->regs[1] == addressCallVoidMethod) && 
				(addressGetVirtulizedMethod == -1)){
			DECAF_printf("	dvmInterpret: 1 <-- %x\n", env->regs[14]);
			DECAF_printf("		dvmInterpret: @%x\n", env->regs[1]);
			addressDvmInterpret = env->regs[1];
			return;
		}
		*/
	}else{
		if(addressDvmInterpret != -1){
			DECAF_printf("	dvmInterpret: 0\n");
			addressDvmInterpret = -1;
			/*
			if(--dvmInterpretHitNum == -1){
				DECAF_printf("	dvmInterpret: 0\n");
				addressDvmInterpret = -1;
				dvmInterpretHitNum = 0;
			}
			*/
		}
	}
}
