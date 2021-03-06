/* HASH CRC-32:0xd9d10d9f */
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
#ifndef __local_wget_current_dir_name_defined
#define __local_wget_current_dir_name_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_wgetcwd) || defined(__CRT_HAVE__wgetcwd)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wgetcwd from parts.wchar.unistd */
#ifndef __local___localdep_wgetcwd_defined
#define __local___localdep_wgetcwd_defined 1
#ifdef __CRT_HAVE_wgetcwd
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT(,__WCHAR_TYPE__ *,__NOTHROW_RPC,__localdep_wgetcwd,(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE__wgetcwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT(,__WCHAR_TYPE__ *,__NOTHROW_RPC,__localdep_wgetcwd,(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),_wgetcwd,(__buf,__bufsize))
#else /* ... */
#undef __local___localdep_wgetcwd_defined
#endif /* !... */
#endif /* !__local___localdep_wgetcwd_defined */
__LOCAL_LIBC(wget_current_dir_name) __ATTR_MALLOC __ATTR_WUNUSED __WCHAR_TYPE__ *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wget_current_dir_name))(void) {
	return __localdep_wgetcwd(__NULLPTR, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wget_current_dir_name_defined
#define __local___localdep_wget_current_dir_name_defined 1
#define __localdep_wget_current_dir_name __LIBC_LOCAL_NAME(wget_current_dir_name)
#endif /* !__local___localdep_wget_current_dir_name_defined */
#else /* __CRT_HAVE_wgetcwd || __CRT_HAVE__wgetcwd */
#undef __local_wget_current_dir_name_defined
#endif /* !__CRT_HAVE_wgetcwd && !__CRT_HAVE__wgetcwd */
#endif /* !__local_wget_current_dir_name_defined */
