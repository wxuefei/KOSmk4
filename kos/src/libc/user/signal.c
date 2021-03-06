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
#ifndef GUARD_LIBC_USER_SIGNAL_C
#define GUARD_LIBC_USER_SIGNAL_C 1

#include "../api.h"
/**/

#include <hybrid/atomic.h>

#include <asm/signum-values-dos.h>
#include <asm/signum-values-kos.h>
#include <kos/exec/idata.h>
#include <kos/syscalls.h>

#include <stddef.h>
#include <string.h>
#include <unistd.h>

#include "../libc/pthread.h"
#include "signal.h"
#include "string.h"

DECL_BEGIN

LOCAL signo_t LIBCCALL
libc_signo_dos2kos(signo_t dos_signo) {
	if (dos_signo == __DOS_SIGABRT)
		return __KOS_SIGABRT;
	return dos_signo;
}

LOCAL int LIBCCALL
libc_sigms_dos2kos(int dos_sigms) {
	if ((unsigned int)dos_sigms & (1 << (__DOS_SIGABRT - 1))) {
		dos_sigms &= ~(1 << (__DOS_SIGABRT - 1));
		dos_sigms |= ~(1 << (__KOS_SIGABRT - 1));
	}
	return dos_sigms;
}


#ifdef LIBC_ARCH_HAVE_SIG_RESTORE
INTDEF void /*ASMCALL*/ libc_sig_restore(void);
#define SET_SIGRESTORE(x) ((x).sa_restorer = &libc_sig_restore, (x).sa_flags |= SA_RESTORER)
#endif /* LIBC_ARCH_HAVE_SIG_RESTORE */

#ifndef SET_SIGRESTORE
#define SET_SIGRESTORE(x) (void)0
#endif /* !SET_SIGRESTORE */




/*[[[head:libd_raise,hash:CRC-32=0x8c6e30c8]]]*/
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") int
NOTHROW_NCX(LIBDCALL libd_raise)(signo_t signo)
/*[[[body:libd_raise]]]*/
{
	return libc_raise(libc_signo_dos2kos(signo));
}
/*[[[end:libd_raise]]]*/

/*[[[head:libc_raise,hash:CRC-32=0xbfc984b3]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_raise)(signo_t signo)
/*[[[body:libc_raise]]]*/
{
	return kill(getpid(),
	            (syscall_ulong_t)(syscall_slong_t)signo);
}
/*[[[end:libc_raise]]]*/

/*[[[head:libd_sysv_signal,hash:CRC-32=0xe68d1b83]]]*/
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") sighandler_t
NOTHROW_NCX(LIBDCALL libd_sysv_signal)(signo_t signo,
                                       sighandler_t handler)
/*[[[body:libd_sysv_signal]]]*/
{
	return libc_sysv_signal(libc_signo_dos2kos(signo), handler);
}
/*[[[end:libd_sysv_signal]]]*/

/*[[[head:libc_sysv_signal,hash:CRC-32=0x39dc26c6]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") sighandler_t
NOTHROW_NCX(LIBCCALL libc_sysv_signal)(signo_t signo,
                                       sighandler_t handler)
/*[[[body:libc_sysv_signal]]]*/
{
	struct sigaction act, oact;
	if unlikely(handler == SIG_ERR) {
		libc_seterrno(EINVAL);
		return SIG_ERR;
	}
	act.sa_handler = handler;
	libc_sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESETHAND | SA_NOMASK | SA_INTERRUPT;
	/*act.sa_flags &= ~SA_RESTART;*/
	SET_SIGRESTORE(act);
	if unlikely(sigaction(signo, &act, &oact))
		oact.sa_handler = SIG_ERR;
	return oact.sa_handler;
}
/*[[[end:libc_sysv_signal]]]*/

/*[[[head:libc_sigblock,hash:CRC-32=0x32d96dc3]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigblock)(int mask)
/*[[[body:libc_sigblock]]]*/
{
	errno_t result;
	result = sys_rt_sigprocmask(SIG_BLOCK,
	                            (sigset_t *)&mask,
	                            NULL,
	                            sizeof(mask));
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sigblock]]]*/

/*[[[head:libc_sigsetmask,hash:CRC-32=0xcfcf517a]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigsetmask)(int mask)
/*[[[body:libc_sigsetmask]]]*/
{
	errno_t result;
	result = sys_rt_sigprocmask(SIG_SETMASK,
	                            (sigset_t *)&mask,
	                            NULL,
	                            sizeof(mask));
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sigsetmask]]]*/

/*[[[head:libc_siggetmask,hash:CRC-32=0x597fe5fd]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_siggetmask)(void)
/*[[[body:libc_siggetmask]]]*/
{
	int value, result;
	result = sys_rt_sigprocmask(SIG_SETMASK,
	                            NULL,
	                            (sigset_t *)&value,
	                            sizeof(value));
	if unlikely(E_ISERR(result)) {
		result = (int)libc_seterrno(-result);
	} else {
		result = value;
	}
	return result;
}
/*[[[end:libc_siggetmask]]]*/


#undef sys_siglist
#undef _sys_siglist
PRIVATE ATTR_SECTION(".bss.crt.errno.sys_siglist") char const *
libc_sys_siglist[NSIG] = { NULL };

DEFINE_PUBLIC_IDATA_G(sys_siglist, libc___p_sys_siglist, NSIG * __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA_G(_sys_siglist, libc___p_sys_siglist, NSIG * __SIZEOF_POINTER__);

/*[[[head:libc___p_sys_siglist,hash:CRC-32=0xa33e9b16]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_CONST ATTR_RETNONNULL WUNUSED char const *const *
NOTHROW(LIBCCALL libc___p_sys_siglist)(void)
/*[[[body:libc___p_sys_siglist]]]*/
{
	char const **result = libc_sys_siglist;
	if (!result[0]) {
		unsigned int i = NSIG;
		/* Lazily initialize */
		for (;;) {
			result[i] = libc_strsignal_s(i);
			COMPILER_WRITE_BARRIER();
			if (!i)
				break;
			--i;
		}
	}
	return result;
}
/*[[[end:libc___p_sys_siglist]]]*/

/*[[[head:libc_sigreturn,hash:CRC-32=0x5c20a42e]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_NORETURN void
NOTHROW_NCX(LIBCCALL libc_sigreturn)(struct sigcontext const *scp)
/*[[[body:libc_sigreturn]]]*/
/*AUTO*/{
	(void)scp;
	CRT_UNIMPLEMENTEDF("sigreturn(%p)", scp); /* TODO */
	assert_failed("Not implemented");
}
/*[[[end:libc_sigreturn]]]*/




PRIVATE ATTR_SECTION(".bss.crt.sched.signal") sigset_t __sigintr;

/*[[[head:libc_bsd_signal,hash:CRC-32=0x8260093]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") sighandler_t
NOTHROW_NCX(LIBCCALL libc_bsd_signal)(signo_t signo,
                                      sighandler_t handler)
/*[[[body:libc_bsd_signal]]]*/
{
	struct sigaction act, oact;
	if unlikely(handler == SIG_ERR) {
		libc_seterrno(EINVAL);
		return SIG_ERR;
	}
	if unlikely(handler == SIG_GET) {
		if unlikely(libc_sigaction(signo, NULL, &oact) < 0)
			oact.sa_handler = SIG_ERR;
	} else {
		act.sa_handler = handler;
		libc_sigemptyset(&act.sa_mask);
		libc_sigaddset(&act.sa_mask, signo);
		act.sa_flags = libc_sigismember(&__sigintr, signo) ? 0 : SA_RESTART;
		SET_SIGRESTORE(act);
		if unlikely(libc_sigaction(signo, &act, &oact) < 0)
			oact.sa_handler = SIG_ERR;
	}
	return oact.sa_handler;
}
/*[[[end:libc_bsd_signal]]]*/

/*[[[head:libd_bsd_signal,hash:CRC-32=0xb42e433d]]]*/
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") sighandler_t
NOTHROW_NCX(LIBDCALL libd_bsd_signal)(signo_t signo,
                                      sighandler_t handler)
/*[[[body:libd_bsd_signal]]]*/
{
	return libc_bsd_signal(libc_signo_dos2kos(signo), handler);
}
/*[[[end:libd_bsd_signal]]]*/


/*[[[head:libc___xpg_sigpause,hash:CRC-32=0xf7eccb73]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc___xpg_sigpause)(signo_t signo)
/*[[[body:libc___xpg_sigpause]]]*/
/*AUTO*/{
	(void)signo;
	CRT_UNIMPLEMENTEDF("__xpg_sigpause(%" PRIxN(__SIZEOF_SIGNO_T__) ")", signo); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc___xpg_sigpause]]]*/

/*[[[head:libc_kill,hash:CRC-32=0x4135227d]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_kill)(pid_t pid,
                                signo_t signo)
/*[[[body:libc_kill]]]*/
{
	errno_t result;
	result = sys_kill(pid, (syscall_ulong_t)(unsigned int)signo);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_kill]]]*/

/*[[[head:libc_sigprocmask,hash:CRC-32=0xf8ce3e0d]]]*/
/* @param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigprocmask)(__STDC_INT_AS_UINT_T how,
                                       sigset_t const *set,
                                       sigset_t *oset)
/*[[[body:libc_sigprocmask]]]*/
{
	errno_t result;
#ifdef __NR_sigprocmask
	result = sys_sigprocmask((syscall_ulong_t)(unsigned int)how,
	                         set, oset);
#else /* __NR_sigprocmask */
	result = sys_rt_sigprocmask((syscall_ulong_t)(unsigned int)how,
	                            set, oset, sizeof(sigset_t));
#endif /* !__NR_sigprocmask */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sigprocmask]]]*/

/*[[[head:libc_sigsuspend,hash:CRC-32=0xf8598483]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_sigsuspend)(sigset_t const *set)
/*[[[body:libc_sigsuspend]]]*/
{
	errno_t result;
#ifdef __NR_sigsuspend
	result = sys_sigsuspend(set);
#else /* __NR_sigsuspend */
	result = sys_rt_sigsuspend(set, sizeof(sigset_t));
#endif /* !__NR_sigsuspend */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sigsuspend]]]*/

/*[[[head:libc_sigaction,hash:CRC-32=0xe485d789]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigaction)(signo_t signo,
                                     struct sigaction const *act,
                                     struct sigaction *oact)
/*[[[body:libc_sigaction]]]*/
{
	errno_t result;
#ifdef LIBC_ARCH_HAVE_SIG_RESTORE
	struct sigaction real_act;
	if (act && !(act->sa_flags & SA_RESTORER)) {
		memcpy(&real_act, act, sizeof(struct sigaction));
		SET_SIGRESTORE(real_act);
		act = &real_act;
	}
#endif /* LIBC_ARCH_HAVE_SIG_RESTORE */
#ifdef __NR_sigaction
	result = sys_sigaction(signo, act, oact);
#else /* __NR_sigaction */
	result = sys_rt_sigaction(signo, act, oact, sizeof(sigset_t));
#endif /* !__NR_sigaction */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sigaction]]]*/

/*[[[head:libc_sigpending,hash:CRC-32=0xcbeddd74]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigpending)(sigset_t *__restrict set)
/*[[[body:libc_sigpending]]]*/
{
	errno_t result;
#ifdef __NR_sigpending
	result = sys_sigpending(set);
#else /* __NR_sigpending */
	result = sys_rt_sigpending(set, sizeof(sigset_t));
#endif /* !__NR_sigpending */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sigpending]]]*/

/*[[[head:libc_sigwait,hash:CRC-32=0xf3b20004]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_sigwait)(sigset_t const *__restrict set,
                                   signo_t *__restrict signo)
/*[[[body:libc_sigwait]]]*/
{
	errno_t result;
	siginfo_t info;
#ifdef __NR_rt_sigtimedwait64
	result = sys_rt_sigtimedwait64(set,
	                               &info,
	                               NULL,
	                               sizeof(sigset_t));
#else /* __NR_rt_sigtimedwait64 */
	result = sys_rt_sigtimedwait(set,
	                             &info,
	                             NULL,
	                             sizeof(sigset_t));
#endif /* !__NR_rt_sigtimedwait64 */
	if likely(result >= 0) {
		*signo = result;
		return 0;
	}
	return -result;
}
/*[[[end:libc_sigwait]]]*/

/*[[[head:libc_sigwaitinfo,hash:CRC-32=0x742d4cef]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_sigwaitinfo)(sigset_t const *__restrict set,
                                       siginfo_t *__restrict info)
/*[[[body:libc_sigwaitinfo]]]*/
{
	errno_t result;
#ifdef __NR_rt_sigtimedwait64
	result = sys_rt_sigtimedwait64(set,
	                               info,
	                               NULL,
	                               sizeof(sigset_t));
#else /* __NR_rt_sigtimedwait64 */
	result = sys_rt_sigtimedwait(set,
	                             info,
	                             NULL,
	                             sizeof(sigset_t));
#endif /* !__NR_rt_sigtimedwait64 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sigwaitinfo]]]*/

/*[[[head:libc_sigtimedwait,hash:CRC-32=0x6e3bc73e]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_sigtimedwait)(sigset_t const *__restrict set,
                                        siginfo_t *__restrict info,
                                        struct timespec const *timeout)
/*[[[body:libc_sigtimedwait]]]*/
{
	errno_t result;
	result = sys_rt_sigtimedwait(set,
	                             info,
	                             timeout,
	                             sizeof(sigset_t));
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sigtimedwait]]]*/

/*[[[head:libc_sigtimedwait64,hash:CRC-32=0x5521c50f]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_sigtimedwait64, libc_sigtimedwait);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_sigtimedwait64)(sigset_t const *__restrict set,
                                          siginfo_t *__restrict info,
                                          struct timespec64 const *timeout)
/*[[[body:libc_sigtimedwait64]]]*/
{
	errno_t result;
	result = sys_rt_sigtimedwait64(set,
	                               info,
	                               timeout,
	                               sizeof(sigset_t));
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_sigtimedwait64]]]*/

/*[[[head:libc_sigqueue,hash:CRC-32=0x24374bab]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigqueue)(pid_t pid,
                                    signo_t signo,
                                    union sigval const val)
/*[[[body:libc_sigqueue]]]*/
{
	siginfo_t info;
	memset(&info, 0, sizeof(siginfo_t));
	info.si_value = val;
	info.si_code  = SI_QUEUE;
	return sigqueueinfo(pid, signo, &info);
}
/*[[[end:libc_sigqueue]]]*/

/*[[[head:libc_sigqueueinfo,hash:CRC-32=0xc4bc11c]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((3)) int
NOTHROW_NCX(LIBCCALL libc_sigqueueinfo)(pid_t tgid,
                                        signo_t signo,
                                        siginfo_t const *uinfo)
/*[[[body:libc_sigqueueinfo]]]*/
{
	errno_t result;
	result = sys_rt_sigqueueinfo(tgid,
	                             (syscall_ulong_t)(unsigned int)signo,
	                             uinfo);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sigqueueinfo]]]*/

/*[[[head:libc_tgsigqueueinfo,hash:CRC-32=0xa3e87001]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((4)) int
NOTHROW_NCX(LIBCCALL libc_tgsigqueueinfo)(pid_t tgid,
                                          pid_t tid,
                                          signo_t signo,
                                          siginfo_t const *uinfo)
/*[[[body:libc_tgsigqueueinfo]]]*/
{
	errno_t result;
	result = sys_rt_tgsigqueueinfo(tgid,
	                               tid,
	                               (syscall_ulong_t)(unsigned int)signo,
	                               uinfo);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_tgsigqueueinfo]]]*/

/*[[[head:libc_killpg,hash:CRC-32=0x632634b6]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_killpg)(pid_t pgrp,
                                  signo_t signo)
/*[[[body:libc_killpg]]]*/
{
	return kill(-pgrp, signo);
}
/*[[[end:libc_killpg]]]*/

/*[[[head:libc_psignal,hash:CRC-32=0x40b58e8a]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") void
NOTHROW_NCX(LIBCCALL libc_psignal)(signo_t signo,
                                   char const *s)
/*[[[body:libc_psignal]]]*/
/*AUTO*/{
	(void)signo;
	(void)s;
	CRT_UNIMPLEMENTEDF("psignal(%" PRIxN(__SIZEOF_SIGNO_T__) ", %q)", signo, s); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_psignal]]]*/

/*[[[head:libc_psiginfo,hash:CRC-32=0xd85c4a47]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_psiginfo)(siginfo_t const *pinfo,
                                    char const *s)
/*[[[body:libc_psiginfo]]]*/
/*AUTO*/{
	(void)pinfo;
	(void)s;
	CRT_UNIMPLEMENTEDF("psiginfo(%p, %q)", pinfo, s); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_psiginfo]]]*/

/*[[[head:libc_siginterrupt,hash:CRC-32=0x7be25065]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_siginterrupt)(signo_t signo,
                                        __STDC_INT_AS_UINT_T interrupt)
/*[[[body:libc_siginterrupt]]]*/
{
	struct sigaction action;
	if (sigaction(signo, (struct sigaction *)NULL, &action) < 0)
		goto err;
	if (interrupt) {
		libc_sigaddset(&__sigintr, signo);
		action.sa_flags &= ~SA_RESTART;
	} else {
		libc_sigdelset(&__sigintr, signo);
		action.sa_flags |= SA_RESTART;
	}
	if (libc_sigaction(signo, &action, (struct sigaction *)NULL) < 0)
		goto err;
	return 0;
err:
	return -1;
}
/*[[[end:libc_siginterrupt]]]*/

/*[[[head:libc_sigstack,hash:CRC-32=0x7f3bfb8c]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigstack)(struct sigstack *ss,
                                    struct sigstack *oss)
/*[[[body:libc_sigstack]]]*/
{
	struct sigaltstack ass, aoss;
	int result;
	if (ss) {
		ass.ss_flags = ss->ss_onstack
		               ? SS_ONSTACK
		               : SS_DISABLE;
		ass.ss_sp   = ss->ss_sp;
		ass.ss_size = (size_t)-1;
	}
	result = sigaltstack(ss ? &ass : NULL,
	                     oss ? &aoss : NULL);
	if (likely(!result) && oss) {
		oss->ss_onstack = !!(aoss.ss_flags & SS_ONSTACK);
		oss->ss_sp      = aoss.ss_sp;
	}
	return result;
}
/*[[[end:libc_sigstack]]]*/

/*[[[head:libc_sigaltstack,hash:CRC-32=0xea1267]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigaltstack)(struct sigaltstack const *ss,
                                       struct sigaltstack *oss)
/*[[[body:libc_sigaltstack]]]*/
{
	errno_t result;
	result = sys_sigaltstack(ss, oss);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sigaltstack]]]*/


PRIVATE int LIBCCALL
set_single_signal_action(int sig, int how) {
	sigset_t set;
	libc_sigemptyset(&set);
	libc_sigaddset(&set, sig);
	return libc_sigprocmask(how, &set, NULL);
}

/*[[[head:libc_sighold,hash:CRC-32=0xb5de5490]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sighold)(signo_t signo)
/*[[[body:libc_sighold]]]*/
{
	return set_single_signal_action(signo, SIG_BLOCK);
}
/*[[[end:libc_sighold]]]*/

/*[[[head:libc_sigrelse,hash:CRC-32=0xce23f035]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigrelse)(signo_t signo)
/*[[[body:libc_sigrelse]]]*/
{
	return set_single_signal_action(signo, SIG_UNBLOCK);
}
/*[[[end:libc_sigrelse]]]*/

/*[[[head:libc_sigignore,hash:CRC-32=0x197c5558]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigignore)(signo_t signo)
/*[[[body:libc_sigignore]]]*/
{
	return libc_bsd_signal(signo, SIG_IGN) == SIG_ERR ? -1 : 0;
}
/*[[[end:libc_sigignore]]]*/

/*[[[head:libc_sigset,hash:CRC-32=0x1270dec0]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") sighandler_t
NOTHROW_NCX(LIBCCALL libc_sigset)(signo_t signo,
                                  sighandler_t disp)
/*[[[body:libc_sigset]]]*/
{
	struct sigaction act, oact;
	sigset_t set, oset;
	if unlikely(disp == SIG_ERR)
		goto err_inval;
	libc_sigemptyset(&set);
	libc_sigaddset(&set, signo);
	if (disp == SIG_HOLD) {
		if unlikely(libc_sigprocmask(SIG_BLOCK, &set, &oset) < 0)
			goto err;
		if unlikely(libc_sigismember(&oset, signo))
			goto err;
		if unlikely(libc_sigaction(signo, NULL, &oact) < 0)
			goto err;
		return oact.sa_handler;
	}
	act.sa_handler = disp;
	libc_sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	SET_SIGRESTORE(act);
	if unlikely(sigaction(signo, &act, &oact) < 0)
		goto err;
	if unlikely(sigprocmask(SIG_UNBLOCK, &set, &oset) < 0)
		goto err;
	return libc_sigismember(&oset, signo)
	       ? SIG_HOLD
	       : oact.sa_handler;
err_inval:
	libc_seterrno(EINVAL);
err:
	return SIG_ERR;
}
/*[[[end:libc_sigset]]]*/

/*[[[head:libc_pthread_sigmask,hash:CRC-32=0xc2fbcd33]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_pthread_sigmask)(__STDC_INT_AS_UINT_T how,
                                           sigset_t const *newmask,
                                           sigset_t *oldmask)
/*[[[body:libc_pthread_sigmask]]]*/
{
	errno_t result;
#ifdef __NR_sigprocmask
	result = sys_sigprocmask((syscall_ulong_t)(unsigned int)how,
	                         newmask, oldmask);
#else /* __NR_sigprocmask */
	result = sys_rt_sigprocmask((syscall_ulong_t)(unsigned int)how,
	                            newmask, oldmask, sizeof(sigset_t));
#endif /* !__NR_sigprocmask */
	return -result;
}
/*[[[end:libc_pthread_sigmask]]]*/

/*[[[head:libc_pthread_kill,hash:CRC-32=0x7438a00e]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_pthread_kill)(pthread_t threadid,
                                        signo_t signo)
/*[[[body:libc_pthread_kill]]]*/
{
	struct pthread *pt = (struct pthread *)threadid;
	pid_t tid;
	errno_t result;
	tid = ATOMIC_READ(pt->pt_tid);
	if unlikely(tid == 0)
		return ESRCH;
	/* No way to handle the case where `pt_tid' got set
	 * to zero, and `tid' got re-used. - Sorry... */
	result = sys_kill(tid, signo);
	return -result;
}
/*[[[end:libc_pthread_kill]]]*/

/*[[[head:libc_pthread_sigqueue,hash:CRC-32=0xef2ef369]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_pthread_sigqueue)(pthread_t threadid,
                                            signo_t signo,
                                            union sigval const value)
/*[[[body:libc_pthread_sigqueue]]]*/
{
	struct pthread *pt = (struct pthread *)threadid;
	siginfo_t info;
	errno_t result;
	pid_t tid;
	memset(&info, 0, sizeof(siginfo_t));
	info.si_value = value;
	info.si_code  = SI_QUEUE;
	tid = ATOMIC_READ(pt->pt_tid);
	if unlikely(tid == 0)
		return ESRCH;
	/* No way to handle the case where `pt_tid' got set
	 * to zero, and `tid' got re-used. - Sorry... */
	result = sys_rt_sigqueueinfo(tid, signo, &info);
	return -result;
}
/*[[[end:libc_pthread_sigqueue]]]*/


/*[[[impl:libc_signal]]]*/
/*[[[impl:libc_ssignal]]]*/
/*[[[impl:libc_gsignal]]]*/
/*[[[impl:libd_signal]]]*/
/*[[[impl:libd_ssignal]]]*/
/*[[[impl:libd_gsignal]]]*/
DEFINE_INTERN_ALIAS(libc_signal, libc_bsd_signal);
DEFINE_INTERN_ALIAS(libc_ssignal, libc_bsd_signal);
DEFINE_INTERN_ALIAS(libc_gsignal, libc_raise);
DEFINE_INTERN_ALIAS(libd_signal, libd_bsd_signal);
DEFINE_INTERN_ALIAS(libd_ssignal, libd_bsd_signal);
DEFINE_INTERN_ALIAS(libd_gsignal, libd_raise);



/*[[[start:exports,hash:CRC-32=0x35c2142d]]]*/
DEFINE_PUBLIC_ALIAS(DOS$raise, libd_raise);
DEFINE_PUBLIC_ALIAS(raise, libc_raise);
DEFINE_PUBLIC_ALIAS(DOS$__sysv_signal, libd_sysv_signal);
DEFINE_PUBLIC_ALIAS(DOS$sysv_signal, libd_sysv_signal);
DEFINE_PUBLIC_ALIAS(__sysv_signal, libc_sysv_signal);
DEFINE_PUBLIC_ALIAS(sysv_signal, libc_sysv_signal);
DEFINE_PUBLIC_ALIAS(DOS$_signal, libd_signal);
DEFINE_PUBLIC_ALIAS(DOS$signal, libd_signal);
DEFINE_PUBLIC_ALIAS(signal, libc_signal);
DEFINE_PUBLIC_ALIAS(DOS$ssignal, libd_ssignal);
DEFINE_PUBLIC_ALIAS(ssignal, libc_ssignal);
DEFINE_PUBLIC_ALIAS(DOS$gsignal, libd_gsignal);
DEFINE_PUBLIC_ALIAS(gsignal, libc_gsignal);
DEFINE_PUBLIC_ALIAS(sigblock, libc_sigblock);
DEFINE_PUBLIC_ALIAS(sigsetmask, libc_sigsetmask);
DEFINE_PUBLIC_ALIAS(siggetmask, libc_siggetmask);
DEFINE_PUBLIC_ALIAS(__p_sys_siglist, libc___p_sys_siglist);
DEFINE_PUBLIC_ALIAS(sigreturn, libc_sigreturn);
DEFINE_PUBLIC_ALIAS(DOS$bsd_signal, libd_bsd_signal);
DEFINE_PUBLIC_ALIAS(bsd_signal, libc_bsd_signal);
DEFINE_PUBLIC_ALIAS(__xpg_sigpause, libc___xpg_sigpause);
DEFINE_PUBLIC_ALIAS(kill, libc_kill);
DEFINE_PUBLIC_ALIAS(sigprocmask, libc_sigprocmask);
DEFINE_PUBLIC_ALIAS(__sigsuspend, libc_sigsuspend);
DEFINE_PUBLIC_ALIAS(sigsuspend, libc_sigsuspend);
DEFINE_PUBLIC_ALIAS(__sigaction, libc_sigaction);
DEFINE_PUBLIC_ALIAS(sigaction, libc_sigaction);
DEFINE_PUBLIC_ALIAS(sigpending, libc_sigpending);
DEFINE_PUBLIC_ALIAS(sigwait, libc_sigwait);
DEFINE_PUBLIC_ALIAS(sigwaitinfo, libc_sigwaitinfo);
DEFINE_PUBLIC_ALIAS(sigtimedwait, libc_sigtimedwait);
DEFINE_PUBLIC_ALIAS(sigqueue, libc_sigqueue);
DEFINE_PUBLIC_ALIAS(sigtimedwait64, libc_sigtimedwait64);
DEFINE_PUBLIC_ALIAS(sigqueueinfo, libc_sigqueueinfo);
DEFINE_PUBLIC_ALIAS(tgsigqueueinfo, libc_tgsigqueueinfo);
DEFINE_PUBLIC_ALIAS(killpg, libc_killpg);
DEFINE_PUBLIC_ALIAS(psignal, libc_psignal);
DEFINE_PUBLIC_ALIAS(psiginfo, libc_psiginfo);
DEFINE_PUBLIC_ALIAS(siginterrupt, libc_siginterrupt);
DEFINE_PUBLIC_ALIAS(sigstack, libc_sigstack);
DEFINE_PUBLIC_ALIAS(sigaltstack, libc_sigaltstack);
DEFINE_PUBLIC_ALIAS(sighold, libc_sighold);
DEFINE_PUBLIC_ALIAS(sigrelse, libc_sigrelse);
DEFINE_PUBLIC_ALIAS(sigignore, libc_sigignore);
DEFINE_PUBLIC_ALIAS(sigset, libc_sigset);
DEFINE_PUBLIC_ALIAS(pthread_sigmask, libc_pthread_sigmask);
DEFINE_PUBLIC_ALIAS(pthread_kill, libc_pthread_kill);
DEFINE_PUBLIC_ALIAS(pthread_sigqueue, libc_pthread_sigqueue);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SIGNAL_C */
