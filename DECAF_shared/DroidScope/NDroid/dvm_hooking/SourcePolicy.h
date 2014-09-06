/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2013-4-14
 *
 * We design a policy for source functions to indicate
 * which parameters have taint.
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
	gva_t addr;								//the target native method address
	int tR0, tR1, tR2, tR3;		//taints of registers: R0, R1, R2, R3
	int num;									//number of stack slots saving parameters
	int* taints;							//taints of parameters on stack
	char* funcShorty;					//ReturnType_Param1Type_Param2Type
	int isStatic;							//whether the method is static
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
