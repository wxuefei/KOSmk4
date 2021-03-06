/* HASH CRC-32:0x784d87e9 */
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
#ifndef __local_memcasecmp_defined
#define __local_memcasecmp_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: tolower from ctype */
#ifndef __local___localdep_tolower_defined
#define __local___localdep_tolower_defined 1
#if __has_builtin(__builtin_tolower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tolower)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),tolower,{ return __builtin_tolower(__ch); })
#elif defined(__CRT_HAVE_tolower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),tolower,(__ch))
#elif defined(__CRT_HAVE__tolower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),_tolower,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/ctype/tolower.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tolower __LIBC_LOCAL_NAME(tolower)
#endif /* !... */
#endif /* !__local___localdep_tolower_defined */
__LOCAL_LIBC(memcasecmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memcasecmp))(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) {
	__BYTE_TYPE__ *__p1 = (__BYTE_TYPE__ *)__s1;
	__BYTE_TYPE__ *__p2 = (__BYTE_TYPE__ *)__s2;
	__BYTE_TYPE__ __v1, __v2;
	__v1 = __v2 = 0;
	while (__n_bytes-- &&
	    (((__v1 = *__p1++) == (__v2 = *__p2++)) ||
	     ((__v1 = __localdep_tolower(__v1)) == (__v2 = __localdep_tolower(__v2)))));
	return (int)__v1 - (int)__v2;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memcasecmp_defined
#define __local___localdep_memcasecmp_defined 1
#define __localdep_memcasecmp __LIBC_LOCAL_NAME(memcasecmp)
#endif /* !__local___localdep_memcasecmp_defined */
#endif /* !__local_memcasecmp_defined */
