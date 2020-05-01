/* HASH CRC-32:0x4b6569e0 */
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
#ifndef __local_fabsf_defined
#define __local_fabsf_defined 1
#include <__crt.h>
#include <libm/fabs.h>
/* Dependency: "fabs" from "math" */
#ifndef ____localdep_fabs_defined
#define ____localdep_fabs_defined 1
#if __has_builtin(__builtin_fabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabs)
/* Absolute value of X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_fabs,(double __x),fabs,{ return __builtin_fabs(__x); })
#elif defined(__CRT_HAVE_fabs)
/* Absolute value of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_fabs,(double __x),fabs,(__x))
#elif defined(__CRT_HAVE___fabs)
/* Absolute value of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_fabs,(double __x),__fabs,(__x))
#else /* LIBC: fabs */
#include <local/math/fabs.h>
/* Absolute value of X */
#define __localdep_fabs (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabs))
#endif /* fabs... */
#endif /* !____localdep_fabs_defined */

__NAMESPACE_LOCAL_BEGIN
/* Absolute value of X */
__LOCAL_LIBC(fabsf) __ATTR_CONST __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(fabsf))(float __x) {
#line 720 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUNF
	#ifdef __LIBM_MATHFUNF
	return __LIBM_MATHFUNF(fabs, __x);
#else /* __LIBM_MATHFUN */
	return __x < 0.0f ? -__x : __x;
#endif /* !__LIBM_MATHFUN */
#else /* __LIBM_MATHFUNF */
	return (float)__localdep_fabs((double)__x);
#endif /* !__LIBM_MATHFUNF */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_fabsf_defined */
