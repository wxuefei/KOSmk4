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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_TSS64_S
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_TSS64_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <kos/kernel/gdt.h>
#include <kos/kernel/paging.h>

.section .data.percpu.tss
INTERN_OBJECT(__kernel_percpu_tss)
	/* u32 __t_zero0; */ .int  0
	EXTERN(__kernel_boottask_stack)
	/* u64   t_rsp0;  */ .quad (__kernel_boottask_stack + KERNEL_STACKSIZE)
	/* u64   t_rsp1;  */ .quad (__kernel_boottask_stack + KERNEL_STACKSIZE)
	/* u64   t_rsp2;  */ .quad (__kernel_boottask_stack + KERNEL_STACKSIZE)
	/* u32 __t_zero1; */ .int  0
	/* u32 __t_zero2; */ .int  0
	EXTERN(__bootcpu_x86_df_stack)
	/* u64   t_ist1;  */ .quad (__bootcpu_x86_df_stack + KERNEL_DF_STACKSIZE)
	/* u64   t_ist2;  */ .quad (__bootcpu_x86_df_stack + KERNEL_DF_STACKSIZE)
	/* u64   t_ist3;  */ .quad (__bootcpu_x86_df_stack + KERNEL_DF_STACKSIZE)
	/* u64   t_ist4;  */ .quad (__bootcpu_x86_df_stack + KERNEL_DF_STACKSIZE)
	/* u64   t_ist5;  */ .quad (__bootcpu_x86_df_stack + KERNEL_DF_STACKSIZE)
	/* u64   t_ist6;  */ .quad (__bootcpu_x86_df_stack + KERNEL_DF_STACKSIZE)
	/* u64   t_ist7;  */ .quad (__bootcpu_x86_df_stack + KERNEL_DF_STACKSIZE)
	/* u32 __t_zero3; */ .int  0
	/* u32 __t_zero4; */ .int  0
	/* u16 __t_zero5; */ .word 0
	EXTERN(__x86_cputss_iob_offset)
	/* u16   t_iomap; */ .word __x86_cputss_iob_offset
END(__kernel_percpu_tss)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_TSS64_S */
