/* HASH CRC-32:0x428cb2b2 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__vsnwscanf_defined
#define __local__vsnwscanf_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_vsnwscanf) __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_vsnwscanf))(__WCHAR_TYPE__ const *__src,
                                                        __SIZE_TYPE__ __bufsize,
                                                        __WCHAR_TYPE__ const *__format,
                                                        __builtin_va_list __args) {
#line 2013 "kos/src/libc/magic/wchar.c"
	(void)__src;
	(void)__bufsize;
	(void)__format;
	(void)__args;
	/* TODO */
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local__vsnwscanf_defined */