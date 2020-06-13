/* HASH CRC-32:0xe70d11f3 */
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
#ifndef __local__get_wpgmptr_defined
#define __local__get_wpgmptr_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE___p__wpgmptr) || (defined(__CRT_HAVE_DOS$__p__wpgmptr) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$__p__wpgmptr) && __SIZEOF_WCHAR_T__ == 2)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: __p__wpgmptr from stdlib */
#ifndef __local___localdep___p__wpgmptr_defined
#define __local___localdep___p__wpgmptr_defined 1
#ifdef __CRT_HAVE___p__wpgmptr
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__WCHAR_TYPE__ **,__NOTHROW_NCX,__localdep___p__wpgmptr,(void),__p__wpgmptr,())
#elif defined(__CRT_HAVE_DOS$__p__wpgmptr) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__WCHAR_TYPE__ **,__NOTHROW_NCX,__localdep___p__wpgmptr,(void),__p__wpgmptr,())
#elif defined(__CRT_HAVE_DOS$__p__wpgmptr) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__WCHAR_TYPE__ **,__NOTHROW_NCX,__localdep___p__wpgmptr,(void),__p__wpgmptr,())
#else /* ... */
#undef __local___localdep___p__wpgmptr_defined
#endif /* !... */
#endif /* !__local___localdep___p__wpgmptr_defined */
__LOCAL_LIBC(_get_wpgmptr) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_get_wpgmptr))(__WCHAR_TYPE__ **__pvalue) {
	*__pvalue = *__localdep___p__wpgmptr();
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__get_wpgmptr_defined
#define __local___localdep__get_wpgmptr_defined 1
#define __localdep__get_wpgmptr __LIBC_LOCAL_NAME(_get_wpgmptr)
#endif /* !__local___localdep__get_wpgmptr_defined */
#else /* __CRT_HAVE___p__wpgmptr || (__CRT_HAVE_DOS$__p__wpgmptr && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$__p__wpgmptr && __SIZEOF_WCHAR_T__ == 2) */
#undef __local__get_wpgmptr_defined
#endif /* !__CRT_HAVE___p__wpgmptr && (!__CRT_HAVE_DOS$__p__wpgmptr || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$__p__wpgmptr || !__SIZEOF_WCHAR_T__ == 2) */
#endif /* !__local__get_wpgmptr_defined */