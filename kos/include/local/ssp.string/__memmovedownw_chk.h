/* HASH CRC-32:0xcb2c02b */
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
#ifndef __local___memmovedownw_chk_defined
#define __local___memmovedownw_chk_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <ssp/chk.h>
/* Dependency: "memmovedownw" from "string" */
#ifndef ____localdep_memmovedownw_defined
#define ____localdep_memmovedownw_defined 1
#ifdef __fast_memmovedownw_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
#define __localdep_memmovedownw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownw))
#elif defined(__CRT_HAVE_memmovedownw)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownw,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words),memmovedownw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_memmovew)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownw,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words),memmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 2)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownw,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words),wmemmove,(__dst,__src,__n_words))
#else /* LIBC: memmovedownw */
#include <local/string/memmovedownw.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
#define __localdep_memmovedownw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedownw))
#endif /* memmovedownw... */
#endif /* !____localdep_memmovedownw_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__memmovedownw_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__memmovedownw_chk))(/*aligned(2)*/ void *__dst,
                                                                /*aligned(2)*/ void const *__src,
                                                                __SIZE_TYPE__ __n_words,
                                                                __SIZE_TYPE__ __dst_objsize) {
#line 90 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memmovedownw", __dst, __n_words * 2, __dst_objsize);
	return __localdep_memmovedownw(__dst, __src, __n_words);
}

__NAMESPACE_LOCAL_END
#endif /* !__local___memmovedownw_chk_defined */