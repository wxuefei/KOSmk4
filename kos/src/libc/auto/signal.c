/* HASH CRC-32:0x323a04d0 */
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
#ifndef GUARD_LIBC_AUTO_SIGNAL_C
#define GUARD_LIBC_AUTO_SIGNAL_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/signal.h"
#include "../user/string.h"

DECL_BEGIN

#include <bits/sigset.h>
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigemptyset)(sigset_t *set) {
	libc_bzeroc(set->__val, COMPILER_LENOF(set->__val), __SIZEOF_POINTER__);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigfillset)(sigset_t *set) {
#if __SIZEOF_POINTER__ == 8
	libc_memsetq(set->__val, __UINT64_C(0xffffffffffffffff), COMPILER_LENOF(set->__val));
#elif __SIZEOF_POINTER__ == 4
	libc_memsetl(set->__val, __UINT32_C(0xffffffff), COMPILER_LENOF(set->__val));
#elif __SIZEOF_POINTER__ == 2
	libc_memsetw(set->__val, __UINT16_C(0xffff), COMPILER_LENOF(set->__val));
#else /* ... */
	libc_memset(set->__val, __UINT8_C(0xff), __SIZEOF_SIGSET_T__);
#endif /* !... */
	return 0;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigaddset)(sigset_t *set,
                                     signo_t signo) {
	ulongptr_t mask = __sigset_mask(signo);
	ulongptr_t word = __sigset_word(signo);
	set->__val[word] |= mask;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigdelset)(sigset_t *set,
                                     signo_t signo) {
	ulongptr_t mask = __sigset_mask(signo);
	ulongptr_t word = __sigset_word(signo);
	set->__val[word] &= ~mask;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigismember)(sigset_t const *set,
                                       signo_t signo) {
	ulongptr_t mask = __sigset_mask(signo);
	ulongptr_t word = __sigset_word(signo);
	return (set->__val[word] & mask) != 0;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigisemptyset)(sigset_t const *__restrict set) {
	size_t i;
	for (i = 0; i < sizeof(sigset_t) / sizeof(ulongptr_t); ++i)
		if (set->__val[i])
			return 0;
	return 1;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBCCALL libc_sigandset)(sigset_t *set,
                                     sigset_t const *left,
                                     sigset_t const *right) {
	size_t i;
	for (i = 0; i < sizeof(sigset_t) / sizeof(ulongptr_t); ++i)
		set->__val[i] = left->__val[i] & right->__val[i];
	return 0;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBCCALL libc_sigorset)(sigset_t *set,
                                    sigset_t const *left,
                                    sigset_t const *right) {
	size_t i;
	for (i = 0; i < sizeof(sigset_t) / sizeof(ulongptr_t); ++i)
		set->__val[i] = left->__val[i] | right->__val[i];
	return 0;
}
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_CONST WUNUSED signo_t
NOTHROW_NCX(LIBCCALL libc___libc_current_sigrtmin)(void) {
	return __SIGRTMIN;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_CONST WUNUSED signo_t
NOTHROW_NCX(LIBCCALL libc___libc_current_sigrtmax)(void) {
	return __SIGRTMAX;
}
#endif /* !__KERNEL__ */

DECL_END

DEFINE_PUBLIC_ALIAS(sigemptyset, libc_sigemptyset);
DEFINE_PUBLIC_ALIAS(sigfillset, libc_sigfillset);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__sigaddset, libc_sigaddset);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(sigaddset, libc_sigaddset);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__sigdelset, libc_sigdelset);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(sigdelset, libc_sigdelset);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__sigismember, libc_sigismember);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(sigismember, libc_sigismember);
DEFINE_PUBLIC_ALIAS(sigisemptyset, libc_sigisemptyset);
DEFINE_PUBLIC_ALIAS(sigandset, libc_sigandset);
DEFINE_PUBLIC_ALIAS(sigorset, libc_sigorset);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__libc_current_sigrtmin, libc___libc_current_sigrtmin);
DEFINE_PUBLIC_ALIAS(__libc_current_sigrtmax, libc___libc_current_sigrtmax);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SIGNAL_C */
