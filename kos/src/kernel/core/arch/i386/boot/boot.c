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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_BOOT_BOOT_C
#define GUARD_KERNEL_CORE_ARCH_I386_BOOT_BOOT_C 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/boot.h>
#include <kernel/cpuid.h>
#include <kernel/driver-param.h>
#include <kernel/gdt.h>
#include <kernel/memory.h>
#include <kernel/multiboot.h>
#include <kernel/printk.h>
#include <kernel/types.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

/**/
#include <kernel/debugtrap.h> /* TODO: Remove me; `kernel_debugtrap()' should be called by _start32.S */
#include <kos/debugtrap.h>    /* TODO: Remove me; `kernel_debugtrap()' should be called by _start32.S */
#include <signal.h>           /* TODO: Remove me; `kernel_debugtrap()' should be called by _start32.S */

/**/
#include <kernel/syscall.h> /* TODO: Remove me; Only used for `syscall_tracing_setenabled()' */

/**/
#include <kernel/panic.h> /* TODO: Remove me; Only used for boot_partition-init */
#include <fs/node.h>      /* TODO: Remove me; Only used for boot_partition-init */
#include <fs/vfs.h>       /* TODO: Remove me; Only used for boot_partition-init */
#include <dev/block.h>    /* TODO: Remove me; Only used for boot_partition-init */

/**/
#include <kernel/rand.h> /* TODO: Remove me; Only used for rand-init */
#include <sys/io.h>      /* TODO: Remove me; Only used for rand-init */


/**/
#include <assert.h>

DECL_BEGIN

PUBLIC ATTR_USED ATTR_SECTION(".bss")
struct fcpustate32 boot_cpustate;
PUBLIC ATTR_USED ATTR_SECTION(".data.cold")
struct boot_device_info boot_device = { 0xff, 0xff, 0xff, 0xff };

INTDEF port_t debug_port;

#define MAKE_DWORD(a, b, c, d) \
	((u32)(a) | ((u32)(b) << 8) | ((u32)(c) << 16) | ((u32)(d) << 24))


INTERN ATTR_FREEBSS bool x86_force_detect_moreram = false;
DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION(x86_force_detect_moreram,
                                            KERNEL_COMMANDLINE_OPTION_TYPE_BOOL,
                                            "force-detect-moreram");


#ifndef CONFIG_NO_DEBUGGER
/* Define options for entering debugger mode at various stages, rather than booting normally. */
DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION(dbg, KERNEL_COMMANDLINE_OPTION_TYPE_PRESENT, "dbg-very-early");
/**/ DEFINE_EARLY_KERNEL_COMMANDLINE_OPTION(dbg, KERNEL_COMMANDLINE_OPTION_TYPE_PRESENT, "dbg-early");
/*      */ DEFINE_KERNEL_COMMANDLINE_OPTION(dbg, KERNEL_COMMANDLINE_OPTION_TYPE_PRESENT, "dbg");
/* */ DEFINE_LATE_KERNEL_COMMANDLINE_OPTION(dbg, KERNEL_COMMANDLINE_OPTION_TYPE_PRESENT, "dbg-late");
#endif /* !CONFIG_NO_DEBUGGER */


INTERN ATTR_FREETEXT struct icpustate *
NOTHROW(KCALL __i386_kernel_main)(struct icpustate *__restrict state) {
	/* Figure out how we can output data to an emulator's STDOUT (if we're being hosted by one)
	 * NOTE: QEMU can consistently be detected via `CPUID[0x80000002].EAX',
	 *       but in order to allow KOS to properly detect BOCHS, you must change
	 *      <cpuid: brand_string="BOCHS         Intel(R) Pentium(R) 4 CPU        ">
	 *       in your .bxrc file
	 */
	if (__x86_bootcpu_idfeatures.ci_80000002a == MAKE_DWORD('Q', 'E', 'M', 'U'))
		debug_port = (port_t)0x3f8;
	else if (__x86_bootcpu_idfeatures.ci_80000002a == MAKE_DWORD('B', 'O', 'C', 'H')) {
		debug_port = (port_t)0xe9;
	}

	printk(FREESTR(KERN_NOTICE "[boot] Begin kernel initialization\n"));
	printk(FREESTR(KERN_INFO "[boot] CPU brand: %q\n"), __x86_bootcpu_idfeatures.ci_brand);

	/* Initialize the paging configuration */
	x86_initialize_paging();

#ifndef __x86_64__
	/* Initialize the atomic64 configuration */
	x86_initialize_atomic64();
#endif /* !__x86_64__ */

	/* Initialize per-task/per-cpu structures */
	kernel_initialize_scheduler();

	/* Load support for the sysenter instruction as soon as possible. */
	x86_initialize_sysenter();

	/* Load default memory banks. */
	x86_initialize_default_memory_banks();

	/* Load multiboot information.
	 * NOTE: All information provided by the bootloader is assumed
	 *       to be located within the first 1Gb of physical memory! */
	{
		size_t total_pages;
		u32 boot_eax = boot_cpustate.fcs_gpregs.gp_eax;
		u32 boot_ebx = boot_cpustate.fcs_gpregs.gp_ebx;

		/* Multiboot support */
		if (boot_eax == MB_BOOTLOADER_MAGIC) {
			/* Multiboot Mk#1 */
			printk(FREESTR(KERN_INFO "[boot] Booting via Multiboot-compliant bootloader\n"));
			x86_load_mb1info(boot_ebx);
		} else if (boot_eax == MB2_BOOTLOADER_MAGIC) {
			/* Multiboot Mk#2 */
			printk(FREESTR(KERN_INFO "[boot] Booting via Multiboot2-compliant bootloader\n"));
			x86_load_mb2info(boot_ebx);
		}

		/* Evaluate commandline options defined as `DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION()' */
		kernel_initialize_commandline_options_very_early();

		/* If we didn't gather at least 1MB, try to consult the bios to find more. */
		total_pages = minfo_usable_ram_pages();
		if (total_pages < X86_BOOT_MINIMUM_AVAILABLE_RAM || x86_force_detect_moreram) { /* Less than 1MB */
			x86_initialize_memory_via_bios();
			total_pages = minfo_usable_ram_pages();
		}
		printk(FREESTR(KERN_INFO "[boot] Located %Iu (%#Ix) bytes (%Iu %s) of usable RAM\n"),
		       VM_PAGE2ADDR(total_pages), VM_PAGE2ADDR(total_pages),
		       total_pages >= VM_ADDR2PAGE(0x100000) ? (total_pages / VM_ADDR2PAGE(0x100000)) : (total_pages * PAGESIZE) / 0x400,
		       total_pages >= VM_ADDR2PAGE(0x100000) ? FREESTR("MiB") : FREESTR("KiB"));
	}

	/* Run task initialization callbacks on the boot task, initializing
	 * important structures such as the r/w-lock descriptor and the task
	 * signal connection manager.
	 * NOTE: We do this now since r/w-locks and signal connections are
	 *       required by the Unwind-FDE cache sub-system, meaning that
	 *       they are also required for us to be able to handle exceptions.
	 * In other words: Only once this function has been called can we
	 *                 start making use of exceptions safely. */
	kernel_initialize_scheduler_callbacks();

	/* Initialize SMP.
	 * NOTE: This must be done while the physical identity mapping is still
	 *       in effect (aka: before `x86_initialize_kernel_vm()' is called)
	 *       Additionally, do this before memory zones have been finalized,
	 *       so we can manually add SMP descriptor memory regions as available
	 *       physical memory, while also preventing that they get overwritten
	 *       by zone initialization, regardless of what the bootloader did
	 *       about them in terms of telling us. */
	x86_initialize_smp();

	/* Same as SMP, ACPI needs access to the physical identity mapping. */
	x86_initialize_acpi();

#if 0
	{
		size_t i;
		for (i = 0; i < minfo.mb_bankc; ++i) {
			printk(KERN_DEBUG "[boot] MEMORY: %I64p...%I64p (%s)\n",
			       (u64)PMEMBANK_TYPE_MIN(minfo.mb_banks[i]),
			       (u64)PMEMBANK_TYPE_MAX(minfo.mb_banks[i]),
			       pmembank_type_names[minfo.mb_banks[i].mb_type]);
		}
	}
#endif

	/* Generate physical memory zones from collected memory information. */
	minfo_makezones();

	/* Since we're about to use randomization, we somehow
	 * need to generate just a tiny bit of entropy first.
	 * So we're just going to read the CMOS RTC state and
	 * use it to set the initial kernel seed. */
	x86_initialize_rand_entropy();

	/* Evaluate commandline options defined as `DEFINE_EARLY_KERNEL_COMMANDLINE_OPTION()' */
	kernel_initialize_commandline_options_early();

	/* Since `kernel_initialize_commandline_options_early()' may have overwritten
	 * the initial seed set by `x86_initialize_rand_entropy()', only log the actually
	 * used seed now so that the system logs remain consistent with the user's expectation. */
	printk(FREESTR(KERN_INFO "[rand] Set pseudo RNG seed to %#I32p\n"), krand_seed);

	/* Initialize the kernel VM, and instigate strict memory protection,
	 * unmapping virtual memory that isn't being used by the kernel, while
	 * also removing write permissions for .text and .rodata, as well as
	 * (if supported) setting the NOEXECUTE bit for anything but `.text'
	 * and `.xdata' / `.xbss'
	 * NOTE: This also unmaps the physical identity mapping found surrounding
	 *       the kernel, which was left in tact until this point in order to
	 *       simplify initialization of SMP control structures (or anything
	 *       left in physical memory below the 1GiB mark). */
	x86_initialize_kernel_vm();

	/* Relocate memory information into higher memory, moving it away from
	 * being somewhere where it could cause problems, or be accidentally
	 * corrupted. */
	minfo_relocate_appropriate();

	/* Flush the entire TLB buffer, now that we're finished setting up the page directory.
	 * NOTE: Technically, this should be unnecessary, but it may still clean up some
	 *       caches that had become clobbered by our incessant modifications above. */
	pagedir_syncall();

	/* Initialize the APIC / PIC */
	x86_initialize_apic();

	/* TODO: ioapic support (ioapic is the modern equivalent of the pic) */

#ifndef CONFIG_NO_FPU
	/* Initialize the FPU sub-system. */
	x86_initialize_fpu();
#endif /* !CONFIG_NO_FPU */

	/* Make the kernel's .text and .rodata sections read-only. */
	x86_initialize_kernel_vm_readonly();

#ifndef CONFIG_NO_USERKERN_SEGMENT
#ifdef __x86_64__
	__wrgsbase((void *)x86_this_userkern_init());
#else /* __x86_64__ */
	update_user_fsbase();
#endif /* !__x86_64__ */
#endif /* !CONFIG_NO_USERKERN_SEGMENT */

	/* Initialize the PID sub-system for the boot task. */
	kernel_initialize_bootpid();

	/* Copy the kernel commandline into high memory. */
	x86_initialize_commandline_himem();

	/* Allocate and set the user-space VM for /bin/init */
	kernel_initialize_user_vm();

	/* Evaluate commandline options defined as `DEFINE_KERNEL_COMMANDLINE_OPTION()' */
	kernel_initialize_commandline_options_stable();

#ifndef CONFIG_NO_DEBUGGER
	/* Before loading drivers proper, copy the BIOS's VGA font. */
	x86_initialize_debugger_textfont();
#endif /* !CONFIG_NO_DEBUGGER */

	/* Initialize builtin core drivers. */
	kernel_initialize_devfs_driver();
	kernel_initialize_pci_driver();
	kernel_initialize_ide_driver();
	kernel_initialize_fat_driver();

	/* Load drivers provided by the bootloader */
	x86_initialize_bootloader_drivers();

	/* Release physical memory from minfo that was marked as `PMEMBANK_TYPE_PRESERVE'
	 * NOTE: This can only be done after bootloader drivers, since drivers provided
	 *       by the bootloader are themself mapped as preserved memory. */
	minfo_release_presevations();

	/* Initialize special builtin character devices (/dev/null, /dev/zero, etc.)
	 * TODO: Have these device files be defined by a dedicated driver, which
	 *       will then be loaded by /bin/init, rather than have them hard-coded
	 *       within the kernel core. */
	kernel_initialize_null_devices();

	/* Initialize the /dev/tty alias device */
	kernel_initialize_ctty_device();

	/* Initialize (load dependencies, apply relocations & call constructors)
	 * all of the drivers provided by the bootloader. */
	kernel_initialize_loaded_drivers();

	/* Load late commandline options. */
	kernel_initialize_commandline_options_late();

#if 0
	{
		byte_t *p = (byte_t *)kmalloc(42, GFP_NORMAL);
		heap_validate_all();
		mall_validate_padding();
		printk("p = %p (%Iu)\n", p, kmalloc_usable_size(p));
		printk("%$[hex]\n", kmalloc_usable_size(p), p);
		printk("p[0] = %x\n", p[0]);
		p[0] = 42;
		printk("p[0] = %x\n", p[0]);
		mall_validate_padding();
		kfree(p);
		printk("%$[hex]\n", 48, p);
		heap_validate_all();
	}
#endif

#if 0
	struct task *test;
	test = task_setup_kernel(task_alloc(&vm_kernel),
	                         (thread_main_t)&test_thread,
	                         2,
	                         "foo",
	                         "bar");
	if (cpu_count > 1)
		test->t_cpu = cpu_vector[1];

	printk("Before task_connect()\n");
	task_connect_ghost(&test_signal);
	task_connect_ghost(&test_signal2);
	printk("Before launch of secondary thread\n");
	task_start(test);
	decref(test);

	printk("Before waiting on signal\n");
	task_waitfor(NULL);
	printk("After waiting on signal\n");
#endif

	/* TODO: Place all of libc's data that requires runtime relocations into a dedicated section `.data.reloc',
	 *       and have that section be page-aligned. That way, only a minimal number of pages need to be faulted
	 *       for libc to be loaded. */

	/* TODO: libdebuginfo freezes with -gdwarf-2
	 * TODO: Check if it still does this (it's been quite a while since I wrote that TODO) */

	/* TODO: If we weren't able to figure out the boot device, check if we can
	 *       somehow make use of the `boot_device' information which was given
	 *       to us by the bootloader... */
	printk(KERN_INFO "boot_device = { %#I8x, %#I8x, %#I8x, %#I8x }\n",
	       boot_device.bdi_biosdev,
	       boot_device.bdi_partition,
	       boot_device.bdi_sub_partition,
	       boot_device.bdi_sub_sub_partition);

	/* Make sure that we've managed to detect a single, valid boot partition, or
	 * that the user started the kernel with a boot=... commandline parameter. */
	if unlikely(boot_partition == NULL)
		kernel_panic(FREESTR("Unable to detect boot partition (reboot with `boot=...')"));
	if unlikely(boot_partition == (struct basic_block_device *)-1)
		kernel_panic(FREESTR("Detected boot partition is ambiguous (reboot with `boot=...')"));

	/* TODO: Don't hard-code fat here. - Instead, try every currently loaded filesystem driver.
	 *       After all: The bootloader may have loaded additional drivers... */
	/* TODO: Move this mount() call into a different file. */
	path_mount(THIS_VFS, "fat", boot_partition, SUPERBLOCK_FNORMAL, NULL, NULL, true);

	mall_dump_leaks(GFP_NORMAL);

	/* TODO: Spread ATTR_LEAF around throughout headers
	 *    - https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#leaf
	 * TODO: Use libvm86 to emulate BIOS callbacks */

	/* Enable system call tracing. */
	syscall_tracing_setenabled(true); /* TODO: Remove me */

#if 0
	decref(driver_insmod("iso9660", "a b foobar bazbaz"));
	{
		REF struct superblock *cd;
		cd = superblock_open("iso9660", "/dev/hdb");
		{
			SCOPED_READLOCK((struct vm_datablock *)cd);
			REF struct directory_entry *ent;
			while ((ent = directory_readnext(cd)) != NULL) {
				printk("ENTRY: %$q, %u, %I64u\n",
				       (size_t)ent->de_namelen,
				       ent->de_name,
				       (unsigned int)ent->de_type,
				       (u64)ent->de_ino);
			}
		}
		superblock_set_unmounted(cd);
		decref(cd);
	}
	driver_delmod("iso9660");
#endif

	/* Update the given initial user-state to start
	 * executing /bin/init (or whatever was passed as `init=...') */
	state = kernel_initialize_exec_init(state);

	printk(FREESTR(KERN_INFO "Initial jump to user-space [pc=%p] [sp=%p]\n"),
	       icpustate_getpc(state),
	       icpustate_getsp(state));

	return state;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_BOOT_BOOT_C */