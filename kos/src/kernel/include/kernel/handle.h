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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/pertask.h>

#include <hybrid/limitcore.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <bits/format-printer.h>
#include <kos/io.h>
#include <kos/kernel/handle.h>

#include <stdbool.h>

DECL_BEGIN

/* Management of user-space descriptors for kernel data, here called
 * handles, but referred to as file-descriptors in user-space.
 * The associated user-space data type is `fd_t', which aliases `int',
 * which is why the kernel uses `unsigned int' as its internal
 * descriptor type. */


#ifdef __CC__
struct dirent;
struct stat;
struct aio_multihandle;
struct path;
struct directory_entry;

#ifdef __INTELLISENSE__
DATDEF
#endif /* __INTELLISENSE__ */
struct handle_types {
	/* NOTE: _ALL_ callbacks in here are _always_ defined. (aka. `[1..1]')
	 *       Those that aren't explicitly implemented are aliased to `h_*[HANDLE_TYPE_UNDEFINED]',
	 *       which (when invoked) always throws an `E_NOT_IMPLEMENTED_UNSUPPORTED' exception.
	 *       In other words: To check if a function is implemented, compare it with
	 *                       its `HANDLE_TYPE_UNDEFINED' counterpart!
	 * NOTE: The incref() and decref() functions for `HANDLE_TYPE_UNDEFINED' are no-ops.
	 * NOTE: The reason why type-ids are vectored at this lowest possible level
	 *       is to speed up callback selection by ensuring a constant base address
	 *      (since `handle_type_db' is known at compile-time, and offsets to fields
	 *       are known, also), with the type-index then only having to be multiplied
	 *       by the size of a pointer.
	 *       Thanks to this, the necessary call operation can be encoded as a single
	 *       instruction on X86:
	 *       >> movl   HANDLE_TYPE, %eax
	 *       >> calll  *handle_type_db+h_sync(,%eax,4)
	 */
	char const *h_typename[HANDLE_TYPE_COUNT];
	__BOOL /*NOTHROW*/ (NOBLOCK NONNULL((1)) FCALL *h_tryincref[HANDLE_TYPE_COUNT])(void *__restrict ptr);
	void /*NOTHROW*/ (NOBLOCK NONNULL((1)) FCALL *h_incref[HANDLE_TYPE_COUNT])(void *__restrict ptr);
	void /*NOTHROW*/ (NOBLOCK NONNULL((1)) FCALL *h_decref[HANDLE_TYPE_COUNT])(void *__restrict ptr);
	refcnt_t /*NOTHROW*/ (NOBLOCK WUNUSED NONNULL((1)) FCALL *h_refcnt[HANDLE_TYPE_COUNT])(void const *__restrict ptr);

	/* Basic read/write primitives.
	 * @throws: E_WOULDBLOCK: `IO_NONBLOCK' was given and no data/space was available (at the moment)
	 * @return: 0 : EOF has been reached
	 * @return: * : The amount of read/written bytes (`<= num_bytes') */
	size_t (WUNUSED NONNULL((1)) KCALL *h_read[HANDLE_TYPE_COUNT])(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) /*THROWS(...)*/;
	size_t (WUNUSED NONNULL((1)) KCALL *h_write[HANDLE_TYPE_COUNT])(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) /*THROWS(...)*/;

	/* Position-based read/write primitives.
	 * @throws: * : Same as `h_read' / `h_write'
	 * @return: * : Same as `h_read' / `h_write' */
	size_t (WUNUSED NONNULL((1)) KCALL *h_pread[HANDLE_TYPE_COUNT])(void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) /*THROWS(...)*/;
	size_t (WUNUSED NONNULL((1)) KCALL *h_pwrite[HANDLE_TYPE_COUNT])(void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) /*THROWS(...)*/;

	/* Vector-based read/write primitives.
	 * @throws: * : Same as `h_read' / `h_write'
	 * @return: * : Same as `h_read' / `h_write' */
	size_t (WUNUSED NONNULL((1, 2)) KCALL *h_readv[HANDLE_TYPE_COUNT])(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) /*THROWS(...)*/;
	size_t (WUNUSED NONNULL((1, 2)) KCALL *h_writev[HANDLE_TYPE_COUNT])(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) /*THROWS(...)*/;
	size_t (WUNUSED NONNULL((1, 2)) KCALL *h_preadv[HANDLE_TYPE_COUNT])(void *__restrict ptr, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) /*THROWS(...)*/;
	size_t (WUNUSED NONNULL((1, 2)) KCALL *h_pwritev[HANDLE_TYPE_COUNT])(void *__restrict ptr, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) /*THROWS(...)*/;

	/* Read a directory entry from the given handle.
	 * @throws: E_WOULDBLOCK: `IO_NONBLOCK' was given and no data/space was available (at the moment)
	 * @return: * : The required buffer size for the current entry */
	size_t (WUNUSED NONNULL((1)) KCALL *h_readdir[HANDLE_TYPE_COUNT])(void *__restrict ptr, USER CHECKED struct dirent *buf,
	                                                                  size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode)
			/*THROWS(...)*/;

	/* Seek within the data stream. */
	pos_t (NONNULL((1)) KCALL *h_seek[HANDLE_TYPE_COUNT])(void *__restrict ptr,
	                                                      off_t offset,
	                                                      unsigned int whence)
			/*THROWS(...)*/;

	/* Perform an ioctl() operation.
	 * @throws: E_WOULDBLOCK: `IO_NONBLOCK' was given and no data/space was available (at the moment)
	 * @throws: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND: [...] */
	syscall_slong_t (NONNULL((1)) KCALL *h_ioctl[HANDLE_TYPE_COUNT])(void *__restrict ptr, syscall_ulong_t cmd,
	                                                                 USER UNCHECKED void *arg, iomode_t mode)
			/*THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...)*/;

	/* Change the effective size of the object (s.a. `ftruncate()'). */
	void (NONNULL((1)) KCALL *h_truncate[HANDLE_TYPE_COUNT])(void *__restrict ptr, pos_t new_size)
			/*THROWS(...)*/;

	/* @param: pminoffset: Set to a base offset to-be added to the mmap file-offset when mapping memory.
	 *                     Handle operators are not required to set this value.
	 *                     It is default initialized to `(pos_t)0'
	 * @param: pnumbytes:  Set to the max number of bytes which may be mapped, starting at `*pminoffset'.
	 *                     Handle operators are not required to set this value.
	 *                     It is default initialized to `(pos_t)-1'
	 * @param: pdatablock_fspath: [0..1][1..1] Optional:
	 *                     May be filled in the filesystem path to the mapped object.
	 *                     It is default initialized to `NULL'
	 * @param: pdatablock_fsname: [0..1][1..1] Optional:
	 *                     May be filled in the filesystem name of the mapped object.
	 *                     It is default initialized to `NULL'
	 * @return: * :        The datablock to-be used for mapping this handle into memory (never NULL). */
	REF struct vm_datablock *
	(WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3, 4, 5)) KCALL *
	 h_mmap[HANDLE_TYPE_COUNT])(void *__restrict ptr,
	                            pos_t *__restrict pminoffset,
	                            pos_t *__restrict pnumbytes,
	                            REF struct path **__restrict pdatablock_fspath,
	                            REF struct directory_entry **__restrict pdatablock_fsname)
			/*THROWS(...)*/;

	/* @return: * : The amount of newly allocated bytes. */
	pos_t (NONNULL((1)) KCALL *h_allocate[HANDLE_TYPE_COUNT])(void *__restrict ptr,
	                                                          fallocate_mode_t mode,
	                                                          pos_t start, pos_t length)
			/*THROWS(...)*/;

	/* Synchronize data */
	void (NONNULL((1)) KCALL *h_sync[HANDLE_TYPE_COUNT])(void *__restrict ptr) /*THROWS(...)*/;
	void (NONNULL((1)) KCALL *h_datasync[HANDLE_TYPE_COUNT])(void *__restrict ptr) /*THROWS(...)*/;

	/* Gather stat-information (s.a. `fstat()')
	 * NOTE: The given `result' will _NOT_ have been initialized already! */
	void (NONNULL((1)) KCALL *h_stat[HANDLE_TYPE_COUNT])(void *__restrict ptr,
	                                                     USER CHECKED struct stat *result)
			/*THROWS(...)*/;

	/* @return: * : Set of available signals. */
	poll_mode_t (WUNUSED NONNULL((1)) KCALL *h_poll[HANDLE_TYPE_COUNT])(void *__restrict ptr,
	                                                                    poll_mode_t what)
			/*THROWS(...)*/;

	/* Implement handle control operations (s.a. `<kos/hop/[...].h>')
	 * @throws: E_WOULDBLOCK: `IO_NONBLOCK' was given and no data/space was available (at the moment) */
	syscall_slong_t (NONNULL((1)) KCALL *h_hop[HANDLE_TYPE_COUNT])(void *__restrict ptr, syscall_ulong_t cmd,
	                                                               USER UNCHECKED void *arg, iomode_t mode)
			/*THROWS(...)*/;
}
#ifdef __INTELLISENSE__
	const handle_type_db;
#else /* __INTELLISENSE__ */
;
DATDEF struct handle_types const handle_type_db;
#endif /* !__INTELLISENSE__ */
#endif /* __CC__ */

#ifdef __CC__
struct handle {
	uintptr_half_t h_type; /* Handle type (One of `HANDLE_TYPE_*') */
	iomode_t       h_mode; /* Handle I/O mode (Set of `IO_*'). */
	REF void      *h_data; /* [1..1] Handle data pointer. */
};


/* Returns the type-kind code for `self' (One of `HANDLE_TYPEKIND_*') */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_half_t
NOTHROW(KCALL handle_typekind)(struct handle const *__restrict self);

/* Print the text that should result from `readlink("/proc/[pid]/fd/[fdno]")' */
FUNDEF NONNULL((1, 2)) ssize_t KCALL
handle_print(struct handle const *__restrict self,
             __pformatprinter printer, void *arg);

/* Try to determine the effective data size of the given handle (as returned by `FIOQSIZE')
 * @return: true:  The data size was stored in `*presult'.
 * @return: false: The data size could not be determined. */
FUNDEF NONNULL((1, 2)) __BOOL KCALL
handle_datasize(struct handle const *__restrict self,
                pos_t *__restrict presult);

#ifdef __cplusplus
extern "C++" {
FUNDEF NOBLOCK ATTR_PURE WUNUSED uintptr_half_t NOTHROW(KCALL handle_typekind)(struct handle const &__restrict self) ASMNAME("handle_typekind");
FUNDEF NONNULL((2)) ssize_t KCALL handle_print(struct handle const &__restrict self, __pformatprinter printer, void *arg) ASMNAME("handle_print");
FUNDEF NONNULL((2)) __BOOL KCALL handle_datasize(struct handle const &__restrict self, pos_t *__restrict presult) ASMNAME("handle_datasize");
} /* extern "C++" */
#endif /* __cplusplus */


#define HANDLE_FUNC(self, name) (*handle_type_db.name[(self).h_type])

#define handle_typename(self)                                    handle_type_db.h_typename[(self).h_type]
#define handle_refcnt(self)                                      HANDLE_FUNC(self, h_refcnt)((self).h_data)
#define handle_tryincref(self)                                   HANDLE_FUNC(self, h_tryincref)((self).h_data)
#define handle_incref(self)                                      HANDLE_FUNC(self, h_incref)((self).h_data)
#define handle_decref(self)                                      HANDLE_FUNC(self, h_decref)((self).h_data)
#define handle_read(self, dst, num_bytes)                        HANDLE_FUNC(self, h_read)((self).h_data, dst, num_bytes, (self).h_mode)
#define handle_write(self, src, num_bytes)                       HANDLE_FUNC(self, h_write)((self).h_data, src, num_bytes, (self).h_mode)
#define handle_readf(self, dst, num_bytes, mode)                 HANDLE_FUNC(self, h_read)((self).h_data, dst, num_bytes, mode)
#define handle_writef(self, src, num_bytes, mode)                HANDLE_FUNC(self, h_write)((self).h_data, src, num_bytes, mode)
#define handle_readv(self, dst, num_bytes)                       HANDLE_FUNC(self, h_readv)((self).h_data, dst, num_bytes, (self).h_mode)
#define handle_writev(self, src, num_bytes)                      HANDLE_FUNC(self, h_writev)((self).h_data, src, num_bytes, (self).h_mode)
#define handle_readvf(self, dst, num_bytes, mode)                HANDLE_FUNC(self, h_readv)((self).h_data, dst, num_bytes, mode)
#define handle_writevf(self, src, num_bytes, mode)               HANDLE_FUNC(self, h_writev)((self).h_data, src, num_bytes, mode)
#define handle_pread(self, dst, num_bytes, addr)                 HANDLE_FUNC(self, h_pread)((self).h_data, dst, num_bytes, addr, (self).h_mode)
#define handle_pwrite(self, src, num_bytes, addr)                HANDLE_FUNC(self, h_pwrite)((self).h_data, src, num_bytes, addr, (self).h_mode)
#define handle_preadf(self, dst, num_bytes, addr, mode)          HANDLE_FUNC(self, h_pread)((self).h_data, dst, num_bytes, addr, mode)
#define handle_pwritef(self, src, num_bytes, addr, mode)         HANDLE_FUNC(self, h_pwrite)((self).h_data, src, num_bytes, addr, mode)
#define handle_preadv(self, dst, num_bytes, addr)                HANDLE_FUNC(self, h_preadv)((self).h_data, dst, num_bytes, addr, (self).h_mode)
#define handle_pwritev(self, src, num_bytes, addr)               HANDLE_FUNC(self, h_pwritev)((self).h_data, src, num_bytes, addr, (self).h_mode)
#define handle_preadvf(self, dst, num_bytes, addr, mode)         HANDLE_FUNC(self, h_preadv)((self).h_data, dst, num_bytes, addr, mode)
#define handle_pwritevf(self, src, num_bytes, addr, mode)        HANDLE_FUNC(self, h_pwritev)((self).h_data, src, num_bytes, addr, mode)
#define handle_readdir(self, buf, bufsize, readdir_mode)         HANDLE_FUNC(self, h_readdir)((self).h_data, buf, bufsize, readdir_mode, (self).h_mode)
#define handle_readdirf(self, buf, bufsize, readdir_mode, mode)  HANDLE_FUNC(self, h_readdir)((self).h_data, buf, bufsize, readdir_mode, mode)
#define handle_seek(self, off, whence)                           HANDLE_FUNC(self, h_seek)((self).h_data, off, whence)
#define handle_ioctl(self, cmd, arg)                             HANDLE_FUNC(self, h_ioctl)((self).h_data, cmd, arg, (self).h_mode)
#define handle_ioctlf(self, cmd, arg, flags)                     HANDLE_FUNC(self, h_ioctl)((self).h_data, cmd, arg, flags)
#define handle_truncate(self, new_size)                          HANDLE_FUNC(self, h_truncate)((self).h_data, new_size)
#define handle_mmap(self, pminoffset, pnumbytes, pdatablock_fspath, pdatablock_fsname) HANDLE_FUNC(self, h_mmap)((self).h_data, pminoffset, pnumbytes, pdatablock_fspath, pdatablock_fsname)
#define handle_allocate(self, mode, start, length)               HANDLE_FUNC(self, h_allocate)((self).h_data, mode, start, length)
#define handle_sync(self)                                        HANDLE_FUNC(self, h_sync)((self).h_data)
#define handle_datasync(self)                                    HANDLE_FUNC(self, h_datasync)((self).h_data)
#define handle_stat(self, result)                                HANDLE_FUNC(self, h_stat)((self).h_data, result)
#define handle_poll(self, what)                                  HANDLE_FUNC(self, h_poll)((self).h_data, what)

#ifdef __cplusplus
extern "C++" {

FORCELOCAL ATTR_ARTIFICIAL NOBLOCK struct handle const &
NOTHROW(KCALL incref)(struct handle const &__restrict self) {
	handle_incref(self);
	return self;
}

FORCELOCAL ATTR_ARTIFICIAL NOBLOCK void
NOTHROW(KCALL decref)(struct handle const &__restrict self) {
	handle_decref(self);
}

FORCELOCAL ATTR_ARTIFICIAL NOBLOCK void
NOTHROW(KCALL decref_likely)(struct handle const &__restrict self) {
	handle_decref(self);
}

FORCELOCAL ATTR_ARTIFICIAL NOBLOCK void
NOTHROW(KCALL decref_unlikely)(struct handle const &__restrict self) {
	handle_decref(self);
}

FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) struct handle const *
NOTHROW(KCALL incref)(struct handle const *__restrict self) {
	return &incref(*self);
}

FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL decref)(struct handle const *__restrict self) {
	decref(*self);
}

FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL decref_likely)(struct handle const *__restrict self) {
	decref_likely(*self);
}

FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL decref_unlikely)(struct handle const *__restrict self) {
	decref_unlikely(*self);
}

}
#endif /* __cplusplus */
#endif /* __CC__ */




#ifdef __CC__
struct handle_hashent {
#define HANDLE_HASHENT_SENTINEL_ID ((unsigned int)-1)
	unsigned int   hh_handle_id;    /* The handle ID in question (or `HANDLE_HASHENT_SENTINEL_ID' for sentinel) */
	unsigned int   hh_vector_index; /* [valid_if(hh_handle_id != HANDLE_HASHENT_SENTINEL_ID)]
	                                 * Index into `hm_vector', where the associated handle is mapped.
	                                 * NOTE: Set to `(unsigned int)-1' when deleted. */
};
struct handle_manager {
	WEAK refcnt_t        hm_refcnt;   /* Reference counter. */
	struct atomic_rwlock hm_lock;     /* Lock for this handle manager's control structures. */
	unsigned int         hm_cntlimit; /* [lock(hm_lock)] The max number of handles which may be bound.
	                                   * NOTE: May not be set to `HANDLE_HASHENT_SENTINEL_ID'! */
	unsigned int         hm_maxlimit; /* [lock(hm_lock)] The max allowed handle number which may be used.
	                                   * NOTE: May not be set to `HANDLE_HASHENT_SENTINEL_ID'! */
	unsigned int         hm_count;    /* [lock(hm_lock)] Number of handles currently in use. */
	unsigned int         hm_minfree;  /* [lock(hm_lock)] Lowest handle index that is potentially unused.
	                                   * When searching for a new, unused handle, start searching here. */
	unsigned int         hm_mode;     /* [lock(hm_lock)] Handle manager operations mode (one of `HANDLE_MANAGER_MODE_*'). */
#define HANDLE_MANAGER_MODE_LINEAR     0x0000 /* Handles are indexed linearly. */
#define HANDLE_MANAGER_MODE_HASHVECTOR 0x0001 /* Handles are indexed via hash-vector indirection. */
	unsigned int         hm_clofork_count; /* [lock(hm_lock)] Number of handles with the `IO_CLOFORK' flag set. */
	unsigned int         hm_cloexec_count; /* [lock(hm_lock)] Number of handles with the `IO_CLOEXEC' flag set. */
	union {
		struct {
			unsigned int   hm_alloc;  /* [lock(hm_lock)] Allocated number of handles. */
			struct handle *hm_vector; /* [0..hm_alloc][owned] Vector of handles. (index == handle-number) */
		}                hm_linear;   /* HANDLE_MANAGER_MODE_LINEAR */
		struct {
			unsigned int   hm_alloc;  /* [lock(hm_lock)] Allocated size of `hm_vector'. */
			struct handle *hm_vector; /* [0..hm_alloc][owned] Vector of handles. (index == hm_hashvec[*]) */
			struct handle_hashent
			              *hm_hashvec;/* [lock(hm_lock)][1..hm_hashmsk+1][owned] Hash-vector for translating
			                           * handle IDs from `fd_t' into an index into `hm_vector'. */
			unsigned int   hm_hashmsk;/* [lock(hm_lock)] Hash-mask for `hm_hashvec'. */
			unsigned int   hm_hashuse;/* [lock(hm_lock)] Number of used handle_hashent (i.e. ones with
			                           * `hh_handle_id != HANDLE_HASHENT_SENTINEL_ID').
			                           * Note that this is very similar to `hm_count', but includes handles
			                           * that have been deleted (i.e. `hh_vector_index == (unsigned int)-1') */
			unsigned int   hm_vecfree;/* [lock(hm_lock)] Lowest index in `hm_vector' that may contain an unused slot. */
#define handle_manager_hashnext(i, perturb) ((i) = (((i) << 2) + (i) + (perturb) + 1), (perturb) >>= 5)
		}                hm_hashvector; /* HANDLE_MANAGER_MODE_HASHVECTOR */
	};
};

/* Destroy the given handle manager. */
FUNDEF NOBLOCK void
NOTHROW(KCALL handle_manager_destroy)(struct handle_manager *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct handle_manager, hm_refcnt, handle_manager_destroy)

/* Allocate a new or / copy the given (which won't
 * copy any `IO_CLOFORK' handle) handle manager */
FUNDEF ATTR_MALLOC ATTR_RETNONNULL REF struct handle_manager *KCALL
handle_manager_alloc(void) THROWS(E_BADALLOC, E_WOULDBLOCK);
FUNDEF ATTR_MALLOC ATTR_RETNONNULL REF struct handle_manager *KCALL
handle_manager_clone(struct handle_manager *__restrict self)
		THROWS(E_BADALLOC, E_WOULDBLOCK);

/* The handle manager of the kernel itself. */
DATDEF struct handle_manager handle_manager_kernel;

/* [1..1][lock(read(THIS_TASK || INTERN(lock)),
 *             write(THIS_TASK && INTERN(lock)))]
 * Handle manager of the calling thread. */
DATDEF ATTR_PERTASK struct handle_manager *this_handle_manager;
#define THIS_HANDLE_MANAGER    PERTASK_GET(this_handle_manager)

/* Return the handle manager of the given thread. */
FUNDEF NOBLOCK WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct handle_manager *
NOTHROW(FCALL task_gethandlemanager)(struct task *__restrict thread);

/* Exchange the handle manager of the calling thread (and return the old one). */
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct handle_manager *FCALL
task_sethandlemanager(struct handle_manager *__restrict newman) THROWS(E_WOULDBLOCK);


/* Close all handles with the `IO_FCLOEXEC' flag set.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked. */
FUNDEF NONNULL((1)) void FCALL
handle_manager_cloexec(struct handle_manager *__restrict self) THROWS(E_WOULDBLOCK);

/* Try to close the handle associated with `fd'.
 * @return: true:  The handle under `fd' was closed.
 * @return: false: No handle was associated with `fd'.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked. */
FUNDEF __BOOL FCALL
handle_tryclose(unsigned int fd) THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((2)) __BOOL FCALL
handle_tryclose_nosym(unsigned int fd,
                      struct handle_manager *__restrict self)
		THROWS(E_WOULDBLOCK);

/* Same as `handle_tryclose()', but throw an error if the given `fd' is invalid */
FUNDEF void FCALL handle_close(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);

/* Same as `handle_tryclose_nosym()', but throw an error if the given `fd' is invalid */
FUNDEF NONNULL((2)) void FCALL
handle_close_nosym(unsigned int fd,
                   struct handle_manager *__restrict self)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);

/* Close all open file handles `>= fd' and return how many were actually closed.
 * If nothing was closed at all (i.e. what would be `return == 0'), then this
 * function returns by throwing an `E_INVALID_HANDLE_FILE' (-EBADF) exception. */
FUNDEF NONNULL((2)) unsigned int FCALL
handle_closefrom_nosym(unsigned int startfd,
                       struct handle_manager *__restrict self)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);

/* Return the next valid FD that is `>= startfd'
 * If no such FD exists, throw an `E_INVALID_HANDLE_FILE' exception */
FUNDEF NONNULL((2)) unsigned int FCALL
handle_nextfd(unsigned int startfd,
              struct handle_manager *__restrict self)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);


/* Modify the I/O-flags of a given file handle
 * The new I/O flags are calculated as `(old_flags & mask) | flag'
 * @return: * :  The handle's old I/O-flags */
FUNDEF NONNULL((1)) iomode_t FCALL
handle_stflags(struct handle_manager *__restrict self,
               unsigned int fd, iomode_t mask, iomode_t flag)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);


/* Add the given handle to the handle manager and
 * return the handle number of where it was placed.
 * @throw: E_BADALLOC: Insufficient kernel memory to allocate more handle slots
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS: Too many open handles
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_RANGE: Too many open handles
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked */
FUNDEF NONNULL((1, 2)) unsigned int FCALL
handle_install(struct handle_manager *__restrict self,
               struct handle const *__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE);

/* Similar to `handle_put()', but place the handle in a
 * descriptor slot that is greater than, or equal to `hint'.
 * @throw: E_BADALLOC: Insufficient kernel memory to allocate more handle slots
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS: Too many open handles
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_RANGE: `hint' is outside the allowed handle range.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked */
FUNDEF NONNULL((1, 3)) unsigned int FCALL
handle_installat(struct handle_manager *__restrict self,
                 unsigned int hint,
                 struct handle const *__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE);

/* Place the given handle into the specified handle slot `dst_fd'.
 * @throw: E_BADALLOC: Insufficient kernel memory to allocate more handle slots
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS: Too many open handles
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_RANGE: `dst_fd' is outside the allowed handle range.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked */
FUNDEF NONNULL((1, 3)) void FCALL
handle_installinto(struct handle_manager *__restrict self,
                   unsigned int dst_fd,
                   struct handle const *__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE);

/* Same as `handle_installinto()', but return the old handle
 * (or a HANDLE_TYPE_UNDEFINED) previously bound to that slot. */
FUNDEF WUNUSED NONNULL((1, 3)) REF struct handle FCALL
handle_installxchg(struct handle_manager *__restrict self,
                   unsigned int dst_fd,
                   struct handle const *__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE);



struct hop_openfd;
/* Do everything required to install a handle via a open openfd
 * command data packet that has been passed via user-space.
 * Note that `data' is an UNCHECKED user pointer! */
FUNDEF NONNULL((2)) unsigned int FCALL
handle_installhop(USER UNCHECKED struct hop_openfd *data,
                  struct handle const *__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE,
		       E_SEGFAULT, E_INVALID_ARGUMENT);


/* Same as `handle_installinto()', but allow `dst_fd' to be a writable, symbolic handle.
 * @throw: E_BADALLOC: Insufficient kernel memory to allocate more handle slots
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS: Too many open handles
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_RANGE: `dst_fd' is outside the allowed handle range.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked */
FUNDEF NONNULL((2)) void FCALL
handle_installinto_sym(unsigned int dst_fd,
                       struct handle const *__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE);

#ifdef __cplusplus
extern "C++" {
FUNDEF NONNULL((1)) unsigned int FCALL
handle_install(struct handle_manager *__restrict self,
               struct handle const &__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE)
		ASMNAME("handle_install");
FUNDEF NONNULL((1)) unsigned int FCALL
handle_installat(struct handle_manager *__restrict self,
                 unsigned int hint,
                 struct handle const &__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE)
		ASMNAME("handle_installat");
FUNDEF NONNULL((1)) void FCALL
handle_installinto(struct handle_manager *__restrict self,
                   unsigned int dst_fd,
                   struct handle const &__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE)
		ASMNAME("handle_installinto");
FUNDEF WUNUSED NONNULL((1)) REF struct handle FCALL
handle_installxchg(struct handle_manager *__restrict self,
                   unsigned int dst_fd,
                   struct handle const &__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE)
		ASMNAME("handle_installxchg");
FUNDEF unsigned int FCALL
handle_installhop(USER UNCHECKED struct hop_openfd *data,
                  struct handle const &__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE,
		       E_SEGFAULT, E_INVALID_ARGUMENT)
		ASMNAME("handle_installhop");
FUNDEF void FCALL
handle_installinto_sym(unsigned int dst_fd,
                       struct handle const &__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE)
		ASMNAME("handle_installinto_sym");
} /* extern "C++" */
#endif /* __cplusplus */


/* The kernel-space equivalent of the user-space `fcntl()' function.
 * @param: cmd: One of `F_*' from <kos/io.h> */
FUNDEF NONNULL((1)) syscall_ulong_t KCALL
handle_fcntl(struct handle_manager *__restrict self,
             unsigned int fd, syscall_ulong_t cmd,
             UNCHECKED USER void *arg)
		THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE,
		       E_WOULDBLOCK, E_BADALLOC, ...);


/* Lookup a given fd-number and return the associated handle.
 * NOTE: When `fd' doesn't refer to a valid handle, the returned
 *       handle has its type set to `HANDLE_TYPE_UNDEFINED'.
 * NOTE: This function also handles symbolic file descriptors!
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked */
FUNDEF WUNUSED REF struct handle FCALL
handle_trylookup(struct handle_manager *__restrict self,
                 unsigned int fd)
		THROWS(E_WOULDBLOCK);

/* Same as `handle_trylookup()', but throw an error when `fd' is invalid. */
FUNDEF WUNUSED REF struct handle FCALL
handle_lookup(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);

FUNDEF WUNUSED REF struct handle FCALL
handle_lookupin(unsigned int fd, struct handle_manager *__restrict self)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);

FUNDEF WUNUSED bool FCALL
handle_existsin(unsigned int fd, struct handle_manager *__restrict self)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);

/* Same as `handle_lookup()', but don't allow for symbolic handles. */
FUNDEF WUNUSED REF struct handle FCALL
handle_lookup_nosym(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);


struct inode;
struct regular_node;
struct directory_node;
struct directory_entry;
struct vm_datablock;
struct superblock;
struct path;
struct taskpid;
struct task;
struct vm;
struct fs;
struct vfs;
struct pipe;
struct driver;
struct pidns;
struct socket;

/* Directly translate handlers to references to objects of specific types. */
FUNDEF WUNUSED ATTR_RETNONNULL REF struct inode *FCALL handle_get_inode(unsigned int fd) THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL REF struct regular_node *FCALL handle_get_regular_node(unsigned int fd) THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL REF struct directory_node *FCALL handle_get_directory_node(unsigned int fd) THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL REF struct directory_entry *FCALL handle_get_directory_entry(unsigned int fd) THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL REF struct vm_datablock *FCALL handle_get_datablock(unsigned int fd) THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL REF struct superblock *FCALL handle_get_superblock(unsigned int fd) THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL REF struct superblock *FCALL handle_get_superblock_relaxed(unsigned int fd) THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL REF struct path *FCALL handle_get_path(unsigned int fd) THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL REF struct taskpid *FCALL handle_get_taskpid(unsigned int fd) THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE);
/* @throw: E_PROCESS_EXITED: `fd' belongs to a task that is no longer allocated. */
FUNDEF WUNUSED ATTR_RETNONNULL REF struct task *FCALL handle_get_task(unsigned int fd) THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE, E_PROCESS_EXITED);
FUNDEF WUNUSED ATTR_RETNONNULL REF struct vm *FCALL handle_get_vm(unsigned int fd) THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL REF struct fs *FCALL handle_get_fs(unsigned int fd) THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL REF struct vfs *FCALL handle_get_vfs(unsigned int fd) THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL REF struct pipe *FCALL handle_get_pipe(unsigned int fd) THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL REF struct driver *FCALL handle_get_driver(unsigned int fd) THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL REF struct pidns *FCALL handle_get_pidns(unsigned int fd) THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL REF struct socket *FCALL handle_get_socket(unsigned int fd) THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE);

/* Try to case the given handle `self' into `wanted_type', and return a
 * reference to a handle-compatible object with type `wanted_type'. If such
 * a cast is impossible, an `E_INVALID_HANDLE_FILETYPE' error is thrown.
 * NOTE: This function also inherits a reference to `self' (unless an exception is thrown) */
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF void *FCALL
handle_as(REF struct handle const *__restrict self, uintptr_half_t wanted_type)
		THROWS(E_INVALID_HANDLE_FILETYPE);

FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct inode *FCALL handle_as_inode(REF struct handle const *__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct regular_node *FCALL handle_as_regular_node(REF struct handle const *__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct directory_node *FCALL handle_as_directory_node(REF struct handle const *__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct directory_entry *FCALL handle_as_directory_entry(REF struct handle const *__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct vm_datablock *FCALL handle_as_datablock(REF struct handle const *__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct superblock *FCALL handle_as_superblock(REF struct handle const *__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct superblock *FCALL handle_as_superblock_relaxed(REF struct handle const *__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct path *FCALL handle_as_path(REF struct handle const *__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct taskpid *FCALL handle_as_taskpid(REF struct handle const *__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE);
/* @throw: E_PROCESS_EXITED: `fd' belongs to a task that is no longer allocated. */
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct task *FCALL handle_as_task(REF struct handle const *__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE, E_PROCESS_EXITED);
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct vm *FCALL handle_as_vm(REF struct handle const *__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct fs *FCALL handle_as_fs(REF struct handle const *__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct vfs *FCALL handle_as_vfs(REF struct handle const *__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct pipe *FCALL handle_as_pipe(REF struct handle const *__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct driver *FCALL handle_as_driver(REF struct handle const *__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct pidns *FCALL handle_as_pidns(REF struct handle const *__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE);
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct socket *FCALL handle_as_socket(REF struct handle const *__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE);

#if defined(__cplusplus) && !defined(NO_CXX_HANDLE_AS_OVERLOADS)
extern "C++" {
FUNDEF WUNUSED ATTR_RETNONNULL REF void *FCALL
handle_as(REF struct handle const &__restrict self, uintptr_half_t wanted_type)
		THROWS(E_INVALID_HANDLE_FILETYPE)
		ASMNAME("handle_as");
FUNDEF WUNUSED ATTR_RETNONNULL REF struct inode *FCALL handle_as_inode(REF struct handle const &__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE) ASMNAME("handle_as_inode");
FUNDEF WUNUSED ATTR_RETNONNULL REF struct regular_node *FCALL handle_as_regular_node(REF struct handle const &__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE) ASMNAME("handle_as_regular_node");
FUNDEF WUNUSED ATTR_RETNONNULL REF struct directory_node *FCALL handle_as_directory_node(REF struct handle const &__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE) ASMNAME("handle_as_directory_node");
FUNDEF WUNUSED ATTR_RETNONNULL REF struct directory_entry *FCALL handle_as_directory_entry(REF struct handle const &__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE) ASMNAME("handle_as_directory_entry");
FUNDEF WUNUSED ATTR_RETNONNULL REF struct vm_datablock *FCALL handle_as_datablock(REF struct handle const &__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE) ASMNAME("handle_as_datablock");
FUNDEF WUNUSED ATTR_RETNONNULL REF struct superblock *FCALL handle_as_superblock(REF struct handle const &__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE) ASMNAME("handle_as_superblock");
FUNDEF WUNUSED ATTR_RETNONNULL REF struct superblock *FCALL handle_as_superblock_relaxed(REF struct handle const &__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE) ASMNAME("handle_as_superblock_relaxed");
FUNDEF WUNUSED ATTR_RETNONNULL REF struct path *FCALL handle_as_path(REF struct handle const &__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE) ASMNAME("handle_as_path");
FUNDEF WUNUSED ATTR_RETNONNULL REF struct taskpid *FCALL handle_as_taskpid(REF struct handle const &__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE) ASMNAME("handle_as_taskpid");
FUNDEF WUNUSED ATTR_RETNONNULL REF struct task *FCALL handle_as_task(REF struct handle const &__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE, E_PROCESS_EXITED) ASMNAME("handle_as_task");
FUNDEF WUNUSED ATTR_RETNONNULL REF struct vm *FCALL handle_as_vm(REF struct handle const &__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE) ASMNAME("handle_as_vm");
FUNDEF WUNUSED ATTR_RETNONNULL REF struct fs *FCALL handle_as_fs(REF struct handle const &__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE) ASMNAME("handle_as_fs");
FUNDEF WUNUSED ATTR_RETNONNULL REF struct vfs *FCALL handle_as_vfs(REF struct handle const &__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE) ASMNAME("handle_as_vfs");
FUNDEF WUNUSED ATTR_RETNONNULL REF struct pipe *FCALL handle_as_pipe(REF struct handle const &__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE) ASMNAME("handle_as_pipe");
FUNDEF WUNUSED ATTR_RETNONNULL REF struct driver *FCALL handle_as_driver(REF struct handle const &__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE) ASMNAME("handle_as_driver");
FUNDEF WUNUSED ATTR_RETNONNULL REF struct pidns *FCALL handle_as_pidns(REF struct handle const &__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE) ASMNAME("handle_as_pidns");
FUNDEF WUNUSED ATTR_RETNONNULL REF struct socket *FCALL handle_as_socket(REF struct handle const &__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE) ASMNAME("handle_as_socket");
} /* extern "C++" */
#endif /* __cplusplus && !NO_CXX_HANDLE_AS_OVERLOADS */


#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_H */
