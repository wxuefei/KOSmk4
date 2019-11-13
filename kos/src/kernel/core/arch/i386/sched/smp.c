/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_SMP_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_SMP_C 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/apic.h>
#include <kernel/paging.h>
#include <kernel/pic.h>
#include <kernel/printk.h>
#include <kernel/vm.h>
#include <sched/cpu.h>
#include <sched/smp.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/unaligned.h>

#include <stddef.h>

DECL_BEGIN

/* VM nodes / datapart for the LAPIC identity mapping. */
INTDEF struct vm_datapart x86_vm_part_lapic;
INTDEF struct vm_node x86_vm_node_lapic;

PRIVATE ATTR_FREETEXT byte_t
NOTHROW(KCALL smp_memsum)(void const *__restrict p, size_t n_bytes) {
	byte_t result = 0;
	byte_t *iter, *end;
	end = (iter = (byte_t *)p) + n_bytes;
	for (; iter != end; ++iter)
		result += *iter;
	return result;
}

PRIVATE ATTR_FREETEXT MpFloatingPointerStructure *
NOTHROW(KCALL Mp_LocateFloatingPointStructureInAddressRange)(VIRT uintptr_t base, size_t bytes) {
	uintptr_t iter, end;
	/* Make sure not to search unmapped memory! */
	if (base < KERNEL_BASE) {
		base += bytes;
		if (base <= KERNEL_BASE)
			return NULL;
		bytes = base - KERNEL_BASE;
		base  = KERNEL_BASE;
	}
	if ((base + bytes) < base)
		bytes = 0 - base;
	end = (iter = (uintptr_t)base) + bytes;
	printk(FREESTR(KERN_DEBUG "Searching for MpFloatingPointerStructure in %p...%p\n"),
	       iter - KERNEL_BASE, (end - 1) - KERNEL_BASE);
	/* Clamp the search area to a 16-byte alignment. */
	iter = CEIL_ALIGN(iter, MPFPS_ALIGN);
	end  = FLOOR_ALIGN(end, MPFPS_ALIGN);
	for (; iter < end; iter += MPFPS_ALIGN) {
		MpFloatingPointerStructure *result = (MpFloatingPointerStructure *)iter;
		if (*(u32 *)result->mp_sig != MP_FLOATING_POINTER_SIGNATURE)
			continue;
		/* When found, check the length and checksum. */
		if (result->mp_length >= sizeof(MpFloatingPointerStructure) / 16 &&
		    !smp_memsum(result, sizeof(MpFloatingPointerStructure)))
			return result;
	}
	return NULL;
}


PRIVATE ATTR_FREETEXT MpFloatingPointerStructure *
NOTHROW(KCALL Mp_LocateFloatingPointStructure)(void) {
	MpFloatingPointerStructure *result;
	uintptr_t base;
	/* NOTE: No need to identity-map these, as they're all part of the
	 *       first 1Gb of physical memory, which is fully mapped at this
	 *       point, both in 32-bit and 64-bit mode. */
	base   = (uintptr_t)*(u16 volatile *)(KERNEL_BASE + 0x40E);
	result = Mp_LocateFloatingPointStructureInAddressRange(KERNEL_BASE + base, 1024);
	if (result)
		goto done;
	base   = (uintptr_t)*(u16 volatile *)(KERNEL_BASE + 0x413);
	result = Mp_LocateFloatingPointStructureInAddressRange(KERNEL_BASE + base * 1024, 1024);
	if (result)
		goto done;
	result = Mp_LocateFloatingPointStructureInAddressRange(KERNEL_BASE + 0x0f0000, 64 * 1024);
done:
	return result;
}


PUBLIC ATTR_PERCPU u8 _x86_lapic_id ASMNAME("x86_lapic_id") = 0;
PUBLIC ATTR_PERCPU u8 _x86_lapic_version ASMNAME("x86_lapic_version") = 0;
DATDEF cpuid_t _cpu_count ASMNAME("cpu_count");
DATDEF struct cpu *_cpu_vector[CONFIG_MAX_CPU_COUNT] ASMNAME("cpu_vector");

PUBLIC VIRT byte_t volatile *x86_lapic_base_address_ ASMNAME("x86_lapic_base_address") = NULL;

INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_smp)(void) {
	MpFloatingPointerStructure *fps;
	MpConfigurationTable *table;
	/* TODO: Commandline option to override address of this structure */
	/* TODO: Commandline option to disable detection of this structure */
	fps = Mp_LocateFloatingPointStructure();
	if unlikely(!fps) {
		printk(FREESTR(KERN_DEBUG "MpFloatingPointerStructure not found\n"));
		return;
	}
	printk(FREESTR(KERN_DEBUG "MpFloatingPointerStructure located at %p (v1.%I8u; defcfg %I8u)\n"),
	       ((uintptr_t)fps - KERNEL_BASE), fps->mp_specrev, fps->mp_defcfg);
	if (fps->mp_defcfg) {
		/* Default configuration. */
		x86_vm_part_lapic.dp_ramdata.rd_block0.rb_start = VM_ADDR2PAGE((vm_phys_t)0xfee00000);
		x86_vm_part_lapic.dp_ramdata.rd_block0.rb_size  = 1;
		x86_vm_part_lapic.dp_tree.a_vmin                = (vm_dpage_t)0;
		x86_vm_part_lapic.dp_tree.a_vmax                = (vm_dpage_t)0;
		FORCPU(&_bootcpu, _x86_lapic_id)                  = 0xff; /* Read later using the LAPIC */
		FORCPU(&_bootcpu, _x86_lapic_version)             = fps->mp_defcfg > 4 ? APICVER_INTEGRATED : APICVER_82489DX;
		return;
	}
	/* Check pointer location. */
	if (fps->mp_cfgtab >= 0x40000000)
		return;
	table = (MpConfigurationTable *)((uintptr_t)fps->mp_cfgtab + KERNEL_BASE);
	/* Check signature. */
	if (UNALIGNED_GET32((u32 *)table->tab_sig) != ENCODE_INT32('P', 'C', 'M', 'P'))
		return;
	/* Check checksum. */
	if (smp_memsum(table, table->tab_length))
		return;
	/* Remember the LAPIC base address. */
	if (table->tab_lapicaddr & (PAGESIZE - 1)) {
		x86_lapic_base_address_ = (byte_t *)(uintptr_t)(table->tab_lapicaddr & (PAGESIZE - 1));
		x86_vm_part_lapic.dp_ramdata.rd_block0.rb_start = VM_ADDR2PAGE((vm_phys_t)table->tab_lapicaddr);
		x86_vm_part_lapic.dp_ramdata.rd_block0.rb_size  = 2;
		x86_vm_part_lapic.dp_tree.a_vmin                = (vm_dpage_t)0;
		x86_vm_part_lapic.dp_tree.a_vmax                = (vm_dpage_t)1;
	} else {
		x86_vm_part_lapic.dp_ramdata.rd_block0.rb_start = VM_ADDR2PAGE((vm_phys_t)table->tab_lapicaddr);
		x86_vm_part_lapic.dp_ramdata.rd_block0.rb_size  = 1;
		x86_vm_part_lapic.dp_tree.a_vmin                = (vm_dpage_t)0;
		x86_vm_part_lapic.dp_tree.a_vmax                = (vm_dpage_t)0;
	}
	/* Process configuration entries. */
	{
		MpConfigurationEntry *entry, *end;
		u16 i, count;
		entry = (MpConfigurationEntry *)(table + 1);
		end   = (MpConfigurationEntry *)((uintptr_t)table + table->tab_length);
		count = table->tab_entryc;
		for (i = 0; i < count && entry < end; ++i) {
			switch (entry->mp_type) {

			case MPCFG_PROCESSOR:
				if (entry->mp_processor.p_cpuflag &
				    (MP_PROCESSOR_FENABLED | MP_PROCESSOR_FBOOTPROCESSOR)) {
					if (entry->mp_processor.p_cpuflag & MP_PROCESSOR_FBOOTPROCESSOR) {
						printk(FREESTR(KERN_INFO "Found boot processor with lapic id %#.2I8x\n"),
						       entry->mp_processor.p_lapicid);
						FORCPU(&_bootcpu, _x86_lapic_id) = entry->mp_processor.p_lapicid;
					}
#ifndef CONFIG_NO_SMP
					else if unlikely(_cpu_count >= CONFIG_MAX_CPU_COUNT) {
						printk(FREESTR(KERN_WARNING "Cannot configure additional Processor with lapic id %#.2I8x\n"),
						       entry->mp_processor.p_lapicid);
					} else {
						/* Remember this additional CPU's LAPIC id.
						 * NOTE: The CPU controller itself will then be allocated and initialized
						 *       later on. - For right now, we only save its LAPIC id where its
						 *       controller point will go later (s.a. `x86_initialize_apic()'). */
						printk(FREESTR(KERN_INFO "Found secondary processor #%u with lapic id %#.2I8x\n"),
						       _cpu_count, entry->mp_processor.p_lapicid);
						/* This entry will later be replaced by a proper `struct cpu' structure! */
						_cpu_vector[_cpu_count] = (struct cpu *)(uintptr_t)(((u16)entry->mp_processor.p_lapicid) |
						                                                    ((u16)entry->mp_processor.p_lapicver << 8));
						++_cpu_count;
					}
#endif /* !CONFIG_NO_SMP */
				}
				*(uintptr_t *)&entry += 20;
				break;

			default: *(uintptr_t *)&entry += 8; break;
			}
		}
	}
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_SMP_C */