/* HASH CRC-32:0xd741ab02 */
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
#ifndef _STDIO_H
#define _STDIO_H 1

#ifdef _CXX_STDONLY_CSTDIO
#ifdef __CXX_SYSTEM_HEADER
#undef _STDIO_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "stdio.h" after "cstdio" */
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#ifndef __fpos_t_defined
#define __fpos_t_defined 1
__NAMESPACE_STD_USING(fpos_t)
#endif /* !__fpos_t_defined */
#ifndef __FILE_defined
#define __FILE_defined 1
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
#if !defined(__remove_defined) && defined(__std_remove_defined)
#define __remove_defined 1
__NAMESPACE_STD_USING(remove)
#endif /* !__remove_defined && __std_remove_defined */
#if !defined(__rename_defined) && defined(__std_rename_defined)
#define __rename_defined 1
__NAMESPACE_STD_USING(rename)
#endif /* !__rename_defined && __std_rename_defined */
#ifdef __CRT_HAVE_tmpnam
__NAMESPACE_STD_USING(tmpnam)
#endif /* __CRT_HAVE_tmpnam */
#if defined(__CRT_HAVE_fclose) || defined(__CRT_HAVE__fclose_nolock) || defined(__CRT_HAVE__IO_fclose)
__NAMESPACE_STD_USING(fclose)
#endif /* __CRT_HAVE_fclose || __CRT_HAVE__fclose_nolock || __CRT_HAVE__IO_fclose */
__NAMESPACE_STD_USING(fflush)
#include <asm/crt/stdio.h>
#if defined(__CRT_HAVE_setbuf) || (defined(___IOFBF) && defined(___IONBF) && defined(__BUFSIZ) && (defined(__CRT_HAVE_setvbuf) || defined(__CRT_HAVE__IO_setvbuf) || defined(__CRT_HAVE_setvbuf_unlocked)))
__NAMESPACE_STD_USING(setbuf)
#endif /* __CRT_HAVE_setbuf || (___IOFBF && ___IONBF && __BUFSIZ && (__CRT_HAVE_setvbuf || __CRT_HAVE__IO_setvbuf || __CRT_HAVE_setvbuf_unlocked)) */
#if defined(__CRT_HAVE_setvbuf) || defined(__CRT_HAVE__IO_setvbuf) || defined(__CRT_HAVE_setvbuf_unlocked)
__NAMESPACE_STD_USING(setvbuf)
#endif /* __CRT_HAVE_setvbuf || __CRT_HAVE__IO_setvbuf || __CRT_HAVE_setvbuf_unlocked */
#if defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)
__NAMESPACE_STD_USING(fgetc)
__NAMESPACE_STD_USING(getc)
#endif /* __CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread */
#include <__crt.h>
#if (defined(__CRT_HAVE_getchar_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_getchar) || defined(__CRT_HAVE__fgetchar) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)))
__NAMESPACE_STD_USING(getchar)
#endif /* (__CRT_HAVE_getchar_unlocked && __USE_STDIO_UNLOCKED) || __CRT_HAVE_getchar || __CRT_HAVE__fgetchar || (!__NO_STDSTREAMS && (__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread)) */
#if defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_STD_USING(fputc)
__NAMESPACE_STD_USING(putc)
#endif /* __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite */
#if defined(__CRT_HAVE_putchar) || defined(__CRT_HAVE__fputchar) || defined(__CRT_HAVE_putchar_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
__NAMESPACE_STD_USING(putchar)
#endif /* __CRT_HAVE_putchar || __CRT_HAVE__fputchar || __CRT_HAVE_putchar_unlocked || (!__NO_STDSTREAMS && (__CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite)) */
#if defined(__CRT_HAVE_fgets) || defined(__CRT_HAVE_fgets_unlocked) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)))
__NAMESPACE_STD_USING(fgets)
#endif /* __CRT_HAVE_fgets || __CRT_HAVE_fgets_unlocked || ((__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked)) */
#if defined(__CRT_HAVE_fputs) || defined(__CRT_HAVE__IO_fputs) || defined(__CRT_HAVE_fputs_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_STD_USING(fputs)
#endif /* __CRT_HAVE_fputs || __CRT_HAVE__IO_fputs || __CRT_HAVE_fputs_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite */
#if defined(__CRT_HAVE_puts) || defined(__CRT_HAVE__IO_puts) || defined(__CRT_HAVE_puts_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
__NAMESPACE_STD_USING(puts)
#endif /* __CRT_HAVE_puts || __CRT_HAVE__IO_puts || __CRT_HAVE_puts_unlocked || (!__NO_STDSTREAMS && (__CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite)) */
#if defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)
__NAMESPACE_STD_USING(ungetc)
#endif /* __CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock */
#if defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)
__NAMESPACE_STD_USING(fread)
#endif /* __CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread */
#if defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_STD_USING(fwrite)
#endif /* __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite */
#if defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64)
__NAMESPACE_STD_USING(fseek)
#endif /* __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseeko64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE__fseeki64 */
#if (defined(__CRT_HAVE_ftell_unlocked) && defined(__USE_STDIO_UNLOCKED)) || (defined(__CRT_HAVE__ftell_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || (defined(__CRT_HAVE_ftello64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked)
__NAMESPACE_STD_USING(ftell)
#endif /* (__CRT_HAVE_ftell_unlocked && __USE_STDIO_UNLOCKED) || (__CRT_HAVE__ftell_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE_ftell || __CRT_HAVE__IO_ftell || (__CRT_HAVE_ftello64 && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__) || __CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked */
#if defined(__CRT_HAVE_rewind) || defined(__CRT_HAVE_rewind_unlocked) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
__NAMESPACE_STD_USING(rewind)
#endif /* __CRT_HAVE_rewind || __CRT_HAVE_rewind_unlocked || __CRT_HAVE_fseeko64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE__fseeki64 || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || __CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock */
#if defined(__CRT_HAVE_clearerr) || defined(__CRT_HAVE_clearerr_unlocked)
__NAMESPACE_STD_USING(clearerr)
#endif /* __CRT_HAVE_clearerr || __CRT_HAVE_clearerr_unlocked */
#if defined(__CRT_HAVE_feof) || defined(__CRT_HAVE__IO_feof) || defined(__CRT_HAVE_feof_unlocked)
__NAMESPACE_STD_USING(feof)
#endif /* __CRT_HAVE_feof || __CRT_HAVE__IO_feof || __CRT_HAVE_feof_unlocked */
#if defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)
__NAMESPACE_STD_USING(ferror)
#endif /* __CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked */
#if !defined(__perror_defined) && defined(__std_perror_defined)
#define __perror_defined 1
__NAMESPACE_STD_USING(perror)
#endif /* !__perror_defined && __std_perror_defined */
#if defined(__CRT_HAVE_tmpfile) || defined(__CRT_HAVE_tmpfile64)
__NAMESPACE_STD_USING(tmpfile)
#endif /* __CRT_HAVE_tmpfile || __CRT_HAVE_tmpfile64 */
#if defined(__CRT_HAVE_fopen) || defined(__CRT_HAVE__IO_fopen) || defined(__CRT_HAVE_fopen64)
__NAMESPACE_STD_USING(fopen)
#endif /* __CRT_HAVE_fopen || __CRT_HAVE__IO_fopen || __CRT_HAVE_fopen64 */
#if defined(__CRT_HAVE_freopen) || defined(__CRT_HAVE_freopen64) || defined(__CRT_HAVE_freopen_unlocked) || defined(__CRT_HAVE_freopen64_unlocked)
__NAMESPACE_STD_USING(freopen)
#endif /* __CRT_HAVE_freopen || __CRT_HAVE_freopen64 || __CRT_HAVE_freopen_unlocked || __CRT_HAVE_freopen64_unlocked */
#if defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || defined(__CRT_HAVE__IO_ftell)
__NAMESPACE_STD_USING(fgetpos)
#endif /* __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked || __CRT_HAVE_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock || __CRT_HAVE__IO_ftell */
#if defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
__NAMESPACE_STD_USING(fsetpos)
#endif /* __CRT_HAVE_fseeko64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE__fseeki64 || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || __CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock */
#if defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_STD_USING(vfprintf)
#endif /* __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite */
#if defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_STD_USING(fprintf)
#endif /* __CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite */
#if defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
__NAMESPACE_STD_USING(vprintf)
#endif /* __CRT_HAVE_vprintf || __CRT_HAVE_vprintf_s || __CRT_HAVE_vprintf_unlocked || (!__NO_STDSTREAMS && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite)) */
#if defined(__CRT_HAVE_printf) || defined(__CRT_HAVE__IO_printf) || defined(__CRT_HAVE_printf_s) || defined(__CRT_HAVE_printf_unlocked) || defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
__NAMESPACE_STD_USING(printf)
#endif /* __CRT_HAVE_printf || __CRT_HAVE__IO_printf || __CRT_HAVE_printf_s || __CRT_HAVE_printf_unlocked || __CRT_HAVE_vprintf || __CRT_HAVE_vprintf_s || __CRT_HAVE_vprintf_unlocked || (!__NO_STDSTREAMS && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite)) */
#if !defined(__vfscanf_defined) && defined(__std_vfscanf_defined)
#define __vfscanf_defined 1
__NAMESPACE_STD_USING(vfscanf)
#endif /* !__vfscanf_defined && __std_vfscanf_defined */
#if !defined(__vscanf_defined) && defined(__std_vscanf_defined)
#define __vscanf_defined 1
__NAMESPACE_STD_USING(vscanf)
#endif /* !__vscanf_defined && __std_vscanf_defined */
#if defined(__CRT_HAVE_fscanf) || defined(__CRT_HAVE_fscanf_unlocked) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
__NAMESPACE_STD_USING(fscanf)
#endif /* __CRT_HAVE_fscanf || __CRT_HAVE_fscanf_unlocked || __CRT_HAVE_vfscanf || __CRT_HAVE__vfscanf || __CRT_HAVE__vfscanf_s || __CRT_HAVE__IO_vfscanf || __CRT_HAVE_vfscanf_unlocked || __CRT_HAVE___vfscanf || ((__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock)) */
#if defined(__CRT_HAVE_scanf) || defined(__CRT_HAVE_scanf_unlocked) || defined(__CRT_HAVE_vscanf) || defined(__CRT_HAVE__vscanf) || defined(__CRT_HAVE_vscanf_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
__NAMESPACE_STD_USING(scanf)
#endif /* __CRT_HAVE_scanf || __CRT_HAVE_scanf_unlocked || __CRT_HAVE_vscanf || __CRT_HAVE__vscanf || __CRT_HAVE_vscanf_unlocked || (!__NO_STDSTREAMS && (__CRT_HAVE_vfscanf || __CRT_HAVE__vfscanf || __CRT_HAVE__vfscanf_s || __CRT_HAVE__IO_vfscanf || __CRT_HAVE_vfscanf_unlocked || __CRT_HAVE___vfscanf || ((__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock)))) */
#if !defined(__gets_defined) && defined(__std_gets_defined)
#define __gets_defined 1
__NAMESPACE_STD_USING(gets)
#endif /* !__gets_defined && __std_gets_defined */
#if !defined(__vsscanf_defined) && defined(__std_vsscanf_defined)
#define __vsscanf_defined 1
__NAMESPACE_STD_USING(vsscanf)
#endif /* !__vsscanf_defined && __std_vsscanf_defined */
__NAMESPACE_STD_USING(sscanf)
__NAMESPACE_STD_USING(vsprintf)
__NAMESPACE_STD_USING(sprintf)
#if !defined(__vsnprintf_defined) && defined(__std_vsnprintf_defined)
#define __vsnprintf_defined 1
__NAMESPACE_STD_USING(vsnprintf)
#endif /* !__vsnprintf_defined && __std_vsnprintf_defined */
#if !defined(__snprintf_defined) && defined(__std_snprintf_defined)
#define __snprintf_defined 1
__NAMESPACE_STD_USING(snprintf)
#endif /* !__snprintf_defined && __std_snprintf_defined */
#undef _CXX_STDONLY_CSTDIO
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CSTDIO */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/crt/stdio.h>
#include <asm/limits.h> /* __IOV_MAX */
#include <asm/oflags.h>
#include <asm/stdio.h>
#include <bits/types.h>
#include <kos/anno.h>

#include <libio.h>

#ifdef __USE_KOS
#include <bits/format-printer.h>
#endif /* __USE_KOS */

#ifdef __USE_DOS
#include <bits/crt/sys_errlist.h>
#include <xlocale.h>
#endif /* __USE_DOS */

#ifdef __CRT_CYG_PRIMARY
#include <sys/reent.h>
#endif /* __CRT_CYG_PRIMARY */

#ifdef __CRT_DOS_PRIMARY
#include <bits/crt/io-file.h>
#endif /* __CRT_DOS_PRIMARY */

__SYSDECL_BEGIN

/* The possibilities for the third argument to `setvbuf()'. */
#ifdef ___IOFBF
#define _IOFBF ___IOFBF /* Fully buffered. */
#endif /* ___IOFBF */
#ifdef ___IOLBF
#define _IOLBF ___IOLBF /* Line buffered. */
#endif /* ___IOLBF */
#ifdef ___IONBF
#define _IONBF ___IONBF /* No buffering. */
#endif /* ___IONBF */

/* Default buffer size.  */
#ifndef BUFSIZ
#define BUFSIZ __BUFSIZ
#endif /* !BUFSIZ */

#ifndef EOF
#define EOF __EOF
#endif /* !EOF */

#ifndef SEEK_SET
#define SEEK_SET __SEEK_SET /* Seek from beginning of file. */
#define SEEK_CUR __SEEK_CUR /* Seek from current position. */
#define SEEK_END __SEEK_END /* Seek from end of file. */
#ifdef __USE_GNU
#ifdef __SEEK_DATA
#define SEEK_DATA __SEEK_DATA /* Seek to next data. */
#endif /* __SEEK_DATA */
#ifdef __SEEK_HOLE
#define SEEK_HOLE __SEEK_HOLE /* Seek to next hole. */
#endif /* __SEEK_HOLE */
#endif /* __USE_GNU */
#endif /* !SEEK_SET */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifdef __CRT_DOS_PRIMARY
#define P_tmpdir "\\"
#else /* __CRT_DOS_PRIMARY */
#define P_tmpdir "/tmp"
#endif /* !__CRT_DOS_PRIMARY */
#endif /* __USE_MISC || __USE_XOPEN */

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

/* Minimum buffer size for temporary file names */
#if !defined(L_tmpnam) && defined(__L_tmpnam)
#define L_tmpnam __L_tmpnam
#endif /* !L_tmpnam && __L_tmpnam */

/* Recommended buffer size for file names. */
#if !defined(FILENAME_MAX) && defined(__FILENAME_MAX)
#define FILENAME_MAX __FILENAME_MAX
#endif /* !FILENAME_MAX && __FILENAME_MAX */

/* Min # of unique temporary file names what can be generated by `tmpnam()' */
#if !defined(TMP_MAX) && defined(__TMP_MAX)
#define TMP_MAX __TMP_MAX
#endif /* !TMP_MAX && __TMP_MAX */

#ifdef __USE_POSIX
/* - Max # of characters in the string returned by `ctermid()'
 * - Buffer size that must be passed to `ctermid_r()' */
#if !defined(L_ctermid) && defined(__L_ctermid)
#define L_ctermid __L_ctermid
#endif /* !L_ctermid && __L_ctermid */

#if !defined(__USE_XOPEN2K) || defined(__USE_GNU)
/* Max # of characters in the string returned by `cuserid()' */
#if !defined(L_cuserid) && defined(__L_cuserid)
#define L_cuserid __L_cuserid
#endif /* !L_cuserid && __L_cuserid */
#endif /* !__USE_XOPEN2K || __USE_GNU */
#endif /* __USE_POSIX */

#ifndef FOPEN_MAX
#ifdef __CRT_DOS_PRIMARY
#define FOPEN_MAX 20
#else /* __CRT_DOS_PRIMARY */
#define FOPEN_MAX 16
#endif /* !__CRT_DOS_PRIMARY */
#endif /* !FOPEN_MAX */

#ifndef IOV_MAX
/* [default:_POSIX_UIO_MAXIOV] Max # of elements in a `struct iovec' vector. */
#if defined(__IOV_MAX) && __IOV_MAX != -1
#define IOV_MAX __IOV_MAX
#else /* __IOV_MAX != -1 */
#define IOV_MAX 16 /* 16 == _XOPEN_IOV_MAX */
#endif /* __IOV_MAX == -1 */
#endif /* !IOV_MAX */



#ifdef __CC__
#ifndef __std_size_t_defined
#define __std_size_t_defined 1
__NAMESPACE_STD_BEGIN
typedef __SIZE_TYPE__ size_t;
__NAMESPACE_STD_END
#endif /* !__std_size_t_defined */
#ifndef __CXX_SYSTEM_HEADER
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifdef __USE_XOPEN2K8
#ifndef __off_t_defined
#define __off_t_defined 1
typedef __typedef_off_t off_t;
#endif /* !__off_t_defined */

#ifndef __ssize_t_defined
#define __ssize_t_defined 1
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

#ifdef __USE_LARGEFILE64
#ifndef __off64_t_defined
#define __off64_t_defined 1
typedef __off64_t off64_t;
#endif /* !__off64_t_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN2K8 */

#ifndef __std_fpos_t_defined
#define __std_fpos_t_defined 1
__NAMESPACE_STD_BEGIN
typedef __FS_TYPE(pos) fpos_t;
__NAMESPACE_STD_END
#endif /* !__std_fpos_t_defined */
#ifndef __CXX_SYSTEM_HEADER
#ifndef __fpos_t_defined
#define __fpos_t_defined 1
__NAMESPACE_STD_USING(fpos_t)
#endif /* !__fpos_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifdef __USE_LARGEFILE64
#ifndef __fpos64_t_defined
#define __fpos64_t_defined 1
typedef __pos64_t fpos64_t;
#endif /* !__fpos64_t_defined */
#endif /* __USE_LARGEFILE64 */

#ifndef __std_FILE_defined
#define __std_FILE_defined 1
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */
#ifndef __CXX_SYSTEM_HEADER
#ifndef __FILE_defined
#define __FILE_defined 1
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __NO_STDSTREAMS
/* Standard streams. */
#ifndef __stdstreams_defined
#define __stdstreams_defined 1
#undef stdin
#undef stdout
#undef stderr
#ifdef __CRT_CYG_PRIMARY
#   define stdin  (__CYG_REENT->__cyg_stdin)
#   define stdout (__CYG_REENT->__cyg_stdout)
#   define stderr (__CYG_REENT->__cyg_stderr)
#elif defined(__CRT_DOS_PRIMARY)
#ifdef __USE_DOS_LINKOBJECTS
#ifndef ___iob_defined
#define ___iob_defined 1
__LIBC FILE _iob[];
#endif /* !___iob_defined */
#   define stdin    (_iob + 0)
#   define stdout   (_iob + 1)
#   define stderr   (_iob + 2)
#else /* __USE_DOS_LINKOBJECTS */
#ifndef ____iob_func_defined
#define ____iob_func_defined 1
__LIBC __ATTR_WUNUSED __ATTR_RETNONNULL FILE *__NOTHROW(__LIBCCALL __iob_func)(void);
#endif /* !____iob_func_defined */
#   define stdin    (__iob_func() + 0)
#   define stdout   (__iob_func() + 1)
#   define stderr   (__iob_func() + 2)
#endif /* !__USE_DOS_LINKOBJECTS */
#else /* __CRT_... */
__LIBC __FILE *stdin;
#define stdin  stdin
__LIBC __FILE *stdout;
#define stdout stdout
__LIBC __FILE *stderr;
#define stderr stderr
#endif /* !__CRT_... */
#endif /* !__stdstreams_defined */
#endif /* !__NO_STDSTREAMS */


__NAMESPACE_STD_BEGIN
#ifndef __std_remove_defined
#define __std_remove_defined 1
#ifdef __remove_defined
/* Remove a file or directory `FILENAME' */
__NAMESPACE_GLB_USING_OR_IMPL(remove, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL remove)(char const *__filename) { return (:: remove)(__filename); })
#elif defined(__CRT_HAVE_remove)
/* Remove a file or directory `FILENAME' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,remove,(char const *__filename),(__filename))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_removeat)
__NAMESPACE_STD_END
#include <local/stdio/remove.h>
__NAMESPACE_STD_BEGIN
/* Remove a file or directory `FILENAME' */
__NAMESPACE_LOCAL_USING_OR_IMPL(remove, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL remove)(char const *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remove))(__filename); })
#else /* ... */
#undef __std_remove_defined
#endif /* !... */
#endif /* !__std_remove_defined */
#ifndef __std_rename_defined
#define __std_rename_defined 1
#ifdef __rename_defined
/* Rename a given file `OLDNAME' to `NEWNAME_OR_PATH', or in the event
 * that `NEWNAME_OR_PATH' refers to a directory, place the file within. */
__NAMESPACE_GLB_USING_OR_IMPL(rename, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL rename)(char const *__oldname, char const *__newname_or_path) { return (:: rename)(__oldname, __newname_or_path); })
#elif defined(__CRT_HAVE_rename)
/* Rename a given file `OLDNAME' to `NEWNAME_OR_PATH', or in the event
 * that `NEWNAME_OR_PATH' refers to a directory, place the file within. */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,rename,(char const *__oldname, char const *__newname_or_path),(__oldname,__newname_or_path))
#elif defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_renameat) || defined(__CRT_HAVE_frenameat))
__NAMESPACE_STD_END
#include <local/stdio/rename.h>
__NAMESPACE_STD_BEGIN
/* Rename a given file `OLDNAME' to `NEWNAME_OR_PATH', or in the event
 * that `NEWNAME_OR_PATH' refers to a directory, place the file within. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rename, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL rename)(char const *__oldname, char const *__newname_or_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rename))(__oldname, __newname_or_path); })
#else /* ... */
#undef __std_rename_defined
#endif /* !... */
#endif /* !__std_rename_defined */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,tmpnam,(char *__buf),(__buf))
#ifdef __CRT_HAVE_fclose
/* Close and destroy a given file `STREAM' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fclose,(FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__fclose_nolock)
/* Close and destroy a given file `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fclose,(FILE *__restrict __stream),_fclose_nolock,(__stream))
#elif defined(__CRT_HAVE__IO_fclose)
/* Close and destroy a given file `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fclose,(FILE *__restrict __stream),_IO_fclose,(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fflush_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
__CREDIRECT(,int,__THROWING,fflush,(FILE *__stream),fflush_unlocked,(__stream))
#elif defined(__CRT_HAVE__fflush_nolock) && defined(__USE_STDIO_UNLOCKED)
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
__CREDIRECT(,int,__THROWING,fflush,(FILE *__stream),_fflush_nolock,(__stream))
#elif defined(__CRT_HAVE_fflush)
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
__CDECLARE(,int,__THROWING,fflush,(FILE *__stream),(__stream))
#elif defined(__CRT_HAVE__IO_fflush)
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
__CREDIRECT(,int,__THROWING,fflush,(FILE *__stream),_IO_fflush,(__stream))
#elif defined(__CRT_HAVE_fflush_unlocked)
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
__CREDIRECT(,int,__THROWING,fflush,(FILE *__stream),fflush_unlocked,(__stream))
#elif defined(__CRT_HAVE__fflush_nolock)
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
__CREDIRECT(,int,__THROWING,fflush,(FILE *__stream),_fflush_nolock,(__stream))
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdio/fflush.h>
__NAMESPACE_STD_BEGIN
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
__NAMESPACE_LOCAL_USING_OR_IMPL(fflush, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL fflush)(FILE *__stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fflush))(__stream); })
#endif /* !... */
#ifdef __CRT_HAVE_setbuf
/* Alias for `setvbuf(STREAM, buf, _IOFBF, BUFSIZ)' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,setbuf,(FILE *__restrict __stream, char *__buf),(__stream,__buf))
#else /* __CRT_HAVE_setbuf */
__NAMESPACE_STD_END
#include <asm/crt/stdio.h>
__NAMESPACE_STD_BEGIN
#if defined(___IOFBF) && defined(___IONBF) && defined(__BUFSIZ) && (defined(__CRT_HAVE_setvbuf) || defined(__CRT_HAVE__IO_setvbuf) || defined(__CRT_HAVE_setvbuf_unlocked))
__NAMESPACE_STD_END
#include <local/stdio/setbuf.h>
__NAMESPACE_STD_BEGIN
/* Alias for `setvbuf(STREAM, buf, _IOFBF, BUFSIZ)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(setbuf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL setbuf)(FILE *__restrict __stream, char *__buf) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setbuf))(__stream, __buf); })
#endif /* ___IOFBF && ___IONBF && __BUFSIZ && (__CRT_HAVE_setvbuf || __CRT_HAVE__IO_setvbuf || __CRT_HAVE_setvbuf_unlocked) */
#endif /* !__CRT_HAVE_setbuf */
#if defined(__CRT_HAVE_setvbuf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Set the buffer and buffer-mode to-be used by the given `STREAM'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,setvbuf,(FILE *__restrict __stream, char *__restrict __buf, int __modes, size_t __bufsize),setvbuf_unlocked,(__stream,__buf,__modes,__bufsize))
#elif defined(__CRT_HAVE_setvbuf)
/* Set the buffer and buffer-mode to-be used by the given `STREAM'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,setvbuf,(FILE *__restrict __stream, char *__restrict __buf, int __modes, size_t __bufsize),(__stream,__buf,__modes,__bufsize))
#elif defined(__CRT_HAVE__IO_setvbuf)
/* Set the buffer and buffer-mode to-be used by the given `STREAM'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,setvbuf,(FILE *__restrict __stream, char *__restrict __buf, int __modes, size_t __bufsize),_IO_setvbuf,(__stream,__buf,__modes,__bufsize))
#elif defined(__CRT_HAVE_setvbuf_unlocked)
/* Set the buffer and buffer-mode to-be used by the given `STREAM'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,setvbuf,(FILE *__restrict __stream, char *__restrict __buf, int __modes, size_t __bufsize),setvbuf_unlocked,(__stream,__buf,__modes,__bufsize))
#endif /* ... */
#if defined(__CRT_HAVE_fgetc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc,(FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc,(FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE_fgetc)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fgetc,(FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_getc)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc,(FILE *__restrict __stream),getc,(__stream))
#elif defined(__CRT_HAVE__IO_getc)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc,(FILE *__restrict __stream),_IO_getc,(__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc,(FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc,(FILE *__restrict __stream),getc_unlocked,(__stream))
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)
__NAMESPACE_STD_END
#include <local/stdio/fgetc.h>
__NAMESPACE_STD_BEGIN
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fgetc)(FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc))(__stream); })
#endif /* ... */
#if defined(__CRT_HAVE_fgetc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc,(FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc,(FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE_fgetc)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc,(FILE *__restrict __stream),fgetc,(__stream))
#elif defined(__CRT_HAVE_getc)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,getc,(FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__IO_getc)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc,(FILE *__restrict __stream),_IO_getc,(__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc,(FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc,(FILE *__restrict __stream),getc_unlocked,(__stream))
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)
__NAMESPACE_STD_END
#include <local/stdio/fgetc.h>
__NAMESPACE_STD_BEGIN
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL getc)(FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc))(__stream); }
#endif /* ... */
#if defined(__CRT_HAVE_getchar_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Alias for `fgetc(stdin)' */
__CREDIRECT(,int,__THROWING,getchar,(void),getchar_unlocked,())
#elif defined(__CRT_HAVE_getchar)
/* Alias for `fgetc(stdin)' */
__CDECLARE(,int,__THROWING,getchar,(void),())
#elif defined(__CRT_HAVE__fgetchar)
/* Alias for `fgetc(stdin)' */
__CREDIRECT(,int,__THROWING,getchar,(void),_fgetchar,())
#else /* ... */
__NAMESPACE_STD_END
#include <__crt.h>
__NAMESPACE_STD_BEGIN
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread))
__NAMESPACE_STD_END
#include <local/stdio/getchar.h>
__NAMESPACE_STD_BEGIN
/* Alias for `fgetc(stdin)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(getchar, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL getchar)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getchar))(); })
#endif /* !__NO_STDSTREAMS && (__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread) */
#endif /* !... */
#if __has_builtin(__builtin_fputc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc)
/* Write a single character `CH' to `STREAM' */
__CEIDECLARE(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),{ return __builtin_fputc(__ch, __stream); })
#elif defined(__CRT_HAVE_fputc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_putc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc)
/* Write a single character `CH' to `STREAM' */
__CDECLARE(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE_putc)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),putc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_putc)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),_IO_putc,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc_unlocked)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_putc_unlocked)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_STD_END
#include <local/stdio/fputc.h>
__NAMESPACE_STD_BEGIN
/* Write a single character `CH' to `STREAM' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fputc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int (__LIBCCALL fputc)(int __ch, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc))(__ch, __stream); })
#endif /* ... */
#if __has_builtin(__builtin_fputc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc)
/* Write a single character `CH' to `STREAM' */
__CEIREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),fputc,{ return __builtin_fputc(__ch, __stream); })
#elif defined(__CRT_HAVE_fputc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_putc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),fputc,(__ch,__stream))
#elif defined(__CRT_HAVE_putc)
/* Write a single character `CH' to `STREAM' */
__CDECLARE(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE__IO_putc)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),_IO_putc,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc_unlocked)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_putc_unlocked)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_STD_END
#include <local/stdio/fputc.h>
__NAMESPACE_STD_BEGIN
/* Write a single character `CH' to `STREAM' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int (__LIBCCALL putc)(int __ch, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc))(__ch, __stream); }
#endif /* ... */
#if __has_builtin(__builtin_putchar) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_putchar)
/* Alias for `fputc(CH, stdout)' */
__CEIDECLARE(,int,__THROWING,putchar,(int __ch),{ return __builtin_putchar(__ch); })
#elif defined(__CRT_HAVE_putchar_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Alias for `fputc(CH, stdout)' */
__CREDIRECT(,int,__THROWING,putchar,(int __ch),putchar_unlocked,(__ch))
#elif defined(__CRT_HAVE_putchar)
/* Alias for `fputc(CH, stdout)' */
__CDECLARE(,int,__THROWING,putchar,(int __ch),(__ch))
#elif defined(__CRT_HAVE__fputchar)
/* Alias for `fputc(CH, stdout)' */
__CREDIRECT(,int,__THROWING,putchar,(int __ch),_fputchar,(__ch))
#elif defined(__CRT_HAVE_putchar_unlocked)
/* Alias for `fputc(CH, stdout)' */
__CREDIRECT(,int,__THROWING,putchar,(int __ch),putchar_unlocked,(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <__crt.h>
__NAMESPACE_STD_BEGIN
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite))
__NAMESPACE_STD_END
#include <local/stdio/putchar.h>
__NAMESPACE_STD_BEGIN
/* Alias for `fputc(CH, stdout)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(putchar, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL putchar)(int __ch) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putchar))(__ch); })
#endif /* !__NO_STDSTREAMS && (__CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite) */
#endif /* !... */
#if defined(__CRT_HAVE_fgets_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Read up to `BUFSIZE - 1' bytes of data from `STREAM', storing them into `BUF' stopped when
 * the buffer is full or a line-feed was read (in this case, the line-feed is also written to `BUF')
 * Afterwards, append a trailing NUL-character and re-return `BUF', or return `NULL' if an error occurred. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char *,__THROWING,fgets,(char *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgets_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgets)
/* Read up to `BUFSIZE - 1' bytes of data from `STREAM', storing them into `BUF' stopped when
 * the buffer is full or a line-feed was read (in this case, the line-feed is also written to `BUF')
 * Afterwards, append a trailing NUL-character and re-return `BUF', or return `NULL' if an error occurred. */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char *,__THROWING,fgets,(char *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgets_unlocked)
/* Read up to `BUFSIZE - 1' bytes of data from `STREAM', storing them into `BUF' stopped when
 * the buffer is full or a line-feed was read (in this case, the line-feed is also written to `BUF')
 * Afterwards, append a trailing NUL-character and re-return `BUF', or return `NULL' if an error occurred. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char *,__THROWING,fgets,(char *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgets_unlocked,(__buf,__bufsize,__stream))
#elif (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))
__NAMESPACE_STD_END
#include <local/stdio/fgets.h>
__NAMESPACE_STD_BEGIN
/* Read up to `BUFSIZE - 1' bytes of data from `STREAM', storing them into `BUF' stopped when
 * the buffer is full or a line-feed was read (in this case, the line-feed is also written to `BUF')
 * Afterwards, append a trailing NUL-character and re-return `BUF', or return `NULL' if an error occurred. */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgets, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) char *(__LIBCCALL fgets)(char *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgets))(__buf, __bufsize, __stream); })
#endif /* ... */
#if __has_builtin(__builtin_fputs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputs)
/* Print a given string `STR' to `STREAM'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
__CEIDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,fputs,(char const *__restrict __str, FILE *__restrict __stream),{ return __builtin_fputs(__str, __stream); })
#elif defined(__CRT_HAVE_fputs_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Print a given string `STR' to `STREAM'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,fputs,(char const *__restrict __str, FILE *__restrict __stream),fputs_unlocked,(__str,__stream))
#elif defined(__CRT_HAVE_fputs)
/* Print a given string `STR' to `STREAM'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,fputs,(char const *__restrict __str, FILE *__restrict __stream),(__str,__stream))
#elif defined(__CRT_HAVE__IO_fputs)
/* Print a given string `STR' to `STREAM'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,fputs,(char const *__restrict __str, FILE *__restrict __stream),_IO_fputs,(__str,__stream))
#elif defined(__CRT_HAVE_fputs_unlocked)
/* Print a given string `STR' to `STREAM'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,fputs,(char const *__restrict __str, FILE *__restrict __stream),fputs_unlocked,(__str,__stream))
#elif defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_STD_END
#include <local/stdio/fputs.h>
__NAMESPACE_STD_BEGIN
/* Print a given string `STR' to `STREAM'. This is identical to:
 * >> fwrite(str, sizeof(char), strlen(str), stream); */
__NAMESPACE_LOCAL_USING_OR_IMPL(fputs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL fputs)(char const *__restrict __str, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputs))(__str, __stream); })
#endif /* ... */
#if __has_builtin(__builtin_puts) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_puts)
/* Print a given string `STR', followed by a line-feed to `STDOUT' */
__CEIDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,puts,(char const *__restrict __string),{ return __builtin_puts(__string); })
#elif defined(__CRT_HAVE_puts_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Print a given string `STR', followed by a line-feed to `STDOUT' */
__CREDIRECT(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,puts,(char const *__restrict __string),puts_unlocked,(__string))
#elif defined(__CRT_HAVE_puts)
/* Print a given string `STR', followed by a line-feed to `STDOUT' */
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,puts,(char const *__restrict __string),(__string))
#elif defined(__CRT_HAVE__IO_puts)
/* Print a given string `STR', followed by a line-feed to `STDOUT' */
__CREDIRECT(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,puts,(char const *__restrict __string),_IO_puts,(__string))
#elif defined(__CRT_HAVE_puts_unlocked)
/* Print a given string `STR', followed by a line-feed to `STDOUT' */
__CREDIRECT(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,puts,(char const *__restrict __string),puts_unlocked,(__string))
#else /* ... */
__NAMESPACE_STD_END
#include <__crt.h>
__NAMESPACE_STD_BEGIN
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite))
__NAMESPACE_STD_END
#include <local/stdio/puts.h>
__NAMESPACE_STD_BEGIN
/* Print a given string `STR', followed by a line-feed to `STDOUT' */
__NAMESPACE_LOCAL_USING_OR_IMPL(puts, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL puts)(char const *__restrict __string) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(puts))(__string); })
#endif /* !__NO_STDSTREAMS && (__CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite) */
#endif /* !... */
#if defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc,(int __ch, FILE *__restrict __stream),ungetc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetc_nolock) && defined(__USE_STDIO_UNLOCKED)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc,(int __ch, FILE *__restrict __stream),_ungetc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetc)
/* Unget a single character byte of data previously returned by `getc()' */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc,(int __ch, FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE__IO_ungetc)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc,(int __ch, FILE *__restrict __stream),_IO_ungetc,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetc_unlocked)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc,(int __ch, FILE *__restrict __stream),ungetc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetc_nolock)
/* Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc,(int __ch, FILE *__restrict __stream),_ungetc_nolock,(__ch,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fread_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),size_t,__THROWING,fread,(void *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),fread_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fread_nolock) && defined(__USE_STDIO_UNLOCKED)
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),size_t,__THROWING,fread,(void *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),_fread_nolock,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__IO_fread) && defined(__USE_STDIO_UNLOCKED)
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),size_t,__THROWING,fread,(void *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),_IO_fread,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fread)
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),size_t,__THROWING,fread,(void *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fread_unlocked)
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),size_t,__THROWING,fread,(void *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),fread_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fread_nolock)
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),size_t,__THROWING,fread,(void *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),_fread_nolock,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__IO_fread)
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),size_t,__THROWING,fread,(void *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),_IO_fread,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf))
__NAMESPACE_STD_END
#include <local/stdio/fread.h>
__NAMESPACE_STD_BEGIN
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fread, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 4)) size_t (__LIBCCALL fread)(void *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fread))(__buf, __elemsize, __elemcount, __stream); })
#endif /* ... */
#if __has_builtin(__builtin_fwrite) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fwrite)
/* Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM' */
__CEIDECLARE(__ATTR_NONNULL((1, 4)),size_t,__THROWING,fwrite,(void const *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),{ return __builtin_fwrite(__buf, __elemsize, __elemcount, __stream); })
#elif defined(__CRT_HAVE_fwrite_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1, 4)),size_t,__THROWING,fwrite,(void const *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),fwrite_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fwrite_nolock) && defined(__USE_STDIO_UNLOCKED)
/* Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1, 4)),size_t,__THROWING,fwrite,(void const *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),_fwrite_nolock,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__IO_fwrite) && defined(__USE_STDIO_UNLOCKED)
/* Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1, 4)),size_t,__THROWING,fwrite,(void const *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),_IO_fwrite,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fwrite)
/* Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM' */
__CDECLARE(__ATTR_NONNULL((1, 4)),size_t,__THROWING,fwrite,(void const *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fwrite_s)
/* Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1, 4)),size_t,__THROWING,fwrite,(void const *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),fwrite_s,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_STD_END
#include <local/stdio/fwrite.h>
__NAMESPACE_STD_BEGIN
/* Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fwrite, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 4)) size_t (__LIBCCALL fwrite)(void const *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwrite))(__buf, __elemsize, __elemcount, __stream); })
#endif /* ... */
#if defined(__CRT_HAVE_fseek_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Change the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && defined(__USE_STDIO_UNLOCKED)
/* Change the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
/* Change the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* Change the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* Change the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek)
/* Change the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek_unlocked)
/* Change the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock)
/* Change the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
/* Change the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* Change the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* Change the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64)
__NAMESPACE_STD_END
#include <local/stdio/fseek.h>
__NAMESPACE_STD_BEGIN
/* Change the current in-file position of `STREAM' as a byte-offet from the start of the file */
__NAMESPACE_LOCAL_USING_OR_IMPL(fseek, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fseek)(FILE *__restrict __stream, long int __off, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fseek))(__stream, __off, __whence); })
#endif /* ... */
#if defined(__CRT_HAVE_ftell_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Return the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && defined(__USE_STDIO_UNLOCKED)
/* Return the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__ && defined(__USE_STDIO_UNLOCKED)
/* Return the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__ && defined(__USE_STDIO_UNLOCKED)
/* Return the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__ && defined(__USE_STDIO_UNLOCKED)
/* Return the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftell)
/* Return the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__IO_ftell)
/* Return the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_ftello) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
/* Return the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE_ftello64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* Return the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE__ftelli64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* Return the current in-file position of `STREAM' as a byte-offet from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked)
__NAMESPACE_STD_END
#include <local/stdio/ftell.h>
__NAMESPACE_STD_BEGIN
/* Return the current in-file position of `STREAM' as a byte-offet from the start of the file */
__NAMESPACE_LOCAL_USING_OR_IMPL(ftell, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) long int (__LIBCCALL ftell)(FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftell))(__stream); })
#endif /* ... */
#if defined(__CRT_HAVE_rewind_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Rewind the current in-file position of `STREAM' to its starting position */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__THROWING,rewind,(FILE *__restrict __stream),rewind_unlocked,(__stream))
#elif defined(__CRT_HAVE_rewind)
/* Rewind the current in-file position of `STREAM' to its starting position */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__THROWING,rewind,(FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_rewind_unlocked)
/* Rewind the current in-file position of `STREAM' to its starting position */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__THROWING,rewind,(FILE *__restrict __stream),rewind_unlocked,(__stream))
#elif defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
__NAMESPACE_STD_END
#include <local/stdio/rewind.h>
__NAMESPACE_STD_BEGIN
/* Rewind the current in-file position of `STREAM' to its starting position */
__NAMESPACE_LOCAL_USING_OR_IMPL(rewind, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void (__LIBCCALL rewind)(FILE *__restrict __stream) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rewind))(__stream); })
#endif /* ... */
#if defined(__CRT_HAVE_clearerr_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Clear the error state of `STREAM', returning the stream to normal operations mode */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,clearerr,(__FILE *__restrict __stream),clearerr_unlocked,(__stream))
#elif defined(__CRT_HAVE_clearerr)
/* Clear the error state of `STREAM', returning the stream to normal operations mode */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,clearerr,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_clearerr_unlocked)
/* Clear the error state of `STREAM', returning the stream to normal operations mode */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,clearerr,(__FILE *__restrict __stream),clearerr_unlocked,(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_feof_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Check if end-of-file has been reached in `STREAM' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,feof,(__FILE __KOS_FIXED_CONST *__restrict __stream),feof_unlocked,(__stream))
#elif defined(__CRT_HAVE_feof)
/* Check if end-of-file has been reached in `STREAM' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,feof,(__FILE __KOS_FIXED_CONST *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__IO_feof)
/* Check if end-of-file has been reached in `STREAM' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,feof,(__FILE __KOS_FIXED_CONST *__restrict __stream),_IO_feof,(__stream))
#elif defined(__CRT_HAVE_feof_unlocked)
/* Check if end-of-file has been reached in `STREAM' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,feof,(__FILE __KOS_FIXED_CONST *__restrict __stream),feof_unlocked,(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_ferror_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Check if an I/O error occurred in `STREAM' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ferror,(__FILE __KOS_FIXED_CONST *__restrict __stream),ferror_unlocked,(__stream))
#elif defined(__CRT_HAVE_ferror)
/* Check if an I/O error occurred in `STREAM' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ferror,(__FILE __KOS_FIXED_CONST *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__IO_ferror)
/* Check if an I/O error occurred in `STREAM' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ferror,(__FILE __KOS_FIXED_CONST *__restrict __stream),_IO_ferror,(__stream))
#elif defined(__CRT_HAVE_ferror_unlocked)
/* Check if an I/O error occurred in `STREAM' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ferror,(__FILE __KOS_FIXED_CONST *__restrict __stream),ferror_unlocked,(__stream))
#endif /* ... */
#ifndef __std_perror_defined
#define __std_perror_defined 1
#ifdef __perror_defined
/* Print a given `MESSAGE' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
__NAMESPACE_GLB_USING_OR_IMPL(perror, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_RPC(__LIBCCALL perror)(char const *__message) { (:: perror)(__message); })
#elif defined(__CRT_HAVE_perror)
/* Print a given `MESSAGE' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
__CDECLARE_VOID(,__NOTHROW_RPC,perror,(char const *__message),(__message))
#else /* ... */
__NAMESPACE_STD_END
#include <__crt.h>
#include <parts/errno.h>
__NAMESPACE_STD_BEGIN
#if !defined(__NO_STDSTREAMS) && defined(__libc_geterrno) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite))
__NAMESPACE_STD_END
#include <local/stdio/perror.h>
__NAMESPACE_STD_BEGIN
/* Print a given `MESSAGE' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
__NAMESPACE_LOCAL_USING_OR_IMPL(perror, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_RPC(__LIBCCALL perror)(char const *__message) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(perror))(__message); })
#else /* !__NO_STDSTREAMS && __libc_geterrno && (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite) */
#undef __std_perror_defined
#endif /* __NO_STDSTREAMS || !__libc_geterrno || (!__CRT_HAVE_fprintf && !__CRT_HAVE__IO_fprintf && !__CRT_HAVE_fprintf_s && !__CRT_HAVE_fprintf_unlocked && !__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_fputc && !__CRT_HAVE_putc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE_putc_unlocked && (!__CRT_DOS || !__CRT_HAVE__flsbuf) && !__CRT_HAVE_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock && !__CRT_HAVE__IO_fwrite) */
#endif /* !... */
#endif /* !__std_perror_defined */
#if defined(__CRT_HAVE_tmpfile64) && defined(__USE_FILE_OFFSET64)
/* Create and return a new file-stream for accessing a temporary file for reading/writing */
__CREDIRECT(__ATTR_WUNUSED,FILE *,__NOTHROW_RPC,tmpfile,(void),tmpfile64,())
#elif defined(__CRT_HAVE_tmpfile)
/* Create and return a new file-stream for accessing a temporary file for reading/writing */
__CDECLARE(__ATTR_WUNUSED,FILE *,__NOTHROW_RPC,tmpfile,(void),())
#elif defined(__CRT_HAVE_tmpfile64)
/* Create and return a new file-stream for accessing a temporary file for reading/writing */
__CREDIRECT(__ATTR_WUNUSED,FILE *,__NOTHROW_RPC,tmpfile,(void),tmpfile64,())
#endif /* ... */
#if defined(__CRT_HAVE_fopen64) && defined(__USE_FILE_OFFSET64)
/* Create and return a new file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),FILE *,__NOTHROW_RPC,fopen,(char const *__restrict __filename, char const *__restrict __modes),fopen64,(__filename,__modes))
#elif defined(__CRT_HAVE_fopen)
/* Create and return a new file-stream for accessing `FILENAME' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),FILE *,__NOTHROW_RPC,fopen,(char const *__restrict __filename, char const *__restrict __modes),(__filename,__modes))
#elif defined(__CRT_HAVE__IO_fopen)
/* Create and return a new file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),FILE *,__NOTHROW_RPC,fopen,(char const *__restrict __filename, char const *__restrict __modes),_IO_fopen,(__filename,__modes))
#elif defined(__CRT_HAVE_fopen64)
/* Create and return a new file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),FILE *,__NOTHROW_RPC,fopen,(char const *__restrict __filename, char const *__restrict __modes),fopen64,(__filename,__modes))
#endif /* ... */
#if defined(__CRT_HAVE_freopen64_unlocked) && defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),FILE *,__NOTHROW_RPC,freopen,(char const *__restrict __filename, char const *__restrict __modes, FILE *__restrict __stream),freopen64_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),FILE *,__NOTHROW_RPC,freopen,(char const *__restrict __filename, char const *__restrict __modes, FILE *__restrict __stream),freopen_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64) && defined(__USE_FILE_OFFSET64)
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),FILE *,__NOTHROW_RPC,freopen,(char const *__restrict __filename, char const *__restrict __modes, FILE *__restrict __stream),freopen64,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen)
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),FILE *,__NOTHROW_RPC,freopen,(char const *__restrict __filename, char const *__restrict __modes, FILE *__restrict __stream),(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64)
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),FILE *,__NOTHROW_RPC,freopen,(char const *__restrict __filename, char const *__restrict __modes, FILE *__restrict __stream),freopen64,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen_unlocked)
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),FILE *,__NOTHROW_RPC,freopen,(char const *__restrict __filename, char const *__restrict __modes, FILE *__restrict __stream),freopen_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64_unlocked)
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),FILE *,__NOTHROW_RPC,freopen,(char const *__restrict __filename, char const *__restrict __modes, FILE *__restrict __stream),freopen64_unlocked,(__filename,__modes,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fgetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos,(FILE *__restrict __stream, fpos_t *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos_unlocked) && defined(__USE_STDIO_UNLOCKED) && !defined(__USE_FILE_OFFSET64)
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos,(FILE *__restrict __stream, fpos_t *__restrict __pos),fgetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64) && defined(__USE_FILE_OFFSET64)
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos,(FILE *__restrict __stream, fpos_t *__restrict __pos),fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos) && !defined(__USE_FILE_OFFSET64)
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos,(FILE *__restrict __stream, fpos_t *__restrict __pos),(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos) && !defined(__USE_FILE_OFFSET64)
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos,(FILE *__restrict __stream, fpos_t *__restrict __pos),_IO_fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos)
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos,(FILE *__restrict __stream, fpos_t *__restrict __pos),(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || defined(__CRT_HAVE__IO_ftell)
__NAMESPACE_STD_END
#include <local/stdio/fgetpos.h>
__NAMESPACE_STD_BEGIN
/* Initialize an opaque descriptor `POS' for the current in-file position of `STREAM'
 * Upon success (return == 0), `POS' can be used to restore the current position by calling `fsetpos()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetpos, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int (__LIBCCALL fgetpos)(FILE *__restrict __stream, fpos_t *__restrict __pos) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetpos))(__stream, __pos); })
#endif /* ... */
#if defined(__CRT_HAVE_fsetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos,(FILE *__restrict __stream, fpos_t const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos_unlocked) && defined(__USE_STDIO_UNLOCKED) && !defined(__USE_FILE_OFFSET64)
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos,(FILE *__restrict __stream, fpos_t const *__restrict __pos),fsetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64) && defined(__USE_FILE_OFFSET64)
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos,(FILE *__restrict __stream, fpos_t const *__restrict __pos),fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos) && !defined(__USE_FILE_OFFSET64)
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos,(FILE *__restrict __stream, fpos_t const *__restrict __pos),(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos) && !defined(__USE_FILE_OFFSET64)
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos,(FILE *__restrict __stream, fpos_t const *__restrict __pos),_IO_fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
__NAMESPACE_STD_END
#include <local/stdio/fsetpos.h>
__NAMESPACE_STD_BEGIN
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fsetpos, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int (__LIBCCALL fsetpos)(FILE *__restrict __stream, fpos_t const *__restrict __pos) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fsetpos))(__stream, __pos); })
#endif /* ... */
#if __has_builtin(__builtin_vfprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfprintf)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CEIDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),{ return __builtin_vfprintf(__stream, __format, __args); })
#elif defined(__CRT_HAVE_vfprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfprintf)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfprintf_s)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_s,(__stream,__format,__args))
#elif defined(__CRT_HAVE__IO_vfprintf)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_IO_vfprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfprintf_unlocked)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_STD_END
#include <local/stdio/vfprintf.h>
__NAMESPACE_STD_BEGIN
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__NAMESPACE_LOCAL_USING_OR_IMPL(vfprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL vfprintf)(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfprintf))(__stream, __format, __args); })
#endif /* ... */
#if __has_builtin(__builtin_fprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fprintf) && __has_builtin(__builtin_va_arg_pack)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CEIDECLARE(__ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,fprintf,(FILE *__restrict __stream, char const *__restrict __format, ...),{ return __builtin_fprintf(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_fprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_unlocked");
#elif defined(__CRT_HAVE_fprintf)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fprintf");
#elif defined(__CRT_HAVE__IO_fprintf)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("_IO_fprintf");
#elif defined(__CRT_HAVE_fprintf_s)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_s");
#elif defined(__CRT_HAVE_fprintf_unlocked)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_unlocked");
#elif defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_STD_END
#include <local/stdio/fprintf.h>
__NAMESPACE_STD_BEGIN
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(fprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fprintf))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define fprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fprintf))
#endif /* !__cplusplus */
#endif /* ... */
#if __has_builtin(__builtin_vprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vprintf)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__CEIDECLARE(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,vprintf,(char const *__restrict __format, __builtin_va_list __args),{ return __builtin_vprintf(__format, __args); })
#elif defined(__CRT_HAVE_vprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,vprintf,(char const *__restrict __format, __builtin_va_list __args),vprintf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_vprintf)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__CDECLARE(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,vprintf,(char const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE_vprintf_s)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,vprintf,(char const *__restrict __format, __builtin_va_list __args),vprintf_s,(__format,__args))
#elif defined(__CRT_HAVE_vprintf_unlocked)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,vprintf,(char const *__restrict __format, __builtin_va_list __args),vprintf_unlocked,(__format,__args))
#else /* ... */
__NAMESPACE_STD_END
#include <__crt.h>
__NAMESPACE_STD_BEGIN
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite))
__NAMESPACE_STD_END
#include <local/stdio/vprintf.h>
__NAMESPACE_STD_BEGIN
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__NAMESPACE_LOCAL_USING_OR_IMPL(vprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL vprintf)(char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vprintf))(__format, __args); })
#endif /* !__NO_STDSTREAMS && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite) */
#endif /* !... */
#if __has_builtin(__builtin_printf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_printf) && __has_builtin(__builtin_va_arg_pack)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__CEIDECLARE(__ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,printf,(char const *__restrict __format, ...),{ return __builtin_printf(__format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_printf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("printf_unlocked");
#elif defined(__CRT_HAVE_printf)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("printf");
#elif defined(__CRT_HAVE__IO_printf)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("_IO_printf");
#elif defined(__CRT_HAVE_printf_s)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("printf_s");
#elif defined(__CRT_HAVE_printf_unlocked)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("printf_unlocked");
#else /* ... */
__NAMESPACE_STD_END
#include <__crt.h>
__NAMESPACE_STD_BEGIN
#if defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
__NAMESPACE_STD_END
#include <local/stdio/printf.h>
__NAMESPACE_STD_BEGIN
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf)(char const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(printf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(printf))
#endif /* !__cplusplus */
#endif /* __CRT_HAVE_vprintf || __CRT_HAVE_vprintf_s || __CRT_HAVE_vprintf_unlocked || (!__NO_STDSTREAMS && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite)) */
#endif /* !... */

#if defined(__USE_ISOC99) || defined(__USE_DOS)
#ifndef __std_vfscanf_defined
#define __std_vfscanf_defined 1
#ifdef __vfscanf_defined
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__NAMESPACE_GLB_USING_OR_IMPL(vfscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL vfscanf)(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (:: vfscanf)(__stream, __format, __args); })
#elif defined(__CRT_HAVE_vfscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfscanf_unlocked,(__stream,__format,__args))
#elif __has_builtin(__builtin_vfscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfscanf)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CEIDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),{ return __builtin_vfscanf(__stream, __format, __args); })
#elif defined(__CRT_HAVE_vfscanf)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE__vfscanf)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_vfscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE__vfscanf_s)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_vfscanf_s,(__stream,__format,__args))
#elif defined(__CRT_HAVE__IO_vfscanf)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_IO_vfscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfscanf_unlocked)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfscanf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE___vfscanf)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),__vfscanf,(__stream,__format,__args))
#elif (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
__NAMESPACE_STD_END
#include <local/stdio/vfscanf.h>
__NAMESPACE_STD_BEGIN
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__NAMESPACE_LOCAL_USING_OR_IMPL(vfscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL vfscanf)(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfscanf))(__stream, __format, __args); })
#else /* ... */
#undef __std_vfscanf_defined
#endif /* !... */
#endif /* !__std_vfscanf_defined */
#ifndef __std_vscanf_defined
#define __std_vscanf_defined 1
#ifdef __vscanf_defined
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__NAMESPACE_GLB_USING_OR_IMPL(vscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL vscanf)(char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (:: vscanf)(__format, __args); })
#elif __has_builtin(__builtin_vscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vscanf)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CEIDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vscanf,(char const *__restrict __format, __builtin_va_list __args),{ return __builtin_vscanf(__format, __args); })
#elif defined(__CRT_HAVE_vscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vscanf,(char const *__restrict __format, __builtin_va_list __args),vscanf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_vscanf)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vscanf,(char const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE__vscanf)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vscanf,(char const *__restrict __format, __builtin_va_list __args),_vscanf,(__format,__args))
#elif defined(__CRT_HAVE_vscanf_unlocked)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vscanf,(char const *__restrict __format, __builtin_va_list __args),vscanf_unlocked,(__format,__args))
#else /* ... */
__NAMESPACE_STD_END
#include <__crt.h>
__NAMESPACE_STD_BEGIN
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))))
__NAMESPACE_STD_END
#include <local/stdio/vscanf.h>
__NAMESPACE_STD_BEGIN
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__NAMESPACE_LOCAL_USING_OR_IMPL(vscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL vscanf)(char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vscanf))(__format, __args); })
#else /* !__NO_STDSTREAMS && (__CRT_HAVE_vfscanf || __CRT_HAVE__vfscanf || __CRT_HAVE__vfscanf_s || __CRT_HAVE__IO_vfscanf || __CRT_HAVE_vfscanf_unlocked || __CRT_HAVE___vfscanf || ((__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock))) */
#undef __std_vscanf_defined
#endif /* __NO_STDSTREAMS || (!__CRT_HAVE_vfscanf && !__CRT_HAVE__vfscanf && !__CRT_HAVE__vfscanf_s && !__CRT_HAVE__IO_vfscanf && !__CRT_HAVE_vfscanf_unlocked && !__CRT_HAVE___vfscanf && ((!__CRT_HAVE_fgetc && !__CRT_HAVE_getc && !__CRT_HAVE__IO_getc && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && (!__CRT_DOS || !__CRT_HAVE__filbuf) && !__CRT_HAVE_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock && !__CRT_HAVE__IO_fread) || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock))) */
#endif /* !... */
#endif /* !__std_vscanf_defined */
#endif /* __USE_ISOC99 || __USE_DOS */

#if __has_builtin(__builtin_fscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fscanf) && __has_builtin(__builtin_va_arg_pack)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CEIDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fscanf,(FILE *__restrict __stream, char const *__restrict __format, ...),{ return __builtin_fscanf(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_fscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fscanf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fscanf_unlocked");
#elif defined(__CRT_HAVE_fscanf)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fscanf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fscanf");
#elif defined(__CRT_HAVE_fscanf_unlocked)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fscanf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fscanf_unlocked");
#elif defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
__NAMESPACE_STD_END
#include <local/stdio/fscanf.h>
__NAMESPACE_STD_BEGIN
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(fscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fscanf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fscanf))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define fscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fscanf))
#endif /* !__cplusplus */
#endif /* ... */
#if __has_builtin(__builtin_scanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scanf) && __has_builtin(__builtin_va_arg_pack)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CEIDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,scanf,(char const *__restrict __format, ...),{ return __builtin_scanf(__format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_scanf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL scanf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("scanf_unlocked");
#elif defined(__CRT_HAVE_scanf)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL scanf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("scanf");
#elif defined(__CRT_HAVE_scanf_unlocked)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL scanf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("scanf_unlocked");
#else /* ... */
__NAMESPACE_STD_END
#include <__crt.h>
__NAMESPACE_STD_BEGIN
#if defined(__CRT_HAVE_vscanf) || defined(__CRT_HAVE__vscanf) || defined(__CRT_HAVE_vscanf_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
__NAMESPACE_STD_END
#include <local/stdio/scanf.h>
__NAMESPACE_STD_BEGIN
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(scanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL scanf)(char const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scanf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scanf))
#endif /* !__cplusplus */
#endif /* __CRT_HAVE_vscanf || __CRT_HAVE__vscanf || __CRT_HAVE_vscanf_unlocked || (!__NO_STDSTREAMS && (__CRT_HAVE_vfscanf || __CRT_HAVE__vfscanf || __CRT_HAVE__vfscanf_s || __CRT_HAVE__IO_vfscanf || __CRT_HAVE_vfscanf_unlocked || __CRT_HAVE___vfscanf || ((__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock)))) */
#endif /* !... */

#if !defined(__USE_ISOC11) || (defined(__cplusplus) && __cplusplus <= 201103L)
#ifndef __std_gets_defined
#define __std_gets_defined 1
#ifdef __gets_defined
__NAMESPACE_GLB_USING_OR_IMPL(gets, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_DEPRECATED("No buffer size checks (use `fgets\' instead)") __ATTR_NONNULL((1)) char *(__LIBCCALL gets)(char *__restrict __buf) __THROWS(...) { return (:: gets)(__buf); })
#elif defined(__CRT_HAVE_gets)
__CDECLARE(__ATTR_WUNUSED __ATTR_DEPRECATED("No buffer size checks (use `fgets\' instead)") __ATTR_NONNULL((1)),char *,__THROWING,gets,(char *__restrict __buf),(__buf))
#elif defined(__CRT_HAVE__IO_gets)
__CREDIRECT(__ATTR_WUNUSED __ATTR_DEPRECATED("No buffer size checks (use `fgets\' instead)") __ATTR_NONNULL((1)),char *,__THROWING,gets,(char *__restrict __buf),_IO_gets,(__buf))
#else /* ... */
__NAMESPACE_STD_END
#include <__crt.h>
__NAMESPACE_STD_BEGIN
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgets) || defined(__CRT_HAVE_fgets_unlocked) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))))
__NAMESPACE_STD_END
#include <local/stdio/gets.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(gets, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_DEPRECATED("No buffer size checks (use `fgets\' instead)") __ATTR_NONNULL((1)) char *(__LIBCCALL gets)(char *__restrict __buf) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gets))(__buf); })
#else /* !__NO_STDSTREAMS && (__CRT_HAVE_fgets || __CRT_HAVE_fgets_unlocked || ((__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked))) */
#undef __std_gets_defined
#endif /* __NO_STDSTREAMS || (!__CRT_HAVE_fgets && !__CRT_HAVE_fgets_unlocked && ((!__CRT_HAVE_fgetc && !__CRT_HAVE_getc && !__CRT_HAVE__IO_getc && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && (!__CRT_DOS || !__CRT_HAVE__filbuf) && !__CRT_HAVE_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock && !__CRT_HAVE__IO_fread) || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock) || (!__CRT_HAVE_ferror && !__CRT_HAVE__IO_ferror && !__CRT_HAVE_ferror_unlocked))) */
#endif /* !... */
#endif /* !__std_gets_defined */
#endif /* !__USE_ISOC11 || __cplusplus <= 201103L */

#if defined(__USE_ISOC99) || defined(__USE_DOS)
#ifndef __std_vsscanf_defined
#define __std_vsscanf_defined 1
#ifdef __vsscanf_defined
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__NAMESPACE_GLB_USING_OR_IMPL(vsscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsscanf)(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args) { return (:: vsscanf)(__input, __format, __args); })
#elif __has_builtin(__builtin_vsscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vsscanf)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__CEIDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsscanf,(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args),{ return __builtin_vsscanf(__input, __format, __args); })
#elif defined(__CRT_HAVE_vsscanf)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsscanf,(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args),(__input,__format,__args))
#elif defined(__CRT_HAVE__vsscanf)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsscanf,(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args),_vsscanf,(__input,__format,__args))
#elif defined(__CRT_HAVE__vsscanf_s)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsscanf,(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args),_vsscanf_s,(__input,__format,__args))
#elif defined(__CRT_HAVE___vsscanf)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsscanf,(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args),__vsscanf,(__input,__format,__args))
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdio/vsscanf.h>
__NAMESPACE_STD_BEGIN
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__NAMESPACE_LOCAL_USING_OR_IMPL(vsscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsscanf)(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsscanf))(__input, __format, __args); })
#endif /* !... */
#endif /* !__std_vsscanf_defined */
#endif /* __USE_ISOC99 || __USE_DOS */

#if __has_builtin(__builtin_sscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sscanf) && __has_builtin(__builtin_va_arg_pack)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__CEIDECLARE(__ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,sscanf,(char const *__restrict __input, char const *__restrict __format, ...),{ return __builtin_sscanf(__input, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_sscanf)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL sscanf)(char const *__restrict __input, char const *__restrict __format, ...) __CASMNAME_SAME("sscanf");
#elif defined(__CRT_HAVE__IO_sscanf)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL sscanf)(char const *__restrict __input, char const *__restrict __format, ...) __CASMNAME("_IO_sscanf");
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdio/sscanf.h>
__NAMESPACE_STD_BEGIN
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(sscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL sscanf)(char const *__restrict __input, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sscanf))(__input, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define sscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sscanf))
#endif /* !__cplusplus */
#endif /* !... */
#if __has_builtin(__builtin_vsprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vsprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__CEIDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vsprintf,(char *__restrict __dest, char const *__restrict __format, __builtin_va_list __args),{ return __builtin_vsprintf(__dest, __format, __args); })
#elif defined(__CRT_HAVE_vsprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vsprintf,(char *__restrict __dest, char const *__restrict __format, __builtin_va_list __args),(__dest,__format,__args))
#elif defined(__CRT_HAVE__IO_vsprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vsprintf,(char *__restrict __dest, char const *__restrict __format, __builtin_va_list __args),_IO_vsprintf,(__dest,__format,__args))
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdio/vsprintf.h>
__NAMESPACE_STD_BEGIN
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__NAMESPACE_LOCAL_USING_OR_IMPL(vsprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL vsprintf)(char *__restrict __dest, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsprintf))(__dest, __format, __args); })
#endif /* !... */
#if __has_builtin(__builtin_sprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sprintf) && __has_builtin(__builtin_va_arg_pack)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__CEIDECLARE(__ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,sprintf,(char *__restrict __buf, char const *__restrict __format, ...),{ return __builtin_sprintf(__buf, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_sprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME_SAME("sprintf");
#elif defined(__CRT_HAVE__IO_sprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("_IO_sprintf");
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdio/sprintf.h>
__NAMESPACE_STD_BEGIN
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(sprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL sprintf)(char *__restrict __buf, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sprintf))(__buf, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define sprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sprintf))
#endif /* !__cplusplus */
#endif /* !... */

#if defined(__USE_ISOC99) || defined(__USE_UNIX98) || defined(__USE_DOS)
#ifndef __std_vsnprintf_defined
#define __std_vsnprintf_defined 1
#ifdef __vsnprintf_defined
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__NAMESPACE_GLB_USING_OR_IMPL(vsnprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsnprintf)(char *__restrict __buf, size_t __buflen, char const *__restrict __format, __builtin_va_list __args) { return (:: vsnprintf)(__buf, __buflen, __format, __args); })
#elif __has_builtin(__builtin_vsnprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vsnprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__CEIDECLARE(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsnprintf,(char *__restrict __buf, size_t __buflen, char const *__restrict __format, __builtin_va_list __args),{ return __builtin_vsnprintf(__buf, __buflen, __format, __args); })
#elif defined(__CRT_HAVE_vsnprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__CDECLARE(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsnprintf,(char *__restrict __buf, size_t __buflen, char const *__restrict __format, __builtin_va_list __args),(__buf,__buflen,__format,__args))
#elif defined(__CRT_HAVE___vsnprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__CREDIRECT(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsnprintf,(char *__restrict __buf, size_t __buflen, char const *__restrict __format, __builtin_va_list __args),__vsnprintf,(__buf,__buflen,__format,__args))
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdio/vsnprintf.h>
__NAMESPACE_STD_BEGIN
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__NAMESPACE_LOCAL_USING_OR_IMPL(vsnprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsnprintf)(char *__restrict __buf, size_t __buflen, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsnprintf))(__buf, __buflen, __format, __args); })
#endif /* !... */
#endif /* !__std_vsnprintf_defined */
#ifndef __std_snprintf_defined
#define __std_snprintf_defined 1
#ifdef __snprintf_defined
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__NAMESPACE_GLB_USING_OR_IMPL(snprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL snprintf)(char *__restrict __buf, size_t __buflen, char const *__restrict __format, ...) { return (:: snprintf)(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#elif __has_builtin(__builtin_snprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_snprintf) && __has_builtin(__builtin_va_arg_pack)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__CEIDECLARE(__ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,snprintf,(char *__restrict __buf, size_t __buflen, char const *__restrict __format, ...),{ return __builtin_snprintf(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_snprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__LIBC __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL snprintf)(char *__restrict __buf, size_t __buflen, char const *__restrict __format, ...) __CASMNAME_SAME("snprintf");
#else /* ... */
__NAMESPACE_STD_END
#include <local/stdio/snprintf.h>
__NAMESPACE_STD_BEGIN
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(snprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL snprintf)(char *__restrict __buf, size_t __buflen, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(snprintf))(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define snprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(snprintf))
#endif /* !__cplusplus */
#endif /* !... */
#endif /* !__std_snprintf_defined */
#endif /* __USE_ISOC99 || __USE_UNIX98 || __USE_DOS */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#if !defined(__remove_defined) && defined(__std_remove_defined)
#define __remove_defined 1
__NAMESPACE_STD_USING(remove)
#endif /* !__remove_defined && __std_remove_defined */
#if !defined(__rename_defined) && defined(__std_rename_defined)
#define __rename_defined 1
__NAMESPACE_STD_USING(rename)
#endif /* !__rename_defined && __std_rename_defined */
#ifdef __CRT_HAVE_tmpnam
__NAMESPACE_STD_USING(tmpnam)
#endif /* __CRT_HAVE_tmpnam */
#if defined(__CRT_HAVE_fclose) || defined(__CRT_HAVE__fclose_nolock) || defined(__CRT_HAVE__IO_fclose)
__NAMESPACE_STD_USING(fclose)
#endif /* __CRT_HAVE_fclose || __CRT_HAVE__fclose_nolock || __CRT_HAVE__IO_fclose */
__NAMESPACE_STD_USING(fflush)
#include <asm/crt/stdio.h>
#if defined(__CRT_HAVE_setbuf) || (defined(___IOFBF) && defined(___IONBF) && defined(__BUFSIZ) && (defined(__CRT_HAVE_setvbuf) || defined(__CRT_HAVE__IO_setvbuf) || defined(__CRT_HAVE_setvbuf_unlocked)))
__NAMESPACE_STD_USING(setbuf)
#endif /* __CRT_HAVE_setbuf || (___IOFBF && ___IONBF && __BUFSIZ && (__CRT_HAVE_setvbuf || __CRT_HAVE__IO_setvbuf || __CRT_HAVE_setvbuf_unlocked)) */
#if defined(__CRT_HAVE_setvbuf) || defined(__CRT_HAVE__IO_setvbuf) || defined(__CRT_HAVE_setvbuf_unlocked)
__NAMESPACE_STD_USING(setvbuf)
#endif /* __CRT_HAVE_setvbuf || __CRT_HAVE__IO_setvbuf || __CRT_HAVE_setvbuf_unlocked */
#if defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)
__NAMESPACE_STD_USING(fgetc)
__NAMESPACE_STD_USING(getc)
#endif /* __CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread */
#include <__crt.h>
#if (defined(__CRT_HAVE_getchar_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_getchar) || defined(__CRT_HAVE__fgetchar) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)))
__NAMESPACE_STD_USING(getchar)
#endif /* (__CRT_HAVE_getchar_unlocked && __USE_STDIO_UNLOCKED) || __CRT_HAVE_getchar || __CRT_HAVE__fgetchar || (!__NO_STDSTREAMS && (__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread)) */
#if defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_STD_USING(fputc)
__NAMESPACE_STD_USING(putc)
#endif /* __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite */
#if defined(__CRT_HAVE_putchar) || defined(__CRT_HAVE__fputchar) || defined(__CRT_HAVE_putchar_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
__NAMESPACE_STD_USING(putchar)
#endif /* __CRT_HAVE_putchar || __CRT_HAVE__fputchar || __CRT_HAVE_putchar_unlocked || (!__NO_STDSTREAMS && (__CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite)) */
#if defined(__CRT_HAVE_fgets) || defined(__CRT_HAVE_fgets_unlocked) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)))
__NAMESPACE_STD_USING(fgets)
#endif /* __CRT_HAVE_fgets || __CRT_HAVE_fgets_unlocked || ((__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked)) */
#if defined(__CRT_HAVE_fputs) || defined(__CRT_HAVE__IO_fputs) || defined(__CRT_HAVE_fputs_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_STD_USING(fputs)
#endif /* __CRT_HAVE_fputs || __CRT_HAVE__IO_fputs || __CRT_HAVE_fputs_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite */
#if defined(__CRT_HAVE_puts) || defined(__CRT_HAVE__IO_puts) || defined(__CRT_HAVE_puts_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
__NAMESPACE_STD_USING(puts)
#endif /* __CRT_HAVE_puts || __CRT_HAVE__IO_puts || __CRT_HAVE_puts_unlocked || (!__NO_STDSTREAMS && (__CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite)) */
#if defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)
__NAMESPACE_STD_USING(ungetc)
#endif /* __CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock */
#if defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)
__NAMESPACE_STD_USING(fread)
#endif /* __CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread */
#if defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_STD_USING(fwrite)
#endif /* __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite */
#if defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64)
__NAMESPACE_STD_USING(fseek)
#endif /* __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseeko64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE__fseeki64 */
#if (defined(__CRT_HAVE_ftell_unlocked) && defined(__USE_STDIO_UNLOCKED)) || (defined(__CRT_HAVE__ftell_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || (defined(__CRT_HAVE_ftello64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked)
__NAMESPACE_STD_USING(ftell)
#endif /* (__CRT_HAVE_ftell_unlocked && __USE_STDIO_UNLOCKED) || (__CRT_HAVE__ftell_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE_ftell || __CRT_HAVE__IO_ftell || (__CRT_HAVE_ftello64 && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__) || __CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked */
#if defined(__CRT_HAVE_rewind) || defined(__CRT_HAVE_rewind_unlocked) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
__NAMESPACE_STD_USING(rewind)
#endif /* __CRT_HAVE_rewind || __CRT_HAVE_rewind_unlocked || __CRT_HAVE_fseeko64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE__fseeki64 || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || __CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock */
#if defined(__CRT_HAVE_clearerr) || defined(__CRT_HAVE_clearerr_unlocked)
__NAMESPACE_STD_USING(clearerr)
#endif /* __CRT_HAVE_clearerr || __CRT_HAVE_clearerr_unlocked */
#if defined(__CRT_HAVE_feof) || defined(__CRT_HAVE__IO_feof) || defined(__CRT_HAVE_feof_unlocked)
__NAMESPACE_STD_USING(feof)
#endif /* __CRT_HAVE_feof || __CRT_HAVE__IO_feof || __CRT_HAVE_feof_unlocked */
#if defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)
__NAMESPACE_STD_USING(ferror)
#endif /* __CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked */
#if !defined(__perror_defined) && defined(__std_perror_defined)
#define __perror_defined 1
__NAMESPACE_STD_USING(perror)
#endif /* !__perror_defined && __std_perror_defined */
#if defined(__CRT_HAVE_tmpfile) || defined(__CRT_HAVE_tmpfile64)
__NAMESPACE_STD_USING(tmpfile)
#endif /* __CRT_HAVE_tmpfile || __CRT_HAVE_tmpfile64 */
#if defined(__CRT_HAVE_fopen) || defined(__CRT_HAVE__IO_fopen) || defined(__CRT_HAVE_fopen64)
__NAMESPACE_STD_USING(fopen)
#endif /* __CRT_HAVE_fopen || __CRT_HAVE__IO_fopen || __CRT_HAVE_fopen64 */
#if defined(__CRT_HAVE_freopen) || defined(__CRT_HAVE_freopen64) || defined(__CRT_HAVE_freopen_unlocked) || defined(__CRT_HAVE_freopen64_unlocked)
__NAMESPACE_STD_USING(freopen)
#endif /* __CRT_HAVE_freopen || __CRT_HAVE_freopen64 || __CRT_HAVE_freopen_unlocked || __CRT_HAVE_freopen64_unlocked */
#if defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || defined(__CRT_HAVE__IO_ftell)
__NAMESPACE_STD_USING(fgetpos)
#endif /* __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked || __CRT_HAVE_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock || __CRT_HAVE__IO_ftell */
#if defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
__NAMESPACE_STD_USING(fsetpos)
#endif /* __CRT_HAVE_fseeko64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE__fseeki64 || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || __CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock */
#if defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_STD_USING(vfprintf)
#endif /* __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite */
#if defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_STD_USING(fprintf)
#endif /* __CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite */
#if defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
__NAMESPACE_STD_USING(vprintf)
#endif /* __CRT_HAVE_vprintf || __CRT_HAVE_vprintf_s || __CRT_HAVE_vprintf_unlocked || (!__NO_STDSTREAMS && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite)) */
#if defined(__CRT_HAVE_printf) || defined(__CRT_HAVE__IO_printf) || defined(__CRT_HAVE_printf_s) || defined(__CRT_HAVE_printf_unlocked) || defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
__NAMESPACE_STD_USING(printf)
#endif /* __CRT_HAVE_printf || __CRT_HAVE__IO_printf || __CRT_HAVE_printf_s || __CRT_HAVE_printf_unlocked || __CRT_HAVE_vprintf || __CRT_HAVE_vprintf_s || __CRT_HAVE_vprintf_unlocked || (!__NO_STDSTREAMS && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite)) */
#if !defined(__vfscanf_defined) && defined(__std_vfscanf_defined)
#define __vfscanf_defined 1
__NAMESPACE_STD_USING(vfscanf)
#endif /* !__vfscanf_defined && __std_vfscanf_defined */
#if !defined(__vscanf_defined) && defined(__std_vscanf_defined)
#define __vscanf_defined 1
__NAMESPACE_STD_USING(vscanf)
#endif /* !__vscanf_defined && __std_vscanf_defined */
#if defined(__CRT_HAVE_fscanf) || defined(__CRT_HAVE_fscanf_unlocked) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
__NAMESPACE_STD_USING(fscanf)
#endif /* __CRT_HAVE_fscanf || __CRT_HAVE_fscanf_unlocked || __CRT_HAVE_vfscanf || __CRT_HAVE__vfscanf || __CRT_HAVE__vfscanf_s || __CRT_HAVE__IO_vfscanf || __CRT_HAVE_vfscanf_unlocked || __CRT_HAVE___vfscanf || ((__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock)) */
#if defined(__CRT_HAVE_scanf) || defined(__CRT_HAVE_scanf_unlocked) || defined(__CRT_HAVE_vscanf) || defined(__CRT_HAVE__vscanf) || defined(__CRT_HAVE_vscanf_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
__NAMESPACE_STD_USING(scanf)
#endif /* __CRT_HAVE_scanf || __CRT_HAVE_scanf_unlocked || __CRT_HAVE_vscanf || __CRT_HAVE__vscanf || __CRT_HAVE_vscanf_unlocked || (!__NO_STDSTREAMS && (__CRT_HAVE_vfscanf || __CRT_HAVE__vfscanf || __CRT_HAVE__vfscanf_s || __CRT_HAVE__IO_vfscanf || __CRT_HAVE_vfscanf_unlocked || __CRT_HAVE___vfscanf || ((__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock)))) */
#if !defined(__gets_defined) && defined(__std_gets_defined)
#define __gets_defined 1
__NAMESPACE_STD_USING(gets)
#endif /* !__gets_defined && __std_gets_defined */
#if !defined(__vsscanf_defined) && defined(__std_vsscanf_defined)
#define __vsscanf_defined 1
__NAMESPACE_STD_USING(vsscanf)
#endif /* !__vsscanf_defined && __std_vsscanf_defined */
__NAMESPACE_STD_USING(sscanf)
__NAMESPACE_STD_USING(vsprintf)
__NAMESPACE_STD_USING(sprintf)
#if !defined(__vsnprintf_defined) && defined(__std_vsnprintf_defined)
#define __vsnprintf_defined 1
__NAMESPACE_STD_USING(vsnprintf)
#endif /* !__vsnprintf_defined && __std_vsnprintf_defined */
#if !defined(__snprintf_defined) && defined(__std_snprintf_defined)
#define __snprintf_defined 1
__NAMESPACE_STD_USING(snprintf)
#endif /* !__snprintf_defined && __std_snprintf_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_vdprintf
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,vdprintf,(__fd_t __fd, char const *__restrict __format, __builtin_va_list __args),(__fd,__format,__args))
#elif defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)
#include <local/stdio/vdprintf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vdprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((2)) __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__LIBCCALL vdprintf)(__fd_t __fd, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vdprintf))(__fd, __format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE_dprintf
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((2)) __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__VLIBCCALL dprintf)(__fd_t __fd, char const *__restrict __format, ...) __CASMNAME_SAME("dprintf");
#elif defined(__CRT_HAVE_vdprintf) || defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)
#include <local/stdio/dprintf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(dprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((2)) __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__VLIBCCALL dprintf)(__fd_t __fd, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dprintf))(__fd, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define dprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dprintf))
#endif /* !__cplusplus */
#endif /* ... */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_ATFILE
#ifdef __CRT_HAVE_renameat
__CDECLARE(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,renameat,(__fd_t __oldfd, char const *__oldname, __fd_t __newfd, char const *__newname_or_path),(__oldfd,__oldname,__newfd,__newname_or_path))
#elif defined(__CRT_HAVE_frenameat)
#include <local/stdio/renameat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(renameat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 4)) int __NOTHROW_RPC(__LIBCCALL renameat)(__fd_t __oldfd, char const *__oldname, __fd_t __newfd, char const *__newname_or_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(renameat))(__oldfd, __oldname, __newfd, __newname_or_path); })
#endif /* ... */

#ifdef __USE_KOS
/* Remove a file or directory `FILENAME' relative to a given base directory `DIRFD' */
__CDECLARE_OPT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,removeat,(__fd_t __dirfd, char const *__filename),(__dirfd,__filename))
/* @param flags: Set of `0 | AT_DOSPATH' */
__CDECLARE_OPT(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,frenameat,(__fd_t __oldfd, char const *__oldname, __fd_t __newfd, char const *__newname_or_path, __atflag_t __flags),(__oldfd,__oldname,__newfd,__newname_or_path,__flags))
#endif /* __USE_KOS */
#endif /* __USE_ATFILE */

#ifdef __USE_MISC
#ifdef __CRT_HAVE_tmpnam_r
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,tmpnam_r,(char *__buf),(__buf))
#elif defined(__CRT_HAVE_tmpnam)
#include <local/stdio/tmpnam_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(tmpnam_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL tmpnam_r)(char *__buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tmpnam_r))(__buf); })
#endif /* ... */
#ifdef __CRT_HAVE_setbuffer
/* Specify the location and size for the buffer to-be used by `STREAM' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,setbuffer,(__FILE *__restrict __stream, char *__buf, __SIZE_TYPE__ __bufsize),(__stream,__buf,__bufsize))
#elif defined(__CRT_HAVE__IO_setbuffer)
/* Specify the location and size for the buffer to-be used by `STREAM' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,setbuffer,(__FILE *__restrict __stream, char *__buf, __SIZE_TYPE__ __bufsize),_IO_setbuffer,(__stream,__buf,__bufsize))
#elif defined(___IOFBF) && defined(___IONBF) && (defined(__CRT_HAVE_setvbuf) || defined(__CRT_HAVE__IO_setvbuf) || defined(__CRT_HAVE_setvbuf_unlocked))
#include <local/stdio/setbuffer.h>
/* Specify the location and size for the buffer to-be used by `STREAM' */
__NAMESPACE_LOCAL_USING_OR_IMPL(setbuffer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL setbuffer)(__FILE *__restrict __stream, char *__buf, __SIZE_TYPE__ __bufsize) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setbuffer))(__stream, __buf, __bufsize); })
#endif /* ... */
#ifdef __CRT_HAVE_setlinebuf
/* Change the given `STREAM' to become line-buffered */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,setlinebuf,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_setvbuf) || defined(__CRT_HAVE__IO_setvbuf) || defined(__CRT_HAVE_setvbuf_unlocked)
#include <local/stdio/setlinebuf.h>
/* Change the given `STREAM' to become line-buffered */
__NAMESPACE_LOCAL_USING_OR_IMPL(setlinebuf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL setlinebuf)(__FILE *__restrict __stream) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setlinebuf))(__stream); })
#endif /* ... */
#ifdef __CRT_HAVE_fflush_unlocked
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
__CDECLARE(,int,__THROWING,fflush_unlocked,(__FILE *__stream),(__stream))
#elif defined(__CRT_HAVE__fflush_nolock)
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(,int,__THROWING,fflush_unlocked,(__FILE *__stream),_fflush_nolock,(__stream))
#elif defined(__CRT_HAVE_fflush)
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(,int,__THROWING,fflush_unlocked,(__FILE *__stream),fflush,(__stream))
#elif defined(__CRT_HAVE__IO_fflush)
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(,int,__THROWING,fflush_unlocked,(__FILE *__stream),_IO_fflush,(__stream))
#else /* ... */
#include <local/stdio/fflush_unlocked.h>
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fflush_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL fflush_unlocked)(__FILE *__stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fflush_unlocked))(__stream); })
#endif /* !... */
#ifdef __CRT_HAVE_fread_unlocked
/* Same as `fread()', but performs I/O without acquiring a lock to `STREAM' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,fread_unlocked,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fread)
/* Same as `fread()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,fread_unlocked,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fread_nolock)
/* Same as `fread()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,fread_unlocked,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_fread_nolock,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__IO_fread)
/* Same as `fread()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,fread_unlocked,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_IO_fread,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf))
#include <local/stdio/fread_unlocked.h>
/* Same as `fread()', but performs I/O without acquiring a lock to `STREAM' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fread_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 4)) __SIZE_TYPE__ (__LIBCCALL fread_unlocked)(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fread_unlocked))(__buf, __elemsize, __elemcount, __stream); })
#endif /* ... */
#ifdef __CRT_HAVE_fwrite_unlocked
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,fwrite_unlocked,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fwrite)
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,fwrite_unlocked,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fwrite_nolock)
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,fwrite_unlocked,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_fwrite_nolock,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__IO_fwrite)
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,fwrite_unlocked,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_IO_fwrite,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)
#include <local/stdio/fwrite_unlocked.h>
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fwrite_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 4)) __SIZE_TYPE__ (__LIBCCALL fwrite_unlocked)(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwrite_unlocked))(__buf, __elemsize, __elemcount, __stream); })
#endif /* ... */
#if defined(__CRT_HAVE_feof_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Same as `feof()', but performs I/O without acquiring a lock to `STREAM' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,feof_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_feof)
/* Same as `feof()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,feof_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),feof,(__stream))
#elif defined(__CRT_HAVE__IO_feof)
/* Same as `feof()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,feof_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),_IO_feof,(__stream))
#elif defined(__CRT_HAVE_feof_unlocked)
/* Same as `feof()', but performs I/O without acquiring a lock to `STREAM' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,feof_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_ferror_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Same as `ferror()', but performs I/O without acquiring a lock to `STREAM' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ferror_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_ferror)
/* Same as `ferror()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ferror_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),ferror,(__stream))
#elif defined(__CRT_HAVE__IO_ferror)
/* Same as `ferror()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ferror_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),_IO_ferror,(__stream))
#elif defined(__CRT_HAVE_ferror_unlocked)
/* Same as `ferror()', but performs I/O without acquiring a lock to `STREAM' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ferror_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_clearerr_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Same as `clearerr()', but performs I/O without acquiring a lock to `STREAM' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,clearerr_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_clearerr)
/* Same as `clearerr()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,clearerr_unlocked,(__FILE *__restrict __stream),clearerr,(__stream))
#elif defined(__CRT_HAVE_clearerr_unlocked)
/* Same as `clearerr()', but performs I/O without acquiring a lock to `STREAM' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,clearerr_unlocked,(__FILE *__restrict __stream),(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fileno_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Same as `fileno()', but performs I/O without acquiring a lock to `STREAM' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,fileno_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_fileno)
/* Same as `fileno()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,fileno_unlocked,(__FILE *__restrict __stream),fileno,(__stream))
#elif defined(__CRT_HAVE__fileno)
/* Same as `fileno()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,fileno_unlocked,(__FILE *__restrict __stream),_fileno,(__stream))
#elif defined(__CRT_HAVE_fileno_unlocked)
/* Same as `fileno()', but performs I/O without acquiring a lock to `STREAM' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,fileno_unlocked,(__FILE *__restrict __stream),(__stream))
#endif /* ... */
#ifdef __CRT_HAVE_fgetc_unlocked
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fgetc_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc_unlocked,(__FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc_unlocked,(__FILE *__restrict __stream),getc,(__stream))
#elif defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc_unlocked,(__FILE *__restrict __stream),fgetc,(__stream))
#elif defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc_unlocked,(__FILE *__restrict __stream),_IO_getc,(__stream))
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)
#include <local/stdio/fgetc_unlocked.h>
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetc_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fgetc_unlocked)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc_unlocked))(__stream); })
#endif /* ... */
#if __has_builtin(__builtin_fputc_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CEIDECLARE(__ATTR_NONNULL((2)),int,__THROWING,fputc_unlocked,(int __ch, __FILE *__restrict __stream),{ return __builtin_fputc_unlocked(__ch, __stream); })
#elif defined(__CRT_HAVE_fputc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CDECLARE(__ATTR_NONNULL((2)),int,__THROWING,fputc_unlocked,(int __ch, __FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE_putc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc_unlocked,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc_unlocked,(int __ch, __FILE *__restrict __stream),putc,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc_unlocked,(int __ch, __FILE *__restrict __stream),fputc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc_unlocked,(int __ch, __FILE *__restrict __stream),_IO_putc,(__ch,__stream))
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s)
#include <local/stdio/fputc_unlocked.h>
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fputc_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int (__LIBCCALL fputc_unlocked)(int __ch, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc_unlocked))(__ch, __stream); })
#endif /* ... */
#endif /* __USE_MISC */

#if defined(__USE_MISC) || defined(__USE_XOPEN) || defined(__USE_DOS)
#ifdef __CRT_HAVE_tempnam
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,tempnam,(char const *__dir, char const *__pfx),(__dir,__pfx))
#elif defined(__CRT_HAVE__tempnam)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,tempnam,(char const *__dir, char const *__pfx),_tempnam,(__dir,__pfx))
#endif /* ... */
#endif /* __USE_MISC || __USE_XOPEN || __USE_DOS */

#if defined(__USE_POSIX) || defined(__USE_DOS)
#ifdef __CRT_HAVE_fdopen
/* Open a new file stream by inheriting a given file descriptor `FD'
 * Note that upon success (`return != NULL'), the given `FD'
 * will be `close()'d once `fclose(return)' is called */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),__FILE *,__NOTHROW_NCX,fdopen,(__fd_t __fd, char const *__restrict __modes),(__fd,__modes))
#elif defined(__CRT_HAVE__fdopen)
/* Open a new file stream by inheriting a given file descriptor `FD'
 * Note that upon success (`return != NULL'), the given `FD'
 * will be `close()'d once `fclose(return)' is called */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__FILE *,__NOTHROW_NCX,fdopen,(__fd_t __fd, char const *__restrict __modes),_fdopen,(__fd,__modes))
#elif defined(__CRT_HAVE__IO_fdopen)
/* Open a new file stream by inheriting a given file descriptor `FD'
 * Note that upon success (`return != NULL'), the given `FD'
 * will be `close()'d once `fclose(return)' is called */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__FILE *,__NOTHROW_NCX,fdopen,(__fd_t __fd, char const *__restrict __modes),_IO_fdopen,(__fd,__modes))
#endif /* ... */
#if defined(__CRT_HAVE_fileno_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Return the underlying file descriptor number used by `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#elif defined(__CRT_HAVE_fileno)
/* Return the underlying file descriptor number used by `STREAM' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,fileno,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__fileno)
/* Return the underlying file descriptor number used by `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,fileno,(__FILE *__restrict __stream),_fileno,(__stream))
#elif defined(__CRT_HAVE_fileno_unlocked)
/* Return the underlying file descriptor number used by `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#endif /* ... */
#endif /* __USE_POSIX || __USE_DOS */

#ifdef __USE_XOPEN2K8
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__FILE *,__NOTHROW_NCX,fmemopen,(void *__mem, __SIZE_TYPE__ __len, char const *__modes),(__mem,__len,__modes))
__CDECLARE_OPT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,open_memstream,(char **__bufloc, __SIZE_TYPE__ *__sizeloc),(__bufloc,__sizeloc))
#if defined(__CRT_HAVE_getdelim_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,__getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),getdelim_unlocked,(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE_getdelim)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,__getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),getdelim,(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE_getdelim_unlocked)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,__getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),getdelim_unlocked,(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE___getdelim)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,__getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
#include <local/stdio/getdelim.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)) __SSIZE_TYPE__ (__LIBCCALL __getdelim)(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getdelim))(__lineptr, __pcount, __delimiter, __stream); }
#endif /* ... */
#if defined(__CRT_HAVE_getdelim_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),getdelim_unlocked,(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE_getdelim)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE_getdelim_unlocked)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),getdelim_unlocked,(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE___getdelim)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),__getdelim,(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
#include <local/stdio/getdelim.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getdelim, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)) __SSIZE_TYPE__ (__LIBCCALL getdelim)(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getdelim))(__lineptr, __pcount, __delimiter, __stream); })
#endif /* ... */
#if defined(__CRT_HAVE_getline_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__SSIZE_TYPE__,__THROWING,getline,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream),getline_unlocked,(__lineptr,__pcount,__stream))
#elif defined(__CRT_HAVE_getline)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__SSIZE_TYPE__,__THROWING,getline,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream),(__lineptr,__pcount,__stream))
#elif defined(__CRT_HAVE_getline_unlocked)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__SSIZE_TYPE__,__THROWING,getline,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream),getline_unlocked,(__lineptr,__pcount,__stream))
#elif defined(__CRT_HAVE_getdelim) || defined(__CRT_HAVE_getdelim_unlocked) || defined(__CRT_HAVE___getdelim) || (defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
#include <local/stdio/getline.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getline, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)) __SSIZE_TYPE__ (__LIBCCALL getline)(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getline))(__lineptr, __pcount, __stream); })
#endif /* ... */
#endif /* __USE_XOPEN2K8 */

#if defined(__USE_POSIX) || defined(__USE_REENTRANT)
#ifdef __CRT_HAVE_fgetc_unlocked
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc_unlocked,(__FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,getc_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc_unlocked,(__FILE *__restrict __stream),getc,(__stream))
#elif defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc_unlocked,(__FILE *__restrict __stream),fgetc,(__stream))
#elif defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc_unlocked,(__FILE *__restrict __stream),_IO_getc,(__stream))
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)
#include <local/stdio/fgetc_unlocked.h>
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL getc_unlocked)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc_unlocked))(__stream); }
#endif /* ... */
#if __has_builtin(__builtin_fputc_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CEIREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc_unlocked,(int __ch, __FILE *__restrict __stream),fputc_unlocked,{ return __builtin_fputc_unlocked(__ch, __stream); })
#elif defined(__CRT_HAVE_fputc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc_unlocked,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_putc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CDECLARE(__ATTR_NONNULL((2)),int,__THROWING,putc_unlocked,(int __ch, __FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc_unlocked,(int __ch, __FILE *__restrict __stream),putc,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc_unlocked,(int __ch, __FILE *__restrict __stream),fputc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc_unlocked,(int __ch, __FILE *__restrict __stream),_IO_putc,(__ch,__stream))
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s)
#include <local/stdio/fputc_unlocked.h>
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int (__LIBCCALL putc_unlocked)(int __ch, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc_unlocked))(__ch, __stream); }
#endif /* ... */
#ifdef __CRT_HAVE_getchar_unlocked
/* Same as `getchar()', but performs I/O without acquiring a lock to `stdin' */
__CDECLARE(,int,__THROWING,getchar_unlocked,(void),())
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread))
#include <local/stdio/getchar_unlocked.h>
/* Same as `getchar()', but performs I/O without acquiring a lock to `stdin' */
__NAMESPACE_LOCAL_USING_OR_IMPL(getchar_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL getchar_unlocked)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getchar_unlocked))(); })
#endif /* ... */
#if __has_builtin(__builtin_putchar_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_putchar_unlocked)
/* Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
__CEIDECLARE(,int,__THROWING,putchar_unlocked,(int __ch),{ return __builtin_putchar_unlocked(__ch); })
#elif defined(__CRT_HAVE_putchar_unlocked)
/* Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
__CDECLARE(,int,__THROWING,putchar_unlocked,(int __ch),(__ch))
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s))
#include <local/stdio/putchar_unlocked.h>
/* Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
__NAMESPACE_LOCAL_USING_OR_IMPL(putchar_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL putchar_unlocked)(int __ch) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putchar_unlocked))(__ch); })
#endif /* ... */
#ifdef __CRT_HAVE_flockfile
/* Acquire a lock to `STREAM' and block until doing so succeeds */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC,flockfile,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__lock_file)
/* Acquire a lock to `STREAM' and block until doing so succeeds */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC,flockfile,(__FILE *__restrict __stream),_lock_file,(__stream))
#elif defined(__CRT_HAVE__IO_flockfile)
/* Acquire a lock to `STREAM' and block until doing so succeeds */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC,flockfile,(__FILE *__restrict __stream),_IO_flockfile,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE_funlockfile
/* Release a previously acquired lock from `STREAM' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,funlockfile,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__unlock_file)
/* Release a previously acquired lock from `STREAM' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,funlockfile,(__FILE *__restrict __stream),_unlock_file,(__stream))
#elif defined(__CRT_HAVE__IO_funlockfile)
/* Release a previously acquired lock from `STREAM' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,funlockfile,(__FILE *__restrict __stream),_IO_funlockfile,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE_ftrylockfile
/* Try to acquire a lock to `STREAM' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ftrylockfile,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__IO_ftrylockfile)
/* Try to acquire a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ftrylockfile,(__FILE *__restrict __stream),_IO_ftrylockfile,(__stream))
#endif /* ... */
#endif /* __USE_POSIX || __USE_REENTRANT */

#ifdef __USE_POSIX
#ifndef __ctermid_defined
#define __ctermid_defined 1
#ifdef __CRT_HAVE_ctermid
__CDECLARE(,char *,__NOTHROW_NCX,ctermid,(char *__s),(__s))
#else /* __CRT_HAVE_ctermid */
#undef __ctermid_defined
#endif /* !__CRT_HAVE_ctermid */
#endif /* !__ctermid_defined */
#endif /* __USE_POSIX */

#ifdef __USE_REENTRANT
#ifndef __ctermid_r_defined
#define __ctermid_r_defined 1
#ifdef __CRT_HAVE_ctermid_r
/* Same as `ctermid', but return `NULL' when `S' is `NULL' */
__CDECLARE(,char *,__NOTHROW_NCX,ctermid_r,(char *__s),(__s))
#elif defined(__CRT_HAVE_ctermid)
#include <local/unistd/ctermid_r.h>
/* Same as `ctermid', but return `NULL' when `S' is `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ctermid_r, __FORCELOCAL __ATTR_ARTIFICIAL char *__NOTHROW_NCX(__LIBCCALL ctermid_r)(char *__s) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctermid_r))(__s); })
#else /* ... */
#undef __ctermid_r_defined
#endif /* !... */
#endif /* !__ctermid_r_defined */
#endif /* __USE_REENTRANT */

#ifdef __USE_XOPEN
#ifndef __cuserid_defined
#define __cuserid_defined 1
#ifdef __CRT_HAVE_cuserid
/* Return the name of the current user (`getpwuid(geteuid())'), storing
 * that name in `S'. When `S' is NULL, a static buffer is used instead */
__CDECLARE(,char *,__NOTHROW_NCX,cuserid,(char *__s),(__s))
#else /* __CRT_HAVE_cuserid */
#undef __cuserid_defined
#endif /* !__CRT_HAVE_cuserid */
#endif /* !__cuserid_defined */
#endif /* Use X/Open, but not issue 6.  */

#ifdef __USE_POSIX2
#ifdef __CRT_HAVE_popen
/* Open and return a new process I/O stream for executing `COMMAND' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,popen,(char const *__command, char const *__modes),(__command,__modes))
#elif defined(__CRT_HAVE__popen)
/* Open and return a new process I/O stream for executing `COMMAND' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,popen,(char const *__command, char const *__modes),_popen,(__command,__modes))
#elif defined(__CRT_HAVE__IO_popen)
/* Open and return a new process I/O stream for executing `COMMAND' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,popen,(char const *__command, char const *__modes),_IO_popen,(__command,__modes))
#endif /* ... */
#ifdef __CRT_HAVE_pclose
/* Close a process I/O file `STREAM' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pclose,(__FILE *__stream),(__stream))
#elif defined(__CRT_HAVE__pclose)
/* Close a process I/O file `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pclose,(__FILE *__stream),_pclose,(__stream))
#endif /* ... */
#endif /* __USE_POSIX2 */

#if (defined(__USE_MISC) || defined(__USE_DOS) || \
     (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K)))
#if defined(__CRT_HAVE_getw_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Similar to `getc()', but read 2 bytes */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getw,(__FILE *__restrict __stream),getw_unlocked,(__stream))
#elif defined(__CRT_HAVE_getw)
/* Similar to `getc()', but read 2 bytes */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,getw,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__getw)
/* Similar to `getc()', but read 2 bytes */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getw,(__FILE *__restrict __stream),_getw,(__stream))
#elif defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)
#include <local/stdio/getw.h>
/* Similar to `getc()', but read 2 bytes */
__NAMESPACE_LOCAL_USING_OR_IMPL(getw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL getw)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getw))(__stream); })
#endif /* ... */
#if defined(__CRT_HAVE_putw_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putw,(int __w, __FILE *__restrict __stream),putw_unlocked,(__w,__stream))
#elif defined(__CRT_HAVE_putw)
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
__CDECLARE(__ATTR_NONNULL((2)),int,__THROWING,putw,(int __w, __FILE *__restrict __stream),(__w,__stream))
#elif defined(__CRT_HAVE__putw)
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putw,(int __w, __FILE *__restrict __stream),_putw,(__w,__stream))
#elif defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
#include <local/stdio/putw.h>
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
__NAMESPACE_LOCAL_USING_OR_IMPL(putw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int (__LIBCCALL putw)(int __w, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putw))(__w, __stream); })
#endif /* ... */
#endif /* __USE_MISC || __USE_DOS || (__USE_XOPEN && !__USE_XOPEN2K) */

#if defined(__USE_GNU) || defined(__USE_DOS)
#ifdef __CRT_HAVE_fcloseall
/* Alias for `_fcloseall()' */
__CDECLARE(,int,__THROWING,fcloseall,(void),())
#elif defined(__CRT_HAVE__fcloseall)
/* Alias for `_fcloseall()' */
__CREDIRECT(,int,__THROWING,fcloseall,(void),_fcloseall,())
#endif /* ... */
#endif /* __USE_GNU || __USE_DOS */

#ifdef __USE_GNU
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__FILE *,__NOTHROW_NCX,fopencookie,(void *__restrict __magic_cookie, char const *__restrict __modes, _IO_cookie_io_functions_t __io_funcs),(__magic_cookie,__modes,__io_funcs))
#ifdef __CRT_HAVE_fgets_unlocked
/* Same as `fgets()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char *,__THROWING,fgets_unlocked,(char *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgets)
/* Same as `fgets()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char *,__THROWING,fgets_unlocked,(char *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgets,(__buf,__bufsize,__stream))
#elif (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))
#include <local/stdio/fgets_unlocked.h>
/* Same as `fgets()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgets_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) char *(__LIBCCALL fgets_unlocked)(char *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgets_unlocked))(__buf, __bufsize, __stream); })
#endif /* ... */
#if __has_builtin(__builtin_fputs_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputs_unlocked)
/* Same as `fputs()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CEIDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputs_unlocked,(char const *__restrict __string, __FILE *__restrict __stream),{ return __builtin_fputs_unlocked(__string, __stream); })
#elif defined(__CRT_HAVE_fputs_unlocked)
/* Same as `fputs()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputs_unlocked,(char const *__restrict __string, __FILE *__restrict __stream),(__string,__stream))
#elif defined(__CRT_HAVE_fputs)
/* Same as `fputs()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputs_unlocked,(char const *__restrict __string, __FILE *__restrict __stream),fputs,(__string,__stream))
#elif defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)
#include <local/stdio/fputs_unlocked.h>
/* Same as `fputs()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fputs_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL fputs_unlocked)(char const *__restrict __string, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputs_unlocked))(__string, __stream); })
#endif /* ... */

struct obstack;
__CDECLARE_OPT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,obstack_vprintf,(struct obstack *__restrict __obstack_, char const *__restrict __format, __builtin_va_list __args),(__obstack_,__format,__args))
#ifdef __CRT_HAVE_obstack_printf
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__VLIBCCALL obstack_printf)(struct obstack *__restrict __obstack_, char const *__restrict __format, ...) __CASMNAME_SAME("obstack_printf");
#elif defined(__CRT_HAVE_obstack_vprintf)
#include <local/stdio/obstack_printf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(obstack_printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__VLIBCCALL obstack_printf)(struct obstack *__restrict __obstack_, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(obstack_printf))(__obstack_, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define obstack_printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(obstack_printf))
#endif /* !__cplusplus */
#endif /* ... */
#endif /* __USE_GNU */
#if defined(__USE_LARGEFILE) || defined(__USE_XOPEN2K)
#if defined(__CRT_HAVE_fseeko64_unlocked) && defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)
/* Change the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)
/* Change the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && defined(__USE_STDIO_UNLOCKED) && !defined(__USE_FILE_OFFSET64)
/* Change the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek_unlocked) && ((defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__))
/* Change the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && ((defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__))
/* Change the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64) && defined(__USE_FILE_OFFSET64)
/* Change the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64) && defined(__USE_FILE_OFFSET64)
/* Change the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && !defined(__USE_FILE_OFFSET64)
/* Change the current in-file position of `STREAM' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek) && ((defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__))
/* Change the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseek,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek_unlocked) && ((defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__))
/* Change the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && ((defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__))
/* Change the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && defined(__USE_FILE_OFFSET64)
/* Change the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && defined(__USE_FILE_OFFSET64)
/* Change the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && !defined(__USE_FILE_OFFSET64)
/* Change the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
#include <local/stdio/fseeko.h>
/* Change the current in-file position of `STREAM' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fseeko, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fseeko)(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fseeko))(__stream, __off, __whence); })
#endif /* ... */
#if defined(__CRT_HAVE_ftello64_unlocked) && defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)
/* Return the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)
/* Return the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && defined(__USE_STDIO_UNLOCKED) && !defined(__USE_FILE_OFFSET64)
/* Return the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell_unlocked) && ((defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__))
/* Return the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && ((defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__))
/* Return the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello64) && defined(__USE_FILE_OFFSET64)
/* Return the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE__ftelli64) && defined(__USE_FILE_OFFSET64)
/* Return the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_ftello) && !defined(__USE_FILE_OFFSET64)
/* Return the current in-file position of `STREAM' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_ftell) && ((defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__))
/* Return the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),ftell,(__stream))
#elif defined(__CRT_HAVE__IO_ftell) && ((defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__))
/* Return the current in-file position of `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || defined(__CRT_HAVE__IO_ftell)
#include <local/stdio/ftello.h>
/* Return the current in-file position of `STREAM' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ftello, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __FS_TYPE(off) (__LIBCCALL ftello)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftello))(__stream); })
#endif /* ... */
#endif /* __USE_LARGEFILE || __USE_XOPEN2K */

#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_tmpfile64
/* 64-bit variant of `tmpfile' */
__CDECLARE(__ATTR_WUNUSED,__FILE *,__NOTHROW_RPC,tmpfile64,(void),())
#elif defined(__CRT_HAVE_tmpfile)
/* 64-bit variant of `tmpfile' */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_RPC,tmpfile64,(void),tmpfile,())
#endif /* ... */
#if defined(__CRT_HAVE_fseeko64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && defined(__USE_STDIO_UNLOCKED)
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64)
/* 64-bit variant of `fseeko' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64)
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked)
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock)
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
#include <local/stdio/fseeko64.h>
/* 64-bit variant of `fseeko' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fseeko64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fseeko64)(__FILE *__restrict __stream, __off64_t __off, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fseeko64))(__stream, __off, __whence); })
#endif /* ... */
#if defined(__CRT_HAVE_ftello64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && defined(__USE_STDIO_UNLOCKED)
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftell_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello64)
/* 64-bit variant of `ftello' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__ftelli64)
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked)
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock)
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),ftell,(__stream))
#elif defined(__CRT_HAVE__IO_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || defined(__CRT_HAVE__IO_ftell)
#include <local/stdio/ftello64.h>
/* 64-bit variant of `ftello' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ftello64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __off64_t (__LIBCCALL ftello64)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftello64))(__stream); })
#endif /* ... */
#ifdef __CRT_HAVE_fopen64
/* 64-bit variant of `fopen' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,fopen64,(char const *__restrict __filename, char const *__restrict __modes),(__filename,__modes))
#elif defined(__CRT_HAVE_fopen)
/* 64-bit variant of `fopen' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,fopen64,(char const *__restrict __filename, char const *__restrict __modes),fopen,(__filename,__modes))
#elif defined(__CRT_HAVE__IO_fopen)
#include <local/stdio/fopen64.h>
/* 64-bit variant of `fopen' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fopen64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __FILE *__NOTHROW_RPC(__LIBCCALL fopen64)(char const *__restrict __filename, char const *__restrict __modes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fopen64))(__filename, __modes); })
#endif /* ... */
#if defined(__CRT_HAVE_freopen64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* 64-bit variant of `freopen' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen64_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64)
/* 64-bit variant of `freopen' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* 64-bit variant of `freopen' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen)
/* 64-bit variant of `freopen' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen_unlocked)
/* 64-bit variant of `freopen' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64_unlocked)
/* 64-bit variant of `freopen' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen64_unlocked,(__filename,__modes,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fgetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* 64-bit variant of `fgetpos' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64)
/* 64-bit variant of `fgetpos' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* 64-bit variant of `fgetpos' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos64)
/* 64-bit variant of `fgetpos' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),_IO_fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64_unlocked)
/* 64-bit variant of `fgetpos' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || defined(__CRT_HAVE__IO_ftell)
#include <local/stdio/fgetpos64.h>
/* 64-bit variant of `fgetpos' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetpos64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int (__LIBCCALL fgetpos64)(__FILE *__restrict __stream, fpos64_t *__restrict __pos) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetpos64))(__stream, __pos); })
#endif /* ... */
#if defined(__CRT_HAVE_fsetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* 64-bit variant of `fsetpos' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64)
/* 64-bit variant of `fsetpos' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* 64-bit variant of `fsetpos' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos64)
/* 64-bit variant of `fsetpos' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),_IO_fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64_unlocked)
/* 64-bit variant of `fsetpos' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#else /* ... */
#include <asm/stdio.h>
#if defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || (defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)))
#include <local/stdio/fsetpos64.h>
/* 64-bit variant of `fsetpos' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fsetpos64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int (__LIBCCALL fsetpos64)(__FILE *__restrict __stream, fpos64_t const *__restrict __pos) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fsetpos64))(__stream, __pos); })
#endif /* __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || (__SEEK_SET && (__CRT_HAVE_fseeko64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock)) */
#endif /* !... */
#endif /* __USE_LARGEFILE64 */

#ifdef __USE_KOS
#if defined(__CRT_HAVE_file_printer_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__FORMATPRINTER_CC,file_printer,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),file_printer_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_printer)
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
__LIBC __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__FORMATPRINTER_CC file_printer)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) __CASMNAME_SAME("file_printer");
#elif defined(__CRT_HAVE_file_printer_unlocked)
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__FORMATPRINTER_CC,file_printer,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),file_printer_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
#include <local/stdio/file_printer.h>
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
__NAMESPACE_LOCAL_USING_OR_IMPL(file_printer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__FORMATPRINTER_CC file_printer)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_printer))(__arg, __data, __datalen); })
#endif /* ... */
#ifdef __CRT_HAVE_file_printer_unlocked
/* Same as `file_printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__LIBC __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__FORMATPRINTER_CC file_printer_unlocked)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) __CASMNAME_SAME("file_printer_unlocked");
#elif defined(__CRT_HAVE_file_printer)
/* Same as `file_printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__FORMATPRINTER_CC,file_printer_unlocked,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),file_printer,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)
#include <local/stdio/file_printer_unlocked.h>
/* Same as `file_printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__NAMESPACE_LOCAL_USING_OR_IMPL(file_printer_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__FORMATPRINTER_CC file_printer_unlocked)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_printer_unlocked))(__arg, __data, __datalen); })
#endif /* ... */
#endif /* __USE_KOS */

#if defined(__USE_GNU) || defined(__USE_SOLARIS)
#ifdef __CRT_HAVE_vasprintf
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vasprintf,(char **__restrict __pstr, char const *__restrict __format, __builtin_va_list __args),(__pstr,__format,__args))
#elif (defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#include <local/stdio/vasprintf.h>
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
__NAMESPACE_LOCAL_USING_OR_IMPL(vasprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL vasprintf)(char **__restrict __pstr, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vasprintf))(__pstr, __format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE_asprintf
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL asprintf)(char **__restrict __pstr, char const *__restrict __format, ...) __CASMNAME_SAME("asprintf");
#elif defined(__CRT_HAVE___asprintf)
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL asprintf)(char **__restrict __pstr, char const *__restrict __format, ...) __CASMNAME("__asprintf");
#elif defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)))
#include <local/stdio/asprintf.h>
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(asprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL asprintf)(char **__restrict __pstr, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asprintf))(__pstr, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define asprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asprintf))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE_asprintf
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL __asprintf)(char **__restrict __pstr, char const *__restrict __format, ...) __CASMNAME("asprintf");
#elif defined(__CRT_HAVE___asprintf)
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL __asprintf)(char **__restrict __pstr, char const *__restrict __format, ...) __CASMNAME_SAME("__asprintf");
#elif defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)))
#include <local/stdio/asprintf.h>
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
#define __asprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asprintf))
#endif /* ... */
#endif /* __USE_GNU || __USE_SOLARIS */




#ifdef __USE_KOS
#if defined(__CRT_HAVE_fdreopen64_unlocked) && defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,fdreopen,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),fdreopen64_unlocked,(__fd,__modes,__stream))
#elif defined(__CRT_HAVE_fdreopen_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,fdreopen,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),fdreopen_unlocked,(__fd,__modes,__stream))
#elif defined(__CRT_HAVE_fdreopen64) && defined(__USE_FILE_OFFSET64)
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,fdreopen,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),fdreopen64,(__fd,__modes,__stream))
#elif defined(__CRT_HAVE_fdreopen)
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
__CDECLARE(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,fdreopen,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),(__fd,__modes,__stream))
#elif defined(__CRT_HAVE_fdreopen64)
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,fdreopen,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),fdreopen64,(__fd,__modes,__stream))
#elif defined(__CRT_HAVE_fdreopen_unlocked)
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,fdreopen,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),fdreopen_unlocked,(__fd,__modes,__stream))
#elif defined(__CRT_HAVE_fdreopen64_unlocked)
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,fdreopen,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),fdreopen64_unlocked,(__fd,__modes,__stream))
#endif /* ... */
#ifdef __CRT_HAVE_fdreopen_unlocked
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
__CDECLARE(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,fdreopen_unlocked,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),(__fd,__modes,__stream))
#elif defined(__CRT_HAVE_fdreopen)
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,fdreopen_unlocked,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),fdreopen,(__fd,__modes,__stream))
#elif defined(__CRT_HAVE_fdreopen64) || defined(__CRT_HAVE_fdreopen64_unlocked)
#include <local/stdio/fdreopen_unlocked.h>
/* Re-open the given `STREAM' as a file-stream for accessing `FD' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fdreopen_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 3)) __FILE *__NOTHROW_RPC(__LIBCCALL fdreopen_unlocked)(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdreopen_unlocked))(__fd, __modes, __stream); })
#endif /* ... */
#if defined(__CRT_HAVE_freopen64_unlocked) && defined(__USE_FILE_OFFSET64)
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen64_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen_unlocked)
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64_unlocked)
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen64_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen)
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64)
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen64,(__filename,__modes,__stream))
#endif /* ... */
#ifdef __CRT_HAVE_freopen64_unlocked
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64)
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen64,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen_unlocked)
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen)
/* Re-open the given `STREAM' as a file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen,(__filename,__modes,__stream))
#endif /* ... */
#ifdef __CRT_HAVE_fseek_unlocked
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fseek_unlocked,(__FILE *__restrict __stream, long int __off, int __whence),(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek_unlocked,(__FILE *__restrict __stream, long int __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek_unlocked,(__FILE *__restrict __stream, long int __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek_unlocked,(__FILE *__restrict __stream, long int __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek_unlocked,(__FILE *__restrict __stream, long int __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek_unlocked,(__FILE *__restrict __stream, long int __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek_unlocked,(__FILE *__restrict __stream, long int __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek_unlocked,(__FILE *__restrict __stream, long int __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64)
#include <local/stdio/fseek_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fseek_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fseek_unlocked)(__FILE *__restrict __stream, long int __off, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fseek_unlocked))(__stream, __off, __whence); })
#endif /* ... */
#ifdef __CRT_HAVE_ftell_unlocked
__CDECLARE(__ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__ftell_nolock)
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE__IO_ftell) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE__ftelli64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || (defined(__CRT_HAVE_ftello64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked)
#include <local/stdio/ftell_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ftell_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) long int (__LIBCCALL ftell_unlocked)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftell_unlocked))(__stream); })
#endif /* ... */
#if defined(__CRT_HAVE_fseeko64_unlocked) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && !defined(__USE_FILE_OFFSET64)
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek_unlocked) && ((defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__))
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && ((defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__))
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek) && ((defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__))
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseek,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
#include <local/stdio/fseeko_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fseeko_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fseeko_unlocked)(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fseeko_unlocked))(__stream, __off, __whence); })
#endif /* ... */
#if defined(__CRT_HAVE_ftello64_unlocked) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE__ftelli64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && !defined(__USE_FILE_OFFSET64)
__CDECLARE(__ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_ftello) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE_ftell_unlocked) && ((defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__))
__CREDIRECT(__ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && ((defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__))
__CREDIRECT(__ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftell) && ((defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (!defined(__USE_FILE_OFFSET64) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__))
__CREDIRECT(__ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),ftell,(__stream))
#elif (defined(__CRT_HAVE_ftello64) && defined(__USE_FILE_OFFSET64)) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || defined(__CRT_HAVE__IO_ftell)
#include <local/stdio/ftello_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ftello_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __FS_TYPE(off) (__LIBCCALL ftello_unlocked)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftello_unlocked))(__stream); })
#endif /* ... */
#ifdef __CRT_HAVE_flushall_unlocked
__CDECLARE(,int,__THROWING,flushall_unlocked,(void),())
#elif defined(__CRT_HAVE__flushall)
__CREDIRECT(,int,__THROWING,flushall_unlocked,(void),_flushall,())
#elif defined(__CRT_HAVE__IO_flush_all)
__CREDIRECT(,int,__THROWING,flushall_unlocked,(void),_IO_flush_all,())
#else /* ... */
#include <local/stdio/flushall_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(flushall_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL flushall_unlocked)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(flushall_unlocked))(); })
#endif /* !... */
#if defined(__CRT_HAVE_fgetpos64_unlocked) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(pos) *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(pos) *__restrict __pos),fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos_unlocked) && !defined(__USE_FILE_OFFSET64)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(pos) *__restrict __pos),(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(pos) *__restrict __pos),fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || defined(__CRT_HAVE__IO_ftell)
#include <local/stdio/fgetpos_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetpos_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int (__LIBCCALL fgetpos_unlocked)(__FILE *__restrict __stream, __FS_TYPE(pos) *__restrict __pos) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetpos_unlocked))(__stream, __pos); })
#endif /* ... */
#if defined(__CRT_HAVE_fsetpos64_unlocked) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(pos) const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(pos) const *__restrict __pos),fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos_unlocked) && !defined(__USE_FILE_OFFSET64)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(pos) const *__restrict __pos),(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(pos) const *__restrict __pos),fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
#include <local/stdio/fsetpos_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fsetpos_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int (__LIBCCALL fsetpos_unlocked)(__FILE *__restrict __stream, __FS_TYPE(pos) const *__restrict __pos) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fsetpos_unlocked))(__stream, __pos); })
#endif /* ... */
#ifdef __CRT_HAVE_getw_unlocked
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,getw_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_getw)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getw_unlocked,(__FILE *__restrict __stream),getw,(__stream))
#elif defined(__CRT_HAVE__getw)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getw_unlocked,(__FILE *__restrict __stream),_getw,(__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)
#include <local/stdio/getw_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getw_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL getw_unlocked)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getw_unlocked))(__stream); })
#endif /* ... */
#ifdef __CRT_HAVE_putw_unlocked
__CDECLARE(__ATTR_NONNULL((2)),int,__THROWING,putw_unlocked,(int __w, __FILE *__restrict __stream),(__w,__stream))
#elif defined(__CRT_HAVE_putw)
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putw_unlocked,(int __w, __FILE *__restrict __stream),putw,(__w,__stream))
#elif defined(__CRT_HAVE__putw)
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putw_unlocked,(int __w, __FILE *__restrict __stream),_putw,(__w,__stream))
#elif defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
#include <local/stdio/putw_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(putw_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int (__LIBCCALL putw_unlocked)(int __w, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putw_unlocked))(__w, __stream); })
#endif /* ... */
#ifdef __CRT_HAVE_setvbuf_unlocked
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,setvbuf_unlocked,(__FILE *__restrict __stream, char *__restrict __buf, int __modes, __SIZE_TYPE__ __bufsize),(__stream,__buf,__modes,__bufsize))
#elif defined(__CRT_HAVE_setvbuf)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,setvbuf_unlocked,(__FILE *__restrict __stream, char *__restrict __buf, int __modes, __SIZE_TYPE__ __bufsize),setvbuf,(__stream,__buf,__modes,__bufsize))
#elif defined(__CRT_HAVE__IO_setvbuf)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,setvbuf_unlocked,(__FILE *__restrict __stream, char *__restrict __buf, int __modes, __SIZE_TYPE__ __bufsize),_IO_setvbuf,(__stream,__buf,__modes,__bufsize))
#endif /* ... */
#ifdef __CRT_HAVE_ungetc_unlocked
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc_unlocked,(int __ch, __FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE__ungetc_nolock)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc_unlocked,(int __ch, __FILE *__restrict __stream),_ungetc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetc)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc_unlocked,(int __ch, __FILE *__restrict __stream),ungetc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_ungetc)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc_unlocked,(int __ch, __FILE *__restrict __stream),_IO_ungetc,(__ch,__stream))
#endif /* ... */
#ifdef __CRT_HAVE_getdelim_unlocked
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,getdelim_unlocked,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE_getdelim)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,getdelim_unlocked,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),getdelim,(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
#include <local/stdio/getdelim_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getdelim_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)) __SSIZE_TYPE__ (__LIBCCALL getdelim_unlocked)(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getdelim_unlocked))(__lineptr, __pcount, __delimiter, __stream); })
#endif /* ... */
#ifdef __CRT_HAVE_getline_unlocked
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__SSIZE_TYPE__,__THROWING,getline_unlocked,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream),(__lineptr,__pcount,__stream))
#elif defined(__CRT_HAVE_getline)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__SSIZE_TYPE__,__THROWING,getline_unlocked,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream),getline,(__lineptr,__pcount,__stream))
#elif defined(__CRT_HAVE_getdelim_unlocked) || defined(__CRT_HAVE_getdelim) || (defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
#include <local/stdio/getline_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getline_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)) __SSIZE_TYPE__ (__LIBCCALL getline_unlocked)(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getline_unlocked))(__lineptr, __pcount, __stream); })
#endif /* ... */
#ifdef __CRT_HAVE_rewind_unlocked
__CDECLARE_VOID(__ATTR_NONNULL((1)),__THROWING,rewind_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_rewind)
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__THROWING,rewind_unlocked,(__FILE *__restrict __stream),rewind,(__stream))
#elif defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
#include <local/stdio/rewind_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(rewind_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void (__LIBCCALL rewind_unlocked)(__FILE *__restrict __stream) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rewind_unlocked))(__stream); })
#endif /* ... */
#ifdef __CRT_HAVE_fisatty
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,fisatty,(__FILE *__restrict __stream),(__stream))
#elif (defined(__CRT_HAVE_isatty) || defined(__CRT_HAVE__isatty)) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked))
#include <local/stdio/fisatty.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fisatty, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL fisatty)(__FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fisatty))(__stream); })
#endif /* ... */
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else /* __USE_KOS */
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif /* !__USE_KOS */
#endif /* !__PIO_OFFSET */
#if defined(__CRT_HAVE_fftruncate64_unlocked) && defined(__USE_STDIO_UNLOCKED) && defined(__USE_FILE_OFFSET64)
/* >> fftruncate(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate,(__FILE *__restrict __stream, __PIO_OFFSET __length),fftruncate64_unlocked,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate_unlocked) && defined(__USE_STDIO_UNLOCKED) && !defined(__USE_FILE_OFFSET64)
/* >> fftruncate(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate,(__FILE *__restrict __stream, __PIO_OFFSET __length),fftruncate_unlocked,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate64) && defined(__USE_FILE_OFFSET64)
/* >> fftruncate(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate,(__FILE *__restrict __stream, __PIO_OFFSET __length),fftruncate64,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate) && !defined(__USE_FILE_OFFSET64)
/* >> fftruncate(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fftruncate,(__FILE *__restrict __stream, __PIO_OFFSET __length),(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate64_unlocked) && defined(__USE_FILE_OFFSET64)
/* >> fftruncate(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate,(__FILE *__restrict __stream, __PIO_OFFSET __length),fftruncate64_unlocked,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate_unlocked) && !defined(__USE_FILE_OFFSET64)
/* >> fftruncate(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate,(__FILE *__restrict __stream, __PIO_OFFSET __length),fftruncate_unlocked,(__stream,__length))
#elif ((defined(__CRT_HAVE__chsize) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_chsize) && !defined(__USE_FILE_OFFSET64)) || defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate)) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked))
#include <local/stdio/fftruncate.h>
/* >> fftruncate(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fftruncate, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fftruncate)(__FILE *__restrict __stream, __PIO_OFFSET __length) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fftruncate))(__stream, __length); })
#endif /* ... */
#if defined(__CRT_HAVE_fftruncate64_unlocked) && defined(__USE_FILE_OFFSET64)
/* >> fftruncate_unlocked(3)
 * Same as `fftruncate()', but don't acquire a lock to the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate_unlocked,(__FILE *__restrict __stream, __PIO_OFFSET __length),fftruncate64_unlocked,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate_unlocked) && !defined(__USE_FILE_OFFSET64)
/* >> fftruncate_unlocked(3)
 * Same as `fftruncate()', but don't acquire a lock to the file */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fftruncate_unlocked,(__FILE *__restrict __stream, __PIO_OFFSET __length),(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate64) && defined(__USE_FILE_OFFSET64)
/* >> fftruncate_unlocked(3)
 * Same as `fftruncate()', but don't acquire a lock to the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate_unlocked,(__FILE *__restrict __stream, __PIO_OFFSET __length),fftruncate64,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate) && !defined(__USE_FILE_OFFSET64)
/* >> fftruncate_unlocked(3)
 * Same as `fftruncate()', but don't acquire a lock to the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate_unlocked,(__FILE *__restrict __stream, __PIO_OFFSET __length),fftruncate,(__stream,__length))
#elif ((defined(__CRT_HAVE__chsize) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_chsize) && !defined(__USE_FILE_OFFSET64)) || defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate)) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked))
#include <local/stdio/fftruncate_unlocked.h>
/* >> fftruncate_unlocked(3)
 * Same as `fftruncate()', but don't acquire a lock to the file */
__NAMESPACE_LOCAL_USING_OR_IMPL(fftruncate_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fftruncate_unlocked)(__FILE *__restrict __stream, __PIO_OFFSET __length) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fftruncate_unlocked))(__stream, __length); })
#endif /* ... */
#if __has_builtin(__builtin_puts_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_puts_unlocked)
__CEIDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,puts_unlocked,(char const *__restrict __string),{ return __builtin_puts_unlocked(__string); })
#elif defined(__CRT_HAVE_puts_unlocked)
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,puts_unlocked,(char const *__restrict __string),(__string))
#elif defined(__CRT_HAVE_puts)
__CREDIRECT(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,puts_unlocked,(char const *__restrict __string),puts,(__string))
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputs_unlocked) || defined(__CRT_HAVE_fputs) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread))
#include <local/stdio/puts_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(puts_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL puts_unlocked)(char const *__restrict __string) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(puts_unlocked))(__string); })
#endif /* ... */

#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_fseeko64_unlocked
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fseeko64_unlocked,(__FILE *__restrict __stream, __off64_t __off, int __whence),(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64_unlocked,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64_unlocked,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64_unlocked,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64_unlocked,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
#include <local/stdio/fseeko64_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fseeko64_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fseeko64_unlocked)(__FILE *__restrict __stream, __off64_t __off, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fseeko64_unlocked))(__stream, __off, __whence); })
#endif /* ... */
#ifdef __CRT_HAVE_ftello64_unlocked
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64_unlocked,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64_unlocked,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE__ftelli64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64_unlocked,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64_unlocked,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || defined(__CRT_HAVE__IO_ftell)
#include <local/stdio/ftello64_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ftello64_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __off64_t (__LIBCCALL ftello64_unlocked)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftello64_unlocked))(__stream); })
#endif /* ... */
#ifdef __CRT_HAVE_fgetpos64_unlocked
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),_IO_fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),fgetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || defined(__CRT_HAVE__IO_ftell)
#include <local/stdio/fgetpos64_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetpos64_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int (__LIBCCALL fgetpos64_unlocked)(__FILE *__restrict __stream, fpos64_t *__restrict __pos) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetpos64_unlocked))(__stream, __pos); })
#endif /* ... */
#ifdef __CRT_HAVE_fsetpos64_unlocked
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),_IO_fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),fsetpos_unlocked,(__stream,__pos))
#else /* ... */
#include <asm/stdio.h>
#if defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || (defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)))
#include <local/stdio/fsetpos64_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fsetpos64_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int (__LIBCCALL fsetpos64_unlocked)(__FILE *__restrict __stream, fpos64_t const *__restrict __pos) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fsetpos64_unlocked))(__stream, __pos); })
#endif /* __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || (__SEEK_SET && (__CRT_HAVE_fseeko64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock)) */
#endif /* !... */
#if defined(__CRT_HAVE_fftruncate64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fftruncate64(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate64,(__FILE *__restrict __stream, __PIO_OFFSET64 __length),fftruncate64_unlocked,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate64)
/* >> fftruncate64(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fftruncate64,(__FILE *__restrict __stream, __PIO_OFFSET64 __length),(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate64_unlocked)
/* >> fftruncate64(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate64,(__FILE *__restrict __stream, __PIO_OFFSET64 __length),fftruncate64_unlocked,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> fftruncate64(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate64,(__FILE *__restrict __stream, __PIO_OFFSET64 __length),fftruncate,(__stream,__length))
#elif (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate)) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked))
#include <local/stdio/fftruncate64.h>
/* >> fftruncate64(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fftruncate64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fftruncate64)(__FILE *__restrict __stream, __PIO_OFFSET64 __length) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fftruncate64))(__stream, __length); })
#endif /* ... */
#ifdef __CRT_HAVE_fftruncate64_unlocked
/* >> fftruncate64_unlocked(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fftruncate64_unlocked,(__FILE *__restrict __stream, __PIO_OFFSET64 __length),(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate64)
/* >> fftruncate64_unlocked(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate64_unlocked,(__FILE *__restrict __stream, __PIO_OFFSET64 __length),fftruncate64,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> fftruncate64_unlocked(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate64_unlocked,(__FILE *__restrict __stream, __PIO_OFFSET64 __length),fftruncate_unlocked,(__stream,__length))
#elif (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate)) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked))
#include <local/stdio/fftruncate64_unlocked.h>
/* >> fftruncate64_unlocked(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fftruncate64_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fftruncate64_unlocked)(__FILE *__restrict __stream, __PIO_OFFSET64 __length) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fftruncate64_unlocked))(__stream, __length); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#ifdef __CRT_HAVE_vfprintf_unlocked
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfprintf)
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfprintf_s)
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_s,(__stream,__format,__args))
#elif defined(__CRT_HAVE__IO_vfprintf)
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_IO_vfprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)
#include <local/stdio/vfprintf_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vfprintf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL vfprintf_unlocked)(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfprintf_unlocked))(__stream, __format, __args); })
#endif /* ... */
#if __has_builtin(__builtin_fprintf_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fprintf_unlocked) && __has_builtin(__builtin_va_arg_pack)
__CEIDECLARE(__ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,fprintf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, ...),{ return __builtin_fprintf_unlocked(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_fprintf_unlocked)
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf_unlocked)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fprintf_unlocked");
#elif defined(__CRT_HAVE_fprintf_s)
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf_unlocked)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_s");
#elif defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)
#include <local/stdio/fprintf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(fprintf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf_unlocked)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fprintf_unlocked))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define fprintf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fprintf_unlocked))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE_vprintf_unlocked
__CDECLARE(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,vprintf_unlocked,(char const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE_vprintf_s)
__CREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,vprintf_unlocked,(char const *__restrict __format, __builtin_va_list __args),vprintf_s,(__format,__args))
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite))
#include <local/stdio/vprintf_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vprintf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL vprintf_unlocked)(char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vprintf_unlocked))(__format, __args); })
#endif /* ... */
#if __has_builtin(__builtin_printf_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_printf_unlocked) && __has_builtin(__builtin_va_arg_pack)
__CEIDECLARE(__ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,printf_unlocked,(char const *__restrict __format, ...),{ return __builtin_printf_unlocked(__format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_printf_unlocked)
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf_unlocked)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("printf_unlocked");
#elif defined(__CRT_HAVE_printf_s)
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf_unlocked)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("printf_s");
#elif defined(__CRT_HAVE_vprintf_unlocked) || defined(__CRT_HAVE_vprintf_s) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
#include <local/stdio/printf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(printf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf_unlocked)(char const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(printf_unlocked))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define printf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(printf_unlocked))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE_vfscanf_unlocked
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfscanf)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE___vfscanf)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),__vfscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE__vfscanf)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_vfscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE__vfscanf_s)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_vfscanf_s,(__stream,__format,__args))
#elif defined(__CRT_HAVE__IO_vfscanf)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_IO_vfscanf,(__stream,__format,__args))
#elif (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
#include <local/stdio/vfscanf_unlocked.h>
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__NAMESPACE_LOCAL_USING_OR_IMPL(vfscanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL vfscanf_unlocked)(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfscanf_unlocked))(__stream, __format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE_vscanf_unlocked
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vscanf_unlocked,(char const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE__vscanf)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vscanf_unlocked,(char const *__restrict __format, __builtin_va_list __args),_vscanf,(__format,__args))
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE___vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || ((defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))))
#include <local/stdio/vscanf_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vscanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL vscanf_unlocked)(char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vscanf_unlocked))(__format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE_fscanf_unlocked
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fscanf_unlocked)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fscanf_unlocked");
#elif defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE___vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || ((defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
#include <local/stdio/fscanf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(fscanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fscanf_unlocked)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fscanf_unlocked))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define fscanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fscanf_unlocked))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE_scanf_unlocked
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL scanf_unlocked)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("scanf_unlocked");
#elif defined(__CRT_HAVE_vscanf_unlocked) || defined(__CRT_HAVE__vscanf) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE___vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || ((defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
#include <local/stdio/scanf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(scanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL scanf_unlocked)(char const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scanf_unlocked))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define scanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scanf_unlocked))
#endif /* !__cplusplus */
#endif /* ... */
#endif /* __USE_KOS */

#ifdef __USE_SOLARIS
#if !defined(__USE_XOPEN) || defined(_EVERY_SOURCE)
#ifndef __getsubopt_defined
#define __getsubopt_defined 1
#ifdef __CRT_HAVE_getsubopt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,getsubopt,(char **__restrict __optionp, char *const *__restrict __tokens, char **__restrict __valuep),(__optionp,__tokens,__valuep))
#else /* __CRT_HAVE_getsubopt */
#include <local/stdlib/getsubopt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getsubopt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBCCALL getsubopt)(char **__restrict __optionp, char *const *__restrict __tokens, char **__restrict __valuep) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getsubopt))(__optionp, __tokens, __valuep); })
#endif /* !__CRT_HAVE_getsubopt */
#endif /* !__getsubopt_defined */
#endif /* !__USE_XOPEN || _EVERY_SOURCE */
#endif /* __USE_SOLARIS */

#endif /* __CC__ */

__SYSDECL_END





#ifdef __USE_DOS
#define _NFILE          512
#define _NSTREAM_       512
#define _IOB_ENTRIES    20
#define _P_tmpdir       "\\"
#define _wP_tmpdir     L"\\"
#define _SYS_OPEN       20
#ifdef __USE_DOS_SLIB
#define L_tmpnam_s      18
#define TMP_MAX_S       2147483647
#define _TMP_MAX_S      2147483647
#endif /* __USE_DOS_SLIB */

#ifndef _FPOS_T_DEFINED
#define _FPOS_T_DEFINED 1
#endif /* !_FPOS_T_DEFINED */

#ifndef _STDSTREAM_DEFINED
#define _STDSTREAM_DEFINED 1
#endif /* !_STDSTREAM_DEFINED */

#ifndef _FILE_DEFINED
#define _FILE_DEFINED 1
#endif /* !_FILE_DEFINED */

#ifndef _CRT_PERROR_DEFINED
#define _CRT_PERROR_DEFINED 1
#endif /* !_CRT_PERROR_DEFINED */

#ifdef __CC__
#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */

#ifndef __rsize_t_defined
#define __rsize_t_defined 1
typedef __SIZE_TYPE__ rsize_t;
#endif /* !__rsize_t_defined */

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __std_FILE_defined
#define __std_FILE_defined 1
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */
#ifndef __FILE_defined
#define __FILE_defined 1
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */


#ifndef _CRT_DIRECTORY_DEFINED
#define _CRT_DIRECTORY_DEFINED 1
#ifndef __unlink_defined
#define __unlink_defined 1
#ifdef __CRT_HAVE_unlink
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,unlink,(char const *__file),(__file))
#elif defined(__CRT_HAVE__unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,unlink,(char const *__file),_unlink,(__file))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <local/unistd/unlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL unlink)(char const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unlink))(__file); })
#else /* ... */
#undef __unlink_defined
#endif /* !... */
#endif /* !__unlink_defined */
#ifndef ___unlink_defined
#define ___unlink_defined 1
#ifdef __CRT_HAVE_unlink
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,_unlink,(char const *__file),unlink,(__file))
#elif defined(__CRT_HAVE__unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,_unlink,(char const *__file),(__file))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <local/unistd/unlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL _unlink)(char const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unlink))(__file); }
#else /* ... */
#undef ___unlink_defined
#endif /* !... */
#endif /* !___unlink_defined */
#endif /* !_CRT_DIRECTORY_DEFINED */

#ifndef _STDIO_DEFINED
#define _STDIO_DEFINED 1
#ifdef __CRT_HAVE_popen
/* Open and return a new process I/O stream for executing `COMMAND' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,_popen,(char const *__command, char const *__modes),popen,(__command,__modes))
#elif defined(__CRT_HAVE__popen)
/* Open and return a new process I/O stream for executing `COMMAND' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,_popen,(char const *__command, char const *__modes),(__command,__modes))
#elif defined(__CRT_HAVE__IO_popen)
/* Open and return a new process I/O stream for executing `COMMAND' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,_popen,(char const *__command, char const *__modes),_IO_popen,(__command,__modes))
#endif /* ... */
#ifdef __CRT_HAVE_pclose
/* Close a process I/O file `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_pclose,(__FILE *__stream),pclose,(__stream))
#elif defined(__CRT_HAVE__pclose)
/* Close a process I/O file `STREAM' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_pclose,(__FILE *__stream),(__stream))
#endif /* ... */
#ifdef __CRT_HAVE__fsopen
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,_fsopen,(char const *__filename, char const *__modes, int __sflag),(__filename,__modes,__sflag))
#elif defined(__CRT_HAVE_fopen) || defined(__CRT_HAVE__IO_fopen) || defined(__CRT_HAVE_fopen64)
#include <local/stdio/_fsopen.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_fsopen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __FILE *__NOTHROW_RPC(__LIBCCALL _fsopen)(char const *__filename, char const *__modes, int __sflag) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fsopen))(__filename, __modes, __sflag); })
#endif /* ... */
#ifdef __CRT_HAVE_fdopen
/* Open a new file stream by inheriting a given file descriptor `FD'
 * Note that upon success (`return != NULL'), the given `FD'
 * will be `close()'d once `fclose(return)' is called */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__FILE *,__NOTHROW_NCX,_fdopen,(__fd_t __fd, char const *__restrict __modes),fdopen,(__fd,__modes))
#elif defined(__CRT_HAVE__fdopen)
/* Open a new file stream by inheriting a given file descriptor `FD'
 * Note that upon success (`return != NULL'), the given `FD'
 * will be `close()'d once `fclose(return)' is called */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),__FILE *,__NOTHROW_NCX,_fdopen,(__fd_t __fd, char const *__restrict __modes),(__fd,__modes))
#elif defined(__CRT_HAVE__IO_fdopen)
/* Open a new file stream by inheriting a given file descriptor `FD'
 * Note that upon success (`return != NULL'), the given `FD'
 * will be `close()'d once `fclose(return)' is called */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__FILE *,__NOTHROW_NCX,_fdopen,(__fd_t __fd, char const *__restrict __modes),_IO_fdopen,(__fd,__modes))
#endif /* ... */
#ifdef __CRT_HAVE__flushall
__CDECLARE(,int,__THROWING,_flushall,(void),())
#elif defined(__CRT_HAVE__IO_flush_all)
__CREDIRECT(,int,__THROWING,_flushall,(void),_IO_flush_all,())
#else /* ... */
#include <local/stdio/_flushall.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_flushall, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL _flushall)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_flushall))(); })
#endif /* !... */
#ifdef __CRT_HAVE_fcloseall
/* Alias for `_fcloseall()' */
__CREDIRECT(,int,__THROWING,_fcloseall,(void),fcloseall,())
#elif defined(__CRT_HAVE__fcloseall)
/* Alias for `_fcloseall()' */
__CDECLARE(,int,__THROWING,_fcloseall,(void),())
#endif /* ... */
#if defined(__CRT_HAVE_fileno_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Return the underlying file descriptor number used by `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,_fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#elif defined(__CRT_HAVE_fileno)
/* Return the underlying file descriptor number used by `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,_fileno,(__FILE *__restrict __stream),fileno,(__stream))
#elif defined(__CRT_HAVE__fileno)
/* Return the underlying file descriptor number used by `STREAM' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,_fileno,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_fileno_unlocked)
/* Return the underlying file descriptor number used by `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,_fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_getchar_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Alias for `fgetc(stdin)' */
__CREDIRECT(,int,__THROWING,_fgetchar,(void),getchar_unlocked,())
#elif defined(__CRT_HAVE_getchar)
/* Alias for `fgetc(stdin)' */
__CREDIRECT(,int,__THROWING,_fgetchar,(void),getchar,())
#elif defined(__CRT_HAVE__fgetchar)
/* Alias for `fgetc(stdin)' */
__CDECLARE(,int,__THROWING,_fgetchar,(void),())
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread))
#include <local/stdio/getchar.h>
/* Alias for `fgetc(stdin)' */
__FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL _fgetchar)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getchar))(); }
#endif /* ... */
#if __has_builtin(__builtin_putchar) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_putchar)
/* Alias for `fputc(CH, stdout)' */
__CEIREDIRECT(,int,__THROWING,_fputchar,(int __ch),putchar,{ return __builtin_putchar(__ch); })
#elif defined(__CRT_HAVE_putchar_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Alias for `fputc(CH, stdout)' */
__CREDIRECT(,int,__THROWING,_fputchar,(int __ch),putchar_unlocked,(__ch))
#elif defined(__CRT_HAVE_putchar)
/* Alias for `fputc(CH, stdout)' */
__CREDIRECT(,int,__THROWING,_fputchar,(int __ch),putchar,(__ch))
#elif defined(__CRT_HAVE__fputchar)
/* Alias for `fputc(CH, stdout)' */
__CDECLARE(,int,__THROWING,_fputchar,(int __ch),(__ch))
#elif defined(__CRT_HAVE_putchar_unlocked)
/* Alias for `fputc(CH, stdout)' */
__CREDIRECT(,int,__THROWING,_fputchar,(int __ch),putchar_unlocked,(__ch))
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite))
#include <local/stdio/putchar.h>
/* Alias for `fputc(CH, stdout)' */
__FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL _fputchar)(int __ch) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putchar))(__ch); }
#endif /* ... */
#if defined(__CRT_HAVE_getw_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Similar to `getc()', but read 2 bytes */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_getw,(__FILE *__restrict __stream),getw_unlocked,(__stream))
#elif defined(__CRT_HAVE_getw)
/* Similar to `getc()', but read 2 bytes */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_getw,(__FILE *__restrict __stream),getw,(__stream))
#elif defined(__CRT_HAVE__getw)
/* Similar to `getc()', but read 2 bytes */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,_getw,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)
#include <local/stdio/getw.h>
/* Similar to `getc()', but read 2 bytes */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL _getw)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getw))(__stream); }
#endif /* ... */
#if defined(__CRT_HAVE_putw_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_putw,(int __w, __FILE *__restrict __stream),putw_unlocked,(__w,__stream))
#elif defined(__CRT_HAVE_putw)
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_putw,(int __w, __FILE *__restrict __stream),putw,(__w,__stream))
#elif defined(__CRT_HAVE__putw)
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
__CDECLARE(__ATTR_NONNULL((2)),int,__THROWING,_putw,(int __w, __FILE *__restrict __stream),(__w,__stream))
#elif defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
#include <local/stdio/putw.h>
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int (__LIBCCALL _putw)(int __w, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putw))(__w, __stream); }
#endif /* ... */
#ifdef __CRT_HAVE_tempnam
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,_tempnam,(char const *__dir, char const *__pfx),tempnam,(__dir,__pfx))
#elif defined(__CRT_HAVE__tempnam)
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,_tempnam,(char const *__dir, char const *__pfx),(__dir,__pfx))
#endif /* ... */

#if defined(__CRT_HAVE_fseeko64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && defined(__USE_STDIO_UNLOCKED)
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64)
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64)
/* 64-bit variant of `fseeko' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked)
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock)
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* 64-bit variant of `fseeko' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
#include <local/stdio/fseeko64.h>
/* 64-bit variant of `fseeko' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL _fseeki64)(__FILE *__restrict __stream, __off64_t __off, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fseeko64))(__stream, __off, __whence); }
#endif /* ... */
#if defined(__CRT_HAVE_ftello64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && defined(__USE_STDIO_UNLOCKED)
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftell_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello64)
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE__ftelli64)
/* 64-bit variant of `ftello' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked)
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock)
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),ftell,(__stream))
#elif defined(__CRT_HAVE__IO_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* 64-bit variant of `ftello' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || defined(__CRT_HAVE__IO_ftell)
#include <local/stdio/ftello64.h>
/* 64-bit variant of `ftello' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __off64_t (__LIBCCALL _ftelli64)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftello64))(__stream); }
#endif /* ... */

__CDECLARE_OPT(,int,__NOTHROW_RPC,_rmtmp,(void),())

__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__THROWING,_filbuf,(__FILE *__restrict __stream),(__stream))
__CDECLARE_OPT(__ATTR_NONNULL((2)),int,__THROWING,_flsbuf,(int __ch, __FILE *__restrict __stream),(__ch,__stream))

__CDECLARE_OPT(__ATTR_WUNUSED,int,__NOTHROW_NCX,_getmaxstdio,(void),())
__CDECLARE_OPT(,int,__NOTHROW_NCX,_setmaxstdio,(int __val),(__val))
__CDECLARE_OPT(__ATTR_WUNUSED,int,__NOTHROW_NCX,_get_printf_count_output,(void),())
__CDECLARE_OPT(,int,__NOTHROW_NCX,_set_printf_count_output,(int __val),(__val))
__CDECLARE_OPT(__ATTR_WUNUSED,__UINT32_TYPE__,__NOTHROW_NCX,_get_output_format,(void),())
__CDECLARE_OPT(,__UINT32_TYPE__,__NOTHROW_NCX,_set_output_format,(__UINT32_TYPE__ __format),(__format))
#if __has_builtin(__builtin_vscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vscanf)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,_vscanf,(char const *__restrict __format, __builtin_va_list __args),vscanf,{ return __builtin_vscanf(__format, __args); })
#elif defined(__CRT_HAVE_vscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,_vscanf,(char const *__restrict __format, __builtin_va_list __args),vscanf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_vscanf)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,_vscanf,(char const *__restrict __format, __builtin_va_list __args),vscanf,(__format,__args))
#elif defined(__CRT_HAVE__vscanf)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,_vscanf,(char const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE_vscanf_unlocked)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,_vscanf,(char const *__restrict __format, __builtin_va_list __args),vscanf_unlocked,(__format,__args))
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))))
#include <local/stdio/vscanf.h>
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL _vscanf)(char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vscanf))(__format, __args); }
#endif /* ... */

#ifdef __CRT_HAVE__scanf_l
__LIBC __ATTR_LIBC_SCANF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _scanf_l)(char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_scanf_l");
#elif defined(__CRT_HAVE__scanf_s_l)
__LIBC __ATTR_LIBC_SCANF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _scanf_l)(char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) __CASMNAME("_scanf_s_l");
#elif defined(__CRT_HAVE__vscanf_l) || defined(__CRT_HAVE__vscanf_s_l) || defined(__CRT_HAVE_vscanf) || defined(__CRT_HAVE__vscanf) || defined(__CRT_HAVE_vscanf_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
#include <local/stdio/_scanf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_scanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_SCANF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _scanf_l)(char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scanf_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _scanf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scanf_l))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__fscanf_l
__LIBC __ATTR_LIBC_SCANF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _fscanf_l)(__FILE *__restrict __stream, char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_fscanf_l");
#elif defined(__CRT_HAVE__fscanf_s_l)
__LIBC __ATTR_LIBC_SCANF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _fscanf_l)(__FILE *__restrict __stream, char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) __CASMNAME("_fscanf_s_l");
#elif defined(__CRT_HAVE__vfscanf_l) || defined(__CRT_HAVE__vfscanf_s_l) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
#include <local/stdio/_fscanf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_fscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_SCANF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _fscanf_l)(__FILE *__restrict __stream, char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fscanf_l))(__stream, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _fscanf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fscanf_l))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__snscanf
__LIBC __ATTR_LIBC_SCANF(3, 4) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snscanf)(char const *__restrict __input, __SIZE_TYPE__ __inputlen, char const *__restrict __format, ...) __CASMNAME_SAME("_snscanf");
#elif defined(__CRT_HAVE__snscanf_s)
__LIBC __ATTR_LIBC_SCANF(3, 4) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snscanf)(char const *__restrict __input, __SIZE_TYPE__ __inputlen, char const *__restrict __format, ...) __CASMNAME("_snscanf_s");
#else /* ... */
#include <local/stdio/_snscanf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_SCANF(3, 4) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snscanf)(char const *__restrict __input, __SIZE_TYPE__ __inputlen, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snscanf))(__input, __inputlen, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snscanf))
#endif /* !__cplusplus */
#endif /* !... */
#ifdef __CRT_HAVE__snscanf_l
__LIBC __ATTR_LIBC_SCANF(3, 5) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snscanf_l)(char const *__restrict __input, __SIZE_TYPE__ __inputlen, char const *__restrict __format, __locale_t __locale, ...) __CASMNAME_SAME("_snscanf_l");
#elif defined(__CRT_HAVE__snscanf_s_l)
__LIBC __ATTR_LIBC_SCANF(3, 5) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snscanf_l)(char const *__restrict __input, __SIZE_TYPE__ __inputlen, char const *__restrict __format, __locale_t __locale, ...) __CASMNAME("_snscanf_s_l");
#else /* ... */
#include <local/stdio/_snscanf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_SCANF(3, 5) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snscanf_l)(char const *__restrict __input, __SIZE_TYPE__ __inputlen, char const *__restrict __format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snscanf_l))(__input, __inputlen, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snscanf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snscanf_l))
#endif /* !__cplusplus */
#endif /* !... */
#ifdef __CRT_HAVE__scanf_s_l
__LIBC __ATTR_LIBC_SCANF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _scanf_s_l)(char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_scanf_s_l");
#elif defined(__CRT_HAVE__vscanf_l) || defined(__CRT_HAVE__vscanf_s_l) || defined(__CRT_HAVE_vscanf) || defined(__CRT_HAVE__vscanf) || defined(__CRT_HAVE_vscanf_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
#include <local/stdio/_scanf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_scanf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_SCANF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _scanf_s_l)(char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scanf_s_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _scanf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scanf_s_l))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__sscanf_s_l
__LIBC __ATTR_LIBC_SCANF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _sscanf_s_l)(char const *__restrict __input, char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_sscanf_s_l");
#else /* __CRT_HAVE__sscanf_s_l */
#include <local/stdio/_sscanf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_sscanf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_SCANF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _sscanf_s_l)(char const *__restrict __input, char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sscanf_s_l))(__input, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _sscanf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sscanf_s_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__sscanf_s_l */
#ifdef __CRT_HAVE__fscanf_s_l
__LIBC __ATTR_LIBC_SCANF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _fscanf_s_l)(__FILE *__restrict __stream, char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_fscanf_s_l");
#elif defined(__CRT_HAVE__vfscanf_l) || defined(__CRT_HAVE__vfscanf_s_l) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
#include <local/stdio/_fscanf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_fscanf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_SCANF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _fscanf_s_l)(__FILE *__restrict __stream, char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fscanf_s_l))(__stream, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _fscanf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fscanf_s_l))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__snscanf_s
__LIBC __ATTR_LIBC_SCANF(3, 4) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snscanf_s)(char const *__restrict __input, __SIZE_TYPE__ __inputlen, char const *__restrict __format, ...) __CASMNAME_SAME("_snscanf_s");
#else /* __CRT_HAVE__snscanf_s */
#include <local/stdio/_snscanf_s.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snscanf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_SCANF(3, 4) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snscanf_s)(char const *__restrict __input, __SIZE_TYPE__ __inputlen, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snscanf_s))(__input, __inputlen, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snscanf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snscanf_s))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snscanf_s */
#ifdef __CRT_HAVE__snscanf_s_l
__LIBC __ATTR_LIBC_SCANF(3, 5) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snscanf_s_l)(char const *__restrict __input, __SIZE_TYPE__ __inputlen, char const *__restrict __format, __locale_t __locale, ...) __CASMNAME_SAME("_snscanf_s_l");
#else /* __CRT_HAVE__snscanf_s_l */
#include <local/stdio/_snscanf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snscanf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_SCANF(3, 5) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snscanf_s_l)(char const *__restrict __input, __SIZE_TYPE__ __inputlen, char const *__restrict __format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snscanf_s_l))(__input, __inputlen, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snscanf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snscanf_s_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snscanf_s_l */

#ifdef __CRT_HAVE__vsprintf_l
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_vsprintf_l,(char *__restrict __buf, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),(__buf,__format,__locale,__args))
#else /* __CRT_HAVE__vsprintf_l */
#include <local/stdio/_vsprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL _vsprintf_l)(char *__restrict __buf, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsprintf_l))(__buf, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vsprintf_l */
#ifdef __CRT_HAVE__vsnprintf_l
__CREDIRECT(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_vsprintf_s_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vsnprintf_l,(__buf,__bufsize,__format,__locale,__args))
#elif defined(__CRT_HAVE__vsprintf_s_l)
__CDECLARE(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_vsprintf_s_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),(__buf,__bufsize,__format,__locale,__args))
#else /* ... */
#include <local/stdio/_vsnprintf_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL _vsprintf_s_l)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnprintf_l))(__buf, __bufsize, __format, __locale, __args); }
#endif /* !... */
#ifdef __CRT_HAVE__vsprintf_p
__CDECLARE(__ATTR_LIBC_PRINTF_P(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_vsprintf_p,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __builtin_va_list __args),(__buf,__bufsize,__format,__args))
#else /* __CRT_HAVE__vsprintf_p */
#include <local/stdio/_vsprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL _vsprintf_p)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsprintf_p))(__buf, __bufsize, __format, __args); })
#endif /* !__CRT_HAVE__vsprintf_p */
#ifdef __CRT_HAVE__vsprintf_p_l
__CDECLARE(__ATTR_LIBC_PRINTF_P(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_vsprintf_p_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),(__buf,__bufsize,__format,__locale,__args))
#else /* __CRT_HAVE__vsprintf_p_l */
#include <local/stdio/_vsprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL _vsprintf_p_l)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsprintf_p_l))(__buf, __bufsize, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vsprintf_p_l */

#ifdef __CRT_HAVE__sprintf_l
__LIBC __ATTR_LIBC_PRINTF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _sprintf_l)(char *__restrict __buf, char const *__restrict __format, __locale_t __locale, ...) __CASMNAME_SAME("_sprintf_l");
#else /* __CRT_HAVE__sprintf_l */
#include <local/stdio/_sprintf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_sprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _sprintf_l)(char *__restrict __buf, char const *__restrict __format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sprintf_l))(__buf, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _sprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sprintf_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__sprintf_l */
#ifdef __CRT_HAVE__sprintf_s_l
__LIBC __ATTR_LIBC_PRINTF(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _sprintf_s_l)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, ...) __CASMNAME_SAME("_sprintf_s_l");
#else /* __CRT_HAVE__sprintf_s_l */
#include <local/stdio/_sprintf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_sprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _sprintf_s_l)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sprintf_s_l))(__buf, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _sprintf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sprintf_s_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__sprintf_s_l */
#ifdef __CRT_HAVE__sprintf_p
__LIBC __ATTR_LIBC_PRINTF_P(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _sprintf_p)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, ...) __CASMNAME_SAME("_sprintf_p");
#else /* __CRT_HAVE__sprintf_p */
#include <local/stdio/_sprintf_p.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_sprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _sprintf_p)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sprintf_p))(__buf, __bufsize, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _sprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sprintf_p))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__sprintf_p */
#ifdef __CRT_HAVE__sprintf_p_l
__LIBC __ATTR_LIBC_PRINTF_P(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _sprintf_p_l)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, ...) __CASMNAME_SAME("_sprintf_p_l");
#else /* __CRT_HAVE__sprintf_p_l */
#include <local/stdio/_sprintf_p_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_sprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _sprintf_p_l)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sprintf_p_l))(__buf, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _sprintf_p_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sprintf_p_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__sprintf_p_l */

#ifdef __CRT_HAVE__vscprintf
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_vscprintf,(char const *__restrict __format, __builtin_va_list __args),(__format,__args))
#else /* __CRT_HAVE__vscprintf */
#include <local/stdio/_vscprintf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL _vscprintf)(char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscprintf))(__format, __args); })
#endif /* !__CRT_HAVE__vscprintf */
#ifdef __CRT_HAVE__scprintf
__LIBC __ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _scprintf)(char const *__restrict __format, ...) __CASMNAME_SAME("_scprintf");
#else /* __CRT_HAVE__scprintf */
#include <local/stdio/_scprintf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_scprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _scprintf)(char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scprintf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _scprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scprintf))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__scprintf */

#ifdef __CRT_HAVE__vscprintf_l
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_vscprintf_l,(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#else /* __CRT_HAVE__vscprintf_l */
#include <local/stdio/_vscprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL _vscprintf_l)(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscprintf_l))(__format, __locale, __args); })
#endif /* !__CRT_HAVE__vscprintf_l */
#ifdef __CRT_HAVE__vscprintf_p
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_vscprintf_p,(char const *__restrict __format, __builtin_va_list __args),(__format,__args))
#else /* __CRT_HAVE__vscprintf_p */
#include <local/stdio/_vscprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL _vscprintf_p)(char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscprintf_p))(__format, __args); })
#endif /* !__CRT_HAVE__vscprintf_p */
#ifdef __CRT_HAVE__vscprintf_p_l
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_vscprintf_p_l,(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#else /* __CRT_HAVE__vscprintf_p_l */
#include <local/stdio/_vscprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL _vscprintf_p_l)(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscprintf_p_l))(__format, __locale, __args); })
#endif /* !__CRT_HAVE__vscprintf_p_l */
#ifdef __CRT_HAVE__scprintf_l
__LIBC __ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _scprintf_l)(char const *__restrict __format, __locale_t __locale, ...) __CASMNAME_SAME("_scprintf_l");
#else /* __CRT_HAVE__scprintf_l */
#include <local/stdio/_scprintf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_scprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _scprintf_l)(char const *__restrict __format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scprintf_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _scprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scprintf_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__scprintf_l */
#ifdef __CRT_HAVE__scprintf_p
__LIBC __ATTR_WUNUSED __ATTR_LIBC_PRINTF_P(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _scprintf_p)(char const *__restrict __format, ...) __CASMNAME_SAME("_scprintf_p");
#else /* __CRT_HAVE__scprintf_p */
#include <local/stdio/_scprintf_p.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_scprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_PRINTF_P(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _scprintf_p)(char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scprintf_p))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _scprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scprintf_p))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__scprintf_p */
#ifdef __CRT_HAVE__scprintf_p_l
__LIBC __ATTR_WUNUSED __ATTR_LIBC_PRINTF_P(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _scprintf_p_l)(char const *__restrict __format, __locale_t __locale, ...) __CASMNAME_SAME("_scprintf_p_l");
#else /* __CRT_HAVE__scprintf_p_l */
#include <local/stdio/_scprintf_p_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_scprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_PRINTF_P(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _scprintf_p_l)(char const *__restrict __format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scprintf_p_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _scprintf_p_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scprintf_p_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__scprintf_p_l */

#ifdef __CRT_HAVE__vsnprintf
/* WARNING: This function returns the number of written character. - Not the required buffer size! */
__CDECLARE(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_vsnprintf,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __builtin_va_list __args),(__buf,__bufsize,__format,__args))
#else /* __CRT_HAVE__vsnprintf */
#include <local/stdio/_vsnprintf.h>
/* WARNING: This function returns the number of written character. - Not the required buffer size! */
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsnprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL _vsnprintf)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnprintf))(__buf, __bufsize, __format, __args); })
#endif /* !__CRT_HAVE__vsnprintf */
#ifdef __CRT_HAVE__vsnprintf_l
__CDECLARE(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_vsnprintf_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),(__buf,__bufsize,__format,__locale,__args))
#elif defined(__CRT_HAVE__vsprintf_s_l)
__CREDIRECT(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_vsnprintf_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vsprintf_s_l,(__buf,__bufsize,__format,__locale,__args))
#else /* ... */
#include <local/stdio/_vsnprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsnprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL _vsnprintf_l)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnprintf_l))(__buf, __bufsize, __format, __locale, __args); })
#endif /* !... */
#ifdef __CRT_HAVE__vsnprintf
/* WARNING: This function returns the number of written character. - Not the required buffer size! */
__CREDIRECT(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_vsnprintf_c,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __builtin_va_list __args),_vsnprintf,(__buf,__bufsize,__format,__args))
#else /* __CRT_HAVE__vsnprintf */
#include <local/stdio/_vsnprintf.h>
/* WARNING: This function returns the number of written character. - Not the required buffer size! */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL _vsnprintf_c)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnprintf))(__buf, __bufsize, __format, __args); }
#endif /* !__CRT_HAVE__vsnprintf */
#ifdef __CRT_HAVE__vsnprintf_l
__CREDIRECT(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_vsnprintf_c_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vsnprintf_l,(__buf,__bufsize,__format,__locale,__args))
#elif defined(__CRT_HAVE__vsprintf_s_l)
__CREDIRECT(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_vsnprintf_c_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vsprintf_s_l,(__buf,__bufsize,__format,__locale,__args))
#else /* ... */
#include <local/stdio/_vsnprintf_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL _vsnprintf_c_l)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnprintf_l))(__buf, __bufsize, __format, __locale, __args); }
#endif /* !... */
#ifdef __CRT_HAVE__vsnprintf_s
__CDECLARE(__ATTR_LIBC_PRINTF(4, 0) __ATTR_NONNULL((4)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_vsnprintf_s,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args),(__buf,__bufsize,__buflen,__format,__args))
#else /* __CRT_HAVE__vsnprintf_s */
#include <local/stdio/_vsnprintf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsnprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(4, 0) __ATTR_NONNULL((4)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL _vsnprintf_s)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnprintf_s))(__buf, __bufsize, __buflen, __format, __args); })
#endif /* !__CRT_HAVE__vsnprintf_s */
#ifdef __CRT_HAVE__vsnprintf_s_l
__CDECLARE(__ATTR_LIBC_PRINTF(4, 0) __ATTR_NONNULL((4)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_vsnprintf_s_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),(__buf,__bufsize,__buflen,__format,__locale,__args))
#else /* __CRT_HAVE__vsnprintf_s_l */
#include <local/stdio/_vsnprintf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsnprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(4, 0) __ATTR_NONNULL((4)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL _vsnprintf_s_l)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnprintf_s_l))(__buf, __bufsize, __buflen, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vsnprintf_s_l */
#ifdef __CRT_HAVE__snprintf
__LIBC __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, ...) __CASMNAME_SAME("_snprintf");
#else /* __CRT_HAVE__snprintf */
#include <local/stdio/_snprintf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf))(__buf, __bufsize, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snprintf */
#ifdef __CRT_HAVE__snprintf_l
__LIBC __ATTR_LIBC_PRINTF(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_l)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, ...) __CASMNAME_SAME("_snprintf_l");
#else /* __CRT_HAVE__snprintf_l */
#include <local/stdio/_snprintf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_l)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_l))(__buf, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snprintf_l */
#ifdef __CRT_HAVE__snprintf_c
__LIBC __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_c)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, ...) __CASMNAME_SAME("_snprintf_c");
#else /* __CRT_HAVE__snprintf_c */
#include <local/stdio/_snprintf_c.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snprintf_c, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_c)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_c))(__buf, __bufsize, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snprintf_c (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_c))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snprintf_c */
#ifdef __CRT_HAVE__snprintf_c_l
__LIBC __ATTR_LIBC_PRINTF(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_c_l)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, ...) __CASMNAME_SAME("_snprintf_c_l");
#else /* __CRT_HAVE__snprintf_c_l */
#include <local/stdio/_snprintf_c_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snprintf_c_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_c_l)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_c_l))(__buf, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snprintf_c_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_c_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snprintf_c_l */
#ifdef __CRT_HAVE__snprintf_s
__LIBC __ATTR_LIBC_PRINTF(4, 5) __ATTR_NONNULL((4)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_s)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, char const *__restrict __format, ...) __CASMNAME_SAME("_snprintf_s");
#else /* __CRT_HAVE__snprintf_s */
#include <local/stdio/_snprintf_s.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(4, 5) __ATTR_NONNULL((4)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_s)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_s))(__buf, __bufsize, __buflen, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snprintf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_s))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snprintf_s */
#ifdef __CRT_HAVE__snprintf_s_l
__LIBC __ATTR_LIBC_PRINTF(4, 6) __ATTR_NONNULL((4)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_s_l)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, char const *__restrict __format, __locale_t __locale, ...) __CASMNAME_SAME("_snprintf_s_l");
#else /* __CRT_HAVE__snprintf_s_l */
#include <local/stdio/_snprintf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(4, 6) __ATTR_NONNULL((4)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_s_l)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, char const *__restrict __format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_s_l))(__buf, __bufsize, __buflen, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snprintf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_s_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snprintf_s_l */

#ifdef __CRT_HAVE__vprintf_l
__CDECLARE(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,_vprintf_l,(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__CRT_HAVE__vprintf_s_l)
__CREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,_vprintf_l,(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vprintf_s_l,(__format,__locale,__args))
#elif defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
#include <local/stdio/_vprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL _vprintf_l)(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vprintf_l))(__format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vprintf_l
__CREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,_vprintf_s_l,(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vprintf_l,(__format,__locale,__args))
#elif defined(__CRT_HAVE__vprintf_s_l)
__CDECLARE(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,_vprintf_s_l,(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
#include <local/stdio/_vprintf_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL _vprintf_s_l)(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vprintf_l))(__format, __locale, __args); }
#endif /* ... */
#ifdef __CRT_HAVE__vprintf_p
__CDECLARE(__ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,_vprintf_p,(char const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE__vfprintf_p) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite))
#include <local/stdio/_vprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL _vprintf_p)(char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vprintf_p))(__format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vprintf_p_l
__CDECLARE(__ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,_vprintf_p_l,(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__CRT_HAVE__vprintf_p) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE__vfprintf_p) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
#include <local/stdio/_vprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL _vprintf_p_l)(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vprintf_p_l))(__format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__printf_l
__LIBC __ATTR_LIBC_PRINTF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _printf_l)(char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_printf_l");
#elif defined(__CRT_HAVE__vprintf_l) || defined(__CRT_HAVE__vprintf_s_l) || defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
#include <local/stdio/_printf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_printf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _printf_l)(char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_printf_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _printf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_printf_l))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__printf_s_l
__LIBC __ATTR_LIBC_PRINTF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _printf_s_l)(char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_printf_s_l");
#elif defined(__CRT_HAVE__vprintf_l) || defined(__CRT_HAVE__vprintf_s_l) || defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
#include <local/stdio/_printf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_printf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _printf_s_l)(char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_printf_s_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _printf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_printf_s_l))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__printf_p
__LIBC __ATTR_LIBC_PRINTF_P(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _printf_p)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("_printf_p");
#elif defined(__CRT_HAVE__vprintf_p) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE__vfprintf_p) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
#include <local/stdio/_printf_p.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_printf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _printf_p)(char const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_printf_p))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _printf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_printf_p))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__printf_p_l
__LIBC __ATTR_LIBC_PRINTF_P(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _printf_p_l)(char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_printf_p_l");
#elif defined(__CRT_HAVE__vprintf_p_l) || defined(__CRT_HAVE__vprintf_p) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE__vfprintf_p) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
#include <local/stdio/_printf_p_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_printf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _printf_p_l)(char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_printf_p_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _printf_p_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_printf_p_l))
#endif /* !__cplusplus */
#endif /* ... */

#ifdef __CRT_HAVE__vfprintf_l
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,_vfprintf_l,(__FILE *__restrict __stream, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),(__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE__vfprintf_s_l)
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,_vfprintf_l,(__FILE *__restrict __stream, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vfprintf_s_l,(__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
#include <local/stdio/_vfprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL _vfprintf_l)(__FILE *__restrict __stream, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfprintf_l))(__stream, __format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vfprintf_l
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,_vfprintf_s_l,(__FILE *__restrict __stream, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),_vfprintf_l,(__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE__vfprintf_s_l)
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,_vfprintf_s_l,(__FILE *__restrict __stream, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),(__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
#include <local/stdio/_vfprintf_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL _vfprintf_s_l)(__FILE *__restrict __stream, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfprintf_l))(__stream, __format, __locale, __args); }
#endif /* ... */
#ifdef __CRT_HAVE__vfprintf_p
__CDECLARE(__ATTR_LIBC_PRINTF_P(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,_vfprintf_p,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
#include <local/stdio/_vfprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL _vfprintf_p)(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfprintf_p))(__stream, __format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vfprintf_p_l
__CDECLARE(__ATTR_LIBC_PRINTF_P(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,_vfprintf_p_l,(__FILE *__restrict __stream, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args),(__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE__vfprintf_p) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
#include <local/stdio/_vfprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL _vfprintf_p_l)(__FILE *__restrict __stream, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfprintf_p_l))(__stream, __format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__fprintf_l
__LIBC __ATTR_LIBC_PRINTF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _fprintf_l)(__FILE *__restrict __stream, char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_fprintf_l");
#elif defined(__CRT_HAVE__vfprintf_l) || defined(__CRT_HAVE__vfprintf_s_l) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
#include <local/stdio/_fprintf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_fprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _fprintf_l)(__FILE *__restrict __stream, char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fprintf_l))(__stream, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _fprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fprintf_l))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__fprintf_s_l
__LIBC __ATTR_LIBC_PRINTF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _fprintf_s_l)(__FILE *__restrict __stream, char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_fprintf_s_l");
#elif defined(__CRT_HAVE__vfprintf_l) || defined(__CRT_HAVE__vfprintf_s_l) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
#include <local/stdio/_fprintf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_fprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _fprintf_s_l)(__FILE *__restrict __stream, char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fprintf_s_l))(__stream, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _fprintf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fprintf_s_l))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__fprintf_p
__LIBC __ATTR_LIBC_PRINTF_P(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _fprintf_p)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("_fprintf_p");
#elif defined(__CRT_HAVE__vfprintf_p) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
#include <local/stdio/_fprintf_p.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_fprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _fprintf_p)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fprintf_p))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _fprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fprintf_p))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__fprintf_p_l
__LIBC __ATTR_LIBC_PRINTF_P(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _fprintf_p_l)(__FILE *__restrict __stream, char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_fprintf_p_l");
#elif defined(__CRT_HAVE__vfprintf_p_l) || defined(__CRT_HAVE__vfprintf_p) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
#include <local/stdio/_fprintf_p_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_fprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL _fprintf_p_l)(__FILE *__restrict __stream, char const *__restrict __format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fprintf_p_l))(__stream, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _fprintf_p_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fprintf_p_l))
#endif /* !__cplusplus */
#endif /* ... */

#ifdef __USE_DOS_SLIB
#ifdef __CRT_HAVE_fopen_s
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),errno_t,__NOTHROW_RPC,fopen_s,(__FILE **__pstream, char const *__filename, char const *__modes),(__pstream,__filename,__modes))
#elif defined(__CRT_HAVE_fopen) || defined(__CRT_HAVE__IO_fopen) || defined(__CRT_HAVE_fopen64)
#include <local/stdio/fopen_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fopen_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) errno_t __NOTHROW_RPC(__LIBCCALL fopen_s)(__FILE **__pstream, char const *__filename, char const *__modes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fopen_s))(__pstream, __filename, __modes); })
#endif /* ... */
#ifdef __CRT_HAVE_freopen_s
__CDECLARE(__ATTR_NONNULL((1, 2, 3, 4)),errno_t,__NOTHROW_RPC,freopen_s,(__FILE **__pstream, char const *__filename, char const *__modes, __FILE *__oldstream),(__pstream,__filename,__modes,__oldstream))
#elif defined(__CRT_HAVE_freopen) || defined(__CRT_HAVE_freopen64) || defined(__CRT_HAVE_freopen_unlocked) || defined(__CRT_HAVE_freopen64_unlocked)
#include <local/stdio/freopen_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(freopen_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3, 4)) errno_t __NOTHROW_RPC(__LIBCCALL freopen_s)(__FILE **__pstream, char const *__filename, char const *__modes, __FILE *__oldstream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(freopen_s))(__pstream, __filename, __modes, __oldstream); })
#endif /* ... */
#ifdef __CRT_HAVE_tmpnam_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,tmpnam_s,(char *__restrict __buf, rsize_t __bufsize),(__buf,__bufsize))
#elif defined(__CRT_HAVE_tmpnam)
#include <local/stdio/tmpnam_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(tmpnam_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL tmpnam_s)(char *__restrict __buf, rsize_t __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tmpnam_s))(__buf, __bufsize); })
#endif /* ... */

#ifdef __CRT_HAVE_clearerr_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,clearerr_s,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_clearerr) || defined(__CRT_HAVE_clearerr_unlocked)
#include <local/stdio/clearerr_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(clearerr_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL clearerr_s)(__FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clearerr_s))(__stream); })
#endif /* ... */
#ifdef __CRT_HAVE_tmpfile_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_RPC,tmpfile_s,(__FILE **__pstream),(__pstream))
#elif defined(__CRT_HAVE_tmpfile64) || defined(__CRT_HAVE_tmpfile)
#include <local/stdio/tmpfile_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(tmpfile_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) errno_t __NOTHROW_RPC(__LIBCCALL tmpfile_s)(__FILE **__pstream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tmpfile_s))(__pstream); })
#endif /* ... */
#ifdef __CRT_HAVE_fread_s
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 5)),__SIZE_TYPE__,__NOTHROW_RPC,fread_s,(void *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),(__buf,__bufsize,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)
#include <local/stdio/fread_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fread_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 5)) __SIZE_TYPE__ __NOTHROW_RPC(__LIBCCALL fread_s)(void *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fread_s))(__buf, __bufsize, __elemsize, __elemcount, __stream); })
#endif /* ... */
#ifdef __CRT_HAVE_gets_s
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_RPC,gets_s,(char *__restrict __buf, rsize_t __bufsize),(__buf,__bufsize))
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgets) || defined(__CRT_HAVE_fgets_unlocked) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))))
#include <local/stdio/gets_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(gets_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_RPC(__LIBCCALL gets_s)(char *__restrict __buf, rsize_t __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gets_s))(__buf, __bufsize); })
#endif /* ... */
#if __has_builtin(__builtin_printf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_printf) && __has_builtin(__builtin_va_arg_pack)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__CEIREDIRECT(__ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,printf_s,(char const *__restrict __format, ...),printf,{ return __builtin_printf(__format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_printf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf_s)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("printf_unlocked");
#elif defined(__CRT_HAVE_printf)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf_s)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("printf");
#elif defined(__CRT_HAVE__IO_printf)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf_s)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("_IO_printf");
#elif defined(__CRT_HAVE_printf_s)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf_s)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("printf_s");
#elif defined(__CRT_HAVE_printf_unlocked)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf_s)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("printf_unlocked");
#elif defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
#include <local/stdio/printf.h>
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
#define printf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(printf))
#endif /* ... */
#if __has_builtin(__builtin_vprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vprintf)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__CEIREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,vprintf_s,(char const *__restrict __format, __builtin_va_list __args),vprintf,{ return __builtin_vprintf(__format, __args); })
#elif defined(__CRT_HAVE_vprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,vprintf_s,(char const *__restrict __format, __builtin_va_list __args),vprintf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_vprintf)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,vprintf_s,(char const *__restrict __format, __builtin_va_list __args),vprintf,(__format,__args))
#elif defined(__CRT_HAVE_vprintf_s)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__CDECLARE(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,vprintf_s,(char const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE_vprintf_unlocked)
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,vprintf_s,(char const *__restrict __format, __builtin_va_list __args),vprintf_unlocked,(__format,__args))
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite))
#include <local/stdio/vprintf.h>
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL vprintf_s)(char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vprintf))(__format, __args); }
#endif /* ... */
#if __has_builtin(__builtin_fprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fprintf) && __has_builtin(__builtin_va_arg_pack)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CEIREDIRECT(__ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,fprintf_s,(FILE *__restrict __stream, char const *__restrict __format, ...),fprintf,{ return __builtin_fprintf(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_fprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf_s)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_unlocked");
#elif defined(__CRT_HAVE_fprintf)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf_s)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf");
#elif defined(__CRT_HAVE__IO_fprintf)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf_s)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("_IO_fprintf");
#elif defined(__CRT_HAVE_fprintf_s)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf_s)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fprintf_s");
#elif defined(__CRT_HAVE_fprintf_unlocked)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf_s)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_unlocked");
#elif defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
#include <local/stdio/fprintf.h>
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
#define fprintf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fprintf))
#endif /* ... */
#if __has_builtin(__builtin_vfprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfprintf)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CEIREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf_s,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf,{ return __builtin_vfprintf(__stream, __format, __args); })
#elif defined(__CRT_HAVE_vfprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf_s,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfprintf)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf_s,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfprintf_s)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf_s,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE__IO_vfprintf)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf_s,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_IO_vfprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfprintf_unlocked)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf_s,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
#include <local/stdio/vfprintf.h>
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL vfprintf_s)(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfprintf))(__stream, __format, __args); }
#endif /* ... */
#if __has_builtin(__builtin_snprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_snprintf) && __has_builtin(__builtin_va_arg_pack)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__CEIREDIRECT(__ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,sprintf_s,(char *__restrict __buf, size_t __buflen, char const *__restrict __format, ...),snprintf,{ return __builtin_snprintf(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_snprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__LIBC __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL sprintf_s)(char *__restrict __buf, size_t __buflen, char const *__restrict __format, ...) __CASMNAME("snprintf");
#else /* ... */
#include <local/stdio/snprintf.h>
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
#define sprintf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(snprintf))
#endif /* !... */
#if __has_builtin(__builtin_vsnprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vsnprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__CEIREDIRECT(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsprintf_s,(char *__restrict __buf, size_t __buflen, char const *__restrict __format, __builtin_va_list __args),vsnprintf,{ return __builtin_vsnprintf(__buf, __buflen, __format, __args); })
#elif defined(__CRT_HAVE_vsnprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__CREDIRECT(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsprintf_s,(char *__restrict __buf, size_t __buflen, char const *__restrict __format, __builtin_va_list __args),vsnprintf,(__buf,__buflen,__format,__args))
#elif defined(__CRT_HAVE___vsnprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__CREDIRECT(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsprintf_s,(char *__restrict __buf, size_t __buflen, char const *__restrict __format, __builtin_va_list __args),__vsnprintf,(__buf,__buflen,__format,__args))
#else /* ... */
#include <local/stdio/vsnprintf.h>
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsprintf_s)(char *__restrict __buf, size_t __buflen, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsnprintf))(__buf, __buflen, __format, __args); }
#endif /* !... */
#if __has_builtin(__builtin_fscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fscanf) && __has_builtin(__builtin_va_arg_pack)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fscanf_s,(FILE *__restrict __stream, char const *__restrict __format, ...),fscanf,{ return __builtin_fscanf(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_fscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fscanf_s)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fscanf_unlocked");
#elif defined(__CRT_HAVE_fscanf)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fscanf_s)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fscanf");
#elif defined(__CRT_HAVE_fscanf_unlocked)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fscanf_s)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fscanf_unlocked");
#elif defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
#include <local/stdio/fscanf.h>
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
#define fscanf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fscanf))
#endif /* ... */
#if defined(__CRT_HAVE_vfscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_s,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfscanf_unlocked,(__stream,__format,__args))
#elif __has_builtin(__builtin_vfscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfscanf)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_s,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfscanf,{ return __builtin_vfscanf(__stream, __format, __args); })
#elif defined(__CRT_HAVE_vfscanf)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_s,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE__vfscanf)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_s,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_vfscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE__vfscanf_s)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_s,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_vfscanf_s,(__stream,__format,__args))
#elif defined(__CRT_HAVE__IO_vfscanf)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_s,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_IO_vfscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfscanf_unlocked)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_s,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfscanf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE___vfscanf)
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_s,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),__vfscanf,(__stream,__format,__args))
#elif (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
#include <local/stdio/vfscanf.h>
/* Scan data from `STREAM', following `FORMAT'
 * Return the number of successfully scanned data items */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL vfscanf_s)(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfscanf))(__stream, __format, __args); }
#endif /* ... */
#if __has_builtin(__builtin_scanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scanf) && __has_builtin(__builtin_va_arg_pack)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,scanf_s,(char const *__restrict __format, ...),scanf,{ return __builtin_scanf(__format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_scanf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL scanf_s)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("scanf_unlocked");
#elif defined(__CRT_HAVE_scanf)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL scanf_s)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("scanf");
#elif defined(__CRT_HAVE_scanf_unlocked)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL scanf_s)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("scanf_unlocked");
#elif defined(__CRT_HAVE_vscanf) || defined(__CRT_HAVE__vscanf) || defined(__CRT_HAVE_vscanf_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
#include <local/stdio/scanf.h>
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
#define scanf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scanf))
#endif /* ... */
#if __has_builtin(__builtin_vscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vscanf)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vscanf_s,(char const *__restrict __format, __builtin_va_list __args),vscanf,{ return __builtin_vscanf(__format, __args); })
#elif defined(__CRT_HAVE_vscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vscanf_s,(char const *__restrict __format, __builtin_va_list __args),vscanf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_vscanf)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vscanf_s,(char const *__restrict __format, __builtin_va_list __args),vscanf,(__format,__args))
#elif defined(__CRT_HAVE__vscanf)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vscanf_s,(char const *__restrict __format, __builtin_va_list __args),_vscanf,(__format,__args))
#elif defined(__CRT_HAVE_vscanf_unlocked)
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vscanf_s,(char const *__restrict __format, __builtin_va_list __args),vscanf_unlocked,(__format,__args))
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))))
#include <local/stdio/vscanf.h>
/* Scan data from `stdin', following `FORMAT'
 * Return the number of successfully scanned data items */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL vscanf_s)(char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vscanf))(__format, __args); }
#endif /* ... */
#if __has_builtin(__builtin_sscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sscanf) && __has_builtin(__builtin_va_arg_pack)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__CEIREDIRECT(__ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,sscanf_s,(char const *__restrict __input, char const *__restrict __format, ...),sscanf,{ return __builtin_sscanf(__input, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_sscanf)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL sscanf_s)(char const *__restrict __input, char const *__restrict __format, ...) __CASMNAME("sscanf");
#elif defined(__CRT_HAVE__IO_sscanf)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL sscanf_s)(char const *__restrict __input, char const *__restrict __format, ...) __CASMNAME("_IO_sscanf");
#else /* ... */
#include <local/stdio/sscanf.h>
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
#define sscanf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sscanf))
#endif /* !... */
#if __has_builtin(__builtin_vsscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vsscanf)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsscanf_s,(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args),vsscanf,{ return __builtin_vsscanf(__input, __format, __args); })
#elif defined(__CRT_HAVE_vsscanf)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsscanf_s,(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args),vsscanf,(__input,__format,__args))
#elif defined(__CRT_HAVE__vsscanf)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsscanf_s,(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args),_vsscanf,(__input,__format,__args))
#elif defined(__CRT_HAVE__vsscanf_s)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsscanf_s,(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args),_vsscanf_s,(__input,__format,__args))
#elif defined(__CRT_HAVE___vsscanf)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsscanf_s,(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args),__vsscanf,(__input,__format,__args))
#else /* ... */
#include <local/stdio/vsscanf.h>
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsscanf_s)(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsscanf))(__input, __format, __args); }
#endif /* !... */
#ifdef __CRT_HAVE_vsnprintf_s
__CDECLARE(__ATTR_LIBC_PRINTF(4, 0) __ATTR_NONNULL((4)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsnprintf_s,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args),(__buf,__bufsize,__buflen,__format,__args))
#else /* __CRT_HAVE_vsnprintf_s */
#include <local/stdio/vsnprintf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vsnprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(4, 0) __ATTR_NONNULL((4)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsnprintf_s)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsnprintf_s))(__buf, __bufsize, __buflen, __format, __args); })
#endif /* !__CRT_HAVE_vsnprintf_s */
#endif /* __USE_DOS_SLIB */

#ifndef _CRT_WPERROR_DEFINED
#define _CRT_WPERROR_DEFINED 1
#ifdef __CRT_HAVE__wperror
__CDECLARE_VOID(__ATTR_COLD,__THROWING,_wperror,(__WCHAR_TYPE__ const *__restrict __message),(__message))
#else /* __CRT_HAVE__wperror */
#include <parts/errno.h>
#if !defined(__NO_STDSTREAMS) && defined(__libc_geterrno) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite))
#include <local/stdio/_wperror.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wperror, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_COLD void (__LIBCCALL _wperror)(__WCHAR_TYPE__ const *__restrict __message) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wperror))(__message); })
#else /* !__NO_STDSTREAMS && __libc_geterrno && (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite) */
#undef _CRT_WPERROR_DEFINED
#endif /* __NO_STDSTREAMS || !__libc_geterrno || (!__CRT_HAVE_fprintf && !__CRT_HAVE__IO_fprintf && !__CRT_HAVE_fprintf_s && !__CRT_HAVE_fprintf_unlocked && !__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_fputc && !__CRT_HAVE_putc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE_putc_unlocked && (!__CRT_DOS || !__CRT_HAVE__flsbuf) && !__CRT_HAVE_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock && !__CRT_HAVE__IO_fwrite) */
#endif /* !__CRT_HAVE__wperror */
#endif /* !_CRT_WPERROR_DEFINED */

#endif /* _STDIO_DEFINED */
#ifdef __CRT_HAVE_fgetc_unlocked
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fgetc_nolock,(__FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fgetc_nolock,(__FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fgetc_nolock,(__FILE *__restrict __stream),getc,(__stream))
#elif defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fgetc_nolock,(__FILE *__restrict __stream),fgetc,(__stream))
#elif defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fgetc_nolock,(__FILE *__restrict __stream),_IO_getc,(__stream))
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)
#include <local/stdio/fgetc_unlocked.h>
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL _fgetc_nolock)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc_unlocked))(__stream); }
#endif /* ... */
#if __has_builtin(__builtin_fputc_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CEIREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_fputc_nolock,(int __ch, __FILE *__restrict __stream),fputc_unlocked,{ return __builtin_fputc_unlocked(__ch, __stream); })
#elif defined(__CRT_HAVE_fputc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_fputc_nolock,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_putc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_fputc_nolock,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_fputc_nolock,(int __ch, __FILE *__restrict __stream),putc,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_fputc_nolock,(int __ch, __FILE *__restrict __stream),fputc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_fputc_nolock,(int __ch, __FILE *__restrict __stream),_IO_putc,(__ch,__stream))
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s)
#include <local/stdio/fputc_unlocked.h>
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int (__LIBCCALL _fputc_nolock)(int __ch, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc_unlocked))(__ch, __stream); }
#endif /* ... */
#ifdef __CRT_HAVE_fgetc_unlocked
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_getc_nolock,(__FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_getc_nolock,(__FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_getc_nolock,(__FILE *__restrict __stream),getc,(__stream))
#elif defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_getc_nolock,(__FILE *__restrict __stream),fgetc,(__stream))
#elif defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_getc_nolock,(__FILE *__restrict __stream),_IO_getc,(__stream))
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)
#include <local/stdio/fgetc_unlocked.h>
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL _getc_nolock)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc_unlocked))(__stream); }
#endif /* ... */
#if __has_builtin(__builtin_fputc_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CEIREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_putc_nolock,(int __ch, __FILE *__restrict __stream),fputc_unlocked,{ return __builtin_fputc_unlocked(__ch, __stream); })
#elif defined(__CRT_HAVE_fputc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_putc_nolock,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_putc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_putc_nolock,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_putc_nolock,(int __ch, __FILE *__restrict __stream),putc,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_putc_nolock,(int __ch, __FILE *__restrict __stream),fputc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_putc_nolock,(int __ch, __FILE *__restrict __stream),_IO_putc,(__ch,__stream))
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s)
#include <local/stdio/fputc_unlocked.h>
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int (__LIBCCALL _putc_nolock)(int __ch, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc_unlocked))(__ch, __stream); }
#endif /* ... */
#ifdef __CRT_HAVE_getchar_unlocked
/* Same as `getchar()', but performs I/O without acquiring a lock to `stdin' */
__CREDIRECT(,int,__THROWING,_getchar_nolock,(void),getchar_unlocked,())
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread))
#include <local/stdio/getchar_unlocked.h>
/* Same as `getchar()', but performs I/O without acquiring a lock to `stdin' */
__FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL _getchar_nolock)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getchar_unlocked))(); }
#endif /* ... */
#if __has_builtin(__builtin_putchar_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_putchar_unlocked)
/* Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
__CEIREDIRECT(,int,__THROWING,_putchar_nolock,(int __ch),putchar_unlocked,{ return __builtin_putchar_unlocked(__ch); })
#elif defined(__CRT_HAVE_putchar_unlocked)
/* Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
__CREDIRECT(,int,__THROWING,_putchar_nolock,(int __ch),putchar_unlocked,(__ch))
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s))
#include <local/stdio/putchar_unlocked.h>
/* Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
__FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL _putchar_nolock)(int __ch) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putchar_unlocked))(__ch); }
#endif /* ... */
#ifdef __CRT_HAVE_flockfile
/* Acquire a lock to `STREAM' and block until doing so succeeds */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC,_lock_file,(__FILE *__restrict __stream),flockfile,(__stream))
#elif defined(__CRT_HAVE__lock_file)
/* Acquire a lock to `STREAM' and block until doing so succeeds */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC,_lock_file,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__IO_flockfile)
/* Acquire a lock to `STREAM' and block until doing so succeeds */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC,_lock_file,(__FILE *__restrict __stream),_IO_flockfile,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE_funlockfile
/* Release a previously acquired lock from `STREAM' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_unlock_file,(__FILE *__restrict __stream),funlockfile,(__stream))
#elif defined(__CRT_HAVE__unlock_file)
/* Release a previously acquired lock from `STREAM' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_unlock_file,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__IO_funlockfile)
/* Release a previously acquired lock from `STREAM' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_unlock_file,(__FILE *__restrict __stream),_IO_funlockfile,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE_fclose
/* Close and destroy a given file `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fclose_nolock,(FILE *__restrict __stream),fclose,(__stream))
#elif defined(__CRT_HAVE__fclose_nolock)
/* Close and destroy a given file `STREAM' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,_fclose_nolock,(FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__IO_fclose)
/* Close and destroy a given file `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fclose_nolock,(FILE *__restrict __stream),_IO_fclose,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE_fflush_unlocked
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(,int,__THROWING,_fflush_nolock,(__FILE *__stream),fflush_unlocked,(__stream))
#elif defined(__CRT_HAVE__fflush_nolock)
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
__CDECLARE(,int,__THROWING,_fflush_nolock,(__FILE *__stream),(__stream))
#elif defined(__CRT_HAVE_fflush)
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(,int,__THROWING,_fflush_nolock,(__FILE *__stream),fflush,(__stream))
#elif defined(__CRT_HAVE__IO_fflush)
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(,int,__THROWING,_fflush_nolock,(__FILE *__stream),_IO_fflush,(__stream))
#else /* ... */
#include <local/stdio/fflush_unlocked.h>
/* Same as `fflush()', but performs I/O without acquiring a lock to `STREAM' */
__FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL _fflush_nolock)(__FILE *__stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fflush_unlocked))(__stream); }
#endif /* !... */
#ifdef __CRT_HAVE_fread_unlocked
/* Same as `fread()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,_fread_nolock,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fread)
/* Same as `fread()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,_fread_nolock,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fread_nolock)
/* Same as `fread()', but performs I/O without acquiring a lock to `STREAM' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,_fread_nolock,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__IO_fread)
/* Same as `fread()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,_fread_nolock,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_IO_fread,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf))
#include <local/stdio/fread_unlocked.h>
/* Same as `fread()', but performs I/O without acquiring a lock to `STREAM' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 4)) __SIZE_TYPE__ (__LIBCCALL _fread_nolock)(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fread_unlocked))(__buf, __elemsize, __elemcount, __stream); }
#endif /* ... */
#ifdef __CRT_HAVE_fwrite_unlocked
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,_fwrite_nolock,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fwrite)
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,_fwrite_nolock,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fwrite_nolock)
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,_fwrite_nolock,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__IO_fwrite)
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,_fwrite_nolock,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_IO_fwrite,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)
#include <local/stdio/fwrite_unlocked.h>
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 4)) __SIZE_TYPE__ (__LIBCCALL _fwrite_nolock)(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwrite_unlocked))(__buf, __elemsize, __elemcount, __stream); }
#endif /* ... */
#ifdef __CRT_HAVE__fread_nolock_s
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 5)),__SIZE_TYPE__,__THROWING,_fread_nolock_s,(void *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),(__buf,__bufsize,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)
#include <local/stdio/_fread_nolock_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_fread_nolock_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 5)) __SIZE_TYPE__ (__LIBCCALL _fread_nolock_s)(void *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fread_nolock_s))(__buf, __bufsize, __elemsize, __elemcount, __stream); })
#endif /* ... */
#ifdef __CRT_HAVE_fseek_unlocked
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseek_nolock,(__FILE *__restrict __stream, long int __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock)
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,_fseek_nolock,(__FILE *__restrict __stream, long int __off, int __whence),(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseek_nolock,(__FILE *__restrict __stream, long int __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseek_nolock,(__FILE *__restrict __stream, long int __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseek_nolock,(__FILE *__restrict __stream, long int __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseek_nolock,(__FILE *__restrict __stream, long int __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseek_nolock,(__FILE *__restrict __stream, long int __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseek_nolock,(__FILE *__restrict __stream, long int __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64)
#include <local/stdio/fseek_unlocked.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL _fseek_nolock)(__FILE *__restrict __stream, long int __off, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fseek_unlocked))(__stream, __off, __whence); }
#endif /* ... */
#ifdef __CRT_HAVE_ftell_unlocked
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock)
__CDECLARE(__ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE__IO_ftell) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE__ftelli64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || (defined(__CRT_HAVE_ftello64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked)
#include <local/stdio/ftell_unlocked.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) long int (__LIBCCALL _ftell_nolock)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftell_unlocked))(__stream); }
#endif /* ... */
#ifdef __CRT_HAVE_fseeko64_unlocked
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64_nolock,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock)
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64_nolock,(__FILE *__restrict __stream, __off64_t __off, int __whence),(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64_nolock,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64_nolock,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64_nolock,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
#include <local/stdio/fseeko64_unlocked.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL _fseeki64_nolock)(__FILE *__restrict __stream, __off64_t __off, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fseeko64_unlocked))(__stream, __off, __whence); }
#endif /* ... */
#ifdef __CRT_HAVE_ftello64_unlocked
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64_nolock,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64_nolock,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_ftello64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64_nolock,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE__ftelli64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64_nolock,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64_nolock,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || defined(__CRT_HAVE__IO_ftell)
#include <local/stdio/ftello64_unlocked.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __off64_t (__LIBCCALL _ftelli64_nolock)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftello64_unlocked))(__stream); }
#endif /* ... */
#ifdef __CRT_HAVE_ungetc_unlocked
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,_ungetc_nolock,(int __ch, __FILE *__restrict __stream),ungetc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetc_nolock)
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,_ungetc_nolock,(int __ch, __FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE_ungetc)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,_ungetc_nolock,(int __ch, __FILE *__restrict __stream),ungetc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_ungetc)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,_ungetc_nolock,(int __ch, __FILE *__restrict __stream),_IO_ungetc,(__ch,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_getchar_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Alias for `fgetc(stdin)' */
__CREDIRECT(,int,__THROWING,fgetchar,(void),getchar_unlocked,())
#elif defined(__CRT_HAVE_getchar)
/* Alias for `fgetc(stdin)' */
__CREDIRECT(,int,__THROWING,fgetchar,(void),getchar,())
#elif defined(__CRT_HAVE__fgetchar)
/* Alias for `fgetc(stdin)' */
__CREDIRECT(,int,__THROWING,fgetchar,(void),_fgetchar,())
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread))
#include <local/stdio/getchar.h>
/* Alias for `fgetc(stdin)' */
__FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL fgetchar)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getchar))(); }
#endif /* ... */
#if __has_builtin(__builtin_putchar) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_putchar)
/* Alias for `fputc(CH, stdout)' */
__CEIREDIRECT(,int,__THROWING,fputchar,(int __ch),putchar,{ return __builtin_putchar(__ch); })
#elif defined(__CRT_HAVE_putchar_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Alias for `fputc(CH, stdout)' */
__CREDIRECT(,int,__THROWING,fputchar,(int __ch),putchar_unlocked,(__ch))
#elif defined(__CRT_HAVE_putchar)
/* Alias for `fputc(CH, stdout)' */
__CREDIRECT(,int,__THROWING,fputchar,(int __ch),putchar,(__ch))
#elif defined(__CRT_HAVE__fputchar)
/* Alias for `fputc(CH, stdout)' */
__CREDIRECT(,int,__THROWING,fputchar,(int __ch),_fputchar,(__ch))
#elif defined(__CRT_HAVE_putchar_unlocked)
/* Alias for `fputc(CH, stdout)' */
__CREDIRECT(,int,__THROWING,fputchar,(int __ch),putchar_unlocked,(__ch))
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite))
#include <local/stdio/putchar.h>
/* Alias for `fputc(CH, stdout)' */
__FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL fputchar)(int __ch) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putchar))(__ch); }
#endif /* ... */
#ifdef __CRT_HAVE__flushall
__CREDIRECT(,int,__THROWING,flushall,(void),_flushall,())
#elif defined(__CRT_HAVE__IO_flush_all)
__CREDIRECT(,int,__THROWING,flushall,(void),_IO_flush_all,())
#else /* ... */
#include <local/stdio/_flushall.h>
__FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL flushall)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_flushall))(); }
#endif /* !... */
#ifdef __CRT_HAVE__rmtmp
__CREDIRECT(,int,__NOTHROW_RPC,rmtmp,(void),_rmtmp,())
#endif /* __CRT_HAVE__rmtmp */
#define SYS_OPEN     _SYS_OPEN

#ifndef _WSTDIO_DEFINED
#define _WSTDIO_DEFINED 1
#ifndef WEOF
#define WEOF __WEOF
#endif /* !WEOF */

/* Define 'wchar_t' */
#ifndef __wchar_t_defined
#define __wchar_t_defined 1
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */
#ifndef __fgetwc_defined
#define __fgetwc_defined 1
#ifdef __std_fgetwc_defined
__NAMESPACE_STD_USING(fgetwc)
#elif defined(__CRT_HAVE_fgetwc)
__CDECLARE(__ATTR_NONNULL((1)),wint_t,__THROWING,fgetwc,(FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_getwc)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__THROWING,fgetwc,(FILE *__restrict __stream),getwc,(__stream))
#else /* ... */
#undef __fgetwc_defined
#endif /* !... */
#endif /* !__fgetwc_defined */
#ifndef __fputwc_defined
#define __fputwc_defined 1
#ifdef __std_fputwc_defined
__NAMESPACE_STD_USING(fputwc)
#elif defined(__CRT_HAVE_fputwc)
__CDECLARE(__ATTR_NONNULL((2)),wint_t,__THROWING,fputwc,(wchar_t __wc, FILE *__stream),(__wc,__stream))
#elif defined(__CRT_HAVE_putwc)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__THROWING,fputwc,(wchar_t __wc, FILE *__stream),putwc,(__wc,__stream))
#else /* ... */
#undef __fputwc_defined
#endif /* !... */
#endif /* !__fputwc_defined */
#ifndef __getwc_defined
#define __getwc_defined 1
#ifdef __CRT_HAVE_fgetwc
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__THROWING,getwc,(FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_getwc)
__CDECLARE(__ATTR_NONNULL((1)),wint_t,__THROWING,getwc,(FILE *__restrict __stream),(__stream))
#else /* ... */
#undef __getwc_defined
#endif /* !... */
#endif /* !__getwc_defined */
#ifndef __getwchar_defined
#define __getwchar_defined 1
#ifdef __std_getwchar_defined
__NAMESPACE_STD_USING(getwchar)
#elif defined(__CRT_HAVE_getwchar)
__CDECLARE(,wint_t,__THROWING,getwchar,(void),())
#elif defined(__CRT_HAVE__fgetwchar)
__CREDIRECT(,wint_t,__THROWING,getwchar,(void),_fgetwchar,())
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc))
#include <local/wchar/getwchar.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getwchar, __FORCELOCAL __ATTR_ARTIFICIAL wint_t (__LIBCCALL getwchar)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwchar))(); })
#else /* ... */
#undef __getwchar_defined
#endif /* !... */
#endif /* !__getwchar_defined */
#ifndef __putwc_defined
#define __putwc_defined 1
#ifdef __CRT_HAVE_fputwc
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__THROWING,putwc,(wchar_t __wc, FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc)
__CDECLARE(__ATTR_NONNULL((2)),wint_t,__THROWING,putwc,(wchar_t __wc, FILE *__stream),(__wc,__stream))
#else /* ... */
#undef __putwc_defined
#endif /* !... */
#endif /* !__putwc_defined */
#ifndef __putwchar_defined
#define __putwchar_defined 1
#ifdef __std_putwchar_defined
__NAMESPACE_STD_USING(putwchar)
#elif defined(__CRT_HAVE_putwchar)
__CDECLARE(,wint_t,__THROWING,putwchar,(wchar_t __wc),(__wc))
#elif defined(__CRT_HAVE__fputwchar)
__CREDIRECT(,wint_t,__THROWING,putwchar,(wchar_t __wc),_fputwchar,(__wc))
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc))
#include <local/wchar/putwchar.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(putwchar, __FORCELOCAL __ATTR_ARTIFICIAL wint_t (__LIBCCALL putwchar)(wchar_t __wc) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putwchar))(__wc); })
#else /* ... */
#undef __putwchar_defined
#endif /* !... */
#endif /* !__putwchar_defined */
#ifndef __ungetwc_defined
#define __ungetwc_defined 1
#ifdef __std_ungetwc_defined
__NAMESPACE_STD_USING(ungetwc)
#elif defined(__CRT_HAVE_ungetwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetwc,(wint_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc)
__CDECLARE(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetwc,(wint_t __wc, FILE *__stream),(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc_unlocked)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetwc,(wint_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#else /* ... */
#undef __ungetwc_defined
#endif /* !... */
#endif /* !__ungetwc_defined */
#ifndef __fgetws_defined
#define __fgetws_defined 1
#ifdef __std_fgetws_defined
__NAMESPACE_STD_USING(fgetws)
#elif defined(__CRT_HAVE_fgetws_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),wchar_t *,__THROWING,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),wchar_t *,__THROWING,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),wchar_t *,__THROWING,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws_unlocked)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),wchar_t *,__THROWING,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),wchar_t *,__THROWING,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))
#include <local/wchar/fgetws.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetws, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) wchar_t *(__LIBCCALL fgetws)(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetws))(__buf, __bufsize, __stream); })
#else /* ... */
#undef __fgetws_defined
#endif /* !... */
#endif /* !__fgetws_defined */
#ifndef __fputws_defined
#define __fputws_defined 1
#ifdef __std_fputws_defined
__NAMESPACE_STD_USING(fputws)
#elif defined(__CRT_HAVE_fputws_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputws,(wchar_t const *__restrict __string, FILE *__restrict __stream),fputws_unlocked,(__string,__stream))
#elif defined(__CRT_HAVE__fputws_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputws,(wchar_t const *__restrict __string, FILE *__restrict __stream),_fputws_nolock,(__string,__stream))
#elif defined(__CRT_HAVE_fputws)
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputws,(wchar_t const *__restrict __string, FILE *__restrict __stream),(__string,__stream))
#elif defined(__CRT_HAVE_fputws_unlocked)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputws,(wchar_t const *__restrict __string, FILE *__restrict __stream),fputws_unlocked,(__string,__stream))
#elif defined(__CRT_HAVE__fputws_nolock)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputws,(wchar_t const *__restrict __string, FILE *__restrict __stream),_fputws_nolock,(__string,__stream))
#elif defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#include <local/wchar/fputws.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fputws, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL fputws)(wchar_t const *__restrict __string, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputws))(__string, __stream); })
#else /* ... */
#undef __fputws_defined
#endif /* !... */
#endif /* !__fputws_defined */
#ifndef __vfwprintf_defined
#define __vfwprintf_defined 1
#ifdef __std_vfwprintf_defined
__NAMESPACE_STD_USING(vfwprintf)
#elif defined(__CRT_HAVE_vfwprintf)
__CDECLARE(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfwprintf,(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#include <local/wchar/vfwprintf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vfwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL vfwprintf)(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf))(__stream, __format, __args); })
#else /* ... */
#undef __vfwprintf_defined
#endif /* !... */
#endif /* !__vfwprintf_defined */
#ifndef __fwprintf_defined
#define __fwprintf_defined 1
#ifdef __std_fwprintf_defined
__NAMESPACE_STD_USING(fwprintf)
#elif defined(__CRT_HAVE_fwprintf)
__LIBC __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwprintf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fwprintf");
#elif defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#include <local/wchar/fwprintf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(fwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwprintf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define fwprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf))
#endif /* !__cplusplus */
#else /* ... */
#undef __fwprintf_defined
#endif /* !... */
#endif /* !__fwprintf_defined */
#ifndef __vfwscanf_defined
#define __vfwscanf_defined 1
#ifdef __std_vfwscanf_defined
__NAMESPACE_STD_USING(vfwscanf)
#elif defined(__CRT_HAVE_vfwscanf)
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfwscanf,(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#else /* ... */
#undef __vfwscanf_defined
#endif /* !... */
#endif /* !__vfwscanf_defined */
#ifndef __fwscanf_defined
#define __fwscanf_defined 1
#ifdef __std_fwscanf_defined
__NAMESPACE_STD_USING(fwscanf)
#elif defined(__CRT_HAVE_fwscanf)
__LIBC __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwscanf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fwscanf");
#elif defined(__CRT_HAVE_vfwscanf)
#include <local/wchar/fwscanf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(fwscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwscanf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define fwscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf))
#endif /* !__cplusplus */
#else /* ... */
#undef __fwscanf_defined
#endif /* !... */
#endif /* !__fwscanf_defined */
#ifndef __vwprintf_defined
#define __vwprintf_defined 1
#ifdef __std_vwprintf_defined
__NAMESPACE_STD_USING(vwprintf)
#elif defined(__CRT_HAVE_vwprintf)
__CDECLARE(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vwprintf,(wchar_t const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif (defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS)
#include <local/wchar/vwprintf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL vwprintf)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf))(__format, __args); })
#else /* ... */
#undef __vwprintf_defined
#endif /* !... */
#endif /* !__vwprintf_defined */
#ifndef __wprintf_defined
#define __wprintf_defined 1
#ifdef __std_wprintf_defined
__NAMESPACE_STD_USING(wprintf)
#elif defined(__CRT_HAVE_wprintf)
__LIBC __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL wprintf)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("wprintf");
#elif defined(__CRT_HAVE_vwprintf) || ((defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS))
#include <local/wchar/wprintf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(wprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL wprintf)(wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define wprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf))
#endif /* !__cplusplus */
#else /* ... */
#undef __wprintf_defined
#endif /* !... */
#endif /* !__wprintf_defined */
#ifndef __vwscanf_defined
#define __vwscanf_defined 1
#ifdef __std_vwscanf_defined
__NAMESPACE_STD_USING(vwscanf)
#elif defined(__CRT_HAVE_vwscanf)
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vwscanf,(wchar_t const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)
#include <local/wchar/vwscanf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vwscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL vwscanf)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf))(__format, __args); })
#else /* ... */
#undef __vwscanf_defined
#endif /* !... */
#endif /* !__vwscanf_defined */
#ifndef __wscanf_defined
#define __wscanf_defined 1
#ifdef __std_wscanf_defined
__NAMESPACE_STD_USING(wscanf)
#elif defined(__CRT_HAVE_wscanf)
__LIBC __ATTR_LIBC_WSCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL wscanf)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("wscanf");
#elif defined(__CRT_HAVE_vwscanf) || (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS))
#include <local/wchar/wscanf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(wscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WSCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL wscanf)(wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define wscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf))
#endif /* !__cplusplus */
#else /* ... */
#undef __wscanf_defined
#endif /* !... */
#endif /* !__wscanf_defined */
#ifndef __vswscanf_defined
#define __vswscanf_defined 1
#ifdef __std_vswscanf_defined
__NAMESPACE_STD_USING(vswscanf)
#elif defined(__CRT_HAVE_vswscanf)
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vswscanf,(wchar_t const *__restrict __src, wchar_t const *__restrict __format, __builtin_va_list __args),(__src,__format,__args))
#else /* ... */
#include <local/wchar/vswscanf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vswscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vswscanf)(wchar_t const *__restrict __src, wchar_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswscanf))(__src, __format, __args); })
#endif /* !... */
#endif /* !__vswscanf_defined */
#ifndef __swscanf_defined
#define __swscanf_defined 1
#ifdef __std_swscanf_defined
__NAMESPACE_STD_USING(swscanf)
#elif defined(__CRT_HAVE_swscanf)
__LIBC __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swscanf)(wchar_t const *__restrict __src, wchar_t const *__restrict __format, ...) __CASMNAME_SAME("swscanf");
#else /* ... */
#include <local/wchar/swscanf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(swscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swscanf)(wchar_t const *__restrict __src, wchar_t const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swscanf))(__src, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define swscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swscanf))
#endif /* !__cplusplus */
#endif /* !... */
#endif /* !__swscanf_defined */
#ifdef __USE_DOS_SLIB
#ifndef __vswprintf_s_defined
#define __vswprintf_s_defined 1
#ifdef __CRT_HAVE_vswprintf
__CREDIRECT(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vswprintf_s,(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, __builtin_va_list __args),vswprintf,(__buf,__buflen,__format,__args))
#else /* __CRT_HAVE_vswprintf */
#include <local/wchar/vswprintf.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vswprintf_s)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswprintf))(__buf, __buflen, __format, __args); }
#endif /* !__CRT_HAVE_vswprintf */
#endif /* !__vswprintf_s_defined */
#ifndef __swprintf_s_defined
#define __swprintf_s_defined 1
#ifdef __CRT_HAVE_swprintf
__LIBC __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swprintf_s)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, ...) __CASMNAME("swprintf");
#elif defined(__CRT_HAVE__swprintf)
__LIBC __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swprintf_s)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, ...) __CASMNAME("_swprintf");
#else /* ... */
#include <local/wchar/swprintf.h>
#define swprintf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swprintf))
#endif /* !... */
#endif /* !__swprintf_s_defined */
#ifndef __vfwprintf_s_defined
#define __vfwprintf_s_defined 1
#ifdef __CRT_HAVE_vfwprintf
__CREDIRECT(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfwprintf_s,(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),vfwprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#include <local/wchar/vfwprintf.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL vfwprintf_s)(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf))(__stream, __format, __args); }
#else /* ... */
#undef __vfwprintf_s_defined
#endif /* !... */
#endif /* !__vfwprintf_s_defined */
#ifndef __fwprintf_s_defined
#define __fwprintf_s_defined 1
#ifdef __CRT_HAVE_fwprintf
__LIBC __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwprintf_s)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("fwprintf");
#elif defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#include <local/wchar/fwprintf.h>
#define fwprintf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf))
#else /* ... */
#undef __fwprintf_s_defined
#endif /* !... */
#endif /* !__fwprintf_s_defined */
#ifndef __vwprintf_s_defined
#define __vwprintf_s_defined 1
#ifdef __CRT_HAVE_vwprintf
__CREDIRECT(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vwprintf_s,(wchar_t const *__restrict __format, __builtin_va_list __args),vwprintf,(__format,__args))
#elif (defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS)
#include <local/wchar/vwprintf.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL vwprintf_s)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf))(__format, __args); }
#else /* ... */
#undef __vwprintf_s_defined
#endif /* !... */
#endif /* !__vwprintf_s_defined */
#ifndef __wprintf_s_defined
#define __wprintf_s_defined 1
#ifdef __CRT_HAVE_wprintf
__LIBC __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL wprintf_s)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("wprintf");
#elif defined(__CRT_HAVE_vwprintf) || ((defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS))
#include <local/wchar/wprintf.h>
#define wprintf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf))
#else /* ... */
#undef __wprintf_s_defined
#endif /* !... */
#endif /* !__wprintf_s_defined */
#ifndef __vswscanf_s_defined
#define __vswscanf_s_defined 1
#ifdef __CRT_HAVE_vswscanf
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vswscanf_s,(wchar_t const *__restrict __src, wchar_t const *__restrict __format, __builtin_va_list __args),vswscanf,(__src,__format,__args))
#else /* __CRT_HAVE_vswscanf */
#include <local/wchar/vswscanf.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vswscanf_s)(wchar_t const *__restrict __src, wchar_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswscanf))(__src, __format, __args); }
#endif /* !__CRT_HAVE_vswscanf */
#endif /* !__vswscanf_s_defined */
#ifndef __swscanf_s_defined
#define __swscanf_s_defined 1
#ifdef __CRT_HAVE_swscanf
__LIBC __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swscanf_s)(wchar_t const *__restrict __src, wchar_t const *__restrict __format, ...) __CASMNAME("swscanf");
#else /* __CRT_HAVE_swscanf */
#include <local/wchar/swscanf.h>
#define swscanf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swscanf))
#endif /* !__CRT_HAVE_swscanf */
#endif /* !__swscanf_s_defined */
#ifndef __vfwscanf_s_defined
#define __vfwscanf_s_defined 1
#ifdef __CRT_HAVE_vfwscanf
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfwscanf_s,(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#else /* __CRT_HAVE_vfwscanf */
#undef __vfwscanf_s_defined
#endif /* !__CRT_HAVE_vfwscanf */
#endif /* !__vfwscanf_s_defined */
#ifndef __fwscanf_s_defined
#define __fwscanf_s_defined 1
#ifdef __CRT_HAVE_fwscanf
__LIBC __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwscanf_s)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("fwscanf");
#elif defined(__CRT_HAVE_vfwscanf)
#include <local/wchar/fwscanf.h>
#define fwscanf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf))
#else /* ... */
#undef __fwscanf_s_defined
#endif /* !... */
#endif /* !__fwscanf_s_defined */
#ifndef __vwscanf_s_defined
#define __vwscanf_s_defined 1
#ifdef __CRT_HAVE_vwscanf
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vwscanf_s,(wchar_t const *__restrict __format, __builtin_va_list __args),vwscanf,(__format,__args))
#elif defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)
#include <local/wchar/vwscanf.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL vwscanf_s)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf))(__format, __args); }
#else /* ... */
#undef __vwscanf_s_defined
#endif /* !... */
#endif /* !__vwscanf_s_defined */
#ifndef __wscanf_s_defined
#define __wscanf_s_defined 1
#ifdef __CRT_HAVE_wscanf
__LIBC __ATTR_LIBC_WSCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL wscanf_s)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("wscanf");
#elif defined(__CRT_HAVE_vwscanf) || (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS))
#include <local/wchar/wscanf.h>
#define wscanf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf))
#else /* ... */
#undef __wscanf_s_defined
#endif /* !... */
#endif /* !__wscanf_s_defined */
#endif /* __USE_DOS_SLIB */
#ifndef ___vscwprintf_defined
#define ___vscwprintf_defined 1
#ifdef __CRT_HAVE__vscwprintf
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vscwprintf,(wchar_t const *__format, __builtin_va_list __args),(__format,__args))
#else /* __CRT_HAVE__vscwprintf */
#include <local/wchar/_vscwprintf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vscwprintf)(wchar_t const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscwprintf))(__format, __args); })
#endif /* !__CRT_HAVE__vscwprintf */
#endif /* !___vscwprintf_defined */
#ifndef ___scwprintf_defined
#define ___scwprintf_defined 1
#ifdef __CRT_HAVE__scwprintf
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scwprintf)(wchar_t const *__format, ...) __CASMNAME_SAME("_scwprintf");
#else /* __CRT_HAVE__scwprintf */
#include <local/wchar/_scwprintf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_scwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scwprintf)(wchar_t const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _scwprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__scwprintf */
#endif /* !___scwprintf_defined */
#ifndef ___vscwprintf_p_defined
#define ___vscwprintf_p_defined 1
#ifdef __CRT_HAVE__vscwprintf_p
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vscwprintf_p,(wchar_t const *__format, __builtin_va_list __args),(__format,__args))
#else /* __CRT_HAVE__vscwprintf_p */
#include <local/wchar/_vscwprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscwprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vscwprintf_p)(wchar_t const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscwprintf_p))(__format, __args); })
#endif /* !__CRT_HAVE__vscwprintf_p */
#endif /* !___vscwprintf_p_defined */
#ifndef ___scwprintf_p_defined
#define ___scwprintf_p_defined 1
#ifdef __CRT_HAVE__scwprintf_p
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scwprintf_p)(wchar_t const *__format, ...) __CASMNAME_SAME("_scwprintf_p");
#else /* __CRT_HAVE__scwprintf_p */
#include <local/wchar/_scwprintf_p.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_scwprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scwprintf_p)(wchar_t const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf_p))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _scwprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf_p))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__scwprintf_p */
#endif /* !___scwprintf_p_defined */
#ifndef ___vscwprintf_l_defined
#define ___vscwprintf_l_defined 1
#ifdef __CRT_HAVE__vscwprintf_l
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vscwprintf_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#else /* __CRT_HAVE__vscwprintf_l */
#include <local/wchar/_vscwprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscwprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vscwprintf_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscwprintf_l))(__format, __locale, __args); })
#endif /* !__CRT_HAVE__vscwprintf_l */
#endif /* !___vscwprintf_l_defined */
#ifndef ___scwprintf_l_defined
#define ___scwprintf_l_defined 1
#ifdef __CRT_HAVE__scwprintf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scwprintf_l)(wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_scwprintf_l");
#else /* __CRT_HAVE__scwprintf_l */
#include <local/wchar/_scwprintf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_scwprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scwprintf_l)(wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _scwprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__scwprintf_l */
#endif /* !___scwprintf_l_defined */
#ifndef ___vscwprintf_p_l_defined
#define ___vscwprintf_p_l_defined 1
#ifdef __CRT_HAVE__vscwprintf_p_l
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vscwprintf_p_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#else /* __CRT_HAVE__vscwprintf_p_l */
#include <local/wchar/_vscwprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscwprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vscwprintf_p_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscwprintf_p_l))(__format, __locale, __args); })
#endif /* !__CRT_HAVE__vscwprintf_p_l */
#endif /* !___vscwprintf_p_l_defined */
#ifndef ___scwprintf_p_l_defined
#define ___scwprintf_p_l_defined 1
#ifdef __CRT_HAVE__scwprintf_p_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scwprintf_p_l)(wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_scwprintf_p_l");
#else /* __CRT_HAVE__scwprintf_p_l */
#include <local/wchar/_scwprintf_p_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_scwprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scwprintf_p_l)(wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf_p_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _scwprintf_p_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf_p_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__scwprintf_p_l */
#endif /* !___scwprintf_p_l_defined */
#ifndef ___vswprintf_c_defined
#define ___vswprintf_c_defined 1
#ifdef __CRT_HAVE_vswprintf
__CREDIRECT(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_vswprintf_c,(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, __builtin_va_list __args),vswprintf,(__buf,__buflen,__format,__args))
#else /* __CRT_HAVE_vswprintf */
#include <local/wchar/vswprintf.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL _vswprintf_c)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswprintf))(__buf, __buflen, __format, __args); }
#endif /* !__CRT_HAVE_vswprintf */
#endif /* !___vswprintf_c_defined */
#ifndef ___swprintf_c_defined
#define ___swprintf_c_defined 1
#ifdef __CRT_HAVE_swprintf
__LIBC __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_c)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, ...) __CASMNAME("swprintf");
#elif defined(__CRT_HAVE__swprintf)
__LIBC __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_c)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, ...) __CASMNAME("_swprintf");
#else /* ... */
#include <local/wchar/swprintf.h>
#define _swprintf_c (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swprintf))
#endif /* !... */
#endif /* !___swprintf_c_defined */
#ifndef ___vsnwprintf_s_defined
#define ___vsnwprintf_s_defined 1
#ifdef __CRT_HAVE__vsnwprintf_s
__CDECLARE(__ATTR_NONNULL((4)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsnwprintf_s,(wchar_t *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, wchar_t const *__format, __builtin_va_list __args),(__buf,__bufsize,__buflen,__format,__args))
#else /* __CRT_HAVE__vsnwprintf_s */
#include <local/wchar/_vsnwprintf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsnwprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsnwprintf_s)(wchar_t *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, wchar_t const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnwprintf_s))(__buf, __bufsize, __buflen, __format, __args); })
#endif /* !__CRT_HAVE__vsnwprintf_s */
#endif /* !___vsnwprintf_s_defined */
#ifndef ___snwprintf_s_defined
#define ___snwprintf_s_defined 1
#ifdef __CRT_HAVE__snwprintf_s
__LIBC __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwprintf_s)(wchar_t *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, wchar_t const *__format, ...) __CASMNAME_SAME("_snwprintf_s");
#else /* __CRT_HAVE__snwprintf_s */
#include <local/wchar/_snwprintf_s.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snwprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwprintf_s)(wchar_t *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, wchar_t const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwprintf_s))(__buf, __bufsize, __buflen, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snwprintf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwprintf_s))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snwprintf_s */
#endif /* !___snwprintf_s_defined */
#ifndef ___vfwprintf_p_defined
#define ___vfwprintf_p_defined 1
#ifdef __CRT_HAVE__vfwprintf_p
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,_vfwprintf_p,(__FILE *__stream, wchar_t const *__format, __builtin_va_list __args),(__stream,__format,__args))
#else /* __CRT_HAVE__vfwprintf_p */
#include <local/wchar/_vfwprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfwprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vfwprintf_p)(__FILE *__stream, wchar_t const *__format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfwprintf_p))(__stream, __format, __args); })
#endif /* !__CRT_HAVE__vfwprintf_p */
#endif /* !___vfwprintf_p_defined */
#ifndef ___fwprintf_p_defined
#define ___fwprintf_p_defined 1
#ifdef __CRT_HAVE__fwprintf_p
__LIBC __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_p)(__FILE *__stream, wchar_t const *__format, ...) __THROWS(...) __CASMNAME_SAME("_fwprintf_p");
#else /* __CRT_HAVE__fwprintf_p */
#include <local/wchar/_fwprintf_p.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_fwprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_p)(__FILE *__stream, wchar_t const *__format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_p))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _fwprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_p))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__fwprintf_p */
#endif /* !___fwprintf_p_defined */
#ifndef ___vwprintf_p_defined
#define ___vwprintf_p_defined 1
#ifdef __CRT_HAVE__vwprintf_p
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,_vwprintf_p,(wchar_t const *__format, __builtin_va_list __args),(__format,__args))
#elif !defined(__NO_STDSTREAMS)
#include <local/wchar/_vwprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vwprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vwprintf_p)(wchar_t const *__format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vwprintf_p))(__format, __args); })
#else /* ... */
#undef ___vwprintf_p_defined
#endif /* !... */
#endif /* !___vwprintf_p_defined */
#ifndef ___wprintf_p_defined
#define ___wprintf_p_defined 1
#ifdef __CRT_HAVE__wprintf_p
__LIBC __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_p)(wchar_t const *__format, ...) __THROWS(...) __CASMNAME_SAME("_wprintf_p");
#elif defined(__CRT_HAVE__vwprintf_p) || !defined(__NO_STDSTREAMS)
#include <local/wchar/_wprintf_p.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_wprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_p)(wchar_t const *__format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_p))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _wprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_p))
#endif /* !__cplusplus */
#else /* ... */
#undef ___wprintf_p_defined
#endif /* !... */
#endif /* !___wprintf_p_defined */
#ifndef ___vswprintf_p_defined
#define ___vswprintf_p_defined 1
#ifdef __CRT_HAVE__vswprintf_p
__CDECLARE(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vswprintf_p,(wchar_t *__buf, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __builtin_va_list __args),(__buf,__bufsize,__format,__args))
#else /* __CRT_HAVE__vswprintf_p */
#include <local/wchar/_vswprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vswprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vswprintf_p)(wchar_t *__buf, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vswprintf_p))(__buf, __bufsize, __format, __args); })
#endif /* !__CRT_HAVE__vswprintf_p */
#endif /* !___vswprintf_p_defined */
#ifndef ___swprintf_p_defined
#define ___swprintf_p_defined 1
#ifdef __CRT_HAVE__swprintf_p
__LIBC __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_p)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, ...) __CASMNAME_SAME("_swprintf_p");
#else /* __CRT_HAVE__swprintf_p */
#include <local/wchar/_swprintf_p.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_swprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_p)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_p))(__dst, __bufsize, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _swprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_p))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__swprintf_p */
#endif /* !___swprintf_p_defined */
#ifndef ___vwprintf_l_defined
#define ___vwprintf_l_defined 1
#ifdef __CRT_HAVE__vwprintf_l
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,_vwprintf_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__CRT_HAVE_vwprintf) || ((defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS))
#include <local/wchar/_vwprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vwprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vwprintf_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vwprintf_l))(__format, __locale, __args); })
#else /* ... */
#undef ___vwprintf_l_defined
#endif /* !... */
#endif /* !___vwprintf_l_defined */
#ifndef ___wprintf_l_defined
#define ___wprintf_l_defined 1
#ifdef __CRT_HAVE__wprintf_l
__LIBC __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_wprintf_l");
#elif defined(__CRT_HAVE__vwprintf_l) || defined(__CRT_HAVE_vwprintf) || ((defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS))
#include <local/wchar/_wprintf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_wprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _wprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_l))
#endif /* !__cplusplus */
#else /* ... */
#undef ___wprintf_l_defined
#endif /* !... */
#endif /* !___wprintf_l_defined */
#ifndef ___vwprintf_p_l_defined
#define ___vwprintf_p_l_defined 1
#ifdef __CRT_HAVE__vwprintf_p_l
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,_vwprintf_p_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__CRT_HAVE__vwprintf_p) || !defined(__NO_STDSTREAMS)
#include <local/wchar/_vwprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vwprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vwprintf_p_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vwprintf_p_l))(__format, __locale, __args); })
#else /* ... */
#undef ___vwprintf_p_l_defined
#endif /* !... */
#endif /* !___vwprintf_p_l_defined */
#ifndef ___wprintf_p_l_defined
#define ___wprintf_p_l_defined 1
#ifdef __CRT_HAVE__wprintf_p_l
__LIBC __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_p_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_wprintf_p_l");
#elif defined(__CRT_HAVE__vwprintf_p_l) || defined(__CRT_HAVE__vwprintf_p) || !defined(__NO_STDSTREAMS)
#include <local/wchar/_wprintf_p_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_wprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_p_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_p_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _wprintf_p_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_p_l))
#endif /* !__cplusplus */
#else /* ... */
#undef ___wprintf_p_l_defined
#endif /* !... */
#endif /* !___wprintf_p_l_defined */
#ifndef ___vwprintf_s_l_defined
#define ___vwprintf_s_l_defined 1
#ifdef __CRT_HAVE__vwprintf_s_l
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,_vwprintf_s_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__CRT_HAVE_vwprintf) || ((defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS))
#include <local/wchar/_vwprintf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vwprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vwprintf_s_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vwprintf_s_l))(__format, __locale, __args); })
#else /* ... */
#undef ___vwprintf_s_l_defined
#endif /* !... */
#endif /* !___vwprintf_s_l_defined */
#ifndef ___wprintf_s_l_defined
#define ___wprintf_s_l_defined 1
#ifdef __CRT_HAVE__wprintf_s_l
__LIBC __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_s_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_wprintf_s_l");
#elif defined(__CRT_HAVE__vwprintf_s_l) || defined(__CRT_HAVE_vwprintf) || ((defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS))
#include <local/wchar/_wprintf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_wprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_s_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_s_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _wprintf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_s_l))
#endif /* !__cplusplus */
#else /* ... */
#undef ___wprintf_s_l_defined
#endif /* !... */
#endif /* !___wprintf_s_l_defined */
#ifndef ___vfwprintf_l_defined
#define ___vfwprintf_l_defined 1
#ifdef __CRT_HAVE__vfwprintf_l
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,_vfwprintf_l,(__FILE *__stream, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#include <local/wchar/_vfwprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfwprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vfwprintf_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfwprintf_l))(__stream, __format, __locale, __args); })
#else /* ... */
#undef ___vfwprintf_l_defined
#endif /* !... */
#endif /* !___vfwprintf_l_defined */
#ifndef ___fwprintf_l_defined
#define ___fwprintf_l_defined 1
#ifdef __CRT_HAVE__fwprintf_l
__LIBC __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_fwprintf_l");
#elif defined(__CRT_HAVE__vfwprintf_l) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#include <local/wchar/_fwprintf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_fwprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_l))(__stream, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _fwprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_l))
#endif /* !__cplusplus */
#else /* ... */
#undef ___fwprintf_l_defined
#endif /* !... */
#endif /* !___fwprintf_l_defined */
#ifndef ___vfwprintf_p_l_defined
#define ___vfwprintf_p_l_defined 1
#ifdef __CRT_HAVE__vfwprintf_p_l
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,_vfwprintf_p_l,(__FILE *__stream, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__stream,__format,__locale,__args))
#else /* __CRT_HAVE__vfwprintf_p_l */
#include <local/wchar/_vfwprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfwprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vfwprintf_p_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfwprintf_p_l))(__stream, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vfwprintf_p_l */
#endif /* !___vfwprintf_p_l_defined */
#ifndef ___fwprintf_p_l_defined
#define ___fwprintf_p_l_defined 1
#ifdef __CRT_HAVE__fwprintf_p_l
__LIBC __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_p_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_fwprintf_p_l");
#else /* __CRT_HAVE__fwprintf_p_l */
#include <local/wchar/_fwprintf_p_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_fwprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_p_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_p_l))(__stream, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _fwprintf_p_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_p_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__fwprintf_p_l */
#endif /* !___fwprintf_p_l_defined */
#ifndef ___vfwprintf_s_l_defined
#define ___vfwprintf_s_l_defined 1
#ifdef __CRT_HAVE__vfwprintf_s_l
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,_vfwprintf_s_l,(__FILE *__stream, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#include <local/wchar/_vfwprintf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfwprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vfwprintf_s_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfwprintf_s_l))(__stream, __format, __locale, __args); })
#else /* ... */
#undef ___vfwprintf_s_l_defined
#endif /* !... */
#endif /* !___vfwprintf_s_l_defined */
#ifndef ___fwprintf_s_l_defined
#define ___fwprintf_s_l_defined 1
#ifdef __CRT_HAVE__fwprintf_s_l
__LIBC __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_s_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_fwprintf_s_l");
#elif defined(__CRT_HAVE__vfwprintf_s_l) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#include <local/wchar/_fwprintf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_fwprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_s_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_s_l))(__stream, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _fwprintf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_s_l))
#endif /* !__cplusplus */
#else /* ... */
#undef ___fwprintf_s_l_defined
#endif /* !... */
#endif /* !___fwprintf_s_l_defined */
#ifndef ___vswprintf_c_l_defined
#define ___vswprintf_c_l_defined 1
#ifdef __CRT_HAVE__vswprintf_c_l
__CDECLARE(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vswprintf_c_l,(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__dst,__bufsize,__format,__locale,__args))
#else /* __CRT_HAVE__vswprintf_c_l */
#include <local/wchar/_vswprintf_c_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vswprintf_c_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vswprintf_c_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vswprintf_c_l))(__dst, __bufsize, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vswprintf_c_l */
#endif /* !___vswprintf_c_l_defined */
#ifndef ___swprintf_c_l_defined
#define ___swprintf_c_l_defined 1
#ifdef __CRT_HAVE__swprintf_c_l
__LIBC __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_c_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_swprintf_c_l");
#else /* __CRT_HAVE__swprintf_c_l */
#include <local/wchar/_swprintf_c_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_swprintf_c_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_c_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_c_l))(__dst, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _swprintf_c_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_c_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__swprintf_c_l */
#endif /* !___swprintf_c_l_defined */
#ifndef ___vswprintf_p_l_defined
#define ___vswprintf_p_l_defined 1
#ifdef __CRT_HAVE__vswprintf_p_l
__CDECLARE(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vswprintf_p_l,(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__dst,__bufsize,__format,__locale,__args))
#else /* __CRT_HAVE__vswprintf_p_l */
#include <local/wchar/_vswprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vswprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vswprintf_p_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vswprintf_p_l))(__dst, __bufsize, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vswprintf_p_l */
#endif /* !___vswprintf_p_l_defined */
#ifndef ___swprintf_p_l_defined
#define ___swprintf_p_l_defined 1
#ifdef __CRT_HAVE__swprintf_p_l
__LIBC __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_p_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_swprintf_p_l");
#else /* __CRT_HAVE__swprintf_p_l */
#include <local/wchar/_swprintf_p_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_swprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_p_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_p_l))(__dst, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _swprintf_p_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_p_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__swprintf_p_l */
#endif /* !___swprintf_p_l_defined */
#ifndef ___vswprintf_s_l_defined
#define ___vswprintf_s_l_defined 1
#ifdef __CRT_HAVE__vswprintf_s_l
__CDECLARE(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vswprintf_s_l,(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__dst,__wchar_count,__format,__locale,__args))
#else /* __CRT_HAVE__vswprintf_s_l */
#include <local/wchar/_vswprintf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vswprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vswprintf_s_l)(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vswprintf_s_l))(__dst, __wchar_count, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vswprintf_s_l */
#endif /* !___vswprintf_s_l_defined */
#ifndef ___swprintf_s_l_defined
#define ___swprintf_s_l_defined 1
#ifdef __CRT_HAVE__swprintf_s_l
__LIBC __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_s_l)(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_swprintf_s_l");
#else /* __CRT_HAVE__swprintf_s_l */
#include <local/wchar/_swprintf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_swprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_s_l)(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_s_l))(__dst, __wchar_count, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _swprintf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_s_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__swprintf_s_l */
#endif /* !___swprintf_s_l_defined */
#ifndef ___vsnwprintf_l_defined
#define ___vsnwprintf_l_defined 1
#ifdef __CRT_HAVE__vsnwprintf_l
__CDECLARE(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsnwprintf_l,(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__dst,__bufsize,__format,__locale,__args))
#else /* __CRT_HAVE__vsnwprintf_l */
#include <local/wchar/_vsnwprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsnwprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsnwprintf_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnwprintf_l))(__dst, __bufsize, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vsnwprintf_l */
#endif /* !___vsnwprintf_l_defined */
#ifndef ___snwprintf_l_defined
#define ___snwprintf_l_defined 1
#ifdef __CRT_HAVE__snwprintf_l
__LIBC __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwprintf_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_snwprintf_l");
#else /* __CRT_HAVE__snwprintf_l */
#include <local/wchar/_snwprintf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snwprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwprintf_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwprintf_l))(__dst, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snwprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwprintf_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snwprintf_l */
#endif /* !___snwprintf_l_defined */
#ifndef ___vsnwprintf_s_l_defined
#define ___vsnwprintf_s_l_defined 1
#ifdef __CRT_HAVE__vsnwprintf_s_l
__CDECLARE(__ATTR_NONNULL((1, 4)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsnwprintf_s_l,(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__dst,__wchar_count,__bufsize,__format,__locale,__args))
#else /* __CRT_HAVE__vsnwprintf_s_l */
#include <local/wchar/_vsnwprintf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsnwprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsnwprintf_s_l)(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnwprintf_s_l))(__dst, __wchar_count, __bufsize, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vsnwprintf_s_l */
#endif /* !___vsnwprintf_s_l_defined */
#ifndef ___snwprintf_s_l_defined
#define ___snwprintf_s_l_defined 1
#ifdef __CRT_HAVE__snwprintf_s_l
__LIBC __ATTR_NONNULL((1, 4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwprintf_s_l)(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_snwprintf_s_l");
#else /* __CRT_HAVE__snwprintf_s_l */
#include <local/wchar/_snwprintf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snwprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwprintf_s_l)(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwprintf_s_l))(__dst, __wchar_count, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snwprintf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwprintf_s_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snwprintf_s_l */
#endif /* !___snwprintf_s_l_defined */
#ifndef ___fwscanf_l_defined
#define ___fwscanf_l_defined 1
#ifdef __CRT_HAVE__fwscanf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwscanf_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_fwscanf_l");
#elif defined(__CRT_HAVE__vfwscanf_l) || defined(__CRT_HAVE_vfwscanf)
#include <local/wchar/_fwscanf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_fwscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwscanf_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwscanf_l))(__stream, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _fwscanf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwscanf_l))
#endif /* !__cplusplus */
#else /* ... */
#undef ___fwscanf_l_defined
#endif /* !... */
#endif /* !___fwscanf_l_defined */
#ifndef ___fwscanf_s_l_defined
#define ___fwscanf_s_l_defined 1
#ifdef __CRT_HAVE__fwscanf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwscanf_s_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME("_fwscanf_l");
#elif defined(__CRT_HAVE__vfwscanf_l) || defined(__CRT_HAVE_vfwscanf)
#include <local/wchar/_fwscanf_l.h>
#define _fwscanf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwscanf_l))
#else /* ... */
#undef ___fwscanf_s_l_defined
#endif /* !... */
#endif /* !___fwscanf_s_l_defined */
#ifndef ___swscanf_l_defined
#define ___swscanf_l_defined 1
#ifdef __CRT_HAVE__swscanf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swscanf_l)(wchar_t const *__src, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_swscanf_l");
#else /* __CRT_HAVE__swscanf_l */
#include <local/wchar/_swscanf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_swscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swscanf_l)(wchar_t const *__src, wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swscanf_l))(__src, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _swscanf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swscanf_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__swscanf_l */
#endif /* !___swscanf_l_defined */
#ifndef ___swscanf_s_l_defined
#define ___swscanf_s_l_defined 1
#ifdef __CRT_HAVE__swscanf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swscanf_s_l)(wchar_t const *__src, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME("_swscanf_l");
#else /* __CRT_HAVE__swscanf_l */
#include <local/wchar/_swscanf_l.h>
#define _swscanf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swscanf_l))
#endif /* !__CRT_HAVE__swscanf_l */
#endif /* !___swscanf_s_l_defined */
#ifndef ___snwscanf_defined
#define ___snwscanf_defined 1
#ifdef __CRT_HAVE__snwscanf
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwscanf)(wchar_t const *__src, __SIZE_TYPE__ __bufsize, wchar_t const *__format, ...) __CASMNAME_SAME("_snwscanf");
#else /* __CRT_HAVE__snwscanf */
#include <local/wchar/_snwscanf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snwscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwscanf)(wchar_t const *__src, __SIZE_TYPE__ __bufsize, wchar_t const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwscanf))(__src, __bufsize, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snwscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwscanf))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snwscanf */
#endif /* !___snwscanf_defined */
#ifndef ___snwscanf_l_defined
#define ___snwscanf_l_defined 1
#ifdef __CRT_HAVE__snwscanf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwscanf_l)(wchar_t const *__src, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_snwscanf_l");
#else /* __CRT_HAVE__snwscanf_l */
#include <local/wchar/_snwscanf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snwscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwscanf_l)(wchar_t const *__src, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwscanf_l))(__src, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snwscanf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwscanf_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snwscanf_l */
#endif /* !___snwscanf_l_defined */
#ifndef ___snwscanf_s_defined
#define ___snwscanf_s_defined 1
#ifdef __CRT_HAVE__snwscanf
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwscanf_s)(wchar_t const *__src, __SIZE_TYPE__ __bufsize, wchar_t const *__format, ...) __CASMNAME("_snwscanf");
#else /* __CRT_HAVE__snwscanf */
#include <local/wchar/_snwscanf.h>
#define _snwscanf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwscanf))
#endif /* !__CRT_HAVE__snwscanf */
#endif /* !___snwscanf_s_defined */
#ifndef ___snwscanf_s_l_defined
#define ___snwscanf_s_l_defined 1
#ifdef __CRT_HAVE__snwscanf_s_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwscanf_s_l)(wchar_t const *__src, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_snwscanf_s_l");
#else /* __CRT_HAVE__snwscanf_s_l */
#include <local/wchar/_snwscanf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snwscanf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwscanf_s_l)(wchar_t const *__src, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwscanf_s_l))(__src, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snwscanf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwscanf_s_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snwscanf_s_l */
#endif /* !___snwscanf_s_l_defined */
#ifndef ___wscanf_l_defined
#define ___wscanf_l_defined 1
#ifdef __CRT_HAVE__wscanf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wscanf_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_wscanf_l");
#elif defined(__CRT_HAVE__vwscanf_l) || defined(__CRT_HAVE_vwscanf) || (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS))
#include <local/wchar/_wscanf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_wscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wscanf_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wscanf_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _wscanf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wscanf_l))
#endif /* !__cplusplus */
#else /* ... */
#undef ___wscanf_l_defined
#endif /* !... */
#endif /* !___wscanf_l_defined */
#ifndef ___wscanf_s_l_defined
#define ___wscanf_s_l_defined 1
#ifdef __CRT_HAVE__wscanf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wscanf_s_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME("_wscanf_l");
#elif defined(__CRT_HAVE__vwscanf_l) || defined(__CRT_HAVE_vwscanf) || (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS))
#include <local/wchar/_wscanf_l.h>
#define _wscanf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wscanf_l))
#else /* ... */
#undef ___wscanf_s_l_defined
#endif /* !... */
#endif /* !___wscanf_s_l_defined */
#ifndef ___wfsopen_defined
#define ___wfsopen_defined 1
#ifdef __CRT_HAVE__wfsopen
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wfsopen,(wchar_t const *__filename, wchar_t const *__mode, __STDC_INT_AS_UINT_T __sh_flag),(__filename,__mode,__sh_flag))
#else /* __CRT_HAVE__wfsopen */
#undef ___wfsopen_defined
#endif /* !__CRT_HAVE__wfsopen */
#endif /* !___wfsopen_defined */
#ifndef ___wfdopen_defined
#define ___wfdopen_defined 1
#ifdef __CRT_HAVE__wfdopen
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),__FILE *,__NOTHROW_NCX,_wfdopen,(__fd_t __fd, wchar_t const *__mode),(__fd,__mode))
#else /* __CRT_HAVE__wfdopen */
#undef ___wfdopen_defined
#endif /* !__CRT_HAVE__wfdopen */
#endif /* !___wfdopen_defined */
#ifndef ___wfopen_s_defined
#define ___wfopen_s_defined 1
#ifdef __CRT_HAVE__wfopen_s
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_NCX,_wfopen_s,(__FILE **__pstream, wchar_t const *__filename, wchar_t const *__mode),(__pstream,__filename,__mode))
#else /* __CRT_HAVE__wfopen_s */
#undef ___wfopen_s_defined
#endif /* !__CRT_HAVE__wfopen_s */
#endif /* !___wfopen_s_defined */
#ifndef ___wfreopen_s_defined
#define ___wfreopen_s_defined 1
#ifdef __CRT_HAVE__wfreopen_s
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_NCX,_wfreopen_s,(__FILE **__pstream, wchar_t const *__filename, wchar_t const *__mode, __FILE *__stream),(__pstream,__filename,__mode,__stream))
#else /* __CRT_HAVE__wfreopen_s */
#undef ___wfreopen_s_defined
#endif /* !__CRT_HAVE__wfreopen_s */
#endif /* !___wfreopen_s_defined */
#ifndef ___wfopen_defined
#define ___wfopen_defined 1
#ifdef __CRT_HAVE_wfopen
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wfopen,(wchar_t const *__filename, wchar_t const *__mode),wfopen,(__filename,__mode))
#elif defined(__CRT_HAVE__wfopen)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wfopen,(wchar_t const *__filename, wchar_t const *__mode),(__filename,__mode))
#else /* ... */
#undef ___wfopen_defined
#endif /* !... */
#endif /* !___wfopen_defined */
#ifndef ___wfreopen_defined
#define ___wfreopen_defined 1
#ifdef __CRT_HAVE_wfreopen
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wfreopen,(wchar_t const *__filename, wchar_t const *__mode, __FILE *__stream),wfreopen,(__filename,__mode,__stream))
#elif defined(__CRT_HAVE__wfreopen)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wfreopen,(wchar_t const *__filename, wchar_t const *__mode, __FILE *__stream),(__filename,__mode,__stream))
#else /* ... */
#undef ___wfreopen_defined
#endif /* !... */
#endif /* !___wfreopen_defined */
#ifndef ___fgetwchar_defined
#define ___fgetwchar_defined 1
#ifdef __CRT_HAVE_getwchar
__CREDIRECT(,wint_t,__THROWING,_fgetwchar,(void),getwchar,())
#elif defined(__CRT_HAVE__fgetwchar)
__CDECLARE(,wint_t,__THROWING,_fgetwchar,(void),())
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc))
#include <local/wchar/getwchar.h>
__FORCELOCAL __ATTR_ARTIFICIAL wint_t (__LIBCCALL _fgetwchar)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwchar))(); }
#else /* ... */
#undef ___fgetwchar_defined
#endif /* !... */
#endif /* !___fgetwchar_defined */
#ifndef ___fputwchar_defined
#define ___fputwchar_defined 1
#ifdef __CRT_HAVE_putwchar
__CREDIRECT(,wint_t,__THROWING,_fputwchar,(wchar_t __wc),putwchar,(__wc))
#elif defined(__CRT_HAVE__fputwchar)
__CDECLARE(,wint_t,__THROWING,_fputwchar,(wchar_t __wc),(__wc))
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc))
#include <local/wchar/putwchar.h>
__FORCELOCAL __ATTR_ARTIFICIAL wint_t (__LIBCCALL _fputwchar)(wchar_t __wc) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putwchar))(__wc); }
#else /* ... */
#undef ___fputwchar_defined
#endif /* !... */
#endif /* !___fputwchar_defined */
#ifndef ___getws_s_defined
#define ___getws_s_defined 1
#ifdef __CRT_HAVE__getws_s
__CDECLARE(,wchar_t *,__NOTHROW_NCX,_getws_s,(wchar_t *__buf, __SIZE_TYPE__ __buflen),(__buf,__buflen))
#elif (defined(__CRT_HAVE_fgetws) || defined(__CRT_HAVE_fgetws_unlocked) || defined(__CRT_HAVE__fgetws_nolock) || ((defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)))) && !defined(__NO_STDSTREAMS)
#include <local/wchar/_getws_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_getws_s, __FORCELOCAL __ATTR_ARTIFICIAL wchar_t *__NOTHROW_NCX(__LIBCCALL _getws_s)(wchar_t *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_getws_s))(__buf, __buflen); })
#else /* ... */
#undef ___getws_s_defined
#endif /* !... */
#endif /* !___getws_s_defined */
#ifndef ___putws_defined
#define ___putws_defined 1
#ifdef __CRT_HAVE__putws
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_putws,(wchar_t const *__string),(__string))
#elif (defined(__CRT_HAVE_fputws) || defined(__CRT_HAVE_fputws_unlocked) || defined(__CRT_HAVE__fputws_nolock) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS)
#include <local/wchar/_putws.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_putws, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL _putws)(wchar_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_putws))(__string); })
#else /* ... */
#undef ___putws_defined
#endif /* !... */
#endif /* !___putws_defined */
#ifndef ___wtempnam_defined
#define ___wtempnam_defined 1
#ifdef __CRT_HAVE__wtempnam
__CDECLARE(__ATTR_WUNUSED,wchar_t *,__NOTHROW_NCX,_wtempnam,(wchar_t const *__directory, wchar_t const *__file_prefix),(__directory,__file_prefix))
#else /* __CRT_HAVE__wtempnam */
#undef ___wtempnam_defined
#endif /* !__CRT_HAVE__wtempnam */
#endif /* !___wtempnam_defined */
#ifndef _CRT_WPERROR_DEFINED
#define _CRT_WPERROR_DEFINED 1
#ifdef __CRT_HAVE__wperror
__CDECLARE_VOID(__ATTR_COLD,__THROWING,_wperror,(__WCHAR_TYPE__ const *__restrict __message),(__message))
#else /* __CRT_HAVE__wperror */
#include <parts/errno.h>
#if !defined(__NO_STDSTREAMS) && defined(__libc_geterrno) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite))
#include <local/stdio/_wperror.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wperror, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_COLD void (__LIBCCALL _wperror)(__WCHAR_TYPE__ const *__restrict __message) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wperror))(__message); })
#else /* !__NO_STDSTREAMS && __libc_geterrno && (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite) */
#undef _CRT_WPERROR_DEFINED
#endif /* __NO_STDSTREAMS || !__libc_geterrno || (!__CRT_HAVE_fprintf && !__CRT_HAVE__IO_fprintf && !__CRT_HAVE_fprintf_s && !__CRT_HAVE_fprintf_unlocked && !__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_fputc && !__CRT_HAVE_putc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE_putc_unlocked && (!__CRT_DOS || !__CRT_HAVE__flsbuf) && !__CRT_HAVE_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock && !__CRT_HAVE__IO_fwrite) */
#endif /* !__CRT_HAVE__wperror */
#define _CRT_WPERROR_DEFINED 1
#ifdef __CRT_HAVE__wperror
__CDECLARE_VOID(__ATTR_COLD,__THROWING,_wperror,(__WCHAR_TYPE__ const *__restrict __message),(__message))
#else /* __CRT_HAVE__wperror */
#include <parts/errno.h>
#if !defined(__NO_STDSTREAMS) && defined(__libc_geterrno) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite))
#include <local/stdio/_wperror.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wperror, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_COLD void (__LIBCCALL _wperror)(__WCHAR_TYPE__ const *__restrict __message) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wperror))(__message); })
#else /* !__NO_STDSTREAMS && __libc_geterrno && (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite) */
#undef _CRT_WPERROR_DEFINED
#endif /* __NO_STDSTREAMS || !__libc_geterrno || (!__CRT_HAVE_fprintf && !__CRT_HAVE__IO_fprintf && !__CRT_HAVE_fprintf_s && !__CRT_HAVE_fprintf_unlocked && !__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_fputc && !__CRT_HAVE_putc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE_putc_unlocked && (!__CRT_DOS || !__CRT_HAVE__flsbuf) && !__CRT_HAVE_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock && !__CRT_HAVE__IO_fwrite) */
#endif /* !__CRT_HAVE__wperror */
#endif /* !_CRT_WPERROR_DEFINED */
#ifndef ___wpopen_defined
#define ___wpopen_defined 1
#ifdef __CRT_HAVE_wpopen
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wpopen,(wchar_t const *__command, wchar_t const *__mode),wpopen,(__command,__mode))
#elif defined(__CRT_HAVE__wpopen)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wpopen,(wchar_t const *__command, wchar_t const *__mode),(__command,__mode))
#else /* ... */
#undef ___wpopen_defined
#endif /* !... */
#endif /* !___wpopen_defined */
#ifndef ___wremove_defined
#define ___wremove_defined 1
#ifdef __CRT_HAVE_wremove
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wremove,(wchar_t const *__filename),wremove,(__filename))
#elif defined(__CRT_HAVE__wremove)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wremove,(wchar_t const *__filename),(__filename))
#else /* ... */
#undef ___wremove_defined
#endif /* !... */
#endif /* !___wremove_defined */
#ifndef ___wtmpnam_s_defined
#define ___wtmpnam_s_defined 1
#ifdef __CRT_HAVE__wtmpnam_s
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,_wtmpnam_s,(wchar_t *__dst, __SIZE_TYPE__ __wchar_count),(__dst,__wchar_count))
#else /* __CRT_HAVE__wtmpnam_s */
#undef ___wtmpnam_s_defined
#endif /* !__CRT_HAVE__wtmpnam_s */
#endif /* !___wtmpnam_s_defined */
#ifndef ___fgetwc_nolock_defined
#define ___fgetwc_nolock_defined 1
#ifdef __CRT_HAVE_fgetwc_unlocked
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,_fgetwc_nolock,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock)
__CDECLARE(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,_fgetwc_nolock,(__FILE *__restrict __stream),(__stream))
#else /* ... */
#undef ___fgetwc_nolock_defined
#endif /* !... */
#endif /* !___fgetwc_nolock_defined */
#ifndef ___fputwc_nolock_defined
#define ___fputwc_nolock_defined 1
#ifdef __CRT_HAVE_fputwc_unlocked
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,_fputwc_nolock,(wchar_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock)
__CDECLARE(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,_fputwc_nolock,(wchar_t __wc, __FILE *__restrict __stream),(__wc,__stream))
#else /* ... */
#undef ___fputwc_nolock_defined
#endif /* !... */
#endif /* !___fputwc_nolock_defined */
#ifndef ___ungetwc_nolock_defined
#define ___ungetwc_nolock_defined 1
#ifdef __CRT_HAVE_ungetwc_unlocked
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,_ungetwc_nolock,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),ungetwc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetwc_nolock)
__CDECLARE(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,_ungetwc_nolock,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE_ungetwc)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,_ungetwc_nolock,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#else /* ... */
#undef ___ungetwc_nolock_defined
#endif /* !... */
#endif /* !___ungetwc_nolock_defined */
#ifndef ___getwc_nolock_defined
#define ___getwc_nolock_defined 1
#ifdef __CRT_HAVE_fgetwc_unlocked
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,_getwc_nolock,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,_getwc_nolock,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#else /* ... */
#undef ___getwc_nolock_defined
#endif /* !... */
#endif /* !___getwc_nolock_defined */
#ifndef ___putwc_nolock_defined
#define ___putwc_nolock_defined 1
#ifdef __CRT_HAVE_fputwc_unlocked
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,_putwc_nolock,(wchar_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,_putwc_nolock,(wchar_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#else /* ... */
#undef ___putwc_nolock_defined
#endif /* !... */
#endif /* !___putwc_nolock_defined */
#endif /* !_WSTDIO_DEFINED */
#endif /* __CC__ */
#endif /* __USE_DOS */


#if ((defined(__USE_XOPEN) && !defined(__USE_XOPEN2K) && !defined(__USE_GNU)) || defined(__USE_SOLARIS))
#include <getopt.h>
#endif /* (__USE_XOPEN && !__USE_XOPEN2K && !__USE_GNU) || __USE_SOLARIS */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_STDIO_H)
#include <parts/uchar/stdio.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_STDIO_H */
#endif /* __USE_UTF */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CSTDIO 1
#undef _STDIO_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CSTDIO */
#endif /* !_STDIO_H */
