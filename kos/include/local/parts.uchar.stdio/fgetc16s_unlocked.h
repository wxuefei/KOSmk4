/* HASH CRC-32:0x77f097ef */
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
#ifndef __local_fgetc16s_unlocked_defined
#define __local_fgetc16s_unlocked_defined 1
#include <__crt.h>
#if ((defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fgetwc_unlocked) || (defined(__CRT_HAVE__fgetwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_fgetwc_nolock)) && ((defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$ungetwc_unlocked) || (defined(__CRT_HAVE__ungetwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_ungetwc_nolock) || (defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$ungetwc)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))
#include <features.h>
#include <hybrid/typecore.h>
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: ferror_unlocked from stdio */
#ifndef __local___localdep_ferror_unlocked_defined
#define __local___localdep_ferror_unlocked_defined 1
#if defined(__CRT_HAVE_ferror_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Same as `ferror()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_ferror_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),ferror_unlocked,(__stream))
#elif defined(__CRT_HAVE_ferror)
/* Same as `ferror()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_ferror_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),ferror,(__stream))
#elif defined(__CRT_HAVE__IO_ferror)
/* Same as `ferror()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_ferror_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),_IO_ferror,(__stream))
#elif defined(__CRT_HAVE_ferror_unlocked)
/* Same as `ferror()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_ferror_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),ferror_unlocked,(__stream))
#else /* ... */
#undef __local___localdep_ferror_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_ferror_unlocked_defined */
/* Dependency: fgetc16_unlocked from parts.uchar.stdio */
#ifndef __local___localdep_fgetc16_unlocked_defined
#define __local___localdep_fgetc16_unlocked_defined 1
#if defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,__localdep_fgetc16_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_DOS$fgetwc_unlocked)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,__localdep_fgetc16_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,__localdep_fgetc16_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#elif defined(__CRT_HAVE_DOS$_fgetwc_nolock)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,__localdep_fgetc16_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#else /* ... */
#undef __local___localdep_fgetc16_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fgetc16_unlocked_defined */
/* Dependency: ungetc16_unlocked from parts.uchar.stdio */
#ifndef __local___localdep_ungetc16_unlocked_defined
#define __local___localdep_ungetc16_unlocked_defined 1
#if defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetc16_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),ungetwc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_DOS$ungetwc_unlocked)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetc16_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),ungetwc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetc16_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),_ungetwc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_DOS$_ungetwc_nolock)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetc16_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),_ungetwc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetc16_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#elif defined(__CRT_HAVE_DOS$ungetwc)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetc16_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#else /* ... */
#undef __local___localdep_ungetc16_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_ungetc16_unlocked_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/stdio.h>
#include <parts/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fgetc16s_unlocked) __ATTR_NONNULL((1, 3)) __CHAR16_TYPE__ *
(__LIBDCALL __LIBC_LOCAL_NAME(fgetc16s_unlocked))(__CHAR16_TYPE__ *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) __THROWS(...) {
	__SIZE_TYPE__ __n;
	if __unlikely(!__buf || !__bufsize) {
		/* The buffer cannot be empty! */
#ifdef __ERANGE
		__libc_seterrno(__ERANGE);
#endif /* __ERANGE */
		return __NULLPTR;
	}
	for (__n = 0; __n < __bufsize - 1; ++__n) {
		__WINT_TYPE__ __ch = __localdep_fgetc16_unlocked(__stream);
		if (__ch == __WEOF16) {
			if (__n == 0 || __localdep_ferror_unlocked(__stream))
				return __NULLPTR;
			break;
		}
		if (__ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			__buf[__n++] = '\n';
			__ch = __localdep_fgetc16_unlocked(__stream);
			if (__ch == __WEOF16) {
				if (__n == 0 || __localdep_ferror_unlocked(__stream))
					return __NULLPTR;
				break;
			}
			if (__ch == '\r')
				continue;
			__localdep_ungetc16_unlocked(__ch, __stream);
			break;
		}
		__buf[__n] = (__CHAR16_TYPE__)__ch;
		if (__ch == '\n')
			break;
	}
	__buf[__n] = '\0';
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fgetc16s_unlocked_defined
#define __local___localdep_fgetc16s_unlocked_defined 1
#define __localdep_fgetc16s_unlocked __LIBC_LOCAL_NAME(fgetc16s_unlocked)
#endif /* !__local___localdep_fgetc16s_unlocked_defined */
#else /* ((__CRT_HAVE_fgetwc_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$fgetwc_unlocked || (__CRT_HAVE__fgetwc_nolock && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$_fgetwc_nolock) && ((__CRT_HAVE_ungetwc_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$ungetwc_unlocked || (__CRT_HAVE__ungetwc_nolock && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$_ungetwc_nolock || (__CRT_HAVE_ungetwc && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$ungetwc) && (__CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked) */
#undef __local_fgetc16s_unlocked_defined
#endif /* ((!__CRT_HAVE_fgetwc_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$fgetwc_unlocked && (!__CRT_HAVE__fgetwc_nolock || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$_fgetwc_nolock) || ((!__CRT_HAVE_ungetwc_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$ungetwc_unlocked && (!__CRT_HAVE__ungetwc_nolock || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$_ungetwc_nolock && (!__CRT_HAVE_ungetwc || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$ungetwc) || (!__CRT_HAVE_ferror && !__CRT_HAVE__IO_ferror && !__CRT_HAVE_ferror_unlocked) */
#endif /* !__local_fgetc16s_unlocked_defined */
