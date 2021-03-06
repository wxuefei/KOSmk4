/* HASH CRC-32:0x9edd0df3 */
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
#ifndef _SPAWN_H
#define _SPAWN_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/crt/posix_spawn.h>
#include <bits/crt/posix_spawn.h>
#include <bits/sched_param.h>
#include <bits/sigset.h> /* struct __sigset_struct */
#include <bits/types.h>
#include <sys/types.h>

#ifdef __USE_GLIBC
#include <sched.h>
#endif /* __USE_GLIBC */

__SYSDECL_BEGIN

/* Flags to be set in the `posix_spawnattr_t'. */
#ifdef __POSIX_SPAWN_RESETIDS
#define POSIX_SPAWN_RESETIDS __POSIX_SPAWN_RESETIDS
#endif /* __POSIX_SPAWN_RESETIDS */
#ifdef __POSIX_SPAWN_SETPGROUP
#define POSIX_SPAWN_SETPGROUP __POSIX_SPAWN_SETPGROUP
#endif /* __POSIX_SPAWN_SETPGROUP */
#ifdef __POSIX_SPAWN_SETSIGDEF
#define POSIX_SPAWN_SETSIGDEF __POSIX_SPAWN_SETSIGDEF
#endif /* __POSIX_SPAWN_SETSIGDEF */
#ifdef __POSIX_SPAWN_SETSIGMASK
#define POSIX_SPAWN_SETSIGMASK __POSIX_SPAWN_SETSIGMASK
#endif /* __POSIX_SPAWN_SETSIGMASK */
#ifdef __POSIX_SPAWN_SETSCHEDPARAM
#define POSIX_SPAWN_SETSCHEDPARAM __POSIX_SPAWN_SETSCHEDPARAM
#endif /* __POSIX_SPAWN_SETSCHEDPARAM */
#ifdef __POSIX_SPAWN_SETSCHEDULER
#define POSIX_SPAWN_SETSCHEDULER __POSIX_SPAWN_SETSCHEDULER
#endif /* __POSIX_SPAWN_SETSCHEDULER */
#ifdef __USE_GNU
#ifdef __POSIX_SPAWN_USEVFORK
#define POSIX_SPAWN_USEVFORK __POSIX_SPAWN_USEVFORK
#endif /* __POSIX_SPAWN_USEVFORK */
#endif /* __USE_GNU */


/* Comments taken from /usr/include/spawn.h of a linux machine.
 * The following is the copyright notice found in the original file. */
/* Definitions for POSIX spawn interface.
   Copyright (C) 2000-2016 Free Software Foundation, Inc.
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

#ifdef __CC__

#ifndef __sigset_t_defined
#define __sigset_t_defined 1
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

#ifndef __pid_t_defined
#define __pid_t_defined 1
typedef __pid_t pid_t;
#endif /* !pid_t_defined */

#ifndef __TARGV
#ifdef __USE_DOS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* ! */
#endif /* !__TARGV */

typedef struct __posix_spawnattr posix_spawnattr_t;
typedef struct __posix_spawn_file_actions posix_spawn_file_actions_t;


/* Spawn a new process executing PATH with the attributes describes in *ATTRP.
 * Before running the process perform the actions described in FILE-ACTIONS.
 * This function is a possible cancellation point and therefore not marked with __THROW */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 5, 6)),int,__NOTHROW_RPC,posix_spawn,(pid_t *__restrict __pid, char const *__restrict __path, posix_spawn_file_actions_t const *__file_actions, posix_spawnattr_t const *__attrp, __TARGV, __TENVP),(__pid,__path,__file_actions,__attrp,___argv,___envp))

/* Similar to `posix_spawn' but search for FILE in the PATH.
 * This function is a possible cancellation point and therefore not marked with __THROW */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 5, 6)),int,__NOTHROW_RPC,posix_spawnp,(pid_t *__restrict __pid, const char *__restrict __file, posix_spawn_file_actions_t const *__file_actions, posix_spawnattr_t const *__attrp, __TARGV, __TENVP),(__pid,__file,__file_actions,__attrp,___argv,___envp))

/* Initialize data structure with attributes for `spawn' to default values */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_spawnattr_init,(posix_spawnattr_t *__restrict __attr),(__attr))

/* Free resources associated with ATTR */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_spawnattr_destroy,(posix_spawnattr_t *__restrict __attr),(__attr))

/* Store signal mask for signals with default handling from ATTR in SIGDEFAULT */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,posix_spawnattr_getsigdefault,(posix_spawnattr_t const *__restrict __attr, sigset_t *__restrict __sigdefault),(__attr,__sigdefault))

/* Set signal mask for signals with default handling in ATTR to SIGDEFAULT */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,posix_spawnattr_setsigdefault,(posix_spawnattr_t *__restrict __attr, sigset_t const *__restrict __sigdefault),(__attr,__sigdefault))

/* Store signal mask for the new process from ATTR in SIGMASK */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,posix_spawnattr_getsigmask,(posix_spawnattr_t const *__restrict __attr, sigset_t *__restrict __sigmask),(__attr,__sigmask))

/* Set signal mask for the new process in ATTR to SIGMASK */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,posix_spawnattr_setsigmask,(posix_spawnattr_t *__restrict __attr, sigset_t const *__restrict __sigmask),(__attr,__sigmask))

/* Get flag word from the attribute structure */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,posix_spawnattr_getflags,(posix_spawnattr_t const *__restrict __attr, __INT16_TYPE__ *__restrict __flags),(__attr,__flags))

/* Store flags in the attribute structure */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_spawnattr_setflags,(posix_spawnattr_t *__restrict __attr, __INT16_TYPE__ __flags),(__attr,__flags))

/* Get process group ID from the attribute structure */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,posix_spawnattr_getpgroup,(posix_spawnattr_t const *__restrict __attr, pid_t *__restrict __pgroup),(__attr,__pgroup))

/* Store rocess group ID in the attribute structure */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_spawnattr_setpgroup,(posix_spawnattr_t *__restrict __attr, pid_t __pgroup),(__attr,__pgroup))

/* Get scheduling policy from the attribute structure */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,posix_spawnattr_getschedpolicy,(posix_spawnattr_t const *__restrict __attr, int *__restrict __schedpolicy),(__attr,__schedpolicy))

/* Store scheduling policy in the attribute structure */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_spawnattr_setschedpolicy,(posix_spawnattr_t *__restrict __attr, int __schedpolicy),(__attr,__schedpolicy))

/* Get scheduling parameters from the attribute structure */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,posix_spawnattr_getschedparam,(posix_spawnattr_t const *__restrict __attr, struct sched_param *__restrict __schedparam),(__attr,__schedparam))

/* Store scheduling parameters in the attribute structure */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,posix_spawnattr_setschedparam,(posix_spawnattr_t *__restrict __attr, struct sched_param const *__restrict __schedparam),(__attr,__schedparam))

/* Initialize data structure for file attribute for `spawn' call */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_spawn_file_actions_init,(posix_spawn_file_actions_t *__restrict __file_actions),(__file_actions))

/* Free resources associated with FILE-ACTIONS */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_spawn_file_actions_destroy,(posix_spawn_file_actions_t *__restrict __file_actions),(__file_actions))

/* Add an action to FILE-ACTIONS which tells the implementation
 * to call `open' for the given file during the `spawn' call */
__CDECLARE_OPT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_NCX,posix_spawn_file_actions_addopen,(posix_spawn_file_actions_t *__restrict __file_actions, __fd_t __fd, char const *__restrict __path, __oflag_t __oflags, mode_t __mode),(__file_actions,__fd,__path,__oflags,__mode))

/* Add an action to FILE-ACTIONS which tells the implementation to
 * call `close' for the given file descriptor during the `spawn' call */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_spawn_file_actions_addclose,(posix_spawn_file_actions_t *__restrict __file_actions, __fd_t __fd),(__file_actions,__fd))

/* Add an action to FILE-ACTIONS which tells the implementation to
 * call `dup2' for the given file descriptors during the `spawn' call */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_spawn_file_actions_adddup2,(posix_spawn_file_actions_t *__restrict __file_actions, __fd_t __fd, __fd_t __newfd),(__file_actions,__fd,__newfd))

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SPAWN_H */
