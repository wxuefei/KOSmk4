/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.remove("-O3"))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_SRC_MISC_PANIC_C
#define GUARD_KERNEL_SRC_MISC_PANIC_C 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/entry.h>
#include <debugger/function.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <debugger/util.h>
#include <kernel/addr2line.h>
#include <kernel/debugtrap.h>
#include <kernel/memory.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/syslog.h>
#include <kernel/vm.h>
#include <sched/async.h>
#include <sched/rwlock-intern.h>
#include <sched/signal-intern.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/host.h>

#include <asm/intrin.h>
#include <kos/kernel/cpu-state-helpers.h>

#include <format-printer.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

#include <libinstrlen/instrlen.h>
#include <libunwind/unwind.h>

#include "../../../libc/libc/assert.h" /* struct assert_args */

DECL_BEGIN

DATDEF bool const _kernel_poisoned;
DATDEF bool __kernel_poisoned ASMNAME("_kernel_poisoned");
PUBLIC bool __kernel_poisoned = false;


#undef LOG_STACK_REMAINDER
#if 1
#define LOG_STACK_REMAINDER 1
#endif

LOCAL ATTR_COLDTEXT NOBLOCK void
NOTHROW(KCALL fixup_uninitialized_thread)(struct task *__restrict thread) {
	if (thread->t_self != thread)
		thread->t_self = thread; /* Shouldn't happen... */
	if (!FORTASK(thread, this_read_locks).rls_vec)
		pertask_readlocks_init(thread);
	if (!FORTASK(thread, this_connections).tc_static_v ||
	    FORTASK(thread, this_connections).tc_signals.ts_thread != thread)
		pertask_init_task_connections(thread);
}

/* Some some potential system inconsistencies that may
 * otherwise cause infinite loops when an assertion gets
 * triggered (after all: there is code that can get called
 * from within an assertion handler, which in turn is able
 * to cause other assertions) */
PRIVATE ATTR_COLDTEXT NOBLOCK void
NOTHROW(KCALL fixup_potential_system_inconsistencies)(void) {
	struct task *mythread = THIS_TASK;
	fixup_uninitialized_thread(&_boottask);
	fixup_uninitialized_thread(&_asyncwork);
	fixup_uninitialized_thread(&_bootidle);
	if (mythread != &_boottask &&
	    mythread != &_asyncwork &&
	    mythread != &_bootidle && mythread != NULL)
		fixup_uninitialized_thread(mythread);
	/* Poison the kernel (indicating that the kernel has become
	 * inconsistent, and can no longer be trusted to sporadically
	 * crash and burn) */
	COMPILER_WRITE_BARRIER();
	__kernel_poisoned = true;
	COMPILER_WRITE_BARRIER();
}


PRIVATE ATTR_COLDTEXT NOBLOCK bool
NOTHROW(KCALL is_pc)(void *pc) {
	struct vm_node *node;
	if (pc < (void *)KERNELSPACE_BASE)
		return false;
	node = vm_getnodeofaddress(&vm_kernel, pc);
	if (!node)
		return false;
	return (node->vn_prot & VM_PROT_EXEC) != 0;
}

INTERN ATTR_COLD ATTR_COLDTEXT void KCALL
kernel_halt_dump_traceback(pformatprinter printer, void *arg,
                           struct ucpustate const *__restrict dumpstate) {
	unsigned int error;
	struct ucpustate state;
	struct exception_info saved_info;
	instrlen_isa_t isa;
#ifdef LOG_STACK_REMAINDER
	uintptr_t last_good_sp;
#endif /* LOG_STACK_REMAINDER */
	fixup_potential_system_inconsistencies();
	memcpy(&state, dumpstate, sizeof(struct ucpustate));
	memcpy(&saved_info, &THIS_EXCEPTION_INFO, sizeof(struct exception_info));
#ifdef LOG_STACK_REMAINDER
	last_good_sp = ucpustate_getsp(&state);
#endif /* LOG_STACK_REMAINDER */
	isa = instrlen_isa_from_ucpustate(&state);
	addr2line_printf(printer, arg,
	                 (uintptr_t)instruction_trypred((void const *)ucpustate_getpc(&state), isa),
	                 ucpustate_getpc(&state),
	                 "Caused here [sp=%p]",
	                 (void *)ucpustate_getsp(&state));
	for (;;) {
		struct ucpustate old_state;
		memcpy(&old_state, &state, sizeof(struct ucpustate));
		error = unwind((void *)(ucpustate_getpc(&old_state) - 1),
		               &unwind_getreg_ucpustate, &old_state,
		               &unwind_setreg_ucpustate, &state);
		if (error != UNWIND_SUCCESS)
			break;
		addr2line_printf(printer, arg,
		                 (uintptr_t)instruction_trypred((void const *)ucpustate_getpc(&state),
		                                                instrlen_isa_from_ucpustate(&state)),
		                 ucpustate_getpc(&state),
		                 "Called here [sp=%p]",
		                 (void *)ucpustate_getsp(&state));
#ifdef LOG_STACK_REMAINDER
		last_good_sp = ucpustate_getsp(&state);
#endif /* LOG_STACK_REMAINDER */
	}
	if (error != UNWIND_NO_FRAME)
		format_printf(printer, arg, "Unwind failure: %u\n", error);
#ifdef LOG_STACK_REMAINDER
	{
		void *minaddr, *endaddr;
		get_stack_for(&minaddr, &endaddr, (void *)last_good_sp);
		if (last_good_sp >= (uintptr_t)minaddr &&
		    last_good_sp < (uintptr_t)endaddr) {
			bool is_first = true;
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
			uintptr_t iter;
			iter = FLOOR_ALIGN(last_good_sp, sizeof(void *));
			for (; iter < (uintptr_t)endaddr; iter += sizeof(void *))
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
			uintptr_t iter;
			iter  = CEIL_ALIGN(last_good_sp, sizeof(void *));
			while (iter > (uintptr_t)minaddr)
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
			{
				void *pc;
#ifndef __ARCH_STACK_GROWS_DOWNWARDS
				iter -= sizeof(void *);
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
				TRY {
					pc = *(void **)iter;
				} EXCEPT {
					break;
				}
				if (!is_pc(pc))
					continue;
				if (is_first) {
					format_printf(printer, arg, "Analyzing remainder of stack\n");
					is_first = false;
				}
				addr2line_printf(printer, arg,
				                 (uintptr_t)instruction_trypred(pc, isa),
				                 (uintptr_t)pc,
				                 "Return address from [sp=%p]",
				                 iter);
			}
		}
	}
#endif /* LOG_STACK_REMAINDER */
	memcpy(&THIS_EXCEPTION_INFO, &saved_info, sizeof(struct exception_info));
}


#ifdef CONFIG_HAVE_DEBUGGER
PRIVATE ATTR_DBGTEXT void KCALL
panic_assert_dbg_main(void *arg) {
	struct assert_args *args;
	args = (struct assert_args *)arg;
	dbg_printf(DF_COLOR(DBG_COLOR_WHITE, DBG_COLOR_MAROON, "Assertion failure") "\n"
	           "expr: "  DF_FGCOLOR(DBG_COLOR_WHITE, "%s") "\n"
	           "file: "  DF_FGCOLOR(DBG_COLOR_WHITE, "%s")
	           " (line " DF_FGCOLOR(DBG_COLOR_WHITE, "%u") ")\n",
	           args->aa_expr,
	           args->aa_file,
	           args->aa_line);
	if (args->aa_func)
		dbg_printf(DBGSTR("func: " DF_FGCOLOR(DBG_COLOR_WHITE, "%s") "\n"), args->aa_func);
	if (args->aa_format) {
		dbg_print(DBGSTR("mesg: " DF_SETCOLOR(DBG_COLOR_TEAL, DBG_COLOR_BLACK)));
		dbg_indent += 6;
		format_vprintf(&dbg_printer, NULL, args->aa_format, args->aa_args);
		dbg_indent -= 6;
		dbg_print(DBGSTR(DF_DEFCOLOR "\n"));
	}
	dbg_printf(DBGSTR("addr: " DF_FGCOLOR(DBG_COLOR_WHITE, "%p") "\n"),
	           kcpustate_getpc(&args->aa_state));
	dbg_main(0);
}
#endif /* CONFIG_HAVE_DEBUGGER */


INTERN ATTR_COLD ATTR_COLDTEXT ATTR_NOINLINE ATTR_NORETURN void FCALL
libc_assertion_failure_core(struct assert_args *__restrict args) {
	PREEMPTION_DISABLE();
	fixup_potential_system_inconsistencies();
	printk(KERN_RAW "\n\n\n");
	printk(KERN_EMERG "Assertion Failure [pc=%p]\n",
	       kcpustate_getpc(&args->aa_state));
	printk(KERN_RAW "%s(%d) : %s%s%s\n",
	       args->aa_file, args->aa_line,
	       args->aa_func ? args->aa_func : "",
	       args->aa_func ? " : " : "",
	       args->aa_expr);
	if (args->aa_format) {
		va_list vargs;
		va_copy(vargs, args->aa_args);
		format_vprintf(&syslog_printer, SYSLOG_LEVEL_RAW, args->aa_format, vargs);
		va_end(vargs);
		printk(KERN_RAW "\n");
	}
	{
		struct ucpustate temp;
		kcpustate_to_ucpustate(&args->aa_state, &temp);
		kernel_halt_dump_traceback(&syslog_printer, SYSLOG_LEVEL_RAW, &temp);
	}
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled())
		kernel_debugtrap(&args->aa_state, SIGTRAP);
#ifdef CONFIG_HAVE_DEBUGGER
	/* Enter the debugger */
	dbg_enter(&panic_assert_dbg_main, args,
	          sizeof(*args), &args->aa_state);
#else /* CONFIG_HAVE_DEBUGGER */
	PREEMPTION_HALT();
#endif /* !CONFIG_HAVE_DEBUGGER */
}




#ifdef CONFIG_HAVE_DEBUGGER
PRIVATE ATTR_DBGTEXT void KCALL
panic_assert_chk_print_message(void *arg) {
	struct assert_args *args;
	args = (struct assert_args *)arg;
	dbg_printf(DBGSTR("expr: " DF_FGCOLOR(DBG_COLOR_WHITE, "%s") "\n"
	                  "file: " DF_FGCOLOR(DBG_COLOR_WHITE, "%s")
	                  " (line " DF_FGCOLOR(DBG_COLOR_WHITE, "%u") ")\n"),
	           args->aa_expr,
	           args->aa_file,
	           args->aa_line);
	if (args->aa_func)
		dbg_printf(DBGSTR("func: " DF_FGCOLOR(DBG_COLOR_WHITE, "%s") "\n"), args->aa_func);
	if (args->aa_format) {
		va_list vargs;
		dbg_print(DBGSTR("mesg: " DF_SETCOLOR(DBG_COLOR_TEAL, DBG_COLOR_BLACK)));
		dbg_indent += 6;
		va_copy(vargs, args->aa_args);
		format_vprintf(&dbg_printer, NULL, args->aa_format, vargs);
		va_end(vargs);
		dbg_indent -= 6;
		dbg_print(DBGSTR(DF_DEFCOLOR "\n"));
	}
	dbg_printf(DBGSTR("addr: " DF_FGCOLOR(DBG_COLOR_WHITE, "%p") "\n"),
	           kcpustate_getpc(&args->aa_state));
}


#define ASSERTION_OPTION_RETRY          0
#define ASSERTION_OPTION_DEBUG          1
#define ASSERTION_OPTION_IGNORE         2
#define ASSERTION_OPTION_IGNORE_ALWAYS  3

PRIVATE ATTR_DBGRODATA char const *const assert_chk_options[] = {
	[ASSERTION_OPTION_RETRY]         = "retry",
	[ASSERTION_OPTION_DEBUG]         = "debug",
	[ASSERTION_OPTION_IGNORE]        = "ignore",
	[ASSERTION_OPTION_IGNORE_ALWAYS] = "ignore (always)",
	NULL
};
PRIVATE ATTR_DBGBSS uintptr_t always_ignored_assertions[64] = { 0 };
PRIVATE ATTR_PURE ATTR_COLDTEXT NOBLOCK bool
NOTHROW(KCALL is_pc_always_ignored)(uintptr_t pc) {
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(always_ignored_assertions); ++i) {
		if (pc == always_ignored_assertions[i])
			return true;
	}
	return false;
}

PRIVATE ATTR_COLD ATTR_COLDTEXT void KCALL
panic_assert_chk_dbg_main(void *arg) {
	struct assert_args *args;
	unsigned int option;
	args = (struct assert_args *)arg;
	if (is_pc_always_ignored(dbg_getpcreg(DBG_REGLEVEL_TRAP))) {
		option = ASSERTION_OPTION_IGNORE;
		goto handle_retry_or_ignore;
	}

	/* Display a menu to let the user select what to do about the assertion... */
	option = dbg_menuex(DF_SETCOLOR(DBG_COLOR_WHITE, DBG_COLOR_MAROON)
	                    "Assertion failure" DF_DEFCOLOR,
	                    assert_chk_options,
	                    0,
	                    &panic_assert_chk_print_message,
	                    args);
	if (option == ASSERTION_OPTION_IGNORE_ALWAYS) {
		unsigned int i;
		for (i = 0; i < COMPILER_LENOF(always_ignored_assertions); ++i) {
			if (always_ignored_assertions[i])
				continue;
			always_ignored_assertions[i] = dbg_getpcreg(DBG_REGLEVEL_TRAP);
			break;
		}
		option = ASSERTION_OPTION_IGNORE;
	}
	if (option == ASSERTION_OPTION_RETRY ||
	    option == ASSERTION_OPTION_IGNORE) {
		uintptr_t acheck_result;
handle_retry_or_ignore:
		acheck_result = option == ASSERTION_OPTION_RETRY ? 1 : 0;
		/* Select the current thread as target for register accessors. */
		dbg_current = THIS_TASK;
		/* TODO: Make this part arch-independent */
#ifdef __x86_64__
		x86_dbg_setregbyidp(DBG_REGLEVEL_TRAP,
		                    X86_REGISTER_GENERAL_PURPOSE_RAX,
		                    acheck_result);
#elif defined(__i386__)
		x86_dbg_setregbyidp(DBG_REGLEVEL_TRAP,
		                    X86_REGISTER_GENERAL_PURPOSE_EAX,
		                    acheck_result);
#else
#error Unsupported arch
#endif
		return;
	}
	/* Enter debugger mode. */
	dbg_fillscreen(' ');
	dbg_setcur(0, 0);
	panic_assert_dbg_main(arg);
}
#endif /* CONFIG_HAVE_DEBUGGER */

INTERN ATTR_COLD ATTR_COLDTEXT ATTR_NOINLINE struct kcpustate *FCALL
libc_assertion_check_core(struct assert_args *__restrict args) {
	/* Check if assertion failures at the caller's PC should always be ignored. */
#ifdef CONFIG_HAVE_DEBUGGER
	if (is_pc_always_ignored(kcpustate_getpc(&args->aa_state))) {
		/* TODO: Make this part arch-independent */
#ifdef __x86_64__
		args->aa_state.kcs_gpregs.gp_rax = 0;
#elif defined(__i386__)
		args->aa_state.kcs_gpregs.gp_eax = 0;
#else
#error Unsupported arch
#endif
		return &args->aa_state;
	}
#endif /* CONFIG_HAVE_DEBUGGER */
	PREEMPTION_DISABLE();
	fixup_potential_system_inconsistencies();
	printk(KERN_RAW "\n\n\n");
	printk(KERN_EMERG "Assertion Check [pc=%p]\n",
	       kcpustate_getpc(&args->aa_state));
	printk(KERN_RAW "%s(%d) : %s%s%s\n",
	       args->aa_file, args->aa_line,
	       args->aa_func ? args->aa_func : "",
	       args->aa_func ? " : " : "",
	       args->aa_expr);
	if (args->aa_format) {
		va_list vargs;
		va_copy(vargs, args->aa_args);
		format_vprintf(&syslog_printer, SYSLOG_LEVEL_RAW, args->aa_format, vargs);
		va_end(vargs);
		printk(KERN_RAW "\n");
	}
	{
		struct ucpustate temp;
		kcpustate_to_ucpustate(&args->aa_state, &temp);
		kernel_halt_dump_traceback(&syslog_printer, SYSLOG_LEVEL_RAW, &temp);
	}
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled())
		kernel_debugtrap(&args->aa_state, SIGTRAP);
#ifdef CONFIG_HAVE_DEBUGGER
	/* Enter the debugger */
	{
		struct kcpustate *result;
		result = dbg_enter_r(&panic_assert_chk_dbg_main,
		                     args, sizeof(*args),
		                     &args->aa_state);
		return result;
	}
#else /* CONFIG_HAVE_DEBUGGER */
	PREEMPTION_HALT();
#endif /* !CONFIG_HAVE_DEBUGGER */
}



#ifdef CONFIG_HAVE_DEBUGGER
PRIVATE ATTR_DBGTEXT void KCALL
panic_genfail_dbg_main(/*char const **/ void *message) {
	uintptr_t pc, prev_pc;
	instrlen_isa_t isa;
	pc      = dbg_getpcreg(DBG_REGLEVEL_TRAP);
	isa     = dbg_instrlen_isa(DBG_REGLEVEL_TRAP);
	prev_pc = (uintptr_t)instruction_trypred((void const *)pc, isa);
	dbg_printf(DBGSTR(DF_SETCOLOR(DBG_COLOR_WHITE, DBG_COLOR_MAROON) "%s" DF_DEFCOLOR "%[vinfo:"
	                  "file: " DF_WHITE("%f") " (line " DF_WHITE("%l") ", column " DF_WHITE("%c") ")\n"
	                  "func: " DF_WHITE("%n") "\n]"
	                  "addr: " DF_WHITE("%p") "+" DF_WHITE("%Iu") "\n"),
	           message, prev_pc, prev_pc,
	           (size_t)(pc - prev_pc));
	dbg_main(0);
}
#endif /* CONFIG_HAVE_DEBUGGER */


/* The `__stack_chk_guard' global is read _very_ often,
 * so place in in the COMPACT_DATA segment. */
#ifndef NDEBUG
PUBLIC ATTR_READMOSTLY uintptr_t __stack_chk_guard = 0x123baf37;
#else /* !NDEBUG */
PUBLIC ATTR_COLDDATA uintptr_t __stack_chk_guard = 0x123baf37;
#endif /* NDEBUG */

INTERN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN void FCALL
libc_stack_failure_core(struct kcpustate *__restrict state) {
	struct ucpustate ustate;
	PREEMPTION_DISABLE();
	fixup_potential_system_inconsistencies();
	printk(KERN_RAW "\n\n\n");
	printk(KERN_EMERG "Stack check failure [pc=%p]\n", kcpustate_getpc(state));
	kcpustate_to_ucpustate(state, &ustate);
	kernel_halt_dump_traceback(&syslog_printer, SYSLOG_LEVEL_RAW, &ustate);
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled())
		kernel_debugtrap(state, SIGSEGV);
#ifdef CONFIG_HAVE_DEBUGGER
	/* Enter the debugger */
	dbg_enter(&panic_genfail_dbg_main,
	          (void *)DBGSTR("Stack check failure (corrupted cookie)\n"),
	          state);
#else /* CONFIG_HAVE_DEBUGGER */
	PREEMPTION_HALT();
#endif /* !CONFIG_HAVE_DEBUGGER */
}

INTERN ATTR_COLD ATTR_COLDTEXT ATTR_NORETURN void FCALL
libc_abort_failure_core(struct kcpustate *__restrict state) {
	struct ucpustate ustate;
	PREEMPTION_DISABLE();
	fixup_potential_system_inconsistencies();
	printk(KERN_RAW "\n\n\n");
	printk(KERN_EMERG "Kernel aborted [pc=%p]\n", kcpustate_getpc(state));
	kcpustate_to_ucpustate(state, &ustate);
	kernel_halt_dump_traceback(&syslog_printer, SYSLOG_LEVEL_RAW, &ustate);
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled())
		kernel_debugtrap(state, SIGABRT);
#ifdef CONFIG_HAVE_DEBUGGER
	/* Enter the debugger */
	dbg_enter(&panic_genfail_dbg_main,
	          (void *)DBGSTR("Kernel called abort()\n"),
	          state);
#else /* CONFIG_HAVE_DEBUGGER */
	PREEMPTION_HALT();
#endif /* !CONFIG_HAVE_DEBUGGER */
}


#ifdef CONFIG_HAVE_DEBUGGER
struct panic_args {
	char const *format;
	va_list     args;
};
PRIVATE ATTR_DBGTEXT void KCALL
panic_kernel_dbg_main(void *arg) {
	struct panic_args *args;
	uintptr_t pc, prev_pc;
	instrlen_isa_t isa;
	args = (struct panic_args *)arg;
	pc      = dbg_getpcreg(DBG_REGLEVEL_TRAP);
	isa     = dbg_instrlen_isa(DBG_REGLEVEL_TRAP);
	prev_pc = (uintptr_t)instruction_trypred((void const *)pc, isa);
	dbg_printf(DBGSTR("Kernel Panic\n"
	                  "%[vinfo:" "file: " DF_WHITE("%f") " (line " DF_WHITE("%l") ", column " DF_WHITE("%c") ")\n"
	                             "func: " DF_WHITE("%n") "\n"
	                  "]"),
	           prev_pc);
	if (args->format) {
		dbg_print(DBGSTR("mesg: " DF_SETCOLOR(DBG_COLOR_TEAL, DBG_COLOR_BLACK)));
		dbg_indent += 6;
		format_vprintf(&dbg_printer, NULL, args->format, args->args);
		dbg_indent -= 6;
		dbg_print(DF_DEFCOLOR "\n");
	}
	dbg_printf(DBGSTR("addr: " DF_WHITE("%p") "+" DF_WHITE("%Iu") "\n"),
	           prev_pc, (size_t)(pc - prev_pc));
	dbg_main(0);
}
#endif /* CONFIG_HAVE_DEBUGGER */

PUBLIC ATTR_NORETURN ATTR_COLD ATTR_COLDTEXT void FCALL
kernel_vpanic_ucpustate(struct ucpustate *__restrict state,
                        char const *format, va_list args) {
	PREEMPTION_DISABLE();
	fixup_potential_system_inconsistencies();
	printk(KERN_RAW "\n\n\n");
	printk(KERN_EMERG "Kernel Panic [pc=%p]\n",
	       ucpustate_getpc(state));
	if (format) {
		va_list cargs;
		va_copy(cargs, args);
		format_vprintf(&syslog_printer, SYSLOG_LEVEL_EMERG, format, cargs);
		va_end(cargs);
		printk(KERN_EMERG "\n");
	}
	kernel_halt_dump_traceback(&syslog_printer, SYSLOG_LEVEL_RAW, state);
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled())
		kernel_debugtrap(state, SIGABRT);
#ifdef CONFIG_HAVE_DEBUGGER
	/* Enter the debugger */
	{
		struct panic_args pargs;
		if (format)
			va_copy(pargs.args, args);
		pargs.format = format;
		dbg_enter(&panic_kernel_dbg_main, &pargs, state);
	}
#else /* CONFIG_HAVE_DEBUGGER */
	PREEMPTION_HALT();
#endif /* !CONFIG_HAVE_DEBUGGER */
}

PUBLIC ATTR_NORETURN ATTR_COLD ATTR_COLDTEXT void FCALL
kernel_vpanic_lcpustate(struct lcpustate *__restrict state,
                        char const *format, va_list args) {
	struct ucpustate ustate;
	lcpustate_to_ucpustate(state, &ustate);
	kernel_vpanic_ucpustate(&ustate, format, args);
}

PUBLIC ATTR_NORETURN ATTR_COLD ATTR_COLDTEXT void FCALL
kernel_vpanic_kcpustate(struct kcpustate *__restrict state,
                        char const *format, va_list args) {
	struct ucpustate ustate;
	kcpustate_to_ucpustate(state, &ustate);
	kernel_vpanic_ucpustate(&ustate, format, args);
}

PUBLIC ATTR_NORETURN ATTR_COLD ATTR_COLDTEXT void FCALL
kernel_vpanic_icpustate(struct icpustate *__restrict state,
                        char const *format, va_list args) {
	struct ucpustate ustate;
	icpustate_to_ucpustate(state, &ustate);
	kernel_vpanic_ucpustate(&ustate, format, args);
}

PUBLIC ATTR_NORETURN ATTR_COLD ATTR_COLDTEXT void FCALL
kernel_vpanic_scpustate(struct scpustate *__restrict state,
                        char const *format, va_list args) {
	struct ucpustate ustate;
	scpustate_to_ucpustate(state, &ustate);
	kernel_vpanic_ucpustate(&ustate, format, args);
}

PUBLIC ATTR_NORETURN ATTR_COLD ATTR_COLDTEXT void FCALL
kernel_vpanic_fcpustate(struct fcpustate *__restrict state,
                        char const *format, va_list args) {
	struct ucpustate ustate;
	/* XXX: Don't convert to ucpustate. - This causes information to be lost... */
	fcpustate_to_ucpustate(state, &ustate);
	kernel_vpanic_ucpustate(&ustate, format, args);
}



PUBLIC ATTR_NORETURN ATTR_COLD ATTR_COLDTEXT void VCALL
kernel_panic_ucpustate(struct ucpustate *__restrict state,
                       char const *format, ...) {
	va_list args;
	va_start(args, format);
	kernel_vpanic_ucpustate(state, format, args);
}

PUBLIC ATTR_NORETURN ATTR_COLD ATTR_COLDTEXT void VCALL
kernel_panic_lcpustate(struct lcpustate *__restrict state,
                       char const *format, ...) {
	va_list args;
	va_start(args, format);
	kernel_vpanic_lcpustate(state, format, args);
}

PUBLIC ATTR_NORETURN ATTR_COLD ATTR_COLDTEXT void VCALL
kernel_panic_kcpustate(struct kcpustate *__restrict state,
                       char const *format, ...) {
	va_list args;
	va_start(args, format);
	kernel_vpanic_kcpustate(state, format, args);
}

PUBLIC ATTR_NORETURN ATTR_COLD ATTR_COLDTEXT void VCALL
kernel_panic_icpustate(struct icpustate *__restrict state,
                       char const *format, ...) {
	va_list args;
	va_start(args, format);
	kernel_vpanic_icpustate(state, format, args);
}

PUBLIC ATTR_NORETURN ATTR_COLD ATTR_COLDTEXT void VCALL
kernel_panic_scpustate(struct scpustate *__restrict state,
                       char const *format, ...) {
	va_list args;
	va_start(args, format);
	kernel_vpanic_scpustate(state, format, args);
}

PUBLIC ATTR_NORETURN ATTR_COLD ATTR_COLDTEXT void VCALL
kernel_panic_fcpustate(struct fcpustate *__restrict state,
                       char const *format, ...) {
	va_list args;
	va_start(args, format);
	kernel_vpanic_fcpustate(state, format, args);
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_PANIC_C */
