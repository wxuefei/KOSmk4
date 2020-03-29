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
#ifdef __INTELLISENSE__
#define EMU86_EMULATE_CONFIG_WANT_SLDT 1
#define EMU86_EMULATE_CONFIG_WANT_LLDT 1
#define EMU86_EMULATE_CONFIG_WANT_STR  1
#define EMU86_EMULATE_CONFIG_WANT_LTR  1
#define EMU86_EMULATE_CONFIG_WANT_SGDT 1
#define EMU86_EMULATE_CONFIG_WANT_LGDT 1
#define EMU86_EMULATE_CONFIG_WANT_SIDT 1
#define EMU86_EMULATE_CONFIG_WANT_LIDT 1
#define EMU86_EMULATE_CONFIG_WANT_VERR 1
#define EMU86_EMULATE_CONFIG_WANT_VERW 1
#define EMU86_EMULATE_CONFIG_WANT_SMSW 1
#define EMU86_EMULATE_CONFIG_WANT_LMSW 1
#define EMU86_EMULATE_CONFIG_WANT_INVLPG 1
#define EMU86_EMULATE_CONFIG_WANT_LAR 1
#define EMU86_EMULATE_CONFIG_WANT_LSL 1
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

EMU86_INTELLISENSE_BEGIN(pmode) {


#if (EMU86_EMULATE_CONFIG_CHECKERROR ||                                 \
     EMU86_EMULATE_CONFIG_WANT_SLDT || EMU86_EMULATE_CONFIG_WANT_STR || \
     EMU86_EMULATE_CONFIG_WANT_LLDT || EMU86_EMULATE_CONFIG_WANT_LTR || \
     ((CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_64BIT) &&     \
      (EMU86_EMULATE_CONFIG_WANT_VERR || EMU86_EMULATE_CONFIG_WANT_VERW)))

case EMU86_OPCODE_ENCODE(0x0f00): {
	MODRM_DECODE();
	switch (modrm.mi_reg) {


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SLDT
	case 0: {
		/* REX.W + 0F 00 /0     SLDT r/m16     Stores segment selector from LDTR in r64/m16. */
#if EMU86_EMULATE_CONFIG_CHECKUSER
#ifndef EMU86_GETCR4_UMIP_IS_ZERO
		if (EMU86_ISUSER() && EMU86_GETCR4_UMIP()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
			                                                 X86_REGISTER_MISC_LDT, 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* !EMU86_GETCR4_UMIP_IS_ZERO */
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_SLDT && defined(EMU86_EMULATE_SLDT)
		{
			u16 ldtr;
			ldtr = EMU86_EMULATE_SLDT();
			MODRM_SETRMW(ldtr);
		}
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_SLDT && EMU86_EMULATE_SLDT */
		MODRM_NOSUP_SETRMW();
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_SLDT || !EMU86_EMULATE_SLDT */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SLDT */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_STR
	case 1: {
		/* 0F 00 /1     STR r/m16     Stores segment selector from TR in r/m16. */
#if EMU86_EMULATE_CONFIG_CHECKUSER
#ifndef EMU86_GETCR4_UMIP_IS_ZERO
		if (EMU86_ISUSER() && EMU86_GETCR4_UMIP()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
			                                                 X86_REGISTER_MISC_TR, 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* !EMU86_GETCR4_UMIP_IS_ZERO */
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_STR && defined(EMU86_EMULATE_STR)
		{
			u16 tr;
			tr = EMU86_EMULATE_STR();
			MODRM_SETRMW(tr);
		}
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_STR && EMU86_EMULATE_STR */
		MODRM_NOSUP_SETRMW();
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_STR || !EMU86_EMULATE_STR */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_STR */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LLDT
	case 2: {
		/* 0F 00 /2     LLDT r/m16     Load segment selector r/m16 into LDTR. */
#if EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LLDT
		u16 ldtr;
		ldtr = MODRM_GETRMW();
#else /* EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LLDT */
		MODRM_NOSUP_GETRMW();
#endif /* !EMU86_EMULATE_CONFIG_CHECKUSER && !EMU86_EMULATE_CONFIG_WANT_LLDT */
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
			                                                 X86_REGISTER_MISC_LDT, ldtr, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_LLDT && defined(EMU86_EMULATE_LLDT)
		EMU86_EMULATE_LLDT(ldtr);
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_LLDT && EMU86_EMULATE_LLDT */
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_LLDT || !EMU86_EMULATE_LLDT */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LLDT */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LTR
	case 3: {
		/* 0F 00 /3     LTR r/m16     Load r/m16 into task register. */
#if EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LTR
		u16 tr;
		tr = MODRM_GETRMW();
#else /* EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LTR */
		MODRM_NOSUP_GETRMW();
#endif /* !EMU86_EMULATE_CONFIG_CHECKUSER && !EMU86_EMULATE_CONFIG_WANT_LTR */
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
			                                                 X86_REGISTER_MISC_TR, tr, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_LTR && defined(EMU86_EMULATE_LTR)
		EMU86_EMULATE_LTR(tr);
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_LTR && EMU86_EMULATE_LTR */
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_LTR || !EMU86_EMULATE_LTR */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LTR */


#if (CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_64BIT || \
     (EMU86_EMULATE_CONFIG_CHECKERROR && CONFIG_LIBEMU86_WANT_16BIT))
#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_VERR
	case 4: {
		/* 0F 00 /4     VERR r/m16     Set ZF=1 if segment specified with r/m16 can be read. */
#if CONFIG_LIBEMU86_WANT_16BIT
#define NEED_return_unsupported_instruction
		if (EMU86_F_IS16(op_flags)) /* This also includes vm86! */
			goto return_unsupported_instruction;
#endif /* CONFIG_LIBEMU86_WANT_16BIT */
#if EMU86_EMULATE_CONFIG_WANT_VERR && defined(EMU86_EMULATE_VERR)
		{
			bool ok;
			u16 segment_index;
			segment_index = MODRM_GETRMW();
			ok = EMU86_EMULATE_VERR(segment_index);
			EMU86_MSKFLAGS(~EFLAGS_ZF, ok ? EFLAGS_ZF : 0);
		}
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_VERR && EMU86_EMULATE_VERR */
		MODRM_NOSUP_GETRMW();
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_VERR || !EMU86_EMULATE_VERR */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_VERR */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_VERW
	case 5: {
		/* 0F 00 /5     VERW r/m16     Set ZF=1 if segment specified with r/m16 can be written. */
#if CONFIG_LIBEMU86_WANT_16BIT
#define NEED_return_unsupported_instruction
		if (EMU86_F_IS16(op_flags)) /* This also includes vm86! */
			goto return_unsupported_instruction;
#endif /* CONFIG_LIBEMU86_WANT_16BIT */
#if EMU86_EMULATE_CONFIG_WANT_VERW && defined(EMU86_EMULATE_VERW)
		{
			bool ok;
			u16 segment_index;
			segment_index = MODRM_GETRMW();
			ok = EMU86_EMULATE_VERW(segment_index);
			EMU86_MSKFLAGS(~EFLAGS_ZF, ok ? EFLAGS_ZF : 0);
		}
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_VERW && EMU86_EMULATE_VERW */
		MODRM_NOSUP_GETRMW();
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_VERW || !EMU86_EMULATE_VERW */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_VERW */
#endif /* CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_64BIT || (EMU86_EMULATE_CONFIG_CHECKERROR && CONFIG_LIBEMU86_WANT_16BIT) */


	default:
#define NEED_return_unknown_instruction_rmreg
		goto return_unknown_instruction_rmreg;
	}
	break;
}
#endif /* EMU86_EMULATE_... */



#if (EMU86_EMULATE_CONFIG_WANT_SGDT || EMU86_EMULATE_CONFIG_WANT_SIDT || \
     EMU86_EMULATE_CONFIG_WANT_LGDT || EMU86_EMULATE_CONFIG_WANT_LIDT || \
     EMU86_EMULATE_CONFIG_WANT_SMSW || EMU86_EMULATE_CONFIG_WANT_LMSW || \
     EMU86_EMULATE_CONFIG_WANT_INVLPG || EMU86_EMULATE_CONFIG_CHECKERROR)
case EMU86_OPCODE_ENCODE(0x0f01): {
	MODRM_DECODE();
	switch (modrm.mi_reg) {

#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SGDT
	case 0: {
		/* 0F 01 /0     SGDT m16&32     Store GDTR to m.
		 * 0F 01 /0     SGDT m16&64     Store GDTR to m. */
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#define NEED_return_expected_memory_modrm_rmreg
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_expected_memory_modrm_rmreg;
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
#if EMU86_EMULATE_CONFIG_CHECKUSER
#ifndef EMU86_GETCR4_UMIP_IS_ZERO
		if (EMU86_ISUSER() && EMU86_GETCR4_UMIP()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
			                                                 IF_64BIT(EMU86_F_IS64(op_flags)
			                                                 ?  X86_REGISTER_MISC_GDT_BASEQ
			                                                 :) X86_REGISTER_MISC_GDT_BASEL,
			                                                 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* !EMU86_GETCR4_UMIP_IS_ZERO */
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_SGDT && defined(EMU86_EMULATE_SGDT)
		{
			byte_t *rmaddr;
			u16 limit;
			EMU86_UREG_TYPE base;
			EMU86_EMULATE_SGDT(limit, base);
			rmaddr = MODRM_MEMADDR();
			IF_64BIT(if (EMU86_F_IS64(op_flags)) {
				EMU86_WRITE_USER_MEMORY(rmaddr, 10);
				EMU86_MEMWRITEW(rmaddr + 0, limit);
				EMU86_MEMWRITEQ(rmaddr + 2, base);
			} else) {
				EMU86_WRITE_USER_MEMORY(rmaddr, 6);
				EMU86_MEMWRITEW(rmaddr + 0, limit);
				EMU86_MEMWRITEL(rmaddr + 2, base);
			}
		}
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_SGDT && EMU86_EMULATE_SGDT */
		EMU86_UNSUPPORTED_MEMACCESS(MODRM_MEMADDR(),
		                            EMU86_F_IS64(op_flags) ? 10 : 6,
		                            false, true);
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_SGDT || !EMU86_EMULATE_SGDT */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SGDT */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SIDT
	case 1: {
		/* 0F 01 /1     SIDT m16&32     Store IDTR to m.
		 * 0F 01 /1     SIDT m16&64     Store IDTR to m. */
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#define NEED_return_expected_memory_modrm_rmreg
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_expected_memory_modrm_rmreg;
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
#if EMU86_EMULATE_CONFIG_CHECKUSER
#ifndef EMU86_GETCR4_UMIP_IS_ZERO
		if (EMU86_ISUSER() && EMU86_GETCR4_UMIP()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
			                                                 IF_64BIT(EMU86_F_IS64(op_flags)
			                                                 ?  X86_REGISTER_MISC_IDT_BASEQ
			                                                 :) X86_REGISTER_MISC_IDT_BASEL,
			                                                 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* !EMU86_GETCR4_UMIP_IS_ZERO */
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_SIDT && defined(EMU86_EMULATE_SIDT)
		{
			u16 limit;
			byte_t *rmaddr;
			EMU86_UREG_TYPE base;
			EMU86_EMULATE_SIDT(limit, base);
			rmaddr = MODRM_MEMADDR();
			IF_64BIT(if (EMU86_F_IS64(op_flags)) {
				EMU86_WRITE_USER_MEMORY(rmaddr, 10);
				EMU86_MEMWRITEW(rmaddr + 0, limit);
				EMU86_MEMWRITEQ(rmaddr + 2, base);
			} else) {
				EMU86_WRITE_USER_MEMORY(rmaddr, 6);
				EMU86_MEMWRITEW(rmaddr + 0, limit);
				EMU86_MEMWRITEL(rmaddr + 2, base);
			}
		}
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_SIDT && EMU86_EMULATE_SIDT */
		EMU86_UNSUPPORTED_MEMACCESS(MODRM_MEMADDR(),
		                            EMU86_F_IS64(op_flags) ? 10 : 6,
		                            false, true);
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_SIDT || !EMU86_EMULATE_SIDT */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SIDT */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LGDT
	case 2: {
		/* 0F 01 /2     LGDT m16&32     Load m into GDTR.
		 * 0F 01 /2     LGDT m16&64     Load m into GDTR. */
#if EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LGDT
		u16 limit;
		EMU86_UREG_TYPE base;
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LGDT */
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#define NEED_return_expected_memory_modrm_rmreg
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_expected_memory_modrm_rmreg;
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
#if EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LGDT
		{
			byte_t *rmaddr;
			rmaddr = MODRM_MEMADDR();
			IF_64BIT(if (EMU86_F_IS64(op_flags)) {
				EMU86_READ_USER_MEMORY(rmaddr, 10);
				limit = EMU86_MEMREADW(rmaddr + 0);
				base  = EMU86_MEMREADQ(rmaddr + 2);
			} else) {
				EMU86_READ_USER_MEMORY(rmaddr, 6);
				limit = EMU86_MEMREADW(rmaddr + 0);
				base  = EMU86_MEMREADL(rmaddr + 2);
			}
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LGDT */
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
			                                                 IF_64BIT(EMU86_F_IS64(op_flags)
			                                                 ?  X86_REGISTER_MISC_GDT_BASEQ
			                                                 :) X86_REGISTER_MISC_GDT_BASEL,
			                                                 base, limit);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_LGDT && defined(EMU86_EMULATE_LGDT)
		EMU86_EMULATE_LGDT(limit, base);
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_LGDT && EMU86_EMULATE_LGDT */
		EMU86_UNSUPPORTED_MEMACCESS(MODRM_MEMADDR(),
		                            EMU86_F_IS64(op_flags) ? 10 : 6,
		                            true, false);
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_LGDT || !EMU86_EMULATE_LGDT */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LGDT */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LIDT
	case 3: {
		/* 0F 01 /3     LIDT m16&32     Load m into IDTR.
		 * 0F 01 /3     LIDT m16&64     Load m into IDTR. */
#if EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LGDT
		u16 limit;
		EMU86_UREG_TYPE base;
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LGDT */
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#define NEED_return_expected_memory_modrm_rmreg
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_expected_memory_modrm_rmreg;
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
#if EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LGDT
		{
			byte_t *rmaddr;
			rmaddr = MODRM_MEMADDR();
			IF_64BIT(if (EMU86_F_IS64(op_flags)) {
				EMU86_READ_USER_MEMORY(rmaddr, 10);
				limit = EMU86_MEMREADW(rmaddr + 0);
				base  = EMU86_MEMREADQ(rmaddr + 2);
			} else) {
				EMU86_READ_USER_MEMORY(rmaddr, 6);
				limit = EMU86_MEMREADW(rmaddr + 0);
				base  = EMU86_MEMREADL(rmaddr + 2);
			}
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LGDT */
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
			                                                 IF_64BIT(EMU86_F_IS64(op_flags)
			                                                 ?  X86_REGISTER_MISC_IDT_BASEQ
			                                                 :) X86_REGISTER_MISC_IDT_BASEL,
			                                                 base, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_LIDT && defined(EMU86_EMULATE_LIDT)
		EMU86_EMULATE_LIDT(limit, base);
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_LIDT && EMU86_EMULATE_LIDT */
		EMU86_UNSUPPORTED_MEMACCESS(MODRM_MEMADDR(),
		                            EMU86_F_IS64(op_flags) ? 10 : 6,
		                            true, false);
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_LIDT || !EMU86_EMULATE_LIDT */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LIDT */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SMSW
	case 4: {
		/* 0F 01 /4     SMSW r/m16     Store machine status word to r/m16. */
#if EMU86_EMULATE_CONFIG_CHECKUSER
#ifndef EMU86_GETCR4_UMIP_IS_ZERO
		if (EMU86_ISUSER() && EMU86_GETCR4_UMIP()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
			                                                 X86_REGISTER_CONTROL_CR0, 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* !EMU86_GETCR4_UMIP_IS_ZERO */
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_SMSW && defined(EMU86_EMULATE_SMSW)
		{
			u16 msw;
			msw = EMU86_EMULATE_SMSW();
			MODRM_SETRMW(msw);
		}
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_SMSW && EMU86_EMULATE_SMSW */
		MODRM_NOSUP_SETRMW();
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_SMSW || !EMU86_EMULATE_SMSW */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SMSW */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LMSW
	case 6: {
		/* 0F 01 /6     LMSW r/m16     Loads r/m16 in machine status word of CR0. */
#if EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LMSW
		u16 msw;
		msw = MODRM_GETRMW();
#else /* EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LMSW */
		MODRM_NOSUP_GETRMW();
#endif /* !EMU86_EMULATE_CONFIG_CHECKUSER && !EMU86_EMULATE_CONFIG_WANT_LMSW */
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
			                                                 X86_REGISTER_CONTROL_CR0, msw, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_LMSW && defined(EMU86_EMULATE_LMSW)
		EMU86_EMULATE_LMSW(msw);
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_LMSW && EMU86_EMULATE_LMSW */
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_LMSW || !EMU86_EMULATE_LMSW */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LMSW */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_INVLPG
	case 7: {
		/* 0F 01 /7     INVLPG m      Invalidate TLB entries for page containing m. */
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#define NEED_return_expected_memory_modrm_rmreg
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_expected_memory_modrm_rmreg;
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
#if EMU86_EMULATE_CONFIG_CHECKUSER
#define NEED_return_privileged_instruction_rmreg
		if (EMU86_ISUSER())
			goto return_privileged_instruction_rmreg;
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_LMSW && defined(EMU86_EMULATE_INVLPG)
		{
			byte_t *addr;
			addr = MODRM_MEMADDR();
			EMU86_EMULATE_INVLPG(addr);
		}
#else /* EMU86_EMULATE_CONFIG_WANT_LMSW && EMU86_EMULATE_INVLPG */
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_LMSW || !EMU86_EMULATE_INVLPG */
		goto done;
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_INVLPG */


	default:
#define NEED_return_unknown_instruction_rmreg
		goto return_unknown_instruction_rmreg;
	}
	break;
}
#endif /* EMU86_EMULATE_... */



#if (CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_64BIT || \
     (EMU86_EMULATE_CONFIG_CHECKERROR && CONFIG_LIBEMU86_WANT_16BIT))
#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LAR
case EMU86_OPCODE_ENCODE(0x0f02): {
	/* 0F 02 /r     LAR r16, r16/m16     r16 := access rights referenced by r16/m16 */
#if CONFIG_LIBEMU86_WANT_16BIT
#define NEED_return_unsupported_instruction
	if (EMU86_F_IS16(op_flags)) /* This also includes vm86! */
		goto return_unsupported_instruction;
#endif /* CONFIG_LIBEMU86_WANT_16BIT */
	MODRM_DECODE();
#if EMU86_EMULATE_CONFIG_WANT_LAR && defined(EMU86_EMULATE_LAR)
	{
		bool ok;
		u16 segment_index;
		u16 segment_rights;
		segment_index = MODRM_GETRMW();
		ok = EMU86_EMULATE_LAR(segment_index,
		                       segment_rights);
		EMU86_MSKFLAGS(~EFLAGS_ZF, ok ? EFLAGS_ZF : 0);
		if (ok)
			MODRM_SETRMREGW(segment_rights);
	}
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_LAR && EMU86_EMULATE_LAR */
	MODRM_NOSUP_GETRMW();
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_LAR || !EMU86_EMULATE_LAR */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LAR */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LSL
case EMU86_OPCODE_ENCODE(0x0f03): {
	/*         0F 03 /r     LSL r16, r16/m16     Load: r16 := segment limit, selector r16/m16.
	 *         0F 03 /r     LSL r32, r32/m16     Load: r32 := segment limit, selector r32/m16.
	 * REX.W + 0F 03 /r     LSL r64, r32/m16     Load: r64 := segment limit, selector r32/m16 */
#if CONFIG_LIBEMU86_WANT_16BIT
#define NEED_return_unsupported_instruction
	if (EMU86_F_IS16(op_flags)) /* This also includes vm86! */
		goto return_unsupported_instruction;
#endif /* CONFIG_LIBEMU86_WANT_16BIT */
	MODRM_DECODE();
#if EMU86_EMULATE_CONFIG_WANT_LSL && defined(EMU86_EMULATE_LSL)
	{
		bool ok;
		u16 segment_index;
		EMU86_UREG_TYPE limit;
		segment_index = MODRM_GETRMW();
		ok = EMU86_EMULATE_LSL(segment_index, limit);
		EMU86_MSKFLAGS(~EFLAGS_ZF, ok ? EFLAGS_ZF : 0);
		if (ok) {
			IF_64BIT(if (IS_64BIT()) {
				MODRM_SETREGQ(limit);
			} else) if (!IS_16BIT()) {
				MODRM_SETREGL(limit);
			} else {
				MODRM_SETREGW(limit);
			}
		}
		goto done;
	}
#else /* EMU86_EMULATE_CONFIG_WANT_LSL && EMU86_EMULATE_LSL */
	MODRM_NOSUP_GETRMW();
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_LSL || !EMU86_EMULATE_LSL */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LSL */
#endif /* CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_64BIT || (EMU86_EMULATE_CONFIG_CHECKERROR && CONFIG_LIBEMU86_WANT_16BIT) */


}
EMU86_INTELLISENSE_END