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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_SYSCALL_BASE64_S
#define GUARD_LIBC_LIBC_ARCH_I386_SYSCALL_BASE64_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <asm/cfi.h>
#include <sys/syscall.h>

.section .text.crt.system.utility.syscall
INTERN_FUNCTION(libc_syscall)
	.cfi_startproc
	movq   %rdi,    %rax /* sysno */
	movq   %rsi,    %rdi /* arg #0 */
	movq   %rdx,    %rsi /* arg #1 */
	movq   %rcx,    %rdx /* arg #2 */
	movq   %r8,     %r10 /* arg #3 */
	movq   %r9,     %r8  /* arg #4 */
	movq   8(%rsp), %r9  /* arg #5 */
	clc
	syscall
	cmpq   $(-4096), %rax /* Check for error. */
	ja     1f
	ret
1:	movq   %rax, %rdi
	INTERN(libc_seterrno)
	call   libc_seterrno /* errno = -return */
//	movq   %rax, %rdx /* Extend to 128 bits. (No such system call exists, so no need) */
	ret
	.cfi_endproc
END(libc_syscall)
DEFINE_INTERN_ALIAS(libc_syscall64, libc_syscall)
DEFINE_PUBLIC_ALIAS(syscall, libc_syscall)
DEFINE_PUBLIC_ALIAS(syscall64, libc_syscall64)

.section .text.crt.except.system.utility.Syscall
INTERN_FUNCTION(libc_Syscall)
	.cfi_startproc
	movq   %rdi,    %rax /* sysno */
	movq   %rsi,    %rdi /* arg #0 */
	movq   %rdx,    %rsi /* arg #1 */
	movq   %rcx,    %rdx /* arg #2 */
	movq   %r8,     %r10 /* arg #3 */
	movq   %r9,     %r8  /* arg #4 */
	movq   8(%rsp), %r9  /* arg #5 */
	stc
	syscall
	ret
	.cfi_endproc
END(libc_Syscall)
DEFINE_INTERN_ALIAS(libc_Syscall64, libc_Syscall)
DEFINE_PUBLIC_ALIAS(Syscall, libc_Syscall)
DEFINE_PUBLIC_ALIAS(Syscall64, libc_Syscall64)

#endif /* !GUARD_LIBC_LIBC_ARCH_I386_SYSCALL_BASE64_S */
