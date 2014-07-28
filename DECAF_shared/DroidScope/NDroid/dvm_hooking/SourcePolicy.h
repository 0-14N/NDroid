/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2013-4-14
 *
 * We design a policy for source functions to indicate
 * which parameters have taint.
 */

/**
 * A policy for each source function should have the following elements:
 * 1. className  ---- in which class this function locates
 * 2. methodName
 * 3. addr   ---- start address of this method
 * 4. tR0, tR1, tR2, tR3   ----- the taint of the first 4 arguments, <= 0 means no taint.
 * 5. num    ---- number of the parameters on the stack.
 * 6. taints[num] ---- the taints of the parameters on the stack, -1 means no taint.
 * 7. handler    ----- the handler to initialize the taints
 *
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
	char* className;
	char* methodName;
	gva_t addr;
	int tR0, tR1, tR2, tR3;
	int num;
	int* taints;
	char* funcShorty;
	int isStatic;
	//SourcePolicy_handler_t handler;
	void (*handler) (struct _SourcePolicy*, CPUState*);
} SourcePolicy; 

void source_policy_handler(SourcePolicy* sourcePolicy, CPUState* env);

int addSourcePolicy(int addr, SourcePolicy* policy);

SourcePolicy* findSourcePolicy(int cur_pc);

#ifdef __cplusplus
}
#endif

#endif
