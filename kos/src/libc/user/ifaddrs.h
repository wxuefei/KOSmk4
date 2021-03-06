/* HASH CRC-32:0x29994974 */
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
#ifndef GUARD_LIBC_USER_IFADDRS_H
#define GUARD_LIBC_USER_IFADDRS_H 1

#include "../api.h"
#include "../auto/ifaddrs.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <ifaddrs.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Create a linked list of `struct ifaddrs' structures, one for each
 * network interface on the host machine. If successful, store the
 * list in *IFAP and return 0. On errors, return -1 and set `errno'.
 * The storage returned in *IFAP is allocated dynamically and can
 * only be properly freed by passing it to `freeifaddrs' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_getifaddrs)(struct ifaddrs **ifap);
/* Reclaim the storage allocated by a previous `getifaddrs' call */
INTDEF void NOTHROW_NCX(LIBCCALL libc_freeifaddrs)(struct ifaddrs *ifa);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_IFADDRS_H */
