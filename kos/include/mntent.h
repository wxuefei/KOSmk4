/* HASH CRC-32:0x8b6b5a59 */
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
#ifndef _MNTENT_H
#define _MNTENT_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <paths.h>

#include <bits/crt/db/mntent.h>

/* Disclaimer: Documentation is taken from Glibc /usr/include/mntent.h */
/* Utilities for reading/writing fstab, mtab, etc.
   Copyright (C) 1995-2016 Free Software Foundation, Inc.
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

/* File listing canonical interesting mount points.  */
#define MNTTAB _PATH_MNTTAB /* Deprecated alias.  */

/* File listing currently active mount points.  */
#define MOUNTED _PATH_MOUNTED /* Deprecated alias.  */

/* General filesystem types.  */
#define MNTTYPE_IGNORE "ignore" /* Ignore this entry.  */
#define MNTTYPE_NFS    "nfs"    /* Network file system.  */
#define MNTTYPE_SWAP   "swap"   /* Swap device.  */

/* Generic mount options.  */
#define MNTOPT_DEFAULTS "defaults" /* Use all default options.  */
#define MNTOPT_RO       "ro"       /* Read only.  */
#define MNTOPT_RW       "rw"       /* Read/write.  */
#define MNTOPT_SUID     "suid"     /* Set uid allowed.  */
#define MNTOPT_NOSUID   "nosuid"   /* No set uid allowed.  */
#define MNTOPT_NOAUTO   "noauto"   /* Do not auto mount. */

#ifdef __CC__

#ifndef __FILE_defined
#define __FILE_defined 1
typedef __FILE FILE;
#endif /* !__FILE_defined */

#ifdef __CRT_HAVE_setmntent
/* Prepare to begin reading and/or writing mount table
 * entries from the beginning of FILE.  MODE is as for `fopen' */
__CDECLARE(__ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,setmntent,(char const *__file, char const *__mode),(__file,__mode))
#elif defined(__CRT_HAVE___setmntent)
/* Prepare to begin reading and/or writing mount table
 * entries from the beginning of FILE.  MODE is as for `fopen' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,setmntent,(char const *__file, char const *__mode),__setmntent,(__file,__mode))
#endif /* ... */
/* Read one mount table entry from STREAM.  Returns a pointer to storage
 * reused on the next call, or null for EOF or error (use feof/ferror to check) */
__CDECLARE_OPT(__ATTR_NONNULL((1)),struct mntent *,__NOTHROW_RPC,getmntent,(__FILE *__stream),(__stream))

#ifdef __USE_MISC
#ifdef __CRT_HAVE_getmntent_r
/* Reentrant version of the above function */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),struct mntent *,__NOTHROW_RPC,getmntent_r,(__FILE *__restrict __stream, struct mntent *__restrict __result, char *__restrict __buffer, __STDC_INT_AS_SIZE_T __bufsize),(__stream,__result,__buffer,__bufsize))
#elif defined(__CRT_HAVE___getmntent_r)
/* Reentrant version of the above function */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),struct mntent *,__NOTHROW_RPC,getmntent_r,(__FILE *__restrict __stream, struct mntent *__restrict __result, char *__restrict __buffer, __STDC_INT_AS_SIZE_T __bufsize),__getmntent_r,(__stream,__result,__buffer,__bufsize))
#endif /* ... */
#endif /* __USE_MISC */

/* Write the mount table entry described by MNT to STREAM.
 * Return zero on success, nonzero on failure */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,addmntent,(__FILE *__restrict __stream, struct mntent const *__restrict __mnt),(__stream,__mnt))
#ifdef __CRT_HAVE_endmntent
/* Close a stream opened with `setmntent' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC_NOKOS,endmntent,(__FILE *__stream),(__stream))
#elif defined(__CRT_HAVE_fclose)
/* Close a stream opened with `setmntent' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC_NOKOS,endmntent,(__FILE *__stream),fclose,(__stream))
#elif defined(__CRT_HAVE___endmntent)
/* Close a stream opened with `setmntent' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC_NOKOS,endmntent,(__FILE *__stream),__endmntent,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE_hasmntopt
/* Search MNT->mnt_opts for an option matching OPT.
 * Returns the address of the substring, or null if none found */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,hasmntopt,(struct mntent const *__mnt, char const *__opt),(__mnt,__opt))
#else /* __CRT_HAVE_hasmntopt */
#include <local/mntent/hasmntopt.h>
/* Search MNT->mnt_opts for an option matching OPT.
 * Returns the address of the substring, or null if none found */
__NAMESPACE_LOCAL_USING_OR_IMPL(hasmntopt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL hasmntopt)(struct mntent const *__mnt, char const *__opt) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hasmntopt))(__mnt, __opt); })
#endif /* !__CRT_HAVE_hasmntopt */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_MNTENT_H */
