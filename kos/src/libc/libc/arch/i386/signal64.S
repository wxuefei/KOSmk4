/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>
#include <asm/cfi.h>
#include <syscall.h>
#include <kos/kernel/cpu-state.h>

.section .text.crt.sched.signal.sig_restore
INTERN_FUNCTION(libc_sig_restore)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %rsp, 0

	/* TODO: Encode CFI instrumentation for unwinding */

	movq  $(SYS_rt_sigreturn), %rax
	syscall
	.cfi_endproc
END(libc_sig_restore)


















