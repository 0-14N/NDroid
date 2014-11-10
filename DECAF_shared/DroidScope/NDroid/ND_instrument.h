/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-7-9
 */

#ifndef  _ND_INSTRUMENT_H
#define  _ND_INSTRUMENT_H

#include "ND_manager.h"

#ifdef __cplusplus
extern "C"
{
#endif

	extern DECAF_Handle nd_ib_handle;
	extern DECAF_Handle nd_be_handle;

	int nd_in_blacklist(gva_t addr);
	void nd_instrument_init();
	void nd_instrument_stop();

#ifdef WITH_MEM_PROTECT
	void refresh_stack_heap_ranges();
#endif

#ifdef __cplusplus
}
#endif

#endif
