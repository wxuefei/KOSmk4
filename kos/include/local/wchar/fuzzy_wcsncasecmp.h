/* HASH CRC-32:0x7488b8ce */
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
#ifndef __local_fuzzy_wcsncasecmp_defined
#define __local_fuzzy_wcsncasecmp_defined 1
#include <__crt.h>
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fuzzy_wmemcasecmp from wchar */
#ifndef __local___localdep_fuzzy_wmemcasecmp_defined
#define __local___localdep_fuzzy_wmemcasecmp_defined 1
#ifdef __CRT_HAVE_fuzzy_wmemcasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_wmemcasecmp,(__WCHAR_TYPE__ const *__s1, __SIZE_TYPE__ __s1_bytes, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_wmemcasecmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif !defined(__NO_MALLOCA)
__NAMESPACE_LOCAL_END
#include <local/wchar/fuzzy_wmemcasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_wmemcasecmp __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp)
#else /* ... */
#undef __local___localdep_fuzzy_wmemcasecmp_defined
#endif /* !... */
#endif /* !__local___localdep_fuzzy_wmemcasecmp_defined */
/* Dependency: wcsnlen from wchar */
#ifndef __local___localdep_wcsnlen_defined
#define __local___localdep_wcsnlen_defined 1
#ifdef __CRT_HAVE_wcsnlen
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(__WCHAR_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#else /* __CRT_HAVE_wcsnlen */
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsnlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_wcsnlen __LIBC_LOCAL_NAME(wcsnlen)
#endif /* !__CRT_HAVE_wcsnlen */
#endif /* !__local___localdep_wcsnlen_defined */
__LOCAL_LIBC(fuzzy_wcsncasecmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp))(__WCHAR_TYPE__ const *__s1, __SIZE_TYPE__ __s1_maxlen, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __s2_maxlen) {
	return __localdep_fuzzy_wmemcasecmp(__s1, __localdep_wcsnlen(__s1, __s1_maxlen), __s2, __localdep_wcsnlen(__s2, __s2_maxlen));
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fuzzy_wcsncasecmp_defined
#define __local___localdep_fuzzy_wcsncasecmp_defined 1
#define __localdep_fuzzy_wcsncasecmp __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp)
#endif /* !__local___localdep_fuzzy_wcsncasecmp_defined */
#else /* __CRT_HAVE_fuzzy_wmemcasecmp || !__NO_MALLOCA */
#undef __local_fuzzy_wcsncasecmp_defined
#endif /* !__CRT_HAVE_fuzzy_wmemcasecmp && __NO_MALLOCA */
#endif /* !__local_fuzzy_wcsncasecmp_defined */
