/* HASH CRC-32:0x81278e72 */
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
#ifndef __local_c32execlpe_defined
#define __local_c32execlpe_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_wexecvpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wexecvpe) || (defined(__CRT_HAVE__wexecvpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wexecvpe)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32execvpe from parts.uchar.process */
#ifndef __local___localdep_c32execvpe_defined
#define __local___localdep_c32execvpe_defined 1
#if defined(__CRT_HAVE_wexecvpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c32execvpe,(__CHAR32_TYPE__ const *__restrict __file, __T32ARGV, __T32ENVP),wexecvpe,(__path,___argv,___envp))
#elif defined(__CRT_HAVE_KOS$wexecvpe)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c32execvpe,(__CHAR32_TYPE__ const *__restrict __file, __T32ARGV, __T32ENVP),wexecvpe,(__path,___argv,___envp))
#elif defined(__CRT_HAVE__wexecvpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c32execvpe,(__CHAR32_TYPE__ const *__restrict __file, __T32ARGV, __T32ENVP),_wexecvpe,(__path,___argv,___envp))
#elif defined(__CRT_HAVE_KOS$_wexecvpe)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c32execvpe,(__CHAR32_TYPE__ const *__restrict __file, __T32ARGV, __T32ENVP),_wexecvpe,(__path,___argv,___envp))
#else /* ... */
#undef __local___localdep_c32execvpe_defined
#endif /* !... */
#endif /* !__local___localdep_c32execvpe_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32execlpe) __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__VLIBKCALL __LIBC_LOCAL_NAME(c32execlpe))(__CHAR32_TYPE__ const *__restrict __file, __CHAR32_TYPE__ const *__args, ...) {
	__REDIRECT_EXECLE(__CHAR32_TYPE__, __localdep_c32execvpe, __file, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32execlpe_defined
#define __local___localdep_c32execlpe_defined 1
#define __localdep_c32execlpe __LIBC_LOCAL_NAME(c32execlpe)
#endif /* !__local___localdep_c32execlpe_defined */
#else /* (__CRT_HAVE_wexecvpe && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wexecvpe || (__CRT_HAVE__wexecvpe && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_wexecvpe */
#undef __local_c32execlpe_defined
#endif /* (!__CRT_HAVE_wexecvpe || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wexecvpe && (!__CRT_HAVE__wexecvpe || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_wexecvpe */
#endif /* !__local_c32execlpe_defined */
