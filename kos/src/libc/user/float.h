/* HASH CRC-32:0x5fcafe8 */
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
#ifndef GUARD_LIBC_USER_FLOAT_H
#define GUARD_LIBC_USER_FLOAT_H 1

#include "../api.h"
#include "../auto/float.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <float.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF uint32_t NOTHROW_NCX(LIBCCALL libc__clearfp)(void);
INTDEF uint32_t NOTHROW_NCX(LIBCCALL libc__controlfp)(uint32_t newval, uint32_t mask);
INTDEF void NOTHROW_NCX(LIBCCALL libc__set_controlfp)(uint32_t newval, uint32_t mask);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__controlfp_s)(uint32_t *pcurrent, uint32_t newval, uint32_t mask);
INTDEF uint32_t NOTHROW_NCX(LIBCCALL libc__statusfp)(void);
INTDEF void NOTHROW_NCX(LIBCCALL libc__statusfp2)(uint32_t *x86_stat, uint32_t *sse2_stat);
INTDEF uint32_t NOTHROW_NCX(LIBCCALL libc__control87)(uint32_t newval, uint32_t mask);
INTDEF int NOTHROW_NCX(LIBCCALL libc___control87_2)(uint32_t newval, uint32_t mask, uint32_t *x86_control_word, uint32_t *sse2_control_word);
INTDEF int *NOTHROW_NCX(LIBCCALL libc___fpecode)(void);
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc__fpclass)(double x);
INTDEF void NOTHROW_NCX(LIBCCALL libc_fpreset)(void);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_FLOAT_H */
