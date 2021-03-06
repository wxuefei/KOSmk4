/* HASH CRC-32:0xa0ddf01c */
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
#ifndef GUARD_LIBC_AUTO_IO_H
#define GUARD_LIBC_AUTO_IO_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <io.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBDCALL libd__access_s)(char const *filename, int type);
INTDEF int NOTHROW_NCX(LIBDCALL libd__findclose)(intptr_t findfd);
INTDEF WUNUSED NONNULL((1, 2)) intptr_t NOTHROW_RPC(LIBDCALL libd__findfirst32)(char const *__restrict filename, struct _finddata32_t *__restrict finddata);
INTDEF WUNUSED NONNULL((1, 2)) intptr_t NOTHROW_RPC(LIBDCALL libd__findfirst32i64)(char const *__restrict filename, struct _finddata32i64_t *__restrict finddata);
INTDEF WUNUSED NONNULL((1, 2)) intptr_t NOTHROW_RPC(LIBDCALL libd__findfirst64)(char const *__restrict filename, struct __finddata64_t *__restrict finddata);
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd__findnext32)(intptr_t findfd, struct _finddata32_t *__restrict finddata);
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd__findnext32i64)(intptr_t findfd, struct _finddata32i64_t *__restrict finddata);
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd__findnext64)(intptr_t findfd, struct __finddata64_t *__restrict finddata);
INTDEF NONNULL((1, 2)) errno_t NOTHROW_RPC(LIBDCALL libd__sopen_s)(fd_t *fd, char const *filename, oflag_t oflags, int sflags, mode_t mode);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd__mktemp_s)(char *template_, size_t size);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd__pipe)(fd_t pipedes[2], uint32_t pipesize, oflag_t textmode);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc__pipe)(fd_t pipedes[2], uint32_t pipesize, oflag_t textmode);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED int64_t NOTHROW_NCX(LIBDCALL libd__filelengthi64)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED int64_t NOTHROW_NCX(LIBCCALL libc__filelengthi64)(fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_umask_s)(mode_t newmode, mode_t *oldmode);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_umask_s)(mode_t newmode, mode_t *oldmode);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_RPC(LIBDCALL libd___lock_fhandle)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF int NOTHROW_RPC(LIBCCALL libc___lock_fhandle)(fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_NCX(LIBDCALL libd__unlock_fhandle)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF void NOTHROW_NCX(LIBCCALL libc__unlock_fhandle)(fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED intptr_t NOTHROW_NCX(LIBDCALL libd__get_osfhandle)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED intptr_t NOTHROW_NCX(LIBCCALL libc__get_osfhandle)(fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED fd_t NOTHROW_NCX(LIBDCALL libd__open_osfhandle)(intptr_t osfd, oflag_t flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED fd_t NOTHROW_NCX(LIBCCALL libc__open_osfhandle)(intptr_t osfd, oflag_t flags);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF oflag_t NOTHROW_NCX(LIBDCALL libd_setmode)(fd_t fd, oflag_t mode);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF oflag_t NOTHROW_NCX(LIBCCALL libc_setmode)(fd_t fd, oflag_t mode);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_RPC(VLIBDCALL libd_sopen)(char const *filename, oflag_t oflags, int sflags, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_RPC(VLIBCCALL libc_sopen)(char const *filename, oflag_t oflags, int sflags, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED __LONG32_TYPE__ NOTHROW_NCX(LIBDCALL libd__filelength)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED __LONG32_TYPE__ NOTHROW_NCX(LIBCCALL libc__filelength)(fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED int NOTHROW_NCX(LIBDCALL libd__eof)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__eof)(fd_t fd);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_IO_H */
