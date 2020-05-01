/* HASH CRC-32:0xe8638936 */
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
#ifndef __local_mempmoveup_defined
#define __local_mempmoveup_defined 1
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
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

__NAMESPACE_LOCAL_BEGIN
/* Same as `memmoveup', but return `DST + N_BYTES', rather than `DST' (assumes that `DST >= SRC || !N_BYTES') */
__LOCAL_LIBC(mempmoveup) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempmoveup))(void *__dst,
                                                        void const *__src,
                                                        __SIZE_TYPE__ __n_bytes) {
#line 2652 "kos/src/libc/magic/string.c"
	return (void *)((__BYTE_TYPE__ *)__localdep_memmoveup(__dst, __src, __n_bytes) + __n_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_mempmoveup_defined */
