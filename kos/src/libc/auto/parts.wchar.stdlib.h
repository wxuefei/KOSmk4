/* HASH CRC-32:0xdd956b45 */
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
#ifndef GUARD_LIBC_AUTO_PARTS_WCHAR_STDLIB_H
#define GUARD_LIBC_AUTO_PARTS_WCHAR_STDLIB_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <parts/wchar/stdlib.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_wtoi)(char16_t const *nptr);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBKCALL libc_wtoi)(char32_t const *nptr);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long NOTHROW_NCX(LIBDCALL libd_wtol)(char16_t const *nptr);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) long NOTHROW_NCX(LIBKCALL libc_wtol)(char32_t const *nptr);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBDCALL libd_wtoll)(char16_t const *nptr);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) __LONGLONG NOTHROW_NCX(LIBKCALL libc_wtoll)(char32_t const *nptr);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_STDLIB_H */
