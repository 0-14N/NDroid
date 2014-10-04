
#ifndef _LIB_C_HOOK_H
#define _LIB_C_HOOK_H
#ifdef __cplusplus

extern "C"
{
#endif
        
#include "sys_lib_hook.h"

#define WCSFTIME_OFFSET_C 0x22794
#define FREEDTOA_OFFSET_C 0x21128
#define FCLOSE_OFFSET_C 0x1aa64
#define GETADDRINFO_OFFSET_C 0x32a74
#define REBOOT_OFFSET_C 0x1a0a0
#define PTHREAD_MUTEX_LOCK_OFFSET_C 0x12284
#define VWARN_OFFSET_C 0x27068
#define SLEEP_OFFSET_C 0x1a27c
#define PTHREAD_CONDATTR_GETPSHARED_OFFSET_C 0x12a10
#define ISXDIGIT_OFFSET_C 0x1f4c0
#define PTHREAD_COND_TIMEDWAIT_RELATIVE_NP_OFFSET_C 0x12f88
#define PTHREAD_KEY_DELETE_OFFSET_C 0x130a4
#define WCSNCASECMP_OFFSET_C 0x22fb2
#define GETRESGID_OFFSET_C 0xc600
#define PTHREAD_ATTR_GETSCOPE_OFFSET_C 0x11e58
#define SHA1INIT_OFFSET_C 0x2a670
#define UMASK_OFFSET_C 0xd8f0
#define SCHED_GETAFFINITY_OFFSET_C 0x29164
#define SEND_OFFSET_C 0x1a10c
#define WCSLCPY_OFFSET_C 0x22f60
#define SCHED_SETPARAM_OFFSET_C 0xd794
#define MALLOC_DEBUG_FINI_OFFSET_C 0x16fc8
#define SETUTENT_OFFSET_C 0x2be08
#define PTHREAD_SETNAME_NP_OFFSET_C 0x13420
#define ISSPACE_OFFSET_C 0x1f480
#define LOCALTIME_OFFSET_C 0x25620
#define VERR_OFFSET_C 0x26f84
#define GETPT_OFFSET_C 0x197c4
#define CTIME_R_OFFSET_C 0x25666
#define GETC_UNLOCKED_OFFSET_C 0x1bc88
#define GETPPID_OFFSET_C 0xc694
#define DLINDEPENDENT_CALLOC_OFFSET_C 0x16374
#define UTMPNAME_OFFSET_C 0x2be84
#define SETEUID_OFFSET_C 0x1a138
#define CAPGET_OFFSET_C 0xc8b0
#define UTIME_OFFSET_C 0x2bdec
#define GETTID_OFFSET_C 0xc61c
#define PTHREAD_ATTR_SETSTACKSIZE_OFFSET_C 0x11d3c
#define ISSETUGID_OFFSET_C 0x19868
#define TIMEGM_OFFSET_C 0x256ac
#define DLPVALLOC_OFFSET_C 0x163ac
#define TCSETPGRP_OFFSET_C 0x1a864
#define FGETLN_OFFSET_C 0x1acc0
#define RECVFROM_OFFSET_C 0xd670
#define SCHED_GET_PRIORITY_MAX_OFFSET_C 0xd7cc
#define GETMNTENT_OFFSET_C 0x2ad74
#define ISWSPACE_OFFSET_C 0x224e4
#define DIV_OFFSET_C 0x1f506
#define ISBLANK_OFFSET_C 0x1f4e0
#define TTYNAME_OFFSET_C 0x2ada0
#define KLOGCTL_OFFSET_C 0xd928
#define SNPRINTF_OFFSET_C 0x1c5ac
#define OPTIND_OFFSET_C 0x44628
#define MEMSET_OFFSET_C 0xe498
#define WCSCHR_OFFSET_C 0x22e8c
#define SYNC_OFFSET_C 0xcd40
#define GETGROUPLIST_OFFSET_C 0x2ac2a
#define MKNOD_OFFSET_C 0xcf44
#define STRCASESTR_OFFSET_C 0x229c8
#define PTHREAD_MUTEX_DESTROY_OFFSET_C 0x129f0
#define WCRTOMB_OFFSET_C 0x2278a
#define STRLCAT_OFFSET_C 0x22b58
#define LLISTXATTR_OFFSET_C 0xd200
#define MKTEMP_OFFSET_C 0x1c0b0
#define GETCHAR_UNLOCKED_OFFSET_C 0x1bce4
#define CLOCK_OFFSET_C 0x1a8e0
#define ATEXIT_OFFSET_C 0x1f17c
#define OPENLOG_OFFSET_C 0x1a390
#define INOTIFY_ADD_WATCH_OFFSET_C 0xda6c
#define ACCESS_OFFSET_C 0xd0d4
#define BASENAME_R_OFFSET_C 0x26d44
#define SETLOGMASK_OFFSET_C 0x1a358
#define WCSTOL_OFFSET_C 0x2279c
#define MUNMAP_OFFSET_C 0xca78
#define SOCKETPAIR_OFFSET_C 0xd570
#define SETTIMEOFDAY_OFFSET_C 0xd2ac
#define SETRESUID_OFFSET_C 0x1a168
#define PTHREAD_DETACH_OFFSET_C 0x12374
#define FTS_CLOSE_OFFSET_C 0x27a2c
#define PTHREAD_ATTR_SETDETACHSTATE_OFFSET_C 0x11cb0
#define SETPGID_OFFSET_C 0xc81c
#define VWPRINTF_OFFSET_C 0x223ce
#define LOCALTIME_R_OFFSET_C 0x255fe
#define TIMELOCAL64_OFFSET_C 0x2b818
#define PTHREAD_ATTR_INIT_OFFSET_C 0x11c68
#define PAUSE_OFFSET_C 0xd274
#define TIMER_SETTIME_OFFSET_C 0x18078
#define SETREGID_OFFSET_C 0xc854
#define FCHDIR_OFFSET_C 0xd12c
#define WCPNCPY_OFFSET_C 0x22e16
#define FAKE_LOCALTIME_R_OFFSET_C 0x2b5fc
#define WAIT_OFFSET_C 0x1a988
#define GETDENTS_OFFSET_C 0xccd0
#define VERRX_OFFSET_C 0x27008
#define EVENTFD_OFFSET_C 0xdac8
#define PIPE2_OFFSET_C 0xcc38
#define ETHER_NTOA_R_OFFSET_C 0x23a28
#define POPEN_OFFSET_C 0x19d80
#define WCSXFRM_OFFSET_C 0x23196
#define FPUTWC_OFFSET_C 0x2268c
#define PERF_EVENT_OPEN_OFFSET_C 0xd9b4
#define SENDMSG_OFFSET_C 0xd704
#define ISWALNUM_OFFSET_C 0x223f8
#define EPOLL_CTL_OFFSET_C 0xda18
#define PTHREAD_MUTEXATTR_GETTYPE_OFFSET_C 0x11f9c
#define BZERO_OFFSET_C 0xe490
#define WCSTOK_OFFSET_C 0x23116
#define BRK_OFFSET_C 0x18328
#define SCHED_RR_GET_INTERVAL_OFFSET_C 0xd804
#define PRINTF_OFFSET_C 0x1c0b4
#define FTOK_OFFSET_C 0x18e26
#define PTHREAD_MUTEX_INIT_OFFSET_C 0x12078
#define WCSTOD_OFFSET_C 0x22798
#define CLOCK_SETTIME_OFFSET_C 0xd320
#define SELECT_OFFSET_C 0xcc74
#define GETCHAR_OFFSET_C 0x1bd08
#define PTHREAD_EQUAL_OFFSET_C 0x11eb0
#define CLOSELOG_R_OFFSET_C 0x1a39c
#define GETSOCKOPT_OFFSET_C 0xd6dc
#define SHA1UPDATE_OFFSET_C 0x2a69c
#define GETPRIORITY_OFFSET_C 0x197b4
#define GHASHTABLE_OFFSET_C 0x47b6c
#define FDATASYNC_OFFSET_C 0xcd08
#define SYS_SIGNAME_OFFSET_C 0x430a0
#define ISATTY_OFFSET_C 0x19834
#define WCSNCPY_OFFSET_C 0x23044
#define PATHCONF_OFFSET_C 0x19b98
#define SCHED_GETSCHEDULER_OFFSET_C 0xd75c
#define WARN_OFFSET_C 0x270d4
#define WCSCAT_OFFSET_C 0x22e70
#define GETTIMEOFDAY_OFFSET_C 0xd290
#define PTHREAD_SIGMASK_OFFSET_C 0x132f0
#define SEM_OPEN_OFFSET_C 0x29294
#define SOCKET_OFFSET_C 0xd550
#define CHDIR_OFFSET_C 0xcf28
#define ERR_OFFSET_C 0x26ff8
#define FTRYLOCKFILE_OFFSET_C 0x1b0ca
#define STRERROR_OFFSET_C 0x22a80
#define ISWLOWER_OFFSET_C 0x22484
#define SETUID_OFFSET_C 0x1a126
#define SWPRINTF_OFFSET_C 0x223b2
#define UTIMENSAT_OFFSET_C 0xd470
#define INET_NSAP_NTOA_OFFSET_C 0x2d25c
#define FNMATCH_OFFSET_C 0x18b2c
#define FTRUNCATE_OFFSET_C 0xcc98
#define GETPROTOBYNUMBER_OFFSET_C 0x2ae60
#define VFORK_OFFSET_C 0xc838
#define SYSCONF_OFFSET_C 0x137a8
#define WPRINTF_OFFSET_C 0x22396
#define MPROTECT_OFFSET_C 0xcacc
#define SEM_TRYWAIT_OFFSET_C 0x29444
#define ACCEPT_OFFSET_C 0xd5e8
#define ABORT_OFFSET_C 0xdbd0
#define FPRINTF_OFFSET_C 0x1b164
#define STRTOLL_OFFSET_C 0x22024
#define TOWUPPER_OFFSET_C 0x2276c
#define STRLEN_OFFSET_C 0x170d4
#define GET_MALLOC_LEAK_INFO_OFFSET_C 0x16dc0
#define STRNCAT_OFFSET_C 0x22bd0
#define PTHREAD_GETSPECIFIC_OFFSET_C 0x13280
#define CHROOT_OFFSET_C 0xc870
#define CLEARERR_OFFSET_C 0x1aa34
#define GETGROUPS_OFFSET_C 0xc65c
#define FEOF_OFFSET_C 0x1ab8c
#define LRAND48_OFFSET_C 0x1f644
#define STRNTOUMAX_OFFSET_C 0x1fbe4
#define WRITE_OFFSET_C 0xc93c
#define VFPRINTF_OFFSET_C 0x1e490
#define REWIND_OFFSET_C 0x1c3b8
#define WMEMCHR_OFFSET_C 0x231da
#define PUTC_UNLOCKED_OFFSET_C 0x1c0d8
#define VWARNX_OFFSET_C 0x270ec
#define WCSRCHR_OFFSET_C 0x230a0
#define FLOCKFILE_OFFSET_C 0x1b0be
#define IF_INDEXTONAME_OFFSET_C 0x27ebc
#define VASPRINTF_OFFSET_C 0x1ca9c
#define MEMRCHR_OFFSET_C 0x22908
#define UNSETENV_OFFSET_C 0x1fb5c
#define OPENAT_OFFSET_C 0x1992c
#define CLONE_OFFSET_C 0x3995c
#define SIGSETMASK_OFFSET_C 0x1a21a
#define GETXATTR_OFFSET_C 0xd1ac
#define PTHREAD_CONDATTR_SETPSHARED_OFFSET_C 0x12a34
#define IOCTL_OFFSET_C 0x27f3c
#define PTHREAD_RWLOCK_WRLOCK_OFFSET_C 0x17720
#define VALLOC_OFFSET_C 0x16f80
#define SETGROUPS_OFFSET_C 0xc800
#define UNLINK_OFFSET_C 0xcef0
#define GMTIME64_R_OFFSET_C 0x2b820
#define TCGETPGRP_OFFSET_C 0x1a84c
#define LONGJMPERROR_OFFSET_C 0x1fb8c
#define STRERROR_R_OFFSET_C 0x22a98
#define BIND_OFFSET_C 0xd58c
#define LOCALTIME64_R_OFFSET_C 0x2bbc8
#define PTHREAD_ATTR_SETSCHEDPOLICY_OFFSET_C 0x11d00
#define ISCNTRL_OFFSET_C 0x1f3c0
#define SETPGRP_OFFSET_C 0x1a184
#define RES_SEARCH_OFFSET_C 0x2d6c4
#define ENVIRON_OFFSET_C 0x493a0
#define PTHREAD_RWLOCK_TIMEDWRLOCK_OFFSET_C 0x17664
#define ENDUSERSHELL_OFFSET_C 0x2aefc
#define GETSERVENT_OFFSET_C 0x339f0
#define STRNTOIMAX_OFFSET_C 0x1fbe0
#define BASENAME_OFFSET_C 0x26d08
#define EXECLE_OFFSET_C 0x18494
#define FGETWC_OFFSET_C 0x22684
#define UNAME_OFFSET_C 0xd8b8
#define BTOWC_OFFSET_C 0x22378
#define MBRLEN_OFFSET_C 0x2269e
#define STRTOUL_OFFSET_C 0x22028
#define PTHREAD_KILL_OFFSET_C 0x132a4
#define EXECLP_OFFSET_C 0x1872c
#define SEM_UNLINK_OFFSET_C 0x292c4
#define EVENTFD_READ_OFFSET_C 0x183e0
#define READAHEAD_OFFSET_C 0xc638
#define FWRITE_OFFSET_C 0x1bc20
#define GETPID_OFFSET_C 0xca38
#define SETGID_OFFSET_C 0xc6cc
#define PTHREAD_MUTEXATTR_SETPSHARED_OFFSET_C 0x12004
#define STRNLEN_OFFSET_C 0x22c4a
#define SCHED_GET_PRIORITY_MIN_OFFSET_C 0xd7e8
#define FCHOWN_OFFSET_C 0xcd24
#define FTS_SET_OFFSET_C 0x27d68
#define GETPWNAM_OFFSET_C 0x2aa80
#define STRCOLL_OFFSET_C 0x22a3c
#define REWINDDIR_OFFSET_C 0x19ab4
#define EXECL_OFFSET_C 0x18410
#define INET_ADDR_OFFSET_C 0x2331c
#define ETHER_NTOA_OFFSET_C 0x23a5c
#define ISWUPPER_OFFSET_C 0x22504
#define BINDRESVPORT_OFFSET_C 0x23244
#define SETREUID_OFFSET_C 0x1a150
#define PTHREAD_ATTR_GETSCHEDPARAM_OFFSET_C 0x11d2c
#define SIGLONGJMP_OFFSET_C 0xe624
#define ERRX_OFFSET_C 0x27058
#define SENDTO_OFFSET_C 0xd648
#define EXECV_OFFSET_C 0x18510
#define FTS_CHILDREN_OFFSET_C 0x27d80
#define MEMCHR_OFFSET_C 0x22826
#define LGETXATTR_OFFSET_C 0xd1c8
#define CLOCK_GETTIME_OFFSET_C 0xd300
#define VSSCANF_OFFSET_C 0x1ee78
#define SYS_SIGLIST_OFFSET_C 0x43020
#define SHA1TRANSFORM_OFFSET_C 0x294a0
#define PTHREAD_ATTR_SETSTACK_OFFSET_C 0x11d90
#define PTHREAD_COND_SIGNAL_OFFSET_C 0x12dbc
#define CONNECT_OFFSET_C 0xd5ac
#define PTHREAD_CREATE_OFFSET_C 0x12468
#define FLOCK_OFFSET_C 0xcbc8
#define DIRNAME_OFFSET_C 0x26e08
#define PTHREAD_MUTEXATTR_INIT_OFFSET_C 0x11f70
#define STRLCPY_OFFSET_C 0x22b9c
#define OPENDIR_OFFSET_C 0x199a4
#define DLMALLOC_WALK_FREE_PAGES_OFFSET_C 0x166e0
#define SETSID_OFFSET_C 0xc6b0
#define RESTORE_CORE_REGS_OFFSET_C 0x10ba8
#define SPRINTF_OFFSET_C 0x1c608
#define VSCANF_OFFSET_C 0x1ee60
#define STRRCHR_OFFSET_C 0x22c84
#define REGEXEC_OFFSET_C 0x3902c
#define EVENTFD_WRITE_OFFSET_C 0x183f4
#define GETHOSTBYADDR_OFFSET_C 0x2ce84
#define PTHREAD_RWLOCK_DESTROY_OFFSET_C 0x17498
#define STRCSPN_OFFSET_C 0x22a40
#define MD5_FINAL_OFFSET_C 0x28be4
#define ASPRINTF_OFFSET_C 0x1a9c0
#define FERROR_OFFSET_C 0x1abb8
#define GETCWD_OFFSET_C 0x18e50
#define FREE_OFFSET_C 0x16f30
#define FAKE_GMTIME_R_OFFSET_C 0x2b61e
#define TFIND_OFFSET_C 0x2bd66
#define ASCTIME_R_OFFSET_C 0x23a68
#define GETPEERNAME_OFFSET_C 0xd628
#define RECV_OFFSET_C 0x1a0b4
#define FWIDE_OFFSET_C 0x22696
#define FSEEKO_OFFSET_C 0x1b5f8
#define PUTCHAR_OFFSET_C 0x1c19c
#define GETHOSTBYNAME_OFFSET_C 0x2cdf4
#define WCSSPN_OFFSET_C 0x230b8
#define GETPROTOBYNAME_OFFSET_C 0x2ae2c
#define TIMES_OFFSET_C 0xd2c8
#define CTIME64_OFFSET_C 0x2bd58
#define SCHED_GETCPU_OFFSET_C 0x29188
#define PWRITE64_OFFSET_C 0xc97c
#define ISLOWER_OFFSET_C 0x1f420
#define PTHREAD_ATTR_GETSTACK_OFFSET_C 0x11dc8
#define ISUPPER_OFFSET_C 0x1f4a0
#define VSYSLOG_OFFSET_C 0x1a748
#define GETOPT_LONG_OFFSET_C 0x1978e
#define GETSERVBYNAME_OFFSET_C 0x33894
#define LOCALTIME64_OFFSET_C 0x2bd34
#define WARNX_OFFSET_C 0x27134
#define QSORT_OFFSET_C 0x1f742
#define SEM_POST_OFFSET_C 0x293d8
#define PTHREAD_JOIN_OFFSET_C 0x12e7c
#define BCOPY_OFFSET_C 0x39b6e
#define PTHREAD_ATTR_GETSTACKSIZE_OFFSET_C 0x11d60
#define LDEXP_OFFSET_C 0x27f58
#define NSDISPATCH_OFFSET_C 0x31a48
#define FSETXATTR_OFFSET_C 0xce5c
#define RES_GET_DNS_CHANGED_OFFSET_C 0x2f3ec
#define ACCT_OFFSET_C 0xc904
#define GETSERVBYPORT_OFFSET_C 0x33c44
#define OPEN_OFFSET_C 0x19908
#define STRNCPY_OFFSET_C 0x22bf8
#define USLEEP_OFFSET_C 0x1a950
#define PTHREAD_MUTEX_LOCK_TIMEOUT_NP_OFFSET_C 0x129ec
#define CLOCK_NANOSLEEP_OFFSET_C 0xd35c
#define WCSNLEN_OFFSET_C 0x2306a
#define ISALNUM_OFFSET_C 0x1f380
#define LISTXATTR_OFFSET_C 0xd1e4
#define SCANF_OFFSET_C 0x1c40c
#define MKDIR_OFFSET_C 0xd048
#define SYSTEM_OFFSET_C 0x1a790
#define SIGPENDING_OFFSET_C 0xd534
#define STRCASECMP_OFFSET_C 0x22970
#define FACCESSAT_OFFSET_C 0xd0f0
#define ISALPHA_OFFSET_C 0x1f3a0
#define MEMCMP_OFFSET_C 0xdd10
#define STRFTIME_TZ_OFFSET_C 0x263c8
#define GMTIME64_OFFSET_C 0x2bd40
#define GETPWNAM_R_OFFSET_C 0x2ac08
#define LISTEN_OFFSET_C 0xd5cc
#define INOTIFY_INIT_OFFSET_C 0xda50
#define DLREALLOC_OFFSET_C 0x15f14
#define MD5_UPDATE_OFFSET_C 0x282fc
#define DLMALLOC_OFFSET_C 0x13f84
#define FGETXATTR_OFFSET_C 0xce80
#define PWRITE_OFFSET_C 0x1a07c
#define MLOCK_OFFSET_C 0xcb04
#define ISASCII_OFFSET_C 0x1f4f6
#define TIMEGM64_OFFSET_C 0x2b3c0
#define SYSLOG_OFFSET_C 0x1a760
#define STATFS_OFFSET_C 0x1a2a8
#define WCSCMP_OFFSET_C 0x22ea4
#define WCSCPY_OFFSET_C 0x22ec0
#define VFDPRINTF_OFFSET_C 0x2714c
#define SETBUFFER_OFFSET_C 0x1c440
#define TZNAME_OFFSET_C 0x447c8
#define SIGWAIT_OFFSET_C 0x1a23e
#define SHA1FINAL_OFFSET_C 0x2a70c
#define GMTIME_R_OFFSET_C 0x2562c
#define VSNPRINTF_OFFSET_C 0x1edcc
#define WCSTOUL_OFFSET_C 0x227a0
#define PTHREAD_ATTR_GETSTACKADDR_OFFSET_C 0x11d78
#define MREMAP_OFFSET_C 0xca94
#define PSELECT_OFFSET_C 0x19f48
#define ETHER_ATON_R_OFFSET_C 0x239ac
#define PTHREAD_ONCE_OFFSET_C 0x13398
#define VPRINTF_OFFSET_C 0x1edb4
#define PTHREAD_ATFORK_OFFSET_C 0x1734c
#define WMEMCPY_OFFSET_C 0x23222
#define ISWGRAPH_OFFSET_C 0x22464
#define JRAND48_OFFSET_C 0x1f5d2
#define GETEUID_OFFSET_C 0xc5ac
#define FSEEK_OFFSET_C 0x1b8b8
#define STRPTIME_OFFSET_C 0x26904
#define DLMALLOC_USABLE_SIZE_OFFSET_C 0x1665c
#define GETOPT_LONG_ONLY_OFFSET_C 0x1979e
#define TSEARCH_OFFSET_C 0x2bdac
#define FUNOPEN_OFFSET_C 0x1b948
#define ISWALPHA_OFFSET_C 0x22418
#define GETRLIMIT_OFFSET_C 0xc7c8
#define REALPATH_OFFSET_C 0x28e4c
#define TIMER_GETOVERRUN_OFFSET_C 0x181c4
#define DLMALLINFO_OFFSET_C 0x16454
#define TOLOWER_OFFSET_C 0x22348
#define SCHED_YIELD_OFFSET_C 0xd778
#define WAITID_OFFSET_C 0x1a9b4
#define SETJMP_OFFSET_C 0xe560
#define IF_NAMETOINDEX_OFFSET_C 0x27e54
#define STRPBRK_OFFSET_C 0x22c60
#define OPTERR_OFFSET_C 0x44620
#define PTHREAD_COND_INIT_OFFSET_C 0x12a70
#define SETSERVENT_OFFSET_C 0x338ec
#define OPTRESET_OFFSET_C 0x493ac
#define SRAND48_OFFSET_C 0x1fb9c
#define PTHREAD_RWLOCK_TRYRDLOCK_OFFSET_C 0x174d4
#define WCSWCS_OFFSET_C 0x227a4
#define ALARM_OFFSET_C 0x182f8
#define DLMALLOC_MAX_FOOTPRINT_OFFSET_C 0x16444
#define GETUTENT_OFFSET_C 0x2be20
#define FUTEX_OFFSET_C 0xd9d8
#define PIPE_OFFSET_C 0xcc1c
#define WCSSTR_OFFSET_C 0x230de
#define PTHREAD_ATTR_GETDETACHSTATE_OFFSET_C 0x11cec
#define UTIMES_OFFSET_C 0xd450
#define SETVBUF_OFFSET_C 0x1c458
#define SCANDIR_OFFSET_C 0x19ae6
#define STRNCASECMP_OFFSET_C 0x22998
#define PTHREAD_GETATTR_NP_OFFSET_C 0x11e18
#define SEM_WAIT_OFFSET_C 0x292d4
#define GALLOCATIONSMUTEX_OFFSET_C 0x496d8
#define FREOPEN_OFFSET_C 0x1b428
#define ASCTIME64_R_OFFSET_C 0x2bcbc
#define FPURGE_OFFSET_C 0x1b17c
#define POSIX2TIME_OFFSET_C 0x256e6
#define PUTCHAR_UNLOCKED_OFFSET_C 0x1c164
#define STRTOULL_OFFSET_C 0x22164
#define DIRNAME_R_OFFSET_C 0x26e44
#define LSEEK64_OFFSET_C 0x1988a
#define STRTOL_OFFSET_C 0x21ea8
#define FPUTC_OFFSET_C 0x1b1e8
#define MALLOC_DOUBLE_FREE_BACKLOG_OFFSET_C 0x493a4
#define EPOLL_CREATE_OFFSET_C 0xd9fc
#define GMALLOCLEAKZYGOTECHILD_OFFSET_C 0x496d0
#define STRTOK_OFFSET_C 0x22d84
#define STRTOD_OFFSET_C 0x20688
#define MKSTEMPS_OFFSET_C 0x1c050
#define WRITEV_OFFSET_C 0xcb90
#define FPUTS_OFFSET_C 0x1b224
#define FCHMOD_OFFSET_C 0xcbe4
#define FTIME_OFFSET_C 0x18dd8
#define PTHREAD_MUTEX_TRYLOCK_OFFSET_C 0x12760
#define EPOLL_WAIT_OFFSET_C 0xda34
#define FSTAT_OFFSET_C 0xcff4
#define CAPSET_OFFSET_C 0xc8cc
#define PERSONALITY_OFFSET_C 0xd998
#define WMEMSET_OFFSET_C 0x2322e
#define ISWCTYPE_OFFSET_C 0x22544
#define DUP2_OFFSET_C 0xcc58
#define WCSCOLL_OFFSET_C 0x22ebc
#define FFS_OFFSET_C 0xdc54
#define INET_NTOP_OFFSET_C 0x2350c
#define ISWXDIGIT_OFFSET_C 0x22524
#define WCSNCMP_OFFSET_C 0x23022
#define STRSEP_OFFSET_C 0x22c9e
#define GETPGRP_OFFSET_C 0x197ae
#define PTSNAME_R_OFFSET_C 0x1a004
#define INET_NTOA_OFFSET_C 0x23468
#define MEMCPY_OFFSET_C 0xe16c
#define FILENO_OFFSET_C 0x1aea0
#define PTHREAD_COND_TIMEOUT_NP_OFFSET_C 0x12f8c
#define PERROR_OFFSET_C 0x19d08
#define PTHREAD_GETSCHEDPARAM_OFFSET_C 0x11ec0
#define FSCANF_OFFSET_C 0x1b5e0
#define UMOUNT_OFFSET_C 0x1a930
#define PTHREAD_COND_WAIT_OFFSET_C 0x12e74
#define ENDUTENT_OFFSET_C 0x2be6c
#define SYSLOG_R_OFFSET_C 0x1a730
#define MKDIRAT_OFFSET_C 0xcdd4
#define FGETWS_OFFSET_C 0x22688
#define STRNCMP_OFFSET_C 0x39c80
#define MKDTEMP_OFFSET_C 0x1c080
#define STRCAT_OFFSET_C 0x22a20
#define SETLOGMASK_R_OFFSET_C 0x1a784
#define FCHOWNAT_OFFSET_C 0xcdf4
#define GETSOCKNAME_OFFSET_C 0xd608
#define HERROR_OFFSET_C 0x2d2f8
#define CLOSE_OFFSET_C 0xc9dc
#define LSETXATTR_OFFSET_C 0xd188
#define FSETPOS_OFFSET_C 0x1b8bc
#define STRCHR_OFFSET_C 0x227dc
#define LREMOVEXATTR_OFFSET_C 0xd238
#define ARC4RANDOM_ADDRANDOM_OFFSET_C 0x26bbc
#define ARC4RANDOM_UNIFORM_OFFSET_C 0x26cd8
#define GETHOSTBYNAME2_OFFSET_C 0x2ce5c
#define FGETPOS_OFFSET_C 0x1adc4
#define FUNLOCKFILE_OFFSET_C 0x1b0d8
#define POSIX_MEMALIGN_OFFSET_C 0x1635c
#define SIGALTSTACK_OFFSET_C 0xc8e8
#define SEM_CLOSE_OFFSET_C 0x292aa
#define ATOLL_OFFSET_C 0x1f33c
#define PTHREAD_RWLOCK_TIMEDRDLOCK_OFFSET_C 0x17538
#define FCNTL_OFFSET_C 0x187a4
#define INET_NSAP_ADDR_OFFSET_C 0x2d150
#define ARC4RANDOM_STIR_OFFSET_C 0x26b9c
#define OPENLOG_R_OFFSET_C 0x1a36c
#define MEMALIGN_OFFSET_C 0x16f6c
#define LSTAT_OFFSET_C 0xd02c
#define INIT_MODULE_OFFSET_C 0xd944
#define SETRESGID_OFFSET_C 0xc720
#define TIMELOCAL_OFFSET_C 0x256a0
#define GETDTABLESIZE_OFFSET_C 0x18e7e
#define PTHREAD_ATTR_SETGUARDSIZE_OFFSET_C 0x11de4
#define SETSOCKOPT_OFFSET_C 0xd6b4
#define FSTATAT_OFFSET_C 0xcdb4
#define INITGROUPS_OFFSET_C 0x197d4
#define RES_MKQUERY_OFFSET_C 0x2d5a0
#define SYSV_SIGNAL_OFFSET_C 0x1a1f6
#define GETHOSTENT_OFFSET_C 0x2cf94
#define CLOSELOG_OFFSET_C 0x1a778
#define FREE_MALLOC_LEAK_INFO_OFFSET_C 0x16f0c
#define STRFTIME_OFFSET_C 0x26410
#define MBSINIT_OFFSET_C 0x2269a
#define TZSET_OFFSET_C 0x255ec
#define TIME2POSIX_OFFSET_C 0x256d0
#define STRXFRM_OFFSET_C 0x22de0
#define CHMOD_OFFSET_C 0xcf60
#define SETXATTR_OFFSET_C 0xd164
#define FDPRINTF_OFFSET_C 0x27178
#define SHUTDOWN_OFFSET_C 0xd694
#define PREAD_OFFSET_C 0x19f38
#define POLL_OFFSET_C 0xdaac
#define UNGETWC_OFFSET_C 0x22784
#define PUTW_OFFSET_C 0x1c254
#define SIGPROCMASK_OFFSET_C 0xd4a8
#define RAISE_OFFSET_C 0x1a08c
#define PUTS_OFFSET_C 0x1c1e8
#define SIGACTION_OFFSET_C 0xd48c
#define NANOSLEEP_OFFSET_C 0xd2e4
#define PUTC_OFFSET_C 0x1c130
#define DUP_OFFSET_C 0xcc00
#define STRTOUMAX_OFFSET_C 0x22168
#define MBRTOWC_OFFSET_C 0x226a8
#define STRSIGNAL_OFFSET_C 0x1a2b0
#define MKTIME_OFFSET_C 0x2567c
#define DLMALLOC_STATS_OFFSET_C 0x16560
#define CTIME64_R_OFFSET_C 0x2bd1c
#define EXECVP_OFFSET_C 0x18528
#define MBSRTOWCS_OFFSET_C 0x226d0
#define STRTOK_R_OFFSET_C 0x22d2e
#define PTHREAD_ATTR_SETSCHEDPARAM_OFFSET_C 0x11d1c
#define WCSWIDTH_OFFSET_C 0x23168
#define EXECVE_OFFSET_C 0xc53c
#define FPUTWS_OFFSET_C 0x22692
#define PTHREAD_ATTR_SETSTACKADDR_OFFSET_C 0x11d70
#define DRAND48_OFFSET_C 0x26f08
#define MADVISE_OFFSET_C 0xcae8
#define MOUNT_OFFSET_C 0xcfb4
#define GETRUSAGE_OFFSET_C 0xc7e4
#define PTHREAD_ATTR_GETSCHEDPOLICY_OFFSET_C 0x11d0c
#define GETGRNAM_OFFSET_C 0x2acbc
#define IOPRIO_GET_OFFSET_C 0xd898
#define GETPWUID_OFFSET_C 0x2a9f8
#define VSPRINTF_OFFSET_C 0x1ee20
#define PTHREAD_RWLOCK_UNLOCK_OFFSET_C 0x17728
#define RENAME_OFFSET_C 0xd09c
#define MALLOC_OFFSET_C 0x16f1c
#define DLMEMALIGN_OFFSET_C 0x161ac
#define WCWIDTH_OFFSET_C 0x227d4
#define PTHREAD_GETCPUCLOCKID_OFFSET_C 0x13378
#define READV_OFFSET_C 0xcb74
#define PRCTL_OFFSET_C 0xc88c
#define RES_QUERY_OFFSET_C 0x2d604
#define PTHREAD_ATTR_SETSCOPE_OFFSET_C 0x11e40
#define DLMALLOC_WALK_HEAP_OFFSET_C 0x167d8
#define SCHED_GETPARAM_OFFSET_C 0xd7b0
#define GETC_OFFSET_C 0x1bca4
#define MUNLOCK_OFFSET_C 0xcb20
#define VSYSLOG_R_OFFSET_C 0x1a3b4
#define RECVMSG_OFFSET_C 0xd720
#define TOWLOWER_OFFSET_C 0x22754
#define DLMALLOPT_OFFSET_C 0x1668c
#define GETS_OFFSET_C 0x1bd40
#define WAITPID_OFFSET_C 0x1a9ae
#define OPTARG_OFFSET_C 0x493a8
#define TDESTROY_OFFSET_C 0x2b24e
#define LONGJMP_OFFSET_C 0xe5a4
#define GETUSERSHELL_OFFSET_C 0x2ae94
#define ASCTIME64_OFFSET_C 0x2bd4c
#define FDOPENDIR_OFFSET_C 0x199e4
#define ISGRAPH_OFFSET_C 0x1f400
#define PTHREAD_RWLOCK_RDLOCK_OFFSET_C 0x17600
#define CALLOC_OFFSET_C 0x16f44
#define SETBUF_OFFSET_C 0x1c430
#define UNLINKAT_OFFSET_C 0xcf0c
#define PTHREAD_ATTR_GETGUARDSIZE_OFFSET_C 0x11e08
#define ISWPRINT_OFFSET_C 0x224a4
#define SETITIMER_OFFSET_C 0xd398
#define CLEARENV_OFFSET_C 0x26de4
#define SIGBLOCK_OFFSET_C 0x1a18c
#define NRAND48_OFFSET_C 0x1f680
#define DN_EXPAND_OFFSET_C 0x2d37c
#define FTS_OPEN_OFFSET_C 0x27884
#define PUTWCHAR_OFFSET_C 0x22710
#define LSEEK_OFFSET_C 0xc9f8
#define WCPCPY_OFFSET_C 0x22e04
#define MALLINFO_OFFSET_C 0x16f10
#define FLISTXATTR_OFFSET_C 0xce9c
#define WMEMCMP_OFFSET_C 0x231f6
#define DLMALLOC_TRIM_OFFSET_C 0x163d0
#define WCSLCAT_OFFSET_C 0x22f14
#define KILL_OFFSET_C 0xdcbc
#define PTHREAD_CONDATTR_DESTROY_OFFSET_C 0x12a54
#define PTHREAD_MUTEXATTR_GETPSHARED_OFFSET_C 0x12050
#define FFLUSH_OFFSET_C 0x1ac40
#define CLOCK_GETRES_OFFSET_C 0xd340
#define SEM_DESTROY_OFFSET_C 0x2926c
#define PTHREAD_ATTR_DESTROY_OFFSET_C 0x11c98
#define MMAP_OFFSET_C 0x198ae
#define TIMER_DELETE_OFFSET_C 0x17f7c
#define PTSNAME_OFFSET_C 0x19fd0
#define SEM_INIT_OFFSET_C 0x2923e
#define SETENV_OFFSET_C 0x1fa30
#define OPTOPT_OFFSET_C 0x4461c
#define LCHOWN_OFFSET_C 0xcf98
#define REALLOC_OFFSET_C 0x16f58
#define IOPRIO_SET_OFFSET_C 0xd878
#define H_ERRLIST_OFFSET_C 0x438a4
#define DELETE_MODULE_OFFSET_C 0xd960
#define WCSPBRK_OFFSET_C 0x2307e
#define READ_OFFSET_C 0xc920
#define ISWCNTRL_OFFSET_C 0x22438
#define TOASCII_OFFSET_C 0x1f500
#define HSTRERROR_OFFSET_C 0x2d2cc
#define GETNETBYADDR_OFFSET_C 0x2adf8
#define CACHEFLUSH_OFFSET_C 0xdb04
#define CTIME_OFFSET_C 0x25658
#define DAEMON_OFFSET_C 0x18358
#define STRSTR_OFFSET_C 0x22cf4
#define RENAMEAT_OFFSET_C 0xce3c
#define FSYNC_OFFSET_C 0xccec
#define MEMMOVE_OFFSET_C 0x17204
#define INET_ATON_OFFSET_C 0x23330
#define ISWPUNCT_OFFSET_C 0x224c4
#define SETEGID_OFFSET_C 0x1a11a
#define TIMER_CREATE_OFFSET_C 0x17d50
#define BSD_SIGNAL_OFFSET_C 0x1a1d2
#define STRCMP_OFFSET_C 0xe730
#define TEMPNAM_OFFSET_C 0x1c72c
#define TMPFILE_OFFSET_C 0x1c84c
#define REGCOMP_OFFSET_C 0x37b70
#define LLDIV_OFFSET_C 0x1f5e4
#define TOUPPER_OFFSET_C 0x22360
#define FGETC_OFFSET_C 0x1ac94
#define PCLOSE_OFFSET_C 0x19ed4
#define MRAND48_OFFSET_C 0x1f664
#define FTRUNCATE64_OFFSET_C 0xccb4
#define READDIR_OFFSET_C 0x19a08
#define SEED48_OFFSET_C 0x1f9cc
#define GETRESUID_OFFSET_C 0xc5e4
#define DAYLIGHT_OFFSET_C 0x4a82c
#define GETLOGIN_OFFSET_C 0x2ac40
#define DLCALLOC_OFFSET_C 0x15ec8
#define FGETS_OFFSET_C 0x1addc
#define GETGID_OFFSET_C 0xc590
#define SEM_GETVALUE_OFFSET_C 0x29470
#define TGKILL_OFFSET_C 0xdcf4
#define SEM_TIMEDWAIT_OFFSET_C 0x29310
#define SCHED_SETAFFINITY_OFFSET_C 0xd820
#define ARC4RANDOM_BUF_OFFSET_C 0x26c6c
#define FREMOVEXATTR_OFFSET_C 0xceb8
#define FTELL_OFFSET_C 0x1b944
#define EXIT_OFFSET_C 0x1f534
#define TTYNAME_R_OFFSET_C 0x2adcc
#define PTHREAD_SETSPECIFIC_OFFSET_C 0x131d4
#define ASCTIME_OFFSET_C 0x23b54
#define INOTIFY_RM_WATCH_OFFSET_C 0xda8c
#define SIGSETJMP_OFFSET_C 0xe614
#define MBSTOWCS_OFFSET_C 0x226fc
#define SETRLIMIT_OFFSET_C 0xc7ac
#define PTHREAD_EXIT_OFFSET_C 0x12ad0
#define GETITIMER_OFFSET_C 0xd37c
#define FCHMODAT_OFFSET_C 0xce1c
#define PTHREAD_RWLOCK_TRYWRLOCK_OFFSET_C 0x17608
#define GMTIME_OFFSET_C 0x2564c
#define SYMLINK_OFFSET_C 0xd110
#define PUTUTLINE_OFFSET_C 0x28d88
#define DIRFD_OFFSET_C 0x199a0
#define GETGRGID_OFFSET_C 0x2ac50
#define TIMER_GETTIME_OFFSET_C 0x18010
#define GETHOSTNAME_OFFSET_C 0x18e98
#define GETNAMEINFO_OFFSET_C 0x33870
#define SYSINFO_OFFSET_C 0xd97c
#define STRTOTIMEVAL_OFFSET_C 0x22d90
#define MSYNC_OFFSET_C 0xcab0
#define SETUSERSHELL_OFFSET_C 0x2aec8
#define MEMSWAP_OFFSET_C 0x22956
#define SIGINTERRUPT_OFFSET_C 0x1a1a4
#define ISWDIGIT_OFFSET_C 0x22458
#define STRCPY_OFFSET_C 0xe638
#define BSEARCH_OFFSET_C 0x1f344
#define READLINK_OFFSET_C 0xd064
#define DLMALLOC_FOOTPRINT_OFFSET_C 0x16434
#define WMEMMOVE_OFFSET_C 0x23228
#define ETHER_ATON_OFFSET_C 0x23a1c
#define ARC4RANDOM_OFFSET_C 0x26bf8
#define DLFREE_OFFSET_C 0x15730
#define UMOUNT2_OFFSET_C 0xcfd8
#define WCSCASECMP_OFFSET_C 0x22e42
#define ISPRINT_OFFSET_C 0x1f440
#define GETPGID_OFFSET_C 0xc678
#define DLVALLOC_OFFSET_C 0x16390
#define FOPEN_OFFSET_C 0x1b0e4
#define MEMCCPY_OFFSET_C 0x227f2
#define PUTENV_OFFSET_C 0x1f694
#define FDOPEN_OFFSET_C 0x1aaf8
#define PTHREAD_KEY_CREATE_OFFSET_C 0x12fd4
#define REMOVEXATTR_OFFSET_C 0xd21c
#define WCSLEN_OFFSET_C 0x22fa0
#define DLINDEPENDENT_COMALLOC_OFFSET_C 0x16388
#define WCSNCAT_OFFSET_C 0x22ff0
#define RMDIR_OFFSET_C 0xd080
#define PTHREAD_MUTEXATTR_DESTROY_OFFSET_C 0x11f84
#define PTHREAD_COND_TIMEDWAIT_OFFSET_C 0x12e6c
#define FORK_OFFSET_C 0x27190
#define MALLOC_DEBUG_INIT_OFFSET_C 0x16f94
#define STRTOIMAX_OFFSET_C 0x21c20
#define ALPHASORT_OFFSET_C 0x19ada
#define PTHREAD_SETSCHEDPARAM_OFFSET_C 0x11f1c
#define GETENV_OFFSET_C 0x1f5c8
#define ATOI_OFFSET_C 0x1f330
#define LINK_OFFSET_C 0xced4
#define PTRACE_OFFSET_C 0x18218
#define PTHREAD_MUTEX_UNLOCK_OFFSET_C 0x1267c
#define GETHOSTBYNAME_R_OFFSET_C 0x2ce2c
#define STRDUP_OFFSET_C 0x22a60
#define UNLOCKPT_OFFSET_C 0x1a938
#define GETNETBYNAME_OFFSET_C 0x2ad48
#define CPUACCT_ADD_OFFSET_C 0x26940
#define ERAND48_OFFSET_C 0x26f18
#define SBRK_OFFSET_C 0x1a0c4
#define WAIT3_OFFSET_C 0x1a996
#define GETPWUID_R_OFFSET_C 0x2abe8
#define SCHED_SETSCHEDULER_OFFSET_C 0xd740
#define FREEADDRINFO_OFFSET_C 0x32990
#define STRSPN_OFFSET_C 0x22cd2
#define TIME_OFFSET_C 0x1a876
#define UNGETC_OFFSET_C 0x1c94c
#define PTHREAD_RWLOCK_INIT_OFFSET_C 0x173dc
#define SSCANF_OFFSET_C 0x1c65c
#define MKTIME64_OFFSET_C 0x2b640
#define CREAT_OFFSET_C 0x1834c
#define STRNDUP_OFFSET_C 0x22c1e
#define SYSCALL_OFFSET_C 0xe970
#define FREAD_OFFSET_C 0x1b280
#define FTELLO_OFFSET_C 0x1b8c4
#define REMOVE_OFFSET_C 0x1c384
#define INET_PTON_OFFSET_C 0x23814
#define WCTYPE_OFFSET_C 0x227a8
#define PTHREAD_MUTEXATTR_SETTYPE_OFFSET_C 0x11fc4
#define PTHREAD_COND_DESTROY_OFFSET_C 0x12aac
#define PREAD64_OFFSET_C 0xc958
#define ISDIGIT_OFFSET_C 0x1f3e0
#define TIMEZONE_OFFSET_C 0x4a828
#define ISPUNCT_OFFSET_C 0x1f460
#define FSTATFS_OFFSET_C 0x18dd0
#define FWSCANF_OFFSET_C 0x223de
#define MEMMEM_OFFSET_C 0x22872
#define TMPNAM_OFFSET_C 0x1c904
#define TKILL_OFFSET_C 0xdcd8
#define SETPRIORITY_OFFSET_C 0xc790
#define GAI_STRERROR_OFFSET_C 0x3297c
#define GETOPT_OFFSET_C 0x19780
#define MKSTEMP_OFFSET_C 0x1c068
#define VFSCANF_OFFSET_C 0x1e4c4
#define TDELETE_OFFSET_C 0x2b1dc
#define MINCORE_OFFSET_C 0xcb3c
#define NICE_OFFSET_C 0x198ee
#define SENDFILE_OFFSET_C 0xcd98
#define PTHREAD_COND_TIMEDWAIT_MONOTONIC_OFFSET_C 0x12f80
#define STAT_OFFSET_C 0xd010
#define TRUNCATE_OFFSET_C 0xd148
#define KILLPG_OFFSET_C 0x1986c
#define SIGSUSPEND_OFFSET_C 0x1a232
#define REGERROR_OFFSET_C 0x37ea4
#define PTHREAD_COND_BROADCAST_OFFSET_C 0x12ac8
#define CLOSEDIR_OFFSET_C 0x19a90
#define GETEGID_OFFSET_C 0xc5c8
#define WCSDUP_OFFSET_C 0x22ef4
#define RES_INIT_OFFSET_C 0x2d510
#define FWPRINTF_OFFSET_C 0x2237a
#define SETLINEBUF_OFFSET_C 0x1c44e
#define GETUID_OFFSET_C 0xc574
#define FTS_READ_OFFSET_C 0x27a9c
#define GETSERVENT_R_OFFSET_C 0x33900
#define DIFFTIME_OFFSET_C 0x23b60
#define REGFREE_OFFSET_C 0x39900
#define WCSCSPN_OFFSET_C 0x22ed0
#define MD5_INIT_OFFSET_C 0x282d8
#define FPATHCONF_OFFSET_C 0x19c50
#define CHOWN_OFFSET_C 0xcf7c
#define H_NERR_OFFSET_C 0x3e564
#define READDIR_R_OFFSET_C 0x19a28
#define PTHREAD_SELF_OFFSET_C 0x11b7c

void sysLibCWcsftimeHookHandler(CPUState* env, int isBefore);
void sysLibCFreedtoaHookHandler(CPUState* env, int isBefore);
void sysLibCFcloseHookHandler(CPUState* env, int isBefore);
void sysLibCGetaddrinfoHookHandler(CPUState* env, int isBefore);
void sysLibCRebootHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Mutex_LockHookHandler(CPUState* env, int isBefore);
void sysLibCVwarnHookHandler(CPUState* env, int isBefore);
void sysLibCSleepHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Condattr_GetpsharedHookHandler(CPUState* env, int isBefore);
void sysLibCIsxdigitHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Cond_Timedwait_Relative_NpHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Key_DeleteHookHandler(CPUState* env, int isBefore);
void sysLibCWcsncasecmpHookHandler(CPUState* env, int isBefore);
void sysLibCGetresgidHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Attr_GetscopeHookHandler(CPUState* env, int isBefore);
void sysLibCSha1InitHookHandler(CPUState* env, int isBefore);
void sysLibCUmaskHookHandler(CPUState* env, int isBefore);
void sysLibCSched_GetaffinityHookHandler(CPUState* env, int isBefore);
void sysLibCSendHookHandler(CPUState* env, int isBefore);
void sysLibCWcslcpyHookHandler(CPUState* env, int isBefore);
void sysLibCSched_SetparamHookHandler(CPUState* env, int isBefore);
void sysLibCMalloc_Debug_FiniHookHandler(CPUState* env, int isBefore);
void sysLibCSetutentHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Setname_NpHookHandler(CPUState* env, int isBefore);
void sysLibCIsspaceHookHandler(CPUState* env, int isBefore);
void sysLibCLocaltimeHookHandler(CPUState* env, int isBefore);
void sysLibCVerrHookHandler(CPUState* env, int isBefore);
void sysLibCGetptHookHandler(CPUState* env, int isBefore);
void sysLibCCtime_RHookHandler(CPUState* env, int isBefore);
void sysLibCGetc_UnlockedHookHandler(CPUState* env, int isBefore);
void sysLibCGetppidHookHandler(CPUState* env, int isBefore);
void sysLibCDlindependent_CallocHookHandler(CPUState* env, int isBefore);
void sysLibCUtmpnameHookHandler(CPUState* env, int isBefore);
void sysLibCSeteuidHookHandler(CPUState* env, int isBefore);
void sysLibCCapgetHookHandler(CPUState* env, int isBefore);
void sysLibCUtimeHookHandler(CPUState* env, int isBefore);
void sysLibCGettidHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Attr_SetstacksizeHookHandler(CPUState* env, int isBefore);
void sysLibCIssetugidHookHandler(CPUState* env, int isBefore);
void sysLibCTimegmHookHandler(CPUState* env, int isBefore);
void sysLibCDlpvallocHookHandler(CPUState* env, int isBefore);
void sysLibCTcsetpgrpHookHandler(CPUState* env, int isBefore);
void sysLibCFgetlnHookHandler(CPUState* env, int isBefore);
void sysLibCRecvfromHookHandler(CPUState* env, int isBefore);
void sysLibCSched_Get_Priority_MaxHookHandler(CPUState* env, int isBefore);
void sysLibCGetmntentHookHandler(CPUState* env, int isBefore);
void sysLibCIswspaceHookHandler(CPUState* env, int isBefore);
void sysLibCDivHookHandler(CPUState* env, int isBefore);
void sysLibCIsblankHookHandler(CPUState* env, int isBefore);
void sysLibCTtynameHookHandler(CPUState* env, int isBefore);
void sysLibCKlogctlHookHandler(CPUState* env, int isBefore);
void sysLibCSnprintfHookHandler(CPUState* env, int isBefore);
void sysLibCOptindHookHandler(CPUState* env, int isBefore);
void sysLibCMemsetHookHandler(CPUState* env, int isBefore);
void sysLibCWcschrHookHandler(CPUState* env, int isBefore);
void sysLibCSyncHookHandler(CPUState* env, int isBefore);
void sysLibCGetgrouplistHookHandler(CPUState* env, int isBefore);
void sysLibCMknodHookHandler(CPUState* env, int isBefore);
void sysLibCStrcasestrHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Mutex_DestroyHookHandler(CPUState* env, int isBefore);
void sysLibCWcrtombHookHandler(CPUState* env, int isBefore);
void sysLibCStrlcatHookHandler(CPUState* env, int isBefore);
void sysLibCLlistxattrHookHandler(CPUState* env, int isBefore);
void sysLibCMktempHookHandler(CPUState* env, int isBefore);
void sysLibCGetchar_UnlockedHookHandler(CPUState* env, int isBefore);
void sysLibCClockHookHandler(CPUState* env, int isBefore);
void sysLibCAtexitHookHandler(CPUState* env, int isBefore);
void sysLibCOpenlogHookHandler(CPUState* env, int isBefore);
void sysLibCInotify_Add_WatchHookHandler(CPUState* env, int isBefore);
void sysLibCAccessHookHandler(CPUState* env, int isBefore);
void sysLibCBasename_RHookHandler(CPUState* env, int isBefore);
void sysLibCSetlogmaskHookHandler(CPUState* env, int isBefore);
void sysLibCWcstolHookHandler(CPUState* env, int isBefore);
void sysLibCMunmapHookHandler(CPUState* env, int isBefore);
void sysLibCSocketpairHookHandler(CPUState* env, int isBefore);
void sysLibCSettimeofdayHookHandler(CPUState* env, int isBefore);
void sysLibCSetresuidHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_DetachHookHandler(CPUState* env, int isBefore);
void sysLibCFts_CloseHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Attr_SetdetachstateHookHandler(CPUState* env, int isBefore);
void sysLibCSetpgidHookHandler(CPUState* env, int isBefore);
void sysLibCVwprintfHookHandler(CPUState* env, int isBefore);
void sysLibCLocaltime_RHookHandler(CPUState* env, int isBefore);
void sysLibCTimelocal64HookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Attr_InitHookHandler(CPUState* env, int isBefore);
void sysLibCPauseHookHandler(CPUState* env, int isBefore);
void sysLibCTimer_SettimeHookHandler(CPUState* env, int isBefore);
void sysLibCSetregidHookHandler(CPUState* env, int isBefore);
void sysLibCFchdirHookHandler(CPUState* env, int isBefore);
void sysLibCWcpncpyHookHandler(CPUState* env, int isBefore);
void sysLibCFake_Localtime_RHookHandler(CPUState* env, int isBefore);
void sysLibCWaitHookHandler(CPUState* env, int isBefore);
void sysLibCGetdentsHookHandler(CPUState* env, int isBefore);
void sysLibCVerrxHookHandler(CPUState* env, int isBefore);
void sysLibCEventfdHookHandler(CPUState* env, int isBefore);
void sysLibCPipe2HookHandler(CPUState* env, int isBefore);
void sysLibCEther_Ntoa_RHookHandler(CPUState* env, int isBefore);
void sysLibCPopenHookHandler(CPUState* env, int isBefore);
void sysLibCWcsxfrmHookHandler(CPUState* env, int isBefore);
void sysLibCFputwcHookHandler(CPUState* env, int isBefore);
void sysLibCPerf_Event_OpenHookHandler(CPUState* env, int isBefore);
void sysLibCSendmsgHookHandler(CPUState* env, int isBefore);
void sysLibCIswalnumHookHandler(CPUState* env, int isBefore);
void sysLibCEpoll_CtlHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Mutexattr_GettypeHookHandler(CPUState* env, int isBefore);
void sysLibCBzeroHookHandler(CPUState* env, int isBefore);
void sysLibCWcstokHookHandler(CPUState* env, int isBefore);
void sysLibCBrkHookHandler(CPUState* env, int isBefore);
void sysLibCSched_Rr_Get_IntervalHookHandler(CPUState* env, int isBefore);
void sysLibCPrintfHookHandler(CPUState* env, int isBefore);
void sysLibCFtokHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Mutex_InitHookHandler(CPUState* env, int isBefore);
void sysLibCWcstodHookHandler(CPUState* env, int isBefore);
void sysLibCClock_SettimeHookHandler(CPUState* env, int isBefore);
void sysLibCSelectHookHandler(CPUState* env, int isBefore);
void sysLibCGetcharHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_EqualHookHandler(CPUState* env, int isBefore);
void sysLibCCloselog_RHookHandler(CPUState* env, int isBefore);
void sysLibCGetsockoptHookHandler(CPUState* env, int isBefore);
void sysLibCSha1UpdateHookHandler(CPUState* env, int isBefore);
void sysLibCGetpriorityHookHandler(CPUState* env, int isBefore);
void sysLibCGhashtableHookHandler(CPUState* env, int isBefore);
void sysLibCFdatasyncHookHandler(CPUState* env, int isBefore);
void sysLibCSys_SignameHookHandler(CPUState* env, int isBefore);
void sysLibCIsattyHookHandler(CPUState* env, int isBefore);
void sysLibCWcsncpyHookHandler(CPUState* env, int isBefore);
void sysLibCPathconfHookHandler(CPUState* env, int isBefore);
void sysLibCSched_GetschedulerHookHandler(CPUState* env, int isBefore);
void sysLibCWarnHookHandler(CPUState* env, int isBefore);
void sysLibCWcscatHookHandler(CPUState* env, int isBefore);
void sysLibCGettimeofdayHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_SigmaskHookHandler(CPUState* env, int isBefore);
void sysLibCSem_OpenHookHandler(CPUState* env, int isBefore);
void sysLibCSocketHookHandler(CPUState* env, int isBefore);
void sysLibCChdirHookHandler(CPUState* env, int isBefore);
void sysLibCErrHookHandler(CPUState* env, int isBefore);
void sysLibCFtrylockfileHookHandler(CPUState* env, int isBefore);
void sysLibCStrerrorHookHandler(CPUState* env, int isBefore);
void sysLibCIswlowerHookHandler(CPUState* env, int isBefore);
void sysLibCSetuidHookHandler(CPUState* env, int isBefore);
void sysLibCSwprintfHookHandler(CPUState* env, int isBefore);
void sysLibCUtimensatHookHandler(CPUState* env, int isBefore);
void sysLibCInet_Nsap_NtoaHookHandler(CPUState* env, int isBefore);
void sysLibCFnmatchHookHandler(CPUState* env, int isBefore);
void sysLibCFtruncateHookHandler(CPUState* env, int isBefore);
void sysLibCGetprotobynumberHookHandler(CPUState* env, int isBefore);
void sysLibCVforkHookHandler(CPUState* env, int isBefore);
void sysLibCSysconfHookHandler(CPUState* env, int isBefore);
void sysLibCWprintfHookHandler(CPUState* env, int isBefore);
void sysLibCMprotectHookHandler(CPUState* env, int isBefore);
void sysLibCSem_TrywaitHookHandler(CPUState* env, int isBefore);
void sysLibCAcceptHookHandler(CPUState* env, int isBefore);
void sysLibCAbortHookHandler(CPUState* env, int isBefore);
void sysLibCFprintfHookHandler(CPUState* env, int isBefore);
void sysLibCStrtollHookHandler(CPUState* env, int isBefore);
void sysLibCTowupperHookHandler(CPUState* env, int isBefore);
void sysLibCStrlenHookHandler(CPUState* env, int isBefore);
void sysLibCGet_Malloc_Leak_InfoHookHandler(CPUState* env, int isBefore);
void sysLibCStrncatHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_GetspecificHookHandler(CPUState* env, int isBefore);
void sysLibCChrootHookHandler(CPUState* env, int isBefore);
void sysLibCClearerrHookHandler(CPUState* env, int isBefore);
void sysLibCGetgroupsHookHandler(CPUState* env, int isBefore);
void sysLibCFeofHookHandler(CPUState* env, int isBefore);
void sysLibCLrand48HookHandler(CPUState* env, int isBefore);
void sysLibCStrntoumaxHookHandler(CPUState* env, int isBefore);
void sysLibCWriteHookHandler(CPUState* env, int isBefore);
void sysLibCVfprintfHookHandler(CPUState* env, int isBefore);
void sysLibCRewindHookHandler(CPUState* env, int isBefore);
void sysLibCWmemchrHookHandler(CPUState* env, int isBefore);
void sysLibCPutc_UnlockedHookHandler(CPUState* env, int isBefore);
void sysLibCVwarnxHookHandler(CPUState* env, int isBefore);
void sysLibCWcsrchrHookHandler(CPUState* env, int isBefore);
void sysLibCFlockfileHookHandler(CPUState* env, int isBefore);
void sysLibCIf_IndextonameHookHandler(CPUState* env, int isBefore);
void sysLibCVasprintfHookHandler(CPUState* env, int isBefore);
void sysLibCMemrchrHookHandler(CPUState* env, int isBefore);
void sysLibCUnsetenvHookHandler(CPUState* env, int isBefore);
void sysLibCOpenatHookHandler(CPUState* env, int isBefore);
void sysLibCCloneHookHandler(CPUState* env, int isBefore);
void sysLibCSigsetmaskHookHandler(CPUState* env, int isBefore);
void sysLibCGetxattrHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Condattr_SetpsharedHookHandler(CPUState* env, int isBefore);
void sysLibCIoctlHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Rwlock_WrlockHookHandler(CPUState* env, int isBefore);
void sysLibCVallocHookHandler(CPUState* env, int isBefore);
void sysLibCSetgroupsHookHandler(CPUState* env, int isBefore);
void sysLibCUnlinkHookHandler(CPUState* env, int isBefore);
void sysLibCGmtime64_RHookHandler(CPUState* env, int isBefore);
void sysLibCTcgetpgrpHookHandler(CPUState* env, int isBefore);
void sysLibCLongjmperrorHookHandler(CPUState* env, int isBefore);
void sysLibCStrerror_RHookHandler(CPUState* env, int isBefore);
void sysLibCBindHookHandler(CPUState* env, int isBefore);
void sysLibCLocaltime64_RHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Attr_SetschedpolicyHookHandler(CPUState* env, int isBefore);
void sysLibCIscntrlHookHandler(CPUState* env, int isBefore);
void sysLibCSetpgrpHookHandler(CPUState* env, int isBefore);
void sysLibCRes_SearchHookHandler(CPUState* env, int isBefore);
void sysLibCEnvironHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Rwlock_TimedwrlockHookHandler(CPUState* env, int isBefore);
void sysLibCEndusershellHookHandler(CPUState* env, int isBefore);
void sysLibCGetserventHookHandler(CPUState* env, int isBefore);
void sysLibCStrntoimaxHookHandler(CPUState* env, int isBefore);
void sysLibCBasenameHookHandler(CPUState* env, int isBefore);
void sysLibCExecleHookHandler(CPUState* env, int isBefore);
void sysLibCFgetwcHookHandler(CPUState* env, int isBefore);
void sysLibCUnameHookHandler(CPUState* env, int isBefore);
void sysLibCBtowcHookHandler(CPUState* env, int isBefore);
void sysLibCMbrlenHookHandler(CPUState* env, int isBefore);
void sysLibCStrtoulHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_KillHookHandler(CPUState* env, int isBefore);
void sysLibCExeclpHookHandler(CPUState* env, int isBefore);
void sysLibCSem_UnlinkHookHandler(CPUState* env, int isBefore);
void sysLibCEventfd_ReadHookHandler(CPUState* env, int isBefore);
void sysLibCReadaheadHookHandler(CPUState* env, int isBefore);
void sysLibCFwriteHookHandler(CPUState* env, int isBefore);
void sysLibCGetpidHookHandler(CPUState* env, int isBefore);
void sysLibCSetgidHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Mutexattr_SetpsharedHookHandler(CPUState* env, int isBefore);
void sysLibCStrnlenHookHandler(CPUState* env, int isBefore);
void sysLibCSched_Get_Priority_MinHookHandler(CPUState* env, int isBefore);
void sysLibCFchownHookHandler(CPUState* env, int isBefore);
void sysLibCFts_SetHookHandler(CPUState* env, int isBefore);
void sysLibCGetpwnamHookHandler(CPUState* env, int isBefore);
void sysLibCStrcollHookHandler(CPUState* env, int isBefore);
void sysLibCRewinddirHookHandler(CPUState* env, int isBefore);
void sysLibCExeclHookHandler(CPUState* env, int isBefore);
void sysLibCInet_AddrHookHandler(CPUState* env, int isBefore);
void sysLibCEther_NtoaHookHandler(CPUState* env, int isBefore);
void sysLibCIswupperHookHandler(CPUState* env, int isBefore);
void sysLibCBindresvportHookHandler(CPUState* env, int isBefore);
void sysLibCSetreuidHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Attr_GetschedparamHookHandler(CPUState* env, int isBefore);
void sysLibCSiglongjmpHookHandler(CPUState* env, int isBefore);
void sysLibCErrxHookHandler(CPUState* env, int isBefore);
void sysLibCSendtoHookHandler(CPUState* env, int isBefore);
void sysLibCExecvHookHandler(CPUState* env, int isBefore);
void sysLibCFts_ChildrenHookHandler(CPUState* env, int isBefore);
void sysLibCMemchrHookHandler(CPUState* env, int isBefore);
void sysLibCLgetxattrHookHandler(CPUState* env, int isBefore);
void sysLibCClock_GettimeHookHandler(CPUState* env, int isBefore);
void sysLibCVsscanfHookHandler(CPUState* env, int isBefore);
void sysLibCSys_SiglistHookHandler(CPUState* env, int isBefore);
void sysLibCSha1TransformHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Attr_SetstackHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Cond_SignalHookHandler(CPUState* env, int isBefore);
void sysLibCConnectHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_CreateHookHandler(CPUState* env, int isBefore);
void sysLibCFlockHookHandler(CPUState* env, int isBefore);
void sysLibCDirnameHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Mutexattr_InitHookHandler(CPUState* env, int isBefore);
void sysLibCStrlcpyHookHandler(CPUState* env, int isBefore);
void sysLibCOpendirHookHandler(CPUState* env, int isBefore);
void sysLibCDlmalloc_Walk_Free_PagesHookHandler(CPUState* env, int isBefore);
void sysLibCSetsidHookHandler(CPUState* env, int isBefore);
void sysLibCRestore_Core_RegsHookHandler(CPUState* env, int isBefore);
void sysLibCSprintfHookHandler(CPUState* env, int isBefore);
void sysLibCVscanfHookHandler(CPUState* env, int isBefore);
void sysLibCStrrchrHookHandler(CPUState* env, int isBefore);
void sysLibCRegexecHookHandler(CPUState* env, int isBefore);
void sysLibCEventfd_WriteHookHandler(CPUState* env, int isBefore);
void sysLibCGethostbyaddrHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Rwlock_DestroyHookHandler(CPUState* env, int isBefore);
void sysLibCStrcspnHookHandler(CPUState* env, int isBefore);
void sysLibCMd5_FinalHookHandler(CPUState* env, int isBefore);
void sysLibCAsprintfHookHandler(CPUState* env, int isBefore);
void sysLibCFerrorHookHandler(CPUState* env, int isBefore);
void sysLibCGetcwdHookHandler(CPUState* env, int isBefore);
void sysLibCFreeHookHandler(CPUState* env, int isBefore);
void sysLibCFake_Gmtime_RHookHandler(CPUState* env, int isBefore);
void sysLibCTfindHookHandler(CPUState* env, int isBefore);
void sysLibCAsctime_RHookHandler(CPUState* env, int isBefore);
void sysLibCGetpeernameHookHandler(CPUState* env, int isBefore);
void sysLibCRecvHookHandler(CPUState* env, int isBefore);
void sysLibCFwideHookHandler(CPUState* env, int isBefore);
void sysLibCFseekoHookHandler(CPUState* env, int isBefore);
void sysLibCPutcharHookHandler(CPUState* env, int isBefore);
void sysLibCGethostbynameHookHandler(CPUState* env, int isBefore);
void sysLibCWcsspnHookHandler(CPUState* env, int isBefore);
void sysLibCGetprotobynameHookHandler(CPUState* env, int isBefore);
void sysLibCTimesHookHandler(CPUState* env, int isBefore);
void sysLibCCtime64HookHandler(CPUState* env, int isBefore);
void sysLibCSched_GetcpuHookHandler(CPUState* env, int isBefore);
void sysLibCPwrite64HookHandler(CPUState* env, int isBefore);
void sysLibCIslowerHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Attr_GetstackHookHandler(CPUState* env, int isBefore);
void sysLibCIsupperHookHandler(CPUState* env, int isBefore);
void sysLibCVsyslogHookHandler(CPUState* env, int isBefore);
void sysLibCGetopt_LongHookHandler(CPUState* env, int isBefore);
void sysLibCGetservbynameHookHandler(CPUState* env, int isBefore);
void sysLibCLocaltime64HookHandler(CPUState* env, int isBefore);
void sysLibCWarnxHookHandler(CPUState* env, int isBefore);
void sysLibCQsortHookHandler(CPUState* env, int isBefore);
void sysLibCSem_PostHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_JoinHookHandler(CPUState* env, int isBefore);
void sysLibCBcopyHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Attr_GetstacksizeHookHandler(CPUState* env, int isBefore);
void sysLibCLdexpHookHandler(CPUState* env, int isBefore);
void sysLibCNsdispatchHookHandler(CPUState* env, int isBefore);
void sysLibCFsetxattrHookHandler(CPUState* env, int isBefore);
void sysLibCRes_Get_Dns_ChangedHookHandler(CPUState* env, int isBefore);
void sysLibCAcctHookHandler(CPUState* env, int isBefore);
void sysLibCGetservbyportHookHandler(CPUState* env, int isBefore);
void sysLibCOpenHookHandler(CPUState* env, int isBefore);
void sysLibCStrncpyHookHandler(CPUState* env, int isBefore);
void sysLibCUsleepHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Mutex_Lock_Timeout_NpHookHandler(CPUState* env, int isBefore);
void sysLibCClock_NanosleepHookHandler(CPUState* env, int isBefore);
void sysLibCWcsnlenHookHandler(CPUState* env, int isBefore);
void sysLibCIsalnumHookHandler(CPUState* env, int isBefore);
void sysLibCListxattrHookHandler(CPUState* env, int isBefore);
void sysLibCScanfHookHandler(CPUState* env, int isBefore);
void sysLibCMkdirHookHandler(CPUState* env, int isBefore);
void sysLibCSystemHookHandler(CPUState* env, int isBefore);
void sysLibCSigpendingHookHandler(CPUState* env, int isBefore);
void sysLibCStrcasecmpHookHandler(CPUState* env, int isBefore);
void sysLibCFaccessatHookHandler(CPUState* env, int isBefore);
void sysLibCIsalphaHookHandler(CPUState* env, int isBefore);
void sysLibCMemcmpHookHandler(CPUState* env, int isBefore);
void sysLibCStrftime_TzHookHandler(CPUState* env, int isBefore);
void sysLibCGmtime64HookHandler(CPUState* env, int isBefore);
void sysLibCGetpwnam_RHookHandler(CPUState* env, int isBefore);
void sysLibCListenHookHandler(CPUState* env, int isBefore);
void sysLibCInotify_InitHookHandler(CPUState* env, int isBefore);
void sysLibCDlreallocHookHandler(CPUState* env, int isBefore);
void sysLibCMd5_UpdateHookHandler(CPUState* env, int isBefore);
void sysLibCDlmallocHookHandler(CPUState* env, int isBefore);
void sysLibCFgetxattrHookHandler(CPUState* env, int isBefore);
void sysLibCPwriteHookHandler(CPUState* env, int isBefore);
void sysLibCMlockHookHandler(CPUState* env, int isBefore);
void sysLibCIsasciiHookHandler(CPUState* env, int isBefore);
void sysLibCTimegm64HookHandler(CPUState* env, int isBefore);
void sysLibCSyslogHookHandler(CPUState* env, int isBefore);
void sysLibCStatfsHookHandler(CPUState* env, int isBefore);
void sysLibCWcscmpHookHandler(CPUState* env, int isBefore);
void sysLibCWcscpyHookHandler(CPUState* env, int isBefore);
void sysLibCVfdprintfHookHandler(CPUState* env, int isBefore);
void sysLibCSetbufferHookHandler(CPUState* env, int isBefore);
void sysLibCTznameHookHandler(CPUState* env, int isBefore);
void sysLibCSigwaitHookHandler(CPUState* env, int isBefore);
void sysLibCSha1FinalHookHandler(CPUState* env, int isBefore);
void sysLibCGmtime_RHookHandler(CPUState* env, int isBefore);
void sysLibCVsnprintfHookHandler(CPUState* env, int isBefore);
void sysLibCWcstoulHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Attr_GetstackaddrHookHandler(CPUState* env, int isBefore);
void sysLibCMremapHookHandler(CPUState* env, int isBefore);
void sysLibCPselectHookHandler(CPUState* env, int isBefore);
void sysLibCEther_Aton_RHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_OnceHookHandler(CPUState* env, int isBefore);
void sysLibCVprintfHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_AtforkHookHandler(CPUState* env, int isBefore);
void sysLibCWmemcpyHookHandler(CPUState* env, int isBefore);
void sysLibCIswgraphHookHandler(CPUState* env, int isBefore);
void sysLibCJrand48HookHandler(CPUState* env, int isBefore);
void sysLibCGeteuidHookHandler(CPUState* env, int isBefore);
void sysLibCFseekHookHandler(CPUState* env, int isBefore);
void sysLibCStrptimeHookHandler(CPUState* env, int isBefore);
void sysLibCDlmalloc_Usable_SizeHookHandler(CPUState* env, int isBefore);
void sysLibCGetopt_Long_OnlyHookHandler(CPUState* env, int isBefore);
void sysLibCTsearchHookHandler(CPUState* env, int isBefore);
void sysLibCFunopenHookHandler(CPUState* env, int isBefore);
void sysLibCIswalphaHookHandler(CPUState* env, int isBefore);
void sysLibCGetrlimitHookHandler(CPUState* env, int isBefore);
void sysLibCRealpathHookHandler(CPUState* env, int isBefore);
void sysLibCTimer_GetoverrunHookHandler(CPUState* env, int isBefore);
void sysLibCDlmallinfoHookHandler(CPUState* env, int isBefore);
void sysLibCTolowerHookHandler(CPUState* env, int isBefore);
void sysLibCSched_YieldHookHandler(CPUState* env, int isBefore);
void sysLibCWaitidHookHandler(CPUState* env, int isBefore);
void sysLibCSetjmpHookHandler(CPUState* env, int isBefore);
void sysLibCIf_NametoindexHookHandler(CPUState* env, int isBefore);
void sysLibCStrpbrkHookHandler(CPUState* env, int isBefore);
void sysLibCOpterrHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Cond_InitHookHandler(CPUState* env, int isBefore);
void sysLibCSetserventHookHandler(CPUState* env, int isBefore);
void sysLibCOptresetHookHandler(CPUState* env, int isBefore);
void sysLibCSrand48HookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Rwlock_TryrdlockHookHandler(CPUState* env, int isBefore);
void sysLibCWcswcsHookHandler(CPUState* env, int isBefore);
void sysLibCAlarmHookHandler(CPUState* env, int isBefore);
void sysLibCDlmalloc_Max_FootprintHookHandler(CPUState* env, int isBefore);
void sysLibCGetutentHookHandler(CPUState* env, int isBefore);
void sysLibCFutexHookHandler(CPUState* env, int isBefore);
void sysLibCPipeHookHandler(CPUState* env, int isBefore);
void sysLibCWcsstrHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Attr_GetdetachstateHookHandler(CPUState* env, int isBefore);
void sysLibCUtimesHookHandler(CPUState* env, int isBefore);
void sysLibCSetvbufHookHandler(CPUState* env, int isBefore);
void sysLibCScandirHookHandler(CPUState* env, int isBefore);
void sysLibCStrncasecmpHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Getattr_NpHookHandler(CPUState* env, int isBefore);
void sysLibCSem_WaitHookHandler(CPUState* env, int isBefore);
void sysLibCGallocationsmutexHookHandler(CPUState* env, int isBefore);
void sysLibCFreopenHookHandler(CPUState* env, int isBefore);
void sysLibCAsctime64_RHookHandler(CPUState* env, int isBefore);
void sysLibCFpurgeHookHandler(CPUState* env, int isBefore);
void sysLibCPosix2TimeHookHandler(CPUState* env, int isBefore);
void sysLibCPutchar_UnlockedHookHandler(CPUState* env, int isBefore);
void sysLibCStrtoullHookHandler(CPUState* env, int isBefore);
void sysLibCDirname_RHookHandler(CPUState* env, int isBefore);
void sysLibCLseek64HookHandler(CPUState* env, int isBefore);
void sysLibCStrtolHookHandler(CPUState* env, int isBefore);
void sysLibCFputcHookHandler(CPUState* env, int isBefore);
void sysLibCMalloc_Double_Free_BacklogHookHandler(CPUState* env, int isBefore);
void sysLibCEpoll_CreateHookHandler(CPUState* env, int isBefore);
void sysLibCGmallocleakzygotechildHookHandler(CPUState* env, int isBefore);
void sysLibCStrtokHookHandler(CPUState* env, int isBefore);
void sysLibCStrtodHookHandler(CPUState* env, int isBefore);
void sysLibCMkstempsHookHandler(CPUState* env, int isBefore);
void sysLibCWritevHookHandler(CPUState* env, int isBefore);
void sysLibCFputsHookHandler(CPUState* env, int isBefore);
void sysLibCFchmodHookHandler(CPUState* env, int isBefore);
void sysLibCFtimeHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Mutex_TrylockHookHandler(CPUState* env, int isBefore);
void sysLibCEpoll_WaitHookHandler(CPUState* env, int isBefore);
void sysLibCFstatHookHandler(CPUState* env, int isBefore);
void sysLibCCapsetHookHandler(CPUState* env, int isBefore);
void sysLibCPersonalityHookHandler(CPUState* env, int isBefore);
void sysLibCWmemsetHookHandler(CPUState* env, int isBefore);
void sysLibCIswctypeHookHandler(CPUState* env, int isBefore);
void sysLibCDup2HookHandler(CPUState* env, int isBefore);
void sysLibCWcscollHookHandler(CPUState* env, int isBefore);
void sysLibCFfsHookHandler(CPUState* env, int isBefore);
void sysLibCInet_NtopHookHandler(CPUState* env, int isBefore);
void sysLibCIswxdigitHookHandler(CPUState* env, int isBefore);
void sysLibCWcsncmpHookHandler(CPUState* env, int isBefore);
void sysLibCStrsepHookHandler(CPUState* env, int isBefore);
void sysLibCGetpgrpHookHandler(CPUState* env, int isBefore);
void sysLibCPtsname_RHookHandler(CPUState* env, int isBefore);
void sysLibCInet_NtoaHookHandler(CPUState* env, int isBefore);
void sysLibCMemcpyHookHandler(CPUState* env, int isBefore);
void sysLibCFilenoHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Cond_Timeout_NpHookHandler(CPUState* env, int isBefore);
void sysLibCPerrorHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_GetschedparamHookHandler(CPUState* env, int isBefore);
void sysLibCFscanfHookHandler(CPUState* env, int isBefore);
void sysLibCUmountHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Cond_WaitHookHandler(CPUState* env, int isBefore);
void sysLibCEndutentHookHandler(CPUState* env, int isBefore);
void sysLibCSyslog_RHookHandler(CPUState* env, int isBefore);
void sysLibCMkdiratHookHandler(CPUState* env, int isBefore);
void sysLibCFgetwsHookHandler(CPUState* env, int isBefore);
void sysLibCStrncmpHookHandler(CPUState* env, int isBefore);
void sysLibCMkdtempHookHandler(CPUState* env, int isBefore);
void sysLibCStrcatHookHandler(CPUState* env, int isBefore);
void sysLibCSetlogmask_RHookHandler(CPUState* env, int isBefore);
void sysLibCFchownatHookHandler(CPUState* env, int isBefore);
void sysLibCGetsocknameHookHandler(CPUState* env, int isBefore);
void sysLibCHerrorHookHandler(CPUState* env, int isBefore);
void sysLibCCloseHookHandler(CPUState* env, int isBefore);
void sysLibCLsetxattrHookHandler(CPUState* env, int isBefore);
void sysLibCFsetposHookHandler(CPUState* env, int isBefore);
void sysLibCStrchrHookHandler(CPUState* env, int isBefore);
void sysLibCLremovexattrHookHandler(CPUState* env, int isBefore);
void sysLibCArc4Random_AddrandomHookHandler(CPUState* env, int isBefore);
void sysLibCArc4Random_UniformHookHandler(CPUState* env, int isBefore);
void sysLibCGethostbyname2HookHandler(CPUState* env, int isBefore);
void sysLibCFgetposHookHandler(CPUState* env, int isBefore);
void sysLibCFunlockfileHookHandler(CPUState* env, int isBefore);
void sysLibCPosix_MemalignHookHandler(CPUState* env, int isBefore);
void sysLibCSigaltstackHookHandler(CPUState* env, int isBefore);
void sysLibCSem_CloseHookHandler(CPUState* env, int isBefore);
void sysLibCAtollHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Rwlock_TimedrdlockHookHandler(CPUState* env, int isBefore);
void sysLibCFcntlHookHandler(CPUState* env, int isBefore);
void sysLibCInet_Nsap_AddrHookHandler(CPUState* env, int isBefore);
void sysLibCArc4Random_StirHookHandler(CPUState* env, int isBefore);
void sysLibCOpenlog_RHookHandler(CPUState* env, int isBefore);
void sysLibCMemalignHookHandler(CPUState* env, int isBefore);
void sysLibCLstatHookHandler(CPUState* env, int isBefore);
void sysLibCInit_ModuleHookHandler(CPUState* env, int isBefore);
void sysLibCSetresgidHookHandler(CPUState* env, int isBefore);
void sysLibCTimelocalHookHandler(CPUState* env, int isBefore);
void sysLibCGetdtablesizeHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Attr_SetguardsizeHookHandler(CPUState* env, int isBefore);
void sysLibCSetsockoptHookHandler(CPUState* env, int isBefore);
void sysLibCFstatatHookHandler(CPUState* env, int isBefore);
void sysLibCInitgroupsHookHandler(CPUState* env, int isBefore);
void sysLibCRes_MkqueryHookHandler(CPUState* env, int isBefore);
void sysLibCSysv_SignalHookHandler(CPUState* env, int isBefore);
void sysLibCGethostentHookHandler(CPUState* env, int isBefore);
void sysLibCCloselogHookHandler(CPUState* env, int isBefore);
void sysLibCFree_Malloc_Leak_InfoHookHandler(CPUState* env, int isBefore);
void sysLibCStrftimeHookHandler(CPUState* env, int isBefore);
void sysLibCMbsinitHookHandler(CPUState* env, int isBefore);
void sysLibCTzsetHookHandler(CPUState* env, int isBefore);
void sysLibCTime2PosixHookHandler(CPUState* env, int isBefore);
void sysLibCStrxfrmHookHandler(CPUState* env, int isBefore);
void sysLibCChmodHookHandler(CPUState* env, int isBefore);
void sysLibCSetxattrHookHandler(CPUState* env, int isBefore);
void sysLibCFdprintfHookHandler(CPUState* env, int isBefore);
void sysLibCShutdownHookHandler(CPUState* env, int isBefore);
void sysLibCPreadHookHandler(CPUState* env, int isBefore);
void sysLibCPollHookHandler(CPUState* env, int isBefore);
void sysLibCUngetwcHookHandler(CPUState* env, int isBefore);
void sysLibCPutwHookHandler(CPUState* env, int isBefore);
void sysLibCSigprocmaskHookHandler(CPUState* env, int isBefore);
void sysLibCRaiseHookHandler(CPUState* env, int isBefore);
void sysLibCPutsHookHandler(CPUState* env, int isBefore);
void sysLibCSigactionHookHandler(CPUState* env, int isBefore);
void sysLibCNanosleepHookHandler(CPUState* env, int isBefore);
void sysLibCPutcHookHandler(CPUState* env, int isBefore);
void sysLibCDupHookHandler(CPUState* env, int isBefore);
void sysLibCStrtoumaxHookHandler(CPUState* env, int isBefore);
void sysLibCMbrtowcHookHandler(CPUState* env, int isBefore);
void sysLibCStrsignalHookHandler(CPUState* env, int isBefore);
void sysLibCMktimeHookHandler(CPUState* env, int isBefore);
void sysLibCDlmalloc_StatsHookHandler(CPUState* env, int isBefore);
void sysLibCCtime64_RHookHandler(CPUState* env, int isBefore);
void sysLibCExecvpHookHandler(CPUState* env, int isBefore);
void sysLibCMbsrtowcsHookHandler(CPUState* env, int isBefore);
void sysLibCStrtok_RHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Attr_SetschedparamHookHandler(CPUState* env, int isBefore);
void sysLibCWcswidthHookHandler(CPUState* env, int isBefore);
void sysLibCExecveHookHandler(CPUState* env, int isBefore);
void sysLibCFputwsHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Attr_SetstackaddrHookHandler(CPUState* env, int isBefore);
void sysLibCDrand48HookHandler(CPUState* env, int isBefore);
void sysLibCMadviseHookHandler(CPUState* env, int isBefore);
void sysLibCMountHookHandler(CPUState* env, int isBefore);
void sysLibCGetrusageHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Attr_GetschedpolicyHookHandler(CPUState* env, int isBefore);
void sysLibCGetgrnamHookHandler(CPUState* env, int isBefore);
void sysLibCIoprio_GetHookHandler(CPUState* env, int isBefore);
void sysLibCGetpwuidHookHandler(CPUState* env, int isBefore);
void sysLibCVsprintfHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Rwlock_UnlockHookHandler(CPUState* env, int isBefore);
void sysLibCRenameHookHandler(CPUState* env, int isBefore);
void sysLibCMallocHookHandler(CPUState* env, int isBefore);
void sysLibCDlmemalignHookHandler(CPUState* env, int isBefore);
void sysLibCWcwidthHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_GetcpuclockidHookHandler(CPUState* env, int isBefore);
void sysLibCReadvHookHandler(CPUState* env, int isBefore);
void sysLibCPrctlHookHandler(CPUState* env, int isBefore);
void sysLibCRes_QueryHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Attr_SetscopeHookHandler(CPUState* env, int isBefore);
void sysLibCDlmalloc_Walk_HeapHookHandler(CPUState* env, int isBefore);
void sysLibCSched_GetparamHookHandler(CPUState* env, int isBefore);
void sysLibCGetcHookHandler(CPUState* env, int isBefore);
void sysLibCMunlockHookHandler(CPUState* env, int isBefore);
void sysLibCVsyslog_RHookHandler(CPUState* env, int isBefore);
void sysLibCRecvmsgHookHandler(CPUState* env, int isBefore);
void sysLibCTowlowerHookHandler(CPUState* env, int isBefore);
void sysLibCDlmalloptHookHandler(CPUState* env, int isBefore);
void sysLibCGetsHookHandler(CPUState* env, int isBefore);
void sysLibCWaitpidHookHandler(CPUState* env, int isBefore);
void sysLibCOptargHookHandler(CPUState* env, int isBefore);
void sysLibCTdestroyHookHandler(CPUState* env, int isBefore);
void sysLibCLongjmpHookHandler(CPUState* env, int isBefore);
void sysLibCGetusershellHookHandler(CPUState* env, int isBefore);
void sysLibCAsctime64HookHandler(CPUState* env, int isBefore);
void sysLibCFdopendirHookHandler(CPUState* env, int isBefore);
void sysLibCIsgraphHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Rwlock_RdlockHookHandler(CPUState* env, int isBefore);
void sysLibCCallocHookHandler(CPUState* env, int isBefore);
void sysLibCSetbufHookHandler(CPUState* env, int isBefore);
void sysLibCUnlinkatHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Attr_GetguardsizeHookHandler(CPUState* env, int isBefore);
void sysLibCIswprintHookHandler(CPUState* env, int isBefore);
void sysLibCSetitimerHookHandler(CPUState* env, int isBefore);
void sysLibCClearenvHookHandler(CPUState* env, int isBefore);
void sysLibCSigblockHookHandler(CPUState* env, int isBefore);
void sysLibCNrand48HookHandler(CPUState* env, int isBefore);
void sysLibCDn_ExpandHookHandler(CPUState* env, int isBefore);
void sysLibCFts_OpenHookHandler(CPUState* env, int isBefore);
void sysLibCPutwcharHookHandler(CPUState* env, int isBefore);
void sysLibCLseekHookHandler(CPUState* env, int isBefore);
void sysLibCWcpcpyHookHandler(CPUState* env, int isBefore);
void sysLibCMallinfoHookHandler(CPUState* env, int isBefore);
void sysLibCFlistxattrHookHandler(CPUState* env, int isBefore);
void sysLibCWmemcmpHookHandler(CPUState* env, int isBefore);
void sysLibCDlmalloc_TrimHookHandler(CPUState* env, int isBefore);
void sysLibCWcslcatHookHandler(CPUState* env, int isBefore);
void sysLibCKillHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Condattr_DestroyHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Mutexattr_GetpsharedHookHandler(CPUState* env, int isBefore);
void sysLibCFflushHookHandler(CPUState* env, int isBefore);
void sysLibCClock_GetresHookHandler(CPUState* env, int isBefore);
void sysLibCSem_DestroyHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Attr_DestroyHookHandler(CPUState* env, int isBefore);
void sysLibCMmapHookHandler(CPUState* env, int isBefore);
void sysLibCTimer_DeleteHookHandler(CPUState* env, int isBefore);
void sysLibCPtsnameHookHandler(CPUState* env, int isBefore);
void sysLibCSem_InitHookHandler(CPUState* env, int isBefore);
void sysLibCSetenvHookHandler(CPUState* env, int isBefore);
void sysLibCOptoptHookHandler(CPUState* env, int isBefore);
void sysLibCLchownHookHandler(CPUState* env, int isBefore);
void sysLibCReallocHookHandler(CPUState* env, int isBefore);
void sysLibCIoprio_SetHookHandler(CPUState* env, int isBefore);
void sysLibCH_ErrlistHookHandler(CPUState* env, int isBefore);
void sysLibCDelete_ModuleHookHandler(CPUState* env, int isBefore);
void sysLibCWcspbrkHookHandler(CPUState* env, int isBefore);
void sysLibCReadHookHandler(CPUState* env, int isBefore);
void sysLibCIswcntrlHookHandler(CPUState* env, int isBefore);
void sysLibCToasciiHookHandler(CPUState* env, int isBefore);
void sysLibCHstrerrorHookHandler(CPUState* env, int isBefore);
void sysLibCGetnetbyaddrHookHandler(CPUState* env, int isBefore);
void sysLibCCacheflushHookHandler(CPUState* env, int isBefore);
void sysLibCCtimeHookHandler(CPUState* env, int isBefore);
void sysLibCDaemonHookHandler(CPUState* env, int isBefore);
void sysLibCStrstrHookHandler(CPUState* env, int isBefore);
void sysLibCRenameatHookHandler(CPUState* env, int isBefore);
void sysLibCFsyncHookHandler(CPUState* env, int isBefore);
void sysLibCMemmoveHookHandler(CPUState* env, int isBefore);
void sysLibCInet_AtonHookHandler(CPUState* env, int isBefore);
void sysLibCIswpunctHookHandler(CPUState* env, int isBefore);
void sysLibCSetegidHookHandler(CPUState* env, int isBefore);
void sysLibCTimer_CreateHookHandler(CPUState* env, int isBefore);
void sysLibCBsd_SignalHookHandler(CPUState* env, int isBefore);
void sysLibCStrcmpHookHandler(CPUState* env, int isBefore);
void sysLibCTempnamHookHandler(CPUState* env, int isBefore);
void sysLibCTmpfileHookHandler(CPUState* env, int isBefore);
void sysLibCRegcompHookHandler(CPUState* env, int isBefore);
void sysLibCLldivHookHandler(CPUState* env, int isBefore);
void sysLibCToupperHookHandler(CPUState* env, int isBefore);
void sysLibCFgetcHookHandler(CPUState* env, int isBefore);
void sysLibCPcloseHookHandler(CPUState* env, int isBefore);
void sysLibCMrand48HookHandler(CPUState* env, int isBefore);
void sysLibCFtruncate64HookHandler(CPUState* env, int isBefore);
void sysLibCReaddirHookHandler(CPUState* env, int isBefore);
void sysLibCSeed48HookHandler(CPUState* env, int isBefore);
void sysLibCGetresuidHookHandler(CPUState* env, int isBefore);
void sysLibCDaylightHookHandler(CPUState* env, int isBefore);
void sysLibCGetloginHookHandler(CPUState* env, int isBefore);
void sysLibCDlcallocHookHandler(CPUState* env, int isBefore);
void sysLibCFgetsHookHandler(CPUState* env, int isBefore);
void sysLibCGetgidHookHandler(CPUState* env, int isBefore);
void sysLibCSem_GetvalueHookHandler(CPUState* env, int isBefore);
void sysLibCTgkillHookHandler(CPUState* env, int isBefore);
void sysLibCSem_TimedwaitHookHandler(CPUState* env, int isBefore);
void sysLibCSched_SetaffinityHookHandler(CPUState* env, int isBefore);
void sysLibCArc4Random_BufHookHandler(CPUState* env, int isBefore);
void sysLibCFremovexattrHookHandler(CPUState* env, int isBefore);
void sysLibCFtellHookHandler(CPUState* env, int isBefore);
void sysLibCExitHookHandler(CPUState* env, int isBefore);
void sysLibCTtyname_RHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_SetspecificHookHandler(CPUState* env, int isBefore);
void sysLibCAsctimeHookHandler(CPUState* env, int isBefore);
void sysLibCInotify_Rm_WatchHookHandler(CPUState* env, int isBefore);
void sysLibCSigsetjmpHookHandler(CPUState* env, int isBefore);
void sysLibCMbstowcsHookHandler(CPUState* env, int isBefore);
void sysLibCSetrlimitHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_ExitHookHandler(CPUState* env, int isBefore);
void sysLibCGetitimerHookHandler(CPUState* env, int isBefore);
void sysLibCFchmodatHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Rwlock_TrywrlockHookHandler(CPUState* env, int isBefore);
void sysLibCGmtimeHookHandler(CPUState* env, int isBefore);
void sysLibCSymlinkHookHandler(CPUState* env, int isBefore);
void sysLibCPututlineHookHandler(CPUState* env, int isBefore);
void sysLibCDirfdHookHandler(CPUState* env, int isBefore);
void sysLibCGetgrgidHookHandler(CPUState* env, int isBefore);
void sysLibCTimer_GettimeHookHandler(CPUState* env, int isBefore);
void sysLibCGethostnameHookHandler(CPUState* env, int isBefore);
void sysLibCGetnameinfoHookHandler(CPUState* env, int isBefore);
void sysLibCSysinfoHookHandler(CPUState* env, int isBefore);
void sysLibCStrtotimevalHookHandler(CPUState* env, int isBefore);
void sysLibCMsyncHookHandler(CPUState* env, int isBefore);
void sysLibCSetusershellHookHandler(CPUState* env, int isBefore);
void sysLibCMemswapHookHandler(CPUState* env, int isBefore);
void sysLibCSiginterruptHookHandler(CPUState* env, int isBefore);
void sysLibCIswdigitHookHandler(CPUState* env, int isBefore);
void sysLibCStrcpyHookHandler(CPUState* env, int isBefore);
void sysLibCBsearchHookHandler(CPUState* env, int isBefore);
void sysLibCReadlinkHookHandler(CPUState* env, int isBefore);
void sysLibCDlmalloc_FootprintHookHandler(CPUState* env, int isBefore);
void sysLibCWmemmoveHookHandler(CPUState* env, int isBefore);
void sysLibCEther_AtonHookHandler(CPUState* env, int isBefore);
void sysLibCArc4RandomHookHandler(CPUState* env, int isBefore);
void sysLibCDlfreeHookHandler(CPUState* env, int isBefore);
void sysLibCUmount2HookHandler(CPUState* env, int isBefore);
void sysLibCWcscasecmpHookHandler(CPUState* env, int isBefore);
void sysLibCIsprintHookHandler(CPUState* env, int isBefore);
void sysLibCGetpgidHookHandler(CPUState* env, int isBefore);
void sysLibCDlvallocHookHandler(CPUState* env, int isBefore);
void sysLibCFopenHookHandler(CPUState* env, int isBefore);
void sysLibCMemccpyHookHandler(CPUState* env, int isBefore);
void sysLibCPutenvHookHandler(CPUState* env, int isBefore);
void sysLibCFdopenHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Key_CreateHookHandler(CPUState* env, int isBefore);
void sysLibCRemovexattrHookHandler(CPUState* env, int isBefore);
void sysLibCWcslenHookHandler(CPUState* env, int isBefore);
void sysLibCDlindependent_ComallocHookHandler(CPUState* env, int isBefore);
void sysLibCWcsncatHookHandler(CPUState* env, int isBefore);
void sysLibCRmdirHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Mutexattr_DestroyHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Cond_TimedwaitHookHandler(CPUState* env, int isBefore);
void sysLibCForkHookHandler(CPUState* env, int isBefore);
void sysLibCMalloc_Debug_InitHookHandler(CPUState* env, int isBefore);
void sysLibCStrtoimaxHookHandler(CPUState* env, int isBefore);
void sysLibCAlphasortHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_SetschedparamHookHandler(CPUState* env, int isBefore);
void sysLibCGetenvHookHandler(CPUState* env, int isBefore);
void sysLibCAtoiHookHandler(CPUState* env, int isBefore);
void sysLibCLinkHookHandler(CPUState* env, int isBefore);
void sysLibCPtraceHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Mutex_UnlockHookHandler(CPUState* env, int isBefore);
void sysLibCGethostbyname_RHookHandler(CPUState* env, int isBefore);
void sysLibCStrdupHookHandler(CPUState* env, int isBefore);
void sysLibCUnlockptHookHandler(CPUState* env, int isBefore);
void sysLibCGetnetbynameHookHandler(CPUState* env, int isBefore);
void sysLibCCpuacct_AddHookHandler(CPUState* env, int isBefore);
void sysLibCErand48HookHandler(CPUState* env, int isBefore);
void sysLibCSbrkHookHandler(CPUState* env, int isBefore);
void sysLibCWait3HookHandler(CPUState* env, int isBefore);
void sysLibCGetpwuid_RHookHandler(CPUState* env, int isBefore);
void sysLibCSched_SetschedulerHookHandler(CPUState* env, int isBefore);
void sysLibCFreeaddrinfoHookHandler(CPUState* env, int isBefore);
void sysLibCStrspnHookHandler(CPUState* env, int isBefore);
void sysLibCTimeHookHandler(CPUState* env, int isBefore);
void sysLibCUngetcHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Rwlock_InitHookHandler(CPUState* env, int isBefore);
void sysLibCSscanfHookHandler(CPUState* env, int isBefore);
void sysLibCMktime64HookHandler(CPUState* env, int isBefore);
void sysLibCCreatHookHandler(CPUState* env, int isBefore);
void sysLibCStrndupHookHandler(CPUState* env, int isBefore);
void sysLibCSyscallHookHandler(CPUState* env, int isBefore);
void sysLibCFreadHookHandler(CPUState* env, int isBefore);
void sysLibCFtelloHookHandler(CPUState* env, int isBefore);
void sysLibCRemoveHookHandler(CPUState* env, int isBefore);
void sysLibCInet_PtonHookHandler(CPUState* env, int isBefore);
void sysLibCWctypeHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Mutexattr_SettypeHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Cond_DestroyHookHandler(CPUState* env, int isBefore);
void sysLibCPread64HookHandler(CPUState* env, int isBefore);
void sysLibCIsdigitHookHandler(CPUState* env, int isBefore);
void sysLibCTimezoneHookHandler(CPUState* env, int isBefore);
void sysLibCIspunctHookHandler(CPUState* env, int isBefore);
void sysLibCFstatfsHookHandler(CPUState* env, int isBefore);
void sysLibCFwscanfHookHandler(CPUState* env, int isBefore);
void sysLibCMemmemHookHandler(CPUState* env, int isBefore);
void sysLibCTmpnamHookHandler(CPUState* env, int isBefore);
void sysLibCTkillHookHandler(CPUState* env, int isBefore);
void sysLibCSetpriorityHookHandler(CPUState* env, int isBefore);
void sysLibCGai_StrerrorHookHandler(CPUState* env, int isBefore);
void sysLibCGetoptHookHandler(CPUState* env, int isBefore);
void sysLibCMkstempHookHandler(CPUState* env, int isBefore);
void sysLibCVfscanfHookHandler(CPUState* env, int isBefore);
void sysLibCTdeleteHookHandler(CPUState* env, int isBefore);
void sysLibCMincoreHookHandler(CPUState* env, int isBefore);
void sysLibCNiceHookHandler(CPUState* env, int isBefore);
void sysLibCSendfileHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Cond_Timedwait_MonotonicHookHandler(CPUState* env, int isBefore);
void sysLibCStatHookHandler(CPUState* env, int isBefore);
void sysLibCTruncateHookHandler(CPUState* env, int isBefore);
void sysLibCKillpgHookHandler(CPUState* env, int isBefore);
void sysLibCSigsuspendHookHandler(CPUState* env, int isBefore);
void sysLibCRegerrorHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_Cond_BroadcastHookHandler(CPUState* env, int isBefore);
void sysLibCClosedirHookHandler(CPUState* env, int isBefore);
void sysLibCGetegidHookHandler(CPUState* env, int isBefore);
void sysLibCWcsdupHookHandler(CPUState* env, int isBefore);
void sysLibCRes_InitHookHandler(CPUState* env, int isBefore);
void sysLibCFwprintfHookHandler(CPUState* env, int isBefore);
void sysLibCSetlinebufHookHandler(CPUState* env, int isBefore);
void sysLibCGetuidHookHandler(CPUState* env, int isBefore);
void sysLibCFts_ReadHookHandler(CPUState* env, int isBefore);
void sysLibCGetservent_RHookHandler(CPUState* env, int isBefore);
void sysLibCDifftimeHookHandler(CPUState* env, int isBefore);
void sysLibCRegfreeHookHandler(CPUState* env, int isBefore);
void sysLibCWcscspnHookHandler(CPUState* env, int isBefore);
void sysLibCMd5_InitHookHandler(CPUState* env, int isBefore);
void sysLibCFpathconfHookHandler(CPUState* env, int isBefore);
void sysLibCChownHookHandler(CPUState* env, int isBefore);
void sysLibCH_NerrHookHandler(CPUState* env, int isBefore);
void sysLibCReaddir_RHookHandler(CPUState* env, int isBefore);
void sysLibCPthread_SelfHookHandler(CPUState* env, int isBefore);

int startOfLibCCalls(int curPC, int libCStartAddr);

sysLibHookHandler hookLibCCalls(int curPC, int libCStartAddr, CPUState* env);

#ifdef __cplusplus
}
#endif

#endif
        