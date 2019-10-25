/* HASH CRC-32:0xac5d3e9c */
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
#ifndef __local_c32upr_defined
#define __local_c32upr_defined 1
/* Dependency: "towupper" from "wctype" */
#ifndef ____localdep_towupper_defined
#define ____localdep_towupper_defined 1
#if __has_builtin(__builtin_towupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_towupper)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW(__LIBCCALL __localdep_towupper)(__WINT_TYPE__ __wc) { return __builtin_towupper(__wc); }
#elif defined(__CRT_HAVE_towupper)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW,__localdep_towupper,(__WINT_TYPE__ __wc),towupper,(__wc))
#else /* LIBC: towupper */
#include <local/wctype/towupper.h>
#define __localdep_towupper (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towupper))
#endif /* towupper... */
#endif /* !____localdep_towupper_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32upr) __ATTR_RETNONNULL __ATTR_NONNULL((1)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32upr))(__CHAR32_TYPE__ *__restrict __str) {
#line 4367 "kos/src/libc/magic/string.c"
	__CHAR32_TYPE__ *__iter, __ch;
	for (__iter = __str; (__ch = *__iter) != '\0'; ++__iter)
		*__iter = (__CHAR32_TYPE__)__localdep_towupper(__ch);
	return __str;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32upr_defined */
