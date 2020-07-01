/* HASH CRC-32:0xd77d2005 */
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
#ifndef _ERR_H
#define _ERR_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <kos/anno.h>
#include <bits/types.h>

#ifdef __CC__

__SYSDECL_BEGIN

#ifdef __CRT_HAVE_warn
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
__LIBC __ATTR_LIBC_PRINTF(1, 2) void (__VLIBCCALL warn)(char const *__format, ...) __THROWS(...) __CASMNAME_SAME("warn");
#elif defined(__CRT_HAVE_vwarn) || defined(__CRT_HAVE_vwarnc) || (!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
#include <local/err/warn.h>
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(warn)
#else /* __cplusplus */
#define warn (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(warn))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE_vwarn
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
__CDECLARE_VOID(__ATTR_LIBC_PRINTF(1, 0),__THROWING,vwarn,(char const *__format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE_vwarnc) || (!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
#include <local/err/vwarn.h>
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
__NAMESPACE_LOCAL_USING_OR_IMPL(vwarn, __FORCELOCAL __ATTR_LIBC_PRINTF(1, 0) void (__LIBCCALL vwarn)(char const *__format, __builtin_va_list __args) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwarn))(__format, __args); })
#endif /* ... */

#ifdef __USE_BSD
#ifdef __CRT_HAVE_warnc
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
__LIBC __ATTR_LIBC_PRINTF(1, 2) void (__VLIBCCALL warnc)(__errno_t __used_errno, char const *__format, ...) __THROWS(...) __CASMNAME_SAME("warnc");
#elif defined(__CRT_HAVE_vwarnc) || (!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
#include <local/err/warnc.h>
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(warnc)
#else /* __cplusplus */
#define warnc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(warnc))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE_vwarnc
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
__CDECLARE_VOID(__ATTR_LIBC_PRINTF(1, 0),__THROWING,vwarnc,(__errno_t __used_errno, char const *__format, __builtin_va_list __args),(__used_errno,__format,__args))
#else /* __CRT_HAVE_vwarnc */
#include <__crt.h>
#include <local/program_invocation_name.h>
#if !defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite))
#include <local/err/vwarnc.h>
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
__NAMESPACE_LOCAL_USING_OR_IMPL(vwarnc, __FORCELOCAL __ATTR_LIBC_PRINTF(1, 0) void (__LIBCCALL vwarnc)(__errno_t __used_errno, char const *__format, __builtin_va_list __args) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwarnc))(__used_errno, __format, __args); })
#endif /* !__NO_STDSTREAMS && __LOCAL_program_invocation_short_name && (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite) && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite) */
#endif /* !__CRT_HAVE_vwarnc */
#endif /* __USE_BSD */

#ifdef __CRT_HAVE_warnx
/* Print to stderr: `<program_invocation_short_name>: <format...>\n' */
__LIBC __ATTR_LIBC_PRINTF(1, 2) void (__VLIBCCALL warnx)(char const *__format, ...) __THROWS(...) __CASMNAME_SAME("warnx");
#elif defined(__CRT_HAVE_vwarnx) || (!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)) && (defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
#include <local/err/warnx.h>
/* Print to stderr: `<program_invocation_short_name>: <format...>\n' */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(warnx)
#else /* __cplusplus */
#define warnx (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(warnx))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE_vwarnx
/* Print to stderr: `<program_invocation_short_name>: <format...>\n' */
__CDECLARE_VOID(__ATTR_LIBC_PRINTF(1, 0),__THROWING,vwarnx,(char const *__format, __builtin_va_list __args),(__format,__args))
#else /* __CRT_HAVE_vwarnx */
#include <__crt.h>
#include <local/program_invocation_name.h>
#if !defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)) && (defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite))
#include <local/err/vwarnx.h>
/* Print to stderr: `<program_invocation_short_name>: <format...>\n' */
__NAMESPACE_LOCAL_USING_OR_IMPL(vwarnx, __FORCELOCAL __ATTR_LIBC_PRINTF(1, 0) void (__LIBCCALL vwarnx)(char const *__format, __builtin_va_list __args) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwarnx))(__format, __args); })
#endif /* !__NO_STDSTREAMS && __LOCAL_program_invocation_short_name && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite) && (__CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite) */
#endif /* !__CRT_HAVE_vwarnx */
#ifdef __CRT_HAVE_err
/* Same as `warn()', but follow up by calling `exit(status)' */
__LIBC __ATTR_NORETURN __ATTR_LIBC_PRINTF(2, 3) void (__VLIBCCALL err)(int __status, char const *__format, ...) __THROWS(...) __CASMNAME_SAME("err");
#elif defined(__CRT_HAVE_verr) || defined(__CRT_HAVE_verrc) || ((defined(__CRT_HAVE_vwarnc) || (!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)))
#include <local/err/err.h>
/* Same as `warn()', but follow up by calling `exit(status)' */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(err)
#else /* __cplusplus */
#define err (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(err))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE_verr
/* Same as `warn()', but follow up by calling `exit(status)' */
__CDECLARE_VOID(__ATTR_NORETURN __ATTR_LIBC_PRINTF(2, 0),__THROWING,verr,(int __status, char const *__format, __builtin_va_list __args),(__status,__format,__args))
#elif defined(__CRT_HAVE_verrc) || ((defined(__CRT_HAVE_vwarnc) || (!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)))
#include <local/err/verr.h>
/* Same as `warn()', but follow up by calling `exit(status)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(verr, __FORCELOCAL __ATTR_NORETURN __ATTR_LIBC_PRINTF(2, 0) void (__LIBCCALL verr)(int __status, char const *__format, __builtin_va_list __args) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(verr))(__status, __format, __args); })
#endif /* ... */

#ifdef __USE_BSD
#ifdef __CRT_HAVE_errc
/* Same as `warnc()', but follow up by calling `exit(status)' */
__LIBC __ATTR_NORETURN __ATTR_LIBC_PRINTF(2, 3) void (__VLIBCCALL errc)(int __status, __errno_t __used_errno, char const *__format, ...) __THROWS(...) __CASMNAME_SAME("errc");
#elif defined(__CRT_HAVE_verrc) || ((defined(__CRT_HAVE_vwarnc) || (!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)))
#include <local/err/errc.h>
/* Same as `warnc()', but follow up by calling `exit(status)' */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(errc)
#else /* __cplusplus */
#define errc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(errc))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE_verrc
/* Same as `warnc()', but follow up by calling `exit(status)' */
__CDECLARE_VOID(__ATTR_NORETURN __ATTR_LIBC_PRINTF(2, 0),__THROWING,verrc,(int __status, __errno_t __used_errno, char const *__format, __builtin_va_list __args),(__status,__used_errno,__format,__args))
#elif (defined(__CRT_HAVE_vwarnc) || (!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit))
#include <local/err/verrc.h>
/* Same as `warnc()', but follow up by calling `exit(status)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(verrc, __FORCELOCAL __ATTR_NORETURN __ATTR_LIBC_PRINTF(2, 0) void (__LIBCCALL verrc)(int __status, __errno_t __used_errno, char const *__format, __builtin_va_list __args) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(verrc))(__status, __used_errno, __format, __args); })
#endif /* ... */
#endif /* __USE_BSD */

#ifdef __CRT_HAVE_errx
/* Same as `warnx()', but follow up by calling `exit(status)' */
__LIBC __ATTR_NORETURN __ATTR_LIBC_PRINTF(2, 3) void (__VLIBCCALL errx)(int __status, char const *__format, ...) __THROWS(...) __CASMNAME_SAME("errx");
#elif defined(__CRT_HAVE_verrx) || ((defined(__CRT_HAVE_vwarnx) || (!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)) && (defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)))
#include <local/err/errx.h>
/* Same as `warnx()', but follow up by calling `exit(status)' */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(errx)
#else /* __cplusplus */
#define errx (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(errx))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE_verrx
/* Same as `warnx()', but follow up by calling `exit(status)' */
__CDECLARE_VOID(__ATTR_NORETURN __ATTR_LIBC_PRINTF(2, 0),__THROWING,verrx,(int __status, char const *__format, __builtin_va_list __args),(__status,__format,__args))
#elif (defined(__CRT_HAVE_vwarnx) || (!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)) && (defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit))
#include <local/err/verrx.h>
/* Same as `warnx()', but follow up by calling `exit(status)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(verrx, __FORCELOCAL __ATTR_NORETURN __ATTR_LIBC_PRINTF(2, 0) void (__LIBCCALL verrx)(int __status, char const *__format, __builtin_va_list __args) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(verrx))(__status, __format, __args); })
#endif /* ... */

__SYSDECL_END

#endif /* __CC__ */

#endif /* !_ERR_H */
