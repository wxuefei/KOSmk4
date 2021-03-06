/* HASH CRC-32:0x74ca0142 */
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
#ifndef __local_wcsnlwr_l_defined
#define __local_wcsnlwr_l_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: towlower_l from wctype */
#ifndef __local___localdep_towlower_l_defined
#define __local___localdep_towlower_l_defined 1
#ifdef __CRT_HAVE_towlower_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),towlower_l,(__wc,__locale))
#elif defined(__CRT_HAVE__towlower_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),_towlower_l,(__wc,__locale))
#elif defined(__CRT_HAVE___towlower_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),__towlower_l,(__wc,__locale))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/wctype/towlower_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_towlower_l __LIBC_LOCAL_NAME(towlower_l)
#endif /* !... */
#endif /* !__local___localdep_towlower_l_defined */
__LOCAL_LIBC(wcsnlwr_l) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsnlwr_l))(__WCHAR_TYPE__ *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale) {
	__WCHAR_TYPE__ *__iter, __ch;
	for (__iter = __str; __maxlen-- && (__ch = *__iter) != '\0'; ++__iter)
		*__iter = (__WCHAR_TYPE__)__localdep_towlower_l(__ch, __locale);
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcsnlwr_l_defined
#define __local___localdep_wcsnlwr_l_defined 1
#define __localdep_wcsnlwr_l __LIBC_LOCAL_NAME(wcsnlwr_l)
#endif /* !__local___localdep_wcsnlwr_l_defined */
#endif /* !__local_wcsnlwr_l_defined */
