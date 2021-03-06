/* HASH CRC-32:0xc80ee422 */
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
#ifndef __local_memrlenl_defined
#define __local_memrlenl_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: memrendl from string */
#ifndef __local___localdep_memrendl_defined
#define __local___localdep_memrendl_defined 1
#ifdef __CRT_HAVE_memrendl
/* Same as `memrchrl', but return `HAYSTACK - 4', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memrendl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memrendl,(__haystack,__needle,__n_dwords))
#else /* __CRT_HAVE_memrendl */
__NAMESPACE_LOCAL_END
#include <local/string/memrendl.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `memrchrl', but return `HAYSTACK - 4', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memrendl __LIBC_LOCAL_NAME(memrendl)
#endif /* !__CRT_HAVE_memrendl */
#endif /* !__local___localdep_memrendl_defined */
/* Same as `memrendl', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 4' if the given `NEEDLE' wasn't found */
__LOCAL_LIBC(memrlenl) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memrlenl))(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords) {
	return (__SIZE_TYPE__)(__localdep_memrendl(__haystack, __needle, __n_dwords) - (__UINT32_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memrlenl_defined
#define __local___localdep_memrlenl_defined 1
#define __localdep_memrlenl __LIBC_LOCAL_NAME(memrlenl)
#endif /* !__local___localdep_memrlenl_defined */
#endif /* !__local_memrlenl_defined */
