/* HASH CRC-32:0x80744a86 */
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
#ifndef __local_c16scasecoll_defined
#define __local_c16scasecoll_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c16scasecmp from parts.uchar.string */
#ifndef __local___localdep_c16scasecmp_defined
#define __local___localdep_c16scasecmp_defined 1
#if defined(__CRT_HAVE_wcscasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c16scasecmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c16scasecmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c16scasecmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$_wcsicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c16scasecmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),_wcsicmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <local/wchar/wcscasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16scasecmp (*(int(__LIBDCALL *)(__CHAR16_TYPE__ const *, __CHAR16_TYPE__ const *))&__LIBC_LOCAL_NAME(wcscasecmp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c16scasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16scasecmp __LIBC_LOCAL_NAME(c16scasecmp)
#endif /* !... */
#endif /* !__local___localdep_c16scasecmp_defined */
__LOCAL_LIBC(c16scasecoll) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16scasecoll))(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2) {
	return __localdep_c16scasecmp(__s1, __s2);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16scasecoll_defined
#define __local___localdep_c16scasecoll_defined 1
#define __localdep_c16scasecoll __LIBC_LOCAL_NAME(c16scasecoll)
#endif /* !__local___localdep_c16scasecoll_defined */
#endif /* !__local_c16scasecoll_defined */
