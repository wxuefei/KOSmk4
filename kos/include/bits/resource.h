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
#ifndef _BITS_RESOURCE_H
#define _BITS_RESOURCE_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __rlimit_defined
#define __rlimit_defined 1
struct rlimit {
	__FS_TYPE(rlim) rlim_cur; /* The current (soft) limit. */
	__FS_TYPE(rlim) rlim_max; /* The hard limit. */
};
#endif /* !__rlimit_defined */

#ifdef __USE_LARGEFILE64
#ifndef __rlimit64_defined
#define __rlimit64_defined 1
struct rlimit64 {
	__rlim64_t rlim_cur; /* The current (soft) limit. */
	__rlim64_t rlim_max; /* The hard limit. */
};
#endif /* !__rlimit64_defined */
#endif /* __USE_LARGEFILE64 */

#endif /* __CC__ */

__SYSDECL_END


#endif /* !_BITS_RESOURCE_H */
