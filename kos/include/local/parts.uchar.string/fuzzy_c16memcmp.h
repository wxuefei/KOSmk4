/* HASH CRC-32:0xb47ca617 */
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
#ifndef __local_fuzzy_c16memcmp_defined
#define __local_fuzzy_c16memcmp_defined 1
#include <__crt.h>
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fuzzy_memcmpw from string */
#ifndef __local___localdep_fuzzy_memcmpw_defined
#define __local___localdep_fuzzy_memcmpw_defined 1
#ifdef __CRT_HAVE_fuzzy_memcmpw
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcmpw,(void const *__s1, __SIZE_TYPE__ __s1_words, void const *__s2, __SIZE_TYPE__ __s2_words),fuzzy_memcmpw,(__s1,__s1_words,__s2,__s2_words))
#elif defined(__CRT_HAVE_fuzzy_wmemcmp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcmpw,(void const *__s1, __SIZE_TYPE__ __s1_words, void const *__s2, __SIZE_TYPE__ __s2_words),fuzzy_wmemcmp,(__s1,__s1_words,__s2,__s2_words))
#elif !defined(__NO_MALLOCA)
__NAMESPACE_LOCAL_END
#include <local/string/fuzzy_memcmpw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_memcmpw __LIBC_LOCAL_NAME(fuzzy_memcmpw)
#else /* ... */
#undef __local___localdep_fuzzy_memcmpw_defined
#endif /* !... */
#endif /* !__local___localdep_fuzzy_memcmpw_defined */
/* Dependency: fuzzy_memcmp from string */
#ifndef __local___localdep_fuzzy_memcmp_defined
#define __local___localdep_fuzzy_memcmp_defined 1
#ifdef __CRT_HAVE_fuzzy_memcmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcmp,(void const *__s1, __SIZE_TYPE__ __s1_bytes, void const *__s2, __SIZE_TYPE__ __s2_bytes),fuzzy_memcmp,(__s1,__s1_bytes,__s2,__s2_bytes))
#elif !defined(__NO_MALLOCA)
__NAMESPACE_LOCAL_END
#include <local/string/fuzzy_memcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_memcmp __LIBC_LOCAL_NAME(fuzzy_memcmp)
#else /* ... */
#undef __local___localdep_fuzzy_memcmp_defined
#endif /* !... */
#endif /* !__local___localdep_fuzzy_memcmp_defined */
/* Dependency: fuzzy_memcmpl from string */
#ifndef __local___localdep_fuzzy_memcmpl_defined
#define __local___localdep_fuzzy_memcmpl_defined 1
#ifdef __CRT_HAVE_fuzzy_memcmpl
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcmpl,(void const *__s1, __SIZE_TYPE__ __s1_dwords, void const *__s2, __SIZE_TYPE__ __s2_dwords),fuzzy_memcmpl,(__s1,__s1_dwords,__s2,__s2_dwords))
#elif defined(__CRT_HAVE_fuzzy_wmemcmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_fuzzy_memcmpl,(void const *__s1, __SIZE_TYPE__ __s1_dwords, void const *__s2, __SIZE_TYPE__ __s2_dwords),fuzzy_wmemcmp,(__s1,__s1_dwords,__s2,__s2_dwords))
#elif defined(__CRT_HAVE_DOS$fuzzy_wmemcmp)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,__LIBCCALL,__localdep_fuzzy_memcmpl,(void const *__s1, __SIZE_TYPE__ __s1_dwords, void const *__s2, __SIZE_TYPE__ __s2_dwords),KOS$fuzzy_wmemcmp,(__s1,__s1_dwords,__s2,__s2_dwords))
#elif !defined(__NO_MALLOCA)
__NAMESPACE_LOCAL_END
#include <local/string/fuzzy_memcmpl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fuzzy_memcmpl __LIBC_LOCAL_NAME(fuzzy_memcmpl)
#else /* ... */
#undef __local___localdep_fuzzy_memcmpl_defined
#endif /* !... */
#endif /* !__local___localdep_fuzzy_memcmpl_defined */
__LOCAL_LIBC(fuzzy_c16memcmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(fuzzy_c16memcmp))(__CHAR16_TYPE__ const *__s1, __SIZE_TYPE__ __s1_chars, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __s2_chars) {
#if 2 == 2
	return __localdep_fuzzy_memcmpw(__s1, __s1_chars, __s2, __s2_chars);
#elif 2 == 4
	return __localdep_fuzzy_memcmpl(__s1, __s1_chars, __s2, __s2_chars);
#else /* ... */
	return __localdep_fuzzy_memcmp(__s1, __s1_chars * sizeof(__CHAR16_TYPE__), __s2, __s2_chars * sizeof(__CHAR16_TYPE__));
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fuzzy_c16memcmp_defined
#define __local___localdep_fuzzy_c16memcmp_defined 1
#define __localdep_fuzzy_c16memcmp __LIBC_LOCAL_NAME(fuzzy_c16memcmp)
#endif /* !__local___localdep_fuzzy_c16memcmp_defined */
#else /* !__NO_MALLOCA */
#undef __local_fuzzy_c16memcmp_defined
#endif /* __NO_MALLOCA */
#endif /* !__local_fuzzy_c16memcmp_defined */