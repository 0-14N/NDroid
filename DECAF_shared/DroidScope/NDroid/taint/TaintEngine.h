/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2013-4-3
 *
 * APIs for taint add, change, clear
 */

#ifndef __NDROID_TAINT_ENGINE_
#define __NDROID_TAINT_ENGINE_

#ifdef __cplusplus
extern "C" {
#endif

	int addTaint(int addr, int tValue);
	void addBlockTaint(int startAddr, int endAddr, int tValue);
	int setTaint(int addr, int tValue);
	int clearTaint(int addr);
	void clearBlockTaint(int startAddr, int endAddr);
	void addTaintToReg(int regIdx, int tValue);
	void setRegTaint(int regIdx, int tValue);
	void clearRegTaint(int regIdx);
	int getTaint(int addr);
	int getRegTaint(int regIdx);

	int addMemToMem(int destAddr, int srcAddr);
	int setMemToMem(int destAddr, int srcAddr);
	int addMemToReg(int regIdx, int srcAddr);
	int setMemToReg(int regIdx, int srcAddr);
	int addRegToMem(int destAddr, int regIdx);
	int setRegToMem(int destAddr, int regIdx);
	void addRegToReg(int destReg, int srcReg);
	void setRegToReg(int destReg, int srcReg);

	int setMem4ToReg(int regIdx, int startAddr);
	int setMem2ToReg(int regIdx, int startAddr);
	void setRegToMem4(int startAddr, int regIdx);
	void setRegToMem2(int startAddr, int regIdx);

#ifdef __cplusplus
}
#endif

#endif
