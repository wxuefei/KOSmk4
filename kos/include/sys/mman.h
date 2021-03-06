/* HASH CRC-32:0x72575fce */
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
#ifndef _SYS_MMAN_H
#define _SYS_MMAN_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */


#include <features.h>
#include <asm/mman.h>
#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __CC__
#ifndef __off_t_defined
#define __off_t_defined 1
typedef __typedef_off_t off_t;
#endif /* !__off_t_defined */

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __mode_t_defined
#define __mode_t_defined 1
typedef __mode_t mode_t; /* INode type (Set of `S_*' from `<fcntl.h>' or `<sys/stat.h>') */
#endif /* !__mode_t_defined */
#endif /* __CC__ */


/* Data cannot be accessed. */
#ifdef __PROT_NONE
#define PROT_NONE __PROT_NONE
#endif /* __PROT_NONE */

/* Data can be executed. */
#ifdef __PROT_EXEC
#define PROT_EXEC __PROT_EXEC
#endif /* __PROT_EXEC */

/* Data can be written. */
#ifdef __PROT_WRITE
#define PROT_WRITE __PROT_WRITE
#endif /* __PROT_WRITE */

/* Data can be read. */
#ifdef __PROT_READ
#define PROT_READ __PROT_READ
#endif /* __PROT_READ */

/* Ignored... */
#ifdef __PROT_SEM
#define PROT_SEM __PROT_SEM
#endif /* __PROT_SEM */


#if defined(__KOS__) && defined(__USE_KOS)
/* Unmap the region within the when cloning a VM (`CLONE_VM'). */
#ifdef __PROT_LOOSE
#define PROT_LOOSE __PROT_LOOSE
#endif /* __PROT_LOOSE */

/* Changes are shared, even after the VM was cloned (`CLONE_VM').
 * NOTE: Same as the `MAP_SHARED' map flag, but
 *       can be set like any other protection. */
#ifdef __PROT_SHARED
#define PROT_SHARED __PROT_SHARED
#endif /* __PROT_SHARED */

#ifdef __USE_KOS_KERNEL
/* Map memory as inaccessible to user-space.
 * WARNING: Not fully enforced for addresses within user-memory. */
#ifdef __PROT_NOUSER
#define PROT_NOUSER __PROT_NOUSER
#endif /* __PROT_NOUSER */

/* Unset whenever user-space re-maps a page as writable. - Cannot be removed.
 * NOTE: This flag is used to prevent rootfork() from working
 *       when called from an otherwise read-only module after
 *       some portion of the section containing the root-fork
 *       system call has been mapped as writable.
 *    >> rootfork() fails when any page in the calling section (.text)
 *       isn't part of a root-module, isn't fully mapped, was
 *       re-mapped somewhere else, or been made writable at any point. */
#ifdef __PROT_CLEAN
#define PROT_CLEAN __PROT_CLEAN
#endif /* __PROT_CLEAN */

#endif /* __USE_KOS_KERNEL */
#endif /* __USE_KOS */

#ifdef __USE_KOS_KERNEL
 /* Mask of flags accessible from user-space. */
#ifdef __PROT_MASK
#define PROT_MASK __PROT_MASK
#endif /* __PROT_MASK */
#endif /* __USE_KOS_KERNEL */



#ifdef __USE_KOS
/* Use sharing behavior specified by `PROT_SHARED'. */
#ifdef __MAP_AUTOMATIC
#define MAP_AUTOMATIC __MAP_AUTOMATIC
#endif /* __MAP_AUTOMATIC */
#endif /* __USE_KOS */

/* Share changes. */
#ifdef __MAP_SHARED
#define MAP_SHARED __MAP_SHARED
#endif /* __MAP_SHARED */

/* Changes are private. */
#ifdef __MAP_PRIVATE
#define MAP_PRIVATE __MAP_PRIVATE
#endif /* __MAP_PRIVATE */

/* Interpret addr exactly. */
#ifdef __MAP_FIXED
#define MAP_FIXED __MAP_FIXED
#endif /* __MAP_FIXED */


#ifdef __USE_MISC
/* Mask for type of mapping. */
#ifdef __MAP_TYPE
#define MAP_TYPE __MAP_TYPE
#endif /* __MAP_TYPE */

/* Do use a file. */
#ifdef __MAP_FILE
#define MAP_FILE __MAP_FILE
#endif /* __MAP_FILE */

/* Don't use a file. */
#ifdef __MAP_ANON
#define MAP_ANONYMOUS __MAP_ANON
#endif /* !__MAP_ANON */
#endif /* __USE_MISC */

/* Don't use a file. */
#ifdef __MAP_ANON
#define MAP_ANON __MAP_ANON
#endif /* __MAP_ANON */


/* Other flags. */
#ifdef __USE_MISC
/* Only give out 32-bit addresses. */
#ifdef __MAP_32BIT
#define MAP_32BIT __MAP_32BIT
#endif /* __MAP_32BIT */
#endif /* __USE_MISC */



#ifdef __USE_MISC
/* Stack-like segment. */
#ifdef __MAP_GROWSDOWN
#define MAP_GROWSDOWN __MAP_GROWSDOWN
#endif /* __MAP_GROWSDOWN */

/* Stack-like segment growing upwards. */
#ifdef __MAP_GROWSUP
#define MAP_GROWSUP __MAP_GROWSUP
#endif /* __MAP_GROWSUP */

/* Ignored. */
#ifdef __MAP_DENYWRITE
#define MAP_DENYWRITE __MAP_DENYWRITE
#endif /* __MAP_DENYWRITE */

/* Ignored. */
#ifdef __MAP_EXECUTABLE
#define MAP_EXECUTABLE __MAP_EXECUTABLE
#endif /* __MAP_EXECUTABLE */

/* Lock the mapping. */
#ifdef __MAP_LOCKED
#define MAP_LOCKED __MAP_LOCKED
#endif /* __MAP_LOCKED */

/* Don't check for reservations. */
#ifdef __MAP_NORESERVE
#define MAP_NORESERVE __MAP_NORESERVE
#endif /* __MAP_NORESERVE */

/* Populate (prefault) pagetables. */
#ifdef __MAP_POPULATE
#define MAP_POPULATE __MAP_POPULATE
#endif /* __MAP_POPULATE */

/* Do not block on IO. */
#ifdef __MAP_NONBLOCK
#define MAP_NONBLOCK __MAP_NONBLOCK
#endif /* __MAP_NONBLOCK */

/* Allocation is for a stack.
 * NOTE: KOS uses this flag to determine where
 *       automatic memory mappings are allocated at. */
#ifdef __MAP_STACK
#define MAP_STACK __MAP_STACK
#endif /* __MAP_STACK */

/* XXX: Implement me? */
#ifdef __MAP_SYNC
#define MAP_SYNC __MAP_SYNC
#endif /* __MAP_SYNC */


/* Create huge page mapping. */
#ifdef __MAP_HUGETLB
#define MAP_HUGETLB __MAP_HUGETLB
#endif /* __MAP_HUGETLB */
#ifdef __MAP_HUGE_SHIFT
#define MAP_HUGE_SHIFT __MAP_HUGE_SHIFT
#endif /* __MAP_HUGE_SHIFT */
#ifdef __MAP_HUGE_MASK
#define MAP_HUGE_MASK __MAP_HUGE_MASK
#endif /* __MAP_HUGE_MASK */


/* For anonymous mmap, memory could be uninitialized.
 * NOTE: Implied for physical mappings.
 * NOTE: The kernel may initialize memory randomly in sandboxed threads. */
#ifdef __MAP_UNINITIALIZED
#define MAP_UNINITIALIZED __MAP_UNINITIALIZED
#endif /* __MAP_UNINITIALIZED */

#ifdef __USE_KOS_KERNEL
/* Don't actually map memory, but test the waters of a memory
 * location hasn't already been mapped, or locate a suitably
 * large free memory range.
 * This flag is usually followed by another call that sets
 * the `MAP_DONT_OVERRIDE' flag. */
#ifdef __MAP_DONT_MAP
#define MAP_DONT_MAP __MAP_DONT_MAP
#endif /* __MAP_DONT_MAP */

/* Don't override existing mappings when `MAP_FIXED' is passed.
 * Instead, TODO:ERROR. */
#ifdef __MAP_DONT_OVERRIDE
#define MAP_DONT_OVERRIDE __MAP_DONT_OVERRIDE
#endif /* __MAP_DONT_OVERRIDE */

/* The `OFFSET' argument of MMAP is actually a pointer to the 64-bit
 * unsigned integer that should actually be used as offset. */
#ifdef __MAP_OFFSET64_POINTER
#define MAP_OFFSET64_POINTER __MAP_OFFSET64_POINTER
#endif /* __MAP_OFFSET64_POINTER */
#endif /* __USE_KOS_KERNEL */
#endif /* __USE_MISC */


/************************************************************************/
/* Error return value for `mmap()'                                      */
/************************************************************************/
#ifdef __MAP_FAILED
#define MAP_FAILED __MAP_FAILED
#endif /* __MAP_FAILED */


/* Extended flags for use with `mprotect()' */

/* Same as `MAP_GROWSDOWN', but may be used with `mprotect()' */
#ifdef __PROT_GROWSDOWN
#define PROT_GROWSDOWN __PROT_GROWSDOWN
#endif /* __PROT_GROWSDOWN */

/* Same as `MAP_GROWSUP', but may be used with `mprotect()' */
#ifdef __PROT_GROWSUP
#define PROT_GROWSUP __PROT_GROWSUP
#endif /* __PROT_GROWSUP */


/************************************************************************/
/* Flags accepted by `msync()'.                                         */
/************************************************************************/

/* Perform the operation asynchronously. */
#ifdef __MS_ASYNC
#define MS_ASYNC __MS_ASYNC
#endif /* __MS_ASYNC */

/* Invalidate caches. */
#ifdef __MS_INVALIDATE
#define MS_INVALIDATE __MS_INVALIDATE
#endif /* __MS_INVALIDATE */

/* Wait for the sync to finish. */
#ifdef __MS_SYNC
#define MS_SYNC __MS_SYNC
#endif /* __MS_SYNC */


/************************************************************************/
/* Flags for 'mremap'.                                                  */
/************************************************************************/
#ifdef __USE_GNU
/* Allowed to move to a different location */
#ifdef __MREMAP_MAYMOVE
#define MREMAP_MAYMOVE __MREMAP_MAYMOVE
#endif /* __MREMAP_MAYMOVE */

/* Fixed target address */
#ifdef __MREMAP_FIXED
#define MREMAP_FIXED __MREMAP_FIXED
#endif /* __MREMAP_FIXED */
#endif /* __USE_GNU */


/* DISCLAIMER: Documentation strings for MADV_*, POSIX_MADV_* and MCL_* were
 *             taken from glibc /usr/include/i386-linux-gnu/bits/mman-linux.h */
/* Definitions for POSIX memory map interface.  Linux generic version.
   Copyright (C) 2001-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


/************************************************************************/
/* Advice to `madvise(2)'.                                              */
/************************************************************************/
#ifdef __USE_MISC
/* No further special treatment. */
#ifdef __MADV_NORMAL
#define MADV_NORMAL __MADV_NORMAL
#endif /* __MADV_NORMAL */

/* Expect random page references. */
#ifdef __MADV_RANDOM
#define MADV_RANDOM __MADV_RANDOM
#endif /* __MADV_RANDOM */

/* Expect sequential page references. */
#ifdef __MADV_SEQUENTIAL
#define MADV_SEQUENTIAL __MADV_SEQUENTIAL
#endif /* __MADV_SEQUENTIAL */

/* Will need these pages. */
#ifdef __MADV_WILLNEED
#define MADV_WILLNEED __MADV_WILLNEED
#endif /* __MADV_WILLNEED */

/* Don't need these pages. */
#ifdef __MADV_DONTNEED
#define MADV_DONTNEED __MADV_DONTNEED
#endif /* __MADV_DONTNEED */

/* Remove these pages and resources. */
#ifdef __MADV_REMOVE
#define MADV_REMOVE __MADV_REMOVE
#endif /* __MADV_REMOVE */

/* Do not inherit across fork. */
#ifdef __MADV_DONTFORK
#define MADV_DONTFORK __MADV_DONTFORK
#endif /* __MADV_DONTFORK */

/* Do inherit across fork. */
#ifdef __MADV_DOFORK
#define MADV_DOFORK __MADV_DOFORK
#endif /* __MADV_DOFORK */

/* KSM may merge identical pages. */
#ifdef __MADV_MERGEABLE
#define MADV_MERGEABLE __MADV_MERGEABLE
#endif /* __MADV_MERGEABLE */

/* KSM may not merge identical pages. */
#ifdef __MADV_UNMERGEABLE
#define MADV_UNMERGEABLE __MADV_UNMERGEABLE
#endif /* __MADV_UNMERGEABLE */

/* Worth backing with hugepages. */
#ifdef __MADV_HUGEPAGE
#define MADV_HUGEPAGE __MADV_HUGEPAGE
#endif /* __MADV_HUGEPAGE */

/* Not worth backing with hugepages. */
#ifdef __MADV_NOHUGEPAGE
#define MADV_NOHUGEPAGE __MADV_NOHUGEPAGE
#endif /* __MADV_NOHUGEPAGE */

/* Explicity exclude from the core dump, overrides the coredump filter bits. */
#ifdef __MADV_DONTDUMP
#define MADV_DONTDUMP __MADV_DONTDUMP
#endif /* __MADV_DONTDUMP */

/* Clear the MADV_DONTDUMP flag. */
#ifdef __MADV_DODUMP
#define MADV_DODUMP __MADV_DODUMP
#endif /* __MADV_DODUMP */

/* Poison a page for testing. */
#ifdef __MADV_HWPOISON
#define MADV_HWPOISON __MADV_HWPOISON
#endif /* __MADV_HWPOISON */
#endif /* __USE_MISC */


/************************************************************************/
/* The POSIX people had to invent similar names for the same things.    */
/************************************************************************/
#ifdef __USE_XOPEN2K
/* No further special treatment. */
#ifdef __POSIX_MADV_NORMAL
#define POSIX_MADV_NORMAL __POSIX_MADV_NORMAL
#endif /* __POSIX_MADV_NORMAL */

/* Expect random page references. */
#ifdef __POSIX_MADV_RANDOM
#define POSIX_MADV_RANDOM __POSIX_MADV_RANDOM
#endif /* __POSIX_MADV_RANDOM */

/* Expect sequential page references. */
#ifdef __POSIX_MADV_SEQUENTIAL
#define POSIX_MADV_SEQUENTIAL __POSIX_MADV_SEQUENTIAL
#endif /* __POSIX_MADV_SEQUENTIAL */

/* Will need these pages. */
#ifdef __POSIX_MADV_WILLNEED
#define POSIX_MADV_WILLNEED __POSIX_MADV_WILLNEED
#endif /* __POSIX_MADV_WILLNEED */

/* Don't need these pages. */
#ifdef __POSIX_MADV_DONTNEED
#define POSIX_MADV_DONTNEED __POSIX_MADV_DONTNEED
#endif /* __POSIX_MADV_DONTNEED */
#endif /* __USE_XOPEN2K */


/************************************************************************/
/* Flags for `mlockall()'.                                              */
/************************************************************************/
#ifndef MCL_CURRENT
/* Lock all currently mapped pages. */
#ifdef __MCL_CURRENT
#define MCL_CURRENT __MCL_CURRENT
#endif /* __MCL_CURRENT */

/* Lock all additions to address space. */
#ifdef __MCL_FUTURE
#define MCL_FUTURE __MCL_FUTURE
#endif /* __MCL_FUTURE */

/* Lock all pages that are faulted in. */
#ifdef __MCL_ONFAULT
#define MCL_ONFAULT __MCL_ONFAULT
#endif /* __MCL_ONFAULT */
#endif /* !MCL_CURRENT */


/************************************************************************/
/* Flags for `memfd_create()'                                           */
/************************************************************************/

/* Close-on-exec */
#ifdef __MFD_CLOEXEC
#define MFD_CLOEXEC __MFD_CLOEXEC
#endif /* __MFD_CLOEXEC */

/* Allow use of `F_ADD_SEALS' and `F_GET_SEALS' (when not given, `F_SEAL_SEAL' is set on creation) */
#ifdef __MFD_ALLOW_SEALING
#define MFD_ALLOW_SEALING __MFD_ALLOW_SEALING
#endif /* __MFD_ALLOW_SEALING */

/* ... */
#ifdef __MFD_HUGETLB
#define MFD_HUGETLB __MFD_HUGETLB
#endif /* __MFD_HUGETLB */


/************************************************************************/
/* Flags for `mlock2()'                                                 */
/************************************************************************/

/* ... */
#ifdef __MLOCK_ONFAULT
#define MLOCK_ONFAULT __MLOCK_ONFAULT
#endif /* __MLOCK_ONFAULT */


/************************************************************************/
/* `ACCESS_RIGHTS' for `pkey_alloc()' and `pkey_set()'                  */
/************************************************************************/

/* ... */
#ifdef __PKEY_DISABLE_ACCESS
#define PKEY_DISABLE_ACCESS __PKEY_DISABLE_ACCESS
#endif /* __PKEY_DISABLE_ACCESS */

/* ... */
#ifdef __PKEY_DISABLE_WRITE
#define PKEY_DISABLE_WRITE __PKEY_DISABLE_WRITE
#endif /* __PKEY_DISABLE_WRITE */



#ifdef __CC__
#if defined(__CRT_HAVE_mmap64) && defined(__USE_FILE_OFFSET64)
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE | MAP_STACK | MAP_SYNC |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_DONT_OVERRIDE' */
__CREDIRECT(__ATTR_WUNUSED,void *,__NOTHROW_NCX,mmap,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __FS_TYPE(off) __offset),mmap64,(__addr,__len,__prot,__flags,__fd,__offset))
#elif defined(__CRT_HAVE_mmap) && !defined(__USE_FILE_OFFSET64)
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE | MAP_STACK | MAP_SYNC |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_DONT_OVERRIDE' */
__CDECLARE(__ATTR_WUNUSED,void *,__NOTHROW_NCX,mmap,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __FS_TYPE(off) __offset),(__addr,__len,__prot,__flags,__fd,__offset))
#elif defined(__CRT_HAVE_mmap64) || defined(__CRT_HAVE_mmap)
#include <local/sys.mman/mmap.h>
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE | MAP_STACK | MAP_SYNC |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_DONT_OVERRIDE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mmap, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED void *__NOTHROW_NCX(__LIBCCALL mmap)(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __FS_TYPE(off) __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mmap))(__addr, __len, __prot, __flags, __fd, __offset); })
#endif /* ... */
/* Unmap memory from `addr...+=len' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,munmap,(void *__addr, size_t __len),(__addr,__len))
/* @param prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE |
 *              PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED |
 *              PROT_GROWSUP | PROT_GROWSDOWN' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,mprotect,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot),(__addr,__len,__prot))
/* @param flags: Set of `MS_ASYNC | MS_INVALIDATE | MS_SYNC' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,msync,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __flags),(__addr,__len,__flags))
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,mlock,(void const *__addr, size_t __len),(__addr,__len))
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,munlock,(void const *__addr, size_t __len),(__addr,__len))
/* @param flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
__CDECLARE_OPT(,int,__NOTHROW_NCX,mlockall,(__STDC_INT_AS_UINT_T __flags),(__flags))
__CDECLARE_OPT(,int,__NOTHROW_NCX,munlockall,(void),())
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,shm_open,(char const *__name, __oflag_t __oflags, mode_t __mode),(__name,__oflags,__mode))
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,shm_unlink,(char const *__name),(__name))

#ifdef __USE_MISC
#ifdef __CRT_HAVE_madvise
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,madvise,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __advice),(__addr,__len,__advice))
#elif defined(__CRT_HAVE___madvise)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,madvise,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __advice),__madvise,(__addr,__len,__advice))
#else /* ... */
#include <local/sys.mman/madvise.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(madvise, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL madvise)(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __advice) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(madvise))(__addr, __len, __advice); })
#endif /* !... */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,mincore,(void *__start, size_t __len, unsigned char *__vec),(__start,__len,__vec))
#endif /* __USE_MISC */

#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_mmap64
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE | MAP_STACK | MAP_SYNC |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_DONT_OVERRIDE' */
__CDECLARE(__ATTR_WUNUSED,void *,__NOTHROW_NCX,mmap64,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __off64_t __offset),(__addr,__len,__prot,__flags,__fd,__offset))
#elif defined(__CRT_HAVE_mmap) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE | MAP_STACK | MAP_SYNC |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_DONT_OVERRIDE' */
__CREDIRECT(__ATTR_WUNUSED,void *,__NOTHROW_NCX,mmap64,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __off64_t __offset),mmap,(__addr,__len,__prot,__flags,__fd,__offset))
#elif defined(__CRT_HAVE_mmap)
#include <local/sys.mman/mmap64.h>
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE | MAP_STACK | MAP_SYNC |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_DONT_OVERRIDE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mmap64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED void *__NOTHROW_NCX(__LIBCCALL mmap64)(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __off64_t __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mmap64))(__addr, __len, __prot, __flags, __fd, __offset); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */

#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_posix_madvise
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_madvise,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __advice),(__addr,__len,__advice))
#else /* __CRT_HAVE_posix_madvise */
#include <local/sys.mman/posix_madvise.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_madvise, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL posix_madvise)(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __advice) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_madvise))(__addr, __len, __advice); })
#endif /* !__CRT_HAVE_posix_madvise */
#endif /* __USE_XOPEN2K */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_mremap
/* @param flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
__LIBC void *__NOTHROW_NCX(__VLIBCCALL mremap)(void *__addr, size_t __old_len, size_t __new_len, __STDC_INT_AS_UINT_T __flags, ...) __CASMNAME_SAME("mremap");
#endif /* __CRT_HAVE_mremap */
__CDECLARE_OPT(,int,__NOTHROW_NCX,remap_file_pages,(void *__start, size_t __size, __STDC_INT_AS_UINT_T __prot, size_t __pgoff, __STDC_INT_AS_UINT_T __flags),(__start,__size,__prot,__pgoff,__flags))
__CDECLARE_OPT(,__fd_t,__NOTHROW_NCX,memfd_create,(char const *__name, unsigned int __flags),(__name,__flags))
__CDECLARE_OPT(,int,__NOTHROW_NCX,mlock2,(void const *__addr, size_t __length, unsigned int __flags),(__addr,__length,__flags))
__CDECLARE_OPT(,int,__NOTHROW_NCX,pkey_alloc,(unsigned int __flags, unsigned int __access_rights),(__flags,__access_rights))
__CDECLARE_OPT(,int,__NOTHROW_NCX,pkey_set,(int __key, unsigned int __access_rights),(__key,__access_rights))
__CDECLARE_OPT(,int,__NOTHROW_NCX,pkey_get,(int __key),(__key))
__CDECLARE_OPT(,int,__NOTHROW_NCX,pkey_free,(int __key),(__key))
__CDECLARE_OPT(,int,__NOTHROW_NCX,pkey_mprotect,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, int __pkey),(__addr,__len,__prot,__pkey))
#endif /* __USE_GNU */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_SYS_MMAN_H)
#include <parts/uchar/sys/mman.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_SYS_MMAN_H */
#endif /* __USE_UTF */

#endif /* !_SYS_MMAN_H */
