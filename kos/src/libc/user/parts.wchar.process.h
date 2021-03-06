/* HASH CRC-32:0x34d3bcc7 */
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
#ifndef GUARD_LIBC_USER_PARTS_WCHAR_PROCESS_H
#define GUARD_LIBC_USER_PARTS_WCHAR_PROCESS_H 1

#include "../api.h"
#include "../auto/parts.wchar.process.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <parts/wchar/process.h>

DECL_BEGIN

#ifndef __T16ARGV
#ifdef __USE_DOS
#define __T16ARGV char16_t const *const *__restrict ___argv
#define __T16ENVP char16_t const *const *__restrict ___envp
#else /* __USE_DOS */
#define __T16ARGV char16_t *const ___argv[__restrict_arr]
#define __T16ENVP char16_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__T16ARGV */
#ifndef __T32ARGV
#ifdef __USE_DOS
#define __T32ARGV char32_t const *const *__restrict ___argv
#define __T32ENVP char32_t const *const *__restrict ___envp
#else /* __USE_DOS */
#define __T32ARGV char32_t *const ___argv[__restrict_arr]
#define __T32ENVP char32_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__T32ARGV */
#ifndef __KERNEL__
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_wexecv)(char16_t const *__restrict path, __T16ARGV);
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBKCALL libc_wexecv)(char32_t const *__restrict path, __T32ARGV);
INTDEF NONNULL((1, 2, 3)) int NOTHROW_RPC(LIBDCALL libd_wexecve)(char16_t const *__restrict path, __T16ARGV, __T16ENVP);
INTDEF NONNULL((1, 2, 3)) int NOTHROW_RPC(LIBKCALL libc_wexecve)(char32_t const *__restrict path, __T32ARGV, __T32ENVP);
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_wexecvp)(char16_t const *__restrict file, __T16ARGV);
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBKCALL libc_wexecvp)(char32_t const *__restrict file, __T32ARGV);
INTDEF NONNULL((1, 2, 3)) int NOTHROW_RPC(LIBDCALL libd_wexecvpe)(char16_t const *__restrict file, __T16ARGV, __T16ENVP);
INTDEF NONNULL((1, 2, 3)) int NOTHROW_RPC(LIBKCALL libc_wexecvpe)(char32_t const *__restrict file, __T32ARGV, __T32ENVP);
INTDEF ATTR_SENTINEL NONNULL((1)) int NOTHROW_RPC(VLIBDCALL libd_wexecl)(char16_t const *__restrict path, char16_t const *args, ...);
INTDEF ATTR_SENTINEL NONNULL((1)) int NOTHROW_RPC(VLIBKCALL libc_wexecl)(char32_t const *__restrict path, char32_t const *args, ...);
INTDEF ATTR_SENTINEL NONNULL((1)) int NOTHROW_RPC(VLIBDCALL libd_wexeclp)(char16_t const *__restrict file, char16_t const *args, ...);
INTDEF ATTR_SENTINEL NONNULL((1)) int NOTHROW_RPC(VLIBKCALL libc_wexeclp)(char32_t const *__restrict file, char32_t const *args, ...);
INTDEF ATTR_SENTINEL_O(1) NONNULL((1)) int NOTHROW_RPC(VLIBDCALL libd_wexecle)(char16_t const *__restrict path, char16_t const *args, ...);
INTDEF ATTR_SENTINEL_O(1) NONNULL((1)) int NOTHROW_RPC(VLIBKCALL libc_wexecle)(char32_t const *__restrict path, char32_t const *args, ...);
INTDEF ATTR_SENTINEL_O(1) NONNULL((1)) int NOTHROW_RPC(VLIBDCALL libd_wexeclpe)(char16_t const *__restrict file, char16_t const *args, ...);
INTDEF ATTR_SENTINEL_O(1) NONNULL((1)) int NOTHROW_RPC(VLIBKCALL libc_wexeclpe)(char32_t const *__restrict file, char32_t const *args, ...);
INTDEF NONNULL((2, 3)) pid_t NOTHROW_RPC(LIBDCALL libd_wspawnv)(int mode, char16_t const *__restrict path, __T16ARGV);
INTDEF NONNULL((2, 3)) pid_t NOTHROW_RPC(LIBKCALL libc_wspawnv)(int mode, char32_t const *__restrict path, __T32ARGV);
INTDEF NONNULL((2, 3, 4)) pid_t NOTHROW_RPC(LIBDCALL libd_wspawnve)(int mode, char16_t const *__restrict path, __T16ARGV, __T16ENVP);
INTDEF NONNULL((2, 3, 4)) pid_t NOTHROW_RPC(LIBKCALL libc_wspawnve)(int mode, char32_t const *__restrict path, __T32ARGV, __T32ENVP);
INTDEF NONNULL((2, 3)) pid_t NOTHROW_RPC(LIBDCALL libd_wspawnvp)(int mode, char16_t const *__restrict file, __T16ARGV);
INTDEF NONNULL((2, 3)) pid_t NOTHROW_RPC(LIBKCALL libc_wspawnvp)(int mode, char32_t const *__restrict file, __T32ARGV);
INTDEF NONNULL((2, 3, 4)) pid_t NOTHROW_RPC(LIBDCALL libd_wspawnvpe)(int mode, char16_t const *__restrict file, __T16ARGV, __T16ENVP);
INTDEF NONNULL((2, 3, 4)) pid_t NOTHROW_RPC(LIBKCALL libc_wspawnvpe)(int mode, char32_t const *__restrict file, __T32ARGV, __T32ENVP);
INTDEF ATTR_SENTINEL NONNULL((2)) pid_t NOTHROW_RPC(VLIBDCALL libd_wspawnl)(int mode, char16_t const *__restrict path, char16_t const *args, ...);
INTDEF ATTR_SENTINEL NONNULL((2)) pid_t NOTHROW_RPC(VLIBKCALL libc_wspawnl)(int mode, char32_t const *__restrict path, char32_t const *args, ...);
INTDEF ATTR_SENTINEL NONNULL((2)) pid_t NOTHROW_RPC(VLIBDCALL libd_wspawnlp)(int mode, char16_t const *__restrict file, char16_t const *args, ...);
INTDEF ATTR_SENTINEL NONNULL((2)) pid_t NOTHROW_RPC(VLIBKCALL libc_wspawnlp)(int mode, char32_t const *__restrict file, char32_t const *args, ...);
INTDEF ATTR_SENTINEL_O(1) NONNULL((2)) pid_t NOTHROW_RPC(VLIBDCALL libd_wspawnle)(int mode, char16_t const *__restrict path, char16_t const *args, ...);
INTDEF ATTR_SENTINEL_O(1) NONNULL((2)) pid_t NOTHROW_RPC(VLIBKCALL libc_wspawnle)(int mode, char32_t const *__restrict path, char32_t const *args, ...);
INTDEF ATTR_SENTINEL_O(1) NONNULL((2)) pid_t NOTHROW_RPC(VLIBDCALL libd_wspawnlpe)(int mode, char16_t const *__restrict file, char16_t const *args, ...);
INTDEF ATTR_SENTINEL_O(1) NONNULL((2)) pid_t NOTHROW_RPC(VLIBKCALL libc_wspawnlpe)(int mode, char32_t const *__restrict file, char32_t const *args, ...);
INTDEF int NOTHROW_RPC(LIBDCALL libd_wsystem)(char16_t const *cmd);
INTDEF int NOTHROW_RPC(LIBKCALL libc_wsystem)(char32_t const *cmd);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_PROCESS_H */
