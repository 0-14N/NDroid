/**
 * author: chenxiong
 * date: 2013-4-14
 */
#include "SourcePolicy.h"
//#include "../Taint.h"
#include <tr1/unordered_map>
#include <stdlib.h>

using namespace std::tr1;
typedef unordered_map<int, SourcePolicy*> source_policy_map;
typedef unordered_map<int, SourcePolicy*>::iterator source_policy_iterator;
typedef std::pair<int, SourcePolicy*> source_policy_pair;

static source_policy_map sourcePolicyMap;

/**
 * handler of Java_com_ndroid_demo_MainActivity_send
 */
void source_policy_handler(SourcePolicy* sourcePolicy, CPUState* env){
	DECAF_myFprintf(NULL, "SourceHandler\n");
	/*
	//Set taint of R0, R1, R2, R3
	if(sourcePolicy->tR0 > 0){
		if(sourcePolicy->funcShorty[0] != 'L'){
			setRegTaint(0, sourcePolicy->tR0);
		}else{
			setTaint(env->regs[0], sourcePolicy->tR0);
		}
	}
	if(sourcePolicy->tR1 > 0){
		if(sourcePolicy->funcShorty[1] != 'L'){
			setRegTaint(1, sourcePolicy->tR1);
		}else{
			setTaint(env->regs[1], sourcePolicy->tR1);
		}
	}
	if(sourcePolicy->tR2 > 0){
		if(sourcePolicy->funcShorty[2] != 'L'){
			setRegTaint(2, sourcePolicy->tR2);
		}else{
			setTaint(env->regs[2], sourcePolicy->tR2);
		}
	}
	if(sourcePolicy->tR3 > 0){
		if(sourcePolicy->funcShorty[3] != 'L'){
			setRegTaint(3, sourcePolicy->tR3);
		}else{
			setTaint(env->regs[3], sourcePolicy->tR3);
		}
	}
	//Handle the taint of stack
	if(sourcePolicy->num > 0){
		int i = 0;
		for(; i < sourcePolicy->num; i++){
			if(sourcePolicy->taints[i] > 0){
				if(sourcePolicy->funcShorty[4+i] != 'L'){
					setTaint(env->regs[13] + i * 4, sourcePolicy->taints[i]);
				}else{
					int addr = 0;
					if(DECAF_read_mem(env, env->regs[13] + i * 4, &addr, 4) != -1){
						setTaint(addr, sourcePolicy->taints[i]);
					}else{
						DECAF_printf("read mem error @SourcePolicy.cpp 63\n");
					}
				}
			}
		}
	}
	*/
}

int addSourceSourcePolicy(int addr, SourcePolicy* policy){
	source_policy_pair new_policy (addr, policy);
	sourcePolicyMap.insert(new_policy);
	return 0;
}

/**
 * Find the policy with the key equals cur_pc.
 * Found: return the policy
 * Else: return NULL
 */
SourcePolicy* findSourcePolicy(int cur_pc){
	source_policy_iterator it = sourcePolicyMap.find(cur_pc);
	
	if(it != sourcePolicyMap.end()){//Found
		return it->second;
	}else{//NotFound
		return NULL;
	}
}
