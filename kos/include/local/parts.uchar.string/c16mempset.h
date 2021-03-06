/* HASH CRC-32:0xe2201fa4 */
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
#ifndef __local_c16mempset_defined
#define __local_c16mempset_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: mempset from string */
#ifndef __local___localdep_mempset_defined
#define __local___localdep_mempset_defined 1
#ifdef __CRT_HAVE_mempset
/* Same as `memset', but return `DST + N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_mempset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),mempset,(__dst,__byte,__n_bytes))
#else /* __CRT_HAVE_mempset */
__NAMESPACE_LOCAL_END
#include <local/string/mempset.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `memset', but return `DST + N_BYTES', rather than `DST' */
#define __localdep_mempset __LIBC_LOCAL_NAME(mempset)
#endif /* !__CRT_HAVE_mempset */
#endif /* !__local___localdep_mempset_defined */
/* Dependency: mempsetl from string */
#ifndef __local___localdep_mempsetl_defined
#define __local___localdep_mempsetl_defined 1
#ifdef __CRT_HAVE_mempsetl
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),mempsetl,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_wmempset) && __SIZEOF_WCHAR_T__ == 4
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),wmempset,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempset) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),KOS$wmempset,(__dst,__dword,__n_dwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/mempsetl.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
#define __localdep_mempsetl __LIBC_LOCAL_NAME(mempsetl)
#endif /* !... */
#endif /* !__local___localdep_mempsetl_defined */
/* Dependency: mempsetw from string */
#ifndef __local___localdep_mempsetw_defined
#define __local___localdep_mempsetw_defined 1
#ifdef __CRT_HAVE_mempsetw
/* Same as `memsetw', but return `DST + N_WORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),mempsetw,(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_wmempset) && __SIZEOF_WCHAR_T__ == 2
/* Same as `memsetw', but return `DST + N_WORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),wmempset,(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempset) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `memsetw', but return `DST + N_WORDS', rather than `DST' */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),DOS$wmempset,(__dst,__word,__n_words))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/mempsetw.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `memsetw', but return `DST + N_WORDS', rather than `DST' */
#define __localdep_mempsetw __LIBC_LOCAL_NAME(mempsetw)
#endif /* !... */
#endif /* !__local___localdep_mempsetw_defined */
/* Same as wmemset, but return a pointer after the last written character */
__LOCAL_LIBC(c16mempset) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16mempset))(__CHAR16_TYPE__ *__dst, __CHAR16_TYPE__ __filler, __SIZE_TYPE__ __num_chars) {

	return (__CHAR16_TYPE__ *)__localdep_mempsetw(__dst, (__UINT16_TYPE__)__filler, __num_chars);





}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16mempset_defined
#define __local___localdep_c16mempset_defined 1
#define __localdep_c16mempset __LIBC_LOCAL_NAME(c16mempset)
#endif /* !__local___localdep_c16mempset_defined */
#endif /* !__local_c16mempset_defined */
