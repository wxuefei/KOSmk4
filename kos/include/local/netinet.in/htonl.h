/* HASH CRC-32:0x6e5ec4c5 */
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
#ifndef __local_htonl_defined
#define __local_htonl_defined 1
#include <__crt.h>
#include <hybrid/__byteswap.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(htonl) __ATTR_CONST __UINT32_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(htonl))(__UINT32_TYPE__ __hostlong) {
	return (__UINT32_TYPE__)__hybrid_htobe32(__hostlong);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_htonl_defined
#define __local___localdep_htonl_defined 1
#define __localdep_htonl __LIBC_LOCAL_NAME(htonl)
#endif /* !__local___localdep_htonl_defined */
#endif /* !__local_htonl_defined */
