/* HASH CRC-32:0xd26b2a07 */
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
#ifndef _LIBC_CORE_UNISTD_H
#define _LIBC_CORE_UNISTD_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#if !defined(____libc_core_syscall_defined) && defined(__CRT_HAVE_syscall)
#define ____libc_core_syscall_defined 1
#include <bits/types.h>
__CVREDIRECT(,__LONGPTR_TYPE__,__NOTHROW_RPC,__libc_core_syscall,(__LONGPTR_TYPE__ __sysno),syscall,(__sysno),__sysno,6,(__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t))
#endif /* !____libc_core_syscall_defined && __CRT_HAVE_syscall */
#ifndef ____libc_core_syscall64_defined
#define ____libc_core_syscall64_defined 1
#ifdef __CRT_HAVE_syscall
#include <bits/types.h>
__CVREDIRECT(,__LONG64_TYPE__,__NOTHROW_RPC,__libc_core_syscall64,(__syscall_ulong_t __sysno),syscall,(__sysno),__sysno,6,(__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t))
#elif defined(__CRT_HAVE_syscall64)
#include <bits/types.h>
__CVREDIRECT(,__LONG64_TYPE__,__NOTHROW_RPC,__libc_core_syscall64,(__syscall_ulong_t __sysno),syscall64,(__sysno),__sysno,6,(__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t))
#else /* ... */
#undef ____libc_core_syscall64_defined
#endif /* !... */
#endif /* !____libc_core_syscall64_defined */

__SYSDECL_END

#endif /* __CC__ */

#endif /* !_LIBC_CORE_UNISTD_H */
