/* HASH CRC-32:0x1eacf6e1 */
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
#ifndef __local_memxlen_defined
#define __local_memxlen_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: memxend from string */
#ifndef __local___localdep_memxend_defined
#define __local___localdep_memxend_defined 1
#ifdef __CRT_HAVE_memxend
/* Same as `memend', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memxend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memxend,(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memxend */
__NAMESPACE_LOCAL_END
#include <local/string/memxend.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `memend', but search for non-matching locations. */
#define __localdep_memxend __LIBC_LOCAL_NAME(memxend)
#endif /* !__CRT_HAVE_memxend */
#endif /* !__local___localdep_memxend_defined */
/* Same as `memlen', but search for non-matching locations. */
__LOCAL_LIBC(memxlen) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memxlen))(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) {
	return (__SIZE_TYPE__)((__BYTE_TYPE__ *)__localdep_memxend(__haystack, __needle, __n_bytes) - (__BYTE_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memxlen_defined
#define __local___localdep_memxlen_defined 1
#define __localdep_memxlen __LIBC_LOCAL_NAME(memxlen)
#endif /* !__local___localdep_memxlen_defined */
#endif /* !__local_memxlen_defined */
