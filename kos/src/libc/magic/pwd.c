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

%[define_replacement(uid_t = __uid_t)]
%[default:section(".text.crt{|.dos}.database.pwd")]

%{
#include <features.h>
#include <bits/types.h>
#include <bits/crt/db/passwd.h>

/* Documentation taken from Glibc /usr/include/pwd.h */
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
/* Reasonable value for the buffer sized used in the
 * reentrant functions below. But better use `sysconf'. */
#define NSS_BUFLEN_PASSWD  1024
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
#ifndef __uid_t_defined
#define __uid_t_defined 1
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */
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

}

%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
@@Rewind the password-file stream
[[cp]]
void setpwent();

@@Close the password-file stream
[[cp_nokos]]
void endpwent();

@@Read an entry from the password-file stream, opening it if necessary
[[cp, decl_include("<bits/crt/db/passwd.h>")]]
struct passwd *getpwent();
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */


@@Search for an entry with a matching user ID
[[cp, decl_include("<bits/crt/db/passwd.h>", "<bits/types.h>")]]
struct passwd *getpwuid($uid_t uid);

@@Search for an entry with a matching username
[[cp, decl_include("<bits/crt/db/passwd.h>")]]
struct passwd *getpwnam([[nonnull]] const char *name);

%
%#ifdef __USE_MISC
@@Read an entry from STREAM
[[cp, decl_include("<bits/crt/db/passwd.h>")]]
struct passwd *fgetpwent([[nonnull]] $FILE *__restrict stream);

@@Write the given entry onto the given stream
[[cp, decl_include("<bits/crt/db/passwd.h>")]]
int putpwent([[nonnull]] struct passwd const *__restrict p,
             [[nonnull]] $FILE *__restrict f);
%#endif /* __USE_MISC */

%
%#ifdef __USE_POSIX
[[cp, doc_alias("getpwuid"), decl_include("<bits/crt/db/passwd.h>", "<bits/types.h>")]]
int getpwuid_r(__uid_t __uid,
               [[nonnull]] struct passwd *__restrict resultbuf,
               [[outp(buflen)]] char *__restrict buffer, size_t buflen,
               [[nonnull]] struct passwd **__restrict result);

[[cp, doc_alias("getpwnam"), decl_include("<bits/crt/db/passwd.h>")]]
int getpwnam_r([[nonnull]] const char *__restrict name,
               [[nonnull]] struct passwd *__restrict resultbuf,
               [[outp(buflen)]] char *__restrict buffer, size_t buflen,
               [[nonnull]] struct passwd **__restrict result);

%#ifdef __USE_MISC
[[cp, doc_alias("getpwent"), decl_include("<bits/crt/db/passwd.h>")]]
getpwent_r:([[nonnull]] struct passwd *__restrict resultbuf,
            [[outp(buflen)]] char *__restrict buffer, size_t buflen,
            [[nonnull]] struct passwd **__restrict result) -> int;

@@Read an entry from STREAM. This function is not standardized and probably never will
[[cp, decl_include("<bits/crt/db/passwd.h>")]]
int fgetpwent_r([[nonnull]] $FILE *__restrict stream,
                [[nonnull]] struct passwd *__restrict resultbuf,
                [[outp(buflen)]] char *__restrict buffer, size_t buflen,
                [[nonnull]] struct passwd **__restrict result);
%#endif /* __USE_MISC */
%#endif	/* __USE_POSIX */

%#ifdef __USE_GNU
@@Re-construct the password-file line for the given uid in the
@@given buffer. This knows the format that the caller will
@@expect, but this need not be the format of the password file
[[cp, decl_include("<bits/types.h>")]]
int getpw(__uid_t uid, char *buffer);
%#endif /* __USE_GNU */


%{
#endif /* __CC__ */

__SYSDECL_END

}