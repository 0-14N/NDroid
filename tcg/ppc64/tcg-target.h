/*
 * Tiny Code Generator for QEMU
 *
 * Copyright (c) 2008 Fabrice Bellard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#define TCG_TARGET_PPC64 1

#define TCG_TARGET_REG_BITS 64
#define TCG_TARGET_WORDS_BIGENDIAN
#define TCG_TARGET_NB_REGS 32

enum {
    TCG_REG_R0 = 0,
    TCG_REG_R1,
    TCG_REG_R2,
    TCG_REG_R3,
    TCG_REG_R4,
    TCG_REG_R5,
    TCG_REG_R6,
    TCG_REG_R7,
    TCG_REG_R8,
    TCG_REG_R9,
    TCG_REG_R10,
    TCG_REG_R11,
    TCG_REG_R12,
    TCG_REG_R13,
    TCG_REG_R14,
    TCG_REG_R15,
    TCG_REG_R16,
    TCG_REG_R17,
    TCG_REG_R18,
    TCG_REG_R19,
    TCG_REG_R20,
    TCG_REG_R21,
    TCG_REG_R22,
    TCG_REG_R23,
    TCG_REG_R24,
    TCG_REG_R25,
    TCG_REG_R26,
    TCG_REG_R27,
    TCG_REG_R28,
    TCG_REG_R29,
    TCG_REG_R30,
    TCG_REG_R31
};

/* used for function call generation */
#define TCG_REG_CALL_STACK TCG_REG_R1
#define TCG_TARGET_STACK_ALIGN 16
#define TCG_TARGET_CALL_STACK_OFFSET 48

/* optional instructions */
#define TCG_TARGET_HAS_div_i32
/* #define TCG_TARGET_HAS_rot_i32 */
#define TCG_TARGET_HAS_ext8s_i32
#define TCG_TARGET_HAS_ext16s_i32
/* #define TCG_TARGET_HAS_ext8u_i32 */
/* #define TCG_TARGET_HAS_ext16u_i32 */
/* #define TCG_TARGET_HAS_bswap16_i32 */
/* #define TCG_TARGET_HAS_bswap32_i32 */
/* #define TCG_TARGET_HAS_not_i32 */
#define TCG_TARGET_HAS_neg_i32
/* #define TCG_TARGET_HAS_andc_i32 */
/* #define TCG_TARGET_HAS_orc_i32 */
/* #define TCG_TARGET_HAS_eqv_i32 */
/* #define TCG_TARGET_HAS_nand_i32 */
/* #define TCG_TARGET_HAS_nor_i32 */

#define TCG_TARGET_HAS_div_i64
/* #define TCG_TARGET_HAS_rot_i64 */
#define TCG_TARGET_HAS_ext8s_i64
#define TCG_TARGET_HAS_ext16s_i64
#define TCG_TARGET_HAS_ext32s_i64
/* #define TCG_TARGET_HAS_ext8u_i64 */
/* #define TCG_TARGET_HAS_ext16u_i64 */
/* #define TCG_TARGET_HAS_ext32u_i64 */
/* #define TCG_TARGET_HAS_bswap16_i64 */
/* #define TCG_TARGET_HAS_bswap32_i64 */
/* #define TCG_TARGET_HAS_bswap64_i64 */
/* #define TCG_TARGET_HAS_not_i64 */
#define TCG_TARGET_HAS_neg_i64
/* #define TCG_TARGET_HAS_andc_i64 */
/* #define TCG_TARGET_HAS_orc_i64 */
/* #define TCG_TARGET_HAS_eqv_i64 */
/* #define TCG_TARGET_HAS_nand_i64 */
/* #define TCG_TARGET_HAS_nor_i64 */

#define TCG_AREG0 TCG_REG_R27

#define TCG_TARGET_HAS_GUEST_BASE
#define TCG_TARGET_EXTEND_ARGS 1
