/* HASH CRC-32:0x563217b2 */
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
#ifndef __local_fopendirat_defined
#define __local_fopendirat_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))
struct __dirstream;
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: close from unistd */
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined 1
#ifdef __CRT_HAVE_close
/* >> close(2)
 * Close a file handle */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
/* >> close(2)
 * Close a file handle */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
/* >> close(2)
 * Close a file handle */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#else /* ... */
#undef __local___localdep_close_defined
#endif /* !... */
#endif /* !__local___localdep_close_defined */
/* Dependency: fdopendir from dirent */
#ifndef __local___localdep_fdopendir_defined
#define __local___localdep_fdopendir_defined 1
/* Create a new directory stream by inheriting the given `FD' as stream handle */
__CREDIRECT(__ATTR_WUNUSED,struct __dirstream *,__NOTHROW_NCX,__localdep_fdopendir,(__fd_t __fd),fdopendir,(__fd))
#endif /* !__local___localdep_fdopendir_defined */
/* Dependency: openat from fcntl */
#ifndef __local___localdep_openat_defined
#define __local___localdep_openat_defined 1
#if defined(__CRT_HAVE_openat64) && defined(__USE_FILE_OFFSET64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__fd_t,__NOTHROW_RPC,__localdep_openat,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),openat64,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_openat) && !defined(__USE_FILE_OFFSET64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__fd_t,__NOTHROW_RPC,__localdep_openat,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),openat,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)
__NAMESPACE_LOCAL_END
#include <local/fcntl/openat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_openat __LIBC_LOCAL_NAME(openat)
#else /* ... */
#undef __local___localdep_openat_defined
#endif /* !... */
#endif /* !__local___localdep_openat_defined */
/* Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
__LOCAL_LIBC(fopendirat) __ATTR_WUNUSED __ATTR_NONNULL((2)) struct __dirstream *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(fopendirat))(__fd_t __dirfd, char const *__name, __oflag_t __oflags) {
	struct __dirstream *__result;
	__fd_t __fd = __localdep_openat(__dirfd, __name, __oflags);
	if __unlikely(__fd < 0)
		return __NULLPTR;
	__result = __localdep_fdopendir(__fd);
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)
	if __unlikely(!__result)
		__localdep_close(__fd);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fopendirat_defined
#define __local___localdep_fopendirat_defined 1
#define __localdep_fopendirat __LIBC_LOCAL_NAME(fopendirat)
#endif /* !__local___localdep_fopendirat_defined */
#else /* __CRT_HAVE_fdopendir && (__CRT_HAVE_openat64 || __CRT_HAVE_openat) */
#undef __local_fopendirat_defined
#endif /* !__CRT_HAVE_fdopendir || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat) */
#endif /* !__local_fopendirat_defined */
