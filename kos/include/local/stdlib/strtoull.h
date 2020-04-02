/* HASH CRC-32:0x8d66b9a0 */
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
#ifndef __local_strtoull_defined
#define __local_strtoull_defined 1
/* Dependency: "strtou32" from "stdlib" */
#ifndef ____localdep_strtou32_defined
#define ____localdep_strtou32_defined 1
#ifdef __CRT_HAVE_strtou32
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, int __base),strtou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && (__SIZEOF_LONG__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, int __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, int __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, int __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, int __base),strtoumax,(__nptr,__endptr,__base))
#else /* LIBC: strtou32 */
#include <local/stdlib/strtou32.h>
#define __localdep_strtou32 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32))
#endif /* strtou32... */
#endif /* !____localdep_strtou32_defined */

/* Dependency: "strtou64" from "stdlib" */
#ifndef ____localdep_strtou64_defined
#define ____localdep_strtou64_defined 1
#ifdef __CRT_HAVE_strtou64
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, int __base),strtou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, int __base),_strtoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, int __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, int __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, int __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, int __base),strtoumax,(__nptr,__endptr,__base))
#else /* LIBC: strtou64 */
#include <local/stdlib/strtou64.h>
#define __localdep_strtou64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64))
#endif /* strtou64... */
#endif /* !____localdep_strtou64_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strtoull) __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtoull))(char const *__restrict __nptr,
                                                      char **__endptr,
                                                      int __base) {
#line 882 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG_LONG__ <= 4
	return (__ULONGLONG)__localdep_strtou32(__nptr, __endptr, __base);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__ULONGLONG)__localdep_strtou64(__nptr, __endptr, __base);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strtoull_defined */
