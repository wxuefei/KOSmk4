/* HASH CRC-32:0xc5377707 */
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
#ifndef GUARD_LIBC_AUTO_PROCESS_H
#define GUARD_LIBC_AUTO_PROCESS_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <process.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF uintptr_t NOTHROW_NCX(LIBDCALL libd__beginthread)(__dos_beginthread_entry_t entry, u32 stacksz, void *arg);
INTDEF uintptr_t NOTHROW_NCX(LIBDCALL libd__beginthreadex)(void *sec, u32 stacksz, __dos_beginthreadex_entry_t entry, void *arg, u32 flags, u32 *threadaddr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF void NOTHROW_NCX(LIBCCALL libc__endthread)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_NCX(LIBDCALL libd__endthreadex)(u32 exitcode);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF void (LIBCCALL libc__c_exit)(void) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF intptr_t (LIBDCALL libd__loaddll)(char __KOS_FIXED_CONST *file) THROWS(...);
INTDEF int (LIBDCALL libd__unloaddll)(intptr_t hnd) THROWS(...);
INTDEF __procfun (LIBDCALL libd__getdllprocaddr)(intptr_t hnd, char __KOS_FIXED_CONST *symname, intptr_t ord) THROWS(...);
INTDEF pid_t NOTHROW_RPC(LIBDCALL libd_cwait)(int *tstat, pid_t pid, int action);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF pid_t NOTHROW_RPC(LIBCCALL libc_cwait)(int *tstat, pid_t pid, int action);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((2, 3)) pid_t NOTHROW_RPC(LIBDCALL libd_spawnv)(int mode, char const *__restrict path, __TARGV);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((2, 3)) pid_t NOTHROW_RPC(LIBCCALL libc_spawnv)(int mode, char const *__restrict path, __TARGV);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((2, 3)) pid_t NOTHROW_RPC(LIBDCALL libd_spawnvp)(int mode, char const *__restrict file, __TARGV);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((2, 3)) pid_t NOTHROW_RPC(LIBCCALL libc_spawnvp)(int mode, char const *__restrict file, __TARGV);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((2, 3, 4)) pid_t NOTHROW_RPC(LIBDCALL libd_spawnve)(int mode, char const *__restrict path, __TARGV, __TENVP);
INTDEF NONNULL((2, 3, 4)) pid_t NOTHROW_RPC(LIBDCALL libd_spawnvpe)(int mode, char const *__restrict file, __TARGV, __TENVP);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((2, 3, 4)) pid_t NOTHROW_RPC(LIBCCALL libc_spawnvpe)(int mode, char const *__restrict file, __TARGV, __TENVP);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_SENTINEL NONNULL((2)) pid_t NOTHROW_RPC(VLIBDCALL libd_spawnl)(int mode, char const *__restrict path, char const *args, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_SENTINEL NONNULL((2)) pid_t NOTHROW_RPC(VLIBCCALL libc_spawnl)(int mode, char const *__restrict path, char const *args, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_SENTINEL NONNULL((2)) pid_t NOTHROW_RPC(VLIBDCALL libd_spawnlp)(int mode, char const *__restrict file, char const *args, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_SENTINEL NONNULL((2)) pid_t NOTHROW_RPC(VLIBCCALL libc_spawnlp)(int mode, char const *__restrict file, char const *args, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_SENTINEL_O(1) NONNULL((2)) pid_t NOTHROW_RPC(VLIBDCALL libd_spawnle)(int mode, char const *__restrict path, char const *args, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_SENTINEL_O(1) NONNULL((2)) pid_t NOTHROW_RPC(VLIBCCALL libc_spawnle)(int mode, char const *__restrict path, char const *args, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_SENTINEL_O(1) NONNULL((2)) pid_t NOTHROW_RPC(VLIBDCALL libd_spawnlpe)(int mode, char const *__restrict file, char const *args, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_SENTINEL_O(1) NONNULL((2)) pid_t NOTHROW_RPC(VLIBCCALL libc_spawnlpe)(int mode, char const *__restrict file, char const *args, ...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PROCESS_H */
