/* HASH CRC-32:0xa02fa275 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_remquol_defined
#if ((__has_builtin(__builtin_remquo) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquo)) || defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo))
#define __local_remquol_defined 1
/* Dependency: "remquo" */
#ifndef ____localdep_remquo_defined
#define ____localdep_remquo_defined 1
#if __has_builtin(__builtin_remquo) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquo)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_remquo)(double __x, double __y, int *__pquo) { return __builtin_remquo(__x, __y, __pquo); }
#elif defined(__CRT_HAVE_remquo)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_remquo,(double __x, double __y, int *__pquo),remquo,(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquo)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_remquo,(double __x, double __y, int *__pquo),__remquo,(__x,__y,__pquo))
#else /* LIBC: remquo */
#undef ____localdep_remquo_defined
#endif /* remquo... */
#endif /* !____localdep_remquo_defined */

__NAMESPACE_LOCAL_BEGIN
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__LOCAL_LIBC(remquol) __ATTR_WUNUSED long double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(remquol))(long double __x,
                                                 long double __y,
                                                 int *__pquo) {
#line 585 "kos/src/libc/magic/math.c"
	return (long double)__localdep_remquo((double)__x, (double)__y, __pquo);
}
__NAMESPACE_LOCAL_END
#endif /* ((__has_builtin(__builtin_remquo) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquo)) || defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)) */
#endif /* !__local_remquol_defined */
