/* HASH CRC-32:0xc636922e */
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
#ifndef __local_timegm64_defined
#define __local_timegm64_defined 1
/* Dependency: "timegm32" from "time" */
#ifndef ____localdep_timegm32_defined
#define ____localdep_timegm32_defined 1
#if defined(__CRT_HAVE_timegm)
/* Like `mktime', but for TP represents Universal Time, not local time */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__time32_t,__NOTHROW_NCX,__localdep_timegm32,(struct tm *__tp),timegm,(__tp))
#else /* LIBC: timegm */
#undef ____localdep_timegm32_defined
#endif /* timegm32... */
#endif /* !____localdep_timegm32_defined */

/* Dependency: "mktime64" from "time" */
#ifndef ____localdep_mktime64_defined
#define ____localdep_mktime64_defined 1
#if defined(__CRT_HAVE_mktime64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(struct tm __KOS_FIXED_CONST *__tp),mktime64,(__tp))
#elif defined(__CRT_HAVE_mktime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(struct tm __KOS_FIXED_CONST *__tp),mktime,(__tp))
#elif defined(__CRT_HAVE__mktime64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(struct tm __KOS_FIXED_CONST *__tp),_mktime64,(__tp))
#elif defined(__CRT_HAVE_timelocal64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(struct tm __KOS_FIXED_CONST *__tp),timelocal64,(__tp))
#else /* LIBC: mktime64 */
#include <local/time/mktime64.h>
/* Return the `time_t' representation of TP and normalize TP */
#define __localdep_mktime64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mktime64))
#endif /* mktime64... */
#endif /* !____localdep_mktime64_defined */

__NAMESPACE_LOCAL_BEGIN
/* Like `mktime', but for TP represents Universal Time, not local time */
__LOCAL_LIBC(timegm64) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __time64_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timegm64))(struct tm *__tp) {
#line 998 "kos/src/libc/magic/time.c"
#if defined(__CRT_HAVE_timegm) && !defined(__BUILDING_LIBC)
	return (__time64_t)__localdep_timegm32(__tp);
#else
	/* TODO: Timezones */
	return __localdep_mktime64(__tp);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_timegm64_defined */
