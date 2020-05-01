/* HASH CRC-32:0x88ef758c */
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
#ifndef __local_vswprintf_defined
#define __local_vswprintf_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vswprintf) __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(vswprintf))(__WCHAR_TYPE__ *__restrict __buf,
                                                       __SIZE_TYPE__ __buflen,
                                                       __WCHAR_TYPE__ const *__restrict __format,
                                                       __builtin_va_list __args) {
#line 717 "kos/src/libc/magic/wchar.c"
	if (__buflen)
		*__buf = 0;
	/* TODO: format_wprintf() */
	(void)__format;
	(void)__args;
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_vswprintf_defined */
