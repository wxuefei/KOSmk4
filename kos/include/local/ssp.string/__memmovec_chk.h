/* HASH CRC-32:0x2ae87e4c */
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
#ifndef __local___memmovec_chk_defined
#define __local___memmovec_chk_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <ssp/chk.h>
/* Dependency: "memmovec" from "string" */
#ifndef ____localdep_memmovec_defined
#define ____localdep_memmovec_defined 1
#ifdef __fast_memmovec_defined
/* Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
#define __localdep_memmovec (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovec))
#elif defined(__CRT_HAVE_memmovec)
/* Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmovec,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmovec,(__dst,__src,__elem_count,__elem_size))
#else /* LIBC: memmovec */
#include <local/string/memmovec.h>
/* Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
#define __localdep_memmovec (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovec))
#endif /* memmovec... */
#endif /* !____localdep_memmovec_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__memmovec_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__memmovec_chk))(void *__dst,
                                                            void const *__src,
                                                            __SIZE_TYPE__ __elem_count,
                                                            __SIZE_TYPE__ __elem_size,
                                                            __SIZE_TYPE__ __dst_objsize) {
#line 65 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memmovec", __dst, __elem_count * __elem_size, __dst_objsize);
	return __localdep_memmovec(__dst, __src, __elem_count, __elem_size);
}

__NAMESPACE_LOCAL_END
#endif /* !__local___memmovec_chk_defined */