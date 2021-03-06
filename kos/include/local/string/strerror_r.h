/* HASH CRC-32:0x6873ad2d */
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
#ifndef __local_strerror_r_defined
#define __local_strerror_r_defined 1
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: memcpyc from string */
#ifndef __local___localdep_memcpyc_defined
#define __local___localdep_memcpyc_defined 1
#ifdef __CRT_HAVE_memcpyc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memcpyc */
__NAMESPACE_LOCAL_END
#include <local/string/memcpyc.h>
__NAMESPACE_LOCAL_BEGIN
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpyc __LIBC_LOCAL_NAME(memcpyc)
#endif /* !__CRT_HAVE_memcpyc */
#endif /* !__local___localdep_memcpyc_defined */
/* Dependency: snprintf from stdio */
#ifndef __local___localdep_snprintf_defined
#define __local___localdep_snprintf_defined 1
#if __has_builtin(__builtin_snprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_snprintf) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__CEIREDIRECT(__ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_snprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, ...),snprintf,{ return __builtin_snprintf(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_snprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__LIBC __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_snprintf)(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, ...) __CASMNAME("snprintf");
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/stdio/snprintf.h>
__NAMESPACE_LOCAL_BEGIN
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
#define __localdep_snprintf __LIBC_LOCAL_NAME(snprintf)
#endif /* !... */
#endif /* !__local___localdep_snprintf_defined */
/* Dependency: strerror from string */
#ifndef __local___localdep_strerror_defined
#define __local___localdep_strerror_defined 1
#ifdef __CRT_HAVE_strerror
__CREDIRECT(__ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_strerror,(__errno_t __errnum),strerror,(__errnum))
#else /* __CRT_HAVE_strerror */
__NAMESPACE_LOCAL_END
#include <local/string/strerror.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strerror __LIBC_LOCAL_NAME(strerror)
#endif /* !__CRT_HAVE_strerror */
#endif /* !__local___localdep_strerror_defined */
/* Dependency: strerror_s from string */
#ifndef __local___localdep_strerror_s_defined
#define __local___localdep_strerror_s_defined 1
#ifdef __CRT_HAVE_strerror_s
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_strerror_s,(__errno_t __errnum),strerror_s,(__errnum))
#else /* __CRT_HAVE_strerror_s */
__NAMESPACE_LOCAL_END
#include <local/string/strerror_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strerror_s __LIBC_LOCAL_NAME(strerror_s)
#endif /* !__CRT_HAVE_strerror_s */
#endif /* !__local___localdep_strerror_s_defined */
/* Dependency: strlen from string */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined 1
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/__assert.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strerror_r) __ATTR_COLD __ATTR_RETNONNULL __ATTR_NONNULL((2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strerror_r))(__errno_t __errnum, char *__buf, __SIZE_TYPE__ __buflen) {
	char const *__string;
	if (!__buf)
		goto __fallback;
	if (!__buflen)
		goto __fallback;
	__string = __localdep_strerror_s(__errnum);
	if (__string) {
		/* Copy the descriptor text. */
		__SIZE_TYPE__ __msg_len = __localdep_strlen(__string) + 1;
		if (__msg_len > __buflen)
			goto __fallback;
		__localdep_memcpyc(__buf, __string, __msg_len, sizeof(char));
	} else {
		if (__localdep_snprintf(__buf, __buflen, "Unknown error %d", __errnum) >= __buflen)
			goto __fallback;
	}
	return __buf;
__fallback:
	return __localdep_strerror(__errnum);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strerror_r_defined
#define __local___localdep_strerror_r_defined 1
#define __localdep_strerror_r __LIBC_LOCAL_NAME(strerror_r)
#endif /* !__local___localdep_strerror_r_defined */
#endif /* !__local_strerror_r_defined */
