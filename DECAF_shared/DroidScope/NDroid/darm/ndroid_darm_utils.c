/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-9-22
 */
#include "ndroid_darm_utils.h"
#include <assert.h>

int darm_my_lsl(int value, int shift){
	assert(shift >= 0);
	if(shift == 0){
		return value;
	}else{
		return (value << shift);
	}
}

int darm_my_lsr(int value, int shift){
	assert(shift >= 0);
	if(shift == 0){
		return value;
	}else{
		return ((unsigned)value >> shift);
	}
}

int darm_my_asr(int value, int shift){
	assert(shift >= 0);
	if(shift == 0){
		return value;
	}else{
		if(value < 0){
			return value >> shift | ~(~0U >> shift);
		}else{
			return value >> shift;
		}
	}
}

int darm_my_ror(int value, int shift){
	assert(shift >= 0);
	if(shift == 0){
		return value;
	}else{
		return ((value >> shift)|(value << (32 - shift)));
	}
}

int darm_my_rrx(int value, int carry_in){
	if(carry_in == 0){
		return (value >> 1);
	}else{
		return ((value >> 1) | 0x80000000);
	}
}

int darm_shift(int value, int type, int imm, int carry_in){
	darm_sr_type myType = darm_decode_imm_shift(type, imm);
	int myImm = (myType == SRType_RRX) ? 1 : imm;
	int retValue = 0;

	if(myImm == 0){
		retValue = value;	
	}else{
		switch(myType){
			case SRType_LSL:
				retValue = darm_my_lsl(value, myImm);
				break;
			case SRType_LSR:
				retValue = darm_my_lsr(value, myImm);
				break;
			case SRType_ASR:
				retValue = darm_my_asr(value, myImm);
				break;
			case SRType_ROR:
				retValue = darm_my_ror(value, myImm);
				break;
			case SRType_RRX:
				retValue = darm_my_rrx(value, carry_in);
				break;
		}
	}

	return retValue;
}

darm_sr_type darm_decode_imm_shift(int type, int imm){
	darm_sr_type retType = SRType_INVALID;
	switch(type){
		case 0b00:
			retType = SRType_LSL;
			break;
		case 0b01:
			retType = SRType_LSR;
			break;
		case 0b10:
			retType = SRType_ASR;
			break;
		case 0b11:
			if(imm == 0){
				retType = SRType_RRX;
			}else{
				retType = SRType_ROR;
			}
			break;
	}
	return retType;
}

int darm_bit_count_16(int bit_string){
	int bitCount = 0;
	int i = 0;
	for(; i < 16; i++){
		if((bit_string & (0b1 << i)) == 1){
			bitCount++;
		}
	}
	return bitCount;
}

