/* HASH CRC-32:0x9a7e9223 */
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
#ifndef _STRINGLIST_H
#define _STRINGLIST_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <sys/types.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef ___stringlist_defined
#define ___stringlist_defined 1
typedef struct _stringlist {
	char   **sl_str; /* [1..1][owned(maybe)][0..sl_cur|ALLOC(sl_max)][owned] Vector of strings */
	size_t   sl_max; /* Allocated vector size */
	size_t   sl_cur; /* Used vector size */
} StringList;
#endif /* !___stringlist_defined */

#ifdef __CRT_HAVE_sl_init
/* Allocates and returns a new StringList object. Upon error, `NULL' is returned */
__CDECLARE(__ATTR_WUNUSED,struct _stringlist *,__NOTHROW_NCX,sl_init,(void),())
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#include <local/stringlist/sl_init.h>
/* Allocates and returns a new StringList object. Upon error, `NULL' is returned */
__NAMESPACE_LOCAL_USING_OR_IMPL(sl_init, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED struct _stringlist *__NOTHROW_NCX(__LIBCCALL sl_init)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sl_init))(); })
#endif /* ... */
#ifdef __CRT_HAVE_sl_add
/* Append a given `NAME' to `SL'. `NAME' is considered
 * inherited if the StringList is destroyed with `1' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,sl_add,(struct _stringlist *__sl, char *__name),(__sl,__name))
#elif defined(__CRT_HAVE_realloc)
#include <local/stringlist/sl_add.h>
/* Append a given `NAME' to `SL'. `NAME' is considered
 * inherited if the StringList is destroyed with `1' */
__NAMESPACE_LOCAL_USING_OR_IMPL(sl_add, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL sl_add)(struct _stringlist *__sl, char *__name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sl_add))(__sl, __name); })
#endif /* ... */
#ifdef __CRT_HAVE_sl_free
/* Free a given string list. When `ALL' is non-zero, all contained
 * string pointers (as previously added with `sl_add()') will also
 * be `free(3)'ed. */
__CDECLARE_VOID(,__NOTHROW_NCX,sl_free,(struct _stringlist *__sl, int __all),(__sl,__all))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
#include <local/stringlist/sl_free.h>
/* Free a given string list. When `ALL' is non-zero, all contained
 * string pointers (as previously added with `sl_add()') will also
 * be `free(3)'ed. */
__NAMESPACE_LOCAL_USING_OR_IMPL(sl_free, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL sl_free)(struct _stringlist *__sl, int __all) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sl_free))(__sl, __all); })
#endif /* ... */
#ifdef __CRT_HAVE_sl_find
/* Search for `NAME' within the given StringList. Upon success,
 * return a pointer to the equivalent string within `SL' (i.e. the
 * pointer originally passed to `sl_add()' to insert that string).
 * If `SL' doesn't contain an equivalent string, return `NULL' instead. */
__CDECLARE(__ATTR_PURE __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,sl_find,(struct _stringlist __KOS_FIXED_CONST *__sl, char const *__name),(__sl,__name))
#else /* __CRT_HAVE_sl_find */
#include <local/stringlist/sl_find.h>
/* Search for `NAME' within the given StringList. Upon success,
 * return a pointer to the equivalent string within `SL' (i.e. the
 * pointer originally passed to `sl_add()' to insert that string).
 * If `SL' doesn't contain an equivalent string, return `NULL' instead. */
__NAMESPACE_LOCAL_USING_OR_IMPL(sl_find, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL sl_find)(struct _stringlist __KOS_FIXED_CONST *__sl, char const *__name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sl_find))(__sl, __name); })
#endif /* !__CRT_HAVE_sl_find */
#ifdef __USE_BSD
#ifndef __sl_delete_defined
#define __sl_delete_defined 1
#ifdef __CRT_HAVE_sl_delete
/* Remove an entry `name' from `sl'
 * When `freeit' is non-zero, a removed string is deallocated using `free(3)'
 * @return: 0:  Successfully removed a string equal to `name'
 * @return: -1: No string equal to `name' was found in `sl' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,sl_delete,(struct _stringlist *__sl, char const *__name, int __freeit),(__sl,__name,__freeit))
#else /* __CRT_HAVE_sl_delete */
#include <local/stringlist/sl_delete.h>
/* Remove an entry `name' from `sl'
 * When `freeit' is non-zero, a removed string is deallocated using `free(3)'
 * @return: 0:  Successfully removed a string equal to `name'
 * @return: -1: No string equal to `name' was found in `sl' */
__NAMESPACE_LOCAL_USING_OR_IMPL(sl_delete, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL sl_delete)(struct _stringlist *__sl, char const *__name, int __freeit) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sl_delete))(__sl, __name, __freeit); })
#endif /* !__CRT_HAVE_sl_delete */
#endif /* !__sl_delete_defined */
#endif /* __USE_BSD */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_STRINGLIST_H */
