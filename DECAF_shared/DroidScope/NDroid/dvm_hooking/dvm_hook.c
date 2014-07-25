/*
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-7-24
 */

#include "DECAF_shared/utils/OutputWrapper.h"
#include "DECAF_shared/DroidScope/NDroid/ND_instrument.h"
#include "dvm_hook.h"

/**
 * The handler of 'dvmCallJNIMethod(const u4* args, JValue* pResult, const Method* method, Thread* self)'
 *
 */
void dvmCallJNIMethodCallback(CPUState* env){
	gva_t argsAddr = env->regs[0];
	gva_t methodAddr = env->regs[2];
	int accessFlag;
	unsigned short insSize;
	gva_t methodNameAddr;
	gva_t insnAddr;
	char methodName[128];
	int shortyAddr;
	char shorty[128];
	int i;
	int slot;
	int objAddr;
	int classAddr;
	int classDescriptorAddr;
	char classDescriptor[128];
	int tmpIndex;

	if(DECAF_read_mem(env, methodAddr + METHOD_INSN_OFFSET, &insnAddr, 4) != -1){
		if(nd_in_blacklist(insnAddr)){

			//read method name
			methodName[0] = '\0';
			if(DECAF_read_mem(env, methodAddr + METHOD_NAME_OFFSET, &methodNameAddr, 4) != -1){
				if(DECAF_read_mem_until(env, methodNameAddr, methodName, 128) > 0){
					DECAF_printf("\n[====dvmCallJNIMethod <%s>====]\n", methodName);
				}
			}
			assert(methodName[0] != '\0');

			//read the shorty
			shorty[0] = '\0';
			if(DECAF_read_mem(env, methodAddr + METHOD_SHORTY_OFFSET, &shortyAddr, 4) != -1){
				if(DECAF_read_mem_until(env, shortyAddr, shorty, 128) > 0){
					DECAF_printf("shorty: %s\n", shorty);
				}
			}	
			assert(shorty[0] != '\0');

			//initialize then funcShorty, delete the return type and add the 'env', 'this'('class')


		}
	}

}

void dvmPlatformInvokeCallback(CPUState* env){
	DECAF_printf("dvmPlatformInvoke\n");
}
