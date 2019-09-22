/* HASH CRC-32:0xa4160629 */
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
#ifndef __local_settimeofday64_defined
#if defined(__CRT_HAVE_settimeofday)
#define __local_settimeofday64_defined 1
/* Dependency: "settimeofday32" from "sys.time" */
#ifndef ____localdep_settimeofday32_defined
#define ____localdep_settimeofday32_defined 1
#if defined(__CRT_HAVE_settimeofday)
/* Set the current time of day and timezone information.
 * This call is restricted to the super-user */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_settimeofday32,(struct __timeval32 const *__tv, struct timezone const *__tz),settimeofday,(__tv,__tz))
#else /* LIBC: settimeofday */
#undef ____localdep_settimeofday32_defined
#endif /* settimeofday32... */
#endif /* !____localdep_settimeofday32_defined */

__NAMESPACE_LOCAL_BEGIN
/* Set the current time of day and timezone information.
 * This call is restricted to the super-user */
__LOCAL_LIBC(settimeofday64) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(settimeofday64))(struct __timeval64 const *__tv,
                                                            struct timezone const *__tz) {
#line 499 "kos/src/libc/magic/sys.time.c"
	struct __timeval32 __tv32;
	if (!__tv)
		return __localdep_settimeofday32(__NULLPTR, __tz);
	__tv32.tv_sec  = (__time32_t)__tv->tv_sec;
	__tv32.tv_usec = __tv->tv_usec;
	return __localdep_settimeofday32(&__tv32, __tz);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_settimeofday) */
#endif /* !__local_settimeofday64_defined */
