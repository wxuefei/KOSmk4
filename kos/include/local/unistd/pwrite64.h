/* HASH CRC-32:0x8491b642 */
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
#ifndef __local_pwrite64_defined
#if (defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write)) && (defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE__lseeki64))))
#define __local_pwrite64_defined 1
/* Dependency: "pwrite32" from "unistd" */
#ifndef ____localdep_pwrite32_defined
#define ____localdep_pwrite32_defined 1
#if defined(__CRT_HAVE_pwrite)
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pwrite32,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize, __pos32_t __offset),pwrite,(__fd,__buf,__bufsize,__offset))
#else /* LIBC: pwrite */
#undef ____localdep_pwrite32_defined
#endif /* pwrite32... */
#endif /* !____localdep_pwrite32_defined */

/* Dependency: "lseek64" from "unistd" */
#ifndef ____localdep_lseek64_defined
#define ____localdep_lseek64_defined 1
#if defined(__CRT_HAVE_lseek64)
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, int __whence),lseek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, int __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseeki64)
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, int __whence),_lseeki64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek)
#include <local/unistd/lseek64.h>
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
#define __localdep_lseek64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lseek64))
#else /* CUSTOM: lseek64 */
#undef ____localdep_lseek64_defined
#endif /* lseek64... */
#endif /* !____localdep_lseek64_defined */

/* Dependency: "write" */
#ifndef ____localdep_write_defined
#define ____localdep_write_defined 1
#if defined(__CRT_HAVE_write)
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__write)
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),_write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___write)
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),__write,(__fd,__buf,__bufsize))
#else /* LIBC: write */
#undef ____localdep_write_defined
#endif /* write... */
#endif /* !____localdep_write_defined */

/* Dependency: "lseek32" from "unistd" */
#ifndef ____localdep_lseek32_defined
#define ____localdep_lseek32_defined 1
#if defined(__CRT_HAVE_lseek)
/* >> lseek32(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off32_t,__NOTHROW_NCX,__localdep_lseek32,(__fd_t __fd, __off32_t __offset, int __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseek)
/* >> lseek32(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off32_t,__NOTHROW_NCX,__localdep_lseek32,(__fd_t __fd, __off32_t __offset, int __whence),_lseek,(__fd,__offset,__whence))
#else /* LIBC: lseek */
#undef ____localdep_lseek32_defined
#endif /* lseek32... */
#endif /* !____localdep_lseek32_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
__LOCAL_LIBC(pwrite64) __ATTR_NONNULL((2)) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pwrite64))(__fd_t __fd,
                                                      void const *__buf,
                                                      __SIZE_TYPE__ __bufsize,
                                                      __PIO_OFFSET64 __offset) {
#line 950 "kos/src/libc/magic/unistd.c"
#if defined(__CRT_HAVE_pwrite) && ((!defined(__CRT_HAVE__lseeki64) && !defined(__CRT_HAVE_lseek64)) || (!defined(__CRT_HAVE_write) && !defined(__CRT_HAVE__write)))
	return __localdep_pwrite32(__fd, __buf, __bufsize, (__pos32_t)__offset);
#elif defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek64)
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	__off64_t __oldpos;
	__SSIZE_TYPE__ __result;
	__oldpos = __localdep_lseek64(__fd, 0, 1);
	if __unlikely(__oldpos < 0)
		return -1;
	if __unlikely(__localdep_lseek64(__fd, (__off64_t)__offset, 0) < 0)
		return -1;
	__result = __localdep_write(__fd, __buf, __bufsize);
	__localdep_lseek64(__fd, __oldpos, 0);
	return __result;
#else
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	__off32_t __oldpos;
	__SSIZE_TYPE__ __result;
	__oldpos = __localdep_lseek32(__fd, 0, 1);
	if __unlikely(__oldpos < 0)
		return -1;
	if __unlikely(__localdep_lseek32(__fd, (__off32_t)__offset, 0) < 0)
		return -1;
	__result = __localdep_write(__fd, __buf, __bufsize);
	__localdep_lseek32(__fd, __oldpos, 0);
	return __result;
#endif
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write)) && (defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE__lseeki64)))) */
#endif /* !__local_pwrite64_defined */
