/*
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-7-24
 */

#include "DECAF_shared/utils/OutputWrapper.h"
#include "DECAF_shared/DroidScope/NDroid/ND_instrument.h"
#include "dvm_hook.h"
#include "SourcePolicy.h"

/**
 * The handler of 'dvmCallJNIMethod(const u4* args, JValue* pResult, const Method* method, Thread* self)'
 * examples:
 * 1. java: public native boolean recordContact(String id, String name, String email)
 *    native: jboolean Java_..._recordContact(JNIEnv *env, jobject jobj, jstring id, jstring name, jstring email)
 *    shorty: ZLLL
 *    insSize: 4 (jobj, id, name, email)
 * 2. java: public static native boolean recordPhoneState(String phoneState)
 *    native: jboolean Java_..._recordPhoneState(JNIEnv *env, jclass jclz, jstring phoneState)
 *    shorty: ZL 
 *    insSize: 1 (phoneState)
 */
void dvmCallJNIMethodCallback(CPUState* env){
	gva_t argsAddr = env->regs[0];
	gva_t methodAddr = env->regs[2];

	gva_t insnAddr;
	if(DECAF_read_mem(env, methodAddr + METHOD_INSN_OFFSET, &insnAddr, 4) != -1){
		//target native method is in third party native library
		if(nd_in_blacklist(insnAddr)){
			SourcePolicy *sp = (SourcePolicy*) malloc(sizeof(SourcePolicy));
			sp->addr = insnAddr;

			//read class name
			int classAddr;
			int classDescriptorAddr;
			char classDescriptor[128];
			classDescriptor[0] = '\0';
			assert(DECAF_read_mem(env, methodAddr, &classAddr, 4) != -1);
			assert(DECAF_read_mem(env, classAddr + CLASS_DESCRIPTOR_OFFSET, &classDescriptorAddr, 4) != -1);
			assert(DECAF_read_mem_until(env, classDescriptorAddr, &classDescriptor, 128) > 0);
			assert(classDescriptor[0] != '\0');
			DECAF_printf("Class: %s\n", classDescriptor);
			sp->className = classDescriptor;

			//read method name
			gva_t methodNameAddr;
			char methodName[128];
			methodName[0] = '\0';
			assert(DECAF_read_mem(env, methodAddr + METHOD_NAME_OFFSET, &methodNameAddr, 4) != -1);
			assert(DECAF_read_mem_until(env, methodNameAddr, &methodName, 128) > 0);
			assert(methodName[0] != '\0');
			DECAF_printf("\n[====dvmCallJNIMethod <%s>====]\n", methodName);
			sp->methodName = methodName;

			//read the shorty
			int shortyAddr;
			char shorty[128];
			shorty[0] = '\0';
			assert(DECAF_read_mem(env, methodAddr + METHOD_SHORTY_OFFSET, &shortyAddr, 4) != -1);
			assert(DECAF_read_mem_until(env, shortyAddr, shorty, 128) > 0);
			assert(shorty[0] != '\0');
			DECAF_printf("shorty: %s\n", shorty);

			//initialize then funcShorty, replace return type with 'this' or 'jclz'
			sp->funcShorty = (char*) malloc(strlen(shorty));	
			sp->funcShorty[0] = 'L';//'this' or 'jclz'
			strcpy(&(sp->funcShorty[1]), &shorty[1]);

			//initialize tR0 ~ tR3
			sp->tR0 = 0;
			sp->tR1 = 0;
			sp->tR2 = 0;
			sp->tR3 = 0;

			//read insSize
			unsigned short insSize;
			assert(DECAF_read_mem(env, methodAddr + METHOD_INS_SIZE_OFFSET, &insSize, 2) != -1);
			DECAF_printf("insSize: %d\n", insSize);

			//read access_flag
			int accessFlag;
			assert(DECAF_read_mem(env, methodAddr + METHOD_ACCESS_FLAG_OFFSET, &accessFlag, 4) != -1);
			DECAF_printf("accessFlag: %d\n", accessFlag);

			if((accessFlag & ACC_STATIC) != 0){//static method
				sp->isStatic = 1;
				//2 additional parameters: 'env' and 'jclz'
				if(insSize + 2 > 4){
					sp->num = (insSize + 2) - 4;
					sp->taints = (int*)malloc((sp->num) * sizeof(int));
					//set taints
					sp->tR0 = 0;
					sp->tR1 = 0;
					
				}else{
					sp->num = 0;
					sp->taints = NULL;
				}
			}else{//non-static method
				sp->isStatic = 0;
				//1 additional parameters: 'env'
				if(insSize + 1 > 4){
					sp->num = (insSize + 1) - 4;
					sp->taints = (int*)malloc((sp->num) * sizeof(int));
				}else{
					sp->num = 0;
					sp->taints = NULL;
				}
			}
		}
	}
}

void dvmPlatformInvokeCallback(CPUState* env){
	DECAF_printf("dvmPlatformInvoke\n");
}
