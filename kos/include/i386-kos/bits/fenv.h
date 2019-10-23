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
#ifndef _I386_KOS_BITS_FENV_H
#define _I386_KOS_BITS_FENV_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

/* Documentation comments are taken from glibc /usr/include/i386-linux-gnu/bits/fenv.h */
/* Copyright (C) 1997-2016 Free Software Foundation, Inc.
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


/*[[[enum]]]*/
#ifdef __CC__
enum {
	FE_INVALID   = 0x01, /* == FSW_IE */
	__FE_DENORM  = 0x02, /* == FSW_DE */
	FE_DIVBYZERO = 0x04, /* == FSW_ZE */
	FE_OVERFLOW  = 0x08, /* == FSW_OE */
	FE_UNDERFLOW = 0x10, /* == FSW_UE */
	FE_INEXACT   = 0x20  /* == FSW_PE */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define FE_INVALID   FE_INVALID   /* == FSW_IE */
#define __FE_DENORM  __FE_DENORM  /* == FSW_DE */
#define FE_DIVBYZERO FE_DIVBYZERO /* == FSW_ZE */
#define FE_OVERFLOW  FE_OVERFLOW  /* == FSW_OE */
#define FE_UNDERFLOW FE_UNDERFLOW /* == FSW_UE */
#define FE_INEXACT   FE_INEXACT   /* == FSW_PE */
#else /* __COMPILER_PREFERR_ENUMS */
#define FE_INVALID   0x01 /* == FSW_IE */
#define __FE_DENORM  0x02 /* == FSW_DE */
#define FE_DIVBYZERO 0x04 /* == FSW_ZE */
#define FE_OVERFLOW  0x08 /* == FSW_OE */
#define FE_UNDERFLOW 0x10 /* == FSW_UE */
#define FE_INEXACT   0x20 /* == FSW_PE */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

#define FE_ALL_EXCEPT \
	(FE_INEXACT | FE_DIVBYZERO | FE_UNDERFLOW | FE_OVERFLOW | FE_INVALID)


/*[[[enum]]]*/
#ifdef __CC__
enum {
	FE_TONEAREST  = 0x0000, /* == FCW_RC_NEAREST */
	FE_DOWNWARD   = 0x0400, /* == FCW_RC_DOWN */
	FE_UPWARD     = 0x0800, /* == FCW_RC_UP */
	FE_TOWARDZERO = 0x0c00  /* == FCW_RC_TRUNC */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define FE_TONEAREST  FE_TONEAREST  /* == FCW_RC_NEAREST */
#define FE_DOWNWARD   FE_DOWNWARD   /* == FCW_RC_DOWN */
#define FE_UPWARD     FE_UPWARD     /* == FCW_RC_UP */
#define FE_TOWARDZERO FE_TOWARDZERO /* == FCW_RC_TRUNC */
#else /* __COMPILER_PREFERR_ENUMS */
#define FE_TONEAREST  0x0000 /* == FCW_RC_NEAREST */
#define FE_DOWNWARD   0x0400 /* == FCW_RC_DOWN */
#define FE_UPWARD     0x0800 /* == FCW_RC_UP */
#define FE_TOWARDZERO 0x0c00 /* == FCW_RC_TRUNC */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


#ifdef __CC__
typedef __UINT16_TYPE__ __fexcept_t;
/* Type representing floating-point environment.
 * This structure corresponds to the layout of the block written by
 * the `fstenv' instruction and has additional fields for the contents
 * of the MXCSR register as written by the `stmxcsr' instruction. */
struct __fenv_struct {
	__UINT16_TYPE__ __control_word;
	__UINT16_TYPE__ __glibc_reserved1;
	__UINT16_TYPE__ __status_word;
	__UINT16_TYPE__ __glibc_reserved2;
	__UINT16_TYPE__ __tags;
	__UINT16_TYPE__ __glibc_reserved3;
	__UINT32_TYPE__ __eip;
	__UINT16_TYPE__ __cs_selector;
	unsigned int    __opcode : 11;
	unsigned int    __glibc_reserved4 : 5;
	__UINT32_TYPE__ __data_offset;
	__UINT16_TYPE__ __data_selector;
	__UINT16_TYPE__ __glibc_reserved5;
#ifdef __x86_64__
	__UINT32_TYPE__ __mxcsr;
#endif /* __x86_64__ */
};
#endif /* __CC__ */

#define FE_DFL_ENV    (__CCAST(const fenv_t *)-1) /* If the default argument is used we use this value. */
#ifdef __USE_GNU
#define FE_NOMASK_ENV (__CCAST(const fenv_t *)-2) /* Floating-point environment where none of the exception is masked. */
#endif /* __USE_GNU */


__SYSDECL_END

#endif /* !_I386_KOS_BITS_FENV_H */
