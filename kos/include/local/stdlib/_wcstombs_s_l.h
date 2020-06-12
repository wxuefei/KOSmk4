/* HASH CRC-32:0x8d9ca2 */
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
#ifndef __local__wcstombs_s_l_defined
#define __local__wcstombs_s_l_defined 1
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wcstombs_s from stdlib */
#ifndef __local___localdep_wcstombs_s_defined
#define __local___localdep_wcstombs_s_defined 1
#ifdef __CRT_HAVE_wcstombs_s
__CREDIRECT(__ATTR_NONNULL((1, 2, 4)),__errno_t,__NOTHROW_NCX,__localdep_wcstombs_s,(__SIZE_TYPE__ *__presult, char *__buf, __SIZE_TYPE__ __buflen, __WCHAR_TYPE__ const *__src, __SIZE_TYPE__ __maxlen),wcstombs_s,(__presult,__buf,__buflen,__src,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcstombs_s) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2, 4)),__errno_t,__NOTHROW_NCX,__localdep_wcstombs_s,(__SIZE_TYPE__ *__presult, char *__buf, __SIZE_TYPE__ __buflen, __CHAR32_TYPE__ const *__src, __SIZE_TYPE__ __maxlen),wcstombs_s,(__presult,__buf,__buflen,__src,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcstombs_s) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2, 4)),__errno_t,__NOTHROW_NCX,__localdep_wcstombs_s,(__SIZE_TYPE__ *__presult, char *__buf, __SIZE_TYPE__ __buflen, __CHAR16_TYPE__ const *__src, __SIZE_TYPE__ __maxlen),wcstombs_s,(__presult,__buf,__buflen,__src,__maxlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/stdlib/wcstombs_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcstombs_s __LIBC_LOCAL_NAME(wcstombs_s)
#endif /* !... */
#endif /* !__local___localdep_wcstombs_s_defined */
__NAMESPACE_LOCAL_END
#include <parts/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_wcstombs_s_l) __ATTR_NONNULL((1, 2, 4)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wcstombs_s_l))(__SIZE_TYPE__ *__presult, char *__buf, __SIZE_TYPE__ __buflen, __WCHAR_TYPE__ const *__src, __SIZE_TYPE__ __maxlen, __locale_t __locale) {
	(void)__locale;
	return __localdep_wcstombs_s(__presult, __buf, __buflen, __src, __maxlen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wcstombs_s_l_defined
#define __local___localdep__wcstombs_s_l_defined 1
#define __localdep__wcstombs_s_l __LIBC_LOCAL_NAME(_wcstombs_s_l)
#endif /* !__local___localdep__wcstombs_s_l_defined */
#endif /* !__local__wcstombs_s_l_defined */
