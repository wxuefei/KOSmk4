/* HASH CRC-32:0x8d72c3f1 */
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
#ifndef __local_logl_defined
#if defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
#define __local_logl_defined 1
#include <bits/math-vector.h>
#include <bits/math-vector.h>
/* Dependency: "log" */
#ifndef ____localdep_log_defined
#define ____localdep_log_defined 1
#if __has_builtin(__builtin_log) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log)
/* Natural logarithm of X */
__CEIREDIRECT(__DECL_SIMD_log __ATTR_WUNUSED,double,__NOTHROW,__localdep_log,(double __x),log,{ return __builtin_log(__x); })
#elif defined(__CRT_HAVE_log)
/* Natural logarithm of X */
__CREDIRECT(__DECL_SIMD_log __ATTR_WUNUSED,double,__NOTHROW,__localdep_log,(double __x),log,(__x))
#elif defined(__CRT_HAVE___log)
/* Natural logarithm of X */
__CREDIRECT(__DECL_SIMD_log __ATTR_WUNUSED,double,__NOTHROW,__localdep_log,(double __x),__log,(__x))
#else /* LIBC: log */
#undef ____localdep_log_defined
#endif /* log... */
#endif /* !____localdep_log_defined */

__NAMESPACE_LOCAL_BEGIN
/* Natural logarithm of X */
__LOCAL_LIBC(logl) __DECL_SIMD_logl __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(logl))(__LONGDOUBLE __x) {
#line 529 "kos/src/libc/magic/math.c"
	return (__LONGDOUBLE)__localdep_log((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_log || __CRT_HAVE___log */
#endif /* !__local_logl_defined */
