/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-9-22
 */
#ifndef _NDROID_DARM_UTILS_H
#define _NDROID_DARM_UTILS_H

#ifdef __cplusplus

extern "C"
{
#endif

	typedef enum _darm_sr_type {
		SRType_LSL,
		SRType_LSR, 
		SRType_ASR,
		SRType_ROR,
		SRType_RRX,
		SRType_INVALID
	} darm_sr_type;

	int darm_shift(int value, int type, int imm, int carry_in);

	darm_sr_type darm_decode_imm_shift(int type, int imm);

	int darm_bit_count_16(int bit_string);

#ifdef __cplusplus
}
#endif

#endif
