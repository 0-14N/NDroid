/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-10-3
 */

#include "jni_api_hook.h"
#include "string_operations.h"
#include "instance_method_calling.h"

/*
int startOfJniApis(int curPC, int dvmStartAddr){
	if(isStringOperations(curPC, dvmStartAddr)){
		return (1);
	}

	if(isInstanceMethodCalling(curPC, dvmStartAddr)){
		return (1);
	}

	return (0);
}
*/

jniHookHandler hookJniApis(int curPC, int dvmStartAddr, CPUState* env){
	jniHookHandler handler = hookStringOperations(curPC, dvmStartAddr, env);
	if(handler != NULL){
		return handler;
	}

	handler = hookInstanceMethodCalling(curPC, dvmStartAddr, env);
	if(handler != NULL){
		return handler;
	}
	return NULL;
}
