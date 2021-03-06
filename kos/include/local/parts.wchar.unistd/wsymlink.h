/* HASH CRC-32:0x231cce5 */
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
#ifndef __local_wsymlink_defined
#define __local_wsymlink_defined 1
#include <__crt.h>
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wsymlinkat)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wsymlinkat from parts.wchar.unistd */
#ifndef __local___localdep_wsymlinkat_defined
#define __local___localdep_wsymlinkat_defined 1
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__CREDIRECT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,__localdep_wsymlinkat,(__WCHAR_TYPE__ const *__link_text, __fd_t __tofd, __WCHAR_TYPE__ const *__target_path),wsymlinkat,(__link_text,__tofd,__target_path))
#endif /* !__local___localdep_wsymlinkat_defined */
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__LOCAL_LIBC(wsymlink) __ATTR_NONNULL((1, 2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wsymlink))(__WCHAR_TYPE__ const *__link_text, __WCHAR_TYPE__ const *__target_path) {
	/* TODO: Header-implementation for `symlink()' on DOS (using the windows API) */
	return __localdep_wsymlinkat(__link_text, __CRT_AT_FDCWD, __target_path);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wsymlink_defined
#define __local___localdep_wsymlink_defined 1
#define __localdep_wsymlink __LIBC_LOCAL_NAME(wsymlink)
#endif /* !__local___localdep_wsymlink_defined */
#else /* __CRT_AT_FDCWD && __CRT_HAVE_wsymlinkat */
#undef __local_wsymlink_defined
#endif /* !__CRT_AT_FDCWD || !__CRT_HAVE_wsymlinkat */
#endif /* !__local_wsymlink_defined */
