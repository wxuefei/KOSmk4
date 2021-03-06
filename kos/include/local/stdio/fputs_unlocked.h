/* HASH CRC-32:0xbaa0802e */
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
#ifndef __local_fputs_unlocked_defined
#define __local_fputs_unlocked_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)
#include <kos/anno.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fwrite_unlocked from stdio */
#ifndef __local___localdep_fwrite_unlocked_defined
#define __local___localdep_fwrite_unlocked_defined 1
#ifdef __CRT_HAVE_fwrite_unlocked
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,__localdep_fwrite_unlocked,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fwrite)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,__localdep_fwrite_unlocked,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,__localdep_fwrite_unlocked,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_fwrite_nolock,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,__localdep_fwrite_unlocked,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_IO_fwrite,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)
__NAMESPACE_LOCAL_END
#include <local/stdio/fwrite_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
#define __localdep_fwrite_unlocked __LIBC_LOCAL_NAME(fwrite_unlocked)
#else /* ... */
#undef __local___localdep_fwrite_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fwrite_unlocked_defined */
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
/* Same as `fputs()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__LOCAL_LIBC(fputs_unlocked) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(fputs_unlocked))(char const *__restrict __string, __FILE *__restrict __stream) __THROWS(...) {
	__STDC_INT_AS_SIZE_T __result;
	__result = __localdep_fwrite_unlocked(__string,
	                         sizeof(char),
	                         __localdep_strlen(__string),
	                         __stream);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fputs_unlocked_defined
#define __local___localdep_fputs_unlocked_defined 1
#define __localdep_fputs_unlocked __LIBC_LOCAL_NAME(fputs_unlocked)
#endif /* !__local___localdep_fputs_unlocked_defined */
#else /* __CRT_HAVE_fwrite_unlocked || __CRT_HAVE_fwrite || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_HAVE_getc && (!__CRT_DOS || !__CRT_HAVE__filbuf)) || (__CRT_HAVE_fgetc && (!__CRT_DOS || !__CRT_HAVE__filbuf)) || (__CRT_HAVE__IO_getc && (!__CRT_DOS || !__CRT_HAVE__filbuf)) || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread || __CRT_HAVE_fread */
#undef __local_fputs_unlocked_defined
#endif /* !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE_fwrite && !__CRT_HAVE__fwrite_nolock && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && (!__CRT_HAVE_getc || (__CRT_DOS && __CRT_HAVE__filbuf)) && (!__CRT_HAVE_fgetc || (__CRT_DOS && __CRT_HAVE__filbuf)) && (!__CRT_HAVE__IO_getc || (__CRT_DOS && __CRT_HAVE__filbuf)) && (!__CRT_DOS || !__CRT_HAVE__filbuf) && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread */
#endif /* !__local_fputs_unlocked_defined */
