/* HASH CRC-32:0x916a0bca */
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
#ifndef __local_c32spawnl_defined
#define __local_c32spawnl_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_wspawnv) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wspawnv) || (defined(__CRT_HAVE__wspawnv) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wspawnv)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32spawnv from parts.uchar.process */
#ifndef __local___localdep_c32spawnv_defined
#define __local___localdep_c32spawnv_defined 1
#if defined(__CRT_HAVE_wspawnv) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnv,(int __mode, __CHAR32_TYPE__ const *__restrict __path, __T32ARGV),wspawnv,(__mode,__path,___argv))
#elif defined(__CRT_HAVE_KOS$wspawnv)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnv,(int __mode, __CHAR32_TYPE__ const *__restrict __path, __T32ARGV),wspawnv,(__mode,__path,___argv))
#elif defined(__CRT_HAVE__wspawnv) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnv,(int __mode, __CHAR32_TYPE__ const *__restrict __path, __T32ARGV),_wspawnv,(__mode,__path,___argv))
#elif defined(__CRT_HAVE_KOS$_wspawnv)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnv,(int __mode, __CHAR32_TYPE__ const *__restrict __path, __T32ARGV),_wspawnv,(__mode,__path,___argv))
#else /* ... */
#undef __local___localdep_c32spawnv_defined
#endif /* !... */
#endif /* !__local___localdep_c32spawnv_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32spawnl) __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t
__NOTHROW_RPC(__VLIBKCALL __LIBC_LOCAL_NAME(c32spawnl))(int __mode, __CHAR32_TYPE__ const *__restrict __path, __CHAR32_TYPE__ const *__args, ...) {
	__REDIRECT_SPAWNL(__CHAR32_TYPE__, __localdep_c32spawnv, __mode, __path, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32spawnl_defined
#define __local___localdep_c32spawnl_defined 1
#define __localdep_c32spawnl __LIBC_LOCAL_NAME(c32spawnl)
#endif /* !__local___localdep_c32spawnl_defined */
#else /* (__CRT_HAVE_wspawnv && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wspawnv || (__CRT_HAVE__wspawnv && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_wspawnv */
#undef __local_c32spawnl_defined
#endif /* (!__CRT_HAVE_wspawnv || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wspawnv && (!__CRT_HAVE__wspawnv || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_wspawnv */
#endif /* !__local_c32spawnl_defined */
