/* HASH CRC-32:0x4e6bdf84 */
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
#ifndef __local_iswprint_l_defined
#define __local_iswprint_l_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: iswprint from wctype */
#ifndef __local___localdep_iswprint_defined
#define __local___localdep_iswprint_defined 1
#if __has_builtin(__builtin_iswprint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswprint)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswprint,(__WINT_TYPE__ __wc),iswprint,{ return __builtin_iswprint(__wc); })
#elif defined(__CRT_HAVE_iswprint)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswprint,(__WINT_TYPE__ __wc),iswprint,(__wc))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/wctype/iswprint.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_iswprint __LIBC_LOCAL_NAME(iswprint)
#endif /* !... */
#endif /* !__local___localdep_iswprint_defined */
__LOCAL_LIBC(iswprint_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(iswprint_l))(__WINT_TYPE__ __wc, __locale_t __locale) {
	(void)__locale;
	__COMPILER_IMPURE();
	return __localdep_iswprint(__wc);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_iswprint_l_defined
#define __local___localdep_iswprint_l_defined 1
#define __localdep_iswprint_l __LIBC_LOCAL_NAME(iswprint_l)
#endif /* !__local___localdep_iswprint_l_defined */
#endif /* !__local_iswprint_l_defined */
