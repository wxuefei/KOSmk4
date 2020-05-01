/* HASH CRC-32:0xe60b8d7 */
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
#ifndef __local___strncpy_chk_defined
#define __local___strncpy_chk_defined 1
#include <__crt.h>
#include <ssp/chk.h>
/* Dependency: "strncpy" from "string" */
#ifndef ____localdep_strncpy_defined
#define ____localdep_strncpy_defined 1
#if __has_builtin(__builtin_strncpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncpy)
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_strncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),strncpy,{ return __builtin_strncpy(__buf, __src, __buflen); })
#elif defined(__CRT_HAVE_strncpy)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_strncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),strncpy,(__buf,__src,__buflen))
#else /* LIBC: strncpy */
#include <local/string/strncpy.h>
#define __localdep_strncpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncpy))
#endif /* strncpy... */
#endif /* !____localdep_strncpy_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__strncpy_chk) __ATTR_LEAF __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__strncpy_chk))(char *__restrict __dst,
                                                           char const *__restrict __src,
                                                           __SIZE_TYPE__ __buflen,
                                                           __SIZE_TYPE__ __dst_objsize) {
#line 43 "kos/src/libc/magic/ssp.string.c"
	(void)__dst_objsize; /* TODO */;
	return __localdep_strncpy(__dst, __src, __buflen);
}

__NAMESPACE_LOCAL_END
#endif /* !__local___strncpy_chk_defined */
