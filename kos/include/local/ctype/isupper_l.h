/* HASH CRC-32:0xce119ad */
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
#ifndef __local_isupper_l_defined
#define __local_isupper_l_defined 1
/* Dependency: "__locale_ctype_ptr_l" from "ctype" */
#ifndef ____localdep___locale_ctype_ptr_l_defined
#define ____localdep___locale_ctype_ptr_l_defined 1
#if defined(__CRT_HAVE___locale_ctype_ptr_l)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW_NCX,__localdep___locale_ctype_ptr_l,(__locale_t __locale),__locale_ctype_ptr_l,(__locale))
#else /* LIBC: __locale_ctype_ptr_l */
#undef ____localdep___locale_ctype_ptr_l_defined
#endif /* __locale_ctype_ptr_l... */
#endif /* !____localdep___locale_ctype_ptr_l_defined */

/* Dependency: "_isctype_l" from "ctype" */
#ifndef ____localdep__isctype_l_defined
#define ____localdep__isctype_l_defined 1
#if defined(__CRT_HAVE__isctype_l)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__isctype_l,(int __ch, int __mask, __locale_t __locale),_isctype_l,(__ch,__mask,__locale))
#else /* LIBC: _isctype_l */
#undef ____localdep__isctype_l_defined
#endif /* _isctype_l... */
#endif /* !____localdep__isctype_l_defined */

/* Dependency: "isupper" from "ctype" */
#ifndef ____localdep_isupper_defined
#define ____localdep_isupper_defined 1
#if __has_builtin(__builtin_isupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isupper)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isupper)(int __ch) { return __builtin_isupper(__ch); }
#elif defined(__CRT_HAVE_isupper)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isupper,(int __ch),isupper,(__ch))
#else /* LIBC: isupper */
#include <local/ctype/isupper.h>
#define __localdep_isupper (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isupper))
#endif /* isupper... */
#endif /* !____localdep_isupper_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(isupper_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(isupper_l))(int __ch,
                                                       __locale_t __locale) {
#line 382 "kos/src/libc/magic/ctype.c"
#if defined(__CRT_HAVE___ctype_b_loc) && defined(__CRT_GLC)
#include <__hybrid/__byteorder.__h>
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return __locale->__ctype_b[__ch] & (1 << 0);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	return __locale->__ctype_b[__ch] & (1 << 8);
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#elif defined(__CRT_HAVE___locale_ctype_ptr_l) && defined(__CRT_CYG)
	return ((__localdep___locale_ctype_ptr_l(__locale) + 1)[__ch & 0xff] & 3) == 1;
#elif defined(__CRT_HAVE__isctype_l) && defined(__CRT_DOS)
	return __localdep__isctype_l(__ch, 0x0001, __locale);
#else
	(void)__locale;
	return __localdep_isupper(__ch);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_isupper_l_defined */
