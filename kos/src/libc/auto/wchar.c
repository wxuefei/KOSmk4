/* HASH CRC-32:0x3f3f2ea8 */
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
#ifndef GUARD_LIBC_AUTO_WCHAR_C
#define GUARD_LIBC_AUTO_WCHAR_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/wchar.h"
#include "parts.wchar.format-printer.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "../user/string.h"
#include "unicode.h"
#include "wctype.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED wint_t
NOTHROW_NCX(LIBDCALL libd_btowc)(int ch) {
	if (ch >= 0 && ch <= 0x7f)
		return (wint_t)ch;



	return (__CCAST(__WINT_TYPE__)0xffff);

}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_CONST WUNUSED wint_t
NOTHROW_NCX(LIBKCALL libc_btowc)(int ch) {
	if (ch >= 0 && ch <= 0x7f)
		return (wint_t)ch;

	return (__CCAST(__WINT_TYPE__)0xffffffffu);



}
#endif /* !__KERNEL__ */
#include <stdio.h>
#ifndef __KERNEL__
#include <asm/crt/stdio.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBCCALL libc_wctob)(wint_t ch) {
	if (ch >= 0 && ch <= 0x7f)
		return (int)ch;
	return EOF;
}
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_INTERN_ALIAS(libc_mbrtoc16, libd_mbrtowc);
DEFINE_INTERN_ALIAS(libc_c16rtomb, libd_wcrtomb);
#else /* __LIBCCALL_IS_LIBDCALL */
/* Because STDC mandates the uchar16 and uchar32 variants:
 *    mbrtowc:mbrtoc16:mbrtoc32
 *    wcrtomb:c16rtomb:c32rtomb
 * which are exposed in <uchar.h>, we need to be a little bit
 * more careful when it comes to defining them on a platform
 * where the standard DOS calling convention differs from the
 * calling convention used by KOS (e.g. x86-64)
 * 
 * In this scenario, magic will have already given the symbols:
 *   - LIBDCALL:DOS$mbrtowc:   size_t(wchar16_t *pwc, char const *str, size_t maxlen, mbstate_t *mbs);
 *     LIBDCALL:DOS$mbrtoc16:  ...
 *   - LIBKCALL:mbrtowc:       size_t(wchar32_t *pwc, char const *str, size_t maxlen, mbstate_t *mbs);
 *     LIBKCALL:mbrtoc32:      ...
 *     LIBDCALL:DOS$mbrtoc32:  ...  (msabi64-generator)
 *   - LIBDCALL:DOS$wcrtomb:   size_t(char *str, wchar16_t wc, mbstate_t *mbs);
 *     LIBDCALL:DOS$c16rtomb:  ...
 *   - LIBKCALL:wcrtomb:       size_t(char *str, wchar32_t wc, mbstate_t *mbs);
 *     LIBKCALL:c32rtomb:      ...
 *     LIBDCALL:DOS$c32rtomb:  ...  (msabi64-generator)
 *
 * However, you can see that this system is still lacking the LIBKCALL
 * variants of 2 functions that are only available as LIBDCALL (thus far):
 *     LIBKCALL:mbrtoc16:  ...
 *     LIBKCALL:c16rtomb:  ...
 *
 * And because the msabi64 generator doesn't include special handling for this case,
 * we simply have to manually implement these 2 functions as LIBKCALL wrappers for
 * the associated LIBDCALL functions:
 *
 *     libc_mbrtoc16(...) { return libd_mbrtowc(...); }
 *     libc_c16rtomb(...) { return libd_wcrtomb(...); }
 */
DEFINE_PUBLIC_ALIAS(mbrtoc16, libc_mbrtoc16);
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") size_t
NOTHROW_NCX(LIBKCALL libc_mbrtoc16)(char16_t *pwc,
                                    char const *__restrict str,
                                    size_t maxlen,
                                    mbstate_t *mbs) {
	return libd_mbrtowc(pwc, str, maxlen, mbs);
}

DEFINE_PUBLIC_ALIAS(c16rtomb, libc_c16rtomb);
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") size_t
NOTHROW_NCX(LIBKCALL libc_c16rtomb)(char *__restrict str,
                                    char16_t wc,
                                    mbstate_t *mbs) {
	return libd_wcrtomb(str, wc, mbs);
}
#endif /* !__LIBCCALL_IS_LIBDCALL */
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") size_t
NOTHROW_NCX(LIBDCALL libd_mbrtowc)(char16_t *pwc,
                                   char const *__restrict str,
                                   size_t maxlen,
                                   mbstate_t *mbs) {
	size_t error;
	if (!mbs) {
		static mbstate_t mbrtowc_ps = __MBSTATE_INIT;
		mbs = &mbrtowc_ps;
	}
	if (!str) {
		mbs->__word = 0;
		return 0;
	}
	if (!maxlen || !*str)
		return 0;

	error = libc_unicode_c8toc16((char16_t *)pwc, str, maxlen, mbs);



#ifdef EILSEQ
	if (error == (size_t)-1)
		__libc_seterrno(EILSEQ);
#endif /* EILSEQ */
	return error;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") size_t
NOTHROW_NCX(LIBKCALL libc_mbrtowc)(char32_t *pwc,
                                   char const *__restrict str,
                                   size_t maxlen,
                                   mbstate_t *mbs) {
	size_t error;
	if (!mbs) {
		static mbstate_t mbrtowc_ps = __MBSTATE_INIT;
		mbs = &mbrtowc_ps;
	}
	if (!str) {
		mbs->__word = 0;
		return 0;
	}
	if (!maxlen || !*str)
		return 0;



	error = libc_unicode_c8toc32((char32_t *)pwc, str, maxlen, mbs);

#ifdef EILSEQ
	if (error == (size_t)-1)
		__libc_seterrno(EILSEQ);
#endif /* EILSEQ */
	return error;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") size_t
NOTHROW_NCX(LIBDCALL libd_wcrtomb)(char *__restrict str,
                                   char16_t wc,
                                   mbstate_t *mbs) {
	char *endptr;
	size_t result;

	/* unicode_c16toc8() */
	if (!mbs) {
		static mbstate_t wcrtomb_ps = __MBSTATE_INIT;
		mbs = &wcrtomb_ps;
	}
	if (!str) {
		mbs->__word = 0;
		return 1;
	}
	if ((mbs->__word & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_UTF16_LO) {
		/* Complete surrogate */
		char32_t ch32;
		if unlikely(!((u16)wc >= 0xdc00 &&
		              (u16)wc <= 0xdfff)) {
			/* Expected low surrogate */
#ifdef EILSEQ
			__libc_seterrno(EILSEQ);
#endif /* EILSEQ */
			return (size_t)-1;
		}
		ch32 = ((mbs->__word & 0x000003ff) << 10) +
		       0x10000 + ((u16)wc - 0xdc00);
		mbs->__word = 0;
		endptr = libc_unicode_writeutf8(str, ch32);
	} else if ((u16)wc >= 0xd800 &&
	           (u16)wc <= 0xdbff) {
		mbs->__word = __MBSTATE_TYPE_UTF16_LO | ((u16)wc - 0xd800);
		return 0;
	} else {
		endptr = libc_unicode_writeutf8(str, (char32_t)(u32)(u16)wc);
	}







	result = (size_t)(endptr - str);
	return result;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") size_t
NOTHROW_NCX(LIBKCALL libc_wcrtomb)(char *__restrict str,
                                   char32_t wc,
                                   mbstate_t *mbs) {
	char *endptr;
	size_t result;

































	/* unicode_c32toc8() */
	(void)mbs;
	if (!str)
		return 1;
	endptr = libc_unicode_writeutf8(str, (char32_t)wc);

	result = (size_t)(endptr - str);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") WUNUSED size_t
NOTHROW_NCX(LIBDCALL libd_mbrlen)(char const *__restrict str,
                                  size_t maxlen,
                                  mbstate_t *mbs) {
	char16_t wc;
	return libd_mbrtowc(&wc, str, maxlen, mbs);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") WUNUSED size_t
NOTHROW_NCX(LIBKCALL libc_mbrlen)(char const *__restrict str,
                                  size_t maxlen,
                                  mbstate_t *mbs) {
	char32_t wc;
	return libc_mbrtowc(&wc, str, maxlen, mbs);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_mbsrtowcs)(char16_t *__restrict dst,
                                     char const **__restrict psrc,
                                     size_t dstlen,
                                     mbstate_t *mbs) {
	size_t result = 0;
	char const *src = *psrc;
	while (dstlen) {
		size_t error;
		char16_t wc;
		error = libd_mbrtowc(&wc, src, (size_t)-1, mbs);
		if (!error)
			break;
		if (error == (size_t)-1)
			return (size_t)-1; /* EILSEQ */
		*dst++ = wc;
		src += error;
		--dstlen;
		++result;
	}
	*psrc = src;
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_mbsrtowcs)(char32_t *__restrict dst,
                                     char const **__restrict psrc,
                                     size_t dstlen,
                                     mbstate_t *mbs) {
	size_t result = 0;
	char const *src = *psrc;
	while (dstlen) {
		size_t error;
		char32_t wc;
		error = libc_mbrtowc(&wc, src, (size_t)-1, mbs);
		if (!error)
			break;
		if (error == (size_t)-1)
			return (size_t)-1; /* EILSEQ */
		*dst++ = wc;
		src += error;
		--dstlen;
		++result;
	}
	*psrc = src;
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsrtombs)(char *dst,
                                     char16_t const **__restrict psrc,
                                     size_t dstlen,
                                     mbstate_t *mbs) {
	size_t result = 0;
	char16_t const *src = *psrc;
	while (dstlen) {
		size_t error;
		char buf[8];
		error = libd_wcrtomb(buf, *src, mbs);
		if (!error)
			break;
		if (error == (size_t)-1)
			return (size_t)-1; /* EILSEQ */
		if (error > dstlen)
			break;
		dst = (char *)libc_mempcpy(dst, buf, error);
		result += error;
		dstlen -= error;
		++src;
	}
	*psrc = src;
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsrtombs)(char *dst,
                                     char32_t const **__restrict psrc,
                                     size_t dstlen,
                                     mbstate_t *mbs) {
	size_t result = 0;
	char32_t const *src = *psrc;
	while (dstlen) {
		size_t error;
		char buf[8];
		error = libc_wcrtomb(buf, *src, mbs);
		if (!error)
			break;
		if (error == (size_t)-1)
			return (size_t)-1; /* EILSEQ */
		if (error > dstlen)
			break;
		dst = (char *)libc_mempcpy(dst, buf, error);
		result += error;
		dstlen -= error;
		++src;
	}
	*psrc = src;
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) long
NOTHROW_NCX(LIBDCALL libd_wcstol)(char16_t const *__restrict nptr,
                                  char16_t **endptr,
                                  __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG__ <= 4
	return (long)libd_wcsto32(nptr, endptr, base);
#else /* __SIZEOF_LONG__ <= 4 */
	return (long)libd_wcsto64(nptr, endptr, base);
#endif /* __SIZEOF_LONG__ > 4 */
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) long
NOTHROW_NCX(LIBKCALL libc_wcstol)(char32_t const *__restrict nptr,
                                  char32_t **endptr,
                                  __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG__ <= 4
	return (long)libc_wcsto32(nptr, endptr, base);
#else /* __SIZEOF_LONG__ <= 4 */
	return (long)libc_wcsto64(nptr, endptr, base);
#endif /* __SIZEOF_LONG__ > 4 */
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) unsigned long
NOTHROW_NCX(LIBDCALL libd_wcstoul)(char16_t const *__restrict nptr,
                                   char16_t **endptr,
                                   __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG__ <= 4
	return (unsigned long)libd_wcstou32(nptr, endptr, base);
#else /* __SIZEOF_LONG__ <= 4 */
	return (unsigned long)libd_wcstou64(nptr, endptr, base);
#endif /* __SIZEOF_LONG__ > 4 */
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) unsigned long
NOTHROW_NCX(LIBKCALL libc_wcstoul)(char32_t const *__restrict nptr,
                                   char32_t **endptr,
                                   __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG__ <= 4
	return (unsigned long)libc_wcstou32(nptr, endptr, base);
#else /* __SIZEOF_LONG__ <= 4 */
	return (unsigned long)libc_wcstou64(nptr, endptr, base);
#endif /* __SIZEOF_LONG__ > 4 */
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_mbsinit)(mbstate_t const *mbs) {
	return !mbs || __MBSTATE_ISINIT(mbs);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcscpy)(char16_t *__restrict buf,
                                  char16_t const *__restrict src) {
	return (char16_t *)libc_memcpyw(buf, src, libd_wcslen(src) + 1);
}
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcscpy)(char32_t *__restrict buf,
                                  char32_t const *__restrict src) {
	return (char32_t *)libc_memcpyl(buf, src, libc_wcslen(src) + 1);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcscat)(char16_t *__restrict buf,
                                  char16_t const *__restrict src) {
	(char16_t *)libc_memcpyw(libd_wcsend(buf), src, libd_wcslen(src) + 1);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcscat)(char32_t *__restrict buf,
                                  char32_t const *__restrict src) {
	(char32_t *)libc_memcpyl(libc_wcsend(buf), src, libc_wcslen(src) + 1);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsncat)(char16_t *__restrict buf,
                                   char16_t const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libd_wcsnlen(src, buflen);
	char16_t *dst = libd_wcsend(buf);
	(char16_t *)libc_memcpyw(dst, src, srclen);
	dst[srclen] = '\0';
	return buf;
}
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsncat)(char32_t *__restrict buf,
                                   char32_t const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libc_wcsnlen(src, buflen);
	char32_t *dst = libc_wcsend(buf);
	(char32_t *)libc_memcpyl(dst, src, srclen);
	dst[srclen] = '\0';
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsncpy)(char16_t *__restrict buf,
                                   char16_t const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libd_wcsnlen(src, buflen);
	(char16_t *)libc_memcpyw(buf, src, srclen);
	(char16_t *)libc_memsetw(buf+srclen, '\0', buflen - srclen);
	return buf;
}
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsncpy)(char32_t *__restrict buf,
                                   char32_t const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libc_wcsnlen(src, buflen);
	(char32_t *)libc_memcpyl(buf, src, srclen);
	(char32_t *)libc_memsetl(buf+srclen, '\0', buflen - srclen);
	return buf;
}
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcscmp)(char16_t const *s1,
                                  char16_t const *s2) {
	char16_t c1, c2;
	do {
		if unlikely((c1 = *s1++) != (c2 = *s2++))
			return (int)((char16_t)c1 - (char16_t)c2);
	} while (c1);
	return 0;
}
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcscmp)(char32_t const *s1,
                                  char32_t const *s2) {
	char32_t c1, c2;
	do {
		if unlikely((c1 = *s1++) != (c2 = *s2++))
			return (int)((char32_t)c1 - (char32_t)c2);
	} while (c1);
	return 0;
}
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsncmp)(char16_t const *s1,
                                   char16_t const *s2,
                                   size_t maxlen) {
	char16_t c1, c2;
	do {
		if (!maxlen--)
			break;
		if ((c1 = *s1++) != (c2 = *s2++))
			return (int)((char16_t)c1 - (char16_t)c2);
	} while (c1);
	return 0;
}
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsncmp)(char32_t const *s1,
                                   char32_t const *s2,
                                   size_t maxlen) {
	char32_t c1, c2;
	do {
		if (!maxlen--)
			break;
		if ((c1 = *s1++) != (c2 = *s2++))
			return (int)((char32_t)c1 - (char32_t)c2);
	} while (c1);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcscoll)(char16_t const *s1,
                                   char16_t const *s2) {
	return libd_wcscmp(s1, s2);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcscoll)(char32_t const *s1,
                                   char32_t const *s2) {
	return libc_wcscmp(s1, s2);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") NONNULL((2)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsxfrm)(char16_t *dst,
                                   char16_t const *__restrict src,
                                   size_t maxlen) {
	/* XXX: Implement me */
	size_t n = libd_wcsnlen(src, maxlen);
	libc_memcpy(dst, src, n * sizeof(char16_t));
	return n;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") NONNULL((2)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsxfrm)(char32_t *dst,
                                   char32_t const *__restrict src,
                                   size_t maxlen) {
	/* XXX: Implement me */
	size_t n = libc_wcsnlen(src, maxlen);
	libc_memcpy(dst, src, n * sizeof(char32_t));
	return n;
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.getc") wint_t
(LIBDCALL libd_getwchar)(void) THROWS(...) {
	return libd_fgetwc(stdin);
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.read.getc") wint_t
(LIBKCALL libc_getwchar)(void) THROWS(...) {
	return libc_fgetwc(stdin);
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.putc") wint_t
(LIBDCALL libd_putwchar)(char16_t wc) THROWS(...) {
	return libd_fputwc(wc, stdout);
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.putc") wint_t
(LIBKCALL libc_putwchar)(char32_t wc) THROWS(...) {
	return libc_fputwc(wc, stdout);
}
#include <parts/errno.h>
#include <asm/crt/stdio.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.read") WUNUSED NONNULL((1, 3)) char16_t *
(LIBDCALL libd_fgetws)(char16_t *__restrict buf,
                       __STDC_INT_AS_SIZE_T bufsize,
                       FILE *__restrict stream) THROWS(...) {
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
#ifdef ERANGE
		__libc_seterrno(ERANGE);
#endif /* ERANGE */
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		wint_t ch = libd_fgetwc(stream);
		if (ch == __WEOF16) {
			if (n == 0 || libc_ferror(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = libd_fgetwc(stream);
			if (ch == __WEOF16) {
				if (n == 0 || libc_ferror(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			libd_ungetwc(ch, stream);
			break;
		}
		buf[n] = (char16_t)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}
#include <parts/errno.h>
#include <asm/crt/stdio.h>
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.read.read") WUNUSED NONNULL((1, 3)) char32_t *
(LIBKCALL libc_fgetws)(char32_t *__restrict buf,
                       __STDC_INT_AS_SIZE_T bufsize,
                       FILE *__restrict stream) THROWS(...) {
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
#ifdef ERANGE
		__libc_seterrno(ERANGE);
#endif /* ERANGE */
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		wint_t ch = libc_fgetwc(stream);
		if (ch == __WEOF32) {
			if (n == 0 || libc_ferror(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = libc_fgetwc(stream);
			if (ch == __WEOF32) {
				if (n == 0 || libc_ferror(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			libc_ungetwc(ch, stream);
			break;
		}
		buf[n] = (char32_t)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.write") NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_fputws)(char16_t const *__restrict string,
                       FILE *__restrict stream) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	result = libd_file_wprinter(stream, string, libd_wcslen(string));
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.write") NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBKCALL libc_fputws)(char32_t const *__restrict string,
                       FILE *__restrict stream) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	result = libc_file_wprinter(stream, string, libc_wcslen(string));
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.strftime") NONNULL((1, 3, 4)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsftime)(char16_t *__restrict buf,
                                    size_t buflen,
                                    char16_t const *__restrict format,
                                    struct tm const *__restrict tp) {
	if (buflen)
		*buf = 0;
	/* TODO */
	(void)format;
	(void)tp;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.format.strftime") NONNULL((1, 3, 4)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsftime)(char32_t *__restrict buf,
                                    size_t buflen,
                                    char32_t const *__restrict format,
                                    struct tm const *__restrict tp) {
	if (buflen)
		*buf = 0;
	/* TODO */
	(void)format;
	(void)tp;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") NONNULL((2, 3)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcstok)(char16_t *string,
                                  char16_t const *__restrict delim,
                                  char16_t **__restrict save_ptr) {
	char16_t *end;
	if (!string)
		string = *save_ptr;
	if (!*string) {
		*save_ptr = string;
		return NULL;
	}
	string += libd_wcsspn(string, delim);
	if (!*string) {
		*save_ptr = string;
		return NULL;
	}
	end = string + libd_wcscspn(string, delim);
	if (!*end) {
		*save_ptr = end;
		return string;
	}
	*end = '\0';
	*save_ptr = end + 1;
	return string;
}
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") NONNULL((2, 3)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcstok)(char32_t *string,
                                  char32_t const *__restrict delim,
                                  char32_t **__restrict save_ptr) {
	char32_t *end;
	if (!string)
		string = *save_ptr;
	if (!*string) {
		*save_ptr = string;
		return NULL;
	}
	string += libc_wcsspn(string, delim);
	if (!*string) {
		*save_ptr = string;
		return NULL;
	}
	end = string + libc_wcscspn(string, delim);
	if (!*end) {
		*save_ptr = end;
		return string;
	}
	*end = '\0';
	*save_ptr = end + 1;
	return string;
}
#ifndef LIBC_ARCH_HAVE_C16SLEN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_wcslen)(char16_t const *__restrict string) {
	return (size_t)(libd_wcsend(string) - string);
}
#endif /* !LIBC_ARCH_HAVE_C16SLEN */
#ifndef LIBC_ARCH_HAVE_C32SLEN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBKCALL libc_wcslen)(char32_t const *__restrict string) {
	return (size_t)(libc_wcsend(string) - string);
}
#endif /* !LIBC_ARCH_HAVE_C32SLEN */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsspn)(char16_t const *haystack,
                                  char16_t const *accept) {
	char16_t const *iter = haystack;
	while (libd_wcschr(accept, *iter))
		++iter;
	return (size_t)(iter - haystack);
}
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsspn)(char32_t const *haystack,
                                  char32_t const *accept) {
	char32_t const *iter = haystack;
	while (libc_wcschr(accept, *iter))
		++iter;
	return (size_t)(iter - haystack);
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_wcscspn)(char16_t const *haystack,
                                   char16_t const *reject) {
	char16_t const *iter = haystack;
	while (*iter && !libd_wcschr(reject, *iter))
		++iter;
	return (size_t)(iter - haystack);
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_wcscspn)(char32_t const *haystack,
                                   char32_t const *reject) {
	char32_t const *iter = haystack;
	while (*iter && !libc_wcschr(reject, *iter))
		++iter;
	return (size_t)(iter - haystack);
}
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcschr)(char16_t const *__restrict haystack,
                                  char16_t needle) {
	for (; *haystack; ++haystack) {
		if unlikely(*haystack == (char16_t)needle)
			return (char16_t *)haystack;
	}
	return NULL;
}
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcschr)(char32_t const *__restrict haystack,
                                  char32_t needle) {
	for (; *haystack; ++haystack) {
		if unlikely(*haystack == (char32_t)needle)
			return (char32_t *)haystack;
	}
	return NULL;
}
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsrchr)(char16_t const *__restrict haystack,
                                   char16_t needle) {
	char16_t const *result = NULL;
	for (; *haystack; ++haystack) {
		if unlikely(*haystack == (char16_t)needle)
			result = haystack;
	}
	return (char16_t *)result;
}
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsrchr)(char32_t const *__restrict haystack,
                                   char32_t needle) {
	char32_t const *result = NULL;
	for (; *haystack; ++haystack) {
		if unlikely(*haystack == (char32_t)needle)
			result = haystack;
	}
	return (char32_t *)result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcspbrk)(char16_t const *haystack,
                                   char16_t const *accept) {
	char16_t haych, ch;
	while ((haych = *haystack++) != '\0') {
		char16_t const *ned_iter;
		ned_iter = accept;
		while ((ch = *ned_iter++) != '\0') {
			if (haych == ch)
				return (char16_t *)haystack - 1;
		}
	}
	return NULL;
}
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcspbrk)(char32_t const *haystack,
                                   char32_t const *accept) {
	char32_t haych, ch;
	while ((haych = *haystack++) != '\0') {
		char32_t const *ned_iter;
		ned_iter = accept;
		while ((ch = *ned_iter++) != '\0') {
			if (haych == ch)
				return (char32_t *)haystack - 1;
		}
	}
	return NULL;
}
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsstr)(char16_t const *haystack,
                                  char16_t const *needle) {
	char16_t ch, needle_start = *needle++;
	while ((ch = *haystack++) != '\0') {
		if (ch == needle_start) {
			char16_t const *hay2, *ned_iter;
			hay2     = haystack;
			ned_iter = needle;
			while ((ch = *ned_iter++) != '\0') {
				if (*hay2++ != ch)
					goto miss;
			}
			return (char16_t *)haystack - 1;
		}
miss:
		;
	}
	return NULL;
}
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsstr)(char32_t const *haystack,
                                  char32_t const *needle) {
	char32_t ch, needle_start = *needle++;
	while ((ch = *haystack++) != '\0') {
		if (ch == needle_start) {
			char32_t const *hay2, *ned_iter;
			hay2     = haystack;
			ned_iter = needle;
			while ((ch = *ned_iter++) != '\0') {
				if (*hay2++ != ch)
					goto miss;
			}
			return (char32_t *)haystack - 1;
		}
miss:
		;
	}
	return NULL;
}
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.utility") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_fwide)(FILE *fp,
                                 int mode) {
	(void)fp;
	(void)mode;
	COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") ATTR_LIBC_WPRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_fwprintf)(FILE *__restrict stream,
                          char16_t const *__restrict format,
                          ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vfwprintf(stream, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.printf") ATTR_LIBC_WPRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBKCALL libc_fwprintf)(FILE *__restrict stream,
                          char32_t const *__restrict format,
                          ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfwprintf(stream, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") ATTR_LIBC_WPRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vfwprintf)(FILE *__restrict stream,
                          char16_t const *__restrict format,
                          va_list args) THROWS(...) {
	return (__STDC_INT_AS_SSIZE_T)libd_format_vwprintf(&libd_file_wprinter, stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.printf") ATTR_LIBC_WPRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBKCALL libc_vfwprintf)(FILE *__restrict stream,
                          char32_t const *__restrict format,
                          va_list args) THROWS(...) {
	return (__STDC_INT_AS_SSIZE_T)libc_format_vwprintf(&libc_file_wprinter, stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") ATTR_LIBC_WPRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_wprintf)(char16_t const *__restrict format,
                         ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vwprintf(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.printf") ATTR_LIBC_WPRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBKCALL libc_wprintf)(char32_t const *__restrict format,
                         ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vwprintf(format, args);
	va_end(args);
	return result;
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") ATTR_LIBC_WPRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vwprintf)(char16_t const *__restrict format,
                         va_list args) THROWS(...) {
	return libd_vfwprintf(stdout, format, args);
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.printf") ATTR_LIBC_WPRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBKCALL libc_vwprintf)(char32_t const *__restrict format,
                         va_list args) THROWS(...) {
	return libc_vfwprintf(stdout, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_LIBC_WSCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_fwscanf)(FILE *__restrict stream,
                         char16_t const *__restrict format,
                         ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vfwscanf(stream, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.read.scanf") ATTR_LIBC_WSCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBKCALL libc_fwscanf)(FILE *__restrict stream,
                         char32_t const *__restrict format,
                         ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfwscanf(stream, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_LIBC_WSCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_wscanf)(char16_t const *__restrict format,
                        ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vwscanf(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.read.scanf") ATTR_LIBC_WSCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBKCALL libc_wscanf)(char32_t const *__restrict format,
                        ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vwscanf(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.scanf") ATTR_LIBC_WSCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd_swscanf)(char16_t const *__restrict src,
                                    char16_t const *__restrict format,
                                    ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vswscanf(src, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.format.scanf") ATTR_LIBC_WSCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBKCALL libc_swscanf)(char32_t const *__restrict src,
                                    char32_t const *__restrict format,
                                    ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vswscanf(src, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_WPRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd_vswprintf)(char16_t *__restrict buf,
                                     size_t buflen,
                                     char16_t const *__restrict format,
                                     va_list args) {
	COMPILER_IMPURE();
	if (buflen)
		*buf = 0;
	/* TODO: format_wprintf() */
	(void)format;
	(void)args;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.format.printf") ATTR_LIBC_WPRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBKCALL libc_vswprintf)(char32_t *__restrict buf,
                                     size_t buflen,
                                     char32_t const *__restrict format,
                                     va_list args) {
	COMPILER_IMPURE();
	if (buflen)
		*buf = 0;
	/* TODO: format_wprintf() */
	(void)format;
	(void)args;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_WPRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd_swprintf)(char16_t *__restrict buf,
                                     size_t buflen,
                                     char16_t const *__restrict format,
                                     ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vswprintf(buf, buflen, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.format.printf") ATTR_LIBC_WPRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBKCALL libc_swprintf)(char32_t *__restrict buf,
                                     size_t buflen,
                                     char32_t const *__restrict format,
                                     ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vswprintf(buf, buflen, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) double
NOTHROW_NCX(LIBDCALL libd_wcstod)(char16_t const *__restrict nptr,
                                  char16_t **endptr) {
	/* TODO */
	COMPILER_IMPURE();
	if (endptr)
		*endptr = (char16_t *)nptr;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) double
NOTHROW_NCX(LIBKCALL libc_wcstod)(char32_t const *__restrict nptr,
                                  char32_t **endptr) {
	/* TODO */
	COMPILER_IMPURE();
	if (endptr)
		*endptr = (char32_t *)nptr;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) float
NOTHROW_NCX(LIBDCALL libd_wcstof)(char16_t const *__restrict nptr,
                                  char16_t **endptr) {
	/* TODO */
	COMPILER_IMPURE();
	if (endptr)
		*endptr = (char16_t *)nptr;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) float
NOTHROW_NCX(LIBKCALL libc_wcstof)(char32_t const *__restrict nptr,
                                  char32_t **endptr) {
	/* TODO */
	COMPILER_IMPURE();
	if (endptr)
		*endptr = (char32_t *)nptr;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) __LONGDOUBLE
NOTHROW_NCX(LIBDCALL libd_wcstold)(char16_t const *__restrict nptr,
                                   char16_t **endptr) {
	/* TODO */
	COMPILER_IMPURE();
	if (endptr)
		*endptr = (char16_t *)nptr;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) __LONGDOUBLE
NOTHROW_NCX(LIBKCALL libc_wcstold)(char32_t const *__restrict nptr,
                                   char32_t **endptr) {
	/* TODO */
	COMPILER_IMPURE();
	if (endptr)
		*endptr = (char32_t *)nptr;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBDCALL libd_wcstoll)(char16_t const *__restrict nptr,
                                   char16_t **endptr,
                                   __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG_LONG__ <= 4
	return (__LONGLONG)libd_wcsto32(nptr, endptr, base);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__LONGLONG)libd_wcsto64(nptr, endptr, base);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBKCALL libc_wcstoll)(char32_t const *__restrict nptr,
                                   char32_t **endptr,
                                   __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG_LONG__ <= 4
	return (__LONGLONG)libc_wcsto32(nptr, endptr, base);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__LONGLONG)libc_wcsto64(nptr, endptr, base);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) __ULONGLONG
NOTHROW_NCX(LIBDCALL libd_wcstoull)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG_LONG__ <= 4
	return (__ULONGLONG)libd_wcstou32(nptr, endptr, base);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__ULONGLONG)libd_wcstou64(nptr, endptr, base);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) __ULONGLONG
NOTHROW_NCX(LIBKCALL libc_wcstoull)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG_LONG__ <= 4
	return (__ULONGLONG)libc_wcstou32(nptr, endptr, base);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__ULONGLONG)libc_wcstou64(nptr, endptr, base);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_WSCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vwscanf)(char16_t const *__restrict format,
                        va_list args) THROWS(...) {
	return libd_vfwscanf(stdin, format, args);
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_WSCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBKCALL libc_vwscanf)(char32_t const *__restrict format,
                        va_list args) THROWS(...) {
	return libc_vfwscanf(stdin, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.scanf") WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd_vswscanf)(char16_t const *__restrict src,
                                    char16_t const *__restrict format,
                                    va_list args) {
	/* TODO: format_wscanf() */
	(void)src;
	(void)format;
	(void)args;
	COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.format.scanf") WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBKCALL libc_vswscanf)(char32_t const *__restrict src,
                                    char32_t const *__restrict format,
                                    va_list args) {
	/* TODO: format_wscanf() */
	(void)src;
	(void)format;
	(void)args;
	COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcscasecmp)(char16_t const *s1,
                                      char16_t const *s2) {
	char16_t c1, c2;
	do {
		if ((c1 = *s1++) != (c2 = *s2++) && ((c1 = (char16_t)libc_towlower(c1)) != (c2 = (char16_t)libc_towlower(c2))))
			return (int)((char16_t)c1 - (char16_t)c2);
	} while (c1);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcscasecmp)(char32_t const *s1,
                                      char32_t const *s2) {
	char32_t c1, c2;
	do {
		if ((c1 = *s1++) != (c2 = *s2++) && ((c1 = (char32_t)libc_towlower(c1)) != (c2 = (char32_t)libc_towlower(c2))))
			return (int)((char32_t)c1 - (char32_t)c2);
	} while (c1);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsncasecmp)(char16_t const *s1,
                                       char16_t const *s2,
                                       size_t maxlen) {
	char16_t c1, c2;
	do {
		if (!maxlen--)
			break;
		if ((c1 = *s1++) != (c2 = *s2++) && ((c1 = (char16_t)libc_towlower(c1)) != (c2 = (char16_t)libc_towlower(c2))))
			return (int)((char16_t)c1 - (char16_t)c2);
	} while (c1);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsncasecmp)(char32_t const *s1,
                                       char32_t const *s2,
                                       size_t maxlen) {
	char32_t c1, c2;
	do {
		if (!maxlen--)
			break;
		if ((c1 = *s1++) != (c2 = *s2++) && ((c1 = (char32_t)libc_towlower(c1)) != (c2 = (char32_t)libc_towlower(c2))))
			return (int)((char32_t)c1 - (char32_t)c2);
	} while (c1);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcscasecmp_l)(char16_t const *s1,
                                        char16_t const *s2,
                                        locale_t locale) {
	(void)locale;
	return libd_wcscasecmp(s1, s2);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcscasecmp_l)(char32_t const *s1,
                                        char32_t const *s2,
                                        locale_t locale) {
	(void)locale;
	return libc_wcscasecmp(s1, s2);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsncasecmp_l)(char16_t const *s1,
                                         char16_t const *s2,
                                         size_t maxlen,
                                         locale_t locale) {
	(void)locale;
	return libd_wcsncasecmp(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsncasecmp_l)(char32_t const *s1,
                                         char32_t const *s2,
                                         size_t maxlen,
                                         locale_t locale) {
	(void)locale;
	return libc_wcsncasecmp(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcscoll_l)(char16_t const *s1,
                                     char16_t const *s2,
                                     locale_t locale) {
	(void)locale;
	return libd_wcscoll(s1, s2);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcscoll_l)(char32_t const *s1,
                                     char32_t const *s2,
                                     locale_t locale) {
	(void)locale;
	return libc_wcscoll(s1, s2);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") NONNULL((2)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsxfrm_l)(char16_t *dst,
                                     char16_t const *__restrict src,
                                     size_t maxlen,
                                     locale_t locale) {
	(void)locale;
	return libd_wcsxfrm(dst, src, maxlen);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") NONNULL((2)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsxfrm_l)(char32_t *dst,
                                     char32_t const *__restrict src,
                                     size_t maxlen,
                                     locale_t locale) {
	(void)locale;
	return libc_wcsxfrm(dst, src, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcpcpy)(char16_t *__restrict dst,
                                  char16_t const *__restrict src) {
	return (char16_t *)libc_mempcpyw(dst, src, libd_wcslen(src) + 1);
}
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcpcpy)(char32_t *__restrict dst,
                                  char32_t const *__restrict src) {
	return (char32_t *)libc_mempcpyl(dst, src, libc_wcslen(src) + 1);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcpncpy)(char16_t *__restrict buf,
                                   char16_t const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libd_wcsnlen(src, buflen);
	(char16_t *)libc_memcpyw(buf, src, srclen);
	(char16_t *)libc_memsetw(buf + srclen, '\0', (size_t)(buflen - srclen));
	return buf + srclen;
}
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcpncpy)(char32_t *__restrict buf,
                                   char32_t const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libc_wcsnlen(src, buflen);
	(char32_t *)libc_memcpyl(buf, src, srclen);
	(char32_t *)libc_memsetl(buf + srclen, '\0', (size_t)(buflen - srclen));
	return buf + srclen;
}
#ifndef LIBC_ARCH_HAVE_C16SNLEN
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsnlen)(char16_t const *__restrict string,
                                   size_t maxlen) {
	return (size_t)(libd_wcsnend(string, maxlen) - string);
}
#endif /* !LIBC_ARCH_HAVE_C16SNLEN */
#ifndef LIBC_ARCH_HAVE_C32SNLEN
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsnlen)(char32_t const *__restrict string,
                                   size_t maxlen) {
	return (size_t)(libc_wcsnend(string, maxlen) - string);
}
#endif /* !LIBC_ARCH_HAVE_C32SNLEN */
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsdup)(char16_t const *__restrict string) {
	size_t resultsize = (libd_wcslen(string) + 1) * sizeof(char16_t);
	char16_t *result = (char16_t *)libc_malloc(resultsize);
	if likely(result)
		libc_memcpy(result, string, resultsize);
	return result;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.wchar.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsdup)(char32_t const *__restrict string) {
	size_t resultsize = (libc_wcslen(string) + 1) * sizeof(char32_t);
	char32_t *result = (char32_t *)libc_malloc(resultsize);
	if likely(result)
		libc_memcpy(result, string, resultsize);
	return result;
}
#include <libc/unicode.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBDCALL libd_wcwidth)(char16_t ch) {

	if (ch >= 0xd800 &&
	    ch <= 0xdfff)
		return 0;

	if (__libc_unicode_isprint(ch))
		return 1;
	if (ch == 0)
		return 0;
	return -1;
}
#include <libc/unicode.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBKCALL libc_wcwidth)(char32_t ch) {





	if (__libc_unicode_isprint(ch))
		return 1;
	if (ch == 0)
		return 0;
	return -1;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_wcswidth)(char16_t const *__restrict string,
                                    size_t num_chars) {
	int temp, result = 0;
	for (; num_chars; --num_chars, ++string) {
		char16_t ch = *string;
		if (!ch)
			break;
		temp = libd_wcwidth(ch);
		if (temp < 0)
			return temp;
		result += temp;
	}
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBKCALL libc_wcswidth)(char32_t const *__restrict string,
                                    size_t num_chars) {
	int temp, result = 0;
	for (; num_chars; --num_chars, ++string) {
		char32_t ch = *string;
		if (!ch)
			break;
		temp = libc_wcwidth(ch);
		if (temp < 0)
			return temp;
		result += temp;
	}
	return 0;
}
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcschrnul)(char16_t const *haystack,
                                     char16_t needle) {
	for (; *haystack; ++haystack) {
		if ((char16_t)*haystack == (char16_t)needle)
			break;
	}
	return (char16_t *)haystack;
}
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcschrnul)(char32_t const *haystack,
                                     char32_t needle) {
	for (; *haystack; ++haystack) {
		if ((char32_t)*haystack == (char32_t)needle)
			break;
	}
	return (char32_t *)haystack;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") NONNULL((1)) long
NOTHROW_NCX(LIBDCALL libd_wcstol_l)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    __STDC_INT_AS_UINT_T base,
                                    locale_t locale) {
	(void)locale;
	return libd_wcstol(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") NONNULL((1)) long
NOTHROW_NCX(LIBKCALL libc_wcstol_l)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    __STDC_INT_AS_UINT_T base,
                                    locale_t locale) {
	(void)locale;
	return libc_wcstol(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") NONNULL((1)) unsigned long
NOTHROW_NCX(LIBDCALL libd_wcstoul_l)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libd_wcstoul(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") NONNULL((1)) unsigned long
NOTHROW_NCX(LIBKCALL libc_wcstoul_l)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libc_wcstoul(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBDCALL libd_wcstoll_l)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libd_wcstoll(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBKCALL libc_wcstoll_l)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libc_wcstoll(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") NONNULL((1)) __ULONGLONG
NOTHROW_NCX(LIBDCALL libd_wcstoull_l)(char16_t const *__restrict nptr,
                                      char16_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libd_wcstoull(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") NONNULL((1)) __ULONGLONG
NOTHROW_NCX(LIBKCALL libc_wcstoull_l)(char32_t const *__restrict nptr,
                                      char32_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libc_wcstoull(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") NONNULL((1)) float
NOTHROW_NCX(LIBDCALL libd_wcstof_l)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    locale_t locale) {
	(void)locale;
	return libd_wcstof(nptr, endptr);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") NONNULL((1)) float
NOTHROW_NCX(LIBKCALL libc_wcstof_l)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    locale_t locale) {
	(void)locale;
	return libc_wcstof(nptr, endptr);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") NONNULL((1)) double
NOTHROW_NCX(LIBDCALL libd_wcstod_l)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    locale_t locale) {
	(void)locale;
	return libd_wcstod(nptr, endptr);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") NONNULL((1)) double
NOTHROW_NCX(LIBKCALL libc_wcstod_l)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    locale_t locale) {
	(void)locale;
	return libc_wcstod(nptr, endptr);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") NONNULL((1)) __LONGDOUBLE
NOTHROW_NCX(LIBDCALL libd_wcstold_l)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     locale_t locale) {
	(void)locale;
	return libd_wcstold(nptr, endptr);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") NONNULL((1)) __LONGDOUBLE
NOTHROW_NCX(LIBKCALL libc_wcstold_l)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     locale_t locale) {
	(void)locale;
	return libc_wcstold(nptr, endptr);
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.getc") wint_t
(LIBDCALL libd_getwchar_unlocked)(void) THROWS(...) {
	return libd_fgetwc_unlocked(stdin);
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.getc") wint_t
(LIBKCALL libc_getwchar_unlocked)(void) THROWS(...) {
	return libc_fgetwc_unlocked(stdin);
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.putc") wint_t
(LIBDCALL libd_putwchar_unlocked)(char16_t wc) THROWS(...) {
	return libd_fputwc_unlocked(wc, stdin);
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.putc") wint_t
(LIBKCALL libc_putwchar_unlocked)(char32_t wc) THROWS(...) {
	return libc_fputwc_unlocked(wc, stdin);
}
#include <asm/crt/stdio.h>
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.read") NONNULL((1, 3)) char16_t *
(LIBDCALL libd_fgetws_unlocked)(char16_t *__restrict buf,
                                __STDC_INT_AS_SIZE_T bufsize,
                                FILE *__restrict stream) THROWS(...) {
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
#ifdef ERANGE
		__libc_seterrno(ERANGE);
#endif /* ERANGE */
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		wint_t ch = libd_fgetwc_unlocked(stream);
		if (ch == __WEOF16) {
			if (n == 0 || libc_ferror(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = libd_fgetwc_unlocked(stream);
			if (ch == __WEOF16) {
				if (n == 0 || libc_ferror(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			libd_ungetwc_unlocked(ch, stream);
			break;
		}
		buf[n] = (char16_t)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}
#include <asm/crt/stdio.h>
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.read") NONNULL((1, 3)) char32_t *
(LIBKCALL libc_fgetws_unlocked)(char32_t *__restrict buf,
                                __STDC_INT_AS_SIZE_T bufsize,
                                FILE *__restrict stream) THROWS(...) {
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
#ifdef ERANGE
		__libc_seterrno(ERANGE);
#endif /* ERANGE */
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		wint_t ch = libc_fgetwc_unlocked(stream);
		if (ch == __WEOF32) {
			if (n == 0 || libc_ferror(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = libc_fgetwc_unlocked(stream);
			if (ch == __WEOF32) {
				if (n == 0 || libc_ferror(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			libc_ungetwc_unlocked(ch, stream);
			break;
		}
		buf[n] = (char32_t)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.write") NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_fputws_unlocked)(char16_t const *__restrict string,
                                FILE *__restrict stream) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	result = libd_file_wprinter_unlocked(stream, string, libd_wcslen(string));
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.write") NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBKCALL libc_fputws_unlocked)(char32_t const *__restrict string,
                                FILE *__restrict stream) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	result = libc_file_wprinter_unlocked(stream, string, libc_wcslen(string));
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.strftime") NONNULL((1, 3, 4)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsftime_l)(char16_t *__restrict buf,
                                      size_t maxsize,
                                      char16_t const *__restrict format,
                                      struct tm const *__restrict tp,
                                      locale_t locale) {
	(void)locale;
	return libd_wcsftime(buf, maxsize, format, tp);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.format.strftime") NONNULL((1, 3, 4)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsftime_l)(char32_t *__restrict buf,
                                      size_t maxsize,
                                      char32_t const *__restrict format,
                                      struct tm const *__restrict tp,
                                      locale_t locale) {
	(void)locale;
	return libc_wcsftime(buf, maxsize, format, tp);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.printf") ATTR_LIBC_WPRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vfwprintf_unlocked)(FILE *__restrict stream,
                                   char16_t const *__restrict format,
                                   va_list args) THROWS(...) {
	return (__STDC_INT_AS_SSIZE_T)libd_format_vwprintf(&libd_file_wprinter_unlocked,
	                                              stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.printf") ATTR_LIBC_WPRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBKCALL libc_vfwprintf_unlocked)(FILE *__restrict stream,
                                   char32_t const *__restrict format,
                                   va_list args) THROWS(...) {
	return (__STDC_INT_AS_SSIZE_T)libc_format_vwprintf(&libc_file_wprinter_unlocked,
	                                              stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.printf") ATTR_LIBC_WPRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_fwprintf_unlocked)(FILE *__restrict stream,
                                   char16_t const *__restrict format,
                                   ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vfwprintf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.printf") ATTR_LIBC_WPRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBKCALL libc_fwprintf_unlocked)(FILE *__restrict stream,
                                   char32_t const *__restrict format,
                                   ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfwprintf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.printf") ATTR_LIBC_WPRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_wprintf_unlocked)(char16_t const *__restrict format,
                                  ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vwprintf_unlocked(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.printf") ATTR_LIBC_WPRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBKCALL libc_wprintf_unlocked)(char32_t const *__restrict format,
                                  ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vwprintf_unlocked(format, args);
	va_end(args);
	return result;
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.printf") ATTR_LIBC_WPRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vwprintf_unlocked)(char16_t const *__restrict format,
                                  va_list args) THROWS(...) {
	return libd_vfwprintf_unlocked(stdout, format, args);
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.printf") ATTR_LIBC_WPRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBKCALL libc_vwprintf_unlocked)(char32_t const *__restrict format,
                                  va_list args) THROWS(...) {
	return libc_vfwprintf_unlocked(stdout, format, args);
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vwscanf_unlocked)(char16_t const *__restrict format,
                                 va_list args) THROWS(...) {
	return libd_vfwscanf_unlocked(stdin, format, args);
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBKCALL libc_vwscanf_unlocked)(char32_t const *__restrict format,
                                 va_list args) THROWS(...) {
	return libc_vfwscanf_unlocked(stdin, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_fwscanf_unlocked)(FILE *__restrict stream,
                                  char16_t const *__restrict format,
                                  ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vfwscanf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBKCALL libc_fwscanf_unlocked)(FILE *__restrict stream,
                                  char32_t const *__restrict format,
                                  ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfwscanf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_wscanf_unlocked)(char16_t const *__restrict format,
                                 ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vwscanf_unlocked(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBKCALL libc_wscanf_unlocked)(char32_t const *__restrict format,
                                 ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vwscanf_unlocked(format, args);
	va_end(args);
	return result;
}
#ifndef LIBC_ARCH_HAVE_C16SEND
/* Same as `STR+wcslen(STR)' */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsend)(char16_t const *__restrict string) {
	while (*string)
		++string;
	return (char16_t *)string;
}
#endif /* !LIBC_ARCH_HAVE_C16SEND */
#ifndef LIBC_ARCH_HAVE_C32SEND
/* Same as `STR+wcslen(STR)' */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsend)(char32_t const *__restrict string) {
	while (*string)
		++string;
	return (char32_t *)string;
}
#endif /* !LIBC_ARCH_HAVE_C32SEND */
#ifndef LIBC_ARCH_HAVE_C16SNEND
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnend)(char16_t const *__restrict string,
                                   size_t maxlen) {
	for (; maxlen && *string; ++string, --maxlen)
		;
	return (char16_t *)string;
}
#endif /* !LIBC_ARCH_HAVE_C16SNEND */
#ifndef LIBC_ARCH_HAVE_C32SNEND
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnend)(char32_t const *__restrict string,
                                   size_t maxlen) {
	for (; maxlen && *string; ++string, --maxlen)
		;
	return (char32_t *)string;
}
#endif /* !LIBC_ARCH_HAVE_C32SNEND */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) int32_t
NOTHROW_NCX(LIBDCALL libd_wcsto32)(char16_t const *__restrict nptr,
                                   char16_t **endptr,
                                   __STDC_INT_AS_UINT_T base) {
	u32 result;
	char16_t sign = *nptr;
	if (sign == '-') {
		++nptr;
		result = libd_wcstou32(nptr, endptr, base);
		return -(s32)result;
	} else if (sign == '+') {
		++nptr;
	}
	result = libd_wcstou32(nptr, endptr, base);
	return (s32)result;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) int32_t
NOTHROW_NCX(LIBKCALL libc_wcsto32)(char32_t const *__restrict nptr,
                                   char32_t **endptr,
                                   __STDC_INT_AS_UINT_T base) {
	u32 result;
	char32_t sign = *nptr;
	if (sign == '-') {
		++nptr;
		result = libc_wcstou32(nptr, endptr, base);
		return -(s32)result;
	} else if (sign == '+') {
		++nptr;
	}
	result = libc_wcstou32(nptr, endptr, base);
	return (s32)result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint32_t
NOTHROW_NCX(LIBDCALL libd_wcstou32)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    __STDC_INT_AS_UINT_T base) {
	u32 result, temp;
	if (!base) {
		if (*nptr == '0') {
			char16_t ch = *++nptr;
			if (ch == 'x' || ch == 'X') {
				++nptr;
				base = 16;
			} else if (ch == 'b' || ch == 'B') {
				++nptr;
				base = 2;
			} else {
				base = 8;
			}
		} else {
			base = 10;
		}
	}
	result = 0;
	for (;;) {
		char16_t ch = *nptr;
		if (ch >= '0' && ch <= '9')
			temp = (u64)(ch - '0');
		else if (ch >= 'a' && ch <= 'z')
			temp = (u64)10 + (ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			temp = (u64)10 + (ch - 'A');
		else {
			/* TODO: Support for unicode decimals, and multi-byte characters.
			 *       But only do this if libc supports it (i.e. don't do this
			 *       in kernel-space) */
			break;
		}
		if (temp >= (unsigned int)base)
			break;
		++nptr;
		/* XXX: Check for overflow when we have a non-noop __libc_seterrno(ERANGE) */
		result *= (unsigned int)base;
		result += temp;
	}
	if (endptr)
		*endptr = (char16_t *)nptr;
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint32_t
NOTHROW_NCX(LIBKCALL libc_wcstou32)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    __STDC_INT_AS_UINT_T base) {
	u32 result, temp;
	if (!base) {
		if (*nptr == '0') {
			char32_t ch = *++nptr;
			if (ch == 'x' || ch == 'X') {
				++nptr;
				base = 16;
			} else if (ch == 'b' || ch == 'B') {
				++nptr;
				base = 2;
			} else {
				base = 8;
			}
		} else {
			base = 10;
		}
	}
	result = 0;
	for (;;) {
		char32_t ch = *nptr;
		if (ch >= '0' && ch <= '9')
			temp = (u64)(ch - '0');
		else if (ch >= 'a' && ch <= 'z')
			temp = (u64)10 + (ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			temp = (u64)10 + (ch - 'A');
		else {
			/* TODO: Support for unicode decimals, and multi-byte characters.
			 *       But only do this if libc supports it (i.e. don't do this
			 *       in kernel-space) */
			break;
		}
		if (temp >= (unsigned int)base)
			break;
		++nptr;
		/* XXX: Check for overflow when we have a non-noop __libc_seterrno(ERANGE) */
		result *= (unsigned int)base;
		result += temp;
	}
	if (endptr)
		*endptr = (char32_t *)nptr;
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint64_t
NOTHROW_NCX(LIBDCALL libd_wcstou64)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    __STDC_INT_AS_UINT_T base) {
	u64 result, temp;
	if (!base) {
		if (*nptr == '0') {
			char16_t ch = *++nptr;
			if (ch == 'x' || ch == 'X') {
				++nptr;
				base = 16;
			} else if (ch == 'b' || ch == 'B') {
				++nptr;
				base = 2;
			} else {
				base = 8;
			}
		} else {
			base = 10;
		}
	}
	result = 0;
	for (;;) {
		char16_t ch = *nptr;
		if (ch >= '0' && ch <= '9')
			temp = (u64)(ch - '0');
		else if (ch >= 'a' && ch <= 'z')
			temp = (u64)10 + (ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			temp = (u64)10 + (ch - 'A');
		else {
			/* TODO: Support for unicode decimals, and multi-byte characters.
			 *       But only do this if libc supports it (i.e. don't do this
			 *       in kernel-space) */
			break;
		}
		if (temp >= (unsigned int)base)
			break;
		++nptr;
		/* XXX: Check for overflow when we have a non-noop __libc_seterrno(ERANGE) */
		result *= (unsigned int)base;
		result += temp;
	}
	if (endptr)
		*endptr = (char16_t *)nptr;
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint64_t
NOTHROW_NCX(LIBKCALL libc_wcstou64)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    __STDC_INT_AS_UINT_T base) {
	u64 result, temp;
	if (!base) {
		if (*nptr == '0') {
			char32_t ch = *++nptr;
			if (ch == 'x' || ch == 'X') {
				++nptr;
				base = 16;
			} else if (ch == 'b' || ch == 'B') {
				++nptr;
				base = 2;
			} else {
				base = 8;
			}
		} else {
			base = 10;
		}
	}
	result = 0;
	for (;;) {
		char32_t ch = *nptr;
		if (ch >= '0' && ch <= '9')
			temp = (u64)(ch - '0');
		else if (ch >= 'a' && ch <= 'z')
			temp = (u64)10 + (ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			temp = (u64)10 + (ch - 'A');
		else {
			/* TODO: Support for unicode decimals, and multi-byte characters.
			 *       But only do this if libc supports it (i.e. don't do this
			 *       in kernel-space) */
			break;
		}
		if (temp >= (unsigned int)base)
			break;
		++nptr;
		/* XXX: Check for overflow when we have a non-noop __libc_seterrno(ERANGE) */
		result *= (unsigned int)base;
		result += temp;
	}
	if (endptr)
		*endptr = (char32_t *)nptr;
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) int64_t
NOTHROW_NCX(LIBDCALL libd_wcsto64)(char16_t const *__restrict nptr,
                                   char16_t **endptr,
                                   __STDC_INT_AS_UINT_T base) {
	u64 result;
	char16_t sign = *nptr;
	if (sign == '-') {
		++nptr;
		result = libd_wcstou64(nptr, endptr, base);
		return -(s64)result;
	} else if (sign == '+') {
		++nptr;
	}
	result = libd_wcstou64(nptr, endptr, base);
	return (s64)result;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) int64_t
NOTHROW_NCX(LIBKCALL libc_wcsto64)(char32_t const *__restrict nptr,
                                   char32_t **endptr,
                                   __STDC_INT_AS_UINT_T base) {
	u64 result;
	char32_t sign = *nptr;
	if (sign == '-') {
		++nptr;
		result = libc_wcstou64(nptr, endptr, base);
		return -(s64)result;
	} else if (sign == '+') {
		++nptr;
	}
	result = libc_wcstou64(nptr, endptr, base);
	return (s64)result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_LEAF NONNULL((1)) int32_t
NOTHROW_NCX(LIBDCALL libd_wcsto32_l)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libd_wcsto32(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") ATTR_LEAF NONNULL((1)) int32_t
NOTHROW_NCX(LIBKCALL libc_wcsto32_l)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libc_wcsto32(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_LEAF NONNULL((1)) uint32_t
NOTHROW_NCX(LIBDCALL libd_wcstou32_l)(char16_t const *__restrict nptr,
                                      char16_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libd_wcstou32(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") ATTR_LEAF NONNULL((1)) uint32_t
NOTHROW_NCX(LIBKCALL libc_wcstou32_l)(char32_t const *__restrict nptr,
                                      char32_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libc_wcstou32(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_LEAF NONNULL((1)) int64_t
NOTHROW_NCX(LIBDCALL libd_wcsto64_l)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libd_wcsto64(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") ATTR_LEAF NONNULL((1)) int64_t
NOTHROW_NCX(LIBKCALL libc_wcsto64_l)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libc_wcsto64(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_LEAF NONNULL((1)) uint64_t
NOTHROW_NCX(LIBDCALL libd_wcstou64_l)(char16_t const *__restrict nptr,
                                      char16_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libd_wcstou64(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") ATTR_LEAF NONNULL((1)) uint64_t
NOTHROW_NCX(LIBKCALL libc_wcstou64_l)(char32_t const *__restrict nptr,
                                      char32_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libc_wcstou64(nptr, endptr, base);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsncoll)(char16_t const *s1,
                                    char16_t const *s2,
                                    size_t maxlen) {
	return libd_wcsncmp(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsncoll)(char32_t const *s1,
                                    char32_t const *s2,
                                    size_t maxlen) {
	return libc_wcsncmp(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcscasecoll)(char16_t const *s1,
                                       char16_t const *s2) {
	return libd_wcscasecmp(s1, s2);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcscasecoll)(char32_t const *s1,
                                       char32_t const *s2) {
	return libc_wcscasecmp(s1, s2);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsncasecoll)(char16_t const *s1,
                                        char16_t const *s2,
                                        size_t maxlen) {
	return libd_wcsncasecmp(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsncasecoll)(char32_t const *s1,
                                        char32_t const *s2,
                                        size_t maxlen) {
	return libc_wcsncasecmp(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnrev)(char16_t *__restrict str,
                                   size_t maxlen) {

	return (char16_t *)libc_memrevw(str, libd_wcsnlen(str, maxlen));





}
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnrev)(char32_t *__restrict str,
                                   size_t maxlen) {



	return (char32_t *)libc_memrevl(str, libc_wcsnlen(str, maxlen));



}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnlwr)(char16_t *__restrict str,
                                   size_t maxlen) {
	char16_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towlower(ch);
	return str;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnlwr)(char32_t *__restrict str,
                                   size_t maxlen) {
	char32_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower(ch);
	return str;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnupr)(char16_t *__restrict str,
                                   size_t maxlen) {
	char16_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towupper(ch);
	return str;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnupr)(char32_t *__restrict str,
                                   size_t maxlen) {
	char32_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper(ch);
	return str;
}
/* Same as `strstr', but ignore casing */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcscasestr)(char16_t const *haystack,
                                      char16_t const *needle) {
	for (; *haystack; ++haystack) {
		if (libd_wcscasecmp(haystack, needle) == 0)
			return (char16_t *)haystack;
	}
	return NULL;
}
/* Same as `strstr', but ignore casing */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcscasestr)(char32_t const *haystack,
                                      char32_t const *needle) {
	for (; *haystack; ++haystack) {
		if (libc_wcscasecmp(haystack, needle) == 0)
			return (char32_t *)haystack;
	}
	return NULL;
}
/* Same as wcscpy, but return a pointer after the last written character */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcspcpy)(char16_t *__restrict buf,
                                   char16_t const *__restrict src) {
	return (char16_t *)libc_mempcpyw(buf, src, libd_wcslen(src) + 1);
}
/* Same as wcscpy, but return a pointer after the last written character */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcspcpy)(char32_t *__restrict buf,
                                   char32_t const *__restrict src) {
	return (char32_t *)libc_mempcpyl(buf, src, libc_wcslen(src) + 1);
}
/* Same as wcsncpy, but return a pointer after the last written character */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcspncpy)(char16_t *__restrict buf,
                                    char16_t const *__restrict src,
                                    size_t buflen) {
	size_t srclen = libd_wcsnlen(src, buflen);
	(char16_t *)libc_memcpyw(buf, src, srclen);
	return (char16_t *)libc_mempsetw(buf + srclen, '\0', buflen - srclen);
}
/* Same as wcsncpy, but return a pointer after the last written character */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcspncpy)(char32_t *__restrict buf,
                                    char32_t const *__restrict src,
                                    size_t buflen) {
	size_t srclen = libc_wcsnlen(src, buflen);
	(char32_t *)libc_memcpyl(buf, src, srclen);
	return (char32_t *)libc_mempsetl(buf + srclen, '\0', buflen - srclen);
}
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnchr)(char16_t const *__restrict haystack,
                                   char16_t needle,
                                   size_t maxlen) {
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((char16_t)*haystack == (char16_t)needle)
			return (char16_t *)haystack;
	}
	return NULL;
}
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnchr)(char32_t const *__restrict haystack,
                                   char32_t needle,
                                   size_t maxlen) {
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((char32_t)*haystack == (char32_t)needle)
			return (char32_t *)haystack;
	}
	return NULL;
}
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnrchr)(char16_t const *__restrict haystack,
                                    char16_t needle,
                                    size_t maxlen) {
	char16_t const *result = NULL;
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((char16_t)*haystack == (char16_t)needle)
			result = haystack;
	}
	return (char16_t *)result;
}
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnrchr)(char32_t const *__restrict haystack,
                                    char32_t needle,
                                    size_t maxlen) {
	char32_t const *result = NULL;
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((char32_t)*haystack == (char32_t)needle)
			result = haystack;
	}
	return (char32_t *)result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcssep)(char16_t **__restrict stringp,
                                  char16_t const *__restrict delim) {
	char16_t *result, *iter;
	if (!stringp || (result = *stringp) == NULL || !*result)
		return NULL;
	for (iter = result; *iter && !libd_wcschr(delim, *iter); ++iter)
		;
	if (*iter)
		*iter++ = '\0';
	*stringp = iter;
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_LEAF NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcssep)(char32_t **__restrict stringp,
                                  char32_t const *__restrict delim) {
	char32_t *result, *iter;
	if (!stringp || (result = *stringp) == NULL || !*result)
		return NULL;
	for (iter = result; *iter && !libc_wcschr(delim, *iter); ++iter)
		;
	if (*iter)
		*iter++ = '\0';
	*stringp = iter;
	return result;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsfry)(char16_t *__restrict string) {
	size_t i, count = libd_wcslen(string);
	for (i = 0; i < count; ++i) {
		char16_t temp;
		size_t j = libc_rand();
		j = i + (j % (count - i));
		/* Swap these 2 characters. */
		temp = string[i];
		string[i] = string[j];
		string[j] = temp;
	}
	return string;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsfry)(char32_t *__restrict string) {
	size_t i, count = libc_wcslen(string);
	for (i = 0; i < count; ++i) {
		char32_t temp;
		size_t j = libc_rand();
		j = i + (j % (count - i));
		/* Swap these 2 characters. */
		temp = string[i];
		string[i] = string[j];
		string[j] = temp;
	}
	return string;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsndup)(char16_t const *__restrict string,
                                   size_t max_chars) {
	size_t resultsize = libd_wcsnlen(string, max_chars) * sizeof(char16_t);
	char16_t *result = (char16_t *)libc_malloc(resultsize + sizeof(char16_t));
	if likely(result) {
		*(char16_t *)libc_mempcpy(result, string, resultsize) = '\0';
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsndup)(char32_t const *__restrict string,
                                   size_t max_chars) {
	size_t resultsize = libc_wcsnlen(string, max_chars) * sizeof(char32_t);
	char32_t *result = (char32_t *)libc_malloc(resultsize + sizeof(char32_t));
	if likely(result) {
		*(char32_t *)libc_mempcpy(result, string, resultsize) = '\0';
	}
	return result;
}
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsrchrnul)(char16_t const *__restrict haystack,
                                      char16_t needle) {
	char16_t const *result = haystack - 1;
	do {
		if unlikely((char16_t)*haystack == (char16_t)needle)
			result = haystack;
	} while (*haystack++);
	return (char16_t *)result;
}
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsrchrnul)(char32_t const *__restrict haystack,
                                      char32_t needle) {
	char32_t const *result = haystack - 1;
	do {
		if unlikely((char32_t)*haystack == (char32_t)needle)
			result = haystack;
	} while (*haystack++);
	return (char32_t *)result;
}
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnchrnul)(char16_t const *__restrict haystack,
                                      char16_t needle,
                                      size_t maxlen) {
	for (; maxlen-- && *haystack && (char16_t)*haystack != (char16_t)needle; ++haystack)
		;
	return (char16_t *)haystack;
}
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnchrnul)(char32_t const *__restrict haystack,
                                      char32_t needle,
                                      size_t maxlen) {
	for (; maxlen-- && *haystack && (char32_t)*haystack != (char32_t)needle; ++haystack)
		;
	return (char32_t *)haystack;
}
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnrchrnul)(char16_t const *__restrict haystack,
                                       char16_t needle,
                                       size_t maxlen) {
	char16_t const *result = haystack - 1;
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((char16_t)*haystack == (char16_t)needle)
			result = haystack;
	}
	return (char16_t *)result;
}
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnrchrnul)(char32_t const *__restrict haystack,
                                       char32_t needle,
                                       size_t maxlen) {
	char32_t const *result = haystack - 1;
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((char32_t)*haystack == (char32_t)needle)
			result = haystack;
	}
	return (char32_t *)result;
}
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsoff)(char16_t const *__restrict haystack,
                                  char16_t needle) {
	return (size_t)(libd_wcschrnul(haystack, needle) - haystack);
}
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsoff)(char32_t const *__restrict haystack,
                                  char32_t needle) {
	return (size_t)(libc_wcschrnul(haystack, needle) - haystack);
}
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsroff)(char16_t const *__restrict haystack,
                                   char16_t needle) {
	return (size_t)(libd_wcsrchrnul(haystack, needle) - haystack);
}
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsroff)(char32_t const *__restrict haystack,
                                   char32_t needle) {
	return (size_t)(libc_wcsrchrnul(haystack, needle) - haystack);
}
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsnoff)(char16_t const *__restrict haystack,
                                   char16_t needle,
                                   size_t maxlen) {
	return (size_t)(libd_wcsnchrnul(haystack, needle, maxlen) - haystack);
}
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsnoff)(char32_t const *__restrict haystack,
                                   char32_t needle,
                                   size_t maxlen) {
	return (size_t)(libc_wcsnchrnul(haystack, needle, maxlen) - haystack);
}
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsnroff)(char16_t const *__restrict haystack,
                                    char16_t needle,
                                    size_t maxlen) {
	return (size_t)(libd_wcsnrchrnul(haystack, needle, maxlen) - haystack);
}
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsnroff)(char32_t const *__restrict haystack,
                                    char32_t needle,
                                    size_t maxlen) {
	return (size_t)(libc_wcsnrchrnul(haystack, needle, maxlen) - haystack);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscmp)(char16_t const *s1,
                                        char16_t const *s2) {
	return libc_fuzzy_memcmpw(s1, libd_wcslen(s1), s2, libd_wcslen(s2));
}
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wcscmp)(char32_t const *s1,
                                        char32_t const *s2) {
	return libc_fuzzy_memcmpl(s1, libc_wcslen(s1), s2, libc_wcslen(s2));
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncmp)(char16_t const *s1,
                                         size_t s1_maxlen,
                                         char16_t const *s2,
                                         size_t s2_maxlen) {
	return libc_fuzzy_memcmpw(s1, libd_wcsnlen(s1, s1_maxlen), s2, libd_wcsnlen(s2, s2_maxlen));
}
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wcsncmp)(char32_t const *s1,
                                         size_t s1_maxlen,
                                         char32_t const *s2,
                                         size_t s2_maxlen) {
	return libc_fuzzy_memcmpl(s1, libc_wcsnlen(s1, s1_maxlen), s2, libc_wcsnlen(s2, s2_maxlen));
}
#include <parts/malloca.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wmemcasecmp)(char16_t const *s1,
                                             size_t s1_bytes,
                                             char16_t const *s2,
                                             size_t s2_bytes) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{
			void const *temp;
			temp = (void const *)s1;
			s1   = s2;
			*(void const **)&s2 = temp;
		}
		{
			size_t temp;
			temp     = s1_bytes;
			s1_bytes = s2_bytes;
			s2_bytes = temp;
		}
	}
	__malloca_tryhard(v0, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0)
		return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_bytes; ++i)
		v0[i] = i;
	for (i = 0; i < s1_bytes; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_bytes; j++) {
			byte_t c1 = ((byte_t *)s1)[i];
			byte_t c2 = ((byte_t *)s2)[j];
			cost  = c1 != c2 && (char16_t)libc_towlower(c1) != (char16_t)libc_towlower(c2);
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		libc_memcpyc((u8 *)v0, (u8 *)v1, s2_bytes, sizeof(size_t));
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}
#include <parts/malloca.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wmemcasecmp)(char32_t const *s1,
                                             size_t s1_bytes,
                                             char32_t const *s2,
                                             size_t s2_bytes) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{
			void const *temp;
			temp = (void const *)s1;
			s1   = s2;
			*(void const **)&s2 = temp;
		}
		{
			size_t temp;
			temp     = s1_bytes;
			s1_bytes = s2_bytes;
			s2_bytes = temp;
		}
	}
	__malloca_tryhard(v0, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0)
		return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_bytes; ++i)
		v0[i] = i;
	for (i = 0; i < s1_bytes; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_bytes; j++) {
			byte_t c1 = ((byte_t *)s1)[i];
			byte_t c2 = ((byte_t *)s2)[j];
			cost  = c1 != c2 && (char32_t)libc_towlower(c1) != (char32_t)libc_towlower(c2);
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		libc_memcpyc((u8 *)v0, (u8 *)v1, s2_bytes, sizeof(size_t));
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscasecmp)(char16_t const *s1,
                                            char16_t const *s2) {
	return libd_fuzzy_wmemcasecmp(s1, libd_wcslen(s1), s2, libd_wcslen(s2));
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wcscasecmp)(char32_t const *s1,
                                            char32_t const *s2) {
	return libc_fuzzy_wmemcasecmp(s1, libc_wcslen(s1), s2, libc_wcslen(s2));
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncasecmp)(char16_t const *s1,
                                             size_t s1_maxlen,
                                             char16_t const *s2,
                                             size_t s2_maxlen) {
	return libd_fuzzy_wmemcasecmp(s1, libd_wcsnlen(s1, s1_maxlen), s2, libd_wcsnlen(s2, s2_maxlen));
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wcsncasecmp)(char32_t const *s1,
                                             size_t s1_maxlen,
                                             char32_t const *s2,
                                             size_t s2_maxlen) {
	return libc_fuzzy_wmemcasecmp(s1, libc_wcsnlen(s1, s1_maxlen), s2, libc_wcsnlen(s2, s2_maxlen));
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wildwcscmp)(char16_t const *pattern,
                                      char16_t const *string) {
	char16_t card_post;
	for (;;) {
		if (!*string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*')
				++pattern;
			return -(int)(char16_t)*pattern;
		}
		if (!*pattern)
			return (int)(char16_t)*string; /* Pattern end doesn't match */
		if (*pattern == '*') {
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			for (;;) {
				char16_t ch = *string++;
				if (ch == card_post) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libd_wildwcscmp(string, pattern))
						return 0;
				} else if (!ch) {
					return -(int)(char16_t)card_post; /* Wildcard suffix not found */
				}
			}
		}
		if (*pattern == *string || *pattern == '?') {
next:
			++string;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((char16_t)*string - (char16_t)*pattern);
}
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wildwcscmp)(char32_t const *pattern,
                                      char32_t const *string) {
	char32_t card_post;
	for (;;) {
		if (!*string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*')
				++pattern;
			return -(int)(char32_t)*pattern;
		}
		if (!*pattern)
			return (int)(char32_t)*string; /* Pattern end doesn't match */
		if (*pattern == '*') {
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			for (;;) {
				char32_t ch = *string++;
				if (ch == card_post) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libc_wildwcscmp(string, pattern))
						return 0;
				} else if (!ch) {
					return -(int)(char32_t)card_post; /* Wildcard suffix not found */
				}
			}
		}
		if (*pattern == *string || *pattern == '?') {
next:
			++string;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((char32_t)*string - (char32_t)*pattern);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wildwcscasecmp)(char16_t const *pattern,
                                          char16_t const *string) {
	char16_t card_post, pattern_ch, wcsing_ch;
	for (;;) {
		if (!*string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*') ++pattern;
			return -(int)*pattern;
		}
		if (!*pattern)
			return (int)*string; /* Pattern end doesn't match */
		if (*pattern == '*') {
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			card_post = (char16_t)libc_towlower(card_post);
			for (;;) {
				char16_t ch = *string++;
				if (card_post == ch || card_post == (char16_t)libc_towlower(ch)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libd_wildwcscasecmp(string, pattern))
						return 0;
				} else if (!ch) {
					return -(int)(char16_t)card_post; /* Wildcard suffix not found */
				}
			}
		}
		pattern_ch = *pattern;
		wcsing_ch = *string;
		if (pattern_ch == wcsing_ch || pattern_ch == '?' ||
		   (pattern_ch = (char16_t)libc_towlower(pattern_ch),
		    wcsing_ch = (char16_t)libc_towlower(wcsing_ch),
		    pattern_ch == wcsing_ch)) {
next:
			++string;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((char16_t)wcsing_ch - (char16_t)pattern_ch);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wildwcscasecmp)(char32_t const *pattern,
                                          char32_t const *string) {
	char32_t card_post, pattern_ch, wcsing_ch;
	for (;;) {
		if (!*string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*') ++pattern;
			return -(int)*pattern;
		}
		if (!*pattern)
			return (int)*string; /* Pattern end doesn't match */
		if (*pattern == '*') {
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			card_post = (char32_t)libc_towlower(card_post);
			for (;;) {
				char32_t ch = *string++;
				if (card_post == ch || card_post == (char32_t)libc_towlower(ch)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libc_wildwcscasecmp(string, pattern))
						return 0;
				} else if (!ch) {
					return -(int)(char32_t)card_post; /* Wildcard suffix not found */
				}
			}
		}
		pattern_ch = *pattern;
		wcsing_ch = *string;
		if (pattern_ch == wcsing_ch || pattern_ch == '?' ||
		   (pattern_ch = (char32_t)libc_towlower(pattern_ch),
		    wcsing_ch = (char32_t)libc_towlower(wcsing_ch),
		    pattern_ch == wcsing_ch)) {
next:
			++string;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((char32_t)wcsing_ch - (char32_t)pattern_ch);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsverscmp)(char16_t const *s1,
                                      char16_t const *s2) {
	char16_t const *s1_start = s1;
	char16_t c1, c2;
	do {
		if ((c1 = *s1) != (c2 = *s2)) {
			unsigned int vala, valb;
			/* Unwind common digits. */
			while (s1 != s1_start) {
				if (s1[-1] < '0' || s1[-1] > '9')
					break;
				c2 = c1 = *--s1, --s2;
			}
			/* Check if both strings have digit sequences in the same places. */
			if ((c1 < '0' || c1 > '9') &&
			    (c2 < '0' || c2 > '9'))
				return (int)((char16_t)c1 - (char16_t)c2);
			/* Deal with leading zeros. */
			if (c1 == '0')
				return -1;
			if (c2 == '0')
				return 1;
			/* Compare digits. */
			vala = c1 - '0';
			valb = c2 - '0';
			for (;;) {
				c1 = *s1++;
				if (c1 < '0' || c1 > '9')
					break;
				vala *= 10;
				vala += c1-'0';
			}
			for (;;) {
				c2 = *s2++;
				if (c2 < '0' || c2 > '9')
					break;
				valb *= 10;
				valb += c2-'0';
			}
			return (int)vala - (int)valb;
		}
		++s1, ++s2;
	} while (c1);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsverscmp)(char32_t const *s1,
                                      char32_t const *s2) {
	char32_t const *s1_start = s1;
	char32_t c1, c2;
	do {
		if ((c1 = *s1) != (c2 = *s2)) {
			unsigned int vala, valb;
			/* Unwind common digits. */
			while (s1 != s1_start) {
				if (s1[-1] < '0' || s1[-1] > '9')
					break;
				c2 = c1 = *--s1, --s2;
			}
			/* Check if both strings have digit sequences in the same places. */
			if ((c1 < '0' || c1 > '9') &&
			    (c2 < '0' || c2 > '9'))
				return (int)((char32_t)c1 - (char32_t)c2);
			/* Deal with leading zeros. */
			if (c1 == '0')
				return -1;
			if (c2 == '0')
				return 1;
			/* Compare digits. */
			vala = c1 - '0';
			valb = c2 - '0';
			for (;;) {
				c1 = *s1++;
				if (c1 < '0' || c1 > '9')
					break;
				vala *= 10;
				vala += c1-'0';
			}
			for (;;) {
				c2 = *s2++;
				if (c2 < '0' || c2 > '9')
					break;
				valb *= 10;
				valb += c2-'0';
			}
			return (int)vala - (int)valb;
		}
		++s1, ++s2;
	} while (c1);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsncoll_l)(char16_t const *s1,
                                      char16_t const *s2,
                                      size_t maxlen,
                                      locale_t locale) {
	(void)locale;
	return libd_wcsncoll(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsncoll_l)(char32_t const *s1,
                                      char32_t const *s2,
                                      size_t maxlen,
                                      locale_t locale) {
	(void)locale;
	return libc_wcsncoll(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcscasecoll_l)(char16_t const *s1,
                                         char16_t const *s2,
                                         locale_t locale) {
	return libd_wcscasecmp_l(s1, s2, locale);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcscasecoll_l)(char32_t const *s1,
                                         char32_t const *s2,
                                         locale_t locale) {
	return libc_wcscasecmp_l(s1, s2, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsncasecoll_l)(char16_t const *s1,
                                          char16_t const *s2,
                                          size_t maxlen,
                                          locale_t locale) {
	(void)locale;
	return libd_wcsncasecoll(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsncasecoll_l)(char32_t const *s1,
                                          char32_t const *s2,
                                          size_t maxlen,
                                          locale_t locale) {
	(void)locale;
	return libc_wcsncasecoll(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcslwr_l)(char16_t *__restrict str,
                                    locale_t locale) {
	char16_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towlower_l(ch, locale);
	return str;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcslwr_l)(char32_t *__restrict str,
                                    locale_t locale) {
	char32_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower_l(ch, locale);
	return str;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsupr_l)(char16_t *__restrict str,
                                    locale_t locale) {
	char16_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towupper_l(ch, locale);
	return str;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsupr_l)(char32_t *__restrict str,
                                    locale_t locale) {
	char32_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper_l(ch, locale);
	return str;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnlwr_l)(char16_t *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
	char16_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towlower_l(ch, locale);
	return str;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnlwr_l)(char32_t *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
	char32_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower_l(ch, locale);
	return str;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnupr_l)(char16_t *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
	char16_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towupper_l(ch, locale);
	return str;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnupr_l)(char32_t *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
	char32_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper_l(ch, locale);
	return str;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcscasestr_l)(char16_t const *haystack,
                                        char16_t const *needle,
                                        locale_t locale) {
	for (; *haystack; ++haystack) {
		if (libd_wcscasecmp_l(haystack, needle, locale) == 0)
			return (char16_t *)haystack;
	}
	return NULL;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcscasestr_l)(char32_t const *haystack,
                                        char32_t const *needle,
                                        locale_t locale) {
	for (; *haystack; ++haystack) {
		if (libc_wcscasecmp_l(haystack, needle, locale) == 0)
			return (char32_t *)haystack;
	}
	return NULL;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wmemcasecmp_l)(char16_t const *s1,
                                               size_t s1_bytes,
                                               char16_t const *s2,
                                               size_t s2_bytes,
                                               locale_t locale) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{
			void const *temp;
			temp = (void const *)s1;
			s1   = s2;
			*(void const **)&s2 = temp;
		}
		{
			size_t temp;
			temp     = s1_bytes;
			s1_bytes = s2_bytes;
			s2_bytes = temp;
		}
	}
	__malloca_tryhard(v0, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0)
		return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_bytes; ++i)
		v0[i] = i;
	for (i = 0; i < s1_bytes; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_bytes; j++) {
			byte_t c1 = ((byte_t *)s1)[i];
			byte_t c2 = ((byte_t *)s2)[j];
			cost  = c1 != c2 && (char16_t)libc_towlower_l(c1, locale) != (char16_t)libc_towlower_l(c2, locale);
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		libc_memcpyc((u8 *)v0, (u8 *)v1, s2_bytes, sizeof(size_t));
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wmemcasecmp_l)(char32_t const *s1,
                                               size_t s1_bytes,
                                               char32_t const *s2,
                                               size_t s2_bytes,
                                               locale_t locale) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{
			void const *temp;
			temp = (void const *)s1;
			s1   = s2;
			*(void const **)&s2 = temp;
		}
		{
			size_t temp;
			temp     = s1_bytes;
			s1_bytes = s2_bytes;
			s2_bytes = temp;
		}
	}
	__malloca_tryhard(v0, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0)
		return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_bytes; ++i)
		v0[i] = i;
	for (i = 0; i < s1_bytes; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_bytes; j++) {
			byte_t c1 = ((byte_t *)s1)[i];
			byte_t c2 = ((byte_t *)s2)[j];
			cost  = c1 != c2 && (char32_t)libc_towlower_l(c1, locale) != (char32_t)libc_towlower_l(c2, locale);
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		libc_memcpyc((u8 *)v0, (u8 *)v1, s2_bytes, sizeof(size_t));
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscasecmp_l)(char16_t const *s1,
                                              char16_t const *s2,
                                              locale_t locale) {
	return libd_fuzzy_wmemcasecmp_l(s1, libd_wcslen(s1), s2, libd_wcslen(s2), locale);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wcscasecmp_l)(char32_t const *s1,
                                              char32_t const *s2,
                                              locale_t locale) {
	return libc_fuzzy_wmemcasecmp_l(s1, libc_wcslen(s1), s2, libc_wcslen(s2), locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncasecmp_l)(char16_t const *s1,
                                               size_t s1_maxlen,
                                               char16_t const *s2,
                                               size_t s2_maxlen,
                                               locale_t locale) {
	return libd_fuzzy_wmemcasecmp_l(s1, libd_wcsnlen(s1, s1_maxlen), s2, libd_wcsnlen(s2, s2_maxlen), locale);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wcsncasecmp_l)(char32_t const *s1,
                                               size_t s1_maxlen,
                                               char32_t const *s2,
                                               size_t s2_maxlen,
                                               locale_t locale) {
	return libc_fuzzy_wmemcasecmp_l(s1, libc_wcsnlen(s1, s1_maxlen), s2, libc_wcsnlen(s2, s2_maxlen), locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wildwcscasecmp_l)(char16_t const *pattern,
                                            char16_t const *string,
                                            locale_t locale) {
	char16_t card_post, pattern_ch, wcsing_ch;
	for (;;) {
		if (!*string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*') ++pattern;
			return -(int)*pattern;
		}
		if (!*pattern)
			return (int)*string; /* Pattern end doesn't match */
		if (*pattern == '*') {
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			card_post = (char16_t)libc_towlower_l(card_post, locale);
			for (;;) {
				char16_t ch = *string++;
				if (card_post == ch || card_post == (char16_t)libc_towlower_l(ch, locale)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libd_wcscasecmp_l(string, pattern, locale))
						return 0;
				} else if (!ch) {
					return -(int)(char16_t)card_post; /* Wildcard suffix not found */
				}
			}
		}
		pattern_ch = *pattern;
		wcsing_ch = *string;
		if (pattern_ch == wcsing_ch || pattern_ch == '?' ||
		   (pattern_ch = (char16_t)libc_towlower_l(pattern_ch, locale),
		    wcsing_ch = (char16_t)libc_towlower_l(wcsing_ch, locale),
		    pattern_ch == wcsing_ch)) {
next:
			++string;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((char16_t)wcsing_ch - (char16_t)pattern_ch);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wildwcscasecmp_l)(char32_t const *pattern,
                                            char32_t const *string,
                                            locale_t locale) {
	char32_t card_post, pattern_ch, wcsing_ch;
	for (;;) {
		if (!*string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*') ++pattern;
			return -(int)*pattern;
		}
		if (!*pattern)
			return (int)*string; /* Pattern end doesn't match */
		if (*pattern == '*') {
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			card_post = (char32_t)libc_towlower_l(card_post, locale);
			for (;;) {
				char32_t ch = *string++;
				if (card_post == ch || card_post == (char32_t)libc_towlower_l(ch, locale)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libc_wcscasecmp_l(string, pattern, locale))
						return 0;
				} else if (!ch) {
					return -(int)(char32_t)card_post; /* Wildcard suffix not found */
				}
			}
		}
		pattern_ch = *pattern;
		wcsing_ch = *string;
		if (pattern_ch == wcsing_ch || pattern_ch == '?' ||
		   (pattern_ch = (char32_t)libc_towlower_l(pattern_ch, locale),
		    wcsing_ch = (char32_t)libc_towlower_l(wcsing_ch, locale),
		    pattern_ch == wcsing_ch)) {
next:
			++string;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((char32_t)wcsing_ch - (char32_t)pattern_ch);
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") errno_t
NOTHROW_NCX(LIBDCALL libd_wcscat_s)(char16_t *dst,
                                    size_t dstsize,
                                    char16_t const *src) {
	if (!dst || !src)
		return __EINVAL;
	while (dstsize && *dst) {
		++dst;
		--dstsize;
	}
	if (!dstsize)
		return __EINVAL;
	while ((*dst++ = *src++) != 0 && --dstsize)
		;
	if (!dstsize)
		return __ERANGE;
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") errno_t
NOTHROW_NCX(LIBKCALL libc_wcscat_s)(char32_t *dst,
                                    size_t dstsize,
                                    char32_t const *src) {
	if (!dst || !src)
		return __EINVAL;
	while (dstsize && *dst) {
		++dst;
		--dstsize;
	}
	if (!dstsize)
		return __EINVAL;
	while ((*dst++ = *src++) != 0 && --dstsize)
		;
	if (!dstsize)
		return __ERANGE;
	return 0;
}
#include <parts/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") errno_t
NOTHROW_NCX(LIBDCALL libd_wcscpy_s)(char16_t *dst,
                                    size_t dstsize,
                                    char16_t const *src) {
	char16_t *iter;
	size_t remaining;
	if ((!dst && dstsize) || !src)
		return __EINVAL;
	iter = dst;
	remaining = dstsize;
	while ((*iter++ = *src++) != 0 && --remaining)
		;
	if (!remaining) {
		__libc_memsetc(dst, 0, dstsize, 2);
		return __ERANGE;
	}
	__libc_memsetc(iter, 0, remaining, 2);
	return 0;
}
#include <parts/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") errno_t
NOTHROW_NCX(LIBKCALL libc_wcscpy_s)(char32_t *dst,
                                    size_t dstsize,
                                    char32_t const *src) {
	char32_t *iter;
	size_t remaining;
	if ((!dst && dstsize) || !src)
		return __EINVAL;
	iter = dst;
	remaining = dstsize;
	while ((*iter++ = *src++) != 0 && --remaining)
		;
	if (!remaining) {
		__libc_memsetc(dst, 0, dstsize, 4);
		return __ERANGE;
	}
	__libc_memsetc(iter, 0, remaining, 4);
	return 0;
}
#include <parts/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") errno_t
NOTHROW_NCX(LIBDCALL libd_wcsncat_s)(char16_t *dst,
                                     rsize_t dstsize,
                                     const char16_t *src,
                                     rsize_t maxlen) {
	char16_t *iter;
	size_t remaining;
	if (!maxlen && !dst && !dstsize)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return __EINVAL;
	for (iter = dst, remaining = dstsize; remaining && *iter; ++iter, --remaining)
		;
	if (!remaining) {
		__libc_memsetc(dst, 0, dstsize, 2);
		return __EINVAL;
	}
	if (maxlen == (size_t)-1) {
		while ((*iter++ = *src++) != 0 && --dstsize)
			;
	} else {
		if (maxlen >= remaining)
			return __ERANGE;
		while (maxlen && (*iter++ = *src++) != 0 && --remaining)
			--maxlen;
		if (!maxlen)
			*iter = 0;
	}
	if (!remaining) {
		if (maxlen == (size_t)-1) {
			dst[dstsize - 1] = 0;
			return __STRUNCATE;
		}
		__libc_memsetc(dst, 0, dstsize, 2);
		return __ERANGE;
	}
	__libc_memsetc(iter, 0, remaining, 2);
	return 0;
}
#include <parts/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") errno_t
NOTHROW_NCX(LIBKCALL libc_wcsncat_s)(char32_t *dst,
                                     rsize_t dstsize,
                                     const char32_t *src,
                                     rsize_t maxlen) {
	char32_t *iter;
	size_t remaining;
	if (!maxlen && !dst && !dstsize)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return __EINVAL;
	for (iter = dst, remaining = dstsize; remaining && *iter; ++iter, --remaining)
		;
	if (!remaining) {
		__libc_memsetc(dst, 0, dstsize, 4);
		return __EINVAL;
	}
	if (maxlen == (size_t)-1) {
		while ((*iter++ = *src++) != 0 && --dstsize)
			;
	} else {
		if (maxlen >= remaining)
			return __ERANGE;
		while (maxlen && (*iter++ = *src++) != 0 && --remaining)
			--maxlen;
		if (!maxlen)
			*iter = 0;
	}
	if (!remaining) {
		if (maxlen == (size_t)-1) {
			dst[dstsize - 1] = 0;
			return __STRUNCATE;
		}
		__libc_memsetc(dst, 0, dstsize, 4);
		return __ERANGE;
	}
	__libc_memsetc(iter, 0, remaining, 4);
	return 0;
}
#include <parts/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") errno_t
NOTHROW_NCX(LIBDCALL libd_wcsncpy_s)(char16_t *dst,
                                     size_t dstsize,
                                     char16_t const *src,
                                     size_t maxlen) {
	char16_t *iter;
	size_t remaining;
	if (maxlen == 0 && dst == NULL && dstsize == 0)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return __EINVAL;
	if (!maxlen) {
		__libc_memsetc(dst, 0, dstsize, 2);
		return 0;
	}
	iter = dst;
	remaining = dstsize;
	if (maxlen == (size_t)-1) {
		while ((*iter++ = *src++) != 0 && --remaining)
			;
	} else {
		if (maxlen >= remaining)
			return __ERANGE;
		while ((*iter++ = *src++) != 0 && --remaining && --maxlen)
			;
		if (!maxlen)
			*iter = 0;
	}
	if (!remaining) {
		if (maxlen == (size_t)-1) {
			dst[dstsize - 1] = 0;
			return __STRUNCATE;
		}
		__libc_memsetc(dst, 0, dstsize, 2);
		return __ERANGE;
	}
	__libc_memsetc(iter, 0, remaining, 2);
	return 0;
}
#include <parts/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") errno_t
NOTHROW_NCX(LIBKCALL libc_wcsncpy_s)(char32_t *dst,
                                     size_t dstsize,
                                     char32_t const *src,
                                     size_t maxlen) {
	char32_t *iter;
	size_t remaining;
	if (maxlen == 0 && dst == NULL && dstsize == 0)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return __EINVAL;
	if (!maxlen) {
		__libc_memsetc(dst, 0, dstsize, 4);
		return 0;
	}
	iter = dst;
	remaining = dstsize;
	if (maxlen == (size_t)-1) {
		while ((*iter++ = *src++) != 0 && --remaining)
			;
	} else {
		if (maxlen >= remaining)
			return __ERANGE;
		while ((*iter++ = *src++) != 0 && --remaining && --maxlen)
			;
		if (!maxlen)
			*iter = 0;
	}
	if (!remaining) {
		if (maxlen == (size_t)-1) {
			dst[dstsize - 1] = 0;
			return __STRUNCATE;
		}
		__libc_memsetc(dst, 0, dstsize, 4);
		return __ERANGE;
	}
	__libc_memsetc(iter, 0, remaining, 4);
	return 0;
}
#include <parts/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") errno_t
NOTHROW_NCX(LIBDCALL libd__wcsnset_s)(char16_t *__restrict buf,
                                      size_t buflen,
                                      char16_t ch,
                                      size_t maxlen) {
	char16_t *iter;
	size_t remaining;
	if (maxlen == 0 && buf == NULL && buflen == 0)
		return 0;
	if (!buf && buflen)
		return __EINVAL;
	if (maxlen >= buflen)
		return __ERANGE;
	iter = buf;
	remaining = buflen;
	while (*iter != 0 && maxlen && --remaining) {
		*iter++ = (char16_t)ch;
		--maxlen;
	}
	if (!maxlen) {
		while (*iter && --remaining)
			++iter;
	}
	if (!remaining) {
		__libc_memsetc(buf, 0, buflen, 2);
		return __EINVAL;
	}
	__libc_memsetc(iter, 0, remaining, 2);
	return 0;
}
#include <parts/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") errno_t
NOTHROW_NCX(LIBKCALL libc__wcsnset_s)(char32_t *__restrict buf,
                                      size_t buflen,
                                      char32_t ch,
                                      size_t maxlen) {
	char32_t *iter;
	size_t remaining;
	if (maxlen == 0 && buf == NULL && buflen == 0)
		return 0;
	if (!buf && buflen)
		return __EINVAL;
	if (maxlen >= buflen)
		return __ERANGE;
	iter = buf;
	remaining = buflen;
	while (*iter != 0 && maxlen && --remaining) {
		*iter++ = (char32_t)ch;
		--maxlen;
	}
	if (!maxlen) {
		while (*iter && --remaining)
			++iter;
	}
	if (!remaining) {
		__libc_memsetc(buf, 0, buflen, 4);
		return __EINVAL;
	}
	__libc_memsetc(iter, 0, remaining, 4);
	return 0;
}
#include <parts/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBDCALL libd__wcsset_s)(char16_t *dst,
                                     size_t dstsize,
                                     char16_t ch) {
	char16_t *p;
	size_t remaining;
	if (!dst && dstsize != 0)
		return __EINVAL;
	p = dst;
	remaining = dstsize;
	while (*p && --remaining != 0)
		*p++ = (char16_t)ch;
	if (remaining == 0) {
		__libc_memsetc(dst, 0, dstsize, 2);
		return __EINVAL;
	}
	__libc_memsetc(p, 0, remaining, 2);
	return 0;
}
#include <parts/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBKCALL libc__wcsset_s)(char32_t *dst,
                                     size_t dstsize,
                                     char32_t ch) {
	char32_t *p;
	size_t remaining;
	if (!dst && dstsize != 0)
		return __EINVAL;
	p = dst;
	remaining = dstsize;
	while (*p && --remaining != 0)
		*p++ = (char32_t)ch;
	if (remaining == 0) {
		__libc_memsetc(dst, 0, dstsize, 4);
		return __EINVAL;
	}
	__libc_memsetc(p, 0, remaining, 4);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") errno_t
NOTHROW_NCX(LIBDCALL libd__wcslwr_s)(char16_t *buf,
                                     size_t buflen) {
	char16_t *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libd_wcsnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towlower(ch);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") errno_t
NOTHROW_NCX(LIBKCALL libc__wcslwr_s)(char32_t *buf,
                                     size_t buflen) {
	char32_t *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libc_wcsnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower(ch);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") errno_t
NOTHROW_NCX(LIBDCALL libd__wcsupr_s)(char16_t *buf,
                                     size_t buflen) {
	char16_t *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libd_wcsnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towupper(ch);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") errno_t
NOTHROW_NCX(LIBKCALL libc__wcsupr_s)(char32_t *buf,
                                     size_t buflen) {
	char32_t *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libc_wcsnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper(ch);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") errno_t
NOTHROW_NCX(LIBDCALL libd__wcslwr_s_l)(char16_t *buf,
                                       size_t buflen,
                                       locale_t locale) {
	char16_t *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libd_wcsnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towlower_l(ch, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") errno_t
NOTHROW_NCX(LIBKCALL libc__wcslwr_s_l)(char32_t *buf,
                                       size_t buflen,
                                       locale_t locale) {
	char32_t *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libc_wcsnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower_l(ch, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") errno_t
NOTHROW_NCX(LIBDCALL libd__wcsupr_s_l)(char16_t *buf,
                                       size_t buflen,
                                       locale_t locale) {
	char16_t *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libd_wcsnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towupper_l(ch, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") errno_t
NOTHROW_NCX(LIBKCALL libc__wcsupr_s_l)(char32_t *buf,
                                       size_t buflen,
                                       locale_t locale) {
	char32_t *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libc_wcsnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper_l(ch, locale);
	return 0;
}
#include <parts/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBDCALL libd_wmemcpy_s)(char16_t *dst,
                                     rsize_t dstlength,
                                     char16_t const *src,
                                     rsize_t srclength) {
	if (!srclength)
		return 0;
	if (dst == NULL)
		return __EINVAL;
	if (!src || dstlength < srclength) {
		__libc_memsetc(dst, 0, dstlength, 2);
		if (!src)
			return __EINVAL;
		if (dstlength < srclength)
			return __ERANGE;
		return __EINVAL;
	}
	__libc_memcpyc(dst, src, srclength, 2);
	return 0;
}
#include <parts/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBKCALL libc_wmemcpy_s)(char32_t *dst,
                                     rsize_t dstlength,
                                     char32_t const *src,
                                     rsize_t srclength) {
	if (!srclength)
		return 0;
	if (dst == NULL)
		return __EINVAL;
	if (!src || dstlength < srclength) {
		__libc_memsetc(dst, 0, dstlength, 4);
		if (!src)
			return __EINVAL;
		if (dstlength < srclength)
			return __ERANGE;
		return __EINVAL;
	}
	__libc_memcpyc(dst, src, srclength, 4);
	return 0;
}
#include <parts/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBDCALL libd_wmemmove_s)(char16_t *dst,
                                      rsize_t dstlength,
                                      char16_t const *src,
                                      rsize_t srclength) {
	if (!srclength)
		return 0;
	if (!dst || !src)
		return __EINVAL;
	if (dstlength < srclength)
		return __ERANGE;
	__libc_memmovec(dst, src, srclength, 2);
	return 0;
}
#include <parts/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBKCALL libc_wmemmove_s)(char32_t *dst,
                                      rsize_t dstlength,
                                      char32_t const *src,
                                      rsize_t srclength) {
	if (!srclength)
		return 0;
	if (!dst || !src)
		return __EINVAL;
	if (dstlength < srclength)
		return __ERANGE;
	__libc_memmovec(dst, src, srclength, 4);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnset)(char16_t *__restrict str,
                                   char16_t ch,
                                   size_t maxlen) {
	char16_t *iter;
	for (iter = str; maxlen-- && *iter; ++iter)
		*iter = (char16_t)ch;
	return str;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnset)(char32_t *__restrict str,
                                   char32_t ch,
                                   size_t maxlen) {
	char32_t *iter;
	for (iter = str; maxlen-- && *iter; ++iter)
		*iter = (char32_t)ch;
	return str;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsrev)(char16_t *__restrict str) {

	return (char16_t *)libc_memrevw(str, libd_wcslen(str));





}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsrev)(char32_t *__restrict str) {



	return (char32_t *)libc_memrevl(str, libc_wcslen(str));



}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsset)(char16_t *__restrict str,
                                  int ch) {
	char16_t *iter;
	for (iter = str; *iter; ++iter)
		*iter = (char16_t)ch;
	return str;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsset)(char32_t *__restrict str,
                                  int ch) {
	char32_t *iter;
	for (iter = str; *iter; ++iter)
		*iter = (char32_t)ch;
	return str;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcslwr)(char16_t *__restrict str) {
	char16_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towlower(ch);
	return str;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcslwr)(char32_t *__restrict str) {
	char32_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower(ch);
	return str;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsupr)(char16_t *__restrict str) {
	char16_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towupper(ch);
	return str;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsupr)(char32_t *__restrict str) {
	char32_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper(ch);
	return str;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vscwprintf)(char16_t const *format,
                                       va_list args) {
	return libd_vswprintf(NULL, 0, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vscwprintf)(char32_t const *format,
                                       va_list args) {
	return libc_vswprintf(NULL, 0, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__scwprintf)(char16_t const *format,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd__vscwprintf(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__scwprintf)(char32_t const *format,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vscwprintf(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vscwprintf_p)(char16_t const *format,
                                         va_list args) {
	/* TODO */
	(void)format;
	(void)args;
	COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vscwprintf_p)(char32_t const *format,
                                         va_list args) {
	/* TODO */
	(void)format;
	(void)args;
	COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__scwprintf_p)(char16_t const *format,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd__vscwprintf_p(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__scwprintf_p)(char32_t const *format,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vscwprintf_p(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vscwprintf_l)(char16_t const *format,
                                         locale_t locale,
                                         va_list args) {
	(void)locale;
	return libd__vscwprintf(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vscwprintf_l)(char32_t const *format,
                                         locale_t locale,
                                         va_list args) {
	(void)locale;
	return libc__vscwprintf(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__scwprintf_l)(char16_t const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vscwprintf_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__scwprintf_l)(char32_t const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vscwprintf_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vscwprintf_p_l)(char16_t const *format,
                                           locale_t locale,
                                           va_list args) {
	(void)locale;
	return libd__vscwprintf_p(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vscwprintf_p_l)(char32_t const *format,
                                           locale_t locale,
                                           va_list args) {
	(void)locale;
	return libc__vscwprintf_p(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__scwprintf_p_l)(char16_t const *format,
                                           locale_t locale,
                                           ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vscwprintf_p_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__scwprintf_p_l)(char32_t const *format,
                                           locale_t locale,
                                           ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vscwprintf_p_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnwprintf_s)(char16_t *buf,
                                         size_t bufsize,
                                         size_t buflen,
                                         char16_t const *format,
                                         va_list args) {
	(void)buflen;
	return libd_vswprintf(buf, bufsize, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vsnwprintf_s)(char32_t *buf,
                                         size_t bufsize,
                                         size_t buflen,
                                         char32_t const *format,
                                         va_list args) {
	(void)buflen;
	return libc_vswprintf(buf, bufsize, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snwprintf_s)(char16_t *buf,
                                         size_t bufsize,
                                         size_t buflen,
                                         char16_t const *format,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd__vsnwprintf_s(buf, bufsize, buflen, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__snwprintf_s)(char32_t *buf,
                                         size_t bufsize,
                                         size_t buflen,
                                         char32_t const *format,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnwprintf_s(buf, bufsize, buflen, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(LIBDCALL libd__vfwprintf_p)(FILE *stream,
                             char16_t const *format,
                             va_list args) THROWS(...) {
	/* TODO */
	(void)stream;
	(void)format;
	(void)args;
	COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(LIBKCALL libc__vfwprintf_p)(FILE *stream,
                             char32_t const *format,
                             va_list args) THROWS(...) {
	/* TODO */
	(void)stream;
	(void)format;
	(void)args;
	COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(VLIBDCALL libd__fwprintf_p)(FILE *stream,
                             char16_t const *format,
                             ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd__vfwprintf_p(stream, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(VLIBKCALL libc__fwprintf_p)(FILE *stream,
                             char32_t const *format,
                             ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vfwprintf_p(stream, format, args);
	va_end(args);
	return result;
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBDCALL libd__vwprintf_p)(char16_t const *format,
                            va_list args) THROWS(...) {
	return libd__vfwprintf_p(stdout, format, args);
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBKCALL libc__vwprintf_p)(char32_t const *format,
                            va_list args) THROWS(...) {
	return libc__vfwprintf_p(stdout, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(VLIBDCALL libd__wprintf_p)(char16_t const *format,
                            ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd__vwprintf_p(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(VLIBKCALL libc__wprintf_p)(char32_t const *format,
                            ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vwprintf_p(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vswprintf_p)(char16_t *buf,
                                        size_t bufsize,
                                        char16_t const *format,
                                        va_list args) {
	/* TODO */
	(void)buf;
	(void)bufsize;
	(void)format;
	(void)args;
	COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vswprintf_p)(char32_t *buf,
                                        size_t bufsize,
                                        char32_t const *format,
                                        va_list args) {
	/* TODO */
	(void)buf;
	(void)bufsize;
	(void)format;
	(void)args;
	COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__swprintf_p)(char16_t *dst,
                                        size_t bufsize,
                                        char16_t const *format,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd__vswprintf_p(dst, bufsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__swprintf_p)(char32_t *dst,
                                        size_t bufsize,
                                        char32_t const *format,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vswprintf_p(dst, bufsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBDCALL libd__vwprintf_l)(char16_t const *format,
                            locale_t locale,
                            va_list args) THROWS(...) {
	(void)locale;
	return libd_vwprintf(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBKCALL libc__vwprintf_l)(char32_t const *format,
                            locale_t locale,
                            va_list args) THROWS(...) {
	(void)locale;
	return libc_vwprintf(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(VLIBDCALL libd__wprintf_l)(char16_t const *format,
                            locale_t locale,
                            ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vwprintf_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(VLIBKCALL libc__wprintf_l)(char32_t const *format,
                            locale_t locale,
                            ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vwprintf_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBDCALL libd__vwprintf_p_l)(char16_t const *format,
                              locale_t locale,
                              va_list args) THROWS(...) {
	(void)locale;
	return libd__vwprintf_p(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBKCALL libc__vwprintf_p_l)(char32_t const *format,
                              locale_t locale,
                              va_list args) THROWS(...) {
	(void)locale;
	return libc__vwprintf_p(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(VLIBDCALL libd__wprintf_p_l)(char16_t const *format,
                              locale_t locale,
                              ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vwprintf_p_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(VLIBKCALL libc__wprintf_p_l)(char32_t const *format,
                              locale_t locale,
                              ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vwprintf_p_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBDCALL libd__vwprintf_s_l)(char16_t const *format,
                              locale_t locale,
                              va_list args) THROWS(...) {
	(void)locale;
	return libd_vwprintf(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBKCALL libc__vwprintf_s_l)(char32_t const *format,
                              locale_t locale,
                              va_list args) THROWS(...) {
	(void)locale;
	return libc_vwprintf(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(VLIBDCALL libd__wprintf_s_l)(char16_t const *format,
                              locale_t locale,
                              ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vwprintf_s_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1)) __STDC_INT_AS_SSIZE_T
(VLIBKCALL libc__wprintf_s_l)(char32_t const *format,
                              locale_t locale,
                              ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vwprintf_s_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(LIBDCALL libd__vfwprintf_l)(FILE *stream,
                             char16_t const *format,
                             locale_t locale,
                             va_list args) THROWS(...) {
	(void)locale;
	return libd_vfwprintf(stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(LIBKCALL libc__vfwprintf_l)(FILE *stream,
                             char32_t const *format,
                             locale_t locale,
                             va_list args) THROWS(...) {
	(void)locale;
	return libc_vfwprintf(stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(VLIBDCALL libd__fwprintf_l)(FILE *stream,
                             char16_t const *format,
                             locale_t locale,
                             ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vfwprintf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(VLIBKCALL libc__fwprintf_l)(FILE *stream,
                             char32_t const *format,
                             locale_t locale,
                             ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfwprintf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(LIBDCALL libd__vfwprintf_p_l)(FILE *stream,
                               char16_t const *format,
                               locale_t locale,
                               va_list args) THROWS(...) {
	(void)locale;
	return libd__vfwprintf_p(stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(LIBKCALL libc__vfwprintf_p_l)(FILE *stream,
                               char32_t const *format,
                               locale_t locale,
                               va_list args) THROWS(...) {
	(void)locale;
	return libc__vfwprintf_p(stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(VLIBDCALL libd__fwprintf_p_l)(FILE *stream,
                               char16_t const *format,
                               locale_t locale,
                               ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vfwprintf_p_l(stream, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(VLIBKCALL libc__fwprintf_p_l)(FILE *stream,
                               char32_t const *format,
                               locale_t locale,
                               ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfwprintf_p_l(stream, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(LIBDCALL libd__vfwprintf_s_l)(FILE *stream,
                               char16_t const *format,
                               locale_t locale,
                               va_list args) THROWS(...) {
	(void)locale;
	return libd_vfwprintf(stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(LIBKCALL libc__vfwprintf_s_l)(FILE *stream,
                               char32_t const *format,
                               locale_t locale,
                               va_list args) THROWS(...) {
	(void)locale;
	return libc_vfwprintf(stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(VLIBDCALL libd__fwprintf_s_l)(FILE *stream,
                               char16_t const *format,
                               locale_t locale,
                               ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vfwprintf_s_l(stream, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(VLIBKCALL libc__fwprintf_s_l)(FILE *stream,
                               char32_t const *format,
                               locale_t locale,
                               ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfwprintf_s_l(stream, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vswprintf_c_l)(char16_t *dst,
                                          size_t bufsize,
                                          char16_t const *format,
                                          locale_t locale,
                                          va_list args) {
	(void)locale;
	return libd_vswprintf(dst, bufsize, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vswprintf_c_l)(char32_t *dst,
                                          size_t bufsize,
                                          char32_t const *format,
                                          locale_t locale,
                                          va_list args) {
	(void)locale;
	return libc_vswprintf(dst, bufsize, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__swprintf_c_l)(char16_t *dst,
                                          size_t bufsize,
                                          char16_t const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vswprintf_c_l(dst, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__swprintf_c_l)(char32_t *dst,
                                          size_t bufsize,
                                          char32_t const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vswprintf_c_l(dst, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vswprintf_p_l)(char16_t *dst,
                                          size_t bufsize,
                                          char16_t const *format,
                                          locale_t locale,
                                          va_list args) {
	(void)locale;
	return libd__vswprintf_p(dst, bufsize, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vswprintf_p_l)(char32_t *dst,
                                          size_t bufsize,
                                          char32_t const *format,
                                          locale_t locale,
                                          va_list args) {
	(void)locale;
	return libc__vswprintf_p(dst, bufsize, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__swprintf_p_l)(char16_t *dst,
                                          size_t bufsize,
                                          char16_t const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vswprintf_p_l(dst, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__swprintf_p_l)(char32_t *dst,
                                          size_t bufsize,
                                          char32_t const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vswprintf_p_l(dst, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vswprintf_s_l)(char16_t *dst,
                                          size_t wchar_count,
                                          char16_t const *format,
                                          locale_t locale,
                                          va_list args) {
	(void)locale;
	return libd_vswprintf(dst, wchar_count, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vswprintf_s_l)(char32_t *dst,
                                          size_t wchar_count,
                                          char32_t const *format,
                                          locale_t locale,
                                          va_list args) {
	(void)locale;
	return libc_vswprintf(dst, wchar_count, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__swprintf_s_l)(char16_t *dst,
                                          size_t wchar_count,
                                          char16_t const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vswprintf_s_l(dst, wchar_count, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__swprintf_s_l)(char32_t *dst,
                                          size_t wchar_count,
                                          char32_t const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vswprintf_s_l(dst, wchar_count, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnwprintf_l)(char16_t *dst,
                                         size_t bufsize,
                                         char16_t const *format,
                                         locale_t locale,
                                         va_list args) {
	(void)locale;
	return libd_vswprintf(dst, bufsize, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vsnwprintf_l)(char32_t *dst,
                                         size_t bufsize,
                                         char32_t const *format,
                                         locale_t locale,
                                         va_list args) {
	(void)locale;
	return libc_vswprintf(dst, bufsize, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snwprintf_l)(char16_t *dst,
                                         size_t bufsize,
                                         char16_t const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vsnwprintf_l(dst, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__snwprintf_l)(char32_t *dst,
                                         size_t bufsize,
                                         char32_t const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnwprintf_l(dst, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnwprintf_s_l)(char16_t *dst,
                                           size_t wchar_count,
                                           size_t bufsize,
                                           char16_t const *format,
                                           locale_t locale,
                                           va_list args) {
	(void)locale;
	return libd__vsnwprintf_s(dst, wchar_count, bufsize, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vsnwprintf_s_l)(char32_t *dst,
                                           size_t wchar_count,
                                           size_t bufsize,
                                           char32_t const *format,
                                           locale_t locale,
                                           va_list args) {
	(void)locale;
	return libc__vsnwprintf_s(dst, wchar_count, bufsize, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snwprintf_s_l)(char16_t *dst,
                                           size_t wchar_count,
                                           size_t bufsize,
                                           char16_t const *format,
                                           locale_t locale,
                                           ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vsnwprintf_s_l(dst, wchar_count, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") NONNULL((1, 4)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__snwprintf_s_l)(char32_t *dst,
                                           size_t wchar_count,
                                           size_t bufsize,
                                           char32_t const *format,
                                           locale_t locale,
                                           ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnwprintf_s_l(dst, wchar_count, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(LIBDCALL libd__vfwscanf_l)(FILE *stream,
                            char16_t const *format,
                            locale_t locale,
                            va_list args) THROWS(...) {
	(void)locale;
	return libd_vfwscanf(stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(LIBKCALL libc__vfwscanf_l)(FILE *stream,
                            char32_t const *format,
                            locale_t locale,
                            va_list args) THROWS(...) {
	(void)locale;
	return libc_vfwscanf(stream, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(VLIBDCALL libd__fwscanf_l)(FILE *stream,
                            char16_t const *format,
                            locale_t locale,
                            ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vfwscanf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
(VLIBKCALL libc__fwscanf_l)(FILE *stream,
                            char32_t const *format,
                            locale_t locale,
                            ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vfwscanf_l(stream, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vswscanf_l)(char16_t const *src,
                                       char16_t const *format,
                                       locale_t locale,
                                       va_list args) {
	(void)locale;
	return libd_vswscanf(src, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vswscanf_l)(char32_t const *src,
                                       char32_t const *format,
                                       locale_t locale,
                                       va_list args) {
	(void)locale;
	return libc_vswscanf(src, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__swscanf_l)(char16_t const *src,
                                       char16_t const *format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vswscanf_l(src, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__swscanf_l)(char32_t const *src,
                                       char32_t const *format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vswscanf_l(src, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnwscanf)(char16_t const *src,
                                      size_t bufsize,
                                      char16_t const *format,
                                      va_list args) {
	/* TODO */
	(void)src;
	(void)bufsize;
	(void)format;
	(void)args;
	COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vsnwscanf)(char32_t const *src,
                                      size_t bufsize,
                                      char32_t const *format,
                                      va_list args) {
	/* TODO */
	(void)src;
	(void)bufsize;
	(void)format;
	(void)args;
	COMPILER_IMPURE();
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snwscanf)(char16_t const *src,
                                      size_t bufsize,
                                      char16_t const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd__vsnwscanf(src, bufsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__snwscanf)(char32_t const *src,
                                      size_t bufsize,
                                      char32_t const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vsnwscanf(src, bufsize, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnwscanf_l)(char16_t const *src,
                                        size_t bufsize,
                                        char16_t const *format,
                                        locale_t locale,
                                        va_list args) {
	(void)locale;
	return libd__vsnwscanf(src, bufsize, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vsnwscanf_l)(char32_t const *src,
                                        size_t bufsize,
                                        char32_t const *format,
                                        locale_t locale,
                                        va_list args) {
	(void)locale;
	return libc__vsnwscanf(src, bufsize, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snwscanf_l)(char16_t const *src,
                                        size_t bufsize,
                                        char16_t const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vsnwscanf_l(src, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__snwscanf_l)(char32_t const *src,
                                        size_t bufsize,
                                        char32_t const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnwscanf_l(src, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vsnwscanf_s_l)(char16_t const *src,
                                          size_t bufsize,
                                          char16_t const *format,
                                          locale_t locale,
                                          va_list args) {
	(void)locale;
	return libd__vsnwscanf(src, bufsize, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vsnwscanf_s_l)(char32_t const *src,
                                          size_t bufsize,
                                          char32_t const *format,
                                          locale_t locale,
                                          va_list args) {
	(void)locale;
	return libc__vsnwscanf(src, bufsize, format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__snwscanf_s_l)(char16_t const *src,
                                          size_t bufsize,
                                          char16_t const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vsnwscanf_s_l(src, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__snwscanf_s_l)(char32_t const *src,
                                          size_t bufsize,
                                          char32_t const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vsnwscanf_s_l(src, bufsize, format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBDCALL libd__vwscanf_l)(char16_t const *format,
                           locale_t locale,
                           va_list args) THROWS(...) {
	(void)locale;
	return libd_vwscanf(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
(LIBKCALL libc__vwscanf_l)(char32_t const *format,
                           locale_t locale,
                           va_list args) THROWS(...) {
	(void)locale;
	return libc_vwscanf(format, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
(VLIBDCALL libd__wscanf_l)(char16_t const *format,
                           locale_t locale,
                           ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vwscanf_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED NONNULL((1)) __STDC_INT_AS_SSIZE_T
(VLIBKCALL libc__wscanf_l)(char32_t const *format,
                           locale_t locale,
                           ...) THROWS(...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vwscanf_l(format, locale, args);
	va_end(args);
	return result;
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.read") char16_t *
NOTHROW_NCX(LIBDCALL libd__getws_s)(char16_t *buf,
                                    size_t buflen) {
	return libd_fgetws(buf, buflen, stdin);
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.read") char32_t *
NOTHROW_NCX(LIBKCALL libc__getws_s)(char32_t *buf,
                                    size_t buflen) {
	return libc_fgetws(buf, buflen, stdin);
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.write") NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd__putws)(char16_t const *string) {
	return libd_fputws(string, stdout);
}
#include <local/stdstreams.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.write") NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBKCALL libc__putws)(char32_t const *string) {
	return libc_fputws(string, stdout);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$btowc, libd_btowc);
DEFINE_PUBLIC_ALIAS(btowc, libc_btowc);
DEFINE_PUBLIC_ALIAS(wctob, libc_wctob);
DEFINE_PUBLIC_ALIAS(DOS$__mbrtowc, libd_mbrtowc);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(mbrtoc16, libd_mbrtowc);
#endif /* __LIBCCALL_IS_LIBDCALL */
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(DOS$mbrtoc16, libd_mbrtowc);
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(DOS$mbrtowc, libd_mbrtowc);
DEFINE_PUBLIC_ALIAS(__mbrtowc, libc_mbrtowc);
DEFINE_PUBLIC_ALIAS(mbrtoc32, libc_mbrtowc);
DEFINE_PUBLIC_ALIAS(mbrtowc, libc_mbrtowc);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(c16rtomb, libd_wcrtomb);
#endif /* __LIBCCALL_IS_LIBDCALL */
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(DOS$c16rtomb, libd_wcrtomb);
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(DOS$wcrtomb, libd_wcrtomb);
DEFINE_PUBLIC_ALIAS(c32rtomb, libc_wcrtomb);
DEFINE_PUBLIC_ALIAS(wcrtomb, libc_wcrtomb);
DEFINE_PUBLIC_ALIAS(DOS$__mbrlen, libd_mbrlen);
DEFINE_PUBLIC_ALIAS(DOS$mbrlen, libd_mbrlen);
DEFINE_PUBLIC_ALIAS(__mbrlen, libc_mbrlen);
DEFINE_PUBLIC_ALIAS(mbrlen, libc_mbrlen);
DEFINE_PUBLIC_ALIAS(DOS$mbsrtowcs, libd_mbsrtowcs);
DEFINE_PUBLIC_ALIAS(mbsrtowcs, libc_mbsrtowcs);
DEFINE_PUBLIC_ALIAS(DOS$wcsrtombs, libd_wcsrtombs);
DEFINE_PUBLIC_ALIAS(wcsrtombs, libc_wcsrtombs);
DEFINE_PUBLIC_ALIAS(DOS$wcstol, libd_wcstol);
DEFINE_PUBLIC_ALIAS(wcstol, libc_wcstol);
DEFINE_PUBLIC_ALIAS(DOS$wcstoul, libd_wcstoul);
DEFINE_PUBLIC_ALIAS(wcstoul, libc_wcstoul);
DEFINE_PUBLIC_ALIAS(mbsinit, libc_mbsinit);
DEFINE_PUBLIC_ALIAS(DOS$wcscpy, libd_wcscpy);
DEFINE_PUBLIC_ALIAS(wcscpy, libc_wcscpy);
DEFINE_PUBLIC_ALIAS(DOS$wcscat, libd_wcscat);
DEFINE_PUBLIC_ALIAS(wcscat, libc_wcscat);
DEFINE_PUBLIC_ALIAS(DOS$wcsncat, libd_wcsncat);
DEFINE_PUBLIC_ALIAS(wcsncat, libc_wcsncat);
DEFINE_PUBLIC_ALIAS(DOS$wcsncpy, libd_wcsncpy);
DEFINE_PUBLIC_ALIAS(wcsncpy, libc_wcsncpy);
DEFINE_PUBLIC_ALIAS(DOS$wcscmp, libd_wcscmp);
DEFINE_PUBLIC_ALIAS(wcscmp, libc_wcscmp);
DEFINE_PUBLIC_ALIAS(DOS$wcsncmp, libd_wcsncmp);
DEFINE_PUBLIC_ALIAS(wcsncmp, libc_wcsncmp);
DEFINE_PUBLIC_ALIAS(DOS$wcscoll, libd_wcscoll);
DEFINE_PUBLIC_ALIAS(wcscoll, libc_wcscoll);
DEFINE_PUBLIC_ALIAS(DOS$wcsxfrm, libd_wcsxfrm);
DEFINE_PUBLIC_ALIAS(wcsxfrm, libc_wcsxfrm);
DEFINE_PUBLIC_ALIAS(DOS$_fgetwchar, libd_getwchar);
DEFINE_PUBLIC_ALIAS(DOS$getwchar, libd_getwchar);
DEFINE_PUBLIC_ALIAS(getwchar, libc_getwchar);
DEFINE_PUBLIC_ALIAS(DOS$_fputwchar, libd_putwchar);
DEFINE_PUBLIC_ALIAS(DOS$putwchar, libd_putwchar);
DEFINE_PUBLIC_ALIAS(putwchar, libc_putwchar);
DEFINE_PUBLIC_ALIAS(DOS$fgetws, libd_fgetws);
DEFINE_PUBLIC_ALIAS(fgetws, libc_fgetws);
DEFINE_PUBLIC_ALIAS(DOS$fputws, libd_fputws);
DEFINE_PUBLIC_ALIAS(fputws, libc_fputws);
DEFINE_PUBLIC_ALIAS(DOS$wcsftime, libd_wcsftime);
DEFINE_PUBLIC_ALIAS(wcsftime, libc_wcsftime);
DEFINE_PUBLIC_ALIAS(DOS$wcstok_s, libd_wcstok);
DEFINE_PUBLIC_ALIAS(wcstok, libc_wcstok);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C16SLEN)
DEFINE_PUBLIC_ALIAS(DOS$wcslen, libd_wcslen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C16SLEN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C32SLEN)
DEFINE_PUBLIC_ALIAS(wcslen, libc_wcslen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C32SLEN */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$wcsspn, libd_wcsspn);
DEFINE_PUBLIC_ALIAS(wcsspn, libc_wcsspn);
DEFINE_PUBLIC_ALIAS(DOS$wcscspn, libd_wcscspn);
DEFINE_PUBLIC_ALIAS(wcscspn, libc_wcscspn);
DEFINE_PUBLIC_ALIAS(DOS$wcschr, libd_wcschr);
DEFINE_PUBLIC_ALIAS(wcschr, libc_wcschr);
DEFINE_PUBLIC_ALIAS(DOS$wcsrchr, libd_wcsrchr);
DEFINE_PUBLIC_ALIAS(wcsrchr, libc_wcsrchr);
DEFINE_PUBLIC_ALIAS(DOS$wcspbrk, libd_wcspbrk);
DEFINE_PUBLIC_ALIAS(wcspbrk, libc_wcspbrk);
DEFINE_PUBLIC_ALIAS(DOS$wcswcs, libd_wcsstr);
DEFINE_PUBLIC_ALIAS(DOS$wcsstr, libd_wcsstr);
DEFINE_PUBLIC_ALIAS(wcswcs, libc_wcsstr);
DEFINE_PUBLIC_ALIAS(wcsstr, libc_wcsstr);
DEFINE_PUBLIC_ALIAS(fwide, libc_fwide);
DEFINE_PUBLIC_ALIAS(DOS$fwprintf, libd_fwprintf);
DEFINE_PUBLIC_ALIAS(fwprintf, libc_fwprintf);
DEFINE_PUBLIC_ALIAS(DOS$vfwprintf, libd_vfwprintf);
DEFINE_PUBLIC_ALIAS(vfwprintf, libc_vfwprintf);
DEFINE_PUBLIC_ALIAS(DOS$wprintf, libd_wprintf);
DEFINE_PUBLIC_ALIAS(wprintf, libc_wprintf);
DEFINE_PUBLIC_ALIAS(DOS$vwprintf, libd_vwprintf);
DEFINE_PUBLIC_ALIAS(vwprintf, libc_vwprintf);
DEFINE_PUBLIC_ALIAS(DOS$fwscanf, libd_fwscanf);
DEFINE_PUBLIC_ALIAS(fwscanf, libc_fwscanf);
DEFINE_PUBLIC_ALIAS(DOS$wscanf, libd_wscanf);
DEFINE_PUBLIC_ALIAS(wscanf, libc_wscanf);
DEFINE_PUBLIC_ALIAS(DOS$swscanf, libd_swscanf);
DEFINE_PUBLIC_ALIAS(swscanf, libc_swscanf);
DEFINE_PUBLIC_ALIAS(DOS$vswprintf, libd_vswprintf);
DEFINE_PUBLIC_ALIAS(vswprintf, libc_vswprintf);
DEFINE_PUBLIC_ALIAS(DOS$_swprintf, libd_swprintf);
DEFINE_PUBLIC_ALIAS(DOS$swprintf, libd_swprintf);
DEFINE_PUBLIC_ALIAS(swprintf, libc_swprintf);
DEFINE_PUBLIC_ALIAS(DOS$wcstod, libd_wcstod);
DEFINE_PUBLIC_ALIAS(wcstod, libc_wcstod);
DEFINE_PUBLIC_ALIAS(DOS$wcstof, libd_wcstof);
DEFINE_PUBLIC_ALIAS(wcstof, libc_wcstof);
DEFINE_PUBLIC_ALIAS(DOS$wcstold, libd_wcstold);
DEFINE_PUBLIC_ALIAS(wcstold, libc_wcstold);
DEFINE_PUBLIC_ALIAS(DOS$wcstoq, libd_wcstoll);
DEFINE_PUBLIC_ALIAS(DOS$wcstoll, libd_wcstoll);
DEFINE_PUBLIC_ALIAS(wcstoq, libc_wcstoll);
DEFINE_PUBLIC_ALIAS(wcstoll, libc_wcstoll);
DEFINE_PUBLIC_ALIAS(DOS$wcstouq, libd_wcstoull);
DEFINE_PUBLIC_ALIAS(DOS$wcstoull, libd_wcstoull);
DEFINE_PUBLIC_ALIAS(wcstouq, libc_wcstoull);
DEFINE_PUBLIC_ALIAS(wcstoull, libc_wcstoull);
DEFINE_PUBLIC_ALIAS(DOS$vwscanf, libd_vwscanf);
DEFINE_PUBLIC_ALIAS(vwscanf, libc_vwscanf);
DEFINE_PUBLIC_ALIAS(DOS$vswscanf, libd_vswscanf);
DEFINE_PUBLIC_ALIAS(vswscanf, libc_vswscanf);
DEFINE_PUBLIC_ALIAS(DOS$_wcsicmp, libd_wcscasecmp);
DEFINE_PUBLIC_ALIAS(DOS$wcscasecmp, libd_wcscasecmp);
DEFINE_PUBLIC_ALIAS(wcscasecmp, libc_wcscasecmp);
DEFINE_PUBLIC_ALIAS(DOS$_wcsnicmp, libd_wcsncasecmp);
DEFINE_PUBLIC_ALIAS(DOS$wcsncasecmp, libd_wcsncasecmp);
DEFINE_PUBLIC_ALIAS(wcsncasecmp, libc_wcsncasecmp);
DEFINE_PUBLIC_ALIAS(DOS$_wcsicmp_l, libd_wcscasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcscasecmp_l, libd_wcscasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$wcscasecmp_l, libd_wcscasecmp_l);
DEFINE_PUBLIC_ALIAS(__wcscasecmp_l, libc_wcscasecmp_l);
DEFINE_PUBLIC_ALIAS(wcscasecmp_l, libc_wcscasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcsnicmp_l, libd_wcsncasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcsncasecmp_l, libd_wcsncasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$wcsncasecmp_l, libd_wcsncasecmp_l);
DEFINE_PUBLIC_ALIAS(__wcsncasecmp_l, libc_wcsncasecmp_l);
DEFINE_PUBLIC_ALIAS(wcsncasecmp_l, libc_wcsncasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcscoll_l, libd_wcscoll_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcscoll_l, libd_wcscoll_l);
DEFINE_PUBLIC_ALIAS(DOS$wcscoll_l, libd_wcscoll_l);
DEFINE_PUBLIC_ALIAS(__wcscoll_l, libc_wcscoll_l);
DEFINE_PUBLIC_ALIAS(wcscoll_l, libc_wcscoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcsxfrm_l, libd_wcsxfrm_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcsxfrm_l, libd_wcsxfrm_l);
DEFINE_PUBLIC_ALIAS(DOS$wcsxfrm_l, libd_wcsxfrm_l);
DEFINE_PUBLIC_ALIAS(__wcsxfrm_l, libc_wcsxfrm_l);
DEFINE_PUBLIC_ALIAS(wcsxfrm_l, libc_wcsxfrm_l);
DEFINE_PUBLIC_ALIAS(DOS$wcpcpy, libd_wcpcpy);
DEFINE_PUBLIC_ALIAS(wcpcpy, libc_wcpcpy);
DEFINE_PUBLIC_ALIAS(DOS$wcpncpy, libd_wcpncpy);
DEFINE_PUBLIC_ALIAS(wcpncpy, libc_wcpncpy);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C16SNLEN)
DEFINE_PUBLIC_ALIAS(DOS$wcsnlen, libd_wcsnlen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C16SNLEN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C32SNLEN)
DEFINE_PUBLIC_ALIAS(wcsnlen, libc_wcsnlen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C32SNLEN */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$_wcsdup, libd_wcsdup);
DEFINE_PUBLIC_ALIAS(DOS$wcsdup, libd_wcsdup);
DEFINE_PUBLIC_ALIAS(wcsdup, libc_wcsdup);
DEFINE_PUBLIC_ALIAS(DOS$wcwidth, libd_wcwidth);
DEFINE_PUBLIC_ALIAS(wcwidth, libc_wcwidth);
DEFINE_PUBLIC_ALIAS(DOS$wcswidth, libd_wcswidth);
DEFINE_PUBLIC_ALIAS(wcswidth, libc_wcswidth);
DEFINE_PUBLIC_ALIAS(DOS$wcschrnul, libd_wcschrnul);
DEFINE_PUBLIC_ALIAS(wcschrnul, libc_wcschrnul);
DEFINE_PUBLIC_ALIAS(DOS$_wcstol_l, libd_wcstol_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcstol_l, libd_wcstol_l);
DEFINE_PUBLIC_ALIAS(DOS$wcstol_l, libd_wcstol_l);
DEFINE_PUBLIC_ALIAS(__wcstol_l, libc_wcstol_l);
DEFINE_PUBLIC_ALIAS(wcstol_l, libc_wcstol_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcstoul_l, libd_wcstoul_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcstoul_l, libd_wcstoul_l);
DEFINE_PUBLIC_ALIAS(DOS$wcstoul_l, libd_wcstoul_l);
DEFINE_PUBLIC_ALIAS(__wcstoul_l, libc_wcstoul_l);
DEFINE_PUBLIC_ALIAS(wcstoul_l, libc_wcstoul_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcstoll_l, libd_wcstoll_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcstoll_l, libd_wcstoll_l);
DEFINE_PUBLIC_ALIAS(DOS$wcstoll_l, libd_wcstoll_l);
DEFINE_PUBLIC_ALIAS(__wcstoll_l, libc_wcstoll_l);
DEFINE_PUBLIC_ALIAS(wcstoll_l, libc_wcstoll_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcstoull_l, libd_wcstoull_l);
DEFINE_PUBLIC_ALIAS(DOS$wcstoull_l, libd_wcstoull_l);
DEFINE_PUBLIC_ALIAS(__wcstoull_l, libc_wcstoull_l);
DEFINE_PUBLIC_ALIAS(wcstoull_l, libc_wcstoull_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcstof_l, libd_wcstof_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcstof_l, libd_wcstof_l);
DEFINE_PUBLIC_ALIAS(DOS$wcstof_l, libd_wcstof_l);
DEFINE_PUBLIC_ALIAS(__wcstof_l, libc_wcstof_l);
DEFINE_PUBLIC_ALIAS(wcstof_l, libc_wcstof_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcstod_l, libd_wcstod_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcstod_l, libd_wcstod_l);
DEFINE_PUBLIC_ALIAS(DOS$wcstod_l, libd_wcstod_l);
DEFINE_PUBLIC_ALIAS(__wcstod_l, libc_wcstod_l);
DEFINE_PUBLIC_ALIAS(wcstod_l, libc_wcstod_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcstold_l, libd_wcstold_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcstold_l, libd_wcstold_l);
DEFINE_PUBLIC_ALIAS(DOS$wcstold_l, libd_wcstold_l);
DEFINE_PUBLIC_ALIAS(__wcstold_l, libc_wcstold_l);
DEFINE_PUBLIC_ALIAS(wcstold_l, libc_wcstold_l);
DEFINE_PUBLIC_ALIAS(DOS$getwchar_unlocked, libd_getwchar_unlocked);
DEFINE_PUBLIC_ALIAS(getwchar_unlocked, libc_getwchar_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$putwchar_unlocked, libd_putwchar_unlocked);
DEFINE_PUBLIC_ALIAS(putwchar_unlocked, libc_putwchar_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_fgetws_nolock, libd_fgetws_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fgetws_unlocked, libd_fgetws_unlocked);
DEFINE_PUBLIC_ALIAS(fgetws_unlocked, libc_fgetws_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_fputws_nolock, libd_fputws_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fputws_unlocked, libd_fputws_unlocked);
DEFINE_PUBLIC_ALIAS(fputws_unlocked, libc_fputws_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_wcsftime_l, libd_wcsftime_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcsftime_l, libd_wcsftime_l);
DEFINE_PUBLIC_ALIAS(DOS$wcsftime_l, libd_wcsftime_l);
DEFINE_PUBLIC_ALIAS(__wcsftime_l, libc_wcsftime_l);
DEFINE_PUBLIC_ALIAS(wcsftime_l, libc_wcsftime_l);
DEFINE_PUBLIC_ALIAS(DOS$vfwprintf_unlocked, libd_vfwprintf_unlocked);
DEFINE_PUBLIC_ALIAS(vfwprintf_unlocked, libc_vfwprintf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fwprintf_unlocked, libd_fwprintf_unlocked);
DEFINE_PUBLIC_ALIAS(fwprintf_unlocked, libc_fwprintf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$wprintf_unlocked, libd_wprintf_unlocked);
DEFINE_PUBLIC_ALIAS(wprintf_unlocked, libc_wprintf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$vwprintf_unlocked, libd_vwprintf_unlocked);
DEFINE_PUBLIC_ALIAS(vwprintf_unlocked, libc_vwprintf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$vwscanf_unlocked, libd_vwscanf_unlocked);
DEFINE_PUBLIC_ALIAS(vwscanf_unlocked, libc_vwscanf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fwscanf_unlocked, libd_fwscanf_unlocked);
DEFINE_PUBLIC_ALIAS(fwscanf_unlocked, libc_fwscanf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$wscanf_unlocked, libd_wscanf_unlocked);
DEFINE_PUBLIC_ALIAS(wscanf_unlocked, libc_wscanf_unlocked);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C16SEND)
DEFINE_PUBLIC_ALIAS(DOS$wcsend, libd_wcsend);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C16SEND */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C32SEND)
DEFINE_PUBLIC_ALIAS(wcsend, libc_wcsend);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C32SEND */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C16SNEND)
DEFINE_PUBLIC_ALIAS(DOS$wcsnend, libd_wcsnend);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C16SNEND */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C32SNEND)
DEFINE_PUBLIC_ALIAS(wcsnend, libc_wcsnend);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C32SNEND */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$wcsto32, libd_wcsto32);
DEFINE_PUBLIC_ALIAS(wcsto32, libc_wcsto32);
DEFINE_PUBLIC_ALIAS(DOS$wcstou32, libd_wcstou32);
DEFINE_PUBLIC_ALIAS(wcstou32, libc_wcstou32);
DEFINE_PUBLIC_ALIAS(DOS$_wcstoui64, libd_wcstou64);
DEFINE_PUBLIC_ALIAS(DOS$wcstou64, libd_wcstou64);
DEFINE_PUBLIC_ALIAS(wcstou64, libc_wcstou64);
DEFINE_PUBLIC_ALIAS(DOS$_wcstoi64, libd_wcsto64);
DEFINE_PUBLIC_ALIAS(DOS$wcsto64, libd_wcsto64);
DEFINE_PUBLIC_ALIAS(wcsto64, libc_wcsto64);
DEFINE_PUBLIC_ALIAS(DOS$wcsto32_l, libd_wcsto32_l);
DEFINE_PUBLIC_ALIAS(wcsto32_l, libc_wcsto32_l);
DEFINE_PUBLIC_ALIAS(DOS$wcstou32_l, libd_wcstou32_l);
DEFINE_PUBLIC_ALIAS(wcstou32_l, libc_wcstou32_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcstoi64_l, libd_wcsto64_l);
DEFINE_PUBLIC_ALIAS(DOS$wcsto64_l, libd_wcsto64_l);
DEFINE_PUBLIC_ALIAS(wcsto64_l, libc_wcsto64_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcstoui64_l, libd_wcstou64_l);
DEFINE_PUBLIC_ALIAS(DOS$wcstou64_l, libd_wcstou64_l);
DEFINE_PUBLIC_ALIAS(wcstou64_l, libc_wcstou64_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcsncoll, libd_wcsncoll);
DEFINE_PUBLIC_ALIAS(DOS$wcsncoll, libd_wcsncoll);
DEFINE_PUBLIC_ALIAS(wcsncoll, libc_wcsncoll);
DEFINE_PUBLIC_ALIAS(DOS$_wcsicoll, libd_wcscasecoll);
DEFINE_PUBLIC_ALIAS(DOS$wcscasecoll, libd_wcscasecoll);
DEFINE_PUBLIC_ALIAS(wcscasecoll, libc_wcscasecoll);
DEFINE_PUBLIC_ALIAS(DOS$_wcsnicoll, libd_wcsncasecoll);
DEFINE_PUBLIC_ALIAS(DOS$wcsncasecoll, libd_wcsncasecoll);
DEFINE_PUBLIC_ALIAS(wcsncasecoll, libc_wcsncasecoll);
DEFINE_PUBLIC_ALIAS(DOS$wcsnrev, libd_wcsnrev);
DEFINE_PUBLIC_ALIAS(wcsnrev, libc_wcsnrev);
DEFINE_PUBLIC_ALIAS(DOS$wcsnlwr, libd_wcsnlwr);
DEFINE_PUBLIC_ALIAS(wcsnlwr, libc_wcsnlwr);
DEFINE_PUBLIC_ALIAS(DOS$wcsnupr, libd_wcsnupr);
DEFINE_PUBLIC_ALIAS(wcsnupr, libc_wcsnupr);
DEFINE_PUBLIC_ALIAS(DOS$wcscasestr, libd_wcscasestr);
DEFINE_PUBLIC_ALIAS(wcscasestr, libc_wcscasestr);
DEFINE_PUBLIC_ALIAS(DOS$wcspcpy, libd_wcspcpy);
DEFINE_PUBLIC_ALIAS(wcspcpy, libc_wcspcpy);
DEFINE_PUBLIC_ALIAS(DOS$wcspncpy, libd_wcspncpy);
DEFINE_PUBLIC_ALIAS(wcspncpy, libc_wcspncpy);
DEFINE_PUBLIC_ALIAS(DOS$wcsnchr, libd_wcsnchr);
DEFINE_PUBLIC_ALIAS(wcsnchr, libc_wcsnchr);
DEFINE_PUBLIC_ALIAS(DOS$wcsnrchr, libd_wcsnrchr);
DEFINE_PUBLIC_ALIAS(wcsnrchr, libc_wcsnrchr);
DEFINE_PUBLIC_ALIAS(DOS$wcssep, libd_wcssep);
DEFINE_PUBLIC_ALIAS(wcssep, libc_wcssep);
DEFINE_PUBLIC_ALIAS(DOS$wcsfry, libd_wcsfry);
DEFINE_PUBLIC_ALIAS(wcsfry, libc_wcsfry);
DEFINE_PUBLIC_ALIAS(DOS$wcsndup, libd_wcsndup);
DEFINE_PUBLIC_ALIAS(wcsndup, libc_wcsndup);
DEFINE_PUBLIC_ALIAS(DOS$wcsrchrnul, libd_wcsrchrnul);
DEFINE_PUBLIC_ALIAS(wcsrchrnul, libc_wcsrchrnul);
DEFINE_PUBLIC_ALIAS(DOS$wcsnchrnul, libd_wcsnchrnul);
DEFINE_PUBLIC_ALIAS(wcsnchrnul, libc_wcsnchrnul);
DEFINE_PUBLIC_ALIAS(DOS$wcsnrchrnul, libd_wcsnrchrnul);
DEFINE_PUBLIC_ALIAS(wcsnrchrnul, libc_wcsnrchrnul);
DEFINE_PUBLIC_ALIAS(DOS$wcsoff, libd_wcsoff);
DEFINE_PUBLIC_ALIAS(wcsoff, libc_wcsoff);
DEFINE_PUBLIC_ALIAS(DOS$wcsroff, libd_wcsroff);
DEFINE_PUBLIC_ALIAS(wcsroff, libc_wcsroff);
DEFINE_PUBLIC_ALIAS(DOS$wcsnoff, libd_wcsnoff);
DEFINE_PUBLIC_ALIAS(wcsnoff, libc_wcsnoff);
DEFINE_PUBLIC_ALIAS(DOS$wcsnroff, libd_wcsnroff);
DEFINE_PUBLIC_ALIAS(wcsnroff, libc_wcsnroff);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wcscmp, libd_fuzzy_wcscmp);
DEFINE_PUBLIC_ALIAS(fuzzy_wcscmp, libc_fuzzy_wcscmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wcsncmp, libd_fuzzy_wcsncmp);
DEFINE_PUBLIC_ALIAS(fuzzy_wcsncmp, libc_fuzzy_wcsncmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wmemcasecmp, libd_fuzzy_wmemcasecmp);
DEFINE_PUBLIC_ALIAS(fuzzy_wmemcasecmp, libc_fuzzy_wmemcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wcscasecmp, libd_fuzzy_wcscasecmp);
DEFINE_PUBLIC_ALIAS(fuzzy_wcscasecmp, libc_fuzzy_wcscasecmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wcsncasecmp, libd_fuzzy_wcsncasecmp);
DEFINE_PUBLIC_ALIAS(fuzzy_wcsncasecmp, libc_fuzzy_wcsncasecmp);
DEFINE_PUBLIC_ALIAS(DOS$wildwcscmp, libd_wildwcscmp);
DEFINE_PUBLIC_ALIAS(wildwcscmp, libc_wildwcscmp);
DEFINE_PUBLIC_ALIAS(DOS$wildwcscasecmp, libd_wildwcscasecmp);
DEFINE_PUBLIC_ALIAS(wildwcscasecmp, libc_wildwcscasecmp);
DEFINE_PUBLIC_ALIAS(DOS$wcsverscmp, libd_wcsverscmp);
DEFINE_PUBLIC_ALIAS(wcsverscmp, libc_wcsverscmp);
DEFINE_PUBLIC_ALIAS(DOS$_wcsncoll_l, libd_wcsncoll_l);
DEFINE_PUBLIC_ALIAS(DOS$wcsncoll_l, libd_wcsncoll_l);
DEFINE_PUBLIC_ALIAS(wcsncoll_l, libc_wcsncoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcsicoll_l, libd_wcscasecoll_l);
DEFINE_PUBLIC_ALIAS(DOS$wcscasecoll_l, libd_wcscasecoll_l);
DEFINE_PUBLIC_ALIAS(wcscasecoll_l, libc_wcscasecoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcsnicoll_l, libd_wcsncasecoll_l);
DEFINE_PUBLIC_ALIAS(DOS$wcsncasecoll_l, libd_wcsncasecoll_l);
DEFINE_PUBLIC_ALIAS(wcsncasecoll_l, libc_wcsncasecoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcslwr_l, libd_wcslwr_l);
DEFINE_PUBLIC_ALIAS(DOS$wcslwr_l, libd_wcslwr_l);
DEFINE_PUBLIC_ALIAS(wcslwr_l, libc_wcslwr_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcsupr_l, libd_wcsupr_l);
DEFINE_PUBLIC_ALIAS(DOS$wcsupr_l, libd_wcsupr_l);
DEFINE_PUBLIC_ALIAS(wcsupr_l, libc_wcsupr_l);
DEFINE_PUBLIC_ALIAS(DOS$wcsnlwr_l, libd_wcsnlwr_l);
DEFINE_PUBLIC_ALIAS(wcsnlwr_l, libc_wcsnlwr_l);
DEFINE_PUBLIC_ALIAS(DOS$wcsnupr_l, libd_wcsnupr_l);
DEFINE_PUBLIC_ALIAS(wcsnupr_l, libc_wcsnupr_l);
DEFINE_PUBLIC_ALIAS(DOS$wcscasestr_l, libd_wcscasestr_l);
DEFINE_PUBLIC_ALIAS(wcscasestr_l, libc_wcscasestr_l);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wmemcasecmp_l, libd_fuzzy_wmemcasecmp_l);
DEFINE_PUBLIC_ALIAS(fuzzy_wmemcasecmp_l, libc_fuzzy_wmemcasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wcscasecmp_l, libd_fuzzy_wcscasecmp_l);
DEFINE_PUBLIC_ALIAS(fuzzy_wcscasecmp_l, libc_fuzzy_wcscasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wcsncasecmp_l, libd_fuzzy_wcsncasecmp_l);
DEFINE_PUBLIC_ALIAS(fuzzy_wcsncasecmp_l, libc_fuzzy_wcsncasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$wildwcscasecmp_l, libd_wildwcscasecmp_l);
DEFINE_PUBLIC_ALIAS(wildwcscasecmp_l, libc_wildwcscasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$wcscat_s, libd_wcscat_s);
DEFINE_PUBLIC_ALIAS(wcscat_s, libc_wcscat_s);
DEFINE_PUBLIC_ALIAS(DOS$wcscpy_s, libd_wcscpy_s);
DEFINE_PUBLIC_ALIAS(wcscpy_s, libc_wcscpy_s);
DEFINE_PUBLIC_ALIAS(DOS$wcsncat_s, libd_wcsncat_s);
DEFINE_PUBLIC_ALIAS(wcsncat_s, libc_wcsncat_s);
DEFINE_PUBLIC_ALIAS(DOS$wcsncpy_s, libd_wcsncpy_s);
DEFINE_PUBLIC_ALIAS(wcsncpy_s, libc_wcsncpy_s);
DEFINE_PUBLIC_ALIAS(DOS$_wcsnset_s, libd__wcsnset_s);
DEFINE_PUBLIC_ALIAS(_wcsnset_s, libc__wcsnset_s);
DEFINE_PUBLIC_ALIAS(DOS$_wcsset_s, libd__wcsset_s);
DEFINE_PUBLIC_ALIAS(_wcsset_s, libc__wcsset_s);
DEFINE_PUBLIC_ALIAS(DOS$_wcslwr_s, libd__wcslwr_s);
DEFINE_PUBLIC_ALIAS(_wcslwr_s, libc__wcslwr_s);
DEFINE_PUBLIC_ALIAS(DOS$_wcsupr_s, libd__wcsupr_s);
DEFINE_PUBLIC_ALIAS(_wcsupr_s, libc__wcsupr_s);
DEFINE_PUBLIC_ALIAS(DOS$_wcslwr_s_l, libd__wcslwr_s_l);
DEFINE_PUBLIC_ALIAS(_wcslwr_s_l, libc__wcslwr_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcsupr_s_l, libd__wcsupr_s_l);
DEFINE_PUBLIC_ALIAS(_wcsupr_s_l, libc__wcsupr_s_l);
DEFINE_PUBLIC_ALIAS(DOS$wmemcpy_s, libd_wmemcpy_s);
DEFINE_PUBLIC_ALIAS(wmemcpy_s, libc_wmemcpy_s);
DEFINE_PUBLIC_ALIAS(DOS$wmemmove_s, libd_wmemmove_s);
DEFINE_PUBLIC_ALIAS(wmemmove_s, libc_wmemmove_s);
DEFINE_PUBLIC_ALIAS(DOS$_wcsnset, libd_wcsnset);
DEFINE_PUBLIC_ALIAS(DOS$wcsnset, libd_wcsnset);
DEFINE_PUBLIC_ALIAS(wcsnset, libc_wcsnset);
DEFINE_PUBLIC_ALIAS(DOS$_wcsrev, libd_wcsrev);
DEFINE_PUBLIC_ALIAS(DOS$wcsrev, libd_wcsrev);
DEFINE_PUBLIC_ALIAS(wcsrev, libc_wcsrev);
DEFINE_PUBLIC_ALIAS(DOS$_wcsset, libd_wcsset);
DEFINE_PUBLIC_ALIAS(DOS$wcsset, libd_wcsset);
DEFINE_PUBLIC_ALIAS(wcsset, libc_wcsset);
DEFINE_PUBLIC_ALIAS(DOS$_wcslwr, libd_wcslwr);
DEFINE_PUBLIC_ALIAS(DOS$wcslwr, libd_wcslwr);
DEFINE_PUBLIC_ALIAS(wcslwr, libc_wcslwr);
DEFINE_PUBLIC_ALIAS(DOS$_wcsupr, libd_wcsupr);
DEFINE_PUBLIC_ALIAS(DOS$wcsupr, libd_wcsupr);
DEFINE_PUBLIC_ALIAS(wcsupr, libc_wcsupr);
DEFINE_PUBLIC_ALIAS(DOS$_vscwprintf, libd__vscwprintf);
DEFINE_PUBLIC_ALIAS(_vscwprintf, libc__vscwprintf);
DEFINE_PUBLIC_ALIAS(DOS$_scwprintf, libd__scwprintf);
DEFINE_PUBLIC_ALIAS(_scwprintf, libc__scwprintf);
DEFINE_PUBLIC_ALIAS(DOS$_vscwprintf_p, libd__vscwprintf_p);
DEFINE_PUBLIC_ALIAS(_vscwprintf_p, libc__vscwprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_scwprintf_p, libd__scwprintf_p);
DEFINE_PUBLIC_ALIAS(_scwprintf_p, libc__scwprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_vscwprintf_l, libd__vscwprintf_l);
DEFINE_PUBLIC_ALIAS(_vscwprintf_l, libc__vscwprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_scwprintf_l, libd__scwprintf_l);
DEFINE_PUBLIC_ALIAS(_scwprintf_l, libc__scwprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vscwprintf_p_l, libd__vscwprintf_p_l);
DEFINE_PUBLIC_ALIAS(_vscwprintf_p_l, libc__vscwprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_scwprintf_p_l, libd__scwprintf_p_l);
DEFINE_PUBLIC_ALIAS(_scwprintf_p_l, libc__scwprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnwprintf_s, libd__vsnwprintf_s);
DEFINE_PUBLIC_ALIAS(_vsnwprintf_s, libc__vsnwprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$_snwprintf_s, libd__snwprintf_s);
DEFINE_PUBLIC_ALIAS(_snwprintf_s, libc__snwprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$_vfwprintf_p, libd__vfwprintf_p);
DEFINE_PUBLIC_ALIAS(_vfwprintf_p, libc__vfwprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_fwprintf_p, libd__fwprintf_p);
DEFINE_PUBLIC_ALIAS(_fwprintf_p, libc__fwprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_vwprintf_p, libd__vwprintf_p);
DEFINE_PUBLIC_ALIAS(_vwprintf_p, libc__vwprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_wprintf_p, libd__wprintf_p);
DEFINE_PUBLIC_ALIAS(_wprintf_p, libc__wprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_vswprintf_p, libd__vswprintf_p);
DEFINE_PUBLIC_ALIAS(_vswprintf_p, libc__vswprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_swprintf_p, libd__swprintf_p);
DEFINE_PUBLIC_ALIAS(_swprintf_p, libc__swprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_vwprintf_l, libd__vwprintf_l);
DEFINE_PUBLIC_ALIAS(_vwprintf_l, libc__vwprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_wprintf_l, libd__wprintf_l);
DEFINE_PUBLIC_ALIAS(_wprintf_l, libc__wprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vwprintf_p_l, libd__vwprintf_p_l);
DEFINE_PUBLIC_ALIAS(_vwprintf_p_l, libc__vwprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_wprintf_p_l, libd__wprintf_p_l);
DEFINE_PUBLIC_ALIAS(_wprintf_p_l, libc__wprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_vwprintf_s_l, libd__vwprintf_s_l);
DEFINE_PUBLIC_ALIAS(_vwprintf_s_l, libc__vwprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_wprintf_s_l, libd__wprintf_s_l);
DEFINE_PUBLIC_ALIAS(_wprintf_s_l, libc__wprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfwprintf_l, libd__vfwprintf_l);
DEFINE_PUBLIC_ALIAS(_vfwprintf_l, libc__vfwprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_fwprintf_l, libd__fwprintf_l);
DEFINE_PUBLIC_ALIAS(_fwprintf_l, libc__fwprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfwprintf_p_l, libd__vfwprintf_p_l);
DEFINE_PUBLIC_ALIAS(_vfwprintf_p_l, libc__vfwprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_fwprintf_p_l, libd__fwprintf_p_l);
DEFINE_PUBLIC_ALIAS(_fwprintf_p_l, libc__fwprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfwprintf_s_l, libd__vfwprintf_s_l);
DEFINE_PUBLIC_ALIAS(_vfwprintf_s_l, libc__vfwprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_fwprintf_s_l, libd__fwprintf_s_l);
DEFINE_PUBLIC_ALIAS(_fwprintf_s_l, libc__fwprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vswprintf_c_l, libd__vswprintf_c_l);
DEFINE_PUBLIC_ALIAS(_vswprintf_c_l, libc__vswprintf_c_l);
DEFINE_PUBLIC_ALIAS(DOS$_swprintf_c_l, libd__swprintf_c_l);
DEFINE_PUBLIC_ALIAS(_swprintf_c_l, libc__swprintf_c_l);
DEFINE_PUBLIC_ALIAS(DOS$_vswprintf_p_l, libd__vswprintf_p_l);
DEFINE_PUBLIC_ALIAS(_vswprintf_p_l, libc__vswprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_swprintf_p_l, libd__swprintf_p_l);
DEFINE_PUBLIC_ALIAS(_swprintf_p_l, libc__swprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_vswprintf_s_l, libd__vswprintf_s_l);
DEFINE_PUBLIC_ALIAS(_vswprintf_s_l, libc__vswprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_swprintf_s_l, libd__swprintf_s_l);
DEFINE_PUBLIC_ALIAS(_swprintf_s_l, libc__swprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnwprintf_l, libd__vsnwprintf_l);
DEFINE_PUBLIC_ALIAS(_vsnwprintf_l, libc__vsnwprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_snwprintf_l, libd__snwprintf_l);
DEFINE_PUBLIC_ALIAS(_snwprintf_l, libc__snwprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnwprintf_s_l, libd__vsnwprintf_s_l);
DEFINE_PUBLIC_ALIAS(_vsnwprintf_s_l, libc__vsnwprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_snwprintf_s_l, libd__snwprintf_s_l);
DEFINE_PUBLIC_ALIAS(_snwprintf_s_l, libc__snwprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vfwscanf_l, libd__vfwscanf_l);
DEFINE_PUBLIC_ALIAS(_vfwscanf_l, libc__vfwscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_fwscanf_l, libd__fwscanf_l);
DEFINE_PUBLIC_ALIAS(_fwscanf_l, libc__fwscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vswscanf_l, libd__vswscanf_l);
DEFINE_PUBLIC_ALIAS(_vswscanf_l, libc__vswscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_swscanf_l, libd__swscanf_l);
DEFINE_PUBLIC_ALIAS(_swscanf_l, libc__swscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnwscanf, libd__vsnwscanf);
DEFINE_PUBLIC_ALIAS(_vsnwscanf, libc__vsnwscanf);
DEFINE_PUBLIC_ALIAS(DOS$_snwscanf, libd__snwscanf);
DEFINE_PUBLIC_ALIAS(_snwscanf, libc__snwscanf);
DEFINE_PUBLIC_ALIAS(DOS$_vsnwscanf_l, libd__vsnwscanf_l);
DEFINE_PUBLIC_ALIAS(_vsnwscanf_l, libc__vsnwscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_snwscanf_l, libd__snwscanf_l);
DEFINE_PUBLIC_ALIAS(_snwscanf_l, libc__snwscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vsnwscanf_s_l, libd__vsnwscanf_s_l);
DEFINE_PUBLIC_ALIAS(_vsnwscanf_s_l, libc__vsnwscanf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_snwscanf_s_l, libd__snwscanf_s_l);
DEFINE_PUBLIC_ALIAS(_snwscanf_s_l, libc__snwscanf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vwscanf_l, libd__vwscanf_l);
DEFINE_PUBLIC_ALIAS(_vwscanf_l, libc__vwscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_wscanf_l, libd__wscanf_l);
DEFINE_PUBLIC_ALIAS(_wscanf_l, libc__wscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_getws_s, libd__getws_s);
DEFINE_PUBLIC_ALIAS(_getws_s, libc__getws_s);
DEFINE_PUBLIC_ALIAS(DOS$_putws, libd__putws);
DEFINE_PUBLIC_ALIAS(_putws, libc__putws);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_WCHAR_C */
