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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_ATOMIC64_H
#define GUARD_KERNEL_INCLUDE_SCHED_ATOMIC64_H 1

#include <kernel/compiler.h>

#include <kernel/arch/atomic64.h>
#include <kernel/types.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>

/* An API for 64-bit atomics that defines a u64+atomic_rwlock data structure,
 * where the lock is used when the host doesn't support the cmpxchg8b instruction
 * on i386, always uses the lock when the host never supports 64-bit atomics, and
 * doesn't even define the lock, and always just defines the raw 64-bit value if
 * the host always supports 64-bit atomics (such as on x86_64)
 * These are 3 configuration modes:
 *   - CONFIG_ATOMIC64_SUPPORT_NEVER:
 *         64-bit atomics are never supported and always have to be emulated
 *   - CONFIG_ATOMIC64_SUPPORT_ALWAYS:
 *         64-bit atomics are always supported and never have to be emulated
 *   - CONFIG_ATOMIC64_SUPPORT_DYNAMIC:
 *         64-bit atomic operations must go through api functions that
 *         dynamically get re-written based on native support determined
 *         at runtime.
 */


/* TODO: Also use `atomic64_t' for `struct fs::f_mode'
 *       Then gcc can stop generating fpu-instructions to facilitate atomic reads/writes */

#if (defined(CONFIG_ATOMIC64_SUPPORT_ALWAYS) + \
     defined(CONFIG_ATOMIC64_SUPPORT_NEVER) +  \
     defined(CONFIG_ATOMIC64_SUPPORT_DYNAMIC)) != 1
#error "Invalid arch-specific atomic64 support configuration"
#endif

DECL_BEGIN

#ifdef __CC__

#ifndef __atomic64_t_defined
#define __atomic64_t_defined 1
#ifdef __INTELLISENSE__
typedef struct {
	u64 _a_val;
} atomic64_t;
#define __atomic64_val(self) (self)._a_val
#define ATOMIC64_INIT(v) { v }
#else /* __INTELLISENSE__ */
typedef u64 atomic64_t;
#define __atomic64_val(self) self
#define ATOMIC64_INIT(v) v
#endif /* !__INTELLISENSE__ */

#define atomic64_init(self, v) (void)(__atomic64_val(*(self)) = (v))
#define atomic64_cinit(self, v)                     \
	(__hybrid_assert(__atomic64_val(*(self)) == 0), \
	 (__builtin_constant_p(v) && (v) == 0)          \
	 ? (void)0                                      \
	 : (void)(__atomic64_val(*(self)) = (v)))
#endif /* !__atomic64_t_defined */

/* NOTE: The read/write functions may be used to guaranty that reads/writes
 *       always return whole values in regards to other reads/writes to the
 *       same memory location that are also made using the atomic64* APIs. */

#ifndef ARCH_ATOMIC64_HAVE_PROTOTYPES
#ifdef CONFIG_ATOMIC64_SUPPORT_ALWAYS

/* Atomically read a 64-bit data word from `self' */
#define atomic64_read(self) \
	__hybrid_atomic_load(__atomic64_val(*(self)), __ATOMIC_SEQ_CST)

/* Atomically write a 64-bit data word to `self' */
#define atomic64_write(self, value) \
	__hybrid_atomic_store(__atomic64_val(*(self)), value, __ATOMIC_SEQ_CST)

/* Atomically compare-exchange a 64-bit data word from `self' */
#define atomic64_cmpxch(self, oldval, newval) \
	__hybrid_atomic_cmpxch(__atomic64_val(*(self)), oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

/* Atomically compare-exchange a 64-bit data word from `self' */
#define atomic64_cmpxch_val(self, oldval, newval) \
	__hybrid_atomic_cmpxch_val(__atomic64_val(*(self)), oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

/* Atomically exchange a 64-bit data word from `self' */
#define atomic64_xch(self, value) \
	__hybrid_atomic_xch(__atomic64_val(*(self)), value, __ATOMIC_SEQ_CST)

/* Atomically fetch-and-add a 64-bit data word from `self' */
#define atomic64_fetchadd(self, value) \
	__hybrid_atomic_fetchadd(__atomic64_val(*(self)), value, __ATOMIC_SEQ_CST)

/* Atomically fetch-and-and a 64-bit data word from `self' */
#define atomic64_fetchand(self, value) \
	__hybrid_atomic_fetchand(__atomic64_val(*(self)), value, __ATOMIC_SEQ_CST)

/* Atomically fetch-and-or a 64-bit data word from `self' */
#define atomic64_fetchor(self, value) \
	__hybrid_atomic_fetchor(__atomic64_val(*(self)), value, __ATOMIC_SEQ_CST)

/* Atomically fetch-and-xor a 64-bit data word from `self' */
#define atomic64_fetchxor(self, value) \
	__hybrid_atomic_fetchxor(__atomic64_val(*(self)), value, __ATOMIC_SEQ_CST)

#else /* CONFIG_ATOMIC64_SUPPORT_ALWAYS */

/* Atomically read a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) u64
NOTHROW(FCALL atomic64_read)(atomic64_t const *__restrict self);

/* Atomically write a 64-bit data word to `self' */
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) void
NOTHROW(FCALL atomic64_write)(atomic64_t *__restrict self, u64 value);

/* Atomically compare-exchange a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) __BOOL
NOTHROW(FCALL atomic64_cmpxch)(atomic64_t *__restrict self,
                               u64 oldval, u64 newval);

/* Atomically compare-exchange a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_cmpxch_val)(atomic64_t *__restrict self,
                                   u64 oldval, u64 newval);

/* Atomically exchange a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_xch)(atomic64_t *__restrict self, u64 value);

/* Atomically fetch-and-add a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_fetchadd)(atomic64_t *__restrict self, u64 value);

/* Atomically fetch-and-and a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_fetchand)(atomic64_t *__restrict self, u64 value);

/* Atomically fetch-and-or a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_fetchor)(atomic64_t *__restrict self, u64 value);

/* Atomically fetch-and-xor a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_fetchxor)(atomic64_t *__restrict self, u64 value);
#endif /* !CONFIG_ATOMIC64_SUPPORT_ALWAYS */
#endif /* !ARCH_ATOMIC64_HAVE_PROTOTYPES */

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_ATOMIC64_H */
