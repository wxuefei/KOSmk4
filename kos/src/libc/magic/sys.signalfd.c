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

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.sched.signalfd")]

%{
#include <features.h>

#include <asm/signalfd.h>
#include <bits/signalfd_siginfo.h>
#include <bits/sigset.h> /* struct __sigset_struct */
#include <bits/types.h>

#ifdef __USE_GLIBC
#include <stdint.h>
#endif /* __USE_GLIBC */

__SYSDECL_BEGIN

/* Flags for signalfd. */
#if (defined(__SFD_NONBLOCK) || defined(__SFD_CLOEXEC) || \
     defined(__SFD_CLOFORK))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __SFD_NONBLOCK
	SFD_NONBLOCK = __SFD_NONBLOCK, /* Do not block when trying to read data that hasn't been written, yet. */
#endif /* __SFD_NONBLOCK */
#ifdef __SFD_CLOEXEC
	SFD_CLOEXEC  = __SFD_CLOEXEC,  /* Close the file during exec() */
#endif /* __SFD_CLOEXEC */
#ifdef __SFD_CLOFORK
	SFD_CLOFORK  = __SFD_CLOFORK,  /* Close the handle when the file descriptors are unshared (s.a. `CLONE_FILES') */
#endif /* __SFD_CLOFORK */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __SFD_NONBLOCK
#define SFD_NONBLOCK SFD_NONBLOCK /* Do not block when trying to read data that hasn't been written, yet. */
#endif /* __SFD_NONBLOCK */
#ifdef __SFD_CLOEXEC
#define SFD_CLOEXEC  SFD_CLOEXEC  /* Close the file during exec() */
#endif /* __SFD_CLOEXEC */
#ifdef __SFD_CLOFORK
#define SFD_CLOFORK  SFD_CLOFORK  /* Close the handle when the file descriptors are unshared (s.a. `CLONE_FILES') */
#endif /* __SFD_CLOFORK */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __SFD_NONBLOCK
#define SFD_NONBLOCK __SFD_NONBLOCK /* Do not block when trying to read data that hasn't been written, yet. */
#endif /* __SFD_NONBLOCK */
#ifdef __SFD_CLOEXEC
#define SFD_CLOEXEC  __SFD_CLOEXEC  /* Close the file during exec() */
#endif /* __SFD_CLOEXEC */
#ifdef __SFD_CLOFORK
#define SFD_CLOFORK  __SFD_CLOFORK  /* Close the handle when the file descriptors are unshared (s.a. `CLONE_FILES') */
#endif /* __SFD_CLOFORK */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __SFD_NONBLOCK || __SFD_CLOEXEC || __SFD_CLOFORK */


#ifdef __CC__

#ifndef __sigset_t_defined
#define __sigset_t_defined 1
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

}

@@Request notification for delivery of signals in MASK to be performed using descriptor FD
[[decl_include("<features.h>", "<bits/sigset.h>")]]
$fd_t signalfd($fd_t fd, [[nonnull]] sigset_t const *mask,
               __STDC_INT_AS_UINT_T flags);

%{
#endif /* __CC__ */

__SYSDECL_END

}