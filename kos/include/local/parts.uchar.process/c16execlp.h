/* HASH CRC-32:0xa60d43bb */
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
#ifndef __local_c16execlp_defined
#define __local_c16execlp_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_wexecvp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wexecvp) || (defined(__CRT_HAVE__wexecvp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wexecvp)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c16execvp from parts.uchar.process */
#ifndef __local___localdep_c16execvp_defined
#define __local___localdep_c16execvp_defined 1
#if defined(__CRT_HAVE_wexecvp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_c16execvp,(__CHAR16_TYPE__ const *__restrict __file, __T16ARGV),wexecvp,(__path,___argv))
#elif defined(__CRT_HAVE_DOS$wexecvp)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_c16execvp,(__CHAR16_TYPE__ const *__restrict __file, __T16ARGV),wexecvp,(__path,___argv))
#elif defined(__CRT_HAVE__wexecvp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_c16execvp,(__CHAR16_TYPE__ const *__restrict __file, __T16ARGV),_wexecvp,(__path,___argv))
#elif defined(__CRT_HAVE_DOS$_wexecvp)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_c16execvp,(__CHAR16_TYPE__ const *__restrict __file, __T16ARGV),_wexecvp,(__path,___argv))
#else /* ... */
#undef __local___localdep_c16execvp_defined
#endif /* !... */
#endif /* !__local___localdep_c16execvp_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16execlp) __ATTR_SENTINEL __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__VLIBDCALL __LIBC_LOCAL_NAME(c16execlp))(__CHAR16_TYPE__ const *__restrict __file, __CHAR16_TYPE__ const *__args, ...) {
	__REDIRECT_EXECL(__CHAR16_TYPE__, __localdep_c16execvp, __file, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16execlp_defined
#define __local___localdep_c16execlp_defined 1
#define __localdep_c16execlp __LIBC_LOCAL_NAME(c16execlp)
#endif /* !__local___localdep_c16execlp_defined */
#else /* (__CRT_HAVE_wexecvp && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wexecvp || (__CRT_HAVE__wexecvp && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$_wexecvp */
#undef __local_c16execlp_defined
#endif /* (!__CRT_HAVE_wexecvp || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wexecvp && (!__CRT_HAVE__wexecvp || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$_wexecvp */
#endif /* !__local_c16execlp_defined */
