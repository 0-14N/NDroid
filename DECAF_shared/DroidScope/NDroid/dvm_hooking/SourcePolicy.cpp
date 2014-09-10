/**
 * author: chenxiong
 * date: 2013-4-14
 */
#include "SourcePolicy.h"
#include <tr1/unordered_map>
#include <stdlib.h>
#include "DECAF_shared/DroidScope/NDroid/taint/TaintEngine.h"

using namespace std::tr1;
typedef unordered_map<gva_t, SourcePolicy*> source_policy_map;
typedef unordered_map<gva_t, SourcePolicy*>::iterator source_policy_iterator;
typedef std::pair<gva_t, SourcePolicy*> source_policy_pair;

static source_policy_map sourcePolicyMap;

/**
 * handler of Java_com_ndroid_demo_MainActivity_send
 */
void source_policy_handler(SourcePolicy* sourcePolicy, CPUState* env){
	DECAF_printf("SourceHandler\n");
	//sourcePolicy->tR0 <==> 'env', always 0
	//tR1 <==> 'jclz' or 'jobj', only >0 in non-static methods
	if((sourcePolicy->isStatic == 0) && (sourcePolicy->tR1 > 0)){
		//'jobj', R1 stores the address of object, not only R1 should be 
		//tainted, but also the address.
		setRegTaint(1, sourcePolicy->tR1);
		setTaint(env->regs[1], sourcePolicy->tR1);
	}

	if(sourcePolicy->shortyLen > 1){
		if((sourcePolicy->funcShorty[1] == 'D') ||
				(sourcePolicy->funcShorty[1] == 'J')){
			//tR2, tR3 store taints of first parameter
			setRegTaint(2, sourcePolicy->tR2);
			setRegTaint(3, sourcePolicy->tR3);

			//taints of rest parameters are stored in sourcePolicy->taints
			int i;
			int taintsIdx = 0;
			for(i = 2; i < sourcePolicy->shortyLen; i++){
				char type = sourcePolicy->funcShorty[i];
				switch(type){
					case 'L':
						setTaint(env->regs[13] + taintsIdx * 4, sourcePolicy->taints[taintsIdx]);		
						int addr = 0;
						assert(DECAF_read_mem(env, env->regs[13] + taintsIdx * 4, &addr, 4) != -1);
						setTaint(addr, sourcePolicy->taints[taintsIdx]);
						taintsIdx++;
						break;
					case 'D':
					case 'J':
						setTaint(env->regs[13] + taintsIdx * 4, sourcePolicy->taints[taintsIdx]);
						setTaint(env->regs[13] + (taintsIdx + 1) * 4, sourcePolicy->taints[taintsIdx + 1]);
						taintsIdx += 2;
						break;
					default:
						setTaint(env->regs[13] + taintsIdx * 4, sourcePolicy->taints[taintsIdx]);
						taintsIdx++;
						break;
				}
			}
		}else{
			if(sourcePolicy->funcShorty[1] == 'L'){
				//tR2 stores taint of first parameter, which is an obj reference
				setRegTaint(2, sourcePolicy->tR2);
				setTaint(env->regs[2], sourcePolicy->tR2);
			}else{
				setRegTaint(2, sourcePolicy->tR2);
			}
		}
	}
}

int addSourcePolicy(gva_t addr, SourcePolicy* policy){
	source_policy_pair new_policy (addr, policy);
	sourcePolicyMap.insert(new_policy);
	return 0;
}

/**
 * Find the policy with the key equals cur_pc.
 * Found: return the policy
 * Else: return NULL
 */
SourcePolicy* findSourcePolicy(gva_t cur_pc){
	source_policy_iterator it = sourcePolicyMap.find(cur_pc);
	
	if(it != sourcePolicyMap.end()){//Found
		return it->second;
	}else{//NotFound
		return NULL;
	}
}
