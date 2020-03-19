/*[[[magic
// Optimize this file for size
local opt = options.setdefault("GCC.options",[]);
opt.removeif([](e) -> e.startswith("-O"));
opt.append("-Os");
]]]*/
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
#ifndef GUARD_LIBVIOCORE_ARCH_I386_VIOCORE_C
#define GUARD_LIBVIOCORE_ARCH_I386_VIOCORE_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1

#include <hybrid/host.h>

#ifdef __x86_64__
#define CONFIG_LIBEMU86_WANT_16BIT 0
#define CONFIG_LIBEMU86_WANT_32BIT 1
#define CONFIG_LIBEMU86_WANT_64BIT 1
#else /* __x86_64__ */
#define CONFIG_LIBEMU86_WANT_16BIT 1
#define CONFIG_LIBEMU86_WANT_32BIT 1
#define CONFIG_LIBEMU86_WANT_64BIT 0
#endif /* !__x86_64__ */

#define CONFIG_LIBEMU86_WANT_SEGREGID 1
#define __LIBEMU86_STATIC 1


#include "../../viocore.h"

#ifdef LIBVIO_CONFIG_ENABLED

#include <hybrid/atomic.h>

#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>
#include <asm/intrin.h>
#include <asm/registers-compat.h>
#include <asm/registers.h>
#include <kos/anno.h>
#include <kos/except.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/segment.h>
#include <kos/kernel/types.h>
#include <kos/types.h>
#include <sys/syslog.h>

#include <int128.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>

#include <libemu86/emu86.h>
#include <libinstrlen/instrlen.h>
#include <libvio/access.h>

#ifdef __KERNEL__
#include <kernel/except.h>
#include <kernel/printk.h>
#include <sched/task.h>
#endif /* __KERNEL__ */

DECL_BEGIN

/* Emulate the instruction pointed-to by `self->vea_args.va_state' and dispatch
 * any memory access made to `self->vea_ptr' by dispatching it using the VIO
 * callback table.
 * Upon success, `self->vea_args.va_state' will point to the updated CPU state,
 * which may be placed at a different address than it was upon entry.
 * This function is intended to be called from a page fault handler. */
INTDEF void CC libviocore_emulate(struct vio_emulate_args *__restrict self);

#ifdef __KERNEL__
#define CS(x) icpustate_##x
#define _CS(x) x##_icpustate
#else /* __KERNEL__ */
#define CS(x) ucpustate_##x
#define _CS(x) x##_ucpustate
#endif /* !__KERNEL__ */

/* Fill in missing exception pointer. */
PRIVATE __NOBLOCK void
NOTHROW(CC libviocore_complete_except)(struct vio_emulate_args *__restrict self,
                                       u32 opcode) {
	struct exception_data *data;
	data = error_data();
	if (data->e_class == E_ILLEGAL_INSTRUCTION) {
		if (!data->e_pointers[0])
			data->e_pointers[0] = opcode;
	}
	/* Fill in the fault address. */
	data->e_faultaddr = (void *)CS(getpc)(self->vea_args.va_state);
}

PRIVATE ATTR_NORETURN void CC
libviocore_throw_unknown_instruction(struct vio_emulate_args *__restrict self,
                                     u32 opcode) {
	struct exception_data *data;
	void const *pc, *next_pc;
	unsigned int i;
	pc      = (void const *)CS(getpc)(self->vea_args.va_state);
	next_pc = instruction_succ(pc);
	if (next_pc)
		CS(setpc)(self->vea_args.va_state, (uintptr_t)next_pc);
#ifdef __KERNEL__
	printk(KERN_WARNING "[vio] Unrecognized instruction %p:%#I32x (accessing %p:%#I64x)\n",
	       pc, opcode, self->vea_ptr, (u64)self->vea_addr);
#else /* __KERNEL__ */
	syslog(LOG_WARN, "[vio] Unrecognized instruction %p:%#I32x (accessing %p:%#I64x)\n",
	       pc, opcode, self->vea_ptr, (u64)self->vea_addr);
#endif /* !__KERNEL__ */
	/* Throw an exception detailing an unsupported opcode. */
	data                = error_data();
	data->e_code        = ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE);
	data->e_faultaddr   = (void *)pc;
	data->e_pointers[0] = opcode;
	for (i = 1; i < EXCEPTION_DATA_POINTERS; ++i)
		data->e_pointers[i] = 0;
	error_throw_current();
}


#define EMU86_EMULATE_READB(addr) \
	libviocore_readb(self, (void const *)(uintptr_t)(addr))
LOCAL NONNULL((1)) u8 CC
libviocore_readb(struct vio_emulate_args *__restrict self,
                 __USER __CHECKED void const *addr) {
	u8 result;
	if likely(addr == self->vea_ptr)
		result = vio_readb(&self->vea_args, self->vea_addr);
	else {
		result = *(u8 const *)addr;
	}
	COMPILER_READ_BARRIER();
	return result;
}

#define EMU86_EMULATE_READW(addr) \
	libviocore_readw(self, (void const *)(uintptr_t)(addr))
LOCAL NONNULL((1)) u16 CC
libviocore_readw(struct vio_emulate_args *__restrict self,
                 __USER __CHECKED void const *addr) {
	u16 result;
	if likely(addr == self->vea_ptr)
		result = vio_readw(&self->vea_args, self->vea_addr);
	else {
		result = *(u16 const *)addr;
	}
	COMPILER_READ_BARRIER();
	return result;
}

#define EMU86_EMULATE_READL(addr) \
	libviocore_readl(self, (void const *)(uintptr_t)(addr))
LOCAL NONNULL((1)) u32 CC
libviocore_readl(struct vio_emulate_args *__restrict self,
                 __USER __CHECKED void const *addr) {
	u32 result;
	if likely(addr == self->vea_ptr)
		result = vio_readl(&self->vea_args, self->vea_addr);
	else {
		result = *(u32 const *)addr;
	}
	COMPILER_READ_BARRIER();
	return result;
}

#ifdef __x86_64__
#define EMU86_EMULATE_READQ(addr) \
	libviocore_readq(self, (void const *)(uintptr_t)(addr))
LOCAL NONNULL((1)) u64 CC
libviocore_readq(struct vio_emulate_args *__restrict self,
                 __USER __CHECKED void const *addr) {
	u64 result;
	if likely(addr == self->vea_ptr)
		result = vio_readq(&self->vea_args, self->vea_addr);
	else {
		result = *(u64 const *)addr;
	}
	COMPILER_READ_BARRIER();
	return result;
}
#endif /* __x86_64__ */

#define EMU86_EMULATE_WRITEB(addr, v) \
	libviocore_writeb(self, (void *)(uintptr_t)(addr), v)
LOCAL NONNULL((1)) void CC
libviocore_writeb(struct vio_emulate_args *__restrict self,
                  __USER __CHECKED void *addr, u8 value) {
	if likely(addr == self->vea_ptr)
		vio_writeb(&self->vea_args, self->vea_addr, value);
	else {
		*(u8 *)addr = value;
	}
	COMPILER_WRITE_BARRIER();
}

#define EMU86_EMULATE_WRITEW(addr, v) \
	libviocore_writew(self, (void *)(uintptr_t)(addr), v)
LOCAL NONNULL((1)) void CC
libviocore_writew(struct vio_emulate_args *__restrict self,
                  __USER __CHECKED void *addr, u16 value) {
	if likely(addr == self->vea_ptr)
		vio_writew(&self->vea_args, self->vea_addr, value);
	else {
		*(u16 *)addr = value;
	}
	COMPILER_WRITE_BARRIER();
}

#define EMU86_EMULATE_WRITEL(addr, v) \
	libviocore_writel(self, (void *)(uintptr_t)(addr), v)
LOCAL NONNULL((1)) void CC
libviocore_writel(struct vio_emulate_args *__restrict self,
                  __USER __CHECKED void *addr, u32 value) {
	if likely(addr == self->vea_ptr)
		vio_writel(&self->vea_args, self->vea_addr, value);
	else {
		*(u32 *)addr = value;
	}
	COMPILER_WRITE_BARRIER();
}

#ifdef __x86_64__
#define EMU86_EMULATE_WRITEQ(addr, v) \
	libviocore_writeq(self, (void *)(uintptr_t)(addr), v)
LOCAL NONNULL((1)) void CC
libviocore_writeq(struct vio_emulate_args *__restrict self,
                  __USER __CHECKED void *addr, u64 value) {
	if likely(addr == self->vea_ptr)
		vio_writeq(&self->vea_args, self->vea_addr, value);
	else {
		*(u64 *)addr = value;
	}
	COMPILER_WRITE_BARRIER();
}
#endif /* __x86_64__ */

#define EMU86_EMULATE_ATOMIC_XCHB(addr, addend, force_atomic) \
	libviocore_atomic_xchb(self, (void *)(uintptr_t)(addr), addend, force_atomic)
LOCAL NONNULL((1)) u8 CC
libviocore_atomic_xchb(struct vio_emulate_args *__restrict self,
                       __USER __CHECKED void *addr, u8 value,
                       bool force_atomic) {
	u8 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_xchb(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_XCH(*(u8 *)addr, value);
	else {
		result = *(u8 *)addr;
		*(u8 *)addr = value;
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_EMULATE_ATOMIC_XCHW(addr, addend, force_atomic) \
	libviocore_atomic_xchw(self, (void *)(uintptr_t)(addr), addend, force_atomic)
LOCAL NONNULL((1)) u16 CC
libviocore_atomic_xchw(struct vio_emulate_args *__restrict self,
                       __USER __CHECKED void *addr, u16 value,
                       bool force_atomic) {
	u16 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_xchw(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_XCH(*(u16 *)addr, value);
	else {
		result = *(u16 *)addr;
		*(u16 *)addr = value;
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_EMULATE_ATOMIC_XCHL(addr, addend, force_atomic) \
	libviocore_atomic_xchl(self, (void *)(uintptr_t)(addr), addend, force_atomic)
LOCAL NONNULL((1)) u32 CC
libviocore_atomic_xchl(struct vio_emulate_args *__restrict self,
                       __USER __CHECKED void *addr, u32 value,
                       bool force_atomic) {
	u32 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_xchl(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_XCH(*(u32 *)addr, value);
	else {
		result = *(u32 *)addr;
		*(u32 *)addr = value;
	}
	COMPILER_BARRIER();
	return result;
}

#ifdef __x86_64__
#define EMU86_EMULATE_ATOMIC_XCHQ(addr, addend, force_atomic) \
	libviocore_atomic_xchq(self, (void *)(uintptr_t)(addr), addend, force_atomic)
LOCAL NONNULL((1)) u64 CC
libviocore_atomic_xchq(struct vio_emulate_args *__restrict self,
                       __USER __CHECKED void *addr, u64 value,
                       bool force_atomic) {
	u64 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_xchq(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_XCH(*(u64 *)addr, value);
	else {
		result = *(u64 *)addr;
		*(u64 *)addr = value;
	}
	COMPILER_BARRIER();
	return result;
}
#endif /* __x86_64__ */

#define EMU86_EMULATE_ATOMIC_FETCHADDB(addr, addend, force_atomic) \
	libviocore_atomic_fetchaddb(self, (void *)(uintptr_t)(addr), addend, force_atomic)
LOCAL NONNULL((1)) u8 CC
libviocore_atomic_fetchaddb(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u8 value,
                            bool force_atomic) {
	u8 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_addb(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHADD(*(u8 *)addr, value);
	else {
		result = *(u8 *)addr;
		*(u8 *)addr = result + value;
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_EMULATE_ATOMIC_FETCHADDW(addr, addend, force_atomic) \
	libviocore_atomic_fetchaddw(self, (void *)(uintptr_t)(addr), addend, force_atomic)
LOCAL NONNULL((1)) u16 CC
libviocore_atomic_fetchaddw(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u16 value,
                            bool force_atomic) {
	u16 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_addw(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHADD(*(u16 *)addr, value);
	else {
		result = *(u16 *)addr;
		*(u16 *)addr = result + value;
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_EMULATE_ATOMIC_FETCHADDL(addr, addend, force_atomic) \
	libviocore_atomic_fetchaddl(self, (void *)(uintptr_t)(addr), addend, force_atomic)
LOCAL NONNULL((1)) u32 CC
libviocore_atomic_fetchaddl(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u32 value,
                            bool force_atomic) {
	u32 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_addl(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHADD(*(u32 *)addr, value);
	else {
		result = *(u32 *)addr;
		*(u32 *)addr = result + value;
	}
	COMPILER_BARRIER();
	return result;
}

#ifdef __x86_64__
#define EMU86_EMULATE_ATOMIC_FETCHADDQ(addr, addend, force_atomic) \
	libviocore_atomic_fetchaddq(self, (void *)(uintptr_t)(addr), addend, force_atomic)
LOCAL NONNULL((1)) u64 CC
libviocore_atomic_fetchaddq(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u64 value,
                            bool force_atomic) {
	u64 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_addq(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHADD(*(u64 *)addr, value);
	else {
		result = *(u64 *)addr;
		*(u64 *)addr = result + value;
	}
	COMPILER_BARRIER();
	return result;
}
#endif /* __x86_64__ */

#define EMU86_EMULATE_ATOMIC_FETCHSUBB(addr, subend, force_atomic) \
	libviocore_atomic_fetchsubb(self, (void *)(uintptr_t)(addr), subend, force_atomic)
LOCAL NONNULL((1)) u8 CC
libviocore_atomic_fetchsubb(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u8 value,
                            bool force_atomic) {
	u8 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_subb(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHSUB(*(u8 *)addr, value);
	else {
		result = *(u8 *)addr;
		*(u8 *)addr = result - value;
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_EMULATE_ATOMIC_FETCHSUBW(addr, subend, force_atomic) \
	libviocore_atomic_fetchsubw(self, (void *)(uintptr_t)(addr), subend, force_atomic)
LOCAL NONNULL((1)) u16 CC
libviocore_atomic_fetchsubw(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u16 value,
                            bool force_atomic) {
	u16 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_subw(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHSUB(*(u16 *)addr, value);
	else {
		result = *(u16 *)addr;
		*(u16 *)addr = result - value;
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_EMULATE_ATOMIC_FETCHSUBL(addr, subend, force_atomic) \
	libviocore_atomic_fetchsubl(self, (void *)(uintptr_t)(addr), subend, force_atomic)
LOCAL NONNULL((1)) u32 CC
libviocore_atomic_fetchsubl(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u32 value,
                            bool force_atomic) {
	u32 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_subl(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHSUB(*(u32 *)addr, value);
	else {
		result = *(u32 *)addr;
		*(u32 *)addr = result - value;
	}
	COMPILER_BARRIER();
	return result;
}

#ifdef __x86_64__
#define EMU86_EMULATE_ATOMIC_FETCHSUBQ(addr, subend, force_atomic) \
	libviocore_atomic_fetchsubq(self, (void *)(uintptr_t)(addr), subend, force_atomic)
LOCAL NONNULL((1)) u64 CC
libviocore_atomic_fetchsubq(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u64 value,
                            bool force_atomic) {
	u64 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_subq(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHSUB(*(u64 *)addr, value);
	else {
		result = *(u64 *)addr;
		*(u64 *)addr = result - value;
	}
	COMPILER_BARRIER();
	return result;
}
#endif /* __x86_64__ */

#define EMU86_EMULATE_ATOMIC_FETCHANDB(addr, andend, force_atomic) \
	libviocore_atomic_fetchandb(self, (void *)(uintptr_t)(addr), andend, force_atomic)
LOCAL NONNULL((1)) u8 CC
libviocore_atomic_fetchandb(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u8 value,
                            bool force_atomic) {
	u8 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_andb(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHAND(*(u8 *)addr, value);
	else {
		result = *(u8 *)addr;
		*(u8 *)addr = result & value;
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_EMULATE_ATOMIC_FETCHANDW(addr, andend, force_atomic) \
	libviocore_atomic_fetchandw(self, (void *)(uintptr_t)(addr), andend, force_atomic)
LOCAL NONNULL((1)) u16 CC
libviocore_atomic_fetchandw(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u16 value,
                            bool force_atomic) {
	u16 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_andw(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHAND(*(u16 *)addr, value);
	else {
		result = *(u16 *)addr;
		*(u16 *)addr = result & value;
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_EMULATE_ATOMIC_FETCHANDL(addr, andend, force_atomic) \
	libviocore_atomic_fetchandl(self, (void *)(uintptr_t)(addr), andend, force_atomic)
LOCAL NONNULL((1)) u32 CC
libviocore_atomic_fetchandl(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u32 value,
                            bool force_atomic) {
	u32 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_andl(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHAND(*(u32 *)addr, value);
	else {
		result = *(u32 *)addr;
		*(u32 *)addr = result & value;
	}
	COMPILER_BARRIER();
	return result;
}

#ifdef __x86_64__
#define EMU86_EMULATE_ATOMIC_FETCHANDQ(addr, andend, force_atomic) \
	libviocore_atomic_fetchandq(self, (void *)(uintptr_t)(addr), andend, force_atomic)
LOCAL NONNULL((1)) u64 CC
libviocore_atomic_fetchandq(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u64 value,
                            bool force_atomic) {
	u64 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_andq(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHAND(*(u64 *)addr, value);
	else {
		result = *(u64 *)addr;
		*(u64 *)addr = result & value;
	}
	COMPILER_BARRIER();
	return result;
}
#endif /* __x86_64__ */

#define EMU86_EMULATE_ATOMIC_FETCHORB(addr, orend, force_atomic) \
	libviocore_atomic_fetchorb(self, (void *)(uintptr_t)(addr), orend, force_atomic)
LOCAL NONNULL((1)) u8 CC
libviocore_atomic_fetchorb(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u8 value,
                            bool force_atomic) {
	u8 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_orb(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHOR(*(u8 *)addr, value);
	else {
		result = *(u8 *)addr;
		*(u8 *)addr = result | value;
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_EMULATE_ATOMIC_FETCHORW(addr, orend, force_atomic) \
	libviocore_atomic_fetchorw(self, (void *)(uintptr_t)(addr), orend, force_atomic)
LOCAL NONNULL((1)) u16 CC
libviocore_atomic_fetchorw(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u16 value,
                            bool force_atomic) {
	u16 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_orw(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHOR(*(u16 *)addr, value);
	else {
		result = *(u16 *)addr;
		*(u16 *)addr = result | value;
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_EMULATE_ATOMIC_FETCHORL(addr, orend, force_atomic) \
	libviocore_atomic_fetchorl(self, (void *)(uintptr_t)(addr), orend, force_atomic)
LOCAL NONNULL((1)) u32 CC
libviocore_atomic_fetchorl(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u32 value,
                            bool force_atomic) {
	u32 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_orl(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHOR(*(u32 *)addr, value);
	else {
		result = *(u32 *)addr;
		*(u32 *)addr = result | value;
	}
	COMPILER_BARRIER();
	return result;
}

#ifdef __x86_64__
#define EMU86_EMULATE_ATOMIC_FETCHORQ(addr, orend, force_atomic) \
	libviocore_atomic_fetchorq(self, (void *)(uintptr_t)(addr), orend, force_atomic)
LOCAL NONNULL((1)) u64 CC
libviocore_atomic_fetchorq(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u64 value,
                            bool force_atomic) {
	u64 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_orq(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHOR(*(u64 *)addr, value);
	else {
		result = *(u64 *)addr;
		*(u64 *)addr = result | value;
	}
	COMPILER_BARRIER();
	return result;
}
#endif /* __x86_64__ */

#define EMU86_EMULATE_ATOMIC_FETCHXORB(addr, xorend, force_atomic) \
	libviocore_atomic_fetchxorb(self, (void *)(uintptr_t)(addr), xorend, force_atomic)
LOCAL NONNULL((1)) u8 CC
libviocore_atomic_fetchxorb(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u8 value,
                            bool force_atomic) {
	u8 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_xorb(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHXOR(*(u8 *)addr, value);
	else {
		result = *(u8 *)addr;
		*(u8 *)addr = result ^ value;
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_EMULATE_ATOMIC_FETCHXORW(addr, xorend, force_atomic) \
	libviocore_atomic_fetchxorw(self, (void *)(uintptr_t)(addr), xorend, force_atomic)
LOCAL NONNULL((1)) u16 CC
libviocore_atomic_fetchxorw(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u16 value,
                            bool force_atomic) {
	u16 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_xorw(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHXOR(*(u16 *)addr, value);
	else {
		result = *(u16 *)addr;
		*(u16 *)addr = result ^ value;
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_EMULATE_ATOMIC_FETCHXORL(addr, xorend, force_atomic) \
	libviocore_atomic_fetchxorl(self, (void *)(uintptr_t)(addr), xorend, force_atomic)
LOCAL NONNULL((1)) u32 CC
libviocore_atomic_fetchxorl(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u32 value,
                            bool force_atomic) {
	u32 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_xorl(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHXOR(*(u32 *)addr, value);
	else {
		result = *(u32 *)addr;
		*(u32 *)addr = result ^ value;
	}
	COMPILER_BARRIER();
	return result;
}

#ifdef __x86_64__
#define EMU86_EMULATE_ATOMIC_FETCHXORQ(addr, xorend, force_atomic) \
	libviocore_atomic_fetchxorq(self, (void *)(uintptr_t)(addr), xorend, force_atomic)
LOCAL NONNULL((1)) u64 CC
libviocore_atomic_fetchxorq(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr, u64 value,
                            bool force_atomic) {
	u64 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_xorq(&self->vea_args, self->vea_addr, value, force_atomic);
	else if (force_atomic)
		result = ATOMIC_FETCHXOR(*(u64 *)addr, value);
	else {
		result = *(u64 *)addr;
		*(u64 *)addr = result ^ value;
	}
	COMPILER_BARRIER();
	return result;
}
#endif /* __x86_64__ */

#define EMU86_EMULATE_ATOMIC_CMPXCHB(addr, oldval, newval, force_atomic) \
	libviocore_atomic_cmpxchb(self, (void *)(uintptr_t)(addr), oldval, newval, force_atomic)
LOCAL NONNULL((1)) u8 CC
libviocore_atomic_cmpxchb(struct vio_emulate_args *__restrict self,
                          __USER __CHECKED void *addr,
                          u8 oldval, u8 newval, bool force_atomic) {
	u8 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_cmpxchb(&self->vea_args, self->vea_addr, oldval, newval, force_atomic);
	else if (force_atomic)
		result = ATOMIC_CMPXCH(*(u8 *)addr, oldval, newval);
	else {
		result = *(u8 *)addr;
		COMPILER_READ_BARRIER();
		if (result == oldval)
			*(u8 *)addr = newval;
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_EMULATE_ATOMIC_CMPXCHW(addr, oldval, newval, force_atomic) \
	libviocore_atomic_cmpxchw(self, (void *)(uintptr_t)(addr), oldval, newval, force_atomic)
LOCAL NONNULL((1)) u16 CC
libviocore_atomic_cmpxchw(struct vio_emulate_args *__restrict self,
                          __USER __CHECKED void *addr,
                          u16 oldval, u16 newval, bool force_atomic) {
	u16 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_cmpxchw(&self->vea_args, self->vea_addr, oldval, newval, force_atomic);
	else if (force_atomic)
		result = ATOMIC_CMPXCH(*(u16 *)addr, oldval, newval);
	else {
		result = *(u16 *)addr;
		COMPILER_READ_BARRIER();
		if (result == oldval)
			*(u16 *)addr = newval;
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_EMULATE_ATOMIC_CMPXCHL(addr, oldval, newval, force_atomic) \
	libviocore_atomic_cmpxchl(self, (void *)(uintptr_t)(addr), oldval, newval, force_atomic)
LOCAL NONNULL((1)) u32 CC
libviocore_atomic_cmpxchl(struct vio_emulate_args *__restrict self,
                          __USER __CHECKED void *addr,
                          u32 oldval, u32 newval, bool force_atomic) {
	u32 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_cmpxchl(&self->vea_args, self->vea_addr, oldval, newval, force_atomic);
	else if (force_atomic)
		result = ATOMIC_CMPXCH(*(u32 *)addr, oldval, newval);
	else {
		result = *(u32 *)addr;
		COMPILER_READ_BARRIER();
		if (result == oldval)
			*(u32 *)addr = newval;
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_EMULATE_ATOMIC_CMPXCHQ(addr, oldval, newval, force_atomic) \
	libviocore_atomic_cmpxchq(self, (void *)(uintptr_t)(addr), oldval, newval, force_atomic)
LOCAL NONNULL((1)) u64 CC
libviocore_atomic_cmpxchq(struct vio_emulate_args *__restrict self,
                          __USER __CHECKED void *addr,
                          u64 oldval, u64 newval, bool force_atomic) {
	u64 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_cmpxchq(&self->vea_args, self->vea_addr, oldval, newval, force_atomic);
	else if (force_atomic)
		result = ATOMIC_CMPXCH(*(u64 *)addr, oldval, newval);
	else {
		result = *(u64 *)addr;
		COMPILER_READ_BARRIER();
		if (result == oldval)
			*(u64 *)addr = newval;
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_EMULATE_ATOMIC_CMPXCH_OR_WRITEB(addr, oldval, newval, force_atomic) \
	libviocore_atomic_cmpxch_or_writeb(self, (void *)(uintptr_t)(addr), oldval, newval, force_atomic)
LOCAL NONNULL((1)) u8 CC
libviocore_atomic_cmpxch_or_writeb(struct vio_emulate_args *__restrict self,
                                   __USER __CHECKED void *addr,
                                   u8 oldval, u8 newval, bool force_atomic) {
	u8 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_cmpxch_or_writeb(&self->vea_args, self->vea_addr, oldval, newval, force_atomic);
	else if (force_atomic)
		result = ATOMIC_CMPXCH(*(u8 *)addr, oldval, newval);
	else {
		result = *(u8 *)addr;
		COMPILER_READ_BARRIER();
		if (result == oldval)
			*(u8 *)addr = newval;
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_EMULATE_ATOMIC_CMPXCH_OR_WRITEW(addr, oldval, newval, force_atomic) \
	libviocore_atomic_cmpxch_or_writew(self, (void *)(uintptr_t)(addr), oldval, newval, force_atomic)
LOCAL NONNULL((1)) u16 CC
libviocore_atomic_cmpxch_or_writew(struct vio_emulate_args *__restrict self,
                                   __USER __CHECKED void *addr,
                                   u16 oldval, u16 newval, bool force_atomic) {
	u16 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_cmpxch_or_writew(&self->vea_args, self->vea_addr, oldval, newval, force_atomic);
	else if (force_atomic)
		result = ATOMIC_CMPXCH(*(u16 *)addr, oldval, newval);
	else {
		result = *(u16 *)addr;
		COMPILER_READ_BARRIER();
		if (result == oldval)
			*(u16 *)addr = newval;
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_EMULATE_ATOMIC_CMPXCH_OR_WRITEL(addr, oldval, newval, force_atomic) \
	libviocore_atomic_cmpxch_or_writel(self, (void *)(uintptr_t)(addr), oldval, newval, force_atomic)
LOCAL NONNULL((1)) u32 CC
libviocore_atomic_cmpxch_or_writel(struct vio_emulate_args *__restrict self,
                                   __USER __CHECKED void *addr,
                                   u32 oldval, u32 newval, bool force_atomic) {
	u32 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_cmpxch_or_writel(&self->vea_args, self->vea_addr, oldval, newval, force_atomic);
	else if (force_atomic)
		result = ATOMIC_CMPXCH(*(u32 *)addr, oldval, newval);
	else {
		result = *(u32 *)addr;
		COMPILER_READ_BARRIER();
		if (result == oldval)
			*(u32 *)addr = newval;
	}
	COMPILER_BARRIER();
	return result;
}

#ifdef __x86_64__
#define EMU86_EMULATE_ATOMIC_CMPXCH_OR_WRITEQ(addr, oldval, newval, force_atomic) \
	libviocore_atomic_cmpxch_or_writeq(self, (void *)(uintptr_t)(addr), oldval, newval, force_atomic)
LOCAL NONNULL((1)) u64 CC
libviocore_atomic_cmpxch_or_writeq(struct vio_emulate_args *__restrict self,
                                   __USER __CHECKED void *addr,
                                   u64 oldval, u64 newval, bool force_atomic) {
	u64 result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr)
		result = vio_cmpxch_or_writeq(&self->vea_args, self->vea_addr, oldval, newval, force_atomic);
	else if (force_atomic)
		result = ATOMIC_CMPXCH(*(u64 *)addr, oldval, newval);
	else {
		result = *(u64 *)addr;
		COMPILER_READ_BARRIER();
		if (result == oldval)
			*(u64 *)addr = newval;
	}
	COMPILER_BARRIER();
	return result;
}

#define EMU86_EMULATE_ATOMIC_CMPXCH128(addr, oldval, newval, force_atomic) \
	libviocore_atomic_cmpxch128(self, addr, oldval, newval, force_atomic)
LOCAL NONNULL((1)) uint128_t CC
libviocore_atomic_cmpxch128(struct vio_emulate_args *__restrict self,
                            __USER __CHECKED void *addr,
                            uint128_t oldval, uint128_t newval, bool force_atomic) {
	uint128_t result;
	COMPILER_BARRIER();
	if likely(addr == self->vea_ptr) {
		result = vio_cmpxch128(&self->vea_args, self->vea_addr, oldval, newval, force_atomic);
	} else if (force_atomic) {
		__asm__ __volatile__("cmpxchg16b %0"
		                     : "+m" (*(uint128_t *)addr)
		                     , "=a" (uint128_vec64(result)[0])
		                     , "=d" (uint128_vec64(result)[1])
		                     : "a" (uint128_vec64(oldval)[0])
		                     , "d" (uint128_vec64(oldval)[1])
		                     , "b" (uint128_vec64(newval)[0])
		                     , "c" (uint128_vec64(newval)[1])
		                     : "cc");
	} else {
		result = *(uint128_t *)addr;
		COMPILER_READ_BARRIER();
		if (uint128_eq128(result, oldval))
			*(uint128_t *)addr = newval;
	}
	COMPILER_BARRIER();
	return result;
}
#endif /* __x86_64__ */





DECL_END

#define EMU86_EMULATE_DECL INTERN
#define EMU86_EMULATE_ATTR NONNULL((1))
#define EMU86_EMULATE_RETURN      return
#define EMU86_EMULATE_RETURN_TYPE void
#define EMU86_EMULATE_RETURN_UNKNOWN_INSTRUCTION(faultaddr, opcode, op_flags) \
	libviocore_throw_unknown_instruction(self, opcode)
#define EMU86_EMULATE_NOTHROW /* nothing */
#define EMU86_EMULATE_CC CC
#define EMU86_EMULATE_NAME libviocore_emulate
#define EMU86_EMULATE_ARGS struct vio_emulate_args *__restrict self
#define EMU86_EMULATE_HELPER_ATTR  NONNULL((1))
#define EMU86_EMULATE_HELPER_ARGS  struct vio_emulate_args *__restrict self
#define EMU86_EMULATE_HELPER_PARAM self
#define EMU86_EMULATE_TRY_SWITCH \
	TRY
#define EMU86_EMULATE_EXCEPT_SWITCH               \
	EXCEPT {                                      \
		libviocore_complete_except(self, opcode); \
		RETHROW();                                \
	}
#define EMU86_EMULATE_GETOPFLAGS() _CS(emu86_opflagsof)(self->vea_args.va_state)
#define EMU86_EMULATE_ONLY_MEMORY 1 /* _ONLY_ emulate memory-based instructions! */
#ifdef __KERNEL__
#include <sched/cred.h>
#define EMU86_ALLOWED_EFLAGS_MODIFY_MASK() cred_allow_eflags_modify_mask()
#endif /* !__KERNEL__ */
#ifdef __x86_64__
#define EMU86_EMULATE_VM86 0
#else /* __x86_64__ */
#define EMU86_EMULATE_VM86 1
#endif /* !__x86_64__ */
#define EMU86_EMULATE_VM86_GETIF()  0       /* TODO: Get vm86 #IF bit */
#define EMU86_EMULATE_VM86_SETIF(v) (void)0 /* TODO: Set vm86 #IF bit */
#ifdef __KERNEL__
#define EMU86_EMULATE_CHECKUSER 1
#define EMU86_ISUSER()        icpustate_isuser(self->vea_args.va_state)
#if EMU86_EMULATE_VM86
#define EMU86_ISUSER_NOVM86() icpustate_isuser_novm86(self->vea_args.va_state)
#define EMU86_ISVM86()        icpustate_isvm86(self->vea_args.va_state)
#else /* EMU86_EMULATE_VM86 */
#define EMU86_ISUSER_NOVM86() icpustate_isuser(self->vea_args.va_state)
#define EMU86_ISVM86()        0
#endif /* !EMU86_EMULATE_VM86 */
#include <kernel/user.h>
#define EMU86_VALIDATE_READABLE(addr, num_bytes) validate_readable((void const *)(uintptr_t)(addr), num_bytes)
#define EMU86_VALIDATE_WRITABLE(addr, num_bytes) validate_writable((void *)(uintptr_t)(addr), num_bytes)
#else /* __KERNEL__ */
#define EMU86_EMULATE_CHECKUSER 0
#define EMU86_ISUSER() 0
#define EMU86_ISUSER_NOVM86() 0
#define EMU86_ISVM86() 0
#define EMU86_VALIDATE_READABLE(addr, num_bytes) (void)0
#define EMU86_VALIDATE_WRITABLE(addr, num_bytes) (void)0
#endif /* !__KERNEL__ */

#define EMU86_GETFLAGS()            CS(getpflags)(self->vea_args.va_state)
#define EMU86_SETFLAGS(v)           CS(setpflags)(self->vea_args.va_state, v)
#define EMU86_MSKFLAGS(mask, value) CS(mskpflags)(self->vea_args.va_state, mask, value)
#define EMU86_EMULATE_GETPC()       CS(getpc)(self->vea_args.va_state)
#define EMU86_EMULATE_SETPC(v)      CS(setpc)(self->vea_args.va_state, (__uintptr_t)(v))
#define EMU86_EMULATE_GETIP()       EMU86_EMULATE_GETPC()
#define EMU86_EMULATE_SETIP(v)      EMU86_EMULATE_SETPC(v)
#define EMU86_GETSP()               CS(getsp)(self->vea_args.va_state)
#if defined(__x86_64__) || !defined(__KERNEL__)
#define EMU86_SETSP(v) (CS(setsp)(self->vea_args.va_state, (__uintptr_t)(v)))
#else /* __x86_64__ */
#define EMU86_SETSP(v) (self->vea_args.va_state = icpustate_setsp_p(self->vea_args.va_state, (__uintptr_t)(v)))
#endif /* !__x86_64__ */
#define EMU86_GETSP_RAW()  EMU86_GETSP()
#define EMU86_SETSP_RAW(v) EMU86_SETSP(v)

#undef EMU86_GETSEGBASE_IS_NOOP
#undef EMU86_GETSEGBASE_IS_NOOP_DS
#undef EMU86_GETSEGBASE_IS_NOOP_ES
#undef EMU86_GETSEGBASE_IS_NOOP_CS
#undef EMU86_GETSEGBASE_IS_NOOP_SS
#undef EMU86_GETSEGBASE_IS_NOOP_FS
#undef EMU86_GETSEGBASE_IS_NOOP_GS

#ifdef __KERNEL__
#ifdef __x86_64__
/* x86_64 only supports a flat address space for es, cs, ss, and ds */
#define EMU86_GETSEGBASE_IS_NOOP_ES 1
#define EMU86_GETSEGBASE_IS_NOOP_CS 1
#define EMU86_GETSEGBASE_IS_NOOP_SS 1
#define EMU86_GETSEGBASE_IS_NOOP_DS 1
#define EMU86_GETSEGBASE(segment_regno)          \
	((segment_regno) == EMU86_R_FS               \
	 ? __rdfsbase()                              \
	 : (segment_regno) == EMU86_R_GS             \
	   ? (EMU86_ISUSER()                         \
	      ? (void *)__rdmsr(IA32_KERNEL_GS_BASE) \
	      : __rdgsbase())                        \
	   : 0)
#define EMU86_GETDSBASE() 0
#define EMU86_GETESBASE() 0
#define EMU86_GETCSBASE() 0
#define EMU86_GETSSBASE() 0
#define EMU86_GETFSBASE() __rdfsbase()
#define EMU86_GETGSBASE() (EMU86_ISUSER() ? (void *)__rdmsr(IA32_KERNEL_GS_BASE) : __rdgsbase())
#else /* __x86_64__ */
/* 32-bit mode supports non-zero bases for any segment! */
DECL_BEGIN
#define EMU86_GETSEGBASE(segment_regno) \
	i386_segment_base(self->vea_args.va_state, segment_regno)
#define EMU86_GETDSBASE() EMU86_GETSEGBASE(EMU86_R_DS)
#define EMU86_GETESBASE() EMU86_GETSEGBASE(EMU86_R_ES)
#define EMU86_GETCSBASE() EMU86_GETSEGBASE(EMU86_R_CS)
#define EMU86_GETSSBASE() EMU86_GETSEGBASE(EMU86_R_SS)
#define EMU86_GETFSBASE() EMU86_GETSEGBASE(EMU86_R_FS)
#define EMU86_GETGSBASE() EMU86_GETSEGBASE(EMU86_R_GS)
PRIVATE WUNUSED NONNULL((1)) u32
NOTHROW(CC i386_segment_base)(struct icpustate *__restrict state,
                              u8 segment_regno) {
	u32 result;
	u16 segment_index;
	pflag_t was;
	struct segment *seg;
	struct desctab dt;
	/* Determine the segment's index. */
	switch (segment_regno) {
	case EMU86_R_ES: segment_index = icpustate_getes(state); break;
	case EMU86_R_CS: segment_index = icpustate_getcs(state); break;
	case EMU86_R_SS: segment_index = icpustate_getcs(state); break;
	case EMU86_R_DS: segment_index = icpustate_getds(state); break;
	case EMU86_R_FS: segment_index = icpustate_getfs(state); break;
	case EMU86_R_GS: segment_index = __rdgs(); break;
	default: __builtin_unreachable();
	}
	was = PREEMPTION_PUSHOFF();
	__sgdt(&dt);
	if (segment_index & 4) {
		/* LDT index. */
		u16 ldt = __sldt() & ~7;
		if unlikely(!ldt || ldt > dt.dt_limit) {
			PREEMPTION_POP(was);
			/* Deal with an invalid / disabled LDT by throwing an error indicating an invalid LDT. */
			THROW(E_ILLEGAL_INSTRUCTION_REGISTER,
			      0,                                    /* opcode */
			      E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD, /* what */
			      X86_REGISTER_MISC_LDT,                /* regno */
			      ldt);                                 /* regval */
		}
		seg = (struct segment *)((byte_t *)dt.dt_base + ldt);
		dt.dt_base  = segment_rdbaseX(seg);
		dt.dt_limit = (uint16_t)segment_rdlimit(seg);
	}
	segment_index &= ~7;
	if (!segment_index || segment_index > dt.dt_limit) {
		PREEMPTION_POP(was);
		THROW(E_ILLEGAL_INSTRUCTION_REGISTER,
		      0,                                       /* opcode */
		      E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD,    /* what */
		      X86_REGISTER_SEGMENT_ES + segment_regno, /* regno */
		      segment_index);                          /* regval */
	}
	seg = (struct segment *)((byte_t *)dt.dt_base + segment_index);
	result = segment_rdbaseX(seg);
	PREEMPTION_POP(was);
	return result;
}
DECL_END
#endif /* !__x86_64__ */
#else /* __KERNEL__ */
/* If the base of any of these segments wasn't 0, then this library
 * couldn't even work (since C expects a flat address space, and this
 * library is written in C) */
#define EMU86_GETSEGBASE_IS_NOOP_ES 1
#define EMU86_GETSEGBASE_IS_NOOP_CS 1
#define EMU86_GETSEGBASE_IS_NOOP_SS 1
#define EMU86_GETSEGBASE_IS_NOOP_DS 1
#define EMU86_GETSEGBASE(segment_regno) \
	((segment_regno) == EMU86_R_FS      \
	 ? __rdfsbase()                     \
	 : (segment_regno) == EMU86_R_GS    \
	   ? __rdgsbase()                   \
	   : 0)
#define EMU86_GETDSBASE() 0
#define EMU86_GETESBASE() 0
#define EMU86_GETCSBASE() 0
#define EMU86_GETSSBASE() 0
#define EMU86_GETFSBASE() __rdfsbase()
#define EMU86_GETGSBASE() __rdgsbase()
#endif /* !__KERNEL__ */
#define EMU86_SEGADDR(segbase, segoffset) ((segbase) + (segoffset))
#define EMU86_GETES()  CS(getes)(self->vea_args.va_state)
#define EMU86_SETES(v) CS(setes)(self->vea_args.va_state, v)
#define EMU86_GETCS()  CS(getcs)(self->vea_args.va_state)
#define EMU86_SETCS(v) CS(setcs)(self->vea_args.va_state, v)
#define EMU86_GETSS()  CS(getss)(self->vea_args.va_state)
#define EMU86_SETSS(v) CS(setss)(self->vea_args.va_state, v)
#define EMU86_GETDS()  CS(getds)(self->vea_args.va_state)
#define EMU86_SETDS(v) CS(setds)(self->vea_args.va_state, v)
#define EMU86_GETFS()  CS(getfs)(self->vea_args.va_state)
#define EMU86_SETFS(v) CS(setfs)(self->vea_args.va_state, v)
#define EMU86_GETGS()  CS(getgs)(self->vea_args.va_state)
#define EMU86_SETGS(v) CS(setgs)(self->vea_args.va_state, v)
#define EMU86_EMULATE_PUSH(new_sp, num_bytes) (void)0
#define EMU86_EMULATE_POP(old_sp, num_bytes) (void)0


DECL_BEGIN

#ifdef __x86_64__
#define X86_GPREGCOUNT 16
#else /* __x86_64__ */
#define X86_GPREGCOUNT 8
#endif /* !__x86_64__ */

#ifdef __KERNEL__
#ifdef __x86_64__
PRIVATE u8 const CS_breg_offsets[16] = {
	/* [EMU86_R_AL]   = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RAX,     /* %al */
	/* [EMU86_R_CL]   = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RCX,     /* %cl */
	/* [EMU86_R_DL]   = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDX,     /* %dl */
	/* [EMU86_R_BL]   = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBX,     /* %bl */
	/* [EMU86_R_AH]   = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RAX + 1, /* %ah */
	/* [EMU86_R_CH]   = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RCX + 1, /* %ch */
	/* [EMU86_R_DH]   = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDX + 1, /* %dh */
	/* [EMU86_R_BH]   = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBX + 1, /* %bh */
	/* [EMU86_R_R8L]  = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R8,      /* %r8l */
	/* [EMU86_R_R9L]  = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R9,      /* %r9l */
	/* [EMU86_R_R10L] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R10,     /* %r10l */
	/* [EMU86_R_R11L] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R11,     /* %r11l */
	/* [EMU86_R_R12L] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R12,     /* %r12l */
	/* [EMU86_R_R13L] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R13,     /* %r13l */
	/* [EMU86_R_R14L] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R14,     /* %r14l */
	/* [EMU86_R_R15L] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R15,     /* %r15l */
};
PRIVATE u8 const CS_reg_offsets[16] = {
	/* [EMU86_R_RAX] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RAX, /* %rax */
	/* [EMU86_R_RCX] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RCX, /* %rcx */
	/* [EMU86_R_RDX] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDX, /* %rdx */
	/* [EMU86_R_RBX] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBX, /* %rbx */
	/* [EMU86_R_RSP] = */ 0,                                                 /* %rsp */
	/* [EMU86_R_RBP] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RBP, /* %rbp */
	/* [EMU86_R_RSI] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RSI, /* %rsi */
	/* [EMU86_R_RDI] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RDI, /* %rdi */
	/* [EMU86_R_R8]  = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R8,  /* %r8 */
	/* [EMU86_R_R9]  = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R9,  /* %r9 */
	/* [EMU86_R_R10] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R10, /* %r10 */
	/* [EMU86_R_R11] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R11, /* %r11 */
	/* [EMU86_R_R12] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R12, /* %r12 */
	/* [EMU86_R_R13] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R13, /* %r13 */
	/* [EMU86_R_R14] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R14, /* %r14 */
	/* [EMU86_R_R15] = */ OFFSET_ICPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_R15, /* %r15 */
};
#else /* __x86_64__ */
PRIVATE u8 const CS_breg_offsets[8] = {
	/* [EMU86_R_AL] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX,     /* %al */
	/* [EMU86_R_CL] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ECX,     /* %cl */
	/* [EMU86_R_DL] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX,     /* %dl */
	/* [EMU86_R_BL] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBX,     /* %bl */
	/* [EMU86_R_AH] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX + 1, /* %ah */
	/* [EMU86_R_CH] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ECX + 1, /* %ch */
	/* [EMU86_R_DH] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX + 1, /* %dh */
	/* [EMU86_R_BH] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBX + 1, /* %bh */
};
PRIVATE u8 const CS_reg_offsets[8] = {
	/* [EMU86_R_EAX] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EAX, /* %eax */
	/* [EMU86_R_ECX] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ECX, /* %ecx */
	/* [EMU86_R_EDX] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDX, /* %edx */
	/* [EMU86_R_EBX] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBX, /* %ebx */
	/* [EMU86_R_ESP] = */ 0,                                           /* %esp */
	/* [EMU86_R_EBP] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EBP, /* %ebp */
	/* [EMU86_R_ESI] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_ESI, /* %esi */
	/* [EMU86_R_EDI] = */ OFFSET_ICPUSTATE_GPREGS + OFFSET_GPREGS_EDI, /* %edi */
};
#endif /* !__x86_64__ */
#else /* __KERNEL__ */
PRIVATE u8 const CS_breg_offsets[X86_GPREGCOUNT] = {
	/* [EMU86_R_AL] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PAX,     /* %al */
	/* [EMU86_R_CL] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PCX,     /* %cl */
	/* [EMU86_R_DL] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PDX,     /* %dl */
	/* [EMU86_R_BL] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PBX,     /* %bl */
	/* [EMU86_R_AH] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PAX + 1, /* %ah */
	/* [EMU86_R_CH] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PCX + 1, /* %ch */
	/* [EMU86_R_DH] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PDX + 1, /* %dh */
	/* [EMU86_R_BH] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PBX + 1, /* %bh */
#ifdef __x86_64__
	/* [EMU86_R_R8L]  = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R8,    /* %r8l */
	/* [EMU86_R_R9L]  = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R9,    /* %r9l */
	/* [EMU86_R_R10L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R10,   /* %r10l */
	/* [EMU86_R_R11L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R11,   /* %r11l */
	/* [EMU86_R_R12L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R12,   /* %r12l */
	/* [EMU86_R_R13L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R13,   /* %r13l */
	/* [EMU86_R_R14L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R14,   /* %r14l */
	/* [EMU86_R_R15L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R15,   /* %r15l */
#endif /* __x86_64__ */
};
PRIVATE u8 const CS_reg_offsets[X86_GPREGCOUNT] = {
	/* [EMU86_R_EAX] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PAX,  /* %(e|r)ax */
	/* [EMU86_R_ECX] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PCX,  /* %(e|r)cx */
	/* [EMU86_R_EDX] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PDX,  /* %(e|r)dx */
	/* [EMU86_R_EBX] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PBX,  /* %(e|r)bx */
	/* [EMU86_R_ESP] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PSP,  /* %(e|r)sp */
	/* [EMU86_R_EBP] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PBP,  /* %(e|r)bp */
	/* [EMU86_R_ESI] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PSI,  /* %(e|r)si */
	/* [EMU86_R_EDI] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PDI,  /* %(e|r)di */
#ifdef __x86_64__
	/* [EMU86_R_R8L]  = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R8,  /* %r8 */
	/* [EMU86_R_R9L]  = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R9,  /* %r9 */
	/* [EMU86_R_R10L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R10, /* %r10 */
	/* [EMU86_R_R11L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R11, /* %r11 */
	/* [EMU86_R_R12L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R12, /* %r12 */
	/* [EMU86_R_R13L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R13, /* %r13 */
	/* [EMU86_R_R14L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R14, /* %r14 */
	/* [EMU86_R_R15L] = */ OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R15, /* %r15 */
#endif /* __x86_64__ */
};
#endif /* !__KERNEL__ */


#ifdef __x86_64__
#define EMU86_GETREGB(regno, op_flags) \
	CS_getregb(self->vea_args.va_state, regno, op_flags)
PRIVATE WUNUSED ATTR_PURE NONNULL((1)) u8
NOTHROW(CC CS_getregb)(vio_cpustate_t const *__restrict state,
                       u8 regno, emu86_opflags_t op_flags) {
	regno &= (X86_GPREGCOUNT - 1);
	if (op_flags & EMU86_F_HASREX) {
#ifdef __KERNEL__
		if (regno == EMU86_R_SPL)
			return (u8)icpustate64_getrsp(state);
#endif /* __KERNEL__ */
		return *(u8 const *)((byte_t const *)state + CS_reg_offsets[regno]);
	}
	return *(u8 const *)((byte_t const *)state + CS_breg_offsets[regno]);
}
#define EMU86_SETREGB(regno, value, op_flags) \
	CS_setregb(self->vea_args.va_state, regno, value, op_flags)
PRIVATE NONNULL((1)) void
NOTHROW(CC CS_setregb)(vio_cpustate_t *__restrict state,
                       u8 regno, u8 value, emu86_opflags_t op_flags) {
	regno &= (X86_GPREGCOUNT - 1);
	if (op_flags & EMU86_F_HASREX) {
#ifdef __KERNEL__
		if (regno == EMU86_R_SPL) {
			icpustate64_setrsp(state,
			                   (u64)(icpustate64_getrsp(state) & ~0xff) |
			                   (u64)value);
		} else
#endif /* __KERNEL__ */
		{
			*(u8 *)((byte_t *)state + CS_reg_offsets[regno]) = value;
		}
	} else {
		*(u8 *)((byte_t *)state + CS_breg_offsets[regno]) = value;
	}
}
#else /* __x86_64__ */
#define EMU86_GETREGB(regno, ...) \
	(*(u8 const *)((byte_t const *)self->vea_args.va_state + CS_breg_offsets[(regno) & (X86_GPREGCOUNT - 1)]))
#define EMU86_SETREGB(regno, value, ...) \
	(*(u8 *)((byte_t *)self->vea_args.va_state + CS_breg_offsets[(regno) & (X86_GPREGCOUNT - 1)]) = (value))
#endif /* !__x86_64__ */

#define _EMU86_GETREGW(state, regno) (*(u16 const *)((byte_t const *)state + CS_reg_offsets[regno]))
#define _EMU86_GETREGL(state, regno) (*(u32 const *)((byte_t const *)state + CS_reg_offsets[regno]))
#define _EMU86_SETREGW(state, regno, value) (*(uintptr_t *)((byte_t *)state + CS_reg_offsets[regno]) = (u16)(value))
#define _EMU86_SETREGL(state, regno, value) (*(uintptr_t *)((byte_t *)state + CS_reg_offsets[regno]) = (u32)(value))
#ifdef __x86_64__
#define _EMU86_GETREGQ(state, regno) (*(u64 const *)((byte_t const *)state + CS_reg_offsets[regno]))
#define _EMU86_SETREGQ(state, regno, value) (*(uintptr_t *)((byte_t *)state + CS_reg_offsets[regno]) = (u64)(value))
#endif /* __x86_64__ */

#ifdef __KERNEL__
#define EMU86_GETREGW(regno) CS_getregw(self->vea_args.va_state, regno)
PRIVATE WUNUSED NONNULL((1)) u16
NOTHROW(CC CS_getregw)(vio_cpustate_t *__restrict state, u8 regno) {
	regno &= (X86_GPREGCOUNT - 1);
	if (regno == EMU86_R_SP) {
		return (u16)icpustate_getsp(state);
	} else {
		return _EMU86_GETREGW(state, regno);
	}
}
#define EMU86_GETREGL(regno) CS_getregl(self->vea_args.va_state, regno)
PRIVATE WUNUSED NONNULL((1)) u32
NOTHROW(CC CS_getregl)(vio_cpustate_t *__restrict state, u8 regno) {
	regno &= (X86_GPREGCOUNT - 1);
	if (regno == EMU86_R_ESP) {
		return (u32)icpustate_getsp(state);
	} else {
		return _EMU86_GETREGL(state, regno);
	}
}
#ifdef __x86_64__
#define EMU86_GETREGQ(regno)        CS_getregq(self->vea_args.va_state, regno)
PRIVATE WUNUSED NONNULL((1)) u64
NOTHROW(CC CS_getregq)(vio_cpustate_t *__restrict state, u8 regno) {
	regno &= (X86_GPREGCOUNT - 1);
	if (regno == EMU86_R_RSP) {
		return icpustate64_getrsp(state);
	} else {
		return _EMU86_GETREGQ(state, regno);
	}
}
#define EMU86_SETREGW(regno, value) CS_setregw(self->vea_args.va_state, regno, value)
PRIVATE WUNUSED NONNULL((1)) void
NOTHROW(CC CS_setregw)(vio_cpustate_t *__restrict state, u8 regno, u16 value) {
	regno &= (X86_GPREGCOUNT - 1);
	if (regno == EMU86_R_SP) {
		icpustate64_setrsp(state, (u64)value);
	} else {
		_EMU86_SETREGW(state, regno, value);
	}
}
#define EMU86_SETREGL(regno, value) CS_setregl(self->vea_args.va_state, regno, value)
PRIVATE WUNUSED NONNULL((1)) void
NOTHROW(CC CS_setregl)(vio_cpustate_t *__restrict state, u8 regno, u32 value) {
	regno &= (X86_GPREGCOUNT - 1);
	if (regno == EMU86_R_ESP) {
		icpustate64_setrsp(state, (u64)value);
	} else {
		_EMU86_SETREGL(state, regno, value);
	}
}
#define EMU86_SETREGQ(regno, value) CS_setregq(self->vea_args.va_state, regno, value)
PRIVATE WUNUSED NONNULL((1)) void
NOTHROW(CC CS_setregq)(vio_cpustate_t *__restrict state, u8 regno, u64 value) {
	regno &= (X86_GPREGCOUNT - 1);
	if (regno == EMU86_R_RSP) {
		icpustate64_setrsp(state, value);
	} else {
		_EMU86_SETREGQ(state, regno, value);
	}
}
#else /* __x86_64__ */
#define EMU86_SETREGW(regno, value) CS_setregw(self, regno, value)
PRIVATE WUNUSED NONNULL((1)) void
NOTHROW(CC CS_setregw)(struct vio_emulate_args *__restrict self, u8 regno, u16 value) {
	regno &= (X86_GPREGCOUNT - 1);
	if (regno == EMU86_R_SP) {
		self->vea_args.va_state = icpustate32_setesp_p(self->vea_args.va_state, (u64)value);
	} else {
		_EMU86_SETREGW(self->vea_args.va_state, regno, value);
	}
}
#define EMU86_SETREGL(regno, value) CS_setregl(self, regno, value)
PRIVATE WUNUSED NONNULL((1)) void
NOTHROW(CC CS_setregl)(struct vio_emulate_args *__restrict self, u8 regno, u32 value) {
	regno &= (X86_GPREGCOUNT - 1);
	if (regno == EMU86_R_ESP) {
		self->vea_args.va_state = icpustate32_setesp_p(self->vea_args.va_state, (u64)value);
	} else {
		_EMU86_SETREGL(self->vea_args.va_state, regno, value);
	}
}
#endif /* __x86_64__ */
#else /* __KERNEL__ */
#define EMU86_GETREGW(regno) _EMU86_GETREGW(self->vea_args.va_state, (regno) & (X86_GPREGCOUNT - 1))
#define EMU86_GETREGL(regno) _EMU86_GETREGL(self->vea_args.va_state, (regno) & (X86_GPREGCOUNT - 1))
#define EMU86_SETREGW(regno, value) _EMU86_SETREGW(self->vea_args.va_state, (regno) & (X86_GPREGCOUNT - 1), value)
#define EMU86_SETREGL(regno, value) _EMU86_SETREGL(self->vea_args.va_state, (regno) & (X86_GPREGCOUNT - 1), value)
#ifdef __x86_64__
#define EMU86_GETREGQ(regno) _EMU86_GETREGQ(self->vea_args.va_state, (regno) & (X86_GPREGCOUNT - 1))
#define EMU86_SETREGQ(regno, value) _EMU86_SETREGQ(self->vea_args.va_state, (regno) & (X86_GPREGCOUNT - 1), value)
#endif /* __x86_64__ */
#endif /* !__KERNEL__ */

#ifdef __x86_64__
#define _EMU86_REGP_MASK(op_flags) (EMU86_F_IS64(op_flags) ? (u64)UINT64_MAX : (u64)UINT32_MAX)
#define EMU86_GETREGP(regno, op_flags)        (EMU86_GETREGQ(regno) & _EMU86_REGP_MASK(op_flags))
#define EMU86_SETREGP(regno, value, op_flags) (EMU86_SETREGQ(regno, (value) & _EMU86_REGP_MASK(op_flags)))
#else /* __x86_64__ */
#define _EMU86_REGP_MASK(op_flags) (EMU86_F_IS32(op_flags) ? (u32)UINT32_MAX : (u32)UINT16_MAX)
#define EMU86_GETREGP(regno, op_flags)        (EMU86_GETREGL(regno) & _EMU86_REGP_MASK(op_flags))
#define EMU86_SETREGP(regno, value, op_flags) (EMU86_SETREGL(regno, (value) & _EMU86_REGP_MASK(op_flags)))
#endif /* !__x86_64__ */

#ifdef __KERNEL__
#define _CPUSTATE_GPREGS self->vea_args.va_state->ics_gpregs
#else /* __KERNEL__ */
#define _CPUSTATE_GPREGS self->vea_args.va_state->ucs_gpregs
#endif /* !__KERNEL__ */

#define EMU86_GETAL() ((u8)_CPUSTATE_GPREGS.gp_pax)
#define EMU86_GETCL() ((u8)_CPUSTATE_GPREGS.gp_pcx)
#define EMU86_GETDL() ((u8)_CPUSTATE_GPREGS.gp_pdx)
#define EMU86_GETBL() ((u8)_CPUSTATE_GPREGS.gp_pbx)
#define EMU86_GETAH() ((u8)(_CPUSTATE_GPREGS.gp_pax >> 8))
#define EMU86_GETCH() ((u8)(_CPUSTATE_GPREGS.gp_pcx >> 8))
#define EMU86_GETDH() ((u8)(_CPUSTATE_GPREGS.gp_pdx >> 8))
#define EMU86_GETBH() ((u8)(_CPUSTATE_GPREGS.gp_pbx >> 8))
#define EMU86_SETAL(value) (((u8 *)&_CPUSTATE_GPREGS.gp_pax)[0] = (u8)(value))
#define EMU86_SETCL(value) (((u8 *)&_CPUSTATE_GPREGS.gp_pcx)[0] = (u8)(value))
#define EMU86_SETDL(value) (((u8 *)&_CPUSTATE_GPREGS.gp_pdx)[0] = (u8)(value))
#define EMU86_SETBL(value) (((u8 *)&_CPUSTATE_GPREGS.gp_pbx)[0] = (u8)(value))
#define EMU86_SETAH(value) (((u8 *)&_CPUSTATE_GPREGS.gp_pax)[1] = (u8)(value))
#define EMU86_SETCH(value) (((u8 *)&_CPUSTATE_GPREGS.gp_pcx)[1] = (u8)(value))
#define EMU86_SETDH(value) (((u8 *)&_CPUSTATE_GPREGS.gp_pdx)[1] = (u8)(value))
#define EMU86_SETBH(value) (((u8 *)&_CPUSTATE_GPREGS.gp_pbx)[1] = (u8)(value))
#define EMU86_GETAX() ((u16)_CPUSTATE_GPREGS.gp_pax)
#define EMU86_GETCX() ((u16)_CPUSTATE_GPREGS.gp_pcx)
#define EMU86_GETDX() ((u16)_CPUSTATE_GPREGS.gp_pdx)
#define EMU86_GETBX() ((u16)_CPUSTATE_GPREGS.gp_pbx)
#define EMU86_GETBP() ((u16)_CPUSTATE_GPREGS.gp_pbp)
#define EMU86_GETSI() ((u16)_CPUSTATE_GPREGS.gp_psi)
#define EMU86_GETDI() ((u16)_CPUSTATE_GPREGS.gp_pdi)
#define EMU86_SETAX(value) (_CPUSTATE_GPREGS.gp_pax = (uintptr_t)(u16)(value))
#define EMU86_SETCX(value) (_CPUSTATE_GPREGS.gp_pcx = (uintptr_t)(u16)(value))
#define EMU86_SETDX(value) (_CPUSTATE_GPREGS.gp_pdx = (uintptr_t)(u16)(value))
#define EMU86_SETBX(value) (_CPUSTATE_GPREGS.gp_pbx = (uintptr_t)(u16)(value))
#define EMU86_SETBP(value) (_CPUSTATE_GPREGS.gp_pbp = (uintptr_t)(u16)(value))
#define EMU86_SETSI(value) (_CPUSTATE_GPREGS.gp_psi = (uintptr_t)(u16)(value))
#define EMU86_SETDI(value) (_CPUSTATE_GPREGS.gp_pdi = (uintptr_t)(u16)(value))
#define EMU86_GETEAX() ((u32)_CPUSTATE_GPREGS.gp_pax)
#define EMU86_GETECX() ((u32)_CPUSTATE_GPREGS.gp_pcx)
#define EMU86_GETEDX() ((u32)_CPUSTATE_GPREGS.gp_pdx)
#define EMU86_GETEBX() ((u32)_CPUSTATE_GPREGS.gp_pbx)
#define EMU86_GETEBP() ((u32)_CPUSTATE_GPREGS.gp_pbp)
#define EMU86_GETESI() ((u32)_CPUSTATE_GPREGS.gp_psi)
#define EMU86_GETEDI() ((u32)_CPUSTATE_GPREGS.gp_pdi)
#define EMU86_SETEAX(value) (_CPUSTATE_GPREGS.gp_pax = (uintptr_t)(u32)(value))
#define EMU86_SETECX(value) (_CPUSTATE_GPREGS.gp_pcx = (uintptr_t)(u32)(value))
#define EMU86_SETEDX(value) (_CPUSTATE_GPREGS.gp_pdx = (uintptr_t)(u32)(value))
#define EMU86_SETEBX(value) (_CPUSTATE_GPREGS.gp_pbx = (uintptr_t)(u32)(value))
#define EMU86_SETEBP(value) (_CPUSTATE_GPREGS.gp_pbp = (uintptr_t)(u32)(value))
#define EMU86_SETESI(value) (_CPUSTATE_GPREGS.gp_psi = (uintptr_t)(u32)(value))
#define EMU86_SETEDI(value) (_CPUSTATE_GPREGS.gp_pdi = (uintptr_t)(u32)(value))
#ifdef __x86_64__
#define EMU86_GETRAX() ((u64)_CPUSTATE_GPREGS.gp_rax)
#define EMU86_GETRCX() ((u64)_CPUSTATE_GPREGS.gp_rcx)
#define EMU86_GETRDX() ((u64)_CPUSTATE_GPREGS.gp_rdx)
#define EMU86_GETRBX() ((u64)_CPUSTATE_GPREGS.gp_rbx)
#define EMU86_GETRBP() ((u64)_CPUSTATE_GPREGS.gp_rbp)
#define EMU86_GETRSI() ((u64)_CPUSTATE_GPREGS.gp_rsi)
#define EMU86_GETRDI() ((u64)_CPUSTATE_GPREGS.gp_rdi)
#define EMU86_SETRAX(value) (_CPUSTATE_GPREGS.gp_rax = (u64)(value))
#define EMU86_SETRCX(value) (_CPUSTATE_GPREGS.gp_rcx = (u64)(value))
#define EMU86_SETRDX(value) (_CPUSTATE_GPREGS.gp_rdx = (u64)(value))
#define EMU86_SETRBX(value) (_CPUSTATE_GPREGS.gp_rbx = (u64)(value))
#define EMU86_SETRBP(value) (_CPUSTATE_GPREGS.gp_rbp = (u64)(value))
#define EMU86_SETRSI(value) (_CPUSTATE_GPREGS.gp_rsi = (u64)(value))
#define EMU86_SETRDI(value) (_CPUSTATE_GPREGS.gp_rdi = (u64)(value))
#endif /* __x86_64__ */
#define EMU86_GETPAX(op_flags)        ((uintptr_t)(_CPUSTATE_GPREGS.gp_pax & _EMU86_REGP_MASK(op_flags)))
#define EMU86_GETPCX(op_flags)        ((uintptr_t)(_CPUSTATE_GPREGS.gp_pcx & _EMU86_REGP_MASK(op_flags)))
#define EMU86_GETPDX(op_flags)        ((uintptr_t)(_CPUSTATE_GPREGS.gp_pdx & _EMU86_REGP_MASK(op_flags)))
#define EMU86_GETPBX(op_flags)        ((uintptr_t)(_CPUSTATE_GPREGS.gp_pbx & _EMU86_REGP_MASK(op_flags)))
#define EMU86_GETPBP(op_flags)        ((uintptr_t)(_CPUSTATE_GPREGS.gp_pbp & _EMU86_REGP_MASK(op_flags)))
#define EMU86_GETPSI(op_flags)        ((uintptr_t)(_CPUSTATE_GPREGS.gp_psi & _EMU86_REGP_MASK(op_flags)))
#define EMU86_GETPDI(op_flags)        ((uintptr_t)(_CPUSTATE_GPREGS.gp_pdi & _EMU86_REGP_MASK(op_flags)))
#define EMU86_SETPAX(value, op_flags) (_CPUSTATE_GPREGS.gp_pax = (uintptr_t)(value) & _EMU86_REGP_MASK(op_flags))
#define EMU86_SETPCX(value, op_flags) (_CPUSTATE_GPREGS.gp_pcx = (uintptr_t)(value) & _EMU86_REGP_MASK(op_flags))
#define EMU86_SETPDX(value, op_flags) (_CPUSTATE_GPREGS.gp_pdx = (uintptr_t)(value) & _EMU86_REGP_MASK(op_flags))
#define EMU86_SETPBX(value, op_flags) (_CPUSTATE_GPREGS.gp_pbx = (uintptr_t)(value) & _EMU86_REGP_MASK(op_flags))
#define EMU86_SETPBP(value, op_flags) (_CPUSTATE_GPREGS.gp_pbp = (uintptr_t)(value) & _EMU86_REGP_MASK(op_flags))
#define EMU86_SETPSI(value, op_flags) (_CPUSTATE_GPREGS.gp_psi = (uintptr_t)(value) & _EMU86_REGP_MASK(op_flags))
#define EMU86_SETPDI(value, op_flags) (_CPUSTATE_GPREGS.gp_pdi = (uintptr_t)(value) & _EMU86_REGP_MASK(op_flags))
#define EMU86_EMULATE_THROW_BOUNDERR(bound_idx, bound_min, bound_max) \
	THROW(E_INDEX_ERROR_OUT_OF_BOUNDS, bound_idx, bound_min, bound_max)

DECL_END

/* Use relative include to force rebuild on change, and prevent -Wsystem-headers */
#if 1
#include "../../../../include/libemu86/emulate.c.inl"
#else
#include <libemu86/emulate.c.inl>
#endif


DECL_BEGIN
DEFINE_PUBLIC_ALIAS(viocore_emulate, libviocore_emulate);
DECL_END

#endif /* LIBVIO_CONFIG_ENABLED */

#endif /* !GUARD_LIBVIOCORE_ARCH_I386_VIOCORE_C */