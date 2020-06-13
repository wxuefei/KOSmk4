/* HASH CRC-32:0xc376dde1 */
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
#ifndef __local_c32stold_l_defined
#define __local_c32stold_l_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32stold from parts.uchar.wchar */
#ifndef __local___localdep_c32stold_defined
#define __local___localdep_c32stold_defined 1
#if defined(__CRT_HAVE_wcstold) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,__localdep_c32stold,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr),wcstold,(__nptr,__endptr))
#elif defined(__CRT_HAVE_DOS$wcstold)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,__localdep_c32stold,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr),wcstold,(__nptr,__endptr))
#elif (__SIZEOF_WCHAR_T__ == 4)
__NAMESPACE_LOCAL_END
#include <local/wchar/wcstold.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32stold (*(__LONGDOUBLE(__LIBKCALL *)(__CHAR32_TYPE__ const *__restrict, __CHAR32_TYPE__ **))&__LIBC_LOCAL_NAME(wcstold))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.wchar/c32stold.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32stold __LIBC_LOCAL_NAME(c32stold)
#endif /* !... */
#endif /* !__local___localdep_c32stold_defined */
__LOCAL_LIBC(c32stold_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __LONGDOUBLE
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32stold_l))(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __locale_t __locale) {
	(void)__locale;
	return __localdep_c32stold(__nptr, __endptr);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32stold_l_defined
#define __local___localdep_c32stold_l_defined 1
#define __localdep_c32stold_l __LIBC_LOCAL_NAME(c32stold_l)
#endif /* !__local___localdep_c32stold_l_defined */
#endif /* !__local_c32stold_l_defined */