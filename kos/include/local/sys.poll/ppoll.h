/* HASH CRC-32:0x47369eaa */
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
#ifndef __local_ppoll_defined
#if defined(__CRT_HAVE_ppoll) || defined(__CRT_HAVE_ppoll64)
#define __local_ppoll_defined 1
#include <__crt.h>
/* Dependency: "ppoll32" from "sys.poll" */
#ifndef ____localdep_ppoll32_defined
#define ____localdep_ppoll32_defined 1
#ifdef __CRT_HAVE_ppoll
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_ppoll32,(struct pollfd *__fds, __UINTPTR_TYPE__ __nfds, struct __timespec32 const *__timeout, struct __sigset_struct const *__ss),ppoll,(__fds,__nfds,__timeout,__ss))
#else /* LIBC: ppoll */
#undef ____localdep_ppoll32_defined
#endif /* ppoll32... */
#endif /* !____localdep_ppoll32_defined */

/* Dependency: "ppoll64" from "sys.poll" */
#ifndef ____localdep_ppoll64_defined
#define ____localdep_ppoll64_defined 1
#ifdef __CRT_HAVE_ppoll64
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_ppoll64,(struct pollfd *__fds, __UINTPTR_TYPE__ __nfds, struct __timespec64 const *__timeout, struct __sigset_struct const *__ss),ppoll64,(__fds,__nfds,__timeout,__ss))
#elif defined(__CRT_HAVE_ppoll) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_ppoll64,(struct pollfd *__fds, __UINTPTR_TYPE__ __nfds, struct __timespec64 const *__timeout, struct __sigset_struct const *__ss),ppoll,(__fds,__nfds,__timeout,__ss))
#elif defined(__CRT_HAVE_ppoll)
#include <local/sys.poll/ppoll64.h>
#define __localdep_ppoll64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ppoll64))
#else /* CUSTOM: ppoll64 */
#undef ____localdep_ppoll64_defined
#endif /* ppoll64... */
#endif /* !____localdep_ppoll64_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ppoll) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(ppoll))(struct pollfd *__fds,
                                                   __UINTPTR_TYPE__ __nfds,
                                                   struct timespec const *__timeout,
                                                   struct __sigset_struct const *__ss) {
#line 93 "kos/src/libc/magic/sys.poll.c"
#ifdef __CRT_HAVE_ppoll
	struct __timespec32 __tmo32;
	if (!__timeout)
		return __localdep_ppoll32(__fds, __nfds, __NULLPTR, __ss);
	__tmo32.tv_sec  = (__time32_t)__timeout->tv_sec;
	__tmo32.tv_nsec = __timeout->tv_nsec;
	return __localdep_ppoll32(__fds, __nfds, &__tmo32, __ss);
#else /* __CRT_HAVE_ppoll */
	struct __timespec64 __tmo64;
	if (!__timeout)
		return __localdep_ppoll64(__fds, __nfds, __NULLPTR, __ss);
	__tmo64.tv_sec  = (__time64_t)__timeout->tv_sec;
	__tmo64.tv_nsec = __timeout->tv_nsec;
	return __localdep_ppoll64(__fds, __nfds, &__tmo64, __ss);
#endif /* !__CRT_HAVE_ppoll */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_ppoll || __CRT_HAVE_ppoll64 */
#endif /* !__local_ppoll_defined */
