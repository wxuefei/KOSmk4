/* HASH CRC-32:0x8b0a7a5b */
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
#ifndef __local_sl_free_defined
#define __local_sl_free_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
#include <hybrid/typecore.h>
#ifndef ___stringlist_defined
#define ___stringlist_defined 1
typedef struct _stringlist {
	char   **sl_str;
	__SIZE_TYPE__   sl_max;
	__SIZE_TYPE__   sl_cur;
} StringList;
#endif /* !___stringlist_defined */
__NAMESPACE_LOCAL_BEGIN
/* Dependency: free from stdlib */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined 1
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ return __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
/* Free a given string list. When `ALL' is non-zero, all contained
 * string pointers (as previously added with `sl_add()') will also
 * be `free(3)'ed. */
__LOCAL_LIBC(sl_free) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sl_free))(struct _stringlist *__sl, int __all) {
	if __unlikely(!__sl)
		return;
	if __likely(__sl->sl_str) {
		if (__all) {
			__SIZE_TYPE__ __i;
			for (__i = 0; __i < __sl->sl_cur; ++__i)
				__localdep_free(__sl->sl_str[__i]);
		}
		__localdep_free(__sl->sl_str);
	}
	__localdep_free(__sl);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sl_free_defined
#define __local___localdep_sl_free_defined 1
#define __localdep_sl_free __LIBC_LOCAL_NAME(sl_free)
#endif /* !__local___localdep_sl_free_defined */
#else /* __CRT_HAVE_free || __CRT_HAVE_cfree */
#undef __local_sl_free_defined
#endif /* !__CRT_HAVE_free && !__CRT_HAVE_cfree */
#endif /* !__local_sl_free_defined */
