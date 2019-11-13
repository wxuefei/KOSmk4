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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EXCEPT_HANDLER_C
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EXCEPT_HANDLER_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/coredump.h>
#include <kernel/except.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <kernel/vm.h>
#include <sched/except-handler.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <hybrid/host.h>

#include <kos/bits/except-handler.h>
#include <kos/bits/except-handler32.h>
#include <kos/bits/exception_data.h>
#include <kos/bits/exception_data32.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state-helpers32.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/cpu-state32.h>
#include <sys/wait.h>

#include <assert.h>
#include <signal.h>
#include <stddef.h>

#include <librpc/rpc.h>

DECL_BEGIN

/* Try to invoke the user-space exception handler for the
 * currently set exception, as described by `error_info()'
 * @param: state:   The user-space CPU state (note that `icpustate_isuser(state)' is assumed!)
 * @param: sc_info: When non-NULL, information about the system call that caused the exception.
 *                  Otherwise, if this argument is `NULL', the exception was caused by user-space,
 *                  such as a user-space program causing an `E_SEGFAULT', as opposed to the kernel
 *                  throwing an `E_FSERROR_FILE_NOT_FOUND'
 *            HINT: Additional information about how the system call was invoked can be extracted
 *                  from `sc_info->rsi_flags'! (s.a. `<librpc/bits/rpc-common.h>')
 * @return: NULL:   User-space does not define an exception handler.
 * @return: * :     The updated interrupt CPU state, modified to invoke the
 *                  user-space exception handler once user-space execution
 *                  resumes. */
#ifdef __x86_64__
PUBLIC WUNUSED struct icpustate *FCALL
x86_userexcept_callhandler(struct icpustate *__restrict state,
                           struct rpc_syscall_info *sc_info)
		THROWS(E_SEGFAULT) {
	struct icpustate *result;
	if (icpustate_is64bit(state)) {
		result = x86_userexcept_callhandler64(state, sc_info);
	} else {
		result = x86_userexcept_callhandler32(state, sc_info);
	}
	return result;
}

PUBLIC WUNUSED struct icpustate *FCALL
x86_userexcept_callhandler64(struct icpustate *__restrict state,
                             struct rpc_syscall_info *sc_info)
		THROWS(E_SEGFAULT) {
	/* Call a 64-bit exception handler. */
	uintptr_t mode;
	USER CHECKED void *stack;
	USER CHECKED __except_handler64_t handler;
	USER CHECKED struct kcpustate64 *user_state;
	USER CHECKED struct exception_data64 *user_error;
	struct exception_data *mydata;
	unsigned int i;
	/* Call the user-space exception handler */
	mode    = PERTASK_GET(_this_user_except_handler.ueh_mode);
	handler = (__except_handler64_t)(uintptr_t)(void *)PERTASK_GET(_this_user_except_handler.ueh_handler);
	stack   = PERTASK_GET(_this_user_except_handler.ueh_stack);
	if unlikely(!(mode & EXCEPT_HANDLER_FLAG_SETHANDLER))
		return NULL; /* No handler defined */
	if (stack == EXCEPT_HANDLER_SP_CURRENT)
		stack = (void *)icpustate_getuserpsp(state);
	/* Align the stack. */
	stack = (void *)((uintptr_t)stack & ~7);
	/* Allocate structures */
	user_state = (struct kcpustate64 *)((byte_t *)stack - sizeof(struct kcpustate64));
	user_error = (struct exception_data64 *)((byte_t *)user_state - sizeof(struct exception_data64));
	/* Ensure that we can write to the given stack. */
	validate_writable(user_error, sizeof(struct exception_data64) + sizeof(struct kcpustate64));
	COMPILER_WRITE_BARRIER();
	/* Fill in user-space context information */
	icpustate_user_to_kcpustate64(state, user_state);
	/* Copy exception data onto the user-space stack. */
	mydata = &THIS_EXCEPTION_INFO.ei_data;
	user_error->e_code = (error_code64_t)mydata->e_code;
	for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i)
		user_error->e_pointers[i] = (u64)mydata->e_pointers[i];
	/* In case of a system call, set the fault
	 * address as the system call return address. */
	user_error->e_faultaddr = sc_info != NULL
	                          ? (__HYBRID_PTR64(void))(u64)(uintptr_t)icpustate_getuserpsp(state)
	                          : (__HYBRID_PTR64(void))(u64)(uintptr_t)mydata->e_faultaddr;
	/* Redirect the given CPU state to return to the user-space handler. */
	gpregs_setpdi(&state->ics_gpregs, (uintptr_t)user_state); /* struct kcpustate64 *__restrict state */
	gpregs_setpsi(&state->ics_gpregs, (uintptr_t)user_error); /* struct exception_data64 *__restrict error */
	icpustate_setuserpsp(state, (uintptr_t)user_error);
	icpustate_setpc(state, (uintptr_t)(void *)handler);
	COMPILER_WRITE_BARRIER();
	/* Disable exception handling in one-shot mode. */
	if (mode & EXCEPT_HANDLER_FLAG_ONESHOT) {
		PERTASK_SET(_this_user_except_handler.ueh_mode,
		            (mode & ~EXCEPT_HANDLER_MODE_MASK) |
		            EXCEPT_HANDLER_MODE_DISABLED);
	}
	return state;
}

PUBLIC WUNUSED struct icpustate *FCALL
x86_userexcept_callhandler32(struct icpustate *__restrict state,
                             struct rpc_syscall_info *sc_info)
		THROWS(E_SEGFAULT)
#else /* __x86_64__ */
PUBLIC WUNUSED struct icpustate *FCALL
x86_userexcept_callhandler(struct icpustate *__restrict state,
                           struct rpc_syscall_info *sc_info)
		THROWS(E_SEGFAULT)
#endif /* !__x86_64__ */
{
	/* Call a 32-bit exception handler. */
	uintptr_t mode;
	USER CHECKED void *stack;
	USER CHECKED __except_handler32_t handler;
	USER CHECKED struct kcpustate32 *user_state;
	USER CHECKED struct exception_data32 *user_error;
	struct exception_data *mydata;
	unsigned int i;
	/* Call the user-space exception handler */
	mode    = PERTASK_GET(_this_user_except_handler.ueh_mode);
	handler = (__except_handler32_t)(uintptr_t)(void *)PERTASK_GET(_this_user_except_handler.ueh_handler);
	stack   = PERTASK_GET(_this_user_except_handler.ueh_stack);
	if unlikely(!(mode & EXCEPT_HANDLER_FLAG_SETHANDLER))
		return NULL; /* No handler defined */
	if (stack == EXCEPT_HANDLER_SP_CURRENT)
		stack = (void *)icpustate_getuserpsp(state);
	/* Align the stack. */
	stack = (void *)((uintptr_t)stack & ~3);
	/* Allocate structures */
	user_state = (struct kcpustate32 *)((byte_t *)stack - sizeof(struct kcpustate32));
	user_error = (struct exception_data32 *)((byte_t *)user_state - sizeof(struct exception_data32));
	/* Ensure that we can write to the given stack. */
	validate_writable(user_error, sizeof(struct exception_data32) + sizeof(struct kcpustate32));
	COMPILER_WRITE_BARRIER();
	/* Fill in user-space context information */
	icpustate_user_to_kcpustate32(state, user_state);
	/* Copy exception data onto the user-space stack. */
	mydata = &THIS_EXCEPTION_INFO.ei_data;
	user_error->e_code = (error_code32_t)mydata->e_code;
	for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i)
		user_error->e_pointers[i] = (u32)mydata->e_pointers[i];
	/* In case of a system call, set the fault
	 * address as the system call return address. */
	user_error->e_faultaddr = sc_info != NULL
	                          ? (__HYBRID_PTR32(void))(u32)(uintptr_t)icpustate_getuserpsp(state)
	                          : (__HYBRID_PTR32(void))(u32)(uintptr_t)mydata->e_faultaddr;
	/* Redirect the given CPU state to return to the user-space handler. */
	gpregs_setpcx(&state->ics_gpregs, (uintptr_t)user_state); /* struct kcpustate32 *__restrict state */
	gpregs_setpdx(&state->ics_gpregs, (uintptr_t)user_error); /* struct exception_data32 *__restrict error */
	icpustate_setuserpsp(state, (uintptr_t)user_error);
	icpustate_setpc(state, (uintptr_t)(void *)handler);
	COMPILER_WRITE_BARRIER();
	/* Disable exception handling in one-shot mode. */
	if (mode & EXCEPT_HANDLER_FLAG_ONESHOT) {
		PERTASK_SET(_this_user_except_handler.ueh_mode,
		            (mode & ~EXCEPT_HANDLER_MODE_MASK) |
		            EXCEPT_HANDLER_MODE_DISABLED);
	}
	return state;
}


LOCAL ATTR_NORETURN void
NOTHROW(FCALL process_exit)(int reason) {
	/* TODO: If the crashing application is critical, invoke kernel PANIC() */
	/* TODO: We need to terminate the _process_; not just this thread! */
	task_exit(reason);
}

LOCAL ATTR_NORETURN void
NOTHROW(FCALL process_exit_for_exception_after_coredump)(void) {
	siginfo_t si;
	/* Try to translate the current exception into a signal, so that we
	 * can use that signal code as reason for why the process has exited. */
	if (!error_as_signal(error_data(), &si))
		si.si_signo = SIGILL;
	process_exit(W_EXITCODE(1, si.si_signo) | WCOREFLAG);
}



/* Raise a posix signal in user-space for `siginfo'
 * @param: state:   The user-space CPU state (note that `icpustate_isuser(state)' is assumed!)
 * @param: sc_info: When non-NULL, information about the system call that caused the signal.
 *                  Otherwise, if this argument is `NULL', the signal was caused by user-space,
 *                  such as a user-space program causing an `E_SEGFAULT', as opposed to the kernel
 *                  throwing an `E_FSERROR_FILE_NOT_FOUND'
 *            HINT: Additional information about how the system call was invoked can be extracted
 *                  from `sc_info->rsi_flags'! (s.a. `<librpc/bits/rpc-common.h>')
 * @param: siginfo: The signal that is being raised
 * @param: derived_from_exception: If true, `siginfo' was generated through `error_as_signal()',
 *                  and if a coredump ends up being generated as a result of the signal being
 *                  raised, that coredump will include information about `error_info()', rather
 *                  than the given `siginfo'
 * @return: NULL:   User-space does not define an signal handler.
 * @return: * :     The updated interrupt CPU state, modified to invoke the
 *                  user-space signal handler once user-space execution
 *                  resumes. */
PUBLIC WUNUSED ATTR_RETNONNULL struct icpustate *FCALL
x86_userexcept_raisesignal(struct icpustate *__restrict state,
                           struct rpc_syscall_info *sc_info,
                           siginfo_t const *__restrict siginfo,
                           bool derived_from_exception) {
	struct icpustate *result;
	struct sighand *hand;
	struct kernel_sigaction action;
	/* Raise a POSIX signal */
again_gethand:
	assert(siginfo->si_signo != 0);
	assert(siginfo->si_signo < NSIG);
	if (!THIS_SIGHAND_PTR) {
		action.sa_handler = KERNEL_SIG_DFL;
		action.sa_flags   = 0;
		action.sa_mask    = NULL;
	} else {
		hand   = sighand_ptr_lockread(THIS_SIGHAND_PTR);
		action = hand->sh_actions[siginfo->si_signo - 1];
		xincref(action.sa_mask);
		sync_endread(hand);
	}

	/* Check for special signal handlers. */
	if (action.sa_handler == KERNEL_SIG_DFL)
		action.sa_handler = sighand_default_action(siginfo->si_signo);
	switch ((uintptr_t)(void *)action.sa_handler) {

#undef __CCAST
#define __CCAST(T) /* nothing */

	case KERNEL_SIG_IGN:
		xdecref_unlikely(action.sa_mask);
#if 0 /* `SA_RESETHAND' only affects user-space signal handler functions */
		if ((action.sa_flags & SIGACTION_SA_RESETHAND) &&
		    unlikely(!sighand_reset_handler(siginfo->si_signo, &action)))
			goto again_gethand;
#endif
		if (sc_info)
			state = x86_userexcept_seterrno(state, sc_info);
		return state;

	case KERNEL_SIG_CORE:
		xdecref_unlikely(action.sa_mask);
		if (derived_from_exception) {
			/* If we've gotten here because of a system call, then we can assume that
			 * the exception does have a kernel-space side, and thus we must include
			 * information about that exception's origin. */
			coredump_create_for_exception(state, sc_info != NULL);
		} else {
			coredump_create_for_signal(state, siginfo);
		}
		process_exit(W_EXITCODE(1, siginfo->si_signo) | WCOREFLAG);

	case KERNEL_SIG_TERM:
		xdecref_unlikely(action.sa_mask);
		process_exit(W_EXITCODE(1, siginfo->si_signo));

	case KERNEL_SIG_EXIT:
		xdecref_unlikely(action.sa_mask);
		task_exit(W_EXITCODE(1, siginfo->si_signo));

	case KERNEL_SIG_CONT:
		xdecref_unlikely(action.sa_mask);
#if 0 /* `SA_RESETHAND' only affects user-space signal handler functions */
		if ((action.sa_flags & SIGACTION_SA_RESETHAND) &&
		    unlikely(!sighand_reset_handler(siginfo->si_signo, &action)))
			goto again_gethand;
#endif
		/* Continue execution. */
		task_sigcont(THIS_TASK);
		return state;

	case KERNEL_SIG_STOP:
		/* TODO: Mask additional signals by looking at `SIGACTION_SA_NODEFER' and `action.sa_mask' */
		xdecref_unlikely(action.sa_mask);
#if 0 /* `SA_RESETHAND' only affects user-space signal handler functions */
		if ((action.sa_flags & SIGACTION_SA_RESETHAND) &&
			unlikely(!sighand_reset_handler(siginfo->si_signo, &action)))
			goto again_gethand;
#endif
		/* Suspend execution. */
		task_sigstop(W_STOPCODE(siginfo->si_signo));
		return state;

#undef __CCAST
#define __CCAST(T) (T)
	default: break;
	}

	/* Invoke a regular, old signal handler. */
	FINALLY_XDECREF_UNLIKELY(action.sa_mask);
	result = sighand_raise_signal(state, &action,
	                              siginfo, sc_info);
	if unlikely(!result)
		goto again_gethand;
	return result;
}


/* Helper function for `x86_userexcept_raisesignal()' that may be used
 * to raise the appropriate POSIX signal for the currently set exception.
 * @return: NULL: The current exception cannot be translated into a posix signal.
 * @return: * :     The updated interrupt CPU state, modified to invoke the
 *                  user-space signal handler once user-space execution
 *                  resumes. */
PUBLIC WUNUSED struct icpustate *FCALL
x86_userexcept_raisesignal_from_exception(struct icpustate *__restrict state,
                                          struct rpc_syscall_info *sc_info) {
	siginfo_t siginfo;
	/* Try to translate the current exception into a signal. */
	if (!error_as_signal(error_data(), &siginfo))
		return NULL;
	/* Include missing information within the signal info. */
	switch (siginfo.si_signo) {

	case SIGSYS:
		siginfo.si_call_addr = (void *)icpustate_getpc(state);
		break;

	default: break;
	}
	return x86_userexcept_raisesignal(state, sc_info,
	                                  &siginfo, true);
}

/* Translate the current exception into an errno and set that errno
 * as the return value of the system call described by `sc_info'. */
PUBLIC WUNUSED struct icpustate *FCALL
x86_userexcept_seterrno(struct icpustate *__restrict state,
                        struct rpc_syscall_info *__restrict sc_info) {
	errno_t errval;
	struct exception_data *data;
	data   = error_data();
	errval = -error_as_errno(data);
#if 1
	{
		unsigned int pointer_count = EXCEPTION_DATA_POINTERS;
		while (pointer_count != 0 &&
		       data->e_pointers[pointer_count - 1] == 0)
			--pointer_count;
		printk(KERN_TRACE "[except] Translate exception %#x:%#x",
		       data->e_class, data->e_subclass);
		if (pointer_count != 0) {
			unsigned int i;
			for (i = 0; i < pointer_count; ++i) {
				printk(KERN_TRACE "%c%#Ix",
				       i == 0 ? '[' : ',',
				       data->e_pointers[i]);
			}
			printk(KERN_TRACE "]");
		}
		printk(KERN_TRACE " into errno=%d [tid=%u]\n",
		       errval, task_getroottid_s());
	}
#endif
	gpregs_setpax(&state->ics_gpregs, errval);
	/* Check if the system call is double-wide so we
	 * can sign-extend the error code if necessary. */
#ifdef __x86_64__
	if (icpustate_is64bit(state)) {
		if (SYSCALL64_DOUBLE_WIDE(gpregs_getpax(&state->ics_gpregs)))
			gpregs_setpdx(&state->ics_gpregs, (uintptr_t)-1); /* sign-extend */
	} else
#endif /* __x86_64__ */
	{
		if (SYSCALL32_DOUBLE_WIDE(gpregs_getpax(&state->ics_gpregs)))
			gpregs_setpdx(&state->ics_gpregs, (uintptr_t)-1); /* sign-extend */
	}
	return state;
}


/* Propagate the currently thrown exception into user-space, using either the user-space
 * exception handler, by raising a POSIX signal, or by translating the exception into an
 * E* error code in the event of a system call with exceptions disabled (on x86, except-
 * enabled is usually controlled by the CF bit, however this function takes that information
 * from the `RPC_SYSCALL_INFO_FEXCEPT' bit in `sc_info->rsi_flags'). */
PUBLIC WUNUSED ATTR_RETNONNULL struct icpustate *FCALL
x86_userexcept_propagate(struct icpustate *__restrict state,
                         struct rpc_syscall_info *sc_info) {
	struct icpustate *result;
	struct exception_info *einfo;
	einfo = error_info();

	/* Handle special exception codes */
	switch (einfo->ei_code) {

	case ERROR_CODEOF(E_EXIT_PROCESS):
		process_exit((int)einfo->ei_data.e_pointers[0]);

	case ERROR_CODEOF(E_EXIT_THREAD):
		task_exit((int)einfo->ei_data.e_pointers[0]);

	default: break;
	}

	/* Handle exception unwinding into user-space. */
	if (sc_info != NULL) {
		if (sc_info->rsi_flags & RPC_SYSCALL_INFO_FEXCEPT) {
			/* System call exceptions are enabled. */
			TRY {
				/* Propagate the exception to user-space if handlers are enabled. */
				if ((PERTASK_GET(_this_user_except_handler.ueh_mode) &
				     EXCEPT_HANDLER_MODE_MASK) != EXCEPT_HANDLER_MODE_DISABLED) {
					result = x86_userexcept_callhandler(state, sc_info);
					if likely(result)
						goto done;
				}
				/* If exceptions don't work, try to propagate a POSIX signal */
				result = x86_userexcept_raisesignal_from_exception(state, sc_info);
				if likely(result)
					goto done;
			} EXCEPT {
			}
			/* If the exception still cannot be handled, terminate the program. */
			goto terminate_app;
		}
		/* Translate the current exception into an errno. */
		result = x86_userexcept_seterrno(state, sc_info);
		goto done;
	}

	TRY {
		/* Check if signal exceptions should be propagated in non-syscall scenarios. */
		if ((PERTASK_GET(_this_user_except_handler.ueh_mode) &
		     EXCEPT_HANDLER_MODE_MASK) == EXCEPT_HANDLER_MODE_SIGHAND) {
			result = x86_userexcept_callhandler(state, sc_info);
			if likely(result)
				goto done;
		}
		/* Deliver a signal to the calling user-space thread. */
		result = x86_userexcept_raisesignal_from_exception(state, sc_info);
		if likely(result)
			goto done;
	} EXCEPT {
	}

terminate_app:
	/* If we've gotten here because of a system call, then we can assume that
	 * the exception does have a kernel-space side, and thus we must include
	 * information about that exception's origin. */
	coredump_create_for_exception(state, sc_info != NULL);
	process_exit_for_exception_after_coredump();
	__builtin_unreachable();
done:
	/* Delete the currently set exception. */
	PERTASK_SET(_this_exception_info.ei_code, (error_code_t)ERROR_CODEOF(E_OK));
	return result;
}




/* Serve all user-space redirection RPCs
 * @return: * :   The new CPU state to restore
 * @param: prestart_system_call: If `reason == TASK_RPC_REASON_SYSCALL', whilst an `E_INTERRUPT_USER_RPC'
 *                               exception was handled, when `RPC_KIND_USER_SYNC' RPCs exist that cannot
 *                               be handled in the current context, then set to true. */
INTDEF struct icpustate *
NOTHROW(FCALL rpc_serve_user_redirection_all)(struct icpustate *__restrict state,
                                              unsigned int reason,
                                              struct rpc_syscall_info const *sc_info,
                                              bool *prestart_system_call);


/* Given a user-space UCPUSTATE, load that state into the active IRET tail, whilst
 * accounting for additional user-space RPC redirection, before serving user-level
 * RPC functions, and finally propagating the then set exception (if one still is)
 * into user-space with the help of `x86_userexcept_propagate()'.
 * Afterwards, load the updated icpustate at the base of the calling thread's stack,
 * and finally fully unwind into user-space by use of `'. */
PUBLIC ATTR_NORETURN void FCALL
x86_userexcept_unwind(struct ucpustate *__restrict ustate,
                      struct rpc_syscall_info *sc_info) {
	struct icpustate *return_state;
	assert(!(THIS_TASK->t_flags & TASK_FKERNTHREAD));
	/* Disable interrupts to prevent Async-RPCs from doing even more re-directions! */
	__cli();
#define kernel_stack_top() \
	((byte_t *)VM_PAGE2ADDR(PERTASK_GET((*(struct vm_node *)&_this_kernel_stack).vn_node.a_vmax) + 1))
	/* Figure out where the return icpustate needs to go. */
	return_state = (struct icpustate *)(kernel_stack_top() -
	                                    (
#ifdef __x86_64__
	                                    SIZEOF_ICPUSTATE64
#else
	                                    ucpustate_isvm86(ustate)
	                                    ? OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_VM86
	                                    : OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_USER
#endif
	                                    ));
	/* Check if user-space got redirected (if so, we need to follow some custom unwinding rules). */
	if (return_state->ics_irregs.ir_pip == (uintptr_t)&x86_rpc_user_redirection) {
		/* A re-direction may have happened whilst we were unwinding. - Adjust for that now!
		 * HINT: The actual user-space return location is stored in `x86_rpc_redirection_iret' */
		assert(PERTASK_GET(x86_rpc_redirection_iret.ir_pip) != (uintptr_t)&x86_rpc_user_redirection);
		assert(return_state->ics_irregs.ir_pflags == 0);
		assert(return_state->ics_irregs.ir_cs == SEGMENT_KERNEL_CODE);
		/* Manually unwind additional FLAGS registers.
		 * Because .cfi_iret_signal_frame perform a kernel-space unwind
		 * due to the redirection, we must manually complete the
		 * unwind to also include ESP and SS
		 *  - Right now, ESP points at &irregs_user::ir_esp / &irregs_vm86::ir_esp */
#ifdef __x86_64__
		assertf(ustate->ucs_gpregs.gp_rsp == return_state->ics_irregs.ir_rsp,
		        "ustate->ucs_gpregs.gp_rsp       = %p\n"
		        "return_state->ics_irregs.ir_rsp = %p\n",
		        ustate->ucs_gpregs.gp_rsp,
		        return_state->ics_irregs.ir_rsp);
#else /* __x86_64__ */
		assertf(ustate->ucs_gpregs.gp_esp == (u32)&return_state->ics_irregs_u.ir_esp,
		        "ustate->ucs_gpregs.gp_esp          = %p\n"
		        "&return_state->ics_irregs_u.ir_esp = %p\n",
		        ustate->ucs_gpregs.gp_esp,
		        &return_state->ics_irregs_u.ir_esp);
#endif /* !__x86_64__ */

#ifdef __x86_64__
		return_state->ics_irregs.ir_rip    = PERTASK_GET(x86_rpc_redirection_iret.ir_rip);
		return_state->ics_irregs.ir_cs     = PERTASK_GET(x86_rpc_redirection_iret.ir_cs16);
		return_state->ics_irregs.ir_rflags = PERTASK_GET(x86_rpc_redirection_iret.ir_rflags);
		return_state->ics_irregs.ir_rsp    = PERTASK_GET(x86_rpc_redirection_iret.ir_rsp);
		return_state->ics_irregs.ir_ss     = PERTASK_GET(x86_rpc_redirection_iret.ir_ss16);
#else /* __x86_64__ */
		return_state->ics_irregs_u.ir_eip    = PERTASK_GET(x86_rpc_redirection_iret.ir_eip);
		return_state->ics_irregs_u.ir_cs     = PERTASK_GET(x86_rpc_redirection_iret.ir_cs16);
		return_state->ics_irregs_u.ir_eflags = PERTASK_GET(x86_rpc_redirection_iret.ir_eflags);
#if 0 /* Still initialized correctly... */
		return_state->ics_irregs_u.ir_ss     = return_state->ics_irregs_u.ir_ss16;
		return_state->ics_irregs_u.ir_esp    = return_state->ics_irregs_u.ir_esp;
#endif
#endif /* !__x86_64__ */
	} else {
		/* Fill in the user-space return location to match `ustate' */
#ifdef __x86_64__
		return_state->ics_irregs.ir_rip    = ustate->ucs_rip;
		return_state->ics_irregs.ir_cs     = ustate->ucs_cs16;
		return_state->ics_irregs.ir_rflags = ustate->ucs_rflags;
		return_state->ics_irregs.ir_rsp    = ustate->ucs_gpregs.gp_rsp;
		return_state->ics_irregs.ir_ss     = ustate->ucs_ss16;
#else /* __x86_64__ */
		return_state->ics_irregs_u.ir_eip    = ustate->ucs_eip;
		return_state->ics_irregs_u.ir_cs     = ustate->ucs_cs16;
		return_state->ics_irregs_u.ir_eflags = ustate->ucs_eflags;
		return_state->ics_irregs_u.ir_esp    = ustate->ucs_gpregs.gp_esp;
		return_state->ics_irregs_u.ir_ss     = ustate->ucs_ss16;
#endif /* !__x86_64__ */
	}
#ifdef __x86_64__
	gpregs_to_gpregsnsp(&ustate->ucs_gpregs, &return_state->ics_gpregs);
	__wrds(ustate->ucs_sgregs.sg_ds16);
	__wres(ustate->ucs_sgregs.sg_es16);
	__wrfs(ustate->ucs_sgregs.sg_fs16);
	__wrgs(ustate->ucs_sgregs.sg_gs16);
	/* FIXME: Restoring segment base registers here is correct, however
	 *        unnecessary in all current use cases. - The solution would
	 *        be to have another kind of cpustate structure that is like
	 *        ucpustate, but don't contain segment base registers on x86_64! */
	set_user_fsbase(ustate->ucs_sgbase.sg_fsbase);
	set_user_gsbase(ustate->ucs_sgbase.sg_gsbase);
#else /* __x86_64__ */
	return_state->ics_gpregs = ustate->ucs_gpregs;
	if (ustate->ucs_eflags & EFLAGS_VM) {
		/* Special case: vm86 return state */
		return_state->ics_ds             = SEGMENT_USER_DATA_RPL;
		return_state->ics_es             = SEGMENT_USER_DATA_RPL;
		return_state->ics_fs             = SEGMENT_USER_FSBASE_RPL;
		return_state->ics_irregs_v.ir_es = ustate->ucs_sgregs.sg_es16;
		return_state->ics_irregs_v.ir_ds = ustate->ucs_sgregs.sg_ds16;
		return_state->ics_irregs_v.ir_fs = ustate->ucs_sgregs.sg_fs16;
		return_state->ics_irregs_v.ir_gs = ustate->ucs_sgregs.sg_gs16;
	} else {
		icpustate_setds_novm86(return_state, ustate->ucs_sgregs.sg_ds16);
		icpustate_setes_novm86(return_state, ustate->ucs_sgregs.sg_es16);
		icpustate_setfs_novm86(return_state, ustate->ucs_sgregs.sg_fs16);
		icpustate_setgs_novm86(return_state, ustate->ucs_sgregs.sg_gs16);
	}
#endif /* !__x86_64__ */


	/* Now that we've constructed an entirely valid ICPUSTATE at the base of our
	 * own stack, we can re-enable interrupts, as it will be this state which is
	 * (presumably) going to be restored when jumping back into user-space. */
	__sti();

	x86_userexcept_unwind_i(return_state, sc_info);
}

/* Same as `x86_userexcept_unwind()', however the caller has already done the work
 * of constructing a `struct icpustate *' at the base of the current thread's kernel stack. */
PUBLIC ATTR_NORETURN void FCALL
x86_userexcept_unwind_i(struct icpustate *__restrict state,
                        struct rpc_syscall_info *sc_info) {
	/* Service RPCs before returning to user-space. */
	if (sc_info) {
		bool must_restart_syscall;
		must_restart_syscall = false;
		state = rpc_serve_user_redirection_all(state,
		                                       TASK_RPC_REASON_SYSCALL,
		                                       sc_info,
		                                       &must_restart_syscall);
		/* If there is still an active exception (i.e. RPC handling didn't resolve
		 * the exception, as would be the case for `E_INTERRUPT_USER_RPC'), then we
		 * must somehow propagate the exception into user-space. */
		if (error_code() != E_OK) {
			assert(!must_restart_syscall);
			state = x86_userexcept_propagate(state, sc_info);
		} else if unlikely(must_restart_syscall) {
			/* Reset the system call by resetting the kernel stack. */
			syscall_emulate_r(state, sc_info);
		}
	} else {
		state = rpc_serve_user_redirection_all(state,
		                                       TASK_RPC_REASON_ASYNCUSER,
		                                       NULL,
		                                       NULL);
		/* If there is still an active exception (i.e. RPC handling didn't resolve
		 * the exception, as would be the case for `E_INTERRUPT_USER_RPC'), then we
		 * must somehow propagate the exception into user-space. */
		if (error_code() != E_OK)
			state = x86_userexcept_propagate(state, NULL);
	}

	/* Unwind into to the target state, thus returning back to userspace, though
	 * with the associated target potentially changed. */
	x86_userexcept_unwind_interrupt(state);
}




DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EXCEPT_HANDLER_C */