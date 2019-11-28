/* HASH CRC-32:0xc14dc6ba */
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
#ifndef __local_wlchown_defined
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wfchownat)
#define __local_wlchown_defined 1
/* Dependency: "wfchownat" from "parts.wchar.unistd" */
#ifndef ____localdep_wfchownat_defined
#define ____localdep_wfchownat_defined 1
#ifdef __CRT_HAVE_wfchownat
/* >> wfchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_wfchownat,(__fd_t __dfd, __WCHAR_TYPE__ const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),wfchownat,(__dfd,__file,__owner,__group,__flags))
#else /* LIBC: wfchownat */
#undef ____localdep_wfchownat_defined
#endif /* wfchownat... */
#endif /* !____localdep_wfchownat_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> wlchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__LOCAL_LIBC(wlchown) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wlchown))(__WCHAR_TYPE__ const *__file,
                                                     __uid_t __owner,
                                                     __gid_t __group) {
#line 1220 "kos/src/libc/magic/unistd.c"
	return __localdep_wfchownat(__CRT_AT_FDCWD, __file, __owner, __group, 0x0100); /* AT_SYMLINK_NOFOLLOW */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_AT_FDCWD && __CRT_HAVE_wfchownat */
#endif /* !__local_wlchown_defined */
