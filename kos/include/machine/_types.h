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
#ifndef _MACHINE__TYPES_H
#define _MACHINE__TYPES_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/types.h>
#include <machine/_default_types.h>

__DECL_BEGIN

#ifdef __CC__

/* Many other types were already defined in <bits/types.h> */
typedef __int16_t  __dev16_t;
typedef __uint16_t __uid16_t;
typedef __uint16_t __gid16_t;
#define __machine_blkcnt_t_defined 1
typedef __FS_TYPE(blkcnt) __blkcnt_t;
#define __machine_blksize_t_defined 1
#define __machine_dev_t_defined 1
#define __machine_fsblkcnt_t_defined 1
typedef __FS_TYPE(fsblkcnt) __fsblkcnt_t;
#define __machine_fsfilcnt_t_defined 1
typedef __FS_TYPE(fsfilcnt) __fsfilcnt_t;
#define __machine_uid_t_defined 1
#define __machine_gid_t_defined 1
#define __machine_ino_t_defined 1
typedef __FS_TYPE(ino) __ino_t;
#define __machine_key_t_defined 1
#define __machine_sa_family_t_defined 1
typedef __uint16_t __sa_family_t;
#define __machine_socklen_t_defined 1

#endif /* __CC__ */

__DECL_END

#endif /* !_MACHINE__TYPES_H */
