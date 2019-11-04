/* HASH CRC-32:0x7bac958c */
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
#ifndef __local_wscanf_unlocked_defined
#if ((defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE_vwscanf_unlocked)
#define __local_wscanf_unlocked_defined 1
#include <kos/anno.h>
/* Dependency: "vwscanf_unlocked" from "wchar" */
#ifndef ____localdep_vwscanf_unlocked_defined
#define ____localdep_vwscanf_unlocked_defined 1
#ifdef __CRT_HAVE_vwscanf_unlocked
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_LIBC_SCANF(1, 0),__STDC_INT_AS_SIZE_T,,__localdep_vwscanf_unlocked,(__WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),vwscanf_unlocked,(__format,__args)) __THROWS(...)
#elif (defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)) && !defined(__NO_STDSTREAMS)
#include <local/wchar/vwscanf_unlocked.h>
#define __localdep_vwscanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf_unlocked))
#else /* CUSTOM: vwscanf_unlocked */
#undef ____localdep_vwscanf_unlocked_defined
#endif /* vwscanf_unlocked... */
#endif /* !____localdep_vwscanf_unlocked_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wscanf_unlocked) __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_LIBC_SCANF(1, 2) __STDC_INT_AS_SIZE_T
(__VLIBCCALL __LIBC_LOCAL_NAME(wscanf_unlocked))(__WCHAR_TYPE__ const *__restrict __format,
                                                 ...) __THROWS(...) {
#line 1120 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vwscanf_unlocked(__format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* ((defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE_vwscanf_unlocked) */
#endif /* !__local_wscanf_unlocked_defined */