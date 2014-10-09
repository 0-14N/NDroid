/**
 * author: chenxiong (R0r5ch4ch) qian
 * date: 2014-8-9
 */

#include "ND_manager.h"
#include "ND_instrument.h"
#include "DECAF_shared/utils/OutputWrapper.h"

gpid_t ND_GLOBAL_TRACING_PID = -1;
target_ulong ND_GLOBAL_TRACING_UID = -1;
gva_t ND_GLOBAL_TRACING_TASK_STRUCT = -1;
/* flag indicate state of tracing
 * 0 	-- waiting (trigger by command 'nd_wait_and_trace_uid')
 * 1 	-- tracing by pid
 * 2  -- tracing by uid
 * -1 -- stop tracing
 */
int ND_TRACING_STATE = ND_STOP;
//the tracing process
ProcessInfo* ND_GLOBAL_TRACING_PROCESS = NULL;

/**
 * The start point of tracing process
 */
void startTracing(){
	nd_instrument_init();
}

void nd_reset(){
	ND_GLOBAL_TRACING_UID = -1;
	ND_GLOBAL_TRACING_PID = -1;
	ND_GLOBAL_TRACING_TASK_STRUCT = -1;
	ND_TRACING_STATE = ND_STOP;
	ND_GLOBAL_TRACING_PROCESS = NULL;
	
	nd_instrument_stop();
}

void nd_manager_trace_pid(Monitor* mon, gpid_t pid){
	if(pid <= 0 || ND_TRACING_STATE != ND_STOP){
		DECAF_printf("A process with pid <%d> uid <%d> is being traced, please stop tracing it first:-)\n", 
				ND_GLOBAL_TRACING_PID, ND_GLOBAL_TRACING_UID);
		return;
	}

	//try to find process with pid <pid>
	ProcessInfo* processInfo = findProcessByPID(pid);
	if(processInfo != NULL){
		ND_GLOBAL_TRACING_PID = pid;
		ND_GLOBAL_TRACING_UID = processInfo->uid;
		ND_GLOBAL_TRACING_TASK_STRUCT = processInfo->task_struct;
		ND_TRACING_STATE = ND_TRACING_PID;
		DECAF_printf("Find process with pid <%d>, start tracing!\n", pid);
		ND_GLOBAL_TRACING_PROCESS = processInfo;
		nd_instrument_init();
	}else{
		DECAF_printf("Canot find process with pid <%d>\n", pid);
	}

}

void nd_manager_trace_uid(Monitor* mon, target_ulong uid){
	if(uid <= 0 || 
			(ND_TRACING_STATE != ND_STOP && ND_TRACING_STATE != ND_WAITING)){
		DECAF_printf("A process with pid <%d> uid <%d> is being traced, please stop tracing it first:-)\n", 
				ND_GLOBAL_TRACING_PID, ND_GLOBAL_TRACING_UID);
		return;
	}

	//try to find process with uid <uid>
	ProcessInfo* processInfo = findProcessByUID(uid);
	if(processInfo != NULL){
		ND_GLOBAL_TRACING_UID = uid;
		ND_GLOBAL_TRACING_PID = processInfo->pid;
		ND_TRACING_STATE = ND_TRACING_UID;
		ND_GLOBAL_TRACING_TASK_STRUCT = processInfo->task_struct;
		DECAF_printf("Find process with uid <%d>, start tracing!\n", uid);
		ND_GLOBAL_TRACING_PROCESS = processInfo;
		nd_instrument_init();
	}else{
		DECAF_printf("Canot find process with uid <%d>\n", uid);
	}
}

void nd_manager_wait_and_trace_uid(Monitor* mon, target_ulong uid){
	if(uid <= 0 || ND_TRACING_STATE != ND_STOP){
		if(ND_GLOBAL_TRACING_PID != -1){
			DECAF_printf("A process with pid <%d> is being traced, please stop tracing it first:-)\n", 
					ND_GLOBAL_TRACING_PID);
		}

		if(ND_GLOBAL_TRACING_UID != -1){
			DECAF_printf("A process with uid <%s> is being traced, please stop tracing it first:-)\n", 
					ND_GLOBAL_TRACING_UID);
		}
		return;
	}

	ND_GLOBAL_TRACING_UID = uid;
	ND_TRACING_STATE = ND_WAITING;
}

void nd_manager_stop_trace_pid(Monitor* mon, gpid_t pid){
	if(pid > 0 && pid == ND_GLOBAL_TRACING_PID){
		nd_reset();
	}else{
		DECAF_printf("Check pid or use command 'nd_stop_trace_uid'\n");
	}
}

void nd_manager_stop_trace_uid(Monitor* mon, target_ulong uid){
	if(uid > 0 && uid == ND_GLOBAL_TRACING_UID){
		nd_reset();
	}else{
		DECAF_printf("Check uid or use command 'nd_stop_trace_pid'\n");
	}
}

