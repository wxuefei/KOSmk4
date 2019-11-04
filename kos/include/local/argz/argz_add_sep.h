/* HASH CRC-32:0xf5d036e4 */
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
#ifndef __local_argz_add_sep_defined
#ifdef __CRT_HAVE_realloc
#define __local_argz_add_sep_defined 1
#include <parts/errno.h>
/* Dependency: "strlen" from "string" */
#ifndef ____localdep_strlen_defined
#define ____localdep_strlen_defined 1
#ifdef __CRT_HAVE_strlen
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* LIBC: strlen */
#include <local/string/strlen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlen))
#endif /* strlen... */
#endif /* !____localdep_strlen_defined */

/* Dependency: "realloc" */
#ifndef ____localdep_realloc_defined
#define ____localdep_realloc_defined 1
#ifdef __std___localdep_realloc_defined
__NAMESPACE_STD_USING(__localdep_realloc)
#elif __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__FORCELOCAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL __localdep_realloc)(void *__mallptr, __SIZE_TYPE__ __n_bytes) { return __builtin_realloc(__mallptr, __n_bytes); }
#elif defined(__CRT_HAVE_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __n_bytes),realloc,(__mallptr,__n_bytes))
#else /* LIBC: realloc */
#undef ____localdep_realloc_defined
#endif /* realloc... */
#endif /* !____localdep_realloc_defined */

/* Dependency: "free" */
#ifndef ____localdep_free_defined
#define ____localdep_free_defined 1
#ifdef __std___localdep_free_defined
__NAMESPACE_STD_USING(__localdep_free)
#elif __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__FORCELOCAL void __NOTHROW_NCX(__LIBCCALL __localdep_free)(void *__mallptr) { return __builtin_free(__mallptr); }
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#else /* LIBC: free */
#undef ____localdep_free_defined
#endif /* free... */
#endif /* !____localdep_free_defined */

__NAMESPACE_LOCAL_BEGIN
/* Append `SEP' separated list in `STRING' to the argz vector in `PARGZ & PARGZ_LEN' */
__LOCAL_LIBC(argz_add_sep) __ATTR_NONNULL((1, 2, 3)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(argz_add_sep))(char **__restrict __pargz,
                                                          __SIZE_TYPE__ *__restrict __pargz_len,
                                                          char const *__restrict __string,
                                                          int __sep) {
#line 281 "kos/src/libc/magic/argz.c"
	char *__result_string, *__dst;
	__SIZE_TYPE__ __oldlen;
	__SIZE_TYPE__ __slen = __localdep_strlen(__string);
	if __unlikely(!__slen)
		return 0;
	__oldlen = *__pargz_len;
	/* Note that GLibc actually has a bug here that causes it write `NULL'
	 * into the given `*pargz' pointer when the allocation fails, instead
	 * of leaving that pointer in its original state (allowing the caller
	 * to cleanup the ARGZ array, instead of forcing the array to become
	 * a memory leak)
	 * -> That bug is fixed here!
	 * Glibc's version of this:
	 * >> *argz = (char *) realloc (*argz, *argz_len + nlen); // <<< Right here!
	 * >> if (*argz == NULL)
	 * >>   return ENOMEM;
	 * As reference that the intended behavior in the ENOMEM-branch is an
	 * unmodified `*pargz' pointer (or at the very least, a simultanious
	 * setting of the `*pargz_len' pointer to ZERO(0)), you may look at
	 * Glibc's version of `argz_append()', which handles that case as
	 * leaving all pointers unmodified (just as one should)
	 */
	__result_string = (char *)__localdep_realloc(*__pargz, (__oldlen + (__slen + 1)) * sizeof(char));
	if __unlikely(!__result_string) {
#ifdef __ENOMEM
		return __ENOMEM;
#else /* __ENOMEM */
		return 1;
#endif /* !__ENOMEM */
	}
	*__pargz = __result_string;
	__dst    = __result_string + __oldlen;
	for (;;) {
		char __ch;
		__ch = *__string++;
__again_check_ch:
		if (!__ch)
			break;
		if (__ch != (char)(unsigned char)(unsigned int)__sep) {
			*__dst++ = __ch;
			continue;
		}
		/* Split the string. */
		*__dst++ = '\0';
		/* Skip consecutive `sep'-characters in `string' */
		do {
			__ch = *__string++;
		} while (__ch == (char)(unsigned char)(unsigned int)__sep);
		goto __again_check_ch;
	}
	if __unlikely(__dst == __result_string) {
		/* Empty string. (this can happen if `string' only consisted of `sep' characters) */
		__localdep_free(__result_string);
		*__pargz     = __NULLPTR;
		*__pargz_len = 0;
		return 0;
	}
	/* Write the terminating NUL-byte (if there isn't one already) */
	if (__dst[-1] != '\0')
		*__dst++ = '\0';
	*__pargz_len = (__SIZE_TYPE__)(__dst - __result_string);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_realloc) */
#endif /* !__local_argz_add_sep_defined */