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
#include "idt32.S"
#define IDT_VECTOR 08
#endif /* __INTELLISENSE__ */


#if IDT_CONFIG_GETDPL(IDT_VECTOR_ID) == 3
IDT_HANDLER_SETDPL(3)
#endif /* IDT_CONFIG_GETDPL(IDT_VECTOR_ID) == 3 */

IDT_HANDLER_BEGIN
	.cfi_startproc simple
#if IDT_VECTOR_ID == 0x08 || defined(__DEEMON__)
	/* Double Fault */
	.cfi_signal_frame
	.cfi_def_cfa %ebp, 0
	.cfi_rel_offset %eip, OFFSET_TSS_EIP
	.cfi_rel_offset %eflags, OFFSET_TSS_EFLAGS
	.cfi_rel_offset %eax, OFFSET_TSS_EAX
	.cfi_rel_offset %ecx, OFFSET_TSS_ECX
	.cfi_rel_offset %edx, OFFSET_TSS_EDX
	.cfi_rel_offset %ebx, OFFSET_TSS_EBX
	.cfi_rel_offset %esp, OFFSET_TSS_ESP
	.cfi_rel_offset %ebp, OFFSET_TSS_EBP
	.cfi_rel_offset %esi, OFFSET_TSS_ESI
	.cfi_rel_offset %edi, OFFSET_TSS_EDI
	.cfi_rel_offset %es, OFFSET_TSS_ES
	.cfi_rel_offset %cs, OFFSET_TSS_CS
	.cfi_rel_offset %ss, OFFSET_TSS_SS
	.cfi_rel_offset %ds, OFFSET_TSS_DS
	.cfi_rel_offset %fs, OFFSET_TSS_FS
	.cfi_rel_offset %gs, OFFSET_TSS_GS
	.cfi_rel_offset %ldtr, OFFSET_TSS_LDTR
	/* Our current register state:
	 *   - EBX -- Base address of the current CPU descriptor (THIS_CPU)
	 *   - ESP -- A complete, dedicated stack only for DF exceptions.
	 *   - EBP -- A pointer akin to `leal thiscpu_x86_tss(%ebx), %edi'
	 *      HINT: The pointed-to TSS contains information about where
	 *            the double-fault happened! */

	/* Make sure that our own TSS keep on containing valid values. */
	EXTERN(thiscpu_x86_tssdf)
	movl   %ebx, thiscpu_x86_tssdf + OFFSET_TSS_ESI(%ebx)
	movl   %esp, thiscpu_x86_tssdf + OFFSET_TSS_ESP(%ebx)
	movl   %ebp, thiscpu_x86_tssdf + OFFSET_TSS_EBP(%ebx)
	movl   $(PP_CAT2(x86_idt_, IDT_VECTOR_NAME)), thiscpu_x86_tssdf + OFFSET_TSS_EIP(%ebx)

	/* Unwind LTR to allow for recursive DF handling. */
	xorl   %eax, %eax
	movl   %eax, OFFSET_TSS_LINK(%ebp) /* Clear the link-pointer of the normal TSS */
	movl   %eax, thiscpu_x86_tssdf + OFFSET_TSS_LINK(%ebx)
	EXTERN(thiscpu_x86_gdt)
	andb   $(0b11111101), thiscpu_x86_gdt + SEGMENT_CPU_TSS + 5(%ebx)
	andb   $(0b11111101), thiscpu_x86_gdt + SEGMENT_CPU_TSS_DF + 5(%ebx)
	movw   $(SEGMENT_CPU_TSS), %ax
	ltrw   %ax
	pushfl
	andl   $(~EFLAGS_NT), 0(%esp)
	popfl

	/* Construct the cpu-state structure that'll get passed to the #DF handler. */
	pushl  OFFSET_TSS_EIP(%ebp)    /* state->dcs_regs.ucs_eip */
	pushl  OFFSET_TSS_EFLAGS(%ebp) /* state->dcs_regs.ucs_eflags */
	pushl  OFFSET_TSS_SS(%ebp)     /* state->dcs_regs.ucs_ss */
	pushl  OFFSET_TSS_CS(%ebp)     /* state->dcs_regs.ucs_cs */
	pushl  OFFSET_TSS_DS(%ebp)     /* state->dcs_regs.ucs_sgregs.sg_ds */
	pushl  OFFSET_TSS_ES(%ebp)     /* state->dcs_regs.ucs_sgregs.sg_es */
	pushl  OFFSET_TSS_FS(%ebp)     /* state->dcs_regs.ucs_sgregs.sg_fs */
	pushl  OFFSET_TSS_GS(%ebp)     /* state->dcs_regs.ucs_sgregs.sg_gs */
	pushl  OFFSET_TSS_EAX(%ebp)    /* state->dcs_regs.ucs_gpregs.gp_eax */
	pushl  OFFSET_TSS_ECX(%ebp)    /* state->dcs_regs.ucs_gpregs.gp_ecx */
	pushl  OFFSET_TSS_EDX(%ebp)    /* state->dcs_regs.ucs_gpregs.gp_edx */
	pushl  OFFSET_TSS_EBX(%ebp)    /* state->dcs_regs.ucs_gpregs.gp_ebx */
	pushl  OFFSET_TSS_ESP(%ebp)    /* state->dcs_regs.ucs_gpregs.gp_esp */
	pushl  OFFSET_TSS_EBP(%ebp)    /* state->dcs_regs.ucs_gpregs.gp_ebp */
	pushl  OFFSET_TSS_ESI(%ebp)    /* state->dcs_regs.ucs_gpregs.gp_esi */
	pushl  OFFSET_TSS_EDI(%ebp)    /* state->dcs_regs.ucs_gpregs.gp_edi */
	pushl  OFFSET_TSS_CR3(%ebp)    /* state->dcs_cr3 */

	.cfi_def_cfa %esp, 4 + SIZEOF_UCPUSTATE
	.cfi_rel_offset %eip, 4 + OFFSET_UCPUSTATE_EIP
	.cfi_rel_offset %eflags, 4 + OFFSET_UCPUSTATE_EFLAGS
	.cfi_rel_offset %ss, 4 + OFFSET_UCPUSTATE_SS
	.cfi_rel_offset %cs, 4 + OFFSET_UCPUSTATE_CS
	.cfi_rel_offset %ds, 4 + OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_DS
	.cfi_rel_offset %es, 4 + OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_ES
	.cfi_rel_offset %fs, 4 + OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_FS
	.cfi_rel_offset %gs, 4 + OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_GS
	.cfi_rel_offset %eax, 4 + OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_EAX
	.cfi_rel_offset %ecx, 4 + OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_ECX
	.cfi_rel_offset %edx, 4 + OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_EDX
	.cfi_rel_offset %ebx, 4 + OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_EBX
	.cfi_rel_offset %esp, 4 + OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_ESP
	.cfi_rel_offset %ebp, 4 + OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_EBP
	.cfi_rel_offset %esi, 4 + OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_ESI
	.cfi_rel_offset %edi, 4 + OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_EDI

	/* Invoke the C-level double-fault handler. */
	movl   %esp, %ecx
	EXTERN(PP_CAT2(x86_handle_, IDT_VECTOR_NAME))
	call   PP_CAT2(x86_handle_, IDT_VECTOR_NAME)
	cli
	movl   %eax, %esp
	/* Load %cr3 */
	popl_cfi %eax
	movl   %eax, %cr3

	/* Load the remainder of as a `struct ucpustate' */
	movl   %esp, %ecx
	EXTERN(cpu_apply_ucpustate)
	jmp    cpu_apply_ucpustate
#undef OFFSET_DF_CPUSTATE_REGS
#else /* IDT_VECTOR_ID == 0x08 */
	.cfi_iret_signal_frame
#if IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID)
	.cfi_def_cfa %esp, 4 /* Adjust for the error code. */
	popl_cfi %ss:-(12 + SIZEOF_GPREGS + 4)(%esp) /* ECODE */
#else /* IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID) */
	.cfi_def_cfa %esp, 0
#endif /* !IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID) */

	/* Encode instructions as explicit bytes so it's clear that the
	 * following sequence of instructions is exactly 5 bytes long.
	 * This is important for code that injects interrupt redirection,
	 * which requires exactly 5 bytes of instructions (E9h, DISP32) */
	.byte 0x1e /* pushl %ds */
	.cfi_adjust_cfa_offset 4
	.cfi_restore_iret_ds_or_offset -4

	.byte 0x06 /* pushl %es */
	.cfi_adjust_cfa_offset 4
	.cfi_restore_iret_es_or_offset -8

	.byte 0x0f, 0xa0 /* pushl %fs */
	.cfi_adjust_cfa_offset 4
	.cfi_restore_iret_fs_or_offset -12

	.byte 0x60 /* pushal */
	.cfi_adjust_cfa_offset 32
	.cfi_rel_offset %edi, 0
	.cfi_rel_offset %esi, 4
	.cfi_rel_offset %ebp, 8
/*	.cfi_rel_offset %esp, 12 */
	.cfi_rel_offset %ebx, 16
	.cfi_rel_offset %edx, 20
	.cfi_rel_offset %ecx, 24
	.cfi_rel_offset %eax, 28


	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs

	movl   %esp, %ecx     /* struct icpustate *state */
#if IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID)
	movl   -4(%esp), %edx /* uintptr_t ecode */
#endif /* IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID) */

	EXTERN(PP_CAT2(x86_handle_, IDT_VECTOR_NAME))
	call   PP_CAT2(x86_handle_, IDT_VECTOR_NAME)

	popal_cfi_r
	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
#endif /* IDT_VECTOR_ID != 0x08 */
	.cfi_endproc
IDT_HANDLER_END


_idt_set_impl_section cirq, IDT_VECTOR_NAME
.weak PP_CAT2(x86_handle_, IDT_VECTOR_NAME)
INTERN_FUNCTION(PP_CAT2(x86_handle_, IDT_VECTOR_NAME))
	.cfi_startproc
#if !IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID)
	xorl   %edx, %edx /* uintptr_t ecode */
#endif /* IDT_CONFIG_PUSHESERRORS(IDT_VECTOR_ID) */
	pushl_cfi $(IDT_VECTOR_ID) /* uintptr_t vecno */
	EXTERN(x86_handle_unhandled_idt)
	call   x86_handle_unhandled_idt
	.cfi_adjust_cfa_offset -4
	ret
	.cfi_endproc
END(PP_CAT2(x86_handle_, IDT_VECTOR_NAME))

#undef IDT_VECTOR
