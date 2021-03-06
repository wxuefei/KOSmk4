/* HASH CRC-32:0xe95aab92 */
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
#ifndef __local_c32spawnlp_defined
#define __local_c32spawnlp_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_wspawnvp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wspawnvp) || (defined(__CRT_HAVE__wspawnvp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wspawnvp)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32spawnvp from parts.uchar.process */
#ifndef __local___localdep_c32spawnvp_defined
#define __local___localdep_c32spawnvp_defined 1
#if defined(__CRT_HAVE_wspawnvp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnvp,(int __mode, __CHAR32_TYPE__ const *__restrict __file, __T32ARGV),wspawnvp,(__mode,__file,___argv))
#elif defined(__CRT_HAVE_KOS$wspawnvp)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnvp,(int __mode, __CHAR32_TYPE__ const *__restrict __file, __T32ARGV),wspawnvp,(__mode,__file,___argv))
#elif defined(__CRT_HAVE__wspawnvp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnvp,(int __mode, __CHAR32_TYPE__ const *__restrict __file, __T32ARGV),_wspawnvp,(__mode,__file,___argv))
#elif defined(__CRT_HAVE_KOS$_wspawnvp)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnvp,(int __mode, __CHAR32_TYPE__ const *__restrict __file, __T32ARGV),_wspawnvp,(__mode,__file,___argv))
#else /* ... */
#undef __local___localdep_c32spawnvp_defined
#endif /* !... */
#endif /* !__local___localdep_c32spawnvp_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32spawnlp) __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t
__NOTHROW_RPC(__VLIBKCALL __LIBC_LOCAL_NAME(c32spawnlp))(int __mode, __CHAR32_TYPE__ const *__restrict __file, __CHAR32_TYPE__ const *__args, ...) {
	__REDIRECT_SPAWNL(__CHAR32_TYPE__, __localdep_c32spawnvp, __mode, __file, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32spawnlp_defined
#define __local___localdep_c32spawnlp_defined 1
#define __localdep_c32spawnlp __LIBC_LOCAL_NAME(c32spawnlp)
#endif /* !__local___localdep_c32spawnlp_defined */
#else /* (__CRT_HAVE_wspawnvp && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wspawnvp || (__CRT_HAVE__wspawnvp && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_wspawnvp */
#undef __local_c32spawnlp_defined
#endif /* (!__CRT_HAVE_wspawnvp || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wspawnvp && (!__CRT_HAVE__wspawnvp || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_wspawnvp */
#endif /* !__local_c32spawnlp_defined */
