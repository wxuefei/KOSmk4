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

%[define_replacement(pid_t = __pid_t)]
%[define_replacement(rusage32 = __rusage32)]
%[define_replacement(rusage64 = __rusage64)]
%[define_replacement(idtype_t = int)]
%[default:section(".text.crt{|.dos}.sched.wait")]

%{
#include <features.h>

#include <asm/wait.h>
#include <bits/types.h>
#include <parts/waitmacros.h>

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#include <bits/siginfo-struct.h> /* `struct __siginfo_struct' */
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */

__SYSDECL_BEGIN

#ifdef __USE_MISC
#ifdef __WCOREFLAG
#define WCOREFLAG __WCOREFLAG
#endif /* __WCOREFLAG */
#ifdef __WCOREDUMP
#define WCOREDUMP(status) __WCOREDUMP(__WAIT_INT(status))
#endif /* __WCOREDUMP */
#ifdef __W_EXITCODE
#define W_EXITCODE(ret, sig) __W_EXITCODE(ret, sig)
#endif /* __W_EXITCODE */
#ifdef __W_STOPCODE
#define W_STOPCODE(sig) __W_STOPCODE(sig)
#endif /* __W_STOPCODE */

#ifdef __WAIT_ANY
#define WAIT_ANY __WAIT_ANY /* Any process. */
#endif /* __WAIT_ANY */
#ifdef __WAIT_MYPGRP
#define WAIT_MYPGRP __WAIT_MYPGRP /* Any process in my process group. */
#endif /* __WAIT_MYPGRP */
#endif /* __USE_MISC */


#ifdef __CC__

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#ifndef __siginfo_t_defined
#define __siginfo_t_defined 1
typedef struct __siginfo_struct siginfo_t;
#endif /* !__siginfo_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */

}


@@Wait for any child process (same as `waitpid(-1, STAT_LOC, 0);')
[[cp, export_alias("__wait"), decl_include("<bits/types.h>", "<parts/waitmacros.h>")]]
$pid_t wait([[nullable]] __WAIT_STATUS stat_loc);

@@Wait for a child process:
@@ - `pid < -1':  Wait for any child process whose process group ID is `-PID'
@@ - `pid == -1': Wait for any child process
@@ - `pid == 0':  Wait for any child process whose process group ID is that of the caller
@@ - `pid > 0':   Wait for the child whose process ID is equal to `PID'
@@@param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted)
[[decl_include("<bits/types.h>", "<features.h>", "<parts/waitmacros.h>")]]
[[cp, export_alias("__waitpid")]]
$pid_t waitpid($pid_t pid, [[nullable]] __WAIT_STATUS stat_loc,
               __STDC_INT_AS_UINT_T options);

%
%#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
%#ifndef __id_t_defined
%#define __id_t_defined 1
%typedef __id_t id_t;
%#endif /* !__id_t_defined */
@@@param options: At least one of `WEXITED | WSTOPPED | WCONTINUED',
@@                optionally or'd with `WNOHANG | WNOWAIT'
[[cp, decl_include("<features.h>")]]
int waitid(idtype_t idtype, id_t id,
           [[nullable]] siginfo_t *infop,
           __STDC_INT_AS_UINT_T options);
%#endif /* __USE_XOPEN || __USE_XOPEN2K8 */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
%struct rusage;

[[decl_include("<bits/types.h>", "<features.h>")]]
[[decl_include("<bits/rusage-struct.h>", "<parts/waitmacros.h>")]]
[[cp, doc_alias("wait3"), ignore, nocrt, alias("wait3")]]
$pid_t wait3_32([[nullable]] __WAIT_STATUS stat_loc,
                __STDC_INT_AS_UINT_T options,
                [[nullable]] struct $rusage32 *usage);

@@Same as `waitpid(-1, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
@@@param options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted)
[[cp, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("wait3_64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("wait3")]]
[[userimpl, requires($has_function(wait3_32) || $has_function(wait3_64))]]
[[decl_include("<bits/types.h>", "<features.h>")]]
[[decl_include("<bits/rusage-struct.h>", "<parts/waitmacros.h>")]]
[[impl_include("<bits/rusage-convert.h>")]]
$pid_t wait3([[nullable]] __WAIT_STATUS stat_loc,
             __STDC_INT_AS_UINT_T options,
             [[nullable]] struct rusage *usage) {
	pid_t result;
@@pp_if $has_function(wait3_32)@@
	struct rusage32 ru32;
	result = wait3_32(stat_loc, options, usage ? &ru32 : NULL);
	if (result >= 0 && usage)
		@rusage32_to_rusage@(&ru32, usage);
@@pp_else@@
	struct __rusage64 ru64;
	result = wait3_64(stat_loc, options, usage ? &ru64 : NULL);
	if (result >= 0 && usage)
		@rusage64_to_rusage@(&ru64, usage);
@@pp_endif@@
	return result;
}

%#ifdef __USE_TIME64
%struct rusage64;
[[decl_include("<bits/types.h>", "<features.h>")]]
[[decl_include("<bits/rusage-struct.h>", "<parts/waitmacros.h>")]]
[[impl_include("<bits/rusage-struct.h>", "<bits/rusage-convert.h>", "<parts/waitmacros.h>")]]
[[doc_alias("wait3"), time64_variant_of(wait3)]]
[[userimpl, requires_function(wait3_32)]]
$pid_t wait3_64([[nullable]] __WAIT_STATUS stat_loc,
                __STDC_INT_AS_UINT_T options,
                [[nullable]] struct rusage64 *usage) {
	pid_t result;
	struct rusage32 ru32;
	result = wait3_32(stat_loc, options, usage ? &ru32 : NULL);
	if (result >= 0 && usage)
		@rusage32_to_rusage64@(&ru32, usage);
	return result;
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%
%#ifdef __USE_MISC

[[decl_include("<bits/types.h>", "<features.h>")]]
[[decl_include("<bits/rusage-struct.h>", "<parts/waitmacros.h>")]]
[[cp, doc_alias("wait4"), ignore, nocrt, alias("wait4")]]
$pid_t wait4_32($pid_t pid, [[nullable]] __WAIT_STATUS stat_loc,
                __STDC_INT_AS_UINT_T options,
                [[nullable]] struct $rusage32 *usage);

@@Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
@@@param options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted)
[[cp, decl_prefix(struct rusage;)]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("wait4_64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("wait4")]]
[[decl_include("<bits/types.h>", "<features.h>")]]
[[decl_include("<bits/rusage-struct.h>", "<parts/waitmacros.h>")]]
[[impl_include("<bits/rusage-convert.h>")]]
[[userimpl, requires($has_function(wait4_32) || $has_function(wait4_64))]]
$pid_t wait4($pid_t pid, [[nullable]] __WAIT_STATUS stat_loc,
             __STDC_INT_AS_UINT_T options,
             [[nullable]] struct rusage *usage) {
	pid_t result;
@@pp_if $has_function(wait4_32)@@
	struct rusage32 ru32;
	result = wait4_32(pid, stat_loc, options, usage ? &ru32 : NULL);
	if (result >= 0 && usage)
		@rusage32_to_rusage@(&ru32, usage);
@@pp_else@@
	struct __rusage64 ru64;
	result = wait4_64(pid, stat_loc, options, usage ? &ru64 : NULL);
	if (result >= 0 && usage)
		@rusage64_to_rusage@(&ru64, usage);
@@pp_endif@@
	return result;
}

%#ifdef __USE_TIME64
%struct rusage64;
[[doc_alias("wait4"), time64_variant_of(wait4), decl_prefix(struct rusage64;)]]
[[decl_include("<bits/types.h>", "<features.h>")]]
[[decl_include("<bits/rusage-struct.h>", "<parts/waitmacros.h>")]]
[[impl_include("<bits/rusage-convert.h>")]]
[[userimpl, requires_function(wait4_32)]]
$pid_t wait4_64($pid_t pid, [[nullable]] __WAIT_STATUS stat_loc,
                __STDC_INT_AS_UINT_T options,
                [[nullable]] struct rusage64 *usage) {
	pid_t result;
	struct rusage32 ru32;
	result = wait4_32(pid, stat_loc, options, usage ? &ru32 : NULL);
	if (result >= 0 && usage)
		@rusage32_to_rusage64@(&ru32, usage);
	return result;
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_MISC */

%
%#ifdef __USE_KOS
@@>> detach(2)
@@Detach the descriptor of `PID' from the thread that
@@would have received a signal when it changes state,
@@as well as prevent the thread from turning into a
@@zombie once it dies.
@@For simplicity, think of it like this:
@@  - pthread_create()  -->  clone()
@@  - pthread_join()    -->  wait()
@@  - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
@@A total of 4 special cases exists to alter the behavior of this function:
@@  - PID == 0 || PID == gettid():
@@    Detach the calling thread from the set of running children within
@@    its own process. Note however that when this is done by the main
@@    thread of the process, gettid() will equal getpid(), and the behavior
@@    will be different.
@@  - PID == getpid():
@@    Detach the calling process from its parent, essentially daemonizing
@@    the calling process the same way a double-fork would:
@@    >> if (fork() == 0) {
@@    >> 	if (fork() == 0) {
@@    >> 		// This is a daemonized process
@@    >> 		// aka. the parent process no longer knows
@@    >> 		// about us, and also can't wait(2) on us.
@@    >> 		...
@@    >> 	}
@@    >> 	exit(0);
@@    >> }
@@    Same as:
@@    >> if (fork() == 0) {
@@    >> 	detach(0); // or `detach(getpid())', since 0 --> gettid() and gettid() == getpid()
@@    >> 	// This is a daemonized process
@@    >> 	// aka. the parent process no longer knows
@@    >> 	// about us, and also can't wait(2) on us.
@@    >> 	...
@@    >> }
@@  - PID == -1:
@@    Detach all child processes/threads of the calling process, essentially
@@    turning its chain of children into a clean slate that no longer contains
@@    any wait(2)able child threads or processes.
@@    If no waitable children existed, `ECHILD' is set; else `0' is returned.
@@Before any of this is done, the thread referred to by `PID' is one of the following:
@@  - The leader of the process that called `fork()' or `clone()' without
@@   `CLONE_PARENT' to create the thread referred to by `PID'
@@  - The creator of the process containing a thread that called
@@   `clone()' with `CLONE_PARENT', which then created the thread
@@    referred to by `PID'.
@@  - Even if the thread doesn't deliver a signal upon it terminating,
@@    the process that would have received such a signal is still relevant.
@@  -> In other words: The thread `PID' must be one of your children,
@@                     or you had to have been assigned as its child.
@@If the calling thread isn't part of that process that will receive
@@the signal if the thread dies without being detached first, then
@@the call fails by throwing an `E_ILLEGAL_OPERATION'.
@@If the thread had already been detached, then the call fails by
@@throwing an `E_ILLEGAL_OPERATION' as well.
@@Upon success, the thread referred to by `PID' will clean up its own
@@PID descriptor without the need of anyone to wait() for it, a behavior
@@that linux implements using `CLONE_THREAD' (which you shouldn't use,
@@because it's flawed by design)
@@Once detached, any further use of PID results in a race condition
@@(which linux neglects to mention for `CLONE_THREAD'), because there
@@is no way of ensuring that PID still refers to the original thread,
@@as another thread may have been created using the same PID, after
@@the detached thread exited.
@@NOTE: If a thread is created using clone() with `CLONE_DETACHED' set,
@@      it will behave effectively as though this function had already
@@      be called.
@@NOTE: If the thread already has terminated, detaching it will kill
@@      its zombie the same way wait() would.
@@NOTE: Passing ZERO(0) for `PID' will detach the calling thread.
@@      However, this operation fails if the calling thread isn't
@@      part of the same process as the parent process of the thread.
@@      In other words, the child of a fork() can't do this, and
@@      neither can the spawnee of clone(CLONE_THREAD|CLONE_PARENT),
@@      clone(0) or clone(CLONE_PARENT).
@@@errno: EPERM:               The calling process isn't the recipient of signals
@@                             delivered when `PID' changes state. This can either
@@                             be because `PID' has already been detached, or because
@@                             YOU CAN'T DETACH SOMEONE ELSE'S THREAD!
@@                             Another possibility is that the thread was already
@@                             detached, then exited, following which a new thread
@@                             got created and had been assigned the PID of your
@@                             ancient, no longer existent thread.
@@@errno: ECHILD:             `PID' was equal to `-1', but no waitable children existed
@@@throw: E_PROCESS_EXITED:    The process referred to by `PID' doesn't exist.
@@                             This could mean that it had already been detached
@@                             and exited, or that the `PID' is just invalid (which
@@                             would also be the case if it was valid at some point)
[[decl_include("<bits/types.h>")]]
int detach($pid_t pid);
%#endif /* __USE_KOS */

%{

#endif /* __CC__ */

__SYSDECL_END

}