/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2013-4-3
 */

#include "TaintEngine.h"
#include <tr1/unordered_map>
#include <assert.h>
#include "DECAF_shared/utils/OutputWrapper.h"
#include "memProtect/mem_protection.h"

using namespace std::tr1;

typedef unordered_map<int, int> taint_map;
typedef unordered_map<int, int>::const_iterator const_taint_iterator;
typedef unordered_map<int, int>::iterator taint_iterator;
typedef std::pair<int, int> taint_pair;

static taint_map taintMap;
static int taintRegs[16];

#define DEFENSIVE_CHECK_TAINT(_tValue) \
	if (_tValue <= 0) return (-1);

#define DEFENSIVE_CHECK_TAINT_NO_RET(_tValue) \
	if (_tValue <= 0) return;

#define CHECK_ON_DVM_STACK(_addr) \
	if(isWithinDVMStack(_addr)) { \
		DECAF_printf("Write mem@%x on DVM stack!\n", _addr); \
	}

#define CHECK_ON_DVM_HEAP(_addr) \
	if(isWithinDVMHeap(_addr)) { \
		DECAF_printf("Write mem@%x on DVM heap!\n", _addr); \
	}

int addTaint(int addr, int tValue){
#ifdef WITH_MEM_PROTECT
	CHECK_ON_DVM_STACK(addr);
	CHECK_ON_DVM_HEAP(addr);
#endif
	DEFENSIVE_CHECK_TAINT(tValue);
	taint_iterator it = taintMap.find(addr);
	if(it != taintMap.end()){
		it->second |= tValue;
		return (1);
	}else{
		taint_pair newTaint (addr, tValue);
		taintMap.insert(newTaint);
		return (0);
	}
}

void addBlockTaint(int startAddr, int endAddr, int tValue){
	DEFENSIVE_CHECK_TAINT_NO_RET(tValue);
	assert(startAddr <= endAddr);
	int addr;
	for(addr = startAddr; addr <= endAddr; addr++){
		addTaint(addr, tValue);
	}
}

int setTaint(int addr, int tValue){
#ifdef WITH_MEM_PROTECT
	CHECK_ON_DVM_STACK(addr);
	CHECK_ON_DVM_HEAP(addr);
#endif
	DEFENSIVE_CHECK_TAINT(tValue);
	taint_iterator it = taintMap.find(addr);	
	if(it != taintMap.end()){
		it->second = tValue;
		return (1);
	}else{
		taint_pair newTaint (addr, tValue);
		taintMap.insert(newTaint);
		return (0);
	}
}

int clearTaint(int addr){
#ifdef WITH_MEM_PROTECT
	CHECK_ON_DVM_STACK(addr);
	CHECK_ON_DVM_HEAP(addr);
#endif
	taint_iterator it = taintMap.find(addr);
	if(it != taintMap.end()){
		taintMap.erase(it);
		return (1);
	}else{
		return (0);
	}
}

void clearBlockTaint(int startAddr, int endAddr){
	int addr;
	assert(startAddr <= endAddr);
	for(addr = startAddr; addr <= endAddr; addr++){
		clearTaint(addr);
	}
}

void addTaintToReg(int regIdx, int tValue){
	DEFENSIVE_CHECK_TAINT_NO_RET(tValue);
	if((regIdx >= 0) && (regIdx <= 15)){
		taintRegs[regIdx] |= tValue;
	}
}

void setRegTaint(int regIdx, int tValue){
	DEFENSIVE_CHECK_TAINT_NO_RET(tValue);
	if((regIdx >= 0) && (regIdx <= 15)){
		taintRegs[regIdx] = tValue;
	}
}

void clearRegTaint(int regIdx){
	if((regIdx >= 0) && (regIdx <= 15)){
		taintRegs[regIdx] = 0;
	}
}

int getTaint(int addr){
	taint_iterator it = taintMap.find(addr);
	if(it != taintMap.end()){
		return it->second;
	}else{
		return (0);
	}
}

int getRegTaint(int regIdx){
	if((regIdx >= 0) && (regIdx <= 15)){
		return taintRegs[regIdx];
	}
	return (0);
}


int addMemToMem(int destAddr, int srcAddr){
	int tValue = getTaint(srcAddr);
	if(tValue > 0){
		addTaint(destAddr, tValue);
		return (1);
	}else{
		return (0);
	}
}

int setMemToMem(int destAddr, int srcAddr){
	int tValue = getTaint(srcAddr);
	if(tValue > 0){
		setTaint(destAddr, tValue);
		return (1);
	}else{
		return (0);
	}
}

int addMemToReg(int regIdx, int srcAddr){
	int tValue = getTaint(srcAddr);
	if(tValue > 0){
		addTaintToReg(regIdx, tValue);
		return (1);
	}else{
		return (0);
	}
}

int setMemToReg(int regIdx, int srcAddr){
	int tValue = getTaint(srcAddr);
	if(tValue > 0){
		setRegTaint(regIdx, tValue);
		return (1);
	}else{
		return (0);
	}
}

int addRegToMem(int destAddr, int regIdx){
	int tValue = getRegTaint(regIdx);
	if(tValue > 0){
		addTaint(destAddr, tValue);
		return (1);
	}else{
		return (0);
	}
}

int setRegToMem(int destAddr, int regIdx){
	int tValue = getRegTaint(regIdx);
	if(tValue > 0){
		setTaint(destAddr, tValue);
		return (1);
	}else{
		return (0);
	}
}

void addRegToReg(int destReg, int srcReg){
	int tValue = getRegTaint(srcReg);
	if(tValue > 0){
		addTaintToReg(destReg, tValue);
	}
}

void setRegToReg(int destReg, int srcReg){
	int tValue = getRegTaint(srcReg);
	if(tValue > 0){
		setRegTaint(destReg, tValue);
	}
}


int setMem4ToReg(int regIdx, int startAddr){
	int addr;
	int tValue = 0;
	for(addr = startAddr; addr < startAddr + 4; addr++){
		tValue |= getTaint(addr);
	}
	if(tValue > 0){
		setRegTaint(regIdx, tValue);
		return (1);
	}else{
		return (0);
	}
}

int addMem4ToReg(int regIdx, int startAddr){
	int addr;
	int tValue = 0;
	for(addr = startAddr; addr < startAddr + 4; addr++){
		tValue |= getTaint(addr);
	}
	if(tValue > 0){
		addTaintToReg(regIdx, tValue);
		return (1);
	}else{
		return (0);
	}
}

int setMem2ToReg(int regIdx, int startAddr){
	int addr;
	int tValue = 0;
	for(addr = startAddr; addr < startAddr + 2; addr++){
		tValue |= getTaint(addr);
	}
	if(tValue > 0){
		setRegTaint(regIdx, tValue);
		return (1);
	}else{
		return (0);
	}
}

void setRegToMem4(int startAddr, int regIdx){
	if((regIdx >= 0) && (regIdx <= 15)){
		int tValue = getRegTaint(regIdx);
		if(tValue > 0){
			int addr;
			for(addr = startAddr; addr < startAddr + 4; addr++){
				setTaint(addr, tValue);
			}
		}
	}
}

void addRegToMem4(int startAddr, int regIdx){
	if((regIdx >= 0) && (regIdx <= 15)){
		int tValue = getRegTaint(regIdx);
		if(tValue > 0){
			int addr;
			for(addr = startAddr; addr < startAddr + 4; addr++){
				addTaint(addr, tValue);
			}
		}
	}
}

void setRegToMem2(int startAddr, int regIdx){
	if((regIdx >= 0) && (regIdx <= 15)){
		int tValue = getRegTaint(regIdx);
		if(tValue > 0){
			int addr;
			for(addr = startAddr; addr < startAddr + 2; addr++){
				setTaint(addr, tValue);
			}
		}
	}
}


