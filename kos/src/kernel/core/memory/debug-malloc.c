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
#ifndef GUARD_KERNEL_SRC_MEMORY_DEBUG_MALLOC_C
#define GUARD_KERNEL_SRC_MEMORY_DEBUG_MALLOC_C 1
#define __OMIT_KMALLOC_CONSTANT_P_WRAPPERS 1
#define __OMIT_HEAP_TRACED_CONSTANT_P_WRAPPERS 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/heap.h>
#include <kernel/malloc-defs.h>
#include <kernel/malloc.h>
#include <kernel/slab.h>

/* TODO: With `#undef CONFIG_DEBUG_MALLOC': Running `deemon' (no arguments)
 *       causes an assertion failure in the non-debug realloc() function. */
#if 0 /* Quick toggle to disable debug_malloc (and use the weak definitions from `malloc.c'). */
#undef CONFIG_DEBUG_MALLOC
#endif

#ifdef CONFIG_DEBUG_MALLOC
#include <debugger/config.h>
#include <debugger/hook.h>
#include <kernel/addr2line.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/syslog.h>
#include <kernel/types.h>
#include <kernel/vm.h>
#include <sched/cpu.h>
#include <sched/pid.h>
#include <sched/task.h>
#ifndef CONFIG_NO_SMP
#include <sched/signal.h>
#endif /* !CONFIG_NO_SMP */

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <assert.h>
#include <format-printer.h>
#include <stdint.h>
#include <string.h>

#include <libinstrlen/instrlen.h>
#include <libunwind/unwind.h>

#include "corebase.h"

#if 0
#define PRINT_LEAKS_SEARCH_PHASE(...) printk(KERN_INFO __VA_ARGS__)
#else
#define PRINT_LEAKS_SEARCH_PHASE(...) (void)0
#endif


DECL_BEGIN

INTERN void /* Must be INTERN, because this function gets overwritten
             * when `nomall' is passed on the commandline */
NOTHROW(KCALL debug_malloc_generate_traceback)(void **__restrict buffer, size_t buflen,
                                               struct lcpustate *__restrict state) {
#if 1
	TRY {
		struct lcpustate oldstate;
		oldstate = *state;
		while (unwind((void *)(lcpustate_getpc(&oldstate) - 1),
		              &unwind_getreg_lcpustate, &oldstate,
		              &unwind_setreg_lcpustate, state) == UNWIND_SUCCESS) {
			*buffer++ = (void *)lcpustate_getpc(state);
			if (!--buflen)
				return;
			oldstate = *state;
		}
	} EXCEPT {
		if (!was_thrown(E_SEGFAULT) && !was_thrown(E_WOULDBLOCK))
			RETHROW(); /* This causes panic because we're NOTHROW */
	}
#endif
	/* Make sure that when there are unused entries, the chain is NULL-terminated */
	if (buflen)
		*buffer = NULL;
}

DECL_END

#define LOAD_CALLER_CONTEXT      \
	struct lcpustate context[1]; \
	lcpustate_current(context);
#define FILL_NODE_TRACE_WITH_CALLER_TRACEBACK(node) \
	debug_malloc_generate_traceback((node)->m_trace, MALLNODE_TRACESZ(node), (struct lcpustate *)context)
#define PANIC_HERE(...) kernel_panic(__VA_ARGS__)
#define PANIC_CALL(...) kernel_panic(__VA_ARGS__) /* XXX: Panic at __builtin_return_address() */

#define PANIC_UNTRACE_NONUSER_NODE_WITH_CALLER_TRACEBACK(node, pointer)                   \
	/* TODO: Also print the node's traceback. */                                          \
	PANIC_CALL("Attempted to untrace non-user-defined mall node %p...%p (pointer: %p)\n", \
	           (node)->m_tree.a_vmin, (node)->m_tree.a_vmax, pointer)
#define PANIC_UNTRACE_NONUSER_NODE(node, pointer)                                         \
	/* TODO: Also print the node's traceback. */                                          \
	PANIC_HERE("Attempted to untrace non-user-defined mall node %p...%p (pointer: %p)\n", \
	           (node)->m_tree.a_vmin, (node)->m_tree.a_vmax, pointer)
#define PANIC_SIZEOF_USER_NODE_WITH_CALLER_TRACEBACK(node, pointer)                              \
	/* TODO: Also print the node's traceback. */                                                 \
	PANIC_HERE("Attempted to kmalloc_usable_size() a user-defined node %p...%p (pointer: %p)\n", \
	           (node)->m_tree.a_vmin, (node)->m_tree.a_vmax, pointer)
#define PANIC_SIZEOF_NOT_NODE_BASE_ADDRESS_WITH_CALLER_TRACEBACK(node, pointer) \
	/* TODO: Also print the node's traceback. */                                                                 \
	PANIC_CALL("The pointer %p passed to kmalloc_usable_size() isn't the malloc base address of node %p...%p\n", \
	           pointer, (node)->m_tree.a_vmin, (node)->m_tree.a_vmax)
#define PANIC_SIZEOF_NODES_MISSMATCH(node, pointer, expected, found) \
	/* TODO: Also print the node's traceback. */                                                         \
	PANIC_CALL("Corrupted size field of malloc-pointer %p (node %p...%p) (is %Iu, but should be %Iu)\n", \
	           pointer, (node)->m_tree.a_vmin, (node)->m_tree.a_vmax, found, expected)
#define PANIC_INVALID_MALL_POINTER_WITH_CALLER_TRACEBACK(pointer) \
	PANIC_CALL("Invalid mall pointer: %p\n", pointer)
#define PANIC_INVALID_MALL_POINTER(pointer) \
	PANIC_HERE("Invalid mall pointer: %p\n", pointer)
#define PANIC_FREE_USER_NODE(node, pointer)                                        \
	/* TODO: Also print the node's traceback. */                                   \
	PANIC_HERE("Attempted to kfree() a user-defined node %p...%p (pointer: %p)\n", \
	           (node)->m_tree.a_vmin, (node)->m_tree.a_vmax, pointer)
#define PANIC_REALLOC_USER_NODE_WITH_CALLER_TRACEBACK(node, pointer)                  \
	/* TODO: Also print the node's traceback. */                                      \
	PANIC_CALL("Attempted to krealloc() a user-defined node %p...%p (pointer: %p)\n", \
	           (node)->m_tree.a_vmin, (node)->m_tree.a_vmax, pointer)
#define PANIC_FREE_NOT_NODE_BASE_ADDRESS(node, pointer)                                            \
	/* TODO: Also print the node's traceback. */                                                   \
	PANIC_CALL("The pointer %p passed to kfree() isn't the malloc base address of node %p...%p\n", \
	           pointer, (node)->m_tree.a_vmin + (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE), \
	           (node)->m_tree.a_vmax - (CONFIG_MALL_TAIL_SIZE))
#define PANIC_REALLOC_NOT_NODE_BASE_ADDRESS_WITH_CALLER_TRACEBACK(node, pointer)                      \
	/* TODO: Also print the node's traceback. */                                                      \
	PANIC_CALL("The pointer %p passed to krealloc() isn't the malloc base address of node %p...%p\n", \
	           pointer, (node)->m_tree.a_vmin + (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE),    \
	           (node)->m_tree.a_vmax - (CONFIG_MALL_TAIL_SIZE))





DECL_BEGIN

/* MALL -- Debug MALLOC API.
 * This one differs from what can be seen in the old KOS significantly.
 * The most important change is that it uses a GC-based memory leak detector,
 * as well as doesn't store file-and-line debug information any more.
 * The traceback stored at the end of the pointer is kept however.
 * Another big change is that MALL information is no longer stored
 * alongside mall pointers themself, but rather accessed through an
 * address TREE with nodes allocated using an independent heap.
 * This way, debug information is even less likely to become corrupt
 * from invalid use of user-pointers.
 * Secondly, free-after-use debug checks are implemented as part of the
 * kernel heap API, rather than only applying to debug-allocated pointers.
 * Thirdly, memory pre-initializations are also done by the heap API,
 * which also does strict enforcing of the state of said data, filling
 * in newly allocated memory with `DEBUGHEAP_FRESH_MEMORY', and clearing
 * all data using `DEBUGHEAP_NO_MANS_LAND' during a call to `free()'. */

#ifndef CONFIG_MALL_HEAD_PATTERN
#define CONFIG_MALL_HEAD_PATTERN   0x33333333
#endif /* !CONFIG_MALL_HEAD_PATTERN */
#ifndef CONFIG_MALL_TAIL_PATTERN
#define CONFIG_MALL_TAIL_PATTERN   0x77777777
#endif /* !CONFIG_MALL_TAIL_PATTERN */
#ifndef CONFIG_MALL_PREFIX_SIZE
#define CONFIG_MALL_PREFIX_SIZE   (__SIZEOF_SIZE_T__)
#endif /* !CONFIG_MALL_PREFIX_SIZE */
#ifndef CONFIG_MALL_HEAD_SIZE
#define CONFIG_MALL_HEAD_SIZE     (HEAP_ALIGNMENT - __SIZEOF_SIZE_T__)
#endif /* !CONFIG_MALL_HEAD_SIZE */
#ifndef CONFIG_MALL_TAIL_SIZE
#define CONFIG_MALL_TAIL_SIZE      HEAP_ALIGNMENT
#endif /* !CONFIG_MALL_TAIL_SIZE */

/* The minimum amount of traceback entries that MALL
 * should attempt to include in debug information of
 * allocated pointers. */
#ifndef CONFIG_MALL_TRACEMIN
#define CONFIG_MALL_TRACEMIN 4
#endif /* !CONFIG_MALL_TRACEMIN */

#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x

#define MALL_HEAP_FLAGS  (GFP_NORMAL | GFP_LOCKED | GFP_PREFLT)

/* Debug-heap used for allocating `struct mallnode' objects. */
INTERN struct heap mall_heap =
HEAP_INIT(PAGESIZE * 4,
          PAGESIZE * 16,
          HINT_GETADDR(KERNEL_VMHINT_DHEAP),
          HINT_GETMODE(KERNEL_VMHINT_DHEAP));
DEFINE_VALIDATABLE_HEAP(mall_heap);
DEFINE_DBG_BZERO_OBJECT(mall_heap.h_lock);



typedef uintptr_half_t mall_ver_t;

struct mallnode {
	ATREE_NODE(struct mallnode,uintptr_t) m_tree;     /* Tree of mall nodes. */
	size_t                                m_size;     /* [const] Allocated heap-size of this node. */

	mall_ver_t                            m_reach;    /* Last leak-check iteration when this node was reached. */
	mall_ver_t                            m_visit;    /* Last leak-check iteration when this node was visited. */
#define MALLNODE_FNORMAL                  0x0000      /* Normal MALLNODE flags. */
#define MALLNODE_FNOLEAK                  GFP_NOLEAK  /* This node not being reachable isn't a leak. */
#define MALLNODE_FNOWALK                  GFP_NOWALK  /* This node should not be scanned for GC-pointers. */
#define MALLNODE_FUSERNODE                0x8000      /* This node describes a custom tracing point. */
	u16                                   m_flags;    /* Set of `MALLNODE_F*' */
	u16                                   m_userver;  /* Is-valid-user-node version number.
	                                                   * When this value is lower than `mall_valid_user_node_version_number',
	                                                   * the node should not be considered as being valid for the purposes
	                                                   * of being re-traced, or untraced. However, it should still be considered
	                                                   * valid for the purposes of GC searches, as well as other passive
	                                                   * interactions such as reading its size.
	                                                   * Note that this only applies to nodes with the `MALLNODE_FUSERNODE' flag set! */
	upid_t                                m_tracetid; /* Traceback thread id (in the root namespace). */
	COMPILER_FLEXIBLE_ARRAY(void *, m_trace);         /* [1..1][0..MALLNODE_TRACESZ(self)]
	                                                   * Traceback of where the pointer was originally allocated. */
};
#define MALLNODE_MIN(x)        ((x)->m_tree.a_vmin)
#define MALLNODE_MAX(x)        ((x)->m_tree.a_vmax)
#define MALLNODE_BEGIN(x)      ((x)->m_tree.a_vmin)
#define MALLNODE_END(x)        ((x)->m_tree.a_vmax + 1)
#define MALLNODE_SIZE(x)      (((x)->m_tree.a_vmax - (x)->m_tree.a_vmin) + 1)
#define MALLNODE_TRACESZ(x)   (((x)->m_size - offsetof(struct mallnode,m_trace)) / sizeof(void *))
#define MALLNODE_ISVALID(x)  (!((x)->m_flags & MALLNODE_FUSERNODE) || (x)->m_userver <= mall_valid_user_node_version_number)


/* The global descriptor table of known MALL nodes. */

/* Lock for accessing `mall_lock'. */
PRIVATE ATTR_MALL_UNTRACKED struct atomic_rwlock mall_lock = ATOMIC_RWLOCK_INIT;
DEFINE_DBG_BZERO_OBJECT(mall_lock);


/* [0..1] Tree of MALL Nodes allocated within this heap. */
PRIVATE ATTR_MALL_UNTRACKED VIRT ATREE_HEAD(struct mallnode) mall_tree;

STATIC_ASSERT(CONFIG_MALL_PREFIX_SIZE >= __SIZEOF_SIZE_T__);

DECL_END

/* Define the ABI for the address tree used by mall nodes. */
#define ATREE(x)      mallnode_tree_##x
#define ATREE_CALL    KCALL
#define ATREE_NOTHROW NOTHROW
#define Tkey          VIRT uintptr_t
#define T             struct mallnode
#define N_NODEPATH    m_tree
#include <hybrid/sequence/atree-abi.h>

DECL_BEGIN

#define CONFIG_MAX_PENDING_UNTRACE_COUNT 128
struct pending_untrace {
	void    *pu_base; /* Base address of the pending untrace. */
	size_t   pu_size; /* Size of the pending untrace (or 0 if merely containing node should be untraced) */
};

PRIVATE WEAK ATTR_MALL_UNTRACKED u16 mall_valid_user_node_version_number = 0;

PRIVATE WEAK ATTR_MALL_UNTRACKED size_t mall_pending_untrace_count = 0; /* Amount of used untrace slots. */
PRIVATE WEAK ATTR_MALL_UNTRACKED struct pending_untrace mall_pending_untrace[CONFIG_MAX_PENDING_UNTRACE_COUNT];
PRIVATE WEAK ATTR_MALL_UNTRACKED uintptr_t mall_pending_inuse[(CONFIG_MAX_PENDING_UNTRACE_COUNT + (BITSOF(uintptr_t) - 1)) / BITSOF(uintptr_t)]; /* Bitset of untrace slots currently in use. */
PRIVATE WEAK ATTR_MALL_UNTRACKED uintptr_t mall_pending_isval[(CONFIG_MAX_PENDING_UNTRACE_COUNT + (BITSOF(uintptr_t) - 1)) / BITSOF(uintptr_t)]; /* Bitset of valid untrace slots. */


PRIVATE ATTR_COLD NOBLOCK void
NOTHROW(KCALL mall_pending_untrace_overflow)(void *__restrict ptr, size_t num_bytes) {
	/* Indicate that all currently defined user-nodes are no longer to be trusted,
	 * causing any attempts to define new tracing nodes for any of them to succeed
	 * without question, acting like any currently existing user-nodes are part of
	 * a flux state between traced and untraced. */
	if (num_bytes) {
		printk(KERN_ERR "Invalidating all MALL user-nodes after failing to untrace %p...%p\n",
		       ptr, (uintptr_t)ptr + num_bytes - 1);
	} else {
		printk(KERN_ERR "Invalidating all MALL user-nodes after failing to untrace %p\n", ptr);
	}
	if unlikely(ATOMIC_FETCHINC(mall_valid_user_node_version_number) == (u16)-1)
		kernel_panic("Too many failed MALL untrace pending attempts - Can no longer keep up\n");
}


#define mall_add_pending_untrace(ptr) \
	mall_add_pending_untrace_n(ptr, 0)
PRIVATE NOBLOCK void
NOTHROW(KCALL mall_add_pending_untrace_n)(void *ptr, size_t num_bytes) {
	/* Keep track of pending untrace operations
	 * through some statically allocated vector. */
	unsigned int i, j, attempt;
	uintptr_t word, alloc_mask;
again:
	attempt = 0;
	while (attempt++ < 8) {
		for (i = 0; i < COMPILER_LENOF(mall_pending_inuse); ++i) {
			word = ATOMIC_READ(mall_pending_inuse[i]);
			if (word == (uintptr_t)-1)
				continue;
			alloc_mask = 1, j = 0;
			while (word & alloc_mask)
				alloc_mask <<= 1, ++j;
			assert(alloc_mask);
			/* Atomically allocate the entry we decided on acquiring. */
			if (!ATOMIC_CMPXCH_WEAK(mall_pending_inuse[i], word, word | alloc_mask))
				goto again;
			j += i * BITSOF(uintptr_t);
			/* Fill in our untrace entry. */
			mall_pending_untrace[j].pu_base = ptr;
			mall_pending_untrace[j].pu_size = num_bytes;
			/* Mark our entry as being valid. */
			ATOMIC_FETCHOR(mall_pending_isval[i], alloc_mask);
			/* Keep track of the number of pending untrace operations. */
			ATOMIC_FETCHINC(mall_pending_untrace_count);
			return;
		}
	}
	mall_pending_untrace_overflow(ptr, num_bytes);
}



struct pending_malloc_free {
	size_t                      mf_usersize; /* The user-visible size field. */
	struct pending_malloc_free *mf_next;     /* Next-pointer */
	gfp_t                       mf_gfp;      /* free-flags. */
};


/* When non-zero, there are some non-user-defined nodes with inconsistent
 * header values. - To deal with such nodes, serve pending mall commands.
 * NOTE: This field actually represents the number of elements apart of
 *       the `mall_pending_mallocfree' linked list (including elements
 *       that are still being added)
 */
PRIVATE WEAK ATTR_MALL_UNTRACKED size_t mall_inconsistent_head_exist = 0;
PRIVATE WEAK ATTR_MALL_UNTRACKED struct pending_malloc_free *mall_pending_mallocfree = NULL;

#define MALL_HAS_PENDING_COMMANDS()                  \
	(ATOMIC_READ(mall_pending_mallocfree) != NULL || \
	 ATOMIC_READ(mall_pending_untrace_count) != 0)


PRIVATE NOBLOCK void NOTHROW(KCALL mall_do_free)(void *__restrict ptr, gfp_t flags, bool should_unlock);
PRIVATE NOBLOCK void NOTHROW(KCALL mallnode_free)(struct mallnode *__restrict self);
PRIVATE ATTR_MALLOC NOBLOCK_IF(flags & GFP_ATOMIC) struct mallnode *NOTHROW(KCALL mallnode_alloc_nx)(gfp_t gfp);
PRIVATE NOBLOCK bool NOTHROW(KCALL mall_serve_pending_commands)(gfp_t flags);


/* Acquire a write-lock to the MALL subsystem, either
 * atomically, or in a manner that is matching the
 * given `flags'. */
LOCAL NOBLOCK bool
NOTHROW(KCALL mall_acquire_atomic)(void) {
again:
	if (!sync_trywrite(&mall_lock))
		return false;
	if (!mall_serve_pending_commands(GFP_ATOMIC))
		goto again;
	return true;
}

LOCAL NOBLOCK_IF(flags & GFP_ATOMIC) bool
NOTHROW(KCALL mall_acquire_nx)(gfp_t flags) {
again:
	if (!sync_trywrite(&mall_lock)) {
		if (flags & GFP_ATOMIC)
			return false;
		if (!sync_write_nx(&mall_lock))
			return false;
	}
	if (!mall_serve_pending_commands(flags))
		goto again;
	return true;
}

LOCAL NOBLOCK_IF(flags & GFP_ATOMIC)
bool KCALL mall_acquire(gfp_t flags) {
again:
	if (!sync_trywrite(&mall_lock)) {
		if (flags & GFP_ATOMIC)
			return false;
		sync_write(&mall_lock);
	}
	if (!mall_serve_pending_commands(flags))
		goto again;
	return true;
}

LOCAL NOBLOCK void
NOTHROW(KCALL mall_release)(void) {
again:
	if (mall_serve_pending_commands(GFP_ATOMIC))
		sync_endwrite(&mall_lock);
	if (MALL_HAS_PENDING_COMMANDS()) {
		if (sync_trywrite(&mall_lock))
			goto again;
	}
}


/* Upon entry, `mall_lock' must be held.
 * @return: true:  `mall_lock' remains locked.
 * @return: false: `mall_lock' was unlocked. */
PRIVATE NOBLOCK_IF(flags & GFP_ATOMIC) bool
NOTHROW(KCALL mall_untrace_n_impl)(void *ptr, size_t num_bytes, gfp_t flags) {
	uintptr_t end_addr = (uintptr_t)ptr + num_bytes;
	while (num_bytes) {
		struct mallnode *node, *hinode;
		size_t node_size;
		node = mallnode_tree_remove(&mall_tree, (uintptr_t)ptr);
generic_handle_node:
		if unlikely(!node) {
			if (mall_valid_user_node_version_number)
				return true; /* Because of the possibility of a failed split in `mall_insert_tree()' */
			sync_endwrite(&mall_lock);
			PANIC_INVALID_MALL_POINTER_WITH_CALLER_TRACEBACK(ptr);
		}
		if unlikely(!(node->m_flags & MALLNODE_FUSERNODE)) {
			sync_endwrite(&mall_lock);
			PANIC_UNTRACE_NONUSER_NODE_WITH_CALLER_TRACEBACK(node, ptr);
		}
		node_size = (node->m_tree.a_vmax - node->m_tree.a_vmin) + 1;
		if (node->m_tree.a_vmin == (uintptr_t)ptr) {
			if (node_size <= num_bytes) {
				/* Fully get rid of this node. */
				mallnode_free(node);
				/* Continue untracing afterwards. */
				num_bytes -= node_size;
				ptr = (void *)((uintptr_t)ptr + node_size);
				continue;
			}
			/* Only a leading part of the node is being untraced. */
			node->m_tree.a_vmin += num_bytes;
			/* Re-insert the node */
			mallnode_tree_insert(&mall_tree, node);
			return true;
		}
		if (end_addr > node->m_tree.a_vmax) {
			/* Only a trailing part of the node is being untraced. */
			num_bytes = (size_t)((end_addr - 1) - node->m_tree.a_vmax);
			node->m_tree.a_vmax = (uintptr_t)ptr - 1;
			assert(node->m_tree.a_vmax >= node->m_tree.a_vmin);
			ptr = (void *)(end_addr - num_bytes);
			/* Re-insert the node */
			mallnode_tree_insert(&mall_tree, node);
			continue;
		}
		/* A sub-segment of the node is being unmapped.
		 * -> For this, we need to allocate a second node! */
		assert((uintptr_t)ptr > node->m_tree.a_vmin);
		assert((end_addr - 1) < node->m_tree.a_vmax);

		hinode = mallnode_alloc_nx(GFP_ATOMIC | flags);
		if unlikely(!hinode) {
			/* Restore the original node and unlock `mall_lock', then re-
			 * attempt allocating the secondary node without `GFP_ATOMIC'. */
			mallnode_tree_insert(&mall_tree, node);
			mall_release();
			hinode = mallnode_alloc_nx(flags);
			if unlikely(!hinode) {
				/* Add the untrace as a pending operation. */
				mall_add_pending_untrace_n(ptr, num_bytes);
				return false;
			}
			/* Re-acquire a lock to the MALL sub-system. */
			if (!mall_acquire_nx(flags)) {
				mallnode_free(hinode);
				mall_add_pending_untrace_n(ptr, num_bytes);
				return false;
			}
			/* Remove the original node once again. */
			node = mallnode_tree_remove(&mall_tree, (uintptr_t)ptr);
			if (!node || !(node->m_flags & MALLNODE_FUSERNODE) ||
			    !((uintptr_t)ptr > node->m_tree.a_vmin) ||
			    !((end_addr - 1) < node->m_tree.a_vmax)) {
				/* The node has changed in the mean time (free our secondary node, and re-try) */
				mallnode_free(hinode);
				goto generic_handle_node;
			}
		}
		/* All right! - We've got a secondary node, so
		 * now we can use it to split the old one in 2 */
		hinode->m_tree.a_vmax = node->m_tree.a_vmax;
		hinode->m_tree.a_vmin = end_addr;
		node->m_tree.a_vmax   = (uintptr_t)ptr - 1;
		hinode->m_flags       = node->m_flags;
		memcpy(hinode->m_trace, node->m_trace,
		       MIN(MALLNODE_TRACESZ(hinode),
		           MALLNODE_TRACESZ(node)),
		       sizeof(void *));
		/* Now just insert both nodes into the MALL tree, and we're done! */
		mallnode_tree_insert(&mall_tree, node);
		mallnode_tree_insert(&mall_tree, hinode);
		return true;
	}
	return true;
}


PRIVATE NOBLOCK void
NOTHROW(KCALL mall_restore_invalid_version_number)(struct mallnode *__restrict node,
                                                    u16 old_max_version) {
again:
	if ((node->m_flags & MALLNODE_FUSERNODE) &&
	    (node->m_userver < old_max_version))
		node->m_userver = 0;
	if (node->m_tree.a_min) {
		if (node->m_tree.a_max)
			mall_restore_invalid_version_number(node->m_tree.a_max, old_max_version);
		node = node->m_tree.a_min;
		goto again;
	} else if (node->m_tree.a_max) {
		node = node->m_tree.a_max;
		goto again;
	}
}

/* Upon entry, `mall_lock' must be held.
 * @return: true:  `mall_lock' remains locked.
 * @return: false: `mall_lock' was unlocked. */
PRIVATE NOBLOCK bool
NOTHROW(KCALL mall_serve_pending_commands)(gfp_t flags) {
	{
		struct pending_malloc_free *pend, *next;
		pend = ATOMIC_XCH(mall_pending_mallocfree, NULL);
		while unlikely(pend) {
			gfp_t flags = pend->mf_gfp;
#define PREFIX_OVERFLOW (CONFIG_MALL_PREFIX_SIZE - __SIZEOF_SIZE_T__)
#if PREFIX_OVERFLOW >= (__SIZEOF_POINTER__ + __SIZEOF_GFP_T__)
			/* Nothing to do here! */
#elif CONFIG_MALL_HEAD_SIZE >= ((__SIZEOF_POINTER__ + __SIZEOF_GFP_T__) - PREFIX_OVERFLOW)
#if ((((__SIZEOF_POINTER__ + __SIZEOF_GFP_T__) - PREFIX_OVERFLOW) + 3) / 4) <= CONFIG_MALL_HEAD_SIZE
			memsetl((byte_t *)pend + CONFIG_MALL_PREFIX_SIZE,
			        CONFIG_MALL_HEAD_PATTERN,
			        (((__SIZEOF_POINTER__ + __SIZEOF_GFP_T__) - PREFIX_OVERFLOW) + 3) / 4);
#else
			mempatl((byte_t *)pend + CONFIG_MALL_PREFIX_SIZE,
			        CONFIG_MALL_HEAD_PATTERN,
			        (__SIZEOF_POINTER__ + __SIZEOF_GFP_T__) - PREFIX_OVERFLOW);
#endif
#else /* Only header */
#define MALLOC_INCONSISTENT_HEADERS_AFFECT_TAILS 1
#if CONFIG_MALL_HEAD_SIZE != 0
#if (CONFIG_MALL_HEAD_SIZE & 3) == 0
			memsetl((byte_t *)pend + CONFIG_MALL_PREFIX_SIZE,
			        CONFIG_MALL_HEAD_PATTERN,
			        CONFIG_MALL_HEAD_SIZE / 4);
#else /* (CONFIG_MALL_HEAD_SIZE & 3) == 0 */
			mempatl((byte_t *)pend + CONFIG_MALL_PREFIX_SIZE,
			        CONFIG_MALL_HEAD_PATTERN,
			        CONFIG_MALL_HEAD_SIZE);
#endif /* (CONFIG_MALL_HEAD_SIZE & 3) != 0 */
#endif /* CONFIG_MALL_HEAD_SIZE != 0 */
#define REMAIN_RESET ((__SIZEOF_POINTER__ + __SIZEOF_GFP_T__) - (PREFIX_OVERFLOW + CONFIG_MALL_HEAD_SIZE))
			{
				size_t block_size;
				block_size = pend->mf_usersize;
				if (block_size < REMAIN_RESET) {
					/* Must restore the tail */
					mempatl((byte_t *)pend + CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE + block_size,
					        CONFIG_MALL_TAIL_PATTERN, REMAIN_RESET - block_size);
				}
			}
#undef REMAIN_RESET
#endif /* Header + block + (optionally) tail */
#undef PREFIX_OVERFLOW
			ATOMIC_FETCHDEC(mall_inconsistent_head_exist);
			next = pend->mf_next;
			mall_do_free((byte_t *)pend +
			             (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE),
			             flags,
			             false);
			pend = next;
		}
	}
	while (ATOMIC_READ(mall_pending_untrace_count) != 0) {
		unsigned int i;
		for (;;) {
			u16 invalid_version_number;
			invalid_version_number = ATOMIC_READ(mall_valid_user_node_version_number);
			if (invalid_version_number <= 1)
				break;
			/* Revert back to using `1' as invalid version number, so we can simply
			 * mark all user-defined nodes that should become invalid with a version number
			 * of `0'. - This way, we can try to counter `mall_valid_user_node_version_number'
			 * from gradually nearing its limits, and eventually overflowing if the kernel
			 * occasionally runs into a situation where the pending-untrace system can't
			 * keep up with demand. */
			if (!ATOMIC_CMPXCH_WEAK(mall_valid_user_node_version_number,
			                        invalid_version_number, 1))
				continue;
			/* Update all invalidated user-nodes to fall back on using version #0 */
			if (mall_tree)
				mall_restore_invalid_version_number(mall_tree, invalid_version_number);
		}
		for (i = 0; i < COMPILER_LENOF(mall_pending_isval); ++i) {
			unsigned int j;
			uintptr_t mask;
			uintptr_t word = ATOMIC_READ(mall_pending_isval[i]);
			if unlikely(!word)
				continue;
			for (j = 0, mask = 1; j < BITSOF(uintptr_t); ++j, mask <<= 1) {
				struct pending_untrace pend;
				if (!(word & mask))
					continue;
				/* Copy the pending-task data. */
				memcpy(&pend, &mall_pending_untrace[i * BITSOF(uintptr_t) + j],
				       sizeof(struct pending_untrace));
				/* Mark the slot as no longer being in-use (consuming the untrace task). */
				if (!(ATOMIC_FETCHAND(mall_pending_isval[i], ~mask) & mask))
					continue;
				ATOMIC_FETCHAND(mall_pending_inuse[i], ~mask); /* Mark the slot as being free again. */
				ATOMIC_FETCHDEC(mall_pending_untrace_count);   /* Keep track of the number of valid blocks. */
				/* Actually do the untrace. */
				if (pend.pu_size == 0) {
					struct mallnode *node;
					node = mallnode_tree_remove(&mall_tree, (uintptr_t)pend.pu_base);
					if unlikely(!node) {
						COMPILER_READ_BARRIER();
						if (ATOMIC_READ(mall_valid_user_node_version_number))
							goto continue_scanning_pending_untrace; /* Because of the possibility of a failed split in `mall_insert_tree()' */
						sync_endwrite(&mall_lock);
						PANIC_INVALID_MALL_POINTER(pend.pu_base);
					}
					if unlikely(!(node->m_flags & MALLNODE_FUSERNODE)) {
						sync_endwrite(&mall_lock);
						PANIC_UNTRACE_NONUSER_NODE(node, pend.pu_base);
					}
					mallnode_free(node);
				} else {
					if (!mall_untrace_n_impl(pend.pu_base, pend.pu_size, flags))
						return false;
				}
continue_scanning_pending_untrace:
				/* Quick check: are there still more untrace commands left to be performed? */
				if (!ATOMIC_READ(mall_pending_untrace_count))
					goto done_pending_untrace;
			}
		}
	}
done_pending_untrace:
	return true;
}





PRIVATE bool NOTHROW(KCALL mallnode_verify_padding)(struct mallnode *__restrict self);
PRIVATE void NOTHROW(KCALL mallnode_free)(struct mallnode *__restrict self);


/* The internal implementation for `kfree()'
 * When this function is called, the caller is already holding a lock to `mall_lock' */
PRIVATE NOBLOCK void
NOTHROW(KCALL mall_do_free)(void *__restrict ptr, gfp_t flags, bool should_unlock) {
	struct mallnode *node;
	struct heapptr fullblock;

	/* Lookup  */
	node = mallnode_tree_remove(&mall_tree, (uintptr_t)ptr);
	if (should_unlock)
		mall_release();
	if unlikely(!node) {
		if (!should_unlock)
			sync_endwrite(&mall_lock);
		PANIC_INVALID_MALL_POINTER(ptr);
	}
	if unlikely(node->m_flags & MALLNODE_FUSERNODE) {
		if (!should_unlock)
			sync_endwrite(&mall_lock);
		PANIC_FREE_USER_NODE(node, ptr);
	}
	if unlikely((uintptr_t)ptr != node->m_tree.a_vmin +
	            (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE)) {
		if (!should_unlock)
			sync_endwrite(&mall_lock);
		PANIC_FREE_NOT_NODE_BASE_ADDRESS(node, ptr);
	}
	/* Validate the padding for a node before freeing it, thus ensuring
	 * that the user hasn't done anything to corrupt the heap block during
	 * the block's life-time. */
	mallnode_verify_padding(node);

	/* All right! everything checks out, so we can actually move on to
	 * freeing the associated node, as well as the user-data block. */
	fullblock.hp_ptr = (void *)node->m_tree.a_vmin;
	fullblock.hp_siz = (size_t)((node->m_tree.a_vmax - node->m_tree.a_vmin) + 1);
	/* Load heap-flag properties from the node itself. */
	flags = (flags & ~__GFP_HEAPMASK) | (node->m_flags & __GFP_HEAPMASK);
	mallnode_free(node);
	assert(fullblock.hp_siz >=
	       MAX(HEAP_MINSIZE, CONFIG_MALL_PREFIX_SIZE +
	                         CONFIG_MALL_HEAD_SIZE +
	                         CONFIG_MALL_TAIL_SIZE));
	/* When freeing zero-initialized memory,
	 * clean up the head & tail blocks first! */
	if (flags & GFP_CALLOC) {
		memset(fullblock.hp_ptr, 0,
		       CONFIG_MALL_PREFIX_SIZE +
		       CONFIG_MALL_HEAD_SIZE);
		memset((byte_t *)fullblock.hp_ptr +
		       (fullblock.hp_siz - CONFIG_MALL_TAIL_SIZE),
		       0, CONFIG_MALL_TAIL_SIZE);
	}
	/* And finally, free the user's actual data block. */
	heap_free_untraced(&kernel_heaps[flags & __GFP_HEAPMASK],
	                   fullblock.hp_ptr,
	                   fullblock.hp_siz,
	                   flags);
}

PRIVATE NOBLOCK void
NOTHROW(KCALL mall_add_pending_free)(void *__restrict ptr, gfp_t flags) {
	struct pending_malloc_free *pend, *next;
	/* Failed to acquire the MALL lock. - We can't validate the pointer, and
	 * we must use the user-data block as part of a linked list of pending
	 * free data blocks. */
	pend = (struct pending_malloc_free *)((byte_t *)ptr - (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE));
	/* Indicate that headers are about to become inconsistent (at least for a while) */
	ATOMIC_FETCHINC(mall_inconsistent_head_exist);
	COMPILER_WRITE_BARRIER();
	pend->mf_gfp = flags;
	do {
		next = ATOMIC_READ(mall_pending_mallocfree);
		pend->mf_next = next;
	} while (!ATOMIC_CMPXCH_WEAK(mall_pending_mallocfree, next, pend));
}


PUBLIC NOBLOCK void
NOTHROW(KCALL kffree)(VIRT void *ptr, gfp_t flags) {
	if (!ptr)
		return; /* Ignore NULL-pointers. */
#ifdef CONFIG_USE_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr)) {
		slab_ffree(ptr, flags);
		return;
	}
#endif /* CONFIG_USE_SLAB_ALLOCATORS */
	if (!mall_acquire_atomic()) {
		/* Use a pending chain to ensure that kfree() is atomic for all cases. */
		mall_add_pending_free(ptr, flags);
		if (sync_trywrite(&mall_lock))
			mall_release();
		return;
	}
	mall_do_free(ptr, flags, true);
}

PUBLIC NOBLOCK void
NOTHROW(KCALL kfree)(VIRT void *ptr) {
	if (!ptr)
		return; /* Ignore NULL-pointers. */
#ifdef CONFIG_USE_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr)) {
		slab_free(ptr);
		return;
	}
#endif /* CONFIG_USE_SLAB_ALLOCATORS */
	if (!mall_acquire_atomic()) {
		/* Use a pending chain to ensure that kfree() is atomic for all cases. */
		mall_add_pending_free(ptr, GFP_NORMAL);
		if (sync_trywrite(&mall_lock))
			mall_release();
		return;
	}
	mall_do_free(ptr, GFP_NORMAL, true);
}



/* The current version number used when searching for memory leaks.
 * This value is used to identity pointers that haven't been reached/search yet. */
PRIVATE mall_ver_t mall_leak_version = 0;

/* Analyze a pointer, or data block for reachable pointers,
 * returning the number of reachable mall pointers. */
PRIVATE NOBLOCK size_t NOTHROW(KCALL mall_reachable_data)(byte_t *base, size_t num_bytes);

PRIVATE NOBLOCK size_t
NOTHROW(KCALL mall_reachable_pointer)(void *ptr) {
	struct mallnode *node;
	if (!ptr)
		return 0; /* Optimization: NULL pointer */
#ifdef X86_PAGING_ISNONCANON
	if (X86_PAGING_ISNONCANON((uintptr_t)ptr))
		return 0;
#endif /* X86_PAGING_ISNONCANON */
	if (((uintptr_t)ptr & (sizeof(void *) - 1)) != 0)
		return 0; /* Unaligned pointer -> not a heap pointer */
#ifdef KERNELSPACE_HIGHMEM
	if ((uintptr_t)ptr < KERNELSPACE_BASE)
		return 0;
#elif defined(KERNELSPACE_LOWMEM)
	if ((uintptr_t)ptr >= KERNEL_CEILING)
		return 0;
#endif
#if __SIZEOF_POINTER__ == 4
#ifdef CONFIG_DEBUG_HEAP
	if ((uintptr_t)ptr == DEBUGHEAP_NO_MANS_LAND)
		return 0; /* Optimization: No mans land */
	if ((uintptr_t)ptr == DEBUGHEAP_FRESH_MEMORY)
		return 0; /* Optimization: Fresh memory. */
#endif /* CONFIG_DEBUG_HEAP */
	if ((uintptr_t)ptr == 0xcccccccc)
		return 0; /* Optimization: Stack pre-initialization. */
#endif /* __SIZEOF_POINTER__ == 4 */
	node = mallnode_tree_locate(mall_tree, (uintptr_t)ptr);
	if (!node)
		return 0;
	if (node->m_reach == mall_leak_version)
		return 0; /* Already reached. */
	node->m_reach = mall_leak_version;
	return 1;
}

PRIVATE NOBLOCK size_t
NOTHROW(KCALL mall_reachable_data)(byte_t *base, size_t num_bytes) {
	size_t result = 0;
	if unlikely((uintptr_t)base & (sizeof(void *) - 1)) {
		/* Align the base pointer. */
		size_t offset;
		offset = sizeof(void *) - ((uintptr_t)base & (sizeof(void *) - 1));
		if unlikely(offset >= num_bytes)
			goto done;
		num_bytes -= offset;
		base += offset;
	}
	while (num_bytes >= sizeof(void *)) {
		void *ptr;
		size_t page_bytes = PAGESIZE - ((uintptr_t)base & PAGEMASK);
		/* Only scan writable pages. */
		if (!pagedir_iswritable(base)) {
			if (page_bytes >= num_bytes)
				break;
			base += page_bytes;
			num_bytes -= page_bytes;
			continue;
		}
		if (page_bytes > num_bytes)
			page_bytes = num_bytes;
		num_bytes -= page_bytes;
		while (page_bytes >= sizeof(void *)) {
			COMPILER_READ_BARRIER();
			ptr = *(void **)base;
			COMPILER_READ_BARRIER();
			/* Check if this is a heap pointer, and if so: mark it as reachable. */
			result += mall_reachable_pointer(ptr);
			base += sizeof(void *);
			page_bytes -= sizeof(void *);
		}
	}
done:
	return result;
}


PRIVATE NOBLOCK void
NOTHROW(KCALL mall_search_task_scpustate)(struct task *__restrict thread,
                                          struct scpustate *__restrict context) {
	/* Search the registers of this thread. */
	if (scpustate_isuser(context)) {
		/* Thread is currently in user-space (meaning its kernel stack is unused) */
	} else {
		unsigned int i;
		void *sp, *stack_min, *stack_end;
		/* Search general-purpose registers. */
		for (i = 0; i < (sizeof(struct gpregs) / sizeof(void *)); ++i)
			mall_reachable_pointer(((void **)&context->scs_gpregs)[i]);
		stack_min = vm_node_getmin(&FORTASK(thread, this_kernel_stacknode));
		stack_end = vm_node_getend(&FORTASK(thread, this_kernel_stacknode));
#ifdef scpustate_getkernelpsp
		sp = (void *)scpustate_getkernelpsp(context);
#else /* scpustate_getkernelpsp */ 
		sp = (void *)scpustate_getsp(context);
#endif /* !scpustate_getkernelpsp */
		if (sp > stack_min && sp <= stack_end) {
			/* Search the used portion of the kernel stack. */
			mall_reachable_data((byte_t *)sp,
			                    (size_t)((byte_t *)stack_end - (byte_t *)sp));
		} else {
			/* Stack pointer is out-of-bounds (no idea what this is
			 * about, but let's just assume the entire stack is allocated) */
			mall_reachable_data((byte_t *)stack_min,
			                    (size_t)((byte_t *)stack_end - (byte_t *)stack_min));
		}
	}
}

#ifndef CONFIG_NO_SMP
PRIVATE NOBLOCK void
NOTHROW(KCALL mall_search_task_icpustate)(struct task *__restrict thread,
                                          struct icpustate *__restrict context) {
	/* Search the registers of this thread. */
	if (irregs_isuser(&context->ics_irregs)) {
		/* Thread is currently in user-space (meaning its kernel stack is unused) */
	} else {
		unsigned int i;
		void *sp, *stack_min, *stack_end;
		/* Search general-purpose registers. */
		for (i = 0; i < (sizeof(struct gpregs) / sizeof(void *)); ++i)
			mall_reachable_pointer(((void **)&context->ics_gpregs)[i]);
		stack_min = vm_node_getmin(&FORTASK(thread, this_kernel_stacknode));
		stack_end = vm_node_getend(&FORTASK(thread, this_kernel_stacknode));
		sp = (void *)irregs_getkernelpsp(&context->ics_irregs);
		if (sp > stack_min && sp <= stack_end) {
			/* Search the used portion of the kernel stack. */
			mall_reachable_data((byte_t *)sp,
			                    (size_t)((byte_t *)stack_end - (byte_t *)sp));
		} else {
			/* Stack pointer is out-of-bounds (no idea what this is
			 * about, but let's just assume the entire stack is allocated) */
			mall_reachable_data((byte_t *)stack_min,
			                    (size_t)((byte_t *)stack_end - (byte_t *)stack_min));
		}
	}
}
#endif /* !CONFIG_NO_SMP */

PRIVATE NOBLOCK void
NOTHROW(KCALL mall_search_this_task)(void) {
	unsigned int i;
	void *sp, *stack_min, *stack_end;
	struct lcpustate context;
	struct vm_node const *my_stack;
	/* Search the registers of this thread. */
	lcpustate_current(&context);
	/* Search general-purpose registers. */
	for (i = 0; i < (sizeof(struct lcpustate) / sizeof(void *)); ++i)
		mall_reachable_pointer(((void **)&context)[i]);
	my_stack = THIS_KERNEL_STACK;
	sp       = (void *)lcpustate_getsp(&context);
	get_stack_for(&stack_min, &stack_end, sp);
	if (sp > stack_min && sp <= stack_end) {
		/* Search the used portion of the kernel stack. */
		mall_reachable_data((byte_t *)sp,
		                    (size_t)((byte_t *)stack_end - (byte_t *)sp));
		/* If we're running from a custom stack, also search the original kernel stack! */
		if (stack_end != (byte_t *)vm_node_getend(my_stack))
			goto do_search_kernel_stack;
	} else {
		/* Stack pointer is out-of-bounds (no idea what this is
		 * about, but let's just assume the entire stack is allocated) */
do_search_kernel_stack:
		stack_min = vm_node_getmin(my_stack);
		stack_end = vm_node_getend(my_stack);
		mall_reachable_data((byte_t *)stack_min,
		                    (size_t)((byte_t *)stack_end - (byte_t *)stack_min));
	}
}

PRIVATE NOBLOCK size_t
NOTHROW(KCALL scan_reachable)(struct mallnode *__restrict node) {
	size_t result = 0;
again:
	if (node->m_reach == mall_leak_version &&
	    node->m_visit != mall_leak_version &&
	    !(node->m_flags & MALLNODE_FNOWALK)) {
		/* Scan the user-data block of this node. */
		if (node->m_flags & MALLNODE_FUSERNODE) {
			result += mall_reachable_data((byte_t *)node->m_tree.a_vmin,
			                              (node->m_tree.a_vmax - node->m_tree.a_vmin) + 1);
		} else {
			result += mall_reachable_data((byte_t *)(node->m_tree.a_vmin + CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE),
			                              ((node->m_tree.a_vmax - node->m_tree.a_vmin) + 1) -
			                              (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE + CONFIG_MALL_TAIL_SIZE));
		}
		node->m_visit = mall_leak_version;
	}
	if (node->m_tree.a_min) {
		if (node->m_tree.a_max)
			result += scan_reachable(node->m_tree.a_max);
		node = node->m_tree.a_min;
		goto again;
	}
	if (node->m_tree.a_max) {
		node = node->m_tree.a_max;
		goto again;
	}
	return result;
}



INTDEF byte_t __debug_malloc_tracked_start[];
INTDEF byte_t __debug_malloc_tracked_end[];
INTDEF byte_t __debug_malloc_tracked_size[];

#ifndef CONFIG_NO_SMP
PRIVATE struct icpustate *mall_other_cpu_states[CONFIG_MAX_CPU_COUNT];
#endif /* !CONFIG_NO_SMP */

PRIVATE NOBLOCK void
NOTHROW(KCALL mall_search_leaks_impl)(void) {
	cpuid_t i;
	/* Search for memory leaks.
	 * The idea here is not to be able to find all memory blocks that were
	 * leaked, but rather to find anything that ~might~ be referenced.
	 * To do this, we search all places we can think of:
	 *    - Kernel .data & .bss
	 *    - Driver .data & .bss
	 *    - Stacks and general purpose registers of all other threads
	 *    - VMs reachable from those threads (XXX: maybe use kmalloc() for VMs in debug mode?)
	 * For this purpose, any properly aligned data word is considered a
	 * possible pointer and if directed at a known VM node, that node is
	 * saved as reachable.
	 * Following this first pass, we recursively analyze the user-data
	 * blocks of all heap pointers that were reached thus far, until we're
	 * no longer encountering any new ones.
	 * Anything that still hasn't been reached is then considered a leak. */
	PRINT_LEAKS_SEARCH_PHASE("Phase #1: Scan .data + .bss\n");
	mall_reachable_data((byte_t *)__debug_malloc_tracked_start,
	                    (size_t)__debug_malloc_tracked_size);

	/* Also search state data segments of loaded drivers.
	 * For this purpose, we only scan writable segments */
	{
		REF struct driver_state *ds;
		size_t i;
		ds = driver_get_state();
		for (i = 0; i < ds->ds_count; ++i) {
			struct driver *d = ds->ds_drivers[i];
			ElfW(Half) j;
			for (j = 0; j < d->d_phnum; ++j) {
				uintptr_t progaddr;
				size_t progsize;
				if (d->d_phdr[i].p_type != PT_LOAD)
					continue; /* Skip segments that don't describe program memory. */
				if (!(d->d_phdr[i].p_flags & PF_W))
					continue; /* Skip non-writable segments. */
				progaddr = (uintptr_t)(d->d_loadaddr + d->d_phdr[i].p_vaddr);
				progsize = d->d_phdr[i].p_memsz;
				/* Scan the contents of this segment. */
				mall_reachable_data((byte_t *)progaddr, progsize);
			}
		}
		decref_unlikely(ds);
	}

	/* Search all threads on all CPUs. */
	PRINT_LEAKS_SEARCH_PHASE("Phase #2: Scan running threads\n");
	for (i = 0; i < cpu_count; ++i) {
		struct cpu *c = cpu_vector[i];
		struct task *iter, *chain;
		bool did_check_idle = false;
		iter = chain = c->c_current;
		do {
			if (iter != THIS_TASK) {
				if (iter == &FORCPU(c, thiscpu_idle))
					did_check_idle = true;
#ifndef CONFIG_NO_SMP
				/* NOTE: Must check if mall_other_cpu_states[i] != NULL, in
				 *       case the CPU didn't get suspended because it is (and
				 *       still should be) in deep sleep. */
				if (iter == chain && mall_other_cpu_states[i] != NULL) {
					/* Special case for the thread that got stopped on the foreign CPU */
					assert(c != THIS_CPU);
					mall_search_task_icpustate(iter, mall_other_cpu_states[i]);
				} else
#endif /* !CONFIG_NO_SMP */
				{
					mall_search_task_scpustate(iter, iter->t_sched.s_state);
				}
			}
		} while ((iter = iter->t_sched.s_running.sr_runnxt) != chain);
		for (chain = c->c_sleeping; chain;
		     chain = chain->t_sched.s_asleep.ss_tmonxt) {
			if (chain == &FORCPU(c, thiscpu_idle))
				did_check_idle = true;
			mall_search_task_scpustate(chain, chain->t_sched.s_state);
		}
#ifndef CONFIG_NO_SMP
		for (chain = c->c_pending; chain != CPU_PENDING_ENDOFCHAIN;
		     chain = chain->t_sched.s_pending.ss_pennxt)
			mall_search_task_scpustate(chain, chain->t_sched.s_state);
#endif /* !CONFIG_NO_SMP */
		if (!did_check_idle) {
			mall_search_task_scpustate(&FORCPU(c, thiscpu_idle),
			                           FORCPU(c, thiscpu_idle).t_sched.s_state);
		}
	}
	PRINT_LEAKS_SEARCH_PHASE("Phase #2.1: Scan the calling thread\n");
	mall_search_this_task();

	/* Scan all allocated COREBASE pointers from the kernel VM.
	 * Since those are randomly sprinkled into the kernel VM tree,
	 * they normally wouldn't be able to forward contained data
	 * pointers, which would then result in us not realizing that
	 * any dynamic node pointed to by them is actually reachable.
	 * NOTE: COREBASE couldn't use `mall_trace()' because that
	 *       could cause infinite recursion when `mall_trace()'
	 *       tried to allocate a new recursion descriptor.
	 */
	PRINT_LEAKS_SEARCH_PHASE("Phase #3: Scan core base\n");
	{
		struct vm_corepage *iter = vm_corepage_head;
		for (; iter; iter = iter->cp_ctrl.cpc_prev)
			mall_reachable_data((byte_t *)iter->cp_parts, sizeof(iter->cp_parts));
	}

#ifdef CONFIG_USE_SLAB_ALLOCATORS
	/* TODO: Data of any slab pointer that was reached must be scanned
	 *       recursively alongside for memory leaks. Finally, any slab
	 *       pointer that wasn't reached should also be considered a
	 *       memory leak!
	 * -> Otherwise, heap-pointer stored in slab-allocated memory blocks
	 *    would not be reachable and would be considered as memory leaks...
	 */
#endif /* CONFIG_USE_SLAB_ALLOCATORS */


	PRINT_LEAKS_SEARCH_PHASE("Phase #4: Recursively scan reached pointers\n");
	if (mall_tree) {
		size_t num_found;
		/* With all data collected, recursively scan the data blocks of all reachable nodes.
		 * The recursion takes place because we keep scanning until nothing new shows up. */
		do {
			num_found = scan_reachable(mall_tree);
			PRINT_LEAKS_SEARCH_PHASE("Phase #4: Reached %Iu pointers\n", num_found);
		} while (num_found);
	}
}



PRIVATE NOBLOCK size_t
NOTHROW(KCALL print_unreachable)(struct mallnode *__restrict node) {
	size_t result = 0;
again:
	if (node->m_reach != mall_leak_version &&
	    !(node->m_flags & MALLNODE_FNOLEAK)) {
		size_t trace_size, i;
		/* This node wasn't reached. */
		if (node->m_flags & MALLNODE_FUSERNODE) {
			addr2line_printf(&syslog_printer, SYSLOG_LEVEL_RAW,
			                 (uintptr_t)instruction_trypred(node->m_trace[0], INSTRLEN_ISA_DEFAULT),
			                 (uintptr_t)node->m_trace[0],
			                 "Leaked %Iu bytes of heap-memory at %p...%p",
			                 MALLNODE_SIZE(node), MALLNODE_MIN(node), MALLNODE_MAX(node));
		} else {
			addr2line_printf(&syslog_printer, SYSLOG_LEVEL_RAW,
			                 (uintptr_t)instruction_trypred(node->m_trace[0], INSTRLEN_ISA_DEFAULT),
			                 (uintptr_t)node->m_trace[0],
			                 "Leaked %Iu bytes of kmalloc-memory at %p...%p",
			                 MALLNODE_SIZE(node) - (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE + CONFIG_MALL_TAIL_SIZE),
			                 MALLNODE_MIN(node) + (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE),
			                 MALLNODE_MAX(node) - CONFIG_MALL_TAIL_SIZE);
		}
		trace_size = MALLNODE_TRACESZ(node);
		for (i = 1; i < trace_size; ++i) {
			if (!node->m_trace[i])
				break;
			addr2line_printf(&syslog_printer, SYSLOG_LEVEL_RAW,
			                 (uintptr_t)instruction_trypred(node->m_trace[i], INSTRLEN_ISA_DEFAULT),
			                 (uintptr_t)node->m_trace[i],
			                 "Called here");
		}
		printk(KERN_RAW "\n");
		++result;
	}
	if (node->m_tree.a_min) {
		if (node->m_tree.a_max)
			result += print_unreachable(node->m_tree.a_max);
		node = node->m_tree.a_min;
		goto again;
	}
	if (node->m_tree.a_max) {
		node = node->m_tree.a_max;
		goto again;
	}
	return result;
}

PRIVATE NOBLOCK size_t
NOTHROW(KCALL mall_print_leaks_impl)(void) {
	size_t result = 0;
	if (mall_tree)
		result += print_unreachable(mall_tree);
	return result;
}


#ifndef CONFIG_NO_SMP
PRIVATE WEAK cpuid_t mall_suspended_cpu_count = 0;
PRIVATE WEAK struct task *mall_suspended_locked = NULL;
PRIVATE struct sig mall_suspended_unlock = SIG_INIT;

PRIVATE NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL mall_singlecore_mode_ipi)(struct icpustate *__restrict state,
                                        void *args[CPU_IPI_ARGCOUNT]) {
	uintptr_t old_flags;
	struct task *me = THIS_TASK;
	struct task *old_override;
	struct task_connections old_cons;
	assert(!PREEMPTION_ENABLED());
	(void)args;

	/* Setup a preemption override for our own CPU */
	COMPILER_BARRIER();
	old_flags    = ATOMIC_FETCHOR(me->t_flags, TASK_FKEEPCORE);
	old_override = me->t_cpu->c_override;
	me->t_cpu->c_override = me;
	COMPILER_BARRIER();

	/* Store the interrupted state for our CPU, allowing the mall
	 * scanner to know our latest register state for the purpose
	 * of scanning it. */
	mall_other_cpu_states[me->t_cpu->c_id] = state;
	COMPILER_BARRIER();

	/* Report that we can now be considered to be suspended. */
	ATOMIC_FETCHINC(mall_suspended_cpu_count);

	/* Wait for the unlock to be signaled. */
	task_pushconnections(&old_cons);
	PREEMPTION_ENABLE();
	while (ATOMIC_READ(mall_suspended_locked) != NULL) {
		/* Wait for `mall_suspended_unlock' */
		task_connect(&mall_suspended_unlock);
		if unlikely(ATOMIC_READ(mall_suspended_locked) == NULL) {
			task_disconnectall();
			break;
		}
		/* Wait for the other thread, but don't service RPCs,
		 * or allow exceptions to be thrown. */
		if (!task_waitfor_norpc_nx())
			task_disconnectall();
	}
	PREEMPTION_DISABLE();
	task_popconnections(&old_cons);

	/* Report that we've resumed execution. */
	ATOMIC_FETCHDEC(mall_suspended_cpu_count);

	/* Restore the old preemption behavior. */
	COMPILER_BARRIER();
	me->t_cpu->c_override = old_override;
	if (!(old_flags & TASK_FKEEPCORE))
		ATOMIC_FETCHAND(me->t_flags, ~TASK_FKEEPCORE);
	COMPILER_BARRIER();

	return state;
}


PRIVATE NOBLOCK bool
NOTHROW(KCALL mall_enter_singlecore_mode)(void) {
	cpuid_t num_suspended;
	struct task *old_thread;
	old_thread = ATOMIC_CMPXCH_VAL(mall_suspended_locked,
	                               NULL, THIS_TASK);
	if unlikely(old_thread != NULL) {
		assertf(old_thread != THIS_TASK,
		        "Recursive call to `mall_enter_singlecore_mode()' on %p",
		        old_thread);
		return false; /* Some other thread already initiated the suspend. */
	}
	memset(mall_other_cpu_states, 0, sizeof(mall_other_cpu_states));
	assert(mall_suspended_cpu_count == 0);
	{
		void *args[CPU_IPI_ARGCOUNT];
		/* Atomically send IPIs to all CPUs that aren't in deep sleep (excluding our own) */
		num_suspended = cpu_broadcastipi_notthis(&mall_singlecore_mode_ipi,
		                                         args, CPU_IPI_FWAITFOR);
	}
	/* Wait until all other CPUs have checked in and reported having become suspended. */
	while (ATOMIC_READ(mall_suspended_cpu_count) < num_suspended)
		task_pause();
	return true;
}

PRIVATE NOBLOCK void
NOTHROW(KCALL mall_leave_singlecore_mode)(void) {
	/* Unlock singlecore mode */
	ATOMIC_WRITE(mall_suspended_locked, NULL);
	/* Wake up all suspended CPUs */
	sig_broadcast(&mall_suspended_unlock);
	/* Wait for CPUs to resume */
	while (ATOMIC_READ(mall_suspended_cpu_count) != 0)
		task_pause();
}

#endif /* !CONFIG_NO_SMP */



/* Locks that must be held when searching for leaks:
 *  - `mall_lock'         (for reading)
 *  - `vm_kernel.v_treelock'
 *  - `vm_corepage_lock'
 */
PUBLIC NOBLOCK_IF(flags & GFP_ATOMIC) size_t KCALL
mall_dump_leaks(gfp_t flags) THROWS(E_WOULDBLOCK) {
	size_t result;
	/* Acquire a lock to the kernel VM and to the MALL heap */
again:
	if (!mall_acquire(flags))
		return 0;
	if (!vm_kernel_treelock_trywrite()) {
		mall_release();
		if (!vm_kernel_treelock_writef(flags))
			return 0;
		if (!mall_acquire_atomic()) {
			vm_kernel_treelock_endwrite();
			goto again;
		}
	}

	{
		uintptr_t old_flags;
		pflag_t was;
		struct task *me = THIS_TASK;
		struct task *old_override;
		/* Setup a preemption override for our own CPU */
		was = PREEMPTION_PUSHOFF();
		old_flags    = ATOMIC_FETCHOR(me->t_flags, TASK_FKEEPCORE);
		old_override = me->t_cpu->c_override;
		me->t_cpu->c_override = me;
		PREEMPTION_POP(was);

#ifndef CONFIG_NO_SMP
		/* Send an IPI to all other CPUs, asking them to suspend
		 * execution until we're done performing our scan. */
		if (!mall_enter_singlecore_mode()) {
			was = PREEMPTION_PUSHOFF();
			me->t_cpu->c_override = old_override;
			if (!(old_flags & TASK_FKEEPCORE))
				ATOMIC_FETCHAND(me->t_flags, ~TASK_FKEEPCORE);
			PREEMPTION_POP(was);
			vm_kernel_treelock_endwrite();
			mall_release();
			task_pause();
			goto again;
		}
#endif /* !CONFIG_NO_SMP */
		/* At this point we've got all the locks we need! */

		++mall_leak_version;
		if unlikely(mall_leak_version == 0)
			mall_leak_version = 1;
		/* Search for leaks. */
		mall_search_leaks_impl();
		/* Print all found leaks. */
		result = mall_print_leaks_impl();

#ifndef CONFIG_NO_SMP
		/* Allow other CPUs to resume execution. */
		mall_leave_singlecore_mode();
#endif /* !CONFIG_NO_SMP */

		/* Restore the old preemption behavior. */
		was = PREEMPTION_PUSHOFF();
		me->t_cpu->c_override = old_override;
		if (!(old_flags & TASK_FKEEPCORE))
			ATOMIC_FETCHAND(me->t_flags, ~TASK_FKEEPCORE);
		PREEMPTION_POP(was);
	}

	vm_kernel_treelock_endwrite();
	mall_release();
	return result;
}

PRIVATE NOBLOCK void
NOTHROW(KCALL mallnode_print_traceback)(struct mallnode *__restrict self,
                                        pformatprinter printer,
                                        void *arg) {
	size_t i, size;
	size = MALLNODE_TRACESZ(self);
	for (i = 0; i < size; ++i) {
		uintptr_t pc = (uintptr_t)self->m_trace[i];
		if (!pc)
			break;
		addr2line_printf(printer, arg,
		                 (uintptr_t)instruction_trypred((void const *)pc, INSTRLEN_ISA_DEFAULT),
		                 pc, i ? "Called here" : "Allocated from here");
	}
}

/* Assert that the header and tail are properly initialized. */
PRIVATE NOBLOCK bool
NOTHROW(KCALL mallnode_verify_padding)(struct mallnode *__restrict self) {
	u32 *base;
	unsigned int i;
	size_t user_size;
	base      = (u32 *)self->m_tree.a_vmin;
	user_size = *(size_t *)base;
	if (user_size != ((self->m_tree.a_vmax - self->m_tree.a_vmin) + 1) -
	                 (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE + CONFIG_MALL_TAIL_SIZE)) {
		printk(KERN_CRIT
		       "\n\nCorrupted MALL header in at %p (offset %Id from %p...%p) (expected %Iu as user-size, but got %Iu)\n",
		       base, -(ssize_t)(CONFIG_MALL_HEAD_SIZE + CONFIG_MALL_PREFIX_SIZE),
		       self->m_tree.a_vmin + CONFIG_MALL_HEAD_SIZE,
		       self->m_tree.a_vmax + 1 - CONFIG_MALL_TAIL_SIZE,
		       ((self->m_tree.a_vmax - self->m_tree.a_vmin) + 1) -
		       (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE + CONFIG_MALL_TAIL_SIZE),
		       user_size);
		goto fail;
	}
	base = (u32 *)((byte_t *)base + CONFIG_MALL_PREFIX_SIZE);
#if CONFIG_MALL_HEAD_SIZE
	for (i = sizeof(size_t) / 4; i < CONFIG_MALL_HEAD_SIZE / 4; ++i) {
		if (base[i] != CONFIG_MALL_HEAD_PATTERN) {
			u32 word;
			if (mall_inconsistent_head_exist)
				return true; /* Inconsistent header states are to be expected (deal with them, then re-try) */
			word = CONFIG_MALL_HEAD_PATTERN;
			base += i;
			while (*(u8 *)base == ((u8 *)&word)[(uintptr_t)base & 3])
				++*(uintptr_t *)&base;
			printk(KERN_CRIT
			       "\n\nCorrupted MALL header in at %p (offset %Id from %p...%p)\n",
			       base, (uintptr_t)base - (self->m_tree.a_vmin + (CONFIG_MALL_HEAD_SIZE + CONFIG_MALL_PREFIX_SIZE)),
			       self->m_tree.a_vmin + (CONFIG_MALL_HEAD_SIZE + CONFIG_MALL_PREFIX_SIZE),
			       self->m_tree.a_vmax + 1 - CONFIG_MALL_TAIL_SIZE);
			goto fail;
		}
	}
#endif /* CONFIG_MALL_HEAD_SIZE */
#if CONFIG_MALL_TAIL_SIZE
	base = (u32 *)(self->m_tree.a_vmax + 1 - CONFIG_MALL_TAIL_SIZE);
	for (i = 0; i < CONFIG_MALL_TAIL_SIZE / 4; ++i) {
		if (base[i] != CONFIG_MALL_TAIL_PATTERN) {
			u32 word;
#ifdef MALLOC_INCONSISTENT_HEADERS_AFFECT_TAILS
			if (mall_inconsistent_head_exist)
				return true; /* Inconsistent header states are to be expected (deal with them, then re-try) */
#endif /* MALLOC_INCONSISTENT_HEADERS_AFFECT_TAILS */
			word = CONFIG_MALL_TAIL_PATTERN;
			base += i;
			while (*(u8 *)base == ((u8 *)&word)[(uintptr_t)base & 3])
				base = (u32 *)((byte_t *)base + 1);
			printk(KERN_CRIT
			       "\n\nCorrupted MALL tail in at %p (offset %Id from %p...%p; offset %Iu from end of usable memory)\n",
			       base, (uintptr_t)base - (self->m_tree.a_vmin + (CONFIG_MALL_HEAD_SIZE + CONFIG_MALL_PREFIX_SIZE)),
			       self->m_tree.a_vmin + (CONFIG_MALL_HEAD_SIZE + CONFIG_MALL_PREFIX_SIZE),
			       self->m_tree.a_vmax + 1 - CONFIG_MALL_TAIL_SIZE,
			       (uintptr_t)base - (self->m_tree.a_vmax + 1 - CONFIG_MALL_TAIL_SIZE));
			goto fail;
		}
	}
#endif /* CONFIG_MALL_TAIL_SIZE */
	return false;
fail:
	format_hexdump(&syslog_printer, SYSLOG_LEVEL_CRIT,
	               (void *)MALLNODE_BEGIN(self),
	               MALLNODE_SIZE(self), 16, FORMAT_HEXDUMP_FNORMAL);
	printk(KERN_CRIT "\n");
	mallnode_print_traceback(self, &syslog_printer, SYSLOG_LEVEL_RAW);
	kernel_panic("Corrupt MALL header or tail");
	return false;
}

PRIVATE NOBLOCK bool
NOTHROW(KCALL mall_validate_padding_impl)(struct mallnode *__restrict self) {
again:
	if (!(self->m_flags & MALLNODE_FUSERNODE) &&
	    mallnode_verify_padding(self))
		return true;
	if (self->m_tree.a_min) {
		if (self->m_tree.a_max) {
			if (mall_validate_padding_impl(self->m_tree.a_max))
				return true;
		}
		self = self->m_tree.a_min;
		goto again;
	}
	if (self->m_tree.a_max) {
		self = self->m_tree.a_max;
		goto again;
	}
	return false;
}

PUBLIC NOBLOCK void
NOTHROW(KCALL mall_validate_padding)(void) {
again:
	if (!sync_tryread(&mall_lock))
		return;
	if (MALL_HAS_PENDING_COMMANDS()) {
upgrade_and_serve_commands:
		if (!sync_tryupgrade(&mall_lock)) {
			sync_endread(&mall_lock);
			if (!mall_acquire_atomic())
				return;
		} else {
do_serve_commands:
			if (!mall_serve_pending_commands(GFP_ATOMIC))
				goto again;
		}
		if (mall_tree) {
			if (mall_validate_padding_impl(mall_tree))
				goto do_serve_commands;
		}
		mall_release();
	} else {
		if (mall_tree) {
			if (mall_validate_padding_impl(mall_tree))
				goto upgrade_and_serve_commands;
		}
		sync_endread(&mall_lock);
	}
}


PRIVATE ATTR_MALLOC ATTR_RETNONNULL NOBLOCK_IF(flags & GFP_ATOMIC)
struct mallnode *KCALL mallnode_alloc(gfp_t gfp) {
	struct mallnode *result;
	struct heapptr ptr;
	ptr = heap_alloc_untraced(&mall_heap,
	                          offsetof(struct mallnode, m_trace) +
	                          (CONFIG_MALL_TRACEMIN * sizeof(void *)),
	                          MALL_HEAP_FLAGS | (gfp & GFP_INHERIT));
	result          = (struct mallnode *)ptr.hp_ptr;
	result->m_size  = ptr.hp_siz;
	result->m_flags = MALLNODE_FNORMAL;
	result->m_visit = 0;
	result->m_reach = 0;
	return result;
}

PRIVATE ATTR_MALLOC NOBLOCK_IF(flags & GFP_ATOMIC) struct mallnode *
NOTHROW(KCALL mallnode_alloc_nx)(gfp_t gfp) {
	struct mallnode *result;
	struct heapptr ptr;
	ptr = heap_alloc_untraced_nx(&mall_heap,
	                             offsetof(struct mallnode, m_trace) +
	                             (CONFIG_MALL_TRACEMIN * sizeof(void *)),
	                             MALL_HEAP_FLAGS | (gfp & GFP_INHERIT));
	if unlikely(!ptr.hp_siz)
		return NULL;
	result          = (struct mallnode *)ptr.hp_ptr;
	result->m_size  = ptr.hp_siz;
	result->m_flags = MALLNODE_FNORMAL;
	result->m_visit = 0;
	result->m_reach = 0;
	return result;
}

PRIVATE NOBLOCK void
NOTHROW(KCALL mallnode_free)(struct mallnode *__restrict self) {
	heap_free_untraced(&mall_heap,
	                   self,
	                   self->m_size,
	                   MALL_HEAP_FLAGS);
}


/* Insert the given node into the MALL tree, potentially overwriting
 * any old, invalidated user-nodes which may have been there beforehand. */
PRIVATE NOBLOCK void
NOTHROW(KCALL mall_insert_tree)(struct mallnode *__restrict node) {
	while (!mallnode_tree_tryinsert(&mall_tree, node)) {
		struct mallnode *existing_node;
		struct mallnode **p_existing_node;
		VIRT uintptr_t addr_semi = ATREE_SEMI0(VIRT uintptr_t);
		unsigned int addr_level  = ATREE_LEVEL0(VIRT uintptr_t);
		p_existing_node = mallnode_tree_prlocate_at(&mall_tree,
		                                            node->m_tree.a_vmin,
		                                            node->m_tree.a_vmax,
		                                            &addr_semi,
		                                            &addr_level);
		assert(p_existing_node);
		existing_node = *p_existing_node;
		assert(existing_node);
		if (MALLNODE_ISVALID(existing_node)) {
			printk(KERN_CRIT "Traceback of existing node:\n");
			mallnode_print_traceback(existing_node, &syslog_printer, SYSLOG_LEVEL_CRIT);
			kernel_panic("Attempted to trace memory at %p...%p, which "
			             "overlaps with an existing tracing of %p...%p",
			             node->m_tree.a_vmin,
			             node->m_tree.a_vmax,
			             existing_node->m_tree.a_vmin,
			             existing_node->m_tree.a_vmax);
		}
		printk(KERN_WARNING "MALL node at %p...%p overlaps with invalidated user-node at %p...%p\n",
		       node->m_tree.a_vmin,
		       node->m_tree.a_vmax,
		       existing_node->m_tree.a_vmin,
		       existing_node->m_tree.a_vmax);
		/* Remove the old, invalidated node. */
		mallnode_tree_pop_at(p_existing_node, addr_semi, addr_level);
		if (node->m_tree.a_vmin > existing_node->m_tree.a_vmin) {
			struct mallnode *hinode;
			/* Try to truncate the existing node. */
			if (node->m_tree.a_vmax >= existing_node->m_tree.a_vmax) {
				existing_node->m_tree.a_vmax = node->m_tree.a_vmin - 1;
				mallnode_tree_insert(&mall_tree, existing_node);
				continue;
			}
			/* The existing node must be split in 2.
			 * #1:  MIN:existing_node->m_tree.a_vmin
			 *      MAX:node->m_tree.a_vmin - 1
			 * #2:  MIN:node->m_tree.a_vmax + 1
			 *      MAX:existing_node->m_tree.a_vmax */
			hinode = mallnode_alloc_nx(GFP_ATOMIC);
			if unlikely(!hinode) {
				/* We've failed to split the existing, invalidated node. - Log an error,
				 * and continue by simply deleting it (it was invalidated after all...,
				 * so we're not entirely wrong in doing this. However, if the user ends
				 * up try into untrace the node at a later point in time, the attempt may
				 * fail unexpectedly)
				 * This problem is also the reason why `mall_untrace_n()' and `mall_untrace()'
				 * ignore failures in locating the requested node once nodes have started
				 * being invalidated. */
				printk(KERN_ERR "Failed to split invalidated user-node at %p...%p into "
				                "%p...%p and %p...%p, to account for a new node at %p...%p\n",
				       existing_node->m_tree.a_vmin,
				       existing_node->m_tree.a_vmax,
				       existing_node->m_tree.a_vmin,
				       node->m_tree.a_vmin - 1,
				       node->m_tree.a_vmax + 1,
				       existing_node->m_tree.a_vmax,
				       node->m_tree.a_vmin,
				       node->m_tree.a_vmax);
			} else {
				hinode->m_tree.a_vmin        = existing_node->m_tree.a_vmax + 1;
				hinode->m_tree.a_vmax        = existing_node->m_tree.a_vmax;
				existing_node->m_tree.a_vmax = existing_node->m_tree.a_vmin - 1;
				hinode->m_flags              = existing_node->m_flags;
				memcpy(hinode->m_trace, existing_node->m_trace,
				       MIN(MALLNODE_TRACESZ(hinode),
				           MALLNODE_TRACESZ(existing_node)),
				       sizeof(void *));
				/* Insert both the existing, as well as the higher-order node into the tree. */
				mallnode_tree_insert(&mall_tree, existing_node);
				mallnode_tree_insert(&mall_tree, hinode);
				continue;
			}
		} else if (node->m_tree.a_vmax < existing_node->m_tree.a_vmax) {
			/* Try to truncate the existing node. */
			existing_node->m_tree.a_vmin = node->m_tree.a_vmax + 1;
			mallnode_tree_insert(&mall_tree, existing_node);
			continue;
		}
		/* Free the existing node. */
		mallnode_free(existing_node);
	}
}


PRIVATE ATTR_RETNONNULL NOBLOCK_IF(flags & GFP_ATOMIC) void *KCALL
mall_trace_impl(void *base, size_t num_bytes, gfp_t flags, void *context) {
	struct mallnode *node = mallnode_alloc(flags);
	assertf(num_bytes, "Cannot define an empty tracing point");
	FILL_NODE_TRACE_WITH_CALLER_TRACEBACK(node);
	node->m_tree.a_vmin = (uintptr_t)base;
	node->m_tree.a_vmax = (uintptr_t)base + num_bytes - 1;
	node->m_flags       = flags;
	node->m_userver     = mall_valid_user_node_version_number;
	node->m_tracetid    = task_gettid_s();
	/* Insert the new node into the tree of user-defined tracing points. */
	if (!mall_acquire(flags)) {
		mallnode_free(node);
		THROW(E_WOULDBLOCK_PREEMPTED);
	}
	mall_insert_tree(node);
	mall_release();
	return base;
}

PRIVATE NOBLOCK_IF(flags & GFP_ATOMIC) void *
NOTHROW(KCALL mall_trace_impl_nx)(void *base, size_t num_bytes, gfp_t flags, void *context) {
	struct mallnode *node;
	node = mallnode_alloc_nx(flags);
	if unlikely(!node)
		return NULL;
	assertf(num_bytes, "Cannot define an empty tracing point");
	FILL_NODE_TRACE_WITH_CALLER_TRACEBACK(node);
	node->m_tree.a_vmin = (uintptr_t)base;
	node->m_tree.a_vmax = (uintptr_t)base + num_bytes - 1;
	node->m_flags       = flags;
	node->m_userver     = mall_valid_user_node_version_number;
	node->m_tracetid    = task_gettid_s();
	/* Insert the new node into the tree of user-defined tracing points. */
	if (!mall_acquire_nx(flags)) {
		mallnode_free(node);
		return NULL;
	}
	mall_insert_tree(node);
	mall_release();
	return base;
}


PUBLIC NOBLOCK_IF(flags & GFP_ATOMIC) ATTR_RETNONNULL void *KCALL
mall_trace(void *base, size_t num_bytes, gfp_t flags) {
	LOAD_CALLER_CONTEXT
	assert(!(flags & MALLNODE_FUSERNODE));
	return mall_trace_impl(base, num_bytes,
	                       (flags & (GFP_NOLEAK | GFP_NOWALK)) |
	                       MALLNODE_FUSERNODE,
	                       context);
}

PUBLIC NOBLOCK_IF(flags & GFP_ATOMIC) void *
NOTHROW(KCALL mall_trace_nx)(void *base, size_t num_bytes, gfp_t flags) {
	LOAD_CALLER_CONTEXT
	assert(!(flags & MALLNODE_FUSERNODE));
	return mall_trace_impl_nx(base, num_bytes,
	                          (flags & (GFP_NOLEAK | GFP_NOWALK)) |
	                          MALLNODE_FUSERNODE,
	                          context);
}



PUBLIC NOBLOCK_IF(flags & GFP_ATOMIC) void
NOTHROW(KCALL mall_print_traceback)(void *ptr, gfp_t flags) {
	struct mallnode *node;
	if (!sync_tryread(&mall_lock)) {
		if (flags & GFP_ATOMIC)
			return; /* Cannot print like this. */
		sync_read(&mall_lock);
	}
	node = mall_tree ? mallnode_tree_locate(mall_tree, (uintptr_t)ptr) : NULL;
	if unlikely(!node) {
		sync_endread(&mall_lock);
		PANIC_INVALID_MALL_POINTER_WITH_CALLER_TRACEBACK(ptr);
	}
	/* TODO: Copy the traceback vector onto a local variable, so
	 *       it can be dumped after having released `&mall_lock' */
	mallnode_print_traceback(node, &syslog_printer, SYSLOG_LEVEL_DEBUG);
	sync_endread(&mall_lock);
}


PUBLIC NOBLOCK_IF(flags & GFP_ATOMIC) void
NOTHROW(KCALL mall_untrace)(void *ptr, gfp_t flags) {
	struct mallnode *node;
	if (!mall_acquire_nx(flags)) {
		mall_add_pending_untrace(ptr);
		if (sync_trywrite(&mall_lock))
			mall_release();
		return;
	}
	node = mallnode_tree_remove(&mall_tree, (uintptr_t)ptr);
	mall_release();
	if unlikely(!node) {
		if (mall_valid_user_node_version_number)
			return; /* Because of the possibility of a failed split in `mall_insert_tree()' */
		PANIC_INVALID_MALL_POINTER_WITH_CALLER_TRACEBACK(ptr);
	}
	if unlikely(!(node->m_flags & MALLNODE_FUSERNODE))
		PANIC_UNTRACE_NONUSER_NODE_WITH_CALLER_TRACEBACK(node, ptr);
	mallnode_free(node);
}

PUBLIC NOBLOCK_IF(flags & GFP_ATOMIC) void
NOTHROW(KCALL mall_untrace_n)(void *ptr, size_t num_bytes, gfp_t flags) {
	bool remains_locked;
	if (!num_bytes)
		return;
	if (!mall_acquire_nx(flags)) {
		mall_add_pending_untrace_n(ptr, num_bytes);
		if (sync_trywrite(&mall_lock))
			mall_release();
		return;
	}
	remains_locked = mall_untrace_n_impl(ptr, num_bytes, flags);
	if (remains_locked)
		mall_release();
}


PUBLIC NOBLOCK void
NOTHROW(KCALL heap_free)(struct heap *__restrict self,
                         VIRT void *ptr, size_t num_bytes,
                         gfp_t flags) {
	mall_untrace_n(ptr, num_bytes, flags | GFP_ATOMIC);
	heap_free_untraced(self, ptr, num_bytes, flags);
}

PUBLIC WUNUSED NONNULL((1)) size_t
NOTHROW(KCALL heap_truncate)(struct heap *__restrict self, void *base,
                             size_t old_size, size_t new_size, gfp_t free_flags) {
	size_t free_bytes;
	assertf(!old_size || old_size >= HEAP_MINSIZE, "Invalid heap_truncate(): Too few bytes (%Iu < %Iu)", old_size, HEAP_MINSIZE);
	assertf(!old_size || IS_ALIGNED((uintptr_t)base, HEAP_ALIGNMENT), "Invalid heap_truncate(): Unaligned base pointer %p", base);
	assertf(IS_ALIGNED(old_size, HEAP_ALIGNMENT), "Invalid heap_truncate(): Unaligned old_size size %Iu (%#Ix)", old_size, old_size);
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
		heap_free(self, (void *)((uintptr_t)base + new_size),
		          free_bytes, free_flags);
		return new_size;
	}
return_old_size:
	return old_size;
}




PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL kmalloc_usable_size)(VIRT void *ptr) {
	struct mallnode *node;
	size_t result, result2;
	if (!ptr)
		return 0;
	assert(IS_ALIGNED((uintptr_t)ptr, HEAP_ALIGNMENT));
#ifdef CONFIG_USE_SLAB_ALLOCATORS
	if (KERNEL_SLAB_CHECKPTR(ptr))
		return SLAB_GET(ptr)->s_size;
#endif /* CONFIG_USE_SLAB_ALLOCATORS */
	if unlikely(!sync_tryread(&mall_lock)) {
		/* We can't validate the pointer, so all we can do is return its saved size field. */
		return *(size_t *)((byte_t *)ptr - (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE));
	}
	node = mall_tree ? mallnode_tree_locate(mall_tree, (uintptr_t)ptr) : NULL;
	if unlikely(!node) {
		sync_endread(&mall_lock);
		PANIC_INVALID_MALL_POINTER_WITH_CALLER_TRACEBACK(ptr);
	}
	if unlikely(node->m_flags & MALLNODE_FUSERNODE) {
		mallnode_tree_remove(&mall_tree, (uintptr_t)ptr);
		sync_endread(&mall_lock);
		PANIC_SIZEOF_USER_NODE_WITH_CALLER_TRACEBACK(node, ptr);
	}
	if unlikely((uintptr_t)ptr != node->m_tree.a_vmin +
	            (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE)) {
		mallnode_tree_remove(&mall_tree, (uintptr_t)ptr);
		sync_endread(&mall_lock);
		PANIC_SIZEOF_NOT_NODE_BASE_ADDRESS_WITH_CALLER_TRACEBACK(node, ptr);
	}
	/* Look in both places where the node's size is stored, and compare them. */
	result  = *(size_t *)((byte_t *)ptr - (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE));
	result2 = ((node->m_tree.a_vmax - node->m_tree.a_vmin) + 1) -
	          (CONFIG_MALL_PREFIX_SIZE + CONFIG_MALL_HEAD_SIZE + CONFIG_MALL_TAIL_SIZE);
	if unlikely(result != result2) {
		mallnode_tree_remove(&mall_tree, (uintptr_t)ptr);
		sync_endread(&mall_lock);
		PANIC_SIZEOF_NODES_MISSMATCH(node, ptr, result2, result);
	}
	sync_endread(&mall_lock);
	return result;
}

DEFINE_PUBLIC_ALIAS(kmalloc_noslab, kmalloc);
DEFINE_PUBLIC_ALIAS(kmalloc_noslab_nx, kmalloc_nx);

DECL_END

#ifndef __INTELLISENSE__
#define MALLOC_NX 1
#include "debug-malloc-impl.c.inl"
#include "debug-malloc-impl.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* CONFIG_DEBUG_MALLOC */

#endif /* !GUARD_KERNEL_SRC_MEMORY_DEBUG_MALLOC_C */
