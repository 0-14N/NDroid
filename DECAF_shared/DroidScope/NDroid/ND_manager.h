/**
 * author: chenxiong (R0r5ch4ch) qian
 * date: 2014-8-9
 */

#ifndef  _ND_MANAGER_H
#define  _ND_MANAGER_H

#include "monitor.h"
#include "DECAF_shared/DECAF_types.h"
#include "DECAF_shared/DroidScope/linuxAPI/ProcessInfo.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern gpid_t ND_GLOBAL_TRACING_PID;
extern target_ulong ND_GLOBAL_TRACING_UID;
extern int ND_TRACING_STATE;
extern ProcessInfo* ND_GLOBAL_TRACING_PROCESS;
#define ND_STOP -1
#define ND_WAITING 0
#define ND_TRACING_PID 1
#define ND_TRACING_UID 2

void nd_manager_trace_pid(Monitor* mon, gpid_t pid);
void nd_manager_trace_uid(Monitor* mon, target_ulong uid);
void nd_manager_wait_and_trace_uid(Monitor* mon, target_ulong uid, 
		gva_t libStartAddr, gva_t libEndAddr);
void nd_manager_stop_trace_pid(Monitor* mon, gpid_t pid);
void nd_manager_stop_trace_uid(Monitor* mon, target_ulong uid);

#ifdef WITH_MEM_PROTECT
void nd_refresh_stack_heap_ranges();
#endif

#ifdef __cplusplus
}
#endif

#endif
