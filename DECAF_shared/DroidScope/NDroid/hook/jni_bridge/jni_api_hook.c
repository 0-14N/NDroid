/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-10-3
 */

#include "jni_api_hook.h"
#include "string_operations.h"
#include "instance_method_calling.h"
#include "static_method_calling.h"
#include "instance_field_access.h"
#include "static_field_access.h"
#include "object_operations.h"

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
	jniHookHandler handler = NULL;

	//string operations
 	handler = hookStringOperations(curPC, dvmStartAddr, env);
	if(handler != NULL){
		return handler;
	}

	//instance method calling
	handler = hookInstanceMethodCalling(curPC, dvmStartAddr, env);
	if(handler != NULL){
		return handler;
	}

	//static method calling
	handler = hookStaticMethodCalling(curPC, dvmStartAddr, env);
	if (handler != NULL){
		return handler;
	}

	//instance field access
	handler = hookInstanceFieldAccess(curPC, dvmStartAddr, env);
	if (handler != NULL){
		return handler;
	}	

	//static field access
	handler = hookStaticFieldAccess(curPC, dvmStartAddr, env);
	if (handler != NULL){
		return handler;
	}

	//object operations
	handler = hookObjectOperations(curPC, dvmStartAddr, env);
	if (handler != NULL){
		return handler;
	}	

	return NULL;
}
