/* HASH CRC-32:0xc788293e */
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
#ifndef __local_FTruncate64_defined
#define __local_FTruncate64_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_FTruncate
#include <kos/anno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: FTruncate32 from kos.unistd */
#ifndef __local___localdep_FTruncate32_defined
#define __local___localdep_FTruncate32_defined 1
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__THROWING,__localdep_FTruncate32,(__fd_t __fd, __pos32_t __length),FTruncate,(__fd,__length))
#endif /* !__local___localdep_FTruncate32_defined */
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__LOCAL_LIBC(FTruncate64) void
(__LIBCCALL __LIBC_LOCAL_NAME(FTruncate64))(__fd_t __fd, __pos64_t __length) __THROWS(...) {
	__localdep_FTruncate32(__fd, (__pos32_t)__length);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_FTruncate64_defined
#define __local___localdep_FTruncate64_defined 1
#define __localdep_FTruncate64 __LIBC_LOCAL_NAME(FTruncate64)
#endif /* !__local___localdep_FTruncate64_defined */
#else /* __CRT_HAVE_FTruncate */
#undef __local_FTruncate64_defined
#endif /* !__CRT_HAVE_FTruncate */
#endif /* !__local_FTruncate64_defined */
