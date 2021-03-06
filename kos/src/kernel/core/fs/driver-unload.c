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
#ifndef GUARD_KERNEL_CORE_FS_DRIVER_UNLOAD_C
#define GUARD_KERNEL_CORE_FS_DRIVER_UNLOAD_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/block.h>
#include <dev/char.h>
#include <kernel/driver.h>

DECL_BEGIN

/* Destroy all places where the given driver may still be loaded
 * globally, including registered devices or object types, as well
 * as task callbacks and interrupt hooks, etc... */
INTERN NONNULL((1)) void KCALL
driver_destroy_global_objects(struct driver *__restrict self) {
	(void)self;
	/* TODO: Delete global hooks of `self' */
}




DECL_END

#endif /* !GUARD_KERNEL_CORE_FS_DRIVER_UNLOAD_C */
