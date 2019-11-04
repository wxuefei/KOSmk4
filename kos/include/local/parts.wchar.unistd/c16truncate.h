/* HASH CRC-32:0x8fb70d7b */
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
#ifndef __local_c16truncate_defined
#if defined(__CRT_HAVE_wtruncate64) || defined(__CRT_HAVE_wtruncate) || ((defined(__CRT_HAVE_open) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE__open)) && (defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64)))
#define __local_c16truncate_defined 1
#include <bits/types.h>
/* Dependency: "wtruncate64" from "parts.wchar.unistd" */
#ifndef ____localdep_c16truncate64_defined
#define ____localdep_c16truncate64_defined 1
#if defined(__CRT_HAVE_wtruncate64) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_c16truncate64,(__CHAR16_TYPE__ const *__file, __PIO_OFFSET64 __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate64)
/* >> c16truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_c16truncate64,(__CHAR16_TYPE__ const *__file, __PIO_OFFSET64 __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate) || ((defined(__CRT_HAVE_open) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE__open)) && (defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64)))
#if __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.unistd/wtruncate64.h>
/* >> c16truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
#define __localdep_c16truncate64(file, length) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtruncate64))((__WCHAR_TYPE__ const *)(file), length)
#else /* LIBC: c16truncate64 */
#include <local/parts.wchar.unistd/c16truncate64.h>
/* >> c16truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
#define __localdep_c16truncate64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16truncate64))
#endif /* LIBC: c16truncate64 */
#else /* CUSTOM: wtruncate64 */
#undef ____localdep_c16truncate64_defined
#endif /* c16truncate64... */
#endif /* !____localdep_c16truncate64_defined */

/* Dependency: "wtruncate32" from "parts.wchar.unistd" */
#ifndef ____localdep_c16truncate32_defined
#define ____localdep_c16truncate32_defined 1
#if defined(__CRT_HAVE_wtruncate32) && (__SIZEOF_WCHAR_T__ == 2)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_c16truncate32,(__CHAR16_TYPE__ const *__file, __pos32_t __length),wtruncate32,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate32)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_DOS(,int,__NOTHROW_NCX,__localdep_c16truncate32,(__CHAR16_TYPE__ const *__file, __pos32_t __length),wtruncate32,(__file,__length))
#else /* LIBC: wtruncate32 */
#undef ____localdep_c16truncate32_defined
#endif /* c16truncate32... */
#endif /* !____localdep_c16truncate32_defined */

/* Dependency: "open" from "fcntl" */
#ifndef ____localdep_open_defined
#define ____localdep_open_defined 1
#if defined(__CRT_HAVE_open64) && (defined(__USE_FILE_OFFSET64))
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) && (!defined(__USE_FILE_OFFSET64))
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat) || defined(__CRT_HAVE_openat64)))
#include <local/fcntl/open.h>
#define __localdep_open (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(open))
#else /* CUSTOM: open */
#undef ____localdep_open_defined
#endif /* open... */
#endif /* !____localdep_open_defined */

/* Dependency: "ftruncate" from "unistd" */
#ifndef ____localdep_ftruncate_defined
#define ____localdep_ftruncate_defined 1
#if defined(__CRT_HAVE_ftruncate64) && (defined(__USE_FILE_OFFSET64))
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate,(__fd_t __fd, __PIO_OFFSET __length),ftruncate64,(__fd,__length))
#elif defined(__CRT_HAVE__chsize_s) && (defined(__USE_FILE_OFFSET64))
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate,(__fd_t __fd, __PIO_OFFSET __length),_chsize_s,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate) && (!defined(__USE_FILE_OFFSET64))
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate,(__fd_t __fd, __PIO_OFFSET __length),ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE__chsize) && (!defined(__USE_FILE_OFFSET64))
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate,(__fd_t __fd, __PIO_OFFSET __length),_chsize,(__fd,__length))
#elif defined(__CRT_HAVE_chsize) && (!defined(__USE_FILE_OFFSET64))
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate,(__fd_t __fd, __PIO_OFFSET __length),chsize,(__fd,__length))
#elif defined(__CRT_HAVE__chsize_s)
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate,(__fd_t __fd, __PIO_OFFSET __length),_chsize_s,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s)
#include <local/unistd/ftruncate.h>
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
#define __localdep_ftruncate (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftruncate))
#else /* CUSTOM: ftruncate */
#undef ____localdep_ftruncate_defined
#endif /* ftruncate... */
#endif /* !____localdep_ftruncate_defined */

/* Dependency: "close" */
#ifndef ____localdep_close_defined
#define ____localdep_close_defined 1
#ifdef __CRT_HAVE_close
/* >> close(2)
 * Close a file handle */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
/* >> close(2)
 * Close a file handle */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
/* >> close(2)
 * Close a file handle */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#else /* LIBC: close */
#undef ____localdep_close_defined
#endif /* close... */
#endif /* !____localdep_close_defined */

__NAMESPACE_LOCAL_BEGIN
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else /* __USE_KOS */
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif /* !__USE_KOS */
#endif /* !__PIO_OFFSET */
/* >> c16truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__LOCAL_LIBC(c16truncate) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c16truncate))(__CHAR16_TYPE__ const *__file,
                                                         __PIO_OFFSET __length) {
#line 1257 "kos/src/libc/magic/unistd.c"
#if defined(__CRT_HAVE_wtruncate64)
	return __localdep_c16truncate64(__file, (__PIO_OFFSET64)__length);
#elif defined(__CRT_HAVE_wtruncate)
	return __localdep_c16truncate32(__file, (__pos32_t)__length);
#else
	int __result;
	__fd_t __fd;
	__fd = __localdep_open(__file, 1); /* O_WRONLY */
	if __unlikely(__fd < 0)
		return -1;
	__result = __localdep_ftruncate(__fd, __length);
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)
	__localdep_close(__fd);
#endif /* defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) */
	return __result;
#endif
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_wtruncate64) || defined(__CRT_HAVE_wtruncate) || ((defined(__CRT_HAVE_open) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE__open)) && (defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64))) */
#endif /* !__local_c16truncate_defined */
