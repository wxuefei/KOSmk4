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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSEXIT32_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSEXIT32_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <kernel/syscall.h>

#include <asm/cfi.h>
#include <asm/instr/ttest.h>


/************************************************************************/
/* SYSEXIT-OPTIMIZED IRET                                               */
/************************************************************************/
.section .text.hot
/* Do the equivalent of `iret', but try to make use of `sysexit' if the register
 * state described by the iret tail stored at `0(%esp)' allow for this to be done.
 * Note that if sysexit ends up being used, the following user-space registers
 * will be clobbered (which cannot be prevented):
 *  - %ecx   (Set to OFFSET_IRREGS_ESP(%esp))
 *  - %edx   (Set to OFFSET_IRREGS_EIP(%esp))
 */
PUBLIC_FUNCTION(__i386_syscall_iret)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %esp, 0
	/* Disable interrupts to prevent any further IRET redirections. */
	cli

	/* sysexit requires that TARGET.%cs == SEGMENT_USER_CODE32_RPL, as
	 * that is the effective %cs that will be loaded by `sysexit'
	 * NOTE: If IRET was re-directed, then this check will fail! */
	cmpw   $(SEGMENT_USER_CODE32_RPL), OFFSET_IRREGS_CS(%esp)
	jne    .Ldo_iret

	/* When returning to vm86, we also cannot make use of `sysexit' */
	ttest  mask=EFLAGS_VM, loc=OFFSET_IRREGS_EFLAGS(%esp)
	jnz    .Ldo_iret

	/* Technically, we'd also have to check for EFLAGS_IF being set,
	 * however the KOS kernel assumes that all user-space code runs
	 * with interrupts enabled, since not doing so would introduce
	 * a security problem! */

	/* Confirmed! We can make use of sysexit! */
	movl   OFFSET_IRREGS_ESP(%esp), %ecx /* Return-%esp (mandated by `sysexit') */
	movl   OFFSET_IRREGS_EIP(%esp), %edx /* Return-%eip (mandated by `sysexit') */
	.cfi_register %esp, %ecx
	.cfi_register %eip, %edx

	/* Load the effective user-space %eflags value (but keep EFLAGS_IF disabled
	 * so we can explicitly enable it as interlocked with the `sysexit' instruction) */
	addl   $(OFFSET_IRREGS_EFLAGS), %esp
	.cfi_adjust_cfa_offset -OFFSET_IRREGS_EFLAGS
	andl   $(~EFLAGS_IF), 0(%esp)
	popfl_cfi
	.cfi_same_value %eflags /* Technically not, as EFLAGS.IF needs to be set... */

	/* Do the sysexit.
	 * Note that `sti' has a special behavior where it will only enable interrupts after
	 * the following instruction, meaning that we are guarantied to not experience any
	 * interrupts before the following `sysexit' has also been executed. */
	sti
	sysexit

.Ldo_iret:
	iret
	.cfi_endproc
END(__i386_syscall_iret)



#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSEXIT32_S */
