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

%[define_ccompat_header("cwchar")]

%[define_replacement(mbstate_t = __mbstate_t)]
%[define_replacement(wchar_t = __WCHAR_TYPE__)]
%[define_replacement(wint_t = __WINT_TYPE__)]
%[define_replacement(WEOF = __WEOF)]
%[define_wchar_replacement(WEOF = __WEOF16, __WEOF32)]
%[define_wchar_replacement(__WEOF = __WEOF16, __WEOF32)]

%[define_replacement(rsize_t  = __SIZE_TYPE__)]

%(auto_source){
#include "../libc/globals.h"
}

%(auto_header){
#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef int errno_t;
#endif /* !__errno_t_defined */
#ifndef __rsize_t_defined
#define __rsize_t_defined 1
typedef size_t rsize_t;
#endif /* !__rsize_t_defined */

}

%{
#include <features.h>

#include <hybrid/limitcore.h> /* __WCHAR_MIN__, __WCHAR_MAX__ */
#include <hybrid/typecore.h>

#include <asm/crt/stdio.h> /* __WEOF */
#include <bits/crt/tm.h>   /* struct tm */
#include <bits/mbstate.h>
#include <kos/anno.h>

#ifdef __USE_KOS
#include <parts/malloca.h>
#endif /* __USE_KOS */

#ifdef __USE_DOS
#include <bits/types.h>
#include <parts/errno.h>
#include <crtdefs.h>
#endif /* __USE_DOS */

__SYSDECL_BEGIN

/* Define `NULL' */
#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

#ifndef WCHAR_MIN
#define WCHAR_MIN __WCHAR_MIN__
#define WCHAR_MAX __WCHAR_MAX__
#endif /* !WCHAR_MIN */

#ifndef WEOF
#define WEOF __WEOF
#endif /* !WEOF */

#ifdef __CC__

#ifndef __std_mbstate_t_defined
#define __std_mbstate_t_defined 1
__NAMESPACE_STD_BEGIN
typedef __mbstate_t mbstate_t;
__NAMESPACE_STD_END
#endif /* !__std_mbstate_t_defined */

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __mbstate_t_defined
#define __mbstate_t_defined 1
__NAMESPACE_STD_USING(mbstate_t)
#endif /* !__mbstate_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

/* Define 'FILE' */
}%(c, ccompat){
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K) || defined(__USE_DOS)
}%{
#ifndef __std_FILE_defined
#define __std_FILE_defined 1
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */
#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __FILE_defined
#define __FILE_defined 1
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */
}%(c, ccompat){
#endif /* __USE_UNIX98 || __USE_XOPEN2K || __USE_DOS */
}%{

/* Define 'wchar_t' */
#ifndef __wchar_t_defined
#define __wchar_t_defined 1
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

__NAMESPACE_STD_BEGIN
#ifndef __std_size_t_defined
#define __std_size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__std_size_t_defined */
#ifndef __std_wint_t_defined
#define __std_wint_t_defined 1
typedef __WINT_TYPE__ wint_t;
#endif /* !__std_wint_t_defined */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __tm_defined
#define __tm_defined 1
__NAMESPACE_STD_USING(tm)
#endif /* !__tm_defined */
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#ifndef __wint_t_defined
#define __wint_t_defined 1
__NAMESPACE_STD_USING(wint_t)
#endif /* !__wint_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

}

%[insert:std]
%[define_replacement(tm = "__NAMESPACE_STD_SYM tm")];



%[default:section(".text.crt{|.dos}.wchar.unicode.static.mbs")];
[[std, wunused, ATTR_CONST, wchar]]
[[decl_include("<hybrid/typecore.h>")]]
wint_t btowc(int ch) {
	if (ch >= 0 && ch <= 0x7f)
		return (wint_t)ch;
@@pp_if __SIZEOF_WCHAR_T__ == 4@@
	return (__CCAST(__WINT_TYPE__)0xffffffffu);
@@pp_else@@
	return (__CCAST(__WINT_TYPE__)0xffff);
@@pp_endif@@
};

%(auto_source)#include <stdio.h>
;

[[std, wunused, ATTR_CONST]]
[[impl_include("<asm/crt/stdio.h>")]]
[[decl_include("<hybrid/typecore.h>")]]
int wctob(wint_t ch) {
	if (ch >= 0 && ch <= 0x7f)
		return (int)ch;
	return EOF;
};


%[declare_user_export("mbrtoc16", "c16rtomb")]
%(auto_source){
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
}

[[std, wchar, export_alias("__mbrtowc")]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("mbrtoc16")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("mbrtoc32")]]
[[decl_include("<bits/mbstate.h>", "<hybrid/typecore.h>")]]
[[impl_include("<parts/errno.h>")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)),  dos_export_as("mbrtoc16")]]
[[if(!defined(__LIBCCALL_IS_LIBDCALL)), dos_export_as("DOS$mbrtoc16")]]
[[kos_export_as("mbrtoc32")]]
size_t mbrtowc([[nullable]] wchar_t *pwc,
               [[inp_opt(maxlen)]] char const *__restrict str, size_t maxlen,
               [[nullable]] mbstate_t *mbs) {
	size_t error;
	if (!mbs) {
		static mbstate_t mbrtowc_ps = __MBSTATE_INIT;
		mbs = &mbrtowc_ps;
	}
	if (!str) {
		mbs->@__word@ = 0;
		return 0;
	}
	if (!maxlen || !*str)
		return 0;
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	error = unicode_c8toc16((char16_t *)pwc, str, maxlen, mbs);
@@pp_else@@
	error = unicode_c8toc32((char32_t *)pwc, str, maxlen, mbs);
@@pp_endif@@
@@pp_ifdef EILSEQ@@
	if (error == (size_t)-1)
		__libc_seterrno(EILSEQ);
@@pp_endif@@
	return error;
};


[[std, wchar]]
[[decl_include("<bits/mbstate.h>", "<hybrid/typecore.h>")]]
[[impl_include("<parts/errno.h>")]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("c16rtomb")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("c32rtomb")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)),  dos_export_as("c16rtomb")]]
[[if(!defined(__LIBCCALL_IS_LIBDCALL)), dos_export_as("DOS$c16rtomb")]]
[[kos_export_as("c32rtomb")]]
size_t wcrtomb(char *__restrict str, wchar_t wc,
               [[nullable]] mbstate_t *mbs) {
	char *endptr;
	size_t result;
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	/* unicode_c16toc8() */
	if (!mbs) {
		static mbstate_t wcrtomb_ps = @__MBSTATE_INIT@;
		mbs = &wcrtomb_ps;
	}
	if (!str) {
		mbs->@__word@ = 0;
		return 1;
	}
	if ((mbs->@__word@ & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_UTF16_LO) {
		/* Complete surrogate */
		char32_t ch32;
		if unlikely(!((u16)wc >= UTF16_LOW_SURROGATE_MIN &&
		              (u16)wc <= UTF16_LOW_SURROGATE_MAX)) {
			/* Expected low surrogate */
@@pp_ifdef EILSEQ@@
			__libc_seterrno(EILSEQ);
@@pp_endif@@
			return (size_t)-1;
		}
		ch32 = ((mbs->@__word@ & 0x000003ff) << 10) +
		       0x10000 + ((u16)wc - 0xdc00);
		mbs->@__word@ = 0;
		endptr = unicode_writeutf8(str, ch32);
	} else if ((u16)wc >= UTF16_HIGH_SURROGATE_MIN &&
	           (u16)wc <= UTF16_HIGH_SURROGATE_MAX) {
		mbs->@__word@ = __MBSTATE_TYPE_UTF16_LO | ((u16)wc - UTF16_HIGH_SURROGATE_MIN);
		return 0;
	} else {
		endptr = unicode_writeutf8(str, (char32_t)(u32)(u16)wc);
	}
@@pp_else@@
	/* unicode_c32toc8() */
	(void)mbs;
	if (!str)
		return 1;
	endptr = unicode_writeutf8(str, (char32_t)wc);
@@pp_endif@@
	result = (size_t)(endptr - str);
	return result;
};

[[std, wchar, wunused, export_alias("__mbrlen")]]
[[decl_include("<bits/mbstate.h>", "<hybrid/typecore.h>")]]
$size_t mbrlen([[inp_opt(maxlen)]] char const *__restrict str, $size_t maxlen,
               [[nullable]] $mbstate_t *mbs) {
	wchar_t wc;
	return mbrtowc(&wc, str, maxlen, mbs);
};

[[std, wchar]]
[[decl_include("<bits/mbstate.h>", "<hybrid/typecore.h>")]]
size_t mbsrtowcs([[outp(dstlen)]] wchar_t *__restrict dst,
                 [[nonnull]] char const **__restrict psrc, size_t dstlen,
                 [[nullable]] mbstate_t *mbs) {
	size_t result = 0;
	char const *src = *psrc;
	while (dstlen) {
		size_t error;
		wchar_t wc;
		error = mbrtowc(&wc, src, (size_t)-1, mbs);
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
};

[[std, wchar]]
[[decl_include("<bits/mbstate.h>", "<hybrid/typecore.h>")]]
size_t wcsrtombs([[outp(dstlen)]] char *dst,
                 [[nonnull]] wchar_t const **__restrict psrc, size_t dstlen,
                 [[nullable]] mbstate_t *mbs) {
	size_t result = 0;
	wchar_t const *src = *psrc;
	while (dstlen) {
		size_t error;
		char buf[UNICODE_UTF8_MAXLEN];
		error = wcrtomb(buf, *src, mbs);
		if (!error)
			break;
		if (error == (size_t)-1)
			return (size_t)-1; /* EILSEQ */
		if (error > dstlen)
			break;
		dst = (char *)mempcpy(dst, buf, error);
		result += error;
		dstlen -= error;
		++src;
	}
	*psrc = src;
	return result;
}

[[std, guard, wchar]]
[[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("wcstoll", "wcstoq")]]
[[if(__SIZEOF_LONG__ == 4), alias("wcsto32")]]
[[if(__SIZEOF_LONG__ == 8), alias("wcsto64", "_wcstoi64")]]
[[if(__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__), alias("wcstoimax")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
wcstol(*) %{generate(str2wcs("strtol"))}

[[std, guard, wchar]]
[[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("wcstoull", "wcstouq")]]
[[if(__SIZEOF_LONG__ == 4), alias("wcstou32")]]
[[if(__SIZEOF_LONG__ == 8), alias("wcstou64", "_wcstoui64")]]
[[if(__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__), alias("wcstoumax")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
wcstoul(*) %{generate(str2wcs("strtoul"))}

[[std, wunused, ATTR_PURE, decl_include("<bits/mbstate.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
[[decl_include("<bits/mbstate.h>")]]
int mbsinit([[nullable]] mbstate_t const *mbs) {
	return !mbs || __MBSTATE_ISINIT(mbs);
}

%[define_wchar_replacement(wmemcmp = memcmpw, memcmpl)]

[[std, wchar, wunused, ATTR_PURE, no_crt_impl]]
[[decl_include("<hybrid/typecore.h>")]]
int wmemcmp([[inp(num_chars)]] wchar_t const *s1,
            [[inp(num_chars)]] wchar_t const *s2,
            size_t num_chars) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return memcmpw(s1, s2, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return memcmpl(s1, s2, num_chars);
@@pp_else@@
	return memcmp(s1, s2, num_chars * sizeof(wchar_t));
@@pp_endif@@
}

%[define_wchar_replacement(wmemcpy = "(char16_t *)memcpyw", "(char32_t *)memcpyl")]

[[std, wchar, nonnull, no_crt_impl]]
[[decl_include("<hybrid/typecore.h>")]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("memcpyw")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("memcpyl")]]
[[if(__SIZEOF_WCHAR_T__ == 2), bind_local_function(memcpyw)]]
[[if(__SIZEOF_WCHAR_T__ == 4), bind_local_function(memcpyl)]]
wchar_t *wmemcpy([[outp(num_chars)]] wchar_t *__restrict dst,
                 [[inp(num_chars)]] wchar_t const *__restrict src,
                 size_t num_chars) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)memcpyw(dst, src, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)memcpyl(dst, src, num_chars);
@@pp_else@@
	return (wchar_t *)memcpyc(dst, src, num_chars, sizeof(wchar_t));
@@pp_endif@@
}

%[define_wchar_replacement(wmemmove = "(char16_t *)memmovew", "(char32_t *)memmovel")]

[[std, wchar, nonnull, no_crt_impl]]
[[decl_include("<hybrid/typecore.h>")]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("memmovew")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("memmovel")]]
[[if(__SIZEOF_WCHAR_T__ == 2), bind_local_function(memmovew)]]
[[if(__SIZEOF_WCHAR_T__ == 4), bind_local_function(memmovel)]]
wchar_t *wmemmove([[outp(num_chars)]] wchar_t *dst,
                  [[inp(num_chars)]] wchar_t const *src,
                  size_t num_chars) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)memmovew(dst, src, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)memmovel(dst, src, num_chars);
@@pp_else@@
	return (wchar_t *)memmove(dst, src, num_chars * sizeof(wchar_t));
@@pp_endif@@
}

%[define_wchar_replacement(wmemset = "(char16_t *)memsetw", "(char32_t *)memsetl")]

[[std, wchar, no_crt_impl]]
[[decl_include("<hybrid/typecore.h>")]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("memsetw")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("memsetl")]]
[[if(__SIZEOF_WCHAR_T__ == 2), bind_local_function(memsetw)]]
[[if(__SIZEOF_WCHAR_T__ == 4), bind_local_function(memsetl)]]
[[nonnull]] wchar_t *wmemset([[outp(num_chars)]] wchar_t *dst,
                             wchar_t filler, size_t num_chars) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)memsetw(dst, (u16)filler, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)memsetl(dst, (u32)filler, num_chars);
@@pp_else@@
	return (wchar_t *)memset(dst, (int)filler, num_chars * sizeof(wchar_t));
@@pp_endif@@
}

[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcscpy([[nonnull]] wchar_t *__restrict buf,
                            [[nonnull]] wchar_t const *__restrict src) {
	return wmemcpy(buf, src, wcslen(src) + 1);
}

[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcscat([[nonnull]] wchar_t *__restrict buf,
                            [[nonnull]] wchar_t const *__restrict src) {
	wmemcpy(wcsend(buf), src, wcslen(src) + 1);
	return buf;
}

[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsncat([[nonnull]] wchar_t *__restrict buf,
                             [[inp(wcsnlen(src, buflen))]] wchar_t const *__restrict src,
                             $size_t buflen) {
	size_t srclen = wcsnlen(src, buflen);
	wchar_t *dst = wcsend(buf);
	wmemcpy(dst, src, srclen);
	dst[srclen] = '\0';
	return buf;
}

[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsncpy([[nonnull]] wchar_t *__restrict buf,
                             [[inp(wcsnlen(src, buflen))]] wchar_t const *__restrict src,
                             $size_t buflen) {
	size_t srclen = wcsnlen(src, buflen);
	wmemcpy(buf, src, srclen);
	wmemset(buf+srclen, '\0', buflen - srclen);
	return buf;
}


[[std, guard, wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
wcscmp(*) %{generate(str2wcs("strcmp"))}

[[std, guard, wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
wcsncmp(*) %{generate(str2wcs("strncmp"))}

[[std, guard, wchar, section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wcscoll(*) %{generate(str2wcs("strcoll"))}

[[std, guard, wchar, section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wcsxfrm(*) %{generate(str2wcs("strxfrm"))}


%[default:section(".text.crt{|.dos}.wchar.FILE.locked.read.getc")]
[[cp_stdio, std, guard, wchar, requires_include("<__crt.h>")]]
[[requires(!defined(__NO_STDSTREAMS) && $has_function(fgetwc))]]
[[impl_include("<local/stdstreams.h>"), dos_export_alias("_fgetwchar")]]
[[decl_include("<hybrid/typecore.h>")]]
wint_t getwchar() {
	return fgetwc(stdin);
}

[[cp_stdio, std, guard, wchar, export_alias("getwc")]]
[[decl_include("<hybrid/typecore.h>")]]
wint_t fgetwc([[nonnull]] FILE *__restrict stream);

%[insert:guarded_std_function(getwc = fgetwc)]

[[cp_stdio, std, guard, wchar, requires_include("<__crt.h>")]]
[[requires(!defined(__NO_STDSTREAMS) && $has_function(fputwc))]]
[[impl_include("<local/stdstreams.h>"), dos_export_alias("_fputwchar")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.write.putc")]]
[[decl_include("<hybrid/typecore.h>")]]
wint_t putwchar(wchar_t wc) {
	return fputwc(wc, stdout);
}

[[cp_stdio, std, guard, wchar, export_alias("putwc")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.write.putc")]]
[[decl_include("<hybrid/typecore.h>")]]
wint_t fputwc(wchar_t wc, [[nonnull]] FILE *stream);

%[insert:guarded_std_function(putwc = fputwc)]



[[section(".text.crt{|.dos}.wchar.FILE.locked.read.read")]]
[[cp_stdio, std, guard, wchar, wunused, alias("fgetws_unlocked", "_fgetws_nolock")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("fgetws_unlocked", "_fgetws_nolock")]]
[[requires($has_function(fgetwc) && $has_function(ungetwc) && $has_function(ferror))]]
[[impl_include("<parts/errno.h>", "<asm/crt/stdio.h>")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
wchar_t *fgetws([[outp(bufsize)]] wchar_t *__restrict buf,
                __STDC_INT_AS_SIZE_T bufsize,
                [[nonnull]] FILE *__restrict stream) {
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
@@pp_ifdef ERANGE@@
		__libc_seterrno(ERANGE);
@@pp_endif@@
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		wint_t ch = fgetwc(stream);
		if (ch == WEOF) {
			if (n == 0 || ferror(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = fgetwc(stream);
			if (ch == WEOF) {
				if (n == 0 || ferror(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			ungetwc(ch, stream);
			break;
		}
		buf[n] = (wchar_t)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}



[[requires_function(file_wprinter)]]
[[cp_stdio, std, guard, wchar, alias("fputws_unlocked", "_fputws_nolock")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("fputws_unlocked", "_fputws_nolock")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.write.write")]]
__STDC_INT_AS_SIZE_T fputws([[nonnull]] wchar_t const *__restrict string,
                            [[nonnull]] FILE *__restrict stream) {
	__STDC_INT_AS_SIZE_T result;
	result = file_wprinter(stream, string, wcslen(string));
	return result;
}

[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, alias("ungetwc_unlocked")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.write.putc")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("ungetwc_unlocked")]]
wint_t ungetwc(wint_t wc, [[nonnull]] FILE *stream);

[[std, guard, wchar]]
[[decl_include("<hybrid/typecore.h>", "<bits/crt/tm.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.format.strftime")]]
size_t wcsftime([[outp(min(return, buflen))]] wchar_t *__restrict buf, size_t buflen,
                [[nonnull]] wchar_t const *__restrict format,
                [[nonnull]] struct tm const *__restrict tp) {
	if (buflen)
		*buf = 0;
	/* TODO */
	(void)format;
	(void)tp;
	return 0;
}

%[default:section(".text.crt{|.dos}.wchar.string.memory")]
%(std)
%(std)#if !defined(__USE_DOS) || defined(__USE_ISOC95)
[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, no_crt_self_import, no_crt_self_export]]
[[dos_export_as("DOS$wcstok_s"), kos_export_as("wcstok")]]
[[if(!defined(__CRT_DOS_PRIMARY)), preferred_alias("wcstok")]]
[[if(defined(__CRT_DOS_PRIMARY)), preferred_alias("wcstok_s")]]
wchar_t *wcstok([[nullable]] wchar_t *string,
                [[nonnull]] wchar_t const *__restrict delim,
                [[nonnull]] wchar_t **__restrict save_ptr)
	%{generate(str2wcs("strtok_r"))}
%(std)#endif /* !__USE_DOS || __USE_ISOC95 */

[[std, guard, wchar]]
[[crt_dos_impl_requires(!defined(LIBC_ARCH_HAVE_C16SLEN))]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_C32SLEN))]]
wcslen(*) %{generate(str2wcs("strlen"))}

[[std, guard, wchar]]
wcsspn(*) %{generate(str2wcs("strspn"))}

[[std, guard, wchar]]
wcscspn(*) %{generate(str2wcs("strcspn"))}

[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, wunused, ATTR_PURE]]
wchar_t *wcschr([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle)
	[([[nonnull]] wchar_t *__restrict haystack, wchar_t needle): wchar_t *]
	[([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle): wchar_t const *]
	%{generate(str2wcs("strchr"))}

[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, wunused, ATTR_PURE]]
wchar_t *wcsrchr([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle)
	[([[nonnull]] wchar_t *__restrict haystack, wchar_t needle): wchar_t *]
	[([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle): wchar_t const *]
	%{generate(str2wcs("strrchr"))}

[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, wunused, ATTR_PURE]]
wchar_t *wcspbrk([[nonnull]] wchar_t const *haystack, [[nonnull]] wchar_t const *accept)
	[([[nonnull]] wchar_t *haystack, [[nonnull]] wchar_t const *accept): wchar_t *]
	[([[nonnull]] wchar_t const *haystack, [[nonnull]] wchar_t const *accept): wchar_t const *]
	%{generate(str2wcs("strpbrk"))}

[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, wunused, ATTR_PURE, export_alias("wcswcs")]]
wchar_t *wcsstr([[nonnull]] wchar_t const *haystack, [[nonnull]] wchar_t const *needle)
	[([[nonnull]] wchar_t *haystack, [[nonnull]] wchar_t *needle): wchar_t *]
	[([[nonnull]] wchar_t const *haystack, [[nonnull]] wchar_t const *needle): wchar_t const *]
	%{generate(str2wcs("strstr"))}

%[define_wchar_replacement(wmemchr = "(char16_t *)memchrw", "(char32_t *)memchrl")]

[[decl_include("<hybrid/typecore.h>")]]
[[std, wchar, wunused, ATTR_PURE, no_crt_impl]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("memchrw")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("memchrl")]]
[[if(__SIZEOF_WCHAR_T__ == 2), bind_local_function(memchrw)]]
[[if(__SIZEOF_WCHAR_T__ == 4), bind_local_function(memchrl)]]
wchar_t *wmemchr([[inp(num_chars)]] wchar_t const *__restrict haystack, wchar_t needle, size_t num_chars)
	[([[inp(num_chars)]] wchar_t *__restrict haystack, wchar_t needle, size_t num_chars): wchar_t *]
	[([[inp(num_chars)]] wchar_t const *__restrict haystack, wchar_t needle, size_t num_chars): wchar_t const *]
{
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)memchrw(haystack, needle, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)memchrl(haystack, needle, num_chars);
@@pp_else@@
	return (wchar_t *)memchr(haystack, (int)needle, num_chars * sizeof(wchar_t));
@@pp_endif@@
}

%(std)#if defined(__USE_ISOC95) || defined(__USE_UNIX98)
[[std, guard]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.utility")]]
int fwide([[nonnull]] FILE *fp, int mode) {
	(void)fp;
	(void)mode;
	COMPILER_IMPURE();
	return 0;
}
%(std)#endif /* __USE_ISOC95 || __USE_UNIX98 */

%(std)
%(std)#if defined(__USE_ISOC95) || defined(__USE_UNIX98) || defined(__USE_DOS)

[[cp_stdio, std, guard, wchar, ATTR_LIBC_WPRINTF(2, 3)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.write.printf")]]
__STDC_INT_AS_SIZE_T fwprintf([[nonnull]] FILE *__restrict stream,
                              [[nonnull]] wchar_t const *__restrict format, ...)
	%{printf("vfwprintf")}

[[requires_dependent_function(file_wprinter)]]
[[cp_stdio, std, guard, wchar, ATTR_LIBC_WPRINTF(2, 0)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.write.printf")]]
__STDC_INT_AS_SIZE_T vfwprintf([[nonnull]] FILE *__restrict stream,
                               [[nonnull]] wchar_t const *__restrict format,
                               $va_list args) {
	return (__STDC_INT_AS_SSIZE_T)format_vwprintf(&file_wprinter, stream, format, args);
}

[[cp_stdio, std, guard, wchar, ATTR_LIBC_WPRINTF(1, 2)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.write.printf")]]
__STDC_INT_AS_SIZE_T wprintf([[nonnull]] wchar_t const *__restrict format, ...)
	%{printf("vwprintf")}

[[cp_stdio, std, guard, wchar, ATTR_LIBC_WPRINTF(1, 0)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[requires_include("<__crt.h>"), impl_include("<local/stdstreams.h>")]]
[[requires($has_function(vfwprintf) && !defined(__NO_STDSTREAMS))]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.write.printf")]]
__STDC_INT_AS_SIZE_T vwprintf([[nonnull]] wchar_t const *__restrict format, $va_list args) {
	return vfwprintf(stdout, format, args);
}

[[cp_stdio, std, guard, wchar, ATTR_LIBC_WSCANF(2, 3)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.read.scanf")]]
__STDC_INT_AS_SIZE_T fwscanf([[nonnull]] FILE *__restrict stream, [[nonnull]] wchar_t const *__restrict format, ...)
	%{printf("vfwscanf")}

[[cp_stdio, std, guard, wchar, ATTR_LIBC_WSCANF(1, 2)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.read.scanf")]]
__STDC_INT_AS_SIZE_T wscanf([[nonnull]] wchar_t const *__restrict format, ...)
	%{printf("vwscanf")}

[[std, guard, wchar, ATTR_LIBC_WSCANF(2, 3)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.format.scanf")]]
__STDC_INT_AS_SIZE_T swscanf([[nonnull]] wchar_t const *__restrict src, [[nonnull]] wchar_t const *__restrict format, ...)
	%{printf("vswscanf")}

[[std, guard, wchar, ATTR_LIBC_WPRINTF(3, 0)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T vswprintf([[outp_opt(min(return + 1, buflen))]] wchar_t *__restrict buf, size_t buflen,
                               [[nonnull]] wchar_t const *__restrict format, $va_list args) {
	COMPILER_IMPURE();
	if (buflen)
		*buf = 0;
	/* TODO: format_wprintf() */
	(void)format;
	(void)args;
	return 0;
}

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[std, guard, wchar, ATTR_LIBC_WPRINTF(3, 4), dos_export_alias("_swprintf")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T swprintf([[outp_opt(min(return + 1, buflen))]] wchar_t *__restrict buf, size_t buflen,
                              [[nonnull]] wchar_t const *__restrict format, ...)
	%{printf("vswprintf")}

%(std)#endif /* __USE_ISOC95 || __USE_UNIX98 || __USE_DOS */

%[default:section(".text.crt{|.dos}.wchar.unicode.static.convert")]
%(std)

%(std,c,ccompat)#ifndef __NO_FPU
[[std, guard, wchar]]
wcstod(*) %{generate(str2wcs("strtod"))}
%(std,c,ccompat)#endif /* !__NO_FPU */

%(std)#ifdef __USE_ISOC99
%(std,c,ccompat)#ifndef __NO_FPU
[[std, guard, wchar]]
wcstof(*) %{generate(str2wcs("strtof"))}

%(std)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, guard, wchar]]
wcstold(*) %{generate(str2wcs("strtold"))}
%(std,c,ccompat)#endif /* !__NO_FPU */
%(std)#endif /* __COMPILER_HAVE_LONGDOUBLE */

[[std, guard, wchar, export_alias("wcstoq")]]
[[if(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("wcstol")]]
[[if(__SIZEOF_LONG_LONG__ == 8), alias("wcsto64", "_wcstoi64")]]
[[if(__SIZEOF_LONG_LONG__ == 4), alias("wcsto32")]]
[[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias("wcstoimax")]]
wcstoll(*) %{generate(str2wcs("strtoll"))}

[[std, guard, wchar, export_alias("wcstouq")]]
[[if(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("wcstoul")]]
[[if(__SIZEOF_LONG_LONG__ == 4), alias("wcstou32")]]
[[if(__SIZEOF_LONG_LONG__ == 8), alias("wcstou64", "_wcstoui64")]]
[[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias("wcstoumax")]]
wcstoull(*) %{generate(str2wcs("strtoull"))}

%[default:section(".text.crt{|.dos}.wchar.FILE.locked.read.scanf")]

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[cp_stdio, std, guard, wchar, wunused, ATTR_LIBC_WSCANF(2, 0)]]
__STDC_INT_AS_SIZE_T vfwscanf([[nonnull]] FILE *__restrict stream,
                              [[nonnull]] wchar_t const *__restrict format, $va_list args);
/* TODO: format_scanf() implementation for `vfwscanf'! */

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[cp_stdio, std, guard, wchar, wunused, ATTR_LIBC_WSCANF(1, 0)]]
[[requires_include("<__crt.h>"), impl_include("<local/stdstreams.h>")]]
[[requires($has_function(vfwscanf) && !defined(__NO_STDSTREAMS))]]
__STDC_INT_AS_SIZE_T vwscanf([[nonnull]] wchar_t const *__restrict format, $va_list args) {
	return vfwscanf(stdin, format, args);
}

%[default:section(".text.crt{|.dos}.wchar.unicode.static.format.scanf")]

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[std, guard, wchar, wunused, ATTR_LIBC_WSCANF(2, 0)]]
__STDC_INT_AS_SIZE_T vswscanf([[nonnull]] wchar_t const *__restrict src,
                              [[nonnull]] wchar_t const *__restrict format, $va_list args) {
	/* TODO: format_wscanf() */
	(void)src;
	(void)format;
	(void)args;
	COMPILER_IMPURE();
	return 0;
}

%(std)#endif /* __USE_ISOC99 */




@@Define wcstok() incorrectly, the same way DOS does
[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, nocrt, inline, exposed_name("wcstok")]]
[[if(defined(__CRT_DOS_PRIMARY)), preferred_alias("wcstok")]]
wchar_t *broken_dos_wcstok([[nullable]] wchar_t *string,
                           [[nonnull]] wchar_t const *__restrict delim) {
	static wchar_t *save_ptr = NULL;
	return wcstok(string, delim, &save_ptr);
}


%[insert:function(__mbrlen = mbrlen)]


%
%#ifdef __USE_XOPEN2K8
[[wchar, dos_export_alias("_wcsicmp")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wcscasecmp(*) %{generate(str2wcs("strcasecmp"))}

[[wchar, dos_export_alias("_wcsnicmp")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wcsncasecmp(*) %{generate(str2wcs("strncasecmp"))}

[[wchar, dos_export_alias("_wcsicmp_l"), export_alias("__wcscasecmp_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.memory")]]
wcscasecmp_l(*) %{generate(str2wcs("strcasecmp_l"))}

[[wchar, dos_export_alias("_wcsnicmp_l"), export_alias("__wcsncasecmp_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.memory")]]
wcsncasecmp_l(*) %{generate(str2wcs("strncasecmp_l"))}

[[wchar, dos_export_alias("_wcscoll_l"), export_alias("__wcscoll_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.memory")]]
wcscoll_l(*) %{generate(str2wcs("strcoll_l"))}

[[wchar, dos_export_alias("_wcsxfrm_l"), export_alias("__wcsxfrm_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.memory")]]
wcsxfrm_l(*) %{generate(str2wcs("strxfrm_l"))}

[[decl_include("<hybrid/typecore.h>")]]
[[wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcpcpy([[nonnull]] wchar_t *__restrict dst,
                            [[nonnull]] wchar_t const *__restrict src) {
	return wmempcpy(dst, src, wcslen(src) + 1);
}

[[decl_include("<hybrid/typecore.h>")]]
[[wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcpncpy([[nonnull]] wchar_t *__restrict buf,
                             [[nonnull]] wchar_t const *__restrict src,
                             $size_t buflen) {
	$size_t srclen = wcsnlen(src, buflen);
	wmemcpy(buf, src, srclen);
	wmemset(buf + srclen, '\0', ($size_t)(buflen - srclen));
	return buf + srclen;
}

[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
[[decl_include("<hybrid/typecore.h>", "<bits/mbstate.h>")]]
$size_t mbsnrtowcs([[nullable]] wchar_t *dst,
                   [[nonnull]] char const **__restrict psrc, $size_t nmc, $size_t len,
                   [[nullable]] $mbstate_t *mbs); /* TODO: Implement here */

[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
[[decl_include("<hybrid/typecore.h>", "<bits/mbstate.h>")]]
$size_t wcsnrtombs([[nullable]] char *dst,
                   [[nonnull]] wchar_t const **__restrict psrc, $size_t nwc, $size_t len,
                   [[nullable]] $mbstate_t *mbs); /* TODO: Implement here */

[[decl_include("<hybrid/typecore.h>")]]
[[wchar, section(".text.crt{|.dos}.wchar.FILE.locked.access")]]
$FILE *open_wmemstream(wchar_t **bufloc, $size_t *sizeloc);
%#endif /* __USE_XOPEN2K8 */

%
%#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)

[[guard, wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
[[crt_dos_impl_requires(!defined(LIBC_ARCH_HAVE_C16SNLEN))]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_C32SNLEN))]]
wcsnlen(*) %{generate(str2wcs("strnlen"))}

[[guard, wchar, dos_export_alias("_wcsdup")]]
[[section(".text.crt{|.dos}.wchar.heap.strdup")]]
wcsdup(*) %{generate(str2wcs("strdup"))}

%#endif /* __USE_XOPEN2K8 || __USE_DOS */

%
%#ifdef __USE_XOPEN
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, ATTR_CONST, impl_include("<libc/unicode.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
int wcwidth(wchar_t ch) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	if (ch >= UTF16_HIGH_SURROGATE_MIN &&
	    ch <= UTF16_LOW_SURROGATE_MAX)
		return 0;
@@pp_endif@@
	if (__libc_unicode_isprint(ch))
		return 1;
	if (ch == 0)
		return 0;
	return -1;
}

[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, ATTR_PURE, section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
int wcswidth([[inp(num_chars)]] wchar_t const *__restrict string, $size_t num_chars) {
	int temp, result = 0;
	for (; num_chars; --num_chars, ++string) {
		wchar_t ch = *string;
		if (!ch)
			break;
		temp = wcwidth(ch);
		if (temp < 0)
			return temp;
		result += temp;
	}
	return 0;
}
%#endif /* __USE_XOPEN */

%
%#if defined(__USE_XOPEN) || defined(__USE_DOS)
%[insert:guarded_function(wcswcs = wcsstr)]
%#endif /* __USE_XOPEN || __USE_DOS */

%
%#ifdef __USE_GNU
@@Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found.
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, ATTR_PURE, section(".text.crt{|.dos}.wchar.string.memory")]]
wchar_t *wcschrnul([[nonnull]] wchar_t const *haystack, wchar_t needle)
	[([[nonnull]] wchar_t *__restrict haystack, wchar_t needle): wchar_t *]
	[([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle): wchar_t const *]
	%{generate(str2wcs("strchrnul"))}


%[define_wchar_replacement(wmempcpy = "(char16_t *)mempcpyw", "(char32_t *)mempcpyl")]

[[wchar, no_crt_impl, decl_include("<hybrid/typecore.h>")]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("mempcpyw")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("mempcpyl")]]
[[if(__SIZEOF_WCHAR_T__ == 2), bind_local_function(mempcpyw)]]
[[if(__SIZEOF_WCHAR_T__ == 4), bind_local_function(mempcpyl)]]
[[nonnull]] wchar_t *wmempcpy([[outp(num_chars)]] wchar_t *__restrict dst,
                              [[inp(num_chars)]] wchar_t const *__restrict src,
                              $size_t num_chars) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)mempcpyw(dst, src, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)mempcpyl(dst, src, num_chars);
@@pp_else@@
	return (wchar_t *)mempcpy(dst, src, num_chars * sizeof(wchar_t));
@@pp_endif@@
}

%[define_wchar_replacement(wmempmove = "(char16_t *)mempmovew", "(char32_t *)mempmovel")]

[[std, wchar, no_crt_impl, decl_include("<hybrid/typecore.h>")]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("mempmovew")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("mempmovel")]]
[[if(__SIZEOF_WCHAR_T__ == 2), bind_local_function(mempmovew)]]
[[if(__SIZEOF_WCHAR_T__ == 4), bind_local_function(mempmovel)]]
[[nonnull]] wchar_t *wmempmove([[outp(num_chars)]] wchar_t *dst,
                               [[inp(num_chars)]] wchar_t const *src,
                               $size_t num_chars) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)mempmovew(dst, src, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)mempmovel(dst, src, num_chars);
@@pp_else@@
	return (wchar_t *)mempmove(dst, src, num_chars * sizeof(wchar_t));
@@pp_endif@@
}

[[wchar, dos_export_alias("_wcstol_l"), export_alias("__wcstol_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcstol_l(*) %{generate(str2wcs("strtol_l"))}

[[wchar, dos_export_alias("_wcstoul_l"), export_alias("__wcstoul_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcstoul_l(*) %{generate(str2wcs("strtoul_l"))}

%[insert:function(wcstoq = wcstoll)]
%[insert:function(wcstouq = wcstoull)]

[[wchar, dos_export_alias("_wcstoll_l"), export_alias("__wcstoll_l")]]
[[if(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("wcstol_l", "_wcstol_l", "__wcstol_l")]]
[[if(__SIZEOF_LONG_LONG__ == 8), alias("_wcstoi64_l")]]
[[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias("wcstoimax_l", "_wcstoimax_l", "__wcstoimax_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcstoll_l(*) %{generate(str2wcs("strtoll_l"))}

[[wchar, export_alias("__wcstoull_l")]]
[[if(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("wcstoul_l", "_wcstoul_l", "__wcstoul_l")]]
[[if(__SIZEOF_LONG_LONG__ == 8), alias("_wcstoui64_l")]]
[[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias("wcstoumax_l", "_wcstoumax_l", "__wcstoumax_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcstoull_l(*) %{generate(str2wcs("strtoull_l"))}

%#ifndef __NO_FPU
[[wchar, dos_export_alias("_wcstof_l"), export_alias("__wcstof_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcstof_l(*) %{generate(str2wcs("strtof_l"))}

[[wchar, dos_export_alias("_wcstod_l"), export_alias("__wcstod_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcstod_l(*) %{generate(str2wcs("strtod_l"))}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[wchar, dos_export_alias("_wcstold_l"), export_alias("__wcstold_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcstold_l(*) %{generate(str2wcs("strtold_l"))}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__NO_FPU */

[[decl_include("<hybrid/typecore.h>")]]
[[cp_stdio, wchar, requires_include("<__crt.h>"), impl_include("<local/stdstreams.h>")]]
[[requires($has_function(fgetwc_unlocked) && !defined(__NO_STDSTREAMS))]]
[[section(".text.crt{|.dos}.wchar.FILE.unlocked.read.getc")]]
$wint_t getwchar_unlocked() {
	return fgetwc_unlocked(stdin);
}

[[decl_include("<hybrid/typecore.h>")]]
[[cp_stdio, wchar, requires_include("<__crt.h>"), impl_include("<local/stdstreams.h>")]]
[[requires($has_function(fputwc_unlocked) && !defined(__NO_STDSTREAMS))]]
[[section(".text.crt{|.dos}.wchar.FILE.unlocked.write.putc")]]
$wint_t putwchar_unlocked(wchar_t wc) {
	return fputwc_unlocked(wc, stdin);
}

%[insert:function(getwc_unlocked = fgetwc_unlocked)]
%[insert:function(putwc_unlocked = fputwc_unlocked)]

[[decl_include("<hybrid/typecore.h>")]]
[[cp_stdio, wchar, dos_export_alias("_fgetwc_nolock")]]
[[section(".text.crt{|.dos}.wchar.FILE.unlocked.read.getc")]]
$wint_t fgetwc_unlocked([[nonnull]] $FILE *__restrict stream);

[[decl_include("<hybrid/typecore.h>")]]
[[cp_stdio, wchar, dos_export_alias("_fputwc_nolock")]]
[[section(".text.crt{|.dos}.wchar.FILE.unlocked.write.putc")]]
$wint_t fputwc_unlocked(wchar_t wc, [[nonnull]] $FILE *__restrict stream);

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[cp_stdio, wchar, dos_export_alias("_fgetws_nolock"), alias("fgetws")]]
[[section(".text.crt{|.dos}.wchar.FILE.unlocked.read.read")]]
[[requires_function(fgetwc_unlocked, ungetwc_unlocked, ferror_unlocked)]]
[[impl_include("<asm/crt/stdio.h>", "<parts/errno.h>")]]
wchar_t *fgetws_unlocked([[outp(bufsize)]] wchar_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize,
                         [[nonnull]] $FILE *__restrict stream) {
	$size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
@@pp_ifdef ERANGE@@
		__libc_seterrno(ERANGE);
@@pp_endif@@
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		wint_t ch = fgetwc_unlocked(stream);
		if (ch == WEOF) {
			if (n == 0 || ferror_unlocked(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = fgetwc_unlocked(stream);
			if (ch == WEOF) {
				if (n == 0 || ferror_unlocked(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			ungetwc_unlocked(ch, stream);
			break;
		}
		buf[n] = (wchar_t)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.FILE.unlocked.write.write")]]
[[cp_stdio, dos_export_alias("_fputws_nolock")]]
[[wchar, requires_function(file_wprinter_unlocked)]]
__STDC_INT_AS_SIZE_T fputws_unlocked([[nonnull]] wchar_t const *__restrict string,
                                     [[nonnull]] $FILE *__restrict stream) {
	__STDC_INT_AS_SIZE_T result;
	result = file_wprinter_unlocked(stream, string, wcslen(string));
	return result;
}


[[wchar, decl_include("<bits/crt/tm.h>", "<hybrid/typecore.h>")]]
[[dos_export_alias("_wcsftime_l"), export_alias("__wcsftime_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.format.strftime")]]
$size_t wcsftime_l([[outp(maxsize)]] wchar_t *__restrict buf, $size_t maxsize,
                   [[nonnull]] wchar_t const *__restrict format,
                   [[nonnull]] struct $tm const *__restrict tp,
                   $locale_t locale) {
	(void)locale;
	return wcsftime(buf, maxsize, format, tp);
}

%#endif /* __USE_GNU */

%
%
%
%

%#ifdef __USE_KOS
%
%/* KOS FILE extension functions. */
%

@@For use with `format_printf()' and friends: Prints to a `FILE *' closure argument
[[decl_include("<hybrid/typecore.h>")]]
[[cp_stdio, wchar, impl_include("<asm/crt/stdio.h>")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("file_wprinter_unlocked")]]
[[alias("file_wprinter_unlocked")]]
[[userimpl, requires($has_function(fputwc))]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.write.write")]]
$ssize_t file_wprinter([[nonnull]] void *arg,
                       [[inp(datalen)]] wchar_t const *__restrict data,
                       $size_t datalen) {
	$size_t i;
	for (i = 0; i < datalen; ++i) {
		if (fputwc(data[i], ($FILE *)arg) == WEOF)
			break;
	}
	return (ssize_t)i;
}

@@Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG'
[[decl_include("<hybrid/typecore.h>")]]
[[cp_stdio, wchar, impl_include("<asm/crt/stdio.h>"), alias("file_wprinter")]]
[[userimpl, requires_function(fputwc_unlocked)]]
[[section(".text.crt{|.dos}.wchar.FILE.unlocked.write.write")]]
$ssize_t file_wprinter_unlocked([[nonnull]] void *arg,
                                [[inp(datalen)]] wchar_t const *__restrict data,
                                $size_t datalen) {
	$size_t i;
	for (i = 0; i < datalen; ++i) {
		if (fputwc_unlocked(data[i], ($FILE *)arg) == WEOF)
			break;
	}
	return (ssize_t)i;
}


[[decl_include("<hybrid/typecore.h>")]]
[[wchar, dos_export_alias("_ungetwc_nolock"), alias("ungetwc")]]
[[section(".text.crt{|.dos}.wchar.FILE.unlocked.write.putc")]]
$wint_t ungetwc_unlocked($wint_t ch, [[nonnull]] $FILE *__restrict stream);


%[default:section(".text.crt{|.dos}.wchar.FILE.unlocked.write.printf")]

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[cp_stdio, wchar, ATTR_LIBC_WPRINTF(2, 0)]]
[[requires_dependent_function(file_wprinter_unlocked)]]
__STDC_INT_AS_SIZE_T vfwprintf_unlocked([[nonnull]] $FILE *__restrict stream,
                                        [[nonnull]] wchar_t const *__restrict format,
                                        $va_list args) {
	return (__STDC_INT_AS_SSIZE_T)format_vwprintf(&file_wprinter_unlocked,
	                                              stream, format, args);
}

[[cp_stdio, wchar, ATTR_LIBC_WPRINTF(2, 3)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SIZE_T fwprintf_unlocked([[nonnull]] $FILE *__restrict stream,
                                       [[nonnull]] wchar_t const *__restrict format, ...)
	%{printf("vfwprintf_unlocked")}

[[cp_stdio, wchar, ATTR_LIBC_WPRINTF(1, 2)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SIZE_T wprintf_unlocked([[nonnull]] wchar_t const *__restrict format, ...)
	%{printf("vwprintf_unlocked")}

[[cp_stdio, wchar, ATTR_LIBC_WPRINTF(1, 0)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[requires_include("<__crt.h>"), impl_include("<local/stdstreams.h>")]]
[[requires($has_function(vfwprintf_unlocked) && !defined(__NO_STDSTREAMS))]]
__STDC_INT_AS_SIZE_T vwprintf_unlocked([[nonnull]] wchar_t const *__restrict format, $va_list args) {
	return vfwprintf_unlocked(stdout, format, args);
}

%[default:section(".text.crt{|.dos}.wchar.FILE.unlocked.read.scanf")]

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[cp_stdio, wunused, ATTR_LIBC_WSCANF(2, 0), wchar, alias("vfwscanf")]]
__STDC_INT_AS_SIZE_T vfwscanf_unlocked([[nonnull]] $FILE *__restrict stream,
                                       [[nonnull]] wchar_t const *__restrict format,
                                       $va_list args);
/* TODO: Inline implementation for `vfwscanf_unlocked()' */

[[impl_include("<local/stdstreams.h>")]]
[[cp_stdio, wchar, ATTR_LIBC_SCANF(1, 0), wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[requires($has_function(vfwscanf_unlocked) && !defined(__NO_STDSTREAMS))]]
__STDC_INT_AS_SIZE_T vwscanf_unlocked([[nonnull]] wchar_t const *__restrict format, $va_list args) {
	return vfwscanf_unlocked(stdin, format, args);
}

[[cp_stdio, wchar, ATTR_LIBC_SCANF(2, 3), wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SIZE_T fwscanf_unlocked([[nonnull]] $FILE *__restrict stream,
                                      [[nonnull]] wchar_t const *__restrict format, ...)
	%{printf("vfwscanf_unlocked")}

[[cp_stdio, wchar, ATTR_LIBC_SCANF(1, 2), wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SIZE_T wscanf_unlocked([[nonnull]] wchar_t const *__restrict format, ...)
	%{printf("vwscanf_unlocked")}


%
%
%
%



/* KOS String extension functions. */
@@Same as `STR+wcslen(STR)'
[[wchar, wunused, ATTR_PURE]]
[[decl_include("<hybrid/typecore.h>")]]
[[crt_dos_impl_requires(!defined(LIBC_ARCH_HAVE_C16SEND))]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_C32SEND))]]
[[section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsend([[nonnull]] wchar_t const *__restrict string)
	[([[nonnull]] wchar_t *__restrict string): [[nonnull]] wchar_t *]
	[([[nonnull]] wchar_t const *__restrict string): [[nonnull]] wchar_t const *]
	%{generate(str2wcs("strend"))}

@@Same as `STR+wcsnlen(STR, MAX_CHARS)'
[[wchar, wunused, ATTR_PURE]]
[[decl_include("<hybrid/typecore.h>")]]
[[crt_dos_impl_requires(!defined(LIBC_ARCH_HAVE_C16SNEND))]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_C32SNEND))]]
[[section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsnend([[inp(maxlen)]] wchar_t const *__restrict string, $size_t maxlen)
	[([[inp(maxlen)]] wchar_t *__restrict string, $size_t maxlen): [[nonnull]] wchar_t *]
	[([[inp(maxlen)]] wchar_t const *__restrict string, $size_t maxlen): [[nonnull]] wchar_t const *]
	%{generate(str2wcs("strnend"))}


[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
[[if(__SIZEOF_LONG__ == 4), alias("wcstol")]]
[[if(__SIZEOF_LONG_LONG__ == 4), alias("wcstoll", "wcstoq")]]
[[if(__SIZEOF_INTMAX_T__ == 4), alias("wcstoimax")]]
wcsto32(*) %{generate(str2wcs("strto32"))}

[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
[[if(__SIZEOF_LONG__ == 4), alias("wcstoul")]]
[[if(__SIZEOF_LONG_LONG__ == 4), alias("wcstoull", "wcstouq")]]
[[if(__SIZEOF_INTMAX_T__ == 4), alias("wcstoumax")]]
wcstou32(*) %{generate(str2wcs("strtou32"))}

%
%#ifdef __UINT64_TYPE__
[[wchar, dos_export_alias("_wcstoui64")]]
[[if(__SIZEOF_LONG__ == 8), alias("wcstoul")]]
[[if(__SIZEOF_LONG_LONG__ == 8), alias("wcstoull", "wcstouq")]]
[[if(__SIZEOF_INTMAX_T__ == 8), alias("wcstoumax")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
wcstou64(*) %{generate(str2wcs("strtou64"))}

[[wchar, dos_export_alias("_wcstoi64")]]
[[if(__SIZEOF_LONG__ == 8), alias("wcstol")]]
[[if(__SIZEOF_LONG_LONG__ == 8), alias("wcstoll", "wcstoq")]]
[[if(__SIZEOF_INTMAX_T__ == 8), alias("wcstoimax")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
wcsto64(*) %{generate(str2wcs("strto64"))}
%#endif /* __UINT64_TYPE__ */

%
%#ifdef __USE_XOPEN2K8
[[wchar, section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
[[if(__SIZEOF_LONG__ == 4), alias("wcstol_l", "_wcstol_l", "__wcstol_l")]]
[[if(__SIZEOF_LONG_LONG__ == 4), alias("wcstoll_l", "_wcstoll_l", "__wcstoll_l")]]
[[if(__SIZEOF_INTMAX_T__ == 4), alias("wcstoimax_l", "_wcstoimax_l", "__wcstoimax_l")]]
wcsto32_l(*) %{generate(str2wcs("strto32_l"))}

[[wchar, section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
[[if(__SIZEOF_LONG__ == 4), alias("wcstoul_l", "_wcstoul_l", "__wcstoul_l")]]
[[if(__SIZEOF_LONG_LONG__ == 4), alias("wcstoull_l", "_wcstoull_l", "__wcstoull_l")]]
[[if(__SIZEOF_INTMAX_T__ == 4), alias("wcstoumax_l", "_wcstoumax_l", "__wcstoumax_l")]]
wcstou32_l(*) %{generate(str2wcs("strtou32_l"))}

%
%#ifdef __UINT64_TYPE__
[[wchar, dos_export_alias("_wcstoi64_l")]]
[[if(__SIZEOF_LONG__ == 8), alias("wcstol_l", "_wcstol_l", "__wcstol_l")]]
[[if(__SIZEOF_LONG_LONG__ == 8), alias("wcstoll_l", "_wcstoll_l", "__wcstoll_l")]]
[[if(__SIZEOF_INTMAX_T__ == 8), alias("wcstoimax_l", "_wcstoimax_l", "__wcstoimax_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcsto64_l(*) %{generate(str2wcs("strto64_l"))}

[[wchar, dos_export_alias("_wcstoui64_l")]]
[[if(__SIZEOF_LONG__ == 8), alias("wcstoul_l", "_wcstoul_l", "__wcstoul_l")]]
[[if(__SIZEOF_LONG_LONG__ == 8), alias("wcstoull_l", "_wcstoull_l", "__wcstoull_l")]]
[[if(__SIZEOF_INTMAX_T__ == 8), alias("wcstoumax_l", "_wcstoumax_l", "__wcstoumax_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcstou64_l(*) %{generate(str2wcs("strtou64_l"))}
%#endif /* __UINT64_TYPE__ */
%#endif /* __USE_XOPEN2K8 */




%
[[wchar, dos_export_alias("_wcsncoll")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wcsncoll(*) %{generate(str2wcs("strncoll"))}

[[wchar, dos_export_alias("_wcsicoll"), alias("wcsicoll")]]
[[alias("wcscasecmp", "_wcsicmp", "wcsicmp")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wcscasecoll(*) %{generate(str2wcs("strcasecoll"))}

[[wchar, dos_export_alias("_wcsnicoll"), alias("wcsnicoll")]]
[[alias("wcsncasecmp", "_wcsnicmp", "wcsnicmp")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wcsncasecoll(*) %{generate(str2wcs("strncasecoll"))}

[[decl_include("<hybrid/typecore.h>")]]
[[wchar, ATTR_LEAF, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsnrev([[inoutp(maxlen)]] wchar_t *__restrict str, $size_t maxlen) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)memrevw(str, wcsnlen(str, maxlen));
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)memrevl(str, wcsnlen(str, maxlen));
@@pp_else@@
	return (wchar_t *)memrev(str, wcsnlen(str, maxlen) * sizeof(wchar_t));
@@pp_endif@@
}

[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wcsnlwr(*) %{generate(str2wcs("strnlwr"))}

[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wcsnupr(*) %{generate(str2wcs("strnupr"))}

[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, ATTR_PURE, section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wchar_t *wcscasestr([[nonnull]] wchar_t const *haystack, wchar_t const *needle)
	[([[nonnull]] wchar_t *haystack, [[nonnull]] wchar_t *needle): wchar_t *]
	[([[nonnull]] wchar_t const *haystack, [[nonnull]] wchar_t const *needle): wchar_t const *]
	%{generate(str2wcs("strcasestr"))}

@@Same as wcscpy, but return a pointer after the last written character
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, ATTR_LEAF, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcspcpy([[nonnull]] wchar_t *__restrict buf,
                             [[nonnull]] wchar_t const *__restrict src) {
	return wmempcpy(buf, src, wcslen(src) + 1);
}

@@Same as wcsncpy, but return a pointer after the last written character
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, ATTR_LEAF, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcspncpy([[outp(buflen)]] wchar_t *__restrict buf,
                              [[nonnull]] wchar_t const *__restrict src, $size_t buflen) {
	$size_t srclen = wcsnlen(src, buflen);
	wmemcpy(buf, src, srclen);
	return wmempset(buf + srclen, '\0', buflen - srclen);
}

%[define_wchar_replacement(wmempset = "(char16_t *)mempsetw", "(char32_t *)mempsetl")]

@@Same as wmemset, but return a pointer after the last written character
[[wchar, ATTR_LEAF, no_crt_impl, decl_include("<hybrid/typecore.h>")]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("mempsetw")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("mempsetl")]]
[[if(__SIZEOF_WCHAR_T__ == 2), bind_local_function(mempsetw)]]
[[if(__SIZEOF_WCHAR_T__ == 4), bind_local_function(mempsetl)]]
[[nonnull]] wchar_t *wmempset([[outp(num_chars)]] wchar_t *dst,
                              wchar_t filler, $size_t num_chars) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)mempsetw(dst, (u16)filler, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)mempsetl(dst, (u32)filler, num_chars);
@@pp_else@@
	return (wchar_t *)mempset(dst, (int)filler, num_chars * sizeof(wchar_t));
@@pp_endif@@
}


@@Same as `wcschr', but don't exceed `MAX_CHARS' characters.
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, ATTR_PURE, section(".text.crt{|.dos}.wchar.string.memory")]]
wchar_t *wcsnchr([[inp(maxlen)]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen)
	[([[inp(maxlen)]] wchar_t *__restrict haystack, wchar_t needle, $size_t maxlen): wchar_t *]
	[([[inp(maxlen)]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen): wchar_t const *]
	%{generate(str2wcs("strnchr"))}

@@Same as `wcsrchr', but don't exceed `MAX_CHARS' characters.
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, ATTR_PURE, section(".text.crt{|.dos}.wchar.string.memory")]]
wchar_t *wcsnrchr([[inp(maxlen)]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen)
	[([[inp(maxlen)]] wchar_t *__restrict haystack, wchar_t needle, $size_t maxlen): wchar_t *]
	[([[inp(maxlen)]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen): wchar_t const *]
	%{generate(str2wcs("strnrchr"))}

[[wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
wcssep(*) %{generate(str2wcs("strsep"))}

[[wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
wcsfry(*) %{generate(str2wcs("strfry"))}

[[wchar, section(".text.crt{|.dos}.wchar.heap.strdup")]]
wcsndup(*) %{generate(str2wcs("strndup"))}


@@Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found.
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, ATTR_PURE, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsrchrnul([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle)
	[([[nonnull]] wchar_t *__restrict haystack, wchar_t needle): [[nonnull]] wchar_t *]
	[([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle): [[nonnull]] wchar_t const *]
	%{generate(str2wcs("strrchrnul"))}

@@Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found.
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, ATTR_PURE, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsnchrnul([[inp(maxlen)]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen)
	[([[inp(maxlen)]] wchar_t *__restrict haystack, wchar_t needle, $size_t maxlen): [[nonnull]] wchar_t *]
	[([[inp(maxlen)]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen): [[nonnull]] wchar_t const *]
	%{generate(str2wcs("strnchrnul"))}

@@Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found.
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, ATTR_PURE, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsnrchrnul([[inp(maxlen)]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen)
	[([[inp(maxlen)]] wchar_t *__restrict haystack, wchar_t needle, $size_t maxlen): [[nonnull]] wchar_t *]
	[([[inp(maxlen)]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen): [[nonnull]] wchar_t const *]
	%{generate(str2wcs("strnrchrnul"))}

@@Same as `wcschrnul', but return the offset from `STR', rather than the actual address
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, ATTR_PURE, section(".text.crt{|.dos}.wchar.string.memory")]]
$size_t wcsoff([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle)
	%{generate(str2wcs("stroff"))}

@@Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, ATTR_PURE, section(".text.crt{|.dos}.wchar.string.memory")]]
$size_t wcsroff([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle)
	%{generate(str2wcs("strroff"))}

@@Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, ATTR_PURE, section(".text.crt{|.dos}.wchar.string.memory")]]
$size_t wcsnoff([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen)
	%{generate(str2wcs("strnoff"))}

@@Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, ATTR_PURE, section(".text.crt{|.dos}.wchar.string.memory")]]
$size_t wcsnroff([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen)
	%{generate(str2wcs("strnroff"))}


%[define_wchar_replacement(fuzzy_wmemcmp = fuzzy_memcmpw, fuzzy_memcmpl)]

[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, ATTR_PURE, no_crt_impl]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("fuzzy_memcmpw")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("fuzzy_memcmpl")]]
[[if(__SIZEOF_WCHAR_T__ == 2), bind_local_function(fuzzy_memcmpw)]]
[[if(__SIZEOF_WCHAR_T__ == 4), bind_local_function(fuzzy_memcmpl)]]
$size_t fuzzy_wmemcmp([[inp(s1_chars)]] wchar_t const *s1, $size_t s1_chars,
                      [[inp(s2_chars)]] wchar_t const *s2, $size_t s2_chars) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return fuzzy_memcmpw(s1, s1_chars, s2, s2_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return fuzzy_memcmpl(s1, s1_chars, s2, s2_chars);
@@pp_else@@
	return fuzzy_memcmp(s1, s1_chars * sizeof(wchar_t), s2, s2_chars * sizeof(wchar_t));
@@pp_endif@@
}

[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, ATTR_PURE, requires_function(fuzzy_wmemcmp)]]
[[section(".text.crt{|.dos}.wchar.string.memory")]]
$size_t fuzzy_wcscmp([[nonnull]] wchar_t const *s1,
                     [[nonnull]] wchar_t const *s2) {
	return fuzzy_wmemcmp(s1, wcslen(s1), s2, wcslen(s2));
}

[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, ATTR_PURE, requires_function(fuzzy_wmemcmp)]]
[[section(".text.crt{|.dos}.wchar.string.memory")]]
$size_t fuzzy_wcsncmp([[inp(s1_maxlen)]] wchar_t const *s1, $size_t s1_maxlen,
                      [[inp(s2_maxlen)]] wchar_t const *s2, $size_t s2_maxlen) {
	return fuzzy_wmemcmp(s1, wcsnlen(s1, s1_maxlen), s2, wcsnlen(s2, s2_maxlen));
}

[[wchar, wunused, ATTR_PURE, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
$size_t fuzzy_wmemcasecmp([[inp(s1_bytes)]] wchar_t const *s1, $size_t s1_bytes,
                          [[inp(s2_bytes)]] wchar_t const *s2, $size_t s2_bytes)
	%{generate(str2wcs("fuzzy_memcasecmp"))}

[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, ATTR_PURE, requires_function(fuzzy_wmemcasecmp)]]
[[section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
fuzzy_wcscasecmp:([[nonnull]] wchar_t const *s1, [[nonnull]] wchar_t const *s2) -> $size_t {
	return fuzzy_wmemcasecmp(s1, wcslen(s1), s2, wcslen(s2));
}

[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, ATTR_PURE, requires_function(fuzzy_wmemcasecmp)]]
[[section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
$size_t fuzzy_wcsncasecmp([[inp(s1_maxlen)]] wchar_t const *s1, $size_t s1_maxlen,
                          [[inp(s2_maxlen)]] wchar_t const *s2, $size_t s2_maxlen) {
	return fuzzy_wmemcasecmp(s1, wcsnlen(s1, s1_maxlen), s2, wcsnlen(s2, s2_maxlen));
}

[[wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
wildwcscmp(*) %{generate(str2wcs("wildstrcmp"))}

[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wildwcscasecmp(*) %{generate(str2wcs("wildstrcasecmp"))}

[[wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
wcsverscmp(*) %{generate(str2wcs("strverscmp"))}






%
%#ifdef __USE_XOPEN2K8
%[default:section(".text.crt{|.dos}.wchar.unicode.locale.memory")]

[[wchar, dos_export_alias("_wcsncoll_l")]]
wcsncoll_l(*) %{generate(str2wcs("strncoll_l"))}

[[wchar, dos_export_alias("_wcsicoll_l")]]
[[alias("wcscasecmp_l", "_wcsicmp_l")]]
wcscasecoll_l(*) %{generate(str2wcs("strcasecoll_l"))}

[[wchar, dos_export_alias("_wcsnicoll_l")]]
[[alias("wcsncasecmp_l", "_wcsnicmp_l")]]
wcsncasecoll_l(*) %{generate(str2wcs("strncasecoll_l"))}

[[wchar, dos_export_alias("_wcslwr_l")]]
wcslwr_l(*) %{generate(str2wcs("strlwr_l"))}

[[wchar, dos_export_alias("_wcsupr_l")]]
wcsupr_l(*) %{generate(str2wcs("strupr_l"))}

[[wchar]] wcsnlwr_l(*) %{generate(str2wcs("strnlwr_l"))}
[[wchar]] wcsnupr_l(*) %{generate(str2wcs("strnupr_l"))}
[[wchar]] wcscasestr_l(*) %{generate(str2wcs("strcasestr_l"))}

[[wchar, wunused, ATTR_PURE]]
[[decl_include("<hybrid/typecore.h>")]]
$size_t fuzzy_wmemcasecmp_l([[nonnull]] wchar_t const *s1, $size_t s1_bytes,
                            [[nonnull]] wchar_t const *s2, $size_t s2_bytes,
                            $locale_t locale)
	%{generate(str2wcs("fuzzy_memcasecmp_l"))}

[[wchar]] fuzzy_wcscasecmp_l(*) %{generate(str2wcs("fuzzy_strcasecmp_l"))}
[[wchar]] fuzzy_wcsncasecmp_l(*) %{generate(str2wcs("fuzzy_strncasecmp_l"))}
[[wchar]] wildwcscasecmp_l(*) %{generate(str2wcs("wildstrcasecmp_l"))}

%#endif /* __USE_XOPEN2K8 */


%#endif /* __USE_KOS */
















%
%
%
%

%
%#ifdef __USE_DOS
%#ifndef _WSTRING_DEFINED
%#define _WSTRING_DEFINED 1

%[insert:guarded_function(_wcsdup = wcsdup)]

%
%#ifdef __USE_DOS_SLIB
[[guard, wchar, section(".text.crt.dos.wchar.string.memory")]]
wcscat_s(*) %{generate(str2wcs("strcat_s"))}

[[guard, wchar, section(".text.crt.dos.wchar.string.memory")]]
wcscpy_s(*) %{generate(str2wcs("strcpy_s"))}

[[decl_include("<hybrid/typecore.h>")]]
[[guard, inline, nocrt, wunused, ATTR_PURE]]
$size_t wcsnlen_s([[nullable]] wchar_t const *str, $size_t maxlen) {
	return str ? wcsnlen(str, maxlen) : 0;
}

[[guard, wchar, section(".text.crt.dos.wchar.string.memory")]]
wcsncat_s(*) %{generate(str2wcs("strncat_s"))}

[[guard, wchar, section(".text.crt.dos.wchar.string.memory")]]
wcsncpy_s(*) %{generate(str2wcs("strncpy_s"))}

%[insert:guarded_function(wcstok_s = wcstok)]

%#endif  /* __USE_DOS_SLIB */

%[default:section(".text.crt.dos.wchar.errno")];
[[guard, wchar, decl_include("<hybrid/typecore.h>")]]
wchar_t *_wcserror(int errno_value);

[[guard, wchar, decl_include("<bits/types.h>")]]
$errno_t _wcserror_s(wchar_t *buf, $size_t bufsize, int errno_value);

[[guard, wchar, decl_include("<hybrid/typecore.h>")]]
wchar_t *__wcserror(wchar_t const *message);

[[guard, wchar, decl_include("<bits/types.h>")]]
$errno_t __wcserror_s(wchar_t *buf, $size_t bufsize, wchar_t const *message);

%[insert:guarded_function(_wcsicmp = wcscasecmp)]
%[insert:guarded_function(_wcsnicmp = wcsncasecmp)]
%[insert:guarded_function(_wcsicmp_l = wcscasecmp_l)]
%[insert:guarded_function(_wcsnicmp_l = wcsncasecmp_l)]

[[guard, wchar, section(".text.crt.dos.wchar.string.memory")]]
[[decl_include("<bits/types.h>")]]
$errno_t _wcsnset_s(wchar_t *__restrict buf, $size_t buflen, wchar_t ch, $size_t maxlen)
	%{generate(str2wcs("_strnset_s"))}

[[guard, wchar, section(".text.crt.dos.wchar.string.memory")]]
[[decl_include("<bits/types.h>")]]
$errno_t _wcsset_s([[nonnull]] wchar_t *dst, $size_t dstsize, wchar_t ch)
	%{generate(str2wcs("_strset_s"))}

[[guard, wchar, section(".text.crt.dos.wchar.unicode.static.memory")]]
_wcslwr_s(*) %{generate(str2wcs("_strlwr_s"))}

[[guard, wchar, section(".text.crt.dos.wchar.unicode.static.memory")]]
_wcsupr_s(*) %{generate(str2wcs("_strupr_s"))}

[[guard, wchar, section(".text.crt.dos.wchar.unicode.locale.memory")]]
_wcslwr_s_l(*) %{generate(str2wcs("_strlwr_s_l"))}

[[guard, wchar, section(".text.crt.dos.wchar.unicode.locale.memory")]]
_wcsupr_s_l(*) %{generate(str2wcs("_strupr_s_l"))}

[[decl_include("<bits/types.h>")]]
[[guard, wchar, section(".text.crt.dos.wchar.string.memory")]]
$errno_t wmemcpy_s([[nonnull]] wchar_t *dst, rsize_t dstlength,
                   [[nonnull]] wchar_t const *src, rsize_t srclength)
	%{generate(str2wcs("memcpy_s"))}

[[decl_include("<bits/types.h>")]]
[[guard, wchar, section(".text.crt.dos.wchar.string.memory")]]
$errno_t wmemmove_s([[nonnull]] wchar_t *dst, rsize_t dstlength,
                    [[nonnull]] wchar_t const *src, rsize_t srclength)
	%{generate(str2wcs("memmove_s"))}

%
%
%

%[insert:guarded_function(_wcsnset = wcsnset)]
%[insert:guarded_function(_wcsrev = wcsrev)]
%[insert:guarded_function(_wcsset = wcsset)]
%[insert:guarded_function(_wcslwr = wcslwr)]
%[insert:guarded_function(_wcsupr = wcsupr)]
%[insert:guarded_function(_wcslwr_l = wcslwr_l)]
%[insert:guarded_function(_wcsupr_l = wcsupr_l)]
%[insert:guarded_function(_wcsxfrm_l = wcsxfrm_l)]
%[insert:guarded_function(_wcscoll_l = wcscoll_l)]
%[insert:guarded_function(_wcsicoll = wcscasecoll)]
%[insert:guarded_function(_wcsicoll_l = wcscasecoll_l)]
%[insert:guarded_function(_wcsncoll = wcsncasecoll)]
%[insert:guarded_function(_wcsncoll_l = wcsncoll_l)]
%[insert:guarded_function(_wcsnicoll = wcsncasecoll)]
%[insert:guarded_function(_wcsnicoll_l = wcsncasecoll_l)]

%
%
%

%[insert:guarded_function(wcsicmp = wcscasecmp)]
%[insert:guarded_function(wcsnicmp = wcsncasecmp)]
%[insert:guarded_function(wcsicoll = wcscasecoll)]

%#endif /* !_WSTRING_DEFINED */
%#endif /* __USE_DOS */


%#if defined(__USE_DOS) || defined(__USE_KOS)
[[decl_include("<hybrid/typecore.h>")]]
[[guard, wchar, dos_export_alias("_wcsnset")]]
[[section(".text.crt.dos.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsnset([[nonnull]] wchar_t *__restrict str, wchar_t ch, $size_t maxlen)
	%{generate(str2wcs("strnset"))}

[[decl_include("<hybrid/typecore.h>")]]
[[guard, wchar, dos_export_alias("_wcsrev")]]
[[section(".text.crt.dos.wchar.string.memory"), doc_alias("strrev")]]
[[nonnull]] wchar_t *wcsrev([[nonnull]] wchar_t *__restrict str) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)memrevw(str, wcslen(str));
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)memrevl(str, wcslen(str));
@@pp_else@@
	return (wchar_t *)memrev(str, wcslen(str) * sizeof(wchar_t));
@@pp_endif@@
}


[[guard, wchar, dos_export_alias("_wcsset")]]
[[section(".text.crt.dos.wchar.string.memory")]]
wcsset(*) %{generate(str2wcs("strset"))}

[[guard, wchar, dos_export_alias("_wcslwr")]]
[[section(".text.crt.dos.wchar.unicode.static.memory")]]
wcslwr(*) %{generate(str2wcs("strlwr"))}

[[guard, wchar, dos_export_alias("_wcsupr")]]
[[section(".text.crt.dos.wchar.unicode.static.memory")]]
wcsupr(*) %{generate(str2wcs("strupr"))}

%#endif /* __USE_DOS || __USE_KOS */


%#ifdef __USE_DOS
%#ifndef _WSTDIO_DEFINED
%#define _WSTDIO_DEFINED 1

%#ifdef __USE_DOS_SLIB
%[insert:guarded_function(vswprintf_s = vswprintf)]
%[insert:guarded_function(swprintf_s = swprintf)]
%[insert:guarded_function(vfwprintf_s = vfwprintf)]
%[insert:guarded_function(fwprintf_s = fwprintf)]
%[insert:guarded_function(vwprintf_s = vwprintf)]
%[insert:guarded_function(wprintf_s = wprintf)]
%[insert:guarded_function(vswscanf_s = vswscanf)]
%[insert:guarded_function(swscanf_s = swscanf)]
%[insert:guarded_function(vfwscanf_s = vfwscanf)]
%[insert:guarded_function(fwscanf_s = fwscanf)]
%[insert:guarded_function(vwscanf_s = vwscanf)]
%[insert:guarded_function(wscanf_s = wscanf)]
%#endif /* __USE_DOS_SLIB */

%[default:section(".text.crt.dos.wchar.FILE.locked.write.printf")]

[[guard, wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vscwprintf([[nonnull]] wchar_t const *format, $va_list args) {
	return vswprintf(NULL, 0, format, args);
}

[[guard, wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _scwprintf([[nonnull]] wchar_t const *format, ...)
	%{printf("_vscwprintf")}

[[guard, wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vscwprintf_p([[nonnull]] wchar_t const *format, $va_list args) {
	/* TODO */
	(void)format;
	(void)args;
	COMPILER_IMPURE();
	return 0;
}

[[guard, wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _scwprintf_p([[nonnull]] wchar_t const *format, ...)
	%{printf("_vscwprintf_p")}

[[guard, wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vscwprintf_l([[nonnull]] wchar_t const *format,
                                    [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return _vscwprintf(format, args);
}

[[guard, wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _scwprintf_l([[nonnull]] wchar_t const *format,
                                   [[nullable]] $locale_t locale, ...)
	%{printf("_vscwprintf_l")}

[[guard, wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vscwprintf_p_l([[nonnull]] wchar_t const *format,
                                      [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return _vscwprintf_p(format, args);
}

[[guard, wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _scwprintf_p_l([[nonnull]] wchar_t const *format,
                                     [[nullable]] $locale_t locale, ...)
	%{printf("_vscwprintf_p_l")}

%[insert:guarded_function(_vswprintf_c = vswprintf)]
%[insert:guarded_function(_swprintf_c = swprintf)]

[[guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vsnwprintf_s([[outp_opt(min(return, bufsize, buflen))]] wchar_t *buf,
                                    $size_t bufsize, $size_t buflen,
                                    [[nonnull]] wchar_t const *format, $va_list args) {
	(void)buflen;
	return vswprintf(buf, bufsize, format, args);
}

[[guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _snwprintf_s([[outp_opt(min(return, bufsize, buflen))]] wchar_t *buf, $size_t bufsize,
                                   $size_t buflen, [[nonnull]] wchar_t const *format, ...)
	%{printf("_vsnwprintf_s")}


[[cp_stdio, guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vfwprintf_p([[nonnull]] $FILE *stream,
                                   [[nonnull]] wchar_t const *format,
                                   $va_list args) {
	/* TODO */
	(void)stream;
	(void)format;
	(void)args;
	COMPILER_IMPURE();
	return 0;
}

[[cp_stdio, guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _fwprintf_p([[nonnull]] $FILE *stream,
                                  [[nonnull]] wchar_t const *format, ...)
	%{printf("_vfwprintf_p")}

[[cp_stdio, guard, wchar]]
[[requires(!defined(__NO_STDSTREAMS) && $has_function(_vfwprintf_p))]]
[[impl_include("<local/stdstreams.h>")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vwprintf_p([[nonnull]] wchar_t const *format, $va_list args) {
	return _vfwprintf_p(stdout, format, args);
}

[[cp_stdio, guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _wprintf_p([[nonnull]] wchar_t const *format, ...)
	%{printf("_vwprintf_p")}

[[guard, wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vswprintf_p([[outp(bufsize)]] wchar_t *buf, $size_t bufsize,
                                   [[nonnull]] wchar_t const *format, $va_list args) {
	/* TODO */
	(void)buf;
	(void)bufsize;
	(void)format;
	(void)args;
	COMPILER_IMPURE();
	return 0;
}

[[guard, wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _swprintf_p([[outp(bufsize)]] wchar_t *dst, $size_t bufsize,
                                  [[nonnull]] wchar_t const *format, ...)
	%{printf("_vswprintf_p")}

[[cp_stdio, guard, wchar, requires_function(vwprintf)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vwprintf_l([[nonnull]] wchar_t const *format,
                                  [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return vwprintf(format, args);
}

[[cp_stdio, guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _wprintf_l([[nonnull]] wchar_t const *format,
                                 [[nullable]] $locale_t locale, ...)
	%{printf("_vwprintf_l")}


[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[cp_stdio, guard, wchar, requires_function(_vwprintf_p)]]
__STDC_INT_AS_SSIZE_T _vwprintf_p_l([[nonnull]] wchar_t const *format,
                                    [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return _vwprintf_p(format, args);
}

[[cp_stdio, guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _wprintf_p_l([[nonnull]] wchar_t const *format,
                                   [[nullable]] $locale_t locale, ...)
	%{printf("_vwprintf_p_l")}


[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[cp_stdio, guard, wchar, requires_function(vwprintf)]]
__STDC_INT_AS_SSIZE_T _vwprintf_s_l([[nonnull]] wchar_t const *format,
                                    [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return vwprintf(format, args);
}

[[cp_stdio, guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _wprintf_s_l([[nonnull]] wchar_t const *format,
                                   [[nullable]] $locale_t locale, ...)
	%{printf("_vwprintf_s_l")}


[[cp_stdio, guard, wchar, requires_function(vfwprintf)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vfwprintf_l([[nonnull]] $FILE *stream, [[nonnull]] wchar_t const *format,
                                   [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return vfwprintf(stream, format, args);
}

[[cp_stdio, guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _fwprintf_l([[nonnull]] $FILE *stream, [[nonnull]] wchar_t const *format,
                                  [[nullable]] $locale_t locale, ...)
	%{printf("_vfwprintf_l")}


[[cp_stdio, guard, wchar, requires_function(_vfwprintf_p)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vfwprintf_p_l([[nonnull]] $FILE *stream,
                                     [[nonnull]] wchar_t const *format,
                                     [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return _vfwprintf_p(stream, format, args);
}

[[cp_stdio, guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _fwprintf_p_l([[nonnull]] $FILE *stream,
                                    [[nonnull]] wchar_t const *format,
                                    [[nullable]] $locale_t locale, ...)
	%{printf("_vfwprintf_p_l")}


[[cp_stdio, guard, wchar, requires_function(vfwprintf)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vfwprintf_s_l([[nonnull]] $FILE *stream,
                                     [[nonnull]] wchar_t const *format,
                                     [[nullable]] $locale_t locale,
                                     $va_list args) {
	(void)locale;
	return vfwprintf(stream, format, args);
}

[[cp_stdio, guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _fwprintf_s_l([[nonnull]] $FILE *stream,
                                    [[nonnull]] wchar_t const *format,
                                    [[nullable]] $locale_t locale, ...)
	%{printf("_vfwprintf_s_l")}


[[guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vswprintf_c_l([[outp(bufsize)]] wchar_t *dst, $size_t bufsize,
                                     [[nonnull]] wchar_t const *format,
                                     [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return vswprintf(dst, bufsize, format, args);
}

[[guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _swprintf_c_l([[outp(bufsize)]] wchar_t *dst, $size_t bufsize,
                                    [[nonnull]] wchar_t const *format,
                                    [[nullable]] $locale_t locale, ...)
	%{printf("_vswprintf_c_l")}


[[guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vswprintf_p_l([[outp(bufsize)]] wchar_t *dst, $size_t bufsize,
                                     [[nonnull]] wchar_t const *format,
                                     [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return _vswprintf_p(dst, bufsize, format, args);
}

[[guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _swprintf_p_l([[outp(bufsize)]] wchar_t *dst, $size_t bufsize,
                                    [[nonnull]] wchar_t const *format,
                                    [[nullable]] $locale_t locale, ...)
	%{printf("_vswprintf_p_l")}


[[guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vswprintf_s_l([[outp(wchar_count)]] wchar_t *dst, $size_t wchar_count,
                                     [[nonnull]] wchar_t const *format,
                                     [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return vswprintf(dst, wchar_count, format, args);
}

[[guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _swprintf_s_l([[outp(wchar_count)]] wchar_t *dst,
                                    $size_t wchar_count,
                                    [[nonnull]] wchar_t const *format,
                                    [[nullable]] $locale_t locale, ...)
	%{printf("_vswprintf_s_l")}


[[guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vsnwprintf_l([[outp(bufsize)]] wchar_t *dst, $size_t bufsize,
                                    [[nonnull]] wchar_t const *format,
                                    [[nullable]] $locale_t locale,
                                    $va_list args) {
	(void)locale;
	return vswprintf(dst, bufsize, format, args);
}

[[guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _snwprintf_l([[outp(bufsize)]] wchar_t *dst, $size_t bufsize,
                                   [[nonnull]] wchar_t const *format,
                                   [[nullable]] $locale_t locale, ...)
	%{printf("_vsnwprintf_l")}


[[guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vsnwprintf_s_l([[outp(wchar_count)]] wchar_t *dst, $size_t wchar_count,
                                      $size_t bufsize, [[nonnull]] wchar_t const *format,
                                      [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return _vsnwprintf_s(dst, wchar_count, bufsize, format, args);
}

[[guard, wchar]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _snwprintf_s_l([[outp(wchar_count)]] wchar_t *dst, $size_t wchar_count,
                                     $size_t bufsize, [[nonnull]] wchar_t const *format,
                                     [[nullable]] $locale_t locale, ...)
	%{printf("_vsnwprintf_s_l")}



%[default:section(".text.crt.dos.wchar.FILE.locked.read.scanf")]

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[ignore, cp_stdio, wchar, wunused, requires_function(vfwscanf)]]
__STDC_INT_AS_SSIZE_T _vfwscanf_l([[nonnull]] $FILE *stream, [[nonnull]] wchar_t const *format,
                                  [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return vfwscanf(stream, format, args);
}

[[cp_stdio, guard, wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _fwscanf_l([[nonnull]] $FILE *stream, [[nonnull]] wchar_t const *format,
                                 [[nullable]] $locale_t locale, ...)
	%{printf("_vfwscanf_l")}

/* %[insert:guarded_function(_vfwscanf_s_l = _vfwscanf_l)] */
%[insert:guarded_function(_fwscanf_s_l = _fwscanf_l)]

[[ignore, wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vswscanf_l([[nonnull]] wchar_t const *src,
                                  [[nonnull]] wchar_t const *format,
                                  [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return vswscanf(src, format, args);
}

[[guard, wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _swscanf_l([[nonnull]] wchar_t const *src,
                                 [[nonnull]] wchar_t const *format,
                                 [[nullable]] $locale_t locale, ...)
	%{printf("_vswscanf_l")}

/* %[insert:guarded_function(_vswscanf_s_l = _vswscanf_l)] */
%[insert:guarded_function(_swscanf_s_l = _swscanf_l)]

[[ignore, wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vsnwscanf([[inp(bufsize)]] wchar_t const *src, $size_t bufsize,
                                 [[nonnull]] wchar_t const *format, $va_list args) {
	/* TODO */
	(void)src;
	(void)bufsize;
	(void)format;
	(void)args;
	COMPILER_IMPURE();
	return 0;
}

[[guard, wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _snwscanf([[inp(bufsize)]] wchar_t const *src, $size_t bufsize,
                                [[nonnull]] wchar_t const *format, ...)
	%{printf("_vsnwscanf")}

[[ignore, wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vsnwscanf_l([[inp(bufsize)]] wchar_t const *src, $size_t bufsize,
                                   [[nonnull]] wchar_t const *format, [[nullable]] $locale_t locale,
                                   $va_list args) {
	(void)locale;
	return _vsnwscanf(src, bufsize, format, args);
}

[[guard, wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _snwscanf_l([[inp(bufsize)]] wchar_t const *src, $size_t bufsize,
                                  [[nonnull]] wchar_t const *format, [[nullable]] $locale_t locale, ...)
	%{printf("_vsnwscanf_l")}

/* %[insert:guarded_function(_vsnwscanf_s = _vsnwscanf)] */
%[insert:guarded_function(_snwscanf_s = _snwscanf)]

[[ignore, wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _vsnwscanf_s_l([[inp(bufsize)]] wchar_t const *src, $size_t bufsize,
                                     [[nonnull]] wchar_t const *format, [[nullable]] $locale_t locale,
                                     $va_list args) {
	(void)locale;
	return _vsnwscanf(src, bufsize, format, args);
}

[[guard, wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _snwscanf_s_l([[inp(bufsize)]] wchar_t const *src, $size_t bufsize,
                                    [[nonnull]] wchar_t const *format, [[nullable]] $locale_t locale, ...)
	%{printf("_vsnwscanf_s_l")}

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[ignore, cp_stdio, wchar, wunused, requires_function(vwscanf)]]
__STDC_INT_AS_SSIZE_T _vwscanf_l([[nonnull]] wchar_t const *format, [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return vwscanf(format, args);
}

[[cp_stdio, guard, wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T _wscanf_l([[nonnull]] wchar_t const *format,
                                [[nullable]] $locale_t locale, ...)
	%{printf("_vwscanf_l")}

/* %[insert:guarded_function(_vwscanf_s_l = _vwscanf_l)] */
%[insert:guarded_function(_wscanf_s_l = _wscanf_l)]


%[default:section(".text.crt.dos.wchar.FILE.locked.access")]

[[guard, wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
$FILE *_wfsopen([[nonnull]] wchar_t const *filename,
                [[nonnull]] wchar_t const *mode,
                __STDC_INT_AS_UINT_T sh_flag);

[[guard, wchar, wunused, decl_include("<bits/types.h>")]]
$FILE *_wfdopen($fd_t fd, [[nonnull]] wchar_t const *mode);

[[guard, wchar, decl_include("<bits/types.h>")]]
$errno_t _wfopen_s([[nonnull]] $FILE **pstream,
                   [[nonnull]] wchar_t const *filename,
                   [[nonnull]] wchar_t const *mode);

[[guard, wchar, decl_include("<bits/types.h>")]]
$errno_t _wfreopen_s([[nonnull]] $FILE **pstream,
                     [[nonnull]] wchar_t const *filename,
                     [[nonnull]] wchar_t const *mode,
                     $FILE *stream);

%[insert:guarded_function(_wfopen = wfopen)]
%[insert:guarded_function(_wfreopen = wfreopen)]
%[insert:guarded_function(_fgetwchar = getwchar)]
%[insert:guarded_function(_fputwchar = putwchar)]


[[decl_include("<hybrid/typecore.h>")]]
[[guard, wchar, requires_include("<__crt.h>"), impl_include("<local/stdstreams.h>")]]
[[requires($has_function(fgetws) && !defined(__NO_STDSTREAMS))]]
[[section(".text.crt.dos.wchar.FILE.locked.read.read")]]
wchar_t *_getws_s(wchar_t *buf, $size_t buflen) {
	return fgetws(buf, buflen, stdin);
}

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[guard, wchar, requires_include("<__crt.h>"), impl_include("<local/stdstreams.h>")]]
[[requires($has_function(fputws) && !defined(__NO_STDSTREAMS))]]
[[section(".text.crt.dos.wchar.FILE.locked.write.write")]]
__STDC_INT_AS_SIZE_T _putws([[nonnull]] wchar_t const *string) {
	return fputws(string, stdout);
}

[[decl_include("<hybrid/typecore.h>")]]
[[guard, wchar, wunused, section(".text.crt.dos.wchar.fs.utility")]]
wchar_t *_wtempnam([[nullable]] wchar_t const *directory,
                   [[nullable]] wchar_t const *file_prefix);

%[insert:function(_wperror = _wperror, guardName: "_CRT_WPERROR_DEFINED")]
%[insert:guarded_function(_wpopen = wpopen)]
%[insert:guarded_function(_wremove = wremove)]

[[decl_include("<bits/types.h>")]]
[[guard, wchar, section(".text.crt.dos.wchar.fs.utility")]]
$errno_t _wtmpnam_s([[outp(wchar_count)]] wchar_t *dst, $size_t wchar_count);

%[insert:guarded_function(_fgetwc_nolock = fgetwc_unlocked)]
%[insert:guarded_function(_fputwc_nolock = fputwc_unlocked)]
%[insert:guarded_function(_ungetwc_nolock = ungetwc_unlocked)]
%[insert:guarded_function(_getwc_nolock = fgetwc_unlocked)]
%[insert:guarded_function(_putwc_nolock = fputwc_unlocked)]

%#endif /* !_WSTDIO_DEFINED */


%#ifndef _WSTDLIB_DEFINED
%#define _WSTDLIB_DEFINED
%[insert:guarded_function(_wcstol_l = wcstol_l)]
%[insert:guarded_function(_wcstoul_l = wcstoul_l)]
%#ifndef __NO_FPU
%[insert:guarded_function(_wcstof_l = wcstof_l)]
%[insert:guarded_function(_wcstod_l = wcstod_l)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:guarded_function(_wcstold_l = wcstold_l)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%[insert:extern(_wtof)]
%[insert:extern(_wtof_l)]
%#endif /* !__NO_FPU */
%[insert:extern(_itow)]
%[insert:extern(_ltow)]
%[insert:extern(_ultow)]
%[insert:extern(_i64tow)]
%[insert:extern(_ui64tow)]
%[insert:extern(_itow_s)]
%[insert:extern(_ltow_s)]
%[insert:extern(_ultow_s)]
%[insert:extern(_i64tow_s)]
%[insert:extern(_ui64tow_s)]
%[insert:extern(_wgetenv)]
%[insert:extern(_wgetenv_s)]
%[insert:extern(_wdupenv_s)]
%[insert:function(_wsystem = wsystem, guardName: "_CRT_WSYSTEM_DEFINED")]
%[insert:guarded_function(_wtoi = wtoi)]
%[insert:guarded_function(_wtol = wtol)]
%[insert:extern(_wtoi64)]
%[insert:guarded_function(_wcstoi64 = wcsto64)]
%[insert:guarded_function(_wcstoui64 = wcstou64)]
%[insert:extern(_wtoi_l)]
%[insert:extern(_wtol_l)]
%[insert:extern(_wtoi64_l)]
%[insert:guarded_function(_wcstoi64_l = wcsto64_l)]
%[insert:guarded_function(_wcstoui64_l = wcstou64_l)]
%#ifdef __LONGLONG
%[insert:guarded_function(_wcstoll_l = wcstoll_l)]
%[insert:guarded_function(_wcstoull_l = wcstoull_l)]
%[insert:guarded_function(_wtoll = wtoll)]
%[insert:extern(_wtoll_l)]
%#endif /* __LONGLONG */
%#endif /* !_WSTDLIB_DEFINED */

%#ifndef _WSTDLIBP_DEFINED
%#define _WSTDLIBP_DEFINED 1
%[insert:extern(_wfullpath)]
%[insert:extern(_wmakepath_s)]
%[insert:extern(_wmakepath)]
%[insert:function(_wperror = _wperror, guardName: "_CRT_WPERROR_DEFINED")]
%[insert:extern(_wputenv)]
%[insert:extern(_wputenv_s)]
%[insert:extern(_wsearchenv_s)]
%[insert:extern(_wsearchenv)]
%[insert:extern(_wsplitpath)]
%[insert:extern(_wsplitpath_s)]
%#endif /* !_WSTDLIBP_DEFINED */

%#endif /* __USE_DOS */


%{

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_KOS
#if defined(_FORMAT_PRINTER_H) && !defined(_PARTS_WCHAR_FORMAT_PRINTER_H)
#include <parts/wchar/format-printer.h>
#endif /* _FORMAT_PRINTER_H && !_PARTS_WCHAR_FORMAT_PRINTER_H */

#if defined(_PROCESS_H) && !defined(_PARTS_WCHAR_PROCESS_H)
#include <parts/wchar/process.h>
#endif /* _PROCESS_H && !_PARTS_WCHAR_PROCESS_H */

#if defined(_UTIME_H) && !defined(_PARTS_WCHAR_UTIME_H)
#include <parts/wchar/utime.h>
#endif /* _UTIME_H && !_PARTS_WCHAR_UTIME_H */

#if defined(_UNISTD_H) && !defined(_PARTS_WCHAR_UNISTD_H)
#include <parts/wchar/unistd.h>
#endif /* _UNISTD_H && !_PARTS_WCHAR_UNISTD_H */

#if defined(_STDLIB_H) && !defined(_PARTS_WCHAR_STDLIB_H)
#include <parts/wchar/stdlib.h>
#endif /* _STDLIB_H && !_PARTS_WCHAR_STDLIB_H */
#endif /* __USE_KOS */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_WCHAR_H)
#include <parts/uchar/wchar.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_WCHAR_H */
#endif /* __USE_KOS */

}

