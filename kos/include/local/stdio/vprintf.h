/* HASH CRC-32:0x2fae8577 */
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
#ifndef __local_vprintf_defined
#include <__crt.h>
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)|| defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked))) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || (__has_builtin(__builtin_vfprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfprintf)) || (defined(__CRT_HAVE_vfprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s))
#define __local_vprintf_defined 1
#include <kos/anno.h>
#include <local/stdstreams.h>
/* Dependency: "vfprintf" from "stdio" */
#ifndef ____localdep_vfprintf_defined
#define ____localdep_vfprintf_defined 1
#if __has_builtin(__builtin_vfprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfprintf)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__FORCELOCAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL __localdep_vfprintf)(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return __builtin_vfprintf(__stream, __format, __args); }
#elif defined(__CRT_HAVE_vfprintf_unlocked) && (defined(__USE_STDIO_UNLOCKED))
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_unlocked,(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vfprintf)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf,(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vfprintf_s)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_s,(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)|| defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked))) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked)
#include <local/stdio/vfprintf.h>
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
#define __localdep_vfprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfprintf))
#else /* CUSTOM: vfprintf */
#undef ____localdep_vfprintf_defined
#endif /* vfprintf... */
#endif /* !____localdep_vfprintf_defined */

__NAMESPACE_LOCAL_BEGIN
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__LOCAL_LIBC(vprintf) __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(vprintf))(char const *__restrict __format,
                                        __builtin_va_list __args) __THROWS(...) {
#line 803 "kos/src/libc/magic/stdio.c"
	return __localdep_vfprintf(__stdout, __format, __args);
}
__NAMESPACE_LOCAL_END
#endif /* !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)|| defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked))) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || (__has_builtin(__builtin_vfprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfprintf)) || (defined(__CRT_HAVE_vfprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s)) */
#endif /* !__local_vprintf_defined */
