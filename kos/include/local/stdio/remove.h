/* HASH CRC-32:0xab2870cf */
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
#ifndef __local_remove_defined
#define __local_remove_defined 1
#include <__crt.h>
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_removeat)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: removeat from stdio */
#ifndef __local___localdep_removeat_defined
#define __local___localdep_removeat_defined 1
/* Remove a file or directory `FILENAME' relative to a given base directory `DIRFD' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_removeat,(__fd_t __dirfd, char const *__filename),removeat,(__dirfd,__filename))
#endif /* !__local___localdep_removeat_defined */
/* Remove a file or directory `FILENAME' */
__LOCAL_LIBC(remove) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(remove))(char const *__filename) {
	return __localdep_removeat(__CRT_AT_FDCWD, __filename);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_remove_defined
#define __local___localdep_remove_defined 1
#define __localdep_remove __LIBC_LOCAL_NAME(remove)
#endif /* !__local___localdep_remove_defined */
#else /* __CRT_AT_FDCWD && __CRT_HAVE_removeat */
#undef __local_remove_defined
#endif /* !__CRT_AT_FDCWD || !__CRT_HAVE_removeat */
#endif /* !__local_remove_defined */
