/* HASH CRC-32:0xf00c4245 */
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
#ifndef __local_c32spcpy_defined
#define __local_c32spcpy_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32slen from parts.uchar.string */
#ifndef __local___localdep_c32slen_defined
#define __local___localdep_c32slen_defined 1
#if defined(__CRT_HAVE_wcslen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32slen,(__CHAR32_TYPE__ const *__restrict __string),wcslen,(__string))
#elif defined(__CRT_HAVE_KOS$wcslen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32slen,(__CHAR32_TYPE__ const *__restrict __string),wcslen,(__string))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <local/wchar/wcslen.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c32slen (*(__SIZE_TYPE__(__LIBKCALL *)(__CHAR32_TYPE__ const *__restrict))&__LIBC_LOCAL_NAME(wcslen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c32slen.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c32slen __LIBC_LOCAL_NAME(c32slen)
#endif /* !... */
#endif /* !__local___localdep_c32slen_defined */
/* Dependency: mempcpyl from string */
#ifndef __local___localdep_mempcpyl_defined
#define __local___localdep_mempcpyl_defined 1
#ifdef __CRT_HAVE_mempcpyl
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),mempcpyl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempcpy) && __SIZEOF_WCHAR_T__ == 4
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),wmempcpy,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempcpy) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),KOS$wmempcpy,(__dst,__src,__n_dwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/mempcpyl.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
#define __localdep_mempcpyl __LIBC_LOCAL_NAME(mempcpyl)
#endif /* !... */
#endif /* !__local___localdep_mempcpyl_defined */
/* Same as wcscpy, but return a pointer after the last written character */
__LOCAL_LIBC(c32spcpy) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32spcpy))(__CHAR32_TYPE__ *__restrict __buf, __CHAR32_TYPE__ const *__restrict __src) {
	return (__CHAR32_TYPE__ *)__localdep_mempcpyl(__buf, __src, __localdep_c32slen(__src) + 1);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32spcpy_defined
#define __local___localdep_c32spcpy_defined 1
#define __localdep_c32spcpy __LIBC_LOCAL_NAME(c32spcpy)
#endif /* !__local___localdep_c32spcpy_defined */
#endif /* !__local_c32spcpy_defined */
