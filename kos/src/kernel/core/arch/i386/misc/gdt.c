/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_GDT_C
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_GDT_C 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */

#include <kernel/compiler.h>

#include <kernel/vm.h>
#include <kernel/x86/gdt.h>
#include <kernel/x86/syscall-tables.h> /* CONFIG_X86_EMULATE_LCALL7 */
#include <sched/pertask.h>
#include <sched/task.h>

DECL_BEGIN

/* Assert architectural requirements for segment indices. */
STATIC_ASSERT(SEGMENT_KERNEL_CODE == SEGMENT_KERNEL_CODE);
STATIC_ASSERT(SEGMENT_KERNEL_DATA == SEGMENT_KERNEL_CODE + 8);
STATIC_ASSERT(SEGMENT_USER_CODE32 == SEGMENT_KERNEL_CODE + 16);
STATIC_ASSERT(SEGMENT_USER_DATA32 == SEGMENT_KERNEL_CODE + 24);
STATIC_ASSERT(SEGMENT_USER_CODE32 == SEGMENT_USER_CODE32);
STATIC_ASSERT(SEGMENT_USER_DATA32 == SEGMENT_USER_CODE32 + 8);
#ifdef __x86_64__
STATIC_ASSERT(SEGMENT_USER_CODE64 == SEGMENT_USER_CODE32 + 16);
#endif /* __x86_64__ */



INTDEF byte_t __x86_gdt_tss_lo[];
INTDEF byte_t __x86_gdt_tss_hi[];
INTDEF byte_t __x86_gdt_ldt_lo[];
INTDEF byte_t __x86_gdt_ldt_hi[];
#ifndef __x86_64__
INTDEF byte_t __x86_gdt_tss_df_lo[];
INTDEF byte_t __x86_gdt_tss_df_hi[];
INTDEF byte_t __x86_gdt_kernel_tls_lo[];
INTDEF byte_t __x86_gdt_kernel_tls_hi[];
#endif /* !__x86_64__ */

#ifdef __x86_64__
#define GDT_L  1
#define GDT_DB 0
#define N64(...) /* nothing */
#else /* __x86_64__ */
#define GDT_L  0
#define GDT_DB 1
#define N64(...) __VA_ARGS__
#endif /* !__x86_64__ */


#ifdef __x86_64__
#define DEFINE_LOHI_SEGMENT(id, lo, hi)                     \
	[SEGMENT_INDEX(id) + 0] = { { .s_u = (uintptr_t)lo } }, \
	[SEGMENT_INDEX(id) + 1] = { { .s_u = (uintptr_t)hi } }
#else /* __x86_64__ */
#define DEFINE_LOHI_SEGMENT(id, lo, hi) \
	[SEGMENT_INDEX(id)] = { { { (uintptr_t)lo, (uintptr_t)hi } } }
#endif /* !__x86_64__ */


#define DTX SEGMENT_DESCRIPTOR_TYPE_CODE_EXRD /* Code descriptor */
#define DTD SEGMENT_DESCRIPTOR_TYPE_DATA_RDWR /* Data descriptor */

PUBLIC ATTR_PERCPU struct segment thiscpu_x86_gdt[SEGMENT_COUNT] = {
	[SEGMENT_INDEX(SEGMENT_NULL)]          = SEGMENT_DESCRIPTOR_INIT(0, 0, 0, 0, 0, 0, 0, 0, 0, 0),                  /* NULL segment */
	DEFINE_LOHI_SEGMENT(SEGMENT_CPU_TSS, __x86_gdt_tss_lo, __x86_gdt_tss_hi),                                        /* CPU TSS */
	N64(DEFINE_LOHI_SEGMENT(SEGMENT_CPU_TSS_DF, __x86_gdt_tss_df_lo, __x86_gdt_tss_df_hi),)                          /* CPU TSS (for #DF) */
	DEFINE_LOHI_SEGMENT(SEGMENT_CPU_LDT, __x86_gdt_ldt_lo, __x86_gdt_ldt_hi),                                        /* CPU LDT */
	N64(DEFINE_LOHI_SEGMENT(SEGMENT_KERNEL_FSBASE, __x86_gdt_kernel_tls_lo, __x86_gdt_kernel_tls_hi),)               /* THIS_TASK */
	[SEGMENT_INDEX(SEGMENT_USER_FSBASE)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTD, 1, 3, 1, 0, 0, 1, 1),          /* User %fs base (32-bit) */
	[SEGMENT_INDEX(SEGMENT_USER_GSBASE)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTD, 1, 3, 1, 0, 0, 1, 1),          /* User %gs base (32-bit) */
	[SEGMENT_INDEX(SEGMENT_KERNEL_CODE)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTX, 1, 0, 1, 0, GDT_L, GDT_DB, 1), /* Kernel code segment */
	[SEGMENT_INDEX(SEGMENT_KERNEL_DATA)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTD, 1, 0, 1, 0, GDT_L, GDT_DB, 1), /* Kernel data segment */
	[SEGMENT_INDEX(SEGMENT_USER_CODE32)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTX, 1, 3, 1, 0, 0, 1, 1),          /* User code (32-bit) */
	[SEGMENT_INDEX(SEGMENT_USER_DATA32)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTD, 1, 3, 1, 0, 0, 1, 1),          /* User data (32-bit) */
#ifdef __x86_64__
	[SEGMENT_INDEX(SEGMENT_USER_CODE64)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTX, 1, 3, 1, 0, 1, 0, 1),          /* User code (64-bit) */
	[SEGMENT_INDEX(SEGMENT_USER_DATA64)]   = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTD, 1, 3, 1, 0, 1, 0, 1),          /* User data (64-bit) */
	[SEGMENT_INDEX(SEGMENT_KERNEL_CODE32)] = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTX, 1, 0, 1, 0, 0, 1, 1),          /* Kernel code (32-bit) */
	[SEGMENT_INDEX(SEGMENT_KERNEL_DATA32)] = SEGMENT_DESCRIPTOR_INIT(0, 0xfffff, DTD, 1, 0, 1, 0, 0, 1, 1),          /* Kernel data (32-bit) */
#endif /* __x86_64__ */
};

#ifndef CONFIG_X86_EMULATE_LCALL7
INTDEF byte_t __x86_ldt_lcall7_main_lo[];
INTDEF byte_t __x86_ldt_lcall7_main_hi[];
#endif /* !CONFIG_X86_EMULATE_LCALL7 */

PUBLIC ATTR_PERCPU struct segment thiscpu_x86_ldt[LDT_SEGMENT_COUNT] = {
#ifdef CONFIG_X86_EMULATE_LCALL7
	/* Define the lcall7 segment as something that will cause a #NP when accessed,
	 * thus allowing us to emulate its behavior, rather than having to implement it
	 * properly. As far as the reasoning for this goes, take a look at the emulation
	 * implementation found in `/kos/src/kernel/core/arch/i386/fault/handle_gpf.c' */
	/* NOTE: Setting the P(present) bit to 0 will trigger a #NP */
#ifdef __x86_64__
	DEFINE_LOHI_SEGMENT(LDT_SEGMENT_SYSCALL,
	                    SEGMENT_CALLGATE_INIT_U   (0, SEGMENT_KERNEL_CODE, SEGMENT_DESCRIPTOR_TYPE_CALLGATE, 3, /*present=*/0),
	                    SEGMENT_CALLGATE_HI_INIT_U(0, SEGMENT_KERNEL_CODE, SEGMENT_DESCRIPTOR_TYPE_CALLGATE, 3, /*present=*/0))
#else /* __x86_64__ */
	DEFINE_LOHI_SEGMENT(LDT_SEGMENT_SYSCALL,
	                    SEGMENT_CALLGATE_INIT_UL(0, SEGMENT_KERNEL_CODE, SEGMENT_DESCRIPTOR_TYPE_CALLGATE, 0, 3, /*present=*/0),
	                    SEGMENT_CALLGATE_INIT_UH(0, SEGMENT_KERNEL_CODE, SEGMENT_DESCRIPTOR_TYPE_CALLGATE, 0, 3, /*present=*/0))
#endif /* !__x86_64__ */
#else /* CONFIG_X86_EMULATE_LCALL7 */
	DEFINE_LOHI_SEGMENT(LDT_SEGMENT_SYSCALL, __x86_ldt_lcall7_main_lo, __x86_ldt_lcall7_main_hi),
#endif /* !CONFIG_X86_EMULATE_LCALL7 */
};


/* The per-task value written to `t_psp0' during scheduler preemption. */
PUBLIC ATTR_PERTASK uintptr_t _this_x86_kernel_psp0 ASMNAME("this_x86_kernel_psp0") = 0;

DEFINE_PERTASK_INIT(init_this_x86_kernel_psp0);
INTERN NOBLOCK void
NOTHROW(KCALL init_this_x86_kernel_psp0)(struct task *__restrict self) {
	/* Initialize the kernel-sp0 valued to-be written during preemption. */
	FORTASK(self, _this_x86_kernel_psp0) = (uintptr_t)vm_node_getend(&FORTASK(self, this_kernel_stacknode));
}


#ifndef __x86_64__
/* The per-task values with which the `SEGMENT_USER_FSBASE' and
 * `SEGMENT_USER_GSBASE' segments are populated during scheduler
 * preemption. */
PUBLIC ATTR_PERTASK uintptr_t this_x86_user_fsbase = 0;
PUBLIC ATTR_PERTASK uintptr_t this_x86_user_gsbase = 0;
#endif /* !__x86_64__ */


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_GDT_C */
