/* HASH CRC-32:0x4fa4a7d5 */
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
#ifndef __local_fisatty_defined
#define __local_fisatty_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_isatty) || defined(__CRT_HAVE__isatty)) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked))
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fileno from stdio */
#ifndef __local___localdep_fileno_defined
#define __local___localdep_fileno_defined 1
#if defined(__CRT_HAVE_fileno_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Return the underlying file descriptor number used by `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#elif defined(__CRT_HAVE_fileno)
/* Return the underlying file descriptor number used by `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),fileno,(__stream))
#elif defined(__CRT_HAVE__fileno)
/* Return the underlying file descriptor number used by `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),_fileno,(__stream))
#elif defined(__CRT_HAVE_fileno_unlocked)
/* Return the underlying file descriptor number used by `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#else /* ... */
#undef __local___localdep_fileno_defined
#endif /* !... */
#endif /* !__local___localdep_fileno_defined */
/* Dependency: isatty from unistd */
#ifndef __local___localdep_isatty_defined
#define __local___localdep_isatty_defined 1
#ifdef __CRT_HAVE_isatty
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> isatty(2)
 * @return: 1: Is a tty
 * @return: 0: Not a tty
 * Check if the given file handle `FD' refers to a TTY */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isatty,(__fd_t __fd),isatty,(__fd))
#elif defined(__CRT_HAVE__isatty)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> isatty(2)
 * @return: 1: Is a tty
 * @return: 0: Not a tty
 * Check if the given file handle `FD' refers to a TTY */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isatty,(__fd_t __fd),_isatty,(__fd))
#else /* ... */
#undef __local___localdep_isatty_defined
#endif /* !... */
#endif /* !__local___localdep_isatty_defined */
__LOCAL_LIBC(fisatty) __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fisatty))(__FILE *__restrict __stream) {
	return __localdep_isatty(__localdep_fileno(__stream));
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fisatty_defined
#define __local___localdep_fisatty_defined 1
#define __localdep_fisatty __LIBC_LOCAL_NAME(fisatty)
#endif /* !__local___localdep_fisatty_defined */
#else /* (__CRT_HAVE_isatty || __CRT_HAVE__isatty) && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) */
#undef __local_fisatty_defined
#endif /* (!__CRT_HAVE_isatty && !__CRT_HAVE__isatty) || (!__CRT_HAVE_fileno && !__CRT_HAVE__fileno && !__CRT_HAVE_fileno_unlocked) */
#endif /* !__local_fisatty_defined */
