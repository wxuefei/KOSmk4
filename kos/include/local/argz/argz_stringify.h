/* HASH CRC-32:0x30ba024 */
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
#ifndef __local_argz_stringify_defined
#define __local_argz_stringify_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strlen from string */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined 1
#ifdef __CRT_HAVE_strlen
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
/* Convert an `ARGZ' string into a NUL-terminated c-string
 * with a total `strlen(argz) == len - 1', by replacing all
 * of the NUL-characters separating the individual ARGZ strings
 * with `SEP'. */
__LOCAL_LIBC(argz_stringify) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(argz_stringify))(char *__argz, __SIZE_TYPE__ __len, int __sep) {
	/* replace(base: argz, count: len - 1, old: '\0', new: sep); */
	if __unlikely(!__len)
		return;
	for (;;) {
		__SIZE_TYPE__ __temp;
		__temp = __localdep_strlen(__argz) + 1;
		if (__temp >= __len)
			break;
		__len  -= __temp;
		__argz += __temp;
		__argz[-1] = (char)(unsigned char)(unsigned int)__sep;
	}
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_argz_stringify_defined
#define __local___localdep_argz_stringify_defined 1
#define __localdep_argz_stringify __LIBC_LOCAL_NAME(argz_stringify)
#endif /* !__local___localdep_argz_stringify_defined */
#endif /* !__local_argz_stringify_defined */
