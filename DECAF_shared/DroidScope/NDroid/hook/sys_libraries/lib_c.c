/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-10-4
 */

#include "lib_c.h"

void sysLibCWcsftimeHookHandler(CPUState* env, int isStart){

}


void sysLibCFreedtoaHookHandler(CPUState* env, int isStart){

}

/**
 * int fclose(FILE *fp)
 */
void sysLibCFcloseHookHandler(CPUState* env, int isStart){
	DECAF_printf("fclose[%d]\n", isStart);
	if(isStart){
		DECAF_printf("close FILE@%x\n", env->regs[0]);
	}
}


void sysLibCGetaddrinfoHookHandler(CPUState* env, int isStart){

}


void sysLibCRebootHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Mutex_LockHookHandler(CPUState* env, int isStart){

}


void sysLibCVwarnHookHandler(CPUState* env, int isStart){

}


void sysLibCSleepHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Condattr_GetpsharedHookHandler(CPUState* env, int isStart){

}


void sysLibCIsxdigitHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Cond_Timedwait_Relative_NpHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Key_DeleteHookHandler(CPUState* env, int isStart){

}


void sysLibCWcsncasecmpHookHandler(CPUState* env, int isStart){

}


void sysLibCGetresgidHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Attr_GetscopeHookHandler(CPUState* env, int isStart){

}


void sysLibCSha1InitHookHandler(CPUState* env, int isStart){

}


void sysLibCUmaskHookHandler(CPUState* env, int isStart){

}


void sysLibCSched_GetaffinityHookHandler(CPUState* env, int isStart){

}


void sysLibCSendHookHandler(CPUState* env, int isStart){

}


void sysLibCWcslcpyHookHandler(CPUState* env, int isStart){

}


void sysLibCSched_SetparamHookHandler(CPUState* env, int isStart){

}


void sysLibCMalloc_Debug_FiniHookHandler(CPUState* env, int isStart){

}


void sysLibCSetutentHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Setname_NpHookHandler(CPUState* env, int isStart){

}


void sysLibCIsspaceHookHandler(CPUState* env, int isStart){

}


void sysLibCLocaltimeHookHandler(CPUState* env, int isStart){

}


void sysLibCVerrHookHandler(CPUState* env, int isStart){

}


void sysLibCGetptHookHandler(CPUState* env, int isStart){

}


void sysLibCCtime_RHookHandler(CPUState* env, int isStart){

}


void sysLibCGetc_UnlockedHookHandler(CPUState* env, int isStart){

}


void sysLibCGetppidHookHandler(CPUState* env, int isStart){

}


void sysLibCDlindependent_CallocHookHandler(CPUState* env, int isStart){

}


void sysLibCUtmpnameHookHandler(CPUState* env, int isStart){

}


void sysLibCSeteuidHookHandler(CPUState* env, int isStart){

}


void sysLibCCapgetHookHandler(CPUState* env, int isStart){

}


void sysLibCUtimeHookHandler(CPUState* env, int isStart){

}


void sysLibCGettidHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Attr_SetstacksizeHookHandler(CPUState* env, int isStart){

}


void sysLibCIssetugidHookHandler(CPUState* env, int isStart){

}


void sysLibCTimegmHookHandler(CPUState* env, int isStart){

}


void sysLibCDlpvallocHookHandler(CPUState* env, int isStart){

}


void sysLibCTcsetpgrpHookHandler(CPUState* env, int isStart){

}


void sysLibCFgetlnHookHandler(CPUState* env, int isStart){

}


void sysLibCRecvfromHookHandler(CPUState* env, int isStart){

}


void sysLibCSched_Get_Priority_MaxHookHandler(CPUState* env, int isStart){

}


void sysLibCGetmntentHookHandler(CPUState* env, int isStart){

}


void sysLibCIswspaceHookHandler(CPUState* env, int isStart){

}


void sysLibCDivHookHandler(CPUState* env, int isStart){

}


void sysLibCIsblankHookHandler(CPUState* env, int isStart){

}


void sysLibCTtynameHookHandler(CPUState* env, int isStart){

}


void sysLibCKlogctlHookHandler(CPUState* env, int isStart){

}


void sysLibCSnprintfHookHandler(CPUState* env, int isStart){

}


void sysLibCOptindHookHandler(CPUState* env, int isStart){

}


void sysLibCMemsetHookHandler(CPUState* env, int isStart){

}


void sysLibCWcschrHookHandler(CPUState* env, int isStart){

}


void sysLibCSyncHookHandler(CPUState* env, int isStart){

}


void sysLibCGetgrouplistHookHandler(CPUState* env, int isStart){

}


void sysLibCMknodHookHandler(CPUState* env, int isStart){

}


void sysLibCStrcasestrHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Mutex_DestroyHookHandler(CPUState* env, int isStart){

}


void sysLibCWcrtombHookHandler(CPUState* env, int isStart){

}


void sysLibCStrlcatHookHandler(CPUState* env, int isStart){

}


void sysLibCLlistxattrHookHandler(CPUState* env, int isStart){

}


void sysLibCMktempHookHandler(CPUState* env, int isStart){

}


void sysLibCGetchar_UnlockedHookHandler(CPUState* env, int isStart){

}


void sysLibCClockHookHandler(CPUState* env, int isStart){

}


void sysLibCAtexitHookHandler(CPUState* env, int isStart){

}


void sysLibCOpenlogHookHandler(CPUState* env, int isStart){

}


void sysLibCInotify_Add_WatchHookHandler(CPUState* env, int isStart){

}


void sysLibCAccessHookHandler(CPUState* env, int isStart){

}


void sysLibCBasename_RHookHandler(CPUState* env, int isStart){

}


void sysLibCSetlogmaskHookHandler(CPUState* env, int isStart){

}


void sysLibCWcstolHookHandler(CPUState* env, int isStart){

}


void sysLibCMunmapHookHandler(CPUState* env, int isStart){

}


void sysLibCSocketpairHookHandler(CPUState* env, int isStart){

}


void sysLibCSettimeofdayHookHandler(CPUState* env, int isStart){

}


void sysLibCSetresuidHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_DetachHookHandler(CPUState* env, int isStart){

}


void sysLibCFts_CloseHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Attr_SetdetachstateHookHandler(CPUState* env, int isStart){

}


void sysLibCSetpgidHookHandler(CPUState* env, int isStart){

}


void sysLibCVwprintfHookHandler(CPUState* env, int isStart){

}


void sysLibCLocaltime_RHookHandler(CPUState* env, int isStart){

}


void sysLibCTimelocal64HookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Attr_InitHookHandler(CPUState* env, int isStart){

}


void sysLibCPauseHookHandler(CPUState* env, int isStart){

}


void sysLibCTimer_SettimeHookHandler(CPUState* env, int isStart){

}


void sysLibCSetregidHookHandler(CPUState* env, int isStart){

}


void sysLibCFchdirHookHandler(CPUState* env, int isStart){

}


void sysLibCWcpncpyHookHandler(CPUState* env, int isStart){

}


void sysLibCFake_Localtime_RHookHandler(CPUState* env, int isStart){

}


void sysLibCWaitHookHandler(CPUState* env, int isStart){

}


void sysLibCGetdentsHookHandler(CPUState* env, int isStart){

}


void sysLibCVerrxHookHandler(CPUState* env, int isStart){

}


void sysLibCEventfdHookHandler(CPUState* env, int isStart){

}


void sysLibCPipe2HookHandler(CPUState* env, int isStart){

}


void sysLibCEther_Ntoa_RHookHandler(CPUState* env, int isStart){

}


void sysLibCPopenHookHandler(CPUState* env, int isStart){

}


void sysLibCWcsxfrmHookHandler(CPUState* env, int isStart){

}


void sysLibCFputwcHookHandler(CPUState* env, int isStart){

}


void sysLibCPerf_Event_OpenHookHandler(CPUState* env, int isStart){

}


void sysLibCSendmsgHookHandler(CPUState* env, int isStart){

}


void sysLibCIswalnumHookHandler(CPUState* env, int isStart){

}


void sysLibCEpoll_CtlHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Mutexattr_GettypeHookHandler(CPUState* env, int isStart){

}


void sysLibCBzeroHookHandler(CPUState* env, int isStart){

}


void sysLibCWcstokHookHandler(CPUState* env, int isStart){

}


void sysLibCBrkHookHandler(CPUState* env, int isStart){

}


void sysLibCSched_Rr_Get_IntervalHookHandler(CPUState* env, int isStart){

}


void sysLibCPrintfHookHandler(CPUState* env, int isStart){

}


void sysLibCFtokHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Mutex_InitHookHandler(CPUState* env, int isStart){

}


void sysLibCWcstodHookHandler(CPUState* env, int isStart){

}


void sysLibCClock_SettimeHookHandler(CPUState* env, int isStart){

}


void sysLibCSelectHookHandler(CPUState* env, int isStart){

}


void sysLibCGetcharHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_EqualHookHandler(CPUState* env, int isStart){

}


void sysLibCCloselog_RHookHandler(CPUState* env, int isStart){

}


void sysLibCGetsockoptHookHandler(CPUState* env, int isStart){

}


void sysLibCSha1UpdateHookHandler(CPUState* env, int isStart){

}


void sysLibCGetpriorityHookHandler(CPUState* env, int isStart){

}


void sysLibCGhashtableHookHandler(CPUState* env, int isStart){

}


void sysLibCFdatasyncHookHandler(CPUState* env, int isStart){

}


void sysLibCSys_SignameHookHandler(CPUState* env, int isStart){

}


void sysLibCIsattyHookHandler(CPUState* env, int isStart){

}


void sysLibCWcsncpyHookHandler(CPUState* env, int isStart){

}


void sysLibCPathconfHookHandler(CPUState* env, int isStart){

}


void sysLibCSched_GetschedulerHookHandler(CPUState* env, int isStart){

}


void sysLibCWarnHookHandler(CPUState* env, int isStart){

}


void sysLibCWcscatHookHandler(CPUState* env, int isStart){

}


void sysLibCGettimeofdayHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_SigmaskHookHandler(CPUState* env, int isStart){

}


void sysLibCSem_OpenHookHandler(CPUState* env, int isStart){

}


void sysLibCSocketHookHandler(CPUState* env, int isStart){

}


void sysLibCChdirHookHandler(CPUState* env, int isStart){

}


void sysLibCErrHookHandler(CPUState* env, int isStart){

}


void sysLibCFtrylockfileHookHandler(CPUState* env, int isStart){

}


void sysLibCStrerrorHookHandler(CPUState* env, int isStart){

}


void sysLibCIswlowerHookHandler(CPUState* env, int isStart){

}


void sysLibCSetuidHookHandler(CPUState* env, int isStart){

}


void sysLibCSwprintfHookHandler(CPUState* env, int isStart){

}


void sysLibCUtimensatHookHandler(CPUState* env, int isStart){

}


void sysLibCInet_Nsap_NtoaHookHandler(CPUState* env, int isStart){

}


void sysLibCFnmatchHookHandler(CPUState* env, int isStart){

}


void sysLibCFtruncateHookHandler(CPUState* env, int isStart){

}


void sysLibCGetprotobynumberHookHandler(CPUState* env, int isStart){

}


void sysLibCVforkHookHandler(CPUState* env, int isStart){

}

/*
 * long sysconf(int name)
 */
void sysLibCSysconfHookHandler(CPUState* env, int isStart){
	if(isStart){
		DECAF_printf("sysconf(%d)\n", env->regs[0]);
	}else{
		DECAF_printf("sysconf ret %d\n", env->regs[0]);
	}
}


void sysLibCWprintfHookHandler(CPUState* env, int isStart){

}

/*
 * int mprotect(void *addr, size_t len, int prot)
 */
void sysLibCMprotectHookHandler(CPUState* env, int isStart){
	if(isStart){
		DECAF_printf("mprotect(0x%x, 0x%x, %d)\n", 
				env->regs[0], env->regs[1], env->regs[2]);
	}else{
		DECAF_printf("mprotect ret %d\n", env->regs[0]);
	}
}


void sysLibCSem_TrywaitHookHandler(CPUState* env, int isStart){

}


void sysLibCAcceptHookHandler(CPUState* env, int isStart){

}


void sysLibCAbortHookHandler(CPUState* env, int isStart){

}

/**
 * int  fprintf(FILE *, const char *, ...)
 */
void sysLibCFprintfHookHandler(CPUState* env, int isStart){
	DECAF_printf("fprintf[%d]\n", isStart);
	if(isStart){
		char fmt[256];	
		fmt[0] = '\0';
		if(DECAF_read_mem_until(env, env->regs[1], &fmt, 356) > 0){
			DECAF_printf("fmt: %s\n", fmt);
			char* p;
			int isOnStack = 0;
			int regIdx = 2;
			int stackIdx = env->regs[13];
			int strAddr = 0;
			int taintValue = 0;
			int tmpTaint = 0;
			for(p = fmt; *p; p++){
				if(*p != '%'){
					continue;
				}
				switch(*++p){
					case 'l':
					case 'L':
						if(regIdx == 3 || isOnStack){
							tmpTaint = getTaint(stackIdx);
							if(tmpTaint > 0){
								taintValue |= tmpTaint;
								DECAF_printf("gTaint[%x]: %x\n", stackIdx, tmpTaint);
							}
							tmpTaint = getTaint(stackIdx + 4);
							if(tmpTaint > 0){
								taintValue |= tmpTaint;
								DECAF_printf("gTaint[%x]: %x\n", stackIdx + 4, tmpTaint);
							}
							stackIdx += 8;
							if(++regIdx == 4){
								isOnStack = 1;
							}
						}else if(regIdx == 2){
							tmpTaint = getRegTaint(2);
							if(tmpTaint > 0){
								taintValue |= tmpTaint;
								DECAF_printf("gR[2]: %x\n", tmpTaint);
							}
							tmpTaint = getRegTaint(3);
							if(tmpTaint > 0){
								taintValue |= tmpTaint;
								DECAF_printf("gR[3]: %x\n", tmpTaint);
							}
							isOnStack = 1;
							regIdx = 4;
						}
						break;
					default:
						if(isOnStack){
							tmpTaint = getTaint(stackIdx);
							if(tmpTaint > 0){
								taintValue |= tmpTaint;
								DECAF_printf("gTaint[%x]: %x\n", stackIdx, tmpTaint);
							}
							if(*p == 's' && DECAF_read_mem(env, stackIdx, &strAddr, 4) != -1){
								tmpTaint = getTaint(strAddr);
								if(tmpTaint > 0){
									taintValue |= tmpTaint;
									DECAF_printf("gTaint[%x]: %x\n", strAddr, tmpTaint);
									char taintedStr[256];
									if(DECAF_read_mem_until(env, strAddr, &taintedStr, 256) > 0){
										DECAF_printf("@%x %s\n", strAddr, taintedStr);
									}
								}
							}
							stackIdx += 4;
						}else{
							tmpTaint = getRegTaint(regIdx);
							if(tmpTaint > 0){
								taintValue |= tmpTaint;
								DECAF_printf("gR[%d]: %x\n", regIdx, tmpTaint);
							}
							if(*p == 's'){
								strAddr = env->regs[regIdx];
								tmpTaint = getTaint(strAddr);
								if(tmpTaint > 0){
									taintValue |= tmpTaint;
									DECAF_printf("gTaint[%x]: %x\n", strAddr, tmpTaint);
									char taintedStr[256];
									if(DECAF_read_mem_until(env, strAddr, &taintedStr, 256) > 0){
										DECAF_printf("@%x %s\n", strAddr, taintedStr);
									}
								}
							}
							if(++regIdx == 4){
								isOnStack = 1;
							}
						}
						break;
				}
			}
			
			if(taintValue > 0){
				DECAF_printf("Write data with taint %x to FILE@%x\n", taintValue, env->regs[0]);
			}	
		}
	}
}


void sysLibCStrtollHookHandler(CPUState* env, int isStart){

}


void sysLibCTowupperHookHandler(CPUState* env, int isStart){

}


void sysLibCStrlenHookHandler(CPUState* env, int isStart){

}


void sysLibCGet_Malloc_Leak_InfoHookHandler(CPUState* env, int isStart){

}


void sysLibCStrncatHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_GetspecificHookHandler(CPUState* env, int isStart){

}


void sysLibCChrootHookHandler(CPUState* env, int isStart){

}


void sysLibCClearerrHookHandler(CPUState* env, int isStart){

}


void sysLibCGetgroupsHookHandler(CPUState* env, int isStart){

}


void sysLibCFeofHookHandler(CPUState* env, int isStart){

}


void sysLibCLrand48HookHandler(CPUState* env, int isStart){

}


void sysLibCStrntoumaxHookHandler(CPUState* env, int isStart){

}


void sysLibCWriteHookHandler(CPUState* env, int isStart){

}


void sysLibCVfprintfHookHandler(CPUState* env, int isStart){

}


void sysLibCRewindHookHandler(CPUState* env, int isStart){

}


void sysLibCWmemchrHookHandler(CPUState* env, int isStart){

}


void sysLibCPutc_UnlockedHookHandler(CPUState* env, int isStart){

}


void sysLibCVwarnxHookHandler(CPUState* env, int isStart){

}


void sysLibCWcsrchrHookHandler(CPUState* env, int isStart){

}


void sysLibCFlockfileHookHandler(CPUState* env, int isStart){

}


void sysLibCIf_IndextonameHookHandler(CPUState* env, int isStart){

}


void sysLibCVasprintfHookHandler(CPUState* env, int isStart){

}


void sysLibCMemrchrHookHandler(CPUState* env, int isStart){

}


void sysLibCUnsetenvHookHandler(CPUState* env, int isStart){

}


void sysLibCOpenatHookHandler(CPUState* env, int isStart){

}


void sysLibCCloneHookHandler(CPUState* env, int isStart){

}


void sysLibCSigsetmaskHookHandler(CPUState* env, int isStart){

}


void sysLibCGetxattrHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Condattr_SetpsharedHookHandler(CPUState* env, int isStart){

}


void sysLibCIoctlHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Rwlock_WrlockHookHandler(CPUState* env, int isStart){

}


void sysLibCVallocHookHandler(CPUState* env, int isStart){

}


void sysLibCSetgroupsHookHandler(CPUState* env, int isStart){

}


void sysLibCUnlinkHookHandler(CPUState* env, int isStart){

}


void sysLibCGmtime64_RHookHandler(CPUState* env, int isStart){

}


void sysLibCTcgetpgrpHookHandler(CPUState* env, int isStart){

}


void sysLibCLongjmperrorHookHandler(CPUState* env, int isStart){

}


void sysLibCStrerror_RHookHandler(CPUState* env, int isStart){

}


void sysLibCBindHookHandler(CPUState* env, int isStart){

}


void sysLibCLocaltime64_RHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Attr_SetschedpolicyHookHandler(CPUState* env, int isStart){

}


void sysLibCIscntrlHookHandler(CPUState* env, int isStart){

}


void sysLibCSetpgrpHookHandler(CPUState* env, int isStart){

}


void sysLibCRes_SearchHookHandler(CPUState* env, int isStart){

}


void sysLibCEnvironHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Rwlock_TimedwrlockHookHandler(CPUState* env, int isStart){

}


void sysLibCEndusershellHookHandler(CPUState* env, int isStart){

}


void sysLibCGetserventHookHandler(CPUState* env, int isStart){

}


void sysLibCStrntoimaxHookHandler(CPUState* env, int isStart){

}


void sysLibCBasenameHookHandler(CPUState* env, int isStart){

}


void sysLibCExecleHookHandler(CPUState* env, int isStart){

}


void sysLibCFgetwcHookHandler(CPUState* env, int isStart){

}


void sysLibCUnameHookHandler(CPUState* env, int isStart){

}


void sysLibCBtowcHookHandler(CPUState* env, int isStart){

}


void sysLibCMbrlenHookHandler(CPUState* env, int isStart){

}


void sysLibCStrtoulHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_KillHookHandler(CPUState* env, int isStart){

}


void sysLibCExeclpHookHandler(CPUState* env, int isStart){

}


void sysLibCSem_UnlinkHookHandler(CPUState* env, int isStart){

}


void sysLibCEventfd_ReadHookHandler(CPUState* env, int isStart){

}


void sysLibCReadaheadHookHandler(CPUState* env, int isStart){

}


void sysLibCFwriteHookHandler(CPUState* env, int isStart){

}


void sysLibCGetpidHookHandler(CPUState* env, int isStart){

}


void sysLibCSetgidHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Mutexattr_SetpsharedHookHandler(CPUState* env, int isStart){

}


void sysLibCStrnlenHookHandler(CPUState* env, int isStart){

}


void sysLibCSched_Get_Priority_MinHookHandler(CPUState* env, int isStart){

}


void sysLibCFchownHookHandler(CPUState* env, int isStart){

}


void sysLibCFts_SetHookHandler(CPUState* env, int isStart){

}


void sysLibCGetpwnamHookHandler(CPUState* env, int isStart){

}


void sysLibCStrcollHookHandler(CPUState* env, int isStart){

}


void sysLibCRewinddirHookHandler(CPUState* env, int isStart){

}


void sysLibCExeclHookHandler(CPUState* env, int isStart){

}


void sysLibCInet_AddrHookHandler(CPUState* env, int isStart){

}


void sysLibCEther_NtoaHookHandler(CPUState* env, int isStart){

}


void sysLibCIswupperHookHandler(CPUState* env, int isStart){

}


void sysLibCBindresvportHookHandler(CPUState* env, int isStart){

}


void sysLibCSetreuidHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Attr_GetschedparamHookHandler(CPUState* env, int isStart){

}


void sysLibCSiglongjmpHookHandler(CPUState* env, int isStart){

}


void sysLibCErrxHookHandler(CPUState* env, int isStart){

}


void sysLibCSendtoHookHandler(CPUState* env, int isStart){

}


void sysLibCExecvHookHandler(CPUState* env, int isStart){

}


void sysLibCFts_ChildrenHookHandler(CPUState* env, int isStart){

}


void sysLibCMemchrHookHandler(CPUState* env, int isStart){

}


void sysLibCLgetxattrHookHandler(CPUState* env, int isStart){

}


void sysLibCClock_GettimeHookHandler(CPUState* env, int isStart){

}


void sysLibCVsscanfHookHandler(CPUState* env, int isStart){

}


void sysLibCSys_SiglistHookHandler(CPUState* env, int isStart){

}


void sysLibCSha1TransformHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Attr_SetstackHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Cond_SignalHookHandler(CPUState* env, int isStart){

}


void sysLibCConnectHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_CreateHookHandler(CPUState* env, int isStart){

}


void sysLibCFlockHookHandler(CPUState* env, int isStart){

}


void sysLibCDirnameHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Mutexattr_InitHookHandler(CPUState* env, int isStart){

}


void sysLibCStrlcpyHookHandler(CPUState* env, int isStart){

}


void sysLibCOpendirHookHandler(CPUState* env, int isStart){

}


void sysLibCDlmalloc_Walk_Free_PagesHookHandler(CPUState* env, int isStart){

}


void sysLibCSetsidHookHandler(CPUState* env, int isStart){

}


void sysLibCRestore_Core_RegsHookHandler(CPUState* env, int isStart){

}


void sysLibCSprintfHookHandler(CPUState* env, int isStart){

}


void sysLibCVscanfHookHandler(CPUState* env, int isStart){

}


void sysLibCStrrchrHookHandler(CPUState* env, int isStart){

}


void sysLibCRegexecHookHandler(CPUState* env, int isStart){

}


void sysLibCEventfd_WriteHookHandler(CPUState* env, int isStart){

}


void sysLibCGethostbyaddrHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Rwlock_DestroyHookHandler(CPUState* env, int isStart){

}


void sysLibCStrcspnHookHandler(CPUState* env, int isStart){

}


void sysLibCMd5_FinalHookHandler(CPUState* env, int isStart){

}


void sysLibCAsprintfHookHandler(CPUState* env, int isStart){

}


void sysLibCFerrorHookHandler(CPUState* env, int isStart){

}


void sysLibCGetcwdHookHandler(CPUState* env, int isStart){

}


void sysLibCFreeHookHandler(CPUState* env, int isStart){

}


void sysLibCFake_Gmtime_RHookHandler(CPUState* env, int isStart){

}


void sysLibCTfindHookHandler(CPUState* env, int isStart){

}


void sysLibCAsctime_RHookHandler(CPUState* env, int isStart){

}


void sysLibCGetpeernameHookHandler(CPUState* env, int isStart){

}


void sysLibCRecvHookHandler(CPUState* env, int isStart){

}


void sysLibCFwideHookHandler(CPUState* env, int isStart){

}


void sysLibCFseekoHookHandler(CPUState* env, int isStart){

}


void sysLibCPutcharHookHandler(CPUState* env, int isStart){

}


void sysLibCGethostbynameHookHandler(CPUState* env, int isStart){

}


void sysLibCWcsspnHookHandler(CPUState* env, int isStart){

}


void sysLibCGetprotobynameHookHandler(CPUState* env, int isStart){

}


void sysLibCTimesHookHandler(CPUState* env, int isStart){

}


void sysLibCCtime64HookHandler(CPUState* env, int isStart){

}


void sysLibCSched_GetcpuHookHandler(CPUState* env, int isStart){

}


void sysLibCPwrite64HookHandler(CPUState* env, int isStart){

}


void sysLibCIslowerHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Attr_GetstackHookHandler(CPUState* env, int isStart){

}


void sysLibCIsupperHookHandler(CPUState* env, int isStart){

}


void sysLibCVsyslogHookHandler(CPUState* env, int isStart){

}


void sysLibCGetopt_LongHookHandler(CPUState* env, int isStart){

}


void sysLibCGetservbynameHookHandler(CPUState* env, int isStart){

}


void sysLibCLocaltime64HookHandler(CPUState* env, int isStart){

}


void sysLibCWarnxHookHandler(CPUState* env, int isStart){

}


void sysLibCQsortHookHandler(CPUState* env, int isStart){

}


void sysLibCSem_PostHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_JoinHookHandler(CPUState* env, int isStart){

}


void sysLibCBcopyHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Attr_GetstacksizeHookHandler(CPUState* env, int isStart){

}


void sysLibCLdexpHookHandler(CPUState* env, int isStart){

}


void sysLibCNsdispatchHookHandler(CPUState* env, int isStart){

}


void sysLibCFsetxattrHookHandler(CPUState* env, int isStart){

}


void sysLibCRes_Get_Dns_ChangedHookHandler(CPUState* env, int isStart){

}


void sysLibCAcctHookHandler(CPUState* env, int isStart){

}


void sysLibCGetservbyportHookHandler(CPUState* env, int isStart){

}


void sysLibCOpenHookHandler(CPUState* env, int isStart){

}


void sysLibCStrncpyHookHandler(CPUState* env, int isStart){

}


void sysLibCUsleepHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Mutex_Lock_Timeout_NpHookHandler(CPUState* env, int isStart){

}


void sysLibCClock_NanosleepHookHandler(CPUState* env, int isStart){

}


void sysLibCWcsnlenHookHandler(CPUState* env, int isStart){

}


void sysLibCIsalnumHookHandler(CPUState* env, int isStart){

}


void sysLibCListxattrHookHandler(CPUState* env, int isStart){

}


void sysLibCScanfHookHandler(CPUState* env, int isStart){

}


void sysLibCMkdirHookHandler(CPUState* env, int isStart){

}


void sysLibCSystemHookHandler(CPUState* env, int isStart){

}


void sysLibCSigpendingHookHandler(CPUState* env, int isStart){

}


void sysLibCStrcasecmpHookHandler(CPUState* env, int isStart){

}


void sysLibCFaccessatHookHandler(CPUState* env, int isStart){

}


void sysLibCIsalphaHookHandler(CPUState* env, int isStart){

}

/*
 * int memcmp(const void *s1, const void *s2, size_t n)
 */
void sysLibCMemcmpHookHandler(CPUState* env, int isStart){
	if(isStart){
		size_t n = env->regs[2];
		char* s1 = (char*) calloc(n+1, sizeof(char));
		char* s2 = (char*) calloc(n+1, sizeof(char));
		s1[n] = s2[n] = '\0';
		DECAF_read_mem_until(env, env->regs[0], s1, n);
		DECAF_read_mem_until(env, env->regs[1], s2, n);
		DECAF_printf("memcmp(%s, %s, %d)\n", s1, s2, n);
	}else{
		DECAF_printf("memcmp ret %d\n", env->regs[0]);
	}
}


void sysLibCStrftime_TzHookHandler(CPUState* env, int isStart){

}


void sysLibCGmtime64HookHandler(CPUState* env, int isStart){

}


void sysLibCGetpwnam_RHookHandler(CPUState* env, int isStart){

}


void sysLibCListenHookHandler(CPUState* env, int isStart){

}


void sysLibCInotify_InitHookHandler(CPUState* env, int isStart){

}


void sysLibCDlreallocHookHandler(CPUState* env, int isStart){

}


void sysLibCMd5_UpdateHookHandler(CPUState* env, int isStart){

}


void sysLibCDlmallocHookHandler(CPUState* env, int isStart){

}


void sysLibCFgetxattrHookHandler(CPUState* env, int isStart){

}


void sysLibCPwriteHookHandler(CPUState* env, int isStart){

}


void sysLibCMlockHookHandler(CPUState* env, int isStart){

}


void sysLibCIsasciiHookHandler(CPUState* env, int isStart){

}


void sysLibCTimegm64HookHandler(CPUState* env, int isStart){

}


void sysLibCSyslogHookHandler(CPUState* env, int isStart){

}


void sysLibCStatfsHookHandler(CPUState* env, int isStart){

}


void sysLibCWcscmpHookHandler(CPUState* env, int isStart){

}


void sysLibCWcscpyHookHandler(CPUState* env, int isStart){

}


void sysLibCVfdprintfHookHandler(CPUState* env, int isStart){

}


void sysLibCSetbufferHookHandler(CPUState* env, int isStart){

}


void sysLibCTznameHookHandler(CPUState* env, int isStart){

}


void sysLibCSigwaitHookHandler(CPUState* env, int isStart){

}


void sysLibCSha1FinalHookHandler(CPUState* env, int isStart){

}


void sysLibCGmtime_RHookHandler(CPUState* env, int isStart){

}


void sysLibCVsnprintfHookHandler(CPUState* env, int isStart){

}


void sysLibCWcstoulHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Attr_GetstackaddrHookHandler(CPUState* env, int isStart){

}


void sysLibCMremapHookHandler(CPUState* env, int isStart){

}


void sysLibCPselectHookHandler(CPUState* env, int isStart){

}


void sysLibCEther_Aton_RHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_OnceHookHandler(CPUState* env, int isStart){

}


void sysLibCVprintfHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_AtforkHookHandler(CPUState* env, int isStart){

}


void sysLibCWmemcpyHookHandler(CPUState* env, int isStart){

}


void sysLibCIswgraphHookHandler(CPUState* env, int isStart){

}


void sysLibCJrand48HookHandler(CPUState* env, int isStart){

}


void sysLibCGeteuidHookHandler(CPUState* env, int isStart){

}


void sysLibCFseekHookHandler(CPUState* env, int isStart){

}


void sysLibCStrptimeHookHandler(CPUState* env, int isStart){

}


void sysLibCDlmalloc_Usable_SizeHookHandler(CPUState* env, int isStart){

}


void sysLibCGetopt_Long_OnlyHookHandler(CPUState* env, int isStart){

}


void sysLibCTsearchHookHandler(CPUState* env, int isStart){

}


void sysLibCFunopenHookHandler(CPUState* env, int isStart){

}


void sysLibCIswalphaHookHandler(CPUState* env, int isStart){

}


void sysLibCGetrlimitHookHandler(CPUState* env, int isStart){

}


void sysLibCRealpathHookHandler(CPUState* env, int isStart){

}


void sysLibCTimer_GetoverrunHookHandler(CPUState* env, int isStart){

}


void sysLibCDlmallinfoHookHandler(CPUState* env, int isStart){

}


void sysLibCTolowerHookHandler(CPUState* env, int isStart){

}


void sysLibCSched_YieldHookHandler(CPUState* env, int isStart){

}


void sysLibCWaitidHookHandler(CPUState* env, int isStart){

}


void sysLibCSetjmpHookHandler(CPUState* env, int isStart){

}


void sysLibCIf_NametoindexHookHandler(CPUState* env, int isStart){

}


void sysLibCStrpbrkHookHandler(CPUState* env, int isStart){

}


void sysLibCOpterrHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Cond_InitHookHandler(CPUState* env, int isStart){

}


void sysLibCSetserventHookHandler(CPUState* env, int isStart){

}


void sysLibCOptresetHookHandler(CPUState* env, int isStart){

}


void sysLibCSrand48HookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Rwlock_TryrdlockHookHandler(CPUState* env, int isStart){

}


void sysLibCWcswcsHookHandler(CPUState* env, int isStart){

}


void sysLibCAlarmHookHandler(CPUState* env, int isStart){

}


void sysLibCDlmalloc_Max_FootprintHookHandler(CPUState* env, int isStart){

}


void sysLibCGetutentHookHandler(CPUState* env, int isStart){

}


void sysLibCFutexHookHandler(CPUState* env, int isStart){

}


void sysLibCPipeHookHandler(CPUState* env, int isStart){

}


void sysLibCWcsstrHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Attr_GetdetachstateHookHandler(CPUState* env, int isStart){

}


void sysLibCUtimesHookHandler(CPUState* env, int isStart){

}


void sysLibCSetvbufHookHandler(CPUState* env, int isStart){

}


void sysLibCScandirHookHandler(CPUState* env, int isStart){

}


void sysLibCStrncasecmpHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Getattr_NpHookHandler(CPUState* env, int isStart){

}


void sysLibCSem_WaitHookHandler(CPUState* env, int isStart){

}


void sysLibCGallocationsmutexHookHandler(CPUState* env, int isStart){

}


void sysLibCFreopenHookHandler(CPUState* env, int isStart){

}


void sysLibCAsctime64_RHookHandler(CPUState* env, int isStart){

}


void sysLibCFpurgeHookHandler(CPUState* env, int isStart){

}


void sysLibCPosix2TimeHookHandler(CPUState* env, int isStart){

}


void sysLibCPutchar_UnlockedHookHandler(CPUState* env, int isStart){

}


void sysLibCStrtoullHookHandler(CPUState* env, int isStart){

}


void sysLibCDirname_RHookHandler(CPUState* env, int isStart){

}


void sysLibCLseek64HookHandler(CPUState* env, int isStart){

}


void sysLibCStrtolHookHandler(CPUState* env, int isStart){

}


void sysLibCFputcHookHandler(CPUState* env, int isStart){

}


void sysLibCMalloc_Double_Free_BacklogHookHandler(CPUState* env, int isStart){

}


void sysLibCEpoll_CreateHookHandler(CPUState* env, int isStart){

}


void sysLibCGmallocleakzygotechildHookHandler(CPUState* env, int isStart){

}


void sysLibCStrtokHookHandler(CPUState* env, int isStart){

}


void sysLibCStrtodHookHandler(CPUState* env, int isStart){

}


void sysLibCMkstempsHookHandler(CPUState* env, int isStart){

}


void sysLibCWritevHookHandler(CPUState* env, int isStart){

}


void sysLibCFputsHookHandler(CPUState* env, int isStart){

}


void sysLibCFchmodHookHandler(CPUState* env, int isStart){

}


void sysLibCFtimeHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Mutex_TrylockHookHandler(CPUState* env, int isStart){

}


void sysLibCEpoll_WaitHookHandler(CPUState* env, int isStart){

}


void sysLibCFstatHookHandler(CPUState* env, int isStart){

}


void sysLibCCapsetHookHandler(CPUState* env, int isStart){

}


void sysLibCPersonalityHookHandler(CPUState* env, int isStart){

}


void sysLibCWmemsetHookHandler(CPUState* env, int isStart){

}


void sysLibCIswctypeHookHandler(CPUState* env, int isStart){

}


void sysLibCDup2HookHandler(CPUState* env, int isStart){

}


void sysLibCWcscollHookHandler(CPUState* env, int isStart){

}


void sysLibCFfsHookHandler(CPUState* env, int isStart){

}


void sysLibCInet_NtopHookHandler(CPUState* env, int isStart){

}


void sysLibCIswxdigitHookHandler(CPUState* env, int isStart){

}


void sysLibCWcsncmpHookHandler(CPUState* env, int isStart){

}


void sysLibCStrsepHookHandler(CPUState* env, int isStart){

}


void sysLibCGetpgrpHookHandler(CPUState* env, int isStart){

}


void sysLibCPtsname_RHookHandler(CPUState* env, int isStart){

}


void sysLibCInet_NtoaHookHandler(CPUState* env, int isStart){

}

/*
 * void *memcpy(void *dest, const void *src, size_t n)
 */
void sysLibCMemcpyHookHandler(CPUState* env, int isStart){
	if(isStart){
		size_t n = env->regs[2];
		int i = 0;
		char* dest = (char*) calloc(n+1, sizeof(char));
		char* src = (char*) calloc(n+1, sizeof(char));
		dest[n] = src[n] = '\0';
		DECAF_read_mem_until(env, env->regs[0], dest, n);
		DECAF_read_mem_until(env, env->regs[1], src, n);
		DECAF_printf("memcpy(%s, %s, %d)\n", dest, src, n);
		for(; i < n; i++){
			int tValue = getTaint(env->regs[1] + i);
			setTaint(env->regs[0] + i, tValue);
		}
	}
}


void sysLibCFilenoHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Cond_Timeout_NpHookHandler(CPUState* env, int isStart){

}


void sysLibCPerrorHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_GetschedparamHookHandler(CPUState* env, int isStart){

}


void sysLibCFscanfHookHandler(CPUState* env, int isStart){

}


void sysLibCUmountHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Cond_WaitHookHandler(CPUState* env, int isStart){

}


void sysLibCEndutentHookHandler(CPUState* env, int isStart){

}


void sysLibCSyslog_RHookHandler(CPUState* env, int isStart){

}


void sysLibCMkdiratHookHandler(CPUState* env, int isStart){

}


void sysLibCFgetwsHookHandler(CPUState* env, int isStart){

}

/*
 * int strncmp(const char *s1, const char *s2, size_t n)
 */
void sysLibCStrncmpHookHandler(CPUState* env, int isStart){
	if(isStart){
		char buf1[128], buf2[128];
		buf1[0] = buf2[0] = '\0';
		DECAF_read_mem_until(env, env->regs[0], &buf1, 128);
		DECAF_read_mem_until(env, env->regs[1], &buf2, 128);
		DECAF_printf("strncmp(%s, %s, %d)\n", buf1, buf2, env->regs[2]);
	}else{
		DECAF_printf("strncmp ret %d\n", env->regs[0]);
	}
}


void sysLibCMkdtempHookHandler(CPUState* env, int isStart){

}


void sysLibCStrcatHookHandler(CPUState* env, int isStart){

}


void sysLibCSetlogmask_RHookHandler(CPUState* env, int isStart){

}


void sysLibCFchownatHookHandler(CPUState* env, int isStart){

}


void sysLibCGetsocknameHookHandler(CPUState* env, int isStart){

}


void sysLibCHerrorHookHandler(CPUState* env, int isStart){

}


void sysLibCCloseHookHandler(CPUState* env, int isStart){

}


void sysLibCLsetxattrHookHandler(CPUState* env, int isStart){

}


void sysLibCFsetposHookHandler(CPUState* env, int isStart){

}


void sysLibCStrchrHookHandler(CPUState* env, int isStart){

}


void sysLibCLremovexattrHookHandler(CPUState* env, int isStart){

}


void sysLibCArc4Random_AddrandomHookHandler(CPUState* env, int isStart){

}


void sysLibCArc4Random_UniformHookHandler(CPUState* env, int isStart){

}


void sysLibCGethostbyname2HookHandler(CPUState* env, int isStart){

}


void sysLibCFgetposHookHandler(CPUState* env, int isStart){

}


void sysLibCFunlockfileHookHandler(CPUState* env, int isStart){

}


void sysLibCPosix_MemalignHookHandler(CPUState* env, int isStart){

}


void sysLibCSigaltstackHookHandler(CPUState* env, int isStart){

}


void sysLibCSem_CloseHookHandler(CPUState* env, int isStart){

}


void sysLibCAtollHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Rwlock_TimedrdlockHookHandler(CPUState* env, int isStart){

}


void sysLibCFcntlHookHandler(CPUState* env, int isStart){

}


void sysLibCInet_Nsap_AddrHookHandler(CPUState* env, int isStart){

}


void sysLibCArc4Random_StirHookHandler(CPUState* env, int isStart){

}


void sysLibCOpenlog_RHookHandler(CPUState* env, int isStart){

}


void sysLibCMemalignHookHandler(CPUState* env, int isStart){

}


void sysLibCLstatHookHandler(CPUState* env, int isStart){

}


void sysLibCInit_ModuleHookHandler(CPUState* env, int isStart){

}


void sysLibCSetresgidHookHandler(CPUState* env, int isStart){

}


void sysLibCTimelocalHookHandler(CPUState* env, int isStart){

}


void sysLibCGetdtablesizeHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Attr_SetguardsizeHookHandler(CPUState* env, int isStart){

}


void sysLibCSetsockoptHookHandler(CPUState* env, int isStart){

}


void sysLibCFstatatHookHandler(CPUState* env, int isStart){

}


void sysLibCInitgroupsHookHandler(CPUState* env, int isStart){

}


void sysLibCRes_MkqueryHookHandler(CPUState* env, int isStart){

}


void sysLibCSysv_SignalHookHandler(CPUState* env, int isStart){

}


void sysLibCGethostentHookHandler(CPUState* env, int isStart){

}


void sysLibCCloselogHookHandler(CPUState* env, int isStart){

}


void sysLibCFree_Malloc_Leak_InfoHookHandler(CPUState* env, int isStart){

}


void sysLibCStrftimeHookHandler(CPUState* env, int isStart){

}


void sysLibCMbsinitHookHandler(CPUState* env, int isStart){

}


void sysLibCTzsetHookHandler(CPUState* env, int isStart){

}


void sysLibCTime2PosixHookHandler(CPUState* env, int isStart){

}


void sysLibCStrxfrmHookHandler(CPUState* env, int isStart){

}


void sysLibCChmodHookHandler(CPUState* env, int isStart){

}


void sysLibCSetxattrHookHandler(CPUState* env, int isStart){

}


void sysLibCFdprintfHookHandler(CPUState* env, int isStart){

}


void sysLibCShutdownHookHandler(CPUState* env, int isStart){

}


void sysLibCPreadHookHandler(CPUState* env, int isStart){

}


void sysLibCPollHookHandler(CPUState* env, int isStart){

}


void sysLibCUngetwcHookHandler(CPUState* env, int isStart){

}


void sysLibCPutwHookHandler(CPUState* env, int isStart){

}


void sysLibCSigprocmaskHookHandler(CPUState* env, int isStart){

}


void sysLibCRaiseHookHandler(CPUState* env, int isStart){

}


void sysLibCPutsHookHandler(CPUState* env, int isStart){

}


void sysLibCSigactionHookHandler(CPUState* env, int isStart){

}


void sysLibCNanosleepHookHandler(CPUState* env, int isStart){

}


void sysLibCPutcHookHandler(CPUState* env, int isStart){

}


void sysLibCDupHookHandler(CPUState* env, int isStart){

}


void sysLibCStrtoumaxHookHandler(CPUState* env, int isStart){

}


void sysLibCMbrtowcHookHandler(CPUState* env, int isStart){

}


void sysLibCStrsignalHookHandler(CPUState* env, int isStart){

}


void sysLibCMktimeHookHandler(CPUState* env, int isStart){

}


void sysLibCDlmalloc_StatsHookHandler(CPUState* env, int isStart){

}


void sysLibCCtime64_RHookHandler(CPUState* env, int isStart){

}


void sysLibCExecvpHookHandler(CPUState* env, int isStart){

}


void sysLibCMbsrtowcsHookHandler(CPUState* env, int isStart){

}


void sysLibCStrtok_RHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Attr_SetschedparamHookHandler(CPUState* env, int isStart){

}


void sysLibCWcswidthHookHandler(CPUState* env, int isStart){

}


void sysLibCExecveHookHandler(CPUState* env, int isStart){

}


void sysLibCFputwsHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Attr_SetstackaddrHookHandler(CPUState* env, int isStart){

}


void sysLibCDrand48HookHandler(CPUState* env, int isStart){

}


void sysLibCMadviseHookHandler(CPUState* env, int isStart){

}


void sysLibCMountHookHandler(CPUState* env, int isStart){

}


void sysLibCGetrusageHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Attr_GetschedpolicyHookHandler(CPUState* env, int isStart){

}


void sysLibCGetgrnamHookHandler(CPUState* env, int isStart){

}


void sysLibCIoprio_GetHookHandler(CPUState* env, int isStart){

}


void sysLibCGetpwuidHookHandler(CPUState* env, int isStart){

}


void sysLibCVsprintfHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Rwlock_UnlockHookHandler(CPUState* env, int isStart){

}


void sysLibCRenameHookHandler(CPUState* env, int isStart){

}


void sysLibCMallocHookHandler(CPUState* env, int isStart){

}


void sysLibCDlmemalignHookHandler(CPUState* env, int isStart){

}


void sysLibCWcwidthHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_GetcpuclockidHookHandler(CPUState* env, int isStart){

}


void sysLibCReadvHookHandler(CPUState* env, int isStart){

}


void sysLibCPrctlHookHandler(CPUState* env, int isStart){

}


void sysLibCRes_QueryHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Attr_SetscopeHookHandler(CPUState* env, int isStart){

}


void sysLibCDlmalloc_Walk_HeapHookHandler(CPUState* env, int isStart){

}


void sysLibCSched_GetparamHookHandler(CPUState* env, int isStart){

}


void sysLibCGetcHookHandler(CPUState* env, int isStart){

}


void sysLibCMunlockHookHandler(CPUState* env, int isStart){

}


void sysLibCVsyslog_RHookHandler(CPUState* env, int isStart){

}


void sysLibCRecvmsgHookHandler(CPUState* env, int isStart){

}


void sysLibCTowlowerHookHandler(CPUState* env, int isStart){

}


void sysLibCDlmalloptHookHandler(CPUState* env, int isStart){

}


void sysLibCGetsHookHandler(CPUState* env, int isStart){

}


void sysLibCWaitpidHookHandler(CPUState* env, int isStart){

}


void sysLibCOptargHookHandler(CPUState* env, int isStart){

}


void sysLibCTdestroyHookHandler(CPUState* env, int isStart){

}


void sysLibCLongjmpHookHandler(CPUState* env, int isStart){

}


void sysLibCGetusershellHookHandler(CPUState* env, int isStart){

}


void sysLibCAsctime64HookHandler(CPUState* env, int isStart){

}


void sysLibCFdopendirHookHandler(CPUState* env, int isStart){

}


void sysLibCIsgraphHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Rwlock_RdlockHookHandler(CPUState* env, int isStart){

}


void sysLibCCallocHookHandler(CPUState* env, int isStart){

}


void sysLibCSetbufHookHandler(CPUState* env, int isStart){

}


void sysLibCUnlinkatHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Attr_GetguardsizeHookHandler(CPUState* env, int isStart){

}


void sysLibCIswprintHookHandler(CPUState* env, int isStart){

}


void sysLibCSetitimerHookHandler(CPUState* env, int isStart){

}


void sysLibCClearenvHookHandler(CPUState* env, int isStart){

}


void sysLibCSigblockHookHandler(CPUState* env, int isStart){

}


void sysLibCNrand48HookHandler(CPUState* env, int isStart){

}


void sysLibCDn_ExpandHookHandler(CPUState* env, int isStart){

}


void sysLibCFts_OpenHookHandler(CPUState* env, int isStart){

}


void sysLibCPutwcharHookHandler(CPUState* env, int isStart){

}


void sysLibCLseekHookHandler(CPUState* env, int isStart){

}


void sysLibCWcpcpyHookHandler(CPUState* env, int isStart){

}


void sysLibCMallinfoHookHandler(CPUState* env, int isStart){

}


void sysLibCFlistxattrHookHandler(CPUState* env, int isStart){

}


void sysLibCWmemcmpHookHandler(CPUState* env, int isStart){

}


void sysLibCDlmalloc_TrimHookHandler(CPUState* env, int isStart){

}


void sysLibCWcslcatHookHandler(CPUState* env, int isStart){

}


void sysLibCKillHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Condattr_DestroyHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Mutexattr_GetpsharedHookHandler(CPUState* env, int isStart){

}


void sysLibCFflushHookHandler(CPUState* env, int isStart){

}


void sysLibCClock_GetresHookHandler(CPUState* env, int isStart){

}


void sysLibCSem_DestroyHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Attr_DestroyHookHandler(CPUState* env, int isStart){

}


void sysLibCMmapHookHandler(CPUState* env, int isStart){

}


void sysLibCTimer_DeleteHookHandler(CPUState* env, int isStart){

}


void sysLibCPtsnameHookHandler(CPUState* env, int isStart){

}


void sysLibCSem_InitHookHandler(CPUState* env, int isStart){

}


void sysLibCSetenvHookHandler(CPUState* env, int isStart){

}


void sysLibCOptoptHookHandler(CPUState* env, int isStart){

}


void sysLibCLchownHookHandler(CPUState* env, int isStart){

}


void sysLibCReallocHookHandler(CPUState* env, int isStart){

}


void sysLibCIoprio_SetHookHandler(CPUState* env, int isStart){

}


void sysLibCH_ErrlistHookHandler(CPUState* env, int isStart){

}


void sysLibCDelete_ModuleHookHandler(CPUState* env, int isStart){

}


void sysLibCWcspbrkHookHandler(CPUState* env, int isStart){

}


void sysLibCReadHookHandler(CPUState* env, int isStart){

}


void sysLibCIswcntrlHookHandler(CPUState* env, int isStart){

}


void sysLibCToasciiHookHandler(CPUState* env, int isStart){

}


void sysLibCHstrerrorHookHandler(CPUState* env, int isStart){

}


void sysLibCGetnetbyaddrHookHandler(CPUState* env, int isStart){

}


void sysLibCCacheflushHookHandler(CPUState* env, int isStart){

}


void sysLibCCtimeHookHandler(CPUState* env, int isStart){

}


void sysLibCDaemonHookHandler(CPUState* env, int isStart){

}


void sysLibCStrstrHookHandler(CPUState* env, int isStart){

}


void sysLibCRenameatHookHandler(CPUState* env, int isStart){

}


void sysLibCFsyncHookHandler(CPUState* env, int isStart){

}


void sysLibCMemmoveHookHandler(CPUState* env, int isStart){

}


void sysLibCInet_AtonHookHandler(CPUState* env, int isStart){

}


void sysLibCIswpunctHookHandler(CPUState* env, int isStart){

}


void sysLibCSetegidHookHandler(CPUState* env, int isStart){

}


void sysLibCTimer_CreateHookHandler(CPUState* env, int isStart){

}


void sysLibCBsd_SignalHookHandler(CPUState* env, int isStart){

}

/*
 * int strcmp(const char *s1, const char *s2)
 */
void sysLibCStrcmpHookHandler(CPUState* env, int isStart){
	if(isStart){
		char buf1[128], buf2[128];
		buf1[0] = buf2[0] = '\0';
		DECAF_read_mem_until(env, env->regs[0], &buf1, 128);
		DECAF_read_mem_until(env, env->regs[1], &buf2, 128);
		DECAF_printf("strcmp(%s, %s)\n", buf1, buf2);
	}else{
		DECAF_printf("strcmp ret %d\n", env->regs[0]);
	}
}


void sysLibCTempnamHookHandler(CPUState* env, int isStart){

}


void sysLibCTmpfileHookHandler(CPUState* env, int isStart){

}


void sysLibCRegcompHookHandler(CPUState* env, int isStart){

}


void sysLibCLldivHookHandler(CPUState* env, int isStart){

}


void sysLibCToupperHookHandler(CPUState* env, int isStart){

}


void sysLibCFgetcHookHandler(CPUState* env, int isStart){

}


void sysLibCPcloseHookHandler(CPUState* env, int isStart){

}


void sysLibCMrand48HookHandler(CPUState* env, int isStart){

}


void sysLibCFtruncate64HookHandler(CPUState* env, int isStart){

}


void sysLibCReaddirHookHandler(CPUState* env, int isStart){

}


void sysLibCSeed48HookHandler(CPUState* env, int isStart){

}


void sysLibCGetresuidHookHandler(CPUState* env, int isStart){

}


void sysLibCDaylightHookHandler(CPUState* env, int isStart){

}


void sysLibCGetloginHookHandler(CPUState* env, int isStart){

}


void sysLibCDlcallocHookHandler(CPUState* env, int isStart){

}


void sysLibCFgetsHookHandler(CPUState* env, int isStart){

}


void sysLibCGetgidHookHandler(CPUState* env, int isStart){

}


void sysLibCSem_GetvalueHookHandler(CPUState* env, int isStart){

}


void sysLibCTgkillHookHandler(CPUState* env, int isStart){

}


void sysLibCSem_TimedwaitHookHandler(CPUState* env, int isStart){

}


void sysLibCSched_SetaffinityHookHandler(CPUState* env, int isStart){

}


void sysLibCArc4Random_BufHookHandler(CPUState* env, int isStart){

}


void sysLibCFremovexattrHookHandler(CPUState* env, int isStart){

}


void sysLibCFtellHookHandler(CPUState* env, int isStart){

}


void sysLibCExitHookHandler(CPUState* env, int isStart){

}


void sysLibCTtyname_RHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_SetspecificHookHandler(CPUState* env, int isStart){

}


void sysLibCAsctimeHookHandler(CPUState* env, int isStart){

}


void sysLibCInotify_Rm_WatchHookHandler(CPUState* env, int isStart){

}


void sysLibCSigsetjmpHookHandler(CPUState* env, int isStart){

}


void sysLibCMbstowcsHookHandler(CPUState* env, int isStart){

}


void sysLibCSetrlimitHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_ExitHookHandler(CPUState* env, int isStart){

}


void sysLibCGetitimerHookHandler(CPUState* env, int isStart){

}


void sysLibCFchmodatHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Rwlock_TrywrlockHookHandler(CPUState* env, int isStart){

}


void sysLibCGmtimeHookHandler(CPUState* env, int isStart){

}


void sysLibCSymlinkHookHandler(CPUState* env, int isStart){

}


void sysLibCPututlineHookHandler(CPUState* env, int isStart){

}


void sysLibCDirfdHookHandler(CPUState* env, int isStart){

}


void sysLibCGetgrgidHookHandler(CPUState* env, int isStart){

}


void sysLibCTimer_GettimeHookHandler(CPUState* env, int isStart){

}


void sysLibCGethostnameHookHandler(CPUState* env, int isStart){

}


void sysLibCGetnameinfoHookHandler(CPUState* env, int isStart){

}


void sysLibCSysinfoHookHandler(CPUState* env, int isStart){

}


void sysLibCStrtotimevalHookHandler(CPUState* env, int isStart){

}


void sysLibCMsyncHookHandler(CPUState* env, int isStart){

}


void sysLibCSetusershellHookHandler(CPUState* env, int isStart){

}


void sysLibCMemswapHookHandler(CPUState* env, int isStart){

}


void sysLibCSiginterruptHookHandler(CPUState* env, int isStart){

}


void sysLibCIswdigitHookHandler(CPUState* env, int isStart){

}


void sysLibCStrcpyHookHandler(CPUState* env, int isStart){

}


void sysLibCBsearchHookHandler(CPUState* env, int isStart){

}


void sysLibCReadlinkHookHandler(CPUState* env, int isStart){

}


void sysLibCDlmalloc_FootprintHookHandler(CPUState* env, int isStart){

}


void sysLibCWmemmoveHookHandler(CPUState* env, int isStart){

}


void sysLibCEther_AtonHookHandler(CPUState* env, int isStart){

}


void sysLibCArc4RandomHookHandler(CPUState* env, int isStart){

}


void sysLibCDlfreeHookHandler(CPUState* env, int isStart){

}


void sysLibCUmount2HookHandler(CPUState* env, int isStart){

}


void sysLibCWcscasecmpHookHandler(CPUState* env, int isStart){

}


void sysLibCIsprintHookHandler(CPUState* env, int isStart){

}


void sysLibCGetpgidHookHandler(CPUState* env, int isStart){

}


void sysLibCDlvallocHookHandler(CPUState* env, int isStart){

}

/**
 * FILE  *fopen(const char *, const char *)
 */
void sysLibCFopenHookHandler(CPUState* env, int isStart){
	DECAF_printf("fopen[%d]\n", isStart);
	if(isStart){
		char buf[128];
		buf[0] = '\0';
		if(DECAF_read_mem_until(env, env->regs[0], &buf, 128) > 0){
			DECAF_printf("fileName:%s\n", buf);
		}else{
			DECAF_read_mem_until(env, env->regs[0], &buf, 128);
			DECAF_printf("fileName:%s\n", buf);
		}

	}else{
		DECAF_printf("FILE@%x\n", env->regs[0]);
	}
}


void sysLibCMemccpyHookHandler(CPUState* env, int isStart){

}


void sysLibCPutenvHookHandler(CPUState* env, int isStart){

}


void sysLibCFdopenHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Key_CreateHookHandler(CPUState* env, int isStart){

}


void sysLibCRemovexattrHookHandler(CPUState* env, int isStart){

}


void sysLibCWcslenHookHandler(CPUState* env, int isStart){

}


void sysLibCDlindependent_ComallocHookHandler(CPUState* env, int isStart){

}


void sysLibCWcsncatHookHandler(CPUState* env, int isStart){

}


void sysLibCRmdirHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Mutexattr_DestroyHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Cond_TimedwaitHookHandler(CPUState* env, int isStart){

}


void sysLibCForkHookHandler(CPUState* env, int isStart){

}


void sysLibCMalloc_Debug_InitHookHandler(CPUState* env, int isStart){

}


void sysLibCStrtoimaxHookHandler(CPUState* env, int isStart){

}


void sysLibCAlphasortHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_SetschedparamHookHandler(CPUState* env, int isStart){

}


void sysLibCGetenvHookHandler(CPUState* env, int isStart){

}


void sysLibCAtoiHookHandler(CPUState* env, int isStart){

}


void sysLibCLinkHookHandler(CPUState* env, int isStart){

}


void sysLibCPtraceHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Mutex_UnlockHookHandler(CPUState* env, int isStart){

}


void sysLibCGethostbyname_RHookHandler(CPUState* env, int isStart){

}


void sysLibCStrdupHookHandler(CPUState* env, int isStart){

}


void sysLibCUnlockptHookHandler(CPUState* env, int isStart){

}


void sysLibCGetnetbynameHookHandler(CPUState* env, int isStart){

}


void sysLibCCpuacct_AddHookHandler(CPUState* env, int isStart){

}


void sysLibCErand48HookHandler(CPUState* env, int isStart){

}


void sysLibCSbrkHookHandler(CPUState* env, int isStart){

}


void sysLibCWait3HookHandler(CPUState* env, int isStart){

}


void sysLibCGetpwuid_RHookHandler(CPUState* env, int isStart){

}


void sysLibCSched_SetschedulerHookHandler(CPUState* env, int isStart){

}


void sysLibCFreeaddrinfoHookHandler(CPUState* env, int isStart){

}


void sysLibCStrspnHookHandler(CPUState* env, int isStart){

}


void sysLibCTimeHookHandler(CPUState* env, int isStart){

}


void sysLibCUngetcHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Rwlock_InitHookHandler(CPUState* env, int isStart){

}


void sysLibCSscanfHookHandler(CPUState* env, int isStart){

}


void sysLibCMktime64HookHandler(CPUState* env, int isStart){

}


void sysLibCCreatHookHandler(CPUState* env, int isStart){

}


void sysLibCStrndupHookHandler(CPUState* env, int isStart){

}


void sysLibCSyscallHookHandler(CPUState* env, int isStart){

}


void sysLibCFreadHookHandler(CPUState* env, int isStart){

}


void sysLibCFtelloHookHandler(CPUState* env, int isStart){

}


void sysLibCRemoveHookHandler(CPUState* env, int isStart){

}


void sysLibCInet_PtonHookHandler(CPUState* env, int isStart){

}


void sysLibCWctypeHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Mutexattr_SettypeHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Cond_DestroyHookHandler(CPUState* env, int isStart){

}


void sysLibCPread64HookHandler(CPUState* env, int isStart){

}


void sysLibCIsdigitHookHandler(CPUState* env, int isStart){

}


void sysLibCTimezoneHookHandler(CPUState* env, int isStart){

}


void sysLibCIspunctHookHandler(CPUState* env, int isStart){

}


void sysLibCFstatfsHookHandler(CPUState* env, int isStart){

}


void sysLibCFwscanfHookHandler(CPUState* env, int isStart){

}


void sysLibCMemmemHookHandler(CPUState* env, int isStart){

}


void sysLibCTmpnamHookHandler(CPUState* env, int isStart){

}


void sysLibCTkillHookHandler(CPUState* env, int isStart){

}


void sysLibCSetpriorityHookHandler(CPUState* env, int isStart){

}


void sysLibCGai_StrerrorHookHandler(CPUState* env, int isStart){

}


void sysLibCGetoptHookHandler(CPUState* env, int isStart){

}


void sysLibCMkstempHookHandler(CPUState* env, int isStart){

}


void sysLibCVfscanfHookHandler(CPUState* env, int isStart){

}


void sysLibCTdeleteHookHandler(CPUState* env, int isStart){

}


void sysLibCMincoreHookHandler(CPUState* env, int isStart){

}


void sysLibCNiceHookHandler(CPUState* env, int isStart){

}


void sysLibCSendfileHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Cond_Timedwait_MonotonicHookHandler(CPUState* env, int isStart){

}


void sysLibCStatHookHandler(CPUState* env, int isStart){

}


void sysLibCTruncateHookHandler(CPUState* env, int isStart){

}


void sysLibCKillpgHookHandler(CPUState* env, int isStart){

}


void sysLibCSigsuspendHookHandler(CPUState* env, int isStart){

}


void sysLibCRegerrorHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_Cond_BroadcastHookHandler(CPUState* env, int isStart){

}


void sysLibCClosedirHookHandler(CPUState* env, int isStart){

}


void sysLibCGetegidHookHandler(CPUState* env, int isStart){

}


void sysLibCWcsdupHookHandler(CPUState* env, int isStart){

}


void sysLibCRes_InitHookHandler(CPUState* env, int isStart){

}


void sysLibCFwprintfHookHandler(CPUState* env, int isStart){

}


void sysLibCSetlinebufHookHandler(CPUState* env, int isStart){

}


void sysLibCGetuidHookHandler(CPUState* env, int isStart){

}


void sysLibCFts_ReadHookHandler(CPUState* env, int isStart){

}


void sysLibCGetservent_RHookHandler(CPUState* env, int isStart){

}


void sysLibCDifftimeHookHandler(CPUState* env, int isStart){

}


void sysLibCRegfreeHookHandler(CPUState* env, int isStart){

}


void sysLibCWcscspnHookHandler(CPUState* env, int isStart){

}


void sysLibCMd5_InitHookHandler(CPUState* env, int isStart){

}


void sysLibCFpathconfHookHandler(CPUState* env, int isStart){

}


void sysLibCChownHookHandler(CPUState* env, int isStart){

}


void sysLibCH_NerrHookHandler(CPUState* env, int isStart){

}


void sysLibCReaddir_RHookHandler(CPUState* env, int isStart){

}


void sysLibCPthread_SelfHookHandler(CPUState* env, int isStart){

}


