/* HASH CRC-32:0x9f000267 */
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
#ifndef __local_c32sto32_defined
#define __local_c32sto32_defined 1
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32stou32 from parts.uchar.wchar */
#ifndef __local___localdep_c32stou32_defined
#define __local___localdep_c32stou32_defined 1
#if defined(__CRT_HAVE_wcstou32) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou32)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoul) && __SIZEOF_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoull) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstouq) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoumax) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <local/wchar/wcstou32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32stou32 (*(__UINT32_TYPE__(__LIBKCALL *)(__CHAR32_TYPE__ const *__restrict, __CHAR32_TYPE__ **, __STDC_INT_AS_UINT_T))&__LIBC_LOCAL_NAME(wcstou32))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.wchar/c32stou32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32stou32 __LIBC_LOCAL_NAME(c32stou32)
#endif /* !... */
#endif /* !__local___localdep_c32stou32_defined */
__LOCAL_LIBC(c32sto32) __ATTR_LEAF __ATTR_NONNULL((1)) __INT32_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32sto32))(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) {
	__UINT32_TYPE__ __result;
	__CHAR32_TYPE__ __sign = *__nptr;
	if (__sign == '-') {
		++__nptr;
		__result = __localdep_c32stou32(__nptr, __endptr, __base);
		return -(__INT32_TYPE__)__result;
	} else if (__sign == '+') {
		++__nptr;
	}
	__result = __localdep_c32stou32(__nptr, __endptr, __base);
	return (__INT32_TYPE__)__result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32sto32_defined
#define __local___localdep_c32sto32_defined 1
#define __localdep_c32sto32 __LIBC_LOCAL_NAME(c32sto32)
#endif /* !__local___localdep_c32sto32_defined */
#endif /* !__local_c32sto32_defined */
