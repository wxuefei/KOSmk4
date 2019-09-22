/* HASH CRC-32:0xea5803c8 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c32lwr_l_defined
#define __local_c32lwr_l_defined 1
/* Dependency: "towlower_l" from "wctype" */
#ifndef ____localdep_towlower_l_defined
#define ____localdep_towlower_l_defined 1
#if defined(__CRT_HAVE_towlower_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),towlower_l,(__wc,__locale))
#elif defined(__CRT_HAVE__towlower_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),_towlower_l,(__wc,__locale))
#else /* LIBC: towlower_l */
#include <local/wctype/towlower_l.h>
#define __localdep_towlower_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towlower_l))
#endif /* towlower_l... */
#endif /* !____localdep_towlower_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32lwr_l) __ATTR_RETNONNULL __ATTR_NONNULL((1)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32lwr_l))(__CHAR32_TYPE__ *__restrict __str,
                                                      __locale_t __locale) {
#line 4056 "kos/src/libc/magic/string.c"
	__CHAR32_TYPE__ *__iter, __ch;
	for (__iter = __str; (__ch = *__iter) != '\0'; ++__iter)
		*__iter = (__CHAR32_TYPE__)__localdep_towlower_l(__ch, __locale);
	return __str;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32lwr_l_defined */
