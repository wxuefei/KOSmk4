/* HASH CRC-32:0x607c9dd3 */
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
#ifndef __local_cbrtl_defined
#if ((__has_builtin(__builtin_cbrt) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cbrt)) || defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt))
#define __local_cbrtl_defined 1
/* Dependency: "cbrt" */
#ifndef ____localdep_cbrt_defined
#define ____localdep_cbrt_defined 1
#if __has_builtin(__builtin_cbrt) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cbrt)
/* Return the cube root of X */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_cbrt)(double __x) { return __builtin_cbrt(__x); }
#elif defined(__CRT_HAVE_cbrt)
/* Return the cube root of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_cbrt,(double __x),cbrt,(__x))
#elif defined(__CRT_HAVE___cbrt)
/* Return the cube root of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_cbrt,(double __x),__cbrt,(__x))
#else /* LIBC: cbrt */
#undef ____localdep_cbrt_defined
#endif /* cbrt... */
#endif /* !____localdep_cbrt_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the cube root of X */
__LOCAL_LIBC(cbrtl) __ATTR_WUNUSED long double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(cbrtl))(long double __x) {
#line 336 "kos/src/libc/magic/math.c"
	return (long double)__localdep_cbrt((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* ((__has_builtin(__builtin_cbrt) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cbrt)) || defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt)) */
#endif /* !__local_cbrtl_defined */
