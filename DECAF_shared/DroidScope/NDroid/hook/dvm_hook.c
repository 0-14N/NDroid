/*
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-7-24
 */

#include "DECAF_shared/utils/OutputWrapper.h"
#include "DECAF_shared/DroidScope/NDroid/ND_instrument.h"
#include "dvm_hook.h"
#include "SourcePolicy.h"
#include "instance_method_calling.h"
#include "string_operations.h"

/**
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

/**
 * mem[addr] stores an string reference, get its taint
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
 * mem[addr] stores an StringObject reference, return its contents
 * pls refer to "dvm_hook.h"
 */
wchar_t* getContentsOfStringAtAddr(CPUState* env, gva_t addr){
	int stringObjAddr = 0;
	int charArrayAddr = 0;
	assert(DECAF_read_mem(env, addr, &stringObjAddr, 4) != -1);
	assert(DECAF_read_mem(env, stringObjAddr + STRING_INSTANCE_DATA_OFFSET, &charArrayAddr, 4) != -1);

	int numOfElements = 0;
	assert(DECAF_read_mem(env, charArrayAddr + STRING_ARRAY_LENGTH_OFFSET, &numOfElements, 4) != -1);
	wchar_t* contents = (wchar_t*) calloc(numOfElements + 1, sizeof(wchar_t));
	

	int i;
	for(i = 0; i < numOfElements; i++){
		assert(DECAF_read_mem(env, charArrayAddr + STRING_CONTENT_OFFSET + i * 2, &contents[i], 2) != -1);
	}
	contents[numOfElements] = L'\x0000';
	return contents;
}

/**
 * mem[addr] stores an StringObject reference, return its length
 * pls refer to "dvm_hook.h"
 */
int getStringLength(CPUState* env, gva_t addr){
	int stringObjAddr = 0;
	int charArrayAddr = 0;
	int length = 0;
	assert(DECAF_read_mem(env, addr, &stringObjAddr, 4) != -1);
	assert(DECAF_read_mem(env, stringObjAddr + STRING_INSTANCE_DATA_OFFSET, &charArrayAddr, 4) != -1);
	assert(DECAF_read_mem(env, charArrayAddr + STRING_ARRAY_LENGTH_OFFSET, &length, 4) != -1);
	return length;
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
 * 					 |___return taint_|
 * 					 |___arg0 taint___|
 * 					 |___arg1 taint___|
 * 					 |___arg1 taint___|
 * 					 |___arg2 taint___|
 * 					 |___arg2 taint___|
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
	int argsOffset = 0;
	int spTaintsOffset = 0;
	int taintsOffset = 0;

	gva_t insnAddr;
	if(DECAF_read_mem(env, methodAddr + METHOD_INSN_OFFSET, &insnAddr, 4) != -1){
		//target native method is in third party native library
		if(nd_in_blacklist(insnAddr)){
			SourcePolicy *sp = (SourcePolicy*) malloc(sizeof(SourcePolicy));
			sp->addr = insnAddr;
			sp->handler = source_policy_handler;
			addSourcePolicy(sp->addr, sp);

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
			sp->className = (char*) calloc(128, sizeof(char));
			strncpy(sp->className, classDescriptor, 127);
			sp->className[127] = '\0';

			//read method name
			gva_t methodNameAddr;
			char methodName[128];
			methodName[0] = '\0';
			assert(DECAF_read_mem(env, methodAddr + METHOD_NAME_OFFSET, &methodNameAddr, 4) != -1);
			assert(DECAF_read_mem_until(env, methodNameAddr, &methodName, 128) > 0);
			assert(methodName[0] != '\0');
			DECAF_printf("[====dvmCallJNIMethod <%s>====]\n", methodName);
			sp->methodName = (char*) calloc(128, sizeof(char));
			strncpy(sp->methodName, methodName, 127);
			sp->methodName[127] = '\0';

			//read the shorty: ReturnType_Param1Type_Param2Type...
			int shortyAddr;
			char shorty[128];
			shorty[0] = '\0';
			assert(DECAF_read_mem(env, methodAddr + METHOD_SHORTY_OFFSET, &shortyAddr, 4) != -1);
			assert(DECAF_read_mem_until(env, shortyAddr, shorty, 128) > 0);
			assert(shorty[0] != '\0');
			DECAF_printf("shorty: %s\n", shorty);

			int shortyLen = strlen(shorty);
			sp->shortyLen = shortyLen;
			sp->funcShorty = (char*) calloc(shortyLen + 1, sizeof(char));	
			strncpy(sp->funcShorty, shorty, shortyLen);
			sp->funcShorty[shortyLen] = '\0';


			//initialize tR0 ~ tR3
			sp->tR0 = 0;
			sp->tR1 = 0;
			sp->tR2 = 0;
			sp->tR3 = 0;

			//read insSize
			unsigned short insSize;
			assert(DECAF_read_mem(env, methodAddr + METHOD_INS_SIZE_OFFSET, &insSize, 2) != -1);
			//start address of taints
			taintsAddr = argsAddr + (insSize + 1) * 4;

			//read access_flag
			int accessFlag;
			assert(DECAF_read_mem(env, methodAddr + METHOD_ACCESS_FLAG_OFFSET, &accessFlag, 4) != -1);
			DECAF_printf("isStatic: %d\n", (accessFlag & ACC_STATIC));
			
			if((accessFlag & ACC_STATIC) != 0){//static method
				sp->isStatic = 1;
				//set taints of 'env' and 'jclz'
				sp->tR0 = 0;//env
				sp->tR1 = 0;//jclz
				//2 additional parameters: 'env' and 'jclz'
				if(insSize + 2 > 4){
					if((sp->funcShorty[1] == 'D') || (sp->funcShorty[1] == 'J')){
						//if the first parameter is double or long, it occupies two slots,
						//and the left parameters are all stored on stack.
						sp->num = (insSize + 2) - 4;
						sp->taints = (int*)calloc(sp->num, sizeof(int));
						//the first parameter is double or long, then it is stored in R2, R3
						//set sp->tR2, sp->tR3, actually sp->tR2 and sp->tR3 both store taint of the first parameter
						assert(DECAF_read_mem(env, taintsAddr, &(sp->tR2), 4) != -1);
						assert(DECAF_read_mem(env, taintsAddr + 4, &(sp->tR3), 4) != -1);
						taintsOffset += 8;
						argsOffset += 8;

						if(sp->funcShorty[1] == 'D'){
							double tmpDouble = 0;
							assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpDouble, 8) != -1);
							DECAF_printf("param[%d]: %lf\n", 1, tmpDouble);
						}else if(sp->funcShorty[1] == 'J'){
							long long tmpLong = 0;
							assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpLong, 8) != -1);
							DECAF_printf("param[%d]: %ld\n", 1, tmpLong);
						}

						argsOffset += 8;
						taintsOffset += 8;

						//the left parameters are all stored on stack
						for(i = 2/*start at second parameter*/; i < shortyLen; i++){
							char type = sp->funcShorty[i];
							switch(type){
								case 'L':
									{
										char tmpClassName[128];
										tmpClassName[0] = '\0';
										getClassTypeAtAddr(env, argsAddr + argsOffset, &tmpClassName[0], 128);
										if(strcmp("Ljava/lang/String;", tmpClassName) == 0){
											//taint of string instance data
											sp->taints[spTaintsOffset] = getTaintOfStringAtAddr(env, argsAddr + argsOffset);

											wchar_t* strContents = getContentsOfStringAtAddr(env, argsAddr + argsOffset);
											DECAF_printf("param[%d]: \"%ls\"\n", i, strContents);
										}else{
											int tmpObjAddr = 0;
											assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpObjAddr, 4) != -1);
											DECAF_printf("param[%d]: %x %s\n", i, tmpObjAddr, tmpClassName);
										}

										//taint of object reference
										int tmpTaintOfObjRef = 0;
										assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &tmpTaintOfObjRef, 4) != -1);
										sp->taints[spTaintsOffset] |= tmpTaintOfObjRef;
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

									if(type == 'D'){
										double tmpDouble = 0;
										assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpDouble, 8) != -1);
										DECAF_printf("param[%d]: %lf\n", i, tmpDouble);
									}else if(type == 'J'){
										long long tmpLong = 0;
										assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpLong, 8) != -1);
										DECAF_printf("param[%d]: %ld\n", i, tmpLong);
									}

									spTaintsOffset += 2;
									argsOffset += 8;
									taintsOffset += 8;
									break;
								default:
									assert(DECAF_read_mem(env, taintsAddr + taintsOffset, 
												&(sp->taints[spTaintsOffset]), 4) != -1);
									
									int tmpInt = 0;
									assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpInt, 4) != -1);
									DECAF_printf("param[%d]: %d\n", i, tmpInt);

									spTaintsOffset += 1;
									argsOffset += 4;
									taintsOffset += 4;
									break;
							}
						}
					}else{
						//the first parameter is not double and long
						
						//first parameter
						if(sp->funcShorty[1] == 'L'){
							char tmpClassName[128];
							tmpClassName[0] = '\0';
							getClassTypeAtAddr(env, argsAddr + argsOffset, &tmpClassName[0], 128);
							if(strcmp("Ljava/lang/String;", tmpClassName) == 0){
								//taint of string instance data
								sp->tR2 = getTaintOfStringAtAddr(env, argsAddr + argsOffset);

								wchar_t* strContents = getContentsOfStringAtAddr(env, argsAddr + argsOffset);
								DECAF_printf("param[%d]: \"%ls\"\n", 1, strContents);
							}else{
								int tmpObjAddr = 0;
								assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpObjAddr, 4) != -1);
								DECAF_printf("param[%d]: %x %s\n", 1, tmpObjAddr, tmpClassName);
							}

							//taint of object reference
							int tmpTaintOfObjRef = 0;
							assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &tmpTaintOfObjRef, 4) != -1);
							sp->tR2 |= tmpTaintOfObjRef;
						}else{
							assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &(sp->tR2), 4) != -1);

							int tmpInt = 0;
							assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpInt, 4) != -1);
							DECAF_printf("param[%d]: %d\n", 1, tmpInt);
						}
						argsOffset += 4;
						taintsOffset += 4;

						//second parameter
						if((sp->funcShorty[2] == 'D') || (sp->funcShorty[2] == 'J')){
							//because the second parameter occupies 8 bytes, according to APCS,
							//the parameter is stored on the stack, rather than the R3
							sp->tR3 = 0;
							sp->num = (insSize + 2) - 3;
							sp->taints = (int*)calloc(sp->num, sizeof(int));

							assert(DECAF_read_mem(env, taintsAddr + taintsOffset, 
										&(sp->taints[spTaintsOffset]), 4) != -1);
							assert(DECAF_read_mem(env, taintsAddr + taintsOffset + 4,
										&(sp->taints[spTaintsOffset + 1]), 4) != -1);
							
							if(sp->funcShorty[2] == 'D'){
								double tmpDouble = 0;
								assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpDouble, 8) != -1);
								DECAF_printf("param[%d]: %lf\n", 2, tmpDouble);
							}else if(sp->funcShorty[2] == 'J'){
								long long tmpLong = 0;
								assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpLong, 8) != -1);
								DECAF_printf("param[%d]: %ld\n", 2, tmpLong);
							}

							spTaintsOffset += 2;
							argsOffset += 8;
							taintsOffset += 8;
						}else{
							//the second parameter occupies 4 bytes
							sp->num = (insSize + 2) - 4;
							sp->taints = (int*)calloc(sp->num, sizeof(int));

							if(sp->funcShorty[2] == 'L'){
								char tmpClassName[128];
								tmpClassName[0] = '\0';
								getClassTypeAtAddr(env, argsAddr + argsOffset, &tmpClassName[0], 128);
								if(strcmp("Ljava/lang/String;", tmpClassName) == 0){
									//taint of string instance data
									sp->tR3 = getTaintOfStringAtAddr(env, argsAddr + argsOffset);

									wchar_t* strContents = getContentsOfStringAtAddr(env, argsAddr + argsOffset);
									DECAF_printf("param[%d]: \"%ls\"\n", 2, strContents);
								}else{
									int tmpObjAddr = 0;
									assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpObjAddr, 4) != -1);
									DECAF_printf("param[%d]: %x %s\n", 2, tmpObjAddr, tmpClassName);
								}

								//taint of object reference
								int tmpTaintOfObjRef = 0;
								assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &tmpTaintOfObjRef, 4) != -1);
								sp->tR3 |= tmpTaintOfObjRef;
							}else{
								assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &(sp->tR3), 4) != -1);

								int tmpInt = 0;
								assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpInt, 4) != -1);
								DECAF_printf("param[%d]: %d\n", 2, tmpInt);
							}
							argsOffset += 4;
							taintsOffset += 4;
						}
						
						for(i = 3/*start at the third parameter*/; i < shortyLen; i++){
							char type = sp->funcShorty[i];
							switch(type){
								case 'L':
									{
										char tmpClassName[128];
										tmpClassName[0] = '\0';
										getClassTypeAtAddr(env, argsAddr + argsOffset, &tmpClassName[0], 128);
										if(strcmp("Ljava/lang/String;", tmpClassName) == 0){
											//taint of string instance data
											sp->taints[spTaintsOffset] = getTaintOfStringAtAddr(env, argsAddr + argsOffset);

											wchar_t* strContents = getContentsOfStringAtAddr(env, argsAddr + argsOffset);
											DECAF_printf("param[%d]: \"%ls\"\n", i, strContents);
										}else{
											int tmpObjAddr = 0;
											assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpObjAddr, 4) != -1);
											DECAF_printf("param[%d]: %x %s\n", i, tmpObjAddr, tmpClassName);
										}

										//taint of object reference
										int tmpTaintOfObjRef = 0;
										assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &tmpTaintOfObjRef, 4) != -1);
										sp->taints[spTaintsOffset] |= tmpTaintOfObjRef;
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

									if(type == 'D'){
										double tmpDouble = 0;
										assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpDouble, 8) != -1);
										DECAF_printf("param[%d]: %lf\n", i, tmpDouble);
									}else if(type == 'J'){
										long long tmpLong = 0;
										assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpLong, 8) != -1);
										DECAF_printf("param[%d]: %ld\n", i, tmpLong);
									}

									spTaintsOffset += 2;
									argsOffset += 8;
									taintsOffset += 8;
									break;
								default:
									assert(DECAF_read_mem(env, taintsAddr + taintsOffset, 
												&(sp->taints[spTaintsOffset]), 4) != -1);
									
									int tmpInt = 0;
									assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpInt, 4) != -1);
									DECAF_printf("param[%d]: %d\n", i, tmpInt);

									spTaintsOffset += 1;
									argsOffset += 4;
									taintsOffset += 4;
									break;
							}
						}
					}
				}else{
					//insSize + 2 <= 4
					sp->num = 0;
					sp->taints = NULL;
					if(shortyLen == 2){
						//only one parameter, occupies 4 or 8 bytes
						if((sp->funcShorty[1] == 'D') || (sp->funcShorty[1] == 'J')){
							//double or long
							assert(DECAF_read_mem(env, taintsAddr, &(sp->tR2), 4) != -1);
							assert(DECAF_read_mem(env, taintsAddr + 4, &(sp->tR3), 4) != -1);
							argsOffset += 8;
							taintsOffset += 8;

							if(sp->funcShorty[1] == 'D'){
								double tmpDouble = 0;
								assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpDouble, 8) != -1);
								DECAF_printf("param[%d]: %lf\n", 1, tmpDouble);
							}else if(sp->funcShorty[1] == 'J'){
								long long tmpLong = 0;
								assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpLong, 8) != -1);
								DECAF_printf("param[%d]: %ld\n", 1, tmpLong);
							}

						}else{
							sp->tR3 = 0;
							if(sp->funcShorty[1] == 'L'){
								char tmpClassName[128];
								tmpClassName[0] = '\0';
								getClassTypeAtAddr(env, argsAddr + argsOffset, &tmpClassName[0], 128);
								if(strcmp("Ljava/lang/String;", tmpClassName) == 0){
									//taint of string instance data
									sp->tR2 = getTaintOfStringAtAddr(env, argsAddr + argsOffset);

									wchar_t* strContents = getContentsOfStringAtAddr(env, argsAddr + argsOffset);
									DECAF_printf("param[%d]: \"%ls\"\n", 1, strContents);
								}else{
									int tmpObjAddr = 0;
									assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpObjAddr, 4) != -1);
									DECAF_printf("param[%d]: %x %s\n", 1, tmpObjAddr, tmpClassName);
								}

								//taint of object reference
								int tmpTaintOfObjRef = 0;
								assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &tmpTaintOfObjRef, 4) != -1);
								sp->tR2 |= tmpTaintOfObjRef;
							}else{
								assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &(sp->tR2), 4) != -1);

								int tmpInt = 0;
								assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpInt, 4) != -1);
								DECAF_printf("param[%d]: %d\n", 1, tmpInt);
							}
							argsOffset += 4;
							taintsOffset += 4;
						}
					}else if(shortyLen == 3){
						//two parameter, each occupies 4 bytes
						if(sp->funcShorty[1] == 'L'){
							char tmpClassName[128];
							tmpClassName[0] = '\0';
							getClassTypeAtAddr(env, argsAddr + argsOffset, &tmpClassName[0], 128);
							if(strcmp("Ljava/lang/String;", tmpClassName) == 0){
								//taint of string instance data
								sp->tR2 = getTaintOfStringAtAddr(env, argsAddr + argsOffset);

								wchar_t* strContents = getContentsOfStringAtAddr(env, argsAddr + argsOffset);
								DECAF_printf("param[%d]: \"%ls\"\n", 1, strContents);
							}else{
								int tmpObjAddr = 0;
								assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpObjAddr, 4) != -1);
								DECAF_printf("param[%d]: %x %s\n", 1, tmpObjAddr, tmpClassName);
							}

							//taint of object reference
							int tmpTaintOfObjRef = 0;
							assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &tmpTaintOfObjRef, 4) != -1);
							sp->tR2 |= tmpTaintOfObjRef;
						}else{
							assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &(sp->tR2), 4) != -1);

							int tmpInt = 0;
							assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpInt, 4) != -1);
							DECAF_printf("param[%d]: %d\n", 1, tmpInt);
						}
						argsOffset += 4;
						taintsOffset += 4;

						if(sp->funcShorty[2] == 'L'){
							char tmpClassName[128];
							tmpClassName[0] = '\0';
							getClassTypeAtAddr(env, argsAddr + argsOffset, &tmpClassName[0], 128);
							if(strcmp("Ljava/lang/String;", tmpClassName) == 0){
								//taint of string instance data
								sp->tR3 = getTaintOfStringAtAddr(env, argsAddr + argsOffset);

								wchar_t* strContents = getContentsOfStringAtAddr(env, argsAddr + argsOffset);
								DECAF_printf("param[%d]: \"%ls\"\n", 2, strContents);
							}else{
								int tmpObjAddr = 0;
								assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpObjAddr, 4) != -1);
								DECAF_printf("param[%d]: %x %s\n", 2, tmpObjAddr, tmpClassName);
							}

							//taint of object reference
							int tmpTaintOfObjRef = 0;
							assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &tmpTaintOfObjRef, 4) != -1);
							sp->tR3 |= tmpTaintOfObjRef;
						}else{
							assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &(sp->tR3), 4) != -1);

							int tmpInt = 0;
							assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpInt, 4) != -1);
							DECAF_printf("param[%d]: %d\n", 2, tmpInt);
						}
						argsOffset += 4;
						taintsOffset += 4;
					}
				}
			}else{//non-static method
				sp->isStatic = 0;
				sp->tR0 = 0;//env
				//1 additional parameters: 'env'
				if(insSize + 1 > 4){
					//'this', occupies 4 bytes, stored in R1
					assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &(sp->tR1), 4) != -1);
					
					int tmpThisAddr = 0;
					assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpThisAddr, 4) != -1);
					DECAF_printf("this: %x\n", tmpThisAddr);

					argsOffset += 4;
					taintsOffset += 4;

					if((sp->funcShorty[1] == 'D') || (sp->funcShorty[1] == 'J')){
						//first parameter occupies 8 bytes, R2, R3
						sp->num = (insSize + 1) - 4;
						sp->taints = (int*)calloc(sp->num, sizeof(int));
						//taints of first parameter are stored in tR2, tR3
						assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &(sp->tR2), 4) != -1);
						assert(DECAF_read_mem(env, taintsAddr + taintsOffset + 4, &(sp->tR3), 4) != -1);

						if(sp->funcShorty[1] == 'D'){
							double tmpDouble = 0;
							assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpDouble, 8) != -1);
							DECAF_printf("param[%d]: %lf\n", 1, tmpDouble);
						}else if(sp->funcShorty[1] == 'J'){
							long long tmpLong = 0;
							assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpLong, 8) != -1);
							DECAF_printf("param[%d]: %ld\n", 1, tmpLong);
						}

						taintsOffset += 8;
						argsOffset += 8;

						//the left paramters are all stored on stack
						for(i = 2; i < shortyLen; i++){
							char type = sp->funcShorty[i];
							switch (type) {
								case 'L':
									{
										char tmpClassName[128];
										tmpClassName[0] = '\0';
										getClassTypeAtAddr(env, argsAddr + argsOffset, &tmpClassName[0], 128);
										if(strcmp("Ljava/lang/String;", tmpClassName) == 0){
											sp->taints[spTaintsOffset] = getTaintOfStringAtAddr(env, argsAddr + argsOffset);

											wchar_t* strContents = getContentsOfStringAtAddr(env, argsAddr + argsOffset);
											DECAF_printf("param[%d]: \"%ls\"\n", i, strContents);
										}else{
											int tmpObjAddr = 0;
											assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpObjAddr, 4) != -1);
											DECAF_printf("param[%d]: %x %s\n", i, tmpObjAddr, tmpClassName);
										}

										//taint of object reference
										int tmpTaintOfObjRef = 0;
										assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &tmpTaintOfObjRef, 4) != -1);
										sp->taints[spTaintsOffset] |= tmpTaintOfObjRef;
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
									
									if(type == 'D'){
										double tmpDouble = 0;
										assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpDouble, 8) != -1);
										DECAF_printf("param[%d]: %lf\n", i, tmpDouble);
									}else if(type == 'J'){
										long long tmpLong = 0;
										assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpLong, 8) != -1);
										DECAF_printf("param[%d]: %ld\n", i, tmpLong);
									}

									spTaintsOffset += 2;
									argsOffset += 8;
									taintsOffset += 8;
									break;
								default:
									assert(DECAF_read_mem(env, taintsAddr + taintsOffset, 
												&(sp->taints[spTaintsOffset]), 4) != -1);

									int tmpInt = 0;
									assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpInt, 4) != -1);
									DECAF_printf("param[%d]: %d\n", i, tmpInt);

									spTaintsOffset += 1;
									argsOffset += 4;
									taintsOffset += 4;
									break;
							}
						}

					}else{
						//first parameter occupies 4 bytes
						if(sp->funcShorty[1] == 'L'){
							char tmpClassName[128];
							tmpClassName[0] = '\0';
							getClassTypeAtAddr(env, argsAddr + argsOffset, &tmpClassName[0], 128);
							if(strcmp("Ljava/lang/String;", tmpClassName) == 0){
								sp->tR2 = getTaintOfStringAtAddr(env, argsAddr + argsOffset);

								wchar_t* strContents = getContentsOfStringAtAddr(env, argsAddr + argsOffset);
								DECAF_printf("param[%d]: \"%ls\"\n", 1, strContents);
							}else{
								int tmpObjAddr = 0;
								assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpObjAddr, 4) != -1);
								DECAF_printf("param[%d]: %x %s\n", 1, tmpObjAddr, tmpClassName);
							}

							//taint of object reference
							int tmpTaintOfObjRef = 0;
							assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &tmpTaintOfObjRef, 4) != -1);
							sp->tR2 |= tmpTaintOfObjRef;
						}else{
							assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &(sp->tR2), 4) != -1);

							int tmpInt = 0;
							assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpInt, 4) != -1);
							DECAF_printf("param[%d]: %d \n", 1, tmpInt);
						}
						argsOffset += 4;
						taintsOffset += 4;

						//second parameter
						if((sp->funcShorty[2] == 'D') || (sp->funcShorty[2] == 'J')){
							//because the second parameter occupies 8 bytes, according to APCS, 
							//the parameter is stored on stack, rather than the R3
							sp->tR3 = 0;
							sp->num = (insSize + 1) - 3;
							sp->taints = (int*)calloc(sp->num, sizeof(int));

							assert(DECAF_read_mem(env,taintsAddr + taintsOffset, 
										&(sp->taints[spTaintsOffset]), 4) != -1);
							assert(DECAF_read_mem(env, taintsAddr + taintsOffset + 4, 
										&(sp->taints[spTaintsOffset + 1]), 4) != -1);


							if(sp->funcShorty[2] == 'D'){
								double tmpDouble = 0;
								assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpDouble, 8) != -1);
								DECAF_printf("param[%d]: %lf\n", 2, tmpDouble);
							}else if(sp->funcShorty[2] == 'J'){
								long long tmpLong = 0;
								assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpLong, 8) != -1);
								DECAF_printf("param[%d]: %ld\n", 2, tmpLong);
							}

							spTaintsOffset += 2;
							argsOffset += 8;
							taintsOffset += 8;
						}else{
							//the second parameter occupies 4 bytes
							sp->num = (insSize + 1) - 4;
							sp->taints = (int*)calloc(sp->num, sizeof(int));

							if(sp->funcShorty[2] == 'L'){
								char tmpClassName[128];
								tmpClassName[0] = '\0';
								getClassTypeAtAddr(env, argsAddr + argsOffset, &tmpClassName[0], 128);
								if(strcmp("Ljava/lang/String;", tmpClassName) == 0){
									sp->tR3 = getTaintOfStringAtAddr(env, argsAddr + argsOffset);

									wchar_t* strContents = getContentsOfStringAtAddr(env, argsAddr + argsOffset);
									DECAF_printf("param[%d]: \"%ls\"\n", 2, strContents);
								}else{
									int tmpObjAddr = 0;
									assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpObjAddr, 4) != -1);
									DECAF_printf("param[%d]: %x %s\n", 2, tmpObjAddr, tmpClassName);
								}

								//taint of object reference
								int tmpTaintOfObjRef = 0;
								assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &tmpTaintOfObjRef, 4) != -1);
								sp->tR3 |= tmpTaintOfObjRef;
							}else{
								assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &(sp->tR3), 4) != -1);

								int tmpInt = 0;
								assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpInt, 4) != -1);
								DECAF_printf("param[%d]: %d\n", 2, tmpInt);
							}
							argsOffset += 4;
							taintsOffset += 4;
					}
					
					for(i = 3; i < shortyLen; i++){
						char type = sp->funcShorty[i];
						switch (type) {
							case 'L':
								{
									char tmpClassName[128];
									tmpClassName[0] = '\0';
									getClassTypeAtAddr(env, argsAddr + argsOffset, &tmpClassName[0], 128);
									if(strcmp("Ljava/lang/String;", tmpClassName) == 0){
										sp->taints[spTaintsOffset] = getTaintOfStringAtAddr(env, argsAddr + argsOffset);

										wchar_t* strContents = getContentsOfStringAtAddr(env, argsAddr + argsOffset);
										DECAF_printf("param[%d]: \"%ls\"\n", i, strContents);
									}else{
										int tmpObjAddr = 0;
										assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpObjAddr, 4) != -1);
										DECAF_printf("param[%d]: %x %s\n", i, tmpObjAddr, tmpClassName);
									}

									//taint of object reference
									int tmpTaintOfObjRef = 0;
									assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &tmpTaintOfObjRef, 4) != -1);
									sp->taints[spTaintsOffset] |= tmpTaintOfObjRef;
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

								if(type == 'D'){
									double tmpDouble = 0;
									assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpDouble, 8) != -1);
									DECAF_printf("param[%d]: %lf\n", i, tmpDouble);
								}else if(type == 'J'){
									long long tmpLong = 0;
									assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpLong, 8) != -1);
									DECAF_printf("param[%d]: %ld\n", i, tmpLong);
								}

								spTaintsOffset += 2;
								argsOffset += 8;
								taintsOffset += 8;
								break;
							default:
								assert(DECAF_read_mem(env, taintsAddr + taintsOffset, 
											&(sp->taints[spTaintsOffset]), 4) != -1);
								
								int tmpInt = 0;
								assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpInt, 4) != -1);
								DECAF_printf("param[%d]: %d\n", i, tmpInt);

								spTaintsOffset += 1;
								argsOffset += 4;
								taintsOffset += 4;
								break;
							}
						}
					}
				}else{
					//insSize + 1 <= 4
					sp->num = 0;
					sp->taints = NULL;
					
					//'this'	
					assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &(sp->tR1), 4) != -1);
					
					int tmpThisAddr = 0;
					assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpThisAddr, 4) != -1);
					DECAF_printf("this: %x\n", tmpThisAddr);

					argsOffset += 4;
					taintsOffset += 4;

					if(shortyLen == 2){
						//only one parameter, occupies 4 or 8 bytes
						if((sp->funcShorty[1] == 'D') || (sp->funcShorty[1] == 'J')){
							//double or long
							assert(DECAF_read_mem(env, taintsAddr, &(sp->tR2), 4) != -1);
							assert(DECAF_read_mem(env, taintsAddr + 4, &(sp->tR3), 4) != -1);

							if(sp->funcShorty[1] == 'D'){
								double tmpDouble = 0;
								assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpDouble, 8) != -1);
								DECAF_printf("param[%d]: %lf\n", 1, tmpDouble);
							}else if(sp->funcShorty[1] == 'J'){
								long long tmpLong = 0;
								assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpLong, 8) != -1);
								DECAF_printf("param[%d]: %ld\n", 1, tmpLong);
							}

							argsOffset += 8;
							taintsOffset += 8;
						}else{
							sp->tR3 = 0;
							if(sp->funcShorty[1] == 'L'){
								char tmpClassName[128];
								tmpClassName[0] = '\0';
								getClassTypeAtAddr(env, argsAddr + argsOffset, &tmpClassName[0], 128);
								if(strcmp("Ljava/lang/String;", tmpClassName) == 0){
									//taint of string instance data
									sp->tR2 = getTaintOfStringAtAddr(env, argsAddr + argsOffset);

									wchar_t* strContents = getContentsOfStringAtAddr(env, argsAddr + argsOffset);
									DECAF_printf("param[%d]: \"%ls\"\n", 1, strContents);
								}else{
									int tmpObjAddr = 0;
									assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpObjAddr, 4) != -1);
									DECAF_printf("param[%d]: %x %s\n", 1, tmpObjAddr, tmpClassName);
								}

								//taint of object reference
								int tmpTaintOfObjRef = 0;
								assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &tmpTaintOfObjRef, 4) != -1);
								sp->tR2 |= tmpTaintOfObjRef;
							}else{
								assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &(sp->tR2), 4) != -1);

								int tmpInt = 0;
								assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpInt, 4) != -1);
								DECAF_printf("param[%d]: %d\n", 1, tmpInt);
							}
							argsOffset += 4;
							taintsOffset += 4;
						}
					}else if(shortyLen == 3){
						//two parameter, each occupies 4 bytes
						if(sp->funcShorty[1] == 'L'){
							char tmpClassName[128];
							tmpClassName[0] = '\0';
							getClassTypeAtAddr(env, argsAddr + argsOffset, &tmpClassName[0], 128);
							if(strcmp("Ljava/lang/String;", tmpClassName) == 0){
								//taint of string instance data
								sp->tR2 = getTaintOfStringAtAddr(env, argsAddr + argsOffset);

								wchar_t* strContents = getContentsOfStringAtAddr(env, argsAddr + argsOffset);
								DECAF_printf("param[%d]: \"%ls\"\n", 1, strContents);
							}else{
								int tmpObjAddr = 0;
								assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpObjAddr, 4) != -1);
								DECAF_printf("param[%d]: %x %s\n", 1, tmpObjAddr, tmpClassName);
							}

							//taint of object reference
							int tmpTaintOfObjRef = 0;
							assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &tmpTaintOfObjRef, 4) != -1);
							sp->tR2 |= tmpTaintOfObjRef;
						}else{
							assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &(sp->tR2), 4) != -1);

							int tmpInt = 0;
							assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpInt, 4) != -1);
							DECAF_printf("param[%d]: %d\n", 1, tmpInt);
						}
						argsOffset += 4;
						taintsOffset += 4;

						if(sp->funcShorty[2] == 'L'){
							char tmpClassName[128];
							tmpClassName[0] = '\0';
							getClassTypeAtAddr(env, argsAddr + argsOffset, &tmpClassName[0], 128);
							if(strcmp("Ljava/lang/String;", tmpClassName) == 0){
								//taint of string instance data
								sp->tR3 = getTaintOfStringAtAddr(env, argsAddr + argsOffset);

								wchar_t* strContents = getContentsOfStringAtAddr(env, argsAddr + argsOffset);
								DECAF_printf("param[%d]: \"%ls\"\n", 2, strContents);
							}else{
								int tmpObjAddr = 0;
								assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpObjAddr, 4) != -1);
								DECAF_printf("param[%d]: %x %s", 2, tmpObjAddr, tmpClassName);
							}

							//taint of object reference
							int tmpTaintOfObjRef = 0;
							assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &tmpTaintOfObjRef, 4) != -1);
							sp->tR3 |= tmpTaintOfObjRef;
						}else{
							assert(DECAF_read_mem(env, taintsAddr + taintsOffset, &(sp->tR3), 4) != -1);

							int tmpInt = 0;
							assert(DECAF_read_mem(env, argsAddr + argsOffset, &tmpInt, 4) != -1);
							DECAF_printf("param[%d]: %d\n", 2, tmpInt);
						}
						argsOffset += 4;
						taintsOffset += 4;
					}

				}
			}
		}
	}
}

/**
 * dvmGetVirtulizedMethod, dvmInterpret
 */
int isStartOfDvmHooks(int curPC, int dvmStartAddr){
	switch(curPC - dvmStartAddr){
		case OFFSET_DVM_GET_VIRTULIZED_METHOD_BEGIN:
		case OFFSET_DVM_INTERPRET_BEGIN:
		case OFFSET_DVM_CREATE_STRING_FROM_CSTR_BEGIN:
			return (1);
	}
	return (0);
}

void dvmHooksBegin(CPUState* env, int curPC, int dvmStartAddr){
	switch(curPC - dvmStartAddr){
		case OFFSET_DVM_GET_VIRTULIZED_METHOD_BEGIN:
			hookDvmGetVirtulizedMethod(env, 1);
		case OFFSET_DVM_INTERPRET_BEGIN:
			hookDvmInterpret(env, 1);
		case OFFSET_DVM_CREATE_STRING_FROM_CSTR_BEGIN:
			hookDvmCreateStringFromCstr(env, 1);
	}
}

/**
 * dvmGetVirtulizedMethod, dvmCreateStringFromCstr
 */
int isEndOfDvmHooks(int curPC, int dvmStartAddr){
	switch(curPC - dvmStartAddr){
		case OFFSET_DVM_GET_VIRTULIZED_METHOD_END:
		case OFFSET_DVM_CREATE_STRING_FROM_CSTR_END:
			return (1);
	}
	return (0);
}

void dvmHooksEnd(CPUState* env, int curPC, int dvmStartAddr){
	switch(curPC - dvmStartAddr){
		case OFFSET_DVM_GET_VIRTULIZED_METHOD_END:
			hookDvmGetVirtulizedMethod(env, 0);
		case OFFSET_DVM_CREATE_STRING_FROM_CSTR_END:
			hookDvmCreateStringFromCstr(env, 0);
	}
}
