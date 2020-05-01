/* HASH CRC-32:0xff5ec62b */
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
#ifndef __local_localtime_defined
#define __local_localtime_defined 1
#include <__crt.h>
#ifndef __STRUCT_TM
#ifdef __tm_defined
#define __STRUCT_TM struct __NAMESPACE_STD_SYM tm
#else /* __tm_defined */
#define __STRUCT_TM struct __NAMESPACE_STD_SYM __NAMESPACE_STD_SYM tm
#ifndef __std_tm_defined
#define __std_tm_defined 1
__NAMESPACE_STD_BEGIN
struct __NAMESPACE_STD_SYM tm {
	int         tm_sec;      /* seconds [0, 61]. */
	int         tm_min;      /* minutes [0, 59]. */
	int         tm_hour;     /* hour [0, 23]. */
	int         tm_mday;     /* day of month [1, 31]. */
	int         tm_mon;      /* month of year [0, 11]. */
	int         tm_year;     /* years since 1900. */
	int         tm_wday;     /* day of week [0, 6] (Sunday = 0). */
	int         tm_yday;     /* day of year [0, 365]. */
	int         tm_isdst;    /* daylight savings flag. */
#ifdef __CRT_GLC
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* __CRT_GLC */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */

#if !(defined(__CRT_HAVE_localtime) || defined(__CRT_HAVE__localtime32)) || !(1)
#ifndef __LIBC_GMTIME_BUFFER_DEFINED
#define __LIBC_GMTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_ATTR_WEAK
__INTERN __ATTR_UNUSED __ATTR_WEAK __STRUCT_TM __gmtime_buf = {0};
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN __ATTR_UNUSED __ATTR_SELECTANY __STRUCT_TM __gmtime_buf = {0};
#else
__PRIVATE __ATTR_UNUSED __STRUCT_TM __gmtime_buf = {0};
#endif
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_GMTIME_BUFFER_DEFINED */
#endif /* !__CRT_HAVE_localtime && !__CRT_HAVE__localtime32 */
/* Dependency: "localtime64" from "time" */
#ifndef ____localdep_localtime64_defined
#define ____localdep_localtime64_defined 1
#ifdef __CRT_HAVE_localtime64
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__STRUCT_TM *,__NOTHROW_NCX,__localdep_localtime64,(__time64_t const *__timer),localtime64,(__timer))
#elif defined(__CRT_HAVE_localtime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__STRUCT_TM *,__NOTHROW_NCX,__localdep_localtime64,(__time64_t const *__timer),localtime,(__timer))
#elif defined(__CRT_HAVE__localtime64)
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__STRUCT_TM *,__NOTHROW_NCX,__localdep_localtime64,(__time64_t const *__timer),_localtime64,(__timer))
#else /* LIBC: localtime64 */
#include <local/time/localtime64.h>
/* Return the `struct tm' representation of *TIMER in the local timezone */
#define __localdep_localtime64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime64))
#endif /* localtime64... */
#endif /* !____localdep_localtime64_defined */

/* Dependency: "localtime32" from "time" */
#ifndef ____localdep_localtime32_defined
#define ____localdep_localtime32_defined 1
#ifdef __CRT_HAVE_localtime
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__STRUCT_TM *,__NOTHROW_NCX,__localdep_localtime32,(__time64_t const *__timer),localtime,(__timer))
#elif defined(__CRT_HAVE__localtime32)
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__STRUCT_TM *,__NOTHROW_NCX,__localdep_localtime32,(__time64_t const *__timer),_localtime32,(__timer))
#else /* LIBC: localtime */
#undef ____localdep_localtime32_defined
#endif /* localtime32... */
#endif /* !____localdep_localtime32_defined */

/* Dependency: "localtime_r" from "time" */
#ifndef ____localdep_localtime_r_defined
#define ____localdep_localtime_r_defined 1
#ifdef __CRT_HAVE_localtime_r
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STRUCT_TM *,__NOTHROW_NCX,__localdep_localtime_r,(__TM_TYPE(time) const *__restrict __timer, __STRUCT_TM *__restrict __tp),localtime_r,(__timer,__tp))
#else /* LIBC: localtime_r */
#include <local/time/localtime_r.h>
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
#define __localdep_localtime_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime_r))
#endif /* localtime_r... */
#endif /* !____localdep_localtime_r_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the `struct tm' representation of *TIMER in the local timezone */
__LOCAL_LIBC(localtime) __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct __NAMESPACE_STD_SYM tm *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(localtime))(__TM_TYPE(time) const *__timer) {
#line 521 "kos/src/libc/magic/time.c"
#if 1
	__time64_t __tm64 = (__time64_t)*__timer;
	return __localdep_localtime64(&__tm64);
#elif 1
	__time32_t __tm32 = (__time32_t)*__timer;
	return __localdep_localtime32(&__tm32);
#else /* 1 */
	return __localdep_localtime_r(__timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);
#endif /* 0 */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_localtime_defined */
