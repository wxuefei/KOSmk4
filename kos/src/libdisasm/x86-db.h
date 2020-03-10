/* Copyright (c) 2019-2020 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBDISASM_X86_DB_H
#define GUARD_LIBDISASM_X86_DB_H 1
#define DISABLE_BRANCH_PROFILING 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include "x86.h"

#include <hybrid/compiler.h>

#include <hybrid/byteorder.h>
#include <hybrid/host.h>
#include <hybrid/unaligned.h>

#include <kos/kernel/types.h>
#include <kos/types.h>

#include <inttypes.h> /* PRI* */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "_binstr.h"

DECL_BEGIN

/* Automatically select jcc and setcc condition
 * representation based on the preceding instruction. */
#undef CONFIG_AUTOSELECT_JCC
#if 1
#define CONFIG_AUTOSELECT_JCC  1
#endif

/* Include implied operands of FPU instructions */
#undef CONFIG_VERBOSE_FINST
#if 1
#define CONFIG_VERBOSE_FINST  1
#endif


#define I(op, flags, repr) { flags, op, repr }
struct instruction {
	/*  */
#define IF_REG0  0x0008 /* Require that modrm.mi_reg == 0 */
#define IF_REG1  0x0009 /* Require that modrm.mi_reg == 1 */
#define IF_REG2  0x000a /* Require that modrm.mi_reg == 2 */
#define IF_REG3  0x000b /* Require that modrm.mi_reg == 3 */
#define IF_REG4  0x000c /* Require that modrm.mi_reg == 4 */
#define IF_REG5  0x000d /* Require that modrm.mi_reg == 5 */
#define IF_REG6  0x000e /* Require that modrm.mi_reg == 6 */
#define IF_REG7  0x000f /* Require that modrm.mi_reg == 7 */
#define IF_MODRM 0x0010 /* Decode a modr/m suffix */
#define IF_BYTE2 0x3017 /* The first repr-byte is required as a follow-up on the instruction byte. */
#define IF_66    0x0020 /* Mandatory prefix: operand-size override */
#define IF_F2    0x0040 /* Mandatory prefix: repne */
#define IF_F3    0x0080 /* Mandatory prefix: rep, repe */
#define IF_67    0x0100 /* Address size override */
#define IF_REXW  0x0200 /* Mask for the matching value of `REX.W' */
#define IF_REXB  0xc000 /* Only match instructions with `REX.B' set */
#define IF_RMM   0x0400 /* Modrm is memory */
#define IF_RMR   0x0800 /* Modrm is register */
#define IF_VEXW0 0x1000 /* VEX + VEX.W == 0 */
#define IF_VEXW1 0x2000 /* VEX + VEX.W == 1 */
#define IF_VEX   0x3000 /* VEX (further specified by first character of repr, which is a set of `IF_VEX_B0_*') */
#define IF_VEX_B0_LL_M   0x03 /* Required value for `VEX.LL' */
#define IF_VEX_B0_LL_S      0 /* Required value for `VEX.LL' */
#define IF_VEX_B0_LIG    0x03 /* Value of `IF_VEX_B0_LL_M' when vector length should be ignored. */
#define IF_VEX_B0_W      0x04 /* Required value for `VEX.W' */
#define IF_VEX_B0_WIG    0x08 /* Ignore `VEX.W' (`IF_VEX_B0_W' must not be set) */
#define IF_VEX_B0_NOEVEX 0x10 /* Require that no EVEX prefix be given */
#define IF_VEX_B0_RESVD  0xe0 /* Reserved bits */
#define IF_X32   0x4000 /* Only match in 32-bit mode */
#define IF_X64   0x8000 /* Only match in 64-bit mode */
	u16  i_flags;    /* Instruction flags (set of `IF_*'). */
	u8   i_opcode;   /* Instruction opcode. */
	char i_repr[13]; /* Instruction representation (name + ["\t" + operands])
	                  * Note that some flag combinations also make use the first
	                  * byte for additional representation. Also note that when
	                  * the first character of the actual representation is a `?',
	                  * then the following 2 bytes represent an unsigned offset
	                  * into `longops_repr', to where the actual representation
	                  * can be found. The representation is always terminated by
	                  * a '\0' (NUL) character. */
};
#define _OP_VEX_B02(noevex, wig, w, ll) BINSTR_000##noevex##wig##w##ll
#define _OP_VEX_B0(noevex, wig, w, ll)  _OP_VEX_B02(noevex, wig, w, ll)
#define OP_VEX_B0(noevex, wig, w, ll)   _OP_VEX_B0(NORMBIN1(noevex), NORMBIN1(wig), NORMBIN1(w), NORMBIN2(ll))
#define B_OP_VEX_B0(noevex, wig, w, ll)  \
	(((noevex) ? IF_VEX_B0_NOEVEX : 0) | \
	 ((wig) ? IF_VEX_B0_WIG : 0) |       \
	 ((w) ? IF_VEX_B0_W : 0) |           \
	 ((ll) << IF_VEX_B0_LL_S))

#define _OP_VEX_B02_LIG(noevex, wig, w) BINSTR_000##noevex##wig##w##11
#define _OP_VEX_B0_LIG(noevex, wig, w)  _OP_VEX_B02_LIG(noevex, wig, w)
#define OP_VEX_B0_LIG(noevex, wig, w)   _OP_VEX_B0_LIG(NORMBIN1(noevex), NORMBIN1(wig), NORMBIN1(w))
#define B_OP_VEX_B0_LIG(noevex, wig, w)  \
	(((noevex) ? IF_VEX_B0_NOEVEX : 0) | \
	 ((wig) ? IF_VEX_B0_WIG : 0) |       \
	 ((w) ? IF_VEX_B0_W : 0) |           \
	 IF_VEX_B0_LL_M)


/* Instruction operand type encodings
 * Each operand (usually) consists of a single ASCII character that
 * describes how and what is printed in order to represent the operand.
 * The final representations of some operands may depend on specific
 * prefix bytes or the value of the instruction's (optional) modr/m.
 * Also note that in order to fully determine the length of an instruction,
 * operands must also be decoded, as operands also contain information
 * about immediate bytes (that are consumed as they are encountered)
 * An instruction representation `i_repr' is encoded as:
 *   #1: "X...":
 *       The first byte of the representation is used for instruction matching when:
 *       `(i_flags & IF_BYTE2) == IF_BYTE2 || (i_flags & IF_VEX) == IF_VEX'
 *       If this is the case, then the first byte of `repr' is consumed and all
 *       of the following encode/decode steps operate as `repr = i_repr + 1'
 *   #2: OPC_LONGREPR + "<O1><O2>":
 *       The actual representation is stored at `longops_repr + UNALIGNED_GET16((u16 *)(repr + 1))'
 *       This is done to overcome the 12 (12+NUL=13) character limit for encoding
 *       a mnemonic and its operands.
 *       If the first character of `repr' was `OPC_LONGREPR', then all of the following
 *       encode/decode steps operate using the string found in `longops_repr'
 *   #3: This is where the ~actual~ representation can be found, which is one of:
 *       - "<mnemonic>\0"
 *       - "<mnemonic>\t<operands...>\0"
 *       With `mnemonic' being the name of the instruction, and `operands'
 *       being a tightly packed string made up of `OP_*', where each macro
 *       expands to represent (usually) one operand (but note the few optional
 *       operands such as `OP_SAE' and `OP_ER', as well as the few macros
 *       that encode multiple operands).
 *       Additionally, each operand from `operands' can be `OP_ESC("...")',
 *       where `...' is an inlined string that will be printed in place of
 *       the operand's representation. The prefix/suffix of this expression
 *       is selected based on the first character of `...':
 *         - `%': DISASSEMBLER_FORMAT_REGISTER_(PREFIX|SUFFIX)
 *         - `$': DISASSEMBLER_FORMAT_IMMEDIATE_(PREFIX|SUFFIX)
 *         - <anything else>: <printed without prefix/suffix>
 */


/* Valid operand namespace: ASCII 0x20-0x7e */

/*      OPC_            ' '  * ... */
/*      OP_             " "  * ... */
#define OPC_RM128_XMM__OPC_VRXMM__OPC_RXMM_MASK '!' /* Short form of: OPC_RM128_XMM OPC_VRXMM OPC_RXMM_MASK */
#define OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK    "!" /* Short form of: OP_RM128_XMM OP_VRXMM OP_RXMM_MASK */
#define OP_RM128_XMM__OP_VRXMM__OP_RXMM         "!" /* Short form of: OP_RM128_XMM OP_VRXMM OP_RXMM_MASK */
#define OPC_RM256_YMM__OPC_VRYMM__OPC_RYMM_MASK '\"'/* Short form of: OPC_RM256_YMM OPC_VRYMM OPC_RYMM_MASK */
#define OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK    "\""/* Short form of: OP_RM256_YMM OP_VRYMM OP_RYMM_MASK */
#define OP_RM256_YMM__OP_VRYMM__OP_RYMM         "\""/* Short form of: OP_RM256_YMM OP_VRYMM OP_RYMM_MASK */
#define OPC_RM512_ZMM__OPC_VRZMM__OPC_RZMM_MASK '#' /* Short form of: OPC_RM512_ZMM OPC_VRZMM OPC_RZMM_MASK */
#define OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK    "#" /* Short form of: OP_RM512_ZMM OP_VRZMM OP_RZMM_MASK */
#define OP_RM512_ZMM__OP_VRZMM__OP_RZMM         "#" /* Short form of: OP_RM512_ZMM OP_VRZMM OP_RZMM_MASK */
#define OPC_VRXMM_MASK  '$' /* %xmm0, %xmm1, etc. (based on F_VEX_VVVVV_M) (followed by {%kN}{z}) */
#define OP_VRXMM_MASK   "$" /* %xmm0, %xmm1, etc. (based on F_VEX_VVVVV_M) (followed by {%kN}{z}) */
#define OPC_VRYMM_MASK  '%' /* %ymm0, %ymm1, etc. (based on F_VEX_VVVVV_M) (followed by {%kN}{z}) */
#define OP_VRYMM_MASK   "%" /* %ymm0, %ymm1, etc. (based on F_VEX_VVVVV_M) (followed by {%kN}{z}) */
#define OPC_VRZMM_MASK  '&' /* %zmm0, %zmm1, etc. (based on F_VEX_VVVVV_M) (followed by {%kN}{z}) */
#define OP_VRZMM_MASK   "&" /* %zmm0, %zmm1, etc. (based on F_VEX_VVVVV_M) (followed by {%kN}{z}) */
#define OPC_RXMM        '\''/* %xmm0, %xmm1, etc. (based on rm.mi_reg) */
#define OP_RXMM         "\'"/* %xmm0, %xmm1, etc. (based on rm.mi_reg) */
#define OPC_RYMM        '(' /* %ymm0, %ymm1, etc. (based on rm.mi_reg) */
#define OP_RYMM         "(" /* %ymm0, %ymm1, etc. (based on rm.mi_reg) */
#define OPC_RZMM        ')' /* %zmm0, %zmm1, etc. (based on rm.mi_reg) */
#define OP_RZMM         ")" /* %zmm0, %zmm1, etc. (based on rm.mi_reg) */
#define OPC_XRM64       '*' /* 64-bit register or memory location prefixed by `*' (requires IF_MODRM) */
#define OP_XRM64        "*" /* 64-bit register or memory location prefixed by `*' (requires IF_MODRM) */
#define OPC_XRM32       '+' /* 32-bit register or memory location prefixed by `*' (requires IF_MODRM) */
#define OP_XRM32        "+" /* 32-bit register or memory location prefixed by `*' (requires IF_MODRM) */
#define OPC_RMM         ',' /* %mm0, %mm1, etc. (based on rm.mi_reg) */
#define OP_RMM          "," /* %mm0, %mm1, etc. (based on rm.mi_reg) */
#define OPC_RXMM_MASK   '-' /* %xmm0, %xmm1, etc. (based on rm.mi_reg) (followed by {%kN}{z}) */
#define OP_RXMM_MASK    "-" /* %xmm0, %xmm1, etc. (based on rm.mi_reg) (followed by {%kN}{z}) */
#define OPC_RYMM_MASK   '.' /* %ymm0, %ymm1, etc. (based on rm.mi_reg) (followed by {%kN}{z}) */
#define OP_RYMM_MASK    "." /* %ymm0, %ymm1, etc. (based on rm.mi_reg) (followed by {%kN}{z}) */
#define OPC_RZMM_MASK   '/' /* %zmm0, %zmm1, etc. (based on rm.mi_reg) (followed by {%kN}{z}) */
#define OP_RZMM_MASK    "/" /* %zmm0, %zmm1, etc. (based on rm.mi_reg) (followed by {%kN}{z}) */
#define OPC_RM8         '0' /* 8-bit register or memory location (requires IF_MODRM) */
#define OP_RM8          "0" /* 8-bit register or memory location (requires IF_MODRM) */
#define OPC_RM16        '1' /* 16-bit register or memory location (requires IF_MODRM) */
#define OP_RM16         "1" /* 16-bit register or memory location (requires IF_MODRM) */
#define OPC_RM32        '2' /* 32-bit register or memory location (requires IF_MODRM) */
#define OP_RM32         "2" /* 32-bit register or memory location (requires IF_MODRM) */
#define OP_MEM          "3" /* Memory location (requires IF_MODRM) */
#define OPC_RM64        '3' /* 64-bit register or memory location (requires IF_MODRM) */
#define OP_RM64         "3" /* 64-bit register or memory location (requires IF_MODRM) */
#define OPC_RMBND       '4' /* %bndN register or memory location (requires IF_MODRM) */
#define OP_RMBND        "4" /* %bndN register or memory location (requires IF_MODRM) */
#define OPC_RMBND_RANGE '5' /* %bndN:%bndN register pair (requires IF_MODRM) */
#define OP_RMBND_RANGE  "5" /* %bndN:%bndN register pair (requires IF_MODRM) */
#define OPC_RMSTi       '6' /* %st(N) register or memory location (requires IF_MODRM) */
#define OP_RMSTi        "6" /* %st(N) register or memory location (requires IF_MODRM) */
#define OPC_RM128_XMM_MASK '7' /* 128-bit memory location or %xmm0, %xmm1, etc. (based on rm.mi_rm) (followed by {%kN}{z}) */
#define OP_RM128_XMM_MASK  "7" /* 128-bit memory location or %xmm0, %xmm1, etc. (based on rm.mi_rm) (followed by {%kN}{z}) */
#define OP_MEM_MASK        "7" /* Memory location (requires IF_MODRM) (followed by {%kN}{z}) */
#define OPC_RM256_YMM_MASK '8' /* 256-bit memory location or %ymm0, %ymm1, etc. (based on rm.mi_rm) (followed by {%kN}{z}) */
#define OP_RM256_YMM_MASK  "8" /* 256-bit memory location or %ymm0, %ymm1, etc. (based on rm.mi_rm) (followed by {%kN}{z}) */
#define OPC_RM512_ZMM_MASK '9' /* 512-bit memory location or %zmm0, %zmm1, etc. (based on rm.mi_rm) (followed by {%kN}{z}) */
#define OP_RM512_ZMM_MASK  "9" /* 512-bit memory location or %zmm0, %zmm1, etc. (based on rm.mi_rm) (followed by {%kN}{z}) */
#define OPC_SHORT       ':' /* Prefix for shortened register names */
#define OP_SHORT        ":" /* Prefix for shortened register names */
#define OPC_RM64_MM     ';' /* 64-bit memory location or %mm0, %mm1, etc. (based on rm.mi_rm) */
#define OP_RM64_MM      ";" /* 64-bit memory location or %mm0, %mm1, etc. (based on rm.mi_rm) */
#define OPC_RM128_XMM   '<' /* 128-bit memory location or %xmm0, %xmm1, etc. (based on rm.mi_rm) */
#define OP_RM128_XMM    "<" /* 128-bit memory location or %xmm0, %xmm1, etc. (based on rm.mi_rm) */
#define OPC_RM256_YMM   '=' /* 256-bit memory location or %ymm0, %ymm1, etc. (based on rm.mi_rm) */
#define OP_RM256_YMM    "=" /* 256-bit memory location or %ymm0, %ymm1, etc. (based on rm.mi_rm) */
#define OPC_RM512_ZMM   '>' /* 512-bit memory location or %zmm0, %zmm1, etc. (based on rm.mi_rm) */
#define OP_RM512_ZMM    ">" /* 512-bit memory location or %zmm0, %zmm1, etc. (based on rm.mi_rm) */
#define OPC_LONGREPR    '?' /* Indicator for a long representation string. */
#define OPC_VRXMM       '@' /* %xmm0, %xmm1, etc. (based on F_VEX_VVVVV_M) */
#define OP_VRXMM        "@" /* %xmm0, %xmm1, etc. (based on F_VEX_VVVVV_M) */
#define OPC_U8          'A' /* imm8 (read from *PC before doing PC+=1) */
#define OP_U8           "A" /* imm8 (read from *PC before doing PC+=1) */
#define OPC_U16         'B' /* imm16 (read from *PC before doing PC+=2) */
#define OP_U16          "B" /* imm16 (read from *PC before doing PC+=2) */
#define OPC_U32         'C' /* imm32 (read from *PC before doing PC+=4) */
#define OP_U32          "C" /* imm32 (read from *PC before doing PC+=4) */
#define OPC_RMK         'D' /* %kN register or memory location (requires IF_MODRM) */
#define OP_RMK          "D" /* %kN register or memory location (requires IF_MODRM) */
#define OPC_MOFFS8      'E' /* moffs8 (read from *PC before doing PC+=1) */
#define OP_MOFFS8       "E" /* moffs8 (read from *PC before doing PC+=1) */
#define OPC_MOFFS16     'F' /* moffs16 (read from *PC before doing PC+=2) */
#define OP_MOFFS16      "F" /* moffs16 (read from *PC before doing PC+=2) */
#define OPC_MOFFS32     'G' /* moffs32 (read from *PC before doing PC+=4) */
#define OP_MOFFS32      "G" /* moffs32 (read from *PC before doing PC+=4) */
#define OPC_MOFFS64     'H' /* moffs64 (read from *PC before doing PC+=8) */
#define OP_MOFFS64      "H" /* moffs64 (read from *PC before doing PC+=8) */
#define OPC_ER          'I' /* {rn-sae}, {rd-sae}, {ru-sae} or {rz-sae} (based on `EVEX.LL') (operand is skipped if `EVEX.b' isn't set) */
#define OP_ER           "I" /* {rn-sae}, {rd-sae}, {ru-sae} or {rz-sae} (based on `EVEX.LL') (operand is skipped if `EVEX.b' isn't set) */
#define OPC_SAE         'J' /* {sae} (operand is skipped if `EVEX.b' isn't set) */
#define OP_SAE          "J" /* {sae} (operand is skipped if `EVEX.b' isn't set) */
#define OPC_IMM8_XMM    'K' /* %xmmN (based on *PC & 0xf0 before doing PC+=1) */
#define OP_IMM8_XMM     "K" /* %xmmN (based on *PC & 0xf0 before doing PC+=1) */
#define OPC_IMM8_YMM    'L' /* %ymmN (based on *PC & 0xf0 before doing PC+=1) */
#define OP_IMM8_YMM     "L" /* %ymmN (based on *PC & 0xf0 before doing PC+=1) */
/*      OPC_            'M'  * ... */
/*      OP_             "M"  * ... */
/*      OPC_            'N'  * ... */
/*      OP_             "N"  * ... */
/*      OPC_            'O'  * ... */
/*      OP_             "O"  * ... */
#define OPC_LJMP        'P' /* seg:offset pair (read from *PC before doing PC+=(4|6)) */
#define OP_LJMP         "P" /* seg:offset pair (read from *PC before doing PC+=(4|6)) */
/*      OPC_            'Q'  * ... */
/*      OP_             "Q"  * ... */
#define OPC_VR8         'R' /* 8-bit general purpose register (based on `VEX.VVVVV'; requires IF_VEX*) */
#define OP_VR8          "R" /* 8-bit general purpose register (based on `VEX.VVVVV'; requires IF_VEX*) */
#define OPC_VR16        'S' /* 16-bit general purpose register (based on `VEX.VVVVV'; requires IF_VEX*) */
#define OP_VR16         "S" /* 16-bit general purpose register (based on `VEX.VVVVV'; requires IF_VEX*) */
#define OPC_VR32        'T' /* 32-bit general purpose register (based on `VEX.VVVVV'; requires IF_VEX*) */
#define OP_VR32         "T" /* 32-bit general purpose register (based on `VEX.VVVVV'; requires IF_VEX*) */
#define OPC_VR64        'U' /* 64-bit general purpose register (based on `VEX.VVVVV'; requires IF_VEX*) */
#define OP_VR64         "U" /* 64-bit general purpose register (based on `VEX.VVVVV'; requires IF_VEX*) */
/*      OPC_            'V'  * ... */
/*      OP_             "V"  * ... */
/*      OPC_            'W'  * ... */
/*      OP_             "W"  * ... */
/*      OPC_            'X'  * ... */
/*      OP_             "X"  * ... */
/*      OPC_            'Y'  * ... */
/*      OP_             "Y"  * ... */
/*      OPC_            'Z'  * ... */
/*      OP_             "Z"  * ... */
/*      OPC_            '['  * ... */
/*      OP_             "["  * ... */
/*      OPC_            '\\' * ... */
/*      OP_             "\\" * ... */
/*      OPC_            ']'  * ... */
/*      OP_             "]"  * ... */
/*      OPC_            '^'  * ... */
/*      OP_             "^"  * ... */
#define OPC_VRK         '_' /* %kN register (based on F_VEX_VVVVV_M) */
#define OP_VRK          "_" /* %kN register (based on F_VEX_VVVVV_M) */
#define OPC_VRYMM       '`' /* %ymm0, %ymm1, etc. (based on F_VEX_VVVVV_M) */
#define OP_VRYMM        "`" /* %ymm0, %ymm1, etc. (based on F_VEX_VVVVV_M) */
#define OPC_S8          'a' /* Simm8 (read from *PC before doing PC+=1) */
#define OP_S8           "a" /* Simm8 (read from *PC before doing PC+=1) */
#define OPC_S16         'b' /* Simm16 (read from *PC before doing PC+=2) */
#define OP_S16          "b" /* Simm16 (read from *PC before doing PC+=2) */
#define OPC_S32         'c' /* Simm32 (read from *PC before doing PC+=4) */
#define OP_S32          "c" /* Simm32 (read from *PC before doing PC+=4) */
#define OPC_U64         'd' /* imm64 (read from *PC before doing PC+=8) */
#define OP_U64          "d" /* imm64 (read from *PC before doing PC+=8) */
/*      OPC_            'e'  * ... */
/*      OP_             "e"  * ... */
/*      OPC_            'f'  * ... */
/*      OP_             "f"  * ... */
/*      OPC_            'g'  * ... */
/*      OP_             "g"  * ... */
/*      OPC_            'h'  * ... */
/*      OP_             "h"  * ... */
/*      OPC_            'i'  * ... */
/*      OP_             "i"  * ... */
/*      OPC_            'j'  * ... */
/*      OP_             "j"  * ... */
/*      OPC_            'k'  * ... */
/*      OP_             "k"  * ... */
/*      OPC_            'l'  * ... */
/*      OP_             "l"  * ... */
#define OPC_DISP8       'm' /* 8-bit PC-displacement symbol */
#define OP_DISP8        "m" /* 8-bit PC-displacement symbol */
#define OPC_DISP16      'n' /* 16-bit PC-displacement symbol */
#define OP_DISP16       "n" /* 16-bit PC-displacement symbol */
#define OPC_DISP32      'o' /* 32-bit PC-displacement symbol */
#define OP_DISP32       "o" /* 32-bit PC-displacement symbol */
#define OPC_RK_MASK     'p' /* %kN register (based on `rm.mi_reg'; requires IF_MODRM) (followed by {%kN}{z}) */
#define OP_RK_MASK      "p" /* %kN register (based on `rm.mi_reg'; requires IF_MODRM) (followed by {%kN}{z}) */
#define OPC_RK          'q' /* %kN register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_RK           "q" /* %kN register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_R8          'r' /* 8-bit general purpose register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_R8           "r" /* 8-bit general purpose register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_R16         's' /* 16-bit general purpose register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_R16          "s" /* 16-bit general purpose register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_R32         't' /* 32-bit general purpose register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_R32          "t" /* 32-bit general purpose register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_R64         'u' /* 64-bit general purpose register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_R64          "u" /* 64-bit general purpose register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_RSEG        'v' /* segment register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_RSEG         "v" /* segment register (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_RCR         'w' /* %crN (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_RCR          "w" /* %crN (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_RDR         'x' /* %drN (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_RDR          "x" /* %drN (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_RBND        'y' /* %bndN (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_RBND         "y" /* %bndN (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_RTR         'z' /* %trN (based on `rm.mi_reg'; requires IF_MODRM) */
#define OP_RTR          "z" /* %trN (based on `rm.mi_reg'; requires IF_MODRM) */
#define OPC_ESC         '{' /* Start of an inlined, escaped operand representation */
#define OPC_ESC_END     '}' /* End of an inlined, escaped operand representation (only recognized after `OPC_ESC') */
#define OP_ESC(s)       "{" s "}" /* Insert an escaped operand representation */
#define OPC_VRZMM       '|' /* %zmm0, %zmm1, etc. (based on F_VEX_VVVVV_M) */
#define OP_VRZMM        "|" /* %zmm0, %zmm1, etc. (based on F_VEX_VVVVV_M) */
/*      OPC_            '}'  * ... */
/*      OP_             "}"  * ... */
#define OPC_XRM16       '~' /* 16-bit register or memory location prefixed by `*' (requires IF_MODRM) */
#define OP_XRM16        "~" /* 16-bit register or memory location prefixed by `*' (requires IF_MODRM) */

#define OP_PAX_PCX_PDX OP_SHORT "a" /* %ax, %cx, %dx | %eax, %ecx, %edx | %rax, %rcx, %rdx (same as pointer-size; s.a. `DA86_IS(16|32|64)()') */
#define OP_PAX_PCX     OP_SHORT "b" /* %ax, %cx | %eax, %ecx | %rax, %rcx (same as pointer-size; s.a. `DA86_IS(16|32|64)()') */
#define OP_PSI         OP_SHORT "c" /* %si, %esi, %rsi (same as pointer-size; s.a. `DA86_IS(16|32|64)()') */

/* Smaller encodings for a couple of fixed register operands.
 * While all of these could be implemented with `OP_ESC()', this
 * format uses much less memory, allowing `i_repr' to be much smaller. */
#define OP_ST0     OP_SHORT "0" /* %st(0) */
#define OP_ST1     OP_SHORT "1" /* %st(1) */
#define OP_ST2     OP_SHORT "2" /* %st(2) */
#define OP_ST3     OP_SHORT "3" /* %st(3) */
#define OP_ST4     OP_SHORT "4" /* %st(4) */
#define OP_ST5     OP_SHORT "5" /* %st(5) */
#define OP_ST6     OP_SHORT "6" /* %st(6) */
#define OP_ST7     OP_SHORT "7" /* %st(7) */
#define OP_R8W     OP_SHORT "K" /* %r8w */
#define OP_R8D     OP_SHORT "L" /* %r8d */
#define OP_R9W     OP_SHORT "M" /* %r9w */
#define OP_R9D     OP_SHORT "N" /* %r9d */
#define OP_R10W    OP_SHORT "O" /* %r10w */
#define OP_R10D    OP_SHORT "P" /* %r10d */
#define OP_R11W    OP_SHORT "Q" /* %r11w */
#define OP_R11D    OP_SHORT "R" /* %r11d */
#define OP_R12W    OP_SHORT "S" /* %r12w */
#define OP_R12D    OP_SHORT "T" /* %r12d */
#define OP_R13W    OP_SHORT "U" /* %r13w */
#define OP_R13D    OP_SHORT "V" /* %r13d */
#define OP_R14W    OP_SHORT "W" /* %r14w */
#define OP_R14D    OP_SHORT "X" /* %r14d */
#define OP_R15W    OP_SHORT "Y" /* %r15w */
#define OP_R15D    OP_SHORT "Z" /* %r15d */
#define OP_EAX     OP_SHORT "k" /* %eax */
#define OP_ECX     OP_SHORT "l" /* %ecx */
#define OP_EDX     OP_SHORT "m" /* %edx */
#define OP_EBX     OP_SHORT "n" /* %ebx */
#define OP_ESP     OP_SHORT "o" /* %esp */
#define OP_EBP     OP_SHORT "p" /* %ebp */
#define OP_ESI     OP_SHORT "q" /* %esi */
#define OP_EDI     OP_SHORT "r" /* %edi */
#define OP_RAX     OP_SHORT "s" /* %rax */
#define OP_RCX     OP_SHORT "t" /* %rcx */
#define OP_RDX     OP_SHORT "u" /* %rdx */
#define OP_RBX     OP_SHORT "v" /* %rbx */
#define OP_RSP     OP_SHORT "w" /* %rsp */
#define OP_RBP     OP_SHORT "x" /* %rbp */
#define OP_RSI     OP_SHORT "y" /* %rsi */
#define OP_RDI     OP_SHORT "z" /* %rdi */

#define OP_AX      OP_SHORT "A" /* %ax */
#define OP_CX      OP_SHORT "B" /* %cx */
#define OP_DX      OP_SHORT "C" /* %dx */
#define OP_BX      OP_SHORT "D" /* %bx */
#define OP_SP      OP_SHORT "E" /* %sp */
#define OP_BP      OP_SHORT "F" /* %bp */
#define OP_SI      OP_SHORT "G" /* %si */
#define OP_DI      OP_SHORT "H" /* %di */

#define OP_X64_RN_MIN ' '
#define OP_X64_RN_MAX '\''
#define OP_X64_R8  OP_SHORT " " /* %r8 */
#define OP_R9      OP_SHORT "!" /* %r9 */
#define OP_R10     OP_SHORT "\""/* %r10 */
#define OP_R11     OP_SHORT "#" /* %r11 */
#define OP_R12     OP_SHORT "$" /* %r12 */
#define OP_R13     OP_SHORT "%" /* %r13 */
#define OP_R14     OP_SHORT "&" /* %r14 */
#define OP_R15     OP_SHORT "\'"/* %r15 */

#define OP_GP16_MIN '('
#define OP_GP16_MAX '/'
#define OP_AL      OP_SHORT "(" /* %al */
#define OP_CL      OP_SHORT ")" /* %cl */
#define OP_DL      OP_SHORT "*" /* %dl */
#define OP_BL      OP_SHORT "+" /* %bl */
#define OP_AH      OP_SHORT "," /* %ah */
#define OP_CH      OP_SHORT "-" /* %ch */
#define OP_DH      OP_SHORT "." /* %dh */
#define OP_BH      OP_SHORT "/" /* %bh */

#define OP_DS   OP_ESC("%ds") /* %ds */
#define OP_ES   OP_ESC("%es") /* %es */
#define OP_FS   OP_ESC("%fs") /* %fs */
#define OP_GS   OP_ESC("%gs") /* %gs */
#define OP_CS   OP_ESC("%cs") /* %cs */
#define OP_SS   OP_ESC("%ss") /* %ss */

#define OP_IMM1 OP_ESC("$1")  /* $1 */
#define OP_XMM0 OP_ESC("%xmm0") /* %xmm0 */


#ifdef CONFIG_VERBOSE_FINST
#define OP_VERBOSE_ST0 OP_ST0
#define OP_VERBOSE_ST1 OP_ST1
#else /* CONFIG_VERBOSE_FINST */
#define OP_VERBOSE_ST0 /* nothing */
#define OP_VERBOSE_ST1 /* nothing */
#endif /* !CONFIG_VERBOSE_FINST */


#ifdef CONFIG_AUTOSELECT_JCC
#define NAME_jc0 "o"   /* "o" */
#define NAME_jc1 "no"  /* "no" */
#define NAME_jc2 "[2]" /* "[b|c|nae]" */
#define NAME_jc3 "[3]" /* "[ae|nb|nc]" */
#define NAME_jc4 "[4]" /* "[z|e]" */
#define NAME_jc5 "[5]" /* "[nz|ne]" */
#define NAME_jc6 "[6]" /* "[be|na]" */
#define NAME_jc7 "[7]" /* "[a|nbe]" */
#define NAME_jc8 "s"   /* "s" */
#define NAME_jc9 "ns"  /* "ns" */
#define NAME_jca "[a]" /* "[p|pe]" */
#define NAME_jcb "[b]" /* "[np|po]" */
#define NAME_jcc "[c]" /* "[l|nge]" */
#define NAME_jcd "[d]" /* "[ge|nl]" */
#define NAME_jce "[e]" /* "[le|ng]" */
#define NAME_jcf "[f]" /* "[g|nle]" */
#else /* CONFIG_AUTOSELECT_JCC */
#define NAME_jc0 "o"
#define NAME_jc1 "no"
#define NAME_jc2 "b"
#define NAME_jc3 "ae"
#define NAME_jc4 "z"
#define NAME_jc5 "nz"
#define NAME_jc6 "be"
#define NAME_jc7 "a"
#define NAME_jc8 "s"
#define NAME_jc9 "ns"
#define NAME_jca "p"
#define NAME_jcb "np"
#define NAME_jcc "l"
#define NAME_jcd "ge"
#define NAME_jce "le"
#define NAME_jcf "g"
#endif /* !CONFIG_AUTOSELECT_JCC */

enum {
#define LONGOP(name, repr) name, _LO_next##name = name + sizeof(repr) - 1,
#include "x86-longops.def"
#undef LONGOP
	_LO_size
};

PRIVATE char const longops_repr[_LO_size + 1] = {
#define LONGOP(name, repr) repr "\0"
#include "x86-longops.def"
#undef LONGOP
};

/* Encode extended-length opcode representation (for better compression). */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define LONGREPR(n)      { '?', (char)(u8)((n) & 0xff), (char)(u8)(((n) >> 8) & 0xff), 0 }
#define LONGREPR_B(b, n) { (char)(u8)b, '?', (char)(u8)((n) & 0xff), (char)(u8)(((n) >> 8) & 0xff), 0 }
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#define LONGREPR(n)      { '?', (char)(u8)(((n) >> 8) & 0xff), (char)(u8)((n) & 0xff), 0 }
#define LONGREPR_B(b, n) { (char)(u8)b, '?', (char)(u8)(((n) >> 8) & 0xff), (char)(u8)((n) & 0xff), 0 }
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */


/* clang-format off */
PRIVATE struct instruction const ops[] = {
/*[[[start:ops]]]*/
	/* REMINDER: After adding/removing instructions from this table, you must run:
	 *           $ deemon -F kos/src/libdisasm/x86-db.h */

	I(0x00, IF_MODRM,        "addb\t" OP_R8   OP_RM8),
	I(0x01, IF_66|IF_MODRM,  "addw\t" OP_R16  OP_RM16),
	I(0x01, IF_MODRM,        "addl\t" OP_R32  OP_RM32),
	I(0x01, IF_MODRM|IF_REXW,"addq\t" OP_R64  OP_RM64),
	I(0x02, IF_MODRM,        "addb\t" OP_RM8  OP_R32),
	I(0x03, IF_66|IF_MODRM,  "addw\t" OP_RM16 OP_R32),
	I(0x03, IF_MODRM,        "addl\t" OP_RM32 OP_R32),
	I(0x03, IF_MODRM|IF_REXW,"addq\t" OP_RM64 OP_R64),
	I(0x04, 0,               "addb\t" OP_U8   OP_AL),
	I(0x05, IF_66,           "addw\t" OP_U16  OP_AX),
	I(0x05, 0,               "addl\t" OP_U32  OP_EAX),
	I(0x05, IF_REXW,         "addq\t" OP_S32  OP_RAX),

	I(0x06, IF_66,           "pushw\t" OP_ES),
	I(0x06, 0,               "pushl\t" OP_ES),
	I(0x07, IF_66,           "popw\t" OP_ES),
	I(0x07, 0,               "popl\t" OP_ES),

	I(0x08, IF_MODRM,        "orb\t" OP_R8   OP_RM8),
	I(0x09, IF_66|IF_MODRM,  "orw\t" OP_R16  OP_RM16),
	I(0x09, IF_MODRM,        "orl\t" OP_R32  OP_RM32),
	I(0x09, IF_MODRM|IF_REXW,"orq\t" OP_R64  OP_RM64),
	I(0x0a, IF_MODRM,        "orb\t" OP_RM8  OP_R32),
	I(0x0b, IF_66|IF_MODRM,  "orw\t" OP_RM16 OP_R32),
	I(0x0b, IF_MODRM,        "orl\t" OP_RM32 OP_R32),
	I(0x0b, IF_MODRM|IF_REXW,"orq\t" OP_RM64 OP_R64),
	I(0x0c, 0,               "orb\t" OP_U8   OP_AL),
	I(0x0d, IF_66,           "orw\t" OP_U16  OP_AX),
	I(0x0d, 0,               "orl\t" OP_U32  OP_EAX),
	I(0x0d, IF_REXW,         "orq\t" OP_S32  OP_RAX),

	I(0x0e, IF_66,           "pushw\t" OP_CS),
	I(0x0e, 0,               "pushl\t" OP_CS),

	I(0x10, IF_MODRM,        "adcb\t" OP_R8   OP_RM8),
	I(0x11, IF_66|IF_MODRM,  "adcw\t" OP_R16  OP_RM16),
	I(0x11, IF_MODRM,        "adcl\t" OP_R32  OP_RM32),
	I(0x11, IF_MODRM|IF_REXW,"adcq\t" OP_R64  OP_RM64),
	I(0x12, IF_MODRM,        "adcb\t" OP_RM8  OP_R32),
	I(0x13, IF_66|IF_MODRM,  "adcw\t" OP_RM16 OP_R32),
	I(0x13, IF_MODRM,        "adcl\t" OP_RM32 OP_R32),
	I(0x13, IF_MODRM|IF_REXW,"adcq\t" OP_RM64 OP_R64),
	I(0x14, 0,               "adcb\t" OP_U8   OP_AL),
	I(0x15, IF_66,           "adcw\t" OP_U16  OP_AX),
	I(0x15, 0,               "adcl\t" OP_U32  OP_EAX),
	I(0x15, IF_REXW,         "adcq\t" OP_S32  OP_RAX),

	I(0x16, IF_66,           "pushw\t" OP_SS),
	I(0x16, 0,               "pushl\t" OP_SS),
	I(0x17, IF_66,           "popw\t" OP_SS),
	I(0x17, 0,               "popl\t" OP_SS),

	I(0x18, IF_MODRM,        "sbbb\t" OP_R8   OP_RM8),
	I(0x19, IF_66|IF_MODRM,  "sbbw\t" OP_R16  OP_RM16),
	I(0x19, IF_MODRM,        "sbbl\t" OP_R32  OP_RM32),
	I(0x19, IF_MODRM|IF_REXW,"sbbq\t" OP_R64  OP_RM64),
	I(0x1a, IF_MODRM,        "sbbb\t" OP_RM8  OP_R32),
	I(0x1b, IF_66|IF_MODRM,  "sbbw\t" OP_RM16 OP_R32),
	I(0x1b, IF_MODRM,        "sbbl\t" OP_RM32 OP_R32),
	I(0x1b, IF_MODRM|IF_REXW,"sbbq\t" OP_RM64 OP_R64),
	I(0x1c, 0,               "sbbb\t" OP_U8   OP_AL),
	I(0x1d, IF_66,           "sbbw\t" OP_U16  OP_AX),
	I(0x1d, 0,               "sbbl\t" OP_U32  OP_EAX),
	I(0x1d, IF_REXW,         "sbbq\t" OP_S32  OP_RAX),

	I(0x1e, IF_66,           "pushw\t" OP_DS),
	I(0x1e, 0,               "pushl\t" OP_DS),
	I(0x1f, IF_66,           "popw\t" OP_DS),
	I(0x1f, 0,               "popl\t" OP_DS),

	I(0x20, IF_MODRM,        "andb\t" OP_R8   OP_RM8),
	I(0x21, IF_66|IF_MODRM,  "andw\t" OP_R16  OP_RM16),
	I(0x21, IF_MODRM,        "andl\t" OP_R32  OP_RM32),
	I(0x21, IF_MODRM|IF_REXW,"andq\t" OP_R64  OP_RM64),
	I(0x22, IF_MODRM,        "andb\t" OP_RM8  OP_R32),
	I(0x23, IF_66|IF_MODRM,  "andw\t" OP_RM16 OP_R32),
	I(0x23, IF_MODRM,        "andl\t" OP_RM32 OP_R32),
	I(0x23, IF_MODRM|IF_REXW,"andq\t" OP_RM64 OP_R64),
	I(0x24, 0,               "andb\t" OP_U8   OP_AL),
	I(0x25, IF_66,           "andw\t" OP_U16  OP_AX),
	I(0x25, 0,               "andl\t" OP_U32  OP_EAX),
	I(0x25, IF_REXW,         "andq\t" OP_S32  OP_RAX),

	/* 0x26 -- PREFIX */
	I(0x27, 0,               "daa"),

	I(0x28, IF_MODRM,        "subb\t" OP_R8   OP_RM8),
	I(0x29, IF_66|IF_MODRM,  "subw\t" OP_R16  OP_RM16),
	I(0x29, IF_MODRM,        "subl\t" OP_R32  OP_RM32),
	I(0x29, IF_MODRM|IF_REXW,"subq\t" OP_R64  OP_RM64),
	I(0x2a, IF_MODRM,        "subb\t" OP_RM8  OP_R32),
	I(0x2b, IF_66|IF_MODRM,  "subw\t" OP_RM16 OP_R32),
	I(0x2b, IF_MODRM,        "subl\t" OP_RM32 OP_R32),
	I(0x2b, IF_MODRM|IF_REXW,"subq\t" OP_RM64 OP_R64),
	I(0x2c, 0,               "subb\t" OP_U8   OP_AL),
	I(0x2d, IF_66,           "subw\t" OP_U16  OP_AX),
	I(0x2d, 0,               "subl\t" OP_U32  OP_EAX),
	I(0x2d, IF_REXW,         "subq\t" OP_S32  OP_RAX),

	/* 0x2e -- PREFIX */
	I(0x2f, 0,               "das"),

	I(0x30, IF_MODRM,        "xorb\t" OP_R8   OP_RM8),
	I(0x31, IF_66|IF_MODRM,  "xorw\t" OP_R16  OP_RM16),
	I(0x31, IF_MODRM,        "xorl\t" OP_R32  OP_RM32),
	I(0x31, IF_MODRM|IF_REXW,"xorq\t" OP_R64  OP_RM64),
	I(0x32, IF_MODRM,        "xorb\t" OP_RM8  OP_R32),
	I(0x33, IF_66|IF_MODRM,  "xorw\t" OP_RM16 OP_R32),
	I(0x33, IF_MODRM,        "xorl\t" OP_RM32 OP_R32),
	I(0x33, IF_MODRM|IF_REXW,"xorq\t" OP_RM64 OP_R64),
	I(0x34, 0,               "xorb\t" OP_U8   OP_AL),
	I(0x35, IF_66,           "xorw\t" OP_U16  OP_AX),
	I(0x35, 0,               "xorl\t" OP_U32  OP_EAX),
	I(0x35, IF_REXW,         "xorq\t" OP_S32  OP_RAX),

	/* 0x36 -- PREFIX */
	I(0x37, 0,               "aaa"),

	I(0x38, IF_MODRM,        "cmpb\t" OP_R8   OP_RM8),
	I(0x39, IF_66|IF_MODRM,  "cmpw\t" OP_R16  OP_RM16),
	I(0x39, IF_MODRM,        "cmpl\t" OP_R32  OP_RM32),
	I(0x39, IF_MODRM|IF_REXW,"cmpq\t" OP_R64  OP_RM64),
	I(0x3a, IF_MODRM,        "cmpb\t" OP_RM8  OP_R32),
	I(0x3b, IF_66|IF_MODRM,  "cmpw\t" OP_RM16 OP_R32),
	I(0x3b, IF_MODRM,        "cmpl\t" OP_RM32 OP_R32),
	I(0x3b, IF_MODRM|IF_REXW,"cmpq\t" OP_RM64 OP_R64),
	I(0x3c, 0,               "cmpb\t" OP_U8   OP_AL),
	I(0x3d, IF_66,           "cmpw\t" OP_U16  OP_AX),
	I(0x3d, 0,               "cmpl\t" OP_U32  OP_EAX),
	I(0x3d, IF_REXW,         "cmpq\t" OP_S32  OP_RAX),

	/* 0x3e -- PREFIX */
	I(0x3f, 0,               "aas"),

	I(0x40, IF_66,           "incw\t" OP_AX),
	I(0x40, 0,               "incl\t" OP_EAX),
	I(0x41, IF_66,           "incw\t" OP_CX),
	I(0x41, 0,               "incl\t" OP_ECX),
	I(0x42, IF_66,           "incw\t" OP_DX),
	I(0x42, 0,               "incl\t" OP_EDX),
	I(0x43, IF_66,           "incw\t" OP_BX),
	I(0x43, 0,               "incl\t" OP_EBX),
	I(0x44, IF_66,           "incw\t" OP_SP),
	I(0x44, 0,               "incl\t" OP_ESP),
	I(0x45, IF_66,           "incw\t" OP_BP),
	I(0x45, 0,               "incl\t" OP_EBP),
	I(0x46, IF_66,           "incw\t" OP_SI),
	I(0x46, 0,               "incl\t" OP_ESI),
	I(0x47, IF_66,           "incw\t" OP_DI),
	I(0x47, 0,               "incl\t" OP_EDI),

	I(0x48, IF_66,           "decw\t" OP_AX),
	I(0x48, 0,               "decl\t" OP_EAX),
	I(0x49, IF_66,           "decw\t" OP_CX),
	I(0x49, 0,               "decl\t" OP_ECX),
	I(0x4a, IF_66,           "decw\t" OP_DX),
	I(0x4a, 0,               "decl\t" OP_EDX),
	I(0x4b, IF_66,           "decw\t" OP_BX),
	I(0x4b, 0,               "decl\t" OP_EBX),
	I(0x4c, IF_66,           "decw\t" OP_SP),
	I(0x4c, 0,               "decl\t" OP_ESP),
	I(0x4d, IF_66,           "decw\t" OP_BP),
	I(0x4d, 0,               "decl\t" OP_EBP),
	I(0x4e, IF_66,           "decw\t" OP_SI),
	I(0x4e, 0,               "decl\t" OP_ESI),
	I(0x4f, IF_66,           "decw\t" OP_DI),
	I(0x4f, 0,               "decl\t" OP_EDI),

	I(0x50, IF_66,           "pushw\t" OP_AX),
	I(0x50, IF_REXB,         "pushq\t" OP_X64_R8),
	I(0x50, IF_X32,          "pushl\t" OP_EAX),
	I(0x50, IF_X64,          "pushq\t" OP_RAX),
	I(0x51, IF_66,           "pushw\t" OP_CX),
	I(0x51, IF_REXB,         "pushq\t" OP_R9),
	I(0x51, IF_X32,          "pushl\t" OP_ECX),
	I(0x51, IF_X64,          "pushq\t" OP_RCX),
	I(0x52, IF_66,           "pushw\t" OP_DX),
	I(0x52, IF_REXB,         "pushq\t" OP_R10),
	I(0x52, IF_X32,          "pushl\t" OP_EDX),
	I(0x52, IF_X64,          "pushq\t" OP_RDX),
	I(0x53, IF_66,           "pushw\t" OP_BX),
	I(0x53, IF_REXB,         "pushq\t" OP_R11),
	I(0x53, IF_X32,          "pushl\t" OP_EBX),
	I(0x53, IF_X64,          "pushq\t" OP_RBX),
	I(0x54, IF_66,           "pushw\t" OP_SP),
	I(0x54, IF_REXB,         "pushq\t" OP_R12),
	I(0x54, IF_X32,          "pushl\t" OP_ESP),
	I(0x54, IF_X64,          "pushq\t" OP_RSP),
	I(0x55, IF_66,           "pushw\t" OP_BP),
	I(0x55, IF_REXB,         "pushq\t" OP_R13),
	I(0x55, IF_X32,          "pushl\t" OP_EBP),
	I(0x55, IF_X64,          "pushq\t" OP_RBP),
	I(0x56, IF_66,           "pushw\t" OP_SI),
	I(0x56, IF_REXB,         "pushq\t" OP_R14),
	I(0x56, IF_X32,          "pushl\t" OP_ESI),
	I(0x56, IF_X64,          "pushq\t" OP_RSI),
	I(0x57, IF_66,           "pushw\t" OP_DI),
	I(0x57, IF_REXB,         "pushq\t" OP_R15),
	I(0x57, IF_X32,          "pushl\t" OP_EDI),
	I(0x57, IF_X64,          "pushq\t" OP_RDI),

	I(0x58, IF_66,           "popw\t" OP_AX),
	I(0x58, IF_REXB,         "popq\t" OP_X64_R8),
	I(0x58, IF_X32,          "popl\t" OP_EAX),
	I(0x58, IF_X64,          "popq\t" OP_RAX),
	I(0x59, IF_66,           "popw\t" OP_CX),
	I(0x59, IF_REXB,         "popq\t" OP_R9),
	I(0x59, IF_X32,          "popl\t" OP_ECX),
	I(0x59, IF_X64,          "popq\t" OP_RCX),
	I(0x5a, IF_66,           "popw\t" OP_DX),
	I(0x5a, IF_REXB,         "popq\t" OP_R10),
	I(0x5a, IF_X32,          "popl\t" OP_EDX),
	I(0x5a, IF_X64,          "popq\t" OP_RDX),
	I(0x5b, IF_66,           "popw\t" OP_BX),
	I(0x5b, IF_REXB,         "popq\t" OP_R11),
	I(0x5b, IF_X32,          "popl\t" OP_EBX),
	I(0x5b, IF_X64,          "popq\t" OP_RBX),
	I(0x5c, IF_66,           "popw\t" OP_SP),
	I(0x5c, IF_REXB,         "popq\t" OP_R12),
	I(0x5c, IF_X32,          "popl\t" OP_ESP),
	I(0x5c, IF_X64,          "popq\t" OP_RSP),
	I(0x5d, IF_66,           "popw\t" OP_BP),
	I(0x5d, IF_REXB,         "popq\t" OP_R13),
	I(0x5d, IF_X32,          "popl\t" OP_EBP),
	I(0x5d, IF_X64,          "popq\t" OP_RBP),
	I(0x5e, IF_66,           "popw\t" OP_SI),
	I(0x5e, IF_REXB,         "popq\t" OP_R14),
	I(0x5e, IF_X32,          "popl\t" OP_ESI),
	I(0x5e, IF_X64,          "popq\t" OP_RSI),
	I(0x5f, IF_66,           "popw\t" OP_DI),
	I(0x5f, IF_REXB,         "popq\t" OP_R15),
	I(0x5f, IF_X32,          "popl\t" OP_EDI),
	I(0x5f, IF_X64,          "popq\t" OP_RDI),

	I(0x60, IF_66,           "pushaw"),
	I(0x60, 0,               "pushal"),

	I(0x61, IF_66,           "popaw"),
	I(0x61, 0,               "popal"),

	I(0x62, IF_66|IF_MODRM,  "boundw\t" OP_RM32 OP_R16),
	I(0x62, IF_MODRM,        "boundl\t" OP_RM64 OP_R32),

	I(0x63, IF_MODRM,        "arpl\t" OP_R16 OP_RM16),

	/* 0x64 -- PREFIX */
	/* 0x65 -- PREFIX */
	/* 0x66 -- PREFIX */
	/* 0x67 -- PREFIX */

	I(0x68, IF_66,           "pushw\t" OP_U16),
	I(0x68, 0,               "pushl\t" OP_U32),
	I(0x68, IF_REXW,         "pushq\t" OP_S32),

	I(0x69, IF_66|IF_MODRM,  "imulw\t" OP_U16 OP_RM16 OP_R16),
	I(0x69, IF_MODRM,        "imull\t" OP_U32 OP_RM32 OP_R32),
	I(0x69, IF_MODRM|IF_REXW,"imulq\t" OP_S32 OP_RM64 OP_R64),

	I(0x6a, 0,               "pushl\t" OP_S8),

	I(0x6b, IF_66|IF_MODRM,  "imulw\t" OP_U8 OP_RM16 OP_R16),
	I(0x6b, IF_MODRM,        "imull\t" OP_U8 OP_RM32 OP_R32),
	I(0x6b, IF_MODRM|IF_REXW,"imulq\t" OP_U8 OP_RM64 OP_R64),

	I(0x6c, 0,               "insb"),
	I(0x6c, IF_F3,           "rep insb"),
	I(0x6d, IF_66,           "insw"),
	I(0x6d, 0,               "insl"),
	I(0x6d, IF_F3|IF_66,     "rep insw"),
	I(0x6d, IF_F3,           "rep insl"),

	I(0x6e, 0,               "outsb"),
	I(0x6e, IF_F3,           "rep outsb"),
	I(0x6f, IF_66,           "outsw"),
	I(0x6f, 0,               "outsl"),
	I(0x6f, IF_F3|IF_66,     "rep outsw"),
	I(0x6f, IF_F3,           "rep outsl"),

	I(0x70, 0,               "j" NAME_jc0 "\t" OP_DISP8),
	I(0x71, 0,               "j" NAME_jc1 "\t" OP_DISP8),
	I(0x72, 0,               "j" NAME_jc2 "\t" OP_DISP8),
	I(0x73, 0,               "j" NAME_jc3 "\t" OP_DISP8),
	I(0x74, 0,               "j" NAME_jc4 "\t" OP_DISP8),
	I(0x75, 0,               "j" NAME_jc5 "\t" OP_DISP8),
	I(0x76, 0,               "j" NAME_jc6 "\t" OP_DISP8),
	I(0x77, 0,               "j" NAME_jc7 "\t" OP_DISP8),
	I(0x78, 0,               "j" NAME_jc8 "\t" OP_DISP8),
	I(0x79, 0,               "j" NAME_jc9 "\t" OP_DISP8),
	I(0x7a, 0,               "j" NAME_jca "\t" OP_DISP8),
	I(0x7b, 0,               "j" NAME_jcb "\t" OP_DISP8),
	I(0x7c, 0,               "j" NAME_jcc "\t" OP_DISP8),
	I(0x7d, 0,               "j" NAME_jcd "\t" OP_DISP8),
	I(0x7e, 0,               "j" NAME_jce "\t" OP_DISP8),
	I(0x7f, 0,               "j" NAME_jcf "\t" OP_DISP8),

	I(0x80, IF_MODRM|IF_REG0, "addb\t" OP_U8 OP_RM8),
	I(0x80, IF_MODRM|IF_REG1, "orb\t"  OP_U8 OP_RM8),
	I(0x80, IF_MODRM|IF_REG2, "adcb\t" OP_U8 OP_RM8),
	I(0x80, IF_MODRM|IF_REG3, "sbbb\t" OP_U8 OP_RM8),
	I(0x80, IF_MODRM|IF_REG4, "andb\t" OP_U8 OP_RM8),
	I(0x80, IF_MODRM|IF_REG5, "subb\t" OP_U8 OP_RM8),
	I(0x80, IF_MODRM|IF_REG6, "xorb\t" OP_U8 OP_RM8),
	I(0x80, IF_MODRM|IF_REG7, "cmpb\t" OP_U8 OP_RM8),

	I(0x81, IF_66|IF_MODRM|IF_REG0, "addw\t" OP_U16 OP_RM16),
	I(0x81, IF_MODRM|IF_REG0, "addl\t" OP_U32 OP_RM32),
	I(0x81, IF_MODRM|IF_REXW|IF_REG0, "addq\t" OP_S32 OP_RM32),

	I(0x81, IF_66|IF_MODRM|IF_REG1, "orw\t"  OP_U16 OP_RM16),
	I(0x81, IF_MODRM|IF_REG1, "orl\t"  OP_U32 OP_RM32),
	I(0x81, IF_MODRM|IF_REXW|IF_REG1, "orq\t"  OP_S32 OP_RM32),

	I(0x81, IF_66|IF_MODRM|IF_REG2, "adcw\t" OP_U16 OP_RM16),
	I(0x81, IF_MODRM|IF_REG2, "adcl\t" OP_U32 OP_RM32),
	I(0x81, IF_MODRM|IF_REXW|IF_REG2, "adcq\t" OP_S32 OP_RM32),

	I(0x81, IF_66|IF_MODRM|IF_REG3, "sbbw\t" OP_U16 OP_RM16),
	I(0x81, IF_MODRM|IF_REG3, "sbbl\t" OP_U32 OP_RM32),
	I(0x81, IF_MODRM|IF_REXW|IF_REG3, "sbbq\t" OP_S32 OP_RM32),

	I(0x81, IF_66|IF_MODRM|IF_REG4, "andw\t" OP_U16 OP_RM16),
	I(0x81, IF_MODRM|IF_REG4, "andl\t" OP_U32 OP_RM32),
	I(0x81, IF_MODRM|IF_REXW|IF_REG4, "andq\t" OP_S32 OP_RM32),

	I(0x81, IF_66|IF_MODRM|IF_REG5, "subw\t" OP_U16 OP_RM16),
	I(0x81, IF_MODRM|IF_REG5, "subl\t" OP_U32 OP_RM32),
	I(0x81, IF_MODRM|IF_REXW|IF_REG5, "subq\t" OP_S32 OP_RM32),

	I(0x81, IF_66|IF_MODRM|IF_REG6, "xorw\t" OP_U16 OP_RM16),
	I(0x81, IF_MODRM|IF_REG6, "xorl\t" OP_U32 OP_RM32),
	I(0x81, IF_MODRM|IF_REXW|IF_REG6, "xorq\t" OP_S32 OP_RM32),

	I(0x81, IF_66|IF_MODRM|IF_REG7, "cmpw\t" OP_U16 OP_RM16),
	I(0x81, IF_MODRM|IF_REG7, "cmpl\t" OP_U32 OP_RM32),
	I(0x81, IF_MODRM|IF_REXW|IF_REG7, "cmpq\t" OP_S32 OP_RM32),

	/* 0x82 is an alias for 0x80, but is only valid in 32-bit mode (not in 64-bit mode!) */
	I(0x82, IF_X32|IF_MODRM|IF_REG0, "addb\t" OP_U8 OP_RM8),
	I(0x82, IF_X32|IF_MODRM|IF_REG1, "orb\t"  OP_U8 OP_RM8),
	I(0x82, IF_X32|IF_MODRM|IF_REG2, "adcb\t" OP_U8 OP_RM8),
	I(0x82, IF_X32|IF_MODRM|IF_REG3, "sbbb\t" OP_U8 OP_RM8),
	I(0x82, IF_X32|IF_MODRM|IF_REG4, "andb\t" OP_U8 OP_RM8),
	I(0x82, IF_X32|IF_MODRM|IF_REG5, "subb\t" OP_U8 OP_RM8),
	I(0x82, IF_X32|IF_MODRM|IF_REG6, "xorb\t" OP_U8 OP_RM8),
	I(0x82, IF_X32|IF_MODRM|IF_REG7, "cmpb\t" OP_U8 OP_RM8),

	I(0x83, IF_66|IF_MODRM|IF_REG0, "addw\t" OP_S8 OP_RM16),
	I(0x83, IF_MODRM|IF_REG0, "addl\t" OP_S8 OP_RM32),
	I(0x83, IF_MODRM|IF_REXW|IF_REG0, "addq\t" OP_S8 OP_RM64),

	I(0x83, IF_66|IF_MODRM|IF_REG1, "orw\t"  OP_S8 OP_RM16),
	I(0x83, IF_MODRM|IF_REG1, "orl\t"  OP_S8 OP_RM32),
	I(0x83, IF_MODRM|IF_REXW|IF_REG1, "orq\t"  OP_S8 OP_RM64),

	I(0x83, IF_66|IF_MODRM|IF_REG2, "adcw\t" OP_S8 OP_RM16),
	I(0x83, IF_MODRM|IF_REG2, "adcl\t" OP_S8 OP_RM32),
	I(0x83, IF_MODRM|IF_REXW|IF_REG2, "adcq\t" OP_S8 OP_RM64),

	I(0x83, IF_66|IF_MODRM|IF_REG3, "sbbw\t" OP_S8 OP_RM16),
	I(0x83, IF_MODRM|IF_REG3, "sbbl\t" OP_S8 OP_RM32),
	I(0x83, IF_MODRM|IF_REXW|IF_REG3, "sbbq\t" OP_S8 OP_RM64),

	I(0x83, IF_66|IF_MODRM|IF_REG4, "andw\t" OP_S8 OP_RM16),
	I(0x83, IF_MODRM|IF_REG4, "andl\t" OP_S8 OP_RM32),
	I(0x83, IF_MODRM|IF_REXW|IF_REG4, "andq\t" OP_S8 OP_RM64),

	I(0x83, IF_66|IF_MODRM|IF_REG5, "subw\t" OP_S8 OP_RM16),
	I(0x83, IF_MODRM|IF_REG5, "subl\t" OP_S8 OP_RM32),
	I(0x83, IF_MODRM|IF_REXW|IF_REG5, "subq\t" OP_S8 OP_RM64),

	I(0x83, IF_66|IF_MODRM|IF_REG6, "xorw\t" OP_S8 OP_RM16),
	I(0x83, IF_MODRM|IF_REG6, "xorl\t" OP_S8 OP_RM32),
	I(0x83, IF_MODRM|IF_REXW|IF_REG6, "xorq\t" OP_S8 OP_RM64),

	I(0x83, IF_66|IF_MODRM|IF_REG7, "cmpw\t" OP_S8 OP_RM16),
	I(0x83, IF_MODRM|IF_REG7, "cmpl\t" OP_S8 OP_RM32),
	I(0x83, IF_MODRM|IF_REXW|IF_REG7, "cmpq\t" OP_S8 OP_RM64),

	I(0x84, IF_MODRM,         "testb\t" OP_R8 OP_RM8),
	I(0x85, IF_66|IF_MODRM,   "testw\t" OP_R16 OP_RM16),
	I(0x85, IF_MODRM,         "testl\t" OP_R32 OP_RM32),
	I(0x85, IF_MODRM|IF_REXW, "testq\t" OP_R64 OP_RM64),

	I(0x86, IF_MODRM,         "xchgb\t" OP_R8 OP_RM8),
	I(0x87, IF_66|IF_MODRM,   "xchgw\t" OP_R16 OP_RM16),
	I(0x87, IF_MODRM,         "xchgl\t" OP_R32 OP_RM32),
	I(0x87, IF_MODRM|IF_REXW, "xchgq\t" OP_R64 OP_RM64),

	I(0x88, IF_MODRM,         "movb\t" OP_R8 OP_RM8),
	I(0x89, IF_66|IF_MODRM,   "movw\t" OP_R16 OP_RM16),
	I(0x89, IF_MODRM,         "movl\t" OP_R32 OP_RM32),
	I(0x89, IF_MODRM|IF_REXW, "movq\t" OP_R64 OP_RM64),

	I(0x8a, IF_MODRM,         "movb\t" OP_RM8 OP_R8),
	I(0x8b, IF_66|IF_MODRM,   "movw\t" OP_RM16 OP_R16),
	I(0x8b, IF_MODRM,         "movl\t" OP_RM32 OP_R32),
	I(0x8b, IF_MODRM|IF_REXW, "movq\t" OP_RM64 OP_R64),

	I(0x8c, IF_66|IF_MODRM,   "movw\t" OP_RSEG OP_RM16),
	I(0x8c, IF_MODRM,         "movl\t" OP_RSEG OP_RM32),
	I(0x8c, IF_MODRM|IF_REXW, "movq\t" OP_RSEG OP_RM64),

	I(0x8d, IF_66|IF_MODRM,   "leaw\t" OP_RM16 OP_R16),
	I(0x8d, IF_MODRM,         "leal\t" OP_RM32 OP_R32),
	I(0x8d, IF_MODRM|IF_REXW, "leaq\t" OP_RM64 OP_R64),

	I(0x8e, IF_66|IF_MODRM,   "movw\t" OP_RM16 OP_RSEG),
	I(0x8e, IF_MODRM,         "movl\t" OP_RM32 OP_RSEG),
	I(0x8e, IF_MODRM|IF_REXW, "movq\t" OP_RM64 OP_RSEG),

	I(0x8f, IF_66|IF_MODRM,         "popw\t" OP_RM16),
	I(0x8f, IF_MODRM,               "popl\t" OP_RM32),
	I(0x8f, IF_MODRM|IF_REXW,       "popq\t" OP_RM64),
	I(0x8f, IF_67|IF_66|IF_MODRM,   "popw\t" OP_RM16),
	I(0x8f, IF_67|IF_MODRM,         "popl\t" OP_RM32),
	I(0x8f, IF_67|IF_MODRM|IF_REXW, "popq\t" OP_RM64),

	I(0x90, 0,                "nop"),
	I(0x90, IF_F3,            "pause"),

	I(0x90, IF_REXB|IF_66,    "xchgw\t" OP_R8W OP_AX),
	I(0x90, IF_REXB,          "xchgl\t" OP_R8D OP_EAX),
	I(0x90, IF_REXB|IF_REXW,  "xchgq\t" OP_X64_R8 OP_RAX),
	I(0x90, IF_66,            "xchgw\t" OP_AX  OP_AX),
/*  I(0x90, 0,                "xchgl\t" OP_EAX OP_EAX), */
	I(0x90, IF_REXW,          "xchgq\t" OP_RAX OP_RAX),
	I(0x91, IF_REXB|IF_66,    "xchgw\t" OP_R9W OP_AX),
	I(0x91, IF_REXB,          "xchgl\t" OP_R9D OP_EAX),
	I(0x91, IF_REXB|IF_REXW,  "xchgq\t" OP_R9  OP_RAX),
	I(0x91, IF_66,            "xchgw\t" OP_CX  OP_AX),
	I(0x91, 0,                "xchgl\t" OP_ECX OP_EAX),
	I(0x91, IF_REXW,          "xchgq\t" OP_RCX OP_RAX),
	I(0x92, IF_REXB|IF_66,    "xchgw\t" OP_R10W OP_AX),
	I(0x92, IF_REXB,          "xchgl\t" OP_R10D OP_EAX),
	I(0x92, IF_REXB|IF_REXW,  "xchgq\t" OP_R10 OP_RAX),
	I(0x92, IF_66,            "xchgw\t" OP_DX  OP_AX),
	I(0x92, 0,                "xchgl\t" OP_EDX OP_EAX),
	I(0x92, IF_REXW,          "xchgq\t" OP_RDX OP_RAX),
	I(0x93, IF_REXB|IF_66,    "xchgw\t" OP_R11W OP_AX),
	I(0x93, IF_REXB,          "xchgl\t" OP_R11D OP_EAX),
	I(0x93, IF_REXB|IF_REXW,  "xchgq\t" OP_R11 OP_RAX),
	I(0x93, IF_66,            "xchgw\t" OP_BX  OP_AX),
	I(0x93, 0,                "xchgl\t" OP_EBX OP_EAX),
	I(0x93, IF_REXW,          "xchgq\t" OP_RBX OP_RAX),
	I(0x94, IF_REXB|IF_66,    "xchgw\t" OP_R12W OP_AX),
	I(0x94, IF_REXB,          "xchgl\t" OP_R12D OP_EAX),
	I(0x94, IF_REXB|IF_REXW,  "xchgq\t" OP_R12 OP_RAX),
	I(0x94, IF_66,            "xchgw\t" OP_SP  OP_AX),
	I(0x94, 0,                "xchgl\t" OP_ESP OP_EAX),
	I(0x94, IF_REXW,          "xchgq\t" OP_RSP OP_RAX),
	I(0x95, IF_REXB|IF_66,    "xchgw\t" OP_R13W OP_AX),
	I(0x95, IF_REXB,          "xchgl\t" OP_R13D OP_EAX),
	I(0x95, IF_REXB|IF_REXW,  "xchgq\t" OP_R13 OP_RAX),
	I(0x95, IF_66,            "xchgw\t" OP_BP  OP_AX),
	I(0x95, 0,                "xchgl\t" OP_EBP OP_EAX),
	I(0x95, IF_REXW,          "xchgq\t" OP_RBP OP_RAX),
	I(0x96, IF_REXB|IF_66,    "xchgw\t" OP_R14W OP_AX),
	I(0x96, IF_REXB,          "xchgl\t" OP_R14D OP_EAX),
	I(0x96, IF_REXB|IF_REXW,  "xchgq\t" OP_R14 OP_RAX),
	I(0x96, IF_66,            "xchgw\t" OP_DI  OP_AX),
	I(0x96, 0,                "xchgl\t" OP_EDI OP_EAX),
	I(0x96, IF_REXW,          "xchgq\t" OP_RDI OP_RAX),
	I(0x97, IF_REXB|IF_66,    "xchgw\t" OP_R15W OP_AX),
	I(0x97, IF_REXB,          "xchgl\t" OP_R15D OP_EAX),
	I(0x97, IF_REXB|IF_REXW,  "xchgq\t" OP_R15 OP_RAX),
	I(0x97, IF_66,            "xchgw\t" OP_SI  OP_AX),
	I(0x97, 0,                "xchgl\t" OP_ESI OP_EAX),
	I(0x97, IF_REXW,          "xchgq\t" OP_RSI OP_RAX),

	I(0x98, 0,                "cbw"),
	I(0x99, IF_66,            "cwd"),
	I(0x99, 0,                "cdq"),
	I(0x9a, IF_67,            "lcallw\t" OP_LJMP),
	I(0x9a, 0,                "lcalll\t" OP_LJMP),

	I(0x9b, IF_66,            "wait"),
	I(0x9b, 0,                "fwait"),

	I(0x9c, IF_66,            "pushfw"),
	I(0x9c, IF_X32,           "pushfl"),
	I(0x9c, IF_X64,           "pushfq"),
	I(0x9d, IF_66,            "popfw"),
	I(0x9d, IF_X32,           "popfl"),
	I(0x9d, IF_X64,           "popfq"),

	I(0x9e, 0,                "sahf"),
	I(0x9f, 0,                "lahf"),

	I(0xa0, 0,                "movb\t" OP_MOFFS8 OP_AL),
	I(0xa0, IF_REXW,          "movb\t" OP_MOFFS8 OP_AL),   /* XXX: This variant ignores segment overrides... */
	I(0xa1, IF_67|IF_66,      "movw\t" OP_MOFFS16 OP_AX),
	I(0xa1, IF_67,            "movl\t" OP_MOFFS16 OP_EAX),
	I(0xa1, IF_66,            "movw\t" OP_MOFFS32 OP_AX),
	I(0xa1, 0,                "movl\t" OP_MOFFS32 OP_EAX),
	I(0xa2, 0,                "movb\t" OP_AL OP_MOFFS8),
	I(0xa2, IF_REXW,          "movb\t" OP_AL OP_MOFFS8),   /* XXX: This variant ignores segment overrides... */
	I(0xa3, IF_67|IF_66,      "movw\t" OP_AX OP_MOFFS16),
	I(0xa3, IF_67,            "movl\t" OP_EAX OP_MOFFS16),
	I(0xa3, IF_66,            "movw\t" OP_AX OP_MOFFS32),
	I(0xa3, 0,                "movl\t" OP_EAX OP_MOFFS32),

	I(0xa4, 0,                "movsb"),
	I(0xa4, IF_F3,            "rep movsb"),
	I(0xa5, IF_66,            "movsw"),
	I(0xa5, 0,                "movsl"),
	I(0xa5, IF_REXW,          "movsq"),
	I(0xa5, IF_F3|IF_66,      "rep movsw"),
	I(0xa5, IF_F3,            "rep movsl"),
	I(0xa5, IF_F3|IF_REXW,    "rep movsq"),

	I(0xa6, 0,                "cmpsb"),
	I(0xa6, IF_F2,            "repne cmpsb"),
	I(0xa6, IF_F3,            "repe cmpsb"),
	I(0xa7, IF_66,            "cmpsw"),
	I(0xa7, 0,                "cmpsl"),
	I(0xa7, IF_REXW,          "cmpsq"),
	I(0xa7, IF_F2|IF_66,      "repne cmpsw"),
	I(0xa7, IF_F3|IF_66,      "repe cmpsw"),
	I(0xa7, IF_F2,            "repne cmpsl"),
	I(0xa7, IF_F3,            "repe cmpsl"),
	I(0xa7, IF_F2|IF_REXW,    "repne cmpsq"),
	I(0xa7, IF_F3|IF_REXW,    "repe cmpsq"),

	I(0xa8, 0,                "testb\t" OP_U8 OP_AL),
	I(0xa9, IF_66,            "testw\t" OP_U16 OP_AX),
	I(0xa9, 0,                "testl\t" OP_U32 OP_EAX),
	I(0xa9, IF_REXW,          "testq\t" OP_S32 OP_RAX),

	I(0xaa, 0,                "stosb"),
	I(0xaa, IF_F3,            "rep stosb"),
	I(0xab, IF_66,            "stosw"),
	I(0xab, 0,                "stosl"),
	I(0xab, IF_REXW,          "stosq"),
	I(0xab, IF_F3|IF_66,      "rep stosw"),
	I(0xab, IF_F3,            "rep stosl"),
	I(0xab, IF_F3|IF_REXW,    "rep stosq"),

	I(0xac, 0,                "lodsb"),
	I(0xac, IF_F3,            "rep lodsb"),
	I(0xad, IF_66,            "lodsw"),
	I(0xad, 0,                "lodsl"),
	I(0xad, IF_REXW,          "lodsq"),
	I(0xad, IF_F3|IF_66,      "rep lodsw"),
	I(0xad, IF_F3,            "rep lodsl"),
	I(0xad, IF_F3|IF_REXW,    "rep lodsq"),

	I(0xae, 0,                "scasb"),
	I(0xae, IF_F2,            "repne scasb"),
	I(0xae, IF_F3,            "repe scasb"),
	I(0xaf, IF_66,            "scasw"),
	I(0xaf, 0,                "scasl"),
	I(0xaf, IF_REXW,          "scasq"),
	I(0xaf, IF_F2|IF_66,      "repne scasw"),
	I(0xaf, IF_F3|IF_66,      "repe scasw"),
	I(0xaf, IF_F2,            "repne scasl"),
	I(0xaf, IF_F3,            "repe scasl"),
	I(0xaf, IF_F2|IF_REXW,    "repne scasq"),
	I(0xaf, IF_F3|IF_REXW,    "repe scasq"),

	I(0xb0, IF_REXB,          "movb\t" OP_U8 OP_R8D),
	I(0xb0, 0,                "movb\t" OP_U8 OP_AL),
	I(0xb1, IF_REXB,          "movb\t" OP_U8 OP_R9D),
	I(0xb1, 0,                "movb\t" OP_U8 OP_CL),
	I(0xb2, IF_REXB,          "movb\t" OP_U8 OP_R10D),
	I(0xb2, 0,                "movb\t" OP_U8 OP_DL),
	I(0xb3, IF_REXB,          "movb\t" OP_U8 OP_R11D),
	I(0xb3, 0,                "movb\t" OP_U8 OP_BL),
	I(0xb4, IF_REXB,          "movb\t" OP_U8 OP_R12D),
	I(0xb4, 0,                "movb\t" OP_U8 OP_AH),
	I(0xb5, IF_REXB,          "movb\t" OP_U8 OP_R13D),
	I(0xb5, 0,                "movb\t" OP_U8 OP_CH),
	I(0xb6, IF_REXB,          "movb\t" OP_U8 OP_R14D),
	I(0xb6, 0,                "movb\t" OP_U8 OP_DH),
	I(0xb7, IF_REXB,          "movb\t" OP_U8 OP_R15D),
	I(0xb7, 0,                "movb\t" OP_U8 OP_BH),

	I(0xb8, IF_REXB|IF_66,    "movw\t"   OP_U16 OP_R8W),
	I(0xb8, IF_REXB,          "movl\t"   OP_U32 OP_R8D),
	I(0xb8, IF_REXB|IF_REXW,  "movabs\t" OP_U64 OP_X64_R8),
	I(0xb8, IF_66,            "movw\t"   OP_U16 OP_AX),
	I(0xb8, 0,                "movl\t"   OP_U32 OP_EAX),
	I(0xb8, IF_REXW,          "movabs\t" OP_U64 OP_RAX),
	I(0xb9, IF_REXB|IF_66,    "movw\t"   OP_U16 OP_R9W),
	I(0xb9, IF_REXB,          "movl\t"   OP_U32 OP_R9D),
	I(0xb9, IF_REXB|IF_REXW,  "movabs\t" OP_U64 OP_R9),
	I(0xb9, IF_66,            "movw\t"   OP_U16 OP_CX),
	I(0xb9, 0,                "movl\t"   OP_U32 OP_ECX),
	I(0xb9, IF_REXW,          "movabs\t" OP_U64 OP_RCX),
	I(0xba, IF_REXB|IF_66,    "movw\t"   OP_U16 OP_R10W),
	I(0xba, IF_REXB,          "movl\t"   OP_U32 OP_R10D),
	I(0xba, IF_REXB|IF_REXW,  "movabs\t" OP_U64 OP_R10),
	I(0xba, IF_66,            "movw\t"   OP_U16 OP_DX),
	I(0xba, 0,                "movl\t"   OP_U32 OP_EDX),
	I(0xba, IF_REXW,          "movabs\t" OP_U64 OP_RDX),
	I(0xbb, IF_REXB|IF_66,    "movw\t"   OP_U16 OP_R11W),
	I(0xbb, IF_REXB,          "movl\t"   OP_U32 OP_R11D),
	I(0xbb, IF_REXB|IF_REXW,  "movabs\t" OP_U64 OP_R11),
	I(0xbb, IF_66,            "movw\t"   OP_U16 OP_BX),
	I(0xbb, 0,                "movl\t"   OP_U32 OP_EBX),
	I(0xbb, IF_REXW,          "movabs\t" OP_U64 OP_RBX),
	I(0xbc, IF_REXB|IF_66,    "movw\t"   OP_U16 OP_R12W),
	I(0xbc, IF_REXB,          "movl\t"   OP_U32 OP_R12D),
	I(0xbc, IF_REXB|IF_REXW,  "movabs\t" OP_U64 OP_R12),
	I(0xbc, IF_66,            "movw\t"   OP_U16 OP_SP),
	I(0xbc, 0,                "movl\t"   OP_U32 OP_ESP),
	I(0xbc, IF_REXW,          "movabs\t" OP_U64 OP_RSP),
	I(0xbd, IF_REXB|IF_66,    "movw\t"   OP_U16 OP_R13W),
	I(0xbd, IF_REXB,          "movl\t"   OP_U32 OP_R13D),
	I(0xbd, IF_REXB|IF_REXW,  "movabs\t" OP_U64 OP_R13),
	I(0xbd, IF_66,            "movw\t"   OP_U16 OP_BP),
	I(0xbd, 0,                "movl\t"   OP_U32 OP_EBP),
	I(0xbd, IF_REXW,          "movabs\t" OP_U64 OP_RBP),
	I(0xbe, IF_REXB|IF_66,    "movw\t"   OP_U16 OP_R14W),
	I(0xbe, IF_REXB,          "movl\t"   OP_U32 OP_R14D),
	I(0xbe, IF_REXB|IF_REXW,  "movabs\t" OP_U64 OP_R14),
	I(0xbe, IF_66,            "movw\t"   OP_U16 OP_DI),
	I(0xbe, 0,                "movl\t"   OP_U32 OP_EDI),
	I(0xbe, IF_REXW,          "movabs\t" OP_U64 OP_RDI),
	I(0xbf, IF_REXB|IF_66,    "movw\t"   OP_U16 OP_R15W),
	I(0xbf, IF_REXB,          "movl\t"   OP_U32 OP_R15D),
	I(0xbf, IF_REXB|IF_REXW,  "movabs\t" OP_U64 OP_R15),
	I(0xbf, IF_66,            "movw\t"   OP_U16 OP_SI),
	I(0xbf, 0,                "movl\t"   OP_U32 OP_ESI),
	I(0xbf, IF_REXW,          "movabs\t" OP_U64 OP_RSI),

	I(0xc0, IF_MODRM|IF_REG0, "rolb\t" OP_U8 OP_RM8),
	I(0xc0, IF_MODRM|IF_REG1, "rorb\t" OP_U8 OP_RM8),
	I(0xc0, IF_MODRM|IF_REG2, "rclb\t" OP_U8 OP_RM8),
	I(0xc0, IF_MODRM|IF_REG3, "rcrb\t" OP_U8 OP_RM8),
	I(0xc0, IF_MODRM|IF_REG4, "salb\t" OP_U8 OP_RM8),
	I(0xc0, IF_MODRM|IF_REG5, "shrb\t" OP_U8 OP_RM8),
	I(0xc0, IF_MODRM|IF_REG6, "shlb\t" OP_U8 OP_RM8),
	I(0xc0, IF_MODRM|IF_REG7, "sarb\t" OP_U8 OP_RM8),

	I(0xc1, IF_66|IF_MODRM|IF_REG0, "rolw\t" OP_U8 OP_RM16),
	I(0xc1, IF_MODRM|IF_REG0, "roll\t" OP_U8 OP_RM32),
	I(0xc1, IF_MODRM|IF_REXW|IF_REG0, "rolq\t" OP_U8 OP_RM64),

	I(0xc1, IF_66|IF_MODRM|IF_REG1, "rorw\t" OP_U8 OP_RM16),
	I(0xc1, IF_MODRM|IF_REG1, "rorl\t" OP_U8 OP_RM32),
	I(0xc1, IF_MODRM|IF_REXW|IF_REG1, "rorq\t" OP_U8 OP_RM64),

	I(0xc1, IF_66|IF_MODRM|IF_REG2, "rclw\t" OP_U8 OP_RM16),
	I(0xc1, IF_MODRM|IF_REG2, "rcll\t" OP_U8 OP_RM32),
	I(0xc1, IF_MODRM|IF_REXW|IF_REG2, "rclq\t" OP_U8 OP_RM64),

	I(0xc1, IF_66|IF_MODRM|IF_REG3, "rcrw\t" OP_U8 OP_RM16),
	I(0xc1, IF_MODRM|IF_REG3, "rcrl\t" OP_U8 OP_RM32),
	I(0xc1, IF_MODRM|IF_REXW|IF_REG3, "rcrq\t" OP_U8 OP_RM64),

	I(0xc1, IF_66|IF_MODRM|IF_REG4, "salw\t" OP_U8 OP_RM16),
	I(0xc1, IF_MODRM|IF_REG4, "sall\t" OP_U8 OP_RM32),
	I(0xc1, IF_MODRM|IF_REXW|IF_REG4, "salq\t" OP_U8 OP_RM64),

	I(0xc1, IF_66|IF_MODRM|IF_REG5, "shrw\t" OP_U8 OP_RM16),
	I(0xc1, IF_MODRM|IF_REG5, "shrl\t" OP_U8 OP_RM32),
	I(0xc1, IF_MODRM|IF_REXW|IF_REG5, "shrq\t" OP_U8 OP_RM64),

	I(0xc1, IF_66|IF_MODRM|IF_REG6, "shlw\t" OP_U8 OP_RM16),
	I(0xc1, IF_MODRM|IF_REG6, "shll\t" OP_U8 OP_RM32),
	I(0xc1, IF_MODRM|IF_REXW|IF_REG6, "shlq\t" OP_U8 OP_RM64),

	I(0xc1, IF_66|IF_MODRM|IF_REG7, "sarw\t" OP_U8 OP_RM16),
	I(0xc1, IF_MODRM|IF_REG7, "sarl\t" OP_U8 OP_RM32),
	I(0xc1, IF_MODRM|IF_REXW|IF_REG7, "sarq\t" OP_U8 OP_RM64),

	I(0xc2, IF_66,            "retw\t" OP_U16),
	I(0xc2, 0,                "ret\t" OP_U16),
	I(0xc3, IF_66,            "retw"),
	I(0xc3, 0,                "ret"),

	I(0xc4, IF_66|IF_MODRM|IF_RMM, "lesw\t" OP_MEM/*32*/ OP_R16),
	I(0xc4, IF_MODRM|IF_RMM,       "lesl\t" OP_MEM/*48*/ OP_R32),
	I(0xc5, IF_66|IF_MODRM|IF_RMM, "ldsw\t" OP_MEM/*32*/ OP_R16),
	I(0xc5, IF_MODRM|IF_RMM,       "ldsl\t" OP_MEM/*48*/ OP_R32),

	I(0xc6, IF_MODRM|IF_REG0,        "movb\t" OP_U8 OP_RM8),
	I(0xc6, IF_BYTE2,         "\xf8" "xabort\t" OP_U8),

	I(0xc7, IF_66|IF_MODRM|IF_REG0,  "movw\t" OP_U16 OP_RM16),
	I(0xc7, IF_MODRM|IF_REG0,        "movl\t" OP_U32 OP_RM32),
	I(0xc7, IF_MODRM|IF_REXW|IF_REG0,"movq\t" OP_S32 OP_RM64),
	I(0xc7, IF_BYTE2|IF_66,   "\xf8" "xbeginw\t" OP_DISP16),
	I(0xc7, IF_BYTE2,         "\xf8" "xbegin\t" OP_DISP32),

	I(0xc8, 0,                "enter\t" OP_U16 OP_U8),
	I(0xc9, 0,                "leave"),
	I(0xca, 0,                "lret\t" OP_U16),
	I(0xcb, 0,                "lret"),
	I(0xcc, 0,                "int3"),
	I(0xcd, 0,                "int\t" OP_U8),
	I(0xce, 0,                "into"),
	I(0xcf, IF_66,            "iretw"),
	I(0xcf, IF_X32,           "iret"),
	I(0xcf, IF_X64,           "iretl"),
	I(0xcf, IF_REXW,          "iretq"),

	I(0xd0, IF_MODRM|IF_REG0, "rolb\t" OP_IMM1 OP_RM8),
	I(0xd0, IF_MODRM|IF_REG1, "rorb\t" OP_IMM1 OP_RM8),
	I(0xd0, IF_MODRM|IF_REG2, "rclb\t" OP_IMM1 OP_RM8),
	I(0xd0, IF_MODRM|IF_REG3, "rcrb\t" OP_IMM1 OP_RM8),
	I(0xd0, IF_MODRM|IF_REG4, "shlb\t" OP_IMM1 OP_RM8),
	I(0xd0, IF_MODRM|IF_REG5, "shrb\t" OP_IMM1 OP_RM8),
	I(0xd0, IF_MODRM|IF_REG6, "salb\t" OP_IMM1 OP_RM8),
	I(0xd0, IF_MODRM|IF_REG7, "sarb\t" OP_IMM1 OP_RM8),

	I(0xd1, IF_66|IF_MODRM|IF_REG0, "rolw\t" OP_IMM1 OP_RM16),
	I(0xd1, IF_MODRM|IF_REG0, "roll\t" OP_IMM1 OP_RM32),
	I(0xd1, IF_MODRM|IF_REXW|IF_REG0, "rolq\t" OP_IMM1 OP_RM64),

	I(0xd1, IF_66|IF_MODRM|IF_REG1, "rorw\t" OP_IMM1 OP_RM16),
	I(0xd1, IF_MODRM|IF_REG1, "rorl\t" OP_IMM1 OP_RM32),
	I(0xd1, IF_MODRM|IF_REXW|IF_REG1, "rorq\t" OP_IMM1 OP_RM64),

	I(0xd1, IF_66|IF_MODRM|IF_REG2, "rclw\t" OP_IMM1 OP_RM16),
	I(0xd1, IF_MODRM|IF_REG2, "rcll\t" OP_IMM1 OP_RM32),
	I(0xd1, IF_MODRM|IF_REXW|IF_REG2, "rclq\t" OP_IMM1 OP_RM64),

	I(0xd1, IF_66|IF_MODRM|IF_REG3, "rcrw\t" OP_IMM1 OP_RM16),
	I(0xd1, IF_MODRM|IF_REG3, "rcrl\t" OP_IMM1 OP_RM32),
	I(0xd1, IF_MODRM|IF_REXW|IF_REG3, "rcrq\t" OP_IMM1 OP_RM64),

	I(0xd1, IF_66|IF_MODRM|IF_REG4, "shlw\t" OP_IMM1 OP_RM16),
	I(0xd1, IF_MODRM|IF_REG4, "shll\t" OP_IMM1 OP_RM32),
	I(0xd1, IF_MODRM|IF_REXW|IF_REG4, "shlq\t" OP_IMM1 OP_RM64),

	I(0xd1, IF_66|IF_MODRM|IF_REG5, "shrw\t" OP_IMM1 OP_RM16),
	I(0xd1, IF_MODRM|IF_REG5, "shrl\t" OP_IMM1 OP_RM32),
	I(0xd1, IF_MODRM|IF_REXW|IF_REG5, "shrq\t" OP_IMM1 OP_RM64),

	I(0xd1, IF_66|IF_MODRM|IF_REG6, "salw\t" OP_IMM1 OP_RM16),
	I(0xd1, IF_MODRM|IF_REG6, "sall\t" OP_IMM1 OP_RM32),
	I(0xd1, IF_MODRM|IF_REXW|IF_REG6, "salq\t" OP_IMM1 OP_RM64),

	I(0xd1, IF_66|IF_MODRM|IF_REG7, "sarw\t" OP_IMM1 OP_RM16),
	I(0xd1, IF_MODRM|IF_REG7, "sarl\t" OP_IMM1 OP_RM32),
	I(0xd1, IF_MODRM|IF_REXW|IF_REG7, "sarq\t" OP_IMM1 OP_RM64),

	I(0xd2, IF_MODRM|IF_REG0, "rolb\t" OP_CL OP_RM8),
	I(0xd2, IF_MODRM|IF_REG1, "rorb\t" OP_CL OP_RM8),
	I(0xd2, IF_MODRM|IF_REG2, "rclb\t" OP_CL OP_RM8),
	I(0xd2, IF_MODRM|IF_REG3, "rcrb\t" OP_CL OP_RM8),
	I(0xd2, IF_MODRM|IF_REG4, "shlb\t" OP_CL OP_RM8),
	I(0xd2, IF_MODRM|IF_REG5, "shrb\t" OP_CL OP_RM8),
	I(0xd2, IF_MODRM|IF_REG6, "salb\t" OP_CL OP_RM8),
	I(0xd2, IF_MODRM|IF_REG7, "sarb\t" OP_CL OP_RM8),

	I(0xd3, IF_66|IF_MODRM|IF_REG0, "rolw\t" OP_CL OP_RM16),
	I(0xd3, IF_MODRM|IF_REG0, "roll\t" OP_CL OP_RM32),
	I(0xd3, IF_MODRM|IF_REXW|IF_REG0, "rolq\t" OP_CL OP_RM64),

	I(0xd3, IF_66|IF_MODRM|IF_REG1, "rorw\t" OP_CL OP_RM16),
	I(0xd3, IF_MODRM|IF_REG1, "rorl\t" OP_CL OP_RM32),
	I(0xd3, IF_MODRM|IF_REXW|IF_REG1, "rorq\t" OP_CL OP_RM64),

	I(0xd3, IF_66|IF_MODRM|IF_REG2, "rclw\t" OP_CL OP_RM16),
	I(0xd3, IF_MODRM|IF_REG2, "rcll\t" OP_CL OP_RM32),
	I(0xd3, IF_MODRM|IF_REXW|IF_REG2, "rclq\t" OP_CL OP_RM64),

	I(0xd3, IF_66|IF_MODRM|IF_REG3, "rcrw\t" OP_CL OP_RM16),
	I(0xd3, IF_MODRM|IF_REG3, "rcrl\t" OP_CL OP_RM32),
	I(0xd3, IF_MODRM|IF_REXW|IF_REG3, "rcrq\t" OP_CL OP_RM64),

	I(0xd3, IF_66|IF_MODRM|IF_REG4, "shlw\t" OP_CL OP_RM16),
	I(0xd3, IF_MODRM|IF_REG4, "shll\t" OP_CL OP_RM32),
	I(0xd3, IF_MODRM|IF_REXW|IF_REG4, "shlq\t" OP_CL OP_RM64),

	I(0xd3, IF_66|IF_MODRM|IF_REG5, "shrw\t" OP_CL OP_RM16),
	I(0xd3, IF_MODRM|IF_REG5, "shrl\t" OP_CL OP_RM32),
	I(0xd3, IF_MODRM|IF_REXW|IF_REG5, "shrq\t" OP_CL OP_RM64),

	I(0xd3, IF_66|IF_MODRM|IF_REG6, "salw\t" OP_CL OP_RM16),
	I(0xd3, IF_MODRM|IF_REG6, "sall\t" OP_CL OP_RM32),
	I(0xd3, IF_MODRM|IF_REXW|IF_REG6, "salq\t" OP_CL OP_RM64),

	I(0xd3, IF_66|IF_MODRM|IF_REG7, "sarw\t" OP_CL OP_RM16),
	I(0xd3, IF_MODRM|IF_REG7, "sarl\t" OP_CL OP_RM32),
	I(0xd3, IF_MODRM|IF_REXW|IF_REG7, "sarq\t" OP_CL OP_RM64),

	I(0xd4, 0,                "aam\t" OP_U8),
	I(0xd5, 0,                "aad\t" OP_U8),
	I(0xd6, 0,                "salc"),
	I(0xd7, 0,                "xlatb"),

	I(0xd8, IF_MODRM|IF_RMR|IF_REG0, "fadd\t" OP_RMSTi OP_ST0),
	I(0xd8, IF_MODRM|IF_RMM|IF_REG0, "faddl\t" OP_RMSTi OP_VERBOSE_ST0),
	I(0xd8, IF_MODRM|IF_RMR|IF_REG1, "fmul\t" OP_RMSTi OP_ST0),
	I(0xd8, IF_MODRM|IF_RMM|IF_REG1, "fmull\t" OP_RM32 OP_VERBOSE_ST0),

	I(0xd8, IF_MODRM|IF_RMR|IF_REG2, "fcom\t" OP_RMSTi OP_VERBOSE_ST0),
	I(0xd8, IF_MODRM|IF_RMM|IF_REG2, "fcoml\t" OP_RM32 OP_VERBOSE_ST0),
	I(0xd8, IF_MODRM|IF_RMR|IF_REG3, "fcomp\t" OP_RMSTi OP_VERBOSE_ST0),
	I(0xd8, IF_MODRM|IF_RMM|IF_REG3, "fcompl\t" OP_RM32 OP_VERBOSE_ST0),
	I(0xd8, IF_MODRM|IF_RMR|IF_REG4, "fsub\t" OP_RMSTi OP_ST0),
	I(0xd8, IF_MODRM|IF_RMM|IF_REG4, "fsubl\t" OP_RM32 OP_VERBOSE_ST0),
	I(0xd8, IF_MODRM|IF_RMR|IF_REG5, "fsubr\t" OP_RMSTi OP_ST0),
	I(0xd8, IF_MODRM|IF_RMM|IF_REG5, "fsubrl\t" OP_RM32 OP_VERBOSE_ST0),
	I(0xd8, IF_MODRM|IF_RMR|IF_REG6, "fdiv\t" OP_RMSTi OP_VERBOSE_ST0),
	I(0xd8, IF_MODRM|IF_RMM|IF_REG6, "fdivl\t" OP_RM32 OP_VERBOSE_ST0),
	I(0xd8, IF_MODRM|IF_RMR|IF_REG7, "fdivr\t" OP_RMSTi OP_VERBOSE_ST0),
	I(0xd8, IF_MODRM|IF_RMM|IF_REG7, "fdivrl\t" OP_RM32 OP_VERBOSE_ST0),

	I(0xd9, IF_BYTE2,        "\xc0" "fld" OP_ST0),
	I(0xd9, IF_BYTE2,        "\xc1" "fld" OP_ST1),
	I(0xd9, IF_BYTE2,        "\xc2" "fld" OP_ST2),
	I(0xd9, IF_BYTE2,        "\xc3" "fld" OP_ST3),
	I(0xd9, IF_BYTE2,        "\xc4" "fld" OP_ST4),
	I(0xd9, IF_BYTE2,        "\xc5" "fld" OP_ST5),
	I(0xd9, IF_BYTE2,        "\xc6" "fld" OP_ST6),
	I(0xd9, IF_BYTE2,        "\xc7" "fld" OP_ST7),
	I(0xd9, IF_BYTE2,        "\xc8" "fxch" OP_ST0),
	I(0xd9, IF_BYTE2,        "\xc9" "fxch" OP_ST1),
	I(0xd9, IF_BYTE2,        "\xca" "fxch" OP_ST2),
	I(0xd9, IF_BYTE2,        "\xcb" "fxch" OP_ST3),
	I(0xd9, IF_BYTE2,        "\xcc" "fxch" OP_ST4),
	I(0xd9, IF_BYTE2,        "\xcd" "fxch" OP_ST5),
	I(0xd9, IF_BYTE2,        "\xce" "fxch" OP_ST6),
	I(0xd9, IF_BYTE2,        "\xcf" "fxch" OP_ST7),
	I(0xd9, IF_BYTE2,        "\xd0" "fnop"),
	I(0xd9, IF_BYTE2,        "\xe0" "fchs"),
	I(0xd9, IF_BYTE2,        "\xe1" "fabs"),
	I(0xd9, IF_BYTE2,        "\xe4" "ftst"),
	I(0xd9, IF_BYTE2,        "\xe5" "fxam"),
	I(0xd9, IF_BYTE2,        "\xe8" "fld1"),
	I(0xd9, IF_BYTE2,        "\xe9" "fldl2t"),
	I(0xd9, IF_BYTE2,        "\xea" "fldl2e"),
	I(0xd9, IF_BYTE2,        "\xeb" "fldpi"),
	I(0xd9, IF_BYTE2,        "\xec" "fldlg2"),
	I(0xd9, IF_BYTE2,        "\xed" "fldln2"),
	I(0xd9, IF_BYTE2,        "\xee" "fldz"),
	I(0xd9, IF_BYTE2,        "\xf0" "f2xm1"),
	I(0xd9, IF_BYTE2,        "\xf1" "fyl2x"),
	I(0xd9, IF_BYTE2,        "\xf2" "fptan"),
	I(0xd9, IF_BYTE2,        "\xf3" "fpatan"),
	I(0xd9, IF_BYTE2,        "\xf4" "fxtract"),
	I(0xd9, IF_BYTE2,        "\xf5" "fprem1"),
	I(0xd9, IF_BYTE2,        "\xf6" "fdecstp"),
	I(0xd9, IF_BYTE2,        "\xf7" "fincstp"),
	I(0xd9, IF_BYTE2,        "\xf8" "fprem"),
	I(0xd9, IF_BYTE2,        "\xf9" "fyl2xp1"),
	I(0xd9, IF_BYTE2,        "\xfa" "fsqrt"),
	I(0xd9, IF_BYTE2,        "\xfb" "fsincos"),
	I(0xd9, IF_BYTE2,        "\xfc" "frndint"),
	I(0xd9, IF_BYTE2,        "\xfd" "fscale"),
	I(0xd9, IF_BYTE2,        "\xfe" "fsin"),
	I(0xd9, IF_BYTE2,        "\xff" "fcos"),
	I(0xd9, IF_MODRM|IF_RMM|IF_REG0, "fldl\t" OP_RM32),
	I(0xd9, IF_MODRM|IF_RMM|IF_REG2, "fstl\t" OP_RM32),
	I(0xd9, IF_MODRM|IF_RMM|IF_REG3, "fstpl\t" OP_RM32),
	I(0xd9, IF_66|IF_MODRM|IF_RMM|IF_REG4, "fldenv14\t" OP_MEM),
	I(0xd9, IF_MODRM|IF_RMM|IF_REG4, "fldenv28\t" OP_MEM),
	I(0xd9, IF_MODRM|IF_RMM|IF_REG5, "fldcww\t" OP_RM16),
	I(0xd9, IF_66|IF_MODRM|IF_RMM|IF_REG6, "fnstenv94\t" OP_MEM),
	I(0xd9, IF_MODRM|IF_RMM|IF_REG6, "fnstenv108\t" OP_MEM),
	I(0xd9, IF_MODRM|IF_RMM|IF_REG7, "fnstcww\t" OP_RM16),

	I(0xda, IF_BYTE2, LONGREPR_B(0xe9, LO_FUCOMPP)), /* fucompp %st(1), %st(0) */
	I(0xda, IF_MODRM|IF_RMM|IF_REG0, "fiaddl\t" OP_RM32 OP_VERBOSE_ST0),
	I(0xda, IF_MODRM|IF_RMR|IF_REG0, "fcmovb\t" OP_RMSTi OP_ST0),
	I(0xda, IF_MODRM|IF_RMR|IF_REG1, "fcmove\t" OP_RMSTi OP_ST0),
	I(0xda, IF_MODRM|IF_RMR|IF_REG2, "fcmovbe\t" OP_RMSTi OP_ST0),
	I(0xda, IF_MODRM|IF_RMR|IF_REG3, "fcmovu\t" OP_RMSTi OP_ST0),

	I(0xda, IF_MODRM|IF_RMM|IF_REG1, "fimull\t" OP_RM32 OP_VERBOSE_ST0),
	I(0xda, IF_MODRM|IF_RMM|IF_REG2, "ficoml\t" OP_RM32 OP_VERBOSE_ST0),
	I(0xda, IF_MODRM|IF_RMM|IF_REG3, "ficompl\t" OP_RM32 OP_VERBOSE_ST0),
	I(0xda, IF_MODRM|IF_RMM|IF_REG4, "fisubl\t" OP_RM32 OP_VERBOSE_ST0),
	I(0xda, IF_MODRM|IF_RMM|IF_REG5, "fisubrl\t" OP_RM32 OP_VERBOSE_ST0),
	I(0xda, IF_MODRM|IF_RMM|IF_REG6, "fidivl\t" OP_RM32 OP_VERBOSE_ST0),
	I(0xda, IF_MODRM|IF_RMM|IF_REG7, "fidivrl\t" OP_RM32 OP_VERBOSE_ST0),

	I(0xdb, IF_BYTE2,  "\xe2" "fnclex"),
	I(0xdb, IF_BYTE2,  "\xe3" "fninit"),
	I(0xdb, IF_BYTE2,  "\xe8" "fucomi" OP_ST0 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xe9" "fucomi" OP_ST1 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xea" "fucomi" OP_ST2 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xeb" "fucomi" OP_ST3 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xec" "fucomi" OP_ST4 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xed" "fucomi" OP_ST5 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xee" "fucomi" OP_ST6 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xef" "fucomi" OP_ST7 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xf0" "fcomi" OP_ST0 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xf1" "fcomi" OP_ST1 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xf2" "fcomi" OP_ST2 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xf3" "fcomi" OP_ST3 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xf4" "fcomi" OP_ST4 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xf5" "fcomi" OP_ST5 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xf6" "fcomi" OP_ST6 OP_ST0),
	I(0xdb, IF_BYTE2,  "\xf7" "fcomi" OP_ST7 OP_ST0),
	I(0xdb, IF_MODRM|IF_RMM|IF_REG0, "fildl\t" OP_RM32),
	I(0xdb, IF_MODRM|IF_RMM|IF_REG1, "fisttpl\t" OP_RM32),
	I(0xdb, IF_MODRM|IF_RMM|IF_REG2, "fistl\t" OP_RM32),
	I(0xdb, IF_MODRM|IF_RMM|IF_REG3, "fistpl\t" OP_RM32),
	I(0xdb, IF_MODRM|IF_RMM|IF_REG5, "fld80" OP_MEM),
	I(0xdb, IF_MODRM|IF_RMM|IF_REG7, "fstp80" OP_MEM),

	I(0xdc, IF_MODRM|IF_RMR|IF_REG0, "fadd\t" OP_ST0 OP_RMSTi),
	I(0xdc, IF_MODRM|IF_RMM|IF_REG0, "faddq\t" OP_RM64 OP_VERBOSE_ST0),
	I(0xdc, IF_MODRM|IF_RMR|IF_REG1, "fmul\t" OP_ST0 OP_RMSTi),
	I(0xdc, IF_MODRM|IF_RMM|IF_REG1, "fmulq\t" OP_RM64 OP_VERBOSE_ST0),
	I(0xdc, IF_MODRM|IF_RMM|IF_REG2, "fcomq\t" OP_RM64 OP_VERBOSE_ST0),
	I(0xdc, IF_MODRM|IF_RMM|IF_REG3, "fcompq\t" OP_RM64 OP_VERBOSE_ST0),
	I(0xdc, IF_MODRM|IF_RMR|IF_REG4, "fsub\t" OP_ST0 OP_RMSTi),
	I(0xdc, IF_MODRM|IF_RMM|IF_REG4, "fsubq\t" OP_RM64 OP_VERBOSE_ST0),
	I(0xdc, IF_MODRM|IF_RMR|IF_REG5, "fsubr\t" OP_ST0 OP_RMSTi),
	I(0xdc, IF_MODRM|IF_RMM|IF_REG5, "fsubrq\t" OP_RM64 OP_VERBOSE_ST0),
	I(0xdc, IF_MODRM|IF_RMR|IF_REG6, "fdiv\t" OP_RMSTi OP_VERBOSE_ST0),
	I(0xdc, IF_MODRM|IF_RMM|IF_REG6, "fdivq\t" OP_RM64 OP_VERBOSE_ST0),
	I(0xdc, IF_MODRM|IF_RMR|IF_REG7, "fdivr\t" OP_RMSTi OP_VERBOSE_ST0),
	I(0xdc, IF_MODRM|IF_RMM|IF_REG7, "fdivrq\t" OP_RM64 OP_VERBOSE_ST0),

	I(0xdd, IF_BYTE2, "\xc0" "ffree\t" OP_ST0),
	I(0xdd, IF_BYTE2, "\xc1" "ffree\t" OP_ST1),
	I(0xdd, IF_BYTE2, "\xc2" "ffree\t" OP_ST2),
	I(0xdd, IF_BYTE2, "\xc3" "ffree\t" OP_ST3),
	I(0xdd, IF_BYTE2, "\xc4" "ffree\t" OP_ST4),
	I(0xdd, IF_BYTE2, "\xc5" "ffree\t" OP_ST5),
	I(0xdd, IF_BYTE2, "\xc6" "ffree\t" OP_ST6),
	I(0xdd, IF_BYTE2, "\xc7" "ffree\t" OP_ST7),
	I(0xdd, IF_BYTE2, "\xe0" "fucom\t" OP_ST0),
	I(0xdd, IF_BYTE2, "\xe1" "fucom\t" OP_ST1),
	I(0xdd, IF_BYTE2, "\xe2" "fucom\t" OP_ST2),
	I(0xdd, IF_BYTE2, "\xe3" "fucom\t" OP_ST3),
	I(0xdd, IF_BYTE2, "\xe4" "fucom\t" OP_ST4),
	I(0xdd, IF_BYTE2, "\xe5" "fucom\t" OP_ST5),
	I(0xdd, IF_BYTE2, "\xe6" "fucom\t" OP_ST6),
	I(0xdd, IF_BYTE2, "\xe7" "fucom\t" OP_ST7),
	I(0xdd, IF_BYTE2, "\xe8" "fucomp\t" OP_ST0),
	I(0xdd, IF_BYTE2, "\xe9" "fucomp\t" OP_ST1),
	I(0xdd, IF_BYTE2, "\xea" "fucomp\t" OP_ST2),
	I(0xdd, IF_BYTE2, "\xeb" "fucomp\t" OP_ST3),
	I(0xdd, IF_BYTE2, "\xec" "fucomp\t" OP_ST4),
	I(0xdd, IF_BYTE2, "\xed" "fucomp\t" OP_ST5),
	I(0xdd, IF_BYTE2, "\xee" "fucomp\t" OP_ST6),
	I(0xdd, IF_BYTE2, "\xef" "fucomp\t" OP_ST7),

	I(0xdd, IF_MODRM|IF_RMM|IF_REG0, "fldq" OP_RM64),
	I(0xdd, IF_MODRM|IF_RMM|IF_REG1, "fisttpq\t" OP_RM64),
	I(0xdd, IF_MODRM|IF_RMR|IF_REG2, "fst\t" OP_RMSTi),
	I(0xdd, IF_MODRM|IF_RMM|IF_REG2, "fstq\t" OP_RM64),
	I(0xdd, IF_MODRM|IF_RMR|IF_REG3, "fstp\t" OP_RMSTi),
	I(0xdd, IF_MODRM|IF_RMM|IF_REG3, "fstpq\t" OP_RM64),
	I(0xdd, IF_66|IF_MODRM|IF_RMM|IF_REG4, "frstor94\t" OP_MEM),
	I(0xdd, IF_MODRM|IF_RMM|IF_REG4, "frstor108\t" OP_MEM),
	I(0xdd, IF_66|IF_MODRM|IF_RMM|IF_REG6, "fnsave94\t" OP_MEM),
	I(0xdd, IF_MODRM|IF_RMM|IF_REG6, "fnsave108\t" OP_MEM),
	I(0xdd, IF_MODRM|IF_RMM|IF_REG7, "fnstcww\t" OP_RM16),

	I(0xde, IF_BYTE2, "\xd9" "fcompp\t" OP_VERBOSE_ST1 OP_VERBOSE_ST0),

	I(0xde, IF_MODRM|IF_RMR|IF_REG0, "faddp\t" OP_ST0 OP_RMSTi),
	I(0xde, IF_MODRM|IF_RMM|IF_REG0, "fiaddw\t" OP_RM16 OP_VERBOSE_ST0),
	I(0xde, IF_MODRM|IF_RMR|IF_REG1, "fmulp\t" OP_ST0 OP_RMSTi),
	I(0xde, IF_MODRM|IF_RMM|IF_REG1, "fimulw\t" OP_RM16 OP_VERBOSE_ST0),
	I(0xde, IF_MODRM|IF_RMM|IF_REG2, "ficomw\t" OP_RM16 OP_VERBOSE_ST0),
	I(0xde, IF_MODRM|IF_RMM|IF_REG3, "ficompw\t" OP_RM16 OP_VERBOSE_ST0),
	I(0xde, IF_MODRM|IF_RMR|IF_REG4, "fsubp\t" OP_ST0 OP_RMSTi),
	I(0xde, IF_MODRM|IF_RMM|IF_REG4, "fisubw\t" OP_RM16 OP_VERBOSE_ST0),
	I(0xde, IF_MODRM|IF_RMR|IF_REG5, "fsubrp\t" OP_ST0 OP_RMSTi),
	I(0xde, IF_MODRM|IF_RMM|IF_REG5, "fisubrw\t" OP_RM16 OP_VERBOSE_ST0),
	I(0xde, IF_MODRM|IF_RMR|IF_REG6, "fdivp\t" OP_ST0 OP_RMSTi),
	I(0xde, IF_MODRM|IF_RMM|IF_REG6, "fidivw\t" OP_RM16 OP_VERBOSE_ST0),
	I(0xde, IF_MODRM|IF_RMR|IF_REG7, "fdivrp\t" OP_ST0 OP_RMSTi),
	I(0xde, IF_MODRM|IF_RMM|IF_REG7, "fidivrw\t" OP_RM16 OP_VERBOSE_ST0),

	I(0xdf, IF_BYTE2,  "\xe0" "fnstsw" OP_AX),
	I(0xdf, IF_BYTE2,  "\xe8" "fucomip" OP_ST0 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xe9" "fucomip" OP_ST1 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xea" "fucomip" OP_ST2 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xeb" "fucomip" OP_ST3 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xec" "fucomip" OP_ST4 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xed" "fucomip" OP_ST5 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xee" "fucomip" OP_ST6 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xef" "fucomip" OP_ST7 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xf0" "fcomip" OP_ST0 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xf1" "fcomip" OP_ST1 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xf2" "fcomip" OP_ST2 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xf3" "fcomip" OP_ST3 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xf4" "fcomip" OP_ST4 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xf5" "fcomip" OP_ST5 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xf6" "fcomip" OP_ST6 OP_ST0),
	I(0xdf, IF_BYTE2,  "\xf7" "fcomip" OP_ST7 OP_ST0),

	I(0xdf, IF_MODRM|IF_RMM|IF_REG0, "fildw\t" OP_RM16),
	I(0xdf, IF_MODRM|IF_RMM|IF_REG1, "fisttpw\t" OP_RM16),
	I(0xdf, IF_MODRM|IF_RMM|IF_REG2, "fistw\t" OP_RM16),
	I(0xdf, IF_MODRM|IF_RMM|IF_REG3, "fistpw\t" OP_RM16),
	I(0xdf, IF_MODRM|IF_RMM|IF_REG4, "fbld\t" OP_MEM),
	I(0xdf, IF_MODRM|IF_RMM|IF_REG5, "fildq\t" OP_RM64),
	I(0xdf, IF_MODRM|IF_RMM|IF_REG6, "fbstp\t" OP_MEM),
	I(0xdf, IF_MODRM|IF_RMM|IF_REG7, "fistpq\t" OP_RM64),


	I(0xe0, 0,                "loopnz\t" OP_DISP8),
	I(0xe1, 0,                "loopz\t" OP_DISP8),
	I(0xe2, 0,                "loop\t" OP_DISP8),
	I(0xe3, IF_66,            "jcxz\t" OP_DISP8),
	I(0xe3, 0,                "jecxz\t" OP_DISP8),
	I(0xe3, IF_REXW,          "jrcxz\t" OP_DISP8),

	I(0xe4, 0,                "inb\t" OP_U8 OP_AL),
	I(0xe5, IF_66,            "inw\t" OP_U8 OP_AX),
	I(0xe5, 0,                "inl\t" OP_U8 OP_EAX),
	I(0xe6, 0,                "outb\t" OP_AL OP_U8),
	I(0xe7, IF_66,            "outw\t" OP_AX OP_U8),
	I(0xe7, 0,                "outl\t" OP_EAX OP_U8),
	/* NOTE: Ignore 66h prefix on x86_64. (the hardware does the same!)
	 *       However, only Intel ignores it. - AMD still obeys the 66h
	 *       prefix and truncates the operand to 16 bits */
#if 1
	I(0xe8, IF_X32|IF_66,     "callw\t" OP_DISP16),
	I(0xe8, 0,                "call\t" OP_DISP32),
	I(0xe9, IF_X32|IF_66,     "jmpw\t" OP_DISP16),
	I(0xe9, 0,                "jmp\t" OP_DISP32),
#else
/*	I(0xe8, IF_66,            "callw\t" OP_DISP16), */
/*	I(0xe8, 0,                "call\t" OP_DISP32), */
/*	I(0xe9, IF_66,            "jmpw\t" OP_DISP16), */
/*	I(0xe9, 0,                "jmp\t" OP_DISP32), */
#endif
	I(0xea, IF_67,            "ljmpw\t" OP_LJMP),
	I(0xea, 0,                "ljmpl\t" OP_LJMP),
	I(0xeb, 0,                "jmp\t" OP_DISP8),
	I(0xec, 0,                "inb\t" OP_DX OP_AL),
	I(0xed, IF_66,            "inw\t" OP_DX OP_AX),
	I(0xed, 0,                "inl\t" OP_DX OP_EAX),
	I(0xee, 0,                "outb\t" OP_AL OP_DX),
	I(0xef, IF_66,            "outw\t" OP_AX OP_DX),
	I(0xef, 0,                "outl\t" OP_EAX OP_DX),

	/* 0xf0 -- PREFIX */

	I(0xf1, 0,                "int1"),

	/* 0xf2 -- PREFIX */
	/* 0xf3 -- PREFIX */

	I(0xf4, 0,                "hlt"),

	I(0xf5, 0,                "cmc"),

	I(0xf6, IF_MODRM|IF_REG0, "testb\t" OP_U8 OP_RM8),
	I(0xf6, IF_MODRM|IF_REG1, "testb\t" OP_U8 OP_RM8), /* Undocumented alias */
	I(0xf6, IF_MODRM|IF_REG2, "notb\t" OP_RM8),
	I(0xf6, IF_MODRM|IF_REG3, "negb\t" OP_RM8),
	I(0xf6, IF_MODRM|IF_REG4, "mulb\t" OP_RM8),
	I(0xf6, IF_MODRM|IF_REG5, "imulb\t" OP_RM8),
	I(0xf6, IF_MODRM|IF_REG6, "divb\t" OP_RM8),
	I(0xf6, IF_MODRM|IF_REG7, "idivb\t" OP_RM8),

	I(0xf7, IF_66|IF_MODRM|IF_REG0, "testw\t" OP_U16 OP_RM16),
	I(0xf7, IF_MODRM|IF_REG0, "testl\t" OP_U32 OP_RM32),
	I(0xf7, IF_MODRM|IF_REXW|IF_REG0, "testq\t" OP_S32 OP_RM64),

	I(0xf7, IF_66|IF_MODRM|IF_REG1, "testw\t" OP_U16 OP_RM16), /* Undocumented alias */
	I(0xf7, IF_MODRM|IF_REG1, "testl\t" OP_U32 OP_RM32), /* Undocumented alias */
	I(0xf7, IF_MODRM|IF_REXW|IF_REG1, "testq\t" OP_S32 OP_RM64), /* Undocumented alias */

	I(0xf7, IF_66|IF_MODRM|IF_REG2, "notw\t" OP_RM16),
	I(0xf7, IF_MODRM|IF_REG2, "notl\t" OP_RM32),
	I(0xf7, IF_MODRM|IF_REXW|IF_REG2, "notq\t" OP_RM64),

	I(0xf7, IF_66|IF_MODRM|IF_REG3, "negw\t" OP_RM16),
	I(0xf7, IF_MODRM|IF_REG3, "negl\t" OP_RM32),
	I(0xf7, IF_MODRM|IF_REXW|IF_REG3, "negq\t" OP_RM64),

	I(0xf7, IF_66|IF_MODRM|IF_REG4, "mulw\t" OP_RM16),
	I(0xf7, IF_MODRM|IF_REG4, "mull\t" OP_RM32),
	I(0xf7, IF_MODRM|IF_REXW|IF_REG4, "mulq\t" OP_RM64),

	I(0xf7, IF_66|IF_MODRM|IF_REG5, "imulw\t" OP_RM16),
	I(0xf7, IF_MODRM|IF_REG5, "imull\t" OP_RM32),
	I(0xf7, IF_MODRM|IF_REXW|IF_REG5, "imulq\t" OP_RM64),

	I(0xf7, IF_66|IF_MODRM|IF_REG6, "divw\t" OP_RM16),
	I(0xf7, IF_MODRM|IF_REG6, "divl\t" OP_RM32),
	I(0xf7, IF_MODRM|IF_REXW|IF_REG6, "divq\t" OP_RM64),

	I(0xf7, IF_66|IF_MODRM|IF_REG7, "idivw\t" OP_RM16),
	I(0xf7, IF_MODRM|IF_REG7, "idivl\t" OP_RM32),
	I(0xf7, IF_MODRM|IF_REXW|IF_REG7, "idivq\t" OP_RM64),

	I(0xf8, 0,                "clc"),
	I(0xf9, 0,                "stc"),
	I(0xfa, 0,                "cli"),
	I(0xfb, 0,                "sti"),
	I(0xfc, 0,                "cld"),
	I(0xfd, 0,                "std"),

	I(0xfe, IF_MODRM|IF_REG0, "incb\t" OP_RM8),
	I(0xfe, IF_MODRM|IF_REG1, "decb\t" OP_RM8),

	I(0xff, IF_66|IF_MODRM|IF_REG0, "incw\t" OP_RM16),
	I(0xff, IF_MODRM|IF_REG0, "incl\t" OP_RM32),
	I(0xff, IF_MODRM|IF_REXW|IF_REG0, "incq\t" OP_RM64),

	I(0xff, IF_66|IF_MODRM|IF_REG1, "decw\t" OP_RM16),
	I(0xff, IF_MODRM|IF_REG1, "decl\t" OP_RM32),
	I(0xff, IF_MODRM|IF_REXW|IF_REG1, "decq\t" OP_RM64),

	I(0xff, IF_66|IF_MODRM|IF_REG2, "callw\t" OP_XRM16),
	I(0xff, IF_MODRM|IF_REG2, "calll\t" OP_XRM32),
	I(0xff, IF_MODRM|IF_REXW|IF_REG2, "callq\t" OP_XRM64),

	I(0xff, IF_RMM|IF_66|IF_MODRM|IF_REG3, "lcallw\t" OP_XRM16),
	I(0xff, IF_RMM|IF_MODRM|IF_REG3, "lcalll\t" OP_XRM32),
	I(0xff, IF_RMM|IF_MODRM|IF_REXW|IF_REG3, "lcallq\t" OP_XRM64),

	I(0xff, IF_66|IF_MODRM|IF_REG4, "jmpw\t" OP_XRM16),
	I(0xff, IF_MODRM|IF_REG4, "jmpl\t" OP_XRM32),
	I(0xff, IF_MODRM|IF_REXW|IF_REG4, "jmpq\t" OP_XRM64),

	I(0xff, IF_RMM|IF_66|IF_MODRM|IF_REG5, "ljmpw\t" OP_XRM16),
	I(0xff, IF_RMM|IF_MODRM|IF_REG5, "ljmpl\t" OP_XRM32),
	I(0xff, IF_RMM|IF_MODRM|IF_REXW|IF_REG5, "ljmpq\t" OP_XRM64),

	I(0xff, IF_66|IF_MODRM|IF_REG6, "pushw\t" OP_RM16),
	I(0xff, IF_MODRM|IF_REG6, "pushl\t" OP_RM32),
	I(0xff, IF_MODRM|IF_REXW|IF_REG6, "pushq\t" OP_RM64),

	I(0, 0, "")
/*[[[end:ops]]]*/
};
/* clang-format on */


/* clang-format off */
PRIVATE struct instruction const ops_0f[] = {
/*[[[start:ops_0f]]]*/
	/* REMINDER: After adding/removing instructions from this table, you must run:
	 *           $ deemon -F kos/src/libdisasm/x86-db.h */
	I(0x00, IF_MODRM|IF_REG0, "sldt\t" OP_RM16),
	I(0x00, IF_MODRM|IF_REG1, "str\t"  OP_RM16),
	I(0x00, IF_MODRM|IF_REG2, "lldt\t" OP_RM16),
	I(0x00, IF_MODRM|IF_REG3, "ltr\t"  OP_RM16),
	I(0x00, IF_MODRM|IF_REG4, "verr\t" OP_RM16),
	I(0x00, IF_MODRM|IF_REG5, "verw\t" OP_RM16),

	I(0x01, IF_X32|IF_MODRM|IF_RMM|IF_REG0,  "sgdtl\t" OP_MEM),
	I(0x01, IF_X64|IF_MODRM|IF_RMM|IF_REG0,  "sgdtq\t" OP_MEM),
	I(0x01, IF_X32|IF_MODRM|IF_RMM|IF_REG1,  "sidtl\t" OP_MEM),
	I(0x01, IF_X64|IF_MODRM|IF_RMM|IF_REG1,  "sidtq\t" OP_MEM),
	I(0x01, IF_X32|IF_MODRM|IF_RMM|IF_REG2,  "lgdtl\t" OP_MEM),
	I(0x01, IF_X64|IF_MODRM|IF_RMM|IF_REG2,  "lgdtq\t" OP_MEM),
	I(0x01, IF_X32|IF_MODRM|IF_RMM|IF_REG3,  "lidtl\t" OP_MEM),
	I(0x01, IF_X64|IF_MODRM|IF_RMM|IF_REG3,  "lidtq\t" OP_MEM),

	I(0x01, IF_66|IF_MODRM|IF_REG4,          "smsww\t" OP_RM16),
	I(0x01, IF_MODRM|IF_REG4,                "smswl\t" OP_RM32),
	I(0x01, IF_MODRM|IF_REXW|IF_REG4,        "smswq\t" OP_RM64),

	I(0x01, IF_MODRM|IF_REG6,                "lmsw\t" OP_RM16),

	I(0x01, IF_MODRM|IF_RMM|IF_REG7,         "invlpg\t" OP_MEM),

	I(0x01, IF_BYTE2,                 "\xf8" "swapgs"),
	I(0x01, IF_BYTE2,                 "\xf9" "rdtscp"),

	I(0x01, IF_BYTE2,                 "\xc1" "vmcall"),
	I(0x01, IF_BYTE2,                 "\xc2" "vmlaunch"),
	I(0x01, IF_BYTE2,                 "\xc3" "vmresume"),
	I(0x01, IF_BYTE2,                 "\xc4" "vmxoff"),
	I(0x01, IF_BYTE2,                 "\xc8" "monitor\t" OP_PAX_PCX_PDX),
	I(0x01, IF_BYTE2,                 "\xc9" "mwait\t" OP_PAX_PCX),
	I(0x01, IF_BYTE2,                 "\xca" "clac"),
	I(0x01, IF_BYTE2,                 "\xcb" "stac"),
	I(0x01, IF_BYTE2,                 "\xcf" "encls"),
	I(0x01, IF_BYTE2,                 "\xd0" "xgetbv"),
	I(0x01, IF_BYTE2,                 "\xd1" "xsetbv"),
	I(0x01, IF_BYTE2,                 "\xd4" "vmfunc"),
	I(0x01, IF_BYTE2,                 "\xd5" "xend"),
	I(0x01, IF_BYTE2,                 "\xd6" "xtest"),
	I(0x01, IF_BYTE2,                 "\xd7" "enclu"),

	I(0x02, IF_66|IF_MODRM,   "larw\t" OP_RM16 OP_R16),
	I(0x02, IF_MODRM,         "larl\t" OP_RM32 OP_R32),
	I(0x03, IF_66|IF_MODRM,   "lslw\t" OP_RM16 OP_R16),
	I(0x03, IF_MODRM,         "lsll\t" OP_RM32 OP_R32),

	I(0x05, IF_X32,           "loadall"), /* Unofficial */
	I(0x05, IF_X64,           "syscall"),
	I(0x06, 0,                "clts"),
	I(0x07, IF_X32,           "loadall\t" OP_PSI), /* Unofficial */
	I(0x07, IF_X64,           "sysret"),
	I(0x08, 0,                "invd"),
	I(0x09, 0,                "wbinvd"),

	I(0x0a, 0,                "cflsh"),

	I(0x0b, 0,                "ud2"),

	I(0x0d, IF_MODRM|IF_REG1|IF_RMM, "prefetchw\t" OP_MEM),
	I(0x0d, IF_MODRM|IF_REG2|IF_RMM, LONGREPR(LO_PREFETCHWT1)),

	I(0x10, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovups\t" OP_RM128_XMM OP_RXMM),      /*  VEX.128.0f.WIG 10 /r vmovups xmm1, xmm2/m128 */
	I(0x10, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovups\t" OP_RM256_YMM OP_RYMM),      /*  VEX.256.0f.WIG 10 /r vmovups ymm1, ymm2/m256 */
	I(0x10, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vmovups\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.0f.W0  10 /r vmovups xmm1{k1}{z}, xmm2/m128 */
	I(0x10, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vmovups\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.0f.W0  10 /r vmovups ymm1{k1}{z}, ymm2/m256 */
	I(0x10, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vmovups\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.0f.W0  10 /r vmovups zmm1{k1}{z}, zmm2/m512 */

	I(0x10, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovupd\t" OP_RM128_XMM OP_RXMM),      /*  VEX.128.66.0f.WIG 10 /r vmovupd xmm1, xmm2/m128 */
	I(0x10, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovupd\t" OP_RM256_YMM OP_RYMM),      /*  VEX.256.66.0f.WIG 10 /r vmovupd ymm1, ymm2/m256 */
	I(0x10, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vmovupd\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f.W1  10 /r vmovupd xmm1{k1}{z}, xmm2/m128 */
	I(0x10, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vmovupd\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.512.66.0f.W1  10 /r vmovupd ymm1{k1}{z}, ymm2/m256 */
	I(0x10, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmovupd\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f.W1  10 /r vmovupd zmm1{k1}{z}, zmm2/m512 */

	I(0x10, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0_LIG(1, 1, 0) "vmovss\t" OP_RM128_XMM OP_VRXMM OP_RXMM),   /*  VEX.LIG.f3.0f.WIG 10 /r vmovss xmm1, xmm2, xmm3 */
	I(0x10, IF_F3|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0_LIG(1, 1, 0) "vmovss\t" OP_MEM OP_RXMM),                  /*  VEX.LIG.f3.0f.WIG 10 /r vmovss xmm1, m32 */
	I(0x10, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0_LIG(0, 0, 0) "vmovss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* EVEX.LIG.f3.0f.W0  10 /r vmovss xmm1{k1}{z}, xmm2, xmm3 */
	I(0x10, IF_F3|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0_LIG(0, 0, 0) "vmovss\t" OP_MEM OP_RXMM_MASK),             /* EVEX.LIG.f3.0f.W0  10 /r vmovss xmm1{k1}{z}, m32 */

	I(0x10, IF_F2|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0_LIG(1, 1, 0) "vmovsd\t" OP_RM128_XMM OP_VRXMM OP_RXMM),   /*  VEX.LIG.f2.0f.WIG 10 /r vmovsd xmm1, xmm2, xmm3 */
	I(0x10, IF_F2|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0_LIG(1, 1, 0) "vmovsd\t" OP_MEM OP_RXMM),                  /*  VEX.LIG.f2.0f.WIG 10 /r vmovsd xmm1, m64 */
	I(0x10, IF_F2|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0_LIG(0, 0, 1) "vmovsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* EVEX.LIG.f2.0f.W1  10 /r vmovsd xmm1{k1}{z}, xmm2, xmm3 */
	I(0x10, IF_F2|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0_LIG(0, 0, 1) "vmovsd\t" OP_MEM OP_RXMM_MASK),             /* EVEX.LIG.f2.0f.W1  10 /r vmovsd xmm1{k1}{z}, m64 */

	I(0x10, IF_MODRM,              "movups\t" OP_RM128_XMM OP_RXMM), /*    0f 10 /r movups xmm1, xmm2/m128 */
	I(0x10, IF_66|IF_MODRM,        "movupd\t" OP_RM128_XMM OP_RXMM), /* 66 0f 10 /r movupd xmm1, xmm2/m128 */
	I(0x10, IF_F3|IF_MODRM|IF_RMR, "movss\t" OP_RM128_XMM OP_RXMM),  /* f3 0f 10 /r movss xmm1, xmm2 */
	I(0x10, IF_F3|IF_MODRM|IF_RMM, "movss\t" OP_MEM OP_RXMM),        /* f3 0f 10 /r movss xmm1, m32 */
	I(0x10, IF_F2|IF_MODRM|IF_RMR, "movsd\t" OP_RM128_XMM OP_RXMM),  /* f2 0f 10 /r movsd xmm1, xmm2 */
	I(0x10, IF_F2|IF_MODRM|IF_RMM, "movsd\t" OP_MEM OP_RXMM),        /* f2 0f 10 /r movsd xmm1, m64 */

	I(0x11, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovups\t" OP_RXMM OP_RM128_XMM),      /*  VEX.128.0f.WIG 11 /r vmovups xmm2/m128, xmm1 */
	I(0x11, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovups\t" OP_RYMM OP_RM256_YMM),      /*  VEX.256.0f.WIG 11 /r vmovups ymm2/m256, ymm1 */
	I(0x11, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vmovups\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.0f.W0  11 /r vmovups xmm2/m128{k1}{z}, xmm1 */
	I(0x11, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vmovups\t" OP_RYMM OP_RM256_YMM_MASK), /* EVEX.256.0f.W0  11 /r vmovups ymm2/m256{k1}{z}, ymm1 */
	I(0x11, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vmovups\t" OP_RZMM OP_RM512_ZMM_MASK), /* EVEX.512.0f.W0  11 /r vmovups zmm2/m512{k1}{z}, zmm1 */

	I(0x11, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovupd\t" OP_RXMM OP_RM128_XMM),      /*  VEX.128.66.0f.WIG 11 /r vmovupd xmm2/m128, xmm1 */
	I(0x11, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovupd\t" OP_RYMM OP_RM256_YMM),      /*  VEX.256.66.0f.WIG 11 /r vmovupd ymm2/m256, ymm1 */
	I(0x11, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vmovupd\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.66.0f.W1  11 /r vmovupd xmm2/m128{k1}{z}, xmm1 */
	I(0x11, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vmovupd\t" OP_RYMM OP_RM256_YMM_MASK), /* EVEX.512.66.0f.W1  11 /r vmovupd ymm2/m256{k1}{z}, ymm1 */
	I(0x11, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmovupd\t" OP_RZMM OP_RM512_ZMM_MASK), /* EVEX.512.66.0f.W1  11 /r vmovupd zmm2/m512{k1}{z}, zmm1 */

	I(0x11, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0_LIG(1, 1, 0) "vmovss\t" OP_RM128_XMM OP_VRXMM OP_RXMM),   /*  VEX.LIG.f3.0f.WIG 11 /r vmovss xmm1, xmm2, xmm3 */
	I(0x11, IF_F3|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0_LIG(1, 1, 0) "vmovss\t" OP_RXMM OP_MEM),                  /*  VEX.LIG.f3.0f.WIG 11 /r vmovss m32, xmm1 */
	I(0x11, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0_LIG(0, 0, 0) "vmovss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* EVEX.LIG.f3.0f.W0  11 /r vmovss xmm1{k1}{z}, xmm2, xmm3 */
	I(0x11, IF_F3|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0_LIG(0, 0, 0) "vmovss\t" OP_RXMM OP_MEM_MASK),             /* EVEX.LIG.f3.0f.W0  11 /r vmovss m32{k1}, xmm1 */

	I(0x11, IF_F2|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0_LIG(1, 1, 0) "vmovsd\t" OP_RM128_XMM OP_VRXMM OP_RXMM),   /*  VEX.LIG.f2.0f.WIG 11 /r vmovsd xmm1, xmm2, xmm3 */
	I(0x11, IF_F2|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0_LIG(1, 1, 0) "vmovsd\t" OP_RXMM OP_MEM),                  /*  VEX.LIG.f2.0f.WIG 11 /r vmovsd m64, xmm1 */
	I(0x11, IF_F2|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0_LIG(0, 0, 1) "vmovsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* EVEX.LIG.f2.0f.W1  11 /r vmovsd xmm1{k1}{z}, xmm2, xmm3 */
	I(0x11, IF_F2|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0_LIG(0, 0, 1) "vmovsd\t" OP_RXMM OP_MEM_MASK),             /* EVEX.LIG.f2.0f.W1  11 /r vmovsd m64{k1}, xmm1 */

	I(0x11, IF_MODRM,              "movups\t" OP_RXMM OP_RM128_XMM), /*    0f 11 /r movups xmm2/m128, xmm1 */
	I(0x11, IF_66|IF_MODRM,        "movupd\t" OP_RXMM OP_RM128_XMM), /* 66 0f 11 /r movupd xmm2/m128, xmm1 */
	I(0x11, IF_F3|IF_MODRM|IF_RMR, "movss\t" OP_RXMM OP_RM128_XMM),  /* f3 0f 11 /r movss xmm2/m32, xmm1 */
	I(0x11, IF_F2|IF_MODRM,        "movsd\t" OP_RXMM OP_RM128_XMM),  /* f2 0f 11 /r movsd xmm1/m64, xmm2 */

	I(0x12, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovlpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /*  VEX.128.66.0f.WIG 12 /r vmovlpd xmm2, xmm1, m64 */
	I(0x12, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 1, 0) "vmovlpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* EVEX.128.66.0f.W1  12 /r vmovlpd xmm2, xmm1, m64 */
	I(0x12, IF_66|IF_MODRM|IF_RMM,                              "movlpd\t" OP_MEM OP_RXMM),                   /*              66 0f 12 /r movlpd xmm1, m64 */

	I(0x12, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovddup\t" OP_RM128_XMM OP_RXMM),      /*  VEX.128.f2.0f.WIG 12 /r vmovddup xmm1, xmm2/m64 */
	I(0x12, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovddup\t" OP_RM256_YMM OP_RYMM),      /*  VEX.256.f2.0f.WIG 12 /r vmovddup ymm1, ymm2/m256 */
	I(0x12, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vmovddup\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.f2.0f.W1  12 /r vmovddup xmm1{k1}{z}, xmm2/m64 */
	I(0x12, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vmovddup\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.f2.0f.W1  12 /r vmovddup ymm1{k1}{z}, ymm2/m256 */
	I(0x12, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmovddup\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.f2.0f.W1  12 /r vmovddup zmm1{k1}{z}, zmm2/m512 */
	I(0x12, IF_F2|IF_MODRM,                              "movddup\t" OP_RM128_XMM OP_RXMM),       /*              f2 0f 12 /r movddup xmm1, xmm2/m64 */

	I(0x12, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VMOVSLDUP_XMM)), /*  VEX.128.f3.0f.WIG 12 /r vmovsldup xmm1, xmm2/m128 */
	I(0x12, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VMOVSLDUP_YMM)), /*  VEX.256.f3.0f.WIG 12 /r vmovsldup ymm1, ymm2/m256 */
	I(0x12, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VMOVSLDUP_XMM)), /* EVEX.128.f3.0f.W0  12 /r vmovsldup xmm1{k1}{z}, xmm2/m128 */
	I(0x12, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VMOVSLDUP_YMM)), /* EVEX.256.f3.0f.W0  12 /r vmovsldup ymm1{k1}{z}, ymm2/m256 */
	I(0x12, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VMOVSLDUP_ZMM)), /* EVEX.512.f3.0f.W0  12 /r vmovsldup zmm1{k1}{z}, zmm2/m512 */
	I(0x12, IF_F3|IF_MODRM,        "movsldup\t" OP_RM128_XMM OP_RXMM),                     /*              f3 0f 12 /r movsldup xmm1, xmm2/m128 */

	I(0x12, IF_VEX|IF_MODRM|IF_RMR, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VMOVHLPS)), /*  VEX.128.0f.WIG 12 /r vmovhlps xmm1, xmm2, xmm3 */
	I(0x12, IF_VEX|IF_MODRM|IF_RMR, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VMOVHLPS)), /* EVEX.128.0f.W0  12 /r vmovhlps xmm1, xmm2, xmm3 */
	I(0x12, IF_MODRM|IF_RMR,        "movhlps\t" OP_RM128_XMM OP_RXMM),                 /*              0f 12 /r movhlps xmm1, xmm2 */

	I(0x12, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovlps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /*  VEX.128.0f.WIG 12 /r vmovlps xmm2, xmm1, m64 */
	I(0x12, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "vmovlps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* EVEX.128.0f.W0  12 /r vmovlps xmm2, xmm1, m64 */
	I(0x12, IF_MODRM|IF_RMM,                              "movlps\t" OP_MEM OP_RXMM),                   /*              0f 12 /r movlps xmm1, m64 */

	I(0x13, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovlps\t" OP_RXMM OP_MEM), /*  VEX.128.0f.WIG 13 /r vmovlps m64, xmm1 */
	I(0x13, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "vmovlps\t" OP_RXMM OP_MEM), /* EVEX.128.0f.W0  13 /r vmovlps m64, xmm1 */

	I(0x13, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovlpd\t" OP_RXMM OP_MEM), /*  VEX.128.66.0f.WIG 13 /r vmovlpd m64, xmm1 */
	I(0x13, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 1, 0) "vmovlpd\t" OP_RXMM OP_MEM), /* EVEX.128.66.0f.W1  13 /r vmovlpd m64, xmm1 */

	I(0x13, IF_MODRM|IF_RMM,       "movlps\t" OP_RXMM OP_MEM), /*    0f 13 /r movlps m64, xmm1 */
	I(0x13, IF_66|IF_MODRM|IF_RMM, "movlpd\t" OP_RXMM OP_MEM), /* 66 0f 13 /r movlpd m64, xmm1 */

	I(0x14, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vunpcklps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.0f.WIG 14 /r vunpcklps xmm1, xmm2, xmm3/m128 */
	I(0x14, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vunpcklps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.0f.WIG 14 /r vunpcklps ymm1, ymm2, ymm3/m256 */
	I(0x14, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vunpcklps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.0f.W0  14 /r vunpcklps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x14, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vunpcklps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.0f.W0  14 /r vunpcklps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x14, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vunpcklps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  14 /r vunpcklps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x14, IF_MODRM,                              "unpcklps\t" OP_RM128_XMM OP_RXMM),                  /*              0f 14 /r unpcklps xmm1, xmm2/m128 */

	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vunpcklpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG 14 /r vunpcklpd xmm1, xmm2, xmm3/m128 */
	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vunpcklpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG 14 /r vunpcklpd ymm1, ymm2, ymm3/m256 */
	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vunpcklpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  14 /r vunpcklpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vunpcklpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  14 /r vunpcklpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vunpcklpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  14 /r vunpcklpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x14, IF_66|IF_MODRM,                              "unpcklpd\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f 14 /r unpcklpd xmm1, xmm2/m128 */

	I(0x15, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vunpckhps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.0f.WIG 15 /r vunpckhps xmm1, xmm2, xmm3/m128 */
	I(0x15, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vunpckhps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.0f.WIG 15 /r vunpckhps ymm1, ymm2, ymm3/m256 */
	I(0x15, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vunpckhps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.0f.W0  15 /r vunpckhps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x15, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vunpckhps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.0f.W0  15 /r vunpckhps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x15, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vunpckhps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  15 /r vunpckhps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x15, IF_MODRM,                              "unpckhps\t" OP_RM128_XMM OP_RXMM),                  /*              0f 15 /r unpckhps xmm1, xmm2/m128 */

	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vunpckhpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG 15 /r vunpckhpd xmm1, xmm2, xmm3/m128 */
	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vunpckhpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG 15 /r vunpckhpd ymm1, ymm2, ymm3/m256 */
	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vunpckhpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  15 /r vunpckhpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vunpckhpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  15 /r vunpckhpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vunpckhpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  15 /r vunpckhpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x15, IF_66|IF_MODRM,                              "unpckhpd\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f 15 /r unpckhpd xmm1, xmm2/m128 */

	I(0x16, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VMOVSHDUP_XMM)), /*  VEX.128.f3.0f.WIG 16 /r vmovshdup xmm1, xmm2/m128 */
	I(0x16, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VMOVSHDUP_YMM)), /*  VEX.256.f3.0f.WIG 16 /r vmovshdup ymm1, ymm2/m256 */
	I(0x16, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VMOVSHDUP_XMM)), /* EVEX.128.f3.0f.W0  16 /r vmovshdup xmm1{k1}{z}, xmm2/m128 */
	I(0x16, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VMOVSHDUP_YMM)), /* EVEX.256.f3.0f.W0  16 /r vmovshdup ymm1{k1}{z}, ymm2/m256 */
	I(0x16, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VMOVSHDUP_ZMM)), /* EVEX.512.f3.0f.W0  16 /r vmovshdup zmm1{k1}{z}, zmm2/m512 */
	I(0x16, IF_F3|IF_MODRM,        "movshdup\t" OP_RM128_XMM OP_RXMM),                     /*              f3 0f 16 /r movshdup xmm1, xmm2/m128 */

	I(0x16, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovhps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /*  VEX.128.0f.WIG 16 /r vmovhps xmm2, xmm1, m64 */
	I(0x16, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "vmovhps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* EVEX.128.0f.W0  16 /r vmovhps xmm2, xmm1, m64 */
	I(0x16, IF_MODRM|IF_RMM,                              "movhps\t" OP_MEM OP_RXMM),                   /*              0f 16 /r movhps xmm1, m64 */

	I(0x16, IF_VEX|IF_MODRM|IF_RMR, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VMOVLHPS)), /*  VEX.128.0f.WIG 16 /r vmovlhps xmm1, xmm2, xmm3 */
	I(0x16, IF_VEX|IF_MODRM|IF_RMR, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VMOVLHPS)), /* EVEX.128.0f.W0  16 /r vmovlhps xmm1, xmm2, xmm3 */
	I(0x16, IF_MODRM|IF_RMR,        "movlhps\t" OP_RM128_XMM OP_RXMM),                 /*              0f 16 /r movlhps xmm1, xmm2 */

	I(0x16, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovhpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /*  VEX.128.66.0f.WIG 16 /r vmovhpd xmm2, xmm1, m64 */
	I(0x16, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 1, 0) "vmovhpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* EVEX.128.66.0f.W1  16 /r vmovhpd xmm2, xmm1, m64 */
	I(0x16, IF_66|IF_MODRM|IF_RMM,                              "movhpd\t" OP_MEM OP_RXMM),                   /*              66 0f 16 /r movhpd xmm1, m64 */

	I(0x17, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovhps\t" OP_RXMM OP_MEM), /*  VEX.128.0f.WIG 17 /r vmovhps m64, xmm1 */
	I(0x17, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "vmovhps\t" OP_RXMM OP_MEM), /* EVEX.128.0f.W0  17 /r vmovhps m64, xmm1 */
	I(0x17, IF_MODRM|IF_RMM,                              "movhps\t" OP_RXMM OP_MEM),  /*              0f 17 /r movhps m64, xmm1 */

	I(0x17, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovhpd\t" OP_RXMM OP_MEM), /*  VEX.128.66.0f.WIG 17 /r vmovhpd m64, xmm1 */
	I(0x17, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 1, 0) "vmovhpd\t" OP_RXMM OP_MEM), /* EVEX.128.66.0f.W1  17 /r vmovhpd m64, xmm1 */
	I(0x17, IF_66|IF_MODRM|IF_RMM,                              "movhpd\t" OP_RXMM OP_MEM),  /*              66 0f 17 /r movhpd m64, xmm1 */

	I(0x18, IF_MODRM|IF_REG0|IF_RMM, LONGREPR(LO_PREFETCHNTA)),
	I(0x18, IF_MODRM|IF_REG1|IF_RMM, "prefetcht0\t" OP_MEM),
	I(0x18, IF_MODRM|IF_REG2|IF_RMM, "prefetcht1\t" OP_MEM),
	I(0x18, IF_MODRM|IF_REG3|IF_RMM, "prefetcht2\t" OP_MEM),

	I(0x1a, IF_X32|IF_F2|IF_MODRM, "bndcu\t" OP_RM32 OP_RBND),
	I(0x1a, IF_X64|IF_F2|IF_MODRM, "bndcu\t" OP_RM64 OP_RBND),
	I(0x1a, IF_X32|IF_F3|IF_MODRM, "bndcl\t" OP_RM32 OP_RBND),
	I(0x1a, IF_X64|IF_F3|IF_MODRM, "bndcl\t" OP_RM64 OP_RBND),
	I(0x1a, IF_MODRM,              "bndldx\t" OP_RMBND_RANGE OP_RBND),
	I(0x1a, IF_66|IF_MODRM,        "bndmov\t" OP_RMBND OP_RBND),
	I(0x1b, IF_X32|IF_F2|IF_MODRM, "bndcn\t" OP_RM32 OP_RBND),
	I(0x1b, IF_X64|IF_F2|IF_MODRM, "bndcn\t" OP_RM64 OP_RBND),
	I(0x1b, IF_66|IF_MODRM,        "bndmov\t" OP_RBND OP_RMBND),
	I(0x1b, IF_X32|IF_F3|IF_MODRM, "bndmk\t" OP_RM32 OP_RBND),
	I(0x1b, IF_X64|IF_F3|IF_MODRM, "bndmk\t" OP_RM64 OP_RBND),

	I(0x1c, IF_MODRM|IF_REG0|IF_RMM, "cldemote\t" OP_MEM),

	I(0x1f, IF_66|IF_MODRM|IF_REG0, "nopw\t" OP_RM16),
	I(0x1f, IF_MODRM|IF_REG0,       "nopl\t" OP_RM32),

	I(0x20, IF_X32|IF_MODRM|IF_RMR,"movl\t" OP_RCR OP_RM32),
	I(0x20, IF_X64|IF_MODRM|IF_RMR,"movq\t" OP_RCR OP_RM64),
	I(0x21, IF_X32|IF_MODRM|IF_RMR,"movl\t" OP_RDR OP_RM32),
	I(0x21, IF_X64|IF_MODRM|IF_RMR,"movq\t" OP_RDR OP_RM64),
	I(0x22, IF_X32|IF_MODRM|IF_RMR,"movl\t" OP_RM32 OP_RCR),
	I(0x22, IF_X64|IF_MODRM|IF_RMR,"movq\t" OP_RM64 OP_RCR),
	I(0x23, IF_X32|IF_MODRM|IF_RMR,"movl\t" OP_RM32 OP_RDR),
	I(0x23, IF_X64|IF_MODRM|IF_RMR,"movq\t" OP_RM64 OP_RDR),

	/* Move to/from test registers (s.a. `https://css.csail.mit.edu/6.858/2014/readings/i386/MOVRS.htm')
	 * Note that these instructions only existed on the i386 and were removed on later processors! */
	I(0x24, IF_MODRM|IF_RMR,  "movl\t" OP_RTR OP_RM32),
	I(0x26, IF_MODRM|IF_RMR,  "movl\t" OP_RM32 OP_RTR),

	I(0x28, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovaps\t" OP_RM128_XMM OP_RXMM),      /*  VEX.128.0f.WIG 28 /r vmovaps xmm1, xmm2/m128 */
	I(0x28, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovaps\t" OP_RM256_YMM OP_RYMM),      /*  VEX.256.0f.WIG 28 /r vmovaps ymm1, ymm2/m256 */
	I(0x28, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vmovaps\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.0f.W0  28 /r vmovaps xmm1{k1}{z}, xmm2/m128 */
	I(0x28, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vmovaps\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.0f.W0  28 /r vmovaps ymm1{k1}{z}, ymm2/m256 */
	I(0x28, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vmovaps\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.0f.W0  28 /r vmovaps zmm1{k1}{z}, zmm2/m512 */
	I(0x28, IF_MODRM,                              "movaps\t" OP_RM128_XMM OP_RXMM),       /*              0f 28 /r movaps xmm1, xmm2/m128 */

	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovapd\t" OP_RM128_XMM OP_RXMM),      /*  VEX.128.66.0f.WIG 28 /r vmovapd xmm1, xmm2/m128 */
	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovapd\t" OP_RM256_YMM OP_RYMM),      /*  VEX.256.66.0f.WIG 28 /r vmovapd ymm1, ymm2/m256 */
	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vmovapd\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f.W1  28 /r vmovapd xmm1{k1}{z}, xmm2/m128 */
	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vmovapd\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.512.66.0f.W1  28 /r vmovapd ymm1{k1}{z}, ymm2/m256 */
	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmovapd\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f.W1  28 /r vmovapd zmm1{k1}{z}, zmm2/m512 */
	I(0x28, IF_66|IF_MODRM,                              "movapd\t" OP_RM128_XMM OP_RXMM),       /*              66 0f 28 /r movapd xmm1, xmm2/m128 */

	I(0x29, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovaps\t" OP_RXMM OP_RM128_XMM),      /*  VEX.128.0f.WIG 29 /r vmovaps xmm2/m128, xmm1 */
	I(0x29, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovaps\t" OP_RYMM OP_RM256_YMM),      /*  VEX.256.0f.WIG 29 /r vmovaps ymm2/m256, ymm1 */
	I(0x29, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vmovaps\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.0f.W0  29 /r vmovaps xmm2/m128{k1}{z}, xmm1 */
	I(0x29, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vmovaps\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.0f.W0  29 /r vmovaps ymm2/m256{k1}{z}, ymm1 */
	I(0x29, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vmovaps\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.0f.W0  29 /r vmovaps zmm2/m512{k1}{z}, zmm1 */
	I(0x29, IF_MODRM,                              "movaps\t" OP_RXMM OP_RM128_XMM),       /*              0f 29 /r movaps xmm2/m128, xmm1 */

	I(0x29, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovapd\t" OP_RXMM OP_RM128_XMM),      /*  VEX.128.66.0f.WIG 29 /r vmovapd xmm2/m128, xmm1 */
	I(0x29, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovapd\t" OP_RYMM OP_RM256_YMM),      /*  VEX.256.66.0f.WIG 29 /r vmovapd ymm2/m256, ymm1 */
	I(0x29, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vmovapd\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f.W1  29 /r vmovapd xmm2/m128{k1}{z}, xmm1 */
	I(0x29, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vmovapd\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.512.66.0f.W1  29 /r vmovapd ymm2/m256{k1}{z}, ymm1 */
	I(0x29, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmovapd\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f.W1  29 /r vmovapd zmm2/m512{k1}{z}, zmm1 */
	I(0x29, IF_66|IF_MODRM,                              "movapd\t" OP_RXMM OP_RM128_XMM),       /*              66 0f 29 /r movapd xmm2/m128, xmm1 */

	I(0x2a, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VCVTSI2SS_R32)), /* EVEX.LIG.f3.0f.W0 2a /r vcvtsi2ss xmm1, xmm2, r/m32{er} */
	I(0x2a, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VCVTSI2SS_R64)), /* EVEX.LIG.f3.0f.W1 2a /r vcvtsi2ss xmm1, xmm2, r/m64{er} */

	I(0x2a, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VCVTSI2SD_R32)), /* EVEX.LIG.f2.0f.W0 2a /r vcvtsi2sd xmm1, xmm2, r/m32 */
	I(0x2a, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VCVTSI2SD_R64)), /* EVEX.LIG.f2.0f.W1 2a /r vcvtsi2sd xmm1, xmm2, r/m64{er} */

	I(0x2a, IF_MODRM,               "cvtpi2ps\t" OP_RM64_MM OP_RXMM_MASK),
	I(0x2a, IF_F3|IF_MODRM,         "cvtsi2ss\t" OP_RM32 OP_RXMM),    /* f3       0f 2a /r cvtsi2ss xmm1, r/m32 */
	I(0x2a, IF_F3|IF_MODRM|IF_REXW, "cvtsi2ss\t" OP_RM64 OP_RXMM),    /* f3 rex.w 0f 2a /r cvtsi2ss xmm1, r/m64 */
	I(0x2a, IF_66|IF_MODRM,         "cvtpi2pd\t" OP_RM64_MM OP_RXMM), /*       66 0f 2a /r cvtpi2pd xmm, mm/m64* */
	I(0x2a, IF_F2|IF_MODRM,         "cvtsi2sd\t" OP_RM32 OP_RXMM),    /* f2       0f 2a /r cvtsi2sd xmm1, r/m32 */
	I(0x2a, IF_F2|IF_MODRM|IF_REXW, "cvtsi2sd\t" OP_RM64 OP_RXMM),    /* f2 rex.w 0f 2a /r cvtsi2sd xmm1, r/m64 */

	I(0x2b, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovntps\t" OP_RXMM OP_MEM), /*  VEX.128.0f.WIG 2b /r vmovntps m128, xmm1 */
	I(0x2b, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 1) "vmovntps\t" OP_RYMM OP_MEM), /*  VEX.256.0f.WIG 2b /r vmovntps m256, ymm1 */
	I(0x2b, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "vmovntps\t" OP_RXMM OP_MEM), /* EVEX.128.0f.W0  2b /r vmovntps m128, xmm1 */
	I(0x2b, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 1) "vmovntps\t" OP_RYMM OP_MEM), /* EVEX.256.0f.W0  2b /r vmovntps m256, ymm1 */
	I(0x2b, IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 2) "vmovntps\t" OP_RZMM OP_MEM), /* EVEX.512.0f.W0  2b /r vmovntps m512, zmm1 */

	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovntpd\t" OP_RXMM OP_MEM), /*  VEX.128.66.0f.WIG 2b /r vmovntpd m128, xmm1 */
	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovntpd\t" OP_RYMM OP_MEM), /*  VEX.256.66.0f.WIG 2b /r vmovntpd m256, ymm1 */
	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vmovntpd\t" OP_RXMM OP_MEM), /* EVEX.128.66.0f.W1  2b /r vmovntpd m128, xmm1 */
	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmovntpd\t" OP_RYMM OP_MEM), /* EVEX.512.66.0f.W1  2b /r vmovntpd m256, ymm1 */
	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmovntpd\t" OP_RZMM OP_MEM), /* EVEX.512.66.0f.W1  2b /r vmovntpd m512, zmm1 */

	I(0x2b, IF_MODRM|IF_RMM, "movntps\t" OP_RXMM OP_MEM),  /*    0f 2b /r movntps m128, xmm1 */
	I(0x2b, IF_66|IF_MODRM,  "movntpd\t" OP_RXMM OP_MEM),  /* 66 0f 2b /r movntpd m128, xmm1 */

	I(0x2c, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VCVTTSS2SI_R32)), /* EVEX.LIG.f3.0f.W0 2c /r vcvttss2si r32, xmm1/m32{sae} */
	I(0x2c, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VCVTTSS2SI_R64)), /* EVEX.LIG.f3.0f.W1 2c /r vcvttss2si r64, xmm1/m32{sae} */

	I(0x2c, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VCVTTSD2SI_R32)), /* EVEX.LIG.f2.0f.W0 2c /r vcvttsd2si r32, xmm1/m64{sae} */
	I(0x2c, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VCVTTSD2SI_R64)), /* EVEX.LIG.f2.0f.W1 2c /r vcvttsd2si r64, xmm1/m64{sae} */

	I(0x2c, IF_66|IF_MODRM,         "cvttpd2pi\t" OP_RM128_XMM OP_RMM),
	I(0x2c, IF_MODRM,               "cvttps2pi\t" OP_RM128_XMM OP_RMM),
	I(0x2c, IF_F3|IF_MODRM,         "cvttss2si\t" OP_RM128_XMM OP_R32), /* f3       0f 2c /r cvttss2si r32, xmm1/m32 */
	I(0x2c, IF_F3|IF_MODRM|IF_REXW, "cvttss2si\t" OP_RM128_XMM OP_R64), /* f3 rex.w 0f 2c /r cvttss2si r64, xmm1/m32 */
	I(0x2c, IF_F2|IF_MODRM,         "cvttsd2si\t" OP_RM128_XMM OP_R32), /* f2       0f 2c /r cvttsd2si r32, xmm1/m64 */
	I(0x2c, IF_F2|IF_MODRM|IF_REXW, "cvttsd2si\t" OP_RM128_XMM OP_R64), /* f2 rex.w 0f 2c /r cvttsd2si r64, xmm1/m64 */

	I(0x2d, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VCVTSD2SI_R32)), /* EVEX.LIG.f2.0f.W0 2d /r vcvtsd2si r32, xmm1/m64{er} */
	I(0x2d, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VCVTSD2SI_R64)), /* EVEX.LIG.f2.0f.W1 2d /r vcvtsd2si r64, xmm1/m64{er} */

	I(0x2d, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VCVTSS2SI_R32)), /* EVEX.LIG.f3.0f.W0 2d /r vcvtss2si r32, xmm1/m32{er} */
	I(0x2d, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VCVTSS2SI_R64)), /* EVEX.LIG.f3.0f.W1 2d /r vcvtss2si r64, xmm1/m32{er} */

	I(0x2d, IF_66|IF_MODRM,         "cvtpd2pi\t" OP_RM128_XMM OP_RMM),
	I(0x2d, IF_MODRM,               "cvtps2pi\t" OP_RM128_XMM OP_RMM),
	I(0x2d, IF_F2|IF_MODRM,         "cvtsd2si\t" OP_RM128_XMM OP_R32), /* f2       0f 2d /r cvtsd2si r32, xmm1/m64 */
	I(0x2d, IF_F2|IF_MODRM|IF_REXW, "cvtsd2si\t" OP_RM128_XMM OP_R64), /* f2 rex.w 0f 2d /r cvtsd2si r64, xmm1/m64 */
	I(0x2d, IF_F3|IF_MODRM,         "cvtss2si\t" OP_RM128_XMM OP_R32), /* f3       0f 2d /r cvtss2si r32, xmm1/m32 */
	I(0x2d, IF_F3|IF_MODRM|IF_REXW, "cvtss2si\t" OP_RM128_XMM OP_R64), /* f3 rex.w 0f 2d /r cvtss2si r64, xmm1/m32 */

	I(0x2e, IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vucomiss\t" OP_RM128_XMM OP_RXMM), /*  VEX.LIG.0f.WIG 2e /r vucomiss xmm1, xmm2/m32 */
	I(0x2e, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VUCOMISS)),    /* EVEX.LIG.0f.W0  2e /r vucomiss xmm1, xmm2/m32{sae} */

	I(0x2e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vucomisd\t" OP_RM128_XMM OP_RXMM), /*  VEX.LIG.66.0f.WIG 2e /r vucomisd xmm1, xmm2/m64 */
	I(0x2e, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VUCOMISD)),    /* EVEX.LIG.66.0f.W1  2e /r vucomisd xmm1, xmm2/m64{sae} */

	I(0x2e, IF_MODRM,       "ucomiss\t" OP_RM128_XMM OP_RXMM), /*    0f 2e /r ucomiss xmm1, xmm2/m32 */
	I(0x2e, IF_66|IF_MODRM, "ucomisd\t" OP_RM128_XMM OP_RXMM), /* 66 0f 2e /r ucomisd xmm1, xmm2/m64 */

	I(0x2f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vcomisd\t" OP_RM128_XMM OP_RXMM),        /*  VEX.LIG.66.0f.WIG 2f /r vcomisd xmm1, xmm2/m64 */
	I(0x2f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vcomisd\t" OP_SAE OP_RM128_XMM OP_RXMM), /* EVEX.LIG.66.0f.W1  2f /r vcomisd xmm1, xmm2/m64{sae} */

	I(0x2f, IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vcomiss\t" OP_RM128_XMM OP_RXMM),             /*  VEX.LIG.0f.WIG 2f /r vcomiss xmm1, xmm2/m32 */
	I(0x2f, IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vcomiss\t" OP_SAE OP_RM128_XMM OP_RXMM_MASK), /* EVEX.LIG.0f.W0  2f /r vcomiss xmm1, xmm2/m32{sae} */

	I(0x2f, IF_MODRM,       "comiss\t" OP_RM128_XMM OP_RXMM), /*    0f 2f /r comiss xmm1, xmm2/m32 */
	I(0x2f, IF_66|IF_MODRM, "comisd\t" OP_RM128_XMM OP_RXMM), /* 66 0f 2f /r comisd xmm1, xmm2/m64 */

	I(0x30, 0,                "wrmsr"),
	I(0x31, 0,                "rdtsc"),
	I(0x32, 0,                "rdmsr"),
	I(0x33, 0,                "rdpmc"),
	I(0x34, 0,                "sysenter"), /* Unofficial: WRECR??? */
	I(0x35, 0,                "sysexit"),
	I(0x36, 0,                "rdecr"), /* Unofficial */

	I(0x37, 0,                "getsec"),

	/* 0x38 -- PREFIX */
	/* 0x3a -- PREFIX */

	/* VIA secret DEC-enable instruction (activated with msr 1107:bit[0],
	 * instructions send by `bound %eax, <OPCODE>(,%eax,1)') */
	I(0x3f, 0,                "jmp\t" OP_EAX),

	I(0x40, IF_66|IF_MODRM,   "cmov" NAME_jc0 "w\t" OP_RM16 OP_R16),
	I(0x40, IF_MODRM,         "cmov" NAME_jc0 "l\t" OP_RM32 OP_R32),
	I(0x40, IF_MODRM|IF_REXW, "cmov" NAME_jc0 "q\t" OP_RM64 OP_R64),

	I(0x41, IF_VEX|IF_MODRM|IF_RMR,       OP_VEX_B0(0, 0, 0, 1) "kandw\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W0 41 /r kandw k1, k2, k3 */
	I(0x41, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 1) "kandb\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W0 41 /r kandb k1, k2, k3 */
	I(0x41, IF_VEX|IF_MODRM|IF_RMR,       OP_VEX_B0(0, 0, 1, 1) "kandq\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W1 41 /r kandq k1, k2, k3 */
	I(0x41, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 1) "kandd\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W1 41 /r kandd k1, k2, k3 */

	I(0x41, IF_66|IF_MODRM,   "cmov" NAME_jc1 "w\t" OP_RM16 OP_R16),
	I(0x41, IF_MODRM,         "cmov" NAME_jc1 "l\t" OP_RM32 OP_R32),
	I(0x41, IF_MODRM|IF_REXW, "cmov" NAME_jc1 "q\t" OP_RM64 OP_R64),

	I(0x42, IF_VEX|IF_MODRM|IF_RMR,       OP_VEX_B0(0, 0, 0, 1) "kandnw\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W0 42 /r kandnw k1, k2, k3 */
	I(0x42, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 1) "kandnb\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W0 42 /r kandnb k1, k2, k3 */
	I(0x42, IF_VEX|IF_MODRM|IF_RMR,       OP_VEX_B0(0, 0, 1, 1) "kandnq\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W1 42 /r kandnq k1, k2, k3 */
	I(0x42, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 1) "kandnd\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W1 42 /r kandnd k1, k2, k3 */

	I(0x42, IF_66|IF_MODRM,   "cmov" NAME_jc2 "w\t" OP_RM16 OP_R16),
	I(0x42, IF_MODRM,         "cmov" NAME_jc2 "l\t" OP_RM32 OP_R32),
	I(0x42, IF_MODRM|IF_REXW, "cmov" NAME_jc2 "q\t" OP_RM64 OP_R64),

	I(0x43, IF_66|IF_MODRM,   "cmov" NAME_jc3 "w\t" OP_RM16 OP_R16),
	I(0x43, IF_MODRM,         "cmov" NAME_jc3 "l\t" OP_RM32 OP_R32),
	I(0x43, IF_MODRM|IF_REXW, "cmov" NAME_jc3 "q\t" OP_RM64 OP_R64),

	I(0x44, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "knotb\t" OP_RMK OP_RK), /* VEX.L0.66.0f.W0 44 /r knotb k1, k2 */
	I(0x44, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 0, 0) "knotw\t" OP_RMK OP_RK), /* VEX.L0.   0f.W0 44 /r knotw k1, k2 */
	I(0x44, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "knotd\t" OP_RMK OP_RK), /* VEX.L0.66.0f.W1 44 /r knotd k1, k2 */
	I(0x44, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 1, 0) "knotq\t" OP_RMK OP_RK), /* VEX.L0.   0f.W1 44 /r knotq k1, k2 */

	I(0x44, IF_66|IF_MODRM,   "cmov" NAME_jc4 "w\t" OP_RM16 OP_R16),
	I(0x44, IF_MODRM,         "cmov" NAME_jc4 "l\t" OP_RM32 OP_R32),
	I(0x44, IF_MODRM|IF_REXW, "cmov" NAME_jc4 "q\t" OP_RM64 OP_R64),

	I(0x45, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "korb\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W0 45 /r korb k1, k2, k3 */
	I(0x45, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 0, 1) "korw\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W0 45 /r korw k1, k2, k3 */
	I(0x45, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "kord\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W1 45 /r kord k1, k2, k3 */
	I(0x45, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 1, 1) "korq\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W1 45 /r korq k1, k2, k3 */

	I(0x45, IF_66|IF_MODRM,   "cmov" NAME_jc5 "w\t" OP_RM16 OP_R16),
	I(0x45, IF_MODRM,         "cmov" NAME_jc5 "l\t" OP_RM32 OP_R32),
	I(0x45, IF_MODRM|IF_REXW, "cmov" NAME_jc5 "q\t" OP_RM64 OP_R64),

	I(0x46, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "kxnorb\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W0 46 /r kxnorb k1, k2, k3 */
	I(0x46, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 0, 1) "kxnorw\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W0 46 /r kxnorw k1, k2, k3 */
	I(0x46, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "kxnord\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W1 46 /r kxnord k1, k2, k3 */
	I(0x46, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 1, 1) "kxnorq\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W1 46 /r kxnorq k1, k2, k3 */

	I(0x46, IF_66|IF_MODRM,   "cmov" NAME_jc6 "w\t" OP_RM16 OP_R16),
	I(0x46, IF_MODRM,         "cmov" NAME_jc6 "l\t" OP_RM32 OP_R32),
	I(0x46, IF_MODRM|IF_REXW, "cmov" NAME_jc6 "q\t" OP_RM64 OP_R64),

	I(0x47, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "kxorb\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W0 47 /r kxorb k1, k2, k3 */
	I(0x47, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 0, 1) "kxorw\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W0 47 /r kxorw k1, k2, k3 */
	I(0x47, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "kxord\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W1 47 /r kxord k1, k2, k3 */
	I(0x47, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 1, 1) "kxorq\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W1 47 /r kxorq k1, k2, k3 */

	I(0x47, IF_66|IF_MODRM,   "cmov" NAME_jc7 "w\t" OP_RM16 OP_R16),
	I(0x47, IF_MODRM,         "cmov" NAME_jc7 "l\t" OP_RM32 OP_R32),
	I(0x47, IF_MODRM|IF_REXW, "cmov" NAME_jc7 "q\t" OP_RM64 OP_R64),

	I(0x48, IF_66|IF_MODRM,   "cmov" NAME_jc8 "w\t" OP_RM16 OP_R16),
	I(0x48, IF_MODRM,         "cmov" NAME_jc8 "l\t" OP_RM32 OP_R32),
	I(0x48, IF_MODRM|IF_REXW, "cmov" NAME_jc8 "q\t" OP_RM64 OP_R64),

	I(0x49, IF_66|IF_MODRM,   "cmov" NAME_jc9 "w\t" OP_RM16 OP_R16),
	I(0x49, IF_MODRM,         "cmov" NAME_jc9 "l\t" OP_RM32 OP_R32),
	I(0x49, IF_MODRM|IF_REXW, "cmov" NAME_jc9 "q\t" OP_RM64 OP_R64),

	I(0x4a, IF_VEX|IF_MODRM|IF_RMR,       OP_VEX_B0(0, 0, 0, 1) "kaddw\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W0 4a /r kaddw k1, k2, k3 */
	I(0x4a, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 1) "kaddb\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W0 4a /r kaddb k1, k2, k3 */
	I(0x4a, IF_VEX|IF_MODRM|IF_RMR,       OP_VEX_B0(0, 0, 1, 1) "kaddq\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.   0f.W1 4a /r kaddq k1, k2, k3 */
	I(0x4a, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 1) "kaddd\t" OP_RMK OP_VRK OP_RK), /* VEX.L1.66.0f.W1 4a /r kaddd k1, k2, k3 */

	I(0x4a, IF_66|IF_MODRM,   "cmov" NAME_jca "w\t" OP_RM16 OP_R16),
	I(0x4a, IF_MODRM,         "cmov" NAME_jca "l\t" OP_RM32 OP_R32),
	I(0x4a, IF_MODRM|IF_REXW, "cmov" NAME_jca "q\t" OP_RM64 OP_R64),

	I(0x4b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_KUNPCKBW)), /* VEX.L1.66.0f.W0 4b /r kunpckbw k1, k2, k3 */
	I(0x4b, IF_VEX|IF_MODRM,       LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_KUNPCKWD)), /* VEX.L1.   0f.W0 4b /r kunpckwd k1, k2, k3 */
	I(0x4b, IF_VEX|IF_MODRM,       LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_KUNPCKDQ)), /* VEX.L1.   0f.W1 4b /r kunpckdq k1, k2, k3 */

	I(0x4b, IF_66|IF_MODRM,   "cmov" NAME_jcb "w\t" OP_RM16 OP_R16),
	I(0x4b, IF_MODRM,         "cmov" NAME_jcb "l\t" OP_RM32 OP_R32),
	I(0x4b, IF_MODRM|IF_REXW,   "cmov" NAME_jcb "q\t" OP_RM64 OP_R64),

	I(0x4c, IF_66|IF_MODRM,   "cmov" NAME_jcc "w\t" OP_RM16 OP_R16),
	I(0x4c, IF_MODRM,         "cmov" NAME_jcc "l\t" OP_RM32 OP_R32),
	I(0x4c, IF_MODRM|IF_REXW, "cmov" NAME_jcc "q\t" OP_RM64 OP_R64),

	I(0x4d, IF_66|IF_MODRM,   "cmov" NAME_jcd "w\t" OP_RM16 OP_R16),
	I(0x4d, IF_MODRM,         "cmov" NAME_jcd "l\t" OP_RM32 OP_R32),
	I(0x4d, IF_MODRM|IF_REXW, "cmov" NAME_jcd "q\t" OP_RM64 OP_R64),

	I(0x4e, IF_66|IF_MODRM,   "cmov" NAME_jce "w\t" OP_RM16 OP_R16),
	I(0x4e, IF_MODRM,         "cmov" NAME_jce "l\t" OP_RM32 OP_R32),
	I(0x4e, IF_MODRM|IF_REXW, "cmov" NAME_jce "q\t" OP_RM64 OP_R64),

	I(0x4f, IF_66|IF_MODRM,   "cmov" NAME_jcf "w\t" OP_RM16 OP_R16),
	I(0x4f, IF_MODRM,         "cmov" NAME_jcf "l\t" OP_RM32 OP_R32),
	I(0x4f, IF_MODRM|IF_REXW, "cmov" NAME_jcf "q\t" OP_RM64 OP_R64),

	I(0x50, IF_VEX|IF_MODRM|IF_RMR,         LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VMOVMSKPS_X_R32)), /* VEX.128.0f.WIG 50 /r vmovmskps r32, xmm2 */
	I(0x50, IF_VEX|IF_MODRM|IF_RMR|IF_REXW, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VMOVMSKPS_X_R64)), /* VEX.128.0f.WIG 50 /r vmovmskps r64, xmm2 */
	I(0x50, IF_VEX|IF_MODRM|IF_RMR,         LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VMOVMSKPS_Y_R32)), /* VEX.256.0f.WIG 50 /r vmovmskps r32, ymm2 */
	I(0x50, IF_VEX|IF_MODRM|IF_RMR|IF_REXW, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VMOVMSKPS_Y_R64)), /* VEX.256.0f.WIG 50 /r vmovmskps r64, ymm2 */

	I(0x50, IF_66|IF_VEX|IF_MODRM|IF_RMR,         LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VMOVMSKPD_X_R32)), /* VEX.128.66.0f.WIG 50 /r vmovmskpd r32, xmm2 */
	I(0x50, IF_66|IF_VEX|IF_MODRM|IF_RMR|IF_REXW, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VMOVMSKPD_X_R64)), /* VEX.128.66.0f.WIG 50 /r vmovmskpd r64, xmm2 */
	I(0x50, IF_66|IF_VEX|IF_MODRM|IF_RMR,         LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VMOVMSKPD_Y_R32)), /* VEX.256.66.0f.WIG 50 /r vmovmskpd r32, ymm2 */
	I(0x50, IF_66|IF_VEX|IF_MODRM|IF_RMR|IF_REXW, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VMOVMSKPD_Y_R64)), /* VEX.256.66.0f.WIG 50 /r vmovmskpd r64, ymm2 */

	I(0x50, IF_MODRM|IF_RMR,               "movmskps\t" OP_RM128_XMM OP_R32), /*    0f 50 /r movmskps r32, xmm */
	I(0x50, IF_MODRM|IF_RMR|IF_REXW,       "movmskps\t" OP_RM128_XMM OP_R64), /*    0f 50 /r movmskps r64, xmm */
	I(0x50, IF_66|IF_MODRM|IF_RMR,         "movmskpd\t" OP_RM128_XMM OP_R32), /* 66 0f 50 /r movmskpd r32, xmm */
	I(0x50, IF_66|IF_MODRM|IF_RMR|IF_REXW, "movmskpd\t" OP_RM128_XMM OP_R64), /* 66 0f 50 /r movmskpd r64, xmm */

	I(0x51, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vsqrtps\t" OP_RM128_XMM OP_RXMM),            /*  VEX.128.0f.WIG 51 /r vsqrtps xmm1, xmm2/m128 */
	I(0x51, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vsqrtps\t" OP_RM256_YMM OP_RYMM),            /*  VEX.256.0f.WIG 51 /r vsqrtps ymm1, ymm2/m256 */
	I(0x51, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vsqrtps\t" OP_RM128_XMM OP_RXMM_MASK),       /* EVEX.128.0f.W0  51 /r vsqrtps xmm1{k1}{z}, xmm2/m128/m32bcst */
	I(0x51, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vsqrtps\t" OP_RM256_YMM OP_RYMM_MASK),       /* EVEX.256.0f.W0  51 /r vsqrtps ymm1{k1}{z}, ymm2/m256/m32bcst */
	I(0x51, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vsqrtps\t" OP_ER OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.0f.W0  51 /r vsqrtps zmm1{k1}{z}, zmm2/m512/m32bcst{er} */

	I(0x51, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vsqrtss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),            /*  VEX.LIG.f3.0f.WIG 51 /r vsqrtss xmm1, xmm2, xmm3/m32 */
	I(0x51, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vsqrtss\t" OP_ER OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.f3.0f.W0  51 /r vsqrtss xmm1{k1}{z}, xmm2, xmm3/m32{er} */

	I(0x51, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vsqrtpd\t" OP_RM128_XMM OP_RXMM),             /*  VEX.128.66.0f.WIG 51 /r vsqrtpd xmm1, xmm2/m128 */
	I(0x51, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vsqrtpd\t" OP_RM256_YMM OP_RYMM),             /*  VEX.256.66.0f.WIG 51 /r vsqrtpd ymm1, ymm2/m256 */
	I(0x51, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vsqrtpd\t" OP_RM128_XMM OP_RXMM_MASK),        /* EVEX.128.66.0f.W1  51 /r vsqrtpd xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0x51, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vsqrtpd\t" OP_RM256_YMM OP_RYMM_MASK),        /* EVEX.512.66.0f.W1  51 /r vsqrtpd ymm1{k1}{z}, ymm2/m256/m64bcst */
	I(0x51, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vsqrtpd\t" OP_SAE OP_RM128_XMM OP_RXMM_MASK), /* EVEX.512.66.0f.W1  51 /r vsqrtpd zmm1{k1}{z}, zmm2/m512/m64bcst{er} */

	I(0x51, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vsqrtsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),            /*  VEX.LIG.f2.0f.WIG 51 /r vsqrtsd xmm1, xmm2, xmm3/m64 */
	I(0x51, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vsqrtsd\t" OP_ER OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.f2.0f.W1  51 /r vsqrtsd xmm1{k1}{z}, xmm2, xmm3/m64{er} */

	I(0x51, IF_MODRM,       "sqrtps\t" OP_RM128_XMM OP_RXMM), /*    0f 51 /r sqrtps xmm1, xmm2/m128 */
	I(0x51, IF_F3|IF_MODRM, "sqrtss\t" OP_RM128_XMM OP_RXMM), /* f3 0f 51 /r sqrtss xmm1, xmm2/m32 */
	I(0x51, IF_66|IF_MODRM, "sqrtpd\t" OP_RM128_XMM OP_RXMM), /* 66 0f 51 /r sqrtpd xmm1, xmm2/m128 */
	I(0x51, IF_F2|IF_MODRM, "sqrtsd\t" OP_RM128_XMM OP_RXMM), /* f2 0f 51 /r sqrtsd xmm1, xmm2/m64 */

	I(0x52, IF_VEX|IF_MODRM,       OP_VEX_B0(1, 1, 0, 0)  "vrsqrtps\t" OP_RM128_XMM OP_RXMM),            /*    VEX.128.0f.WIG 52 /r vrsqrtps xmm1, xmm2/m128 */
	I(0x52, IF_VEX|IF_MODRM,       OP_VEX_B0(1, 1, 0, 1)  "vrsqrtps\t" OP_RM256_YMM OP_RYMM),            /*    VEX.256.0f.WIG 52 /r vrsqrtps ymm1, ymm2/m256 */
	I(0x52, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 1, 0) "vrsqrtss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.LIG.f3.0f.WIG 52 /r vrsqrtss xmm1, xmm2, xmm3/m32 */

	I(0x52, IF_MODRM,       "rsqrtps\t" OP_RM128_XMM OP_RXMM), /*    0f 52 /r rsqrtps xmm1, xmm2/m128 */
	I(0x52, IF_F3|IF_MODRM, "rsqrtss\t" OP_RM128_XMM OP_RXMM), /* f3 0f 52 /r rsqrtss xmm1, xmm2/m32 */

	I(0x53, IF_VEX|IF_MODRM,       OP_VEX_B0(1, 1, 0, 0)  "vrcpps\t" OP_RM128_XMM OP_RXMM),            /*    VEX.128.0f.WIG 53 /r vrcpps xmm1, xmm2/m128 */
	I(0x53, IF_VEX|IF_MODRM,       OP_VEX_B0(1, 1, 0, 1)  "vrcpps\t" OP_RM256_YMM OP_RYMM),            /*    VEX.256.0f.WIG 53 /r vrcpps ymm1, ymm2/m256 */
	I(0x53, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 1, 0) "vrcpss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.LIG.f3.0f.WIG 53 /r vrcpss xmm1, xmm2, xmm3/m32 */

	I(0x53, IF_MODRM,       "rcpps\t" OP_RM128_XMM OP_RXMM), /*    0f 53 /r rcpps xmm1, xmm2/m128 */
	I(0x53, IF_F3|IF_MODRM, "rcpss\t" OP_RM128_XMM OP_RXMM), /* f3 0f 53 /r rcpss xmm1, xmm2/m32 */

	I(0x54, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vandps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.0f.WIG 54 /r vandps xmm1, xmm2, xmm3/m128 */
	I(0x54, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vandps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.0f.WIG 54 /r vandps ymm1, ymm2, ymm3/m256 */
	I(0x54, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vandps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.0f.W0  54 /r vandps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x54, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vandps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.0f.W0  54 /r vandps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x54, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vandps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  54 /r vandps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */

	I(0x54, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vandpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG 54 /r vandpd xmm1, xmm2, xmm3/m128 */
	I(0x54, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vandpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG 54 /r vandpd ymm1, ymm2, ymm3/m256 */
	I(0x54, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vandpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  54 /r vandpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x54, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vandpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  54 /r vandpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x54, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vandpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  54 /r vandpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x54, IF_MODRM,       "andps\t" OP_RM128_XMM OP_RXMM), /*    0f 54 /r andps xmm1, xmm2/m128 */
	I(0x54, IF_66|IF_MODRM, "andpd\t" OP_RM128_XMM OP_RXMM), /* 66 0f 54 /r andpd xmm1, xmm2/m128 */

	I(0x55, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vandnps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.0f.WIG 55 /r vandnps xmm1, xmm2, xmm3/m128 */
	I(0x55, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vandnps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.0f.WIG 55 /r vandnps ymm1, ymm2, ymm3/m256 */
	I(0x55, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vandnps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.0f.W0  55 /r vandnps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x55, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vandnps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.0f.W0  55 /r vandnps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x55, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vandnps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  55 /r vandnps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */

	I(0x55, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vandnpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG 55 /r vandnpd xmm1, xmm2, xmm3/m128 */
	I(0x55, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vandnpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG 55 /r vandnpd ymm1, ymm2, ymm3/m256 */
	I(0x55, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vandnpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  55 /r vandnpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x55, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vandnpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  55 /r vandnpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x55, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vandnpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  55 /r vandnpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x55, IF_MODRM,       "andnps\t" OP_RM128_XMM OP_RXMM), /*    0f 55 /r andnps xmm1, xmm2/m128 */
	I(0x55, IF_66|IF_MODRM, "andnpd\t" OP_RM128_XMM OP_RXMM), /* 66 0f 55 /r andnpd xmm1, xmm2/m128 */

	I(0x56, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vorps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.0f.WIG 56 /r vorps xmm1, xmm2, xmm3/m128 */
	I(0x56, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vorps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.0f.WIG 56 /r vorps ymm1, ymm2, ymm3/m256 */
	I(0x56, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vorps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.0f.W0  56 /r vorps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x56, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vorps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.0f.W0  56 /r vorps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x56, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vorps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  56 /r vorps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */

	I(0x56, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vorpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG 56 /r vorpd xmm1, xmm2, xmm3/m128 */
	I(0x56, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vorpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG 56 /r vorpd ymm1, ymm2, ymm3/m256 */
	I(0x56, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vorpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  56 /r vorpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x56, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vorpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  56 /r vorpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x56, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vorpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  56 /r vorpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x56, IF_MODRM,       "orps\t" OP_RM128_XMM OP_RXMM), /*    0f 56 /r orps xmm1, xmm2/m128 */
	I(0x56, IF_66|IF_MODRM, "orpd\t" OP_RM128_XMM OP_RXMM), /* 66 0f 56 /r orpd xmm1, xmm2/m128 */

	I(0x57, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vxorps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.0f.WIG 57 /r vxorps xmm1, xmm2, xmm3/m128 */
	I(0x57, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vxorps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.0f.WIG 57 /r vxorps ymm1, ymm2, ymm3/m256 */
	I(0x57, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vxorps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.0f.W0  57 /r vxorps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x57, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vxorps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.0f.W0  57 /r vxorps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x57, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vxorps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  57 /r vxorps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */

	I(0x57, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vxorpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG 57 /r vxorpd xmm1, xmm2, xmm3/m128 */
	I(0x57, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vxorpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG 57 /r vxorpd ymm1, ymm2, ymm3/m256 */
	I(0x57, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vxorpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  57 /r vxorpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x57, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vxorpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  57 /r vxorpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x57, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vxorpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  57 /r vxorpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x57, IF_MODRM,       "xorps\t" OP_RM128_XMM OP_RXMM), /*    0f 57 /r xorps xmm1, xmm2/m128 */
	I(0x57, IF_66|IF_MODRM, "xorpd\t" OP_RM128_XMM OP_RXMM), /* 66 0f 57 /r xorpd xmm1, xmm2/m128 */

	I(0x58, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vaddps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),            /*  VEX.128.0f.WIG 58 /r vaddps xmm1, xmm2, xmm3/m128 */
	I(0x58, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vaddps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),            /*  VEX.256.0f.WIG 58 /r vaddps ymm1, ymm2, ymm3/m256 */
	I(0x58, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vaddps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),       /* EVEX.128.0f.W0  58 /r vaddps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x58, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vaddps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),       /* EVEX.256.0f.W0  58 /r vaddps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x58, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vaddps\t" OP_ER OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  58 /r vaddps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{er} */

	I(0x58, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vaddss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),            /*  VEX.LIG.f3.0f.WIG 58 /r vaddss xmm1, xmm2, xmm3/m32 */
	I(0x58, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vaddss\t" OP_ER OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.f3.0f.W0  58 /r vaddss xmm1{k1}{z}, xmm2, xmm3/m32{er} */

	I(0x58, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vaddpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),            /*  VEX.128.66.0f.WIG 58 /r vaddpd xmm1, xmm2, xmm3/m128 */
	I(0x58, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vaddpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),            /*  VEX.256.66.0f.WIG 58 /r vaddpd ymm1, ymm2, ymm3/m256 */
	I(0x58, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vaddpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),       /* EVEX.128.66.0f.W1  58 /r vaddpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x58, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vaddpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),       /* EVEX.512.66.0f.W1  58 /r vaddpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x58, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vaddpd\t" OP_ER OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  58 /r vaddpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{er} */

	I(0x58, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vaddsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),            /*  VEX.LIG.f2.0f.WIG 58 /r vaddsd xmm1, xmm2, xmm3/m64 */
	I(0x58, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vaddsd\t" OP_ER OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.f2.0f.W1  58 /r vaddsd xmm1{k1}{z}, xmm2, xmm3/m64{er} */

	I(0x58, IF_MODRM,       "addps\t" OP_RM128_XMM OP_RXMM), /*    0f 58 /r addps xmm1, xmm2/m128 */
	I(0x58, IF_F3|IF_MODRM, "addss\t" OP_RM128_XMM OP_RXMM), /* f3 0f 58 /r addss xmm1, xmm2/m32 */
	I(0x58, IF_66|IF_MODRM, "addpd\t" OP_RM128_XMM OP_RXMM), /* 66 0f 58 /r addpd xmm1, xmm2/m128 */
	I(0x58, IF_F2|IF_MODRM, "addsd\t" OP_RM128_XMM OP_RXMM), /* f2 0f 58 /r addsd xmm1, xmm2/m64 */

	I(0x59, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmulps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),            /*  VEX.128.0f.WIG 59 /r vmulps xmm1, xmm2, xmm3/m128 */
	I(0x59, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmulps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),            /*  VEX.256.0f.WIG 59 /r vmulps ymm1, ymm2, ymm3/m256 */
	I(0x59, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vmulps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),       /* EVEX.128.0f.W0  59 /r vmulps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x59, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vmulps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),       /* EVEX.256.0f.W0  59 /r vmulps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x59, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vmulps\t" OP_ER OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  59 /r vmulps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{er} */

	I(0x59, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vmulss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),            /*  VEX.LIG.f3.0f.WIG 59 /r vmulss xmm1, xmm2, xmm3/m32 */
	I(0x59, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vmulss\t" OP_ER OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.f3.0f.W0  59 /r vmulss xmm1{k1}{z}, xmm2, xmm3/m32{er} */

	I(0x59, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmulpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),            /*  VEX.128.66.0f.WIG 59 /r vmulpd xmm1, xmm2, xmm3/m128 */
	I(0x59, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmulpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),            /*  VEX.256.66.0f.WIG 59 /r vmulpd ymm1, ymm2, ymm3/m256 */
	I(0x59, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vmulpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),       /* EVEX.128.66.0f.W1  59 /r vmulpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x59, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmulpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),       /* EVEX.512.66.0f.W1  59 /r vmulpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x59, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmulpd\t" OP_ER OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  59 /r vmulpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{er} */

	I(0x59, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vmulsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),            /*  VEX.LIG.f2.0f.WIG 59 /r vmulsd xmm1, xmm2, xmm3/m64 */
	I(0x59, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vmulsd\t" OP_ER OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.f2.0f.W1  59 /r vmulsd xmm1{k1}{z}, xmm2, xmm3/m64{er} */

	I(0x59, IF_MODRM,       "mulps\t" OP_RM128_XMM OP_RXMM), /*    0f 59 /r mulps xmm1, xmm2/m128 */
	I(0x59, IF_F3|IF_MODRM, "mulss\t" OP_RM128_XMM OP_RXMM), /* f3 0f 59 /r mulss xmm1, xmm2/m32 */
	I(0x59, IF_66|IF_MODRM, "mulpd\t" OP_RM128_XMM OP_RXMM), /* 66 0f 59 /r mulpd xmm1, xmm2/m128 */
	I(0x59, IF_F2|IF_MODRM, "mulsd\t" OP_RM128_XMM OP_RXMM), /* f2 0f 59 /r mulsd xmm1, xmm2/m64 */

	I(0x5a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VCVTPD2PS_XMM)),   /*  VEX.128.66.0f.WIG 5a /r vcvtpd2ps xmm1, xmm2/m128 */
	I(0x5a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VCVTPD2PS_YMM)),   /*  VEX.256.66.0f.WIG 5a /r vcvtpd2ps xmm1, ymm2/m256 */
	I(0x5a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VCVTPD2PS_XMM)),   /* EVEX.128.66.0f.W1  5a /r vcvtpd2ps xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0x5a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VCVTPD2PS_YMM)),   /* EVEX.512.66.0f.W1  5a /r vcvtpd2ps xmm1{k1}{z}, ymm2/m256/m64bcst */
	I(0x5a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VCVTPD2PS_ZMM)),   /* EVEX.512.66.0f.W1  5a /r vcvtpd2ps ymm1{k1}{z}, zmm2/m512/m64bcst{er} */

	I(0x5a, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vcvtsd2ss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /*  VEX.LIG.f2.0f.WIG 5a /r vcvtsd2ss xmm1, xmm2, xmm3/m64 */
	I(0x5a, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VCVTSD2SS)),               /* EVEX.LIG.f2.0f.W1  5a /r vcvtsd2ss xmm1{k1}{z}, xmm2, xmm3/m64{er} */

	I(0x5a, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VCVTPS2PD_XMM)), /*  VEX.128.0f.WIG 5a /r vcvtps2pd xmm1, xmm2/m64 */
	I(0x5a, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VCVTPS2PD_YMM)), /*  VEX.256.0f.WIG 5a /r vcvtps2pd ymm1, xmm2/m128 */
	I(0x5a, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VCVTPS2PD_XMM)), /* EVEX.128.0f.W0  5a /r vcvtps2pd xmm1{k1}{z}, xmm2/m64/m32bcst */
	I(0x5a, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VCVTPS2PD_YMM)), /* EVEX.256.0f.W0  5a /r vcvtps2pd ymm1{k1}{z}, xmm2/m128/m32bcst */
	I(0x5a, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VCVTPS2PD_ZMM)), /* EVEX.512.0f.W0  5a /r vcvtps2pd zmm1{k1}{z}, ymm2/m256/m32bcst{sae} */

	I(0x5a, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vcvtss2sd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /*  VEX.LIG.f3.0f.WIG 5a /r vcvtss2sd xmm1, xmm2, xmm3/m32 */
	I(0x5a, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VCVTSS2SD)),               /* EVEX.LIG.f3.0f.W0  5a /r vcvtss2sd xmm1{k1}{z}, xmm2, xmm3/m32{sae} */

	I(0x5a, IF_MODRM,       "cvtps2pd\t" OP_RM128_XMM OP_RXMM), /*    0f 5a /r cvtps2pd xmm1, xmm2/m64 */
	I(0x5a, IF_66|IF_MODRM, "cvtpd2ps\t" OP_RM128_XMM OP_RXMM), /* 66 0f 5a /r cvtpd2ps xmm1, xmm2/m128 */
	I(0x5a, IF_F2|IF_MODRM, "cvtsd2ss\t" OP_RM128_XMM OP_RXMM), /* f2 0f 5a /r cvtsd2ss xmm1, xmm2/m64 */
	I(0x5a, IF_F3|IF_MODRM, "cvtss2sd\t" OP_RM128_XMM OP_RXMM), /* f3 0f 5a /r cvtss2sd xmm1, xmm2/m32 */

	I(0x5b, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VCVTDQ2PS_XMM)), /*  VEX.128.0f.WIG 5b /r vcvtdq2ps xmm1, xmm2/m128 */
	I(0x5b, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VCVTDQ2PS_YMM)), /*  VEX.256.0f.WIG 5b /r vcvtdq2ps ymm1, ymm2/m256 */
	I(0x5b, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VCVTDQ2PS_XMM)), /* EVEX.128.0f.W0  5b /r vcvtdq2ps xmm1{k1}{z}, xmm2/m128/m32bcst */
	I(0x5b, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VCVTDQ2PS_YMM)), /* EVEX.256.0f.W0  5b /r vcvtdq2ps ymm1{k1}{z}, ymm2/m256/m32bcst */
	I(0x5b, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VCVTDQ2PS_ZMM)), /* EVEX.512.0f.W0  5b /r vcvtdq2ps zmm1{k1}{z}, zmm2/m512/m32bcst{er} */

	I(0x5b, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VCVTQQ2PS_XMM)), /* EVEX.128.0f.W1 5b /r vcvtqq2ps xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0x5b, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VCVTQQ2PS_YMM)), /* EVEX.256.0f.W1 5b /r vcvtqq2ps xmm1{k1}{z}, ymm2/m256/m64bcst */
	I(0x5b, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VCVTQQ2PS_ZMM)), /* EVEX.512.0f.W1 5b /r vcvtqq2ps ymm1{k1}{z}, zmm2/m512/m64bcst{er} */

	I(0x5b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VCVTPS2DQ_XMM)), /*  VEX.128.66.0f.WIG 5b /r vcvtps2dq xmm1, xmm2/m128 */
	I(0x5b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VCVTPS2DQ_YMM)), /*  VEX.256.66.0f.WIG 5b /r vcvtps2dq ymm1, ymm2/m256 */
	I(0x5b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VCVTPS2DQ_XMM)), /* EVEX.128.66.0f.W0  5b /r vcvtps2dq xmm1{k1}{z}, xmm2/m128/m32bcst */
	I(0x5b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VCVTPS2DQ_YMM)), /* EVEX.256.66.0f.W0  5b /r vcvtps2dq ymm1{k1}{z}, ymm2/m256/m32bcst */
	I(0x5b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VCVTPS2DQ_ZMM)), /* EVEX.512.66.0f.W0  5b /r vcvtps2dq zmm1{k1}{z}, zmm2/m512/m32bcst{er} */

	I(0x5b, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VCVTTPS2DQ_XMM)), /*  VEX.128.f3.0f.WIG 5b /r vcvttps2dq xmm1, xmm2/m128 */
	I(0x5b, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VCVTTPS2DQ_YMM)), /*  VEX.256.f3.0f.WIG 5b /r vcvttps2dq ymm1, ymm2/m256 */
	I(0x5b, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VCVTTPS2DQ_XMM)), /* EVEX.128.f3.0f.W0  5b /r vcvttps2dq xmm1{k1}{z}, xmm2/m128/m32bcst */
	I(0x5b, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VCVTTPS2DQ_YMM)), /* EVEX.256.f3.0f.W0  5b /r vcvttps2dq ymm1{k1}{z}, ymm2/m256/m32bcst */
	I(0x5b, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VCVTTPS2DQ_ZMM)), /* EVEX.512.f3.0f.W0  5b /r vcvttps2dq zmm1{k1}{z}, zmm2/m512/m32bcst{sae} */

	I(0x5b, IF_MODRM,       "cvtdq2ps\t" OP_RM128_XMM OP_RXMM),  /*    0f 5b /r cvtdq2ps xmm1, xmm2/m128 */
	I(0x5b, IF_66|IF_MODRM, "cvtps2dq\t" OP_RM128_XMM OP_RXMM),  /* 66 0f 5b /r cvtps2dq xmm1, xmm2/m128 */
	I(0x5b, IF_F3|IF_MODRM, "cvttps2dq\t" OP_RM128_XMM OP_RXMM), /* f3 0f 5b /r cvttps2dq xmm1, xmm2/m128 */

	I(0x5c, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vsubps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),            /*  VEX.128.0f.WIG 5c /r vsubps xmm1, xmm2, xmm3/m128 */
	I(0x5c, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vsubps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),            /*  VEX.256.0f.WIG 5c /r vsubps ymm1, ymm2, ymm3/m256 */
	I(0x5c, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vsubps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),       /* EVEX.128.0f.W0  5c /r vsubps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x5c, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vsubps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),       /* EVEX.256.0f.W0  5c /r vsubps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x5c, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vsubps\t" OP_ER OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  5c /r vsubps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{er} */

	I(0x5c, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vsubss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),            /*  VEX.LIG.f3.0f.WIG 5c /r vsubss xmm1, xmm2, xmm3/m32 */
	I(0x5c, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vsubss\t" OP_ER OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.f3.0f.W0  5c /r vsubss xmm1{k1}{z}, xmm2, xmm3/m32{er} */

	I(0x5c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vsubpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),            /*  VEX.128.66.0f.WIG 5c /r vsubpd xmm1, xmm2, xmm3/m128 */
	I(0x5c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vsubpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),            /*  VEX.256.66.0f.WIG 5c /r vsubpd ymm1, ymm2, ymm3/m256 */
	I(0x5c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vsubpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),       /* EVEX.128.66.0f.W1  5c /r vsubpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x5c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vsubpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),       /* EVEX.512.66.0f.W1  5c /r vsubpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x5c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vsubpd\t" OP_ER OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  5c /r vsubpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{er} */

	I(0x5c, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vsubsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),            /*  VEX.LIG.f2.0f.WIG 5c /r vsubsd xmm1, xmm2, xmm3/m64 */
	I(0x5c, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vsubsd\t" OP_ER OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.f2.0f.W1  5c /r vsubsd xmm1{k1}{z}, xmm2, xmm3/m64{er} */

	I(0x5c, IF_MODRM,       "subps\t" OP_RM128_XMM OP_RXMM), /*    0f 5c /r subps xmm1, xmm2/m128 */
	I(0x5c, IF_F3|IF_MODRM, "subss\t" OP_RM128_XMM OP_RXMM), /* f3 0f 5c /r subss xmm1, xmm2/m32 */
	I(0x5c, IF_66|IF_MODRM, "subpd\t" OP_RM128_XMM OP_RXMM), /* 66 0f 5c /r subpd xmm1, xmm2/m128 */
	I(0x5c, IF_F2|IF_MODRM, "subsd\t" OP_RM128_XMM OP_RXMM), /* f2 0f 5c /r subsd xmm1, xmm2/m64 */

	I(0x5d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vminpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.128.66.0f.WIG 5d /r vminpd xmm1, xmm2, xmm3/m128 */
	I(0x5d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vminpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),             /*  VEX.256.66.0f.WIG 5d /r vminpd ymm1, ymm2, ymm3/m256 */
	I(0x5d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vminpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0f.W1  5d /r vminpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x5d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vminpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.512.66.0f.W1  5d /r vminpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x5d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vminpd\t" OP_SAE OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  5d /r vminpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{sae} */

	I(0x5d, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vminsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.LIG.f2.0f.WIG 5d /r vminsd xmm1, xmm2, xmm3/m64 */
	I(0x5d, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vminsd\t" OP_SAE OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.f2.0f.W1  5d /r vminsd xmm1{k1}{z}, xmm2, xmm3/m64{sae} */

	I(0x5d, IF_66|IF_MODRM, "minpd\t" OP_RM128_XMM OP_RXMM), /* 66 0f 5d /r minpd xmm1, xmm2/m128 */
	I(0x5d, IF_F2|IF_MODRM, "minsd\t" OP_RM128_XMM OP_RXMM), /* f2 0f 5d /r minsd xmm1, xmm2/m64 */

	I(0x5d, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vminps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.128.0f.WIG 5d /r vminps xmm1, xmm2, xmm3/m128 */
	I(0x5d, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vminps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),             /*  VEX.256.0f.WIG 5d /r vminps ymm1, ymm2, ymm3/m256 */
	I(0x5d, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vminps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.0f.W0  5d /r vminps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x5d, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vminps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.0f.W0  5d /r vminps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x5d, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vminps\t" OP_SAE OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  5d /r vminps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{sae} */

	I(0x5d, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vminss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.LIG.f3.0f.WIG 5d /r vminss xmm1, xmm2, xmm3/m32 */
	I(0x5d, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vminss\t" OP_SAE OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.f3.0f.W0  5d /r vminss xmm1{k1}{z}, xmm2, xmm3/m32{sae} */

	I(0x5d, IF_MODRM,       "minps\t" OP_RM128_XMM OP_RXMM), /*    0f 5d /r minps xmm1, xmm2/m128 */
	I(0x5d, IF_F3|IF_MODRM, "minss\t" OP_RM128_XMM OP_RXMM), /* f3 0f 5d /r minss xmm1, xmm2/m32 */

	I(0x5e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vdivpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),            /*  VEX.128.66.0f.WIG 5e /r vdivpd xmm1, xmm2, xmm3/m128 */
	I(0x5e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vdivpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),            /*  VEX.256.66.0f.WIG 5e /r vdivpd ymm1, ymm2, ymm3/m256 */
	I(0x5e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vdivpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),       /* EVEX.128.66.0f.W1  5e /r vdivpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x5e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vdivpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),       /* EVEX.512.66.0f.W1  5e /r vdivpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x5e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vdivpd\t" OP_ER OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  5e /r vdivpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{er} */

	I(0x5e, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vdivsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),            /*  VEX.LIG.f2.0f.WIG 5e /r vdivsd xmm1, xmm2, xmm3/m64 */
	I(0x5e, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vdivsd\t" OP_ER OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.f2.0f.W1  5e /r vdivsd xmm1{k1}{z}, xmm2, xmm3/m64{er} */

	I(0x5e, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vdivps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),            /*  VEX.128.0f.WIG 5e /r vdivps xmm1, xmm2, xmm3/m128 */
	I(0x5e, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vdivps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),            /*  VEX.256.0f.WIG 5e /r vdivps ymm1, ymm2, ymm3/m256 */
	I(0x5e, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vdivps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),       /* EVEX.128.0f.W0  5e /r vdivps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x5e, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vdivps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),       /* EVEX.256.0f.W0  5e /r vdivps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x5e, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vdivps\t" OP_ER OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  5e /r vdivps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{er} */

	I(0x5e, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vdivss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),            /*  VEX.LIG.f3.0f.WIG 5e /r vdivss xmm1, xmm2, xmm3/m32 */
	I(0x5e, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vdivss\t" OP_ER OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.f3.0f.W0  5e /r vdivss xmm1{k1}{z}, xmm2, xmm3/m32{er} */

	I(0x5e, IF_MODRM,       "divps\t" OP_RM128_XMM OP_RXMM), /*    0f 5e /r divps xmm1, xmm2/m128 */
	I(0x5e, IF_66|IF_MODRM, "divpd\t" OP_RM128_XMM OP_RXMM), /* 66 0f 5e /r divpd xmm1, xmm2/m128 */
	I(0x5e, IF_F2|IF_MODRM, "divsd\t" OP_RM128_XMM OP_RXMM), /* f2 0f 5e /r divsd xmm1, xmm2/m64 */
	I(0x5e, IF_F3|IF_MODRM, "divss\t" OP_RM128_XMM OP_RXMM), /* f3 0f 5e /r divss xmm1, xmm2/m32 */

	I(0x5f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmaxpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.128.66.0f.WIG 5f /r vmaxpd xmm1, xmm2, xmm3/m128 */
	I(0x5f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmaxpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),             /*  VEX.256.66.0f.WIG 5f /r vmaxpd ymm1, ymm2, ymm3/m256 */
	I(0x5f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vmaxpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.66.0f.W1  5f /r vmaxpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x5f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmaxpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.512.66.0f.W1  5f /r vmaxpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x5f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vmaxpd\t" OP_SAE OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  5f /r vmaxpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{sae} */

	I(0x5f, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vmaxsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.LIG.f2.0f.WIG 5f /r vmaxsd xmm1, xmm2, xmm3/m64 */
	I(0x5f, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vmaxsd\t" OP_SAE OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.f2.0f.W1  5f /r vmaxsd xmm1{k1}{z}, xmm2, xmm3/m64{sae} */

	I(0x5f, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmaxps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.128.0f.WIG 5f /r vmaxps xmm1, xmm2, xmm3/m128 */
	I(0x5f, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmaxps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),             /*  VEX.256.0f.WIG 5f /r vmaxps ymm1, ymm2, ymm3/m256 */
	I(0x5f, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vmaxps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),        /* EVEX.128.0f.W0  5f /r vmaxps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x5f, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vmaxps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),        /* EVEX.256.0f.W0  5f /r vmaxps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x5f, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vmaxps\t" OP_SAE OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  5f /r vmaxps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{sae} */

	I(0x5f, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vmaxss\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),             /*  VEX.LIG.f3.0f.WIG 5f /r vmaxss xmm1, xmm2, xmm3/m32 */
	I(0x5f, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 0) "vmaxss\t" OP_SAE OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.f3.0f.W0  5f /r vmaxss xmm1{k1}{z}, xmm2, xmm3/m32{sae} */

	I(0x5f, IF_MODRM,       "maxps\t" OP_RM128_XMM OP_RXMM), /*    0f 5f /r maxps xmm1, xmm2/m128 */
	I(0x5f, IF_66|IF_MODRM, "maxpd\t" OP_RM128_XMM OP_RXMM), /* 66 0f 5f /r maxpd xmm1, xmm2/m128 */
	I(0x5f, IF_F2|IF_MODRM, "maxsd\t" OP_RM128_XMM OP_RXMM), /* f2 0f 5f /r maxsd xmm1, xmm2/m64 */
	I(0x5f, IF_F3|IF_MODRM, "maxss\t" OP_RM128_XMM OP_RXMM), /* f3 0f 5f /r maxss xmm1, xmm2/m32 */

	I(0x60, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPUNPCKLBW_XMM)), /* EVEX.128.66.0f.WIG 60 /r vpunpcklbw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x60, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPUNPCKLBW_YMM)), /* EVEX.256.66.0f.WIG 60 /r vpunpcklbw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x60, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPUNPCKLBW_ZMM)), /* EVEX.512.66.0f.WIG 60 /r vpunpcklbw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x60, IF_MODRM,              "punpcklbw\t" OP_RM64_MM OP_RMM),                        /*                 0f 60 /r punpcklbw mm, mm/m32 */
	I(0x60, IF_66|IF_MODRM,        "punpcklbw\t" OP_RM128_XMM OP_RXMM),                     /*              66 0f 60 /r punpcklbw xmm1, xmm2/m128 */

	I(0x61, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPUNPCKLWD_XMM)), /* EVEX.128.66.0f.WIG 61 /r vpunpcklwd xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x61, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPUNPCKLWD_YMM)), /* EVEX.256.66.0f.WIG 61 /r vpunpcklwd ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x61, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPUNPCKLWD_ZMM)), /* EVEX.512.66.0f.WIG 61 /r vpunpcklwd zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x61, IF_MODRM,              "punpcklwd\t" OP_RM64_MM OP_RMM),                        /*                 0f 61 /r punpcklwd mm, mm/m32 */
	I(0x61, IF_66|IF_MODRM,        "punpcklwd\t" OP_RM128_XMM OP_RXMM),                     /*              66 0f 61 /r punpcklwd xmm1, xmm2/m128 */

	I(0x62, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VPUNPCKLDQ_XMM)), /*  VEX.128.66.0f.WIG 62 /r vpunpckldq xmm1, xmm2, xmm3/m128 */
	I(0x62, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VPUNPCKLDQ_YMM)), /*  VEX.256.66.0f.WIG 62 /r vpunpckldq ymm1, ymm2, ymm3/m256 */
	I(0x62, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPUNPCKLDQ_XMM)), /* EVEX.128.66.0f.W0  62 /r vpunpckldq xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x62, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPUNPCKLDQ_YMM)), /* EVEX.256.66.0f.W0  62 /r vpunpckldq ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x62, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPUNPCKLDQ_ZMM)), /* EVEX.512.66.0f.W0  62 /r vpunpckldq zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x62, IF_MODRM,              "punpckldq\t" OP_RM64_MM OP_RMM),                        /*                 0f 62 /r punpckldq mm, mm/m32 */
	I(0x62, IF_66|IF_MODRM,        "punpckldq\t" OP_RM128_XMM OP_RXMM),                     /*              66 0f 62 /r punpckldq xmm1, xmm2/m128 */

	I(0x63, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpacksswb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG 63 /r vpacksswb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x63, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpacksswb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG 63 /r vpacksswb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x63, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpacksswb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG 63 /r vpacksswb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x63, IF_MODRM,              "packsswb\t" OP_RM64_MM OP_RMM),                                           /*                 0f 63 /r packsswb mm1, mm2/m64 */
	I(0x63, IF_66|IF_MODRM,        "packsswb\t" OP_RM128_XMM OP_RXMM_MASK),                                   /*              66 0f 63 /r packsswb xmm1, xmm2/m128 */

	I(0x64, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpcmpgtb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x64, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpcmpgtb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x64, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpcmpgtb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0x64, IF_MODRM,              "pcmpgtb\t" OP_RMM OP_RM64_MM),
	I(0x64, IF_66|IF_MODRM,        "pcmpgtb\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0x65, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpcmpgtw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x65, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpcmpgtw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x65, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpcmpgtw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0x65, IF_MODRM,              "pcmpgtw\t" OP_RMM OP_RM64_MM),
	I(0x65, IF_66|IF_MODRM,        "pcmpgtw\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0x66, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpcmpgtd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x66, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpcmpgtd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x66, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpcmpgtd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x66, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpcmpgtd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x66, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpcmpgtd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0x66, IF_MODRM,              "pcmpgtd\t" OP_RMM OP_RM64_MM),
	I(0x66, IF_66|IF_MODRM,        "pcmpgtd\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0x67, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpackuswb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x67, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpackuswb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x67, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpackuswb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0x67, IF_MODRM,              "packuswb\t" OP_RM64_MM OP_RMM),
	I(0x67, IF_66|IF_MODRM,        "packuswb\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0x68, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPUNPCKHBW_XMM)), /* EVEX.128.66.0f.WIG 68 /r vpunpckhbw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x68, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPUNPCKHBW_YMM)), /* EVEX.256.66.0f.WIG 68 /r vpunpckhbw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x68, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPUNPCKHBW_ZMM)), /* EVEX.512.66.0f.WIG 68 /r vpunpckhbw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x68, IF_MODRM,              "punpckhbw\t" OP_RM64_MM OP_RMM),                        /*                 0f 68 /r punpckhbw mm, mm/m64 */
	I(0x68, IF_66|IF_MODRM,        "punpckhbw\t" OP_RM128_XMM OP_RXMM),                     /*              66 0f 68 /r punpckhbw xmm1, xmm2/m128 */

	I(0x69, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPUNPCKHWD_XMM)), /* EVEX.128.66.0f.WIG 69 /r vpunpckhwd xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x69, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPUNPCKHWD_YMM)), /* EVEX.256.66.0f.WIG 69 /r vpunpckhwd ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x69, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPUNPCKHWD_ZMM)), /* EVEX.512.66.0f.WIG 69 /r vpunpckhwd zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x69, IF_MODRM,              "punpckhwd\t" OP_RM64_MM OP_RMM),                        /*                 0f 69 /r punpckhwd mm, mm/m64 */
	I(0x69, IF_66|IF_MODRM,        "punpckhwd\t" OP_RM128_XMM OP_RXMM),                     /*              66 0f 69 /r punpckhwd xmm1, xmm2/m128 */

	I(0x6a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VPUNPCKHDQ_XMM)), /*  VEX.128.66.0f.WIG 6a /r vpunpckhdq xmm1, xmm2, xmm3/m128 */
	I(0x6a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VPUNPCKHDQ_YMM)), /*  VEX.256.66.0f.WIG 6a /r vpunpckhdq ymm1, ymm2, ymm3/m256 */
	I(0x6a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPUNPCKHDQ_XMM)), /* EVEX.128.66.0f.W0  6a /r vpunpckhdq xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x6a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPUNPCKHDQ_YMM)), /* EVEX.256.66.0f.W0  6a /r vpunpckhdq ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x6a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPUNPCKHDQ_ZMM)), /* EVEX.512.66.0f.W0  6a /r vpunpckhdq zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x6a, IF_MODRM,              "punpckhdq\t" OP_RM64_MM OP_RMM),                        /*                 0f 6a /r punpckhdq mm, mm/m64 */
	I(0x6a, IF_66|IF_MODRM,        "punpckhdq\t" OP_RM128_XMM OP_RXMM),                     /*              66 0f 6a /r punpckhdq xmm1, xmm2/m128 */

	I(0x6b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpackssdw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x6b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpackssdw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x6b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpackssdw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0x6b, IF_MODRM,              "packssdw\t" OP_RM64_MM OP_RMM),
	I(0x6b, IF_66|IF_MODRM,        "packssdw\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0x6c, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VPUNPCKLQDQ_XMM)), /*  VEX.128.66.0f.WIG 6c /r vpunpcklqdq xmm1, xmm2, xmm3/m128 */
	I(0x6c, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VPUNPCKLQDQ_YMM)), /*  VEX.256.66.0f.WIG 6c /r vpunpcklqdq ymm1, ymm2, ymm3/m256 */
	I(0x6c, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPUNPCKLQDQ_XMM)), /* EVEX.128.66.0f.W1  6c /r vpunpcklqdq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x6c, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPUNPCKLQDQ_YMM)), /* EVEX.512.66.0f.W1  6c /r vpunpcklqdq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x6c, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPUNPCKLQDQ_ZMM)), /* EVEX.512.66.0f.W1  6c /r vpunpcklqdq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x6c, IF_66|IF_MODRM,        LONGREPR(LO_PUNPCKLQDQ_XMM)),                             /*              66 0f 6c /r punpcklqdq xmm1, xmm2/m128 */

	I(0x6d, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VPUNPCKHQDQ_XMM)), /*  VEX.128.66.0f.WIG 6d /r vpunpckhqdq xmm1, xmm2, xmm3/m128 */
	I(0x6d, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VPUNPCKHQDQ_YMM)), /*  VEX.256.66.0f.WIG 6d /r vpunpckhqdq ymm1, ymm2, ymm3/m256 */
	I(0x6d, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPUNPCKHQDQ_XMM)), /* EVEX.128.66.0f.W1  6d /r vpunpckhqdq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x6d, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPUNPCKHQDQ_YMM)), /* EVEX.512.66.0f.W1  6d /r vpunpckhqdq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x6d, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPUNPCKHQDQ_ZMM)), /* EVEX.512.66.0f.W1  6d /r vpunpckhqdq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x6d, IF_66|IF_MODRM,        LONGREPR(LO_PUNPCKHQDQ_XMM)),                             /*              66 0f 6d /r punpckhqdq xmm1, xmm2/m128 */

	I(0x6e, IF_66|IF_VEX|IF_MODRM,  OP_VEX_B0(0, 0, 0, 0) "vmovd\t" OP_RM32 OP_RXMM), /* EVEX.128.66.0f.W0 6e /r vmovd xmm1, r/m32 */
	I(0x6e, IF_66|IF_VEX|IF_MODRM,  OP_VEX_B0(0, 0, 1, 0) "vmovq\t" OP_RM64 OP_RXMM), /* EVEX.128.66.0f.W1 6e /r vmovq xmm1, r/m64 */
	I(0x6e, IF_MODRM,               "movd\t" OP_RM32 OP_RMM),                         /*                0f 6e /r movd mm, r/m32 */
	I(0x6e, IF_MODRM|IF_REXW,       "movq\t" OP_RM64 OP_RMM),                         /*        rex.w + 0f 6e /r movq mm, r/m64 */
	I(0x6e, IF_66|IF_MODRM,         "movd\t" OP_RM32 OP_RXMM),                        /*     66         0f 6e /r movd xmm, r/m32 */
	I(0x6e, IF_66|IF_MODRM|IF_REXW, "movq\t" OP_RM64 OP_RXMM),                        /*     66 rex.w + 0f 6e /r movq xmm, r/m64 */

	I(0x6f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovdqa\t" OP_RM128_XMM OP_RXMM), /*  VEX.128.66.0f.WIG 6f /r vmovdqa xmm1, xmm2/m128 */
	I(0x6f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovdqa\t" OP_RM256_YMM OP_RYMM), /*  VEX.256.66.0f.WIG 6f /r vmovdqa ymm1, ymm2/m256 */
	I(0x6f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VMOVDQA32_XMM)),  /* EVEX.128.66.0f.W0  6f /r vmovdqa32 xmm1{k1}{z}, xmm2/m128 */
	I(0x6f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VMOVDQA32_YMM)),  /* EVEX.256.66.0f.W0  6f /r vmovdqa32 ymm1{k1}{z}, ymm2/m256 */
	I(0x6f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VMOVDQA32_ZMM)),  /* EVEX.512.66.0f.W0  6f /r vmovdqa32 zmm1{k1}{z}, zmm2/m512 */
	I(0x6f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VMOVDQA64_XMM)),  /* EVEX.128.66.0f.W1  6f /r vmovdqa64 xmm1{k1}{z}, xmm2/m128 */
	I(0x6f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VMOVDQA64_YMM)),  /* EVEX.512.66.0f.W1  6f /r vmovdqa64 ymm1{k1}{z}, ymm2/m256 */
	I(0x6f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VMOVDQA64_ZMM)),  /* EVEX.512.66.0f.W1  6f /r vmovdqa64 zmm1{k1}{z}, zmm2/m512 */
	I(0x6f, IF_66|IF_MODRM,        "movdqa\t" OP_RM128_XMM OP_RXMM),                        /*              66 0f 6f /r movdqa xmm1, xmm2/m128 */

	I(0x6f, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovdqu\t" OP_RM128_XMM OP_RXMM),       /*  VEX.128.f3.0f.WIG 6f /r vmovdqu xmm1, xmm2/m128 */
	I(0x6f, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovdqu\t" OP_RM256_YMM OP_RYMM),       /*  VEX.256.f3.0f.WIG 6f /r vmovdqu ymm1, ymm2/m256 */
	I(0x6f, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vmovdqu8\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.f2.0f.W0  6f /r vmovdqu8 xmm1{k1}{z}, xmm2/m128 */
	I(0x6f, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vmovdqu8\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.f2.0f.W0  6f /r vmovdqu8 ymm1{k1}{z}, ymm2/m256 */
	I(0x6f, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vmovdqu8\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.f2.0f.W0  6f /r vmovdqu8 zmm1{k1}{z}, zmm2/m512 */
	I(0x6f, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VMOVDQU16_XMM)),        /* EVEX.128.f2.0f.W1  6f /r vmovdqu16 xmm1{k1}{z}, xmm2/m128 */
	I(0x6f, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VMOVDQU16_YMM)),        /* EVEX.256.f2.0f.W1  6f /r vmovdqu16 ymm1{k1}{z}, ymm2/m256 */
	I(0x6f, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VMOVDQU16_ZMM)),        /* EVEX.512.f2.0f.W1  6f /r vmovdqu16 zmm1{k1}{z}, zmm2/m512 */
	I(0x6f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VMOVDQU32_XMM)),        /* EVEX.128.f3.0f.W0  6f /r vmovdqu32 xmm1{k1}{z}, xmm2/m128 */
	I(0x6f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VMOVDQU32_YMM)),        /* EVEX.256.f3.0f.W0  6f /r vmovdqu32 ymm1{k1}{z}, ymm2/m256 */
	I(0x6f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VMOVDQU32_ZMM)),        /* EVEX.512.f3.0f.W0  6f /r vmovdqu32 zmm1{k1}{z}, zmm2/m512 */
	I(0x6f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VMOVDQU64_XMM)),        /* EVEX.128.f3.0f.W1  6f /r vmovdqu64 xmm1{k1}{z}, xmm2/m128 */
	I(0x6f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VMOVDQU64_YMM)),        /* EVEX.256.f3.0f.W1  6f /r vmovdqu64 ymm1{k1}{z}, ymm2/m256 */
	I(0x6f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VMOVDQU64_ZMM)),        /* EVEX.512.f3.0f.W1  6f /r vmovdqu64 zmm1{k1}{z}, zmm2/m512 */
	I(0x6f, IF_F3|IF_MODRM,        "movdqu\t" OP_RM128_XMM OP_RXMM),                              /*              f3 0f 6f /r movdqu xmm1, xmm2/m128 */

	I(0x70, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpshufd\t" OP_U8 OP_RM128_XMM OP_RXMM),      /*  VEX.128.66.0f.WIG 70 /r ib vpshufd xmm1, xmm2/m128, imm8 */
	I(0x70, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpshufd\t" OP_U8 OP_RM256_YMM OP_RYMM),      /*  VEX.256.66.0f.WIG 70 /r ib vpshufd ymm1, ymm2/m256, imm8 */
	I(0x70, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpshufd\t" OP_U8 OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f.W0  70 /r ib vpshufd xmm1{k1}{z}, xmm2/m128/m32bcst, imm8 */
	I(0x70, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpshufd\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f.W0  70 /r ib vpshufd ymm1{k1}{z}, ymm2/m256/m32bcst, imm8 */
	I(0x70, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpshufd\t" OP_U8 OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f.W0  70 /r ib vpshufd zmm1{k1}{z}, zmm2/m512/m32bcst, imm8 */
	I(0x70, IF_66|IF_MODRM,                              "pshufd\t" OP_U8 OP_RM128_XMM OP_RXMM),       /*              66 0f 70 /r ib pshufd xmm1, xmm2/m128, imm8 */

	I(0x70, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPSHUFHW_XMM)), /* EVEX.128.f3.0f.WIG 70 /r ib vpshufhw xmm1{k1}{z}, xmm2/m128, imm8 */
	I(0x70, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPSHUFHW_YMM)), /* EVEX.256.f3.0f.WIG 70 /r ib vpshufhw ymm1{k1}{z}, ymm2/m256, imm8 */
	I(0x70, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPSHUFHW_ZMM)), /* EVEX.512.f3.0f.WIG 70 /r ib vpshufhw zmm1{k1}{z}, zmm2/m512, imm8 */
	I(0x70, IF_F3|IF_MODRM,        "pshufhw\t" OP_U8 OP_RM128_XMM OP_RXMM),               /*              f3 0f 70 /r ib pshufhw xmm1, xmm2/m128, imm8 */

	I(0x70, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPSHUFLW_XMM)), /* EVEX.128.f2.0f.WIG 70 /r ib vpshuflw xmm1{k1}{z}, xmm2/m128, imm8 */
	I(0x70, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPSHUFLW_YMM)), /* EVEX.256.f2.0f.WIG 70 /r ib vpshuflw ymm1{k1}{z}, ymm2/m256, imm8 */
	I(0x70, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPSHUFLW_ZMM)), /* EVEX.512.f2.0f.WIG 70 /r ib vpshuflw zmm1{k1}{z}, zmm2/m512, imm8 */
	I(0x70, IF_F2|IF_MODRM,        "pshuflw\t" OP_U8 OP_RM128_XMM OP_RXMM),               /*              f2 0f 70 /r ib pshuflw xmm1, xmm2/m128, imm8 */

	I(0x70, IF_MODRM, "pshufw\t" OP_U8 OP_RM64_MM OP_RMM),

	I(0x71, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 1, 0, 0) "vpsrlw\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK), /* EVEX.128.66.0f.WIG 71 /2 ib vpsrlw xmm1{k1}{z}, xmm2/m128, imm8 */
	I(0x71, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 1, 0, 1) "vpsrlw\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK), /* EVEX.256.66.0f.WIG 71 /2 ib vpsrlw ymm1{k1}{z}, ymm2/m256, imm8 */
	I(0x71, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 1, 0, 2) "vpsrlw\t" OP_U8 OP_RM512_ZMM OP_VRZMM_MASK), /* EVEX.512.66.0f.WIG 71 /2 ib vpsrlw zmm1{k1}{z}, zmm2/m512, imm8 */
	I(0x71, IF_MODRM|IF_REG2,                                    "psrlw\t" OP_U8 OP_RM64_MM),                  /*                 0f 71 /2 ib psrlw mm, imm8 */
	I(0x71, IF_66|IF_MODRM|IF_REG2,                              "psrlw\t" OP_U8 OP_RM128_XMM),                /*              66 0f 71 /2 ib psrlw xmm1, imm8 */

	I(0x71, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(0, 1, 0, 0) "vpsraw\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK), /* EVEX.128.66.0f.WIG 71 /4 ib vpsraw xmm1{k1}{z}, xmm2/m128, imm8 */
	I(0x71, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(0, 1, 0, 1) "vpsraw\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK), /* EVEX.256.66.0f.WIG 71 /4 ib vpsraw ymm1{k1}{z}, ymm2/m256, imm8 */
	I(0x71, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(0, 1, 0, 2) "vpsraw\t" OP_U8 OP_RM512_ZMM OP_VRZMM_MASK), /* EVEX.512.66.0f.WIG 71 /4 ib vpsraw zmm1{k1}{z}, zmm2/m512, imm8 */
	I(0x71, IF_MODRM|IF_REG4,                                    "psraw\t" OP_U8 OP_RM64_MM),                  /*                 0f 71 /4 ib psraw mm, imm8 */
	I(0x71, IF_66|IF_MODRM|IF_REG4,                              "psraw\t" OP_U8 OP_RM128_XMM),                /*              66 0f 71 /4 ib psraw xmm1, imm8 */

	I(0x71, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(0, 1, 0, 0) "vpsllw\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK),
	I(0x71, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(0, 1, 0, 1) "vpsllw\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK),
	I(0x71, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(0, 1, 0, 2) "vpsllw\t" OP_U8 OP_RM512_ZMM OP_VRZMM_MASK),
	I(0x71, IF_MODRM|IF_RMR|IF_REG6,       "psllw\t" OP_U8 OP_RM64_MM),
	I(0x71, IF_66|IF_MODRM|IF_RMR|IF_REG6, "psllw\t" OP_U8 OP_RM128_XMM),

	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG0, OP_VEX_B0(0, 0, 0, 0) "vprord\t" OP_U8 OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f.W0 72 /0 ib vprord xmm1{k1}{z}, xmm2/m128/m32bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG0, OP_VEX_B0(0, 0, 1, 0) "vprorq\t" OP_U8 OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f.W1 72 /0 ib vprorq xmm1{k1}{z}, xmm2/m128/m64bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG0, OP_VEX_B0(0, 0, 0, 1) "vprord\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f.W0 72 /0 ib vprord ymm1{k1}{z}, ymm2/m256/m32bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG0, OP_VEX_B0(0, 0, 1, 1) "vprorq\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f.W1 72 /0 ib vprorq ymm1{k1}{z}, ymm2/m256/m64bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG0, OP_VEX_B0(0, 0, 0, 2) "vprord\t" OP_U8 OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f.W0 72 /0 ib vprord zmm1{k1}{z}, zmm2/m512/m32bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG0, OP_VEX_B0(0, 0, 1, 2) "vprorq\t" OP_U8 OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f.W1 72 /0 ib vprorq zmm1{k1}{z}, zmm2/m512/m64bcst, imm8 */

	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 0, 0) "vprold\t" OP_U8 OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f.W0 72 /1 ib vprold xmm1{k1}{z}, xmm2/m128/m32bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 1, 0) "vprolq\t" OP_U8 OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f.W1 72 /1 ib vprolq xmm1{k1}{z}, xmm2/m128/m64bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 0, 1) "vprold\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f.W0 72 /1 ib vprold ymm1{k1}{z}, ymm2/m256/m32bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 1, 1) "vprolq\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f.W1 72 /1 ib vprolq ymm1{k1}{z}, ymm2/m256/m64bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 0, 2) "vprold\t" OP_U8 OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f.W0 72 /1 ib vprold zmm1{k1}{z}, zmm2/m512/m32bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 1, 2) "vprolq\t" OP_U8 OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f.W1 72 /1 ib vprolq zmm1{k1}{z}, zmm2/m512/m64bcst, imm8 */

	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(1, 1, 0, 0) "vpsrld\t" OP_U8 OP_RM128_XMM OP_VRXMM),      /*  VEX.128.66.0f.WIG 72 /2 ib vpsrld xmm1, xmm2, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(1, 1, 0, 1) "vpsrld\t" OP_U8 OP_RM256_YMM OP_VRYMM),      /*  VEX.256.66.0f.WIG 72 /2 ib vpsrld ymm1, ymm2, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 0, 0) "vpsrld\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK), /* EVEX.128.66.0f.W0  72 /2 ib vpsrld xmm1{k1}{z}, xmm2/m128/m32bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 0, 1) "vpsrld\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK), /* EVEX.256.66.0f.W0  72 /2 ib vpsrld ymm1{k1}{z}, ymm2/m256/m32bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 0, 2) "vpsrld\t" OP_U8 OP_RM512_ZMM OP_VRZMM_MASK), /* EVEX.512.66.0f.W0  72 /2 ib vpsrld zmm1{k1}{z}, zmm2/m512/m32bcst, imm8 */
	I(0x72, IF_MODRM|IF_REG2,                                    "psrld\t" OP_U8 OP_RM64_MM),                  /*                 0f 72 /2 ib psrld mm, imm8 */
	I(0x72, IF_66|IF_MODRM|IF_REG2,                              "psrld\t" OP_U8 OP_RM128_XMM),                /*              66 0f 72 /2 ib psrld xmm1, imm8 */

	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(1, 1, 0, 0) "vpsrad\t" OP_U8 OP_RM128_XMM OP_VRXMM),      /*  VEX.128.66.0f.WIG 72 /4 ib vpsrad xmm1, xmm2, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(1, 1, 0, 1) "vpsrad\t" OP_U8 OP_RM256_YMM OP_VRYMM),      /*  VEX.256.66.0f.WIG 72 /4 ib vpsrad ymm1, ymm2, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(0, 0, 0, 0) "vpsrad\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK), /* EVEX.128.66.0f.W0  72 /4 ib vpsrad xmm1{k1}{z}, xmm2/m128/m32bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(0, 0, 0, 1) "vpsrad\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK), /* EVEX.256.66.0f.W0  72 /4 ib vpsrad ymm1{k1}{z}, ymm2/m256/m32bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(0, 0, 0, 2) "vpsrad\t" OP_U8 OP_RM512_ZMM OP_VRZMM_MASK), /* EVEX.512.66.0f.W0  72 /4 ib vpsrad zmm1{k1}{z}, zmm2/m512/m32bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(0, 0, 1, 0) "vpsraq\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK), /* EVEX.128.66.0f.W1  72 /4 ib vpsraq xmm1{k1}{z}, xmm2/m128/m64bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(0, 0, 1, 1) "vpsraq\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK), /* EVEX.512.66.0f.W1  72 /4 ib vpsraq ymm1{k1}{z}, ymm2/m256/m64bcst, imm8 */
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG4, OP_VEX_B0(0, 0, 1, 2) "vpsraq\t" OP_U8 OP_RM512_ZMM OP_VRZMM_MASK), /* EVEX.512.66.0f.W1  72 /4 ib vpsraq zmm1{k1}{z}, zmm2/m512/m64bcst, imm8 */
	I(0x72, IF_MODRM|IF_REG4,                                    "psrad\t" OP_U8 OP_RM64_MM),                  /*                 0f 72 /4 ib psrad mm, imm8 */
	I(0x72, IF_66|IF_MODRM|IF_REG4,                              "psrad\t" OP_U8 OP_RM128_XMM),                /*              66 0f 72 /4 ib psrad xmm1, imm8 */

	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_RMM|IF_REG6, OP_VEX_B0(1, 1, 0, 0) "vpslld\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK),
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_RMM|IF_REG6, OP_VEX_B0(1, 1, 0, 1) "vpslld\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK),
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(0, 0, 0, 0) "vpslld\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK),
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(0, 0, 0, 1) "vpslld\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK),
	I(0x72, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(0, 0, 0, 2) "vpslld\t" OP_U8 OP_RM512_ZMM OP_VRZMM_MASK),
	I(0x72, IF_MODRM|IF_RMR|IF_REG6,       "pslld\t" OP_U8 OP_RM64_MM),
	I(0x72, IF_66|IF_MODRM|IF_RMR|IF_REG6, "pslld\t" OP_U8 OP_RM128_XMM),

	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(1, 1, 0, 0) "vpsrlq\t" OP_U8 OP_RM128_XMM OP_VRXMM),      /*  VEX.128.66.0f.WIG 73 /2 ib vpsrlq xmm1, xmm2, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(1, 1, 0, 1) "vpsrlq\t" OP_U8 OP_RM256_YMM OP_VRYMM),      /*  VEX.256.66.0f.WIG 73 /2 ib vpsrlq ymm1, ymm2, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 1, 0) "vpsrlq\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK), /* EVEX.128.66.0f.W1  73 /2 ib vpsrlq xmm1{k1}{z}, xmm2/m128/m64bcst, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 1, 1) "vpsrlq\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK), /* EVEX.512.66.0f.W1  73 /2 ib vpsrlq ymm1{k1}{z}, ymm2/m256/m64bcst, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 1, 2) "vpsrlq\t" OP_U8 OP_RM512_ZMM OP_VRZMM_MASK), /* EVEX.512.66.0f.W1  73 /2 ib vpsrlq zmm1{k1}{z}, zmm2/m512/m64bcst, imm8 */
	I(0x73, IF_MODRM|IF_REG2,                                    "psrlq\t" OP_U8 OP_RM64_MM),                  /*                 0f 73 /2 ib psrlq mm, imm8 */
	I(0x73, IF_66|IF_MODRM|IF_REG2,                              "psrlq\t" OP_U8 OP_RM128_XMM),                /*              66 0f 73 /2 ib psrlq xmm1, imm8 */

	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG3, OP_VEX_B0(0, 1, 0, 0) "vpsrldq\t" OP_U8 OP_RM128_XMM OP_VRXMM), /* EVEX.128.66.0f.WIG 73 /3 ib vpsrldq xmm1, xmm2/m128, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG3, OP_VEX_B0(0, 1, 0, 1) "vpsrldq\t" OP_U8 OP_RM256_YMM OP_VRYMM), /* EVEX.256.66.0f.WIG 73 /3 ib vpsrldq ymm1, ymm2/m256, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG3, OP_VEX_B0(0, 1, 0, 2) "vpsrldq\t" OP_U8 OP_RM512_ZMM OP_VRZMM), /* EVEX.512.66.0f.WIG 73 /3 ib vpsrldq zmm1, zmm2/m512, imm8 */
	I(0x73, IF_66|IF_MODRM|IF_REG3,                              "psrldq\t" OP_U8 OP_RM128_XMM),           /*              66 0f 73 /3 ib psrldq xmm1, imm8 */

	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(1, 1, 0, 0) "vpsllq\t" OP_U8 OP_RM128_XMM OP_VRXMM),      /*  VEX.128.66.0f.WIG 73 /6 ib vpsllq xmm1, xmm2, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(1, 1, 0, 1) "vpsllq\t" OP_U8 OP_RM256_YMM OP_VRYMM),      /*  VEX.256.66.0f.WIG 73 /6 ib vpsllq ymm1, ymm2, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(0, 0, 1, 0) "vpsllq\t" OP_U8 OP_RM128_XMM OP_VRXMM_MASK), /* EVEX.128.66.0f.W1  73 /6 ib vpsllq xmm1{k1}{z}, xmm2/m128/m64bcst, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(0, 0, 1, 1) "vpsllq\t" OP_U8 OP_RM256_YMM OP_VRYMM_MASK), /* EVEX.512.66.0f.W1  73 /6 ib vpsllq ymm1{k1}{z}, ymm2/m256/m64bcst, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG6, OP_VEX_B0(0, 0, 1, 2) "vpsllq\t" OP_U8 OP_RM512_ZMM OP_VRZMM_MASK), /* EVEX.512.66.0f.W1  73 /6 ib vpsllq zmm1{k1}{z}, zmm2/m512/m64bcst, imm8 */
	I(0x73, IF_MODRM|IF_REG6,                                    "psllq\t" OP_U8 OP_RM64_MM),                  /*                 0f 73 /6 ib psllq mm, imm8 */
	I(0x73, IF_66|IF_MODRM|IF_REG6,                              "psllq\t" OP_U8 OP_RM128_XMM),                /*              66 0f 73 /6 ib psllq xmm1, imm8 */

	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG7, OP_VEX_B0(0, 1, 0, 0) "vpslldq\t" OP_U8 OP_RM128_XMM OP_VRXMM), /* EVEX.128.66.0f.WIG 73 /7 ib vpslldq xmm1, xmm2/m128, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG7, OP_VEX_B0(0, 1, 0, 1) "vpslldq\t" OP_U8 OP_RM256_YMM OP_VRYMM), /* EVEX.256.66.0f.WIG 73 /7 ib vpslldq ymm1, ymm2/m256, imm8 */
	I(0x73, IF_66|IF_VEX|IF_MODRM|IF_REG7, OP_VEX_B0(0, 1, 0, 2) "vpslldq\t" OP_U8 OP_RM512_ZMM OP_VRZMM), /* EVEX.512.66.0f.WIG 73 /7 ib vpslldq zmm1, zmm2/m512, imm8 */
	I(0x73, IF_66|IF_MODRM|IF_REG7,                              "pslldq\t" OP_U8 OP_RM128_XMM),           /*              66 0f 73 /7 ib pslldq xmm1, imm8 */

	I(0x74, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpcmpeqb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x74, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpcmpeqb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x74, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpcmpeqb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0x74, IF_MODRM,              "pcmpeqb\t" OP_RMM OP_RM64_MM),
	I(0x74, IF_66|IF_MODRM,        "pcmpeqb\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0x75, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpcmpeqw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x75, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpcmpeqw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x75, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpcmpeqw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0x75, IF_MODRM,              "pcmpeqw\t" OP_RMM OP_RM64_MM),
	I(0x75, IF_66|IF_MODRM,        "pcmpeqw\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0x76, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpcmpeqd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x76, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpcmpeqd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0x76, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpcmpeqd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x76, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpcmpeqd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0x76, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpcmpeqd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0x76, IF_MODRM,              "pcmpeqd\t" OP_RMM OP_RM64_MM),
	I(0x76, IF_66|IF_MODRM,        "pcmpeqd\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0x77, IF_VEX, OP_VEX_B0(0, 1, 0, 0) "vzeroupper"),
	I(0x77, IF_VEX, OP_VEX_B0(0, 1, 0, 1) "vzeroall"),
	I(0x77, 0,                      "emms"),

//	I(0x78, IF_MODRM|IF_RMM,  "svdc\t" OP_RSEG OP_MEM/*80*/), /* Unofficial */
//	I(0x79, IF_MODRM|IF_RMM,  "rsdc\t" OP_MEM/*80*/ OP_RSEG), /* Unofficial */

	I(0x78, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VCVTTPD2UDQ_XMM)), /* EVEX.128.0f.W1 78 /r vcvttpd2udq xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0x78, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VCVTTPD2UDQ_YMM)), /* EVEX.256.0f.W1 78 /r vcvttpd2udq xmm1{k1}{z}, ymm2/m256/m64bcst */
	I(0x78, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VCVTTPD2UDQ_ZMM)), /* EVEX.512.0f.W1 78 /r vcvttpd2udq ymm1{k1}{z}, zmm2/m512/m64bcst{sae} */

	I(0x78, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VCVTTPD2UQQ_XMM)), /* EVEX.128.66.0f.W1 78 /r vcvttpd2uqq xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0x78, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VCVTTPD2UQQ_YMM)), /* EVEX.256.66.0f.W1 78 /r vcvttpd2uqq ymm1{k1}{z}, ymm2/m256/m64bcst */
	I(0x78, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VCVTTPD2UQQ_ZMM)), /* EVEX.512.66.0f.W1 78 /r vcvttpd2uqq zmm1{k1}{z}, zmm2/m512/m64bcst{sae} */

	I(0x78, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VCVTTPS2UDQ_XMM)), /* EVEX.128.0f.W0 78 /r vcvttps2udq xmm1{k1}{z}, xmm2/m128/m32bcst */
	I(0x78, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VCVTTPS2UDQ_YMM)), /* EVEX.256.0f.W0 78 /r vcvttps2udq ymm1{k1}{z}, ymm2/m256/m32bcst */
	I(0x78, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VCVTTPS2UDQ_ZMM)), /* EVEX.512.0f.W0 78 /r vcvttps2udq zmm1{k1}{z}, zmm2/m512/m32bcst{sae} */

	I(0x78, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VCVTTPS2UQQ_XMM)), /* EVEX.128.66.0f.W0 78 /r vcvttps2uqq xmm1{k1}{z}, xmm2/m64/m32bcst */
	I(0x78, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VCVTTPS2UQQ_YMM)), /* EVEX.256.66.0f.W0 78 /r vcvttps2uqq ymm1{k1}{z}, xmm2/m128/m32bcst */
	I(0x78, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VCVTTPS2UQQ_ZMM)), /* EVEX.512.66.0f.W0 78 /r vcvttps2uqq zmm1{k1}{z}, ymm2/m256/m32bcst{sae} */

	I(0x78, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VCVTTSD2USI_R32)), /* EVEX.LIG.f2.0f.W0 78 /r vcvttsd2usi r32, xmm1/m64{sae} */
	I(0x78, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VCVTTSD2USI_R64)), /* EVEX.LIG.f2.0f.W1 78 /r vcvttsd2usi r64, xmm1/m64{sae} */
	I(0x78, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VCVTTSS2USI_R32)), /* EVEX.LIG.f3.0f.W0 78 /r vcvttss2usi r32, xmm1/m32{sae} */
	I(0x78, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VCVTTSS2USI_R64)), /* EVEX.LIG.f3.0f.W1 78 /r vcvttss2usi r64, xmm1/m32{sae} */

	I(0x78, IF_X32|IF_MODRM,        "vmreadl\t" OP_R32 OP_RM32),
	I(0x78, IF_X64|IF_MODRM,        "vmreadq\t" OP_R64 OP_RM64),

	I(0x79, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VCVTPD2UDQ_XMM)), /* EVEX.128.0f.W1 79 /r vcvtpd2udq xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0x79, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VCVTPD2UDQ_YMM)), /* EVEX.256.0f.W1 79 /r vcvtpd2udq xmm1{k1}{z}, ymm2/m256/m64bcst */
	I(0x79, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VCVTPD2UDQ_ZMM)), /* EVEX.512.0f.W1 79 /r vcvtpd2udq ymm1{k1}{z}, zmm2/m512/m64bcst{er} */
	I(0x79, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VCVTPS2UDQ_XMM)), /* EVEX.128.0f.W0 79 /r vcvtps2udq xmm1{k1}{z}, xmm2/m128/m32bcst */
	I(0x79, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VCVTPS2UDQ_YMM)), /* EVEX.256.0f.W0 79 /r vcvtps2udq ymm1{k1}{z}, ymm2/m256/m32bcst */
	I(0x79, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VCVTPS2UDQ_ZMM)), /* EVEX.512.0f.W0 79 /r vcvtps2udq zmm1{k1}{z}, zmm2/m512/m32bcst{er} */

	I(0x79, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VCVTPD2UQQ_XMM)), /* EVEX.128.66.0f.W1 79 /r vcvtpd2uqq xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0x79, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VCVTPD2UQQ_YMM)), /* EVEX.256.66.0f.W1 79 /r vcvtpd2uqq ymm1{k1}{z}, ymm2/m256/m64bcst */
	I(0x79, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VCVTPD2UQQ_ZMM)), /* EVEX.512.66.0f.W1 79 /r vcvtpd2uqq zmm1{k1}{z}, zmm2/m512/m64bcst{er} */
	I(0x79, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VCVTPS2UQQ_XMM)), /* EVEX.128.66.0f.W0 79 /r vcvtps2uqq xmm1{k1}{z}, xmm2/m64/m32bcst */
	I(0x79, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VCVTPS2UQQ_YMM)), /* EVEX.256.66.0f.W0 79 /r vcvtps2uqq ymm1{k1}{z}, xmm2/m128/m32bcst */
	I(0x79, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VCVTPS2UQQ_ZMM)), /* EVEX.512.66.0f.W0 79 /r vcvtps2uqq zmm1{k1}{z}, ymm2/m256/m32bcst{er} */

	I(0x79, IF_F2|IF_VEX|IF_MODRM,        LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VCVTSD2USI_R32)), /* EVEX.LIG.f2.0f.W0 79 /r vcvtsd2usi r32, xmm1/m64{er} */
	I(0x79, IF_X32|IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VCVTSD2USI_R32)), /* EVEX.LIG.f2.0f.W1 79 /r vcvtsd2usi r64, xmm1/m64{er} */
	I(0x79, IF_X64|IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VCVTSD2USI_R64)), /* EVEX.LIG.f2.0f.W1 79 /r vcvtsd2usi r64, xmm1/m64{er} */

	I(0x79, IF_F3|IF_VEX|IF_MODRM,        LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VCVTSS2USI_R32)), /* EVEX.LIG.f3.0f.W0 79 /r vcvtss2usi r32, xmm1/m32{er} */
	I(0x79, IF_X32|IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VCVTSS2USI_R32)), /* EVEX.LIG.f3.0f.W1 79 /r vcvtss2usi r64, xmm1/m32{er} */
	I(0x79, IF_X64|IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VCVTSS2USI_R64)), /* EVEX.LIG.f3.0f.W1 79 /r vcvtss2usi r64, xmm1/m32{er} */

	I(0x79, IF_X32|IF_MODRM,        "vmwritel\t" OP_R32 OP_RM32),
	I(0x79, IF_X64|IF_MODRM,        "vmwriteq\t" OP_R64 OP_RM64),

	I(0x7a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VCVTTPD2QQ_XMM)), /* EVEX.128.66.0f.W1 7a /r vcvttpd2qq xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0x7a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VCVTTPD2QQ_YMM)), /* EVEX.256.66.0f.W1 7a /r vcvttpd2qq ymm1{k1}{z}, ymm2/m256/m64bcst */
	I(0x7a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VCVTTPD2QQ_ZMM)), /* EVEX.512.66.0f.W1 7a /r vcvttpd2qq zmm1{k1}{z}, zmm2/m512/m64bcst{sae} */
	I(0x7a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VCVTTPS2QQ_XMM)), /* EVEX.128.66.0f.W0 7a /r vcvttps2qq xmm1{k1}{z}, xmm2/m64/m32bcst */
	I(0x7a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VCVTTPS2QQ_YMM)), /* EVEX.256.66.0f.W0 7a /r vcvttps2qq ymm1{k1}{z}, xmm2/m128/m32bcst */
	I(0x7a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VCVTTPS2QQ_ZMM)), /* EVEX.512.66.0f.W0 7a /r vcvttps2qq zmm1{k1}{z}, ymm2/m256/m32bcst{sae} */

	I(0x7a, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VCVTUQQ2PD_XMM)), /* EVEX.128.f3.0f.W1 7a /r vcvtuqq2pd xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0x7a, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VCVTUQQ2PD_YMM)), /* EVEX.256.f3.0f.W1 7a /r vcvtuqq2pd ymm1{k1}{z}, ymm2/m256/m64bcst */
	I(0x7a, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VCVTUQQ2PD_ZMM)), /* EVEX.512.f3.0f.W1 7a /r vcvtuqq2pd zmm1{k1}{z}, zmm2/m512/m64bcst{er} */
	I(0x7a, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VCVTUDQ2PD_XMM)), /* EVEX.128.f3.0f.W0 7a /r vcvtudq2pd xmm1{k1}{z}, xmm2/m64/m32bcst */
	I(0x7a, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VCVTUDQ2PD_YMM)), /* EVEX.256.f3.0f.W0 7a /r vcvtudq2pd ymm1{k1}{z}, xmm2/m128/m32bcst */
	I(0x7a, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VCVTUDQ2PD_ZMM)), /* EVEX.512.f3.0f.W0 7a /r vcvtudq2pd zmm1{k1}{z}, ymm2/m256/m32bcst */

	I(0x7a, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VCVTUDQ2PS_XMM)), /* EVEX.128.f2.0f.W0 7a /r vcvtudq2ps xmm1{k1}{z}, xmm2/m128/m32bcst */
	I(0x7a, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VCVTUDQ2PS_YMM)), /* EVEX.256.f2.0f.W0 7a /r vcvtudq2ps ymm1{k1}{z}, ymm2/m256/m32bcst */
	I(0x7a, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VCVTUDQ2PS_ZMM)), /* EVEX.512.f2.0f.W0 7a /r vcvtudq2ps zmm1{k1}{z}, zmm2/m512/m32bcst{er} */
	I(0x7a, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VCVTUQQ2PS_XMM)), /* EVEX.128.f2.0f.W1 7a /r vcvtuqq2ps xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0x7a, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VCVTUQQ2PS_YMM)), /* EVEX.256.f2.0f.W1 7a /r vcvtuqq2ps xmm1{k1}{z}, ymm2/m256/m64bcst */
	I(0x7a, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VCVTUQQ2PS_ZMM)), /* EVEX.512.f2.0f.W1 7a /r vcvtuqq2ps ymm1{k1}{z}, zmm2/m512/m64bcst{er} */

	I(0x7b, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VCVTUSI2SD_R32)), /* EVEX.LIG.f2.0f.W0 7b /r vcvtusi2sd xmm1, xmm2, r/m32 */
	I(0x7b, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VCVTUSI2SD_R64)), /* EVEX.LIG.f2.0f.W1 7b /r vcvtusi2sd xmm1, xmm2, r/m64{er} */

	I(0x7b, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VCVTUSI2SS_R32)), /* EVEX.LIG.f3.0f.W0 7b /r vcvtusi2ss xmm1, xmm2, r/m32{er} */
	I(0x7b, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VCVTUSI2SS_R64)), /* EVEX.LIG.f3.0f.W1 7b /r vcvtusi2ss xmm1, xmm2, r/m64{er} */

	I(0x7b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VCVTPD2QQ_XMM)), /* EVEX.128.66.0f.W1 7b /r vcvtpd2qq xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0x7b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VCVTPD2QQ_YMM)), /* EVEX.256.66.0f.W1 7b /r vcvtpd2qq ymm1{k1}{z}, ymm2/m256/m64bcst */
	I(0x7b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VCVTPD2QQ_ZMM)), /* EVEX.512.66.0f.W1 7b /r vcvtpd2qq zmm1{k1}{z}, zmm2/m512/m64bcst{er} */
	I(0x7b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VCVTPS2QQ_XMM)), /* EVEX.128.66.0f.W0 7b /r vcvtps2qq xmm1{k1}{z}, xmm2/m64/m32bcst */
	I(0x7b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VCVTPS2QQ_YMM)), /* EVEX.256.66.0f.W0 7b /r vcvtps2qq ymm1{k1}{z}, xmm2/m128/m32bcst */
	I(0x7b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VCVTPS2QQ_ZMM)), /* EVEX.512.66.0f.W0 7b /r vcvtps2qq zmm1{k1}{z}, ymm2/m256/m32bcst{er} */

	I(0x7c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vhaddpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f.WIG 7c /r vhaddpd xmm1, xmm2, xmm3/m128 */
	I(0x7c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vhaddpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f.WIG 7c /r vhaddpd ymm1, ymm2, ymm3/m256 */
	I(0x7c, IF_66|IF_MODRM,                              "haddpd\t" OP_RM128_XMM OP_RXMM),             /*             66 0f 7c /r haddpd xmm1, xmm2/m128 */

	I(0x7c, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vhaddps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.f2.0f.WIG 7c /r vhaddps xmm1, xmm2, xmm3/m128 */
	I(0x7c, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vhaddps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.f2.0f.WIG 7c /r vhaddps ymm1, ymm2, ymm3/m256 */
	I(0x7c, IF_F2|IF_MODRM,                              "haddps\t" OP_RM128_XMM OP_RXMM),             /*             f2 0f 7c /r haddps xmm1, xmm2/m128 */

	I(0x7d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vhsubpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f.WIG 7d /r vhsubpd xmm1, xmm2, xmm3/m128 */
	I(0x7d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vhsubpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f.WIG 7d /r vhsubpd ymm1, ymm2, ymm3/m256 */
	I(0x7d, IF_66|IF_MODRM,                              "hsubpd\t" OP_RM128_XMM OP_RXMM),             /*             66 0f 7d /r hsubpd xmm1, xmm2/m128 */

	I(0x7d, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vhsubps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.f2.0f.WIG 7d /r vhsubps xmm1, xmm2, xmm3/m128 */
	I(0x7d, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vhsubps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.f2.0f.WIG 7d /r vhsubps ymm1, ymm2, ymm3/m256 */
	I(0x7d, IF_F2|IF_MODRM,                              "hsubps\t" OP_RM128_XMM OP_RXMM),             /*             f2 0f 7d /r hsubps xmm1, xmm2/m128 */

	I(0x7e, IF_66|IF_VEX|IF_MODRM,  OP_VEX_B0(0, 0, 0, 0) "vmovd\t" OP_RXMM OP_RM32), /* EVEX.128.66.0f.W0 7e /r vmovd r/m32, xmm1 */
	I(0x7e, IF_66|IF_VEX|IF_MODRM,  OP_VEX_B0(0, 0, 1, 0) "vmovq\t" OP_RXMM OP_RM64), /* EVEX.128.66.0f.W1 7e /r vmovq r/m64, xmm1 */
	I(0x7e, IF_MODRM,               "movd\t" OP_RMM OP_RM32),                         /*                0f 7e /r movd r/m32, mm */
	I(0x7e, IF_MODRM|IF_REXW,       "movq\t" OP_RMM OP_RM64),                         /*        rex.w + 0f 7e /r movq r/m64, mm */
	I(0x7e, IF_66|IF_MODRM,         "movd\t" OP_RXMM OP_RM32),                        /*     66         0f 7e /r movd r/m32, xmm */
	I(0x7e, IF_66|IF_MODRM|IF_REXW, "movq\t" OP_RXMM OP_RM64),                        /*     66 rex.w + 0f 7e /r movq r/m64, xmm */

	I(0x7f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovdqa\t" OP_RXMM OP_RM128_XMM),    /*  VEX.128.66.0f.WIG 7f /r vmovdqa xmm2/m128, xmm1 */
	I(0x7f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovdqa\t" OP_RYMM OP_RM256_YMM),    /*  VEX.256.66.0f.WIG 7f /r vmovdqa ymm2/m256, ymm1 */
	I(0x7f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VMOVDQA32_XMM_REV)), /* EVEX.128.66.0f.W0  7f /r vmovdqa32 xmm2/m128{k1}{z}, xmm1 */
	I(0x7f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VMOVDQA32_YMM_REV)), /* EVEX.256.66.0f.W0  7f /r vmovdqa32 ymm2/m256{k1}{z}, ymm1 */
	I(0x7f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VMOVDQA32_ZMM_REV)), /* EVEX.512.66.0f.W0  7f /r vmovdqa32 zmm2/m512{k1}{z}, zmm1 */
	I(0x7f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VMOVDQA64_XMM_REV)), /* EVEX.128.66.0f.W1  7f /r vmovdqa64 xmm2/m128{k1}{z}, xmm1 */
	I(0x7f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VMOVDQA64_YMM_REV)), /* EVEX.512.66.0f.W1  7f /r vmovdqa64 ymm2/m256{k1}{z}, ymm1 */
	I(0x7f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VMOVDQA64_ZMM_REV)), /* EVEX.512.66.0f.W1  7f /r vmovdqa64 zmm2/m512{k1}{z}, zmm1 */
	I(0x7f, IF_66|IF_MODRM,        "movdqa\t" OP_RXMM OP_RM128_XMM),                           /*              66 0f 7f /r movdqa xmm2/m128, xmm1 */

	I(0x7f, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmovdqu\t" OP_RXMM OP_RM128_XMM),       /*  VEX.128.f3.0f.WIG 7f /r vmovdqu xmm2/m128, xmm1 */
	I(0x7f, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmovdqu\t" OP_RYMM OP_RM256_YMM),       /*  VEX.256.f3.0f.WIG 7f /r vmovdqu ymm2/m256, ymm1 */
	I(0x7f, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vmovdqu8\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.f2.0f.W0  7f /r vmovdqu8 xmm2/m128{k1}{z}, xmm1 */
	I(0x7f, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vmovdqu8\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.f2.0f.W0  7f /r vmovdqu8 ymm2/m256{k1}{z}, ymm1 */
	I(0x7f, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vmovdqu8\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.f2.0f.W0  7f /r vmovdqu8 zmm2/m512{k1}{z}, zmm1 */
	I(0x7f, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VMOVDQU16_XMM_REV)),    /* EVEX.128.f2.0f.W1  7f /r vmovdqu16 xmm2/m128{k1}{z}, xmm1 */
	I(0x7f, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VMOVDQU16_YMM_REV)),    /* EVEX.256.f2.0f.W1  7f /r vmovdqu16 ymm2/m256{k1}{z}, ymm1 */
	I(0x7f, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VMOVDQU16_ZMM_REV)),    /* EVEX.512.f2.0f.W1  7f /r vmovdqu16 zmm2/m512{k1}{z}, zmm1 */
	I(0x7f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VMOVDQU32_XMM_REV)),    /* EVEX.128.f3.0f.W0  7f /r vmovdqu32 xmm2/m128{k1}{z}, xmm1 */
	I(0x7f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VMOVDQU32_YMM_REV)),    /* EVEX.256.f3.0f.W0  7f /r vmovdqu32 ymm2/m256{k1}{z}, ymm1 */
	I(0x7f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VMOVDQU32_ZMM_REV)),    /* EVEX.512.f3.0f.W0  7f /r vmovdqu32 zmm2/m512{k1}{z}, zmm1 */
	I(0x7f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VMOVDQU64_XMM_REV)),    /* EVEX.128.f3.0f.W1  7f /r vmovdqu64 xmm2/m128{k1}{z}, xmm1 */
	I(0x7f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VMOVDQU64_YMM_REV)),    /* EVEX.256.f3.0f.W1  7f /r vmovdqu64 ymm2/m256{k1}{z}, ymm1 */
	I(0x7f, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VMOVDQU64_ZMM_REV)),    /* EVEX.512.f3.0f.W1  7f /r vmovdqu64 zmm2/m512{k1}{z}, zmm1 */
	I(0x7f, IF_F3|IF_MODRM,        "movdqu\t" OP_RXMM OP_RM128_XMM),                              /*              f3 0f 7f /r movdqu xmm2/m128, xmm1 */

	I(0x80, IF_66,            "j" NAME_jc0 "\t" OP_DISP16),
	I(0x80, 0,                "j" NAME_jc0 "\t" OP_DISP32),

	I(0x81, IF_66,            "j" NAME_jc1 "\t" OP_DISP16),
	I(0x81, 0,                "j" NAME_jc1 "\t" OP_DISP32),

	I(0x82, IF_66,            "j" NAME_jc2 "\t" OP_DISP16),
	I(0x82, 0,                "j" NAME_jc2 "\t" OP_DISP32),

	I(0x83, IF_66,            "j" NAME_jc3 "\t" OP_DISP16),
	I(0x83, 0,                "j" NAME_jc3 "\t" OP_DISP32),

	I(0x84, IF_66,            "j" NAME_jc4 "\t" OP_DISP16),
	I(0x84, 0,                "j" NAME_jc4 "\t" OP_DISP32),

	I(0x85, IF_66,            "j" NAME_jc5 "\t" OP_DISP16),
	I(0x85, 0,                "j" NAME_jc5 "\t" OP_DISP32),

	I(0x86, IF_66,            "j" NAME_jc6 "\t" OP_DISP16),
	I(0x86, 0,                "j" NAME_jc6 "\t" OP_DISP32),

	I(0x87, IF_66,            "j" NAME_jc7 "\t" OP_DISP16),
	I(0x87, 0,                "j" NAME_jc7 "\t" OP_DISP32),

	I(0x88, IF_66,            "j" NAME_jc8 "\t" OP_DISP16),
	I(0x88, 0,                "j" NAME_jc8 "\t" OP_DISP32),

	I(0x89, IF_66,            "j" NAME_jc9 "\t" OP_DISP16),
	I(0x89, 0,                "j" NAME_jc9 "\t" OP_DISP32),

	I(0x8a, IF_66,            "j" NAME_jca "\t" OP_DISP16),
	I(0x8a, 0,                "j" NAME_jca "\t" OP_DISP32),

	I(0x8b, IF_66,            "j" NAME_jcb "\t" OP_DISP16),
	I(0x8b, 0,                "j" NAME_jcb "\t" OP_DISP32),

	I(0x8c, IF_66,            "j" NAME_jcc "\t" OP_DISP16),
	I(0x8c, 0,                "j" NAME_jcc "\t" OP_DISP32),

	I(0x8d, IF_66,            "j" NAME_jcd "\t" OP_DISP16),
	I(0x8d, 0,                "j" NAME_jcd "\t" OP_DISP32),

	I(0x8e, IF_66,            "j" NAME_jce "\t" OP_DISP16),
	I(0x8e, 0,                "j" NAME_jce "\t" OP_DISP32),

	I(0x8f, IF_66,            "j" NAME_jcf "\t" OP_DISP16),
	I(0x8f, 0,                "j" NAME_jcf "\t" OP_DISP32),

	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "kmovb\t" OP_RMK OP_RK), /* VEX.L0.66.0f.W0 90 /r kmovb k1, k2/m8 */
	I(0x90, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 0, 0) "kmovw\t" OP_RMK OP_RK), /* VEX.L0.   0f.W0 90 /r kmovw k1, k2/m16 */
	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "kmovd\t" OP_RMK OP_RK), /* VEX.L0.66.0f.W1 90 /r kmovd k1, k2/m32 */
	I(0x90, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 1, 0) "kmovq\t" OP_RMK OP_RK), /* VEX.L0.   0f.W1 90 /r kmovq k1, k2/m64 */

	I(0x90, IF_MODRM,         "set" NAME_jc0 "\t" OP_RM8),

	I(0x91, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "kmovb\t" OP_RK OP_MEM), /* VEX.L0.66.0f.W0 91 /r kmovb m8, k1 */
	I(0x91, IF_VEX|IF_MODRM|IF_RMM,       OP_VEX_B0(0, 0, 0, 0) "kmovw\t" OP_RK OP_MEM), /* VEX.L0.   0f.W0 91 /r kmovw m16, k1 */
	I(0x91, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 1, 0) "kmovd\t" OP_RK OP_MEM), /* VEX.L0.66.0f.W1 91 /r kmovd m32, k1 */
	I(0x91, IF_VEX|IF_MODRM|IF_RMM,       OP_VEX_B0(0, 0, 1, 0) "kmovq\t" OP_RK OP_MEM), /* VEX.L0.   0f.W1 91 /r kmovq m64, k1 */

	I(0x91, IF_MODRM,         "set" NAME_jc1 "\t" OP_RM8),

	I(0x92, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "kmovb\t" OP_RM32 OP_RK), /* VEX.L0.66.0f.W0 92 /r kmovb k1, r32 */
	I(0x92, IF_VEX|IF_MODRM|IF_RMR,       OP_VEX_B0(0, 0, 0, 0) "kmovw\t" OP_RM32 OP_RK), /* VEX.L0.   0f.W0 92 /r kmovw k1, r32 */
	I(0x92, IF_F2|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "kmovd\t" OP_RM32 OP_RK), /* VEX.L0.f2.0f.W0 92 /r kmovd k1, r32 */
	I(0x92, IF_F2|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 0) "kmovq\t" OP_RM64 OP_RK), /* VEX.L0.f2.0f.W1 92 /r kmovq k1, r64 */

	I(0x92, IF_MODRM,         "set" NAME_jc2 "\t" OP_RM8),

	I(0x93, IF_66|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "kmovb\t" OP_RMK OP_R32), /* VEX.L0.66.0f.W0 93 /r kmovb r32, k1 */
	I(0x93, IF_VEX|IF_MODRM|IF_RMR,       OP_VEX_B0(0, 0, 0, 0) "kmovw\t" OP_RMK OP_R32), /* VEX.L0.   0f.W0 93 /r kmovw r32, k1 */
	I(0x93, IF_F2|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "kmovd\t" OP_RMK OP_R32), /* VEX.L0.f2.0f.W0 93 /r kmovd r32, k1 */
	I(0x93, IF_F2|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 0) "kmovq\t" OP_RMK OP_R64), /* VEX.L0.f2.0f.W1 93 /r kmovq r64, k1 */

	I(0x93, IF_MODRM,         "set" NAME_jc3 "\t" OP_RM8),

	I(0x94, IF_MODRM,         "set" NAME_jc4 "\t" OP_RM8),

	I(0x95, IF_MODRM,         "set" NAME_jc5 "\t" OP_RM8),

	I(0x96, IF_MODRM,         "set" NAME_jc6 "\t" OP_RM8),

	I(0x97, IF_MODRM,         "set" NAME_jc7 "\t" OP_RM8),

	I(0x98, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "kortestb\t" OP_RMK OP_RK), /* VEX.L0.66.0f.W0 98 /r kortestb k1, k2 */
	I(0x98, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 0, 0) "kortestw\t" OP_RMK OP_RK), /* VEX.L0.   0f.W0 98 /r kortestw k1, k2 */
	I(0x98, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "kortestd\t" OP_RMK OP_RK), /* VEX.L0.66.0f.W1 98 /r kortestd k1, k2 */
	I(0x98, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 1, 0) "kortestq\t" OP_RMK OP_RK), /* VEX.L0.   0f.W1 98 /r kortestq k1, k2 */

	I(0x98, IF_MODRM,         "set" NAME_jc8 "\t" OP_RM8),

	I(0x99, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "ktestb\t" OP_RMK OP_RK), /* VEX.L0.66.0f.W0 99 /r ktestb k1, k2 */
	I(0x99, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 0, 0) "ktestw\t" OP_RMK OP_RK), /* VEX.L0.   0f.W0 99 /r ktestw k1, k2 */
	I(0x99, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "ktestd\t" OP_RMK OP_RK), /* VEX.L0.66.0f.W1 99 /r ktestd k1, k2 */
	I(0x99, IF_VEX|IF_MODRM,       OP_VEX_B0(0, 0, 1, 0) "ktestq\t" OP_RMK OP_RK), /* VEX.L0.   0f.W1 99 /r ktestq k1, k2 */

	I(0x99, IF_MODRM,         "set" NAME_jc9 "\t" OP_RM8),

	I(0x9a, IF_MODRM,         "set" NAME_jca "\t" OP_RM8),

	I(0x9b, IF_MODRM,         "set" NAME_jcb "\t" OP_RM8),

	I(0x9c, IF_MODRM,         "set" NAME_jcc "\t" OP_RM8),

	I(0x9d, IF_MODRM,         "set" NAME_jcd "\t" OP_RM8),

	I(0x9e, IF_MODRM,         "set" NAME_jce "\t" OP_RM8),

	I(0x9f, IF_MODRM,         "set" NAME_jcf "\t" OP_RM8),

	I(0xa0, IF_66,            "pushw\t" OP_FS),
	I(0xa0, IF_X32,           "pushl\t" OP_FS),
	I(0xa0, IF_X64,           "pushq\t" OP_FS),
	I(0xa1, IF_66,            "popw\t"  OP_FS),
	I(0xa1, IF_X32,           "popl\t"  OP_FS),
	I(0xa1, IF_X64,           "popq\t"  OP_FS),

	I(0xa2, 0,                "cpuid"),

	I(0xa3, IF_66|IF_MODRM,   "btw\t" OP_R16 OP_RM16),
	I(0xa3, IF_MODRM,         "btl\t" OP_R32 OP_RM32),
	I(0xa3, IF_MODRM|IF_REXW, "btq\t" OP_R64 OP_RM64),

	I(0xa4, IF_66|IF_MODRM,   "shldw\t" OP_RM16 OP_R16 OP_U8),
	I(0xa4, IF_MODRM,         "shldl\t" OP_RM32 OP_R32 OP_U8),
	I(0xa4, IF_MODRM|IF_REXW, "shldq\t" OP_RM64 OP_R64 OP_U8),

	I(0xa5, IF_66|IF_MODRM,   "shldw\t" OP_RM16 OP_R16 OP_CL),
	I(0xa5, IF_MODRM,         "shldl\t" OP_RM32 OP_R32 OP_CL),
	I(0xa5, IF_MODRM|IF_REXW, "shldq\t" OP_RM64 OP_R64 OP_CL),

	I(0xa8, IF_66,            "pushw\t" OP_GS),
	I(0xa8, IF_X32,           "pushl\t" OP_GS),
	I(0xa8, IF_X64,           "pushq\t" OP_GS),

	I(0xa9, IF_66,            "popw\t"  OP_GS),
	I(0xa9, IF_X32,           "popl\t"  OP_GS),
	I(0xa9, IF_X64,           "popq\t"  OP_GS),

	I(0xaa, 0,                "rsm"),

	I(0xab, IF_66|IF_MODRM,   "btsw\t" OP_R8 OP_RM8),
	I(0xab, IF_MODRM,         "btsl\t" OP_R16 OP_RM16),
	I(0xab, IF_MODRM|IF_REXW, "btsq\t" OP_R32 OP_RM32),

	I(0xac, IF_66|IF_MODRM,   "shrdw\t" OP_RM16 OP_R16 OP_U8),
	I(0xac, IF_MODRM,         "shrdl\t" OP_RM32 OP_R32 OP_U8),
	I(0xac, IF_MODRM|IF_REXW, "shrdq\t" OP_RM64 OP_R64 OP_U8),

	I(0xad, IF_66|IF_MODRM,   "shrdw\t" OP_RM16 OP_R16 OP_CL),
	I(0xad, IF_MODRM,         "shrdl\t" OP_RM32 OP_R32 OP_CL),
	I(0xad, IF_MODRM|IF_REXW, "shrdq\t" OP_RM64 OP_R64 OP_CL),

	I(0xae, IF_VEX|IF_MODRM|IF_RMM|IF_REG2, OP_VEX_B0(0,1,0,0) "vldmxcsr\t" OP_MEM),
	I(0xae, IF_VEX|IF_MODRM|IF_RMM|IF_REG3, OP_VEX_B0(0,1,0,0) "vstmxcsr\t" OP_MEM),
	I(0xae, IF_F3|IF_MODRM|IF_REG0,         "rdfsbasel\t" OP_RM32),
	I(0xae, IF_REXW|IF_F3|IF_MODRM|IF_REG0, "rdfsbaseq\t" OP_RM64),

	I(0xae, IF_F3|IF_MODRM|IF_REG1,         "rdgsbasel\t" OP_RM32),
	I(0xae, IF_REXW|IF_F3|IF_MODRM|IF_REG1, "rdgsbaseq\t" OP_RM64),

	I(0xae, IF_F3|IF_MODRM|IF_REG2,         "wrfsbasel\t" OP_RM32),
	I(0xae, IF_REXW|IF_F3|IF_MODRM|IF_REG2, "wrfsbaseq\t" OP_RM64),

	I(0xae, IF_F3|IF_MODRM|IF_REG3,         "wrgsbasel\t" OP_RM32),
	I(0xae, IF_REXW|IF_F3|IF_MODRM|IF_REG3, "wrgsbaseq\t" OP_RM64),

	I(0xae, IF_MODRM|IF_RMM|IF_REG0,        "fxsave\t" OP_MEM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG1,        "fxrstor\t" OP_MEM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG2,        "ldmxcsr\t" OP_MEM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG3,        "stmxcsr\t" OP_MEM),

	I(0xae, IF_MODRM|IF_RMM|IF_REG4,        "xsave\t" OP_MEM),
	I(0xae, IF_MODRM|IF_REXW|IF_RMM|IF_REG4,"xsave64\t" OP_MEM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG5,        "xrstor\t" OP_MEM),
	I(0xae, IF_MODRM|IF_REXW|IF_RMM|IF_REG5,"xrstor64\t" OP_MEM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG6,        "xsaveopt\t" OP_MEM),
	I(0xae, IF_MODRM|IF_REXW|IF_RMM|IF_REG6,"xsaveopt64\t" OP_MEM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG7,        "clflush\t" OP_MEM),
	I(0xae, IF_66|IF_MODRM|IF_RMM|IF_REG7,  "clflushopt\t" OP_RM32),

	I(0xae, IF_MODRM|IF_RMM|IF_REG0,         "fxsave\t" OP_MEM),
	I(0xae, IF_MODRM|IF_REXW|IF_RMM|IF_REG0, "fxsave64\t" OP_MEM),
	I(0xae, IF_MODRM|IF_RMM|IF_REG1,         "fxrstor\t" OP_MEM),
	I(0xae, IF_MODRM|IF_REXW|IF_RMM|IF_REG1, "fxrstor64\t" OP_MEM),

	I(0xae, IF_F3|IF_MODRM|IF_REG6|IF_RMR|IF_X32, "umonitorl\t" OP_RM32),
	I(0xae, IF_F3|IF_MODRM|IF_REG6|IF_RMR|IF_X64, "umonitorq\t" OP_RM64),
	I(0xae, IF_F2|IF_MODRM|IF_REG6,               "umwait\t" OP_EAX OP_EDX OP_RM32),

	I(0xae, IF_BYTE2,                "\xe8" "lfence"),
	I(0xae, IF_BYTE2,                "\xf0" "mfence"),
	I(0xae, IF_BYTE2,                "\xf8" "sfence"),

	I(0xaf, IF_66|IF_MODRM,  "imulb\t" OP_RM8 OP_R8),
	I(0xaf, IF_MODRM,        "imulw\t" OP_RM16 OP_R16),
	I(0xaf, IF_MODRM|IF_REXW,"imull\t" OP_RM32 OP_R32),

	I(0xb0, IF_MODRM,        "cmpxchgb\t" OP_R8 OP_RM8),
	I(0xb1, IF_66|IF_MODRM,  "cmpxchgw\t" OP_R16 OP_RM16),
	I(0xb1, IF_MODRM,        "cmpxchgl\t" OP_R32 OP_RM32),
	I(0xb1, IF_MODRM|IF_REXW,"cmpxchgq\t" OP_R64 OP_RM64),

	I(0xb2, IF_66|IF_MODRM|IF_RMM,  "lssw\t" OP_MEM/*32*/ OP_R16),
	I(0xb2, IF_MODRM|IF_RMM,        "lssl\t" OP_MEM/*48*/ OP_R32),
	I(0xb2, IF_MODRM|IF_REXW|IF_RMM,"lssq\t" OP_MEM/*80*/ OP_R64),

	I(0xb3, IF_66|IF_MODRM,  "btrw\t" OP_R16 OP_RM16),
	I(0xb3, IF_MODRM,        "btrl\t" OP_R32 OP_RM32),
	I(0xb3, IF_MODRM|IF_REXW,"btrq\t" OP_R64 OP_RM64),

	I(0xb4, IF_66|IF_MODRM|IF_RMM,  "lfsw\t" OP_MEM/*32*/ OP_R16),
	I(0xb4, IF_MODRM|IF_RMM,        "lfsl\t" OP_MEM/*48*/ OP_R32),
	I(0xb4, IF_MODRM|IF_REXW|IF_RMM,"lfsq\t" OP_MEM/*80*/ OP_R64),
	I(0xb5, IF_66|IF_MODRM|IF_RMM,  "lgsw\t" OP_MEM/*32*/ OP_R16),
	I(0xb5, IF_MODRM|IF_RMM,        "lgsl\t" OP_MEM/*48*/ OP_R32),
	I(0xb5, IF_MODRM|IF_REXW|IF_RMM,"lgsq\t" OP_MEM/*80*/ OP_R64),

	I(0xb6, IF_66|IF_MODRM,  "movzbw\t" OP_RM8 OP_R32),
	I(0xb6, IF_MODRM,        "movzbl\t" OP_RM8 OP_R32),
	I(0xb6, IF_MODRM|IF_REXW,"movzbq\t" OP_RM8 OP_R64),
	I(0xb7, IF_MODRM,        "movzwl\t" OP_RM16 OP_R32),
	I(0xb7, IF_MODRM|IF_REXW,"movzwq\t" OP_RM16 OP_R64),

	I(0xb8, IF_F3|IF_66|IF_MODRM,  "popcntw\t" OP_RM16 OP_R16),
	I(0xb8, IF_F3|IF_MODRM,        "popcntl\t" OP_RM32 OP_R32),
	I(0xb8, IF_F3|IF_MODRM|IF_REXW,"popcntq\t" OP_RM64 OP_R64),

	I(0xb9, IF_MODRM,        "ud1\t" OP_RM32 OP_R32),

	I(0xba, IF_66|IF_MODRM|IF_REG4,"btw\t" OP_U8 OP_RM16),
	I(0xba, IF_MODRM|IF_REG4,"btl\t" OP_U8 OP_RM32),
	I(0xba, IF_MODRM|IF_REXW|IF_REG4,"btq\t" OP_U8 OP_RM64),

	I(0xba, IF_66|IF_MODRM|IF_REG5,"btsw\t" OP_U8 OP_RM16),
	I(0xba, IF_MODRM|IF_REG5,"btsl\t" OP_U8 OP_RM32),
	I(0xba, IF_MODRM|IF_REXW|IF_REG5,"btsq\t" OP_U8 OP_RM64),

	I(0xba, IF_66|IF_MODRM|IF_REG6,"btrw\t" OP_U8 OP_RM16),
	I(0xba, IF_MODRM|IF_REG6,"btrl\t" OP_U8 OP_RM32),
	I(0xba, IF_MODRM|IF_REXW|IF_REG6,"btrq\t" OP_U8 OP_RM64),

	I(0xba, IF_66|IF_MODRM|IF_REG7,"btcw\t" OP_U8 OP_RM16),
	I(0xba, IF_MODRM|IF_REG7,"btcl\t" OP_U8 OP_RM32),
	I(0xba, IF_MODRM|IF_REXW|IF_REG7,"btcq\t" OP_U8 OP_RM64),

	I(0xbb, IF_66|IF_MODRM,  "btcw\t" OP_R16 OP_RM16),
	I(0xbb, IF_MODRM,        "btcl\t" OP_R32 OP_RM32),
	I(0xbb, IF_MODRM|IF_REXW,"btcq\t" OP_R64 OP_RM64),

	I(0xbc, IF_66|IF_MODRM,  "bsfw\t" OP_RM16 OP_R16),
	I(0xbc, IF_MODRM,        "bsfl\t" OP_RM32 OP_R32),
	I(0xbc, IF_MODRM|IF_REXW,"bsfq\t" OP_RM64 OP_R64),

	I(0xbc, IF_F3|IF_66|IF_MODRM,  "tzcntw\t" OP_RM16 OP_R16),
	I(0xbc, IF_F3|IF_MODRM,        "tzcntl\t" OP_RM32 OP_R32),
	I(0xbc, IF_F3|IF_MODRM|IF_REXW,"tzcntq\t" OP_RM64 OP_R64),

	I(0xbd, IF_66|IF_MODRM,  "bsrw\t" OP_RM16 OP_R16),
	I(0xbd, IF_MODRM,        "bsrl\t" OP_RM32 OP_R32),
	I(0xbd, IF_MODRM|IF_REXW,"bsrq\t" OP_RM64 OP_R64),

	I(0xbd, IF_F3|IF_66|IF_MODRM,  "lzcntw\t" OP_RM16 OP_R16),
	I(0xbd, IF_F3|IF_MODRM,        "lzcntl\t" OP_RM32 OP_R32),
	I(0xbd, IF_F3|IF_MODRM|IF_REXW,"lzcntq\t" OP_RM64 OP_R64),

	I(0xbe, IF_66|IF_MODRM,  "movsbw\t" OP_RM8 OP_R32),
	I(0xbe, IF_MODRM,        "movsbl\t" OP_RM8 OP_R32),
	I(0xbe, IF_MODRM|IF_REXW,"movsbq\t" OP_RM8 OP_R64),

	I(0xbf, IF_MODRM,        "movswl\t" OP_RM16 OP_R32),
	I(0xbf, IF_MODRM|IF_REXW,"movswq\t" OP_RM16 OP_R64),

	I(0xc0, IF_MODRM,        "xaddb\t" OP_R8 OP_RM8),

	I(0xc1, IF_66|IF_MODRM,  "xaddw\t" OP_R16 OP_RM16),
	I(0xc1, IF_MODRM,        "xaddl\t" OP_R32 OP_RM32),
	I(0xc1, IF_MODRM|IF_REXW,"xaddq\t" OP_R64 OP_RM64),

	I(0xc2, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vcmpps\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM),  /*  VEX.128.0f.WIG c2 /r ib vcmpps xmm1, xmm2, xmm3/m128, imm8 */
	I(0xc2, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vcmpps\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM),  /*  VEX.256.0f.WIG c2 /r ib vcmpps ymm1, ymm2, ymm3/m256, imm8 */
	I(0xc2, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vcmpps\t" OP_U8 OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.0f.W0  c2 /r ib vcmpps k1{k2}, xmm2, xmm3/m128/m32bcst, imm8 */
	I(0xc2, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vcmpps\t" OP_U8 OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.256.0f.W0  c2 /r ib vcmpps k1{k2}, ymm2, ymm3/m256/m32bcst, imm8 */
	I(0xc2, IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VCMPPS)),                      /* EVEX.512.0f.W0  c2 /r ib vcmpps k1{k2}, zmm2, zmm3/m512/m32bcst{sae}, imm8 */

	I(0xc2, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vcmpss\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /*  VEX.LIG.f3.0f.WIG c2 /r ib vcmpss xmm1, xmm2, xmm3/m32, imm8 */
	I(0xc2, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VCMPSS)),                     /* EVEX.LIG.f3.0f.W0  c2 /r ib vcmpss k1{k2}, xmm2, xmm3/m32{sae}, imm8 */

	I(0xc2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vcmppd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM),  /*  VEX.128.66.0f.WIG c2 /r ib vcmppd xmm1, xmm2, xmm3/m128, imm8 */
	I(0xc2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vcmppd\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM),  /*  VEX.256.66.0f.WIG c2 /r ib vcmppd ymm1, ymm2, ymm3/m256, imm8 */
	I(0xc2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vcmppd\t" OP_U8 OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.66.0f.W1  c2 /r ib vcmppd k1{k2}, xmm2, xmm3/m128/m64bcst, imm8 */
	I(0xc2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vcmppd\t" OP_U8 OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.512.66.0f.W1  c2 /r ib vcmppd k1{k2}, ymm2, ymm3/m256/m64bcst, imm8 */
	I(0xc2, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VCMPPD)),                      /* EVEX.512.66.0f.W1  c2 /r ib vcmppd k1{k2}, zmm2, zmm3/m512/m64bcst{sae}, imm8 */

	I(0xc2, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vcmpsd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /*  VEX.LIG.f2.0f.WIG c2 /r ib vcmpsd xmm1, xmm2, xmm3/m64, imm8 */
	I(0xc2, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VCMPSD)),                     /* EVEX.LIG.f2.0f.W1  c2 /r ib vcmpsd k1{k2}, xmm2, xmm3/m64{sae}, imm8 */

	I(0xc2, IF_MODRM,       "cmpps\t" OP_U8 OP_RM128_XMM OP_RXMM), /*    0f c2 /r ib cmpps xmm1, xmm2/m128, imm8 */
	I(0xc2, IF_F3|IF_MODRM, "cmpss\t" OP_U8 OP_RM128_XMM OP_RXMM), /* f3 0f c2 /r ib cmpss xmm1, xmm2/m32, imm8 */
	I(0xc2, IF_66|IF_MODRM, "cmppd\t" OP_U8 OP_RM128_XMM OP_RXMM), /* 66 0f c2 /r ib cmppd xmm1, xmm2/m128, imm8 */
	I(0xc2, IF_F2|IF_MODRM, "cmpsd\t" OP_U8 OP_RM128_XMM OP_RXMM), /* f2 0f c2 /r ib cmpsd xmm1, xmm2/m64, imm8 */

	I(0xc3, IF_MODRM|IF_RMM,        "movntil\t" OP_R32 OP_RM32),
	I(0xc3, IF_MODRM|IF_REXW|IF_RMM,"movntiq\t" OP_R64 OP_RM64),

	I(0xc4, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 0), LO_VPINSRW)), /*  VEX.128.66.0f.W0  c4 /r ib vpinsrw xmm1, xmm2, r32/m16, imm8 */
	I(0xc4, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPINSRW)), /* EVEX.128.66.0f.WIG c4 /r ib vpinsrw xmm1, xmm2, r32/m16, imm8 */
	I(0xc4, IF_MODRM,              "pinsrw\t" OP_U8 OP_RM32 OP_RMM),                 /*                 0f c4 /r ib pinsrw mm, r32/m16, imm8 */
	I(0xc4, IF_66|IF_MODRM,        "pinsrw\t" OP_U8 OP_RM32 OP_RXMM),                /*              66 0f c4 /r ib pinsrw xmm, r32/m16, imm8 */

	I(0xc5, IF_66|IF_VEX|IF_MODRM|IF_RMR,         OP_VEX_B0(1, 0, 0, 0) "vpextrw\t" OP_U8 OP_RM128_XMM OP_R32), /*  VEX.128.66.0f.W0  c5 /r ib vpextrw r32, xmm1, imm8 */
	I(0xc5, IF_66|IF_VEX|IF_MODRM|IF_RMR|IF_REXW, OP_VEX_B0(1, 0, 0, 0) "vpextrw\t" OP_U8 OP_RM128_XMM OP_R64), /*  VEX.128.66.0f.W0  c5 /r ib vpextrw r64, xmm1, imm8 */
	I(0xc5, IF_66|IF_VEX|IF_MODRM|IF_RMR,         OP_VEX_B0(0, 1, 0, 0) "vpextrw\t" OP_U8 OP_RM128_XMM OP_R32), /* EVEX.128.66.0f.WIG c5 /r ib vpextrw r32, xmm1, imm8 */
	I(0xc5, IF_66|IF_VEX|IF_MODRM|IF_RMR|IF_REXW, OP_VEX_B0(0, 1, 0, 0) "vpextrw\t" OP_U8 OP_RM128_XMM OP_R64), /* EVEX.128.66.0f.WIG c5 /r ib vpextrw r64, xmm1, imm8 */
	I(0xc5, IF_MODRM|IF_RMR,                                            "pextrw\t" OP_U8 OP_RM64_MM OP_R32),    /*                 0f c5 /r ib pextrw r32, mm, imm8 */
	I(0xc5, IF_MODRM|IF_RMR|IF_REXW,                                    "pextrw\t" OP_U8 OP_RM64_MM OP_R64),    /*                 0f c5 /r ib pextrw r64, mm, imm8 */
	I(0xc5, IF_66|IF_MODRM|IF_RMR,                                      "pextrw\t" OP_U8 OP_RM128_XMM OP_R32),  /*              66 0f c5 /r ib pextrw r32, xmm, imm8 */
	I(0xc5, IF_66|IF_MODRM|IF_RMR|IF_REXW,                              "pextrw\t" OP_U8 OP_RM128_XMM OP_R64),  /*              66 0f c5 /r ib pextrw r64, xmm, imm8 */

	I(0xc6, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vshufps\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.0f.WIG c6 /r ib vshufps xmm1, xmm2, xmm3/m128, imm8 */
	I(0xc6, IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vshufps\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.0f.WIG c6 /r ib vshufps ymm1, ymm2, ymm3/m256, imm8 */
	I(0xc6, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vshufps\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.0f.W0  c6 /r ib vshufps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst, imm8 */
	I(0xc6, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vshufps\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.0f.W0  c6 /r ib vshufps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst, imm8 */
	I(0xc6, IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vshufps\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.0f.W0  c6 /r ib vshufps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst, imm8 */
	I(0xc6, IF_MODRM,                              "shufps\t" OP_U8 OP_RM128_XMM OP_RXMM),                  /*              0f c6 /r ib shufps xmm1, xmm3/m128, imm8 */

	I(0xc6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vshufpd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG c6 /r ib vshufpd xmm1, xmm2, xmm3/m128, imm8 */
	I(0xc6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vshufpd\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG c6 /r ib vshufpd ymm1, ymm2, ymm3/m256, imm8 */
	I(0xc6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vshufpd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  c6 /r ib vshufpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst, imm8 */
	I(0xc6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vshufpd\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  c6 /r ib vshufpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst, imm8 */
	I(0xc6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vshufpd\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  c6 /r ib vshufpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst, imm8 */
	I(0xc6, IF_66|IF_MODRM,                              "shufpd\t" OP_U8 OP_RM128_XMM OP_RXMM),                  /*              66 0f c6 /r ib shufpd xmm1, xmm2/m128, imm8 */

	I(0xc7, IF_X32|IF_MODRM|IF_RMM|IF_REG1,       "cmpxchg8b\t" OP_MEM),
	I(0xc7, IF_X64|IF_MODRM|IF_RMM|IF_REG1,       "cmpxchg16b\t" OP_MEM),

	I(0xc7, IF_MODRM|IF_RMM|IF_REG4,              "xsavec\t" OP_MEM),
	I(0xc7, IF_MODRM|IF_REXW|IF_RMM|IF_REG4,      "xsavec64\t" OP_MEM),

	I(0xc7, IF_MODRM|IF_RMM|IF_REG5,              "xsaves\t" OP_MEM),
	I(0xc7, IF_MODRM|IF_REXW|IF_RMM|IF_REG5,      "xsaves64\t" OP_MEM),

	I(0xc7, IF_MODRM|IF_RMM|IF_REG6,              "vmptrld\t" OP_RM64),
	I(0xc7, IF_66|IF_MODRM|IF_RMM|IF_REG6,        "vmclear\t" OP_RM64),
	I(0xc7, IF_F3|IF_MODRM|IF_RMM|IF_REG6,        "vmxon\t" OP_RM64),
	I(0xc7, IF_X32|IF_MODRM|IF_RMR|IF_REG6,       "rdrandl\t" OP_RM32),
	I(0xc7, IF_X64|IF_MODRM|IF_RMR|IF_REG6,       "rdrandq\t" OP_RM64),

	I(0xc7, IF_MODRM|IF_RMM|IF_RMM|IF_REG7,       "vmptrst\t" OP_MEM),
	I(0xc7, IF_X32|IF_MODRM|IF_RMR|IF_REG7,       "rdseedl\t" OP_RM32),
	I(0xc7, IF_X64|IF_MODRM|IF_RMR|IF_REG7,       "rdseedq\t" OP_RM64),
	I(0xc7, IF_X32|IF_F3|IF_MODRM|IF_RMR|IF_REG7, "rdpidl\t" OP_RM32),
	I(0xc7, IF_X64|IF_F3|IF_MODRM|IF_RMR|IF_REG7, "rdpidq\t" OP_RM64),

	I(0xc8, IF_REXB,         "bswapl\t" OP_R8D),
	I(0xc8, IF_REXB|IF_REXW, "bswapq\t" OP_X64_R8),
	I(0xc8, 0,               "bswapl\t" OP_EAX),
	I(0xc8, IF_REXW,         "bswapq\t" OP_RAX),
	I(0xc9, IF_REXB,         "bswapl\t" OP_R9D),
	I(0xc9, IF_REXB|IF_REXW, "bswapq\t" OP_R9),
	I(0xc9, 0,               "bswapl\t" OP_ECX),
	I(0xc9, IF_REXW,         "bswapq\t" OP_RCX),
	I(0xca, IF_REXB,         "bswapl\t" OP_R10D),
	I(0xca, IF_REXB|IF_REXW, "bswapq\t" OP_R10),
	I(0xca, 0,               "bswapl\t" OP_EDX),
	I(0xca, IF_REXW,         "bswapq\t" OP_RDX),
	I(0xcb, IF_REXB,         "bswapl\t" OP_R11D),
	I(0xcb, IF_REXB|IF_REXW, "bswapq\t" OP_R11),
	I(0xcb, 0,               "bswapl\t" OP_EBX),
	I(0xcb, IF_REXW,         "bswapq\t" OP_RBX),
	I(0xcc, IF_REXB,         "bswapl\t" OP_R12D),
	I(0xcc, IF_REXB|IF_REXW, "bswapq\t" OP_R12),
	I(0xcc, 0,               "bswapl\t" OP_ESP),
	I(0xcc, IF_REXW,         "bswapq\t" OP_RSP),
	I(0xcd, IF_REXB,         "bswapl\t" OP_R13D),
	I(0xcd, IF_REXB|IF_REXW, "bswapq\t" OP_R13),
	I(0xcd, 0,               "bswapl\t" OP_EBP),
	I(0xcd, IF_REXW,         "bswapq\t" OP_RBP),
	I(0xce, IF_REXB,         "bswapl\t" OP_R14D),
	I(0xce, IF_REXB|IF_REXW, "bswapq\t" OP_R14),
	I(0xce, 0,               "bswapl\t" OP_ESI),
	I(0xce, IF_REXW,         "bswapq\t" OP_RSI),
	I(0xcf, IF_REXB,         "bswapl\t" OP_R15D),
	I(0xcf, IF_REXB|IF_REXW, "bswapq\t" OP_R15),
	I(0xcf, 0,               "bswapl\t" OP_EDI),
	I(0xcf, IF_REXW,         "bswapq\t" OP_RDI),

	I(0xd0, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vaddsubpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f.WIG d0 /r vaddsubpd xmm1, xmm2, xmm3/m128 */
	I(0xd0, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vaddsubpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f.WIG d0 /r vaddsubpd ymm1, ymm2, ymm3/m256 */
	I(0xd0, IF_66|IF_MODRM,                              "addsubpd\t" OP_RM128_XMM OP_RXMM),             /*             66 0f d0 /r addsubpd xmm1, xmm2/m128 */

	I(0xd0, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vaddsubps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.f2.0f.WIG d0 /r vaddsubps xmm1, xmm2, xmm3/m128 */
	I(0xd0, IF_F2|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vaddsubps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.f2.0f.WIG d0 /r vaddsubps ymm1, ymm2, ymm3/m256 */
	I(0xd0, IF_F2|IF_MODRM,                              "addsubps\t" OP_RM128_XMM OP_RXMM),             /*             f2 0f d0 /r addsubps xmm1, xmm2/m128 */

	I(0xd1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsrlw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG d1 /r vpsrlw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xd1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsrlw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG d1 /r vpsrlw ymm1{k1}{z}, ymm2, xmm3/m128 */
	I(0xd1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsrlw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG d1 /r vpsrlw zmm1{k1}{z}, zmm2, xmm3/m128 */
	I(0xd1, IF_MODRM,                                    "psrlw\t" OP_RM64_MM OP_RMM),                     /*                 0f d1 /r psrlw mm, mm/m64 */
	I(0xd1, IF_66|IF_MODRM,                              "psrlw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f d1 /r psrlw xmm1, xmm2/m128 */

	I(0xd2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpsrld\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG d2 /r vpsrld xmm1, xmm2, xmm3/m128 */
	I(0xd2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpsrld\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG d2 /r vpsrld ymm1, ymm2, xmm3/m128 */
	I(0xd2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpsrld\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W0  d2 /r vpsrld xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xd2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpsrld\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.W0  d2 /r vpsrld ymm1{k1}{z}, ymm2, xmm3/m128 */
	I(0xd2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpsrld\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W0  d2 /r vpsrld zmm1{k1}{z}, zmm2, xmm3/m128 */
	I(0xd2, IF_MODRM,                                    "psrld\t" OP_RM64_MM OP_RMM),                     /*                 0f d2 /r psrld mm, mm/m64 */
	I(0xd2, IF_66|IF_MODRM,                              "psrld\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f d2 /r psrld xmm1, xmm2/m128 */

	I(0xd3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpsrlq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG d3 /r vpsrlq xmm1, xmm2, xmm3/m128 */
	I(0xd3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpsrlq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG d3 /r vpsrlq ymm1, ymm2, xmm3/m128 */
	I(0xd3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsrlq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  d3 /r vpsrlq xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xd3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsrlq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  d3 /r vpsrlq ymm1{k1}{z}, ymm2, xmm3/m128 */
	I(0xd3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsrlq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  d3 /r vpsrlq zmm1{k1}{z}, zmm2, xmm3/m128 */
	I(0xd3, IF_MODRM,                                    "psrlq\t" OP_RM64_MM OP_RMM),                     /*                 0f d3 /r psrlq mm, mm/m64 */
	I(0xd3, IF_66|IF_MODRM,                              "psrlq\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f d3 /r psrlq xmm1, xmm2/m128 */

	I(0xd4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpaddq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG d4 /r vpaddq xmm1, xmm2, xmm3/m128 */
	I(0xd4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpaddq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG d4 /r vpaddq ymm1, ymm2, ymm3/m256 */
	I(0xd4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpaddq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  d4 /r vpaddq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0xd4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpaddq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  d4 /r vpaddq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0xd4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpaddq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  d4 /r vpaddq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0xd4, IF_MODRM,                                    "paddq\t" OP_RM64_MM OP_RMM),                     /*                 0f d4 /r paddq mm, mm/m64 */
	I(0xd4, IF_66|IF_MODRM,                              "paddq\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f d4 /r paddq xmm1, xmm2/m128 */

	I(0xd5, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpmullw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xd5, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpmullw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xd5, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpmullw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xd5, IF_MODRM,              "pmullw\t" OP_RMM OP_RM64_MM),
	I(0xd5, IF_66|IF_MODRM,        "pmullw\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xd6, IF_F2|IF_MODRM|IF_RMR, "movdq2q\t" OP_RM128_XMM OP_RMM),
	I(0xd6, IF_F2|IF_MODRM|IF_RMR, "movq2dq\t" OP_RMM OP_RM128_XMM),

	I(0xd7, IF_66|IF_VEX|IF_MODRM,         LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVMSKB_XMM_R32)), /* VEX.128.66.0f.WIG d7 /r vpmovmskb r32, xmm1 */
	I(0xd7, IF_66|IF_VEX|IF_MODRM|IF_REXW, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVMSKB_XMM_R64)), /* VEX.128.66.0f.WIG d7 /r vpmovmskb r64, xmm1 */
	I(0xd7, IF_66|IF_VEX|IF_MODRM,         LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVMSKB_YMM_R32)), /* VEX.256.66.0f.WIG d7 /r vpmovmskb r32, ymm1 */
	I(0xd7, IF_66|IF_VEX|IF_MODRM|IF_REXW, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVMSKB_YMM_R64)), /* VEX.256.66.0f.WIG d7 /r vpmovmskb r64, ymm1 */
	I(0xd7, IF_MODRM|IF_RMR,               "pmovmskbl\t" OP_RMM OP_R32),                               /*                0f d7 /r pmovmskb r32, mm */
	I(0xd7, IF_MODRM|IF_RMR|IF_REXW,       "pmovmskbq\t" OP_RMM OP_R64),                               /*                0f d7 /r pmovmskb r64, mm */
	I(0xd7, IF_66|IF_MODRM|IF_RMR,         "pmovmskbl\t" OP_RXMM OP_R32),                              /*             66 0f d7 /r pmovmskb r32, xmm */
	I(0xd7, IF_66|IF_MODRM|IF_RMR|IF_REXW, "pmovmskbl\t" OP_RXMM OP_R64),                              /*             66 0f d7 /r pmovmskb r64, xmm */

	I(0xd8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsubusb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG d8 /r vpsubusb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xd8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsubusb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG d8 /r vpsubusb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xd8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsubusb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG d8 /r vpsubusb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xd8, IF_MODRM,                                    "psubusb\t" OP_RM64_MM OP_RMM),                     /*                 0f d8 /r psubusb mm, mm/m64 */
	I(0xd8, IF_66|IF_MODRM,                              "psubusb\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f d8 /r psubusb xmm1, xmm2/m128 */

	I(0xd9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsubusw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG d9 /r vpsubusw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xd9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsubusw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG d9 /r vpsubusw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xd9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsubusw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG d9 /r vpsubusw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xd9, IF_MODRM,                                    "psubusw\t" OP_RM64_MM OP_RMM),                     /*                 0f d9 /r psubusw mm, mm/m64 */
	I(0xd9, IF_66|IF_MODRM,                              "psubusw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f d9 /r psubusw xmm1, xmm2/m128 */

	I(0xda, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpminub\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG da /r vpminub xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xda, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpminub\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG da /r vpminub ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xda, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpminub\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG da /r vpminub zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xda, IF_MODRM,                                    "pminub\t" OP_RM64_MM OP_RMM),                     /*                 0f da /r pminub mm1, mm2/m64 */
	I(0xda, IF_66|IF_MODRM,                              "pminub\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f da /r pminub xmm1, xmm2/m128 */

	I(0xdb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpand\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xdb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpand\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xdb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpandd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xdb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpandd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xdb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpandd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xdb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpandq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xdb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpandq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xdb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpandq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xdb, IF_MODRM,              "pand\t" OP_RM64_MM OP_RMM),
	I(0xdb, IF_66|IF_MODRM,        "pand\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xdc, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpaddusb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xdc, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpaddusb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xdc, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpaddusb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xdc, IF_MODRM,              "paddusb\t" OP_RMM OP_RM64_MM),
	I(0xdc, IF_66|IF_MODRM,        "paddusb\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xdd, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpaddusw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xdd, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpaddusw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xdd, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpaddusw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xdd, IF_MODRM,              "paddusw\t" OP_RMM OP_RM64_MM),
	I(0xdd, IF_66|IF_MODRM,        "paddusw\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xde, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpmaxub\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG de /r vpmaxub xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xde, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpmaxub\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG de /r vpmaxub ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xde, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpmaxub\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG de /r vpmaxub zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xde, IF_MODRM,                                    "pmaxub\t" OP_RM64_MM OP_RMM),                     /*                 0f de /r pmaxub mm1, mm2/m64 */
	I(0xde, IF_66|IF_MODRM,                              "pmaxub\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f de /r pmaxub xmm1, xmm2/m128 */

	I(0xdf, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpandn\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xdf, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpandn\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xdf, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpandnd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xdf, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpandnd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xdf, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpandnd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xdf, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpandnq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xdf, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpandnq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xdf, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpandnq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xdf, IF_MODRM,              "pandn\t" OP_RM64_MM OP_RMM),
	I(0xdf, IF_66|IF_MODRM,        "pandn\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xe0, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpavgb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG e0 /r vpavgb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xe0, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpavgb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG e0 /r vpavgb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xe0, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpavgb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG e0 /r vpavgb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xe0, IF_MODRM,                                    "pavgb\t" OP_RM64_MM OP_RMM),                     /*                 0f e0 /r pavgb mm1, mm2/m64 */
	I(0xe0, IF_66|IF_MODRM,                              "pavgb\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f e0 /r pavgb xmm1, xmm2/m128 */

	I(0xe1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsraw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG e1 /r vpsraw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xe1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsraw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG e1 /r vpsraw ymm1{k1}{z}, ymm2, xmm3/m128 */
	I(0xe1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsraw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG e1 /r vpsraw zmm1{k1}{z}, zmm2, xmm3/m128 */
	I(0xe1, IF_MODRM,                                    "psraw\t" OP_RM64_MM OP_RMM),                     /*                 0f e1 /r psraw mm, mm/m64 */
	I(0xe1, IF_66|IF_MODRM,                              "psraw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f e1 /r psraw xmm1, xmm2/m128 */

	I(0xe2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpsrad\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG e2 /r vpsrad xmm1, xmm2, xmm3/m128 */
	I(0xe2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpsrad\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG e2 /r vpsrad ymm1, ymm2, xmm3/m128 */
	I(0xe2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpsrad\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W0  e2 /r vpsrad xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xe2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpsrad\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.W0  e2 /r vpsrad ymm1{k1}{z}, ymm2, xmm3/m128 */
	I(0xe2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpsrad\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W0  e2 /r vpsrad zmm1{k1}{z}, zmm2, xmm3/m128 */
	I(0xe2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsraq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  e2 /r vpsraq xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xe2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsraq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  e2 /r vpsraq ymm1{k1}{z}, ymm2, xmm3/m128 */
	I(0xe2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsraq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  e2 /r vpsraq zmm1{k1}{z}, zmm2, xmm3/m128 */
	I(0xe2, IF_MODRM,                                    "psrad\t" OP_RM64_MM OP_RMM),                     /*                 0f e2 /r psrad mm, mm/m64 */
	I(0xe2, IF_66|IF_MODRM,                              "psrad\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f e2 /r psrad xmm1, xmm2/m128 */

	I(0xe3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpavgw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG e3 /r vpavgw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xe3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpavgw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG e3 /r vpavgw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xe3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpavgw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG e3 /r vpavgw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xe3, IF_MODRM,                                    "pavgw\t" OP_RM64_MM OP_RMM),                     /*                 0f e3 /r pavgw mm1, mm2/m64 */
	I(0xe3, IF_66|IF_MODRM,                              "pavgw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f e3 /r pavgw xmm1, xmm2/m128 */

	I(0xe4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpmulhuw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG e4 /r vpmulhuw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xe4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpmulhuw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG e4 /r vpmulhuw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xe4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpmulhuw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG e4 /r vpmulhuw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xe4, IF_MODRM,                                    "pmulhuw\t" OP_RM64_MM OP_RMM),                     /*                 0f e4 /r pmulhuw mm1, mm2/m64 */
	I(0xe4, IF_66|IF_MODRM,                              "pmulhuw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f e4 /r pmulhuw xmm1, xmm2/m128 */

	I(0xe5, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpmulhw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xe5, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpmulhw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xe5, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpmulhw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xe5, IF_MODRM,              "pmulhw\t" OP_RMM OP_RM64_MM),
	I(0xe5, IF_66|IF_MODRM,        "pmulhw\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xe6, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VCVTDQ2PD_XMM)), /*  VEX.128.f3.0f.WIG e6 /r vcvtdq2pd xmm1, xmm2/m64 */
	I(0xe6, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VCVTDQ2PD_YMM)), /*  VEX.256.f3.0f.WIG e6 /r vcvtdq2pd ymm1, xmm2/m128 */
	I(0xe6, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VCVTDQ2PD_XMM)), /* EVEX.128.f3.0f.W0  e6 /r vcvtdq2pd xmm1{k1}{z}, xmm2/m128/m32bcst */
	I(0xe6, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VCVTDQ2PD_YMM)), /* EVEX.256.f3.0f.W0  e6 /r vcvtdq2pd ymm1{k1}{z}, xmm2/m128/m32bcst */
	I(0xe6, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VCVTDQ2PD_ZMM)), /* EVEX.512.f3.0f.W0  e6 /r vcvtdq2pd zmm1{k1}{z}, ymm2/m256/m32bcst */
	I(0xe6, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VCVTQQ2PD_XMM)), /* EVEX.128.f3.0f.W1  e6 /r vcvtqq2pd xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0xe6, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VCVTQQ2PD_YMM)), /* EVEX.256.f3.0f.W1  e6 /r vcvtqq2pd ymm1{k1}{z}, ymm2/m256/m64bcst */
	I(0xe6, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VCVTQQ2PD_ZMM)), /* EVEX.512.f3.0f.W1  e6 /r vcvtqq2pd zmm1{k1}{z}, zmm2/m512/m64bcst{er} */

	I(0xe6, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VCVTPD2DQ_XMM)), /*  VEX.128.f2.0f.WIG e6 /r vcvtpd2dq xmm1, xmm2/m128 */
	I(0xe6, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VCVTPD2DQ_YMM)), /*  VEX.256.f2.0f.WIG e6 /r vcvtpd2dq xmm1, ymm2/m256 */
	I(0xe6, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VCVTPD2DQ_XMM)), /* EVEX.128.f2.0f.W1  e6 /r vcvtpd2dq xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0xe6, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VCVTPD2DQ_YMM)), /* EVEX.256.f2.0f.W1  e6 /r vcvtpd2dq xmm1{k1}{z}, ymm2/m256/m64bcst */
	I(0xe6, IF_F2|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VCVTPD2DQ_ZMM)), /* EVEX.512.f2.0f.W1  e6 /r vcvtpd2dq ymm1{k1}{z}, zmm2/m512/m64bcst{er} */

	I(0xe6, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VCVTTPD2DQ_XMM)), /*  VEX.128.66.0f.WIG e6 /r vcvttpd2dq xmm1, xmm2/m128 */
	I(0xe6, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VCVTTPD2DQ_YMM)), /*  VEX.256.66.0f.WIG e6 /r vcvttpd2dq xmm1, ymm2/m256 */
	I(0xe6, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VCVTTPD2DQ_XMM)), /* EVEX.128.66.0f.W1  e6 /r vcvttpd2dq xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0xe6, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VCVTTPD2DQ_YMM)), /* EVEX.512.66.0f.W1  e6 /r vcvttpd2dq xmm1{k1}{z}, ymm2/m256/m64bcst */
	I(0xe6, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VCVTTPD2DQ_ZMM)), /* EVEX.512.66.0f.W1  e6 /r vcvttpd2dq ymm1{k1}{z}, zmm2/m512/m64bcst{sae} */

	I(0xe6, IF_F3|IF_MODRM, "cvtdq2pd\t" OP_RM128_XMM OP_RXMM),  /* f3 0f e6 /r cvtdq2pd xmm1, xmm2/m64 */
	I(0xe6, IF_F2|IF_MODRM, "cvtpd2dq\t" OP_RM128_XMM OP_RXMM),  /* f2 0f e6 /r cvtpd2dq xmm1, xmm2/m128 */
	I(0xe6, IF_66|IF_MODRM, "cvttpd2dq\t" OP_RM128_XMM OP_RXMM), /* 66 0f e6 /r cvttpd2dq xmm1, xmm2/m128 */

	I(0xe7, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 0) "vmovntdq\t" OP_RXMM OP_MEM), /*  VEX.128.66.0f.WIG e7 /r vmovntdq m128, xmm1 */
	I(0xe7, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(1, 1, 0, 1) "vmovntdq\t" OP_RYMM OP_MEM), /*  VEX.256.66.0f.WIG e7 /r vmovntdq m256, ymm1 */
	I(0xe7, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 0) "vmovntdq\t" OP_RXMM OP_MEM), /* EVEX.128.66.0f.W0  e7 /r vmovntdq m128, xmm1 */
	I(0xe7, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 1) "vmovntdq\t" OP_RYMM OP_MEM), /* EVEX.256.66.0f.W0  e7 /r vmovntdq m256, ymm1 */
	I(0xe7, IF_66|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 0, 0, 2) "vmovntdq\t" OP_RZMM OP_MEM), /* EVEX.512.66.0f.W0  e7 /r vmovntdq m512, zmm1 */
	I(0xe7, IF_66|IF_MODRM|IF_RMM,                              "movntdq\t" OP_RXMM OP_MEM),  /*              66 0f e7 /r movntdq m128, xmm1 */
	I(0xe7, IF_MODRM|IF_RMM,                                    "movntq\t" OP_RMM OP_MEM),

	I(0xe8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsubsb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG e8 /r vpsubsb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xe8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsubsb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG e8 /r vpsubsb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xe8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsubsb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG e8 /r vpsubsb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xe8, IF_MODRM,                                    "psubsb\t" OP_RM64_MM OP_RMM),                     /*                 0f e8 /r psubsb mm, mm/m64 */
	I(0xe8, IF_66|IF_MODRM,                              "psubsb\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f e8 /r psubsb xmm1, xmm2/m128 */

	I(0xe9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsubsw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG e9 /r vpsubsw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xe9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsubsw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG e9 /r vpsubsw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xe9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsubsw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG e9 /r vpsubsw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xe9, IF_MODRM,                                    "psubsw\t" OP_RM64_MM OP_RMM),                     /*                 0f e9 /r psubsw mm, mm/m64 */
	I(0xe9, IF_66|IF_MODRM,                              "psubsw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f e9 /r psubsw xmm1, xmm2/m128 */

	I(0xea, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpminsw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG ea /r vpminsw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xea, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpminsw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG ea /r vpminsw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xea, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpminsw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG ea /r vpminsw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xea, IF_MODRM,                                    "pminsw\t" OP_RM64_MM OP_RMM),                     /*                 0f ea /r pminsw mm1, mm2/m64 */
	I(0xea, IF_66|IF_MODRM,                              "pminsw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f ea /r pminsw xmm1, xmm2/m128 */

	I(0xeb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpor\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xeb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpor\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xeb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpord\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xeb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpord\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xeb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpord\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xeb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vporq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xeb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vporq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xeb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vporq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xeb, IF_MODRM,              "por\t" OP_RM64_MM OP_RMM),
	I(0xeb, IF_66|IF_MODRM,        "por\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xec, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpaddsb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG ec /r vpaddsb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xec, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpaddsb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG ec /r vpaddsb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xec, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpaddsb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG ec /r vpaddsb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xec, IF_MODRM,                                    "paddsb\t" OP_RM64_MM OP_RMM),                     /*                 0f ec /r paddsb mm, mm/m64 */
	I(0xec, IF_66|IF_MODRM,                              "paddsb\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f ec /r paddsb xmm1, xmm2/m128 */

	I(0xed, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpaddsw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG ed /r vpaddsw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xed, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpaddsw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG ed /r vpaddsw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xed, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpaddsw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG ed /r vpaddsw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xed, IF_MODRM,                                    "paddsw\t" OP_RM64_MM OP_RMM),                     /*                 0f ed /r paddsw mm, mm/m64 */
	I(0xed, IF_66|IF_MODRM,                              "paddsw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f ed /r paddsw xmm1, xmm2/m128 */

	I(0xee, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpmaxsw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG ee /r vpmaxsw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xee, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpmaxsw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG ee /r vpmaxsw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xee, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpmaxsw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG ee /r vpmaxsw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xee, IF_MODRM,                                    "pmaxsw\t" OP_RM64_MM OP_RMM),                     /*                 0f ee /r pmaxsw mm1, mm2/m64 */
	I(0xee, IF_66|IF_MODRM,                              "pmaxsw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f ee /r pmaxsw xmm1, xmm2/m128 */

	I(0xef, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpxor\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),       /*  VEX.128.66.0f.WIG ef /r vpxor xmm1, xmm2, xmm3/m128 */
	I(0xef, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpxor\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),       /*  VEX.256.66.0f.WIG ef /r vpxor ymm1, ymm2, ymm3/m256 */
	I(0xef, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpxord\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W0  ef /r vpxord xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0xef, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpxord\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.W0  ef /r vpxord ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0xef, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpxord\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W0  ef /r vpxord zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0xef, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpxorq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  ef /r vpxorq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0xef, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpxorq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  ef /r vpxorq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0xef, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpxorq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  ef /r vpxorq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0xef, IF_MODRM,                                    "pxor\t" OP_RM64_MM OP_RMM),                      /*                 0f ef /r pxor mm, mm/m64 */
	I(0xef, IF_66|IF_MODRM,                              "pxor\t" OP_RM128_XMM OP_RXMM),                   /*              66 0f ef /r pxor xmm1, xmm2/m128 */

	I(0xf0, IF_F2|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 1, 0, 0) "vlddqu\t" OP_MEM OP_RXMM), /* VEX.128.f2.0f.WIG f0 /r vlddqu xmm1, m128 */
	I(0xf0, IF_F2|IF_VEX|IF_MODRM|IF_RMM, OP_VEX_B0(0, 1, 0, 1) "vlddqu\t" OP_MEM OP_RYMM), /* VEX.256.f2.0f.WIG f0 /r vlddqu ymm1, m256 */
	I(0xf0, IF_F2|IF_MODRM|IF_RMM,                              "lddqu\t" OP_MEM OP_RXMM),  /*             f2 0f f0 /r lddqu xmm1, mem */

	I(0xf1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsllw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xf1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsllw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xf1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsllw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xf1, IF_MODRM,              "psllw\t" OP_RMM OP_RM64_MM),
	I(0xf1, IF_66|IF_MODRM,        "psllw\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xf2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpslld\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xf2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpslld\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xf2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpslld\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xf2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpslld\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xf2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpslld\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xf2, IF_MODRM,              "pslld\t" OP_RMM OP_RM64_MM),
	I(0xf2, IF_66|IF_MODRM,        "pslld\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xf3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpsllq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG f3 /r vpsllq xmm1, xmm2, xmm3/m128 */
	I(0xf3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpsllq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG f3 /r vpsllq ymm1, ymm2, xmm3/m128 */
	I(0xf3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsllq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  f3 /r vpsllq xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xf3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsllq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  f3 /r vpsllq ymm1{k1}{z}, ymm2, xmm3/m128 */
	I(0xf3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsllq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  f3 /r vpsllq zmm1{k1}{z}, zmm2, xmm3/m128 */
	I(0xf3, IF_MODRM,                                    "psllq\t" OP_RM64_MM OP_RMM),                     /*                 0f f3 /r psllq mm, mm/m64 */
	I(0xf3, IF_66|IF_MODRM,                              "psllq\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f f3 /r psllq xmm1, xmm2/m128 */

	I(0xf4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpmuludq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG f4 /r vpmuludq xmm1, xmm2, xmm3/m128 */
	I(0xf4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpmuludq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG f4 /r vpmuludq ymm1, ymm2, ymm3/m256 */
	I(0xf4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpmuludq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  f4 /r vpmuludq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0xf4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpmuludq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  f4 /r vpmuludq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0xf4, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpmuludq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  f4 /r vpmuludq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0xf4, IF_MODRM,                                    "pmuludq\t" OP_RM64_MM OP_RMM),                     /*                 0f f4 /r pmuludq mm1, mm2/m64 */
	I(0xf4, IF_66|IF_MODRM,                              "pmuludq\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f f4 /r pmuludq xmm1, xmm2/m128 */

	I(0xf5, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpmaddwd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),
	I(0xf5, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpmaddwd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),
	I(0xf5, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpmaddwd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),
	I(0xf5, IF_MODRM,              "pmaddwd\t" OP_RMM OP_RM64_MM),
	I(0xf5, IF_66|IF_MODRM,        "pmaddwd\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xf6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsadbw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* EVEX.128.66.0f.WIG f6 /r vpsadbw xmm1, xmm2, xmm3/m128 */
	I(0xf6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsadbw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* EVEX.256.66.0f.WIG f6 /r vpsadbw ymm1, ymm2, ymm3/m256 */
	I(0xf6, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsadbw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM), /* EVEX.512.66.0f.WIG f6 /r vpsadbw zmm1, zmm2, zmm3/m512 */
	I(0xf6, IF_MODRM,                                    "psadbw\t" OP_RM64_MM OP_RMM),                /*                 0f f6 /r psadbw mm1, mm2/m64 */
	I(0xf6, IF_66|IF_MODRM,                              "psadbw\t" OP_RM128_XMM OP_RXMM),             /*              66 0f f6 /r psadbw xmm1, xmm2/m128 */

	I(0xf7, IF_MODRM|IF_RMR,       "maskmovq\t" OP_RM64_MM OP_RMM),

	I(0xf7, IF_66|IF_VEX|IF_MODRM|IF_RMR, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VMASKMOVDQU)), /* VEX.128.66.0f.WIG f7 /r vmaskmovdqu xmm1, xmm2 */
	I(0xf7, IF_66|IF_MODRM|IF_RMR,        LONGREPR(LO_MASKMOVDQU)),                             /*             66 0f f7 /r maskmovdqu xmm1, xmm2 */

	I(0xf8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsubb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG f8 /r vpsubb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xf8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsubb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG f8 /r vpsubb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xf8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsubb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG f8 /r vpsubb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xf8, IF_MODRM,                                    "psubb\t" OP_RM64_MM OP_RMM),                     /*                 0f f8 /r psubb mm, mm/m64 */
	I(0xf8, IF_66|IF_MODRM,                              "psubb\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f f8 /r psubb xmm1, xmm2/m128 */

	I(0xf9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpsubw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG f9 /r vpsubw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xf9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpsubw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG f9 /r vpsubw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xf9, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpsubw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG f9 /r vpsubw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xf9, IF_MODRM,                                    "psubw\t" OP_RM64_MM OP_RMM),                     /*                 0f f9 /r psubw mm, mm/m64 */
	I(0xf9, IF_66|IF_MODRM,                              "psubw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f f9 /r psubw xmm1, xmm2/m128 */

	I(0xfa, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpsubd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG fa /r vpsubd xmm1, xmm2, xmm3/m128 */
	I(0xfa, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpsubd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG fa /r vpsubd ymm1, ymm2, ymm3/m256 */
	I(0xfa, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpsubd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W0  fa /r vpsubd xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0xfa, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpsubd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.W0  fa /r vpsubd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0xfa, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpsubd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W0  fa /r vpsubd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0xfa, IF_MODRM,                                    "psubd\t" OP_RM64_MM OP_RMM),                     /*                 0f fa /r psubd mm, mm/m64 */
	I(0xfa, IF_66|IF_MODRM,                              "psubd\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f fa /r psubd xmm1, xmm2/m128 */

	I(0xfb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpsubq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG fb /r vpsubq xmm1, xmm2, xmm3/m128 */
	I(0xfb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpsubq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG fb /r vpsubq ymm1, ymm2, ymm3/m256 */
	I(0xfb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsubq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W1  fb /r vpsubq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0xfb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsubq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.512.66.0f.W1  fb /r vpsubq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0xfb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsubq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W1  fb /r vpsubq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0xfb, IF_MODRM,                                    "psubq\t" OP_RM64_MM OP_RMM),                     /*                 0f fb /r psubq mm1, mm2/m64 */
	I(0xfb, IF_66|IF_MODRM,                              "psubq\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f fb /r psubq xmm1, xmm2/m128 */

	I(0xfc, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpaddb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG fc /r vpaddb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xfc, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpaddb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG fc /r vpaddb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xfc, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpaddb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG fc /r vpaddb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xfc, IF_MODRM,                                    "paddb\t" OP_RM64_MM OP_RMM),                     /*                 0f fc /r paddb mm, mm/m64 */
	I(0xfc, IF_66|IF_MODRM,                              "paddb\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f fc /r paddb xmm1, xmm2/m128 */

	I(0xfd, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpaddw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.WIG fd /r vpaddw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0xfd, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpaddw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.WIG fd /r vpaddw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0xfd, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpaddw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.WIG fd /r vpaddw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0xfd, IF_MODRM,                                    "paddw\t" OP_RM64_MM OP_RMM),                     /*                 0f fd /r paddw mm, mm/m64 */
	I(0xfd, IF_66|IF_MODRM,                              "paddw\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f fd /r paddw xmm1, xmm2/m128 */

	I(0xfe, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpaddd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f.WIG fe /r vpaddd xmm1, xmm2, xmm3/m128 */
	I(0xfe, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpaddd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f.WIG fe /r vpaddd ymm1, ymm2, ymm3/m256 */
	I(0xfe, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpaddd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f.W0  fe /r vpaddd xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0xfe, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpaddd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f.W0  fe /r vpaddd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0xfe, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpaddd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f.W0  fe /r vpaddd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0xfe, IF_MODRM,                                    "paddd\t" OP_RM64_MM OP_RMM),                     /*                 0f fe /r paddd mm, mm/m64 */
	I(0xfe, IF_66|IF_MODRM,                              "paddd\t" OP_RM128_XMM OP_RXMM),                  /*              66 0f fe /r paddd xmm1, xmm2/m128 */

	I(0xff, IF_MODRM,        "ud0\t" OP_RM32 OP_R32),

	I(0, 0, "")
/*[[[end:ops_0f]]]*/
};
/* clang-format on */

/* clang-format off */
PRIVATE struct instruction const ops_0f38[] = {
/*[[[start:ops_0f38]]]*/
	/* REMINDER: After adding/removing instructions from this table, you must run:
	 *           $ deemon -F kos/src/libdisasm/x86-db.h */

	/* 0x0f38XX */

	I(0x00, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpshufb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.WIG 00 /r vpshufb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x00, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpshufb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.WIG 00 /r vpshufb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x00, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpshufb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.WIG 00 /r vpshufb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x00, IF_MODRM,                                    "pshufb\t" OP_RM64_MM OP_RMM),                     /*                0f 38 00 /r pshufb mm1, mm2/m64 */
	I(0x00, IF_66|IF_MODRM,                              "pshufb\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 00 /r pshufb xmm1, xmm2/m128 */

	I(0x01, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vphaddw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG 01 /r vphaddw xmm1, xmm2, xmm3/m128 */
	I(0x01, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vphaddw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f38.WIG 01 /r vphaddw ymm1, ymm2, ymm3/m256 */
	I(0x01, IF_MODRM,                                    "phaddw\t" OP_RM64_MM OP_RMM),                /*               0f 38 01 /r phaddw mm1, mm2/m64 */
	I(0x01, IF_66|IF_MODRM,                              "phaddw\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 01 /r phaddw xmm1, xmm2/m128 */

	I(0x02, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vphaddd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG 02 /r vphaddd xmm1, xmm2, xmm3/m128 */
	I(0x02, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vphaddd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f38.WIG 02 /r vphaddd ymm1, ymm2, ymm3/m256 */
	I(0x02, IF_MODRM,                                    "phaddd\t" OP_RM64_MM OP_RMM),                /*               0f 38 02 /r phaddd mm1, mm2/m64 */
	I(0x02, IF_66|IF_MODRM,                              "phaddd\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 02 /r phaddd xmm1, xmm2/m128 */

	I(0x03, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vphaddsw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG 03 /r vphaddsw xmm1, xmm2, xmm3/m128 */
	I(0x03, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vphaddsw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f38.WIG 03 /r vphaddsw ymm1, ymm2, ymm3/m256 */
	I(0x03, IF_MODRM,                                    "phaddsw\t" OP_RM64_MM OP_RMM),                /*               0f 38 03 /r phaddsw mm1, mm2/m64 */
	I(0x03, IF_66|IF_MODRM,                              "phaddsw\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 03 /r phaddsw xmm1, xmm2/m128 */

	I(0x04, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMADDUBSW_XMM)), /* EVEX.128.66.0f38.WIG 04 /r vpmaddubsw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x04, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMADDUBSW_YMM)), /* EVEX.256.66.0f38.WIG 04 /r vpmaddubsw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x04, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMADDUBSW_ZMM)), /* EVEX.512.66.0f38.WIG 04 /r vpmaddubsw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x04, IF_MODRM,              "pmaddubsw\t" OP_RM64_MM OP_RMM),                        /*                0f 38 04 /r pmaddubsw mm1, mm2/m64 */
	I(0x04, IF_66|IF_MODRM,        "pmaddubsw\t" OP_RM128_XMM OP_RXMM),                     /*             66 0f 38 04 /r pmaddubsw xmm1, xmm2/m128 */

	I(0x05, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vphsubw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG 05 /r vphsubw xmm1, xmm2, xmm3/m128 */
	I(0x05, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vphsubw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f38.WIG 05 /r vphsubw ymm1, ymm2, ymm3/m256 */
	I(0x05, IF_MODRM,                                    "phsubw\t" OP_RM64_MM OP_RMM),                /*               0f 38 05 /r phsubw mm1, mm2/m64 */
	I(0x05, IF_66|IF_MODRM,                              "phsubw\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 05 /r phsubw xmm1, xmm2/m128 */

	I(0x06, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vphsubd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG 06 /r vphsubd xmm1, xmm2, xmm3/m128 */
	I(0x06, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vphsubd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f38.WIG 06 /r vphsubd ymm1, ymm2, ymm3/m256 */
	I(0x06, IF_MODRM,                                    "phsubd\t" OP_RM64_MM OP_RMM),                /*               0f 38 06 /r phsubd mm1, mm2/m64 */
	I(0x06, IF_66|IF_MODRM,                              "phsubd\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 06 /r phsubd xmm1, xmm2/m128 */

	I(0x07, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vphsubsw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG 07 /r vphsubsw xmm1, xmm2, xmm3/m128 */
	I(0x07, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vphsubsw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f38.WIG 07 /r vphsubsw ymm1, ymm2, ymm3/m256 */
	I(0x07, IF_MODRM,                                    "phsubsw\t" OP_RM64_MM OP_RMM),                /*               0f 38 07 /r phsubsw mm1, mm2/m64 */
	I(0x07, IF_66|IF_MODRM,                              "phsubsw\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 07 /r phsubsw xmm1, xmm2/m128 */

	I(0x08, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpsignb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG 08 /r vpsignb xmm1, xmm2, xmm3/m128 */
	I(0x08, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpsignb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f38.WIG 08 /r vpsignb ymm1, ymm2, ymm3/m256 */
	I(0x08, IF_MODRM,                                    "psignb\t" OP_RM64_MM OP_RMM),                /*               0f 38 08 /r psignb mm1, mm2/m64 */
	I(0x08, IF_66|IF_MODRM,                              "psignb\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 08 /r psignb xmm1, xmm2/m128 */

	I(0x09, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpsignw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG 09 /r vpsignw xmm1, xmm2, xmm3/m128 */
	I(0x09, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpsignw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f38.WIG 09 /r vpsignw ymm1, ymm2, ymm3/m256 */
	I(0x09, IF_MODRM,                                    "psignw\t" OP_RM64_MM OP_RMM),                /*               0f 38 09 /r psignw mm1, mm2/m64 */
	I(0x09, IF_66|IF_MODRM,                              "psignw\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 09 /r psignw xmm1, xmm2/m128 */

	I(0x0a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpsignd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG 0a /r vpsignd xmm1, xmm2, xmm3/m128 */
	I(0x0a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpsignd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f38.WIG 0a /r vpsignd ymm1, ymm2, ymm3/m256 */
	I(0x0a, IF_MODRM,                                    "psignd\t" OP_RM64_MM OP_RMM),                /*               0f 38 0a /r psignd mm1, mm2/m64 */
	I(0x0a, IF_66|IF_MODRM,                              "psignd\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 0a /r psignd xmm1, xmm2/m128 */

	I(0x0b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpmulhrsw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.WIG 0b /r vpmulhrsw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x0b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpmulhrsw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.WIG 0b /r vpmulhrsw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x0b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpmulhrsw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.WIG 0b /r vpmulhrsw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x0b, IF_MODRM,                                    "pmulhrsw\t" OP_RM64_MM OP_RMM),                     /*                0f 38 0b /r pmulhrsw mm1, mm2/m64 */
	I(0x0b, IF_66|IF_MODRM,                              "pmulhrsw\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 0b /r pmulhrsw xmm1, xmm2/m128 */

	I(0x0c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpermilps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 0c /r vpermilps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x0c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermilps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 0c /r vpermilps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x0c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermilps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 0c /r vpermilps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */

	I(0x0d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 0, 0, 0) "vpermilpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f38.W0 0d /r vpermilpd xmm1, xmm2, xmm3/m128 */
	I(0x0d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 0, 0, 1) "vpermilpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f38.W0 0d /r vpermilpd ymm1, ymm2, ymm3/m256 */
	I(0x0d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpermilpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 0d /r vpermilpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x0d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermilpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 0d /r vpermilpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x0d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermilpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 0d /r vpermilpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x0e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vtestps\t" OP_RM128_XMM OP_RXMM), /* VEX.128.66.0f38.W0 0e /r vtestps xmm1, xmm2/m128 */
	I(0x0e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vtestps\t" OP_RM256_YMM OP_RYMM), /* VEX.256.66.0f38.W0 0e /r vtestps ymm1, ymm2/m256 */

	I(0x0f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vtestpd\t" OP_RM128_XMM OP_RXMM), /* VEX.128.66.0f38.W0 0f /r vtestpd xmm1, xmm2/m128 */
	I(0x0f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vtestpd\t" OP_RM256_YMM OP_RYMM), /* VEX.256.66.0f38.W0 0f /r vtestpd ymm1, ymm2/m256 */

	I(0x10, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPMOVUSWB_XMM)), /* EVEX.128.f3.0f38.W0 10 /r vpmovuswb xmm1/m64{k1}{z}, xmm2 */
	I(0x10, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPMOVUSWB_YMM)), /* EVEX.256.f3.0f38.W0 10 /r vpmovuswb xmm1/m128{k1}{z}, ymm2 */
	I(0x10, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPMOVUSWB_ZMM)), /* EVEX.512.f3.0f38.W0 10 /r vpmovuswb ymm1/m256{k1}{z}, zmm2 */

	I(0x10, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsrlvw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 10 /r vpsrlvw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x10, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsrlvw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 10 /r vpsrlvw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x10, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsrlvw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 10 /r vpsrlvw zmm1{k1}{z}, zmm2, zmm3/m512 */

	I(0x10, IF_66|IF_MODRM, LONGREPR(LO_PBLENDVB)), /* 66 0f 38 10 /r pblendvb xmm1, xmm2/m128, <xmm0> */

	I(0x11, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPMOVUSDB_XMM)), /* EVEX.128.f3.0f38.W0 11 /r vpmovusdb xmm1/m32{k1}{z}, xmm2 */
	I(0x11, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPMOVUSDB_YMM)), /* EVEX.256.f3.0f38.W0 11 /r vpmovusdb xmm1/m64{k1}{z}, ymm2 */
	I(0x11, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPMOVUSDB_ZMM)), /* EVEX.512.f3.0f38.W0 11 /r vpmovusdb xmm1/m128{k1}{z}, zmm2 */

	I(0x11, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsravw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 11 /r vpsravw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x11, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsravw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 11 /r vpsravw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x11, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsravw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 11 /r vpsravw zmm1{k1}{z}, zmm2, zmm3/m512 */

	I(0x12, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPMOVUSQB_XMM)), /* EVEX.128.f3.0f38.W0 12 /r vpmovusqb xmm1/m16{k1}{z}, xmm2 */
	I(0x12, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPMOVUSQB_YMM)), /* EVEX.256.f3.0f38.W0 12 /r vpmovusqb xmm1/m32{k1}{z}, ymm2 */
	I(0x12, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPMOVUSQB_ZMM)), /* EVEX.512.f3.0f38.W0 12 /r vpmovusqb xmm1/m64{k1}{z}, zmm2 */

	I(0x12, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsllvw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 12 /r vpsllvw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x12, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsllvw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 12 /r vpsllvw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x12, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsllvw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 12 /r vpsllvw zmm1{k1}{z}, zmm2, zmm3/m512 */

	I(0x13, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPMOVUSDW_XMM)), /* EVEX.128.f3.0f38.W0 13 /r vpmovusdw xmm1/m64{k1}{z}, xmm2 */
	I(0x13, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPMOVUSDW_YMM)), /* EVEX.256.f3.0f38.W0 13 /r vpmovusdw xmm1/m128{k1}{z}, ymm2 */
	I(0x13, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPMOVUSDW_ZMM)), /* EVEX.512.f3.0f38.W0 13 /r vpmovusdw ymm1/m256{k1}{z}, zmm2 */

	I(0x13, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VCVTPH2PS_XMM)), /* EVEX.128.66.0f38.W0 13 /r vcvtph2ps xmm1{k1}{z}, xmm2/m64 */
	I(0x13, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VCVTPH2PS_YMM)), /* EVEX.256.66.0f38.W0 13 /r vcvtph2ps ymm1{k1}{z}, xmm2/m128 */
	I(0x13, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VCVTPH2PS_ZMM)), /* EVEX.512.66.0f38.W0 13 /r vcvtph2ps zmm1{k1}{z}, ymm2/m256{sae} */

	I(0x14, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPMOVUSQW_XMM)), /* EVEX.128.f3.0f38.W0 14 /r vpmovusqw xmm1/m32{k1}{z}, xmm2 */
	I(0x14, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPMOVUSQW_YMM)), /* EVEX.256.f3.0f38.W0 14 /r vpmovusqw xmm1/m64{k1}{z}, ymm2 */
	I(0x14, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPMOVUSQW_ZMM)), /* EVEX.512.f3.0f38.W0 14 /r vpmovusqw xmm1/m128{k1}{z}, zmm2 */

	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vprorvd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 14 /r vprorvd xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vprorvq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 14 /r vprorvq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vprorvd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 14 /r vprorvd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vprorvq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 14 /r vprorvq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vprorvd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 14 /r vprorvd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vprorvq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 14 /r vprorvq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x14, IF_66|IF_MODRM, LONGREPR(LO_BLENDVPS)), /* 66 0f 38 14 /r blendvps xmm1, xmm2/m128, <xmm0> */

	I(0x15, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPMOVUSQD_XMM)),        /* EVEX.128.f3.0f38.W0 15 /r vpmovusqd xmm1/m64{k1}{z}, xmm2 */
	I(0x15, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPMOVUSQD_YMM)),        /* EVEX.256.f3.0f38.W0 15 /r vpmovusqd xmm1/m128{k1}{z}, ymm2 */
	I(0x15, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPMOVUSQD_ZMM)),        /* EVEX.512.f3.0f38.W0 15 /r vpmovusqd ymm1/m256{k1}{z}, zmm2 */

	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vprolvd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 15 /r vprolvd xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vprolvq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 15 /r vprolvq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vprolvd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 15 /r vprolvd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vprolvq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 15 /r vprolvq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vprolvd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 15 /r vprolvd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vprolvq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 15 /r vprolvq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x15, IF_66|IF_MODRM, LONGREPR(LO_BLENDVPD)), /* 66 0f 38 15 /r blendvpd xmm1, xmm2/m128, <xmm0> */

	I(0x16, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 16 /r vpermpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x16, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 16 /r vpermpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x16, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 16 /r vpermps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x16, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 16 /r vpermps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */

	I(0x17, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vptest\t" OP_RM128_XMM OP_RXMM), /* VEX.128.66.0f38.WIG 17 /r vptest xmm1, xmm2/m128 */
	I(0x17, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vptest\t" OP_RM256_YMM OP_RYMM), /* VEX.256.66.0f38.WIG 17 /r vptest ymm1, ymm2/m256 */
	I(0x17, IF_66|IF_MODRM,                              "ptest\t" OP_RM128_XMM OP_RXMM),  /*            66 0f 38 17 /r ptest xmm1, xmm2/m128 */

	I(0x18, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 0), LO_VBROADCASTSS_XMM)),    /*  VEX.128.66.0f38.W0 18 /r vbroadcastss xmm1, xmm2/m32 */
	I(0x18, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 1), LO_VBROADCASTSS_YMM)),    /*  VEX.256.66.0f38.W0 18 /r vbroadcastss ymm1, xmm2/m32 */
	I(0x18, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VBROADCASTSS_XMM)),    /* EVEX.128.66.0f38.W0 18 /r vbroadcastss xmm1{k1}{z}, xmm2/m32 */
	I(0x18, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VBROADCASTSS_YMM)),    /* EVEX.256.66.0f38.W0 18 /r vbroadcastss ymm1{k1}{z}, xmm2/m32 */
	I(0x18, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VBROADCASTSS_ZMM)),    /* EVEX.512.66.0f38.W0 18 /r vbroadcastss zmm1{k1}{z}, xmm2/m32 */

	I(0x19, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 1), LO_VBROADCASTSD)),        /*  VEX.256.66.0f38.W0 19 /r vbroadcastsd ymm1, xmm2 */
	I(0x19, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VBROADCASTSD_YMM)),    /* EVEX.256.66.0f38.W1 19 /r vbroadcastsd ymm1{k1}{z}, xmm2/m64 */
	I(0x19, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VBROADCASTSD_ZMM)),    /* EVEX.512.66.0f38.W1 19 /r vbroadcastsd zmm1{k1}{z}, xmm2/m64 */
	I(0x19, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VBROADCASTF32X2_YMM)), /* EVEX.256.66.0f38.W0 19 /r vbroadcastf32x2 ymm1{k1}{z}, xmm2/m64 */
	I(0x19, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VBROADCASTF32X2_ZMM)), /* EVEX.512.66.0f38.W0 19 /r vbroadcastf32x2 zmm1{k1}{z}, xmm2/m64 */

	I(0x1a, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 1), LO_VBROADCASTF128)),      /*  VEX.256.66.0f38.W0 1a /r vbroadcastf128 ymm1, m128 */
	I(0x1a, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VBROADCASTF32X4_YMM)), /* EVEX.256.66.0f38.W0 1a /r vbroadcastf32x4 ymm1{k1}{z}, m128 */
	I(0x1a, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VBROADCASTF32X4_ZMM)), /* EVEX.512.66.0f38.W0 1a /r vbroadcastf32x4 zmm1{k1}{z}, m128 */
	I(0x1a, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VBROADCASTF64X2_YMM)), /* EVEX.256.66.0f38.W1 1a /r vbroadcastf64x2 ymm1{k1}{z}, m128 */
	I(0x1a, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VBROADCASTF64X2_ZMM)), /* EVEX.512.66.0f38.W1 1a /r vbroadcastf64x2 zmm1{k1}{z}, m128 */

	I(0x1b, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VBROADCASTF32X8_ZMM)), /* EVEX.512.66.0f38.W0 1b /r vbroadcastf32x8 zmm1{k1}{z}, m256 */
	I(0x1b, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VBROADCASTF64X4_ZMM)), /* EVEX.512.66.0f38.W1 1b /r vbroadcastf64x4 zmm1{k1}{z}, m256 */

	I(0x1c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpabsb\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f38.WIG 1c /r vpabsb xmm1{k1}{z}, xmm2/m128 */
	I(0x1c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpabsb\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f38.WIG 1c /r vpabsb ymm1{k1}{z}, ymm2/m256 */
	I(0x1c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpabsb\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f38.WIG 1c /r vpabsb zmm1{k1}{z}, zmm2/m512 */
	I(0x1c, IF_MODRM,                                    "pabsb\t" OP_RM64_MM OP_RMM),          /*                0f 38 1c /r pabsb mm1, mm2/m64 */
	I(0x1c, IF_66|IF_MODRM,                              "pabsb\t" OP_RM128_XMM OP_RXMM),       /*             66 0f 38 1c /r pabsb xmm1, xmm2/m128 */

	I(0x1d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpabsw\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f38.WIG 1d /r vpabsw xmm1{k1}{z}, xmm2/m128 */
	I(0x1d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpabsw\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f38.WIG 1d /r vpabsw ymm1{k1}{z}, ymm2/m256 */
	I(0x1d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpabsw\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f38.WIG 1d /r vpabsw zmm1{k1}{z}, zmm2/m512 */
	I(0x1d, IF_MODRM,                                    "pabsw\t" OP_RM64_MM OP_RMM),          /*                0f 38 1d /r pabsw mm1, mm2/m64 */
	I(0x1d, IF_66|IF_MODRM,                              "pabsw\t" OP_RM128_XMM OP_RXMM),       /*             66 0f 38 1d /r pabsw xmm1, xmm2/m128 */

	I(0x1e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpabsd\t" OP_RM128_XMM OP_RXMM),      /*  VEX.128.66.0f38.WIG 1e /r vpabsd xmm1, xmm2/m128 */
	I(0x1e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpabsd\t" OP_RM256_YMM OP_RYMM),      /*  VEX.256.66.0f38.WIG 1e /r vpabsd ymm1, ymm2/m256 */
	I(0x1e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpabsd\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f38.W0  1e /r vpabsd xmm1{k1}{z}, xmm2/m128/m32bcst */
	I(0x1e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpabsd\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f38.W0  1e /r vpabsd ymm1{k1}{z}, ymm2/m256/m32bcst */
	I(0x1e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpabsd\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f38.W0  1e /r vpabsd zmm1{k1}{z}, zmm2/m512/m32bcst */
	I(0x1e, IF_MODRM,                                    "pabsd\t" OP_RM64_MM OP_RMM),          /*                0f 38 1e /r pabsd mm1, mm2/m64 */
	I(0x1e, IF_66|IF_MODRM,                              "pabsd\t" OP_RM128_XMM OP_RXMM),       /*             66 0f 38 1e /r pabsd xmm1, xmm2/m128 */

	I(0x1f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpabsq\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f38.W1  1f /r vpabsq xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0x1f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpabsq\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f38.W1  1f /r vpabsq ymm1{k1}{z}, ymm2/m256/m64bcst */
	I(0x1f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpabsq\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f38.W1  1f /r vpabsq zmm1{k1}{z}, zmm2/m512/m64bcst */

	I(0x20, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovswb\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.f3.0f38.W0 20 /r vpmovswb xmm1/m64{k1}{z}, xmm2 */
	I(0x20, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovswb\t" OP_RYMM OP_RM128_XMM_MASK), /* EVEX.256.f3.0f38.W0 20 /r vpmovswb xmm1/m128{k1}{z}, ymm2 */
	I(0x20, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovswb\t" OP_RZMM OP_RM256_YMM_MASK), /* EVEX.512.f3.0f38.W0 20 /r vpmovswb ymm1/m256{k1}{z}, zmm2 */

	I(0x20, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVSXBW_RXMM)), /* EVEX.128.66.0f38.WIG 20 /r vpmovsxbw xmm1{k1}{z}, xmm2/m64 */
	I(0x20, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVSXBW_RYMM)), /* EVEX.256.66.0f38.WIG 20 /r vpmovsxbw ymm1{k1}{z}, xmm2/m128 */
	I(0x20, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVSXBW_RZMM)), /* EVEX.512.66.0f38.WIG 20 /r vpmovsxbw zmm1{k1}{z}, ymm2/m256 */
	I(0x20, IF_66|IF_MODRM,        "pmovsxbw\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 20 /r pmovsxbw xmm1, xmm2/m64 */

	I(0x21, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovsdb\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.f3.0f38.W0 21 /r vpmovsdb xmm1/m32{k1}{z}, xmm2 */
	I(0x21, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovsdb\t" OP_RYMM OP_RM128_XMM_MASK), /* EVEX.256.f3.0f38.W0 21 /r vpmovsdb xmm1/m64{k1}{z}, ymm2 */
	I(0x21, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovsdb\t" OP_RZMM OP_RM128_XMM_MASK), /* EVEX.512.f3.0f38.W0 21 /r vpmovsdb xmm1/m128{k1}{z}, zmm2 */

	I(0x21, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVSXBD_RXMM)), /* EVEX.128.66.0f38.WIG 21 /r vpmovsxbd xmm1{k1}{z}, xmm2/m32 */
	I(0x21, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVSXBD_RYMM)), /* EVEX.256.66.0f38.WIG 21 /r vpmovsxbd ymm1{k1}{z}, xmm2/m64 */
	I(0x21, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVSXBD_RZMM)), /* EVEX.512.66.0f38.WIG 21 /r vpmovsxbd zmm1{k1}{z}, xmm2/m128 */
	I(0x21, IF_66|IF_MODRM,        "pmovsxbd\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 21 /r pmovsxbd xmm1, xmm2/m32 */

	I(0x22, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovsqb\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.f3.0f38.W0 22 /r vpmovsqb xmm1/m16{k1}{z}, xmm2 */
	I(0x22, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovsqb\t" OP_RYMM OP_RM128_XMM_MASK), /* EVEX.256.f3.0f38.W0 22 /r vpmovsqb xmm1/m32{k1}{z}, ymm2 */
	I(0x22, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovsqb\t" OP_RZMM OP_RM128_XMM_MASK), /* EVEX.512.f3.0f38.W0 22 /r vpmovsqb xmm1/m64{k1}{z}, zmm2 */

	I(0x22, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVSXBQ_RXMM)), /* EVEX.128.66.0f38.WIG 22 /r vpmovsxbq xmm1{k1}{z}, xmm2/m16 */
	I(0x22, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVSXBQ_RYMM)), /* EVEX.256.66.0f38.WIG 22 /r vpmovsxbq ymm1{k1}{z}, xmm2/m32 */
	I(0x22, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVSXBQ_RZMM)), /* EVEX.512.66.0f38.WIG 22 /r vpmovsxbq zmm1{k1}{z}, xmm2/m64 */
	I(0x22, IF_66|IF_MODRM,        "pmovsxbq\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 22 /r pmovsxbq xmm1, xmm2/m16 */

	I(0x23, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovsdw\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.f3.0f38.W0 23 /r vpmovsdw xmm1/m64{k1}{z}, xmm2 */
	I(0x23, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovsdw\t" OP_RYMM OP_RM128_XMM_MASK), /* EVEX.256.f3.0f38.W0 23 /r vpmovsdw xmm1/m128{k1}{z}, ymm2 */
	I(0x23, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovsdw\t" OP_RZMM OP_RM256_YMM_MASK), /* EVEX.512.f3.0f38.W0 23 /r vpmovsdw ymm1/m256{k1}{z}, zmm2 */

	I(0x23, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVSXWD_RXMM)), /* EVEX.128.66.0f38.WIG 23 /r vpmovsxwd xmm1{k1}{z}, xmm2/m64 */
	I(0x23, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVSXWD_RYMM)), /* EVEX.256.66.0f38.WIG 23 /r vpmovsxwd ymm1{k1}{z}, xmm2/m128 */
	I(0x23, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVSXWD_RZMM)), /* EVEX.512.66.0f38.WIG 23 /r vpmovsxwd zmm1{k1}{z}, ymm2/m256 */
	I(0x23, IF_66|IF_MODRM,        "pmovsxwd\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 23 /r pmovsxwd xmm1, xmm2/m64 */

	I(0x24, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovsqw\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.f3.0f38.W0 24 /r vpmovsqw xmm1/m32{k1}{z}, xmm2 */
	I(0x24, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovsqw\t" OP_RYMM OP_RM128_XMM_MASK), /* EVEX.256.f3.0f38.W0 24 /r vpmovsqw xmm1/m64{k1}{z}, ymm2 */
	I(0x24, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovsqw\t" OP_RZMM OP_RM128_XMM_MASK), /* EVEX.512.f3.0f38.W0 24 /r vpmovsqw xmm1/m128{k1}{z}, zmm2 */

	I(0x24, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVSXWQ_RXMM)), /* EVEX.128.66.0f38.WIG 24 /r vpmovsxwq xmm1{k1}{z}, xmm2/m32 */
	I(0x24, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVSXWQ_RYMM)), /* EVEX.256.66.0f38.WIG 24 /r vpmovsxwq ymm1{k1}{z}, xmm2/m64 */
	I(0x24, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVSXWQ_RZMM)), /* EVEX.512.66.0f38.WIG 24 /r vpmovsxwq zmm1{k1}{z}, xmm2/m128 */
	I(0x24, IF_66|IF_MODRM,        "pmovsxwq\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 24 /r pmovsxwq xmm1, xmm2/m32 */

	I(0x25, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovsqd\t" OP_RXMM OP_RM128_XMM_MASK), /* EVEX.128.f3.0f38.W0 25 /r vpmovsqd xmm1/m64{k1}{z}, xmm2 */
	I(0x25, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovsqd\t" OP_RYMM OP_RM128_XMM_MASK), /* EVEX.256.f3.0f38.W0 25 /r vpmovsqd xmm1/m128{k1}{z}, ymm2 */
	I(0x25, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovsqd\t" OP_RZMM OP_RM256_YMM_MASK), /* EVEX.512.f3.0f38.W0 25 /r vpmovsqd ymm1/m256{k1}{z}, zmm2 */

	I(0x25, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VPMOVSXDQ_RXMM)), /*  VEX.128.66.0f38.WIG 25 /r vpmovsxdq xmm1, xmm2/m64 */
	I(0x25, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VPMOVSXDQ_RYMM)), /*  VEX.256.66.0f38.WIG 25 /r vpmovsxdq ymm1, xmm2/m128 */
	I(0x25, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPMOVSXDQ_RXMM)), /* EVEX.128.66.0f38.W0  25 /r vpmovsxdq xmm1{k1}{z}, xmm2/m64 */
	I(0x25, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPMOVSXDQ_RYMM)), /* EVEX.256.66.0f38.W0  25 /r vpmovsxdq ymm1{k1}{z}, xmm2/m128 */
	I(0x25, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPMOVSXDQ_RZMM)), /* EVEX.512.66.0f38.W0  25 /r vpmovsxdq zmm1{k1}{z}, ymm2/m256 */
	I(0x25, IF_66|IF_MODRM,        "pmovsxdq\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 25 /r pmovsxdq xmm1, xmm2/m64 */

	I(0x26, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPTESTMB_XMM)), /* EVEX.128.66.0f38.W0 26 /r vptestmb k2{k1}, xmm2, xmm3/m128 */
	I(0x26, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPTESTMB_YMM)), /* EVEX.256.66.0f38.W0 26 /r vptestmb k2{k1}, ymm2, ymm3/m256 */
	I(0x26, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPTESTMB_ZMM)), /* EVEX.512.66.0f38.W0 26 /r vptestmb k2{k1}, zmm2, zmm3/m512 */
	I(0x26, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPTESTMW_XMM)), /* EVEX.128.66.0f38.W1 26 /r vptestmw k2{k1}, xmm2, xmm3/m128 */
	I(0x26, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPTESTMW_YMM)), /* EVEX.256.66.0f38.W1 26 /r vptestmw k2{k1}, ymm2, ymm3/m256 */
	I(0x26, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPTESTMW_ZMM)), /* EVEX.512.66.0f38.W1 26 /r vptestmw k2{k1}, zmm2, zmm3/m512 */

	I(0x26, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPTESTNMB_XMM)), /* EVEX.128.f3.0f38.W0 26 /r vptestnmb k2{k1}, xmm2, xmm3/m128 */
	I(0x26, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPTESTNMB_YMM)), /* EVEX.256.f3.0f38.W0 26 /r vptestnmb k2{k1}, ymm2, ymm3/m256 */
	I(0x26, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPTESTNMB_ZMM)), /* EVEX.512.f3.0f38.W0 26 /r vptestnmb k2{k1}, zmm2, zmm3/m512 */
	I(0x26, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPTESTNMW_XMM)), /* EVEX.128.f3.0f38.W1 26 /r vptestnmw k2{k1}, xmm2, xmm3/m128 */
	I(0x26, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPTESTNMW_YMM)), /* EVEX.256.f3.0f38.W1 26 /r vptestnmw k2{k1}, ymm2, ymm3/m256 */
	I(0x26, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPTESTNMW_ZMM)), /* EVEX.512.f3.0f38.W1 26 /r vptestnmw k2{k1}, zmm2, zmm3/m512 */

	I(0x27, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPTESTMD_XMM)), /* EVEX.128.66.0f38.W0 27 /r vptestmd k2{k1}, xmm2, xmm3/m128/m32bcst */
	I(0x27, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPTESTMD_YMM)), /* EVEX.256.66.0f38.W0 27 /r vptestmd k2{k1}, ymm2, ymm3/m256/m32bcst */
	I(0x27, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPTESTMD_ZMM)), /* EVEX.512.66.0f38.W0 27 /r vptestmd k2{k1}, zmm2, zmm3/m512/m32bcst */
	I(0x27, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPTESTMQ_XMM)), /* EVEX.128.66.0f38.W1 27 /r vptestmq k2{k1}, xmm2, xmm3/m128/m64bcst */
	I(0x27, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPTESTMQ_YMM)), /* EVEX.256.66.0f38.W1 27 /r vptestmq k2{k1}, ymm2, ymm3/m256/m64bcst */
	I(0x27, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPTESTMQ_ZMM)), /* EVEX.512.66.0f38.W1 27 /r vptestmq k2{k1}, zmm2, zmm3/m512/m64bcst */

	I(0x27, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPTESTNMD_XMM)), /* EVEX.128.f3.0f38.W0 27 /r vptestnmd k2{k1}, xmm2, xmm3/m128/m32bcst */
	I(0x27, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPTESTNMD_YMM)), /* EVEX.256.f3.0f38.W0 27 /r vptestnmd k2{k1}, ymm2, ymm3/m256/m32bcst */
	I(0x27, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPTESTNMD_ZMM)), /* EVEX.512.f3.0f38.W0 27 /r vptestnmd k2{k1}, zmm2, zmm3/m512/m32bcst */
	I(0x27, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPTESTNMQ_XMM)), /* EVEX.128.f3.0f38.W1 27 /r vptestnmq k2{k1}, xmm2, xmm3/m128/m64bcst */
	I(0x27, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPTESTNMQ_YMM)), /* EVEX.256.f3.0f38.W1 27 /r vptestnmq k2{k1}, ymm2, ymm3/m256/m64bcst */
	I(0x27, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPTESTNMQ_ZMM)), /* EVEX.512.f3.0f38.W1 27 /r vptestnmq k2{k1}, zmm2, zmm3/m512/m64bcst */

	I(0x28, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "vpmovm2b\t" OP_RMK OP_RXMM), /* EVEX.128.f3.0f38.W0 28 /r vpmovm2b xmm1, k1 */
	I(0x28, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 1) "vpmovm2b\t" OP_RMK OP_RYMM), /* EVEX.256.f3.0f38.W0 28 /r vpmovm2b ymm1, k1 */
	I(0x28, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 2) "vpmovm2b\t" OP_RMK OP_RZMM), /* EVEX.512.f3.0f38.W0 28 /r vpmovm2b zmm1, k1 */
	I(0x28, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 0) "vpmovm2w\t" OP_RMK OP_RXMM), /* EVEX.128.f3.0f38.W1 28 /r vpmovm2w xmm1, k1 */
	I(0x28, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 1) "vpmovm2w\t" OP_RMK OP_RYMM), /* EVEX.256.f3.0f38.W1 28 /r vpmovm2w ymm1, k1 */
	I(0x28, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 2) "vpmovm2w\t" OP_RMK OP_RZMM), /* EVEX.512.f3.0f38.W1 28 /r vpmovm2w zmm1, k1 */

	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpmuldq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f38.WIG 28 /r vpmuldq xmm1, xmm2, xmm3/m128 */
	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpmuldq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f38.WIG 28 /r vpmuldq ymm1, ymm2, ymm3/m256 */
	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpmuldq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1  28 /r vpmuldq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpmuldq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1  28 /r vpmuldq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x28, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpmuldq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1  28 /r vpmuldq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x28, IF_66|IF_MODRM,                              "pmuldq\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 28 /r pmuldq xmm1, xmm2/m128 */

	I(0x29, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "vpmovb2m\t" OP_RM128_XMM OP_RK), /* EVEX.128.f3.0f38.W0 29 /r vpmovb2m k1, xmm1 */
	I(0x29, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 1) "vpmovb2m\t" OP_RM256_YMM OP_RK), /* EVEX.256.f3.0f38.W0 29 /r vpmovb2m k1, ymm1 */
	I(0x29, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 2) "vpmovb2m\t" OP_RM512_ZMM OP_RK), /* EVEX.512.f3.0f38.W0 29 /r vpmovb2m k1, zmm1 */
	I(0x29, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 0) "vpmovw2m\t" OP_RM128_XMM OP_RK), /* EVEX.128.f3.0f38.W1 29 /r vpmovw2m k1, xmm1 */
	I(0x29, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 1) "vpmovw2m\t" OP_RM256_YMM OP_RK), /* EVEX.256.f3.0f38.W1 29 /r vpmovw2m k1, ymm1 */
	I(0x29, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 2) "vpmovw2m\t" OP_RM512_ZMM OP_RK), /* EVEX.512.f3.0f38.W1 29 /r vpmovw2m k1, zmm1 */

	I(0x29, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpcmpeqq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),  /*  VEX.128.66.0f38.WIG 29 /r vpcmpeqq xmm1, xmm2, xmm3/m128 */
	I(0x29, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpcmpeqq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),  /*  VEX.256.66.0f38.WIG 29 /r vpcmpeqq ymm1, ymm2, ymm3 /m256 */
	I(0x29, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPCMPEQQ_RXMM)),               /* EVEX.128.66.0f38.W1  29 /r vpcmpeqq k1{k2}, xmm2, xmm3/m128/m64bcst */
	I(0x29, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPCMPEQQ_RYMM)),               /* EVEX.256.66.0f38.W1  29 /r vpcmpeqq k1{k2}, ymm2, ymm3/m256/m64bcst */
	I(0x29, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPCMPEQQ_RZMM)),               /* EVEX.512.66.0f38.W1  29 /r vpcmpeqq k1{k2}, zmm2, zmm3/m512/m64bcst */
	I(0x29, IF_66|IF_MODRM,        "pcmpeqq\t" OP_RM128_XMM OP_RXMM),                                    /*             66 0f 38 29 /r pcmpeqq xmm1, xmm2/m128 */

	I(0x2a, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPBROADCASTMB2Q_XMM)), /* EVEX.128.f3.0f38.W1 2a /r vpbroadcastmb2q xmm1, k1 */
	I(0x2a, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPBROADCASTMB2Q_YMM)), /* EVEX.256.f3.0f38.W1 2a /r vpbroadcastmb2q ymm1, k1 */
	I(0x2a, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPBROADCASTMB2Q_ZMM)), /* EVEX.512.f3.0f38.W1 2a /r vpbroadcastmb2q zmm1, k1 */

	I(0x2a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VMOVNTDQA_XMM)), /*  VEX.128.66.0f38.WIG 2a /r vmovntdqa xmm1, m128 */
	I(0x2a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VMOVNTDQA_YMM)), /*  VEX.256.66.0f38.WIG 2a /r vmovntdqa ymm1, m256 */
	I(0x2a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VMOVNTDQA_XMM)), /* EVEX.128.66.0f38.W0  2a /r vmovntdqa xmm1, m128 */
	I(0x2a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VMOVNTDQA_YMM)), /* EVEX.256.66.0f38.W0  2a /r vmovntdqa ymm1, m256 */
	I(0x2a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VMOVNTDQA_ZMM)), /* EVEX.512.66.0f38.W0  2a /r vmovntdqa zmm1, m512 */
	I(0x2a, IF_66|IF_MODRM,        "movntdqa\t" OP_MEM OP_RXMM),                           /*             66 0f 38 2a /r movntdqa xmm1, m128 */

	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpackusdw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /* VEX.128.66.0f38.WIG 2b /r vpackusdw xmm1, xmm2, xmm3/m128 */
	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpackusdw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /* VEX.256.66.0f38.WIG 2b /r vpackusdw ymm1, ymm2, ymm3/m256 */
	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpackusdw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 2b /r vpackusdw xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpackusdw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 2b /r vpackusdw ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x2b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpackusdw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 2b /r vpackusdw zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x2b, IF_66|IF_MODRM,                              "packusdw\t" OP_RM128_XMM OP_RXMM),                  /*            66 0f 38 2b /r packusdw xmm1, xmm2/m128 */

	I(0x2c, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 0), LO_VMASKMOVPS_XMM)),                         /*  VEX.128.66.0f38.W0 2c /r vmaskmovps xmm1, xmm2, m128 */
	I(0x2c, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 1), LO_VMASKMOVPS_YMM)),                         /*  VEX.256.66.0f38.W0 2c /r vmaskmovps ymm1, ymm2, m256 */
	I(0x2c, IF_66|IF_VEX|IF_MODRM,              OP_VEX_B0(0, 0, 1, 0) "vscalefpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 2c /r vscalefpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x2c, IF_66|IF_VEX|IF_MODRM,              OP_VEX_B0(0, 0, 1, 1) "vscalefpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 2c /r vscalefpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x2c, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VSCALEFPD)),                                 /* EVEX.512.66.0f38.W1 2c /r vscalefpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{er} */
	I(0x2c, IF_66|IF_VEX|IF_MODRM,              OP_VEX_B0(0, 0, 0, 0) "vscalefps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 2c /r vscalefps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x2c, IF_66|IF_VEX|IF_MODRM,              OP_VEX_B0(0, 0, 0, 1) "vscalefps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 2c /r vscalefps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x2c, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VSCALEFPS)),                                 /* EVEX.512.66.0f38.W0 2c /r vscalefps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{er} */

	I(0x2d, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 0), LO_VMASKMOVPD_XMM)), /*  VEX.128.66.0f38.W0 2d /r vmaskmovpd xmm1, xmm2, m128 */
	I(0x2d, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 1), LO_VMASKMOVPD_YMM)), /*  VEX.256.66.0f38.W0 2d /r vmaskmovpd ymm1, ymm2, m256 */
	I(0x2d, IF_66|IF_VEX|IF_MODRM,        LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VSCALEFSD)), /* EVEX.LIG.66.0f38.W1 2d /r vscalefsd xmm1{k1}{z}, xmm2, xmm3/m64{er} */
	I(0x2d, IF_66|IF_VEX|IF_MODRM,        LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VSCALEFSS)), /* EVEX.LIG.66.0f38.W0 2d /r vscalefss xmm1{k1}{z}, xmm2, xmm3/m32{er} */

	I(0x2e, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VMASKMOVPS_XMM_REV)), /* VEX.128.66.0f38.W0 2e /r vmaskmovps m128, xmm1, xmm2 */
	I(0x2e, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VMASKMOVPS_YMM_REV)), /* VEX.256.66.0f38.W0 2e /r vmaskmovps m256, ymm1, ymm2 */

	I(0x2f, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VMASKMOVPD_XMM_REV)), /* VEX.128.66.0f38.W0 2f /r vmaskmovpd m128, xmm1, xmm2 */
	I(0x2f, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VMASKMOVPD_YMM_REV)), /* VEX.256.66.0f38.W0 2f /r vmaskmovpd m256, ymm1, ymm2 */

	I(0x30, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovwb\t" OP_RXMM OP_RM128_XMM_MASK),  /* EVEX.128.f3.0f38.W0 30 /r vpmovwb xmm1/m64{k1}{z}, xmm2 */
	I(0x30, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovwb\t" OP_RYMM OP_RM128_XMM_MASK),  /* EVEX.256.f3.0f38.W0 30 /r vpmovwb xmm1/m128{k1}{z}, ymm2 */
	I(0x30, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovwb\t" OP_RZMM OP_RM256_YMM_MASK),  /* EVEX.512.f3.0f38.W0 30 /r vpmovwb ymm1/m256{k1}{z}, zmm2 */

	I(0x30, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVZXBW_RXMM)), /* EVEX.128.66.0f38.WIG 30 /r vpmovzxbw xmm1{k1}{z}, xmm2/m64 */
	I(0x30, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVZXBW_RYMM)), /* EVEX.256.66.0f38.WIG 30 /r vpmovzxbw ymm1{k1}{z}, xmm2/m128 */
	I(0x30, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVZXBW_RZMM)), /* EVEX.512.66.0f38.WIG 30 /r vpmovzxbw zmm1{k1}{z}, ymm2/m256 */
	I(0x30, IF_66|IF_MODRM,        "pmovzxbw\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 30 /r pmovzxbw xmm1, xmm2/m64 */

	I(0x31, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovdb\t" OP_RXMM OP_RM128_XMM_MASK),  /* EVEX.128.f3.0f38.W0 31 /r vpmovdb xmm1/m32{k1}{z}, xmm2 */
	I(0x31, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovdb\t" OP_RYMM OP_RM128_XMM_MASK),  /* EVEX.256.f3.0f38.W0 31 /r vpmovdb xmm1/m64{k1}{z}, ymm2 */
	I(0x31, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovdb\t" OP_RZMM OP_RM128_XMM_MASK),  /* EVEX.512.f3.0f38.W0 31 /r vpmovdb xmm1/m128{k1}{z}, zmm2 */

	I(0x31, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVZXBD_RXMM)), /* EVEX.128.66.0f38.WIG 31 /r vpmovzxbd xmm1{k1}{z}, xmm2/m32 */
	I(0x31, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVZXBD_RYMM)), /* EVEX.256.66.0f38.WIG 31 /r vpmovzxbd ymm1{k1}{z}, xmm2/m64 */
	I(0x31, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVZXBD_RZMM)), /* EVEX.512.66.0f38.WIG 31 /r vpmovzxbd zmm1{k1}{z}, xmm2/m128 */
	I(0x31, IF_66|IF_MODRM,        "pmovzxbd\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 31 /r pmovzxbd xmm1, xmm2/m32 */

	I(0x32, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovqb\t" OP_RXMM OP_RM128_XMM_MASK),  /* EVEX.128.f3.0f38.W0 32 /r vpmovqb xmm1/m16{k1}{z}, xmm2 */
	I(0x32, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovqb\t" OP_RYMM OP_RM128_XMM_MASK),  /* EVEX.256.f3.0f38.W0 32 /r vpmovqb xmm1/m32{k1}{z}, ymm2 */
	I(0x32, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovqb\t" OP_RZMM OP_RM128_XMM_MASK),  /* EVEX.512.f3.0f38.W0 32 /r vpmovqb xmm1/m64{k1}{z}, zmm2 */

	I(0x32, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVZXBQ_RXMM)), /* EVEX.128.66.0f38.WIG 32 /r vpmovzxbq xmm1{k1}{z}, xmm2/m16 */
	I(0x32, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVZXBQ_RYMM)), /* EVEX.256.66.0f38.WIG 32 /r vpmovzxbq ymm1{k1}{z}, xmm2/m32 */
	I(0x32, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVZXBQ_RZMM)), /* EVEX.512.66.0f38.WIG 32 /r vpmovzxbq zmm1{k1}{z}, xmm2/m64 */
	I(0x32, IF_66|IF_MODRM,        "pmovzxbq\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 32 /r pmovzxbq xmm1, xmm2/m16 */

	I(0x33, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovdw\t" OP_RXMM OP_RM128_XMM_MASK),  /* EVEX.128.f3.0f38.W0 33 /r vpmovdw xmm1/m64{k1}{z}, xmm2 */
	I(0x33, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovdw\t" OP_RYMM OP_RM128_XMM_MASK),  /* EVEX.256.f3.0f38.W0 33 /r vpmovdw xmm1/m128{k1}{z}, ymm2 */
	I(0x33, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovdw\t" OP_RZMM OP_RM256_YMM_MASK),  /* EVEX.512.f3.0f38.W0 33 /r vpmovdw ymm1/m256{k1}{z}, zmm2 */

	I(0x33, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVZXWD_RXMM)), /* EVEX.128.66.0f38.WIG 33 /r vpmovzxwd xmm1{k1}{z}, xmm2/m64 */
	I(0x33, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVZXWD_RYMM)), /* EVEX.256.66.0f38.WIG 33 /r vpmovzxwd ymm1{k1}{z}, xmm2/m128 */
	I(0x33, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVZXWD_RZMM)), /* EVEX.512.66.0f38.WIG 33 /r vpmovzxwd zmm1{k1}{z}, ymm2/m256 */
	I(0x33, IF_66|IF_MODRM,        "pmovzxwd\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 33 /r pmovzxwd xmm1, xmm2/m64 */

	I(0x34, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovqw\t" OP_RXMM OP_RM128_XMM_MASK),  /* EVEX.128.f3.0f38.W0 34 /r vpmovqw xmm1/m32{k1}{z}, xmm2 */
	I(0x34, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovqw\t" OP_RYMM OP_RM128_XMM_MASK),  /* EVEX.256.f3.0f38.W0 34 /r vpmovqw xmm1/m64{k1}{z}, ymm2 */
	I(0x34, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovqw\t" OP_RZMM OP_RM128_XMM_MASK),  /* EVEX.512.f3.0f38.W0 34 /r vpmovqw xmm1/m128{k1}{z}, zmm2 */

	I(0x34, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPMOVZXWQ_RXMM)), /* EVEX.128.66.0f38.WIG 34 /r vpmovzxwq xmm1{k1}{z}, xmm2/m32 */
	I(0x34, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 1), LO_VPMOVZXWQ_RYMM)), /* EVEX.256.66.0f38.WIG 34 /r vpmovzxwq ymm1{k1}{z}, xmm2/m64 */
	I(0x34, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 2), LO_VPMOVZXWQ_RZMM)), /* EVEX.512.66.0f38.WIG 34 /r vpmovzxwq zmm1{k1}{z}, xmm2/m128 */
	I(0x34, IF_66|IF_MODRM,        "pmovzxwq\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 34 /r pmovzxwq xmm1, xmm2/m32 */

	I(0x35, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmovqd\t" OP_RXMM OP_RM128_XMM_MASK),  /* EVEX.128.f3.0f38.W0 35 /r vpmovqd xmm1/m128{k1}{z}, xmm2 */
	I(0x35, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmovqd\t" OP_RYMM OP_RM128_XMM_MASK),  /* EVEX.256.f3.0f38.W0 35 /r vpmovqd xmm1/m128{k1}{z}, ymm2 */
	I(0x35, IF_F3|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmovqd\t" OP_RZMM OP_RM256_YMM_MASK),  /* EVEX.512.f3.0f38.W0 35 /r vpmovqd ymm1/m256{k1}{z}, zmm2 */

	I(0x35, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VPMOVZXDQ_RXMM)), /*  VEX.128.66.0f38.WIG 35 /r vpmovzxdq xmm1, xmm2/m64 */
	I(0x35, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VPMOVZXDQ_RYMM)), /*  VEX.256.66.0f38.WIG 35 /r vpmovzxdq ymm1, xmm2/m128 */
	I(0x35, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPMOVZXDQ_RXMM)), /* EVEX.128.66.0f38.W0  35 /r vpmovzxdq xmm1{k1}{z}, xmm2/m64 */
	I(0x35, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPMOVZXDQ_RYMM)), /* EVEX.256.66.0f38.W0  35 /r vpmovzxdq ymm1{k1}{z}, xmm2/m128 */
	I(0x35, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPMOVZXDQ_RZMM)), /* EVEX.512.66.0f38.W0  35 /r vpmovzxdq zmm1{k1}{z}, ymm2/m256 */
	I(0x35, IF_66|IF_MODRM,        "pmovzxdq\t" OP_RM128_XMM OP_RXMM),                      /*             66 0f 38 35 /r pmovzxdq xmm1, xmm2/m64 */

	I(0x36, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 36 /r vpermq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x36, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 36 /r vpermq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x36, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 36 /r vpermd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x36, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 36 /r vpermd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */

	I(0x37, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpcmpgtq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /*  VEX.128.66.0f38.WIG 37 /r vpcmpgtq xmm1, xmm2, xmm3/m128 */
	I(0x37, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpcmpgtq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM), /*  VEX.256.66.0f38.WIG 37 /r vpcmpgtq ymm1, ymm2, ymm3/m256 */
	I(0x37, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPCMPGTQ_XMM)),               /* EVEX.128.66.0f38.W1  37 /r vpcmpgtq k1{k2}, xmm2, xmm3/m128/m64bcst */
	I(0x37, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPCMPGTQ_YMM)),               /* EVEX.256.66.0f38.W1  37 /r vpcmpgtq k1{k2}, ymm2, ymm3/m256/m64bcst */
	I(0x37, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPCMPGTQ_ZMM)),               /* EVEX.512.66.0f38.W1  37 /r vpcmpgtq k1{k2}, zmm2, zmm3/m512/m64bcst */
	I(0x37, IF_66|IF_MODRM,                              "pcmpgtq\t" OP_RM128_XMM OP_RXMM),             /*             66 0f 38 37 /r pcmpgtq xmm1, xmm2/m128 */

	I(0x38, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "vpmovm2d\t" OP_RMK OP_RXMM), /* EVEX.128.f3.0f38.W0 38 /r vpmovm2d xmm1, k1 */
	I(0x38, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 1) "vpmovm2d\t" OP_RMK OP_RYMM), /* EVEX.256.f3.0f38.W0 38 /r vpmovm2d ymm1, k1 */
	I(0x38, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 2) "vpmovm2d\t" OP_RMK OP_RZMM), /* EVEX.512.f3.0f38.W0 38 /r vpmovm2d zmm1, k1 */
	I(0x38, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 0) "vpmovm2q\t" OP_RMK OP_RXMM), /* EVEX.128.f3.0f38.W1 38 /r vpmovm2q xmm1, k1 */
	I(0x38, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 1) "vpmovm2q\t" OP_RMK OP_RYMM), /* EVEX.256.f3.0f38.W1 38 /r vpmovm2q ymm1, k1 */
	I(0x38, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 2) "vpmovm2q\t" OP_RMK OP_RZMM), /* EVEX.512.f3.0f38.W1 38 /r vpmovm2q zmm1, k1 */

	I(0x38, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpminsb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.WIG 38 /r vpminsb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x38, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpminsb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.WIG 38 /r vpminsb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x38, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpminsb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.WIG 38 /r vpminsb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x38, IF_66|IF_MODRM,                              "pminsb\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 38 /r pminsb xmm1, xmm2/m128 */

	I(0x39, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 0) "vpmovd2m\t" OP_RM128_XMM OP_RK), /* EVEX.128.f3.0f38.W0 39 /r vpmovd2m k1, xmm1 */
	I(0x39, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 1) "vpmovd2m\t" OP_RM256_YMM OP_RK), /* EVEX.256.f3.0f38.W0 39 /r vpmovd2m k1, ymm1 */
	I(0x39, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 0, 2) "vpmovd2m\t" OP_RM512_ZMM OP_RK), /* EVEX.512.f3.0f38.W0 39 /r vpmovd2m k1, zmm1 */
	I(0x39, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 0) "vpmovq2m\t" OP_RM128_XMM OP_RK), /* EVEX.128.f3.0f38.W1 39 /r vpmovq2m k1, xmm1 */
	I(0x39, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 1) "vpmovq2m\t" OP_RM256_YMM OP_RK), /* EVEX.256.f3.0f38.W1 39 /r vpmovq2m k1, ymm1 */
	I(0x39, IF_F3|IF_VEX|IF_MODRM|IF_RMR, OP_VEX_B0(0, 0, 1, 2) "vpmovq2m\t" OP_RM512_ZMM OP_RK), /* EVEX.512.f3.0f38.W1 39 /r vpmovq2m k1, zmm1 */

	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpminsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f38.WIG 39 /r vpminsd xmm1, xmm2, xmm3/m128 */
	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpminsd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f38.WIG 39 /r vpminsd ymm1, ymm2, ymm3/m256 */
	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpminsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0  39 /r vpminsd xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpminsd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0  39 /r vpminsd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpminsd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0  39 /r vpminsd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpminsq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1  39 /r vpminsq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpminsq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1  39 /r vpminsq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x39, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpminsq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1  39 /r vpminsq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x39, IF_66|IF_MODRM,                              "pminsd\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 39 /r pminsd xmm1, xmm2/m128 */

	I(0x3a, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPBROADCASTMW2D_XMM)), /* EVEX.128.f3.0f38.W0 3a /r vpbroadcastmw2d xmm1, k1 */
	I(0x3a, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPBROADCASTMW2D_YMM)), /* EVEX.256.f3.0f38.W0 3a /r vpbroadcastmw2d ymm1, k1 */
	I(0x3a, IF_F3|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPBROADCASTMW2D_ZMM)), /* EVEX.512.f3.0f38.W0 3a /r vpbroadcastmw2d zmm1, k1 */

	I(0x3a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpminuw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.WIG 3a /r vpminuw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x3a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpminuw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.WIG 3a /r vpminuw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x3a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpminuw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.WIG 3a /r vpminuw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x3a, IF_66|IF_MODRM,                              "pminuw\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 3a /r pminuw xmm1, xmm2/m128 */

	I(0x3b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpminud\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f38.WIG 3b /r vpminud xmm1, xmm2, xmm3/m128 */
	I(0x3b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpminud\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f38.WIG 3b /r vpminud ymm1, ymm2, ymm3/m256 */
	I(0x3b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpminud\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0  3b /r vpminud xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x3b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpminud\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0  3b /r vpminud ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x3b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpminud\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0  3b /r vpminud zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x3b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpminuq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1  3b /r vpminuq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x3b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpminuq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1  3b /r vpminuq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x3b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpminuq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1  3b /r vpminuq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x3b, IF_66|IF_MODRM,                              "pminud\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 3b /r pminud xmm1, xmm2/m128 */

	I(0x3c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpmaxsb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.WIG 3c /r vpmaxsb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x3c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpmaxsb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.WIG 3c /r vpmaxsb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x3c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpmaxsb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.WIG 3c /r vpmaxsb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x3c, IF_66|IF_MODRM,                              "pmaxsb\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 3c /r pmaxsb xmm1, xmm2/m128 */

	I(0x3d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpmaxsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f38.WIG 3d /r vpmaxsd xmm1, xmm2, xmm3/m128 */
	I(0x3d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpmaxsd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f38.WIG 3d /r vpmaxsd ymm1, ymm2, ymm3/m256 */
	I(0x3d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmaxsd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0  3d /r vpmaxsd xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x3d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmaxsd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0  3d /r vpmaxsd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x3d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmaxsd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0  3d /r vpmaxsd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x3d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpmaxsq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1  3d /r vpmaxsq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x3d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpmaxsq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1  3d /r vpmaxsq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x3d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpmaxsq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1  3d /r vpmaxsq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x3d, IF_66|IF_MODRM,                              "pmaxsd\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 3d /r pmaxsd xmm1, xmm2/m128 */

	I(0x3e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpmaxuw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.WIG 3e /r vpmaxuw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x3e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpmaxuw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.WIG 3e /r vpmaxuw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x3e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpmaxuw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.WIG 3e /r vpmaxuw zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x3e, IF_66|IF_MODRM,                              "pmaxuw\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 3e /r pmaxuw xmm1, xmm2/m128 */

	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpmaxud\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f38.WIG 3f /r vpmaxud xmm1, xmm2, xmm3/m128 */
	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpmaxud\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f38.WIG 3f /r vpmaxud ymm1, ymm2, ymm3/m256 */
	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmaxud\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0  3f /r vpmaxud xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmaxud\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0  3f /r vpmaxud ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmaxud\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0  3f /r vpmaxud zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpmaxuq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1  3f /r vpmaxuq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpmaxuq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1  3f /r vpmaxuq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpmaxuq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1  3f /r vpmaxuq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x3f, IF_66|IF_MODRM,                              "pmaxud\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 3f /r pmaxud xmm1, xmm2/m128 */

	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vpmulld\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM),      /*  VEX.128.66.0f38.WIG 40 /r vpmulld xmm1, xmm2, xmm3/m128 */
	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vpmulld\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM),      /*  VEX.256.66.0f38.WIG 40 /r vpmulld ymm1, ymm2, ymm3/m256 */
	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpmulld\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0  40 /r vpmulld xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpmulld\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0  40 /r vpmulld ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpmulld\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0  40 /r vpmulld zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpmullq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1  40 /r vpmullq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpmullq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1  40 /r vpmullq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpmullq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1  40 /r vpmullq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x40, IF_66|IF_MODRM,                              "pmulld\t" OP_RM128_XMM OP_RXMM),                  /*             66 0f 38 40 /r pmulld xmm1, xmm2/m128 */

	I(0x41, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VPHMINPOSUW)), /* VEX.128.66.0f38.WIG 41 /r vphminposuw xmm1, xmm2/m128 */
	I(0x41, IF_66|IF_MODRM,        LONGREPR(LO_PHMINPOSUW)),                             /*            66 0f 38 41 /r phminposuw xmm1, xmm2/m128 */

	I(0x42, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VGETEXPPD_XMM)), /* EVEX.128.66.0f38.W1 42 /r vgetexppd xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0x42, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VGETEXPPD_YMM)), /* EVEX.256.66.0f38.W1 42 /r vgetexppd ymm1{k1}{z}, ymm2/m256/m64bcst */
	I(0x42, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VGETEXPPD_ZMM)), /* EVEX.512.66.0f38.W1 42 /r vgetexppd zmm1{k1}{z}, zmm2/m512/m64bcst{sae} */
	I(0x42, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VGETEXPPS_XMM)), /* EVEX.128.66.0f38.W0 42 /r vgetexpps xmm1{k1}{z}, xmm2/m128/m32bcst */
	I(0x42, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VGETEXPPS_YMM)), /* EVEX.256.66.0f38.W0 42 /r vgetexpps ymm1{k1}{z}, ymm2/m256/m32bcst */
	I(0x42, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VGETEXPPS_ZMM)), /* EVEX.512.66.0f38.W0 42 /r vgetexpps zmm1{k1}{z}, zmm2/m512/m32bcst{sae} */

	I(0x43, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VGETEXPSS)), /* EVEX.LIG.66.0f38.W0 43 /r vgetexpss xmm1{k1}{z}, xmm2, xmm3/m32{sae} */
	I(0x43, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VGETEXPSD)), /* EVEX.LIG.66.0f38.W1 43 /r vgetexpsd xmm1{k1}{z}, xmm2, xmm3/m64{sae} */

	I(0x44, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vplzcntd\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 44 /r vplzcntd xmm1{k1}{z}, xmm2/m128/m32bcst */
	I(0x44, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vplzcntd\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 44 /r vplzcntd ymm1{k1}{z}, ymm2/m256/m32bcst */
	I(0x44, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vplzcntd\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 44 /r vplzcntd zmm1{k1}{z}, zmm2/m512/m32bcst */
	I(0x44, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vplzcntq\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 44 /r vplzcntq xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0x44, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vplzcntq\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 44 /r vplzcntq ymm1{k1}{z}, ymm2/m256/m64bcst */
	I(0x44, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vplzcntq\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 44 /r vplzcntq zmm1{k1}{z}, zmm2/m512/m64bcst */

	I(0x45, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpsrlvd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 45 /r vpsrlvd xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x45, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpsrlvd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 45 /r vpsrlvd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x45, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpsrlvd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 45 /r vpsrlvd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x45, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsrlvq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 45 /r vpsrlvq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x45, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsrlvq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 45 /r vpsrlvq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x45, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsrlvq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 45 /r vpsrlvq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x46, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpsravd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 46 /r vpsravd xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x46, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpsravd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 46 /r vpsravd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x46, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpsravd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 46 /r vpsravd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x46, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsravq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 46 /r vpsravq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x46, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsravq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 46 /r vpsravq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x46, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsravq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 46 /r vpsravq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x47, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpsllvd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 47 /r vpsllvd xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x47, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpsllvd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 47 /r vpsllvd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x47, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpsllvd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 47 /r vpsllvd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x47, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpsllvq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 47 /r vpsllvq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x47, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpsllvq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 47 /r vpsllvq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x47, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpsllvq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 47 /r vpsllvq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x4c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vrcp14pd\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 4c /r vrcp14pd xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0x4c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vrcp14pd\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 4c /r vrcp14pd ymm1{k1}{z}, ymm2/m256/m64bcst */
	I(0x4c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vrcp14pd\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 4c /r vrcp14pd zmm1{k1}{z}, zmm2/m512/m64bcst */

	I(0x4c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vrcp14ps\t" OP_RM128_XMM OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 4c /r vrcp14ps xmm1{k1}{z}, xmm2/m128/m32bcst */
	I(0x4c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vrcp14ps\t" OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 4c /r vrcp14ps ymm1{k1}{z}, ymm2/m256/m32bcst */
	I(0x4c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vrcp14ps\t" OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 4c /r vrcp14ps zmm1{k1}{z}, zmm2/m512/m32bcst */

	I(0x4d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vrcp14sd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.66.0f38.W1 4d /r vrcp14sd xmm1{k1}{z}, xmm2, xmm3/m64 */

	I(0x4e, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VRSQRT14PD_XMM)), /* EVEX.128.66.0f38.W1 4e /r vrsqrt14pd xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0x4e, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VRSQRT14PD_YMM)), /* EVEX.256.66.0f38.W1 4e /r vrsqrt14pd ymm1{k1}{z}, ymm2/m256/m64bcst */
	I(0x4e, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VRSQRT14PD_ZMM)), /* EVEX.512.66.0f38.W1 4e /r vrsqrt14pd zmm1{k1}{z}, zmm2/m512/m64bcst */
	I(0x4e, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VRSQRT14PS_XMM)), /* EVEX.128.66.0f38.W0 4e /r vrsqrt14ps xmm1{k1}{z}, xmm2/m128/m32bcst */
	I(0x4e, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VRSQRT14PS_YMM)), /* EVEX.256.66.0f38.W0 4e /r vrsqrt14ps ymm1{k1}{z}, ymm2/m256/m32bcst */
	I(0x4e, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VRSQRT14PS_ZMM)), /* EVEX.512.66.0f38.W0 4e /r vrsqrt14ps zmm1{k1}{z}, zmm2/m512/m32bcst */

	I(0x4f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VRSQRT14SD)), /* EVEX.LIG.66.0f38.W1 4f /r vrsqrt14sd xmm1{k1}{z}, xmm2, xmm3/m64 */
	I(0x4f, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VRSQRT14SS)), /* EVEX.LIG.66.0f38.W0 4f /r vrsqrt14ss xmm1{k1}{z}, xmm2, xmm3/m32 */

	I(0x52, IF_F2|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VP4DPWSSD)), /* EVEX.512.f2.0f38.W0 52 /r vp4dpwssd zmm1{k1}{z}, zmm2+3, m128 */

	I(0x53, IF_F2|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VP4DPWSSDS)), /* EVEX.512.f2.0f38.W0 53 /r vp4dpwssds zmm1{k1}{z}, zmm2+3, m128 */

	I(0x58, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPBROADCASTD_XX)), /* EVEX.128.66.0f38.W0 58 /r vpbroadcastd xmm1{k1}{z}, xmm2/m32 */
	I(0x58, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPBROADCASTD_XY)), /* EVEX.256.66.0f38.W0 58 /r vpbroadcastd ymm1{k1}{z}, xmm2/m32 */
	I(0x58, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPBROADCASTD_XZ)), /* EVEX.512.66.0f38.W0 58 /r vpbroadcastd zmm1{k1}{z}, xmm2/m32 */

	I(0x59, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 0), LO_VPBROADCASTQ_XX)),    /*  VEX.128.66.0f38.W0 59 /r vpbroadcastq xmm1, xmm2/m64 */
	I(0x59, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 1), LO_VPBROADCASTQ_XY)),    /*  VEX.256.66.0f38.W0 59 /r vpbroadcastq ymm1, xmm2/m64 */
	I(0x59, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPBROADCASTQ_XX)),    /* EVEX.128.66.0f38.W1 59 /r vpbroadcastq xmm1{k1}{z}, xmm2/m64 */
	I(0x59, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPBROADCASTQ_XY)),    /* EVEX.256.66.0f38.W1 59 /r vpbroadcastq ymm1{k1}{z}, xmm2/m64 */
	I(0x59, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPBROADCASTQ_XZ)),    /* EVEX.512.66.0f38.W1 59 /r vpbroadcastq zmm1{k1}{z}, xmm2/m64 */
	I(0x59, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VBROADCASTI32X2_XX)), /* EVEX.128.66.0f38.W0 59 /r vbroadcasti32x2 xmm1{k1}{z}, xmm2/m64 */
	I(0x59, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VBROADCASTI32X2_XY)), /* EVEX.256.66.0f38.W0 59 /r vbroadcasti32x2 ymm1{k1}{z}, xmm2/m64 */
	I(0x59, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VBROADCASTI32X2_XZ)), /* EVEX.512.66.0f38.W0 59 /r vbroadcasti32x2 zmm1{k1}{z}, xmm2/m64 */

	I(0x5a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 1), LO_VBROADCASTI128)),     /*  VEX.256.66.0f38.W0 5a /r vbroadcasti128 ymm1, m128 */
	I(0x5a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VBROADCASTI32X4_XY)), /* EVEX.256.66.0f38.W0 5a /r vbroadcasti32x4 ymm1{k1}{z}, m128 */
	I(0x5a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VBROADCASTI32X4_XZ)), /* EVEX.512.66.0f38.W0 5a /r vbroadcasti32x4 zmm1{k1}{z}, m128 */
	I(0x5a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VBROADCASTI64X2_XY)), /* EVEX.256.66.0f38.W1 5a /r vbroadcasti64x2 ymm1{k1}{z}, m128 */
	I(0x5a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VBROADCASTI64X2_XZ)), /* EVEX.512.66.0f38.W1 5a /r vbroadcasti64x2 zmm1{k1}{z}, m128 */

	I(0x5b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VBROADCASTI32X8)), /* EVEX.512.66.0f38.W0 5b /r vbroadcasti32x8 zmm1{k1}{z}, m256 */
	I(0x5b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VBROADCASTI64X4)), /* EVEX.512.66.0f38.W1 5b /r vbroadcasti64x4 zmm1{k1}{z}, m256 */

	I(0x64, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpblendmd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 64 /r vpblendmd xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x64, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpblendmd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 64 /r vpblendmd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x64, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpblendmd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 64 /r vpblendmd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x64, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpblendmq\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 64 /r vpblendmq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x64, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpblendmq\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 64 /r vpblendmq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x64, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpblendmq\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 64 /r vpblendmq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x65, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vblendmpd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 65 /r vblendmpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x65, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vblendmpd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 65 /r vblendmpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x65, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vblendmpd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 65 /r vblendmpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */
	I(0x65, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vblendmps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 65 /r vblendmps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x65, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vblendmps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 65 /r vblendmps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x65, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vblendmps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 65 /r vblendmps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */

	I(0x66, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpblendmb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 66 /r vpblendmb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x66, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpblendmb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 66 /r vpblendmb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x66, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpblendmb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 66 /r vpblendmb zmm1{k1}{z}, zmm2, zmm3/m512 */
	I(0x66, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpblendmw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 66 /r vpblendmw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x66, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpblendmw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 66 /r vpblendmw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x66, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpblendmw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 66 /r vpblendmw zmm1{k1}{z}, zmm2, zmm3/m512 */

	I(0x75, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpermi2b\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 75 /r vpermi2b xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x75, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermi2b\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 75 /r vpermi2b ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x75, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermi2b\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 75 /r vpermi2b zmm1{k1}{z}, zmm2, zmm3/m512 */

	I(0x75, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpermi2w\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),  /* EVEX.128.66.0f38.W1 75 /r vpermi2w xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x75, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermi2w\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),  /* EVEX.256.66.0f38.W1 75 /r vpermi2w ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x75, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermi2w\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),  /* EVEX.512.66.0f38.W1 75 /r vpermi2w zmm1{k1}{z}, zmm2, zmm3/m512 */

	I(0x76, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpermi2d\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),  /* EVEX.128.66.0f38.W0 76 /r vpermi2d xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x76, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermi2d\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),  /* EVEX.256.66.0f38.W0 76 /r vpermi2d ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x76, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermi2d\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),  /* EVEX.512.66.0f38.W0 76 /r vpermi2d zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x76, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpermi2q\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),  /* EVEX.128.66.0f38.W1 76 /r vpermi2q xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x76, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermi2q\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),  /* EVEX.256.66.0f38.W1 76 /r vpermi2q ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x76, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermi2q\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),  /* EVEX.512.66.0f38.W1 76 /r vpermi2q zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x77, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpermi2ps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 77 /r vpermi2ps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x77, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermi2ps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 77 /r vpermi2ps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x77, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermi2ps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 77 /r vpermi2ps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x77, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpermi2pd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 77 /r vpermi2pd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x77, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermi2pd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 77 /r vpermi2pd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x77, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermi2pd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 77 /r vpermi2pd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x78, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPBROADCASTB_XX)), /* EVEX.128.66.0f38.W0 78 /r vpbroadcastb xmm1{k1}{z}, xmm2/m8 */
	I(0x78, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPBROADCASTB_XY)), /* EVEX.256.66.0f38.W0 78 /r vpbroadcastb ymm1{k1}{z}, xmm2/m8 */
	I(0x78, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPBROADCASTB_XZ)), /* EVEX.512.66.0f38.W0 78 /r vpbroadcastb zmm1{k1}{z}, xmm2/m8 */

	I(0x79, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPBROADCASTW_XX)), /* EVEX.128.66.0f38.W0 79 /r vpbroadcastw xmm1{k1}{z}, xmm2/m16 */
	I(0x79, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPBROADCASTW_XY)), /* EVEX.256.66.0f38.W0 79 /r vpbroadcastw ymm1{k1}{z}, xmm2/m16 */
	I(0x79, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPBROADCASTW_XZ)), /* EVEX.512.66.0f38.W0 79 /r vpbroadcastw zmm1{k1}{z}, xmm2/m16 */

	I(0x7a, IF_66|IF_VEX|IF_MODRM|IF_RMR, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPBROADCASTB_XMM)), /* EVEX.128.66.0f38.W0 7a /r vpbroadcastb xmm1{k1}{z}, r8 */
	I(0x7a, IF_66|IF_VEX|IF_MODRM|IF_RMR, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPBROADCASTB_YMM)), /* EVEX.256.66.0f38.W0 7a /r vpbroadcastb ymm1{k1}{z}, r8 */
	I(0x7a, IF_66|IF_VEX|IF_MODRM|IF_RMR, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPBROADCASTB_ZMM)), /* EVEX.512.66.0f38.W0 7a /r vpbroadcastb zmm1{k1}{z}, r8 */

	I(0x7b, IF_66|IF_VEX|IF_MODRM|IF_RMR, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPBROADCASTW_XMM)), /* EVEX.128.66.0f38.W0 7b /r vpbroadcastw xmm1{k1}{z}, r16 */
	I(0x7b, IF_66|IF_VEX|IF_MODRM|IF_RMR, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPBROADCASTW_YMM)), /* EVEX.256.66.0f38.W0 7b /r vpbroadcastw ymm1{k1}{z}, r16 */
	I(0x7b, IF_66|IF_VEX|IF_MODRM|IF_RMR, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPBROADCASTW_ZMM)), /* EVEX.512.66.0f38.W0 7b /r vpbroadcastw zmm1{k1}{z}, r16 */

	I(0x7c, IF_66|IF_VEX|IF_MODRM|IF_RMR, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPBROADCASTD_XMM)), /* EVEX.128.66.0f38.W0 7c /r vpbroadcastd xmm1{k1}{z}, r32 */
	I(0x7c, IF_66|IF_VEX|IF_MODRM|IF_RMR, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPBROADCASTD_YMM)), /* EVEX.256.66.0f38.W0 7c /r vpbroadcastd ymm1{k1}{z}, r32 */
	I(0x7c, IF_66|IF_VEX|IF_MODRM|IF_RMR, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPBROADCASTD_ZMM)), /* EVEX.512.66.0f38.W0 7c /r vpbroadcastd zmm1{k1}{z}, r32 */
	I(0x7c, IF_66|IF_VEX|IF_MODRM|IF_RMR, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPBROADCASTQ_XMM)), /* EVEX.128.66.0f38.W1 7c /r vpbroadcastq xmm1{k1}{z}, r64 */
	I(0x7c, IF_66|IF_VEX|IF_MODRM|IF_RMR, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPBROADCASTQ_YMM)), /* EVEX.256.66.0f38.W1 7c /r vpbroadcastq ymm1{k1}{z}, r64 */
	I(0x7c, IF_66|IF_VEX|IF_MODRM|IF_RMR, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPBROADCASTQ_ZMM)), /* EVEX.512.66.0f38.W1 7c /r vpbroadcastq zmm1{k1}{z}, r64 */

	I(0x7d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpermt2b\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 7d /r vpermt2b xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x7d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermt2b\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 7d /r vpermt2b ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x7d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermt2b\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 7d /r vpermt2b zmm1{k1}{z}, zmm2, zmm3/m512 */

	I(0x7d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpermt2w\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),  /* EVEX.128.66.0f38.W1 7d /r vpermt2w xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x7d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermt2w\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),  /* EVEX.256.66.0f38.W1 7d /r vpermt2w ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x7d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermt2w\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),  /* EVEX.512.66.0f38.W1 7d /r vpermt2w zmm1{k1}{z}, zmm2, zmm3/m512 */

	I(0x7e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpermt2d\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),  /* EVEX.128.66.0f38.W0 7e /r vpermt2d xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x7e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermt2d\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),  /* EVEX.256.66.0f38.W0 7e /r vpermt2d ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x7e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermt2d\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),  /* EVEX.512.66.0f38.W0 7e /r vpermt2d zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x7e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpermt2q\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK),  /* EVEX.128.66.0f38.W1 7e /r vpermt2q xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x7e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermt2q\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK),  /* EVEX.256.66.0f38.W1 7e /r vpermt2q ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x7e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermt2q\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK),  /* EVEX.512.66.0f38.W1 7e /r vpermt2q zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x7f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpermt2ps\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 7f /r vpermt2ps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x7f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermt2ps\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 7f /r vpermt2ps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x7f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermt2ps\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 7f /r vpermt2ps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst */
	I(0x7f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpermt2pd\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 7f /r vpermt2pd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x7f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermt2pd\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 7f /r vpermt2pd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x7f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermt2pd\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 7f /r vpermt2pd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x80, IF_X32|IF_66|IF_MODRM|IF_RMM,"inveptl\t" OP_MEM OP_R32),
	I(0x80, IF_X64|IF_66|IF_MODRM|IF_RMM,"inveptq\t" OP_MEM OP_R64),

	I(0x81, IF_X32|IF_66|IF_MODRM|IF_RMM,"invvpidl\t" OP_MEM OP_R32),
	I(0x81, IF_X64|IF_66|IF_MODRM|IF_RMM,"invvpidq\t" OP_MEM OP_R64),

	I(0x82, IF_X32|IF_66|IF_MODRM|IF_RMM,"invpcidl\t" OP_MEM OP_R32),
	I(0x82, IF_X64|IF_66|IF_MODRM|IF_RMM,"invpcidq\t" OP_MEM OP_R64),

	I(0x83, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPMULTISHIFTQB_XMM)), /* EVEX.128.66.0f38.W1 83 /r vpmultishiftqb xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x83, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPMULTISHIFTQB_YMM)), /* EVEX.256.66.0f38.W1 83 /r vpmultishiftqb ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x83, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPMULTISHIFTQB_ZMM)), /* EVEX.512.66.0f38.W1 83 /r vpmultishiftqb zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0x88, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VEXPANDPD_XMM)), /* EVEX.128.66.0f38.W1 88 /r vexpandpd xmm1{k1}{z}, xmm2/m128 */
	I(0x88, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VEXPANDPD_YMM)), /* EVEX.256.66.0f38.W1 88 /r vexpandpd ymm1{k1}{z}, ymm2/m256 */
	I(0x88, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VEXPANDPD_ZMM)), /* EVEX.512.66.0f38.W1 88 /r vexpandpd zmm1{k1}{z}, zmm2/m512 */

	I(0x88, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VEXPANDPS_XMM)), /* EVEX.128.66.0f38.W0 88 /r vexpandps xmm1{k1}{z}, xmm2/m128 */
	I(0x88, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VEXPANDPS_YMM)), /* EVEX.256.66.0f38.W0 88 /r vexpandps ymm1{k1}{z}, ymm2/m256 */
	I(0x88, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VEXPANDPS_ZMM)), /* EVEX.512.66.0f38.W0 88 /r vexpandps zmm1{k1}{z}, zmm2/m512 */

	I(0x89, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPEXPANDD_XMM)), /* EVEX.128.66.0f38.W0 89 /r vpexpandd xmm1{k1}{z}, xmm2/m128 */
	I(0x89, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPEXPANDD_YMM)), /* EVEX.256.66.0f38.W0 89 /r vpexpandd ymm1{k1}{z}, ymm2/m256 */
	I(0x89, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPEXPANDD_ZMM)), /* EVEX.512.66.0f38.W0 89 /r vpexpandd zmm1{k1}{z}, zmm2/m512 */

	I(0x89, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPEXPANDQ_XMM)), /* EVEX.128.66.0f38.W1 89 /r vpexpandq xmm1{k1}{z}, xmm2/m128 */
	I(0x89, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPEXPANDQ_YMM)), /* EVEX.256.66.0f38.W1 89 /r vpexpandq ymm1{k1}{z}, ymm2/m256 */
	I(0x89, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPEXPANDQ_ZMM)), /* EVEX.512.66.0f38.W1 89 /r vpexpandq zmm1{k1}{z}, zmm2/m512 */

	I(0x8a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VCOMPRESSPD_XMM)), /* EVEX.128.66.0f38.W1 8a /r vcompresspd xmm1/m128{k1}{z}, xmm2 */
	I(0x8a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VCOMPRESSPD_YMM)), /* EVEX.256.66.0f38.W1 8a /r vcompresspd ymm1/m256{k1}{z}, ymm2 */
	I(0x8a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VCOMPRESSPD_ZMM)), /* EVEX.512.66.0f38.W1 8a /r vcompresspd zmm1/m512{k1}{z}, zmm2 */

	I(0x8a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VCOMPRESSPS_XMM)), /* EVEX.128.66.0f38.W0 8a /r vcompressps xmm1/m128{k1}{z}, xmm2 */
	I(0x8a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VCOMPRESSPS_YMM)), /* EVEX.256.66.0f38.W0 8a /r vcompressps ymm1/m256{k1}{z}, ymm2 */
	I(0x8a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VCOMPRESSPS_ZMM)), /* EVEX.512.66.0f38.W0 8a /r vcompressps zmm1/m512{k1}{z}, zmm2 */

	I(0x8b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPCOMPRESSD_XMM)), /* EVEX.128.66.0f38.W0 8b /r vpcompressd xmm1/m128{k1}{z}, xmm2 */
	I(0x8b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPCOMPRESSD_YMM)), /* EVEX.256.66.0f38.W0 8b /r vpcompressd ymm1/m256{k1}{z}, ymm2 */
	I(0x8b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPCOMPRESSD_ZMM)), /* EVEX.512.66.0f38.W0 8b /r vpcompressd zmm1/m512{k1}{z}, zmm2 */

	I(0x8b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPCOMPRESSQ_XMM)), /* EVEX.128.66.0f38.W1 8b /r vpcompressq xmm1/m128{k1}{z}, xmm2 */
	I(0x8b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPCOMPRESSQ_YMM)), /* EVEX.256.66.0f38.W1 8b /r vpcompressq ymm1/m256{k1}{z}, ymm2 */
	I(0x8b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPCOMPRESSQ_ZMM)), /* EVEX.512.66.0f38.W1 8b /r vpcompressq zmm1/m512{k1}{z}, zmm2 */

	I(0x8c, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPMASKMOVD_XMM)),     /* VEX.128.66.0f38.W0 8c /r vpmaskmovd xmm1, xmm2, m128 */
	I(0x8c, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPMASKMOVD_YMM)),     /* VEX.256.66.0f38.W0 8c /r vpmaskmovd ymm1, ymm2, m256 */
	I(0x8c, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPMASKMOVQ_XMM)),     /* VEX.128.66.0f38.W1 8c /r vpmaskmovq xmm1, xmm2, m128 */
	I(0x8c, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPMASKMOVQ_YMM)),     /* VEX.256.66.0f38.W1 8c /r vpmaskmovq ymm1, ymm2, m256 */

	I(0x8d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpermb\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W0 8d /r vpermb xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x8d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpermb\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W0 8d /r vpermb ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x8d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpermb\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 8d /r vpermb zmm1{k1}{z}, zmm2, zmm3/m512 */

	I(0x8d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpermw\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f38.W1 8d /r vpermw xmm1{k1}{z}, xmm2, xmm3/m128 */
	I(0x8d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermw\t" OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f38.W1 8d /r vpermw ymm1{k1}{z}, ymm2, ymm3/m256 */
	I(0x8d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermw\t" OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 8d /r vpermw zmm1{k1}{z}, zmm2, zmm3/m512 */

	I(0x8e, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPMASKMOVD_XMM_REV)), /* VEX.128.66.0f38.W0 8e /r vpmaskmovd m128, xmm1, xmm2 */
	I(0x8e, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPMASKMOVD_YMM_REV)), /* VEX.256.66.0f38.W0 8e /r vpmaskmovd m256, ymm1, ymm2 */
	I(0x8e, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPMASKMOVQ_XMM_REV)), /* VEX.128.66.0f38.W1 8e /r vpmaskmovq m128, xmm1, xmm2 */
	I(0x8e, IF_66|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPMASKMOVQ_YMM_REV)), /* VEX.256.66.0f38.W1 8e /r vpmaskmovq m256, ymm1, ymm2 */

	I(0x96, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VFMADDSUB132PD_XMM)), /* EVEX.128.66.0f38.W1 96 /r vfmaddsub132pd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x96, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VFMADDSUB132PD_YMM)), /* EVEX.256.66.0f38.W1 96 /r vfmaddsub132pd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x96, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VFMADDSUB132PD_ZMM)), /* EVEX.512.66.0f38.W1 96 /r vfmaddsub132pd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{er} */
	I(0x96, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VFMADDSUB132PS_XMM)), /* EVEX.128.66.0f38.W0 96 /r vfmaddsub132ps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x96, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VFMADDSUB132PS_YMM)), /* EVEX.256.66.0f38.W0 96 /r vfmaddsub132ps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x96, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VFMADDSUB132PS_ZMM)), /* EVEX.512.66.0f38.W0 96 /r vfmaddsub132ps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{er} */
	
	I(0x97, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VFMSUBADD132PD_XMM)), /* EVEX.128.66.0f38.W1 97 /r vfmsubadd132pd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x97, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VFMSUBADD132PD_YMM)), /* EVEX.256.66.0f38.W1 97 /r vfmsubadd132pd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x97, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VFMSUBADD132PD_ZMM)), /* EVEX.512.66.0f38.W1 97 /r vfmsubadd132pd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{er} */
	I(0x97, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VFMSUBADD132PS_XMM)), /* EVEX.128.66.0f38.W0 97 /r vfmsubadd132ps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x97, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VFMSUBADD132PS_YMM)), /* EVEX.256.66.0f38.W0 97 /r vfmsubadd132ps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x97, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VFMSUBADD132PS_ZMM)), /* EVEX.512.66.0f38.W0 97 /r vfmsubadd132ps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{er} */

	I(0x98, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VFMADD132PD_XMM)), /* EVEX.128.66.0f38.W1 98 /r vfmadd132pd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x98, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VFMADD132PD_YMM)), /* EVEX.256.66.0f38.W1 98 /r vfmadd132pd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x98, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VFMADD132PD_ZMM)), /* EVEX.512.66.0f38.W1 98 /r vfmadd132pd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{er} */
	I(0x98, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VFMADD132PS_XMM)), /* EVEX.128.66.0f38.W0 98 /r vfmadd132ps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x98, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VFMADD132PS_YMM)), /* EVEX.256.66.0f38.W0 98 /r vfmadd132ps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x98, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VFMADD132PS_ZMM)), /* EVEX.512.66.0f38.W0 98 /r vfmadd132ps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{er} */

	I(0x99, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VFMADD132SD_XMM)), /* EVEX.LIG.66.0f38.W1 99 /r vfmadd132sd xmm1{k1}{z}, xmm2, xmm3/m64{er} */
	I(0x99, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VFMADD132SS_XMM)), /* EVEX.LIG.66.0f38.W0 99 /r vfmadd132ss xmm1{k1}{z}, xmm2, xmm3/m32{er} */

	I(0x9a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VFMSUB132PD_XMM)), /* EVEX.128.66.0f38.W1 9a /r vfmsub132pd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0x9a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VFMSUB132PD_YMM)), /* EVEX.256.66.0f38.W1 9a /r vfmsub132pd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0x9a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VFMSUB132PD_ZMM)), /* EVEX.512.66.0f38.W1 9a /r vfmsub132pd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{er} */
	I(0x9a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VFMSUB132PS_XMM)), /* EVEX.128.66.0f38.W0 9a /r vfmsub132ps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0x9a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VFMSUB132PS_YMM)), /* EVEX.256.66.0f38.W0 9a /r vfmsub132ps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0x9a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VFMSUB132PS_ZMM)), /* EVEX.512.66.0f38.W0 9a /r vfmsub132ps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{er} */

	I(0x9a, IF_F2|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_V4FMADDPS_ZMM)),  /* EVEX.512.f2.0f38.W0 9a /r v4fmaddps zmm1{k1}{z}, zmm2+3, m128 */

	I(0x9b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VFMSUB132SD_XMM)), /* EVEX.LIG.66.0f38.W1 9b /r vfmsub132sd xmm1{k1}{z}, xmm2, xmm3/m64{er} */
	I(0x9b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VFMSUB132SS_XMM)), /* EVEX.LIG.66.0f38.W0 9b /r vfmsub132ss xmm1{k1}{z}, xmm2, xmm3/m32{er} */

	I(0x9b, IF_F2|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_V4FMADDSS_XMM)),  /* EVEX.LIG.f2.0f38.W0 9b /r v4fmaddss xmm1{k1}{z}, xmm2+3, m128 */

	I(0xa6, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VFMADDSUB213PD_XMM)), /* EVEX.128.66.0f38.W1 a6 /r vfmaddsub213pd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0xa6, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VFMADDSUB213PD_YMM)), /* EVEX.256.66.0f38.W1 a6 /r vfmaddsub213pd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0xa6, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VFMADDSUB213PD_ZMM)), /* EVEX.512.66.0f38.W1 a6 /r vfmaddsub213pd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{er} */
	I(0xa6, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VFMADDSUB213PS_XMM)), /* EVEX.128.66.0f38.W0 a6 /r vfmaddsub213ps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0xa6, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VFMADDSUB213PS_YMM)), /* EVEX.256.66.0f38.W0 a6 /r vfmaddsub213ps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0xa6, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VFMADDSUB213PS_ZMM)), /* EVEX.512.66.0f38.W0 a6 /r vfmaddsub213ps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{er} */
	
	I(0xa7, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VFMSUBADD213PD_XMM)), /* EVEX.128.66.0f38.W1 a7 /r vfmsubadd213pd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0xa7, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VFMSUBADD213PD_YMM)), /* EVEX.256.66.0f38.W1 a7 /r vfmsubadd213pd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0xa7, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VFMSUBADD213PD_ZMM)), /* EVEX.512.66.0f38.W1 a7 /r vfmsubadd213pd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{er} */
	I(0xa7, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VFMSUBADD213PS_XMM)), /* EVEX.128.66.0f38.W0 a7 /r vfmsubadd213ps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0xa7, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VFMSUBADD213PS_YMM)), /* EVEX.256.66.0f38.W0 a7 /r vfmsubadd213ps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0xa7, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VFMSUBADD213PS_ZMM)), /* EVEX.512.66.0f38.W0 a7 /r vfmsubadd213ps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{er} */

	I(0xa8, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VFMADD213PD_XMM)), /* EVEX.128.66.0f38.W1 a8 /r vfmadd213pd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0xa8, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VFMADD213PD_YMM)), /* EVEX.256.66.0f38.W1 a8 /r vfmadd213pd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0xa8, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VFMADD213PD_ZMM)), /* EVEX.512.66.0f38.W1 a8 /r vfmadd213pd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{er} */
	I(0xa8, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VFMADD213PS_XMM)), /* EVEX.128.66.0f38.W0 a8 /r vfmadd213ps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0xa8, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VFMADD213PS_YMM)), /* EVEX.256.66.0f38.W0 a8 /r vfmadd213ps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0xa8, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VFMADD213PS_ZMM)), /* EVEX.512.66.0f38.W0 a8 /r vfmadd213ps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{er} */

	I(0xa9, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VFMADD213SD_XMM)), /* EVEX.LIG.66.0f38.W1 a9 /r vfmadd213sd xmm1{k1}{z}, xmm2, xmm3/m64{er} */
	I(0xa9, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VFMADD213SS_XMM)), /* EVEX.LIG.66.0f38.W0 a9 /r vfmadd213ss xmm1{k1}{z}, xmm2, xmm3/m32{er} */

	I(0xaa, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VFMSUB213PD_XMM)), /* EVEX.128.66.0f38.W1 aa /r vfmsub213pd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0xaa, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VFMSUB213PD_YMM)), /* EVEX.256.66.0f38.W1 aa /r vfmsub213pd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0xaa, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VFMSUB213PD_ZMM)), /* EVEX.512.66.0f38.W1 aa /r vfmsub213pd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{er} */
	I(0xaa, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VFMSUB213PS_XMM)), /* EVEX.128.66.0f38.W0 aa /r vfmsub213ps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0xaa, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VFMSUB213PS_YMM)), /* EVEX.256.66.0f38.W0 aa /r vfmsub213ps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0xaa, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VFMSUB213PS_ZMM)), /* EVEX.512.66.0f38.W0 aa /r vfmsub213ps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{er} */

	I(0xaa, IF_F2|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_V4FNMADDPS_ZMM)), /* EVEX.512.f2.0f38.W0 aa /r v4fnmaddps zmm1{k1}{z}, zmm2+3, m128 */

	I(0xab, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VFMSUB213SD_XMM)), /* EVEX.LIG.66.0f38.W1 ab /r vfmsub213sd xmm1{k1}{z}, xmm2, xmm3/m64{er} */
	I(0xab, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VFMSUB213SS_XMM)), /* EVEX.LIG.66.0f38.W0 ab /r vfmsub213ss xmm1{k1}{z}, xmm2, xmm3/m32{er} */

	I(0xab, IF_F2|IF_VEX|IF_MODRM|IF_RMM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_V4FNMADDSS_XMM)), /* EVEX.LIG.f2.0f38.W0 ab /r v4fnmaddss xmm1{k1}{z}, xmm2+3, m128 */

	I(0xb4, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPMADD52LUQ_XMM)), /* EVEX.128.66.0f38.W1 b4 /r vpmadd52luq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0xb4, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPMADD52LUQ_YMM)), /* EVEX.256.66.0f38.W1 b4 /r vpmadd52luq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0xb4, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPMADD52LUQ_ZMM)), /* EVEX.512.66.0f38.W1 b4 /r vpmadd52luq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0xb5, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPMADD52HUQ_XMM)), /* EVEX.128.66.0f38.W1 b5 /r vpmadd52huq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0xb5, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPMADD52HUQ_YMM)), /* EVEX.256.66.0f38.W1 b5 /r vpmadd52huq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0xb5, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPMADD52HUQ_ZMM)), /* EVEX.512.66.0f38.W1 b5 /r vpmadd52huq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst */

	I(0xb6, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VFMADDSUB231PD_XMM)), /* EVEX.128.66.0f38.W1 b6 /r vfmaddsub231pd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0xb6, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VFMADDSUB231PD_YMM)), /* EVEX.256.66.0f38.W1 b6 /r vfmaddsub231pd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0xb6, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VFMADDSUB231PD_ZMM)), /* EVEX.512.66.0f38.W1 b6 /r vfmaddsub231pd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{er} */
	I(0xb6, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VFMADDSUB231PS_XMM)), /* EVEX.128.66.0f38.W0 b6 /r vfmaddsub231ps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0xb6, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VFMADDSUB231PS_YMM)), /* EVEX.256.66.0f38.W0 b6 /r vfmaddsub231ps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0xb6, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VFMADDSUB231PS_ZMM)), /* EVEX.512.66.0f38.W0 b6 /r vfmaddsub231ps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{er} */

	I(0xb7, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VFMSUBADD231PD_XMM)), /* EVEX.128.66.0f38.W1 b7 /r vfmsubadd231pd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0xb7, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VFMSUBADD231PD_YMM)), /* EVEX.256.66.0f38.W1 b7 /r vfmsubadd231pd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0xb7, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VFMSUBADD231PD_ZMM)), /* EVEX.512.66.0f38.W1 b7 /r vfmsubadd231pd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{er} */
	I(0xb7, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VFMSUBADD231PS_XMM)), /* EVEX.128.66.0f38.W0 b7 /r vfmsubadd231ps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0xb7, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VFMSUBADD231PS_YMM)), /* EVEX.256.66.0f38.W0 b7 /r vfmsubadd231ps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0xb7, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VFMSUBADD231PS_ZMM)), /* EVEX.512.66.0f38.W0 b7 /r vfmsubadd231ps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{er} */

	I(0xb8, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VFMADD231PD_XMM)), /* EVEX.128.66.0f38.W1 b8 /r vfmadd231pd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0xb8, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VFMADD231PD_YMM)), /* EVEX.256.66.0f38.W1 b8 /r vfmadd231pd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0xb8, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VFMADD231PD_ZMM)), /* EVEX.512.66.0f38.W1 b8 /r vfmadd231pd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{er} */
	I(0xb8, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VFMADD231PS_XMM)), /* EVEX.128.66.0f38.W0 b8 /r vfmadd231ps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0xb8, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VFMADD231PS_YMM)), /* EVEX.256.66.0f38.W0 b8 /r vfmadd231ps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0xb8, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VFMADD231PS_ZMM)), /* EVEX.512.66.0f38.W0 b8 /r vfmadd231ps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{er} */

	I(0xb9, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VFMADD231SD_XMM)), /* EVEX.LIG.66.0f38.W1 b9 /r vfmadd231sd xmm1{k1}{z}, xmm2, xmm3/m64{er} */
	I(0xb9, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VFMADD231SS_XMM)), /* EVEX.LIG.66.0f38.W0 b9 /r vfmadd231ss xmm1{k1}{z}, xmm2, xmm3/m32{er} */

	I(0xba, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VFMSUB231PD_XMM)), /* EVEX.128.66.0f38.W1 ba /r vfmsub231pd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst */
	I(0xba, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VFMSUB231PD_YMM)), /* EVEX.256.66.0f38.W1 ba /r vfmsub231pd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst */
	I(0xba, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VFMSUB231PD_ZMM)), /* EVEX.512.66.0f38.W1 ba /r vfmsub231pd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{er} */

	I(0xba, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VFMSUB231PS_XMM)), /* EVEX.128.66.0f38.W0 ba /r vfmsub231ps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst */
	I(0xba, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VFMSUB231PS_YMM)), /* EVEX.256.66.0f38.W0 ba /r vfmsub231ps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst */
	I(0xba, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VFMSUB231PS_ZMM)), /* EVEX.512.66.0f38.W0 ba /r vfmsub231ps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{er} */

	I(0xbb, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VFMSUB231SD_XMM)), /* EVEX.LIG.66.0f38.W1 bb /r vfmsub231sd xmm1{k1}{z}, xmm2, xmm3/m64{er} */
	I(0xbb, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VFMSUB231SS_XMM)), /* EVEX.LIG.66.0f38.W0 bb /r vfmsub231ss xmm1{k1}{z}, xmm2, xmm3/m32{er} */

	I(0xc4, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPCONFLICTD_XMM)), /* EVEX.128.66.0f38.W0 c4 /r vpconflictd xmm1{k1}{z}, xmm2/m128/m32bcst */
	I(0xc4, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPCONFLICTD_YMM)), /* EVEX.256.66.0f38.W0 c4 /r vpconflictd ymm1{k1}{z}, ymm2/m256/m32bcst */
	I(0xc4, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPCONFLICTD_ZMM)), /* EVEX.512.66.0f38.W0 c4 /r vpconflictd zmm1{k1}{z}, zmm2/m512/m32bcst */

	I(0xc4, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPCONFLICTQ_XMM)), /* EVEX.128.66.0f38.W1 c4 /r vpconflictq xmm1{k1}{z}, xmm2/m128/m64bcst */
	I(0xc4, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPCONFLICTQ_YMM)), /* EVEX.256.66.0f38.W1 c4 /r vpconflictq ymm1{k1}{z}, ymm2/m256/m64bcst */
	I(0xc4, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPCONFLICTQ_ZMM)), /* EVEX.512.66.0f38.W1 c4 /r vpconflictq zmm1{k1}{z}, zmm2/m512/m64bcst */

	I(0xc8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vexp2ps\t" OP_SAE OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f38.W0 c8 /r vexp2ps zmm1{k1}{z}, zmm2/m512/m32bcst{sae} */
	I(0xc8, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vexp2pd\t" OP_SAE OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f38.W1 c8 /r vexp2pd zmm1{k1}{z}, zmm2/m512/m64bcst{sae} */
	I(0xc8, IF_MODRM, "sha1nexte\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xc9, IF_MODRM, "sha1msg1\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xca, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VRCP28PS)), /* EVEX.512.66.0f38.W0 ca /r vrcp28ps zmm1{k1}{z}, zmm2/m512/m32bcst{sae} */
	I(0xca, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VRCP28PD)), /* EVEX.512.66.0f38.W1 ca /r vrcp28pd zmm1{k1}{z}, zmm2/m512/m64bcst{sae} */
	I(0xca, IF_MODRM, "sha1msg2\t" OP_RM128_XMM OP_RXMM_MASK),

	I(0xcb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(0, 0, 1) "vrcp28sd\t" OP_SAE OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.LIG.66.0f38.W1 cb /r vrcp28sd xmm1{k1}{z}, xmm2, xmm3/m64{sae} */
	I(0xcb, IF_MODRM, LONGREPR(LO_SHA256RNDS2)),

	I(0xcc, IF_MODRM, LONGREPR(LO_SHA256MSG1)),

	I(0xcd, IF_MODRM, LONGREPR(LO_SHA256MSG2)),

	I(0xcf, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VGF2P8MULB)), /* VEX.128.66.0f38.WIG cf /r vgf2p8mulb xmm1, xmm2/m128 */
	I(0xcf, IF_66|IF_MODRM,        "gf2p8mulb\t" OP_RM128_XMM OP_RXMM),                 /*            66 0f 38 cf /r gf2p8mulb xmm1, xmm2/m128 */

	I(0xdb, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vaesimc\t" OP_RM128_XMM OP_RXMM), /* VEX.128.66.0f38.WIG db /r vaesimc xmm1, xmm2/m128 */
	I(0xdb, IF_66|IF_MODRM,                              "aesimc\t" OP_RM128_XMM OP_RXMM),  /*            66 0f 38 db /r aesimc xmm1, xmm2/m128 */

	I(0xdc, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vaesenc\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG dc /r vaesenc xmm1, xmm2, xmm3/m128 */
	I(0xdc, IF_66|IF_MODRM,                              "aesenc\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 dc /r aesenc xmm1, xmm2/m128 */

	I(0xdd, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VAESENCLAST)), /* VEX.128.66.0f38.WIG dd /r vaesenclast xmm1, xmm2, xmm3/m128 */
	I(0xdd, IF_66|IF_MODRM,        LONGREPR(LO_AESEECLAST)),                             /*            66 0f 38 dd /r aesenclast xmm1, xmm2/m128 */

	I(0xde, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vaesdec\t" OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f38.WIG de /r vaesdec xmm1, xmm2, xmm3/m128 */
	I(0xde, IF_66|IF_MODRM,                              "aesdec\t" OP_RM128_XMM OP_RXMM),             /*            66 0f 38 de /r aesdec xmm1, xmm2/m128 */

	I(0xdf, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VAESDECLAST)), /* VEX.128.66.0f38.WIG df /r vaesdeclast xmm1, xmm2, xmm3/m128 */
	I(0xdf, IF_66|IF_MODRM,        LONGREPR(LO_AESDECLAST)),                             /*            66 0f 38 df /r aesdeclast xmm1, xmm2/m128 */

	I(0xf0, IF_66|IF_MODRM/*|IF_RMM*/,   "movbew\t" OP_RM16 OP_R16), /* KOS Emulates the register variant */
	I(0xf0, IF_MODRM/*|IF_RMM*/,         "movbel\t" OP_RM32 OP_R32),
	I(0xf0, IF_MODRM|IF_REXW/*|IF_RMM*/, "movbeq\t" OP_RM64 OP_R64),
	I(0xf0, IF_F2|IF_MODRM,              "crc32b\t" OP_RM8 OP_R32),
	I(0xf0, IF_F2|IF_MODRM|IF_REXW,      "crc32b\t" OP_RM8 OP_R64),
	I(0xf1, IF_66|IF_MODRM/*|IF_RMM*/,   "movbew\t" OP_R16 OP_RM16), /* KOS Emulates the register variant */
	I(0xf1, IF_MODRM/*|IF_RMM*/,         "movbel\t" OP_R32 OP_RM32),
	I(0xf1, IF_MODRM|IF_REXW/*|IF_RMM*/, "movbeq\t" OP_R64 OP_RM64),
	I(0xf1, IF_F2|IF_66|IF_MODRM,        "crc32w\t" OP_RM16 OP_R32),
	I(0xf1, IF_F2|IF_MODRM,              "crc32l\t" OP_RM32 OP_R32),
	I(0xf1, IF_F2|IF_MODRM|IF_REXW,      "crc32q\t" OP_RM64 OP_R64),

	I(0xf2, IF_VEXW0|IF_MODRM, "andnl\t" OP_RM32 OP_VR32 OP_R32),
	I(0xf2, IF_VEXW1|IF_MODRM, "andnq\t" OP_RM64 OP_VR64 OP_R64),

	I(0xf3, IF_VEXW0|IF_MODRM|IF_REG1,"blsrl\t" OP_RM32 OP_VR32),
	I(0xf3, IF_VEXW1|IF_MODRM|IF_REG1,"blsrq\t" OP_RM64 OP_VR64),
	I(0xf3, IF_VEXW0|IF_MODRM|IF_REG2,"blsmskl\t" OP_RM32 OP_VR32),
	I(0xf3, IF_VEXW1|IF_MODRM|IF_REG2,"blsmskq\t" OP_RM64 OP_VR64),
	I(0xf3, IF_VEXW0|IF_MODRM|IF_REG3,"blsil\t" OP_RM32 OP_VR32),
	I(0xf3, IF_VEXW1|IF_MODRM|IF_REG3,"blsiq\t" OP_RM64 OP_VR64),

	I(0xf5, IF_VEXW0|IF_MODRM,       "bzhil\t" OP_VR32 OP_RM32 OP_R32),
	I(0xf5, IF_VEXW1|IF_MODRM,       "bzhiq\t" OP_VR64 OP_RM64 OP_R64),
	I(0xf5, IF_VEXW0|IF_F3|IF_MODRM, "pextl\t" OP_RM32 OP_VR32 OP_R32),
	I(0xf5, IF_VEXW1|IF_F3|IF_MODRM, "pextq\t" OP_RM64 OP_VR64 OP_R64),
	I(0xf5, IF_VEXW0|IF_F2|IF_MODRM, "pdepl\t" OP_RM32 OP_VR32 OP_R32),
	I(0xf5, IF_VEXW1|IF_F2|IF_MODRM, "pdepq\t" OP_RM64 OP_VR64 OP_R64),

	I(0xf6, IF_66|IF_MODRM,         "adcxl\t" OP_RM32 OP_R32),
	I(0xf6, IF_66|IF_MODRM|IF_REXW, "adcxq\t" OP_RM64 OP_R64),
	I(0xf6, IF_F3|IF_MODRM,         "adoxl\t" OP_RM32 OP_R32),
	I(0xf6, IF_F3|IF_MODRM|IF_REXW, "adoxq\t" OP_RM64 OP_R64),
	I(0xf6, IF_F2|IF_MODRM,         "mulxl\t" OP_RM32 OP_VR32 OP_R32),
	I(0xf6, IF_F2|IF_MODRM|IF_REXW, "mulxq\t" OP_RM64 OP_VR64 OP_R64),

	I(0xf7, IF_VEXW0|IF_MODRM,       "bextrl\t" OP_VR32 OP_RM32 OP_R32),
	I(0xf7, IF_VEXW1|IF_MODRM,       "bextrq\t" OP_VR64 OP_RM64 OP_R64),
	I(0xf7, IF_66|IF_VEXW0|IF_MODRM, "shlxl\t" OP_VR32 OP_RM32 OP_R32),
	I(0xf7, IF_66|IF_VEXW1|IF_MODRM, "shlxq\t" OP_VR64 OP_RM64 OP_R64),
	I(0xf7, IF_F3|IF_VEXW0|IF_MODRM, "sarxl\t" OP_VR32 OP_RM32 OP_R32),
	I(0xf7, IF_F3|IF_VEXW1|IF_MODRM, "sarxq\t" OP_VR64 OP_RM64 OP_R64),
	I(0xf7, IF_F2|IF_VEXW0|IF_MODRM, "shrxl\t" OP_VR32 OP_RM32 OP_R32),
	I(0xf7, IF_F2|IF_VEXW1|IF_MODRM, "shrxq\t" OP_VR64 OP_RM64 OP_R64),

	I(0xf8, IF_X32|IF_66|IF_MODRM|IF_RMM, "movdir64b\t" OP_RM64 OP_R32),
	I(0xf8, IF_X64|IF_66|IF_MODRM|IF_RMM, "movdir64b\t" OP_RM64 OP_R64),

	I(0, 0, "")
/*[[[end:ops_0f38]]]*/
};
/* clang-format on */








/* clang-format off */
PRIVATE struct instruction const ops_0f3a[] = {
/*[[[start:ops_0f3a]]]*/
	/* REMINDER: After adding/removing instructions from this table, you must run:
	 *           $ deemon -F kos/src/libdisasm/x86-db.h */

	/* 0x0f3aXX */
	I(0x00, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermq\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f3a.W1 00 /r ib vpermq ymm1{k1}{z}, ymm2/m256/m64bcst, imm8 */
	I(0x00, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermq\t" OP_U8 OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f3a.W1 00 /r ib vpermq zmm1{k1}{z}, zmm2/m512/m64bcst, imm8 */

	I(0x01, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpermpd\t" OP_U8 OP_RM256_YMM OP_RYMM_MASK), /* EVEX.256.66.0f3a.W1 01 /r ib vpermpd ymm1{k1}{z}, ymm2/m256/m64bcst, imm8 */
	I(0x01, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpermpd\t" OP_U8 OP_RM512_ZMM OP_RZMM_MASK), /* EVEX.512.66.0f3a.W1 01 /r ib vpermpd zmm1{k1}{z}, zmm2/m512/m64bcst, imm8 */

	I(0x02, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpblendd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f3a.W0 02 /r ib vpblendd xmm1, xmm2, xmm3/m128, imm8 */
	I(0x02, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpblendd\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f3a.W0 02 /r ib vpblendd ymm1, ymm2, ymm3/m256, imm8 */

	I(0x03, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "valignd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f3a.W0 03 /r ib valignd xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst, imm8 */
	I(0x03, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "valignq\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f3a.W1 03 /r ib valignq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst, imm8 */
	I(0x03, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "valignd\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f3a.W0 03 /r ib valignd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst, imm8 */
	I(0x03, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "valignq\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f3a.W1 03 /r ib valignq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst, imm8 */
	I(0x03, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "valignd\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f3a.W0 03 /r ib valignd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst, imm8 */
	I(0x03, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "valignq\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f3a.W1 03 /r ib valignq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst, imm8 */

	I(0x04, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPERMILPS_XMM)), /* EVEX.128.66.0f3a.W0 04 /r ib vpermilps xmm1{k1}{z}, xmm2/m128/m32bcst, imm8 */
	I(0x04, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPERMILPS_YMM)), /* EVEX.256.66.0f3a.W0 04 /r ib vpermilps ymm1{k1}{z}, ymm2/m256/m32bcst, imm8 */
	I(0x04, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPERMILPS_ZMM)), /* EVEX.512.66.0f3a.W0 04 /r ib vpermilps zmm1{k1}{z}, zmm2/m512/m32bcst, imm8 */

	I(0x05, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 0), LO_VPERMILPD_XMM)), /*  VEX.128.66.0f3a.W0 05 /r ib vpermilpd xmm1, xmm2/m128, imm8 */
	I(0x05, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 1), LO_VPERMILPD_YMM)), /*  VEX.256.66.0f3a.W0 05 /r ib vpermilpd ymm1, ymm2/m256, imm8 */
	I(0x05, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPERMILPD_XMM)), /* EVEX.128.66.0f3a.W1 05 /r ib vpermilpd xmm1{k1}{z}, xmm2/m128/m64bcst, imm8 */
	I(0x05, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPERMILPD_YMM)), /* EVEX.256.66.0f3a.W1 05 /r ib vpermilpd ymm1{k1}{z}, ymm2/m256/m64bcst, imm8 */
	I(0x05, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPERMILPD_ZMM)), /* EVEX.512.66.0f3a.W1 05 /r ib vpermilpd zmm1{k1}{z}, zmm2/m512/m64bcst, imm8 */

	I(0x06, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPERM2F128)), /* VEX.256.66.0f3a.W0 06 /r ib vperm2f128 ymm1, ymm2, ymm3/m256, imm8 */

	I(0x08, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VROUNDPS_RXMM)),   /*  VEX.128.66.0f3a.WIG 08 /r ib vroundps xmm1, xmm2/m128, imm8 */
	I(0x08, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VROUNDPS_RYMM)),   /*  VEX.256.66.0f3a.WIG 08 /r ib vroundps ymm1, ymm2/m256, imm8 */
	I(0x08, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VRNDSCALEPS_XMM)), /* EVEX.128.66.0f3a.W0  08 /r ib vrndscaleps xmm1{k1}{z}, xmm2/m128/m32bcst, imm8 */
	I(0x08, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VRNDSCALEPS_YMM)), /* EVEX.256.66.0f3a.W0  08 /r ib vrndscaleps ymm1{k1}{z}, ymm2/m256/m32bcst, imm8 */
	I(0x08, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VRNDSCALEPS_ZMM)), /* EVEX.512.66.0f3a.W0  08 /r ib vrndscaleps zmm1{k1}{z}, zmm2/m512/m32bcst{sae}, imm8 */

	I(0x08, IF_66|IF_MODRM, "roundps\t" OP_U8 OP_RM128_XMM OP_RXMM), /* 66 0f 3a 08 /r ib roundps xmm1, xmm2/m128, imm8 */

	I(0x09, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VROUNDPD_RXMM)),   /*  VEX.128.66.0f3a.WIG 09 /r ib vroundpd xmm1, xmm2/m128, imm8 */
	I(0x09, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 1), LO_VROUNDPD_RYMM)),   /*  VEX.256.66.0f3a.WIG 09 /r ib vroundpd ymm1, ymm2/m256, imm8 */
	I(0x09, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VRNDSCALEPD_XMM)), /* EVEX.128.66.0f3a.W1  09 /r ib vrndscalepd xmm1{k1}{z}, xmm2/m128/m64bcst, imm8 */
	I(0x09, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VRNDSCALEPD_YMM)), /* EVEX.256.66.0f3a.W1  09 /r ib vrndscalepd ymm1{k1}{z}, ymm2/m256/m64bcst, imm8 */
	I(0x09, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VRNDSCALEPD_ZMM)), /* EVEX.512.66.0f3a.W1  09 /r ib vrndscalepd zmm1{k1}{z}, zmm2/m512/m64bcst{sae}, imm8 */

	I(0x09, IF_66|IF_MODRM, "roundpd\t" OP_U8 OP_RM128_XMM OP_RXMM), /* 66 0f 3a 09 /r ib roundpd xmm1, xmm2/m128, imm8 */

	I(0x0a, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vroundss\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /*  VEX.LIG.66.0f3a.WIG 0a /r ib vroundss xmm1, xmm2, xmm3/m32, imm8 */
	I(0x0a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VRNDSCALESS)),                  /* EVEX.LIG.66.0f3a.W0  0a /r ib vrndscaless xmm1{k1}{z}, xmm2, xmm3/m32{sae}, imm8 */

	I(0x0a, IF_66|IF_MODRM, "roundss\t" OP_U8 OP_RM128_XMM OP_RXMM), /* 66 0f 3a 0a /r ib roundss xmm1, xmm2/m32, imm8 */

	I(0x0b, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0_LIG(1, 1, 0) "vroundsd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /*  VEX.LIG.66.0f3a.WIG 0b /r ib vroundsd xmm1, xmm2, xmm3/m64, imm8 */
	I(0x0b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VRNDSCALESD)),                  /* EVEX.LIG.66.0f3a.W1  0b /r ib vrndscalesd xmm1{k1}{z}, xmm2, xmm3/m64{sae}, imm8 */

	I(0x0b, IF_66|IF_MODRM, "roundsd\t" OP_U8 OP_RM128_XMM OP_RXMM), /* 66 0f 3a 0b /r ib roundsd xmm1, xmm2/m64, imm8 */

	I(0x0c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vblendps\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f3a.WIG 0c /r ib vblendps xmm1, xmm2, xmm3/m128, imm8 */
	I(0x0c, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vblendps\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f3a.WIG 0c /r ib vblendps ymm1, ymm2, ymm3/m256, imm8 */
	I(0x0c, IF_66|IF_MODRM,                              "blendps\t" OP_U8 OP_RM128_XMM OP_RXMM),             /*            66 0f 3a 0c /r ib blendps xmm1, xmm2/m128, imm8 */

	I(0x0d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vblendpd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f3a.WIG 0d /r ib vblendpd xmm1, xmm2, xmm3/m128, imm8 */
	I(0x0d, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vblendpd\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f3a.WIG 0d /r ib vblendpd ymm1, ymm2, ymm3/m256, imm8 */
	I(0x0d, IF_66|IF_MODRM,                              "blendpd\t" OP_U8 OP_RM128_XMM OP_RXMM),             /*            66 0f 3a 0d /r ib blendpd xmm1, xmm2/m128, imm8 */

	I(0x0e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpblendw\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f3a.WIG 0e /r ib vpblendw xmm1, xmm2, xmm3/m128, imm8 */
	I(0x0e, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpblendw\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f3a.WIG 0e /r ib vpblendw ymm1, ymm2, ymm3/m256, imm8 */
	I(0x0e, IF_66|IF_MODRM,                              "pblendw\t" OP_U8 OP_RM128_XMM OP_RXMM),             /*            66 0f 3a 0e /r ib pblendw xmm1, xmm2/m128, imm8 */

	I(0x0f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpalignr\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f3a.WIG 0f /r ib vpalignr xmm1{k1}{z}, xmm2, xmm3/m128, imm8 */
	I(0x0f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vpalignr\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f3a.WIG 0f /r ib vpalignr ymm1{k1}{z}, ymm2, ymm3/m256, imm8 */
	I(0x0f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 2) "vpalignr\t" OP_U8 OP_RM512_ZMM__OP_VRZMM__OP_RZMM_MASK), /* EVEX.512.66.0f3a.WIG 0f /r ib vpalignr zmm1{k1}{z}, zmm2, zmm3/m512, imm8 */
	I(0x0f, IF_MODRM,                                    "palignr\t" OP_U8 OP_RM64_MM OP_RMM),                /*                0f 3a 0f /r ib palignr mm1, mm2/m64, imm8 */
	I(0x0f, IF_66|IF_MODRM,                              "palignr\t" OP_U8 OP_RM128_XMM OP_RXMM),             /*             66 0f 3a 0f /r ib palignr xmm1, xmm2/m128, imm8 */

	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 0, 0, 0) "vpextrb\t" OP_U8 OP_RXMM OP_RM8),  /*  VEX.128.66.0f3a.W0  14 /r ib vpextrb r/m8, xmm2, imm8 */
	I(0x14, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpextrb\t" OP_U8 OP_RXMM OP_RM8),  /* EVEX.128.66.0f3a.WIG 14 /r ib vpextrb r/m8, xmm2, imm8 */
	I(0x14, IF_66|IF_MODRM,                              "pextrb\t" OP_U8 OP_RXMM OP_RM8),   /*       66       0f 3a 14 /r ib pextrb r/m8, xmm2, imm8 */

	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 0, 0, 0) "vpextrw\t" OP_U8 OP_RXMM OP_RM16), /*  VEX.128.66.0f3a.W0  15 /r ib vpextrw r/m16, xmm2, imm8 */
	I(0x15, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vpextrw\t" OP_U8 OP_RXMM OP_RM16), /* EVEX.128.66.0f3a.WIG 15 /r ib vpextrw r/m16, xmm2, imm8 */
	I(0x15, IF_66|IF_MODRM,                              "pextrw\t" OP_U8 OP_RXMM OP_RM16),  /*             66 0f 3a 15 /r ib pextrw r/m16, xmm, imm8 */

	I(0x16, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpextrd\t" OP_U8 OP_RXMM OP_RM32), /* EVEX.128.66.0f3a.W0  16 /r ib vpextrd r/m32, xmm2, imm8 */
	I(0x16, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpextrq\t" OP_U8 OP_RXMM OP_RM64), /* EVEX.128.66.0f3a.W1  16 /r ib vpextrq r/m64, xmm2, imm8 */
	I(0x16, IF_66|IF_MODRM,        "pextrd\t" OP_U8 OP_RXMM OP_RM32),                        /*       66       0f 3a 16 /r ib pextrd r/m32, xmm2, imm8 */
	I(0x16, IF_66|IF_MODRM,        "pextrq\t" OP_U8 OP_RXMM OP_RM64),                        /*       66 rex.w 0f 3a 16 /r ib pextrq r/m64, xmm2, imm8 */

	I(0x17, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VEXTRACTPS)), /* EVEX.128.66.0f3a.WIG 17 /r ib vextractps r/m32, xmm1, imm8 */
	I(0x17, IF_66|IF_MODRM,        LONGREPR(LO_EXTRACTPS)),                             /*             66 0f 3a 17 /r ib extractps r/m32, xmm1, imm8 */

	I(0x18, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 1), LO_VINSERTF128)),      /*  VEX.256.66.0f3a.W0 18 /r ib vinsertf128 ymm1, ymm2, xmm3/m128, imm8 */
	I(0x18, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VINSERTF32X4_YMM)), /* EVEX.256.66.0f3a.W0 18 /r ib vinsertf32x4 ymm1{k1}{z}, ymm2, xmm3/m128, imm8 */
	I(0x18, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VINSERTF32X4_ZMM)), /* EVEX.512.66.0f3a.W0 18 /r ib vinsertf32x4 zmm1{k1}{z}, zmm2, xmm3/m128, imm8 */
	I(0x18, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VINSERTF64X2_YMM)), /* EVEX.256.66.0f3a.W1 18 /r ib vinsertf64x2 ymm1{k1}{z}, ymm2, xmm3/m128, imm8 */
	I(0x18, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VINSERTF64X2_ZMM)), /* EVEX.512.66.0f3a.W1 18 /r ib vinsertf64x2 zmm1{k1}{z}, zmm2, xmm3/m128, imm8 */

	I(0x19, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 1), LO_VEXTRACTF128)),      /*  VEX.256.66.0f3a.W0 19 /r ib vextractf128 xmm1/m128, ymm2, imm8 */
	I(0x19, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VEXTRACTF32X4_YMM)), /* EVEX.256.66.0f3a.W0 19 /r ib vextractf32x4 xmm1/m128{k1}{z}, ymm2, imm8 */
	I(0x19, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VEXTRACTF32X4_ZMM)), /* EVEX.512.66.0f3a.W0 19 /r ib vextractf32x4 xmm1/m128{k1}{z}, zmm2, imm8 */
	I(0x19, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VEXTRACTF64X2_YMM)), /* EVEX.256.66.0f3a.W1 19 /r ib vextractf64x2 xmm1/m128{k1}{z}, ymm2, imm8 */
	I(0x19, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VEXTRACTF64X2_ZMM)), /* EVEX.512.66.0f3a.W1 19 /r ib vextractf64x2 xmm1/m128{k1}{z}, zmm2, imm8 */

	I(0x1a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VINSERTF32X8)), /* EVEX.512.66.0f3a.W0 1a /r ib vinsertf32x8 zmm1{k1}{z}, zmm2, ymm3/m256, imm8 */
	I(0x1a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VINSERTF64X4)), /* EVEX.512.66.0f3a.W1 1a /r ib vinsertf64x4 zmm1{k1}{z}, zmm2, ymm3/m256, imm8 */

	I(0x1b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VEXTRACTF32X8_ZMM)), /* EVEX.512.66.0f3a.W0 1b /r ib vextractf32x8 ymm1/m256{k1}{z}, zmm2, imm8 */
	I(0x1b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VEXTRACTF64X4_ZMM)), /* EVEX.512.66.0f3a.W1 1b /r ib vextractf64x4 ymm1/m256{k1}{z}, zmm2, imm8 */

	I(0x1d, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VCVTPS2PH_XMM)),   /* EVEX.128.66.0f3a.W0 1d /r ib vcvtps2ph xmm1/m64{k1}{z}, xmm2, imm8 */
	I(0x1d, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VCVTPS2PH_YMM)),   /* EVEX.256.66.0f3a.W0 1d /r ib vcvtps2ph xmm1/m128{k1}{z}, ymm2, imm8 */
	I(0x1d, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VCVTPS2PH_ZMM)),   /* EVEX.512.66.0f3a.W0 1d /r ib vcvtps2ph ymm1/m256{k1}{z}, zmm2{sae}, imm8 */

	I(0x1e, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPCMPUD_XMM)), /* EVEX.128.66.0f3a.W0 1e /r ib vpcmpud k1{k2}, xmm2, xmm3/m128/m32bcst, imm8 */
	I(0x1e, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPCMPUD_YMM)), /* EVEX.256.66.0f3a.W0 1e /r ib vpcmpud k1{k2}, ymm2, ymm3/m256/m32bcst, imm8 */
	I(0x1e, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPCMPUD_ZMM)), /* EVEX.512.66.0f3a.W0 1e /r ib vpcmpud k1{k2}, zmm2, zmm3/m512/m32bcst, imm8 */
	I(0x1e, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPCMPUQ_XMM)), /* EVEX.128.66.0f3a.W1 1e /r ib vpcmpuq k1{k2}, xmm2, xmm3/m128/m64bcst, imm8 */
	I(0x1e, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPCMPUQ_YMM)), /* EVEX.256.66.0f3a.W1 1e /r ib vpcmpuq k1{k2}, ymm2, ymm3/m256/m64bcst, imm8 */
	I(0x1e, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPCMPUQ_ZMM)), /* EVEX.512.66.0f3a.W1 1e /r ib vpcmpuq k1{k2}, zmm2, zmm3/m512/m64bcst, imm8 */

	I(0x1f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpcmpd\t" OP_U8 OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.66.0f3a.W0 1f /r ib vpcmpd k1{k2}, xmm2, xmm3/m128/m32bcst, imm8 */
	I(0x1f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpcmpd\t" OP_U8 OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.256.66.0f3a.W0 1f /r ib vpcmpd k1{k2}, ymm2, ymm3/m256/m32bcst, imm8 */
	I(0x1f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpcmpd\t" OP_U8 OP_RM512_ZMM OP_VRZMM OP_RK_MASK), /* EVEX.512.66.0f3a.W0 1f /r ib vpcmpd k1{k2}, zmm2, zmm3/m512/m32bcst, imm8 */

	I(0x1f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpcmpq\t" OP_U8 OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.66.0f3a.W1 1f /r ib vpcmpq k1{k2}, xmm2, xmm3/m128/m64bcst, imm8 */
	I(0x1f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpcmpq\t" OP_U8 OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.256.66.0f3a.W1 1f /r ib vpcmpq k1{k2}, ymm2, ymm3/m256/m64bcst, imm8 */
	I(0x1f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpcmpq\t" OP_U8 OP_RM512_ZMM OP_VRZMM OP_RK_MASK), /* EVEX.512.66.0f3a.W1 1f /r ib vpcmpq k1{k2}, zmm2, zmm3/m512/m64bcst, imm8 */

	I(0x20, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 0), LO_VPINSRB)), /*  VEX.128.66.0f3a.W0  20 /r ib vpinsrb xmm1, xmm2, r32/m8, imm8 */
	I(0x20, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPINSRB)), /* EVEX.128.66.0f3a.WIG 20 /r ib vpinsrb xmm1, xmm2, r32/m8, imm8 */
	I(0x20, IF_66|IF_MODRM,        "pinsrb\t" OP_U8 OP_RM8 OP_RXMM),                 /*       66       0f 3a 20 /r ib pinsrb xmm1, r32/m8, imm8 */

	I(0x21, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 1, 0, 0), LO_VINSERTPS_XMM)), /*  VEX.128.66.0f3a.WIG 21 /r ib vinsertps xmm1, xmm2, xmm3/m32, imm8 */
	I(0x21, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VINSERTPS_YMM)), /* EVEX.128.66.0f3a.W0  21 /r ib vinsertps xmm1, xmm2, xmm3/m32, imm8 */
	I(0x21, IF_66|IF_MODRM,        "insertps\t" OP_U8 OP_RM128_XMM OP_RXMM),               /*             66 0f 3a 21 /r ib insertps xmm1, xmm2/m32, imm8 */

	I(0x22, IF_66|IF_VEX|IF_MODRM,  LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPINSRD)), /* EVEX.128.66.0f3a.W0  22 /r ib vpinsrd xmm1, xmm2, r/m32, imm8 */
	I(0x22, IF_66|IF_VEX|IF_MODRM,  LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPINSRQ)), /* EVEX.128.66.0f3a.W1  22 /r ib vpinsrq xmm1, xmm2, r/m64, imm8 */
	I(0x22, IF_66|IF_MODRM,         "pinsrd\t" OP_U8 OP_RM32 OP_RXMM),                /*       66       0f 3a 22 /r ib pinsrd xmm1, r/m32, imm8 */
	I(0x22, IF_66|IF_MODRM|IF_REXW, "pinsrq\t" OP_U8 OP_RM64 OP_RXMM),                /*       66 rex.w 0f 3a 22 /r ib pinsrq xmm1, r/m64, imm8 */

	I(0x23, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VSHUFF32X4_YMM)), /* EVEX.256.66.0f3a.W0 23 /r ib vshuff32x4 ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst, imm8 */
	I(0x23, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VSHUFF32X4_ZMM)), /* EVEX.512.66.0f3a.W0 23 /r ib vshuff32x4 zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst, imm8 */
	I(0x23, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VSHUFF64X2_YMM)), /* EVEX.256.66.0f3a.W1 23 /r ib vshuff64x2 ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst, imm8 */
	I(0x23, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VSHUFF64X2_ZMM)), /* EVEX.512.66.0f3a.W1 23 /r ib vshuff64x2 zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst, imm8 */

	I(0x25, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPTERNLOGD_XMM)), /* EVEX.128.66.0f3a.W0 25 /r ib vpternlogd xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst, imm8 */
	I(0x25, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPTERNLOGD_YMM)), /* EVEX.256.66.0f3a.W0 25 /r ib vpternlogd ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst, imm8 */
	I(0x25, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPTERNLOGD_ZMM)), /* EVEX.512.66.0f3a.W0 25 /r ib vpternlogd zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst, imm8 */
	I(0x25, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPTERNLOGQ_XMM)), /* EVEX.128.66.0f3a.W1 25 /r ib vpternlogq xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst, imm8 */
	I(0x25, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPTERNLOGQ_YMM)), /* EVEX.256.66.0f3a.W1 25 /r ib vpternlogq ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst, imm8 */
	I(0x25, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPTERNLOGQ_ZMM)), /* EVEX.512.66.0f3a.W1 25 /r ib vpternlogq zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst, imm8 */

	I(0x26, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VGETMANTPD_XMM)), /* EVEX.128.66.0f3a.W1 26 /r ib vgetmantpd xmm1{k1}{z}, xmm2/m128/m64bcst, imm8 */
	I(0x26, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VGETMANTPD_YMM)), /* EVEX.256.66.0f3a.W1 26 /r ib vgetmantpd ymm1{k1}{z}, ymm2/m256/m64bcst, imm8 */
	I(0x26, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VGETMANTPD_ZMM)), /* EVEX.512.66.0f3a.W1 26 /r ib vgetmantpd zmm1{k1}{z}, zmm2/m512/m64bcst{sae}, imm8 */

	I(0x26, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VGETMANTPS_XMM)), /* EVEX.128.66.0f3a.W0 26 /r ib vgetmantps xmm1{k1}{z}, xmm2/m128/m32bcst, imm8 */
	I(0x26, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VGETMANTPS_YMM)), /* EVEX.256.66.0f3a.W0 26 /r ib vgetmantps ymm1{k1}{z}, ymm2/m256/m32bcst, imm8 */
	I(0x26, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VGETMANTPS_ZMM)), /* EVEX.512.66.0f3a.W0 26 /r ib vgetmantps zmm1{k1}{z}, zmm2/m512/m32bcst{sae}, imm8 */

	I(0x27, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VGETMANTSS)), /* EVEX.LIG.66.0f3a.W0 27 /r ib vgetmantss xmm1{k1}{z}, xmm2, xmm3/m32{sae}, imm8 */
	I(0x27, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VGETMANTSD)), /* EVEX.LIG.66.0f3a.W1 27 /r ib vgetmantsd xmm1{k1}{z}, xmm2, xmm3/m64{sae}, imm8 */

	I(0x30, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_KSHIFTRB)), /* VEX.L0.66.0f3a.W0 30 /r kshiftrb k1, k2, imm8 */
	I(0x30, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_KSHIFTRW)), /* VEX.L0.66.0f3a.W1 30 /r kshiftrw k1, k2, imm8 */

	I(0x31, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_KSHIFTRD)), /* VEX.L0.66.0f3a.W0 31 /r kshiftrd k1, k2, imm8 */
	I(0x31, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_KSHIFTRQ)), /* VEX.L0.66.0f3a.W1 31 /r kshiftrq k1, k2, imm8 */

	I(0x32, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_KSHIFTLB)), /* VEX.L0.66.0f3a.W0 32 /r kshiftlb k1, k2, imm8 */
	I(0x32, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_KSHIFTLW)), /* VEX.L0.66.0f3a.W1 32 /r kshiftlw k1, k2, imm8 */

	I(0x33, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_KSHIFTLD)), /* VEX.L0.66.0f3a.W0 33 /r kshiftld k1, k2, imm8 */
	I(0x33, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_KSHIFTLQ)), /* VEX.L0.66.0f3a.W1 33 /r kshiftlq k1, k2, imm8 */

	I(0x38, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 1), LO_VINSERTI128)),      /*  VEX.256.66.0f3a.W0 38 /r ib vinserti128 ymm1, ymm2, xmm3/m128, imm8 */
	I(0x38, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VINSERTI32X4_YMM)), /* EVEX.256.66.0f3a.W0 38 /r ib vinserti32x4 ymm1{k1}{z}, ymm2, xmm3/m128, imm8 */
	I(0x38, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VINSERTI32X4_ZMM)), /* EVEX.512.66.0f3a.W0 38 /r ib vinserti32x4 zmm1{k1}{z}, zmm2, xmm3/m128, imm8 */
	I(0x38, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VINSERTI64X2_YMM)), /* EVEX.256.66.0f3a.W1 38 /r ib vinserti64x2 ymm1{k1}{z}, ymm2, xmm3/m128, imm8 */
	I(0x38, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VINSERTI64X2_ZMM)), /* EVEX.512.66.0f3a.W1 38 /r ib vinserti64x2 zmm1{k1}{z}, zmm2, xmm3/m128, imm8 */

	I(0x39, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(1, 0, 0, 1), LO_VEXTRACTI128)),      /*  VEX.256.66.0f3a.W0 39 /r ib vextracti128 xmm1/m128, ymm2, imm8 */
	I(0x39, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VEXTRACTI32X4_YMM)), /* EVEX.256.66.0f3a.W0 39 /r ib vextracti32x4 xmm1/m128{k1}{z}, ymm2, imm8 */
	I(0x39, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VEXTRACTI32X4_ZMM)), /* EVEX.512.66.0f3a.W0 39 /r ib vextracti32x4 xmm1/m128{k1}{z}, zmm2, imm8 */
	I(0x39, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VEXTRACTI64X2_YMM)), /* EVEX.256.66.0f3a.W1 39 /r ib vextracti64x2 xmm1/m128{k1}{z}, ymm2, imm8 */
	I(0x39, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VEXTRACTI64X2_ZMM)), /* EVEX.512.66.0f3a.W1 39 /r ib vextracti64x2 xmm1/m128{k1}{z}, zmm2, imm8 */

	I(0x3a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VINSERTI32X8)), /* EVEX.512.66.0f3a.W0 3a /r ib vinserti32x8 zmm1{k1}{z}, zmm2, ymm3/m256, imm8 */
	I(0x3a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VINSERTI64X4)), /* EVEX.512.66.0f3a.W1 3a /r ib vinserti64x4 zmm1{k1}{z}, zmm2, ymm3/m256, imm8 */

	I(0x3b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VEXTRACTI32X8_ZMM)), /* EVEX.512.66.0f3a.W0 3b /r ib vextracti32x8 ymm1/m256{k1}{z}, zmm2, imm8 */
	I(0x3b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VEXTRACTI64X4_ZMM)), /* EVEX.512.66.0f3a.W1 3b /r ib vextracti64x4 ymm1/m256{k1}{z}, zmm2, imm8 */

	I(0x3e, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VPCMPUW_XMM)), /* EVEX.128.66.0f3a.W1 3e /r ib vpcmpuw k1{k2}, xmm2, xmm3/m128, imm8 */
	I(0x3e, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VPCMPUW_YMM)), /* EVEX.256.66.0f3a.W1 3e /r ib vpcmpuw k1{k2}, ymm2, ymm3/m256, imm8 */
	I(0x3e, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VPCMPUW_ZMM)), /* EVEX.512.66.0f3a.W1 3e /r ib vpcmpuw k1{k2}, zmm2, zmm3/m512, imm8 */

	I(0x3e, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPCMPUB_XMM)), /* EVEX.128.66.0f3a.W0 3e /r ib vpcmpub k1{k2}, xmm2, xmm3/m128, imm8 */
	I(0x3e, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPCMPUB_YMM)), /* EVEX.256.66.0f3a.W0 3e /r ib vpcmpub k1{k2}, ymm2, ymm3/m256, imm8 */
	I(0x3e, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VPCMPUB_ZMM)), /* EVEX.512.66.0f3a.W0 3e /r ib vpcmpub k1{k2}, zmm2, zmm3/m512, imm8 */

	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpcmpw\t" OP_U8 OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.66.0f3a.W1 3f /r ib vpcmpw k1{k2}, xmm2, xmm3/m128, imm8 */
	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpcmpw\t" OP_U8 OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.256.66.0f3a.W1 3f /r ib vpcmpw k1{k2}, ymm2, ymm3/m256, imm8 */
	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpcmpw\t" OP_U8 OP_RM512_ZMM OP_VRZMM OP_RK_MASK), /* EVEX.512.66.0f3a.W1 3f /r ib vpcmpw k1{k2}, zmm2, zmm3/m512, imm8 */

	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpcmpb\t" OP_U8 OP_RM128_XMM OP_VRXMM OP_RK_MASK), /* EVEX.128.66.0f3a.W0 3f /r ib vpcmpb k1{k2}, xmm2, xmm3/m128, imm8 */
	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpcmpb\t" OP_U8 OP_RM256_YMM OP_VRYMM OP_RK_MASK), /* EVEX.256.66.0f3a.W0 3f /r ib vpcmpb k1{k2}, ymm2, ymm3/m256, imm8 */
	I(0x3f, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpcmpb\t" OP_U8 OP_RM512_ZMM OP_VRZMM OP_RK_MASK), /* EVEX.512.66.0f3a.W0 3f /r ib vpcmpb k1{k2}, zmm2, zmm3/m512, imm8 */

	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vdpps\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f3a.WIG 40 /r ib vdpps xmm1, xmm2, xmm3/m128, imm8 */
	I(0x40, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 1) "vdpps\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f3a.WIG 40 /r ib vdpps ymm1, ymm2, ymm3/m256, imm8 */
	I(0x40, IF_66|IF_MODRM,                              "dpps\t" OP_U8 OP_RM128_XMM OP_RXMM),             /*            66 0f 3a 40 /r ib dpps xmm1, xmm2/m128, imm8 */

	I(0x41, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 1, 0, 0) "vdppd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f3a.WIG 41 /r ib vdppd xmm1, xmm2, xmm3/m128, imm8 */
	I(0x41, IF_66|IF_MODRM,                              "dppd\t" OP_U8 OP_RM128_XMM OP_RXMM),             /*            66 0f 3a 41 /r ib dppd xmm1, xmm2/m128, imm8 */

	I(0x42, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 0) "vmpsadbw\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM), /* VEX.128.66.0f3a.WIG 42 /r ib vmpsadbw xmm1, xmm2, xmm3/m128, imm8 */
	I(0x42, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(1, 1, 0, 1) "vmpsadbw\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM), /* VEX.256.66.0f3a.WIG 42 /r ib vmpsadbw ymm1, ymm2, ymm3/m256, imm8 */
	I(0x42, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VDBPSADBW_XMM)),                    /* EVEX.128.66.0f3a.W0 42 /r ib vdbpsadbw xmm1{k1}{z}, xmm2, xmm3/m128, imm8 */
	I(0x42, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VDBPSADBW_YMM)),                    /* EVEX.256.66.0f3a.W0 42 /r ib vdbpsadbw ymm1{k1}{z}, ymm2, ymm3/m256, imm8 */
	I(0x42, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VDBPSADBW_ZMM)),                    /* EVEX.512.66.0f3a.W0 42 /r ib vdbpsadbw zmm1{k1}{z}, zmm2, zmm3/m512, imm8 */
	I(0x42, IF_66|IF_MODRM,        "mpsadbw\t" OP_U8 OP_RM128_XMM OP_RXMM),                                   /*            66 0f 3a 42 /r ib mpsadbw xmm1, xmm2/m128, imm8 */

	I(0x43, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VSHUFI32X4_YMM)), /* EVEX.256.66.0f3a.W0 43 /r ib vshufi32x4 ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst, imm8 */
	I(0x43, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VSHUFI32X4_ZMM)), /* EVEX.512.66.0f3a.W0 43 /r ib vshufi32x4 zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst, imm8 */
	I(0x43, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VSHUFI64X2_YMM)), /* EVEX.256.66.0f3a.W1 43 /r ib vshufi64x2 ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst, imm8 */
	I(0x43, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VSHUFI64X2_ZMM)), /* EVEX.512.66.0f3a.W1 43 /r ib vshufi64x2 zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst, imm8 */

	I(0x44, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPCLMULQDQ)), /* VEX.128.66.0f3a.WIG 44 /r ib vpclmulqdq xmm1, xmm2, xmm3/m128, imm8 */
	I(0x44, IF_66|IF_MODRM,        LONGREPR(LO_PCLMULQDQ)),                             /*            66 0f 3a 44 /r ib pclmulqdq xmm1, xmm2/m128, imm8 */

	I(0x46, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPERM2I128)), /* VEX.256.66.0f3a.W0 46 /r ib vperm2i128 ymm1, ymm2, ymm3/m256, imm8 */

	I(0x4a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VBLENDVPS_XMM)), /* VEX.128.66.0f3a.W0 4a /r /is4 vblendvps xmm1, xmm2, xmm3/m128, xmm4 */
	I(0x4a, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VBLENDVPS_YMM)), /* VEX.256.66.0f3a.W0 4a /r /is4 vblendvps ymm1, ymm2, ymm3/m256, ymm4 */

	I(0x4b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VBLENDVPD_XMM)), /* VEX.128.66.0f3a.W0 4b /r /is4 vblendvpd xmm1, xmm2, xmm3/m128, xmm4 */
	I(0x4b, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VBLENDVPD_YMM)), /* VEX.256.66.0f3a.W0 4b /r /is4 vblendvpd ymm1, ymm2, ymm3/m256, ymm4 */
	
	I(0x4c, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VPBLENDVB_XMM)), /* VEX.128.66.0f3a.W0 4c /r /is4 vpblendvb xmm1, xmm2, xmm3/m128, xmm4 */
	I(0x4c, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VPBLENDVB_YMM)), /* VEX.256.66.0f3a.W0 4c /r /is4 vpblendvb ymm1, ymm2, ymm3/m256, ymm4 */

	I(0x50, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vrangepd\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f3a.W1 50 /r ib vrangepd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst, imm8 */
	I(0x50, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vrangepd\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f3a.W1 50 /r ib vrangepd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst, imm8 */
	I(0x50, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VRANGEPD)),                          /* EVEX.512.66.0f3a.W1 50 /r ib vrangepd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{sae}, imm8 */
	I(0x50, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vrangeps\t" OP_U8 OP_RM128_XMM__OP_VRXMM__OP_RXMM_MASK), /* EVEX.128.66.0f3a.W0 50 /r ib vrangeps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst, imm8 */
	I(0x50, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vrangeps\t" OP_U8 OP_RM256_YMM__OP_VRYMM__OP_RYMM_MASK), /* EVEX.256.66.0f3a.W0 50 /r ib vrangeps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst, imm8 */
	I(0x50, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VRANGEPS)),                          /* EVEX.512.66.0f3a.W0 50 /r ib vrangeps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{sae}, imm8 */

	I(0x51, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VRANGESS)), /* EVEX.LIG.66.0f3a.W0 51 /r vrangess xmm1{k1}{z}, xmm2, xmm3/m32{sae}, imm8 */
	I(0x51, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VRANGESD)), /* EVEX.LIG.66.0f3a.W1 51 /r vrangesd xmm1{k1}{z}, xmm2, xmm3/m64{sae}, imm8 */

	I(0x54, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VFIXUPIMMPD_XMM)), /* EVEX.128.66.0f3a.W1 54 /r ib vfixupimmpd xmm1{k1}{z}, xmm2, xmm3/m128/m64bcst, imm8 */
	I(0x54, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VFIXUPIMMPD_YMM)), /* EVEX.256.66.0f3a.W1 54 /r ib vfixupimmpd ymm1{k1}{z}, ymm2, ymm3/m256/m64bcst, imm8 */
	I(0x54, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VFIXUPIMMPD_ZMM)), /* EVEX.512.66.0f3a.W1 54 /r ib vfixupimmpd zmm1{k1}{z}, zmm2, zmm3/m512/m64bcst{sae}, imm8 */
	I(0x54, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VFIXUPIMMPS_XMM)), /* EVEX.128.66.0f3a.W0 54 /r vfixupimmps xmm1{k1}{z}, xmm2, xmm3/m128/m32bcst, imm8 */
	I(0x54, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VFIXUPIMMPS_YMM)), /* EVEX.256.66.0f3a.W0 54 /r vfixupimmps ymm1{k1}{z}, ymm2, ymm3/m256/m32bcst, imm8 */
	I(0x54, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VFIXUPIMMPS_ZMM)), /* EVEX.512.66.0f3a.W0 54 /r ib vfixupimmps zmm1{k1}{z}, zmm2, zmm3/m512/m32bcst{sae}, imm8 */

	I(0x55, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VFIXUPIMMSD)), /* EVEX.LIG.66.0f3a.W1 55 /r ib vfixupimmsd xmm1{k1}{z}, xmm2, xmm3/m64{sae}, imm8 */
	I(0x55, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VFIXUPIMMSS)), /* EVEX.LIG.66.0f3a.W0 55 /r ib vfixupimmss xmm1{k1}{z}, xmm2, xmm3/m32{sae}, imm8 */

	I(0x56, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VREDUCEPD_XMM)), /* EVEX.128.66.0f3a.W1 56 /r ib vreducepd xmm1{k1}{z}, xmm2/m128/m64bcst, imm8 */
	I(0x56, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VREDUCEPD_YMM)), /* EVEX.256.66.0f3a.W1 56 /r ib vreducepd ymm1{k1}{z}, ymm2/m256/m64bcst, imm8 */
	I(0x56, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VREDUCEPD_ZMM)), /* EVEX.512.66.0f3a.W1 56 /r ib vreducepd zmm1{k1}{z}, zmm2/m512/m64bcst{sae}, imm8 */
	I(0x56, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VREDUCEPS_XMM)), /* EVEX.128.66.0f3a.W0 56 /r ib vreduceps xmm1{k1}{z}, xmm2/m128/m32bcst, imm8 */
	I(0x56, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VREDUCEPS_YMM)), /* EVEX.256.66.0f3a.W0 56 /r ib vreduceps ymm1{k1}{z}, ymm2/m256/m32bcst, imm8 */
	I(0x56, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VREDUCEPS_ZMM)), /* EVEX.512.66.0f3a.W0 56 /r ib vreduceps zmm1{k1}{z}, zmm2/m512/m32bcst{sae}, imm8 */

	I(0x57, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VREDUCESS)), /* EVEX.LIG.66.0f3a.W0 57 /r ib vreducess xmm1{k1}{z}, xmm2, xmm3/m32{sae}, imm8 */
	I(0x57, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VREDUCESD)), /* EVEX.LIG.66.0f3a.W1 57 /r vreducesd xmm1{k1}{z}, xmm2, xmm3/m64{sae}, imm8 */

	I(0x60, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPCMPESTRM)), /* VEX.128.66.0f3a.WIG 60 /r ib vpcmpestrm xmm1, xmm2/m128, imm8 */
	I(0x60, IF_66|IF_MODRM,        LONGREPR(LO_PCMPESTRM)),                             /*            66 0f 3a 60 /r ib pcmpestrm xmm1, xmm2/m128, imm8 */

	I(0x61, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPCMPESTRI)), /* VEX.128.66.0f3a.WIG 61 /r ib vpcmpestri xmm1, xmm2/m128, imm8 */
	I(0x61, IF_66|IF_MODRM,        LONGREPR(LO_PCMPESTRI)),                             /*            66 0f 3a 61 /r ib pcmpestri xmm1, xmm2/m128, imm8 */

	I(0x62, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPCMPISTRM)), /* VEX.128.66.0f3a.WIG 62 /r ib vpcmpistrm xmm1, xmm2/m128, imm8 */
	I(0x62, IF_66|IF_MODRM,        LONGREPR(LO_PCMPISTRM)),                             /*            66 0f 3a 62 /r ib pcmpistrm xmm1, xmm2/m128, imm8 */

	I(0x63, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VPCMPISTRI)), /* VEX.128.66.0f3a.WIG 63 /r ib vpcmpistri xmm1, xmm2/m128, imm8 */
	I(0x63, IF_66|IF_MODRM,        LONGREPR(LO_PCMPISTRI)),                             /*            66 0f 3a 63 /r ib pcmpistri xmm1, xmm2/m128, imm8 */

	I(0x66, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 0), LO_VFPCLASSPD_XMM)), /* EVEX.128.66.0f3a.W1 66 /r ib vfpclasspd k2{k1}, xmm2/m128/m64bcst, imm8 */
	I(0x66, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 1), LO_VFPCLASSPD_YMM)), /* EVEX.256.66.0f3a.W1 66 /r ib vfpclasspd k2{k1}, ymm2/m256/m64bcst, imm8 */
	I(0x66, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 1, 2), LO_VFPCLASSPD_ZMM)), /* EVEX.512.66.0f3a.W1 66 /r ib vfpclasspd k2{k1}, zmm2/m512/m64bcst, imm8 */

	I(0x66, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 0), LO_VFPCLASSPS_XMM)), /* EVEX.128.66.0f3a.W0 66 /r ib vfpclassps k2{k1}, xmm2/m128/m32bcst, imm8 */
	I(0x66, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 1), LO_VFPCLASSPS_YMM)), /* EVEX.256.66.0f3a.W0 66 /r ib vfpclassps k2{k1}, ymm2/m256/m32bcst, imm8 */
	I(0x66, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 0, 0, 2), LO_VFPCLASSPS_ZMM)), /* EVEX.512.66.0f3a.W0 66 /r ib vfpclassps k2{k1}, zmm2/m512/m32bcst, imm8 */

	I(0x67, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 1), LO_VFPCLASSSD)), /* EVEX.LIG.66.0f3a.W1 67 /r ib vfpclasssd k2{k1}, xmm2/m64, imm8 */

	I(0x67, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0_LIG(0, 0, 0), LO_VFPCLASSSS)), /* EVEX.LIG.66.0f3a.W0 67 /r vfpclassss k2{k1}, xmm2/m32, imm8 */

	I(0xcc, IF_MODRM, LONGREPR(LO_SHA1RNDS4)),

	I(0xce, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VGF2P8AFFINEQB)), /* VEX.128.66.0f3a.WIG ce /r ib vgf2p8affineqb xmm1, xmm2/m128, imm8 */
	I(0xce, IF_66|IF_MODRM,        LONGREPR(LO_GF2P8AFFINEQB)),                             /*             66 0f3a ce /r ib gf2p8affineqb xmm1, xmm2/m128, imm8 */

	I(0xcf, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VGF2P8AFFINEINVQB)), /* VEX.128.66.0f3a.WIG cf /r ib vgf2p8affineinvqb xmm1, xmm2/m128, imm8 */
	I(0xcf, IF_66|IF_MODRM,        LONGREPR(LO_GF2P8AFFINEINVQB)),                             /*             66 0f3a cf /r ib gf2p8affineinvqb xmm1, xmm2/m128, imm8 */

	I(0xdf, IF_66|IF_VEX|IF_MODRM, LONGREPR_B(B_OP_VEX_B0(0, 1, 0, 0), LO_VAESKEYGENASSIST)), /* VEX.128.66.0f3a.WIG df /r ib vaeskeygenassist xmm1, xmm2/m128, imm8 */
	I(0xdf, IF_66|IF_MODRM,        LONGREPR(LO_AESKEYGENASSIST)),                             /*            66 0f 3a df /r ib aeskeygenassist xmm1, xmm2/m128, imm8 */

	I(0xf0, IF_F2|IF_VEXW0|IF_MODRM, "rorxl\t" OP_U8 OP_RM32 OP_R32),
	I(0xf0, IF_F2|IF_VEXW1|IF_MODRM, "rorxq\t" OP_U8 OP_RM64 OP_R64),

	I(0, 0, "")
/*[[[end:ops_0f3a]]]*/
};
/* clang-format on */

#if 0
	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vgatherdpd\txmm, vm32x, xmm"), /* VEX.128.66.0f38.W1 92 /r vgatherdpd xmm1, vm32x, xmm2 */
	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vgatherdpd\tymm, vm32x, ymm"), /* VEX.256.66.0f38.W1 92 /r vgatherdpd ymm1, vm32x, ymm2 */
	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vgatherqpd\txmm, vm64x, xmm"), /* VEX.128.66.0f38.W1 93 /r vgatherqpd xmm1, vm64x, xmm2 */
	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vgatherqpd\tymm, vm64y, ymm"), /* VEX.256.66.0f38.W1 93 /r vgatherqpd ymm1, vm64y, ymm2 */

	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vgatherdps\txmm{k1}, vm32x"), /* EVEX.128.66.0f38.W0 92 /vsib vgatherdps xmm1{k1}, vm32x */
	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vgatherdps\tymm{k1}, vm32y"), /* EVEX.256.66.0f38.W0 92 /vsib vgatherdps ymm1{k1}, vm32y */
	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vgatherdps\tzmm{k1}, vm32z"), /* EVEX.512.66.0f38.W0 92 /vsib vgatherdps zmm1{k1}, vm32z */
	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vgatherdpd\txmm{k1}, vm32x"), /* EVEX.128.66.0f38.W1 92 /vsib vgatherdpd xmm1{k1}, vm32x */
	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vgatherdpd\tymm{k1}, vm32x"), /* EVEX.256.66.0f38.W1 92 /vsib vgatherdpd ymm1{k1}, vm32x */
	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vgatherdpd\tzmm{k1}, vm32y"), /* EVEX.512.66.0f38.W1 92 /vsib vgatherdpd zmm1{k1}, vm32y */

	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vgatherdps\txmm, vm32x, xmm"), /* VEX.128.66.0f38.W0 92 /r vgatherdps xmm1, vm32x, xmm2 */
	I(0x92, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vgatherdps\tymm, vm32y, ymm"), /* VEX.256.66.0f38.W0 92 /r vgatherdps ymm1, vm32y, ymm2 */
	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vgatherqps\txmm, vm64x, xmm"), /* VEX.128.66.0f38.W0 93 /r vgatherqps xmm1, vm64x, xmm2 */
	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vgatherqps\txmm, vm64y, xmm"), /* VEX.256.66.0f38.W0 93 /r vgatherqps xmm1, vm64y, xmm2 */

	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vgatherqps\txmm{k1}, vm64x"), /* EVEX.128.66.0f38.W0 93 /vsib vgatherqps xmm1{k1}, vm64x */
	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vgatherqps\txmm{k1}, vm64y"), /* EVEX.256.66.0f38.W0 93 /vsib vgatherqps xmm1{k1}, vm64y */
	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vgatherqps\tymm{k1}, vm64z"), /* EVEX.512.66.0f38.W0 93 /vsib vgatherqps ymm1{k1}, vm64z */
	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vgatherqpd\txmm{k1}, vm64x"), /* EVEX.128.66.0f38.W1 93 /vsib vgatherqpd xmm1{k1}, vm64x */
	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vgatherqpd\tymm{k1}, vm64y"), /* EVEX.256.66.0f38.W1 93 /vsib vgatherqpd ymm1{k1}, vm64y */
	I(0x93, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vgatherqpd\tzmm{k1}, vm64z"), /* EVEX.512.66.0f38.W1 93 /vsib vgatherqpd zmm1{k1}, vm64z */

	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpgatherdd\txmm, vm32x, xmm"), /* VEX.128.66.0f38.W0 90 /r vpgatherdd xmm1, vm32x, xmm2 */
	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpgatherdd\tymm, vm32y, ymm"), /* VEX.256.66.0f38.W0 90 /r vpgatherdd ymm1, vm32y, ymm2 */
	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpgatherqd\txmm, vm64x, xmm"), /* VEX.128.66.0f38.W0 91 /r vpgatherqd xmm1, vm64x, xmm2 */
	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpgatherqd\txmm, vm64y, xmm"), /* VEX.256.66.0f38.W0 91 /r vpgatherqd xmm1, vm64y, xmm2 */

	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpgatherdd\txmm{k1}, vm32x"), /* EVEX.128.66.0f38.W0 90 /vsib vpgatherdd xmm1{k1}, vm32x */
	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpgatherdd\tymm{k1}, vm32y"), /* EVEX.256.66.0f38.W0 90 /vsib vpgatherdd ymm1{k1}, vm32y */
	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpgatherdd\tzmm{k1}, vm32z"), /* EVEX.512.66.0f38.W0 90 /vsib vpgatherdd zmm1{k1}, vm32z */
	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpgatherdq\txmm{k1}, vm32x"), /* EVEX.128.66.0f38.W1 90 /vsib vpgatherdq xmm1{k1}, vm32x */
	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpgatherdq\tymm{k1}, vm32x"), /* EVEX.256.66.0f38.W1 90 /vsib vpgatherdq ymm1{k1}, vm32x */
	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpgatherdq\tzmm{k1}, vm32y"), /* EVEX.512.66.0f38.W1 90 /vsib vpgatherdq zmm1{k1}, vm32y */

	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpgatherqd\txmm{k1}, vm64x"), /* EVEX.128.66.0f38.W0 91 /vsib vpgatherqd xmm1{k1}, vm64x */
	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpgatherqd\txmm{k1}, vm64y"), /* EVEX.256.66.0f38.W0 91 /vsib vpgatherqd xmm1{k1}, vm64y */
	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpgatherqd\tymm{k1}, vm64z"), /* EVEX.512.66.0f38.W0 91 /vsib vpgatherqd ymm1{k1}, vm64z */
	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpgatherqq\txmm{k1}, vm64x"), /* EVEX.128.66.0f38.W1 91 /vsib vpgatherqq xmm1{k1}, vm64x */
	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpgatherqq\tymm{k1}, vm64y"), /* EVEX.256.66.0f38.W1 91 /vsib vpgatherqq ymm1{k1}, vm64y */
	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpgatherqq\tzmm{k1}, vm64z"), /* EVEX.512.66.0f38.W1 91 /vsib vpgatherqq zmm1{k1}, vm64z */

	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpgatherdq\txmm, vm32x, xmm"), /* VEX.128.66.0f38.W1 90 /r vpgatherdq xmm1, vm32x, xmm2 */
	I(0x90, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpgatherdq\tymm, vm32x, ymm"), /* VEX.256.66.0f38.W1 90 /r vpgatherdq ymm1, vm32x, ymm2 */
	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpgatherqq\txmm, vm64x, xmm"), /* VEX.128.66.0f38.W1 91 /r vpgatherqq xmm1, vm64x, xmm2 */
	I(0x91, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpgatherqq\tymm, vm64y, ymm"), /* VEX.256.66.0f38.W1 91 /r vpgatherqq ymm1, vm64y, ymm2 */

	I(0xa0, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpscatterdd\tvm32x{k1}, xmm"), /* EVEX.128.66.0f38.W0 a0 /vsib vpscatterdd vm32x{k1}, xmm1 */
	I(0xa0, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpscatterdd\tvm32y{k1}, ymm"), /* EVEX.256.66.0f38.W0 a0 /vsib vpscatterdd vm32y{k1}, ymm1 */
	I(0xa0, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpscatterdd\tvm32z{k1}, zmm"), /* EVEX.512.66.0f38.W0 a0 /vsib vpscatterdd vm32z{k1}, zmm1 */
	I(0xa0, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpscatterdq\tvm32x{k1}, xmm"), /* EVEX.128.66.0f38.W1 a0 /vsib vpscatterdq vm32x{k1}, xmm1 */
	I(0xa0, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpscatterdq\tvm32x{k1}, ymm"), /* EVEX.256.66.0f38.W1 a0 /vsib vpscatterdq vm32x{k1}, ymm1 */
	I(0xa0, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpscatterdq\tvm32y{k1}, zmm"), /* EVEX.512.66.0f38.W1 a0 /vsib vpscatterdq vm32y{k1}, zmm1 */
	I(0xa1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vpscatterqd\tvm64x{k1}, xmm"), /* EVEX.128.66.0f38.W0 a1 /vsib vpscatterqd vm64x{k1}, xmm1 */
	I(0xa1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vpscatterqd\tvm64y{k1}, xmm"), /* EVEX.256.66.0f38.W0 a1 /vsib vpscatterqd vm64y{k1}, xmm1 */
	I(0xa1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vpscatterqd\tvm64z{k1}, ymm"), /* EVEX.512.66.0f38.W0 a1 /vsib vpscatterqd vm64z{k1}, ymm1 */
	I(0xa1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vpscatterqq\tvm64x{k1}, xmm"), /* EVEX.128.66.0f38.W1 a1 /vsib vpscatterqq vm64x{k1}, xmm1 */
	I(0xa1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vpscatterqq\tvm64y{k1}, ymm"), /* EVEX.256.66.0f38.W1 a1 /vsib vpscatterqq vm64y{k1}, ymm1 */
	I(0xa1, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vpscatterqq\tvm64z{k1}, zmm"), /* EVEX.512.66.0f38.W1 a1 /vsib vpscatterqq vm64z{k1}, zmm1 */

	I(0xa2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vscatterdps\tvm32x{k1}, xmm"), /* EVEX.128.66.0f38.W0 a2 /vsib vscatterdps vm32x{k1}, xmm1 */
	I(0xa2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vscatterdps\tvm32y{k1}, ymm"), /* EVEX.256.66.0f38.W0 a2 /vsib vscatterdps vm32y{k1}, ymm1 */
	I(0xa2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vscatterdps\tvm32z{k1}, zmm"), /* EVEX.512.66.0f38.W0 a2 /vsib vscatterdps vm32z{k1}, zmm1 */
	I(0xa2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vscatterdpd\tvm32x{k1}, xmm"), /* EVEX.128.66.0f38.W1 a2 /vsib vscatterdpd vm32x{k1}, xmm1 */
	I(0xa2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vscatterdpd\tvm32x{k1}, ymm"), /* EVEX.256.66.0f38.W1 a2 /vsib vscatterdpd vm32x{k1}, ymm1 */
	I(0xa2, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vscatterdpd\tvm32y{k1}, zmm"), /* EVEX.512.66.0f38.W1 a2 /vsib vscatterdpd vm32y{k1}, zmm1 */
	I(0xa3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 0) "vscatterqps\tvm64x{k1}, xmm"), /* EVEX.128.66.0f38.W0 a3 /vsib vscatterqps vm64x{k1}, xmm1 */
	I(0xa3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 1) "vscatterqps\tvm64y{k1}, xmm"), /* EVEX.256.66.0f38.W0 a3 /vsib vscatterqps vm64y{k1}, xmm1 */
	I(0xa3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 0, 2) "vscatterqps\tvm64z{k1}, ymm"), /* EVEX.512.66.0f38.W0 a3 /vsib vscatterqps vm64z{k1}, ymm1 */
	I(0xa3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 0) "vscatterqpd\tvm64x{k1}, xmm"), /* EVEX.128.66.0f38.W1 a3 /vsib vscatterqpd vm64x{k1}, xmm1 */
	I(0xa3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 1) "vscatterqpd\tvm64y{k1}, ymm"), /* EVEX.256.66.0f38.W1 a3 /vsib vscatterqpd vm64y{k1}, ymm1 */
	I(0xa3, IF_66|IF_VEX|IF_MODRM, OP_VEX_B0(0, 0, 1, 2) "vscatterqpd\tvm64z{k1}, zmm"), /* EVEX.512.66.0f38.W1 a3 /vsib vscatterqpd vm64z{k1}, zmm1 */

	I(0xc6, IF_66|IF_VEX|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 0, 2) "/vsib vgatherpf0dps\tvm32z{k1}"), /* EVEX.512.66.0f38.W0 c6 /1 /vsib vgatherpf0dps vm32z{k1} */
	I(0xc7, IF_66|IF_VEX|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 0, 2) "/vsib vgatherpf0qps\tvm64z{k1}"), /* EVEX.512.66.0f38.W0 c7 /1 /vsib vgatherpf0qps vm64z{k1} */
	I(0xc6, IF_66|IF_VEX|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 1, 2) "/vsib vgatherpf0dpd\tvm32y{k1}"), /* EVEX.512.66.0f38.W1 c6 /1 /vsib vgatherpf0dpd vm32y{k1} */
	I(0xc7, IF_66|IF_VEX|IF_MODRM|IF_REG1, OP_VEX_B0(0, 0, 1, 2) "/vsib vgatherpf0qpd\tvm64z{k1}"), /* EVEX.512.66.0f38.W1 c7 /1 /vsib vgatherpf0qpd vm64z{k1} */

	I(0xc6, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 0, 2) "/vsib vgatherpf1dps\tvm32z{k1}"), /* EVEX.512.66.0f38.W0 c6 /2 /vsib vgatherpf1dps vm32z{k1} */
	I(0xc7, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 0, 2) "/vsib vgatherpf1qps\tvm64z{k1}"), /* EVEX.512.66.0f38.W0 c7 /2 /vsib vgatherpf1qps vm64z{k1} */
	I(0xc6, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 1, 2) "/vsib vgatherpf1dpd\tvm32y{k1}"), /* EVEX.512.66.0f38.W1 c6 /2 /vsib vgatherpf1dpd vm32y{k1} */
	I(0xc7, IF_66|IF_VEX|IF_MODRM|IF_REG2, OP_VEX_B0(0, 0, 1, 2) "/vsib vgatherpf1qpd\tvm64z{k1}"), /* EVEX.512.66.0f38.W1 c7 /2 /vsib vgatherpf1qpd vm64z{k1} */
#endif




/*[[[deemon
import * from deemon;
local mytext = File.open(__FILE__, "r").read().decode("utf-8");

@@Calculate the offsets of opcodes and return a 256-element vector of offset indices
@@The return value is (OffsetTable, OpcodeCount)
function calculateOpcodeOffsets(start: string, end: string): ({int...}, int) {
	local data = mytext[mytext.index(start) + #start:mytext.index(end)].strip();
	local result = [none] * 256;
	local prev_opcode = -1;
	local curr_offset = 0;
	for (local l: data.splitlines(false)) {
		l = l.lstrip();
		if (!l.startswith("I("))
			continue;
		local line_opcode;
		try {
			line_opcode = l.scanf("I( %[xX0-9a-fA-F]")...;
		} catch (...) {
			print File.stderr: "ERROR: Failed to parse line:", repr l;
			throw;
		}
		if (line_opcode == "0")
			break; // Sentinel marker
		line_opcode = int(line_opcode);
		if (line_opcode < prev_opcode) {
			print File.stderr: "ERROR: Invalid opcode ordering";
			print File.stderr: "Line for opcode", line_opcode.hex(), ":", repr l;
			print File.stderr: "Should come before line for opcode", prev_opcode.hex();
			throw Error("Invalid opcode ordering");
		}
		if (result[line_opcode] is none)
			result[line_opcode] = curr_offset;
		prev_opcode = line_opcode;
		++curr_offset;
	}
	for (local i: [:256]) {
		// All undefined opcodes should point at the end of the tables.
		if (result[i] is none)
			result[i] = curr_offset;
	}
	return (result, curr_offset + 1);
}

function generateOffsetTable(name: string) {
	final local START_MARKER_PATTERN = "/" "*[[[start:{}]]]*" "/";
	final local END_MARKER_PATTERN = "/" "*[[[end:{}]]]*" "/";
	local offsets, count = calculateOpcodeOffsets(
		START_MARKER_PATTERN.format({ name }),
		END_MARKER_PATTERN.format({ name }))...;
	local maxOffset = offsets[0xff];
	local offsetType = "u8";
	if (maxOffset > 0xff)
		offsetType = "u16";
	if (maxOffset > 0xffff)
		offsetType = "u32";
	print "#define HAVE_",;
	print name.upper(),;
	print "_OFFSETS 1";
	print "STATIC_ASSERT(COMPILER_LENOF(",;
	print name,;
	print ") == ",;
	print count,;
	print ");";
	print "PRIVATE ",;
	print offsetType,;
	print " const ",;
	print name,;
	print "_offsets[256] = {";
	for (local i: [:256]) {
		if ((i % 16) == 0)
			print "\t",;
		else {
			print " ",;
		}
		print offsets[i],;
		if (i != 255)
			print ",",;
		if ((i % 16) == 15)
			print "\n",;
	}
	print "};";
	print;
}
generateOffsetTable("ops");
generateOffsetTable("ops_0f");
generateOffsetTable("ops_0f38");
generateOffsetTable("ops_0f3a");
]]]*/
#define HAVE_OPS_OFFSETS 1
STATIC_ASSERT(COMPILER_LENOF(ops) == 953);
PRIVATE u16 const ops_offsets[256] = {
	0, 1, 4, 5, 8, 9, 12, 14, 16, 17, 20, 21, 24, 25, 28, 952,
	30, 31, 34, 35, 38, 39, 42, 44, 46, 47, 50, 51, 54, 55, 58, 60,
	62, 63, 66, 67, 70, 71, 952, 74, 75, 76, 79, 80, 83, 84, 952, 87,
	88, 89, 92, 93, 96, 97, 952, 100, 101, 102, 105, 106, 109, 110, 952, 113,
	114, 116, 118, 120, 122, 124, 126, 128, 130, 132, 134, 136, 138, 140, 142, 144,
	146, 150, 154, 158, 162, 166, 170, 174, 178, 182, 186, 190, 194, 198, 202, 206,
	210, 212, 214, 216, 952, 952, 952, 952, 217, 220, 223, 224, 227, 229, 233, 235,
	239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254,
	255, 263, 287, 295, 319, 320, 323, 324, 327, 328, 331, 332, 335, 338, 341, 344,
	350, 357, 363, 369, 375, 381, 387, 393, 399, 400, 402, 404, 406, 409, 412, 413,
	414, 416, 420, 422, 426, 428, 434, 437, 446, 447, 450, 452, 458, 460, 466, 469,
	478, 480, 482, 484, 486, 488, 490, 492, 494, 500, 506, 512, 518, 524, 530, 536,
	542, 550, 574, 576, 578, 580, 582, 584, 589, 590, 591, 592, 593, 594, 595, 596,
	600, 608, 632, 640, 664, 665, 666, 667, 668, 684, 737, 750, 774, 788, 823, 838,
	863, 864, 865, 866, 869, 870, 872, 873, 875, 877, 879, 881, 882, 883, 885, 886,
	952, 888, 952, 952, 889, 890, 891, 899, 923, 924, 925, 926, 927, 928, 929, 931
};

#define HAVE_OPS_0F_OFFSETS 1
STATIC_ASSERT(COMPILER_LENOF(ops_0f) == 1509);
PRIVATE u16 const ops_0f_offsets[256] = {
	0, 6, 36, 38, 1508, 40, 42, 43, 45, 46, 47, 48, 1508, 49, 1508, 1508,
	51, 75, 97, 118, 124, 136, 148, 163, 169, 1508, 173, 179, 184, 1508, 1508, 185,
	187, 189, 191, 193, 195, 1508, 196, 1508, 197, 209, 221, 231, 243, 253, 263, 269,
	275, 276, 277, 278, 279, 280, 281, 282, 1508, 1508, 1508, 1508, 1508, 1508, 1508, 283,
	284, 287, 294, 301, 304, 311, 318, 325, 332, 335, 338, 345, 351, 354, 357, 360,
	363, 375, 393, 398, 403, 415, 427, 439, 451, 469, 487, 505, 526, 544, 562, 580,
	598, 603, 608, 615, 620, 625, 630, 637, 642, 647, 652, 659, 664, 670, 676, 682,
	706, 721, 736, 772, 794, 799, 804, 811, 814, 832, 852, 870, 880, 886, 892, 898,
	922, 924, 926, 928, 930, 932, 934, 936, 938, 940, 942, 944, 946, 948, 950, 952,
	954, 959, 964, 969, 974, 975, 976, 977, 978, 983, 988, 989, 990, 991, 992, 993,
	994, 997, 1000, 1001, 1004, 1007, 1508, 1508, 1010, 1013, 1016, 1017, 1020, 1023, 1026, 1058,
	1061, 1062, 1065, 1068, 1071, 1074, 1077, 1080, 1082, 1085, 1086, 1098, 1101, 1107, 1113, 1116,
	1118, 1119, 1122, 1140, 1142, 1146, 1154, 1166, 1182, 1186, 1190, 1194, 1198, 1202, 1206, 1210,
	1214, 1220, 1225, 1232, 1239, 1246, 1251, 1253, 1261, 1266, 1271, 1276, 1286, 1291, 1296, 1301,
	1311, 1316, 1321, 1331, 1336, 1341, 1346, 1367, 1374, 1379, 1384, 1389, 1399, 1404, 1409, 1414,
	1424, 1427, 1432, 1439, 1446, 1453, 1458, 1463, 1466, 1471, 1476, 1483, 1490, 1495, 1500, 1507
};

#define HAVE_OPS_0F38_OFFSETS 1
STATIC_ASSERT(COMPILER_LENOF(ops_0f38) == 758);
PRIVATE u16 const ops_0f38_offsets[256] = {
	0, 5, 9, 13, 17, 22, 26, 30, 34, 38, 42, 46, 51, 54, 59, 61,
	63, 70, 76, 82, 88, 98, 108, 112, 115, 120, 125, 130, 132, 137, 142, 149,
	152, 159, 166, 173, 180, 187, 196, 208, 220, 232, 244, 253, 259, 267, 271, 273,
	275, 282, 289, 296, 303, 310, 319, 323, 329, 339, 354, 361, 370, 374, 383, 387,
	396, 405, 407, 413, 415, 421, 427, 433, 757, 757, 757, 757, 439, 445, 446, 452,
	757, 757, 454, 455, 757, 757, 757, 757, 456, 459, 467, 472, 757, 757, 757, 757,
	757, 757, 757, 757, 474, 480, 486, 757, 757, 757, 757, 757, 757, 757, 757, 757,
	757, 757, 757, 757, 757, 492, 498, 504, 510, 513, 516, 519, 522, 528, 534, 540,
	546, 548, 550, 552, 757, 757, 757, 757, 555, 561, 567, 573, 579, 583, 589, 757,
	757, 757, 757, 757, 757, 757, 593, 599, 605, 611, 613, 620, 757, 757, 757, 757,
	757, 757, 757, 757, 757, 757, 623, 629, 635, 641, 643, 650, 757, 757, 757, 757,
	757, 757, 757, 757, 653, 656, 659, 665, 671, 677, 679, 685, 757, 757, 757, 757,
	757, 757, 757, 757, 687, 757, 757, 757, 693, 696, 697, 700, 702, 703, 757, 704,
	757, 757, 757, 757, 757, 757, 757, 757, 757, 757, 757, 706, 708, 710, 712, 714,
	757, 757, 757, 757, 757, 757, 757, 757, 757, 757, 757, 757, 757, 757, 757, 757,
	716, 721, 727, 729, 757, 735, 741, 747, 755, 757, 757, 757, 757, 757, 757, 757
};

#define HAVE_OPS_0F3A_OFFSETS 1
STATIC_ASSERT(COMPILER_LENOF(ops_0f3a) == 230);
PRIVATE u8 const ops_0f3a_offsets[256] = {
	0, 2, 4, 6, 12, 15, 20, 229, 21, 27, 33, 36, 39, 42, 45, 48,
	229, 229, 229, 229, 53, 56, 59, 63, 65, 70, 75, 77, 229, 79, 82, 88,
	94, 97, 100, 104, 229, 108, 114, 120, 229, 229, 229, 229, 229, 229, 229, 229,
	122, 124, 126, 128, 229, 229, 229, 229, 130, 135, 140, 142, 229, 229, 144, 150,
	156, 159, 161, 167, 171, 229, 173, 229, 229, 229, 174, 176, 178, 229, 229, 229,
	180, 186, 229, 229, 188, 194, 196, 202, 229, 229, 229, 229, 229, 229, 229, 229,
	204, 206, 208, 210, 229, 229, 212, 218, 229, 229, 229, 229, 229, 229, 229, 229,
	229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229,
	229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229,
	229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229,
	229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229,
	229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229,
	229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 220, 229, 221, 223,
	229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 225,
	229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229,
	227, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229
};
//[[[end]]]


DECL_END

#endif /* !GUARD_LIBDISASM_X86_DB_H */