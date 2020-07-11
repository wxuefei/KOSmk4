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
#ifndef GUARD_MODRTM_MEMORY_C
#define GUARD_MODRTM_MEMORY_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "memory.h"

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/paging.h> /* PAGESIZE */
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <kernel/vm.h>
#include <kernel/vm/futex.h>
#include <sched/task.h>

#include <hybrid/__assert.h>
#include <hybrid/atomic.h>
#include <hybrid/sequence/bsearch.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "rtm.h"

DECL_BEGIN

/* Max amount of kernel heap memory that may be used by
 * a single instance of a `struct rtm_memory' structure. */
INTERN size_t rtm_memory_limit = 4 * PAGESIZE;

/* NOTE: The caller must be holding a read- or write-lock to `self' */
#define vm_datapart_get_rtm_version(self) \
	((self)->dp_futex ? (self)->dp_futex->fc_rtm_vers : 0)


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL rtm_memory_free)(struct rtm_memory *__restrict self, void *ptr) {
	self->rm_mem_avl += kmalloc_usable_size(ptr);
	kfree(ptr);
}

/* Try to truncate `*pheap_pointer' to point to a heap block of only `num_bytes'
 * bytes of memory, returning `true' on success (`*pheap_pointer' now points at
 * a heap block that is smaller than before, but still holds at least `num_bytes'
 * bytes of memory), or `false' (`*pheap_pointer' could not be trucated and has
 * been left unmodified)
 * NOTE: When `*pheap_pointer' is equal to `protected_pointer', always return `false' */
PRIVATE NONNULL((1)) bool
NOTHROW(FCALL rtm_memory_truncate)(struct rtm_memory *__restrict self,
                                   void **__restrict pheap_pointer,
                                   size_t num_bytes,
                                   void *protected_pointer) {
	void *heap_pointer;
	size_t oldavl, newavl;
	heap_pointer = *pheap_pointer;
	if (heap_pointer == protected_pointer)
		return false; /* Don't truncate this one! */
	oldavl = kmalloc_usable_size(heap_pointer);
	assertf(oldavl >= num_bytes,
	        "oldavl    = %Iu\n"
	        "num_bytes = %Iu\n",
	        oldavl, num_bytes);
	if (oldavl == num_bytes)
		return false; /* Can't possibly be truncated! */
	/* Try to truncate the pointer */
	heap_pointer = krealloc_nx(heap_pointer, num_bytes, GFP_NORMAL);
	if unlikely(!heap_pointer)
		return false; /* Shouldn't happen (tm) */
	*pheap_pointer = heap_pointer;
	newavl = kmalloc_usable_size(heap_pointer);
	assertf(newavl >= num_bytes,
	        "newavl    = %Iu\n"
	        "num_bytes = %Iu\n",
	        newavl, num_bytes);
	assertf(newavl <= oldavl,
	        "newavl = %Iu\n"
	        "oldavl = %Iu\n",
	        newavl, oldavl);
	if (newavl >= oldavl) /* Should actually be `newavl == oldavl'; is `>=' for safety */
		return false; /* Nothing's changed */
	/* Yes! We did actually manage to truncate the pointer! */
	self->rm_mem_avl += oldavl;
	self->rm_mem_avl -= newavl;
	return true;
}


/* Try to reclaim unused memory by truncating heap pointers reachable from `self'
 * Note however that a heap pointer `protected_pointer' will not be truncated! */
PRIVATE NONNULL((1)) bool
NOTHROW(FCALL rtm_memory_reclaim)(struct rtm_memory *__restrict self,
                                  void *protected_pointer) {
	size_t i;
	bool result;
	/* Reclaim memory from the region vector */
	result = rtm_memory_truncate(self, (void **)&self->rm_regionv,
	                             self->rm_regionc * sizeof(struct rtm_memory_region *),
	                             protected_pointer);
	/* Reclaim memory from individual regions */
	for (i = 0; i < self->rm_regionc; ++i) {
		struct rtm_memory_region **pregion;
		pregion = &self->rm_regionv[i];
		result |= rtm_memory_truncate(self,
		                              (void **)pregion,
		                              offsetof(struct rtm_memory_region, mr_data) +
		                              rtm_memory_region_getsize(*pregion),
		                              protected_pointer);
	}
	return result;
}


/* Heap helpers that will automatically account for consumed heap memory. */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *FCALL
rtm_memory_malloc(struct rtm_memory *__restrict self,
                  size_t num_bytes) {
	void *result;
	size_t result_usable;
again:
	if unlikely(num_bytes > self->rm_mem_avl) {
		if (rtm_memory_reclaim(self, NULL))
			goto again;
do_throw_badalloc:
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		      num_bytes);
	}
	result        = kmalloc(num_bytes, GFP_NORMAL);
	result_usable = kmalloc_usable_size(result);
	if unlikely(result_usable > self->rm_mem_avl) {
		/* Must reclaim more memory! */
		if (!rtm_memory_reclaim(self, NULL)) {
do_free_result_and_throw_badalloc:
			kfree(result);
			num_bytes = result_usable;
			goto do_throw_badalloc;
		}
		/* Check if we've got sufficient memory now. */
		if (result_usable > self->rm_mem_avl)
			goto do_free_result_and_throw_badalloc;
	}
	self->rm_mem_avl -= result_usable;
	return result;
}

PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *FCALL
rtm_memory_realloc(struct rtm_memory *__restrict self,
                   void *ptr, size_t num_bytes) {
	void *result;
	size_t old_bytes;
	size_t result_bytes;
	size_t missing;
	if (!ptr)
		return rtm_memory_malloc(self, num_bytes);
	old_bytes = kmalloc_usable_size(ptr);
	if (num_bytes <= old_bytes) {
		/* Still try to truncate the pointer. */
		if (old_bytes == num_bytes)
			return ptr;
		result = krealloc_nx(ptr, num_bytes, GFP_NORMAL);
		if unlikely(!result)
			return ptr; /* Shouldn't happen (tm) */
		result_bytes = kmalloc_usable_size(result);
		assert(result_bytes <= old_bytes);
		self->rm_mem_avl += old_bytes;
		self->rm_mem_avl -= result_bytes;
		return result;
	}
	missing = num_bytes - old_bytes;
again_check_missing:
	if unlikely(missing > self->rm_mem_avl) {
		if (rtm_memory_reclaim(self, ptr))
			goto again_check_missing;
do_throw_badalloc_missing:
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		      missing);
	}
	/* Must increase the available memory. */
	result = krealloc_in_place(ptr, num_bytes, GFP_NORMAL);
	if (result) {
		/* Inplace relocation was successful! */
		assert(result == ptr);
		result_bytes = kmalloc_usable_size(result);
		assert(result_bytes >= num_bytes);
		assert(result_bytes > old_bytes);
		missing = result_bytes - old_bytes;
again_check_missing_after_inplace:
		if unlikely(missing > self->rm_mem_avl) {
			if (rtm_memory_reclaim(self, ptr))
				goto again_check_missing_after_inplace;
			/* (Try to) re-truncate the pointer to its previous size. */
			krealloc_in_place_nx(ptr, old_bytes, GFP_NORMAL);
			/* Allocation failed. */
			goto do_throw_badalloc_missing;
		}
		self->rm_mem_avl -= missing;
		return result;
	}
	/* The memory block is being extended, but cannot be done so in-place.
	 * -> Must allocate a new (larger) block to which we can then copy
	 *    the old block's data. */
	result = kmalloc(num_bytes, GFP_NORMAL);
	result_bytes = kmalloc_usable_size(result);
	assert(result_bytes >= num_bytes);
	assert(result_bytes > old_bytes);
	missing = result_bytes - old_bytes;
again_check_missing_after_malloc:
	if unlikely(missing > self->rm_mem_avl) {
		if (rtm_memory_reclaim(self, ptr))
			goto again_check_missing_after_malloc;
		kfree(result);
		/* Allocation failed. */
		goto do_throw_badalloc_missing;
	}
	/* Copy data into the new heap block. */
	memcpy(result, ptr, old_bytes);
	/* Free the old block */
	kfree(ptr);
	/* Return the new block */
	return result;
}


/* Helper to resize a `struct rtm_memory_region', such that the
 * `mr_data' vector of the returned region is capable of holding
 * at least `mr_data_size_in_bytes' bytes of memory.
 * Note however that this function does not update `mr_addr(lo|hi)'
 * to reflect the increased size of the `mr_data' vector! */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct rtm_memory_region *FCALL
rtm_memory_realloc_region(struct rtm_memory *__restrict self,
                          struct rtm_memory_region *__restrict region,
                          size_t mr_data_size_in_bytes) {
	void *result;
	result = rtm_memory_realloc(self,
	                            region,
	                            offsetof(struct rtm_memory_region, mr_data) +
	                            mr_data_size_in_bytes);
	return (struct rtm_memory_region *)result;
}


/* Finalize a given `struct rtm_memory' */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL rtm_memory_fini)(struct rtm_memory *__restrict self) {
	size_t i;
	for (i = 0; i < self->rm_regionc; ++i) {
		struct rtm_memory_region *region;
		region = self->rm_regionv[i];
		assert(region);
		/* Drop our reference to the accessed datapart */
		decref_unlikely(rtm_memory_region_getpart(region));
		kfree(region);
	}
	kfree(self->rm_regionv);
}


/* Read/Write RTM memory.
 * @throw: E_SEGFAULT: Faulty `addr', or `addr' points into a VIO mapping.
 * @throw: E_BADALLOC: Not enough memory, or `rtm_memory_limit' has been reached. */
PRIVATE NONNULL((1, 3)) void FCALL
rtm_memory_readwrite(struct rtm_memory *__restrict self, USER void *addr,
                     void *__restrict buf, size_t num_bytes, bool write)
		THROWS(E_BADALLOC, E_SEGFAULT) {
	/* Step #1: Check if the given `addr' is apart of an existing region. */
	size_t i;
	if (!num_bytes)
		return; /* Nothing to do here! */
again:
	i = 0;
	BSEARCHR(i, self->rm_regionv, self->rm_regionc,
	         ->mr_addrlo, ->mr_addrhi, addr) {
		struct rtm_memory_region *region;
		size_t avail_bytes;
		byte_t *rdat;
		/* Found it! */
		region = self->rm_regionv[i];
again_rw_region:
		assert(addr >= region->mr_addrlo);
		assert(addr <= region->mr_addrhi);
		avail_bytes = 1 + (size_t)((byte_t *)region->mr_addrhi -
		                           (byte_t *)addr);
		/* Start by copying whatever amount of data has already been loaded. */
		rdat = region->mr_data + (size_t)((byte_t *)addr -
		                                  (byte_t *)region->mr_addrlo);
		if likely(avail_bytes >= num_bytes) {
			/* All data is already available */
			if (write) {
				buf = mempcpy(rdat, buf, num_bytes);
				rtm_memory_region_setchanged(region);
			} else {
				buf = mempcpy(buf, rdat, num_bytes);
			}
			return;
		}
		if (write) {
			buf = mempcpy(rdat, buf, avail_bytes);
			rtm_memory_region_setchanged(region);
		} else {
			buf = mempcpy(buf, rdat, avail_bytes);
		}
		addr = (USER byte_t *)addr + avail_bytes;
		num_bytes -= avail_bytes;
		/* Some data is still missing.
		 * -> Check if the next region starts where the current left off.
		 *    If it does (start there, that is), then we can continue
		 *    accessing data from it. */
		if ((i + 1) < self->rm_regionc) {
			struct rtm_memory_region *next_region;
			next_region = self->rm_regionv[i + 1];
			if (next_region->mr_addrlo == (byte_t *)region->mr_addrhi + 1) {
				/* Yes! -> Continue accessing from this region! */
				region = next_region;
				++i;
				goto again_rw_region;
			}
		}
	}
	/* No region is associated with `addr'!
	 * -> Must allocate a new one, or try to extend an existing one.
	 *
	 * But first off: Check that the given `addr' is valid when `rm_chkuser' is set. */
	if (self->rm_chkuser) {
		if (write) {
			validate_writable(addr, num_bytes);
		} else {
			validate_readable(addr, num_bytes);
		}
	}
	{
		struct vm *effective_vm;
		struct vm_node *node;
		struct vm_datapart *node_part;
		struct rtm_memory_region *region;
		size_t j, access_bytes;
		/* Next, acquire a lock to the effective VM */
#ifdef KERNELSPACE_HIGHMEM
		effective_vm = &vm_kernel;
		if (ADDR_ISUSER(addr)) {
			size_t maxsize;
			effective_vm = THIS_VM;
			/* Check if the entire address range is apart of user-space. */
			maxsize = (size_t)((byte_t *)KERNELSPACE_BASE - (byte_t *)addr);
			if unlikely(num_bytes > maxsize) {
				/* Split the read into 2 segments. */
				rtm_memory_readwrite(self,
				                     (byte_t *)KERNELSPACE_BASE,
				                     (byte_t *)buf + maxsize,
				                     num_bytes - maxsize,
				                     write);
				num_bytes = maxsize;
			}
#ifdef ADDR_IS_NONCANON
			if (ADDR_IS_NONCANON((byte_t *)addr + num_bytes - 1)) {
				uintptr_t context;
				context = E_SEGFAULT_CONTEXT_FAULT |
				          E_SEGFAULT_CONTEXT_NONCANON;
				if (write)
					context |= E_SEGFAULT_CONTEXT_WRITING;
				if (self->rm_chkuser)
					context |= E_SEGFAULT_CONTEXT_USERCODE;
				THROW(E_SEGFAULT_UNMAPPED,
				      (byte_t *)addr + num_bytes - 1,
				      context);
			}
#endif /* ADDR_IS_NONCANON */
		}
#else /* KERNELSPACE_HIGHMEM */
		effective_vm = THIS_VM;
		if (ADDR_ISKERN(addr)) {
			size_t maxsize;
			if unlikely((byte_t *)addr + num_bytes < (byte_t *)addr) {
				uintptr_t context;
				context = E_SEGFAULT_CONTEXT_FAULT;
				if (write)
					context |= E_SEGFAULT_CONTEXT_WRITING;
				if (self->rm_chkuser)
					context |= E_SEGFAULT_CONTEXT_USERCODE;
				THROW(E_SEGFAULT_UNMAPPED, 0, context);
			}
			effective_vm = &vm_kernel;
			/* Check if the entire address range is apart of kernel-space. */
			maxsize = (size_t)((byte_t *)KERNELSPACE_END - (byte_t *)addr);
			if unlikely(num_bytes > maxsize) {
#ifdef ADDR_IS_NONCANON
				if (ADDR_IS_NONCANON((byte_t *)KERNELSPACE_END) {
					uintptr_t context;
					context = E_SEGFAULT_CONTEXT_FAULT |
					          E_SEGFAULT_CONTEXT_NONCANON;
					if (write)
						context |= E_SEGFAULT_CONTEXT_WRITING;
					if (self->rm_chkuser)
						context |= E_SEGFAULT_CONTEXT_USERCODE;
					THROW(E_SEGFAULT_UNMAPPED,
					      (byte_t *)KERNELSPACE_END,
					      context);
				}
#endif /* ADDR_IS_NONCANON */
				/* Split the read into 2 segments. */
				rtm_memory_readwrite(self,
				                     (byte_t *)KERNELSPACE_END,
				                     (byte_t *)buf + maxsize,
				                     num_bytes - maxsize,
				                     write);
				num_bytes = maxsize;
			}
		}
#endif /* !KERNELSPACE_HIGHMEM */
		/* Force the address range to be faulted. */
#ifdef LIBVIO_CONFIG_ENABLED
		vm_forcefault_p(effective_vm, addr, num_bytes,
		                VM_FORCEFAULT_FLAG_READ |
		                VM_FORCEFAULT_FLAG_NOVIO);
#else /* LIBVIO_CONFIG_ENABLED */
		vm_forcefault_p(effective_vm, addr, num_bytes,
		                VM_FORCEFAULT_FLAG_READ);
#endif /* !LIBVIO_CONFIG_ENABLED */
again_lock_effective_vm:
		sync_read(effective_vm);
		/* Locate the VM node that is backing the storage for `addr' */
		node = vm_getnodeofaddress(effective_vm, (void *)addr);
		/* Verify address permissions. */
#ifdef LIBVIO_CONFIG_ENABLED
		if unlikely(!node || (node_part = node->vn_part) == NULL ||
		            node_part->dp_state == VM_DATAPART_STATE_VIOPRT)
#else /* LIBVIO_CONFIG_ENABLED */
		if unlikely(!node || (node_part = node->vn_part) == NULL)
#endif /* !LIBVIO_CONFIG_ENABLED */
		{
			uintptr_t context;
			context = E_SEGFAULT_CONTEXT_FAULT;
#ifdef LIBVIO_CONFIG_ENABLED
			if (node && node->vn_part &&
			    node->vn_part->dp_state == VM_DATAPART_STATE_VIOPRT)
				context |= E_SEGFAULT_CONTEXT_VIO;
#endif /* LIBVIO_CONFIG_ENABLED */
			sync_endread(effective_vm);
			/* Unmapped address! */
			if (self->rm_chkuser)
				context |= E_SEGFAULT_CONTEXT_USERCODE;
			if (write)
				context |= E_SEGFAULT_CONTEXT_WRITING;
			THROW(E_SEGFAULT_UNMAPPED, addr, context);
		}
		/* NOTE: For write-access, we assert both read+write, since any write operation in RTM-mode is
		 *       the equivalent of a read-compare-exchange operation, meaning that in order to perform
		 *       a write, we literally and figuratively have to perform a read first! */
		if unlikely(write ? (node->vn_prot & (VM_PROT_READ | VM_PROT_WRITE)) != (VM_PROT_READ | VM_PROT_WRITE)
		                  : !(node->vn_prot & VM_PROT_READ)) {
			uintptr_t context;
			sync_endread(effective_vm);
			/* Unmapped address! */
			context = 0;
			if (self->rm_chkuser)
				context |= E_SEGFAULT_CONTEXT_USERCODE;
			if (write) {
				THROW(E_SEGFAULT_READONLY, addr,
				      E_SEGFAULT_CONTEXT_WRITING |
				      context);
			} else {
				THROW(E_SEGFAULT_NOTREADABLE, addr,
				      context);
			}
		}
		/* Figure out how many bytes we actually want to access from `node' */
		access_bytes = (size_t)((byte_t *)vm_node_getend(node) - (byte_t *)addr);
		if (access_bytes > num_bytes)
			access_bytes = num_bytes;
		/* Check for some additional region with which the given
		 * address range may overlap at some later point in time.
		 * HINT: `i' is still left initialized by the `BSEARCHR()' above,
		 *       and currently points at where the region for `addr' would
		 *       have been (if it existed), or at the region before that
		 *       index. */
		if (i >= self->rm_regionc) {
			assertf(i == 0,
			        "i                = %Iu\n"
			        "self->rm_regionc = %Iu\n",
			        i, self->rm_regionc);
		} else {
			struct rtm_memory_region *next_region;
			next_region = self->rm_regionv[i];
			if (next_region->mr_addrhi < addr) {
				/* `i' points before the should-be index. */
				++i;
				/* And now `i' points at the should-be index. */
				if (i < self->rm_regionc) {
#ifndef NDEBUG
					next_region = self->rm_regionv[i];
#endif /* !NDEBUG */
					goto verify_access_range;
				}
			} else {
				size_t distance_to_next_region;
verify_access_range:
				assertf(next_region->mr_addrlo > addr,
				        "addr                   = %p\n"
				        "next_region->mr_addrlo = %p\n"
				        "next_region->mr_addrhi = %p\n",
				        addr,
				        next_region->mr_addrlo,
				        next_region->mr_addrhi);
				distance_to_next_region = (size_t)((byte_t *)next_region->mr_addrlo -
				                                   (byte_t *)addr);
				if (access_bytes > distance_to_next_region)
					access_bytes = distance_to_next_region;
			}
		}
		/* Access permissions have been confirmed, and we now know that we're
		 * really dealing with a proper memory mapping that is able to represent
		 * actual memory. (rather than some other kind of mapping)
		 *
		 * At this point, we must check for some other RTM region that way already
		 * exist for `node_part', since the RTM region list may only ever contain
		 * a single region for any given datapart, and because every data part can
		 * be mapped an arbitrary number of times within a single VM, we have to
		 * make sure that no other region already describes this one! */
		for (j = 0; j < self->rm_regionc; ++j) {
			struct vm_node *aliasing_node;
			struct vm *aliasing_node_vm;
			size_t access_offset_into_node;
			byte_t *aliasing_region_node_start;
			region = self->rm_regionv[j];
			if likely(rtm_memory_region_getpart(region) != node_part)
				continue;
			/* Welp... There's an overlap with this region's datapart. */
			assert((byte_t *)region->mr_addrhi < (byte_t *)addr ||
			       (byte_t *)region->mr_addrlo > (byte_t *)addr + access_bytes - 1);
			/* Check if this region is mapped by the same VM node. - If it is, then 
			 * we have to extend this region to also contain `addr...+=access_bytes'.
			 * Otherwise, we have to perform an address translation so that the
			 * access instead happens for this region's mapping. (At least we know
			 * that if the data parts are identical, then both of the VM node
			 * mappings will have identical sizes, since the size of a vm_node is
			 * always identical to the size of an associated vm_datapart!) */
			aliasing_node_vm = &vm_kernel;
			if (ADDR_ISUSER(region->mr_addrlo))
				aliasing_node_vm = THIS_VM;
			if likely(aliasing_node_vm == effective_vm) {
				aliasing_node = vm_getnodeofaddress(effective_vm, region->mr_addrlo);
				if (aliasing_node == node) {
					size_t old_region_size;
					sync_endread(effective_vm);
					/* Extend node to encompass `addr...+=access_bytes' */
					old_region_size = rtm_memory_region_getsize(region);
					if (addr < region->mr_addrlo) {
						/* Extend downwards */
						size_t missing_bytes, copy_error;
						missing_bytes = (size_t)((byte_t *)region->mr_addrlo - (byte_t *)addr);
						assert(missing_bytes);
						region = rtm_memory_realloc_region(self, region,
						                                   old_region_size +
						                                   missing_bytes);
						/* Shift region data to account of newly allocated space. */
						memmoveup(region->mr_data + missing_bytes,
						          region->mr_data, old_region_size);
						region->mr_addrlo = (byte_t *)region->mr_addrlo - missing_bytes;
						self->rm_regionv[j] = region; /* Inherit */
						/* Fill in the missing area. */
						copy_error = memcpy_nopf(region->mr_data,
						                         region->mr_addrlo,
						                         missing_bytes);
						if unlikely(copy_error != 0) {
							/* Failed to load region data.
							 * -> Since we're extending downwards, `region' now contains a hole of
							 *    uninitialized data. But since RTM regions must be continuous, the
							 *    only thing we can do to recover is discard everything we're just
							 *    did to extend `region' and try again from the start... */
							memmovedown(region->mr_data,
							            region->mr_data + missing_bytes,
							            old_region_size);
							region->mr_addrlo = (byte_t *)region->mr_addrlo + missing_bytes;
							goto again;
						}
						assert((byte_t *)addr == (byte_t *)region->mr_addrlo);
					} else {
						/* Extend upwards */
						size_t missing_bytes, copy_error;
						USER byte_t *missing_addr_start;
						assertf((byte_t *)addr + access_bytes - 1 > region->mr_addrhi,
						        "addr + .... - 1    = %p\n"
						        "region->mr_addrhi  = %p\n",
						        (byte_t *)addr + access_bytes - 1,
						        region->mr_addrhi);
						missing_bytes = (size_t)(((byte_t *)addr + access_bytes) -
						                         ((byte_t *)region->mr_addrhi + 1));
						assert(missing_bytes);
						region = rtm_memory_realloc_region(self, region,
						                                   old_region_size +
						                                   missing_bytes);
						missing_addr_start = (USER byte_t *)region->mr_addrhi + 1;
						region->mr_addrhi = (byte_t *)region->mr_addrhi + missing_bytes;
						self->rm_regionv[j] = region; /* Inherit */
						/* Fill in the missing area. */
						copy_error = memcpy_nopf(region->mr_data + old_region_size,
						                         missing_addr_start, missing_bytes);
						if unlikely(copy_error != 0) {
							/* Re-truncate the region so we can at least
							 * account for what we were able to copy! */
							region->mr_addrhi = (byte_t *)region->mr_addrhi - copy_error;
							goto again;
						}
						assert((byte_t *)addr + access_bytes - 1 == (byte_t *)region->mr_addrhi);
					}
					goto do_access_region;
				}
			} else {
				if unlikely(!sync_tryread(aliasing_node_vm)) {
					sync_endread(effective_vm);
					while (!sync_canread(aliasing_node_vm))
						task_yield();
					goto again_lock_effective_vm;
				}
				aliasing_node = vm_getnodeofaddress(effective_vm, region->mr_addrlo);
			}
			assert(aliasing_node != node);
			/* Figure out access offsets so we can translate `addr' */
			access_offset_into_node    = (size_t)((byte_t *)addr - (byte_t *)vm_node_getstart(node));
			aliasing_region_node_start = (byte_t *)vm_node_getstart(aliasing_node);
			printk(KERN_DEBUG "[rtm] Region redirect: data from %p...%p is already mapped at %p...%p (map %p -> %p)\n",
			       vm_node_getmin(node), vm_node_getmax(node),
			       vm_node_getmin(aliasing_node), vm_node_getmax(aliasing_node),
			       addr, aliasing_region_node_start + access_offset_into_node);
			if unlikely(aliasing_node_vm != effective_vm)
				sync_endread(aliasing_node_vm);
			sync_endread(effective_vm);
			/* Calculate the translated address for the aliasing mapping, and try again. */
			addr = aliasing_region_node_start +
			       access_offset_into_node;
			goto again;
		}
		incref(node_part); /* To-be inherited by the new RTM region. */
		sync_endread(effective_vm);
		/* Create a new RTM region. */
		TRY {
			region = (struct rtm_memory_region *)rtm_memory_malloc(self,
			                                                       offsetof(struct rtm_memory_region, mr_data) +
			                                                       access_bytes);
		} EXCEPT {
			decref(node_part);
			RETHROW();
		}
		region->mr_addrlo = (byte_t *)addr;
		region->mr_addrhi = (byte_t *)addr + access_bytes - 1;
		region->mr_part   = node_part; /* Inherit reference */
		region->mr_vers   = 0;
		if (ATOMIC_READ(node_part->dp_futex) != NULL) {
			/* Check for non-zero version counter. */
			struct vm_futex_controller *ftx;
			TRY {
				sync_read(node_part);
			} EXCEPT {
				rtm_memory_free(self, region);
				decref(node_part);
				RETHROW();
			}
			ftx = ATOMIC_READ(node_part->dp_futex);
			if likely(ftx != NULL)
				region->mr_vers = ftx->fc_rtm_vers;
			sync_endread(node_part);
		}
		/* Insert `region' into the vector at index `i' */
		{
			size_t avl_vector_size;
			size_t req_vector_size;
			avl_vector_size = kmalloc_usable_size(self->rm_regionv);
			req_vector_size = (self->rm_regionc + 1) * sizeof(struct rtm_memory_region *);
			if (req_vector_size > avl_vector_size) {
				/* Must increase the allocated vector size. */
				struct rtm_memory_region **newvec;
				TRY {
					newvec = (struct rtm_memory_region **)rtm_memory_realloc(self,
					                                                         self->rm_regionv,
					                                                         req_vector_size);
				} EXCEPT {
					rtm_memory_free(self, region);
					decref(node_part);
					RETHROW();
				}
				self->rm_regionv = newvec;
			}
			memmoveupc(&self->rm_regionv[i + 1],
			           &self->rm_regionv[i],
			           self->rm_regionc - i,
			           sizeof(struct rtm_memory_region *));
			++self->rm_regionc;
			self->rm_regionv[i] = region; /* Inherit */
		}
		/* Populate the accessed `region' with data from the VM
		 * NOTE: We use `memcpy_nopf()' for this to ensure that the current memory state
		 *       remains consistent with what was set-up by the `vm_forcefault()' above. */
		{
			size_t copy_error;
			copy_error = memcpy_nopf(region->mr_data,
			                         addr,
			                         access_bytes);
			if unlikely(copy_error != 0) {
				/* The last `copy_error' bytes could not be copied... */
				size_t copy_ok;
				assert(copy_error <= access_bytes);
				copy_ok = access_bytes - copy_error;
				if (!copy_ok) {
					/* Nothing was copied (remove `region' from the vector) */
					--self->rm_regionc;
					memmovedownc(&self->rm_regionv[i],
					             &self->rm_regionv[i + 1],
					             self->rm_regionc - i,
					             sizeof(struct rtm_memory_region *));
					rtm_memory_free(self, region);
					decref(node_part);
				} else {
					/* At least ~something~ was copied (Update `region' to
					 * only contain the portion that was _actually_ copied) */
					region->mr_addrhi = (byte_t *)addr + copy_ok - 1;
				}
				goto again;
			}
		}
do_access_region:
		assert((byte_t *)addr >= (byte_t *)region->mr_addrlo);
		assert((byte_t *)addr + access_bytes - 1 <= (byte_t *)region->mr_addrhi);
		{
			byte_t *rdat;
			rdat = region->mr_data + (size_t)((byte_t *)addr -
			                                  (byte_t *)region->mr_addrlo);
			/* Copy accessed data. */
			if (write) {
				memcpy(rdat, buf, access_bytes);
				rtm_memory_region_setchanged(region);
			} else {
				memcpy(buf, rdat, access_bytes);
			}
		}
		/* Check if we're done, and if we aren't, continue
		 * reading after what has already been read. */
		if (access_bytes >= num_bytes)
			return;
		addr = (byte_t *)addr + access_bytes;
		buf  = (byte_t *)buf + access_bytes;
		num_bytes -= access_bytes;
		goto again;
	}
}

/* Read RTM memory.
 * @throw: E_SEGFAULT: Faulty `addr', or `addr' points into a VIO mapping.
 * @throw: E_BADALLOC: Not enough memory, or `rtm_memory_limit' has been reached. */
INTERN NONNULL((1, 3)) void FCALL
rtm_memory_read(struct rtm_memory *__restrict self, USER void const *addr,
                void *__restrict buf, size_t num_bytes)
		THROWS(E_BADALLOC, E_SEGFAULT) {
	rtm_memory_readwrite(self,
	                     (USER void *)addr,
	                     buf,
	                     num_bytes,
	                     false);
}

/* Write RTM memory.
 * @throw: E_SEGFAULT: Faulty `addr', or `addr' points into a VIO mapping.
 * @throw: E_BADALLOC: Not enough memory, or `rtm_memory_limit' has been reached. */
INTERN NONNULL((1, 3)) void FCALL
rtm_memory_write(struct rtm_memory *__restrict self, USER void *addr,
                 void const *__restrict buf, size_t num_bytes)
		THROWS(E_BADALLOC, E_SEGFAULT) {
	rtm_memory_readwrite(self,
	                     addr,
	                     (void *)buf,
	                     num_bytes,
	                     true);
}







#ifdef VM_FORCEFAULT_FLAG_NOVIO
#define VM_FORCEFAULT_FLAG_NOVIO_OPT VM_FORCEFAULT_FLAG_NOVIO
#else /* VM_FORCEFAULT_FLAG_NOVIO */
#define VM_FORCEFAULT_FLAG_NOVIO_OPT 0
#endif /* !VM_FORCEFAULT_FLAG_NOVIO */

PRIVATE void FCALL
prefault_memory_for_writing(USER void *addr, size_t num_bytes) {
	vm_forcefault(ADDR_ISKERN(addr) ? &vm_kernel
	                                : THIS_VM,
	              addr, num_bytes,
	              VM_FORCEFAULT_FLAG_WRITE |
	              VM_FORCEFAULT_FLAG_NOVIO_OPT);
}



PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL rtm_memory_endwrite_modified_parts)(struct rtm_memory const *__restrict self,
                                                  size_t i) {
	while (i) {
		struct rtm_memory_region *region;
		--i;
		region = self->rm_regionv[i];
		if (rtm_memory_region_waschanged(region))
			sync_endwrite(rtm_memory_region_getpart(region));
	}
}


/* Verify that the given address range is writable
 * without any chance of triggering a #PF */
PRIVATE ATTR_PURE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL rtm_verify_writable_nopf)(USER CHECKED void *addr,
                                        size_t num_bytes) {
	num_bytes += (uintptr_t)addr & PAGEMASK;
	for (;;) {
		if (!pagedir_iswritable(addr))
			return false;
		if (num_bytes <= PAGESIZE)
			break;
		num_bytes -= PAGESIZE;
		addr = (byte_t *)addr + PAGESIZE;
	}
	return true;
}


/* Atomically verify RTM version integrity, as well as apply RTM memory modifications.
 * @return: true:  Memory successfully applied
 * @return: false: Version of memory inconsistency detected (try again) */
INTERN NONNULL((1)) bool FCALL
rtm_memory_apply(struct rtm_memory const *__restrict self) {
	struct vm *myvm;
	size_t i;
	bool must_allocate_missing_futex_controllers;
	bool has_modified_kern;
	bool has_modified_user;
	myvm  = THIS_VM;
again_forcefault:
	/* Step #1: prefault the address ranges of all modified regions. */
	for (i = 0; i < self->rm_regionc; ++i) {
		struct rtm_memory_region *region;
		region = self->rm_regionv[i];
		assert(region);
		if (!rtm_memory_region_waschanged(region))
			continue; /* Not modified... */
		/* Prefault memory. */
		prefault_memory_for_writing(region->mr_addrlo,
		                            rtm_memory_region_getsize(region));
	}

	/* Step #2: Acquire tx-locks to all of the modified data parts, and
	 *          verify that accessed data parts are still up-to-date */
again_acquire_region_locks:
	must_allocate_missing_futex_controllers = false;
	for (i = 0; i < self->rm_regionc; ++i) {
		struct rtm_memory_region *region;
		struct vm_datapart *part;
		region = self->rm_regionv[i];
		part   = rtm_memory_region_getpart(region);
		{
			struct vm_node *node;
			struct vm *effective_vm = myvm;
			size_t node_size_after_addr;
			pageid_t region_start_page;
			if (ADDR_ISKERN(region->mr_addrlo))
				effective_vm = &vm_kernel;
			region_start_page = PAGEID_ENCODE(region->mr_addrlo);
			node = vm_getnodeofpageid(myvm, region_start_page);
			if unlikely(!node || node->vn_part != part) {
				sync_endread(effective_vm);
				goto partially_release_locks_and_retry;
			}
			/* Make sure that the node has sufficient memory after `region->mr_addrlo'
			 * to account for at least `region->mr_size' bytes of memory. */
			node_size_after_addr = vm_node_getendpageid(node);
			sync_endread(effective_vm);
			node_size_after_addr -= region_start_page;
			node_size_after_addr *= PAGESIZE;
			node_size_after_addr += PAGESIZE - ((uintptr_t)region->mr_addrlo & PAGEMASK);
			if (rtm_memory_region_getsize(region) > node_size_after_addr)
				goto partially_release_locks_and_retry;
		}
		if (rtm_memory_region_waschanged(region)) {
			struct vm_futex_controller *fxc;
			if (!sync_trywrite(part)) {
				rtm_memory_endwrite_modified_parts(self, i);
				/* Poll until the lock becomes available. - _then_ try acquiring locks again */
				while (!sync_canwrite(part))
					task_yield();
				goto again_acquire_region_locks;
			}
			/* Verify that the version of this region did not change */
			fxc = part->dp_futex;
			if (fxc) {
				if (fxc->fc_rtm_vers != region->mr_vers) {
endwrite_par_and_release_locks_and_retry:
					sync_endwrite(part);
					goto partially_release_locks_and_retry;
				}
			} else {
				if (region->mr_vers != 0)
					goto endwrite_par_and_release_locks_and_retry;
				/* We need to allocate this missing futex controller down below */
				must_allocate_missing_futex_controllers = true;
			}
		} else {
			if (!sync_tryread(part)) {
				rtm_memory_endwrite_modified_parts(self, i);
				/* Poll until the lock becomes available. - _then_ try acquiring locks again */
				while (!sync_canread(part))
					task_yield();
				goto again_acquire_region_locks;
			}
			/* Verify that the version of this region did not change */
			if (vm_datapart_get_rtm_version(part) != region->mr_vers) {
				sync_endread(part);
				goto partially_release_locks_and_retry;
			}
			sync_endread(part);
		}
	}
	if (must_allocate_missing_futex_controllers) {
		/* Allocate missing futex controllers. */
		for (i = 0; i < self->rm_regionc; ++i) {
			struct rtm_memory_region *region;
			struct vm_datapart *part;
			struct vm_futex_controller *ftx;
			region = self->rm_regionv[i];
			if (!rtm_memory_region_waschanged(region))
				continue;
			part = rtm_memory_region_getpart(region);
			ftx  = part->dp_futex;
			if (ftx)
				continue; /* Already allocated. */
			/* Must allocate the missing controller.
			 * Note that we're holding a couple of non-recursive locks
			 * at the moment, so we must be careful not to do a blocking
			 * memory allocation! */
			ftx = vm_futex_controller_allocf_nx(GFP_ATOMIC);
			if unlikely(!ftx) {
				/* The difficult case:
				 * In this case, we must release all of our beautiful locks, :(
				 * just so we can do a blocking heap allocation. And once
				 * that's done we'll have to start over with acquiring all
				 * of the necessary locks... */
				rtm_memory_endwrite_modified_parts(self, self->rm_regionc);
#ifndef __OPTIMIZE_SIZE__
again_allocate_ftx_controller_for_part:
#endif /* !__OPTIMIZE_SIZE__ */
				ftx = vm_futex_controller_alloc();
				/* Try to install `ftx' into `part' */
				TRY {
					sync_write(part);
				} EXCEPT {
					vm_futex_controller_free(ftx);
					RETHROW();
				}
				if likely(!part->dp_futex) {
					/* Install the new controller. */
					part->dp_futex = ftx;
					sync_endwrite(part);
				} else {
					/* Race condition: Someone else already installed a controller. */
					sync_endwrite(part);
					vm_futex_controller_free(ftx);
				}
#ifndef __OPTIMIZE_SIZE__
				/* While we're at it, also try to look head if there are
				 * more modified regions with parts that are lacking their
				 * futex controllers. Because if there are more, then we
				 * can just fill in their controllers all at once, without
				 * having to fill them in one-at-a-time. */
				for (++i; i < self->rm_regionc; ++i) {
					region = self->rm_regionv[i];
					if (!rtm_memory_region_waschanged(region))
						continue; /* Not needed */
					part = rtm_memory_region_getpart(region);
					if (ATOMIC_READ(part->dp_futex))
						continue; /* Already allocated */
					/* Allocate another controller for this one! */
					goto again_allocate_ftx_controller_for_part;
				}
#endif /* !__OPTIMIZE_SIZE__ */
				goto again_acquire_region_locks;
			}
			part->dp_futex = ftx;
		}
	}

	/* Step #3: Verify that all modified in-memory data ranges can be
	 *          written to without any chance of triggering a pagefault. */
	has_modified_kern = false;
	has_modified_user = false;
	for (i = 0; i < self->rm_regionc; ++i) {
		struct rtm_memory_region *region;
		struct vm_datapart *part;
		struct vm *effective_vm;
		region = self->rm_regionv[i];
		if (!rtm_memory_region_waschanged(region))
			continue; /* Unchanged region. */
		part = rtm_memory_region_getpart(region);
		assert(sync_writing(part));
		effective_vm = myvm;
		if (ADDR_ISKERN(region->mr_addrlo))
			effective_vm = &vm_kernel;
		if (effective_vm == &vm_kernel) {
			/* Ensure that we've for a read-lock to the kernel's VM */
			if (!has_modified_kern) {
				if (!sync_tryread(&vm_kernel))
					goto again_acquire_region_locks_for_vm_lock;
				has_modified_kern = true;
			}
		} else {
			/* Ensure that we've for a read-lock to the user's VM */
			if (!has_modified_user) {
				if (!sync_tryread(effective_vm)) {
again_acquire_region_locks_for_vm_lock:
					rtm_memory_endwrite_modified_parts(self, self->rm_regionc);
					while (!sync_canread(effective_vm))
						task_yield();
					goto again_acquire_region_locks;
				}
				has_modified_user = true;
			}
		}
		/* Verify that the backing memory of the accessed range is still writable.
		 * This was originally asserted by `prefault_memory_for_writing()' above,
		 * which we'd have to jump back to if memory isn't writable any more. */
		if unlikely(!rtm_verify_writable_nopf(region->mr_addrlo,
		                                      rtm_memory_region_getsize(region))) {
			if (has_modified_kern)
				sync_endwrite(&vm_kernel);
			if (has_modified_user)
				sync_endwrite(myvm);
			rtm_memory_endwrite_modified_parts(self, self->rm_regionc);
			goto again_forcefault;
		}
	}
	/* ===== Point of no return =====
	 * After this point, we can no longer rewind to try again! */

	/* Step #4: Apply modifications, update version counters, and release locks */
	assert(i == self->rm_regionc);
	while (i) {
		struct rtm_memory_region *region;
		struct vm_datapart *part;
		--i;
		region = self->rm_regionv[i];
		if (!rtm_memory_region_waschanged(region))
			continue; /* Unchanged region. */
		part = rtm_memory_region_getpart(region);
		assert(sync_writing(part));
		/* Copy modified memory.
		 * NOTE: We've verified that all of this memory can be written without
		 *       causing a pagefault in step #3, and we know that the associated
		 *       mappings won't have changed in the mean time because we're still
		 *       holding locks to their corresponding VMs! */
#ifdef NDEBUG
		memcpy(region->mr_addrlo,
		       region->mr_data,
		       rtm_memory_region_getsize(region));
#else /* NDEBUG */
		{
			size_t error;
			error = memcpy_nopf(region->mr_addrlo,
			                    region->mr_data,
			                    rtm_memory_region_getsize(region));
			assertf(error == 0,
			        "But we're asserted that all of this should be writable...\n"
			        "region->mr_addrlo = %p\n"
			        "region->mr_addrhi = %p\n"
			        "region->mr_data   = %p\n"
			        "SIZE(region)      = %Iu\n"
			        "error             = %Iu\n",
			        region->mr_addrlo,
			        region->mr_addrhi,
			        region->mr_data,
			        rtm_memory_region_getsize(region),
			        error);
		}
#endif /* !NDEBUG */
		/* Increment the RTM version counter of this part. */
		assert(part->dp_futex);
		++part->dp_futex->fc_rtm_vers;
		COMPILER_BARRIER();
		/* Release our lock to this part. */
		sync_endwrite(part);
	}
	if (has_modified_kern)
		sync_endwrite(&vm_kernel);
	if (has_modified_user)
		sync_endwrite(myvm);
	return true;
partially_release_locks_and_retry:
	rtm_memory_endwrite_modified_parts(self, i);
	return false;
}


DECL_END

#endif /* !GUARD_MODRTM_MEMORY_C */