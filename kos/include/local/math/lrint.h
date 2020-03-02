/* HASH CRC-32:0xea25d02d */
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
#ifndef __local_lrint_defined
#define __local_lrint_defined 1
#include <hybrid/typecore.h>

#include <libm/lrint.h>
/* Dependency: "rint" from "math" */
#ifndef ____localdep_rint_defined
#define ____localdep_rint_defined 1
#if __has_builtin(__builtin_rint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rint)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_rint,(double __x),rint,{ return __builtin_rint(__x); })
#elif defined(__CRT_HAVE_rint)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_rint,(double __x),rint,(__x))
#elif defined(__CRT_HAVE___rint)
/* Return the integer nearest X in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_rint,(double __x),__rint,(__x))
#else /* LIBC: rint */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/rint.h>
/* Return the integer nearest X in the direction of the prevailing rounding mode */
#define __localdep_rint (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rint))
#else /* CUSTOM: rint */
#undef ____localdep_rint_defined
#endif /* rint... */
#endif /* rint... */
#endif /* !____localdep_rint_defined */

__NAMESPACE_LOCAL_BEGIN
/* Round X to nearest integral value according to current rounding direction */
__LOCAL_LIBC(lrint) __ATTR_CONST __ATTR_WUNUSED long int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(lrint))(double __x) {
#line 995 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(lrint, __x);
#else /* __LIBM_MATHFUNI */
	return (long int)__localdep_rint(__x);
#endif /* !__LIBM_MATHFUNI */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_lrint_defined */