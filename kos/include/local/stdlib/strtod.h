/* HASH CRC-32:0x6983fa8f */
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
#ifndef __local_strtod_defined
#define __local_strtod_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strtod) __ATTR_LEAF __ATTR_NONNULL((1)) double
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtod))(char const *__restrict __nptr, char **__endptr) {
	/* TODO */
	__COMPILER_IMPURE();
	if (__endptr)
		*__endptr = (char *)__nptr;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtod_defined
#define __local___localdep_strtod_defined 1
#define __localdep_strtod __LIBC_LOCAL_NAME(strtod)
#endif /* !__local___localdep_strtod_defined */
#endif /* !__local_strtod_defined */
