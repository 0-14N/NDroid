/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-10-4
 */

#include "DECAF_shared/utils/OutputWrapper.h"
#include "instance_method_calling.h"
#include "../dvm_hook.h"

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
 * void dvmInterpret(Thread* self, const Method* method, JValue* pResult, u4* rtaint)
 * TODO
 */
int addrDvmInterpret = -1;
int flagDvmInterpret = 0;
int *taintsDvmInterpret = NULL;
void hookDvmInterpret(CPUState* env, int isStart){
	if(isStart && addrDvmInterpret != -1 && flagDvmInterpret == 0){
		if (env->regs[1] == addrDvmInterpret){
			DECAF_printf("	dvmInterpret: 1\n");
			DECAF_printf("		dvmInterpret: @%x\n", env->regs[1]);
			flagDvmInterpret = 1;

			//set taints on DVM stack
			int selfAddr = env->regs[0];
			int methodAddr = env->regs[1];
			int tmpAddr = 0;
			char methodName[128];
			char methodShorty[128];
			unsigned short registerSize = 0;
			unsigned short insSize = 0;
			int curFrameAddr = 0;
			int accessFlag = 0;
			int insAddr = 0;

			//read method name
			assert(DECAF_read_mem(env, methodAddr + METHOD_NAME_OFFSET, &tmpAddr, 4) != -1);
			assert(DECAF_read_mem_until(env, tmpAddr, &methodName, 128) > 0);
			DECAF_printf("		method name: %s\n", methodName);

			//read method shorty
			assert(DECAF_read_mem(env, methodAddr + METHOD_SHORTY_OFFSET, &tmpAddr, 4) != -1);
			assert(DECAF_read_mem_until(env, tmpAddr, &methodShorty, 128) > 0);
			DECAF_printf("		method shorty: %s\n", methodShorty);

			//read register size
			assert(DECAF_read_mem(env, methodAddr + METHOD_REGISTER_SIZE_OFFSET, 
						&registerSize, 2) != -1);

			//read insSize
			assert(DECAF_read_mem(env, methodAddr + METHOD_INS_SIZE_OFFSET, 
						&insSize, 2) != -1);
			DECAF_printf("		register size: %d; ins size: %d\n", registerSize, insSize);

			//read curFrameAddr
			assert(DECAF_read_mem(env, selfAddr + 4, &curFrameAddr, 4) != -1);

			//read accessFlag
			assert(DECAF_read_mem(env, methodAddr + METHOD_ACCESS_FLAG_OFFSET,
						&accessFlag, 4) != -1);

			//not native
			if (!(accessFlag & ACC_NATIVE)){
				insAddr = curFrameAddr + (registerSize - insSize) * 8;
				int i = 0;
				for (; i < insSize; i++){
					assert(DECAF_write_mem(env, insAddr + 4 + i * 8, &taintsDvmInterpret[i], 4) != -1);
				}
			}
		}
	}else{
		if(flagDvmInterpret){
			DECAF_printf("	dvmInterpret: 0\n");
			addrDvmInterpret = -1;
			flagDvmInterpret = 0;
			free(taintsDvmInterpret);
		}
	}
}

/*
 * void dvmCallMethodV(Thread* self, const Method* method, Object* obj,
 * 			bool fromJni, JValue* pResult, va_list args)
 */
int addrDvmCallMethodV = -1;
int flagDvmCallMethodV = 0;
int argsPointer = -1;
void hookDvmCallMethodV(CPUState* env, int isStart){
	if (isStart && flagDvmCallMethodV == 0){
		if ((env->regs[1] != -1) &&
				(addrDvmCallMethodV == env->regs[1]) && 
				(env->regs[3] == 1)){
			assert(DECAF_read_mem(env, env->regs[13] + 4, &argsPointer, 4) != -1);
			DECAF_printf("	dvmCallMethodV: 1\n");
			DECAF_printf("		method@%x; argsPointer@%x\n", 
					addrDvmCallMethodV, argsPointer);
			assert((argsPointer & 0b11) == 0);
			flagDvmCallMethodV = 1;
			addrDvmInterpret = env->regs[1];

			//save taints
			int methodAddr = env->regs[1];
			int tmpAddr = 0;
			int insSize = 0;	
			char methodShorty[128];
			int accessFlag = 0;
			int slotCnt = 0;
			int verifyCnt = 0;
			int objAddr = 0;

			//read method shorty
			assert(DECAF_read_mem(env, methodAddr + METHOD_SHORTY_OFFSET, &tmpAddr, 4) != -1);
			assert(DECAF_read_mem_until(env, tmpAddr, &methodShorty, 128) > 0);
			DECAF_printf("		method shorty: %s\n", methodShorty);

			//read insSize
			assert(DECAF_read_mem(env, methodAddr + METHOD_INS_SIZE_OFFSET, 
						&insSize, 2) != -1);
			DECAF_printf("		ins size: %d\n", insSize);

			//read accessFlag
			assert(DECAF_read_mem(env, methodAddr + METHOD_ACCESS_FLAG_OFFSET,
						&accessFlag, 4) != -1);
			
			//not native
			if (!(accessFlag & ACC_NATIVE)){
				//save taints for hookDvmInterpret
				taintsDvmInterpret = (int*) calloc(insSize, sizeof(int));
				//not static
				if (!(accessFlag & ACC_STATIC)){
					int thisObjAddr = env->regs[2];
					taintsDvmInterpret[slotCnt++] = getTaint(thisObjAddr);
					verifyCnt++;
				}
				
				int i = 1;
				while (methodShorty[i] != '\0'){
					switch (methodShorty[i++]){
						case 'D': case 'J':
							taintsDvmInterpret[slotCnt++] = getTaint(argsPointer);
							argsPointer += 4;
							taintsDvmInterpret[slotCnt++] = getTaint(argsPointer);
							argsPointer += 4;
							verifyCnt += 2;
							break;
						case 'L':
							assert(DECAF_read_mem(env, argsPointer, &objAddr, 4) != -1);
							taintsDvmInterpret[slotCnt++] = getTaint(objAddr);
							argsPointer += 4;
							verifyCnt += 1;
							break;
						default:
							taintsDvmInterpret[slotCnt++] = getTaint(argsPointer);
							argsPointer += 4;
							verifyCnt += 1;
							break;
					}
				}
				assert(verifyCnt == insSize);
				//print taints
				for (i = 0; i < insSize; i++){
					DECAF_printf("		taintsDvmInterpret[%d]: %x\n", i, taintsDvmInterpret[i]);	
				}
			}
		}
	}else{
		if (flagDvmCallMethodV){
			addrDvmCallMethodV = -1;
			flagDvmCallMethodV = 0;
			argsPointer = -1;
		}
	}
}

/*
 * void dvmCallMethodA(Thread* self, const Method* method, Object* obj,
 * 			bool fromJni, JValue* pResult, const jvalue* args)
 */
void hookDvmCallMethodA(CPUState* env, int isStart){
}

/**
 * void CallVoidMethod(JNIEnv *env, jobject obj,
 * jmethodID methodID, ...)
 */
int addrCallVoidMethod = -1;
void hookCallVoidMethod(CPUState* env, int isStart){
	DECAF_printf("CallVoidMethod[%d]\n", isStart);
	if (isStart && addrCallVoidMethod == -1){
		addrCallVoidMethod = env->regs[2];
		DECAF_printf("CallVoidMethod@%x\n", addrCallVoidMethod);
	}else{
		if (addrCallVoidMethod != -1){
			addrCallVoidMethod = -1;
		}
	}
}

/**
 * const Method* dvmGetVirtualizedMethod(const ClassObject* clazz, const Method* meth)
 */
int addrGetVirtulizedMethod = -1;
void hookDvmGetVirtulizedMethod(CPUState* env, int isStart){
	if(isStart && addrGetVirtulizedMethod == -1){
		if (env->regs[1] == addrCallVoidMethod){
			addrGetVirtulizedMethod = env->regs[1];
			DECAF_printf("	getVirtulizedMethod: 1\n");
		}
	}else{
		if(addrGetVirtulizedMethod != -1){
			DECAF_printf("		dvmGetVirtulizedMethod: @%x --> @%x\n", 
					addrGetVirtulizedMethod, env->regs[0]);
			DECAF_printf("	getVirtulizedMethod: 0\n");
			addrGetVirtulizedMethod = -1;
			addrCallVoidMethod = env->regs[0];
			addrDvmCallMethodV = env->regs[0];
		}
	}
}



