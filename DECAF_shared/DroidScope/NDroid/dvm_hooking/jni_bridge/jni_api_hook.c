/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-10-3
 */

#include "jni_api_hook.h"
#include "string_operations.h"

int startOfJniApis(int curPC, int dvmStartAddr){
	if(isStringOperations(curPC, dvmStartAddr)){
		return (1);
	}

	return (0);
}

jniHookHandler hookJniApis(int curPC, int dvmStartAddr, CPUState* env){
	return hookStringOperations(curPC, dvmStartAddr, env);
}
