/*
Copyright (c) 2013, Jurriaan Bremer
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
* Neither the name of the darm developer(s) nor the names of its
  contributors may be used to endorse or promote products derived from this
  software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "darm.h"
#include "darm-internal.h"
#include "thumb-tbl.h"

#define BITMSK_8 ((1 << 8) - 1)

static int thumb_disasm(darm_t *d, uint16_t w, CPUState* env)
{
    d->instr = thumb_instr_labels[w >> 8];
    d->instr_type = thumb_instr_types[w >> 8];

		/* NDROID START */
		int offset_addr = 0, address = 0, base = 0, i = 0;
		/* NDROID END */

    switch ((uint32_t) d->instr_type) {
    case T_THUMB_ONLY_IMM8:
        d->I = B_SET;
        d->imm = w & BITMSK_8;
        return 0;

    case T_THUMB_COND_BRANCH:
        d->cond = (w >> 8) & b1111;
        d->I = B_SET;
        d->imm = (uint32_t)(int8_t)(w & BITMSK_8) << 1;
        return 0;

    case T_THUMB_UNCOND_BRANCH:
        d->I = B_SET;
        d->imm = w & ((1 << 11) - 1);

        // manually sign-extend it
        if(((d->imm >> 10) & 1) != 0) {
            d->imm |= ~((1 << 11) - 1);
        }

        // finally, shift it one byte to the left
        d->imm <<= 1;
        return 0;

    case T_THUMB_SHIFT_IMM:
        d->Rd = (w >> 0) & b111;
        d->Rm = (w >> 3) & b111;
        d->shift = (w >> 6) & b11111;

				/* NDROID START */
				setRegTaint(d->Rd, d->Rm);
				/* NDROID END */

        // if the shift is zero and this is the lsl instruction, then this is
        // actually a mov instruction
        if(d->shift == 0 && d->instr == I_LSL) {
            d->instr = I_MOV;
        }
        else {
            // set the correct shift-type
            switch ((uint32_t) d->instr) {
            case I_ASR:
                d->shift_type = S_ASR;
                break;

            case I_LSL:
                d->shift_type = S_LSL;
                break;

            case I_LSR:
                d->shift_type = S_LSR;
                break;
            }
        }
        return 0;

    case T_THUMB_STACK:
        d->I = B_SET;
        d->imm = (w & BITMSK_8) << 2;
        d->Rn = SP;
        d->Rt = (w >> 8) & b111;
        d->U = B_SET;
        d->W = B_UNSET;
        d->P = B_SET;

				/* NDROID START */
				offset_addr = (d->W == 1) ? (env->regs[d->Rn] + d->imm)
					: (env->regs[d->Rn] - d->imm);
				address = offset_addr;
				if(d->instr == I_LDR){
					setMem4ToReg(d->Rt, address);
				}else{
					setRegToMem4(address, d->Rt);
				}
				/* NDROID END */
        return 0;

    case T_THUMB_LDR_PC:
        d->I = B_SET;
        d->imm = (w & BITMSK_8) << 2;
        d->Rn = PC;
        d->Rt = (w >> 8) & b111;
        d->U = B_SET;
        d->W = B_UNSET;
        d->P = B_SET;

				/* NDROID START */
				base = env->regs[PC] & 0b00;
				address = base + d->imm;
				setMem4ToReg(d->Rt, address);
				/* NDROID END */
        return 0;

    case T_THUMB_GPI:
        d->instr = type_gpi_instr_lookup[(w >> 6) & b1111];
        switch ((uint32_t) d->instr) {
        case I_AND: case I_EOR: case I_LSL: case I_LSR:
        case I_ASR: case I_ADC: case I_SBC: case I_ROR:
            d->Rd = d->Rn = w & b111;
            d->Rm = (w >> 3) & b111;

						/* NDROID START */
						addRegToReg(d->Rd, d->Rm);
						/* NDROID END */
            return 0;

        case I_TST: case I_CMP: case I_CMN:
            d->Rn = w & b111;
            d->Rm = (w >> 3) & b111;
            return 0;

        case I_RSB:
            d->I = B_SET;
            d->imm = 0;
            d->Rd = w & b111;
            d->Rn = (w >> 3) & b111;

						/* NDROID START */
						setRegToReg(d->Rd, d->Rn);
						/* NDROID END */
            return 0;

        case I_ORR: case I_BIC:
            d->Rn = w & b111;
            // fall-through as the mvn handler is almost the same, except
            // for parsing Rn

        case I_MVN:
            d->Rd = w & b111;
            d->Rm = (w >> 3) & b111;

						/* NDROID START */
						setRegToReg(d->Rd, d->Rm);
						/* NDROID END */
            return 0;

        case I_MUL:
            d->Rd = d->Rm = w & b111;
            d->Rn = (w >> 3) & b111;

						/* NDROID START */
						addRegToReg(d->Rd, d->Rn);
						/* NDROID END */
            return 0;
        }

    case T_THUMB_BRANCH_REG:
        d->instr = (w >> 7) & 1 ? I_BLX : I_BX;
        d->Rm = (w >> 3) & b1111;
        return 0;

    case T_THUMB_IT_HINTS:
        // one of the hints instructions (instructions that hint the cpu and
        // don't take any operands)
        if((w & b1111) == 0) {
            d->instr = type_hints_instr_lookup[(w >> 4) & b111];
            return d->instr == I_INVLD ? -1 : 0;
        }

        // if-then instruction
        d->instr = I_IT;
        d->mask = w & b1111;
        d->firstcond = (w >> 4) & b1111;
        return 0;

    case T_THUMB_HAS_IMM8:
        d->I = B_SET;
        d->imm = w & BITMSK_8;

        switch ((uint32_t) d->instr) {
        case I_ADD: case I_SUB:
            d->Rd = d->Rn = (w >> 8) & b111;
            return 0;

        case I_ADR:
            d->Rn = PC;
            d->U = B_SET;
            d->imm <<= 2;
            // fall-through as adr also has to set Rd

        case I_MOV:
            d->Rd = (w >> 8) & b111;
						
						/* NDROID START */
						setRegToReg(d->Rd, d->Rn);
						/* NDROID END */
            return 0;

        case I_CMP:
            d->Rn = (w >> 8) & b111;
            return 0;
        }

    case T_THUMB_EXTEND:
        d->instr = type_extend_instr_lookup[(w >> 6) & b11];
        d->Rd = w & b111;
        d->Rm = (w >> 3) & b111;

				/* NDROID START */
				setRegToReg(d->Rd, d->Rm);
				/* NDROID END */
        return 0;

    case T_THUMB_MOD_SP_IMM:
        d->instr = (w >> 7) & 1 ? I_SUB : I_ADD;
        d->Rd = d->Rn = SP;
        d->I = B_SET;
        d->imm = (w & 0x7f) << 2;
        return 0;

    case T_THUMB_3REG:
        d->Rd = (w >> 0) & b111;
        d->Rn = (w >> 3) & b111;
        d->Rm = (w >> 6) & b111;

				/* NDROID START */
				setRegToReg(d->Rd, d->Rn);
				addRegToReg(d->Rd, d->Rm);
				/* NDROID END */
        return 0;

    case T_THUMB_2REG_IMM:
        d->Rd = w & b111;
        d->Rn = (w >> 3) & b111;
        d->I = B_SET;
        d->imm = (w >> 6) & b111;

				/* NDROID START */
				setRegToReg(d->Rd, d->Rn);
				/* NDROID END */
        return 0;

    case T_THUMB_ADD_SP_IMM:
        d->I = B_SET;
        d->imm = (w & BITMSK_8) << 2;
        d->Rn = SP;
        d->Rd = (w >> 8) & b111;

				/* NDROID START */
				setRegToReg(d->Rd, SP);
				/* NDROID END */
        return 0;

    case T_THUMB_MOV4:
        // D is the 8th bit and has to become the 3th bit, to function as
        // highest bit for Rd
        d->Rd = ((w >> 4) & 8) | (w & b111);
        d->Rm = (w >> 3) & b1111;

				/* NDROID START */
				setRegToReg(d->Rd, d->Rm);
				/* NDROID END */
        return 0;

    case T_THUMB_RW_MEMI:
        d->Rt = w & b111;
        d->Rn = (w >> 3) & b111;
        d->I = B_SET;
        d->imm = (w >> 6) & b11111;

        // some instructions require some shifting for the immediate
        switch ((uint32_t) d->instr) {
        case I_LDR: case I_STR:
            d->imm <<= 2;
						
						/* NDROID START */
						offset_addr = env->regs[d->Rn] + d->imm;
						address = offset_addr;
						if(d->instr == I_LDR){
							setMem4ToReg(d->Rt, address);
						}else{
							setRegToMem4(address, d->Rt);
						}
						/* NDROID END */
            break;

        case I_LDRH: case I_STRH:
            d->imm <<= 1;

						/* NDROID START */
						offset_addr = env->regs[d->Rn] + d->imm;
						address = offset_addr;
						if(d->instr == I_LDRH){
							setMem2ToReg(d->Rt, address);
						}else{
							setRegToMem2(address, d->Rt);
						}
						/* NDROID END */
            break;
        }

        d->P = B_SET;
        d->U = B_SET;
        d->W = B_UNSET;
        return 0;

    case T_THUMB_RW_MEMO:
        d->Rt = (w >> 0) & b111;
        d->Rn = (w >> 3) & b111;
        d->Rm = (w >> 6) & b111;
        d->P = B_SET;
        d->U = B_SET;
        d->W = B_UNSET;

				/* NDROID START */
				offset_addr = env->regs[d->Rn] + env->regs[d->Rm];
				address = offset_addr;
				switch(d->instr){
					case I_STR:
						setRegToMem4(address, d->Rt);
						break;
					case I_STRH:
						setRegToMem2(address, d->Rt);
						break;
					case I_STRB:
						setRegToMem(address, d->Rt);
						break;
					case I_LDR:
						setMem4ToReg(d->Rt, address);
						break;
					case I_LDRB:
					case I_LDRSB:
						setMemToReg(d->Rt, address);
						break;
					case I_LDRH:
					case I_LDRSH:
						setMem2ToReg(d->Rt, address);
						break;
				}
				/* NDROID END */
        return 0;

    case T_THUMB_RW_REG:
        // TODO write-back support for LDM
        d->reglist = w & BITMSK_8;
        d->Rn = (w >> 8) & b111;

				/* NDROID START */
				address = env->regs[d->Rn];
				for(i = 0; i < 16; i++){
					if((d->reglist & (0b1 << i)) == 1){
						if(d->instr == I_LDM){
							setMem4ToReg(i, address);
						}else{
							setRegToMem4(address, i);
						}
						address += 4;	
					}
				}
				/* NDROID END */
        return 0;

    case T_THUMB_REV:
        d->instr = type_rev_instr_lookup[(w >> 6) & b11];
        if(d->instr == I_INVLD) return -1;

        d->Rd = (w >> 0) & b111;
        d->Rm = (w >> 3) & b111;
				
				/* NDROID START */
				setRegToReg(d->Rd, d->Rm);
				/* NDROID END */
        return 0;

    case T_THUMB_SETEND:
        d->E = (w >> 4) & b1;
        return 0;

    case T_THUMB_PUSHPOP:
        d->reglist = w & BITMSK_8;

        // for push we have to set LR
        if(d->instr == I_PUSH) {
            d->reglist |= ((w >> 8) & 1) << LR;

						/* NDROID START */
						address = env->regs[SP] - 4 * darm_bit_count_16(d->reglist);
						for(i = 0; i < 16; i++){
							if((d->reglist & (0b1 << i)) ==1){
								setRegToMem4(address, i);
								address += 4;
							}
						}
						/* NDROID END */
        }
        // for pop we have to set PC
        else {
            d->reglist |= ((w >> 8) & 1) << PC;

						/* NDROID START */
						address = env->regs[SP];
						for(i = 0; i < 16; i++){
							if((d->reglist & (0b1 << i)) == 1){
								setMem4ToReg(i, address);
								address += 4;
							}
						}
						/* NDROID END */
        }
        return 0;

    case T_THUMB_CMP:
        // the 4th bit for Rn is stored as the 7th bit
        d->Rn = (w & b111) | ((w >> 4) & b1000);
        d->Rm = (w >> 3) & b1111;
        return 0;

    case T_THUMB_MOD_SP_REG:
        // a8.8.6 t2 (also implies a8.8.10 t2)
        d->Rd = d->Rn = ((w >> 4) & b1000) | (w & b0111);
        d->Rm = (w >> 3) & b1111;
				
				/* NDROID START */
				setRegToReg(d->Rd, d->Rm);
				/* NDROID END */

        // a8.8.10 t1
        if(d->Rm == SP) {
            d->Rd = d->Rm = d->Rn;
            d->Rn = SP;
        }
        return 0;

    case T_THUMB_CBZ:
        d->instr = (w >> 11) & 1 ? I_CBNZ : I_CBZ;
        d->Rn = w & b111;
        d->Rm = PC;
        d->U = B_SET;
        d->I = B_SET;
        d->imm = ((w >> 2) & (b11111 << 1)) | ((w >> 5) & (1 << 6));
        return 0;
    }
    return -1;
}

int darm_thumb_disasm(darm_t *d, uint16_t w, CPUState* env)
{
    darm_init(d);
    d->w = w;

    // we set all conditional flags to "execute always" by default, as most
    // thumb instructions don't feature a conditional flag
    d->cond = C_AL;

    switch (w >> 11) {
    case b11101: case b11110: case b11111:
        return -1;

    default:
        return thumb_disasm(d, w, env);
    }
}
