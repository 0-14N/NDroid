/**
 * author: chenxiong
 * date: 2013-4-14
 */
#include "SourcePolicy.h"
//#include "../Taint.h"
#include <tr1/unordered_map>
#include <stdlib.h>

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
