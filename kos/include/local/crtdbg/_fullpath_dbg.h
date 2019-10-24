/* HASH CRC-32:0xc0511a85 */
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
#ifndef __local__fullpath_dbg_defined
#if defined(__CRT_HAVE__fullpath)
#define __local__fullpath_dbg_defined 1
/* Dependency: "_fullpath" */
#ifndef ____localdep__fullpath_defined
#define ____localdep__fullpath_defined 1
#if defined(__CRT_HAVE__fullpath)
__CREDIRECT(,char *,__NOTHROW_RPC,__localdep__fullpath,(char *__buf, char const *__path, __SIZE_TYPE__ __buflen),_fullpath,(__buf,__path,__buflen))
#else /* LIBC: _fullpath */
#undef ____localdep__fullpath_defined
#endif /* _fullpath... */
#endif /* !____localdep__fullpath_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_fullpath_dbg) __ATTR_WUNUSED __ATTR_NONNULL((2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_fullpath_dbg))(char *__full_path,
                                                           char const *__path,
                                                           __SIZE_TYPE__ __bufsize,
                                                           int __block_type,
                                                           char const *__filename,
                                                           int __line) {
#line 453 "kos/src/libc/magic/crtdbg.c"
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return __localdep__fullpath(__full_path, __path, __bufsize);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE__fullpath) */
#endif /* !__local__fullpath_dbg_defined */