/* HASH CRC-32:0x26554d6e */
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
#ifndef __local_fputc32s_defined
#define __local_fputc32s_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_file_wprinter_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter_unlocked) || ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$putwc)
#include <kos/anno.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32slen from parts.uchar.string */
#ifndef __local___localdep_c32slen_defined
#define __local___localdep_c32slen_defined 1
#if defined(__CRT_HAVE_wcslen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32slen,(__CHAR32_TYPE__ const *__restrict __string),wcslen,(__string))
#elif defined(__CRT_HAVE_KOS$wcslen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32slen,(__CHAR32_TYPE__ const *__restrict __string),wcslen,(__string))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <local/wchar/wcslen.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c32slen (*(__SIZE_TYPE__(__LIBKCALL *)(__CHAR32_TYPE__ const *__restrict))&__LIBC_LOCAL_NAME(wcslen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c32slen.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c32slen __LIBC_LOCAL_NAME(c32slen)
#endif /* !... */
#endif /* !__local___localdep_c32slen_defined */
/* Dependency: file_c32printer from parts.uchar.stdio */
#ifndef __local___localdep_file_c32printer_defined
#define __local___localdep_file_c32printer_defined 1
#if defined(__CRT_HAVE_file_wprinter_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_file_c32printer,(void *__arg, __CHAR32_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$file_wprinter_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_file_c32printer,(void *__arg, __CHAR32_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_file_c32printer,(void *__arg, __CHAR32_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$file_wprinter)
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_file_c32printer,(void *__arg, __CHAR32_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_file_c32printer,(void *__arg, __CHAR32_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$file_wprinter_unlocked)
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_file_c32printer,(void *__arg, __CHAR32_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <local/wchar/file_wprinter.h>
__NAMESPACE_LOCAL_BEGIN
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
#define __localdep_file_c32printer (*(__SSIZE_TYPE__(__LIBKCALL *)(void *, __CHAR32_TYPE__ const *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(file_wprinter))
#elif (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$putwc)
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.stdio/file_c32printer.h>
__NAMESPACE_LOCAL_BEGIN
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
#define __localdep_file_c32printer __LIBC_LOCAL_NAME(file_c32printer)
#else /* ... */
#undef __local___localdep_file_c32printer_defined
#endif /* !... */
#endif /* !__local___localdep_file_c32printer_defined */
__LOCAL_LIBC(fputc32s) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(__LIBKCALL __LIBC_LOCAL_NAME(fputc32s))(__CHAR32_TYPE__ const *__restrict __string, __FILE *__restrict __stream) __THROWS(...) {
	__STDC_INT_AS_SIZE_T __result;
	__result = __localdep_file_c32printer(__stream, __string, __localdep_c32slen(__string));
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fputc32s_defined
#define __local___localdep_fputc32s_defined 1
#define __localdep_fputc32s __LIBC_LOCAL_NAME(fputc32s)
#endif /* !__local___localdep_fputc32s_defined */
#else /* (__CRT_HAVE_file_wprinter_unlocked && __USE_STDIO_UNLOCKED && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || (__CRT_HAVE_file_wprinter && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$file_wprinter || (__CRT_HAVE_file_wprinter_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$file_wprinter_unlocked || ((__CRT_HAVE_fputwc || __CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_fputwc && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$fputwc || (__CRT_HAVE_putwc && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$putwc */
#undef __local_fputc32s_defined
#endif /* (!__CRT_HAVE_file_wprinter_unlocked || !__USE_STDIO_UNLOCKED || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && (!__CRT_HAVE_file_wprinter || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$file_wprinter && (!__CRT_HAVE_file_wprinter_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$file_wprinter_unlocked && ((!__CRT_HAVE_fputwc && !__CRT_HAVE_putwc) || __SIZEOF_WCHAR_T__ != 4) && (!__CRT_HAVE_fputwc || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$fputwc && (!__CRT_HAVE_putwc || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$putwc */
#endif /* !__local_fputc32s_defined */
