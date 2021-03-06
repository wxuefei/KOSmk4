/* HASH CRC-32:0x8d024d0 */
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
#ifndef _FNMATCH_H
#define _FNMATCH_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

/* Documentation taken from Glibc /usr/include/fnmatch.h */
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

#define FNM_PATHNAME    0x01 /* No wildcard can ever match '/'. */
#define FNM_NOESCAPE    0x02 /* Backslashes don't quote special chars. */
#define FNM_PERIOD      0x04 /* Leading '.' is matched only explicitly. */
#if (!defined(_POSIX_C_SOURCE) || _POSIX_C_SOURCE < 2 || defined(__USE_GNU))
#define FNM_FILE_NAME   FNM_PATHNAME /* Preferred GNU name. */
#define FNM_LEADING_DIR 0x08 /* Ignore '/...' after a match. */
#define FNM_CASEFOLD    0x10 /* Compare without regard to case. */
#define FNM_EXTMATCH    0x20 /* Use ksh-like extended matching. */
#endif /* !_POSIX_C_SOURCE || _POSIX_C_SOURCE < 2 || __USE_GNU */
#define FNM_NOMATCH      1 /* Value returned by 'fnmatch' if STRING does not match PATTERN. */
#ifdef __USE_XOPEN
#define FNM_NOSYS      (-1)
#endif /* __USE_XOPEN */

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_fnmatch
/* Match NAME against the filename pattern PATTERN,
 * returning zero if it matches, FNM_NOMATCH if not */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,fnmatch,(char const *__pattern, char const *__name, __STDC_INT_AS_UINT_T __match_flags),(__pattern,__name,__match_flags))
#else /* __CRT_HAVE_fnmatch */
#include <local/fnmatch/fnmatch.h>
/* Match NAME against the filename pattern PATTERN,
 * returning zero if it matches, FNM_NOMATCH if not */
__NAMESPACE_LOCAL_USING_OR_IMPL(fnmatch, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL fnmatch)(char const *__pattern, char const *__name, __STDC_INT_AS_UINT_T __match_flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fnmatch))(__pattern, __name, __match_flags); })
#endif /* !__CRT_HAVE_fnmatch */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_FNMATCH_H */
