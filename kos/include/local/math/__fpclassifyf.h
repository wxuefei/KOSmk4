/* HASH CRC-32:0x3439845f */
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
#ifndef __local___fpclassifyf_defined
#define __local___fpclassifyf_defined 1
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE___fpclassify) || defined(__CRT_HAVE__dclass) || defined(__CRT_HAVE_fpclassify) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: __fpclassify from math */
#ifndef __local___localdep___fpclassify_defined
#define __local___localdep___fpclassify_defined 1
#ifdef __CRT_HAVE___fpclassify
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___fpclassify,(double __x),__fpclassify,(__x))
#elif defined(__CRT_HAVE__dclass)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___fpclassify,(double __x),_dclass,(__x))
#elif defined(__CRT_HAVE_fpclassify)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___fpclassify,(double __x),fpclassify,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <local/math/__fpclassify.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___fpclassify __LIBC_LOCAL_NAME(__fpclassify)
#else /* ... */
#undef __local___localdep___fpclassify_defined
#endif /* !... */
#endif /* !__local___localdep___fpclassify_defined */
__NAMESPACE_LOCAL_END
#include <libm/fpclassify.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__fpclassifyf) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(__fpclassifyf))(float __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	
#ifdef __IEEE754_DOUBLE_TYPE_IS_FLOAT__
	return __ieee754_fpclassify((__IEEE754_DOUBLE_TYPE__)__x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
	return __ieee754_fpclassifyf((__IEEE754_FLOAT_TYPE__)__x);
#else /* ... */
	return __ieee854_fpclassifyl((__IEEE854_LONG_DOUBLE_TYPE__)__x);
#endif /* !... */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return __localdep___fpclassify((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___fpclassifyf_defined
#define __local___localdep___fpclassifyf_defined 1
#define __localdep___fpclassifyf __LIBC_LOCAL_NAME(__fpclassifyf)
#endif /* !__local___localdep___fpclassifyf_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE___fpclassify || __CRT_HAVE__dclass || __CRT_HAVE_fpclassify || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local___fpclassifyf_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE___fpclassify && !__CRT_HAVE__dclass && !__CRT_HAVE_fpclassify && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local___fpclassifyf_defined */
