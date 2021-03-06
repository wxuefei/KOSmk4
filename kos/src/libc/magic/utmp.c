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
%[default:section(".text.crt{|.dos}.database.utmp")]

%{
#include <features.h>
#include <bits/crt/db/utmp.h>
#include <bits/types.h>
#include <paths.h>

#ifdef __USE_GLIBC
#include <sys/time.h>
#include <sys/types.h>
#endif /* __USE_GLIBC */

/* Documentation taken from Glibc /usr/include/utmp.h */
/* Copyright (C) 1993-2016 Free Software Foundation, Inc.
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

/* Compatibility names for the strings of the canonical file names. */
#define UTMP_FILE     _PATH_UTMP
#define UTMP_FILENAME _PATH_UTMP
#define WTMP_FILE     _PATH_WTMP
#define WTMP_FILENAME _PATH_WTMP

#ifdef __CC__
}


@@Make FD be the controlling terminal, stdin, stdout, and stderr;
@@then close FD. Returns 0 on success, nonzero on error
[[guard, cp_kos, section(".text.crt{|.dos}.io.tty")]]
int login_tty($fd_t fd);

@@Write the given entry into utmp and wtmp
[[guard, cp_kos, decl_include("<bits/crt/db/utmp.h>")]]
void login([[nonnull]] struct utmp const *entry);

@@Write the utmp entry to say the user on UT_LINE has logged out
[[guard, cp_kos]]
int logout([[nonnull]] char const *ut_line);

@@Append to wtmp an entry for the current time and the given info
[[guard, cp_kos]]
void logwtmp([[nonnull]] char const *ut_line,
             [[nonnull]] char const *ut_name,
             [[nonnull]] char const *ut_host);

@@Append entry UTMP to the wtmp-like file WTMP_FILE
[[cp_kos, decl_include("<bits/crt/db/utmp.h>")]]
void updwtmp([[nonnull]] char const *wtmp_file,
             [[nonnull]] struct utmp const *utmp);

@@Change name of the utmp file to be examined
[[cp_kos]]
int utmpname([[nonnull]] char const *file);

@@Read next entry from a utmp-like file
[[cp_kos, decl_include("<bits/crt/db/utmp.h>")]]
struct utmp *getutent();

@@Reset the input stream to the beginning of the file
[[cp_kos]]
void setutent();

@@Close the current open file
void endutent();

@@Search forward from the current point in the utmp file
@@until the next entry with a ut_type matching ID->ut_type
[[cp_kos, decl_include("<bits/crt/db/utmp.h>")]]
struct utmp *getutid([[nonnull]] struct utmp const *id);

@@Search forward from the current point in the utmp file
@@until the next entry with a ut_line matching LINE->ut_line
[[cp_kos, decl_include("<bits/crt/db/utmp.h>")]]
struct utmp *getutline([[nonnull]] struct utmp const *line);

@@Write out entry pointed to by UTMP_PTR into the utmp file
[[cp_kos, decl_include("<bits/crt/db/utmp.h>")]]
struct utmp *pututline([[nonnull]] struct utmp const *utmp_ptr);

%
%#ifdef __USE_MISC
@@Reentrant versions of the file for handling utmp files
[[cp_kos, decl_include("<bits/crt/db/utmp.h>")]]
int getutent_r([[nonnull]] struct utmp *buffer,
               [[nonnull]] struct utmp **result);

[[cp_kos, doc_alias(getutent_r), decl_include("<bits/crt/db/utmp.h>")]]
int getutid_r([[nonnull]] struct utmp const *id,
              [[nonnull]] struct utmp *buffer,
              [[nonnull]] struct utmp **result);

[[cp_kos, doc_alias(getutent_r), decl_include("<bits/crt/db/utmp.h>")]]
int getutline_r([[nonnull]] struct utmp const *line,
                [[nonnull]] struct utmp *buffer,
                [[nonnull]] struct utmp **result);
%#endif /* __USE_MISC */


%{
#endif /* __CC__ */

__SYSDECL_END

}