/*
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-7-24
 */

#include "DECAF_shared/utils/OutputWrapper.h"
#include "DECAF_shared/DroidScope/NDroid/ND_instrument.h"
#include "dvm_hook.h"
#include "SourcePolicy.h"

/*
 * mem[addr] stores an object reference, get its type
 */
void getClassTypeAtAddr(CPUState* env, gva_t addr, char* type, int length){
			//read class name
			int objAddr;
			int classAddr;
			int classDescriptorAddr;
			assert(DECAF_read_mem(env, addr, &objAddr, 4) != -1);
			assert(DECAF_read_mem(env, objAddr, &classAddr, 4) != -1);
			assert(DECAF_read_mem(env, classAddr + CLASS_DESCRIPTOR_OFFSET, &classDescriptorAddr, 4) != -1);
			assert(DECAF_read_mem_until(env, classDescriptorAddr, type, length) > 0);
			assert(type[0] != '\0');
}

/*
 * mem[add] stores an string reference, get its taint
 */
int getTaintOfStringAtAddr(CPUState* env, gva_t addr){
	int stringObjAddr = 0;
	int charArrayAddr = 0;
	int taint = 0;
	assert(DECAF_read_mem(env, addr, &stringObjAddr, 4) != -1);
	assert(DECAF_read_mem(env, stringObjAddr + STRING_INSTANCE_DATA_OFFSET, &charArrayAddr, 4) != -1);
	assert(DECAF_read_mem(env, charArrayAddr + STRING_TAINT_OFFSET, &taint, 4) != -1);
	return taint;
}

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
 * 3. java: public native double testDouble(double d1, double d2)
 * 		shorty: DDD
 * 		insSize: 5 (jobj, d1, d2)
 * 		d1 = 1234.1234 = 0x4093487e5c91d14e
 * 		 			  ________________
 * 		args-->|______this______|
 * 					 |___0x5c91d14e___|
 * 					 |___0x4093487e___|
 * 					 |___ ........ ___|
 * 					 |___ ........ ___|
 *
 * WARN: Currently, we do not consider the case that argument is CPRC (Co-processor Register Candidate)
 *
 * The APCS reference: Procedure Call Standard for the ARM Architecture
 */
void dvmCallJNIMethodCallback(CPUState* env){
	gva_t argsAddr = env->regs[0];
	gva_t methodAddr = env->regs[2];
	gva_t taintsAddr = 0;
	int i = 0;

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
			taintsAddr = argsAddr + (insSize + 1) * 4;

			//read access_flag
			int accessFlag;
			assert(DECAF_read_mem(env, methodAddr + METHOD_ACCESS_FLAG_OFFSET, &accessFlag, 4) != -1);
			DECAF_printf("accessFlag: %d\n", accessFlag);

			/*
			int i = 0;
			int arg = 0;
			for(; i < insSize; i++){
				assert(DECAF_read_mem(env, argsAddr + (i * 4), &arg, 4) != -1);
				printf("argsAddr[%d] = %x\n", i, arg);
			}
			*/

			if((accessFlag & ACC_STATIC) != 0){//static method
				sp->isStatic = 1;
				//2 additional parameters: 'env' and 'jclz'
				if(insSize + 2 > 4){
					sp->num = (insSize + 2) - 4;
					sp->taints = (int*)calloc(sp->num, sizeof(int));
					//set taints
					sp->tR0 = 0;//env
					sp->tR1 = 0;//jclz

					int argsOffset = 0;
					int spTaintsOffset = 0;
					int taintsOffset = 0;
					if((sp->funcShorty[1] == 'D') || (sp->funcShorty[1] == 'J')){
						//the first parameter is double or long, then it is stored in R2, R3
						//set sp->tR2, sp->tR3
						assert(DECAF_read_mem(env, taintsAddr, &(sp->tR2), 4) != -1);
						assert(DECAF_read_mem(env, taintsAddr + 4, &(sp->tR3), 4) != -1);
						taintsOffset += 8;
						argsOffset += 8;

						//the left parameters are all stored on stack
						for(i = 1/*start at second parameter*/; i < insSize; i++){
							char type = sp->funcShorty[i + 1];
							switch(type){
								case 'L':
									{
										char tmpClassName[128];
										tmpClassName[0] = '\0';
										getClassTypeAtAddr(env, argsAddr + argsOffset, &tmpClassName[0], 128);
										if(strcmp("Ljava/lang/String;", tmpClassName) == 0){
											sp->taints[spTaintsOffset] = getTaintOfStringAtAddr(env, argsAddr + argsOffset);		
										}
									}
									spTaintsOffset += 1;
									argsOffset += 4;
									taintsOffset += 4;
									break;
								case 'D':
								case 'J':
									assert(DECAF_read_mem(env, taintsAddr + taintsOffset, 
												&(sp->taints[spTaintsOffset]), 4) != -1);
									assert(DECAF_read_mem(env, taintsAddr + taintsOffset + 4,
												&(sp->taints[spTaintsOffset + 1]), 4) != -1);
									spTaintsOffset += 2;
									argsOffset += 8;
									taintsOffset += 8;
									break;
								default:
									assert(DECAF_read_mem(env, taintsAddr + taintsOffset, 
												&(sp->taints[spTaintsOffset]), 4) != -1);
									spTaintsOffset += 1;
									argsOffset += 4;
									taintsOffset += 4;
									break;
							}
						}
					}else{
					}
				}else{
					sp->num = 0;
					sp->taints = NULL;
				}
			}else{//non-static method
				sp->isStatic = 0;
				//1 additional parameters: 'env'
				if(insSize + 1 > 4){
					sp->num = (insSize + 1) - 4;
					sp->taints = (int*)calloc(sp->num, sizeof(int));
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
