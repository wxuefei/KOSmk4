/* HASH CRC-32:0xcf214520 */
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
#ifndef __local___strcat_chk_defined
#define __local___strcat_chk_defined 1
#include <__crt.h>
#include <ssp/chk.h>
/* Dependency: "strcat" from "string" */
#ifndef ____localdep_strcat_defined
#define ____localdep_strcat_defined 1
#if __has_builtin(__builtin_strcat) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcat)
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_strcat,(char *__restrict __buf, char const *__restrict __src),strcat,{ return __builtin_strcat(__buf, __src); })
#elif defined(__CRT_HAVE_strcat)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_strcat,(char *__restrict __buf, char const *__restrict __src),strcat,(__buf,__src))
#else /* LIBC: strcat */
#include <local/string/strcat.h>
#define __localdep_strcat (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcat))
#endif /* strcat... */
#endif /* !____localdep_strcat_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__strcat_chk) __ATTR_LEAF __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__strcat_chk))(char *__restrict __dst,
                                                          char const *__restrict __src,
                                                          __SIZE_TYPE__ __dst_objsize) {
#line 40 "kos/src/libc/magic/ssp.string.c"
	(void)__dst_objsize; /* TODO */;
	return __localdep_strcat(__dst, __src);
}

__NAMESPACE_LOCAL_END
#endif /* !__local___strcat_chk_defined */
