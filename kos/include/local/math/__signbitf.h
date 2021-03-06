/* HASH CRC-32:0x8c1bbe19 */
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
#ifndef __local___signbitf_defined
#define __local___signbitf_defined 1
#include <__crt.h>
#include <libm/signbit.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__signbitf) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(__signbitf))(float __x) {
#ifdef __IEEE754_DOUBLE_TYPE_IS_FLOAT__
	return __ieee754_signbit((__IEEE754_DOUBLE_TYPE__)__x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
	return __ieee754_signbitf((__IEEE754_FLOAT_TYPE__)__x);
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
	return __ieee854_signbitl((__IEEE854_LONG_DOUBLE_TYPE__)__x);
#else /* ... */
	return __x < 0.0f;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___signbitf_defined
#define __local___localdep___signbitf_defined 1
#define __localdep___signbitf __LIBC_LOCAL_NAME(__signbitf)
#endif /* !__local___localdep___signbitf_defined */
#endif /* !__local___signbitf_defined */
