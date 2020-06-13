/* HASH CRC-32:0x8c80b6b */
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
#ifndef __local_vc32printf_unlocked_defined
#define __local_vc32printf_unlocked_defined 1
#include <__crt.h>
#if ((defined(__CRT_HAVE_vfwprintf_unlocked) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$vfwprintf_unlocked) || ((defined(__CRT_HAVE_file_wprinter_unlocked) || (defined(__CRT_HAVE_DOS$file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_file_wprinter) || (defined(__CRT_HAVE_DOS$file_wprinter) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$file_wprinter) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_fputwc_unlocked) || (defined(__CRT_HAVE_DOS$fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 4)) || (defined(__CRT_HAVE_file_wprinter_unlocked) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$file_wprinter_unlocked) || (defined(__CRT_HAVE_file_wprinter) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$file_wprinter) || ((defined(__CRT_HAVE_fputwc_unlocked) || (defined(__CRT_HAVE_DOS$fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 4)) || (defined(__CRT_HAVE_fputwc_unlocked) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$fputwc_unlocked)) && !defined(__NO_STDSTREAMS)
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: vfc32printf_unlocked from parts.uchar.stdio */
#ifndef __local___localdep_vfc32printf_unlocked_defined
#define __local___localdep_vfc32printf_unlocked_defined 1
#if defined(__CRT_HAVE_vfwprintf_unlocked) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vfc32printf_unlocked,(__FILE *__restrict __stream, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_DOS$vfwprintf_unlocked)
__CREDIRECT_KOS(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vfc32printf_unlocked,(__FILE *__restrict __stream, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwprintf_unlocked,(__stream,__format,__args))
#elif (defined(__CRT_HAVE_file_wprinter_unlocked) || (defined(__CRT_HAVE_DOS$file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_file_wprinter) || (defined(__CRT_HAVE_DOS$file_wprinter) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$file_wprinter) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_fputwc_unlocked) || (defined(__CRT_HAVE_DOS$fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 4)
__NAMESPACE_LOCAL_END
#include <local/wchar/vfwprintf_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vfc32printf_unlocked (*(__STDC_INT_AS_SIZE_T(__LIBKCALL *)(__FILE *__restrict, __CHAR32_TYPE__ const *__restrict, __builtin_va_list))&__LIBC_LOCAL_NAME(vfwprintf_unlocked))
#elif (defined(__CRT_HAVE_file_wprinter_unlocked) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$file_wprinter_unlocked) || (defined(__CRT_HAVE_file_wprinter) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$file_wprinter) || ((defined(__CRT_HAVE_fputwc_unlocked) || (defined(__CRT_HAVE_DOS$fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 4)) || (defined(__CRT_HAVE_fputwc_unlocked) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$fputwc_unlocked)
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.stdio/vfc32printf_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vfc32printf_unlocked __LIBC_LOCAL_NAME(vfc32printf_unlocked)
#else /* ... */
#undef __local___localdep_vfc32printf_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_vfc32printf_unlocked_defined */
__NAMESPACE_LOCAL_END
#include <local/stdstreams.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vc32printf_unlocked) __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T
(__LIBKCALL __LIBC_LOCAL_NAME(vc32printf_unlocked))(__CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args) __THROWS(...) {
	return __localdep_vfc32printf_unlocked(__LOCAL_stdout, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vc32printf_unlocked_defined
#define __local___localdep_vc32printf_unlocked_defined 1
#define __localdep_vc32printf_unlocked __LIBC_LOCAL_NAME(vc32printf_unlocked)
#endif /* !__local___localdep_vc32printf_unlocked_defined */
#else /* ((__CRT_HAVE_vfwprintf_unlocked && (__SIZEOF_WCHAR_T__ == 4) && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_DOS$vfwprintf_unlocked || ((__CRT_HAVE_file_wprinter_unlocked || (__CRT_HAVE_DOS$file_wprinter_unlocked && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$file_wprinter_unlocked && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_file_wprinter || (__CRT_HAVE_DOS$file_wprinter && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$file_wprinter && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_fputwc_unlocked || (__CRT_HAVE_DOS$fputwc_unlocked && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$_fputwc_nolock && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 4)) || (__CRT_HAVE_file_wprinter_unlocked && (__SIZEOF_WCHAR_T__ == 4) && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_DOS$file_wprinter_unlocked || (__CRT_HAVE_file_wprinter && (__SIZEOF_WCHAR_T__ == 4) && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_DOS$file_wprinter || ((__CRT_HAVE_fputwc_unlocked || (__CRT_HAVE_DOS$fputwc_unlocked && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$_fputwc_nolock && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 4)) || (__CRT_HAVE_fputwc_unlocked && (__SIZEOF_WCHAR_T__ == 4) && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_DOS$fputwc_unlocked) && !__NO_STDSTREAMS */
#undef __local_vc32printf_unlocked_defined
#endif /* ((!__CRT_HAVE_vfwprintf_unlocked || !(__SIZEOF_WCHAR_T__ == 4) || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_DOS$vfwprintf_unlocked && ((!__CRT_HAVE_file_wprinter_unlocked && (!__CRT_HAVE_DOS$file_wprinter_unlocked || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$file_wprinter_unlocked || !__SIZEOF_WCHAR_T__ == 2) && !__CRT_HAVE_file_wprinter && (!__CRT_HAVE_DOS$file_wprinter || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$file_wprinter || !__SIZEOF_WCHAR_T__ == 2) && !__CRT_HAVE_fputwc_unlocked && (!__CRT_HAVE_DOS$fputwc_unlocked || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$_fputwc_nolock || !__SIZEOF_WCHAR_T__ == 2)) || !(__SIZEOF_WCHAR_T__ == 4)) && (!__CRT_HAVE_file_wprinter_unlocked || !(__SIZEOF_WCHAR_T__ == 4) || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_DOS$file_wprinter_unlocked && (!__CRT_HAVE_file_wprinter || !(__SIZEOF_WCHAR_T__ == 4) || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_DOS$file_wprinter && ((!__CRT_HAVE_fputwc_unlocked && (!__CRT_HAVE_DOS$fputwc_unlocked || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$_fputwc_nolock || !__SIZEOF_WCHAR_T__ == 2)) || !(__SIZEOF_WCHAR_T__ == 4)) && (!__CRT_HAVE_fputwc_unlocked || !(__SIZEOF_WCHAR_T__ == 4) || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_DOS$fputwc_unlocked) || __NO_STDSTREAMS */
#endif /* !__local_vc32printf_unlocked_defined */