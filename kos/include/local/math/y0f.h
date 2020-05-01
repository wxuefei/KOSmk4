/* HASH CRC-32:0x79e02c67 */
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
#ifndef __local_y0f_defined
#if defined(__CRT_HAVE_y0) || defined(__CRT_HAVE___y0)
#define __local_y0f_defined 1
#include <__crt.h>
/* Dependency: "y0" */
#ifndef ____localdep_y0_defined
#define ____localdep_y0_defined 1
#if __has_builtin(__builtin_y0) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y0)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_y0,(double __x),y0,{ return __builtin_y0(__x); })
#elif defined(__CRT_HAVE_y0)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_y0,(double __x),y0,(__x))
#elif defined(__CRT_HAVE___y0)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_y0,(double __x),__y0,(__x))
#else /* LIBC: y0 */
#undef ____localdep_y0_defined
#endif /* y0... */
#endif /* !____localdep_y0_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(y0f) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(y0f))(float __x) {
#line 1577 "kos/src/libc/magic/math.c"
	return (float)__localdep_y0((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_y0 || __CRT_HAVE___y0 */
#endif /* !__local_y0f_defined */
