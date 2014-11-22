/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-11-10
 */

#ifndef _ND_MEM_PROTECT_H
#define _ND_MEM_PROTECT_H

#ifdef __cplusplus
extern "C"
{
#endif

	#include "DECAF_shared/DECAF_types.h"

//	#define WITH_MEM_PROTECT

	/*
	 * http://stackoverflow.com/questions/22299403/whats-the-data-in-dalvik-linearalloc-dalvik-aux-structure-dalvik-bitmap-1-da
	 * The above link refers to different kinds of datas stored in /dev/ashmem/-- modules.
	 *
	 */

	//To protect DVM heap, we care about "/dev/ashmem/dalvik-heap".
	void initDVMHeapRanges(gpid_t tracingPID);

	//To protect DVM's linear allocated, we care about "/dev/ashmem/dalvik-LinearAlloc".
	void initDVMLinearAllocRanges(gpid_t tracingPID);

	//Refresh the DVM heap
	void refreshDVMHeapRanges(gpid_t tracingPID);

	//Refresh the DVM stack();
	void refreshDVMLinearAllocRanges(gpid_t tracingPID);

	int isWithinDVMHeap(gva_t addr);

	int isWithinDVMLinearAlloc(gva_t addr);

	int isWithinDVMStack(gva_t addr);

#ifdef __cplusplus
}
#endif

#endif
