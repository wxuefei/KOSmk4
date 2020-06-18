/* HASH CRC-32:0x6ffeb1c1 */
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
#ifndef __local___lock_fhandle_defined
#define __local___lock_fhandle_defined 1
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__lock_fhandle) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(__lock_fhandle))(__fd_t __fd) {
	(void)__fd;
	/* No-op */
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___lock_fhandle_defined
#define __local___localdep___lock_fhandle_defined 1
#define __localdep___lock_fhandle __LIBC_LOCAL_NAME(__lock_fhandle)
#endif /* !__local___localdep___lock_fhandle_defined */
#endif /* !__local___lock_fhandle_defined */