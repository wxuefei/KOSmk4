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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(time_t   = "__TM_TYPE(time)")]
%[define_replacement(time32_t = __time32_t)]
%[define_replacement(time64_t = __time64_t)]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(timeval32  = __timeval32)]
%[define_replacement(timeval64  = __timeval64)]
%[define_replacement(itimerval32 = __itimerval32)]
%[define_replacement(itimerval64 = __itimerval64)]


%{
#include <features.h>

#include <asm/time.h>
#include <bits/types.h>
#include <bits/itimerval.h>
#include <sys/select.h>

/* Documentation taken from /usr/include/i386-linux-gnu/sys/time.h */
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


__SYSDECL_BEGIN

#if (defined(__ITIMER_REAL) || defined(__ITIMER_VIRTUAL) || \
     defined(__ITIMER_PROF))
/*[[[enum]]]*/
#ifdef __CC__
typedef enum __itimer_which {
#ifdef __ITIMER_REAL
	ITIMER_REAL    = __ITIMER_REAL,
#endif /* __ITIMER_REAL */
#ifdef __ITIMER_VIRTUAL
	ITIMER_VIRTUAL = __ITIMER_VIRTUAL,
#endif /* __ITIMER_VIRTUAL */
#ifdef __ITIMER_PROF
	ITIMER_PROF    = __ITIMER_PROF
#endif /* __ITIMER_PROF */
} __itimer_which_t;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __ITIMER_REAL
#define ITIMER_REAL    ITIMER_REAL
#endif /* __ITIMER_REAL */
#ifdef __ITIMER_VIRTUAL
#define ITIMER_VIRTUAL ITIMER_VIRTUAL
#endif /* __ITIMER_VIRTUAL */
#ifdef __ITIMER_PROF
#define ITIMER_PROF    ITIMER_PROF
#endif /* __ITIMER_PROF */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __ITIMER_REAL
#define ITIMER_REAL    __ITIMER_REAL
#endif /* __ITIMER_REAL */
#ifdef __ITIMER_VIRTUAL
#define ITIMER_VIRTUAL __ITIMER_VIRTUAL
#endif /* __ITIMER_VIRTUAL */
#ifdef __ITIMER_PROF
#define ITIMER_PROF    __ITIMER_PROF
#endif /* __ITIMER_PROF */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

#ifdef __CC__

#ifndef __time_t_defined
#define __time_t_defined  1
typedef __TM_TYPE(time) time_t;
#endif /* !__time_t_defined */

#ifndef __suseconds_t_defined
#define __suseconds_t_defined
typedef __suseconds_t suseconds_t;
#endif /* !__suseconds_t_defined */

#ifdef __USE_GNU
#define TIMEVAL_TO_TIMESPEC(tv, ts) (void)((ts)->tv_sec = (tv)->tv_sec, (ts)->tv_nsec = (tv)->tv_usec * 1000)
#define TIMESPEC_TO_TIMEVAL(tv, ts) (void)((tv)->tv_sec = (ts)->tv_sec, (tv)->tv_usec = (ts)->tv_nsec / 1000)
#endif /* __USE_GNU */

#ifdef __USE_MISC
#ifndef __struct_timezone_defined
#define __struct_timezone_defined 1
struct timezone {
	__INT32_TYPE__ tz_minuteswest; /* Minutes west of GMT. */
	__INT32_TYPE__ tz_dsttime;     /* Nonzero if DST is ever in effect. */
};
#endif /* !__struct_timezone_defined */
#endif /* __USE_MISC */

#ifndef ____timezone_ptr_t_defined
#define ____timezone_ptr_t_defined 1
#ifdef __USE_MISC
typedef struct timezone *__restrict __timezone_ptr_t;
#else /* __USE_MISC */
typedef void *__restrict __timezone_ptr_t;
#endif /* !__USE_MISC */
#endif /* !____timezone_ptr_t_defined */

}

%[define_replacement(__timezone_ptr_t = "void *")]
%[define_replacement(__itimer_which_t = int)]


[[doc_alias("gettimeofday"), ignore, nocrt, alias("gettimeofday", "__gettimeofday")]]
int gettimeofday32([[nonnull]] struct $timeval32 *__restrict tv,
                   [[nullable]] __timezone_ptr_t tz);

[[doc_alias("getitimer"), ignore, nocrt, alias("getitimer")]]
int getitimer32(__itimer_which_t which, [[nonnull]] struct $itimerval32 *curr_value);

[[doc_alias("setitimer"), ignore, nocrt, alias("setitimer")]]
int setitimer32(__itimer_which_t which,
                [[nonnull]] struct $itimerval32 const *__restrict newval,
                [[nullable]] struct $itimerval32 *__restrict oldval);

[[doc_alias("utimes"), ignore, nocrt, alias("utimes")]]
int utimes32([[nonnull]] char const *file, [[nonnull]] struct $timeval32 const tvp[2]);

[[doc_alias("futimesat"), ignore, nocrt, alias("futimesat")]]
int futimesat32($fd_t fd, [[nonnull]] char const *file, [[nonnull]] struct $timeval32 const tvp[2]);

[[doc_alias("settimeofday"), ignore, nocrt, alias("settimeofday")]]
int settimeofday32([[nullable]] struct $timeval32 const *tv, [[nullable]] struct timezone const *tz);

[[doc_alias("adjtime"), ignore, nocrt, alias("adjtime")]]
int adjtime32([[nullable]] struct $timeval32 const *delta, [[nullable]] struct $timeval32 *olddelta);

[[doc_alias("lutimes"), ignore, nocrt, alias("lutimes")]]
int lutimes32([[nonnull]] char const *file, [[nullable]] struct $timeval32 const tvp[2]);

[[doc_alias("lutimes"), ignore, nocrt, alias("futimes")]]
int futimes32($fd_t fd, [[nullable]] struct $timeval32 const tvp[2]);



@@Get the current time of day and timezone information,
@@putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
@@Returns 0 on success, -1 on errors.
@@NOTE: This form of timezone information is obsolete.
@@Use the functions and variables declared in <time.h> instead
[[section(".text.crt{|.dos}.time"), export_as("__gettimeofday"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("gettimeofday64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("gettimeofday", "__gettimeofday")]]
[[userimpl, requires($has_function(gettimeofday32) || $has_function(gettimeofday64))]]
int gettimeofday([[nonnull]] struct timeval *__restrict tv,
                 [[nullable]] __timezone_ptr_t tz) {
@@pp_if $has_function(gettimeofday32)@@
	int result;
	struct $timeval32 tv32;
	if (!tv)
		return gettimeofday32(NULL, tz);
	result = gettimeofday32(&tv32, tz);
	if likely(!result) {
		tv->tv_sec  = (time64_t)tv32.tv_sec;
		tv->tv_usec = tv32.tv_usec;
	}
	return result;
@@pp_else@@
	int result;
	struct $timeval64 tv64;
	if (!tv)
		return gettimeofday64(NULL, tz);
	result = gettimeofday64(&tv64, tz);
	if likely(!result) {
		tv->tv_sec  = (time32_t)tv64.tv_sec;
		tv->tv_usec = tv64.tv_usec;
	}
	return result;
@@pp_endif@@
}


@@Set *VALUE to the current setting of timer WHICH.
@@Return 0 on success, -1 on errors
[[section(".text.crt{|.dos}.time"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("getitimer64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("getitimer")]]
[[userimpl, requires($has_function(getitimer32) || $has_function(getitimer64))]]
int getitimer(__itimer_which_t which,
              [[nonnull]] struct itimerval *curr_value) {
@@pp_if $has_function(getitimer32)@@
	int result;
	struct $itimerval32 tv32;
	result = getitimer32(which, &tv32);
	if likely(!result) {
		curr_value->@it_interval@.tv_sec  = (time64_t)tv32.@it_interval@.tv_sec;
		curr_value->@it_interval@.tv_usec = tv32.@it_interval@.tv_usec;
		curr_value->@it_value@.tv_sec     = (time64_t)tv32.@it_value@.tv_sec;
		curr_value->@it_value@.tv_usec    = tv32.@it_value@.tv_usec;
	}
	return result;
@@pp_else@@
	int result;
	struct $timeval64 tv64;
	result = getitimer64(which, &tv64);
	if likely(!result) {
		curr_value->@it_interval@.tv_sec  = (time32_t)tv64.@it_interval@.tv_sec;
		curr_value->@it_interval@.tv_usec = tv64.@it_interval@.tv_usec;
		curr_value->@it_value@.tv_sec     = (time32_t)tv64.@it_value@.tv_sec;
		curr_value->@it_value@.tv_usec    = tv64.@it_value@.tv_usec;
	}
	return result;
@@pp_endif@@
}

@@Set the timer WHICH to *NEWVAL. If OLDVAL is not NULL, set *OLDVAL to the old value of timer WHICH.
@@Returns 0 on success, -1 on errors
[[section(".text.crt{|.dos}.time"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("setitimer64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("setitimer")]]
[[userimpl, requires($has_function(setitimer32) || $has_function(setitimer64))]]
int setitimer(__itimer_which_t which,
              [[nonnull]] struct itimerval const *newval,
              [[nullable]] struct itimerval *oldval) {
@@pp_if $has_function(setitimer32)@@
	int result;
	struct $itimerval32 new32, old32;
	new32.@it_interval@.tv_sec  = (time32_t)newval->@it_interval@.tv_sec;
	new32.@it_interval@.tv_usec = newval->@it_interval@.tv_usec;
	new32.@it_value@.tv_sec     = (time32_t)newval->@it_value@.tv_sec;
	new32.@it_value@.tv_usec    = newval->@it_value@.tv_usec;
	result = setitimer32(which, &new32, oldval ? &old32 : NULL);
	if (likely(!result) && oldval) {
		oldval->@it_interval@.tv_sec  = (time64_t)old32.@it_interval@.tv_sec;
		oldval->@it_interval@.tv_usec = old32.@it_interval@.tv_usec;
		oldval->@it_value@.tv_sec     = (time64_t)old32.@it_value@.tv_sec;
		oldval->@it_value@.tv_usec    = old32.@it_value@.tv_usec;
	}
	return result;
@@pp_else@@
	int result;
	struct $itimerval64 new64, old64;
	new64.@it_interval@.tv_sec  = (time64_t)newval->@it_interval@.tv_sec;
	new64.@it_interval@.tv_usec = newval->@it_interval@.tv_usec;
	new64.@it_value@.tv_sec     = (time64_t)newval->@it_value@.tv_sec;
	new64.@it_value@.tv_usec    = newval->@it_value@.tv_usec;
	result = setitimer64(which, &new64, oldval ? &old64 : NULL);
	if (likely(!result) && oldval) {
		oldval->@it_interval@.tv_sec  = (time32_t)old64.@it_interval@.tv_sec;
		oldval->@it_interval@.tv_usec = old64.@it_interval@.tv_usec;
		oldval->@it_value@.tv_sec     = (time32_t)old64.@it_value@.tv_sec;
		oldval->@it_value@.tv_usec    = old64.@it_value@.tv_usec;
	}
	return result;
@@pp_endif@@
}


@@Change the access time of FILE to TVP[0] and the modification time of
@@FILE to TVP[1]. If TVP is a null pointer, use the current time instead.
@@Returns 0 on success, -1 on errors
[[section(".text.crt{|.dos}.fs.modify_time"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("utimes64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("utimes")]]
[[userimpl, requires($has_function(utimes32) || $has_function(utimes64))]]
int utimes([[nonnull]] char const *file,
           [[nullable]] struct timeval const tvp[2]) {
@@pp_if $has_function(utimes32)@@
	struct $timeval32 tv32[2];
	if (!tvp)
		return utimes32(file, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return utimes32(file, tv32);
@@pp_else@@
	struct $timeval64 tv64[2];
	if (!tvp)
		return utimes64(file, NULL);
	tv64[0].tv_sec  = (time64_t)tvp[0].tv_sec;
	tv64[0].tv_usec = tvp[0].tv_usec;
	tv64[1].tv_sec  = (time64_t)tvp[1].tv_sec;
	tv64[1].tv_usec = tvp[1].tv_usec;
	return utimes64(file, tv64);
@@pp_endif@@
}

%
%#ifdef __USE_GNU
@@Same as `utimes', but takes an open file descriptor instead of a name
[[section(".text.crt{|.dos}.fs.modify_time"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("futimesat64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("futimesat")]]
[[userimpl, requires($has_function(futimesat32) || $has_function(futimesat64))]]
int futimesat($fd_t fd, [[nonnull]] char const *file,
              [[nullable]] struct timeval const tvp[2]) {
@@pp_if $has_function(utimes32)@@
	struct $timeval32 tv32[2];
	if (!tvp)
		return futimesat32(fd, file, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return futimesat32(fd, file, tv32);
@@pp_else@@
	struct $timeval64 tv64[2];
	if (!tvp)
		return futimesat64(fd, file, NULL);
	tv64[0].tv_sec  = (time64_t)tvp[0].tv_sec;
	tv64[0].tv_usec = tvp[0].tv_usec;
	tv64[1].tv_sec  = (time64_t)tvp[1].tv_sec;
	tv64[1].tv_usec = tvp[1].tv_usec;
	return futimesat64(fd, file, tv64);
@@pp_endif@@
}
%#endif /* __USE_GNU */

%
%#ifdef __USE_MISC
@@Set the current time of day and timezone information.
@@This call is restricted to the super-user
[[section(".text.crt{|.dos}.system.adjtime"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("settimeofday64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("settimeofday")]]
[[userimpl, requires($has_function(settimeofday32) || $has_function(settimeofday64))]]
int settimeofday([[nullable]] struct timeval const *tv,
                 [[nullable]] struct timezone const *tz) {
@@pp_if $has_function(settimeofday32)@@
	struct $timeval32 tv32;
	if (!tv)
		return settimeofday32(NULL, tz);
	tv32.tv_sec  = (time32_t)tv->tv_sec;
	tv32.tv_usec = tv->tv_usec;
	return settimeofday32(&tv32, tz);
@@pp_else@@
	struct $timeval64 tv64;
	if (!tv)
		return settimeofday64(NULL, tz);
	tv64.tv_sec  = (time64_t)tv->tv_sec;
	tv64.tv_usec = tv->tv_usec;
	return settimeofday64(&tv64, tz);
@@pp_endif@@
}

@@Adjust the current time of day by the amount in DELTA.
@@If OLDDELTA is not NULL, it is filled in with the amount of time
@@adjustment remaining to be done from the last `adjtime' call.
@@This call is restricted to the super-user
[[section(".text.crt{|.dos}.system.adjtime"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("adjtime64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("adjtime")]]
[[userimpl, requires($has_function(adjtime32) || $has_function(adjtime64))]]
int adjtime([[nullable]] struct timeval const *delta,
            [[nullable]] struct timeval *olddelta) {
@@pp_if $has_function(adjtime32)@@
	int result;
	struct $timeval32 delta32, olddelta32;
	if (delta) {
		delta32.tv_sec  = (time32_t)delta->tv_sec;
		delta32.tv_usec = delta->tv_usec;
	}
	result = adjtime32(which, delta ? &delta32 : NULL, olddelta ? &olddelta32 : NULL);
	if (likely(!result) && olddelta) {
		olddelta->tv_sec  = (time64_t)olddelta32.tv_sec;
		olddelta->tv_usec = olddelta32.tv_usec;
	}
	return result;
@@pp_else@@
	int result;
	struct $timeval64 delta64, olddelta64;
	if (delta) {
		delta64.tv_sec  = (time64_t)delta->tv_sec;
		delta64.tv_usec = delta->tv_usec;
	}
	result = adjtime64(which, delta ? &delta64 : NULL, olddelta ? &olddelta64 : NULL);
	if (likely(!result) && olddelta) {
		olddelta->tv_sec  = (time32_t)olddelta64.tv_sec;
		olddelta->tv_usec = olddelta64.tv_usec;
	}
	return result;
@@pp_endif@@
}

@@Same as `utimes', but does not follow symbolic links
[[section(".text.crt{|.dos}.fs.modify_time"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("lutimes64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("lutimes")]]
[[userimpl, requires($has_function(lutimes32) || $has_function(lutimes64))]]
int lutimes([[nonnull]] char const *file,
            [[nullable]] struct timeval const tvp[2]) {
@@pp_if $has_function(utimes32)@@
	struct $timeval32 tv32[2];
	if (!tvp)
		return lutimes32(file, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return lutimes32(file, tv32);
@@pp_else@@
	struct $timeval64 tv64[2];
	if (!tvp)
		return lutimes64(file, NULL);
	tv64[0].tv_sec  = (time64_t)tvp[0].tv_sec;
	tv64[0].tv_usec = tvp[0].tv_usec;
	tv64[1].tv_sec  = (time64_t)tvp[1].tv_sec;
	tv64[1].tv_usec = tvp[1].tv_usec;
	return lutimes64(file, tv64);
@@pp_endif@@
}


@@Same as `utimes', but takes an open file descriptor instead of a name
[[section(".text.crt{|.dos}.fs.modify_time"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("futimes64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("futimes")]]
[[userimpl, requires($has_function(futimes32) || $has_function(futimes64))]]
int futimes($fd_t fd, [[nullable]] struct timeval const tvp[2]) {
@@pp_if $has_function(futimes32)@@
	struct $timeval32 tv32[2];
	if (!tvp)
		return futimes32(fd, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return futimes32(fd, tv32);
@@pp_else@@
	struct $timeval64 tv64[2];
	if (!tvp)
		return futimes64(fd, NULL);
	tv64[0].tv_sec  = (time64_t)tvp[0].tv_sec;
	tv64[0].tv_usec = tvp[0].tv_usec;
	tv64[1].tv_sec  = (time64_t)tvp[1].tv_sec;
	tv64[1].tv_usec = tvp[1].tv_usec;
	return futimes64(fd, tv64);
@@pp_endif@@
}

%#endif /* __USE_MISC */

%
%#ifdef __USE_TIME64
[[doc_alias("gettimeofday"), time64_variant_of(gettimeofday), section(".text.crt{|.dos}.time")]]
[[userimpl, requires_function(gettimeofday32)]]
int gettimeofday64([[nonnull]] struct timeval64 *__restrict tv,
                   [[nullable]] __timezone_ptr_t tz) {
	int result;
	struct $timeval32 tv32;
	if (!tv)
		return gettimeofday32(NULL, tz);
	result = gettimeofday32(&tv32, tz);
	if likely(!result) {
		tv->tv_sec  = (time64_t)tv32.tv_sec;
		tv->tv_usec = tv32.tv_usec;
	}
	return result;
}

[[doc_alias("getitimer"), time64_variant_of(getitimer), section(".text.crt{|.dos}.time")]]
[[userimpl, requires_function(getitimer32)]]
int getitimer64(__itimer_which_t which,
                [[nonnull]] struct itimerval64 *curr_value) {
	int result;
	struct $itimerval32 tv32;
	result = getitimer32(which, &tv32);
	if likely(!result) {
		curr_value->@it_interval@.tv_sec  = (time64_t)tv32.@it_interval@.tv_sec;
		curr_value->@it_interval@.tv_usec = tv32.@it_interval@.tv_usec;
		curr_value->@it_value@.tv_sec     = (time64_t)tv32.@it_value@.tv_sec;
		curr_value->@it_value@.tv_usec    = tv32.@it_value@.tv_usec;
	}
	return result;
}

[[doc_alias("setitimer"), time64_variant_of(setitimer), section(".text.crt{|.dos}.time")]]
[[userimpl, requires_function(setitimer32)]]
int setitimer64(__itimer_which_t which,
                [[nonnull]] struct itimerval64 const *newval,
                [[nullable]] struct itimerval64 *oldval) {
	int result;
	struct $itimerval32 new32, old32;
	new32.@it_interval@.tv_sec  = (time32_t)newval->@it_interval@.tv_sec;
	new32.@it_interval@.tv_usec = newval->@it_interval@.tv_usec;
	new32.@it_value@.tv_sec     = (time32_t)newval->@it_value@.tv_sec;
	new32.@it_value@.tv_usec    = newval->@it_value@.tv_usec;
	result = setitimer32(which, &new32, oldval ? &old32 : NULL);
	if (likely(!result) && oldval) {
		oldval->@it_interval@.tv_sec  = (time64_t)old32.@it_interval@.tv_sec;
		oldval->@it_interval@.tv_usec = old32.@it_interval@.tv_usec;
		oldval->@it_value@.tv_sec     = (time64_t)old32.@it_value@.tv_sec;
		oldval->@it_value@.tv_usec    = old32.@it_value@.tv_usec;
	}
	return result;
}


[[doc_alias("utimes"), time64_variant_of(utimes), section(".text.crt{|.dos}.fs.modify_time")]]
[[userimpl, requires_function(utimes32)]]
int utimes64([[nonnull]] char const *file,
             [[nullable]] struct timeval64 const tvp[2]) {
	struct $timeval32 tv32[2];
	if (!tvp)
		return utimes32(file, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return utimes32(file, tv32);
}

%
%#ifdef __USE_MISC
[[doc_alias("settimeofday"), time64_variant_of(settimeofday), section(".text.crt{|.dos}.system.adjtime")]]
[[userimpl, requires_function(settimeofday32)]]
int settimeofday64([[nullable]] struct timeval64 const *tv,
                   [[nullable]] struct timezone const *tz) {
	struct $timeval32 tv32;
	if (!tv)
		return settimeofday32(NULL, tz);
	tv32.tv_sec  = (time32_t)tv->tv_sec;
	tv32.tv_usec = tv->tv_usec;
	return settimeofday32(&tv32, tz);
}

[[doc_alias("adjtime"), time64_variant_of(adjtime), section(".text.crt{|.dos}.system.adjtime")]]
[[userimpl, requires_function(adjtime32)]]
int adjtime64([[nullable]] struct timeval64 const *delta,
              [[nullable]] struct timeval64 *olddelta) {
	int result;
	struct $timeval32 delta32, olddelta32;
	if (delta) {
		delta32.tv_sec  = (time32_t)delta->tv_sec;
		delta32.tv_usec = delta->tv_usec;
	}
	result = adjtime32(which, delta ? &delta32 : NULL, olddelta ? &olddelta32 : NULL);
	if (likely(!result) && olddelta) {
		olddelta->tv_sec  = (time64_t)olddelta32.tv_sec;
		olddelta->tv_usec = olddelta32.tv_usec;
	}
	return result;
}

[[doc_alias("lutimes"), time64_variant_of(lutimes), section(".text.crt{|.dos}.fs.modify_time")]]
[[userimpl, requires_function(lutimes32)]]
int lutimes64([[nonnull]] char const *file,
              [[nullable]] struct timeval64 const tvp[2]) {
	struct $timeval32 tv32[2];
	if (!tvp)
		return lutimes32(file, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return lutimes32(file, tv32);
}


[[doc_alias("lutimes"), time64_variant_of(lutimes), section(".text.crt{|.dos}.fs.modify_time")]]
[[userimpl, requires_function(futimes32)]]
int futimes64($fd_t fd, [[nullable]] struct timeval64 const tvp[2]) {
	struct $timeval32 tv32[2];
	if (!tvp)
		return futimes32(fd, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return futimes32(fd, tv32);
}

%#endif /* __USE_MISC */

%
%#ifdef __USE_GNU
[[doc_alias("futimesat"), time64_variant_of(futimesat), section(".text.crt{|.dos}.fs.modify_time")]]
[[userimpl, requires_function(futimesat32)]]
int futimesat64($fd_t fd, [[nonnull]] char const *file,
                [[nullable]] struct timeval64 const tvp[2]) {
	struct $timeval32 tv32[2];
	if (!tvp)
		return futimesat32(fd, file, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return futimesat32(fd, file, tv32);
}
%#endif /* __USE_GNU */
%#endif /* __USE_TIME64 */


%{

#ifdef __USE_MISC
#undef timerisset
#undef timerclear
#undef timercmp
#define timerisset(tvp) ((tvp)->tv_sec || (tvp)->tv_usec)
#define timerclear(tvp) ((tvp)->tv_sec = (tvp)->tv_usec = 0)
#define timercmp(a, b, CMP)           \
	(((a)->tv_sec == (b)->tv_sec)     \
	 ? ((a)->tv_usec CMP(b)->tv_usec) \
	 : ((a)->tv_sec CMP(b)->tv_sec))
#define timeradd(a, b, result)                           \
	do {                                                 \
		(result)->tv_sec  = (a)->tv_sec + (b)->tv_sec;   \
		(result)->tv_usec = (a)->tv_usec + (b)->tv_usec; \
		if ((result)->tv_usec >= 1000000) {              \
			++(result)->tv_sec;                          \
			(result)->tv_usec -= 1000000;                \
		}                                                \
	} __WHILE0
#define timersub(a, b, result)                           \
	do {                                                 \
		(result)->tv_sec  = (a)->tv_sec - (b)->tv_sec;   \
		(result)->tv_usec = (a)->tv_usec - (b)->tv_usec; \
		if ((result)->tv_usec < 0) {                     \
			--(result)->tv_sec;                          \
			(result)->tv_usec += 1000000;                \
		}                                                \
	} __WHILE0
#endif /* __USE_MISC */

#endif /* __CC__ */

__SYSDECL_END

}
