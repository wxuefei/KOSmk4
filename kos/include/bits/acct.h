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
#ifndef _BITS_ACCT_H
#define _BITS_ACCT_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

__DECL_BEGIN

#if defined(__KOS__) || defined(__linux__)

/* Documentation taken from Glibc /usr/include/i386-linux-gnu/sys/acct.h */
/* Copyright (C) 1996-2016 Free Software Foundation, Inc.
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


#define ACCT_COMM 16
#define AHZ       100

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define ACCT_BYTEORDER 0x80  /* Accounting file is big endian. */
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#define ACCT_BYTEORDER 0x00  /* Accounting file is little endian. */
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */

/*[[[enum]]]*/
#ifdef __CC__
enum {
	AFORK = 0x01, /* Has executed fork, but no exec. */
	ASU   = 0x02, /* Used super-user privileges. */
	ACORE = 0x08, /* Dumped core. */
	AXSIG = 0x10  /* Killed by a signal. */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define AFORK AFORK /* Has executed fork, but no exec. */
#define ASU   ASU   /* Used super-user privileges. */
#define ACORE ACORE /* Dumped core. */
#define AXSIG AXSIG /* Killed by a signal. */
#else /* __COMPILER_PREFERR_ENUMS */
#define AFORK 0x01 /* Has executed fork, but no exec. */
#define ASU   0x02 /* Used super-user privileges. */
#define ACORE 0x08 /* Dumped core. */
#define AXSIG 0x10 /* Killed by a signal. */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


#ifdef __CC__
/* comp_t is a 16-bit "floating" point number with a 3-bit base 8
 * exponent and a 13-bit fraction. See linux/kernel/acct.c for the
 * specific encoding system used. */
typedef __UINT16_TYPE__ comp_t;

struct acct {
	__BYTE_TYPE__   ac_flag;                /* Flags. */
	__UINT16_TYPE__ ac_uid;                 /* Real user ID. */
	__UINT16_TYPE__ ac_gid;                 /* Real group ID. */
	__UINT16_TYPE__ ac_tty;                 /* Controlling terminal. */
	__UINT32_TYPE__ ac_btime;               /* Beginning time. */
	comp_t          ac_utime;               /* User time. */
	comp_t          ac_stime;               /* System time. */
	comp_t          ac_etime;               /* Elapsed time. */
	comp_t          ac_mem;                 /* Average memory usage. */
	comp_t          ac_io;                  /* Chars transferred. */
	comp_t          ac_rw;                  /* Blocks read or written. */
	comp_t          ac_minflt;              /* Minor pagefaults. */
	comp_t          ac_majflt;              /* Major pagefaults. */
	comp_t          ac_swaps;               /* Number of swaps. */
	__UINT32_TYPE__ ac_exitcode;            /* Process exitcode. */
	__CHAR8_TYPE__  ac_comm[ACCT_COMM + 1]; /* Command name. */
	__BYTE_TYPE__   ac_pad[10];             /* Padding bytes. */
};

struct acct_v3 {
	__BYTE_TYPE__   ac_flag;            /* Flags. */
	__BYTE_TYPE__   ac_version;         /* Always set to ACCT_VERSION. */
	__UINT16_TYPE__ ac_tty;             /* Control Terminal. */
	__UINT32_TYPE__ ac_exitcode;        /* Exitcode. */
	__UINT32_TYPE__ ac_uid;             /* Real User ID. */
	__UINT32_TYPE__ ac_gid;             /* Real Group ID. */
	__UINT32_TYPE__ ac_pid;             /* Process ID. */
	__UINT32_TYPE__ ac_ppid;            /* Parent Process ID. */
	__UINT32_TYPE__ ac_btime;           /* Process Creation Time. */
	float           ac_etime;           /* Elapsed Time. */
	comp_t          ac_utime;           /* User Time. */
	comp_t          ac_stime;           /* System Time. */
	comp_t          ac_mem;             /* Average Memory Usage. */
	comp_t          ac_io;              /* Chars Transferred. */
	comp_t          ac_rw;              /* Blocks Read or Written. */
	comp_t          ac_minflt;          /* Minor Page faults. */
	comp_t          ac_majflt;          /* Major Page faults. */
	comp_t          ac_swaps;           /* Number of Swaps. */
	__CHAR8_TYPE__  ac_comm[ACCT_COMM]; /* Command Name. */
};
#endif /* __CC__ */

#endif /* __KOS__ || __linux__ */

__DECL_END

#endif /* !_BITS_ACCT_H */
