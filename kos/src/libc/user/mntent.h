/* HASH CRC-32:0x6fed02de */
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
#ifndef GUARD_LIBC_USER_MNTENT_H
#define GUARD_LIBC_USER_MNTENT_H 1

#include "../api.h"
#include "../auto/mntent.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <mntent.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Prepare to begin reading and/or writing mount table
 * entries from the beginning of FILE.  MODE is as for `fopen' */
INTDEF NONNULL((1, 2)) FILE *NOTHROW_RPC(LIBCCALL libc_setmntent)(char const *file, char const *mode);
/* Read one mount table entry from STREAM.  Returns a pointer to storage
 * reused on the next call, or null for EOF or error (use feof/ferror to check) */
INTDEF NONNULL((1)) struct mntent *NOTHROW_RPC(LIBCCALL libc_getmntent)(FILE *stream);
/* Reentrant version of the above function */
INTDEF NONNULL((1, 2, 3)) struct mntent *NOTHROW_RPC(LIBCCALL libc_getmntent_r)(FILE *__restrict stream, struct mntent *__restrict result, char *__restrict buffer, __STDC_INT_AS_SIZE_T bufsize);
/* Write the mount table entry described by MNT to STREAM.
 * Return zero on success, nonzero on failure */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_addmntent)(FILE *__restrict stream, struct mntent const *__restrict mnt);
/* Close a stream opened with `setmntent' */
INTDEF NONNULL((1)) int NOTHROW_RPC_NOKOS(LIBCCALL libc_endmntent)(FILE *stream);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_MNTENT_H */
