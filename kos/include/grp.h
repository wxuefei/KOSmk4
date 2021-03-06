/* HASH CRC-32:0x6f176304 */
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
#ifndef _GRP_H
#define _GRP_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <bits/crt/db/group.h>


/* Documentation taken from Glibc /usr/include/grp.h */
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

#if defined(__USE_POSIX) && defined(__USE_MISC)
#define NSS_BUFLEN_GROUP    1024
#endif /* __USE_POSIX && __USE_MISC */

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __gid_t_defined
#define __gid_t_defined 1
typedef __gid_t gid_t;
#endif /* !__gid_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifndef __std_FILE_defined
#define __std_FILE_defined 1
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __FILE_defined
#define __FILE_defined 1
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
#endif /* !__CXX_SYSTEM_HEADER */

/* Search for an entry with a matching group ID */
__CDECLARE_OPT(,struct group *,__NOTHROW_RPC,getgrgid,(__gid_t __gid),(__gid))
/* Search for an entry with a matching group name */
__CDECLARE_OPT(__ATTR_NONNULL((1)),struct group *,__NOTHROW_RPC,getgrnam,(char const *__restrict __name),(__name))

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
/* Rewind the group-file stream */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,setgrent,(void),())
/* Close the group-file stream */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC_NOKOS,endgrent,(void),())
/* Read an entry from the group-file stream, opening it if necessary */
__CDECLARE_OPT(,struct group *,__NOTHROW_RPC,getgrent,(void),())
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#ifdef __USE_GNU
/* Write the given entry onto the given stream */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,putgrent,(struct group const *__restrict __entry, __FILE *__restrict __stream),(__entry,__stream))
#endif /* __USE_GNU */

#ifdef __USE_POSIX
/* Search for an entry with a matching group ID */
__CDECLARE_OPT(__ATTR_NONNULL((2, 3, 5)),int,__NOTHROW_RPC,getgrgid_r,(__gid_t __gid, struct group *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct group **__restrict __result),(__gid,__resultbuf,__buffer,__buflen,__result))
/* Search for an entry with a matching group name */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 3, 5)),int,__NOTHROW_RPC,getgrnam_r,(char const *__restrict __name, struct group *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct group **__restrict __result),(__name,__resultbuf,__buffer,__buflen,__result))

#ifdef __USE_GNU
/* Read an entry from the group-file stream, opening it if necessary */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 4)),int,__NOTHROW_RPC,getgrent_r,(struct group *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct group **__restrict __result),(__resultbuf,__buffer,__buflen,__result))
#endif /* __USE_GNU */

#ifdef __USE_MISC
/* Read a group entry from STREAM */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 3, 5)),int,__NOTHROW_RPC,fgetgrent_r,(__FILE *__restrict __stream, struct group *__restrict __resultbuf, char *__restrict __buffer, size_t __buflen, struct group **__restrict __result),(__stream,__resultbuf,__buffer,__buflen,__result))
#endif /* __USE_MISC */
#endif /* __USE_POSIX */

#ifdef __USE_MISC
/* Read a group entry from STREAM */
__CDECLARE_OPT(__ATTR_NONNULL((1)),struct group *,__NOTHROW_RPC,fgetgrent,(__FILE *__restrict __stream),(__stream))
/* Set the group set for the current user to GROUPS (N of them) */
__CDECLARE_OPT(,int,__NOTHROW_RPC,setgroups,(size_t __count, __gid_t const *__groups),(__count,__groups))
/* Store at most *NGROUPS members of the group set for USER into
 * *GROUPS. Also include GROUP. The actual number of groups found is
 * returned in *NGROUPS.  Return -1 if the if *NGROUPS is too small */
__CDECLARE_OPT(__ATTR_NONNULL((1, 3, 4)),int,__NOTHROW_RPC,getgrouplist,(char const *__user, __gid_t __group, __gid_t *__groups, int *__ngroups),(__user,__group,__groups,__ngroups))
/* Initialize the group set for the current user
 * by reading the group database and using all groups
 * of which USER is a member. Also include GROUP. */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,initgroups,(char const *__user, __gid_t __group),(__user,__group))
#endif /* __USE_MISC */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_GRP_H */
