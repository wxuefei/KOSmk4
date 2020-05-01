/* HASH CRC-32:0x96eb9c95 */
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
#ifndef __local_fuzzy_memcmpq_defined
#ifndef __NO_MALLOCA
#define __local_fuzzy_memcmpq_defined 1
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <parts/malloca.h>
/* Dependency: "memcpyc" from "string" */
#ifndef ____localdep_memcpyc_defined
#define ____localdep_memcpyc_defined 1
#ifdef __fast_memcpyc_defined
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpyc (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyc))
#elif defined(__CRT_HAVE_memcpyc)
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* LIBC: memcpyc */
#include <local/string/memcpyc.h>
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpyc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyc))
#endif /* memcpyc... */
#endif /* !____localdep_memcpyc_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fuzzy_memcmpq) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fuzzy_memcmpq))(void const *__s1,
                                                           __SIZE_TYPE__ __s1_qwords,
                                                           void const *__s2,
                                                           __SIZE_TYPE__ __s2_qwords) {
#line 4660 "kos/src/libc/magic/string.c"
	__SIZE_TYPE__ *__v0, *__v1, __i, __j, __cost, __temp;
	if __unlikely(!__s1_qwords)
		return __s2_qwords;
	if __unlikely(!__s2_qwords)
		return __s1_qwords;
	if (__s2_qwords > __s1_qwords) {
		{
			void const *__temp;
			__temp = __s1;
			__s1   = __s2;
			__s2   = __temp;
		}
		{
			__SIZE_TYPE__ __temp;
			__temp      = __s1_qwords;
			__s1_qwords = __s2_qwords;
			__s2_qwords = __temp;
		}
	}
	__malloca_tryhard(__v0, (__s2_qwords+1) * sizeof(__SIZE_TYPE__));
#ifdef __malloca_tryhard_mayfail
	if __unlikely(!__v0) return (__SIZE_TYPE__)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(__v1, (__s2_qwords+1) * sizeof(__SIZE_TYPE__));
#ifdef __malloca_tryhard_mayfail
	if __unlikely(!__v1) {
		__freea(__v0);
		return (__SIZE_TYPE__)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (__i = 0; __i < __s2_qwords; ++__i)
		__v0[__i] = __i;
	for (__i = 0; __i < __s1_qwords; ++__i) {
		__v1[0] = __i + 1;
		for (__j = 0; __j < __s2_qwords; __j++) {
			__cost  = ((__UINT64_TYPE__ *)__s1)[__i] != ((__UINT64_TYPE__ *)__s2)[__j];
			__cost += __v0[__j];
			__temp  = __v1[__j] + 1;
			if (__cost > __temp)
				__cost = __temp;
			__temp  = __v0[__j + 1] + 1;
			if (__cost > __temp)
				__cost = __temp;
			__v1[__j + 1] = __cost;
		}
		__localdep_memcpyc((__UINT8_TYPE__ *)__v0, (__UINT8_TYPE__ *)__v1, __s2_qwords, sizeof(__SIZE_TYPE__));
	}
	__temp = __v1[__s2_qwords];
	__freea(__v1);
	__freea(__v0);
	return __temp;
}
__NAMESPACE_LOCAL_END
#endif /* !__NO_MALLOCA */
#endif /* !__local_fuzzy_memcmpq_defined */
