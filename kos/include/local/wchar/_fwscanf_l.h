/* HASH CRC-32:0x87079081 */
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
#ifndef __local__fwscanf_l_defined
#define __local__fwscanf_l_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE__vfwscanf_l) || defined(__CRT_HAVE_vfwscanf)
#include <kos/anno.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: _vfwscanf_l from wchar */
#ifndef __local___localdep__vfwscanf_l_defined
#define __local___localdep__vfwscanf_l_defined 1
#ifdef __CRT_HAVE__vfwscanf_l
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep__vfwscanf_l,(__FILE *__stream, __WCHAR_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args),_vfwscanf_l,(__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE_vfwscanf)
__NAMESPACE_LOCAL_END
#include <local/wchar/_vfwscanf_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vfwscanf_l __LIBC_LOCAL_NAME(_vfwscanf_l)
#else /* ... */
#undef __local___localdep__vfwscanf_l_defined
#endif /* !... */
#endif /* !__local___localdep__vfwscanf_l_defined */
__LOCAL_LIBC(_fwscanf_l) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(__VLIBCCALL __LIBC_LOCAL_NAME(_fwscanf_l))(__FILE *__stream, __WCHAR_TYPE__ const *__format, __locale_t __locale, ...) __THROWS(...) {
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __locale);
	__result = __localdep__vfwscanf_l(__stream, __format, __locale, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__fwscanf_l_defined
#define __local___localdep__fwscanf_l_defined 1
#define __localdep__fwscanf_l __LIBC_LOCAL_NAME(_fwscanf_l)
#endif /* !__local___localdep__fwscanf_l_defined */
#else /* __CRT_HAVE__vfwscanf_l || __CRT_HAVE_vfwscanf */
#undef __local__fwscanf_l_defined
#endif /* !__CRT_HAVE__vfwscanf_l && !__CRT_HAVE_vfwscanf */
#endif /* !__local__fwscanf_l_defined */
