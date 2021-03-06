/* HASH CRC-32:0xcd79393d */
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
#ifndef __local_pselect_defined
#define __local_pselect_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_pselect64) || defined(__CRT_HAVE_pselect)
#include <features.h>
#include <bits/timespec.h>
#include <bits/sigset.h>
struct __fd_set_struct;
__NAMESPACE_LOCAL_BEGIN
/* Dependency: pselect32 from sys.select */
#if !defined(__local___localdep_pselect32_defined) && defined(__CRT_HAVE_pselect)
#define __local___localdep_pselect32_defined 1
__CREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_pselect32,(__STDC_INT_AS_SIZE_T __nfds, struct __fd_set_struct *__restrict __readfds, struct __fd_set_struct *__restrict __writefds, struct __fd_set_struct *__restrict __exceptfds, struct __timespec32 const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask),pselect,(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask))
#endif /* !__local___localdep_pselect32_defined && __CRT_HAVE_pselect */
/* Dependency: pselect64 from sys.select */
#ifndef __local___localdep_pselect64_defined
#define __local___localdep_pselect64_defined 1
#ifdef __CRT_HAVE_pselect64
__CREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_pselect64,(__STDC_INT_AS_SIZE_T __nfds, struct __fd_set_struct *__restrict __readfds, struct __fd_set_struct *__restrict __writefds, struct __fd_set_struct *__restrict __exceptfds, struct __timespec64 const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask),pselect64,(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask))
#elif defined(__CRT_HAVE_pselect) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_pselect64,(__STDC_INT_AS_SIZE_T __nfds, struct __fd_set_struct *__restrict __readfds, struct __fd_set_struct *__restrict __writefds, struct __fd_set_struct *__restrict __exceptfds, struct __timespec64 const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask),pselect,(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask))
#elif defined(__CRT_HAVE_pselect)
__NAMESPACE_LOCAL_END
#include <local/sys.select/pselect64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_pselect64 __LIBC_LOCAL_NAME(pselect64)
#else /* ... */
#undef __local___localdep_pselect64_defined
#endif /* !... */
#endif /* !__local___localdep_pselect64_defined */
__LOCAL_LIBC(pselect) __STDC_INT_AS_SSIZE_T
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pselect))(__STDC_INT_AS_SIZE_T __nfds, struct __fd_set_struct *__restrict __readfds, struct __fd_set_struct *__restrict __writefds, struct __fd_set_struct *__restrict __exceptfds, struct timespec const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask) {
#if defined(__CRT_HAVE_pselect64) || defined(__CRT_HAVE_pselect)
	struct __timespec64 __tmv;
	if (!__timeout)
		return __localdep_pselect64(__nfds, __readfds, __writefds, __exceptfds, __NULLPTR, __sigmask);
	__tms.tv_sec  = (__time64_t)__timeout->tv_sec;
	__tms.tv_nsec = __timeout->tv_nsec;
	return __localdep_pselect64(__nfds, __readfds, __writefds, __exceptfds, &__tms, __sigmask);
#else /* __CRT_HAVE_pselect64 || __CRT_HAVE_pselect */
	struct __timespec32 __tms;
	if (!__timeout)
		return __localdep_pselect32(__nfds, __readfds, __writefds, __exceptfds, __NULLPTR, __sigmask);
	__tms.tv_sec  = (__time32_t)__timeout->tv_sec;
	__tms.tv_nsec = __timeout->tv_nsec;
	return __localdep_pselect32(__nfds, __readfds, __writefds, __exceptfds, &__tms, __sigmask);
#endif /* !__CRT_HAVE_pselect64 && !__CRT_HAVE_pselect */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pselect_defined
#define __local___localdep_pselect_defined 1
#define __localdep_pselect __LIBC_LOCAL_NAME(pselect)
#endif /* !__local___localdep_pselect_defined */
#else /* __CRT_HAVE_pselect64 || __CRT_HAVE_pselect */
#undef __local_pselect_defined
#endif /* !__CRT_HAVE_pselect64 && !__CRT_HAVE_pselect */
#endif /* !__local_pselect_defined */
