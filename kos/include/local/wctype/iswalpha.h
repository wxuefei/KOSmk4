/* HASH CRC-32:0x9ad13708 */
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
#ifndef __local_iswalpha_defined
#define __local_iswalpha_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: isalpha from ctype */
#ifndef __local___localdep_isalpha_defined
#define __local___localdep_isalpha_defined 1
#if __has_builtin(__builtin_isalpha) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isalpha)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isalpha,(int __ch),isalpha,{ return __builtin_isalpha(__ch); })
#elif defined(__CRT_HAVE_isalpha)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isalpha,(int __ch),isalpha,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/ctype/isalpha.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isalpha __LIBC_LOCAL_NAME(isalpha)
#endif /* !... */
#endif /* !__local___localdep_isalpha_defined */
__LOCAL_LIBC(iswalpha) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(iswalpha))(__WINT_TYPE__ __wc) {
	return __localdep_isalpha((int)__wc);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_iswalpha_defined
#define __local___localdep_iswalpha_defined 1
#define __localdep_iswalpha __LIBC_LOCAL_NAME(iswalpha)
#endif /* !__local___localdep_iswalpha_defined */
#endif /* !__local_iswalpha_defined */
