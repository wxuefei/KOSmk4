/* HASH CRC-32:0x6dc94b37 */
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
#ifndef __local_opendir_defined
#if defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_fopendirat) || defined(__CRT_HAVE_opendirat))
#define __local_opendir_defined 1
/* Dependency: "opendirat" from "dirent" */
#ifndef ____localdep_opendirat_defined
#define ____localdep_opendirat_defined 1
#ifdef __CRT_HAVE_opendirat
/* Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),DIR *,__NOTHROW_RPC,__localdep_opendirat,(__fd_t __dirfd, char const *__name),opendirat,(__dirfd,__name))
#elif defined(__CRT_HAVE_fopendirat)
#include <local/dirent/opendirat.h>
/* Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
#define __localdep_opendirat (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(opendirat))
#else /* CUSTOM: opendirat */
#undef ____localdep_opendirat_defined
#endif /* opendirat... */
#endif /* !____localdep_opendirat_defined */

__NAMESPACE_LOCAL_BEGIN
/* Open and return a new directory stream for reading, referring to `name' */
__LOCAL_LIBC(opendir) __ATTR_WUNUSED __ATTR_NONNULL((1)) DIR *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(opendir))(char const *__name) {
#line 120 "kos/src/libc/magic/dirent.c"
	return __localdep_opendirat(__CRT_AT_FDCWD, __name);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_AT_FDCWD && (__CRT_HAVE_fopendirat || __CRT_HAVE_opendirat) */
#endif /* !__local_opendir_defined */
