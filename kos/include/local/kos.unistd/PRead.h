/* HASH CRC-32:0xf039e85 */
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
#ifndef __local_PRead_defined
#define __local_PRead_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_PRead64) || defined(__CRT_HAVE_PRead)
#include <kos/anno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: PRead32 from kos.unistd */
#if !defined(__local___localdep_PRead32_defined) && defined(__CRT_HAVE_PRead)
#define __local___localdep_PRead32_defined 1
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__THROWING,__localdep_PRead32,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __pos32_t __offset),PRead,(__fd,__buf,__bufsize,__offset))
#endif /* !__local___localdep_PRead32_defined && __CRT_HAVE_PRead */
/* Dependency: PRead64 from kos.unistd */
#ifndef __local___localdep_PRead64_defined
#define __local___localdep_PRead64_defined 1
#ifdef __CRT_HAVE_PRead64
/* >> pread64(2)
 * Read data from a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__THROWING,__localdep_PRead64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __pos64_t __offset),PRead64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PRead) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> pread64(2)
 * Read data from a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__THROWING,__localdep_PRead64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __pos64_t __offset),PRead,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PRead)
__NAMESPACE_LOCAL_END
#include <local/kos.unistd/PRead64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> pread64(2)
 * Read data from a file at a specific offset */
#define __localdep_PRead64 __LIBC_LOCAL_NAME(PRead64)
#else /* ... */
#undef __local___localdep_PRead64_defined
#endif /* !... */
#endif /* !__local___localdep_PRead64_defined */
/* >> pread(2)
 * Read data from a file at a specific offset */
__LOCAL_LIBC(PRead) __ATTR_NONNULL((2)) __SIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(PRead))(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __FS_TYPE(pos) __offset) __THROWS(...) {
#ifdef __CRT_HAVE_PRead
	return __localdep_PRead32(__fd, __buf, __bufsize, (__pos32_t)__offset);
#else /* __CRT_HAVE_PRead */
	return __localdep_PRead64(__fd, __buf, __bufsize, (__pos64_t)__offset);
#endif /* !__CRT_HAVE_PRead */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_PRead_defined
#define __local___localdep_PRead_defined 1
#define __localdep_PRead __LIBC_LOCAL_NAME(PRead)
#endif /* !__local___localdep_PRead_defined */
#else /* __CRT_HAVE_PRead64 || __CRT_HAVE_PRead */
#undef __local_PRead_defined
#endif /* !__CRT_HAVE_PRead64 && !__CRT_HAVE_PRead */
#endif /* !__local_PRead_defined */
