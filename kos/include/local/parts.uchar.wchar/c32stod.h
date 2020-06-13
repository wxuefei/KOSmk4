/* HASH CRC-32:0x2a34a17b */
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
#ifndef __local_c32stod_defined
#define __local_c32stod_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32stod) __ATTR_NONNULL((1)) double
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32stod))(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr) {
	/* TODO */
	__COMPILER_IMPURE();
	if (__endptr)
		*__endptr = (__CHAR32_TYPE__ *)__nptr;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32stod_defined
#define __local___localdep_c32stod_defined 1
#define __localdep_c32stod __LIBC_LOCAL_NAME(c32stod)
#endif /* !__local___localdep_c32stod_defined */
#endif /* !__local_c32stod_defined */