/* HASH CRC-32:0xdd85e84b */
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
#ifndef __local_fopen64_defined
#define __local_fopen64_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_fopen) || defined(__CRT_HAVE__IO_fopen) || defined(__CRT_HAVE_fopen64)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fopen from stdio */
#ifndef __local___localdep_fopen_defined
#define __local___localdep_fopen_defined 1
#if defined(__CRT_HAVE_fopen64) && defined(__USE_FILE_OFFSET64)
/* Create and return a new file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,__localdep_fopen,(char const *__restrict __filename, char const *__restrict __modes),fopen64,(__filename,__modes))
#elif defined(__CRT_HAVE_fopen)
/* Create and return a new file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,__localdep_fopen,(char const *__restrict __filename, char const *__restrict __modes),fopen,(__filename,__modes))
#elif defined(__CRT_HAVE__IO_fopen)
/* Create and return a new file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,__localdep_fopen,(char const *__restrict __filename, char const *__restrict __modes),_IO_fopen,(__filename,__modes))
#elif defined(__CRT_HAVE_fopen64)
/* Create and return a new file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,__localdep_fopen,(char const *__restrict __filename, char const *__restrict __modes),fopen64,(__filename,__modes))
#else /* ... */
#undef __local___localdep_fopen_defined
#endif /* !... */
#endif /* !__local___localdep_fopen_defined */
/* 64-bit variant of `fopen' */
__LOCAL_LIBC(fopen64) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __FILE *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(fopen64))(char const *__restrict __filename, char const *__restrict __modes) {
	return __localdep_fopen(__filename, __modes);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fopen64_defined
#define __local___localdep_fopen64_defined 1
#define __localdep_fopen64 __LIBC_LOCAL_NAME(fopen64)
#endif /* !__local___localdep_fopen64_defined */
#else /* __CRT_HAVE_fopen || __CRT_HAVE__IO_fopen || __CRT_HAVE_fopen64 */
#undef __local_fopen64_defined
#endif /* !__CRT_HAVE_fopen && !__CRT_HAVE__IO_fopen && !__CRT_HAVE_fopen64 */
#endif /* !__local_fopen64_defined */
