/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-10-4
 */

#include "lib_c.h"

void sysLibCWcsftimeHookHandler(CPUState* env, int isBefore){

}


void sysLibCFreedtoaHookHandler(CPUState* env, int isBefore){

}

/**
 * int fclose(FILE *fp)
 */
void sysLibCFcloseHookHandler(CPUState* env, int isBefore){
	DECAF_printf("fclose[%d]\n", isBefore);
	if(isBefore){
		DECAF_printf("close FILE@%x\n", env->regs[0]);
	}
}


void sysLibCGetaddrinfoHookHandler(CPUState* env, int isBefore){

}


void sysLibCRebootHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Mutex_LockHookHandler(CPUState* env, int isBefore){

}


void sysLibCVwarnHookHandler(CPUState* env, int isBefore){

}


void sysLibCSleepHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Condattr_GetpsharedHookHandler(CPUState* env, int isBefore){

}


void sysLibCIsxdigitHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Cond_Timedwait_Relative_NpHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Key_DeleteHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcsncasecmpHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetresgidHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Attr_GetscopeHookHandler(CPUState* env, int isBefore){

}


void sysLibCSha1InitHookHandler(CPUState* env, int isBefore){

}


void sysLibCUmaskHookHandler(CPUState* env, int isBefore){

}


void sysLibCSched_GetaffinityHookHandler(CPUState* env, int isBefore){

}


void sysLibCSendHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcslcpyHookHandler(CPUState* env, int isBefore){

}


void sysLibCSched_SetparamHookHandler(CPUState* env, int isBefore){

}


void sysLibCMalloc_Debug_FiniHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetutentHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Setname_NpHookHandler(CPUState* env, int isBefore){

}


void sysLibCIsspaceHookHandler(CPUState* env, int isBefore){

}


void sysLibCLocaltimeHookHandler(CPUState* env, int isBefore){

}


void sysLibCVerrHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetptHookHandler(CPUState* env, int isBefore){

}


void sysLibCCtime_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetc_UnlockedHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetppidHookHandler(CPUState* env, int isBefore){

}


void sysLibCDlindependent_CallocHookHandler(CPUState* env, int isBefore){

}


void sysLibCUtmpnameHookHandler(CPUState* env, int isBefore){

}


void sysLibCSeteuidHookHandler(CPUState* env, int isBefore){

}


void sysLibCCapgetHookHandler(CPUState* env, int isBefore){

}


void sysLibCUtimeHookHandler(CPUState* env, int isBefore){

}


void sysLibCGettidHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Attr_SetstacksizeHookHandler(CPUState* env, int isBefore){

}


void sysLibCIssetugidHookHandler(CPUState* env, int isBefore){

}


void sysLibCTimegmHookHandler(CPUState* env, int isBefore){

}


void sysLibCDlpvallocHookHandler(CPUState* env, int isBefore){

}


void sysLibCTcsetpgrpHookHandler(CPUState* env, int isBefore){

}


void sysLibCFgetlnHookHandler(CPUState* env, int isBefore){

}


void sysLibCRecvfromHookHandler(CPUState* env, int isBefore){

}


void sysLibCSched_Get_Priority_MaxHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetmntentHookHandler(CPUState* env, int isBefore){

}


void sysLibCIswspaceHookHandler(CPUState* env, int isBefore){

}


void sysLibCDivHookHandler(CPUState* env, int isBefore){

}


void sysLibCIsblankHookHandler(CPUState* env, int isBefore){

}


void sysLibCTtynameHookHandler(CPUState* env, int isBefore){

}


void sysLibCKlogctlHookHandler(CPUState* env, int isBefore){

}


void sysLibCSnprintfHookHandler(CPUState* env, int isBefore){

}


void sysLibCOptindHookHandler(CPUState* env, int isBefore){

}


void sysLibCMemsetHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcschrHookHandler(CPUState* env, int isBefore){

}


void sysLibCSyncHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetgrouplistHookHandler(CPUState* env, int isBefore){

}


void sysLibCMknodHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrcasestrHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Mutex_DestroyHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcrtombHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrlcatHookHandler(CPUState* env, int isBefore){

}


void sysLibCLlistxattrHookHandler(CPUState* env, int isBefore){

}


void sysLibCMktempHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetchar_UnlockedHookHandler(CPUState* env, int isBefore){

}


void sysLibCClockHookHandler(CPUState* env, int isBefore){

}


void sysLibCAtexitHookHandler(CPUState* env, int isBefore){

}


void sysLibCOpenlogHookHandler(CPUState* env, int isBefore){

}


void sysLibCInotify_Add_WatchHookHandler(CPUState* env, int isBefore){

}


void sysLibCAccessHookHandler(CPUState* env, int isBefore){

}


void sysLibCBasename_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetlogmaskHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcstolHookHandler(CPUState* env, int isBefore){

}


void sysLibCMunmapHookHandler(CPUState* env, int isBefore){

}


void sysLibCSocketpairHookHandler(CPUState* env, int isBefore){

}


void sysLibCSettimeofdayHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetresuidHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_DetachHookHandler(CPUState* env, int isBefore){

}


void sysLibCFts_CloseHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Attr_SetdetachstateHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetpgidHookHandler(CPUState* env, int isBefore){

}


void sysLibCVwprintfHookHandler(CPUState* env, int isBefore){

}


void sysLibCLocaltime_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCTimelocal64HookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Attr_InitHookHandler(CPUState* env, int isBefore){

}


void sysLibCPauseHookHandler(CPUState* env, int isBefore){

}


void sysLibCTimer_SettimeHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetregidHookHandler(CPUState* env, int isBefore){

}


void sysLibCFchdirHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcpncpyHookHandler(CPUState* env, int isBefore){

}


void sysLibCFake_Localtime_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCWaitHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetdentsHookHandler(CPUState* env, int isBefore){

}


void sysLibCVerrxHookHandler(CPUState* env, int isBefore){

}


void sysLibCEventfdHookHandler(CPUState* env, int isBefore){

}


void sysLibCPipe2HookHandler(CPUState* env, int isBefore){

}


void sysLibCEther_Ntoa_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCPopenHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcsxfrmHookHandler(CPUState* env, int isBefore){

}


void sysLibCFputwcHookHandler(CPUState* env, int isBefore){

}


void sysLibCPerf_Event_OpenHookHandler(CPUState* env, int isBefore){

}


void sysLibCSendmsgHookHandler(CPUState* env, int isBefore){

}


void sysLibCIswalnumHookHandler(CPUState* env, int isBefore){

}


void sysLibCEpoll_CtlHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Mutexattr_GettypeHookHandler(CPUState* env, int isBefore){

}


void sysLibCBzeroHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcstokHookHandler(CPUState* env, int isBefore){

}


void sysLibCBrkHookHandler(CPUState* env, int isBefore){

}


void sysLibCSched_Rr_Get_IntervalHookHandler(CPUState* env, int isBefore){

}


void sysLibCPrintfHookHandler(CPUState* env, int isBefore){

}


void sysLibCFtokHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Mutex_InitHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcstodHookHandler(CPUState* env, int isBefore){

}


void sysLibCClock_SettimeHookHandler(CPUState* env, int isBefore){

}


void sysLibCSelectHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetcharHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_EqualHookHandler(CPUState* env, int isBefore){

}


void sysLibCCloselog_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetsockoptHookHandler(CPUState* env, int isBefore){

}


void sysLibCSha1UpdateHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetpriorityHookHandler(CPUState* env, int isBefore){

}


void sysLibCGhashtableHookHandler(CPUState* env, int isBefore){

}


void sysLibCFdatasyncHookHandler(CPUState* env, int isBefore){

}


void sysLibCSys_SignameHookHandler(CPUState* env, int isBefore){

}


void sysLibCIsattyHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcsncpyHookHandler(CPUState* env, int isBefore){

}


void sysLibCPathconfHookHandler(CPUState* env, int isBefore){

}


void sysLibCSched_GetschedulerHookHandler(CPUState* env, int isBefore){

}


void sysLibCWarnHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcscatHookHandler(CPUState* env, int isBefore){

}


void sysLibCGettimeofdayHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_SigmaskHookHandler(CPUState* env, int isBefore){

}


void sysLibCSem_OpenHookHandler(CPUState* env, int isBefore){

}


void sysLibCSocketHookHandler(CPUState* env, int isBefore){

}


void sysLibCChdirHookHandler(CPUState* env, int isBefore){

}


void sysLibCErrHookHandler(CPUState* env, int isBefore){

}


void sysLibCFtrylockfileHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrerrorHookHandler(CPUState* env, int isBefore){

}


void sysLibCIswlowerHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetuidHookHandler(CPUState* env, int isBefore){

}


void sysLibCSwprintfHookHandler(CPUState* env, int isBefore){

}


void sysLibCUtimensatHookHandler(CPUState* env, int isBefore){

}


void sysLibCInet_Nsap_NtoaHookHandler(CPUState* env, int isBefore){

}


void sysLibCFnmatchHookHandler(CPUState* env, int isBefore){

}


void sysLibCFtruncateHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetprotobynumberHookHandler(CPUState* env, int isBefore){

}


void sysLibCVforkHookHandler(CPUState* env, int isBefore){

}


void sysLibCSysconfHookHandler(CPUState* env, int isBefore){

}


void sysLibCWprintfHookHandler(CPUState* env, int isBefore){

}


void sysLibCMprotectHookHandler(CPUState* env, int isBefore){

}


void sysLibCSem_TrywaitHookHandler(CPUState* env, int isBefore){

}


void sysLibCAcceptHookHandler(CPUState* env, int isBefore){

}


void sysLibCAbortHookHandler(CPUState* env, int isBefore){

}

/**
 * int  fprintf(FILE *, const char *, ...)
 */
void sysLibCFprintfHookHandler(CPUState* env, int isBefore){
	DECAF_printf("fprintf[%d]\n", isBefore);
	if(isBefore){
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


void sysLibCStrtollHookHandler(CPUState* env, int isBefore){

}


void sysLibCTowupperHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrlenHookHandler(CPUState* env, int isBefore){

}


void sysLibCGet_Malloc_Leak_InfoHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrncatHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_GetspecificHookHandler(CPUState* env, int isBefore){

}


void sysLibCChrootHookHandler(CPUState* env, int isBefore){

}


void sysLibCClearerrHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetgroupsHookHandler(CPUState* env, int isBefore){

}


void sysLibCFeofHookHandler(CPUState* env, int isBefore){

}


void sysLibCLrand48HookHandler(CPUState* env, int isBefore){

}


void sysLibCStrntoumaxHookHandler(CPUState* env, int isBefore){

}


void sysLibCWriteHookHandler(CPUState* env, int isBefore){

}


void sysLibCVfprintfHookHandler(CPUState* env, int isBefore){

}


void sysLibCRewindHookHandler(CPUState* env, int isBefore){

}


void sysLibCWmemchrHookHandler(CPUState* env, int isBefore){

}


void sysLibCPutc_UnlockedHookHandler(CPUState* env, int isBefore){

}


void sysLibCVwarnxHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcsrchrHookHandler(CPUState* env, int isBefore){

}


void sysLibCFlockfileHookHandler(CPUState* env, int isBefore){

}


void sysLibCIf_IndextonameHookHandler(CPUState* env, int isBefore){

}


void sysLibCVasprintfHookHandler(CPUState* env, int isBefore){

}


void sysLibCMemrchrHookHandler(CPUState* env, int isBefore){

}


void sysLibCUnsetenvHookHandler(CPUState* env, int isBefore){

}


void sysLibCOpenatHookHandler(CPUState* env, int isBefore){

}


void sysLibCCloneHookHandler(CPUState* env, int isBefore){

}


void sysLibCSigsetmaskHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetxattrHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Condattr_SetpsharedHookHandler(CPUState* env, int isBefore){

}


void sysLibCIoctlHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Rwlock_WrlockHookHandler(CPUState* env, int isBefore){

}


void sysLibCVallocHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetgroupsHookHandler(CPUState* env, int isBefore){

}


void sysLibCUnlinkHookHandler(CPUState* env, int isBefore){

}


void sysLibCGmtime64_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCTcgetpgrpHookHandler(CPUState* env, int isBefore){

}


void sysLibCLongjmperrorHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrerror_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCBindHookHandler(CPUState* env, int isBefore){

}


void sysLibCLocaltime64_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Attr_SetschedpolicyHookHandler(CPUState* env, int isBefore){

}


void sysLibCIscntrlHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetpgrpHookHandler(CPUState* env, int isBefore){

}


void sysLibCRes_SearchHookHandler(CPUState* env, int isBefore){

}


void sysLibCEnvironHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Rwlock_TimedwrlockHookHandler(CPUState* env, int isBefore){

}


void sysLibCEndusershellHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetserventHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrntoimaxHookHandler(CPUState* env, int isBefore){

}


void sysLibCBasenameHookHandler(CPUState* env, int isBefore){

}


void sysLibCExecleHookHandler(CPUState* env, int isBefore){

}


void sysLibCFgetwcHookHandler(CPUState* env, int isBefore){

}


void sysLibCUnameHookHandler(CPUState* env, int isBefore){

}


void sysLibCBtowcHookHandler(CPUState* env, int isBefore){

}


void sysLibCMbrlenHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrtoulHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_KillHookHandler(CPUState* env, int isBefore){

}


void sysLibCExeclpHookHandler(CPUState* env, int isBefore){

}


void sysLibCSem_UnlinkHookHandler(CPUState* env, int isBefore){

}


void sysLibCEventfd_ReadHookHandler(CPUState* env, int isBefore){

}


void sysLibCReadaheadHookHandler(CPUState* env, int isBefore){

}


void sysLibCFwriteHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetpidHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetgidHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Mutexattr_SetpsharedHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrnlenHookHandler(CPUState* env, int isBefore){

}


void sysLibCSched_Get_Priority_MinHookHandler(CPUState* env, int isBefore){

}


void sysLibCFchownHookHandler(CPUState* env, int isBefore){

}


void sysLibCFts_SetHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetpwnamHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrcollHookHandler(CPUState* env, int isBefore){

}


void sysLibCRewinddirHookHandler(CPUState* env, int isBefore){

}


void sysLibCExeclHookHandler(CPUState* env, int isBefore){

}


void sysLibCInet_AddrHookHandler(CPUState* env, int isBefore){

}


void sysLibCEther_NtoaHookHandler(CPUState* env, int isBefore){

}


void sysLibCIswupperHookHandler(CPUState* env, int isBefore){

}


void sysLibCBindresvportHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetreuidHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Attr_GetschedparamHookHandler(CPUState* env, int isBefore){

}


void sysLibCSiglongjmpHookHandler(CPUState* env, int isBefore){

}


void sysLibCErrxHookHandler(CPUState* env, int isBefore){

}


void sysLibCSendtoHookHandler(CPUState* env, int isBefore){

}


void sysLibCExecvHookHandler(CPUState* env, int isBefore){

}


void sysLibCFts_ChildrenHookHandler(CPUState* env, int isBefore){

}


void sysLibCMemchrHookHandler(CPUState* env, int isBefore){

}


void sysLibCLgetxattrHookHandler(CPUState* env, int isBefore){

}


void sysLibCClock_GettimeHookHandler(CPUState* env, int isBefore){

}


void sysLibCVsscanfHookHandler(CPUState* env, int isBefore){

}


void sysLibCSys_SiglistHookHandler(CPUState* env, int isBefore){

}


void sysLibCSha1TransformHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Attr_SetstackHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Cond_SignalHookHandler(CPUState* env, int isBefore){

}


void sysLibCConnectHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_CreateHookHandler(CPUState* env, int isBefore){

}


void sysLibCFlockHookHandler(CPUState* env, int isBefore){

}


void sysLibCDirnameHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Mutexattr_InitHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrlcpyHookHandler(CPUState* env, int isBefore){

}


void sysLibCOpendirHookHandler(CPUState* env, int isBefore){

}


void sysLibCDlmalloc_Walk_Free_PagesHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetsidHookHandler(CPUState* env, int isBefore){

}


void sysLibCRestore_Core_RegsHookHandler(CPUState* env, int isBefore){

}


void sysLibCSprintfHookHandler(CPUState* env, int isBefore){

}


void sysLibCVscanfHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrrchrHookHandler(CPUState* env, int isBefore){

}


void sysLibCRegexecHookHandler(CPUState* env, int isBefore){

}


void sysLibCEventfd_WriteHookHandler(CPUState* env, int isBefore){

}


void sysLibCGethostbyaddrHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Rwlock_DestroyHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrcspnHookHandler(CPUState* env, int isBefore){

}


void sysLibCMd5_FinalHookHandler(CPUState* env, int isBefore){

}


void sysLibCAsprintfHookHandler(CPUState* env, int isBefore){

}


void sysLibCFerrorHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetcwdHookHandler(CPUState* env, int isBefore){

}


void sysLibCFreeHookHandler(CPUState* env, int isBefore){

}


void sysLibCFake_Gmtime_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCTfindHookHandler(CPUState* env, int isBefore){

}


void sysLibCAsctime_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetpeernameHookHandler(CPUState* env, int isBefore){

}


void sysLibCRecvHookHandler(CPUState* env, int isBefore){

}


void sysLibCFwideHookHandler(CPUState* env, int isBefore){

}


void sysLibCFseekoHookHandler(CPUState* env, int isBefore){

}


void sysLibCPutcharHookHandler(CPUState* env, int isBefore){

}


void sysLibCGethostbynameHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcsspnHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetprotobynameHookHandler(CPUState* env, int isBefore){

}


void sysLibCTimesHookHandler(CPUState* env, int isBefore){

}


void sysLibCCtime64HookHandler(CPUState* env, int isBefore){

}


void sysLibCSched_GetcpuHookHandler(CPUState* env, int isBefore){

}


void sysLibCPwrite64HookHandler(CPUState* env, int isBefore){

}


void sysLibCIslowerHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Attr_GetstackHookHandler(CPUState* env, int isBefore){

}


void sysLibCIsupperHookHandler(CPUState* env, int isBefore){

}


void sysLibCVsyslogHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetopt_LongHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetservbynameHookHandler(CPUState* env, int isBefore){

}


void sysLibCLocaltime64HookHandler(CPUState* env, int isBefore){

}


void sysLibCWarnxHookHandler(CPUState* env, int isBefore){

}


void sysLibCQsortHookHandler(CPUState* env, int isBefore){

}


void sysLibCSem_PostHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_JoinHookHandler(CPUState* env, int isBefore){

}


void sysLibCBcopyHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Attr_GetstacksizeHookHandler(CPUState* env, int isBefore){

}


void sysLibCLdexpHookHandler(CPUState* env, int isBefore){

}


void sysLibCNsdispatchHookHandler(CPUState* env, int isBefore){

}


void sysLibCFsetxattrHookHandler(CPUState* env, int isBefore){

}


void sysLibCRes_Get_Dns_ChangedHookHandler(CPUState* env, int isBefore){

}


void sysLibCAcctHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetservbyportHookHandler(CPUState* env, int isBefore){

}


void sysLibCOpenHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrncpyHookHandler(CPUState* env, int isBefore){

}


void sysLibCUsleepHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Mutex_Lock_Timeout_NpHookHandler(CPUState* env, int isBefore){

}


void sysLibCClock_NanosleepHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcsnlenHookHandler(CPUState* env, int isBefore){

}


void sysLibCIsalnumHookHandler(CPUState* env, int isBefore){

}


void sysLibCListxattrHookHandler(CPUState* env, int isBefore){

}


void sysLibCScanfHookHandler(CPUState* env, int isBefore){

}


void sysLibCMkdirHookHandler(CPUState* env, int isBefore){

}


void sysLibCSystemHookHandler(CPUState* env, int isBefore){

}


void sysLibCSigpendingHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrcasecmpHookHandler(CPUState* env, int isBefore){

}


void sysLibCFaccessatHookHandler(CPUState* env, int isBefore){

}


void sysLibCIsalphaHookHandler(CPUState* env, int isBefore){

}


void sysLibCMemcmpHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrftime_TzHookHandler(CPUState* env, int isBefore){

}


void sysLibCGmtime64HookHandler(CPUState* env, int isBefore){

}


void sysLibCGetpwnam_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCListenHookHandler(CPUState* env, int isBefore){

}


void sysLibCInotify_InitHookHandler(CPUState* env, int isBefore){

}


void sysLibCDlreallocHookHandler(CPUState* env, int isBefore){

}


void sysLibCMd5_UpdateHookHandler(CPUState* env, int isBefore){

}


void sysLibCDlmallocHookHandler(CPUState* env, int isBefore){

}


void sysLibCFgetxattrHookHandler(CPUState* env, int isBefore){

}


void sysLibCPwriteHookHandler(CPUState* env, int isBefore){

}


void sysLibCMlockHookHandler(CPUState* env, int isBefore){

}


void sysLibCIsasciiHookHandler(CPUState* env, int isBefore){

}


void sysLibCTimegm64HookHandler(CPUState* env, int isBefore){

}


void sysLibCSyslogHookHandler(CPUState* env, int isBefore){

}


void sysLibCStatfsHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcscmpHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcscpyHookHandler(CPUState* env, int isBefore){

}


void sysLibCVfdprintfHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetbufferHookHandler(CPUState* env, int isBefore){

}


void sysLibCTznameHookHandler(CPUState* env, int isBefore){

}


void sysLibCSigwaitHookHandler(CPUState* env, int isBefore){

}


void sysLibCSha1FinalHookHandler(CPUState* env, int isBefore){

}


void sysLibCGmtime_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCVsnprintfHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcstoulHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Attr_GetstackaddrHookHandler(CPUState* env, int isBefore){

}


void sysLibCMremapHookHandler(CPUState* env, int isBefore){

}


void sysLibCPselectHookHandler(CPUState* env, int isBefore){

}


void sysLibCEther_Aton_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_OnceHookHandler(CPUState* env, int isBefore){

}


void sysLibCVprintfHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_AtforkHookHandler(CPUState* env, int isBefore){

}


void sysLibCWmemcpyHookHandler(CPUState* env, int isBefore){

}


void sysLibCIswgraphHookHandler(CPUState* env, int isBefore){

}


void sysLibCJrand48HookHandler(CPUState* env, int isBefore){

}


void sysLibCGeteuidHookHandler(CPUState* env, int isBefore){

}


void sysLibCFseekHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrptimeHookHandler(CPUState* env, int isBefore){

}


void sysLibCDlmalloc_Usable_SizeHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetopt_Long_OnlyHookHandler(CPUState* env, int isBefore){

}


void sysLibCTsearchHookHandler(CPUState* env, int isBefore){

}


void sysLibCFunopenHookHandler(CPUState* env, int isBefore){

}


void sysLibCIswalphaHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetrlimitHookHandler(CPUState* env, int isBefore){

}


void sysLibCRealpathHookHandler(CPUState* env, int isBefore){

}


void sysLibCTimer_GetoverrunHookHandler(CPUState* env, int isBefore){

}


void sysLibCDlmallinfoHookHandler(CPUState* env, int isBefore){

}


void sysLibCTolowerHookHandler(CPUState* env, int isBefore){

}


void sysLibCSched_YieldHookHandler(CPUState* env, int isBefore){

}


void sysLibCWaitidHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetjmpHookHandler(CPUState* env, int isBefore){

}


void sysLibCIf_NametoindexHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrpbrkHookHandler(CPUState* env, int isBefore){

}


void sysLibCOpterrHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Cond_InitHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetserventHookHandler(CPUState* env, int isBefore){

}


void sysLibCOptresetHookHandler(CPUState* env, int isBefore){

}


void sysLibCSrand48HookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Rwlock_TryrdlockHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcswcsHookHandler(CPUState* env, int isBefore){

}


void sysLibCAlarmHookHandler(CPUState* env, int isBefore){

}


void sysLibCDlmalloc_Max_FootprintHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetutentHookHandler(CPUState* env, int isBefore){

}


void sysLibCFutexHookHandler(CPUState* env, int isBefore){

}


void sysLibCPipeHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcsstrHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Attr_GetdetachstateHookHandler(CPUState* env, int isBefore){

}


void sysLibCUtimesHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetvbufHookHandler(CPUState* env, int isBefore){

}


void sysLibCScandirHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrncasecmpHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Getattr_NpHookHandler(CPUState* env, int isBefore){

}


void sysLibCSem_WaitHookHandler(CPUState* env, int isBefore){

}


void sysLibCGallocationsmutexHookHandler(CPUState* env, int isBefore){

}


void sysLibCFreopenHookHandler(CPUState* env, int isBefore){

}


void sysLibCAsctime64_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCFpurgeHookHandler(CPUState* env, int isBefore){

}


void sysLibCPosix2TimeHookHandler(CPUState* env, int isBefore){

}


void sysLibCPutchar_UnlockedHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrtoullHookHandler(CPUState* env, int isBefore){

}


void sysLibCDirname_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCLseek64HookHandler(CPUState* env, int isBefore){

}


void sysLibCStrtolHookHandler(CPUState* env, int isBefore){

}


void sysLibCFputcHookHandler(CPUState* env, int isBefore){

}


void sysLibCMalloc_Double_Free_BacklogHookHandler(CPUState* env, int isBefore){

}


void sysLibCEpoll_CreateHookHandler(CPUState* env, int isBefore){

}


void sysLibCGmallocleakzygotechildHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrtokHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrtodHookHandler(CPUState* env, int isBefore){

}


void sysLibCMkstempsHookHandler(CPUState* env, int isBefore){

}


void sysLibCWritevHookHandler(CPUState* env, int isBefore){

}


void sysLibCFputsHookHandler(CPUState* env, int isBefore){

}


void sysLibCFchmodHookHandler(CPUState* env, int isBefore){

}


void sysLibCFtimeHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Mutex_TrylockHookHandler(CPUState* env, int isBefore){

}


void sysLibCEpoll_WaitHookHandler(CPUState* env, int isBefore){

}


void sysLibCFstatHookHandler(CPUState* env, int isBefore){

}


void sysLibCCapsetHookHandler(CPUState* env, int isBefore){

}


void sysLibCPersonalityHookHandler(CPUState* env, int isBefore){

}


void sysLibCWmemsetHookHandler(CPUState* env, int isBefore){

}


void sysLibCIswctypeHookHandler(CPUState* env, int isBefore){

}


void sysLibCDup2HookHandler(CPUState* env, int isBefore){

}


void sysLibCWcscollHookHandler(CPUState* env, int isBefore){

}


void sysLibCFfsHookHandler(CPUState* env, int isBefore){

}


void sysLibCInet_NtopHookHandler(CPUState* env, int isBefore){

}


void sysLibCIswxdigitHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcsncmpHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrsepHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetpgrpHookHandler(CPUState* env, int isBefore){

}


void sysLibCPtsname_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCInet_NtoaHookHandler(CPUState* env, int isBefore){

}


void sysLibCMemcpyHookHandler(CPUState* env, int isBefore){

}


void sysLibCFilenoHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Cond_Timeout_NpHookHandler(CPUState* env, int isBefore){

}


void sysLibCPerrorHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_GetschedparamHookHandler(CPUState* env, int isBefore){

}


void sysLibCFscanfHookHandler(CPUState* env, int isBefore){

}


void sysLibCUmountHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Cond_WaitHookHandler(CPUState* env, int isBefore){

}


void sysLibCEndutentHookHandler(CPUState* env, int isBefore){

}


void sysLibCSyslog_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCMkdiratHookHandler(CPUState* env, int isBefore){

}


void sysLibCFgetwsHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrncmpHookHandler(CPUState* env, int isBefore){

}


void sysLibCMkdtempHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrcatHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetlogmask_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCFchownatHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetsocknameHookHandler(CPUState* env, int isBefore){

}


void sysLibCHerrorHookHandler(CPUState* env, int isBefore){

}


void sysLibCCloseHookHandler(CPUState* env, int isBefore){

}


void sysLibCLsetxattrHookHandler(CPUState* env, int isBefore){

}


void sysLibCFsetposHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrchrHookHandler(CPUState* env, int isBefore){

}


void sysLibCLremovexattrHookHandler(CPUState* env, int isBefore){

}


void sysLibCArc4Random_AddrandomHookHandler(CPUState* env, int isBefore){

}


void sysLibCArc4Random_UniformHookHandler(CPUState* env, int isBefore){

}


void sysLibCGethostbyname2HookHandler(CPUState* env, int isBefore){

}


void sysLibCFgetposHookHandler(CPUState* env, int isBefore){

}


void sysLibCFunlockfileHookHandler(CPUState* env, int isBefore){

}


void sysLibCPosix_MemalignHookHandler(CPUState* env, int isBefore){

}


void sysLibCSigaltstackHookHandler(CPUState* env, int isBefore){

}


void sysLibCSem_CloseHookHandler(CPUState* env, int isBefore){

}


void sysLibCAtollHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Rwlock_TimedrdlockHookHandler(CPUState* env, int isBefore){

}


void sysLibCFcntlHookHandler(CPUState* env, int isBefore){

}


void sysLibCInet_Nsap_AddrHookHandler(CPUState* env, int isBefore){

}


void sysLibCArc4Random_StirHookHandler(CPUState* env, int isBefore){

}


void sysLibCOpenlog_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCMemalignHookHandler(CPUState* env, int isBefore){

}


void sysLibCLstatHookHandler(CPUState* env, int isBefore){

}


void sysLibCInit_ModuleHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetresgidHookHandler(CPUState* env, int isBefore){

}


void sysLibCTimelocalHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetdtablesizeHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Attr_SetguardsizeHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetsockoptHookHandler(CPUState* env, int isBefore){

}


void sysLibCFstatatHookHandler(CPUState* env, int isBefore){

}


void sysLibCInitgroupsHookHandler(CPUState* env, int isBefore){

}


void sysLibCRes_MkqueryHookHandler(CPUState* env, int isBefore){

}


void sysLibCSysv_SignalHookHandler(CPUState* env, int isBefore){

}


void sysLibCGethostentHookHandler(CPUState* env, int isBefore){

}


void sysLibCCloselogHookHandler(CPUState* env, int isBefore){

}


void sysLibCFree_Malloc_Leak_InfoHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrftimeHookHandler(CPUState* env, int isBefore){

}


void sysLibCMbsinitHookHandler(CPUState* env, int isBefore){

}


void sysLibCTzsetHookHandler(CPUState* env, int isBefore){

}


void sysLibCTime2PosixHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrxfrmHookHandler(CPUState* env, int isBefore){

}


void sysLibCChmodHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetxattrHookHandler(CPUState* env, int isBefore){

}


void sysLibCFdprintfHookHandler(CPUState* env, int isBefore){

}


void sysLibCShutdownHookHandler(CPUState* env, int isBefore){

}


void sysLibCPreadHookHandler(CPUState* env, int isBefore){

}


void sysLibCPollHookHandler(CPUState* env, int isBefore){

}


void sysLibCUngetwcHookHandler(CPUState* env, int isBefore){

}


void sysLibCPutwHookHandler(CPUState* env, int isBefore){

}


void sysLibCSigprocmaskHookHandler(CPUState* env, int isBefore){

}


void sysLibCRaiseHookHandler(CPUState* env, int isBefore){

}


void sysLibCPutsHookHandler(CPUState* env, int isBefore){

}


void sysLibCSigactionHookHandler(CPUState* env, int isBefore){

}


void sysLibCNanosleepHookHandler(CPUState* env, int isBefore){

}


void sysLibCPutcHookHandler(CPUState* env, int isBefore){

}


void sysLibCDupHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrtoumaxHookHandler(CPUState* env, int isBefore){

}


void sysLibCMbrtowcHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrsignalHookHandler(CPUState* env, int isBefore){

}


void sysLibCMktimeHookHandler(CPUState* env, int isBefore){

}


void sysLibCDlmalloc_StatsHookHandler(CPUState* env, int isBefore){

}


void sysLibCCtime64_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCExecvpHookHandler(CPUState* env, int isBefore){

}


void sysLibCMbsrtowcsHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrtok_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Attr_SetschedparamHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcswidthHookHandler(CPUState* env, int isBefore){

}


void sysLibCExecveHookHandler(CPUState* env, int isBefore){

}


void sysLibCFputwsHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Attr_SetstackaddrHookHandler(CPUState* env, int isBefore){

}


void sysLibCDrand48HookHandler(CPUState* env, int isBefore){

}


void sysLibCMadviseHookHandler(CPUState* env, int isBefore){

}


void sysLibCMountHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetrusageHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Attr_GetschedpolicyHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetgrnamHookHandler(CPUState* env, int isBefore){

}


void sysLibCIoprio_GetHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetpwuidHookHandler(CPUState* env, int isBefore){

}


void sysLibCVsprintfHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Rwlock_UnlockHookHandler(CPUState* env, int isBefore){

}


void sysLibCRenameHookHandler(CPUState* env, int isBefore){

}


void sysLibCMallocHookHandler(CPUState* env, int isBefore){

}


void sysLibCDlmemalignHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcwidthHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_GetcpuclockidHookHandler(CPUState* env, int isBefore){

}


void sysLibCReadvHookHandler(CPUState* env, int isBefore){

}


void sysLibCPrctlHookHandler(CPUState* env, int isBefore){

}


void sysLibCRes_QueryHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Attr_SetscopeHookHandler(CPUState* env, int isBefore){

}


void sysLibCDlmalloc_Walk_HeapHookHandler(CPUState* env, int isBefore){

}


void sysLibCSched_GetparamHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetcHookHandler(CPUState* env, int isBefore){

}


void sysLibCMunlockHookHandler(CPUState* env, int isBefore){

}


void sysLibCVsyslog_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCRecvmsgHookHandler(CPUState* env, int isBefore){

}


void sysLibCTowlowerHookHandler(CPUState* env, int isBefore){

}


void sysLibCDlmalloptHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetsHookHandler(CPUState* env, int isBefore){

}


void sysLibCWaitpidHookHandler(CPUState* env, int isBefore){

}


void sysLibCOptargHookHandler(CPUState* env, int isBefore){

}


void sysLibCTdestroyHookHandler(CPUState* env, int isBefore){

}


void sysLibCLongjmpHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetusershellHookHandler(CPUState* env, int isBefore){

}


void sysLibCAsctime64HookHandler(CPUState* env, int isBefore){

}


void sysLibCFdopendirHookHandler(CPUState* env, int isBefore){

}


void sysLibCIsgraphHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Rwlock_RdlockHookHandler(CPUState* env, int isBefore){

}


void sysLibCCallocHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetbufHookHandler(CPUState* env, int isBefore){

}


void sysLibCUnlinkatHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Attr_GetguardsizeHookHandler(CPUState* env, int isBefore){

}


void sysLibCIswprintHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetitimerHookHandler(CPUState* env, int isBefore){

}


void sysLibCClearenvHookHandler(CPUState* env, int isBefore){

}


void sysLibCSigblockHookHandler(CPUState* env, int isBefore){

}


void sysLibCNrand48HookHandler(CPUState* env, int isBefore){

}


void sysLibCDn_ExpandHookHandler(CPUState* env, int isBefore){

}


void sysLibCFts_OpenHookHandler(CPUState* env, int isBefore){

}


void sysLibCPutwcharHookHandler(CPUState* env, int isBefore){

}


void sysLibCLseekHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcpcpyHookHandler(CPUState* env, int isBefore){

}


void sysLibCMallinfoHookHandler(CPUState* env, int isBefore){

}


void sysLibCFlistxattrHookHandler(CPUState* env, int isBefore){

}


void sysLibCWmemcmpHookHandler(CPUState* env, int isBefore){

}


void sysLibCDlmalloc_TrimHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcslcatHookHandler(CPUState* env, int isBefore){

}


void sysLibCKillHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Condattr_DestroyHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Mutexattr_GetpsharedHookHandler(CPUState* env, int isBefore){

}


void sysLibCFflushHookHandler(CPUState* env, int isBefore){

}


void sysLibCClock_GetresHookHandler(CPUState* env, int isBefore){

}


void sysLibCSem_DestroyHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Attr_DestroyHookHandler(CPUState* env, int isBefore){

}


void sysLibCMmapHookHandler(CPUState* env, int isBefore){

}


void sysLibCTimer_DeleteHookHandler(CPUState* env, int isBefore){

}


void sysLibCPtsnameHookHandler(CPUState* env, int isBefore){

}


void sysLibCSem_InitHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetenvHookHandler(CPUState* env, int isBefore){

}


void sysLibCOptoptHookHandler(CPUState* env, int isBefore){

}


void sysLibCLchownHookHandler(CPUState* env, int isBefore){

}


void sysLibCReallocHookHandler(CPUState* env, int isBefore){

}


void sysLibCIoprio_SetHookHandler(CPUState* env, int isBefore){

}


void sysLibCH_ErrlistHookHandler(CPUState* env, int isBefore){

}


void sysLibCDelete_ModuleHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcspbrkHookHandler(CPUState* env, int isBefore){

}


void sysLibCReadHookHandler(CPUState* env, int isBefore){

}


void sysLibCIswcntrlHookHandler(CPUState* env, int isBefore){

}


void sysLibCToasciiHookHandler(CPUState* env, int isBefore){

}


void sysLibCHstrerrorHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetnetbyaddrHookHandler(CPUState* env, int isBefore){

}


void sysLibCCacheflushHookHandler(CPUState* env, int isBefore){

}


void sysLibCCtimeHookHandler(CPUState* env, int isBefore){

}


void sysLibCDaemonHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrstrHookHandler(CPUState* env, int isBefore){

}


void sysLibCRenameatHookHandler(CPUState* env, int isBefore){

}


void sysLibCFsyncHookHandler(CPUState* env, int isBefore){

}


void sysLibCMemmoveHookHandler(CPUState* env, int isBefore){

}


void sysLibCInet_AtonHookHandler(CPUState* env, int isBefore){

}


void sysLibCIswpunctHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetegidHookHandler(CPUState* env, int isBefore){

}


void sysLibCTimer_CreateHookHandler(CPUState* env, int isBefore){

}


void sysLibCBsd_SignalHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrcmpHookHandler(CPUState* env, int isBefore){

}


void sysLibCTempnamHookHandler(CPUState* env, int isBefore){

}


void sysLibCTmpfileHookHandler(CPUState* env, int isBefore){

}


void sysLibCRegcompHookHandler(CPUState* env, int isBefore){

}


void sysLibCLldivHookHandler(CPUState* env, int isBefore){

}


void sysLibCToupperHookHandler(CPUState* env, int isBefore){

}


void sysLibCFgetcHookHandler(CPUState* env, int isBefore){

}


void sysLibCPcloseHookHandler(CPUState* env, int isBefore){

}


void sysLibCMrand48HookHandler(CPUState* env, int isBefore){

}


void sysLibCFtruncate64HookHandler(CPUState* env, int isBefore){

}


void sysLibCReaddirHookHandler(CPUState* env, int isBefore){

}


void sysLibCSeed48HookHandler(CPUState* env, int isBefore){

}


void sysLibCGetresuidHookHandler(CPUState* env, int isBefore){

}


void sysLibCDaylightHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetloginHookHandler(CPUState* env, int isBefore){

}


void sysLibCDlcallocHookHandler(CPUState* env, int isBefore){

}


void sysLibCFgetsHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetgidHookHandler(CPUState* env, int isBefore){

}


void sysLibCSem_GetvalueHookHandler(CPUState* env, int isBefore){

}


void sysLibCTgkillHookHandler(CPUState* env, int isBefore){

}


void sysLibCSem_TimedwaitHookHandler(CPUState* env, int isBefore){

}


void sysLibCSched_SetaffinityHookHandler(CPUState* env, int isBefore){

}


void sysLibCArc4Random_BufHookHandler(CPUState* env, int isBefore){

}


void sysLibCFremovexattrHookHandler(CPUState* env, int isBefore){

}


void sysLibCFtellHookHandler(CPUState* env, int isBefore){

}


void sysLibCExitHookHandler(CPUState* env, int isBefore){

}


void sysLibCTtyname_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_SetspecificHookHandler(CPUState* env, int isBefore){

}


void sysLibCAsctimeHookHandler(CPUState* env, int isBefore){

}


void sysLibCInotify_Rm_WatchHookHandler(CPUState* env, int isBefore){

}


void sysLibCSigsetjmpHookHandler(CPUState* env, int isBefore){

}


void sysLibCMbstowcsHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetrlimitHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_ExitHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetitimerHookHandler(CPUState* env, int isBefore){

}


void sysLibCFchmodatHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Rwlock_TrywrlockHookHandler(CPUState* env, int isBefore){

}


void sysLibCGmtimeHookHandler(CPUState* env, int isBefore){

}


void sysLibCSymlinkHookHandler(CPUState* env, int isBefore){

}


void sysLibCPututlineHookHandler(CPUState* env, int isBefore){

}


void sysLibCDirfdHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetgrgidHookHandler(CPUState* env, int isBefore){

}


void sysLibCTimer_GettimeHookHandler(CPUState* env, int isBefore){

}


void sysLibCGethostnameHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetnameinfoHookHandler(CPUState* env, int isBefore){

}


void sysLibCSysinfoHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrtotimevalHookHandler(CPUState* env, int isBefore){

}


void sysLibCMsyncHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetusershellHookHandler(CPUState* env, int isBefore){

}


void sysLibCMemswapHookHandler(CPUState* env, int isBefore){

}


void sysLibCSiginterruptHookHandler(CPUState* env, int isBefore){

}


void sysLibCIswdigitHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrcpyHookHandler(CPUState* env, int isBefore){

}


void sysLibCBsearchHookHandler(CPUState* env, int isBefore){

}


void sysLibCReadlinkHookHandler(CPUState* env, int isBefore){

}


void sysLibCDlmalloc_FootprintHookHandler(CPUState* env, int isBefore){

}


void sysLibCWmemmoveHookHandler(CPUState* env, int isBefore){

}


void sysLibCEther_AtonHookHandler(CPUState* env, int isBefore){

}


void sysLibCArc4RandomHookHandler(CPUState* env, int isBefore){

}


void sysLibCDlfreeHookHandler(CPUState* env, int isBefore){

}


void sysLibCUmount2HookHandler(CPUState* env, int isBefore){

}


void sysLibCWcscasecmpHookHandler(CPUState* env, int isBefore){

}


void sysLibCIsprintHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetpgidHookHandler(CPUState* env, int isBefore){

}


void sysLibCDlvallocHookHandler(CPUState* env, int isBefore){

}

/**
 * FILE  *fopen(const char *, const char *)
 */
void sysLibCFopenHookHandler(CPUState* env, int isBefore){
	DECAF_printf("fopen[%d]\n", isBefore);
	if(isBefore){
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


void sysLibCMemccpyHookHandler(CPUState* env, int isBefore){

}


void sysLibCPutenvHookHandler(CPUState* env, int isBefore){

}


void sysLibCFdopenHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Key_CreateHookHandler(CPUState* env, int isBefore){

}


void sysLibCRemovexattrHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcslenHookHandler(CPUState* env, int isBefore){

}


void sysLibCDlindependent_ComallocHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcsncatHookHandler(CPUState* env, int isBefore){

}


void sysLibCRmdirHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Mutexattr_DestroyHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Cond_TimedwaitHookHandler(CPUState* env, int isBefore){

}


void sysLibCForkHookHandler(CPUState* env, int isBefore){

}


void sysLibCMalloc_Debug_InitHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrtoimaxHookHandler(CPUState* env, int isBefore){

}


void sysLibCAlphasortHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_SetschedparamHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetenvHookHandler(CPUState* env, int isBefore){

}


void sysLibCAtoiHookHandler(CPUState* env, int isBefore){

}


void sysLibCLinkHookHandler(CPUState* env, int isBefore){

}


void sysLibCPtraceHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Mutex_UnlockHookHandler(CPUState* env, int isBefore){

}


void sysLibCGethostbyname_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrdupHookHandler(CPUState* env, int isBefore){

}


void sysLibCUnlockptHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetnetbynameHookHandler(CPUState* env, int isBefore){

}


void sysLibCCpuacct_AddHookHandler(CPUState* env, int isBefore){

}


void sysLibCErand48HookHandler(CPUState* env, int isBefore){

}


void sysLibCSbrkHookHandler(CPUState* env, int isBefore){

}


void sysLibCWait3HookHandler(CPUState* env, int isBefore){

}


void sysLibCGetpwuid_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCSched_SetschedulerHookHandler(CPUState* env, int isBefore){

}


void sysLibCFreeaddrinfoHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrspnHookHandler(CPUState* env, int isBefore){

}


void sysLibCTimeHookHandler(CPUState* env, int isBefore){

}


void sysLibCUngetcHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Rwlock_InitHookHandler(CPUState* env, int isBefore){

}


void sysLibCSscanfHookHandler(CPUState* env, int isBefore){

}


void sysLibCMktime64HookHandler(CPUState* env, int isBefore){

}


void sysLibCCreatHookHandler(CPUState* env, int isBefore){

}


void sysLibCStrndupHookHandler(CPUState* env, int isBefore){

}


void sysLibCSyscallHookHandler(CPUState* env, int isBefore){

}


void sysLibCFreadHookHandler(CPUState* env, int isBefore){

}


void sysLibCFtelloHookHandler(CPUState* env, int isBefore){

}


void sysLibCRemoveHookHandler(CPUState* env, int isBefore){

}


void sysLibCInet_PtonHookHandler(CPUState* env, int isBefore){

}


void sysLibCWctypeHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Mutexattr_SettypeHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Cond_DestroyHookHandler(CPUState* env, int isBefore){

}


void sysLibCPread64HookHandler(CPUState* env, int isBefore){

}


void sysLibCIsdigitHookHandler(CPUState* env, int isBefore){

}


void sysLibCTimezoneHookHandler(CPUState* env, int isBefore){

}


void sysLibCIspunctHookHandler(CPUState* env, int isBefore){

}


void sysLibCFstatfsHookHandler(CPUState* env, int isBefore){

}


void sysLibCFwscanfHookHandler(CPUState* env, int isBefore){

}


void sysLibCMemmemHookHandler(CPUState* env, int isBefore){

}


void sysLibCTmpnamHookHandler(CPUState* env, int isBefore){

}


void sysLibCTkillHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetpriorityHookHandler(CPUState* env, int isBefore){

}


void sysLibCGai_StrerrorHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetoptHookHandler(CPUState* env, int isBefore){

}


void sysLibCMkstempHookHandler(CPUState* env, int isBefore){

}


void sysLibCVfscanfHookHandler(CPUState* env, int isBefore){

}


void sysLibCTdeleteHookHandler(CPUState* env, int isBefore){

}


void sysLibCMincoreHookHandler(CPUState* env, int isBefore){

}


void sysLibCNiceHookHandler(CPUState* env, int isBefore){

}


void sysLibCSendfileHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Cond_Timedwait_MonotonicHookHandler(CPUState* env, int isBefore){

}


void sysLibCStatHookHandler(CPUState* env, int isBefore){

}


void sysLibCTruncateHookHandler(CPUState* env, int isBefore){

}


void sysLibCKillpgHookHandler(CPUState* env, int isBefore){

}


void sysLibCSigsuspendHookHandler(CPUState* env, int isBefore){

}


void sysLibCRegerrorHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_Cond_BroadcastHookHandler(CPUState* env, int isBefore){

}


void sysLibCClosedirHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetegidHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcsdupHookHandler(CPUState* env, int isBefore){

}


void sysLibCRes_InitHookHandler(CPUState* env, int isBefore){

}


void sysLibCFwprintfHookHandler(CPUState* env, int isBefore){

}


void sysLibCSetlinebufHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetuidHookHandler(CPUState* env, int isBefore){

}


void sysLibCFts_ReadHookHandler(CPUState* env, int isBefore){

}


void sysLibCGetservent_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCDifftimeHookHandler(CPUState* env, int isBefore){

}


void sysLibCRegfreeHookHandler(CPUState* env, int isBefore){

}


void sysLibCWcscspnHookHandler(CPUState* env, int isBefore){

}


void sysLibCMd5_InitHookHandler(CPUState* env, int isBefore){

}


void sysLibCFpathconfHookHandler(CPUState* env, int isBefore){

}


void sysLibCChownHookHandler(CPUState* env, int isBefore){

}


void sysLibCH_NerrHookHandler(CPUState* env, int isBefore){

}


void sysLibCReaddir_RHookHandler(CPUState* env, int isBefore){

}


void sysLibCPthread_SelfHookHandler(CPUState* env, int isBefore){

}


