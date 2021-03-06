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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_SCHED64_S
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_SCHED64_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <kernel/arch/paging64.h>
#include <kernel/except.h>
#include <kernel/fpu.h> /* CONFIG_FPU */
#include <kernel/syscall.h>
#include <kernel/x86/apic.h>
#include <kernel/x86/breakpoint.h>
#include <kernel/x86/gdt.h>
#include <kernel/x86/pic.h>
#include <kernel/x86/pit.h>
#include <kernel/x86/syscall-tables.h>
#include <sched/task.h>
#include <sched/x86/tss.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>
#include <asm/instr/fsgsbase.h>
#include <asm/instr/interrupt.h>
#include <asm/instr/kgsbase.h>
#include <asm/instr/movzxq.h>
#include <asm/instr/ttest.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state.h>



.section .text
INTERN_FUNCTION(x86_idt_apic_spurious)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	intr_enter INTR

	pushq_cfi_r %rax    /* [C] Accumulator register */
	pushq_cfi_r %rcx    /* [C] Count register */
	pushq_cfi_r %rdx    /* [C] Data register */
	pushq_cfi_r %rsi    /* [C] Source pointer */
	pushq_cfi_r %rdi    /* [C] Destination pointer */
	pushq_cfi_r %r8     /* [C] General purpose register #8 */
	pushq_cfi_r %r9     /* [C] General purpose register #9 */
	pushq_cfi_r %r10    /* [C] General purpose register #10 */
	pushq_cfi_r %r11    /* [C] General purpose register #11 */

	EXTERN(x86_apic_spur)
	call   x86_apic_spur
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rax
	movl   $(APIC_EOI_FSIGNAL), APIC_EOI(%rax)

	popq_cfi_r %r11     /* [C] General purpose register #11 */
	popq_cfi_r %r10     /* [C] General purpose register #10 */
	popq_cfi_r %r9      /* [C] General purpose register #9 */
	popq_cfi_r %r8      /* [C] General purpose register #8 */
	popq_cfi_r %rdi     /* [C] Destination pointer */
	popq_cfi_r %rsi     /* [C] Source pointer */
	popq_cfi_r %rdx     /* [C] Data register */
	popq_cfi_r %rcx     /* [C] Count register */
	popq_cfi_r %rax     /* [C] Accumulator register */

	intr_exit intr_enabled=0
	.cfi_endproc
END(x86_idt_apic_spurious)


.section .rodata.free
INTERN_FUNCTION(x86_ack_apic)
	EXTERN(x86_lapicbase)
	movq   x86_lapicbase, %rax
	movl   $(APIC_EOI_FSIGNAL), APIC_EOI(%rax)
INTERN_CONST(x86_ack_apic_size, . - x86_ack_apic)
END(x86_ack_apic)

.section .rodata.free
INTERN_FUNCTION(x86_ack_pic)
	movb   $(X86_PIC_CMD_EOI), %al
	outb   %al, $(X86_PIC1_CMD)
	.skip  x86_ack_apic_size - (. - x86_ack_pic), 0x90
END(x86_ack_pic)




/* The PIT interrupt handler -- Used for scheduling.
 * NOTE: If available, this interrupt will actually be fired by the LAPIC */
.section .text
INTERN_FUNCTION(x86_idt_preemption)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	intr_enter INTR

	/* Construct a full `struct scpustate' structure */
	ASM_PUSH_SCPUSTATE_AFTER_IRET_CFI_R

	/* Acknowledge the interrupt. */
INTERN_FUNCTION(x86_pic_acknowledge)
	.rept  x86_ack_apic_size
	.byte  0x90
	.endr
END(x86_pic_acknowledge)

	movq   %gs:0, %rsi          /* cpu_scheduler_interrupt::struct task *__restrict thread */
	EXTERN(this_sched_state)
	movq   %rsp, this_sched_state(%rsi)
	EXTERN(this_cpu)
	movq   this_cpu(%rsi), %rbx /* THIS_CPU */
	movq   %rbx, %rdi           /* cpu_scheduler_interrupt::struct cpu *__restrict caller */

	/* Invoke the C-level interrupt implementation. */
	EXTERN(cpu_scheduler_interrupt)
	call   cpu_scheduler_interrupt

	/* Set the task returned by `cpu_scheduler_interrupt()'
	 * as the new current one. */
	EXTERN(thiscpu_current)
	movq   %rax, thiscpu_current(%rbx)

INTERN_FUNCTION(x86_load_thread_rax_cpu_rbx)
	EXTERN(this_sched_state)
	movq   this_sched_state(%rax), %rsp

	/* Load other scheduler-related register values. */
	EXTERN(this_x86_kernel_psp0)
	movq   this_x86_kernel_psp0(%rax), %rcx
	EXTERN(thiscpu_x86_tss)
	movq   %rcx, thiscpu_x86_tss + OFFSET_TSS_RSP0(%rbx)

#ifdef CONFIG_FPU
	/* Disable the FPU, preparing it to be loaded lazily. */
	movq   %cr0, %rcx
	andq   $~CR0_TS, %rcx
	EXTERN(thiscpu_x86_fputhread)
	movq   thiscpu_x86_fputhread(%rbx), %rdx
	cmpq   %rdx, %rax
	je     1f
	/* Only disable if the target thread isn't holding the active FPU-context */
	orq    $(CR0_TS), %rcx
1:	movq   %rcx, %cr0
#endif /* CONFIG_FPU */

	/* Check if the old thread had its I/O permissions bitmap loaded. */
	EXTERN(thiscpu_x86_ioperm_bitmap)
	cmpq   $(0), thiscpu_x86_ioperm_bitmap(%rbx)
	jne    .Llazy_disable_ioperm_bitmap
.Llazy_disable_ioperm_bitmap_return:

	.cfi_remember_state

	/* Update the used page directory pointer. */
	EXTERN(this_vm)
	movq   this_vm(%rax), %rcx
	EXTERN(thisvm_pdir_phys_ptr)
	movq   thisvm_pdir_phys_ptr(%rcx), %rdi
	movq   %cr3, %rdx
	cmpq   %rdx, %rdi
	je     1f
	movq   %rdi, %cr3
	/* Reload debug registers */
	reload_x86_debug_registers %rcx, %rdi, %rsi, 1
1:

.Lload_scpustate_rsp_gsbase_rax:
	/* Load segment registers. */
	ASM_POP_SGREGS_CFI_R(%rcx)

	/* Update the kernel TLS pointer.
	 * NOTE: This must be done _after_ segment registers were loaded,
	 *       as the use of `ASM_POP_SGREGS_CFI_R()' clobbered %gs.base! */
	wrgsbaseq %rax

	/* Load fsbase and kgsbase */
	ASM_POP_SGBASE_CFI_R

	/* Load GP registers. */
	ASM_POP_GPREGSNSP_CFI_R

	/* Resume execution */
	intr_exit intr_enabled=0
	.cfi_restore_state

	/* Disable the I/O permissions bitmap. */
.Llazy_disable_ioperm_bitmap:
	/* Check if the loaded I/O permissions bitmap is the calling thread's */
	EXTERN(this_x86_ioperm_bitmap)
	movq   this_x86_ioperm_bitmap(%rax), %rdx
	EXTERN(thiscpu_x86_ioperm_bitmap)
	cmpq   %rdx, thiscpu_x86_ioperm_bitmap(%rbx)
	je     .Llazy_disable_ioperm_bitmap_return
	/* Must actually unmap the I/O permissions bitmap! */
	EXTERN(thiscpu_x86_iobnode_pagedir_identity)
	movq   thiscpu_x86_iobnode_pagedir_identity(%rbx), %rdx
	movzlq $(P64_PAGE_FPREPARED), %rcx
	movq   $(0), thiscpu_x86_ioperm_bitmap(%rbx)
	movq   %rcx, 0x0(%rdx)
	movq   %rcx, 0x8(%rdx)
	/* XXX: invlpg */
	jmp    .Llazy_disable_ioperm_bitmap_return
	.cfi_endproc
END(x86_load_thread_rax_cpu_rbx)
END(x86_idt_preemption)



#ifdef CONFIG_HAVE_DEBUGGER
.section .text.cold
INTERN_FUNCTION(x86_dbgidt_preemption) /* ISR_X86_f0 */
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	intr_enter INTR
	pushq_cfi_r %rax
	/* Acknowledge the interrupt. */
INTERN_FUNCTION(x86_debug_pic_acknowledge)
	.rept  x86_ack_apic_size
	.byte  0x90
	.endr
END(x86_debug_pic_acknowledge)
	popq_cfi_r %rax
	intr_exit intr_enabled=0
	.cfi_endproc
END(x86_dbgidt_preemption)
#endif /* CONFIG_HAVE_DEBUGGER */



.section .text
PUBLIC_FUNCTION(task_pause)
	.cfi_startproc
#ifndef CONFIG_NO_SMP
	pause
#endif /* !CONFIG_NO_SMP */
	ret
	.cfi_endproc
END(task_pause)

PUBLIC_FUNCTION(task_yield)
	.cfi_startproc
	.cfi_signal_frame
	popq_cfi %rax
	.cfi_register %rip, %rax
	movq   %rsp, %rcx
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rcx                    /* ir_rsp */
	.cfi_rel_offset %rsp, 0
	pushfq_cfi_r                      /* ir_rflags */
	ttest  mask=EFLAGS_IF, loc=0(%rsp)
	.cfi_remember_state
	jz     .Lillegal_task_yield
	pushq_cfi $(SEGMENT_KERNEL_CODE)  /* ir_cs */
	.cfi_rel_offset %cs, 0
	pushq_cfi %rax                    /* ir_rip */
	.cfi_rel_offset %rip, 0

INTERN_FUNCTION(X86_ASMSYSCALL64(sched_yield))
	/* Construct a full `struct scpustate' structure */
	ASM_PUSH_SCPUSTATE_AFTER_IRET_CFI_R

	/* Remember the current scheduler state. */
	movq   %gs:0, %rbx
	cli
	EXTERN(this_sched_runnxt)
	movq   this_sched_runnxt(%rbx), %rbp
	cmpq   %rbx, %rbp
	je     .Lyield_same_target
.Ldo_task_yield_rbx_to_rbp:

	/* Check for a scheduling override. */
	EXTERN(this_cpu)
	movq   this_cpu(%rbx), %rcx
	EXTERN(thiscpu_override)
	cmpq   $(0), thiscpu_override(%rcx)
	jne    .Lyield_same_target_with_override

	/* CURR: %rbx */
	/* NEXT: %rbp*/
	EXTERN(this_sched_state)
	movq   %rsp, this_sched_state(%rbx)

	/* Prematurely end the current quantum */
	movq   %rbx, %rdi /* current */
	movq   %rbp, %rsi /* next */
	EXTERN(cpu_quantum_end_nopr)
	call   cpu_quantum_end_nopr

	/* Load the new CPU state */
	EXTERN(this_cpu)
	movq   this_cpu(%rbx), %rbx
	EXTERN(thiscpu_current)
	movq   %rbp, thiscpu_current(%rbx)
	movq   %rbp, %rax
	jmp    x86_load_thread_rax_cpu_rbx
.Lyield_same_target_with_override:
#ifndef NDEBUG
	EXTERN(thiscpu_override)
	cmpq   %rbx, thiscpu_override(%rcx)
	je     .Lyield_same_target
	int3   /* Assertion failed: CPU override does not match calling thread.
	        * >> struct task *caller = %rbx;
	        * >> struct cpu  *mycpu  = %rcx; */
#endif /* !NDEBUG */
.Lyield_same_target:
#ifndef CONFIG_NO_SMP
	sti
	movq   %rbx, %rax
	pause
	cli
#else /* !CONFIG_NO_SMP */
	movq   %rbx, %rax
#endif /* CONFIG_NO_SMP */
	jmp    .Lload_scpustate_rsp_gsbase_rax
	.cfi_restore_state
.Lillegal_task_yield:
	movq   $(ERROR_CODEOF(E_WOULDBLOCK_PREEMPTED)), %rdi
	EXTERN(error_throw)
	call   error_throw
END(X86_ASMSYSCALL64(sched_yield))
END(task_yield)
.cfi_endproc

DEFINE_PUBLIC_ALIAS(sys_sched_yield, task_yield)

/* sched_yield() is has an identical implementation in compatibility mode */
DEFINE_INTERN_ALIAS(X86_ASMSYSCALL32_SYSENTER(sched_yield), X86_ASMSYSCALL64(sched_yield))
DEFINE_INTERN_ALIAS(X86_ASMSYSCALL32_INT80(sched_yield), X86_ASMSYSCALL64(sched_yield))





.section .text
PUBLIC_FUNCTION(task_yield_nx)
	.cfi_startproc
	.cfi_signal_frame
	popq_cfi %rax
	.cfi_register %rip, %rax
	movq   %rsp, %rcx
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rcx                    /* ir_rsp */
	.cfi_rel_offset %rsp, 0
	pushfq_cfi_r                      /* ir_rflags */
	ttest  mask=EFLAGS_IF, loc=0(%rsp)
	.cfi_remember_state
	jz     .Lillegal_task_yield_nx
	pushq_cfi $(SEGMENT_KERNEL_CODE)  /* ir_cs */
	.cfi_rel_offset %cs, 0
	pushq_cfi %rax                    /* ir_rip */
	.cfi_rel_offset %rip, 0

	/* Construct a full `struct scpustate' structure */
	pushq_cfi $(1)                   /* [C] Accumulator register */
	.cfi_rel_offset %rax, 0 /* Eventually, we want to return true. */
	ASM_PUSH_GPREGSNSP_NORAX_CFI_R
	ASM_PUSH_SGBASE_CFI_R
	ASM_PUSH_SGREGS_CFI_R(%rax)

	/* Remember the current scheduler state. */
	movq   %gs:0, %rbx
	cli
	EXTERN(this_sched_runnxt)
	movq   this_sched_runnxt(%rbx), %rbp
	cmpq   %rbx, %rbp
	je     .Lyield_same_target
	jmp    .Ldo_task_yield_rbx_to_rbp
	.cfi_restore_state
.Lillegal_task_yield_nx:
	addq   $(24), %rsp
	.cfi_adjust_cfa_offset -24
	movq   %rax, %rcx
	.cfi_register %rip, %rcx
	movq   $(0), %rax
	jmpq   *%rcx
	.cfi_endproc
END(task_yield_nx)



.section .text
PUBLIC_FUNCTION(task_tryyield_or_pause)
	.cfi_startproc
	.cfi_signal_frame
	popq_cfi %rcx
	.cfi_register %rip, %rcx
	movq   %rsp, %rdx
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rdx                    /* ir_rsp */
	.cfi_rel_offset %rsp, 0
	pushfq_cfi_r                      /* ir_rflags */
	ttest  mask=EFLAGS_IF, loc=0(%rsp)
	jnz    1f
	addq   $(24), %rsp
	.cfi_adjust_cfa_offset -24
	.cfi_same_value %rflags
	movq   $(TASK_TRYYIELD_PREEMPTION_DISABLED), %rax
#ifndef CONFIG_NO_SMP
	pause
#endif /* !CONFIG_NO_SMP */
	jmpq   *%rcx
END(task_tryyield_or_pause)
	.cfi_adjust_cfa_offset 8
	.cfi_restore %rip
PUBLIC_FUNCTION(task_tryyield)
	popq_cfi %rcx
	.cfi_register %rip, %rcx
	movq   %rsp, %rdx
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rdx                    /* ir_rsp */
	.cfi_rel_offset %rsp, 0
	pushfq_cfi_r                      /* ir_rflags */
	ttest  mask=EFLAGS_IF, loc=0(%rsp)
	jnz    1f
	addq   $(24), %rsp
	.cfi_adjust_cfa_offset -24
	.cfi_same_value %rflags
	movq   $(TASK_TRYYIELD_PREEMPTION_DISABLED), %rax
#ifndef CONFIG_NO_SMP
	pause
#endif /* !CONFIG_NO_SMP */
	jmpq   *%rcx
1:	.cfi_adjust_cfa_offset 24
	.cfi_rel_offset %eflags, 0
	pushq_cfi $(SEGMENT_KERNEL_CODE) /* ir_cs */
	.cfi_rel_offset %cs, 0
	pushq_cfi %rcx                   /* ir_rip */
	.cfi_rel_offset %rip, 0

	/* Construct a full `struct scpustate' structure */
	pushq_cfi $(TASK_TRYYIELD_SUCCESS) /* [C] Accumulator register */
	.cfi_rel_offset %rax, 0
	ASM_PUSH_GPREGSNSP_NORAX_CFI_R
	ASM_PUSH_SGBASE_CFI_R
	ASM_PUSH_SGREGS_CFI_R(%rax)

	/* Remember the current scheduler state. */
	movq   %gs:0, %rbx
	cli
	EXTERN(this_sched_runnxt)
	movq   this_sched_runnxt(%rbx), %rbp
	cmpq   %rbx, %rbp
	jne    .Ldo_task_yield_rbx_to_rbp
#ifndef CONFIG_NO_SMP
	sti
#endif /* !CONFIG_NO_SMP */

	/* Same target... */
	movq   $(TASK_TRYYIELD_NO_SUCCESSOR), (OFFSET_SCPUSTATE_GPREGSNSP + OFFSET_GPREGSNSP_RAX)(%rsp)
#ifndef CONFIG_NO_SMP
	pause
#endif /* !CONFIG_NO_SMP */
	movq   %rbx, %rax
#ifndef CONFIG_NO_SMP
	cli
#endif /* !CONFIG_NO_SMP */
	jmp    .Lload_scpustate_rsp_gsbase_rax
	.cfi_endproc
END(task_tryyield)



.section .text
PUBLIC_FUNCTION(cpu_run_current_and_remember_nopr)
	/* %rdi: <struct task *__restrict caller> */
	.cfi_startproc
	.cfi_signal_frame
	popq_cfi %rax
	.cfi_register %rip, %rax
	movq   %rsp, %rcx
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* ir_ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rcx                    /* ir_rsp */
	.cfi_rel_offset %rsp, 0
	pushfq_cfi_r                      /* ir_rflags */
	orq    $(EFLAGS_IF), (%rsp)
	pushq_cfi $(SEGMENT_KERNEL_CODE)  /* ir_cs */
	.cfi_rel_offset %cs, 0
	pushq_cfi %rax                    /* ir_rip */
	.cfi_rel_offset %rip, 0

	/* Construct a full `struct scpustate' structure */
	ASM_PUSH_SCPUSTATE_AFTER_IRET_CFI_R

	/* Remember the current scheduler state. */
	EXTERN(this_sched_state)
	movq   %rsp, this_sched_state(%rdi)
	EXTERN(this_cpu)
	movq   this_cpu(%rdi), %rbx

	/* Load the new CPU state */
	EXTERN(thiscpu_current)
	movq   thiscpu_current(%rbx), %rax
	EXTERN(x86_load_thread_rax_cpu_rbx)
	jmp    x86_load_thread_rax_cpu_rbx
	.cfi_endproc
END(cpu_run_current_and_remember_nopr)

.section .text
PUBLIC_FUNCTION(cpu_run_current_nopr)
	.cfi_startproc
	/* Load the CPU state of the task set as current. */
	movq   %gs:0, %rax
	EXTERN(this_cpu)
	movq   this_cpu(%rax), %rbx
	EXTERN(thiscpu_current)
	movq   thiscpu_current(%rbx), %rax
	EXTERN(x86_load_thread_rax_cpu_rbx)
	jmp    x86_load_thread_rax_cpu_rbx
	.cfi_endproc
END(cpu_run_current_nopr)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_SCHED64_S */
