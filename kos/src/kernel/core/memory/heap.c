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
#ifndef GUARD_KERNEL_SRC_MEMORY_HEAP_C
#define GUARD_KERNEL_SRC_MEMORY_HEAP_C 1
#define __OMIT_HEAP_CONSTANT_P_WRAPPERS 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/hook.h>
#include <kernel/except.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>
#include <hybrid/sequence/atree.h>
#include <hybrid/sequence/list.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* Define the ABI for the address tree used by heaps. */
#define ATREE(x)       mfree_tree_##x
#define ATREE_CALL     KCALL
#define ATREE_NOTHROW  NOTHROW
#define ATREE_NODE_MIN MFREE_MIN
#define ATREE_NODE_MAX MFREE_MAX
#define Tkey           VIRT uintptr_t
#define T              struct mfree
#define N_NODEPATH     mf_laddr
#include <hybrid/sequence/atree-abi.h>

#if 0 /* Quick toggle to disable all debugging aids. */
#undef CONFIG_DEBUG_HEAP
#undef CONFIG_HEAP_RANDOMIZE_OFFSETS
#endif

DECL_BEGIN

STATIC_ASSERT(SIZEOF_MFREE == offsetof(struct mfree, mf_data));

#if defined(NDEBUG) || 0
#define heap_validate(heap)    (void)0
#define heap_validate_all()    (void)0
#endif /* NDEBUG */

#if defined(NDEBUG) || 1 /* Pedantic heap validation enable/disable */
#define heap_validate_after_free(heap) (void)0
#define heap_validate_all_after_free() (void)0
#else /* NDEBUG */
#define heap_validate_after_free(heap) heap_validate(heap)
#define heap_validate_all_after_free() heap_validate_all()
#endif /* !NDEBUG */

#if defined(NDEBUG) || 1 /* Pedantic heap validation enable/disable */
#define heap_validate_pedantic(heap) (void)0
#define heap_validate_all_pedantic() (void)0
#else /* NDEBUG */
#define heap_validate_pedantic(heap) heap_validate(heap)
#define heap_validate_all_pedantic() heap_validate_all()
#endif /* !NDEBUG */

#undef TRACE
#if 0
#define TRACE(...) printk(KERN_DEBUG __VA_ARGS__)
#else
#define TRACE(...) (void)0
#endif


#if !defined(NDEBUG) && 1
#define PRINTK_SYSTEM_ALLOCATION(...) printk(KERN_DEBUG __VA_ARGS__)
#else /* !NDEBUG */
#define PRINTK_SYSTEM_ALLOCATION(...) (void)0
#endif /* NDEBUG */


#if defined(NDEBUG) || 0
#define HEAP_ASSERT(expr)       (void)0
#define HEAP_ASSERTE(expr)      (expr)
#define HEAP_ASSERTF(expr, ...) (void)0
#else /* NDEBUG */
#ifdef NDEBUG
#define HEAP_ASSERTE /* nothing */
#else /* NDEBUG */
#define HEAP_ASSERTE assert
#endif /* !NDEBUG */
#define HEAP_ASSERT  assert
#define HEAP_ASSERTF assertf
#endif /* !NDEBUG */


#if !defined(NDEBUG) && 0
#define HEAP_ADD_DANGLE(self, count)                             \
	(((count) && (self) == &kernel_locked_heap)                  \
	 ? printk(KERN_RAW "%s(%d) : Add dangle %Iu + %Iu -> %Iu\n", \
	          __FILE__, __LINE__, (self)->h_dangle,              \
	          count, (self)->h_dangle + (count))                 \
	 : (void)0,                                                  \
	 ATOMIC_FETCHADD((self)->h_dangle, count))
#define HEAP_SUB_DANGLE(self, count)                             \
	(((count) && (self) == &kernel_locked_heap)                  \
	 ? printk(KERN_RAW "%s(%d) : Sub dangle %Iu - %Iu -> %Iu\n", \
	          __FILE__, __LINE__, (self)->h_dangle,              \
	          count, (self)->h_dangle - (count))                 \
	 : (void)0,                                                  \
	 ATOMIC_FETCHSUB((self)->h_dangle, count))
#else /* !NDEBUG */
#define HEAP_ADD_DANGLE(self,count) ATOMIC_FETCHADD((self)->h_dangle,count)
#define HEAP_SUB_DANGLE(self,count) ATOMIC_FETCHSUB((self)->h_dangle,count)
#endif /* NDEBUG */

#if 0
#define DEFAULT_OVERALLOC  (PAGESIZE)
#define DEFAULT_FREETHRESH (PAGESIZE*2)
#elif PAGESIZE*16 > 65536
#define DEFAULT_OVERALLOC  (PAGESIZE*16)
#define DEFAULT_FREETHRESH (PAGESIZE*32)
#else
#define DEFAULT_OVERALLOC  (PAGESIZE*32)
#define DEFAULT_FREETHRESH (PAGESIZE*64)
#endif


#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x

#ifdef CONFIG_DEBUG_HEAP
PRIVATE void
NOTHROW(KCALL debug_pat_loadpart)(struct vm_datablock *__restrict UNUSED(self),
                                  datapage_t UNUSED(start),
                                  vm_phys_t buffer, size_t num_data_pages) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	HEAP_ASSERT((buffer & PAGEMASK) == 0);
	HEAP_ASSERT(num_data_pages != 0);
	tramp  = THIS_TRAMPOLINE_BASE;
	backup = pagedir_push_mapone(tramp, buffer,
	                             PAGEDIR_MAP_FREAD |
	                             PAGEDIR_MAP_FWRITE);
	for (;;) {
		pagedir_syncone(tramp);
		memsetl(tramp, DEBUGHEAP_FRESH_MEMORY, PAGESIZE / 4);
		if (!--num_data_pages)
			break;
		buffer += PAGESIZE;
		pagedir_mapone(tramp, buffer,
		               PAGEDIR_MAP_FREAD |
		               PAGEDIR_MAP_FWRITE);
	}
	pagedir_pop_mapone(tramp, backup);
}

PUBLIC struct vm_datablock_type vm_datablock_debugheap_type = {
	/* .dt_destroy  = */ NULL,
	/* .dt_initpart = */ NULL,
	/* .dt_loadpart = */ &debug_pat_loadpart,
	/* .dt_savepart = */ NULL,
};

PUBLIC struct vm_datablock vm_datablock_debugheap = {
	/* .db_refcnt = */ ((refcnt_t)-1)/2,
	/* .db_lock   = */ RWLOCK_INIT,
	/* .db_type   = */ &vm_datablock_debugheap_type,
#ifdef LIBVIO_CONFIG_ENABLED
	/* .db_vio    = */ NULL,
#endif /* LIBVIO_CONFIG_ENABLED */
	/* .db_parts  = */ VM_DATABLOCK_ANONPARTS_INIT,
	VM_DATABLOCK_INIT_PAGEINFO(0)
};

DEFINE_DBG_BZERO_OBJECT(vm_datablock_debugheap.db_lock);
#endif /* CONFIG_DEBUG_HEAP */


/* Unlock the kernel heaps while inside of the debugger. */
DEFINE_DBG_BZERO_VECTOR(&kernel_heaps[0].h_lock,
                         __GFP_HEAPCOUNT,
                         sizeof(kernel_heaps[0].h_lock),
                         sizeof(kernel_heaps[0]));

DEFINE_VALIDATABLE_HEAP(kernel_default_heap);
DEFINE_VALIDATABLE_HEAP(kernel_locked_heap);
PUBLIC struct heap kernel_heaps[__GFP_HEAPCOUNT] = {
	/* Define the controller structures for the builtin kernel heaps. */
	/* [GFP_NORMAL] = */ HEAP_INIT(DEFAULT_OVERALLOC,
	                               DEFAULT_FREETHRESH,
	                               HINT_GETADDR(KERNEL_VMHINT_HEAP),
	                               HINT_GETMODE(KERNEL_VMHINT_HEAP)),
	/* [GFP_LOCKED] = */ HEAP_INIT(DEFAULT_OVERALLOC,
	                               DEFAULT_FREETHRESH,
	                               HINT_GETADDR(KERNEL_VMHINT_LHEAP),
	                               HINT_GETMODE(KERNEL_VMHINT_LHEAP)),
};


#ifdef CONFIG_DEBUG_HEAP
PRIVATE WUNUSED byte_t *
NOTHROW(KCALL find_modified_address)(byte_t *start, u32 pattern, size_t num_bytes) {
	while ((uintptr_t)start & 3) {
		if __untraced(!num_bytes)
			return NULL;
		if __untraced(*(u8 *)start != ((u8 *)&pattern)[(uintptr_t)start & 3])
			return start;
		--num_bytes, ++start;
	}
	while (num_bytes > 4) {
		if __untraced(!((uintptr_t)start & PAGEMASK)) {
			for (;;) {
#if 0
#elif defined(ARCH_PAGEDIR_HAVE_CHANGED)
				/* If supported by the host, speed this up using page directory dirty bits. */
				if (pagedir_haschanged(start)) {
					pagedir_unsetchanged(start);
					break;
				}
#else
				if (pagedir_ismapped(start))
					break;
#endif
				if (num_bytes <= PAGESIZE)
					return NULL;
				start += PAGESIZE;
				num_bytes -= PAGESIZE;
			}
		}
		if __untraced(*(u32 *)start == pattern) {
			start += 4;
			num_bytes -= 4;
			continue;
		}
		if __untraced(((u8 *)start)[0] != ((u8 *)&pattern)[0])
			return start + 0;
		if __untraced(((u8 *)start)[1] != ((u8 *)&pattern)[1])
			return start + 1;
		if __untraced(((u8 *)start)[2] != ((u8 *)&pattern)[2])
			return start + 2;
		return start + 3;
	}
	while (num_bytes) {
		if __untraced(*(u8 *)start != ((u8 *)&pattern)[(uintptr_t)start & 3])
			return start;
		--num_bytes, ++start;
	}
	return NULL;
}

PRIVATE WUNUSED ATTR_PURE NONNULL((1)) u8
NOTHROW(KCALL mfree_get_checksum)(struct mfree *__restrict self) {
	u8 sum = 0, *iter, *end;
	end = (iter = (u8 *)&self->mf_size) + sizeof(self->mf_size);
	for (; iter < end; ++iter)
		sum += *iter;
	return 0 - sum;
}

PRIVATE NONNULL((1)) void
NOTHROW(KCALL mfree_set_checksum)(struct mfree *__restrict self) {
	self->mf_szchk = mfree_get_checksum(self);
}

PRIVATE bool
NOTHROW(KCALL quick_verify_mfree)(struct mfree *__restrict self) {
	if __untraced(!IS_ALIGNED((uintptr_t)self, HEAP_ALIGNMENT))
		goto bad;
	TRY {
		struct mfree **pself;
		if __untraced(!IS_ALIGNED(self->mf_size, HEAP_ALIGNMENT))
			goto bad;
		pself = self->mf_lsize.ln_pself;
		if __untraced(!ADDR_ISKERN(pself))
			goto bad;
		if __untraced(*pself != self)
			goto bad;
		return true;
	} EXCEPT {
	}
bad:
	return false;
}


INTDEF struct heap *const __kernel_validatable_heaps_start[];
INTDEF struct heap *const __kernel_validatable_heaps_end[];

/* Validate the memory of the given heap for
 * consistency, checking for invalid use-after-free. */
PUBLIC NOBLOCK ATTR_NOINLINE void
NOTHROW(KCALL heap_validate_all)(void) {
	struct heap *const *iter;
	for (iter = __kernel_validatable_heaps_start;
	     iter < __kernel_validatable_heaps_end; ++iter)
		(heap_validate)(*iter);
}

PUBLIC NOBLOCK ATTR_NOINLINE NONNULL((1)) void
NOTHROW(KCALL heap_validate)(struct heap *__restrict self) {
	unsigned int i;
	/* If we're already poisoned, then there's no point in trying to look for more errors.
	 * -> We're already screwed, and our caller probably knows that. But we may not be
	 *    screwed badly enough to actually cause our caller's operation to break... */
	if (kernel_poisoned())
		return;
	if (!sync_tryread(&self->h_lock))
		return;
#if 0
	printk(KERN_TRACE "[heap] Begin validate %p (%Iu, from %p)\n",
	       self, self->h_lock.arw_lock, THIS_TASK);
#endif
	for (i = 0; i < COMPILER_LENOF(self->h_size); ++i) {
		struct mfree **piter, *iter;
		piter = &self->h_size[i];
		for (; (iter = *piter) != NULL; piter = &iter->mf_lsize.ln_next) {
			void *faulting_address;
			u32 expected_data;
			assertf(IS_ALIGNED((uintptr_t)iter, HEAP_ALIGNMENT),
			        "\tPotential USE-AFTER-FREE of <%p...%p>\n"
			        "Free node at %p isn't aligned by `HEAP_ALIGNMENT' (pointed to by %p)",
			        piter, (uintptr_t)piter + sizeof(void *) - 1, iter, piter);
			assertf(iter->mf_size >= HEAP_MINSIZE,
			        "\tPotential USE-AFTER-FREE of <%p...%p>\n"
			        "Free node at %p is too small (%Iu=%#Ix bytes) (size bucket %Iu/%Iu)\n",
			        &iter->mf_size, (uintptr_t)&iter->mf_size + sizeof(size_t) - 1,
			        iter, iter->mf_size, iter->mf_size, i, COMPILER_LENOF(self->h_size));
			assertf((uintptr_t)iter + iter->mf_size > (uintptr_t)iter,
			        "\tPotential USE-AFTER-FREE of <%p...%p>\n"
			        "Free node at %p is too large (%Iu=%#Ix bytes) (size bucket %Iu/%Iu)\n"
			        "PHYS: %I64p",
			        &iter->mf_size, (uintptr_t)&iter->mf_size + sizeof(size_t) - 1,
			        iter, iter->mf_size, iter->mf_size, i, COMPILER_LENOF(self->h_size),
			        (u64)pagedir_translate(&iter->mf_size));
			assertf(IS_ALIGNED(iter->mf_size, HEAP_ALIGNMENT),
			        "\tPotential USE-AFTER-FREE of <%p...%p>\n"
			        "Size of free node at %p...%p (%Iu=%#Ix bytes) isn't aligned by `HEAP_ALIGNMENT'",
			        &iter->mf_size, (uintptr_t)&iter->mf_size + sizeof(size_t) - 1,
			        MFREE_MIN(iter), MFREE_MAX(iter), iter->mf_size, iter->mf_size);
			assertf(!(iter->mf_flags & ~MFREE_FMASK),
			        "\tPotential USE-AFTER-FREE of <%p>\n"
			        "Free node at %p...%p contains invalid flags %#x",
			        &iter->mf_flags, MFREE_MIN(iter),
			        MFREE_MAX(iter), iter->mf_flags);
			assertf(!iter->mf_laddr.a_min || quick_verify_mfree(iter->mf_laddr.a_min),
			        "\tPotential USE-AFTER-FREE of <%p...%p>\n"
			        "Free node at %p...%p has broken min-pointer to invalid node at %p",
			        (uintptr_t)&iter->mf_laddr.a_min,
			        (uintptr_t)&iter->mf_laddr.a_min + sizeof(void *) - 1,
			        MFREE_MIN(iter), MFREE_MAX(iter), iter->mf_laddr.a_min);
			assertf(!iter->mf_laddr.a_max || quick_verify_mfree(iter->mf_laddr.a_max),
			        "\tPotential USE-AFTER-FREE of <%p...%p>\n"
			        "Free node at %p...%p has broken min-pointer to invalid node at %p",
			        (uintptr_t)&iter->mf_laddr.a_max,
			        (uintptr_t)&iter->mf_laddr.a_max + sizeof(void *) - 1,
			        MFREE_MIN(iter), MFREE_MAX(iter), iter->mf_laddr.a_max);
			assertf(iter->mf_lsize.ln_pself == piter,
			        "\tPotential USE-AFTER-FREE of <%p...%p>\n"
			        "Expected self pointer of free node %p...%p at %p, but is actually at %p",
			        (uintptr_t)&iter->mf_lsize.ln_pself,
			        (uintptr_t)&iter->mf_lsize.ln_pself + sizeof(void *) - 1,
			        MFREE_MIN(iter), MFREE_MAX(iter), piter, iter->mf_lsize.ln_pself);
			assertf(iter->mf_szchk == mfree_get_checksum(iter),
			        "\tPotential USE-AFTER-FREE of <%p...%p> or %p\n"
			        "Invalid checksum in free node %p...%p (expected %#.2I8x, but got %#.2I8x)",
			        (uintptr_t)&iter->mf_size, (uintptr_t)(&iter->mf_size + 1) - 1,
			        (uintptr_t)&iter->mf_szchk,
			        MFREE_MIN(iter), MFREE_MAX(iter),
			        mfree_get_checksum(iter), iter->mf_szchk);
			/* Verify memory of this node. */
			expected_data    = iter->mf_flags & MFREE_FZERO ? 0 : DEBUGHEAP_NO_MANS_LAND;
			faulting_address = find_modified_address(iter->mf_data, expected_data,
			                                         iter->mf_size - SIZEOF_MFREE);
			if unlikely_untraced(faulting_address) {
				u8 *fault_start = (u8 *)faulting_address - 32;
				PREEMPTION_DISABLE();
				if __untraced(!pagedir_ismapped(fault_start))
					fault_start = (u8 *)FLOOR_ALIGN((uintptr_t)faulting_address, PAGESIZE);
				if __untraced(fault_start < (u8 *)iter->mf_data)
					fault_start = (u8 *)iter->mf_data;
				printk(KERN_RAW "\n\n\n");
				kernel_panic("%$[hex]\n"
				             "\tIllegal USE-AFTER-FREE of <%p>\n"
				             "Free node:     %p...%p\n"
				             "Node offset:   %Iu (%#Ix)\n"
				             "Expected byte: %.2I8x\n"
				             "Found byte:    %.2I8x",
				             (size_t)((size_t)16 + 2 * (size_t)((u8 *)faulting_address - fault_start)), fault_start,
				             faulting_address,
				             MFREE_MIN(iter), MFREE_MAX(iter),
				             (size_t)((uintptr_t)faulting_address - MFREE_MIN(iter)),
				             (size_t)((uintptr_t)faulting_address - MFREE_MIN(iter)),
				             ((u8 *)&expected_data)[(uintptr_t)faulting_address & 3],
				             *(u8 *)faulting_address);
			}
		}
	}
#if 0
	printk(KERN_TRACE "[heap] End validate %p (%Iu, from %p)\n",
	       self, self->h_lock.arw_lock, THIS_TASK);
#endif
	sync_endread(&self->h_lock);
}
#else /* CONFIG_DEBUG_HEAP */
#define mfree_set_checksum(self) (void)0

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL heap_validate)(struct heap *__restrict UNUSED(self)) {
}

PUBLIC NOBLOCK void
NOTHROW(KCALL heap_validate_all)(void) {
}
#endif /* !CONFIG_DEBUG_HEAP */


#ifdef CONFIG_DEBUG_HEAP
PRIVATE NOBLOCK void
NOTHROW(KCALL reset_heap_data)(byte_t *ptr, u32 pattern, size_t num_bytes) {
	if (num_bytes < PAGESIZE)
		goto do_remainder;
	/* Only write pages that have been allocated. */
	if ((uintptr_t)ptr & PAGEMASK) {
		size_t inpage_free = PAGESIZE - ((uintptr_t)ptr & PAGEMASK);
		if (inpage_free > num_bytes)
			inpage_free = num_bytes;
		mempatl(ptr, pattern, inpage_free);
		ptr += inpage_free;
		num_bytes -= inpage_free;
	}
	while (num_bytes >= PAGESIZE) {
		/* Only reset pages that have been allocated.
		 * This optimization goes hand-in-hand with `heap_validate_all()'
		 * not checking pages that haven't been allocated. */
		if (pagedir_ismapped(ptr))
			memsetl(ptr, pattern, PAGESIZE / 4);
		num_bytes -= PAGESIZE;
		ptr += PAGESIZE;
	}
	if (num_bytes) {
do_remainder:
		mempatl(ptr, pattern, num_bytes);
	}
}
#endif /* CONFIG_DEBUG_HEAP */




LOCAL NOBLOCK void
NOTHROW(KCALL heap_insert_node_unlocked)(struct heap *__restrict self,
                                          struct mfree *__restrict node) {
	struct mfree **pslot, *slot;
	size_t num_bytes = node->mf_size;
	HEAP_ASSERTF(node->mf_size, "Empty node at %p", node);
	/* Insert the node into the address and size trees. */
	mfree_tree_insert(&self->h_addr, node);
	/* Figure out where the free-slot should go in the chain of free ranges. */
	pslot = &LLIST_HEAD(self->h_size[HEAP_BUCKET_OF(num_bytes)]);
	while ((slot = *pslot) != NULL &&
	       MFREE_SIZE(slot) < num_bytes)
		pslot = &LLIST_NEXT(slot, mf_lsize);
	node->mf_lsize.ln_pself = pslot;
	node->mf_lsize.ln_next  = slot;
	if (slot)
		slot->mf_lsize.ln_pself = &node->mf_lsize.ln_next;
	*pslot = node;
}


/* Acquire a lock to the heap, while also serving any pending free operations.
 * @return: true:  Successfully acquired a lock. (Always returned by `heap_acquirelock' when `GFP_ATOMIC' isn't set)
 * @return: false: Failed to acquire a lock (`GFP_ATOMIC' was set, and the operation would have blocked) */
LOCAL bool KCALL heap_acquirelock(struct heap *__restrict self, gfp_t flags);
LOCAL WUNUSED bool NOTHROW(KCALL heap_acquirelock_nx)(struct heap *__restrict self, gfp_t flags);
LOCAL NOBLOCK bool NOTHROW(KCALL heap_acquirelock_atomic)(struct heap *__restrict self);


/* Same as `heap_free_raw_lock_and_maybe_unlock_impl()',
 * but always unlock the heap afterwards. */
LOCAL NOBLOCK void
NOTHROW(KCALL heap_free_raw)(struct heap *__restrict self,
                              VIRT void *ptr, size_t num_bytes,
                              gfp_t flags);

/* Upon entry, the heap must not be locked.
 * This function then tries to acquire a lock to the heap without blocking.
 * If this succeeds, it calls forward to `heap_free_raw_and_unlock_impl()'.
 * If it doesn't, it will instead track the given memory block as a pending free.
 * @return: true:  The heap remains locked (the caller inherits the lock). 
 * @return: false: The heap was unlocked before returning.*/
LOCAL NOBLOCK bool
NOTHROW(KCALL heap_free_raw_lock_and_maybe_unlock_impl)(struct heap *__restrict self,
                                                         VIRT void *ptr, size_t num_bytes,
                                                         gfp_t flags);

/* Upon entry, the heap must be locked.
 * @return: true:  The heap remains locked. 
 * @return: false: The heap was unlocked.*/
PRIVATE NOBLOCK bool
NOTHROW(KCALL heap_free_raw_and_unlock_impl)(struct heap *__restrict self,
                                              VIRT void *ptr, size_t num_bytes,
                                              gfp_t flags);


/* @return: true:  Successfully served all pending free operations,
 *                 following which the heap lock remains acquired.
 * @return: false: Successfully served all pending free operations,
 *                 but the heap lock was lost and could not be re-
 *                 acquired. */
PRIVATE bool
NOTHROW(KCALL heap_serve_pending)(struct heap *__restrict self,
                                   struct heap_pending_free *__restrict pend,
                                   gfp_t flags) {
	struct heap_pending_free *next;
	for (;;) {
		bool still_locked;
		size_t pend_size;
		gfp_t pend_flags;
		next       = pend->hpf_next;
		pend_size  = pend->hpf_size;
		pend_flags = pend->hpf_flags;
		/* Bring the pending free block back into a consistent state! */
		if (pend_flags & GFP_CALLOC)
			memset(pend, 0, sizeof(struct heap_pending_free));
#ifdef CONFIG_DEBUG_HEAP
		else {
			mempatl(pend, DEBUGHEAP_NO_MANS_LAND,
			        sizeof(struct heap_pending_free));
		}
#endif
		still_locked = heap_free_raw_and_unlock_impl(self, pend, pend_size, pend_flags);
		if (!still_locked) {
			/* Try to re-acquire the lock. */
			if (!sync_trywrite(&self->h_lock)) {
				/* In ATOMIC mode, we mustn't block, but must instead re-add the chain of
				 * pending free operations that we took away from the heap, back onto it. */
				if (flags & GFP_ATOMIC) {
					if (next) {
						struct heap_pending_free *current;
						/* Find the last pending segment we need to re-schedule as pending. */
						pend = next;
						while (pend->hpf_next)
							pend = pend->hpf_next;
						do {
							pend->hpf_next = current = ATOMIC_READ(self->h_pfree);
						} while (!ATOMIC_CMPXCH_WEAK(self->h_pfree, current, next));
					}
					/* Indicate to the caller that we lost the lock. */
					return false;
				}
				/* Just block until we've acquired the lock again! */
				sync_write(&self->h_lock);
			}
		}
		/* Continue with the next part. */
		if (!next)
			break;
		pend = next;
	}
	assert(sync_writing(&self->h_lock));
	return true; /* Lock is still being held. */
}


/* Acquire a lock to the heap, while also serving any pending free operations.
 * @return: true:  Successfully acquired a lock.
 * @return: false: Failed to acquire a lock (`GFP_ATOMIC' was set, and the operation would have blocked) */
LOCAL bool KCALL
heap_acquirelock(struct heap *__restrict self, gfp_t flags) {
	struct heap_pending_free *pend;
	if (!sync_trywrite(&self->h_lock)) {
		if (flags & GFP_ATOMIC)
			return false;
		sync_write(&self->h_lock);
	}
	pend = ATOMIC_XCH(self->h_pfree, NULL);
	if unlikely(pend)
		return heap_serve_pending(self, pend, flags);
	assert(sync_writing(&self->h_lock));
	return true;
}

LOCAL WUNUSED bool
NOTHROW(KCALL heap_acquirelock_nx)(struct heap *__restrict self, gfp_t flags) {
	struct heap_pending_free *pend;
	if (!sync_trywrite(&self->h_lock)) {
		if (flags & GFP_ATOMIC)
			return false;
		if (!sync_write_nx(&self->h_lock))
			return false;
	}
	pend = ATOMIC_XCH(self->h_pfree, NULL);
	if unlikely(pend)
		return heap_serve_pending(self, pend, flags);
	assert(sync_writing(&self->h_lock));
	return true;
}

LOCAL NOBLOCK bool
NOTHROW(KCALL heap_acquirelock_atomic)(struct heap *__restrict self) {
	struct heap_pending_free *pend;
	if (!sync_trywrite(&self->h_lock))
		return false;
	pend = ATOMIC_XCH(self->h_pfree, NULL);
	if unlikely(pend)
		return heap_serve_pending(self, pend, GFP_ATOMIC);
	assert(sync_writing(&self->h_lock));
	return true;
}




/* Upon entry, the heap must not be locked.
 * This function then tries to acquire a lock to the heap without blocking.
 * If this succeeds, it calls forward to `heap_free_raw_and_unlock_impl()'.
 * If it doesn't, it will instead track the given memory block as a pending free.
 * @return: true:  The heap remains locked (the caller inherits the lock). 
 * @return: false: The heap was unlocked before returning.*/
LOCAL NOBLOCK bool
NOTHROW(KCALL heap_free_raw_lock_and_maybe_unlock_impl)(struct heap *__restrict self,
                                                        VIRT void *ptr, size_t num_bytes,
                                                        gfp_t flags) {
	heap_validate_all_pedantic();
	if (!heap_acquirelock_atomic(self)) {
		/* Set up `ptr...num_bytes' as a pending free-block of the heap,
		 * to-be freed by whoever will be next to acquire a lock. */
		struct heap_pending_free *pend, *next;
		pend            = (struct heap_pending_free *)ptr;
		pend->hpf_size  = num_bytes;
		pend->hpf_flags = flags;
		do {
			next = ATOMIC_READ(self->h_pfree);
			pend->hpf_next = next;
		} while (!ATOMIC_CMPXCH_WEAK(self->h_pfree, next, pend));
		return false;
	}
	return heap_free_raw_and_unlock_impl(self, ptr, num_bytes, flags);
}


LOCAL NOBLOCK void
NOTHROW(KCALL heap_free_raw)(struct heap *__restrict self,
                              VIRT void *ptr, size_t num_bytes,
                              gfp_t flags) {
	bool still_locked;
	still_locked = heap_free_raw_lock_and_maybe_unlock_impl(self, ptr, num_bytes, flags);
	if (still_locked) {
		assert(sync_writing(&self->h_lock));
		sync_endwrite(&self->h_lock);
	}
}




/* Upon entry, the heap must be locked.
 * @return: true:  The heap remains locked. 
 * @return: false: The heap was unlocked.*/
PRIVATE NOBLOCK bool
NOTHROW(KCALL heap_free_raw_and_unlock_impl)(struct heap *__restrict self,
                                              VIRT void *ptr, size_t num_bytes,
                                              gfp_t flags) {
	ATREE_SEMI_T(uintptr_t)
	addr_semi;
	ATREE_LEVEL_T addr_level;
	struct mfree **pslot, *slot, *new_slot;
#ifdef CONFIG_DEBUG_HEAP
#ifdef CONFIG_HEAP_TRACE_DANGLE
	size_t dandle_size = 0;
#endif /* CONFIG_HEAP_TRACE_DANGLE */
#endif /* CONFIG_DEBUG_HEAP */
	HEAP_ASSERTF(num_bytes >= HEAP_MINSIZE,
	             "Invalid heap_free(): Too few bytes (%Iu < %Iu)",
	             num_bytes, HEAP_MINSIZE);
	HEAP_ASSERTF(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT),
	             "Invalid heap_free(): Unaligned base pointer %p",
	             ptr);
	HEAP_ASSERTF(IS_ALIGNED(num_bytes, HEAP_ALIGNMENT),
	             "Invalid heap_free(): Unaligned free size %Iu (%#Ix)",
	             num_bytes, num_bytes);
	HEAP_ASSERTF(((uintptr_t)ptr + num_bytes) > (uintptr_t)ptr,
	             "Address space overflow when freeing %p...%p",
	             ptr, (uintptr_t)ptr + num_bytes - 1);

	addr_semi  = ATREE_SEMI0(uintptr_t);
	addr_level = ATREE_LEVEL0(uintptr_t);
	/* Search for a node below, which could then be extended above. */
	pslot = mfree_tree_plocate_at(&self->h_addr, (uintptr_t)ptr - 1,
	                              &addr_semi, &addr_level);
	if (pslot) {
		slot = *pslot;
		HEAP_ASSERTE(mfree_tree_pop_at(pslot, addr_semi, addr_level) == slot);
		LLIST_REMOVE(slot, mf_lsize);

		/* Extend this node above. */
#ifndef CONFIG_DEBUG_HEAP
		slot->mf_flags &= flags & GFP_CALLOC;
		slot->mf_size += num_bytes;
#else /* !CONFIG_DEBUG_HEAP */
		if ((flags & GFP_CALLOC) && (slot->mf_flags & GFP_CALLOC)) {
			slot->mf_size += num_bytes;
		} else {
#ifdef CONFIG_HEAP_TRACE_DANGLE
			bool result;
			HEAP_ADD_DANGLE(self, slot->mf_size);
			dandle_size += slot->mf_size;
#endif /* CONFIG_HEAP_TRACE_DANGLE */
			sync_endwrite(&self->h_lock);
			if (flags & GFP_CALLOC) {
				heap_validate_all_pedantic();
				reset_heap_data((byte_t *)ptr, DEBUGHEAP_NO_MANS_LAND, num_bytes);
				heap_validate_all_pedantic();
				flags &= ~GFP_CALLOC;
			}
			if (slot->mf_flags & GFP_CALLOC) {
				heap_validate_all_pedantic();
				reset_heap_data((byte_t *)((uintptr_t)slot + SIZEOF_MFREE),
				                DEBUGHEAP_NO_MANS_LAND, slot->mf_size - SIZEOF_MFREE);
				heap_validate_all_pedantic();
			}
			ptr = (VIRT void *)slot;
			num_bytes += slot->mf_size;
			mempatl(ptr, DEBUGHEAP_NO_MANS_LAND, SIZEOF_MFREE);
#ifdef CONFIG_HEAP_TRACE_DANGLE
			result = heap_free_raw_lock_and_maybe_unlock_impl(self, ptr, num_bytes, flags);
			HEAP_SUB_DANGLE(self, dandle_size);
			return result;
#else /* CONFIG_HEAP_TRACE_DANGLE */
			return heap_free_raw_lock_and_maybe_unlock_impl(self, ptr, num_bytes, flags);
#endif /* !CONFIG_HEAP_TRACE_DANGLE */
		}
#endif /* CONFIG_DEBUG_HEAP */

		/* Check if there is another node above that we must now merge with. */
		addr_semi  = ATREE_SEMI0(uintptr_t);
		addr_level = ATREE_LEVEL0(uintptr_t);
		pslot = mfree_tree_plocate_at(&self->h_addr, (uintptr_t)ptr + num_bytes,
		                              &addr_semi, &addr_level);
		if unlikely(pslot) {
			struct mfree *high_slot;
			high_slot = *pslot;
			/* Include this high-slot in the union that will be freed. */
			HEAP_ASSERTE(mfree_tree_pop_at(pslot, addr_semi, addr_level) == high_slot);
			LLIST_REMOVE(high_slot, mf_lsize);
#ifndef CONFIG_DEBUG_HEAP
			slot->mf_flags &= high_slot->mf_flags & GFP_CALLOC;
			slot->mf_size += high_slot->mf_size;
			if (slot->mf_flags & GFP_CALLOC)
				memset(high_slot, 0, SIZEOF_MFREE);
#else /* !CONFIG_DEBUG_HEAP */
			if ((slot->mf_flags & GFP_CALLOC) &&
			    (high_slot->mf_flags & GFP_CALLOC)) {
				slot->mf_size += high_slot->mf_size;
				memset(high_slot, 0, SIZEOF_MFREE);
			} else {
#ifdef CONFIG_HEAP_TRACE_DANGLE
				bool result;
				HEAP_ADD_DANGLE(self, high_slot->mf_size);
				dandle_size += high_slot->mf_size;
#endif /* CONFIG_HEAP_TRACE_DANGLE */
				sync_endwrite(&self->h_lock);
				if (slot->mf_flags & GFP_CALLOC) {
					heap_validate_all_pedantic();
					reset_heap_data((byte_t *)((uintptr_t)slot + SIZEOF_MFREE),
					                DEBUGHEAP_NO_MANS_LAND,
					                slot->mf_size - SIZEOF_MFREE);
					heap_validate_all_pedantic();
				}
				if (high_slot->mf_flags & GFP_CALLOC) {
					heap_validate_all_pedantic();
					reset_heap_data((byte_t *)((uintptr_t)high_slot + SIZEOF_MFREE),
					                DEBUGHEAP_NO_MANS_LAND,
					                high_slot->mf_size - SIZEOF_MFREE);
					heap_validate_all_pedantic();
				}
				ptr       = (VIRT void *)slot;
				num_bytes = slot->mf_size + high_slot->mf_size;
				flags &= ~GFP_CALLOC;
				mempatl(slot, DEBUGHEAP_NO_MANS_LAND, SIZEOF_MFREE);
				mempatl(high_slot, DEBUGHEAP_NO_MANS_LAND, SIZEOF_MFREE);
#ifdef CONFIG_HEAP_TRACE_DANGLE
				result = heap_free_raw_lock_and_maybe_unlock_impl(self, ptr, num_bytes, flags);
				HEAP_SUB_DANGLE(self, dandle_size);
				return result;
#else /* CONFIG_HEAP_TRACE_DANGLE */
				return heap_free_raw_lock_and_maybe_unlock_impl(self, ptr, num_bytes, flags);
#endif /* !CONFIG_HEAP_TRACE_DANGLE */
			}
#endif /* CONFIG_DEBUG_HEAP */
		}
		/* No high-slot. Just re-insert our new, bigger node. */
		new_slot = slot;
		goto load_new_slot;
	}

	/* Search for a node above, which could then be extended below. */
	addr_semi  = ATREE_SEMI0(uintptr_t);
	addr_level = ATREE_LEVEL0(uintptr_t);
	pslot = mfree_tree_plocate_at(&self->h_addr, (uintptr_t)ptr + num_bytes,
	                              &addr_semi, &addr_level);
	if (pslot) {
		gfp_t slot_flags;
		size_t slot_size;
		slot = *pslot;
		HEAP_ASSERTE(mfree_tree_pop_at(pslot, addr_semi, addr_level) == slot);
		LLIST_REMOVE(slot, mf_lsize);
		/* Extend this node below. */

#ifndef CONFIG_DEBUG_HEAP
		slot_flags = slot->mf_flags & flags;
		slot_size  = slot->mf_size;
		if (slot_flags & GFP_CALLOC)
			memset(slot, 0, SIZEOF_MFREE);
		new_slot           = (struct mfree *)ptr;
		new_slot->mf_size  = slot_size + num_bytes;
		new_slot->mf_flags = slot_flags;
#else /* !CONFIG_DEBUG_HEAP */
		slot_flags = slot->mf_flags;
		slot_size  = slot->mf_size;
		if ((slot_flags & GFP_CALLOC) && (flags & GFP_CALLOC)) {
			memset(slot, 0, SIZEOF_MFREE);
			new_slot           = (struct mfree *)ptr;
			new_slot->mf_size  = slot_size + num_bytes;
			new_slot->mf_flags = slot_flags;
		} else {
#ifdef CONFIG_HEAP_TRACE_DANGLE
			bool result;
			HEAP_ADD_DANGLE(self, slot_size);
			dandle_size += slot_size;
#endif /* CONFIG_HEAP_TRACE_DANGLE */
			sync_endwrite(&self->h_lock);
			if (flags & GFP_CALLOC)
				reset_heap_data((byte_t *)ptr, DEBUGHEAP_NO_MANS_LAND, num_bytes);
			if (slot_flags & GFP_CALLOC)
				reset_heap_data((byte_t *)slot, DEBUGHEAP_NO_MANS_LAND, slot_size);
			else
				mempatl(slot, DEBUGHEAP_NO_MANS_LAND, SIZEOF_MFREE);
			flags &= ~GFP_CALLOC;
			num_bytes += slot_size;
#ifdef CONFIG_HEAP_TRACE_DANGLE
			result = heap_free_raw_lock_and_maybe_unlock_impl(self, ptr, num_bytes, flags);
			HEAP_SUB_DANGLE(self, dandle_size);
			return result;
#else /* CONFIG_HEAP_TRACE_DANGLE */
			return heap_free_raw_lock_and_maybe_unlock_impl(self, ptr, num_bytes, flags);
#endif /* !CONFIG_HEAP_TRACE_DANGLE */
		}
#endif /* CONFIG_DEBUG_HEAP */
		/* Re-insert our new, bigger node. */
		goto load_new_slot;
	}

	/* Create a new node. */
	new_slot           = (struct mfree *)ptr;
	new_slot->mf_size  = num_bytes;
	new_slot->mf_flags = flags & MFREE_FMASK;
load_new_slot:
#ifdef CONFIG_DEBUG_HEAP
#ifdef CONFIG_HEAP_TRACE_DANGLE
	/* Untrack danging heap data. */
	HEAP_SUB_DANGLE(self, dandle_size);
#endif /* CONFIG_HEAP_TRACE_DANGLE */
#endif /* CONFIG_DEBUG_HEAP */
	if (!(flags & GFP_NOMMAP) &&
	    new_slot->mf_size >= self->h_freethresh) {
		/*  When a slot grows larger than `self->h_freethresh' and
		 * `GFP_NOMMAP' isn't set, free as much of it as possible by
		 *  passing its memory to `core_page_free()' */
		void *free_minaddr = (void *)CEIL_ALIGN(MFREE_MIN(new_slot), PAGESIZE);
		void *free_endaddr = (void *)FLOOR_ALIGN(MFREE_END(new_slot), PAGESIZE);
		if (free_minaddr < free_endaddr) {
			void *old_hint, *hkeep, *tkeep;
			size_t hkeep_size, tkeep_size;
			/* Figure out the header and tail which we can't release. */
			hkeep      = (void *)MFREE_MIN(new_slot);
			tkeep      = free_endaddr;
			hkeep_size = (size_t)((byte_t *)free_minaddr - (byte_t *)hkeep);
			HEAP_ASSERTF((byte_t *)MFREE_END(new_slot) >= (byte_t *)tkeep,
			             "new_slot = %p...%p\n"
			             "tkeep    = %p\n",
			             MFREE_MIN(new_slot),
			             MFREE_MAX(new_slot),
			             tkeep);
			tkeep_size = (size_t)((byte_t *)MFREE_END(new_slot) - (byte_t *)tkeep);
			flags &= ~GFP_CALLOC;
			flags |= new_slot->mf_flags;
			/* Ensure that the keep-segments are large enough. */
			if unlikely(hkeep_size && hkeep_size < HEAP_MINSIZE) {
				hkeep_size += PAGESIZE;
				free_minaddr = (byte_t *)free_minaddr + PAGESIZE;
			}
			if unlikely(tkeep_size && tkeep_size < HEAP_MINSIZE) {
				tkeep_size += PAGESIZE;
				tkeep = (byte_t *)tkeep - PAGESIZE;
				free_endaddr = (byte_t *)free_endaddr - PAGESIZE;
			}
			if unlikely(free_minaddr >= free_endaddr)
				goto do_load_new_slot;
			sync_endwrite(&self->h_lock);

			/* Release this slot to the VM. */
			if (hkeep_size) {
				if (flags & GFP_CALLOC)
					memset(hkeep, 0, SIZEOF_MFREE);
#ifdef CONFIG_DEBUG_HEAP
				else {
					mempatl(hkeep, DEBUGHEAP_NO_MANS_LAND, SIZEOF_MFREE);
				}
#endif /* CONFIG_DEBUG_HEAP */
			}
			if (tkeep_size) {
				if (flags & GFP_CALLOC)
					memset(tkeep, 0, SIZEOF_MFREE);
#ifdef CONFIG_DEBUG_HEAP
				else {
					mempatl(tkeep, DEBUGHEAP_NO_MANS_LAND, SIZEOF_MFREE);
				}
#endif /* CONFIG_DEBUG_HEAP */
			}
			PRINTK_SYSTEM_ALLOCATION("[heap] Release kernel heap: [%p+%#Ix head] %p...%p [%p+%#Ix tail]\n",
			                         hkeep, hkeep_size,
			                         (byte_t *)free_minaddr,
			                         (byte_t *)free_endaddr - 1,
			                         tkeep, tkeep_size);

			/* Free unused header and tail data. */
			if (hkeep_size)
				heap_free_raw(self, hkeep, hkeep_size, flags);
			if (tkeep_size)
				heap_free_raw(self, tkeep, tkeep_size, flags);

			/* Release full pages back to the system. */
			vm_unmap_kernel_ram(free_minaddr,
			                    (size_t)((byte_t *)free_endaddr -
			                             (byte_t *)free_minaddr),
			                    !!(flags & GFP_CALLOC));

			/* Reset the heap hint in a way that will keep our heap
			 * around the same area of memory, preventing it from slowly
			 * crawling across the entire address space. */
			if (self->h_hintmode & VM_GETFREE_BELOW) {
				do {
					if ((old_hint = ATOMIC_READ(self->h_hintaddr)) >= free_endaddr)
						break;
				} while (!ATOMIC_CMPXCH_WEAK(self->h_hintaddr, old_hint, free_endaddr));
			} else {
				do {
					if ((old_hint = ATOMIC_READ(self->h_hintaddr)) <= free_minaddr)
						break;
				} while (!ATOMIC_CMPXCH_WEAK(self->h_hintaddr, old_hint, free_minaddr));
			}
			heap_validate_all_after_free();
			return false;
		}
	}
do_load_new_slot:
	mfree_set_checksum(new_slot);
	/* Insert the node into the address and size trees. */
	heap_insert_node_unlocked(self, new_slot);
	heap_validate_all_after_free();
	return true;
}










PUBLIC NOBLOCK void
NOTHROW(KCALL heap_free_untraced)(struct heap *__restrict self,
                                  VIRT void *ptr, size_t num_bytes,
                                  gfp_t flags) {
	TRACE("heap_free_untraced(%p,%p,%Iu,%#x)\n", self, ptr, num_bytes, flags);
	HEAP_ASSERTF(num_bytes >= HEAP_MINSIZE,
	             "Invalid heap_free(): Too few bytes (%Iu < %Iu)",
	             num_bytes, HEAP_MINSIZE);
	HEAP_ASSERTF(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT),
	             "Invalid heap_free(): Unaligned base pointer %p",
	             ptr);
	HEAP_ASSERTF(IS_ALIGNED(num_bytes, HEAP_ALIGNMENT),
	             "Invalid heap_free(): Unaligned free size %Iu (%#Ix)",
	             num_bytes, num_bytes);
	/* Reset debug information. */
#ifdef CONFIG_DEBUG_HEAP
	if (!(flags & GFP_CALLOC))
		reset_heap_data((byte_t *)ptr, DEBUGHEAP_NO_MANS_LAND, num_bytes);
#endif /* CONFIG_DEBUG_HEAP */
	heap_free_raw(self, ptr, num_bytes, flags);
}

PUBLIC WUNUSED NONNULL((1)) size_t
NOTHROW(KCALL heap_truncate_untraced)(struct heap *__restrict self, void *base,
                                      size_t old_size, size_t new_size, gfp_t free_flags) {
	size_t free_bytes;
	TRACE("heap_truncate_untraced(%p,%p,%Iu,%Iu,%#x)\n", self, base, old_size, new_size, flags);
	HEAP_ASSERTF(!old_size || old_size >= HEAP_MINSIZE,
	             "Invalid heap_truncate(): Too few bytes (%Iu < %Iu)",
	             old_size, HEAP_MINSIZE);
	HEAP_ASSERTF(!old_size || IS_ALIGNED((uintptr_t)base, HEAP_ALIGNMENT),
	             "Invalid heap_truncate(): Unaligned base pointer %p",
	             base);
	HEAP_ASSERTF(IS_ALIGNED(old_size, HEAP_ALIGNMENT),
	             "Invalid heap_truncate(): Unaligned old_size size %Iu (%#Ix)",
	             old_size, old_size);
	if unlikely(OVERFLOW_UADD(new_size, (size_t)(HEAP_ALIGNMENT - 1), &new_size))
		goto return_old_size;
	new_size &= ~(HEAP_ALIGNMENT - 1);
	if unlikely(new_size < HEAP_MINSIZE)
		new_size = HEAP_MINSIZE;
	if unlikely(new_size >= old_size)
		goto return_old_size;
	/* Free trailing memory. */
	free_bytes = old_size - new_size;
	if (free_bytes >= HEAP_MINSIZE) {
		heap_free_untraced(self, (void *)((uintptr_t)base + new_size),
		                   free_bytes, free_flags);
		return new_size;
	}
return_old_size:
	return old_size;
}



/* Truncate the given heap, releasing unmapping free memory chunks
 * that are greater than, or equal to `CEIL_ALIGN(threshold, PAGESIZE)'
 * This function is automatically invoked for kernel heaps as part of
 * the clear-cache machinery, though regular should never feel moved
 * to invoke this function manually, as all it really does is slow down
 * future calls to allocating heap functions.
 * @return: * : The total number of bytes released back to the core (a multiple of PAGESIZE) */
PUBLIC size_t
NOTHROW(KCALL heap_trim)(struct heap *__restrict self, size_t threshold) {
	size_t result = 0;
	struct mfree **iter, **end;
	DEFINE_PUBLIC_SYMBOL(kernel_default_heap, &kernel_heaps[GFP_NORMAL], sizeof(struct heap));
	DEFINE_PUBLIC_SYMBOL(kernel_locked_heap, &kernel_heaps[GFP_LOCKED], sizeof(struct heap));
	threshold = CEIL_ALIGN(threshold, PAGESIZE);
	if (!threshold)
		threshold = PAGESIZE;
again:
	/* Search all buckets for free data blocks of at least `threshold' bytes. */
	iter = &self->h_size[HEAP_BUCKET_OF(threshold)];
	end  = COMPILER_ENDOF(self->h_size);
	if (!heap_acquirelock_nx(self, GFP_NORMAL))
		return 0;
	for (; iter != end; ++iter) {
		struct mfree *chain;
		void *free_minaddr, *free_endaddr;
		size_t head_keep, tail_keep;
		void *tail_pointer;
		u8 free_flags;
		/* Search this bucket. */
		chain = *iter;
		while (chain &&
		       (HEAP_ASSERTF(IS_ALIGNED(MFREE_SIZE(chain), HEAP_ALIGNMENT),
		                     "MFREE_SIZE(chain) = %#Ix",
		                     MFREE_SIZE(chain)),
		        MFREE_SIZE(chain) < threshold))
			chain = LLIST_NEXT(chain, mf_lsize);
		if (!chain)
			continue;
		/* Figure out how much we can actually return to the core. */
		free_minaddr = (void *)CEIL_ALIGN(MFREE_BEGIN(chain), PAGESIZE);
		free_endaddr = (void *)FLOOR_ALIGN(MFREE_END(chain), PAGESIZE);
		if unlikely(free_minaddr >= free_endaddr)
			continue; /* Even though the range is large enough, due to alignment it doesn't span a whole page */
		/* Figure out how much memory must be kept in the
		 * head and tail portions of the free data block. */
		head_keep = (size_t)((byte_t *)free_minaddr - (byte_t *)MFREE_BEGIN(chain));
		tail_keep = (size_t)((byte_t *)MFREE_END(chain) - (byte_t *)free_endaddr);
		/* Make sure that data blocks that cannot be freed are still
		 * large enough to remain representable as their own blocks. */
		if (head_keep && head_keep < HEAP_MINSIZE)
			continue;
		if (tail_keep && tail_keep < HEAP_MINSIZE)
			continue;
		/* Remove this chain entry. */
		HEAP_ASSERTE(mfree_tree_remove(&self->h_addr, (uintptr_t)MFREE_BEGIN(chain)) == chain);
		LLIST_REMOVE(chain, mf_lsize);
		sync_endwrite(&self->h_lock);

		tail_pointer = (void *)((uintptr_t)MFREE_END(chain) - tail_keep);
		free_flags   = chain->mf_flags;

		/* Reset memory contained within the header of the data block we just allocated. */
		if (free_flags & GFP_CALLOC)
			memset(chain, 0, SIZEOF_MFREE);
#ifdef CONFIG_DEBUG_HEAP
		else {
			mempatl(chain, DEBUGHEAP_NO_MANS_LAND, SIZEOF_MFREE);
		}
#endif /* CONFIG_DEBUG_HEAP */

		/* Re-release the unused portions of the head and tail data blocks. */
		if (head_keep)
			heap_free_raw(self, chain, head_keep, free_flags);
		if (tail_keep)
			heap_free_raw(self, tail_pointer, tail_keep, free_flags);

		/* Release full pages in-between back to the core. */
		vm_unmap_kernel_ram(free_minaddr,
		                    (size_t)((byte_t *)free_endaddr -
		                             (byte_t *)free_minaddr),
		                    !!(free_flags & GFP_CALLOC));

		/* Keep track of how much has already been released to the core. */
		result += (size_t)((byte_t *)free_endaddr - (byte_t *)free_minaddr);
		goto again;
	}
	sync_endwrite(&self->h_lock);
	return result;
}


/* Free a low/high-memory overallocation of `num_free_bytes' at `overallocation_base'.
 * This function deals with debug-initialization in the
 * event that the overallocated base location hasn't been
 * allocated yet, in a way that prevent the associated
 * pages from being allocated during `heap_free_raw()' in
 * a way that would produce invalid (use-after-free) memory. */
#ifdef CONFIG_DEBUG_HEAP
#define IS_FRESH_MEMORY(p) (*(u32 *)(p) == 0 || *(u32 *)(p) == DEBUGHEAP_FRESH_MEMORY)

PRIVATE void
NOTHROW(KCALL heap_free_overallocation)(struct heap *__restrict self,
                                        void *overallocation_base,
                                        size_t num_free_bytes,
                                        gfp_t flags) {
	HEAP_ASSERT(IS_ALIGNED((uintptr_t)overallocation_base, HEAP_ALIGNMENT));
	HEAP_ASSERT(IS_ALIGNED(num_free_bytes, HEAP_ALIGNMENT));
	/* When the CALLOC flag is set, then memory will initialize itself to ZERO */
	if (!(flags & GFP_CALLOC)) {
#if 1
		/* If the overallocation_base...+=SIZEOF_MFREE-1 contains a page boundary,
		 * where the higher page is entirely contained within the overallocation,
		 * then we must MEMPAT(DEBUGHEAP_NO_MANS_LAND) that high page, as it will
		 * be initialized by `heap_free_raw()'. */
		uintptr_t high_page_addr;
		high_page_addr = ((uintptr_t)overallocation_base + SIZEOF_MFREE - 1) & ~PAGEMASK;
		if ((((uintptr_t)overallocation_base) & ~PAGEMASK) != high_page_addr) {
			/* Page-boundary within the mfree structure. */
			if ((uintptr_t)overallocation_base + num_free_bytes >=
			    (uintptr_t)high_page_addr + PAGESIZE) {
				/* The high-page is entirely contained in the overallocation
				 * NOTE: Technically, we don't need to initialize the first
				 *      `((uintptr_t)overallocation_base + SIZEOF_MFREE - 1) & PAGEMASK'
				 *       bytes of the high page (those will be used by `heap_free_raw'),
				 *       but calculating that amount is more complicated at this point,
				 *       and so insignificant in the end that it's simpler to always just
				 *       initialize the whole page. */
				if (IS_FRESH_MEMORY(high_page_addr)) { /* Check for fresh memory */
#if 0
					printk(KERN_DEBUG "Reset no mans land #1 for page %p...%p\n",
					       high_page_addr, high_page_addr + PAGESIZE - 1);
#endif
					mempatl((void *)high_page_addr, DEBUGHEAP_NO_MANS_LAND, PAGESIZE);
				}
			}
		} else {
			/* -> The mfree structure of the overallocation is contained within a single page.
			 *    In this case we must check if that same page is also apart of the associated
			 *    user-allocation (which exists at `<BASE_POINTER>...overallocation_base-1')
			 *    This can easily be detected by `overallocation_base' not being page-aligned.
			 *    If this is the case, then we must MEMPAT overallocation_base...END_OF_SAME_PAGE,
			 *    though only if the entirety of that area is apart of the overallocation.
			 */
			if (((uintptr_t)overallocation_base & PAGEMASK) != 0) {
				uintptr_t end_of_page;
				end_of_page = ((uintptr_t)overallocation_base & ~PAGEMASK) + PAGESIZE;
				if ((uintptr_t)overallocation_base + num_free_bytes >= end_of_page) {
					/* Must MEMPAT all memory within the original page */
					if (IS_FRESH_MEMORY(overallocation_base)) {
#if 0
						printk(KERN_DEBUG "Reset no mans land #2 for page %p...%p\n",
						       overallocation_base, end_of_page - 1);
#endif
						mempatl((void *)overallocation_base, DEBUGHEAP_NO_MANS_LAND,
						        end_of_page - (uintptr_t)overallocation_base);
					}
				}
			} else {
				/* When the overallocation starts at a page boundary, and the
				 * total number of freed bytes is such that the entire first
				 * page is contained within the overallocation, we must initialize
				 * that first page in its entirety
				 * (If the overallocation is smaller, then some other mfree
				 *  must exist that has already initialized that page) */
				if (num_free_bytes >= PAGESIZE) {
					if (IS_FRESH_MEMORY(overallocation_base)) {
#if 0
						printk(KERN_DEBUG "Reset no mans land #3 for page %p...%p\n",
						       overallocation_base, (byte_t *)overallocation_base + PAGESIZE - 1);
#endif
						mempatl((void *)overallocation_base,
						        DEBUGHEAP_NO_MANS_LAND,
						        PAGESIZE);
					}
				}
			}
		}
#else
		mempatl(overallocation_base, DEBUGHEAP_NO_MANS_LAND, num_free_bytes);
#endif
	}
	heap_free_raw(self, overallocation_base,
	              num_free_bytes, flags);
}

PRIVATE void
NOTHROW(KCALL heap_free_underallocation)(struct heap *__restrict self,
                                         void *underallocation_base,
                                         size_t num_free_bytes,
                                         gfp_t flags) {
	HEAP_ASSERT(IS_ALIGNED((uintptr_t)underallocation_base, HEAP_ALIGNMENT));
	HEAP_ASSERT(IS_ALIGNED(num_free_bytes, HEAP_ALIGNMENT));
	/* When the CALLOC flag is set, then memory will initialize itself to ZERO */
	if (!(flags & GFP_CALLOC)) {
#if 1
		uintptr_t underallocation_end;
		underallocation_end = (uintptr_t)underallocation_base + num_free_bytes;
		/* Check if the under allocation starts at a new page.
		 * If it doesn't, then we can assume that some other mfree
		 * exists for the area below, meaning that the first page
		 * will have already been initialized. */
		if (((uintptr_t)underallocation_base & PAGEMASK) == 0) {
			/* Must initialize data at underallocation_base...MIN(END_OF_FREE_RANGE,END_OF_PAGE(underallocation_base)) */
			HEAP_ASSERT(num_free_bytes >= 4);
			if (IS_FRESH_MEMORY(underallocation_base)) {
				size_t init_size = num_free_bytes;
				if (init_size > PAGESIZE)
					init_size = PAGESIZE;
				mempatl(underallocation_base, DEBUGHEAP_NO_MANS_LAND, init_size);
			}
		} else {
			/* If the underallocation doesn't start at a page, check if
			 * its mfree structure would cross a page boundary. If it does,
			 * and the higher of the 2 pages is entirely contained within
			 * the underallocation, then we must initialize the page. */
			uintptr_t page_base;
			page_base = ((uintptr_t)underallocation_base + SIZEOF_MFREE - 1) & ~PAGEMASK;
			if ((((uintptr_t)underallocation_base) & ~PAGEMASK) != page_base) {
				/* Descriptor crosses a page boundary. */
				size_t num_reset_bytes;
				HEAP_ASSERT(underallocation_end > page_base);
				num_reset_bytes = underallocation_end - page_base;
				if (num_reset_bytes > PAGESIZE) {
					if (IS_FRESH_MEMORY(page_base))
						mempatl((void *)page_base, DEBUGHEAP_NO_MANS_LAND, PAGESIZE);
				} else {
					if (num_reset_bytes < 4 || IS_FRESH_MEMORY(page_base))
						mempatl((void *)page_base, DEBUGHEAP_NO_MANS_LAND, num_reset_bytes);
				}
			}
		}
		/* Must clear all data before the start of `underallocation_end', and
		 * within the same page, if `underallocation_end' isn't located at the
		 * start of a page. */
		if ((underallocation_end & PAGEMASK) != 0) {
			STATIC_ASSERT(SIZEOF_MFREE >= 7);
			if (IS_FRESH_MEMORY((underallocation_end & ~(4 - 1)) - 4)) {
				uintptr_t clear_size;
				clear_size = underallocation_end & PAGEMASK;
				if (clear_size > num_free_bytes)
					clear_size = num_free_bytes;
				mempatl((void *)(underallocation_end - clear_size),
				        DEBUGHEAP_NO_MANS_LAND, clear_size);
			}
		}
#else
		mempatl(underallocation_base, DEBUGHEAP_NO_MANS_LAND, num_free_bytes);
#endif
	}
	heap_free_raw(self, underallocation_base,
	              num_free_bytes, flags);
}

#else /* CONFIG_DEBUG_HEAP */

/* Without debug initialization, this isn't a problem! */
#define heap_free_overallocation(self, overallocation_base, num_free_bytes, flags) \
	heap_free_raw(self, overallocation_base, num_free_bytes, flags)
#define heap_free_underallocation(self, underallocation_base, num_free_bytes, flags) \
	heap_free_raw(self, underallocation_base, num_free_bytes, flags)

#endif /* !CONFIG_DEBUG_HEAP */


DECL_END

#ifndef __INTELLISENSE__
#define HEAP_NX 1
#include "heap-impl.c.inl"
/**/
#include "heap-impl.c.inl"
#endif /* !__INTELLISENSE__ */

DECL_BEGIN

PUBLIC NOBLOCK void
NOTHROW(KCALL vpage_free_untraced)(VIRT /*page-aligned*/ void *base,
                                   size_t num_pages) {
	assertf(IS_ALIGNED((uintptr_t)base, PAGESIZE), "base = %p", base);
	vm_unmap_kernel_ram(base, num_pages * PAGESIZE, false);
}

PUBLIC NOBLOCK void
NOTHROW(KCALL vpage_ffree_untraced)(VIRT /*page-aligned*/ void *base,
                                    size_t num_pages, gfp_t flags) {
	assertf(IS_ALIGNED((uintptr_t)base, PAGESIZE), "base = %p", base);
	vm_unmap_kernel_ram(base, num_pages * PAGESIZE, !!(flags & GFP_CALLOC));
}



/* Weakly alias the TRACED-versions of heap functions.
 * When DEBUG_MALLOC is enabled, `debug-malloc.c' will override these. */
DEFINE_PUBLIC_WEAK_ALIAS(heap_alloc, heap_alloc_untraced);
DEFINE_PUBLIC_WEAK_ALIAS(heap_align, heap_align_untraced);
DEFINE_PUBLIC_WEAK_ALIAS(heap_allat, heap_allat_untraced);
DEFINE_PUBLIC_WEAK_ALIAS(heap_alloc_nx, heap_alloc_untraced_nx);
DEFINE_PUBLIC_WEAK_ALIAS(heap_align_nx, heap_align_untraced_nx);
DEFINE_PUBLIC_WEAK_ALIAS(heap_allat_nx, heap_allat_untraced_nx);
DEFINE_PUBLIC_WEAK_ALIAS(heap_realloc_nx, heap_realloc_untraced_nx);
DEFINE_PUBLIC_WEAK_ALIAS(heap_realign_nx, heap_realign_untraced_nx);
DEFINE_PUBLIC_WEAK_ALIAS(heap_free, heap_free_untraced);
DEFINE_PUBLIC_WEAK_ALIAS(heap_truncate, heap_truncate_untraced);
DEFINE_PUBLIC_WEAK_ALIAS(heap_realloc, heap_realloc_untraced);
DEFINE_PUBLIC_WEAK_ALIAS(heap_realign, heap_realign_untraced);
DEFINE_PUBLIC_WEAK_ALIAS(vpage_alloc, vpage_alloc_untraced);
DEFINE_PUBLIC_WEAK_ALIAS(vpage_alloc_nx, vpage_alloc_untraced_nx);
DEFINE_PUBLIC_WEAK_ALIAS(vpage_realloc, vpage_realloc_untraced);
DEFINE_PUBLIC_WEAK_ALIAS(vpage_realloc_nx, vpage_realloc_untraced_nx);
DEFINE_PUBLIC_WEAK_ALIAS(vpage_free, vpage_free_untraced);
DEFINE_PUBLIC_WEAK_ALIAS(vpage_ffree, vpage_ffree_untraced);

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_HEAP_C */
