/* HASH CRC-32:0x6d68baa3 */
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
#ifndef __local_argz_replace_defined
#define __local_argz_replace_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: memmem from string */
#ifndef __local___localdep_memmem_defined
#define __local___localdep_memmem_defined 1
#if defined(__CRT_HAVE_memmem0) && defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,__localdep_memmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memmem0,(__haystack,__haystacklen,__needle,__needlelen))
#elif defined(__CRT_HAVE_memmem) && !defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,__localdep_memmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memmem,(__haystack,__haystacklen,__needle,__needlelen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/memmem.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
#define __localdep_memmem __LIBC_LOCAL_NAME(memmem)
#endif /* !... */
#endif /* !__local___localdep_memmem_defined */
/* Dependency: memmovedownc from string */
#ifndef __local___localdep_memmovedownc_defined
#define __local___localdep_memmovedownc_defined 1
#ifdef __CRT_HAVE_memmovedownc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmovedownc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmovedownc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memmovedownc */
__NAMESPACE_LOCAL_END
#include <local/string/memmovedownc.h>
__NAMESPACE_LOCAL_BEGIN
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
#define __localdep_memmovedownc __LIBC_LOCAL_NAME(memmovedownc)
#endif /* !__CRT_HAVE_memmovedownc */
#endif /* !__local___localdep_memmovedownc_defined */
/* Dependency: memmoveupc from string */
#ifndef __local___localdep_memmoveupc_defined
#define __local___localdep_memmoveupc_defined 1
#ifdef __CRT_HAVE_memmoveupc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmoveupc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmoveupc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memmoveupc */
__NAMESPACE_LOCAL_END
#include <local/string/memmoveupc.h>
__NAMESPACE_LOCAL_BEGIN
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
#define __localdep_memmoveupc __LIBC_LOCAL_NAME(memmoveupc)
#endif /* !__CRT_HAVE_memmoveupc */
#endif /* !__local___localdep_memmoveupc_defined */
/* Dependency: mempcpyc from string */
#ifndef __local___localdep_mempcpyc_defined
#define __local___localdep_mempcpyc_defined 1
#ifdef __CRT_HAVE_mempcpyc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `memcpyc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_mempcpyc */
__NAMESPACE_LOCAL_END
#include <local/string/mempcpyc.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `memcpyc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
#define __localdep_mempcpyc __LIBC_LOCAL_NAME(mempcpyc)
#endif /* !__CRT_HAVE_mempcpyc */
#endif /* !__local___localdep_mempcpyc_defined */
/* Dependency: realloc from stdlib */
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined 1
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#else /* __has_builtin(__builtin_realloc) && __LIBC_BIND_CRTBUILTINS */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#endif /* !__has_builtin(__builtin_realloc) || !__LIBC_BIND_CRTBUILTINS */
#endif /* !__local___localdep_realloc_defined */
/* Dependency: strlen from string */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined 1
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__NAMESPACE_LOCAL_END
#include <parts/errno.h>
__NAMESPACE_LOCAL_BEGIN
/* Replace all matches of `STR' inside of every string or sub-string from `PARGZ...+=PARGZ_LEN'
 * with `WITH', and resize the ARGZ string if necessary. For every replacement that is done,
 * the given `REPLACE_COUNT' is incremented by one (if `REPLACE_COUNT' is non-NULL)
 * @return: 0:      Success
 * @return: ENOMEM: Insufficient heap memory (can only happen when `strlen(with) > strlen(str)',
 *                  but note that the GLibc implementation of this function is completely
 *                  unreadable and may be able to return this for other cases as well...) */
__LOCAL_LIBC(argz_replace) __ATTR_NONNULL((1, 2, 4)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(argz_replace))(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char const *__restrict __str, char const *__restrict __with, unsigned int *__restrict __replace_count) {
	__SIZE_TYPE__ __findlen, __repllen;
	__SIZE_TYPE__ __find_offset;
	if __unlikely(!__str)
		return 0; /* no-op */
	__findlen = __localdep_strlen(__str);
	if __unlikely(!__findlen)
		return 0; /* no-op */
	__repllen = __localdep_strlen(__with);
	__find_offset = 0;
	/* I have no idea what the GLibc implementation does here, and I'm not
	 * quite sure it knows either. - At first I though that this function
	 * was supposed to only replace entries of an ARGZ string as a whole,
	 * but now I believe it's just supposed to do replacement of any match
	 * found. However, GLibc appears to be utterly afraid of using `memmem()'
	 * for this, and instead opt's to using `argz_next()' to iterate the
	 * ARGZ vector, and doing `strstr()' on each element, before doing some
	 * dark voodoo magic with `strndup()', temporary buffers, and god only
	 * knows why there are even delayed calls to `argz_add()' in there???
	 * If this implementation doesn't do exactly what GLibc does, don't fault
	 * me. Every function in this file was originally created as a GLibc
	 * extension, so there really isn't any official documentation on intended
	 * behavior other than GLibc reference implementation.
	 * Anyways... At least my version is readable... */
	while (__find_offset < *__pargz_len) {
		char *__pos;
		__pos = (char *)__localdep_memmem(*__pargz + __find_offset,
		                     *__pargz_len - __find_offset,
		                     __str, __findlen);
		if (!__pos)
			break; /* Nothing else to find! */
		if (__repllen < __findlen) {
			/* Simple case: The replacement string is smaller than the find-string */
			char *__old_argz, *__new_argz;
			__SIZE_TYPE__ __diff, __trailing_characters;
			__pos  = (char *)__localdep_mempcpyc(__pos, __with, __repllen, sizeof(char));
			__diff = __findlen - __repllen;
			*__pargz_len -= __diff;
			__old_argz = *__pargz;
			__trailing_characters = *__pargz_len - (__SIZE_TYPE__)(__pos - __old_argz);
			__localdep_memmovedownc(__pos, __pos + __diff, __trailing_characters, sizeof(char));
			__new_argz = (char *)__localdep_realloc(__old_argz, *__pargz_len * sizeof(char));
			if __likely(__new_argz) {
				__pos    = __new_argz + (__pos - __old_argz);
				*__pargz = __new_argz;
			}
		} else if (__repllen > __findlen) {
			char *__old_argz, *__new_argz;
			__SIZE_TYPE__ __old_argzlen, __new_argzlen;
			__SIZE_TYPE__ __diff, __trailing_characters;
			/* Difficult case: The replacement string is longer than the find-string */
			__diff = __repllen - __findlen;
			__old_argzlen = *__pargz_len;
			__new_argzlen = __old_argzlen + __diff;
			__old_argz = *__pargz;
			__new_argz = (char *)__localdep_realloc(__old_argz, __new_argzlen * sizeof(char));
			if __unlikely(!__new_argz) {
#ifdef __ENOMEM
				return __ENOMEM;
#else /* __ENOMEM */
				return 1;
#endif /* !__ENOMEM */
			}
			__pos = __new_argz + (__pos - __old_argz);
			/* Make space for extra data */
			__trailing_characters = __new_argzlen - ((__pos + __repllen) - __new_argz);
			__localdep_memmoveupc(__pos + __repllen,
			           __pos + __findlen,
			           __trailing_characters,
			           sizeof(char));
			/* Fill in the replacement string. */
			__pos = (char *)__localdep_mempcpyc(__pos, __with, __repllen, sizeof(char));
		} else {
			/* Simple case: The replacement string has the same length as the find-string */
			__pos = (char *)__localdep_mempcpyc(__pos, __with, __repllen, sizeof(char));
		}
		if (__replace_count)
			++*__replace_count;
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_argz_replace_defined
#define __local___localdep_argz_replace_defined 1
#define __localdep_argz_replace __LIBC_LOCAL_NAME(argz_replace)
#endif /* !__local___localdep_argz_replace_defined */
#else /* __CRT_HAVE_realloc && (__CRT_HAVE_free || __CRT_HAVE_cfree) */
#undef __local_argz_replace_defined
#endif /* !__CRT_HAVE_realloc || (!__CRT_HAVE_free && !__CRT_HAVE_cfree) */
#endif /* !__local_argz_replace_defined */
