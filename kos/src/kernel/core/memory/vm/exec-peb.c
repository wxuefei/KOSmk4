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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_EXEC_PEB_C
#define GUARD_KERNEL_SRC_MEMORY_VM_EXEC_PEB_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/user.h>
#include <kernel/compat.h>
#include <kernel/vm.h>
#include <kernel/vm/builder.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <kos/exec/peb.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x

#ifdef __ARCH_HAVE_COMPAT
#if __ARCH_COMPAT_SIZEOF_POINTER == 4
#include <kos/exec/bits/peb32.h>
#elif __ARCH_COMPAT_SIZEOF_POINTER == 8
#include <kos/exec/bits/peb64.h>
#endif
#endif /* __ARCH_HAVE_COMPAT */

#ifndef __INTELLISENSE__
#define IN_POINTERSIZE __SIZEOF_POINTER__
#define OU_POINTERSIZE __SIZEOF_POINTER__
#include "exec-peb-impl.c.inl"

#ifdef __ARCH_HAVE_COMPAT
#if __SIZEOF_POINTER__ != 4
#define IN_POINTERSIZE 4
#define OU_POINTERSIZE 4
#include "exec-peb-impl.c.inl"
#endif /* __SIZEOF_POINTER__ != 4 */

#if __SIZEOF_POINTER__ != 8
#define IN_POINTERSIZE 8
#define OU_POINTERSIZE 8
#include "exec-peb-impl.c.inl"
#endif /* __SIZEOF_POINTER__ != 8 */

#define IN_POINTERSIZE 4
#define OU_POINTERSIZE 8
#include "exec-peb-impl.c.inl"

#define IN_POINTERSIZE 8
#define OU_POINTERSIZE 4
#include "exec-peb-impl.c.inl"
#endif /* __ARCH_HAVE_COMPAT */

#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_EXEC_PEB_C */
