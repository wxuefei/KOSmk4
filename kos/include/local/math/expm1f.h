/* HASH CRC-32:0x6bd5de31 */
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
#ifndef __local_expm1f_defined
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1)
#define __local_expm1f_defined 1
#include <__crt.h>
#include <libm/matherr.h>

#include <libm/signbit.h>

#include <libm/finite.h>

#include <libm/expm1.h>
/* Dependency: "expm1" from "math" */
#ifndef ____localdep_expm1_defined
#define ____localdep_expm1_defined 1
#if __has_builtin(__builtin_expm1) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expm1)
/* Return exp(X) - 1 */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_expm1,(double __x),expm1,{ return __builtin_expm1(__x); })
#elif defined(__CRT_HAVE_expm1)
/* Return exp(X) - 1 */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_expm1,(double __x),expm1,(__x))
#elif defined(__CRT_HAVE___expm1)
/* Return exp(X) - 1 */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_expm1,(double __x),__expm1,(__x))
#else /* LIBC: expm1 */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/expm1.h>
/* Return exp(X) - 1 */
#define __localdep_expm1 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expm1))
#else /* CUSTOM: expm1 */
#undef ____localdep_expm1_defined
#endif /* expm1... */
#endif /* expm1... */
#endif /* !____localdep_expm1_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return exp(X) - 1 */
__LOCAL_LIBC(expm1f) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(expm1f))(float __x) {
#line 473 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUNF
	float __result;
	__result = __LIBM_MATHFUNF(expm1, __x);
	if ((!__LIBM_MATHFUNF(finite, __result) || __result == -1.0f) &&
	    __LIBM_MATHFUNF(finite , __x) && __LIBM_LIB_VERSION != __LIBM_IEEE) {
		return __kernel_standard_f(__x, __x, __result,
		                         __LIBM_MATHFUNF(signbit, __x)
		                         ? __LIBM_KMATHERRL_EXPM1_UNDERFLOW
		                         : __LIBM_KMATHERRL_EXPM1_OVERFLOW);
	}
	return __result;
#else /* __LIBM_MATHFUNF */
	return (float)__localdep_expm1((double)__x);
#endif /* !__LIBM_MATHFUNF */
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __CRT_HAVE_expm1 || __CRT_HAVE___expm1 */
#endif /* !__local_expm1f_defined */
