/* HASH CRC-32:0xa90f1966 */
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
#ifndef __local_pathconf_defined
#define __local_pathconf_defined 1
#include <__crt.h>
#include <asm/fcntl.h>
#if defined(__CRT_HAVE_fpathconf) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && defined(__O_RDONLY)
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: close from unistd */
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined 1
#ifdef __CRT_HAVE_close
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> close(2)
 * Close a file handle */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> close(2)
 * Close a file handle */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> close(2)
 * Close a file handle */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#else /* ... */
#undef __local___localdep_close_defined
#endif /* !... */
#endif /* !__local___localdep_close_defined */
/* Dependency: fpathconf from unistd */
#ifndef __local___localdep_fpathconf_defined
#define __local___localdep_fpathconf_defined 1
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> fpathconf(2)
 * @param: NAME: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `NAME' for `FD'
 * return: * : The configuration limit associated with `NAME' for `FD'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `FD'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CREDIRECT(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,__localdep_fpathconf,(__fd_t __fd, __STDC_INT_AS_UINT_T __name),fpathconf,(__fd,__name))
#endif /* !__local___localdep_fpathconf_defined */
/* Dependency: open from fcntl */
#ifndef __local___localdep_open_defined
#define __local___localdep_open_defined 1
#if defined(__CRT_HAVE_open64) && defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open) && !defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
__NAMESPACE_LOCAL_END
#include <local/fcntl/open.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_open __LIBC_LOCAL_NAME(open)
#else /* ... */
#undef __local___localdep_open_defined
#endif /* !... */
#endif /* !__local___localdep_open_defined */
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__LOCAL_LIBC(pathconf) __ATTR_NONNULL((1)) __LONGPTR_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pathconf))(char const *__path, __STDC_INT_AS_UINT_T __name) {
	__fd_t __fd;
	__LONGPTR_TYPE__ __result;
	__fd = __localdep_open(__path, __O_RDONLY);
	if __unlikely(__fd < 0)
		return -1;
	__result = __localdep_fpathconf(__fd, __name);
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)
	__localdep_close(__fd);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pathconf_defined
#define __local___localdep_pathconf_defined 1
#define __localdep_pathconf __LIBC_LOCAL_NAME(pathconf)
#endif /* !__local___localdep_pathconf_defined */
#else /* __CRT_HAVE_fpathconf && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__CRT_AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && __O_RDONLY */
#undef __local_pathconf_defined
#endif /* !__CRT_HAVE_fpathconf || (!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && (!__CRT_AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || !__O_RDONLY */
#endif /* !__local_pathconf_defined */
