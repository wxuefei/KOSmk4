/* HASH CRC-32:0x511382c3 */
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
#ifndef __local_stroff_defined
#define __local_stroff_defined 1
/* Dependency: "strchrnul" from "string" */
#ifndef ____localdep_strchrnul_defined
#define ____localdep_strchrnul_defined 1
#ifdef __CRT_HAVE_strchrnul
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strchrnul,(char const *__restrict __haystack, int __needle),strchrnul,(__haystack,__needle))
#else /* LIBC: strchrnul */
#include <local/string/strchrnul.h>
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_strchrnul (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchrnul))
#endif /* strchrnul... */
#endif /* !____localdep_strchrnul_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `strchrnul', but return the offset from `STR', rather than the actual address */
__LOCAL_LIBC(stroff) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(stroff))(char const *__restrict __haystack,
                                                    int __needle) {
#line 2485 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_strchrnul(__haystack, __needle) - __haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_stroff_defined */
