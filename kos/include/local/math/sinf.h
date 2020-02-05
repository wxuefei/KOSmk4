/* HASH CRC-32:0xf172b028 */
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
#ifndef __local_sinf_defined
#if defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
#define __local_sinf_defined 1
#include <bits/math-vector.h>
/* Dependency: "sin" */
#ifndef ____localdep_sin_defined
#define ____localdep_sin_defined 1
#if __has_builtin(__builtin_sin) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sin)
/* Sine of X */
__CEIREDIRECT(__DECL_SIMD_sin __ATTR_WUNUSED,double,__NOTHROW,__localdep_sin,(double __x),sin,{ return __builtin_sin(__x); })
#elif defined(__CRT_HAVE_sin)
/* Sine of X */
__CREDIRECT(__DECL_SIMD_sin __ATTR_WUNUSED,double,__NOTHROW,__localdep_sin,(double __x),sin,(__x))
#elif defined(__CRT_HAVE___sin)
/* Sine of X */
__CREDIRECT(__DECL_SIMD_sin __ATTR_WUNUSED,double,__NOTHROW,__localdep_sin,(double __x),__sin,(__x))
#else /* LIBC: sin */
#undef ____localdep_sin_defined
#endif /* sin... */
#endif /* !____localdep_sin_defined */

__NAMESPACE_LOCAL_BEGIN
/* Sine of X */
__LOCAL_LIBC(sinf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(sinf))(float __x) {
#line 213 "kos/src/libc/magic/math.c"
	return (float)__localdep_sin((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_sin || __CRT_HAVE___sin */
#endif /* !__local_sinf_defined */
