/* HASH CRC-32:0x8498de22 */
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
#ifndef __local__vsnwscanf_l_defined
#define __local__vsnwscanf_l_defined 1
/* Dependency: "_vsnwscanf" from "wchar" */
#ifndef ____localdep__vsnwscanf_defined
#define ____localdep__vsnwscanf_defined 1
#ifdef __CRT_HAVE__vsnwscanf
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vsnwscanf,(__WCHAR_TYPE__ const *__src, __SIZE_TYPE__ __bufsize, __WCHAR_TYPE__ const *__format, __builtin_va_list __args),_vsnwscanf,(__src,__bufsize,__format,__args))
#else /* LIBC: _vsnwscanf */
#include <local/wchar/_vsnwscanf.h>
#define __localdep__vsnwscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnwscanf))
#endif /* _vsnwscanf... */
#endif /* !____localdep__vsnwscanf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_vsnwscanf_l) __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_vsnwscanf_l))(__WCHAR_TYPE__ const *__src,
                                                          __SIZE_TYPE__ __bufsize,
                                                          __WCHAR_TYPE__ const *__format,
                                                          __locale_t __locale,
                                                          __builtin_va_list __args) {
#line 2030 "kos/src/libc/magic/wchar.c"
	(void)__locale;
	return __localdep__vsnwscanf(__src, __bufsize, __format, __args);
}
__NAMESPACE_LOCAL_END
#endif /* !__local__vsnwscanf_l_defined */