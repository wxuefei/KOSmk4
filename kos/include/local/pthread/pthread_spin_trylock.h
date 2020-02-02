/* HASH CRC-32:0x148fe3eb */
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
#ifndef __local_pthread_spin_trylock_defined
#define __local_pthread_spin_trylock_defined 1
#include <hybrid/__atomic.h>

#include <parts/errno.h>
__NAMESPACE_LOCAL_BEGIN
/* Try to lock spinlock LOCK */
__LOCAL_LIBC(pthread_spin_trylock) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pthread_spin_trylock))(__pthread_spinlock_t *__lock) {
#line 1280 "kos/src/libc/magic/pthread.c"
	if (__hybrid_atomic_xch(*__lock, 1, __ATOMIC_ACQUIRE) == 0)
		return 0;
#ifdef __EBUSY
	return __EBUSY;
#elif defined(__EWOULDBLOCK)
	return __EWOULDBLOCK;
#elif defined(__EAGAIN)
	return __EAGAIN;
#else /* ... */
	return 1;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_pthread_spin_trylock_defined */