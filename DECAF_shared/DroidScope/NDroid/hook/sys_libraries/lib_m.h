
#ifndef _LIB_M_HOOK_H
#define _LIB_M_HOOK_H
#ifdef __cplusplus

extern "C"
{
#endif
        
#include "sys_lib_hook.h"

#define COSHF_OFFSET_M 0x3f48
#define CBRTF_OFFSET_M 0xbce8
#define NEARBYINT_OFFSET_M 0xf9f8
#define DREMF_OFFSET_M 0x114dc
#define EXPM1F_OFFSET_M 0xdf50
#define FINITEF_OFFSET_M 0xe2d4
#define ACOSH_OFFSET_M 0x30d8
#define Y1_OFFSET_M 0x6060
#define Y0_OFFSET_M 0x5338
#define LOGBF_OFFSET_M 0xf6b8
#define FABSF_OFFSET_M 0xe22c
#define LRINTF_OFFSET_M 0xf754
#define ILOGB_OFFSET_M 0xedcc
#define FREXP_OFFSET_M 0x11500
#define ROUNDF_OFFSET_M 0x106e8
#define CBRT_OFFSET_M 0xbb98
#define MODFF_OFFSET_M 0xf838
#define SCALBF_OFFSET_M 0xa120
#define LGAMMAF_OFFSET_M 0x7be8
#define SCALBNF_OFFSET_M 0x11860
#define YN_OFFSET_M 0x6c90
#define TGAMMA_OFFSET_M 0x2728
#define SCALBN_OFFSET_M 0x11700
#define CEIL_OFFSET_M 0xbe00
#define FMAF_OFFSET_M 0xe958
#define YNF_OFFSET_M 0x71a4
#define SCALBLNF_OFFSET_M 0x116f4
#define RINT_OFFSET_M 0x10438
#define FMOD_OFFSET_M 0x4548
#define ROUND_OFFSET_M 0x10658
#define JNF_OFFSET_M 0x6ec8
#define COSF_OFFSET_M 0xc300
#define NEXTAFTERF_OFFSET_M 0xfb58
#define REMQUOF_OFFSET_M 0x101a0
#define J0_OFFSET_M 0x50f0
#define J1_OFFSET_M 0x5e48
#define COSH_OFFSET_M 0x3e18
#define LOGF_OFFSET_M 0x87e0
#define FMINL_OFFSET_M 0xecf4
#define HYPOT_OFFSET_M 0x4b00
#define LOGB_OFFSET_M 0xf620
#define SINHF_OFFSET_M 0xa380
#define ACOSF_OFFSET_M 0x2e68
#define SINCOS_OFFSET_M 0x1fd8
#define ASIN_OFFSET_M 0x3320
#define ISNAN_OFFSET_M 0x11588
#define SCALB_OFFSET_M 0xa018
#define NANL_OFFSET_M 0xf998
#define Y1F_OFFSET_M 0x6684
#define NANF_OFFSET_M 0xf9cc
#define ERFCF_OFFSET_M 0xd4c8
#define LLROUNDL_OFFSET_M 0xf038
#define LDEXPF_OFFSET_M 0x116e0
#define ATAN2F_OFFSET_M 0x3a20
#define LLROUNDF_OFFSET_M 0xf028
#define MODF_OFFSET_M 0x115fc
#define FMAX_OFFSET_M 0xe980
#define TGAMMAF_OFFSET_M 0x11230
#define LOG1PF_OFFSET_M 0xf370
#define COPYSIGN_OFFSET_M 0xc1f8
#define SIGNIFICANDF_OFFSET_M 0x10848
#define ILOGBL_OFFSET_M 0xeeb8
#define JN_OFFSET_M 0x68a0
#define DREM_OFFSET_M 0x114d8
#define TRUNCF_OFFSET_M 0x11340
#define ACOSHF_OFFSET_M 0x3210
#define SINF_OFFSET_M 0x10970
#define ILOGBF_OFFSET_M 0xee5c
#define REMAINDER_OFFSET_M 0x9df8
#define TRUNC_OFFSET_M 0x11258
#define EXPM1_OFFSET_M 0xdbf0
#define LROUNDF_OFFSET_M 0xf7c8
#define ATANHF_OFFSET_M 0x3d40
#define LROUNDL_OFFSET_M 0xf7e0
#define ERFF_OFFSET_M 0xd0f8
#define SIGNGAM_OFFSET_M 0x16000
#define ERFC_OFFSET_M 0xcb98
#define FMIN_OFFSET_M 0xeb64
#define LLROUND_OFFSET_M 0xf018
#define ACOS_OFFSET_M 0x2b98
#define GAMMA_OFFSET_M 0x4ad8
#define ROUNDL_OFFSET_M 0x10778
#define SINH_OFFSET_M 0xa210
#define FLOORF_OFFSET_M 0xe448
#define FMAXF_OFFSET_M 0xea48
#define J1F_OFFSET_M 0x64a4
#define POW_OFFSET_M 0x8a18
#define FLOORL_OFFSET_M 0xe510
#define FMAXL_OFFSET_M 0xeb10
#define FABSL_OFFSET_M 0x114ec
#define LDEXP_OFFSET_M 0x116f0
#define SQRTF_OFFSET_M 0xa6a0
#define HYPOTF_OFFSET_M 0x4d0c
#define COPYSIGNF_OFFSET_M 0xc208
#define LOG_OFFSET_M 0x8330
#define FDIMF_OFFSET_M 0xe280
#define EXP2_OFFSET_M 0xd8c0
#define LROUND_OFFSET_M 0xf770
#define FMINF_OFFSET_M 0xec2c
#define LOG10_OFFSET_M 0x85e0
#define TANHF_OFFSET_M 0x11148
#define GAMMA_R_OFFSET_M 0x4ae8
#define ASINH_OFFSET_M 0xb4c0
#define NEXTTOWARDF_OFFSET_M 0xfc2c
#define NEARBYINTF_OFFSET_M 0xf9fc
#define ASINF_OFFSET_M 0x35a0
#define COS_OFFSET_M 0xc218
#define J0F_OFFSET_M 0x57cc
#define LLRINT_OFFSET_M 0xeff8
#define LRINT_OFFSET_M 0xf73c
#define LLRINTF_OFFSET_M 0xf008
#define TRUNCL_OFFSET_M 0x113d0
#define TANH_OFFSET_M 0x11070
#define FDIM_OFFSET_M 0xe238
#define TANF_OFFSET_M 0x10d40
#define SCALBLNL_OFFSET_M 0x116f8
#define RINTF_OFFSET_M 0x105ac
#define LGAMMA_OFFSET_M 0x72dc
#define ERF_OFFSET_M 0xc658
#define Y0F_OFFSET_M 0x59d0
#define LGAMMAF_R_OFFSET_M 0x7bf8
#define FMA_OFFSET_M 0xe6f8
#define LOG1P_OFFSET_M 0xf048
#define EXPF_OFFSET_M 0x4308
#define LOG10F_OFFSET_M 0x86f8
#define LGAMMA_R_OFFSET_M 0x72f0
#define TAN_OFFSET_M 0x10c90
#define ATANF_OFFSET_M 0xb998
#define FABS_OFFSET_M 0x114f4
#define FLOOR_OFFSET_M 0xe2e8
#define ATANH_OFFSET_M 0x3c18
#define COPYSIGNL_OFFSET_M 0x114e0
#define SQRT_OFFSET_M 0xa4b0
#define GAMMAF_R_OFFSET_M 0x4afc
#define FMODF_OFFSET_M 0x48ec
#define FINITE_OFFSET_M 0xe2c0
#define SIN_OFFSET_M 0x10870
#define NEXTAFTER_OFFSET_M 0xfa00
#define FREXPF_OFFSET_M 0xed48
#define CEILF_OFFSET_M 0xbf58
#define ATAN_OFFSET_M 0xb740
#define CEILL_OFFSET_M 0xc010
#define GAMMAF_OFFSET_M 0x4aec
#define REMAINDERF_OFFSET_M 0x9f20
#define ISNANF_OFFSET_M 0x115cc
#define SIGNIFICAND_OFFSET_M 0x10818
#define EXP2F_OFFSET_M 0xda88
#define POWF_OFFSET_M 0x9258
#define ATAN2_OFFSET_M 0x37c0
#define ASINHF_OFFSET_M 0xb608
#define EXP_OFFSET_M 0x4058
#define REMQUO_OFFSET_M 0xfd40
#define SINCOSF_OFFSET_M 0x2028

void sysLibMCoshfHookHandler(CPUState* env, int isBefore);
void sysLibMCbrtfHookHandler(CPUState* env, int isBefore);
void sysLibMNearbyintHookHandler(CPUState* env, int isBefore);
void sysLibMDremfHookHandler(CPUState* env, int isBefore);
void sysLibMExpm1FHookHandler(CPUState* env, int isBefore);
void sysLibMFinitefHookHandler(CPUState* env, int isBefore);
void sysLibMAcoshHookHandler(CPUState* env, int isBefore);
void sysLibMY1HookHandler(CPUState* env, int isBefore);
void sysLibMY0HookHandler(CPUState* env, int isBefore);
void sysLibMLogbfHookHandler(CPUState* env, int isBefore);
void sysLibMFabsfHookHandler(CPUState* env, int isBefore);
void sysLibMLrintfHookHandler(CPUState* env, int isBefore);
void sysLibMIlogbHookHandler(CPUState* env, int isBefore);
void sysLibMFrexpHookHandler(CPUState* env, int isBefore);
void sysLibMRoundfHookHandler(CPUState* env, int isBefore);
void sysLibMCbrtHookHandler(CPUState* env, int isBefore);
void sysLibMModffHookHandler(CPUState* env, int isBefore);
void sysLibMScalbfHookHandler(CPUState* env, int isBefore);
void sysLibMLgammafHookHandler(CPUState* env, int isBefore);
void sysLibMScalbnfHookHandler(CPUState* env, int isBefore);
void sysLibMYnHookHandler(CPUState* env, int isBefore);
void sysLibMTgammaHookHandler(CPUState* env, int isBefore);
void sysLibMScalbnHookHandler(CPUState* env, int isBefore);
void sysLibMCeilHookHandler(CPUState* env, int isBefore);
void sysLibMFmafHookHandler(CPUState* env, int isBefore);
void sysLibMYnfHookHandler(CPUState* env, int isBefore);
void sysLibMScalblnfHookHandler(CPUState* env, int isBefore);
void sysLibMRintHookHandler(CPUState* env, int isBefore);
void sysLibMFmodHookHandler(CPUState* env, int isBefore);
void sysLibMRoundHookHandler(CPUState* env, int isBefore);
void sysLibMJnfHookHandler(CPUState* env, int isBefore);
void sysLibMCosfHookHandler(CPUState* env, int isBefore);
void sysLibMNextafterfHookHandler(CPUState* env, int isBefore);
void sysLibMRemquofHookHandler(CPUState* env, int isBefore);
void sysLibMJ0HookHandler(CPUState* env, int isBefore);
void sysLibMJ1HookHandler(CPUState* env, int isBefore);
void sysLibMCoshHookHandler(CPUState* env, int isBefore);
void sysLibMLogfHookHandler(CPUState* env, int isBefore);
void sysLibMFminlHookHandler(CPUState* env, int isBefore);
void sysLibMHypotHookHandler(CPUState* env, int isBefore);
void sysLibMLogbHookHandler(CPUState* env, int isBefore);
void sysLibMSinhfHookHandler(CPUState* env, int isBefore);
void sysLibMAcosfHookHandler(CPUState* env, int isBefore);
void sysLibMSincosHookHandler(CPUState* env, int isBefore);
void sysLibMAsinHookHandler(CPUState* env, int isBefore);
void sysLibMIsnanHookHandler(CPUState* env, int isBefore);
void sysLibMScalbHookHandler(CPUState* env, int isBefore);
void sysLibMNanlHookHandler(CPUState* env, int isBefore);
void sysLibMY1FHookHandler(CPUState* env, int isBefore);
void sysLibMNanfHookHandler(CPUState* env, int isBefore);
void sysLibMErfcfHookHandler(CPUState* env, int isBefore);
void sysLibMLlroundlHookHandler(CPUState* env, int isBefore);
void sysLibMLdexpfHookHandler(CPUState* env, int isBefore);
void sysLibMAtan2FHookHandler(CPUState* env, int isBefore);
void sysLibMLlroundfHookHandler(CPUState* env, int isBefore);
void sysLibMModfHookHandler(CPUState* env, int isBefore);
void sysLibMFmaxHookHandler(CPUState* env, int isBefore);
void sysLibMTgammafHookHandler(CPUState* env, int isBefore);
void sysLibMLog1PfHookHandler(CPUState* env, int isBefore);
void sysLibMCopysignHookHandler(CPUState* env, int isBefore);
void sysLibMSignificandfHookHandler(CPUState* env, int isBefore);
void sysLibMIlogblHookHandler(CPUState* env, int isBefore);
void sysLibMJnHookHandler(CPUState* env, int isBefore);
void sysLibMDremHookHandler(CPUState* env, int isBefore);
void sysLibMTruncfHookHandler(CPUState* env, int isBefore);
void sysLibMAcoshfHookHandler(CPUState* env, int isBefore);
void sysLibMSinfHookHandler(CPUState* env, int isBefore);
void sysLibMIlogbfHookHandler(CPUState* env, int isBefore);
void sysLibMRemainderHookHandler(CPUState* env, int isBefore);
void sysLibMTruncHookHandler(CPUState* env, int isBefore);
void sysLibMExpm1HookHandler(CPUState* env, int isBefore);
void sysLibMLroundfHookHandler(CPUState* env, int isBefore);
void sysLibMAtanhfHookHandler(CPUState* env, int isBefore);
void sysLibMLroundlHookHandler(CPUState* env, int isBefore);
void sysLibMErffHookHandler(CPUState* env, int isBefore);
void sysLibMSigngamHookHandler(CPUState* env, int isBefore);
void sysLibMErfcHookHandler(CPUState* env, int isBefore);
void sysLibMFminHookHandler(CPUState* env, int isBefore);
void sysLibMLlroundHookHandler(CPUState* env, int isBefore);
void sysLibMAcosHookHandler(CPUState* env, int isBefore);
void sysLibMGammaHookHandler(CPUState* env, int isBefore);
void sysLibMRoundlHookHandler(CPUState* env, int isBefore);
void sysLibMSinhHookHandler(CPUState* env, int isBefore);
void sysLibMFloorfHookHandler(CPUState* env, int isBefore);
void sysLibMFmaxfHookHandler(CPUState* env, int isBefore);
void sysLibMJ1FHookHandler(CPUState* env, int isBefore);
void sysLibMPowHookHandler(CPUState* env, int isBefore);
void sysLibMFloorlHookHandler(CPUState* env, int isBefore);
void sysLibMFmaxlHookHandler(CPUState* env, int isBefore);
void sysLibMFabslHookHandler(CPUState* env, int isBefore);
void sysLibMLdexpHookHandler(CPUState* env, int isBefore);
void sysLibMSqrtfHookHandler(CPUState* env, int isBefore);
void sysLibMHypotfHookHandler(CPUState* env, int isBefore);
void sysLibMCopysignfHookHandler(CPUState* env, int isBefore);
void sysLibMLogHookHandler(CPUState* env, int isBefore);
void sysLibMFdimfHookHandler(CPUState* env, int isBefore);
void sysLibMExp2HookHandler(CPUState* env, int isBefore);
void sysLibMLroundHookHandler(CPUState* env, int isBefore);
void sysLibMFminfHookHandler(CPUState* env, int isBefore);
void sysLibMLog10HookHandler(CPUState* env, int isBefore);
void sysLibMTanhfHookHandler(CPUState* env, int isBefore);
void sysLibMGamma_RHookHandler(CPUState* env, int isBefore);
void sysLibMAsinhHookHandler(CPUState* env, int isBefore);
void sysLibMNexttowardfHookHandler(CPUState* env, int isBefore);
void sysLibMNearbyintfHookHandler(CPUState* env, int isBefore);
void sysLibMAsinfHookHandler(CPUState* env, int isBefore);
void sysLibMCosHookHandler(CPUState* env, int isBefore);
void sysLibMJ0FHookHandler(CPUState* env, int isBefore);
void sysLibMLlrintHookHandler(CPUState* env, int isBefore);
void sysLibMLrintHookHandler(CPUState* env, int isBefore);
void sysLibMLlrintfHookHandler(CPUState* env, int isBefore);
void sysLibMTrunclHookHandler(CPUState* env, int isBefore);
void sysLibMTanhHookHandler(CPUState* env, int isBefore);
void sysLibMFdimHookHandler(CPUState* env, int isBefore);
void sysLibMTanfHookHandler(CPUState* env, int isBefore);
void sysLibMScalblnlHookHandler(CPUState* env, int isBefore);
void sysLibMRintfHookHandler(CPUState* env, int isBefore);
void sysLibMLgammaHookHandler(CPUState* env, int isBefore);
void sysLibMErfHookHandler(CPUState* env, int isBefore);
void sysLibMY0FHookHandler(CPUState* env, int isBefore);
void sysLibMLgammaf_RHookHandler(CPUState* env, int isBefore);
void sysLibMFmaHookHandler(CPUState* env, int isBefore);
void sysLibMLog1PHookHandler(CPUState* env, int isBefore);
void sysLibMExpfHookHandler(CPUState* env, int isBefore);
void sysLibMLog10FHookHandler(CPUState* env, int isBefore);
void sysLibMLgamma_RHookHandler(CPUState* env, int isBefore);
void sysLibMTanHookHandler(CPUState* env, int isBefore);
void sysLibMAtanfHookHandler(CPUState* env, int isBefore);
void sysLibMFabsHookHandler(CPUState* env, int isBefore);
void sysLibMFloorHookHandler(CPUState* env, int isBefore);
void sysLibMAtanhHookHandler(CPUState* env, int isBefore);
void sysLibMCopysignlHookHandler(CPUState* env, int isBefore);
void sysLibMSqrtHookHandler(CPUState* env, int isBefore);
void sysLibMGammaf_RHookHandler(CPUState* env, int isBefore);
void sysLibMFmodfHookHandler(CPUState* env, int isBefore);
void sysLibMFiniteHookHandler(CPUState* env, int isBefore);
void sysLibMSinHookHandler(CPUState* env, int isBefore);
void sysLibMNextafterHookHandler(CPUState* env, int isBefore);
void sysLibMFrexpfHookHandler(CPUState* env, int isBefore);
void sysLibMCeilfHookHandler(CPUState* env, int isBefore);
void sysLibMAtanHookHandler(CPUState* env, int isBefore);
void sysLibMCeillHookHandler(CPUState* env, int isBefore);
void sysLibMGammafHookHandler(CPUState* env, int isBefore);
void sysLibMRemainderfHookHandler(CPUState* env, int isBefore);
void sysLibMIsnanfHookHandler(CPUState* env, int isBefore);
void sysLibMSignificandHookHandler(CPUState* env, int isBefore);
void sysLibMExp2FHookHandler(CPUState* env, int isBefore);
void sysLibMPowfHookHandler(CPUState* env, int isBefore);
void sysLibMAtan2HookHandler(CPUState* env, int isBefore);
void sysLibMAsinhfHookHandler(CPUState* env, int isBefore);
void sysLibMExpHookHandler(CPUState* env, int isBefore);
void sysLibMRemquoHookHandler(CPUState* env, int isBefore);
void sysLibMSincosfHookHandler(CPUState* env, int isBefore);

int startOfLibMCalls(int curPC, int libMStartAddr);

sysLibHookHandler hookLibMCalls(int curPC, int libMStartAddr, CPUState* env);

#ifdef __cplusplus
}
#endif

#endif
        