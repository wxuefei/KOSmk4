/* HASH CRC-32:0x9e5806a */
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
#ifndef __local_c32chown_defined
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wfchownat)
#define __local_c32chown_defined 1
#include <__crt.h>
/* Dependency: "wfchownat" from "parts.wchar.unistd" */
#ifndef ____localdep_c32fchownat_defined
#define ____localdep_c32fchownat_defined 1
#if defined(__CRT_HAVE_wfchownat) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_c32fchownat,(__fd_t __dfd, __CHAR32_TYPE__ const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),wfchownat,(__dfd,__file,__owner,__group,__flags))
#else /* LIBC: wfchownat */
#undef ____localdep_c32fchownat_defined
#endif /* c32fchownat... */
#endif /* !____localdep_c32fchownat_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> c32chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__LOCAL_LIBC(c32chown) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(c32chown))(__CHAR32_TYPE__ const *__file,
                                                      __uid_t __owner,
                                                      __gid_t __group) {
#line 513 "kos/src/libc/magic/unistd.c"
	return __localdep_c32fchownat(__CRT_AT_FDCWD, __file, __owner, __group, 0);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_AT_FDCWD && __CRT_HAVE_wfchownat */
#endif /* !__local_c32chown_defined */
