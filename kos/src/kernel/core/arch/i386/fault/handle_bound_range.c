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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_BOUND_RANGE_C
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_BOUND_RANGE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <kernel/x86/fault.h> /* x86_handle_bound_range() */
#include <kernel/x86/idt.h>   /* IDT_CONFIG_ISTRAP() */
#include <sched/except-handler.h>
#include <sched/task.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <asm/registers.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <libinstrlen/instrlen.h>

#include "decode.h"

DECL_BEGIN


INTERN struct icpustate *FCALL
x86_handle_bound_range(struct icpustate *__restrict state) {
	STATIC_ASSERT(IDT_CONFIG_ISTRAP(0x05)); /* #BR  Bound Range */
	byte_t const *pc;
	emu86_opcode_t opcode;
	emu86_opflags_t flags;
	uintptr_t bound_index, bound_min, bound_max;
	pc = (byte_t *)icpustate_getpc(state);
	PERTASK_SET(this_exception_faultaddr, (void *)pc);
	flags     = emu86_opflagsof_icpustate(state);
	pc        = emu86_opcode_decode(pc, &opcode, &flags);
	bound_min = bound_index = bound_max = 0;
	if (opcode == EMU86_OPCODE_ENCODE(0x62)) {
		struct emu86_modrm mod;
		/* 62 /r      BOUND r16, m16&16      Check if r16 (array index) is within bounds specified by m16&16
		 * 62 /r      BOUND r32, m32&32      Check if r32 (array index) is within bounds specified by m32&32 */
		pc = emu86_modrm_decode(pc, &mod, flags);
		TRY {
			byte_t *addr;
			addr = (byte_t *)x86_decode_modrmgetmem(state, &mod, flags);
			/* If the interrupt originated for user-space, make sure to validate
			 * the address bounds structure, so-as not to leak kernel memory. */
			if (icpustate_isuser(state))
				validate_readable(addr, (flags & EMU86_F_OP16) ? 4 : 8);
			if (flags & EMU86_F_OP16) {
				bound_index = modrm_getregw(state, &mod, flags);
				bound_min   = *(u16 *)(addr + 0);
				bound_max   = *(u16 *)(addr + 2);
			} else {
				bound_index = modrm_getregl(state, &mod, flags);
				bound_min   = *(u32 *)(addr + 0);
				bound_max   = *(u32 *)(addr + 4);
			}
		} EXCEPT {
			icpustate_setpc(state, (uintptr_t)pc);
			RETHROW();
		}
		if ((s32)bound_index >= (s32)bound_min &&
		    (s32)bound_index <= (s32)bound_max) {
			/* Race condition: the CPU read bad bounds, but some other thread
			 *                 must have modified the bounds before we got to
			 *                 read them. - Just ignore this and act as though
			 *                 this exception has never gotten raised! */
			icpustate_setpc(state, (uintptr_t)pc);
			return state;
		}
	} else {
		byte_t *next_pc;
		next_pc = (byte_t *)icpustate_getpc(state);
		next_pc = instruction_succ_nx(next_pc, instrlen_isa_from_icpustate(state));
		if (next_pc)
			pc = next_pc;
	}
	PERTASK_SET(this_exception_code,
	            ERROR_CODEOF(E_INDEX_ERROR_OUT_OF_BOUNDS));
	PERTASK_SET(this_exception_pointers[0], bound_index);
	PERTASK_SET(this_exception_pointers[1], bound_min);
	PERTASK_SET(this_exception_pointers[2], bound_max);
	{
		unsigned int i;
		for (i = 3; i < EXCEPTION_DATA_POINTERS; ++i)
			PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
#if EXCEPT_BACKTRACE_SIZE != 0
		for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i)
			PERTASK_SET(this_exception_trace[i], (void *)0);
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	}
	icpustate_setpc(state, (uintptr_t)pc);
	x86_userexcept_unwind_interrupt(state);
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_BOUND_RANGE_C */
