/* HASH CRC-32:0xea64c094 */
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
#ifndef __local__wsearchenv_defined
#define __local__wsearchenv_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE__wsearchenv_s
__NAMESPACE_LOCAL_BEGIN
/* Dependency: _wsearchenv_s from stdlib */
#ifndef __local___localdep__wsearchenv_s_defined
#define __local___localdep__wsearchenv_s_defined 1
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_RPC,__localdep__wsearchenv_s,(__WCHAR_TYPE__ const *__file, __WCHAR_TYPE__ const *__envvar, __WCHAR_TYPE__ *__restrict __resultpath, __SIZE_TYPE__ __buflen),_wsearchenv_s,(__file,__envvar,__resultpath,__buflen))
#endif /* !__local___localdep__wsearchenv_s_defined */
__LOCAL_LIBC(_wsearchenv) __ATTR_NONNULL((1, 2, 3)) void
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_wsearchenv))(__WCHAR_TYPE__ const *__file, __WCHAR_TYPE__ const *__envvar, __WCHAR_TYPE__ *__restrict __resultpath) {
	__localdep__wsearchenv_s(__file, __envvar, __resultpath, (__SIZE_TYPE__)-1);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wsearchenv_defined
#define __local___localdep__wsearchenv_defined 1
#define __localdep__wsearchenv __LIBC_LOCAL_NAME(_wsearchenv)
#endif /* !__local___localdep__wsearchenv_defined */
#else /* __CRT_HAVE__wsearchenv_s */
#undef __local__wsearchenv_defined
#endif /* !__CRT_HAVE__wsearchenv_s */
#endif /* !__local__wsearchenv_defined */
