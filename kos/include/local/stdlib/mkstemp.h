/* HASH CRC-32:0x5461a15b */
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
#ifndef __local_mkstemp_defined
#define __local_mkstemp_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_mktemp) || defined(__CRT_HAVE__mktemp) || defined(__CRT_HAVE___mktemp)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: mktemp from stdlib */
#ifndef __local___localdep_mktemp_defined
#define __local___localdep_mktemp_defined 1
#ifdef __CRT_HAVE_mktemp
__CREDIRECT(__ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_mktemp,(char *__template_),mktemp,(__template_))
#elif defined(__CRT_HAVE__mktemp)
__CREDIRECT(__ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_mktemp,(char *__template_),_mktemp,(__template_))
#elif defined(__CRT_HAVE___mktemp)
__CREDIRECT(__ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_mktemp,(char *__template_),__mktemp,(__template_))
#else /* ... */
#undef __local___localdep_mktemp_defined
#endif /* !... */
#endif /* !__local___localdep_mktemp_defined */
__LOCAL_LIBC(mkstemp) __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mkstemp))(char *__template_) {
	return __localdep_mktemp(__template_) ? 0 : -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mkstemp_defined
#define __local___localdep_mkstemp_defined 1
#define __localdep_mkstemp __LIBC_LOCAL_NAME(mkstemp)
#endif /* !__local___localdep_mkstemp_defined */
#else /* __CRT_HAVE_mktemp || __CRT_HAVE__mktemp || __CRT_HAVE___mktemp */
#undef __local_mkstemp_defined
#endif /* !__CRT_HAVE_mktemp && !__CRT_HAVE__mktemp && !__CRT_HAVE___mktemp */
#endif /* !__local_mkstemp_defined */
