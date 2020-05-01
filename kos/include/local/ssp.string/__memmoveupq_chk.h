/* HASH CRC-32:0xc5f9af15 */
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
#ifndef __local___memmoveupq_chk_defined
#define __local___memmoveupq_chk_defined 1
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <ssp/chk.h>
/* Dependency: "memmoveupq" from "string" */
#ifndef ____localdep_memmoveupq_defined
#define ____localdep_memmoveupq_defined 1
#ifdef __fast_memmoveupq_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_QWORDS') */
#define __localdep_memmoveupq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupq))
#elif defined(__CRT_HAVE_memmoveupq)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_QWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupq,(/*aligned(8)*/ void *__dst, /*aligned(8)*/ void const *__src, __SIZE_TYPE__ __n_qwords),memmoveupq,(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_memmoveq)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_QWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupq,(/*aligned(8)*/ void *__dst, /*aligned(8)*/ void const *__src, __SIZE_TYPE__ __n_qwords),memmoveq,(__dst,__src,__n_qwords))
#else /* LIBC: memmoveupq */
#include <local/string/memmoveupq.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_QWORDS') */
#define __localdep_memmoveupq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupq))
#endif /* memmoveupq... */
#endif /* !____localdep_memmoveupq_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__memmoveupq_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__memmoveupq_chk))(/*aligned(8)*/ void *__dst,
                                                              /*aligned(8)*/ void const *__src,
                                                              __SIZE_TYPE__ __n_qwords,
                                                              __SIZE_TYPE__ __dst_objsize) {
#line 106 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memmoveupq", __dst, __n_qwords * 8, __dst_objsize);
	return __localdep_memmoveupq(__dst, __src, __n_qwords);
}

__NAMESPACE_LOCAL_END
#endif /* !__local___memmoveupq_chk_defined */
