/* HASH CRC-32:0xb4f98216 */
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
#ifndef __local_fprintf_defined
#if (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked)
#define __local_fprintf_defined 1
#include <kos/anno.h>
/* Dependency: "vfprintf" from "stdio" */
#ifndef ____localdep_vfprintf_defined
#define ____localdep_vfprintf_defined 1
#if __has_builtin(__builtin_vfprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfprintf)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SSIZE_T (__LIBCCALL __localdep_vfprintf)(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return __builtin_vfprintf(__stream, __format, __args); }
#elif defined(__CRT_HAVE_vfprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_unlocked,(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vfprintf)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf,(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vfprintf_s)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_s,(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE__IO_vfprintf)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_IO_vfprintf,(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vfprintf_unlocked)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_unlocked,(__stream,__format,__args)) __THROWS(...)
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked)
#include <local/stdio/vfprintf.h>
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
#define __localdep_vfprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfprintf))
#else /* CUSTOM: vfprintf */
#undef ____localdep_vfprintf_defined
#endif /* vfprintf... */
#endif /* !____localdep_vfprintf_defined */

__NAMESPACE_LOCAL_BEGIN
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__LOCAL_LIBC(fprintf) __ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T
(__VLIBCCALL __LIBC_LOCAL_NAME(fprintf))(__FILE *__restrict __stream,
                                         char const *__restrict __format,
                                         ...) __THROWS(...) {
#line 828 "kos/src/libc/magic/stdio.c"
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vfprintf(__stream, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked */
#endif /* !__local_fprintf_defined */
