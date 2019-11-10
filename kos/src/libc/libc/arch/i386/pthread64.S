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

#include "../../pthread.h"
/**/

#include <hybrid/compiler.h>
#include <sched.h>
#include <asm/cfi.h>
#include <sys/syscall.h>



/* Assembly-side for the process of cloning a thread.
 * This function simply clones the calling thread before invoking
 * `libc_pthread_main()' within the context of the newly spawned thread.
 * NOTE: This function also fills in `thread->pt_tid' */
/* INTDEF errno_t NOTHROW(__FCALL libc_pthread_clone)(struct pthread *__restrict thread,
 *                                                    __pthread_start_routine_t start); */
.section .text.crt.sched.pthread.pthread_clone
INTERN_FUNCTION(libc_pthread_clone)
	.cfi_startproc

	/* We use %r14 and %r15 to pass arguments to the new thread,
	 * since those registers aren't used by the system call, and
	 * also don't get clobbered */
	pushq_cfi_r %r14
	pushq_cfi_r %r15
	movq   %rdi, %r14 /* struct pthread *__restrict thread */
	movq   %rsi, %r15 /* __pthread_start_routine_t start */

	movq   OFFSET_PTHREAD_TLS(%ecx), %r8        /* void *newtls */
	movq   OFFSET_PTHREAD_TID(%ecx), %r10       /* pid_t *ctid */
	xorq   %rdx, %rdx                           /* pid_t *ptid */
	movq   OFFSET_PTHREAD_STACKADDR(%rdi), %rsi
	addq   OFFSET_PTHREAD_STACKSIZE(%rdi), %rsi /* void *child_stack */
	movq       $(CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | \
	             CLONE_PARENT | CLONE_THREAD | CLONE_SYSVSEM | CLONE_SETTLS | \
	             CLONE_CHILD_CLEARTID | CLONE_DETACHED  | CLONE_CHILD_SETTID | \
	             CLONE_IO), %rdi /* int flags */
	movq   $(SYS_clone), %rax
	syscall

	/* Check if we're inside of the child thread
	 * If so, just to pthread's thread entry point.
	 * Note that `%ecx' and `%edx' weren't clobbered, so the new
	 * thread will have automatically inherited them from us! */
	testq  %rax, %rax
	jnz    1f
	movq   %r14, %rdi /* struct pthread *__restrict thread */
	movq   %r15, %rsi /* __pthread_start_routine_t start */
	INTERN(libc_pthread_main)
	jmp    libc_pthread_main

1:	popq_cfi_r %r15
	popq_cfi_r %r14
	ret
	.cfi_endproc
END(libc_pthread_clone)


/* INTDEF ATTR_NORETURN void __FCALL
 * libc_pthread_unmap_stack_and_exit(%rdi: void *stackaddr,
 *                                   %rsi: size_t stacksize,
 *                                   %rdx: int exitcode); */
.section .text.crt.sched.pthread.pthread_unmap_stack_and_exit
INTERN_FUNCTION(libc_pthread_unmap_stack_and_exit)
	movq   %rdx, %rbp          /* int exitcode */
	movq   $(SYS_munmap), %rax
	syscall                    /* unmap our own stack. */
	/* WARNING: No more accessing stack memory from here on! */

	movq   %rbp,        %rdi   /* int exitcode */
	movq   $(SYS_exit), %rax
	syscall
	/* -unreachable- */
END(libc_pthread_unmap_stack_and_exit)



