/* HASH CRC-32:0xe63457a1 */
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
#ifndef GUARD_LIBC_USER_SYS_TIMES_H
#define GUARD_LIBC_USER_SYS_TIMES_H 1

#include "../api.h"
#include "../auto/sys.times.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/times.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Store the CPU time used by this process and all its
 * dead children (and their dead children) in BUFFER.
 * Return the elapsed real time, or (clock_t) -1 for errors.
 * All times are in CLK_TCKths of a second */
INTDEF clock_t NOTHROW_NCX(LIBCCALL libc_times)(struct tms *buffer);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_TIMES_H */
