/* HASH CRC-32:0x1467510a */
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
#ifndef __local_dysize_defined
#define __local_dysize_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __isleap
#define __isleap(__year) ((__year)%4 == 0 && ((__year)%100 != 0 || (__year)%400 == 0))
#endif /* !__isleap */
/* Return the number of days in YEAR */
__LOCAL_LIBC(dysize) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(dysize))(int __year) {
#line 913 "kos/src/libc/magic/time.c"
	return __isleap(__year) ? 366 : 365;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_dysize_defined */
