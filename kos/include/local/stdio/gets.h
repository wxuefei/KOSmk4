/* HASH CRC-32:0x2ffe9208 */
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
#ifndef __local_gets_defined
#define __local_gets_defined 1
#include <__crt.h>
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgets) || defined(__CRT_HAVE_fgets_unlocked) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))))
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fgets from stdio */
#ifndef __local___localdep_fgets_defined
#define __local___localdep_fgets_defined 1
#if defined(__CRT_HAVE_fgets_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Read up to `BUFSIZE - 1' bytes of data from `STREAM', storing them into `BUF' stopped when
 * the buffer is full or a line-feed was read (in this case, the line-feed is also written to `BUF')
 * Afterwards, append a trailing NUL-character and re-return `BUF', or return `NULL' if an error occurred. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char *,__THROWING,__localdep_fgets,(char *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgets_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgets)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Read up to `BUFSIZE - 1' bytes of data from `STREAM', storing them into `BUF' stopped when
 * the buffer is full or a line-feed was read (in this case, the line-feed is also written to `BUF')
 * Afterwards, append a trailing NUL-character and re-return `BUF', or return `NULL' if an error occurred. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char *,__THROWING,__localdep_fgets,(char *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgets,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgets_unlocked)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Read up to `BUFSIZE - 1' bytes of data from `STREAM', storing them into `BUF' stopped when
 * the buffer is full or a line-feed was read (in this case, the line-feed is also written to `BUF')
 * Afterwards, append a trailing NUL-character and re-return `BUF', or return `NULL' if an error occurred. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char *,__THROWING,__localdep_fgets,(char *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgets_unlocked,(__buf,__bufsize,__stream))
#elif (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))
__NAMESPACE_LOCAL_END
#include <local/stdio/fgets.h>
__NAMESPACE_LOCAL_BEGIN
/* Read up to `BUFSIZE - 1' bytes of data from `STREAM', storing them into `BUF' stopped when
 * the buffer is full or a line-feed was read (in this case, the line-feed is also written to `BUF')
 * Afterwards, append a trailing NUL-character and re-return `BUF', or return `NULL' if an error occurred. */
#define __localdep_fgets __LIBC_LOCAL_NAME(fgets)
#else /* ... */
#undef __local___localdep_fgets_defined
#endif /* !... */
#endif /* !__local___localdep_fgets_defined */
__NAMESPACE_LOCAL_END
#include <local/stdstreams.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(gets) __ATTR_WUNUSED __ATTR_DEPRECATED("No buffer size checks (use `fgets\' instead)") __ATTR_NONNULL((1)) char *
(__LIBCCALL __LIBC_LOCAL_NAME(gets))(char *__restrict __buf) __THROWS(...) {
	return __localdep_fgets(__buf, __INT_MAX__, __LOCAL_stdin);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_gets_defined
#define __local___localdep_gets_defined 1
#define __localdep_gets __LIBC_LOCAL_NAME(gets)
#endif /* !__local___localdep_gets_defined */
#else /* !__NO_STDSTREAMS && (__CRT_HAVE_fgets || __CRT_HAVE_fgets_unlocked || ((__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked))) */
#undef __local_gets_defined
#endif /* __NO_STDSTREAMS || (!__CRT_HAVE_fgets && !__CRT_HAVE_fgets_unlocked && ((!__CRT_HAVE_fgetc && !__CRT_HAVE_getc && !__CRT_HAVE__IO_getc && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && (!__CRT_DOS || !__CRT_HAVE__filbuf) && !__CRT_HAVE_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock && !__CRT_HAVE__IO_fread) || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock) || (!__CRT_HAVE_ferror && !__CRT_HAVE__IO_ferror && !__CRT_HAVE_ferror_unlocked))) */
#endif /* !__local_gets_defined */
