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

%[define_replacement(fd_t         = __fd_t)]
%[define_replacement(time_t       = "__TM_TYPE(time)")]
%[define_replacement(time32_t     = __time32_t)]
%[define_replacement(time64_t     = __time64_t)]
%[define_replacement(timespec32   = __timespec32)]
%[define_replacement(timespec64   = __timespec64)]
%[define_replacement(timeval32    = __timeval32)]
%[define_replacement(timeval64    = __timeval64)]
%[define_replacement(ntptimeval32 = __ntptimeval32)]
%[define_replacement(ntptimeval64 = __ntptimeval64)]
%[define_replacement(timex32      = __timex32)]
%[define_replacement(timex64      = __timex64)]


%{
#include <features.h>

#include <bits/timex.h>
#include <bits/types.h>
#include <sys/time.h>

	/* Documentation taken from /usr/include/i386-linux-gnu/sys/timex.h */
/* Copyright (C) 1995-2016 Free Software Foundation, Inc.
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

#define NTP_API  4 /* NTP API version */

/* Clock states (time_state) */
#define TIME_OK     0          /* clock synchronized, no leap second */
#define TIME_INS    1          /* insert leap second */
#define TIME_DEL    2          /* delete leap second */
#define TIME_OOP    3          /* leap second in progress */
#define TIME_WAIT   4          /* leap second has occurred */
#define TIME_ERROR  5          /* clock not synchronized */
#define TIME_BAD    TIME_ERROR /* bw compat */

/* Maximum time constant of the PLL.  */
#define MAXTC       6


__SYSDECL_BEGIN

#ifdef __CC__

#if __TM_SIZEOF(TIME) <= 4
#define __ntptimeval64   __ntptimeval_alt
#define __ntptimeval32   ntptimeval
#else /* __TM_SIZEOF(TIME) <= 4 */
#define __ntptimeval64   ntptimeval
#define __ntptimeval32   __ntptimeval_alt
#endif /* __TM_SIZEOF(TIME) > 4 */

#ifdef __USE_TIME64
#if __TM_SIZEOF(TIME) <= 4
#define __ntptimeval_alt ntptimeval64
#else /* __TM_SIZEOF(TIME) <= 4 */
#define ntptimeval64     ntptimeval
#endif /* __TM_SIZEOF(TIME) > 4 */
#endif /* __USE_TIME64 */

#ifdef __USE_KOS
#if __TM_SIZEOF(TIME) <= 4
#define ntptimeval32 ntptimeval
#else /* __TM_SIZEOF(TIME) <= 4 */
#define ntptimeval32 __ntptimeval_alt
#endif /* __TM_SIZEOF(TIME) > 4 */
#endif /* __USE_KOS */

}%[push_macro @undef { time maxerror esterror tai }]%{
struct ntptimeval {
	struct timeval       time;            /* current time (ro) */
	__LONGPTR_TYPE__     maxerror;        /* maximum error (us) (ro) */
	__LONGPTR_TYPE__     esterror;        /* estimated error (us) (ro) */
	__LONGPTR_TYPE__     tai;             /* TAI offset (ro) */
	__LONGPTR_TYPE__   __glibc_reserved1; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved2; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved3; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved4; /* ... */
};
struct __ntptimeval_alt {
	struct __timeval_alt time;            /* current time (ro) */
	__LONGPTR_TYPE__     maxerror;        /* maximum error (us) (ro) */
	__LONGPTR_TYPE__     esterror;        /* estimated error (us) (ro) */
	__LONGPTR_TYPE__     tai;             /* TAI offset (ro) */
	__LONGPTR_TYPE__   __glibc_reserved1; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved2; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved3; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved4; /* ... */
};
}%[pop_macro]%{

}

[[ignore, nocrt, alias("adjtimex", "__adjtimex")]]
int adjtimex32([[nonnull]] struct $timex32 *__restrict __ntx);

[[ignore, nocrt, alias("ntp_gettimex")]]
int ntp_gettime32([[nonnull]] struct $ntptimeval32 *__restrict ntv);

[[ignore, nocrt, alias("ntp_adjtime")]]
int ntp_adjtime32([[nonnull]] struct $timex32 *__restrict tntx);



%[insert:function(__adjtimex = adjtimex)]

[[export_as("__adjtimex"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("adjtimex64", "__adjtimex64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("adjtimex", "__adjtimex")]]
[[userimpl, requires($has_function(adjtimex32) || $has_function(adjtimex64))]]
int adjtimex([[nonnull]] struct timex *__restrict ntx) {
	int result;
@@pp_if $has_function(adjtimex32)@@
	struct $timex32 nxtalt;
	nxtalt.@time@.tv_sec  = (time32_t)ntx->@time@.tv_sec;
	nxtalt.@time@.tv_usec = ntx->@time@.tv_usec;
	nxtalt.@offset@       = (time32_t)ntx->@offset@;
	nxtalt.@freq@         = (time32_t)ntx->@freq@;
	nxtalt.@maxerror@     = (time32_t)ntx->@maxerror@;
	nxtalt.@esterror@     = (time32_t)ntx->@esterror@;
	nxtalt.@constant@     = (time32_t)ntx->@constant@;
/*	nxtalt.@precision@    = (time32_t)ntx->@precision@; */
/*	nxtalt.@tolerance@    = (time32_t)ntx->@tolerance@; */
	nxtalt.@tick@         = (time32_t)ntx->@tick@;
/*	nxtalt.@ppsfreq@      = (time32_t)ntx->@ppsfreq@; */
/*	nxtalt.@jitter@       = (time32_t)ntx->@jitter@; */
/*	nxtalt.@shift@        = (time32_t)ntx->@shift@; */
/*	nxtalt.@stabil@       = (time32_t)ntx->@stabil@; */
/*	nxtalt.@jitcnt@       = (time32_t)ntx->@jitcnt@; */
/*	nxtalt.@calcnt@       = (time32_t)ntx->@calcnt@; */
/*	nxtalt.@errcnt@       = (time32_t)ntx->@errcnt@; */
/*	nxtalt.@stbcnt@       = (time32_t)ntx->@stbcnt@; */
/*	nxtalt.@tai@          = (time32_t)ntx->@tai@; */
@@pp_else@@
	struct $timex64 nxtalt;
	nxtalt.@time@.tv_sec  = (time64_t)ntx->@time@.tv_sec;
	nxtalt.@time@.tv_usec = ntx->@time@.tv_usec;
	nxtalt.@offset@       = (time64_t)ntx->@offset@;
	nxtalt.@freq@         = (time64_t)ntx->@freq@;
	nxtalt.@maxerror@     = (time64_t)ntx->@maxerror@;
	nxtalt.@esterror@     = (time64_t)ntx->@esterror@;
	nxtalt.@constant@     = (time64_t)ntx->@constant@;
/*	nxtalt.@precision@    = (time64_t)ntx->@precision@; */
/*	nxtalt.@tolerance@    = (time64_t)ntx->@tolerance@; */
	nxtalt.@tick@         = (time64_t)ntx->@tick@;
/*	nxtalt.@ppsfreq@      = (time64_t)ntx->@ppsfreq@; */
/*	nxtalt.@jitter@       = (time64_t)ntx->@jitter@; */
/*	nxtalt.@shift@        = (time64_t)ntx->@shift@; */
/*	nxtalt.@stabil@       = (time64_t)ntx->@stabil@; */
/*	nxtalt.@jitcnt@       = (time64_t)ntx->@jitcnt@; */
/*	nxtalt.@calcnt@       = (time64_t)ntx->@calcnt@; */
/*	nxtalt.@errcnt@       = (time64_t)ntx->@errcnt@; */
/*	nxtalt.@stbcnt@       = (time64_t)ntx->@stbcnt@; */
/*	nxtalt.@tai@          = (time64_t)ntx->@tai@; */
@@pp_endif@@
	nxtalt.@modes@  = ntx->@modes@;
	nxtalt.@status@ = ntx->@status@;
@@pp_if $has_function(adjtimex32)@@
	result = adjtimex32(&nxtalt);
@@pp_else@@
	result = adjtimex64(&nxtalt);
@@pp_endif@@
	if likely(result == 0) {
@@pp_if $has_function(adjtimex32)@@
		ntx->@time@.tv_sec  = (time64_t)nxtalt.@time@.tv_sec;
		ntx->@time@.tv_usec = nxtalt.@time@.tv_usec;
		ntx->@offset@       = (time64_t)nxtalt.@offset@;
		ntx->@freq@         = (time64_t)nxtalt.@freq@;
		ntx->@maxerror@     = (time64_t)nxtalt.@maxerror@;
		ntx->@esterror@     = (time64_t)nxtalt.@esterror@;
		ntx->@constant@     = (time64_t)nxtalt.@constant@;
		ntx->@precision@    = (time64_t)nxtalt.@precision@;
		ntx->@tolerance@    = (time64_t)nxtalt.@tolerance@;
		ntx->@tick@         = (time64_t)nxtalt.@tick@;
		ntx->@ppsfreq@      = (time64_t)nxtalt.@ppsfreq@;
		ntx->@jitter@       = (time64_t)nxtalt.@jitter@;
		ntx->@shift@        = (time64_t)nxtalt.@shift@;
		ntx->@stabil@       = (time64_t)nxtalt.@stabil@;
		ntx->@jitcnt@       = (time64_t)nxtalt.@jitcnt@;
		ntx->@calcnt@       = (time64_t)nxtalt.@calcnt@;
		ntx->@errcnt@       = (time64_t)nxtalt.@errcnt@;
		ntx->@stbcnt@       = (time64_t)nxtalt.@stbcnt@;
		ntx->@tai@          = (time64_t)nxtalt.@tai@;
@@pp_else@@
		ntx->@time@.tv_sec  = (time32_t)nxtalt.@time@.tv_sec;
		ntx->@time@.tv_usec = nxtalt.@time@.tv_usec;
		ntx->@offset@       = (time32_t)nxtalt.@offset@;
		ntx->@freq@         = (time32_t)nxtalt.@freq@;
		ntx->@maxerror@     = (time32_t)nxtalt.@maxerror@;
		ntx->@esterror@     = (time32_t)nxtalt.@esterror@;
		ntx->@constant@     = (time32_t)nxtalt.@constant@;
		ntx->@precision@    = (time32_t)nxtalt.@precision@;
		ntx->@tolerance@    = (time32_t)nxtalt.@tolerance@;
		ntx->@tick@         = (time32_t)nxtalt.@tick@;
		ntx->@ppsfreq@      = (time32_t)nxtalt.@ppsfreq@;
		ntx->@jitter@       = (time32_t)nxtalt.@jitter@;
		ntx->@shift@        = (time32_t)nxtalt.@shift@;
		ntx->@stabil@       = (time32_t)nxtalt.@stabil@;
		ntx->@jitcnt@       = (time32_t)nxtalt.@jitcnt@;
		ntx->@calcnt@       = (time32_t)nxtalt.@calcnt@;
		ntx->@errcnt@       = (time32_t)nxtalt.@errcnt@;
		ntx->@stbcnt@       = (time32_t)nxtalt.@stbcnt@;
		ntx->@tai@          = (time32_t)nxtalt.@tai@;
@@pp_endif@@
		ntx->@modes@  = nxtalt.@modes@;
		ntx->@status@ = nxtalt.@status@;
	}
	return result;
}


[[crt_name("ntp_gettimex"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("ntp_gettimex64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("ntp_gettimex")]]
[[userimpl, requires($has_function(ntp_gettime32) || $has_function(ntp_gettime64))]]
int ntp_gettime([[nonnull]] struct ntptimeval *__restrict ntv) {
@@pp_if $has_function(ntp_gettime32)@@
	struct $ntptimeval32 ntv32;
	int result = ntp_gettime32(&ntv32);
	if likely(result == 0) {
		ntv->@time@.tv_sec       = (time64_t)ntv32.@time@.tv_sec;
		ntv->@time@.tv_usec      = ntv32.@time@.tv_usec;
		ntv->@maxerror@          = ntv32.@maxerror@;
		ntv->@esterror@          = ntv32.@esterror@;
		ntv->@tai@               = ntv32.@tai@;
		ntv->@__glibc_reserved1@ = ntv32.@__glibc_reserved1@;
		ntv->@__glibc_reserved2@ = ntv32.@__glibc_reserved2@;
		ntv->@__glibc_reserved3@ = ntv32.@__glibc_reserved3@;
		ntv->@__glibc_reserved4@ = ntv32.@__glibc_reserved4@;
	}
	return result;
@@pp_else@@
	struct $ntptimeval64 ntv64;
	int result = ntp_gettime64(&ntv64);
	if likely(result == 0) {
		ntv->@time@.tv_sec       = (time32_t)ntv64.@time@.tv_sec;
		ntv->@time@.tv_usec      = ntv64.@time@.tv_usec;
		ntv->@maxerror@          = ntv64.@maxerror@;
		ntv->@esterror@          = ntv64.@esterror@;
		ntv->@tai@               = ntv64.@tai@;
		ntv->@__glibc_reserved1@ = ntv64.@__glibc_reserved1@;
		ntv->@__glibc_reserved2@ = ntv64.@__glibc_reserved2@;
		ntv->@__glibc_reserved3@ = ntv64.@__glibc_reserved3@;
		ntv->@__glibc_reserved4@ = ntv64.@__glibc_reserved4@;
	}
	return result;
@@pp_endif@@
}

[[no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("ntp_adjtime64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("ntp_adjtime")]]
[[userimpl, requires($has_function(ntp_adjtime32) || $has_function(ntp_adjtime64))]]
int ntp_adjtime([[nonnull]] struct timex *__restrict tntx) {
	int result;
@@pp_if $has_function(ntp_adjtime32)@@
	struct $timex32 nxtalt;
	nxtalt.@time@.tv_sec  = (time32_t)ntx->@time@.tv_sec;
	nxtalt.@time@.tv_usec = ntx->@time@.tv_usec;
	nxtalt.@offset@       = (time32_t)ntx->@offset@;
	nxtalt.@freq@         = (time32_t)ntx->@freq@;
	nxtalt.@maxerror@     = (time32_t)ntx->@maxerror@;
	nxtalt.@esterror@     = (time32_t)ntx->@esterror@;
	nxtalt.@constant@     = (time32_t)ntx->@constant@;
/*	nxtalt.@precision@    = (time32_t)ntx->@precision@; */
/*	nxtalt.@tolerance@    = (time32_t)ntx->@tolerance@; */
	nxtalt.@tick@         = (time32_t)ntx->@tick@;
/*	nxtalt.@ppsfreq@      = (time32_t)ntx->@ppsfreq@; */
/*	nxtalt.@jitter@       = (time32_t)ntx->@jitter@; */
/*	nxtalt.@shift@        = (time32_t)ntx->@shift@; */
/*	nxtalt.@stabil@       = (time32_t)ntx->@stabil@; */
/*	nxtalt.@jitcnt@       = (time32_t)ntx->@jitcnt@; */
/*	nxtalt.@calcnt@       = (time32_t)ntx->@calcnt@; */
/*	nxtalt.@errcnt@       = (time32_t)ntx->@errcnt@; */
/*	nxtalt.@stbcnt@       = (time32_t)ntx->@stbcnt@; */
/*	nxtalt.@tai@          = (time32_t)ntx->@tai@; */
@@pp_else@@
	struct $timex64 nxtalt;
	nxtalt.@time@.tv_sec  = (time64_t)ntx->@time@.tv_sec;
	nxtalt.@time@.tv_usec = ntx->@time@.tv_usec;
	nxtalt.@offset@       = (time64_t)ntx->@offset@;
	nxtalt.@freq@         = (time64_t)ntx->@freq@;
	nxtalt.@maxerror@     = (time64_t)ntx->@maxerror@;
	nxtalt.@esterror@     = (time64_t)ntx->@esterror@;
	nxtalt.@constant@     = (time64_t)ntx->@constant@;
/*	nxtalt.@precision@    = (time64_t)ntx->@precision@; */
/*	nxtalt.@tolerance@    = (time64_t)ntx->@tolerance@; */
	nxtalt.@tick@         = (time64_t)ntx->@tick@;
/*	nxtalt.@ppsfreq@      = (time64_t)ntx->@ppsfreq@; */
/*	nxtalt.@jitter@       = (time64_t)ntx->@jitter@; */
/*	nxtalt.@shift@        = (time64_t)ntx->@shift@; */
/*	nxtalt.@stabil@       = (time64_t)ntx->@stabil@; */
/*	nxtalt.@jitcnt@       = (time64_t)ntx->@jitcnt@; */
/*	nxtalt.@calcnt@       = (time64_t)ntx->@calcnt@; */
/*	nxtalt.@errcnt@       = (time64_t)ntx->@errcnt@; */
/*	nxtalt.@stbcnt@       = (time64_t)ntx->@stbcnt@; */
/*	nxtalt.@tai@          = (time64_t)ntx->@tai@; */
@@pp_endif@@
	nxtalt.@modes@  = ntx->@modes@;
	nxtalt.@status@ = ntx->@status@;
@@pp_if $has_function(ntp_adjtime32)@@
	result = ntp_adjtime32(&nxtalt);
@@pp_else@@
	result = ntp_adjtime64(&nxtalt);
@@pp_endif@@
	if likely(result == 0) {
@@pp_if $has_function(ntp_adjtime32)@@
		ntx->@time@.tv_sec  = (time64_t)nxtalt.@time@.tv_sec;
		ntx->@time@.tv_usec = nxtalt.@time@.tv_usec;
		ntx->@offset@       = (time64_t)nxtalt.@offset@;
		ntx->@freq@         = (time64_t)nxtalt.@freq@;
		ntx->@maxerror@     = (time64_t)nxtalt.@maxerror@;
		ntx->@esterror@     = (time64_t)nxtalt.@esterror@;
		ntx->@constant@     = (time64_t)nxtalt.@constant@;
		ntx->@precision@    = (time64_t)nxtalt.@precision@;
		ntx->@tolerance@    = (time64_t)nxtalt.@tolerance@;
		ntx->@tick@         = (time64_t)nxtalt.@tick@;
		ntx->@ppsfreq@      = (time64_t)nxtalt.@ppsfreq@;
		ntx->@jitter@       = (time64_t)nxtalt.@jitter@;
		ntx->@shift@        = (time64_t)nxtalt.@shift@;
		ntx->@stabil@       = (time64_t)nxtalt.@stabil@;
		ntx->@jitcnt@       = (time64_t)nxtalt.@jitcnt@;
		ntx->@calcnt@       = (time64_t)nxtalt.@calcnt@;
		ntx->@errcnt@       = (time64_t)nxtalt.@errcnt@;
		ntx->@stbcnt@       = (time64_t)nxtalt.@stbcnt@;
		ntx->@tai@          = (time64_t)nxtalt.@tai@;
@@pp_else@@
		ntx->@time@.tv_sec  = (time32_t)nxtalt.@time@.tv_sec;
		ntx->@time@.tv_usec = nxtalt.@time@.tv_usec;
		ntx->@offset@       = (time32_t)nxtalt.@offset@;
		ntx->@freq@         = (time32_t)nxtalt.@freq@;
		ntx->@maxerror@     = (time32_t)nxtalt.@maxerror@;
		ntx->@esterror@     = (time32_t)nxtalt.@esterror@;
		ntx->@constant@     = (time32_t)nxtalt.@constant@;
		ntx->@precision@    = (time32_t)nxtalt.@precision@;
		ntx->@tolerance@    = (time32_t)nxtalt.@tolerance@;
		ntx->@tick@         = (time32_t)nxtalt.@tick@;
		ntx->@ppsfreq@      = (time32_t)nxtalt.@ppsfreq@;
		ntx->@jitter@       = (time32_t)nxtalt.@jitter@;
		ntx->@shift@        = (time32_t)nxtalt.@shift@;
		ntx->@stabil@       = (time32_t)nxtalt.@stabil@;
		ntx->@jitcnt@       = (time32_t)nxtalt.@jitcnt@;
		ntx->@calcnt@       = (time32_t)nxtalt.@calcnt@;
		ntx->@errcnt@       = (time32_t)nxtalt.@errcnt@;
		ntx->@stbcnt@       = (time32_t)nxtalt.@stbcnt@;
		ntx->@tai@          = (time32_t)nxtalt.@tai@;
@@pp_endif@@
		ntx->@modes@  = nxtalt.@modes@;
		ntx->@status@ = nxtalt.@status@;
	}
	return result;
}

%
%#ifdef __USE_TIME64
[[export_alias("__adjtimex64"), time64_variant_of(adjtimex)]]
[[userimpl, requires_function(adjtimex32)]]
int adjtimex64([[nonnull]] struct timex64 *__restrict ntx) {
	int result;
	struct $timex32 nxtalt;
	nxtalt.@time@.tv_sec  = (time32_t)ntx->@time@.tv_sec;
	nxtalt.@time@.tv_usec = ntx->@time@.tv_usec;
	nxtalt.@modes@        = ntx->@modes@;
	nxtalt.@offset@       = (time32_t)ntx->@offset@;
	nxtalt.@freq@         = (time32_t)ntx->@freq@;
	nxtalt.@maxerror@     = (time32_t)ntx->@maxerror@;
	nxtalt.@esterror@     = (time32_t)ntx->@esterror@;
	nxtalt.@status@       = ntx->@status@;
	nxtalt.@constant@     = (time32_t)ntx->@constant@;
/*	nxtalt.@precision@    = (time32_t)ntx->@precision@; */
/*	nxtalt.@tolerance@    = (time32_t)ntx->@tolerance@; */
	nxtalt.@tick@         = (time32_t)ntx->@tick@;
/*	nxtalt.@ppsfreq@      = (time32_t)ntx->@ppsfreq@; */
/*	nxtalt.@jitter@       = (time32_t)ntx->@jitter@; */
/*	nxtalt.@shift@        = (time32_t)ntx->@shift@; */
/*	nxtalt.@stabil@       = (time32_t)ntx->@stabil@; */
/*	nxtalt.@jitcnt@       = (time32_t)ntx->@jitcnt@; */
/*	nxtalt.@calcnt@       = (time32_t)ntx->@calcnt@; */
/*	nxtalt.@errcnt@       = (time32_t)ntx->@errcnt@; */
/*	nxtalt.@stbcnt@       = (time32_t)ntx->@stbcnt@; */
/*	nxtalt.@tai@          = (time32_t)ntx->@tai@; */
	result = adjtimex32(&nxtalt);
	if likely(result == 0) {
		ntx->@time@.tv_sec  = (time64_t)nxtalt.@time@.tv_sec;
		ntx->@time@.tv_usec = nxtalt.@time@.tv_usec;
		ntx->@modes@        = nxtalt.@modes@;
		ntx->@offset@       = (time64_t)nxtalt.@offset@;
		ntx->@freq@         = (time64_t)nxtalt.@freq@;
		ntx->@maxerror@     = (time64_t)nxtalt.@maxerror@;
		ntx->@esterror@     = (time64_t)nxtalt.@esterror@;
		ntx->@status@       = nxtalt.@status@;
		ntx->@constant@     = (time64_t)nxtalt.@constant@;
		ntx->@precision@    = (time64_t)nxtalt.@precision@;
		ntx->@tolerance@    = (time64_t)nxtalt.@tolerance@;
		ntx->@tick@         = (time64_t)nxtalt.@tick@;
		ntx->@ppsfreq@      = (time64_t)nxtalt.@ppsfreq@;
		ntx->@jitter@       = (time64_t)nxtalt.@jitter@;
		ntx->@shift@        = (time64_t)nxtalt.@shift@;
		ntx->@stabil@       = (time64_t)nxtalt.@stabil@;
		ntx->@jitcnt@       = (time64_t)nxtalt.@jitcnt@;
		ntx->@calcnt@       = (time64_t)nxtalt.@calcnt@;
		ntx->@errcnt@       = (time64_t)nxtalt.@errcnt@;
		ntx->@stbcnt@       = (time64_t)nxtalt.@stbcnt@;
		ntx->@tai@          = (time64_t)nxtalt.@tai@;
	}
	return result;
}

[[time64_variant_of(ntp_adjtime)]]
[[userimpl, requires_function(ntp_adjtime32)]]
int ntp_adjtime64([[nonnull]] struct timex64 *__restrict tntx) {
	int result;
	struct $timex32 nxtalt;
	nxtalt.@time@.tv_sec  = (time32_t)tntx->@time@.tv_sec;
	nxtalt.@time@.tv_usec = tntx->@time@.tv_usec;
	nxtalt.@modes@        = tntx->@modes@;
	nxtalt.@offset@       = (time32_t)tntx->@offset@;
	nxtalt.@freq@         = (time32_t)tntx->@freq@;
	nxtalt.@maxerror@     = (time32_t)tntx->@maxerror@;
	nxtalt.@esterror@     = (time32_t)tntx->@esterror@;
	nxtalt.@status@       = tntx->@status@;
	nxtalt.@constant@     = (time32_t)tntx->@constant@;
/*	nxtalt.@precision@    = (time32_t)tntx->@precision@; */
/*	nxtalt.@tolerance@    = (time32_t)tntx->@tolerance@; */
	nxtalt.@tick@         = (time32_t)tntx->@tick@;
/*	nxtalt.@ppsfreq@      = (time32_t)tntx->@ppsfreq@; */
/*	nxtalt.@jitter@       = (time32_t)tntx->@jitter@; */
/*	nxtalt.@shift@        = (time32_t)tntx->@shift@; */
/*	nxtalt.@stabil@       = (time32_t)tntx->@stabil@; */
/*	nxtalt.@jitcnt@       = (time32_t)tntx->@jitcnt@; */
/*	nxtalt.@calcnt@       = (time32_t)tntx->@calcnt@; */
/*	nxtalt.@errcnt@       = (time32_t)tntx->@errcnt@; */
/*	nxtalt.@stbcnt@       = (time32_t)tntx->@stbcnt@; */
/*	nxtalt.@tai@          = (time32_t)tntx->@tai@; */
	result = ntp_adjtime32(&nxtalt);
	if likely(result == 0) {
		tntx->@time@.tv_sec  = (time64_t)nxtalt.@time@.tv_sec;
		tntx->@time@.tv_usec = nxtalt.@time@.tv_usec;
		tntx->@modes@        = nxtalt.@modes@;
		tntx->@offset@       = (time64_t)nxtalt.@offset@;
		tntx->@freq@         = (time64_t)nxtalt.@freq@;
		tntx->@maxerror@     = (time64_t)nxtalt.@maxerror@;
		tntx->@esterror@     = (time64_t)nxtalt.@esterror@;
		tntx->@status@       = nxtalt.@status@;
		tntx->@constant@     = (time64_t)nxtalt.@constant@;
		tntx->@precision@    = (time64_t)nxtalt.@precision@;
		tntx->@tolerance@    = (time64_t)nxtalt.@tolerance@;
		tntx->@tick@         = (time64_t)nxtalt.@tick@;
		tntx->@ppsfreq@      = (time64_t)nxtalt.@ppsfreq@;
		tntx->@jitter@       = (time64_t)nxtalt.@jitter@;
		tntx->@shift@        = (time64_t)nxtalt.@shift@;
		tntx->@stabil@       = (time64_t)nxtalt.@stabil@;
		tntx->@jitcnt@       = (time64_t)nxtalt.@jitcnt@;
		tntx->@calcnt@       = (time64_t)nxtalt.@calcnt@;
		tntx->@errcnt@       = (time64_t)nxtalt.@errcnt@;
		tntx->@stbcnt@       = (time64_t)nxtalt.@stbcnt@;
		tntx->@tai@          = (time64_t)nxtalt.@tai@;
	}
	return result;
}


[[crt_name("ntp_gettimex64"), time64_variant_of(ntp_gettimex)]]
[[userimpl, requires_function(ntp_gettime32)]]
int ntp_gettime64([[nonnull]] struct ntptimeval64 *__restrict ntv) {
	struct $ntptimeval32 ntv32;
	int result = ntp_gettime32(&ntv32);
	if likely(result == 0) {
		ntv->@time@.tv_sec       = (time64_t)ntv32.@time@.tv_sec;
		ntv->@time@.tv_usec      = ntv32.@time@.tv_usec;
		ntv->@maxerror@          = ntv32.@maxerror@;
		ntv->@esterror@          = ntv32.@esterror@;
		ntv->@tai@               = ntv32.@tai@;
		ntv->@__glibc_reserved1@ = ntv32.@__glibc_reserved1@;
		ntv->@__glibc_reserved2@ = ntv32.@__glibc_reserved2@;
		ntv->@__glibc_reserved3@ = ntv32.@__glibc_reserved3@;
		ntv->@__glibc_reserved4@ = ntv32.@__glibc_reserved4@;
	}
	return result;
}
%#endif /* __USE_TIME64 */


%{

#endif /* __CC__ */

__SYSDECL_END

}