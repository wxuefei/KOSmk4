/* HASH CRC-32:0xb795cfeb */
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
#ifndef __local_inet_neta_defined
#define __local_inet_neta_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <parts/errno.h>
/* Dependency: "memcpy" from "string" */
#ifndef ____localdep_memcpy_defined
#define ____localdep_memcpy_defined 1
#ifdef __fast_memcpy_defined
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpy (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))
#elif defined(__CRT_HAVE_memcpy)
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* LIBC: memcpy */
#include <local/string/memcpy.h>
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy))
#endif /* memcpy... */
#endif /* !____localdep_memcpy_defined */

/* Dependency: "snprintf" from "stdio" */
#ifndef ____localdep_snprintf_defined
#define ____localdep_snprintf_defined 1
#ifdef __std___localdep_snprintf_defined
__NAMESPACE_STD_USING(__localdep_snprintf)
#elif __has_builtin(__builtin_snprintf) && __has_builtin(__builtin_va_arg_pack) && !defined(__NO_EXTERNINLINE) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_snprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__CEIREDIRECT(__ATTR_NONNULL((3)) __ATTR_LIBC_PRINTF(3, 4),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_snprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, ...),snprintf,{ return __builtin_snprintf(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_snprintf) && !defined(__NO_ASMNAME)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__LIBC __ATTR_NONNULL((3)) __ATTR_LIBC_PRINTF(3, 4) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_snprintf)(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, ...) __CASMNAME("snprintf");
#else /* LIBC: snprintf */
#include <local/stdio/snprintf.h>
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
#define __localdep_snprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(snprintf))
#endif /* snprintf... */
#endif /* !____localdep_snprintf_defined */

__NAMESPACE_LOCAL_BEGIN
/* Format a network number NET into presentation format and place
 * result in buffer starting at BUF with length of LEN bytes */
__LOCAL_LIBC(inet_neta) __ATTR_NONNULL((2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(inet_neta))(__UINT32_TYPE__ __net,
                                                       char *__buf,
                                                       __SIZE_TYPE__ __len) {
#line 346 "kos/src/libc/magic/arpa.inet.c"
	__SIZE_TYPE__ __reqlen;
	if (__net <= 0xff) {
		if (!__net) {
			__reqlen = 8;
			if __likely(__len >= 8)
				__localdep_memcpy(__buf, "0.0.0.0", 8 * sizeof(char));
		} else {
			__reqlen = __localdep_snprintf(__buf, __len, "%u", (unsigned int)__net);
		}
	} else if (__net <= 0xffff) {
		__reqlen = __localdep_snprintf(__buf, __len, "%u.%u",
		                  (unsigned int)((__net & 0xff00) >> 8),
		                  (unsigned int)(__net & 0xff));
	} else if (__net <= 0xffffff) {
		__reqlen = __localdep_snprintf(__buf, __len, "%u.%u.%u",
		                  (unsigned int)((__net & 0xff0000) >> 16),
		                  (unsigned int)((__net & 0xff00) >> 8),
		                  (unsigned int)(__net & 0xff));
	} else {
		__reqlen = __localdep_snprintf(__buf, __len, "%u.%u.%u.%u",
		                  (unsigned int)((__net & 0xff000000) >> 24),
		                  (unsigned int)((__net & 0xff0000) >> 16),
		                  (unsigned int)((__net & 0xff00) >> 8),
		                  (unsigned int)(__net & 0xff));
	}
	if __unlikely(__reqlen > __len)
		goto __too_small;
	return __buf;
__too_small:
#ifdef __EMSGSIZE
	__libc_seterrno(__EMSGSIZE);
#elif defined(__ERANGE)
	__libc_seterrno(__ERANGE);
#elif defined(__EINVAL)
	__libc_seterrno(__EINVAL);
#endif
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_inet_neta_defined */