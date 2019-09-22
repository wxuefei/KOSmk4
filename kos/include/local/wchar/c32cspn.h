/* HASH CRC-32:0x2e8302e1 */
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
#ifndef __local_c32cspn_defined
#define __local_c32cspn_defined 1
/* Dependency: "wcschr" from "wchar" */
#ifndef ____localdep_c32chr_defined
#define ____localdep_c32chr_defined 1
#if defined(__CRT_HAVE_wcschr) && (__SIZEOF_WCHAR_T__ == 4)
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32chr,(__CHAR32_TYPE__ const *__restrict __haystack, __CHAR32_TYPE__ __needle),wcschr,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcschr.h>
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
#define __localdep_c32chr(haystack, needle) (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))((__WCHAR_TYPE__ const *)(haystack), (__WCHAR_TYPE__)(needle))
#else /* LIBC: c32chr */
#include <local/wchar/c32chr.h>
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
#define __localdep_c32chr (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chr))
#endif /* c32chr... */
#endif /* !____localdep_c32chr_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32cspn) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32cspn))(__CHAR32_TYPE__ const *__haystack,
                                                     __CHAR32_TYPE__ const *__reject) {
#line 312 "kos/src/libc/magic/string.c"
	__CHAR32_TYPE__ const *__iter = __haystack;
	while (*__iter && !__localdep_c32chr(__reject, *__iter))
		++__iter;
	return (__SIZE_TYPE__)(__iter - __haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32cspn_defined */
