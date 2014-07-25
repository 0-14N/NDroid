/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2013-4-14
 *
 * We design a policy for source functions to indicate
 * that which parameters have taint.
 */

/**
 * A policy for each source function should have the following elements:
 * 1. modulename ---- which module this function belongs to.
 * 2. offset	   ---- the offset of the function, base address is the module's start address.
 * 3. tR0, tR1, tR2, tR3   ----- the taint of the first 4 arguments, -1 means no taint.
 * 4. num    ---- number of the parameters on the stack.
 * 5. taints[num] ---- the taints of the parameters on the stack, -1 means no taint.
 * 6. handler    ----- the handler to initialize the taints
 *
 * For example:
 * JNIEXPORT jboolean JNICALL Java_com_ndroid_demo_MainActivity_send(JNIEnv* env, jobject thiz,
 * jdouble lat, jdouble lng);
 *
 * modulename: libdemo.so
 * offset: 0x00000e90
 * tR0, tR1, tR2, tR3: -1, -1, 1, 1 //assume taint value of latitude and longitude is 1
 * num: 0
 * taints: NULL
 */

#ifndef __NDROID_SOURCE_POLICY_
#define __NDROID_SOURCE_POLICY_

#ifdef __cplusplus
extern "C" {
#endif
#include "DECAF_shared/DroidScope/LinuxAPI.h"
#include "DECAF_shared/utils/OutputWrapper.h"

#define SOURCES_FILE "SourcePolicies"

//the first arg 'void*' is actually a pointer of SourcePolicy
//typedef void (*SourcePolicy_handler_t)(void*, CPUState*);


typedef struct _SourcePolicy{
	char* modulename;
	int offset;
	int tR0, tR1, tR2, tR3;
	int num;
	int* taints;
	char* funcShorty;
	//SourcePolicy_handler_t handler;
	void (*handler) (struct _SourcePolicy*, CPUState*);
} SourcePolicy; 

void source_policy_handler(SourcePolicy* sourcePolicy, CPUState* env);

void initSourcePolicies(int pid);

int addSourcePolicy(int pid, SourcePolicy* policy);

int addEasySourcePolicy(int pid, int addr, SourcePolicy* policy);

SourcePolicy* findSourcePolicy(int cur_pc);

#ifdef __cplusplus
}
#endif

#endif
