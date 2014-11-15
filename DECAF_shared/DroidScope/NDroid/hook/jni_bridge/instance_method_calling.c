/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-10-4
 */

#include "DECAF_shared/utils/OutputWrapper.h"
#include "instance_method_calling.h"
#include "../dvm_hook.h"

//taint for new created object
extern int taintNewObjectGeneral;

jniHookHandler hookInstanceMethodCalling(int curPC, int dvmStartAddr, CPUState* env){
	switch(curPC - dvmStartAddr){
		case CallVoidMethod_OFFSET:
			hookCallVoidMethod(env, 1);
			return hookCallVoidMethod;
		case CallVoidMethodA_OFFSET:
			hookCallVoidMethodA(env, 1);
			return hookCallVoidMethodA;
		case CallVoidMethodV_OFFSET:
			hookCallVoidMethodV(env, 1);
			return hookCallVoidMethodV;
		case CallObjectMethod_OFFSET:
			hookCallObjectMethod(env, 1);
			return hookCallObjectMethod;
		case CallObjectMethodA_OFFSET:
			hookCallObjectMethodA(env, 1);
			return hookCallObjectMethodA;
		case CallObjectMethodV_OFFSET:
			hookCallObjectMethodV(env, 1);
			return hookCallObjectMethodV;
		case CallBooleanMethod_OFFSET:
			hookCallBooleanMethod(env, 1);
			return hookCallBooleanMethod;
		case CallBooleanMethodA_OFFSET:
			hookCallBooleanMethodA(env, 1);
			return hookCallBooleanMethodA;
		case CallBooleanMethodV_OFFSET:
			hookCallBooleanMethodV(env, 1);
			return hookCallBooleanMethodV;
		case CallByteMethod_OFFSET:
			hookCallByteMethod(env, 1);
			return hookCallByteMethod;
		case CallByteMethodA_OFFSET:
			hookCallByteMethodA(env, 1);
			return hookCallByteMethodA;
		case CallByteMethodV_OFFSET:
			hookCallByteMethodV(env, 1);
			return hookCallByteMethodV;
		case CallCharMethod_OFFSET:
			hookCallCharMethod(env, 1);
			return hookCallCharMethod;
		case CallCharMethodA_OFFSET:
			hookCallCharMethodA(env, 1);
			return hookCallCharMethodA;
		case CallCharMethodV_OFFSET:
			hookCallCharMethodV(env, 1);
			return hookCallCharMethodV;
		case CallShortMethod_OFFSET:
			hookCallShortMethod(env, 1);
			return hookCallShortMethod;
		case CallShortMethodA_OFFSET:
			hookCallShortMethodA(env, 1);
			return hookCallShortMethodA;
		case CallShortMethodV_OFFSET:
			hookCallShortMethodV(env, 1);
			return hookCallShortMethodV;
		case CallIntMethod_OFFSET:
			hookCallIntMethod(env, 1);
			return hookCallIntMethod;
		case CallIntMethodA_OFFSET:
			hookCallIntMethodA(env, 1);
			return hookCallIntMethodA;
		case CallIntMethodV_OFFSET:
			hookCallIntMethodV(env, 1);
			return hookCallIntMethodV;
		case CallLongMethod_OFFSET:
			hookCallLongMethod(env, 1);
			return hookCallLongMethod;
		case CallLongMethodA_OFFSET:
			hookCallLongMethodA(env, 1);
			return hookCallLongMethodA;
		case CallLongMethodV_OFFSET:
			hookCallLongMethodV(env, 1);
			return hookCallLongMethodV;
		case CallFloatMethod_OFFSET:
			hookCallFloatMethod(env, 1);
			return hookCallFloatMethod;
		case CallFloatMethodA_OFFSET:
			hookCallFloatMethodA(env, 1);
			return hookCallFloatMethodA;
		case CallFloatMethodV_OFFSET:
			hookCallFloatMethodV(env, 1);
			return hookCallFloatMethodV;
		case CallDoubleMethod_OFFSET:
			hookCallDoubleMethod(env, 1);
			return hookCallDoubleMethod;
		case CallDoubleMethodA_OFFSET:
			hookCallDoubleMethodA(env, 1);
			return hookCallDoubleMethodA;
		case CallDoubleMethodV_OFFSET:
			hookCallDoubleMethodV(env, 1);
			return hookCallDoubleMethodV;
	}
	return NULL;
}

/**
 * const Method* dvmGetVirtualizedMethod(const ClassObject* clazz, const Method* meth)
 */
int addrGetVirtulizedMethod = -1;
int flagGetVirtualizedMethod = 0;
int addrRetVirtulizedMethod = -1;
void hookDvmGetVirtulizedMethod(CPUState* env, int isStart){
	if(isStart && flagGetVirtualizedMethod == 0){
		if ((addrGetVirtulizedMethod != -1) &&
				(env->regs[1] == addrGetVirtulizedMethod)){
			DECAF_printf("	getVirtulizedMethod: 1\n");
			flagGetVirtualizedMethod = 1;
			addrRetVirtulizedMethod = -1;
		}
	}else{
		if (flagGetVirtualizedMethod){
			DECAF_printf("		dvmGetVirtulizedMethod: @%x --> @%x\n", 
					addrGetVirtulizedMethod, env->regs[0]);
			DECAF_printf("	getVirtulizedMethod: 0\n");
			addrGetVirtulizedMethod = -1;
			flagGetVirtualizedMethod = 0;
			addrRetVirtulizedMethod = env->regs[0];
		}
	}
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
			
			int isConstructor = 0;
			if (strcmp(methodName, "<init>") == 0){
				isConstructor = 1;
			}
			//not native
			if (!(accessFlag & ACC_NATIVE)){
				insAddr = curFrameAddr + (registerSize - insSize) * 8;
				int i = 0;
				for (; i < insSize; i++){
					assert(DECAF_write_mem(env, insAddr + 4 + i * 8, &taintsDvmInterpret[i], 4) != -1);
					if (isConstructor){
						taintNewObjectGeneral |= taintsDvmInterpret[i];
					}
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
int flagDvmCallMethodV = 0;
int argsPointer = -1;
void hookDvmCallMethodV(CPUState* env, int isStart){
	if (isStart && flagDvmCallMethodV == 0){
		if ((env->regs[1] != -1) &&
				(addrRetVirtulizedMethod == env->regs[1]) && 
				(env->regs[3] == 1)){
			assert(DECAF_read_mem(env, env->regs[13] + 4, &argsPointer, 4) != -1);
			DECAF_printf("	dvmCallMethodV: 1\n");
			DECAF_printf("		method@%x; argsPointer@%x\n", 
					addrRetVirtulizedMethod, argsPointer);
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
			flagDvmCallMethodV = 0;
			argsPointer = -1;
		}
	}
}

/*
 * void dvmCallMethodA(Thread* self, const Method* method, Object* obj,
 * 			bool fromJni, JValue* pResult, const jvalue* args)
 */
int flagDvmCallMethodA = 0;
int argsArrayPointer = -1;
void hookDvmCallMethodA(CPUState* env, int isStart){
	if (isStart && flagDvmCallMethodA == 0){
		if ((env->regs[1] != -1) &&
				(addrRetVirtulizedMethod == env->regs[1]) && 
				(env->regs[3] == 1)){
			assert(DECAF_read_mem(env, env->regs[13] + 4, &argsArrayPointer, 4) != -1);
			DECAF_printf("	dvmCallMethodA: 1\n");
			DECAF_printf("		method@%x; argsArrayPointer@%x\n", 
					addrRetVirtulizedMethod, argsArrayPointer);
			assert((argsArrayPointer & 0b11) == 0);
			flagDvmCallMethodA = 1;
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
							taintsDvmInterpret[slotCnt++] = getTaint(argsArrayPointer);
							argsArrayPointer += 4;
							taintsDvmInterpret[slotCnt++] = getTaint(argsArrayPointer);
							argsArrayPointer += 4;
							verifyCnt += 2;
							break;
						case 'L':
							assert(DECAF_read_mem(env, argsArrayPointer, &objAddr, 4) != -1);
							taintsDvmInterpret[slotCnt++] = getTaint(objAddr);
							argsArrayPointer += 4;
							verifyCnt += 1;
							break;
						default:
							taintsDvmInterpret[slotCnt++] = getTaint(argsArrayPointer);
							argsArrayPointer += 4;
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
		if (flagDvmCallMethodA){
			flagDvmCallMethodA = 0;
			argsArrayPointer = -1;
		}
	}
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
		addrGetVirtulizedMethod = env->regs[2];
	}else{
		if (addrCallVoidMethod != -1){
			addrCallVoidMethod = -1;
		}
	}
}

/**
 * void CallVoidMethod(JNIEnv *env, jobject obj,
 * jmethodID methodID, jvalue* args)
 */
int addrCallVoidMethodA = -1;
void hookCallVoidMethodA(CPUState* env, int isStart){
	DECAF_printf("CallVoidMethodA[%d]\n", isStart);
	if (isStart && addrCallVoidMethodA == -1){
		addrCallVoidMethodA = env->regs[2];
		addrGetVirtulizedMethod = env->regs[2];
		DECAF_printf("CallVoidMethodA@%x\n", addrCallVoidMethodA);
	}else{
		if (addrCallVoidMethodA != -1){
			addrCallVoidMethodA = -1;
		}
	}
}

/**
 * void CallVoidMethod(JNIEnv *env, jobject obj,
 * jmethodID methodID, va_list args)
 */
int addrCallVoidMethodV = -1;
void hookCallVoidMethodV(CPUState* env, int isStart){
	DECAF_printf("CallVoidMethodV[%d]\n", isStart);
	if (isStart && addrCallVoidMethodV == -1){
		addrCallVoidMethodV = env->regs[2];
		addrGetVirtulizedMethod = env->regs[2];
		DECAF_printf("CallVoidMethodV@%x\n", addrCallVoidMethodV);
	}else{
		if (addrCallVoidMethodV != -1){
			addrCallVoidMethodV = -1;
		}
	}
}

void hookCallObjectMethod(CPUState* env, int isStart){
	hookCallVoidMethod(env, isStart);
}

void hookCallObjectMethodA(CPUState* env, int isStart){
	hookCallVoidMethodA(env, isStart);
}

void hookCallObjectMethodV(CPUState* env, int isStart){
	hookCallVoidMethodV(env, isStart);
}

void hookCallBooleanMethod(CPUState* env, int isStart){
	hookCallVoidMethod(env, isStart);
}

void hookCallBooleanMethodA(CPUState* env, int isStart){
	hookCallVoidMethodA(env, isStart);
}

void hookCallBooleanMethodV(CPUState* env, int isStart){
	hookCallVoidMethodV(env, isStart);
}

void hookCallByteMethod(CPUState* env, int isStart){
	hookCallVoidMethod(env, isStart);
}

void hookCallByteMethodA(CPUState* env, int isStart){
	hookCallVoidMethodA(env, isStart);
}

void hookCallByteMethodV(CPUState* env, int isStart){
	hookCallVoidMethodV(env, isStart);
}

void hookCallCharMethod(CPUState* env, int isStart){
	hookCallVoidMethod(env, isStart);
}

void hookCallCharMethodA(CPUState* env, int isStart){
	hookCallVoidMethodA(env, isStart);
}

void hookCallCharMethodV(CPUState* env, int isStart){
	hookCallVoidMethodV(env, isStart);
}

void hookCallShortMethod(CPUState* env, int isStart){
	hookCallVoidMethod(env, isStart);
}

void hookCallShortMethodA(CPUState* env, int isStart){
	hookCallVoidMethodA(env, isStart);
}

void hookCallShortMethodV(CPUState* env, int isStart){
	hookCallVoidMethodV(env, isStart);
}

void hookCallIntMethod(CPUState* env, int isStart){
	hookCallVoidMethod(env, isStart);
}

void hookCallIntMethodA(CPUState* env, int isStart){
	hookCallVoidMethodA(env, isStart);
}

void hookCallIntMethodV(CPUState* env, int isStart){
	hookCallVoidMethodV(env, isStart);
}

void hookCallLongMethod(CPUState* env, int isStart){
	hookCallVoidMethod(env, isStart);
}

void hookCallLongMethodA(CPUState* env, int isStart){
	hookCallVoidMethodA(env, isStart);
}

void hookCallLongMethodV(CPUState* env, int isStart){
	hookCallVoidMethodV(env, isStart);
}

void hookCallFloatMethod(CPUState* env, int isStart){
	hookCallVoidMethod(env, isStart);
}

void hookCallFloatMethodA(CPUState* env, int isStart){
	hookCallVoidMethodA(env, isStart);
}

void hookCallFloatMethodV(CPUState* env, int isStart){
	hookCallVoidMethodV(env, isStart);
}

void hookCallDoubleMethod(CPUState* env, int isStart){
	hookCallVoidMethod(env, isStart);
}

void hookCallDoubleMethodA(CPUState* env, int isStart){
	hookCallVoidMethodA(env, isStart);
}

void hookCallDoubleMethodV(CPUState* env, int isStart){
	hookCallVoidMethodV(env, isStart);
}
