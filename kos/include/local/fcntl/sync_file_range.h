/* HASH CRC-32:0x34d5496f */
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
#ifndef __local_sync_file_range_defined
#define __local_sync_file_range_defined 1
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sync_file_range) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sync_file_range))(__fd_t __fd, __off64_t __offset, __off64_t __count, unsigned int __flags) {
	(void)__fd;
	(void)__offset;
	(void)__count;
	(void)__flags;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sync_file_range_defined
#define __local___localdep_sync_file_range_defined 1
#define __localdep_sync_file_range __LIBC_LOCAL_NAME(sync_file_range)
#endif /* !__local___localdep_sync_file_range_defined */
#endif /* !__local_sync_file_range_defined */
