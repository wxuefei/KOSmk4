/* HASH CRC-32:0xfbbde9da */
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
#ifndef GUARD_LIBC_USER_PROCESS_H
#define GUARD_LIBC_USER_PROCESS_H 1

#include "../api.h"
#include "../auto/process.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <process.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF uintptr_t NOTHROW_NCX(LIBCCALL libc__beginthread)(__dos_beginthread_entry_t entry, u32 stacksz, void *arg);
INTDEF uintptr_t NOTHROW_NCX(LIBCCALL libc__beginthreadex)(void *sec, u32 stacksz, __dos_beginthreadex_entry_t entry, void *arg, u32 flags, u32 *threadaddr);
INTDEF void NOTHROW_NCX(LIBCCALL libc__endthreadex)(u32 exitcode);
INTDEF void (LIBCCALL libc__cexit)(void) THROWS(...);
INTDEF intptr_t (LIBCCALL libc__loaddll)(char __KOS_FIXED_CONST *file) THROWS(...);
INTDEF int (LIBCCALL libc__unloaddll)(intptr_t hnd) THROWS(...);
INTDEF __procfun (LIBCCALL libc__getdllprocaddr)(intptr_t hnd, char __KOS_FIXED_CONST *symname, intptr_t ord) THROWS(...);
INTDEF NONNULL((2, 3, 4)) pid_t NOTHROW_RPC(LIBCCALL libc_spawnve)(int mode, char const *__restrict path, __TARGV, __TENVP);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_PROCESS_H */
