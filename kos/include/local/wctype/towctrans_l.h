/* HASH CRC-32:0x7f824beb */
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
#ifndef __local_towctrans_l_defined
#define __local_towctrans_l_defined 1
/* Dependency: "towctrans" from "wctype" */
#ifndef ____localdep_towctrans_defined
#define ____localdep_towctrans_defined 1
#ifdef __std___localdep_towctrans_defined
__NAMESPACE_STD_USING(__localdep_towctrans)
#elif defined(__CRT_HAVE_towctrans)
__CREDIRECT(__ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towctrans,(__WINT_TYPE__ __wc, __wctrans_t __desc),towctrans,(__wc,__desc))
#elif defined(__CRT_HAVE___towctrans)
__CREDIRECT(__ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towctrans,(__WINT_TYPE__ __wc, __wctrans_t __desc),__towctrans,(__wc,__desc))
#else /* LIBC: towctrans */
#include <local/wctype/towctrans.h>
#define __localdep_towctrans (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towctrans))
#endif /* towctrans... */
#endif /* !____localdep_towctrans_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(towctrans_l) __ATTR_WUNUSED __WINT_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(towctrans_l))(__WINT_TYPE__ __wc,
                                                         __wctrans_t __desc,
                                                         __locale_t __locale) {
#line 323 "kos/src/libc/magic/wctype.c"
	(void)__locale;
	return __localdep_towctrans(__wc, __desc);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_towctrans_l_defined */
