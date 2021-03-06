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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_BOOT_ACPI_C
#define GUARD_KERNEL_CORE_ARCH_I386_BOOT_ACPI_C 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>
#include <kernel/x86/acpi.h>

#include <hybrid/align.h>
#include <hybrid/minmax.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* ACPI support by the host */
PUBLIC unsigned int acpi_mode = ACPI_MODE_NONE;

/* [valid_if(acpi_mode != ACPI_MODE_NONE)] pointer to the RSDT or XSDT (based on `acpi_mode') */
PUBLIC vm_phys_t acpi_root = 0;

/* [valid_if(acpi_mode == ACPI_MODE_RSDT)] Length of the vector `((ACPISDTHeader *)acpi_root)->rsdp_sdts' */
PUBLIC size_t acpi_sdt_count = 0;

#ifdef NO_PHYS_IDENTITY
#define vm_copyfromphys_noidentity vm_copyfromphys
#else /* NO_PHYS_IDENTITY */
PRIVATE ATTR_FREETEXT size_t
NOTHROW(KCALL vm_copyfromphys_noidentity_partial)(void *__restrict dst,
                                                  PHYS vm_phys_t src,
                                                  size_t num_bytes) {
	uintptr_t offset;
	size_t result;
	byte_t *vsrc = THIS_TRAMPOLINE_BASE;
	pagedir_pushval_t pv;
	/* NOTE: We must still preserve the trampoline here, since the trampoline
	 *       for _boottask is allocated past the end of the kernel's .free
	 *       section. This is important since the bootloader/bios may have
	 *       placed various data structures at that location (on QEMU I
	 *       noticed that the kernel's commandline is placed directly over-
	 *       top of the _boottask's page directory identity mapping)
	 *       As such, we must preserve this mapping, as things such that the
	 *       kernel commandline are still used by later steps of the boot
	 *       process. */
	pv = pagedir_push_mapone(vsrc, src & ~(PAGESIZE - 1), PAGEDIR_MAP_FREAD);
	pagedir_syncone(vsrc);
	offset = (uintptr_t)(src & (PAGESIZE - 1));
	result = PAGESIZE - offset;
	if (result > num_bytes)
		result = num_bytes;
	memcpy(dst, vsrc + offset, result);
	pagedir_pop_mapone(vsrc, pv);
	return result;
}

/* Because the pyhs2virt identity mapping is initialized _after_
 * ACPI, which needs to be done this way because pyhs2virt must
 * be able to allocate physical memory, which requires a prior
 * call to `kernel_initialize_minfo_makezones()', which requires
 * that memory bank initialization has been finalized, which it
 * isn't yet (as indicative of `x86_initialize_acpi()' below
 * calling `minfo_addbank()')
 * This function behaves the same as `vm_copyfromphys()', however
 * will not make use of the phys2virt identity segment. */
PRIVATE ATTR_FREETEXT void
NOTHROW(KCALL vm_copyfromphys_noidentity)(void *__restrict dst,
                                          PHYS vm_phys_t src,
                                          size_t num_bytes) {
	for (;;) {
		size_t temp;
		temp = vm_copyfromphys_noidentity_partial(dst, src, num_bytes);
		if (temp >= num_bytes)
			break;
		dst = (byte_t *)dst + temp;
		src += temp;
		num_bytes -= temp;
	}
}
#endif /* !NO_PHYS_IDENTITY */

PRIVATE ATTR_FREETEXT ATTR_PURE byte_t
NOTHROW(KCALL acpi_memsum)(void const *__restrict p, size_t n_bytes) {
	byte_t result = 0;
	byte_t *iter, *end;
	end = (iter = (byte_t *)p) + n_bytes;
	for (; iter != end; ++iter)
		result += *iter;
	return result;
}

PRIVATE ATTR_FREETEXT ATTR_PURE byte_t
NOTHROW(KCALL acpi_memsum_phys)(vm_phys_t p, size_t n_bytes) {
	u8 buf[256];
	byte_t result = 0;
	while (n_bytes) {
		size_t cnt = MIN(n_bytes, COMPILER_LENOF(buf));
		vm_copyfromphys_noidentity(buf, p, cnt);
		result += acpi_memsum(buf, cnt);
		n_bytes -= cnt;
		p += cnt;
	}
	return result;
}


PRIVATE ATTR_FREETEXT RSDPDescriptor *
NOTHROW(KCALL RSDP_LocateInRange)(VIRT uintptr_t base, size_t bytes) {
	uintptr_t iter, end;
	/* Make sure not to search unmapped memory! */
	if (base < KERNEL_CORE_BASE) {
		base += bytes;
		if (base <= KERNEL_CORE_BASE)
			return NULL;
		bytes = base - KERNEL_CORE_BASE;
		base  = KERNEL_CORE_BASE;
	}
	if ((base + bytes) < base)
		bytes = 0 - base;
	end = (iter = (uintptr_t)base) + bytes;
	printk(FREESTR(KERN_DEBUG "[acpi] Searching for RSDPDescriptor in %p...%p\n"),
	       iter - KERNEL_CORE_BASE, (end - 1) - KERNEL_CORE_BASE);
	/* Clamp the search area to a 16-byte alignment. */
	iter = CEIL_ALIGN(iter, RSDPDESCRIPTOR_ALIGN);
	end  = FLOOR_ALIGN(end, RSDPDESCRIPTOR_ALIGN);
	for (; iter < end; iter += RSDPDESCRIPTOR_ALIGN) {
		PRIVATE union {
			char c[8];
#ifdef __x86_64__
			u64  u;
#else /* __x86_64__ */
			u32  u[2];
#endif /* !__x86_64__ */
		} const signature = {
			{ 'R', 'S', 'D', ' ', 'P', 'T', 'R', ' ' }
		};
		RSDPDescriptor *result = (RSDPDescriptor *)iter;
		/* Check for the signature. */
#ifdef __x86_64__
		if (((u64 *)result->rsdp_signature)[0] != signature.u)
			continue;
#else /* __x86_64__ */
		if (((u32 *)result->rsdp_signature)[0] != signature.u[0])
			continue;
		if (((u32 *)result->rsdp_signature)[1] != signature.u[1])
			continue;
#endif /* !__x86_64__ */
		/* When found, check the checksum. */
		if (!acpi_memsum(result, offsetafter(RSDPDescriptor, rsdp_rsdtaddr)))
			return result;
	}
	return NULL;
}

PRIVATE ATTR_FREETEXT RSDPDescriptor *
NOTHROW(KCALL RSDP_LocateDescriptor)(void) {
	RSDPDescriptor *result;
	uintptr_t base;
	base = (uintptr_t)*(u16 volatile *)(KERNEL_CORE_BASE + 0x40E);
	result = RSDP_LocateInRange(KERNEL_CORE_BASE + base, 1024);
	if (result)
		goto done;
	result = RSDP_LocateInRange(KERNEL_CORE_BASE + 0x0e0000, 0x020000);
done:
	return result;
}




INTERN ATTR_FREETEXT void NOTHROW(KCALL x86_initialize_acpi)(void) {
	RSDPDescriptor *rsdp;
	ACPISDTHeader header;
	/* TODO: Commandline option to override address of this structure */
	/* TODO: Commandline option to disable detection of this structure */
	rsdp = RSDP_LocateDescriptor();
	if unlikely(!rsdp) {
		printk(FREESTR(KERN_DEBUG "[acpi] RSDPDescriptor not found\n"));
		return;
	}
	printk(FREESTR(KERN_DEBUG "[acpi] RSDPDescriptor located at %p [oem: %.?q, rev: %I8u]\n"),
	       (uintptr_t)rsdp - KERNEL_CORE_BASE,
	       COMPILER_LENOF(rsdp->rsdp_oemid),
	       rsdp->rsdp_oemid,
	       rsdp->rsdp_revision);
	acpi_mode = ACPI_MODE_RSDT;
	acpi_root = (vm_phys_t)rsdp->rsdp_rsdtaddr;
	if (rsdp->rsdp_revision >= 2) {
		/* Use XSDT (but validate it first) */
		if (rsdp->rsdp_length < offsetof(RSDPDescriptor,rsdp_reserved) ||
		    acpi_memsum(rsdp, rsdp->rsdp_length) != 0) {
			printk(FREESTR(KERN_ERR "[acpi] XSDT table extension is corrupted (using RSDT instead)\n"));
		} else {
			acpi_mode = ACPI_MODE_XSDT;
			acpi_root = (vm_phys_t)rsdp->rsdp_xsdtaddr;
		}
	}
	vm_copyfromphys_noidentity(&header, acpi_root, sizeof(ACPISDTHeader));
	/* Validate the header. */
	if unlikely(acpi_memsum_phys(acpi_root, header.rsdp_length) != 0) {
		printk(FREESTR(KERN_ERR "[acpi] Corrupted %cSDT checksum [table: %I64p...%I64p]\n"),
		       acpi_mode == ACPI_MODE_RSDT ? 'R' : 'X',
		       (u64)acpi_root,
		       (u64)acpi_root + header.rsdp_length - 1);
		return;
	}

	/* Figure out how many tables there are. */
	acpi_sdt_count = (header.rsdp_length - sizeof(ACPISDTHeader)) / ACPI_POINTER_SIZE;
	if unlikely(!acpi_sdt_count) {
		printk(FREESTR(KERN_ERR "[acpi] %cSDT contains no SDTs [table: %I64p...%I64p]\n"),
		       acpi_mode == ACPI_MODE_RSDT ? 'R' : 'X',
		       (u64)acpi_root,
		       (u64)acpi_root + header.rsdp_length - 1);
		return;
	}

	/* Preserve the contents of the RSDT table. */
	minfo_addbank(acpi_root,
	              (vm_phys_t)header.rsdp_length,
	              PMEMBANK_TYPE_DEVICE);

	/* Go through all available tables, enumerating them and validating their checksum
	 * Each table that checks out is then marked as PRESERVE, while each table that appears
	 * to be corrupt gets its signature overwritten with all ZEROes, so when later searching
	 * the table, we don't end up stumbling over corrupted entries.
	 * Note though, that corrupted entries in themself probably indicate a bigger problem... */
	{
		size_t i;
		for (i = 0; i < acpi_sdt_count; ++i) {
			vm_phys_t addr, base;
			addr = acpi_root + sizeof(ACPISDTHeader) + i * ACPI_POINTER_SIZE;
			/* Dereference the base pointer. */
			base = 0;
			vm_copyfromphys_noidentity(&base, addr, ACPI_POINTER_SIZE);
			/* Load the component header. */
			vm_copyfromphys_noidentity(&header, base, sizeof(header));
			/* Validate the table. */
			if unlikely(acpi_memsum_phys(base, header.rsdp_length) != 0) {
				printk(FREESTR(KERN_ERR "[acpi:sdt:%Iu:%.?q] corrupted table [table: %I64p...%I64p, oem: %.?q, oemtab: %.?q]\n"),
				       i, COMPILER_LENOF(header.rsdp_signature), header.rsdp_signature,
				       (u64)base, (u64)base + header.rsdp_length - 1,
				       COMPILER_LENOF(header.rsdp_oemid), header.rsdp_oemid,
				       COMPILER_LENOF(header.rsdp_oemtableid), header.rsdp_oemtableid);
				memset(header.rsdp_signature, 0, sizeof(header.rsdp_signature));
				vm_copytophys(base + offsetof(ACPISDTHeader, rsdp_signature),
				              &header.rsdp_signature[0], sizeof(header.rsdp_signature));
				continue;
			}
			printk(FREESTR(KERN_INFO "[acpi:sdt:%Iu:%.?q] found table [table: %I64p...%I64p, oem: %.?q, oemtab: %.?q]\n"),
			       i, COMPILER_LENOF(header.rsdp_signature), header.rsdp_signature,
			       (u64)base, (u64)base + header.rsdp_length - 1,
			       COMPILER_LENOF(header.rsdp_oemid), header.rsdp_oemid,
			       COMPILER_LENOF(header.rsdp_oemtableid), header.rsdp_oemtableid);
			minfo_addbank(base, (vm_phys_t)header.rsdp_length, PMEMBANK_TYPE_DEVICE);
		}
	}

#if 0 /* TODO: Remove me */
	{
		FADT fadt;
		if (acpi_lookup("FACP", &fadt, sizeof(fadt))) {
			printk(FREESTR(KERN_DEBUG "[acpi] fadt_Dsdt = %I32p\n"),fadt.fadt_Dsdt);
		}
	}
#endif
}


PUBLIC size_t
NOTHROW(KCALL acpi_lookup)(char const signature[4],
                           void *buf, size_t buflen,
                           vm_phys_t *ptableaddr) {
	size_t i, result;
	assert(buflen >= sizeof(ACPISDTHeader));
	for (i = 0; i < acpi_sdt_count; ++i) {
		vm_phys_t addr, base;
		size_t missing;
		addr = acpi_root + sizeof(ACPISDTHeader) + i * ACPI_POINTER_SIZE;
		base = ACPI_POINTER_SIZE == 4
		       ? (vm_phys_t)vm_readphysl_unaligned(addr)
		       : (vm_phys_t)vm_readphysq_unaligned(addr);
		vm_copyfromphys(buf, base, sizeof(ACPISDTHeader));
		if (*(u32 *)((ACPISDTHeader *)buf)->rsdp_signature != *(u32 *)signature)
			continue;
		result = ((ACPISDTHeader *)buf)->rsdp_length;
		/* Make sure not to copy more than the given buffer can hold. */
		missing = buflen;
		if (buflen > result) {
			/* Zero-initialize trailing memory. */
			memset((byte_t *)buf + result, 0, buflen - result);
			missing = result;
		}
		if (missing > sizeof(ACPISDTHeader)) {
			/* Copy additional data. */
			vm_copyfromphys((byte_t *)buf + sizeof(ACPISDTHeader),
			                (vm_phys_t)(base + sizeof(ACPISDTHeader)),
			                missing - sizeof(ACPISDTHeader));
		}
		if (ptableaddr)
			*ptableaddr = base;
		return result;
	}
	return 0;
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_BOOT_ACPI_C */
