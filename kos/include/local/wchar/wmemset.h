/* HASH CRC-32:0xc6d7a05 */
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
#ifndef __local_wmemset_defined
#define __local_wmemset_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: memset from string */
#ifndef __local___localdep_memset_defined
#define __local___localdep_memset_defined 1
#ifdef __CRT_HAVE_memset
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* __CRT_HAVE_memset */
__NAMESPACE_LOCAL_END
#include <local/string/memset.h>
__NAMESPACE_LOCAL_BEGIN
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __localdep_memset __LIBC_LOCAL_NAME(memset)
#endif /* !__CRT_HAVE_memset */
#endif /* !__local___localdep_memset_defined */
/* Dependency: memsetl from string */
#ifndef __local___localdep_memsetl_defined
#define __local___localdep_memsetl_defined 1
#ifdef __CRT_HAVE_memsetl
/* Fill memory with a given dword */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memsetl,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_wmemset) && __SIZEOF_WCHAR_T__ == 4
/* Fill memory with a given dword */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),wmemset,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemset) && defined(__LIBCCALL_IS_LIBKCALL)
/* Fill memory with a given dword */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),KOS$wmemset,(__dst,__dword,__n_dwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/memsetl.h>
__NAMESPACE_LOCAL_BEGIN
/* Fill memory with a given dword */
#define __localdep_memsetl __LIBC_LOCAL_NAME(memsetl)
#endif /* !... */
#endif /* !__local___localdep_memsetl_defined */
/* Dependency: memsetw from string */
#ifndef __local___localdep_memsetw_defined
#define __local___localdep_memsetw_defined 1
#ifdef __CRT_HAVE_memsetw
/* Fill memory with a given word */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memsetw,(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_wmemset) && __SIZEOF_WCHAR_T__ == 2
/* Fill memory with a given word */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),wmemset,(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemset) && defined(__LIBCCALL_IS_LIBDCALL)
/* Fill memory with a given word */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),DOS$wmemset,(__dst,__word,__n_words))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/memsetw.h>
__NAMESPACE_LOCAL_BEGIN
/* Fill memory with a given word */
#define __localdep_memsetw __LIBC_LOCAL_NAME(memsetw)
#endif /* !... */
#endif /* !__local___localdep_memsetw_defined */
__LOCAL_LIBC(wmemset) __ATTR_RETNONNULL __ATTR_NONNULL((1)) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wmemset))(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ __filler, __SIZE_TYPE__ __num_chars) {
#if __SIZEOF_WCHAR_T__ == 2
	return (__WCHAR_TYPE__ *)__localdep_memsetw(__dst, (__UINT16_TYPE__)__filler, __num_chars);
#elif __SIZEOF_WCHAR_T__ == 4
	return (__WCHAR_TYPE__ *)__localdep_memsetl(__dst, (__UINT32_TYPE__)__filler, __num_chars);
#else /* ... */
	return (__WCHAR_TYPE__ *)__localdep_memset(__dst, (int)__filler, __num_chars * sizeof(__WCHAR_TYPE__));
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wmemset_defined
#define __local___localdep_wmemset_defined 1
#define __localdep_wmemset __LIBC_LOCAL_NAME(wmemset)
#endif /* !__local___localdep_wmemset_defined */
#endif /* !__local_wmemset_defined */
