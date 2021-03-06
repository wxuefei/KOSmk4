/* HASH CRC-32:0xe1e4ba8e */
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
#ifndef __local_fuzzy_c16sncmp_defined
#define __local_fuzzy_c16sncmp_defined 1
#include <__crt.h>
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_memcmpw) || (defined(__CRT_HAVE_fuzzy_wmemcmp) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) && defined(__LIBCCALL_IS_LIBDCALL)) || !defined(__NO_MALLOCA)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c16snlen from parts.uchar.string */
#ifndef __local___localdep_c16snlen_defined
#define __local___localdep_c16snlen_defined 1
#if defined(__CRT_HAVE_wcsnlen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16snlen,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnlen)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16snlen,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsnlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_c16snlen (*(__SIZE_TYPE__(__LIBDCALL *)(__CHAR16_TYPE__ const *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(wcsnlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c16snlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_c16snlen __LIBC_LOCAL_NAME(c16snlen)
#endif /* !... */
#endif /* !__local___localdep_c16snlen_defined */
/* Dependency: fuzzy_memcmpw from string */
#ifndef __local___localdep_fuzzy_memcmpw_defined
#define __local___localdep_fuzzy_memcmpw_defined 1
#ifdef __CRT_HAVE_fuzzy_memcmpw
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcmpw,(void const *__s1, __SIZE_TYPE__ __s1_words, void const *__s2, __SIZE_TYPE__ __s2_words),fuzzy_memcmpw,(__s1,__s1_words,__s2,__s2_words))
#elif defined(__CRT_HAVE_fuzzy_wmemcmp) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcmpw,(void const *__s1, __SIZE_TYPE__ __s1_words, void const *__s2, __SIZE_TYPE__ __s2_words),fuzzy_wmemcmp,(__s1,__s1_words,__s2,__s2_words))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcmp) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBCCALL,__localdep_fuzzy_memcmpw,(void const *__s1, __SIZE_TYPE__ __s1_words, void const *__s2, __SIZE_TYPE__ __s2_words),DOS$fuzzy_wmemcmp,(__s1,__s1_words,__s2,__s2_words))
#elif !defined(__NO_MALLOCA)
__NAMESPACE_LOCAL_END
#include <local/string/fuzzy_memcmpw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_memcmpw __LIBC_LOCAL_NAME(fuzzy_memcmpw)
#else /* ... */
#undef __local___localdep_fuzzy_memcmpw_defined
#endif /* !... */
#endif /* !__local___localdep_fuzzy_memcmpw_defined */
__LOCAL_LIBC(fuzzy_c16sncmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(fuzzy_c16sncmp))(__CHAR16_TYPE__ const *__s1, __SIZE_TYPE__ __s1_maxlen, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __s2_maxlen) {
	return __localdep_fuzzy_memcmpw(__s1, __localdep_c16snlen(__s1, __s1_maxlen), __s2, __localdep_c16snlen(__s2, __s2_maxlen));
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fuzzy_c16sncmp_defined
#define __local___localdep_fuzzy_c16sncmp_defined 1
#define __localdep_fuzzy_c16sncmp __LIBC_LOCAL_NAME(fuzzy_c16sncmp)
#endif /* !__local___localdep_fuzzy_c16sncmp_defined */
#else /* __CRT_HAVE_fuzzy_memcmpw || (__CRT_HAVE_fuzzy_wmemcmp && __SIZEOF_WCHAR_T__ == 2) || (__CRT_HAVE_DOS$fuzzy_wmemcmp && __LIBCCALL_IS_LIBDCALL) || !__NO_MALLOCA */
#undef __local_fuzzy_c16sncmp_defined
#endif /* !__CRT_HAVE_fuzzy_memcmpw && (!__CRT_HAVE_fuzzy_wmemcmp || __SIZEOF_WCHAR_T__ != 2) && (!__CRT_HAVE_DOS$fuzzy_wmemcmp || !__LIBCCALL_IS_LIBDCALL) && __NO_MALLOCA */
#endif /* !__local_fuzzy_c16sncmp_defined */
