/* HASH CRC-32:0xbb6378a2 */
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
#ifndef GUARD_LIBC_AUTO_FENV_H
#define GUARD_LIBC_AUTO_FENV_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <fenv.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Clear the supported exceptions represented by EXCEPTS */
INTDEF int NOTHROW(LIBDCALL libd_feclearexcept)(int excepts);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Clear the supported exceptions represented by EXCEPTS */
INTDEF int NOTHROW(LIBCCALL libc_feclearexcept)(int excepts);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Raise the supported exceptions represented by EXCEPTS */
INTDEF int (LIBDCALL libd_feraiseexcept)(int excepts) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Raise the supported exceptions represented by EXCEPTS */
INTDEF int (LIBCCALL libc_feraiseexcept)(int excepts) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Store implementation-defined representation of the exception
 * flags indicated by EXCEPTS in the object pointed to by FLAGP */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_fegetexceptflag)(fexcept_t *flagp, int excepts);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Store implementation-defined representation of the exception
 * flags indicated by EXCEPTS in the object pointed to by FLAGP */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_fegetexceptflag)(fexcept_t *flagp, int excepts);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Set complete status for exceptions indicated by EXCEPTS according
 * to the representation in the object pointed to by FLAGP */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_fesetexceptflag)(fexcept_t const *flagp, int excepts);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Set complete status for exceptions indicated by EXCEPTS according
 * to the representation in the object pointed to by FLAGP */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_fesetexceptflag)(fexcept_t const *flagp, int excepts);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Determine which of subset of the exceptions
 * specified by EXCEPTS are currently set */
INTDEF ATTR_PURE WUNUSED int NOTHROW(LIBDCALL libd_fetestexcept)(int excepts);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Determine which of subset of the exceptions
 * specified by EXCEPTS are currently set */
INTDEF ATTR_PURE WUNUSED int NOTHROW(LIBCCALL libc_fetestexcept)(int excepts);
/* Get current rounding direction
 * @return: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
INTDEF ATTR_PURE WUNUSED int NOTHROW(LIBCCALL libc_fegetround)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Establish the rounding direction represented by `rounding_direction'
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
INTDEF int NOTHROW(LIBDCALL libd_fesetround)(int rounding_direction);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Establish the rounding direction represented by `rounding_direction'
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
INTDEF int NOTHROW(LIBCCALL libc_fesetround)(int rounding_direction);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Store the current floating-point environment in the object pointed to by ENVP */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_fegetenv)(fenv_t *envp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Store the current floating-point environment in the object pointed to by ENVP */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_fegetenv)(fenv_t *envp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Save the current environment in the object pointed to by ENVP, clear
 * exception flags and install a non-stop mode (if available) for all exceptions */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_feholdexcept)(fenv_t *envp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Save the current environment in the object pointed to by ENVP, clear
 * exception flags and install a non-stop mode (if available) for all exceptions */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_feholdexcept)(fenv_t *envp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Establish the floating-point environment represented by the object pointed to by ENVP */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_fesetenv)(fenv_t const *envp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Establish the floating-point environment represented by the object pointed to by ENVP */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_fesetenv)(fenv_t const *envp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Save current exceptions in temporary storage, install environment
 * represented by object pointed to by ENVP and raise exceptions
 * according to saved exceptions */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_feupdateenv)(fenv_t const *envp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Save current exceptions in temporary storage, install environment
 * represented by object pointed to by ENVP and raise exceptions
 * according to saved exceptions */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_feupdateenv)(fenv_t const *envp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Enable individual exceptions.  Will not enable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully set, otherwise returns -1 */
INTDEF int NOTHROW(LIBDCALL libd_feenableexcept)(int excepts);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Enable individual exceptions.  Will not enable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully set, otherwise returns -1 */
INTDEF int NOTHROW(LIBCCALL libc_feenableexcept)(int excepts);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Disable individual exceptions.  Will not disable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully disabled, otherwise returns -1 */
INTDEF int NOTHROW(LIBDCALL libd_fedisableexcept)(int excepts);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Disable individual exceptions.  Will not disable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully disabled, otherwise returns -1 */
INTDEF int NOTHROW(LIBCCALL libc_fedisableexcept)(int excepts);
/* Return enabled exceptions */
INTDEF ATTR_PURE WUNUSED int NOTHROW(LIBCCALL libc_fegetexcept)(void);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_FENV_H */
