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

void callVoidMethod(CPUState* env, int isBefore){
	DECAF_printf("CallVoidMethod[%d]\n", isBefore);
}
