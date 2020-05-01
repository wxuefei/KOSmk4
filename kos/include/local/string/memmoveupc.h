/* HASH CRC-32:0x6188b9c2 */
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
#ifndef __local_memmoveupc_defined
#define __local_memmoveupc_defined 1
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <hybrid/host.h>
/* Dependency: "memmoveup" from "string" */
#ifndef ____localdep_memmoveup_defined
#define ____localdep_memmoveup_defined 1
#ifdef __fast_memmoveup_defined
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
#define __localdep_memmoveup (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveup))
#elif defined(__CRT_HAVE_memmoveup)
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmoveup,(__dst,__src,__n_bytes))
#else /* LIBC: memmoveup */
#include <local/string/memmoveup.h>
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
#define __localdep_memmoveup (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveup))
#endif /* memmoveup... */
#endif /* !____localdep_memmoveup_defined */

/* Dependency: "memmoveupw" from "string" */
#ifndef ____localdep_memmoveupw_defined
#define ____localdep_memmoveupw_defined 1
#ifdef __fast_memmoveupw_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_WORDS') */
#define __localdep_memmoveupw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupw))
#elif defined(__CRT_HAVE_memmoveupw)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupw,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words),memmoveupw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_memmovew)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupw,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words),memmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 2)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupw,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words),wmemmove,(__dst,__src,__n_words))
#else /* LIBC: memmoveupw */
#include <local/string/memmoveupw.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_WORDS') */
#define __localdep_memmoveupw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupw))
#endif /* memmoveupw... */
#endif /* !____localdep_memmoveupw_defined */

/* Dependency: "memmoveupl" from "string" */
#ifndef ____localdep_memmoveupl_defined
#define ____localdep_memmoveupl_defined 1
#ifdef __fast_memmoveupl_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
#define __localdep_memmoveupl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupl))
#elif defined(__CRT_HAVE_memmoveupl)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupl,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords),memmoveupl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 4)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupl,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_memmovel)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupl,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords),memmovel,(__dst,__src,__n_dwords))
#else /* LIBC: memmoveupl */
#include <local/string/memmoveupl.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
#define __localdep_memmoveupl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupl))
#endif /* memmoveupl... */
#endif /* !____localdep_memmoveupl_defined */

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
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__LOCAL_LIBC(memmoveupc) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memmoveupc))(void *__dst,
                                                        void const *__src,
                                                        __SIZE_TYPE__ __elem_count,
                                                        __SIZE_TYPE__ __elem_size) {
#line 2494 "kos/src/libc/magic/string.c"
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (__elem_size) {

	case 1:
		return __localdep_memmoveup(__dst, __src, __elem_count);

	case 2:
		return __localdep_memmoveupw(__dst, __src, __elem_count);

	case 4:
		return __localdep_memmoveupl(__dst, __src, __elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return __localdep_memmoveupq(__dst, __src, __elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return __localdep_memmoveup(__dst, __src, __elem_count * __elem_size);
}

__NAMESPACE_LOCAL_END
#endif /* !__local_memmoveupc_defined */
