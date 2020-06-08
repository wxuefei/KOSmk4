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

#include <asm/stdio.h> /* __WEOF */
#include <bits/mbstate.h>

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

/* Define `struct tm' */
__NAMESPACE_STD_BEGIN
#ifndef __std_tm_defined
#define __std_tm_defined 1
#ifdef __tm_defined
__NAMESPACE_GLB_USING(tm)
#else /* __tm_defined */
struct tm {
	int         tm_sec;      /* seconds [0, 61]. */
	int         tm_min;      /* minutes [0, 59]. */
	int         tm_hour;     /* hour [0, 23]. */
	int         tm_mday;     /* day of month [1, 31]. */
	int         tm_mon;      /* month of year [0, 11]. */
	int         tm_year;     /* years since 1900. */
	int         tm_wday;     /* day of week [0, 6] (Sunday = 0). */
	int         tm_yday;     /* day of year [0, 365]. */
	int         tm_isdst;    /* daylight savings flag. */
#ifdef __CRT_GLC
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* __CRT_GLC */
};
#endif /* !__tm_defined */
#endif /* !__std_tm_defined */
#ifndef __std_size_t_defined
#define __std_size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__std_size_t_defined */
#ifndef __std_wint_t_defined
#define __std_wint_t_defined 1
typedef __WINT_TYPE__ wint_t;
#endif /* !__std_wint_t_defined */
__NAMESPACE_STD_END

#ifndef __STRUCT_TM
#define __STRUCT_TM struct __NAMESPACE_STD_SYM tm
#endif /* !__STRUCT_TM */

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __tm_defined
#define __tm_defined 1
#undef __STRUCT_TM
#define __STRUCT_TM struct tm
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



%[default_impl_section("{.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs}")];
[[std, ATTR_WUNUSED, ATTR_CONST, wchar]]
wint_t btowc(int ch) {
	if (ch >= 0 && ch <= 0x7f)
		return (wint_t)ch;
#if __SIZEOF_WCHAR_T__ == 4
	return (__CCAST(__WINT_TYPE__)0xffffffffu);
#else /* __SIZEOF_WCHAR_T__ == 4 */
	return (__CCAST(__WINT_TYPE__)0xffff);
#endif /* __SIZEOF_WCHAR_T__ != 4 */
};

%(auto_source)#include <stdio.h>
;

[[std, ATTR_WUNUSED, ATTR_CONST]]
[[impl_include("<asm/stdio.h>")]]
int wctob(wint_t ch) {
	if (ch >= 0 && ch <= 0x7f)
		return (int)ch;
	return EOF;
};

[[std, wchar, export_alias("__mbrtowc")]]
[[decl_include("<bits/mbstate.h>"), impl_prefix(
#ifndef ____local_mbrtowc_ps_defined
#define ____local_mbrtowc_ps_defined 1
__LOCAL_LIBC_DATA(mbrtowc_ps) mbstate_t mbrtowc_ps = __MBSTATE_INIT;
#endif /* !____local_mbrtowc_ps_defined */
), impl_include("<parts/errno.h>")]]
size_t mbrtowc([[nullable]] wchar_t *pwc,
               [[inp_opt(maxlen)]] char const *__restrict str, size_t maxlen,
               [[nullable]] mbstate_t *mbs) {
	size_t error;
	if (!mbs)
		mbs = &mbrtowc_ps;
	if (!str) {
		mbs->@__word@ = 0;
		return 0;
	}
	if (!maxlen || !*str)
		return 0;
#if __SIZEOF_WCHAR_T__ == 2
	error = unicode_c8toc16((char16_t *)pwc, str, maxlen, mbs);
#else /* __SIZEOF_WCHAR_T__ == 2 */
	error = unicode_c8toc32((char32_t *)pwc, str, maxlen, mbs);
#endif /* __SIZEOF_WCHAR_T__ != 2 */
#ifdef EILSEQ
	if (error == (size_t)-1)
		__libc_seterrno(EILSEQ);
#endif /* EILSEQ */
	return error;
};


[[std, wchar, impl_include("<parts/errno.h>")]]
size_t wcrtomb(char *__restrict str, wchar_t wc,
               [[nullable]] mbstate_t *mbs) {
	char *endptr;
	size_t result;
#if __SIZEOF_WCHAR_T__ == 2
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
#ifdef EILSEQ
			__libc_seterrno(EILSEQ);
#endif /* EILSEQ */
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
#else /* __SIZEOF_WCHAR_T__ == 2 */
	/* unicode_c32toc8() */
	(void)mbs;
	if (!str)
		return 1;
	endptr = unicode_writeutf8(str, (char32_t)wc);
#endif /* __SIZEOF_WCHAR_T__ != 2 */
	result = (size_t)(endptr - str);
	return result;
};

[[std, ATTR_WUNUSED, wchar, export_alias("__mbrlen")]]
size_t mbrlen([[inp_opt(maxlen)]] char const *__restrict str, size_t maxlen,
              [[nullable]] mbstate_t *mbs) {
	wchar_t wc;
	return mbrtowc(&wc, str, maxlen, mbs);
};

[[std, wchar]]
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
[[section({.text.crt.wchar.unicode.static.convert|.text.crt.dos.wchar.unicode.static.convert})]]
wcstol:([[nonnull]] wchar_t const *__restrict nptr,
        [[nullable]] wchar_t **endptr, int base) -> long %{generate(str2wcs)};

[[std, guard, wchar]]
[[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("wcstoull", "wcstouq")]]
[[if(__SIZEOF_LONG__ == 4), alias("wcstou32")]]
[[if(__SIZEOF_LONG__ == 8), alias("wcstou64", "_wcstoui64")]]
[[if(__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__), alias("wcstoumax")]]
[[section({.text.crt.wchar.unicode.static.convert|.text.crt.dos.wchar.unicode.static.convert})]]
wcstoul:([[nonnull]] wchar_t const *__restrict nptr,
         [[nullable]] wchar_t **endptr, int base) -> unsigned long %{generate(str2wcs)};

[[std, ATTR_WUNUSED, ATTR_PURE, decl_include("<bits/mbstate.h>")]]
[[section("{.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs}")]]
int mbsinit([[nullable]] mbstate_t const *mbs) {
	return !mbs || __MBSTATE_ISINIT(mbs);
};

[[std, wchar, ATTR_WUNUSED, ATTR_PURE]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
int wmemcmp:([[inp(num_chars)]] wchar_t const *s1,
             [[inp(num_chars)]] wchar_t const *s2,
             size_t num_chars) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return memcmpw(s1, s2, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return memcmpl(s1, s2, num_chars);
@@pp_else@@
	return memcmp(s1, s2, num_chars * sizeof(wchar_t));
@@pp_endif@@
};

[[std, wchar, nonnull]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("memcpyw")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("memcpyl")]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
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
};

[[std, wchar, nonnull]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("memmovew")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("memmovel")]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
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
};

[[std, wchar]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("memsetw")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("memsetl")]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
[[nonnull]] wchar_t *wmemset([[outp(num_chars)]] wchar_t *dst, wchar_t filler, size_t num_chars) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)memsetw(dst, (u16)filler, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)memsetl(dst, (u32)filler, num_chars);
@@pp_else@@
	return (wchar_t *)memset(dst, (int)filler, num_chars * sizeof(wchar_t));
@@pp_endif@@
};

[[std, guard, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
[[nonnull]] wchar_t *wcscpy([[nonnull]] wchar_t *__restrict buf,
                            [[nonnull]] wchar_t const *__restrict src) {
	return wmemcpy(buf, src, wcslen(src) + 1);
}

[[std, guard, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
[[nonnull]] wchar_t *wcscat([[nonnull]] wchar_t *__restrict buf,
                            [[nonnull]] wchar_t const *__restrict src) {
	wmemcpy(wcsend(buf), src, wcslen(src) + 1);
	return buf;
}

[[std, guard, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
[[nonnull]] wchar_t *wcsncat([[nonnull]] wchar_t *__restrict buf,
                             [[inp(wcsnlen(src, buflen))]] wchar_t const *__restrict src,
                             $size_t buflen) {
	size_t srclen = wcsnlen(src, buflen);
	wchar_t *dst = wcsend(buf);
	wmemcpy(dst, src, srclen);
	dst[srclen] = '\0';
	return buf;
}

[[std, guard, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
[[nonnull]] wchar_t *wcsncpy([[nonnull]] wchar_t *__restrict buf,
                             [[inp(wcsnlen(src, buflen))]] wchar_t const *__restrict src,
                             $size_t buflen) {
	size_t srclen = wcsnlen(src, buflen);
	wmemcpy(buf, src, srclen);
	wmemset(buf+srclen, '\0', buflen - srclen);
	return buf;
}


[[std, guard, ATTR_WUNUSED, ATTR_PURE, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
wcscmp:([[nonnull]] wchar_t const *s1, [[nonnull]] wchar_t const *s2) -> int %{generate(str2wcs)}

[[std, guard, ATTR_WUNUSED, ATTR_PURE, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
wcsncmp:([[nonnull]] wchar_t const *s1, [[nonnull]] wchar_t const *s2, $size_t maxlen) -> int %{generate(str2wcs)}

[[std, guard, ATTR_WUNUSED, ATTR_PURE, wchar]]
[[section("{.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory}")]]
wcscoll:([[nonnull]] wchar_t const *s1, [[nonnull]] wchar_t const *s2) -> int %{generate(str2wcs)}

[[std, guard, wchar]]
[[section("{.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory}")]]
wcsxfrm:([[nonnull]] wchar_t *dst, [[inp(maxlen)]] wchar_t const *__restrict src, $size_t maxlen) -> $size_t %{generate(str2wcs)}


%[default_impl_section({.text.crt.wchar.FILE.locked.read.getc|.text.crt.dos.wchar.FILE.locked.read.getc})]
[[cp_stdio, std, guard, wchar, requires_include("<__crt.h>")]]
[requires(!defined(__NO_STDSTREAMS) && $has_function(fgetwc))]
[impl_include("<local/stdstreams.h>")][[userimpl]][export_alias(_fgetwchar)]
getwchar:() -> wint_t {
	return fgetwc(stdin);
}

[[cp_stdio, std, guard, wchar, export_alias("getwc")]]
fgetwc:([[nonnull]] FILE *__restrict stream) -> wint_t;
[[std, guard]] getwc:(*) = fgetwc;

[section({.text.crt.wchar.FILE.locked.write.putc|.text.crt.dos.wchar.FILE.locked.write.putc})]
[[cp_stdio, std, guard, wchar, requires_include("<__crt.h>")]]
[requires(!defined(__NO_STDSTREAMS) && $has_function(fputwc))]
[impl_include("<local/stdstreams.h>")][[userimpl]][export_alias(_fputwchar)]
putwchar:(wchar_t wc) -> wint_t {
	return fputwc(wc, stdout);
}

[[section({.text.crt.wchar.FILE.locked.write.putc|.text.crt.dos.wchar.FILE.locked.write.putc})]]
[[cp_stdio, std, guard, wchar, export_alias("putwc")]]
fputwc:(wchar_t wc, [[nonnull]] FILE *stream) -> wint_t;

[[std, guard]] putwc:(*) = fputwc;



[section({.text.crt.wchar.FILE.locked.read.read|.text.crt.dos.wchar.FILE.locked.read.read})]
[[cp_stdio, std, guard, wchar, ATTR_WUNUSED]][alias(fgetws_unlocked, _fgetws_nolock)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fgetws_unlocked, _fgetws_nolock)]
[requires($has_function(fgetwc) && $has_function(ungetwc) && $has_function(ferror))][[userimpl]]
[[impl_include("<parts/errno.h>")]]
[impl_include("<asm/stdio.h>")][[userimpl]]
fgetws:([[outp(bufsize)]] wchar_t *__restrict buf,
        __STDC_INT_AS_SIZE_T bufsize,
        [[nonnull]] FILE *__restrict stream) -> wchar_t * {
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
#ifdef ERANGE
		__libc_seterrno(ERANGE);
#endif /* ERANGE */
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



[section({.text.crt.wchar.FILE.locked.write.write|.text.crt.dos.wchar.FILE.locked.write.write})]
[[cp_stdio, std, guard, wchar, userimpl]]
[requires($has_function(file_wprinter))][alias(fputws_unlocked, _fputws_nolock)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fputws_unlocked, _fputws_nolock)]
fputws:([[nonnull]] wchar_t const *__restrict string, [[nonnull]] FILE *__restrict stream) -> __STDC_INT_AS_SIZE_T {
	__STDC_INT_AS_SIZE_T result;
	result = file_wprinter(stream, string, wcslen(string));
	return result;
}

[section({.text.crt.wchar.FILE.locked.write.putc|.text.crt.dos.wchar.FILE.locked.write.putc})]
[[std, guard, wchar]][alias(ungetwc_unlocked)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(ungetwc_unlocked)]
ungetwc:(wint_t wc, [[nonnull]] FILE *stream) -> wint_t;

[section({.text.crt.wchar.unicode.static.format.strftime|.text.crt.dos.wchar.unicode.static.format.strftime})]
[[std, guard, wchar, userimpl]]
wcsftime:([outp(min(return,buflen))] wchar_t *__restrict buf, size_t buflen,
          [[nonnull]] wchar_t const *__restrict format,
          [[nonnull]] struct tm const *__restrict tp) -> size_t {
	if (buflen)
		*buf = 0;
	/* TODO */
	(void)format;
	(void)tp;
	return 0;
}

%[default_impl_section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]
%(std)
%(std)#if !defined(__USE_DOS) || defined(__USE_ISOC95)
[[std, guard, wchar, no_crt_self_import]]
[[if(!defined(__CRT_DOS_PRIMARY)), preferred_alias("wcstok")]]
[[alias("wcstok_s")]]
wcstok:([[nullable]] wchar_t *string,
        [[nonnull]] wchar_t const *__restrict delim,
        [[nonnull]] wchar_t **__restrict save_ptr) -> wchar_t *
	%{generate(str2wcs("strtok_r"))}
%(std)#endif

[[std, guard, ATTR_WUNUSED, ATTR_PURE, wchar]]
wcslen:([[nonnull]] wchar_t const *__restrict string) -> $size_t %{generate(str2wcs)}

[[std, guard, ATTR_WUNUSED, ATTR_PURE, wchar]]
wcsspn:([[nonnull]] wchar_t const *haystack, [[nonnull]] wchar_t const *accept) -> $size_t %{generate(str2wcs)}
[[std, guard, ATTR_WUNUSED, ATTR_PURE, wchar]]
wcscspn:([[nonnull]] wchar_t const *haystack, [[nonnull]] wchar_t const *reject) -> $size_t %{generate(str2wcs)}

[[std, guard, ATTR_WUNUSED, ATTR_PURE, wchar]]
wchar_t *wcschr([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle)
	[([[nonnull]] wchar_t *__restrict haystack, wchar_t needle): wchar_t *]
	[([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle): wchar_t const *]
	%{generate(str2wcs)}

[[std, guard, ATTR_WUNUSED, ATTR_PURE, wchar]]
wchar_t *wcsrchr([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle)
	[([[nonnull]] wchar_t *__restrict haystack, wchar_t needle): wchar_t *]
	[([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle): wchar_t const *]
	%{generate(str2wcs)}

[[std, guard, ATTR_WUNUSED, ATTR_PURE, wchar]]
wchar_t *wcspbrk([[nonnull]] wchar_t const *haystack, [[nonnull]] wchar_t const *accept)
	[([[nonnull]] wchar_t *haystack, [[nonnull]] wchar_t const *accept): wchar_t *]
	[([[nonnull]] wchar_t const *haystack, [[nonnull]] wchar_t const *accept): wchar_t const *]
	%{generate(str2wcs)}

[[std, guard, ATTR_WUNUSED, ATTR_PURE, export_alias("wcswcs"), wchar]]
wchar_t *wcsstr([[nonnull]] wchar_t const *haystack, [[nonnull]] wchar_t const *needle)
	[([[nonnull]] wchar_t *haystack, [[nonnull]] wchar_t *needle): wchar_t *]
	[([[nonnull]] wchar_t const *haystack, [[nonnull]] wchar_t const *needle): wchar_t const *]
	%{generate(str2wcs)}

[[std, ATTR_WUNUSED, ATTR_PURE, wchar]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("memchrw")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("memchrl")]]
wchar_t *wmemchr([[inp(num_chars)]] wchar_t const *__restrict haystack, wchar_t needle, size_t num_chars)
	[([[inp(num_chars)]] wchar_t *__restrict haystack, wchar_t needle, size_t num_chars): wchar_t *]
	[([[inp(num_chars)]] wchar_t const *__restrict haystack, wchar_t needle, size_t num_chars): wchar_t const *]
{
#if __SIZEOF_WCHAR_T__ == 2
	return (wchar_t *)memchrw(haystack, needle, num_chars);
#elif __SIZEOF_WCHAR_T__ == 4
	return (wchar_t *)memchrl(haystack, needle, num_chars);
#else
	return (wchar_t *)memchr(haystack, (int)needle, num_chars * sizeof(wchar_t));
#endif
}

%(std)#if defined(__USE_ISOC95) || defined(__USE_UNIX98)
[[std, guard]]
[section({.text.crt.wchar.FILE.locked.utility|.text.crt.dos.wchar.FILE.locked.utility})]
fwide:([[nonnull]] FILE *fp, int mode) -> int {
	(void)fp;
	(void)mode;
	COMPILER_IMPURE();
	return 0;
}
%(std)#endif /* __USE_ISOC95 || __USE_UNIX98 */

%(std)
%(std)#if defined(__USE_ISOC95) || defined(__USE_UNIX98) || defined(__USE_DOS)
[[cp_stdio, std, guard]][ATTR_LIBC_WPRINTF(2, 3)][[wchar]]
[section({.text.crt.wchar.FILE.locked.write.printf|.text.crt.dos.wchar.FILE.locked.write.printf})]
fwprintf:([[nonnull]] FILE *__restrict stream, [[nonnull]] wchar_t const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
	%{printf("vfwprintf")}

[[cp_stdio, std, guard]][ATTR_LIBC_WPRINTF(2, 0)][[wchar]][requires_dependent_function(file_wprinter)]
[section({.text.crt.wchar.FILE.locked.write.printf|.text.crt.dos.wchar.FILE.locked.write.printf})][[userimpl]]
vfwprintf:([[nonnull]] FILE *__restrict stream, [[nonnull]] wchar_t const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	return (__STDC_INT_AS_SSIZE_T)format_vwprintf(&file_wprinter, stream, format, args);
}

[[cp_stdio, std, guard]][ATTR_LIBC_WPRINTF(1, 2)][[wchar]]
[section({.text.crt.wchar.FILE.locked.write.printf|.text.crt.dos.wchar.FILE.locked.write.printf})]
wprintf:([[nonnull]] wchar_t const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
	%{printf("vwprintf")}

[[cp_stdio, std, guard]][ATTR_LIBC_WPRINTF(1, 0)][[wchar]]
[[requires_include("<__crt.h>")]]
[requires($has_function(vfwprintf) && !defined(__NO_STDSTREAMS))]
[impl_include("<local/stdstreams.h>")][[userimpl]]
[section({.text.crt.wchar.FILE.locked.write.printf|.text.crt.dos.wchar.FILE.locked.write.printf})]
vwprintf:([[nonnull]] wchar_t const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	return vfwprintf(stdout, format, args);
}

[[cp_stdio, std, guard]][ATTR_LIBC_WSCANF(2, 3)][[wchar]]
[section("{.text.crt.wchar.FILE.locked.read.scanf|.text.crt.dos.wchar.FILE.locked.read.scanf}")]
fwscanf:([[nonnull]] FILE *__restrict stream, [[nonnull]] wchar_t const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
	%{printf("vfwscanf")}
[[cp_stdio, std, guard]][ATTR_LIBC_WSCANF(1, 2)][[wchar]]
[section("{.text.crt.wchar.FILE.locked.read.scanf|.text.crt.dos.wchar.FILE.locked.read.scanf}")]
wscanf:([[nonnull]] wchar_t const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
	%{printf("vwscanf")}

[[std, guard]][ATTR_LIBC_WSCANF(2, 3)][[wchar]]
[section("{.text.crt.wchar.unicode.static.format.scanf|.text.crt.dos.wchar.unicode.static.format.scanf}")]
swscanf:([[nonnull]] wchar_t const *__restrict src, [[nonnull]] wchar_t const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
	%{printf("vswscanf")}

[[std, guard]][ATTR_LIBC_WPRINTF(3, 0)][[wchar]]
[section({.text.crt.wchar.unicode.static.format.printf|.text.crt.dos.wchar.unicode.static.format.printf})]
vswprintf:([outp_opt(min(return+1,buflen))] wchar_t *__restrict buf, size_t buflen,
           [[nonnull]] wchar_t const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	if (buflen)
		*buf = 0;
	/* TODO: format_wprintf() */
	(void)format;
	(void)args;
	return 0;
}

[[std, guard]][ATTR_LIBC_WPRINTF(3, 4)][[wchar]][export_alias(_swprintf)]
[section({.text.crt.wchar.unicode.static.format.printf|.text.crt.dos.wchar.unicode.static.format.printf})]
swprintf:([outp_opt(min(return+1,buflen))] wchar_t *__restrict buf, size_t buflen,
          [[nonnull]] wchar_t const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
	%{printf("vswprintf")}

%(std)#endif /* __USE_ISOC95 || __USE_UNIX98 || __USE_DOS */

%[default_impl_section({.text.crt.wchar.unicode.static.convert|.text.crt.dos.wchar.unicode.static.convert})]
%(std)

%(std,c,ccompat)#ifndef __NO_FPU
[[std, guard, wchar]]
wcstod:([[nonnull]] wchar_t const *__restrict nptr,
        [[nullable]] wchar_t **endptr) -> double %{generate(str2wcs)}
%(std,c,ccompat)#endif /* !__NO_FPU */
%(std)#ifdef __USE_ISOC99
%(std,c,ccompat)#ifndef __NO_FPU
[[std, guard, ATTR_PURE, wchar]]
wcstof:([[nonnull]] wchar_t const *__restrict nptr, [[nullable]] wchar_t **endptr) -> float
	%{generate(str2wcs)}
%(std)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, guard, ATTR_PURE, wchar]]
wcstold:([[nonnull]] wchar_t const *__restrict nptr, [[nullable]] wchar_t **endptr) -> __LONGDOUBLE
	%{generate(str2wcs)}
%(std,c,ccompat)#endif /* !__NO_FPU */
%(std)#endif /* __COMPILER_HAVE_LONGDOUBLE */

[[std, guard, wchar, export_alias("wcstoq")]]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("wcstol")]
[if(__SIZEOF_LONG_LONG__ == 8), alias("wcsto64", "_wcstoi64")]
[if(__SIZEOF_LONG_LONG__ == 4), alias("wcsto32")]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias("wcstoimax")]
__LONGLONG wcstoll([[nonnull]] wchar_t const *__restrict nptr,
                   [[nullable]] wchar_t **endptr, int base)
	%{generate(str2wcs)}

[[std, guard, wchar, export_alias("wcstouq")]]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("wcstoul")]
[if(__SIZEOF_LONG_LONG__ == 4), alias("wcstou32")]
[if(__SIZEOF_LONG_LONG__ == 8), alias("wcstou64", "_wcstoui64")]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias("wcstoumax")]
__ULONGLONG wcstoull([[nonnull]] wchar_t const *__restrict nptr,
                     [[nullable]] wchar_t **endptr, int base)
	%{generate(str2wcs)}

%[default_impl_section("{.text.crt.wchar.FILE.locked.read.scanf|.text.crt.dos.wchar.FILE.locked.read.scanf}")]
[[cp_stdio, std, guard, wchar, ATTR_WUNUSED, ATTR_LIBC_WSCANF(2, 0)]]
__STDC_INT_AS_SIZE_T vfwscanf([[nonnull]] FILE *__restrict stream,
                              [[nonnull]] wchar_t const *__restrict format, $va_list args);
/* TODO: format_scanf() implementation for `vfwscanf'! */

[[cp_stdio, std, guard, wchar, ATTR_WUNUSED, ATTR_LIBC_WSCANF(1, 0)]]
[[requires_include("<__crt.h>"), impl_include("<local/stdstreams.h>")]]
[[userimpl, requires($has_function(vfwscanf) && !defined(__NO_STDSTREAMS))]]
__STDC_INT_AS_SIZE_T vwscanf([[nonnull]] wchar_t const *__restrict format, $va_list args) {
	return vfwscanf(stdin, format, args);
}

%[default_impl_section("{.text.crt.wchar.unicode.static.format.scanf|.text.crt.dos.wchar.unicode.static.format.scanf}")]
[[std, guard, ATTR_WUNUSED, wchar, ATTR_LIBC_WSCANF(2, 0)]]
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




%{
#ifndef __std_wcstok_defined
#define __std_wcstok_defined 1
/* Define wcstok() incorrectly, the same way DOS does. */
#if defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE_wcstok)
__NAMESPACE_STD_BEGIN
__CDECLARE(__ATTR_NONNULL((2)),wchar_t *,__NOTHROW_NCX,wcstok,(wchar_t *__string,wchar_t const *__restrict __delim),(__string,__delim))
__NAMESPACE_STD_END
#else /* __CRT_DOS_PRIMARY && __CRT_HAVE_wcstok */
__NAMESPACE_INT_BEGIN
#ifdef __CRT_HAVE_wcstok_s
__CREDIRECT(__ATTR_NONNULL((2,3)),wchar_t *,__NOTHROW_NCX,__crt_wcstok,(wchar_t *__string,wchar_t const *__restrict __delim,wchar_t **__restrict __save_ptr),wcstok_s,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok)
__CREDIRECT(__ATTR_NONNULL((2,3)),wchar_t *,__NOTHROW_NCX,__crt_wcstok,(wchar_t *__string,wchar_t const *__restrict __delim,wchar_t **__restrict __save_ptr),wcstok,(__string,__delim,__save_ptr))
#else /* ... */
__NAMESPACE_INT_END
#include <local/wchar/wcstok.h>
__NAMESPACE_INT_BEGIN
#define __crt_wcstok(string, delim, save_ptr) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))(string, delim, save_ptr)
#endif /* !... */
__LOCAL_LIBC_DATA(__wcstok_save_ptr) char *__wcstok_save_ptr = __NULLPTR;
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
__LOCAL_LIBC(wcstok) __ATTR_NONNULL((2)) wchar_t *
__NOTHROW_NCX(__LIBCCALL wcstok)(wchar_t *__string, wchar_t const *__restrict __delim) {
	return __NAMESPACE_LOCAL_SYM __crt_wcstok(__string, __delim, &__NAMESPACE_LOCAL_SYM __wcstok_save_ptr);
}
__NAMESPACE_STD_END
#endif /* !__CRT_DOS_PRIMARY || !__CRT_HAVE_wcstok */
#endif /* !__std_wcstok_defined */
#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __wcstok_defined
#define __wcstok_defined 1
__NAMESPACE_STD_USING(wcstok)
#endif /* !__wcstok_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */
}


__mbrlen(*) = mbrlen;


%
%#ifdef __USE_XOPEN2K8
[[ATTR_WUNUSED, ATTR_PURE, wchar, export_alias("_wcsicmp", "wcsicmp")]]
[[section("{.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory}")]]
int wcscasecmp([[nonnull]] wchar_t const *s1,
               [[nonnull]] wchar_t const *s2)
	%{generate(str2wcs)}

[[ATTR_WUNUSED, ATTR_PURE, wchar, export_alias("_wcsnicmp", "wcsnicmp")]]
[[section("{.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory}")]]
int wcsncasecmp([[nonnull]] wchar_t const *s1,
                [[nonnull]] wchar_t const *s2, $size_t maxlen)
	%{generate(str2wcs)}

[[ATTR_WUNUSED, ATTR_PURE, wchar, export_alias("_wcsicmp_l", "wcsicmp_l", "__wcscasecmp_l")]]
[[section("{.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory}")]]
wcscasecmp_l:([[nonnull]] wchar_t const *s1, [[nonnull]] wchar_t const *s2, $locale_t locale) -> int %{generate(str2wcs)}

[[ATTR_WUNUSED, ATTR_PURE, wchar, export_alias("_wcsnicmp_l", "wcsnicmp_l", "__wcsncasecmp_l")]]
[[section("{.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory}")]]
int wcsncasecmp_l([[nonnull]] wchar_t const *s1,
                  [[nonnull]] wchar_t const *s2,
                  $size_t maxlen, $locale_t locale)
	%{generate(str2wcs)}

[alias(_wcscoll_l)][[ATTR_WUNUSED, ATTR_PURE, wchar]][export_alias(__wcscoll_l)]
[[section("{.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory}")]]
int wcscoll_l([[nonnull]] wchar_t const *s1,
              [[nonnull]] wchar_t const *s2,
              $locale_t locale)
	%{generate(str2wcs)}

[alias(_wcsxfrm_l)][[wchar, userimpl]][export_alias("__wcsxfrm_l")]
[[section("{.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory}")]]
$size_t wcsxfrm_l(wchar_t *dst, [[nonnull]] wchar_t const *__restrict src, $size_t maxlen, $locale_t locale)
	%{generate(str2wcs)}

[[wchar, section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
[[nonnull]] wchar_t *wcpcpy([[nonnull]] wchar_t *__restrict dst,
                            [[nonnull]] wchar_t const *__restrict src) {
	return wmempcpy(dst, src, wcslen(src) + 1);
}

[[wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
[[nonnull]] wchar_t *wcpncpy([[nonnull]] wchar_t *__restrict buf,
                             [[nonnull]] wchar_t const *__restrict src,
                             $size_t buflen) {
	$size_t srclen = wcsnlen(src, buflen);
	wmemcpy(buf, src, srclen);
	wmemset(buf + srclen, '\0', ($size_t)(buflen - srclen));
	return buf + srclen;
}

[[wchar, section("{.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs}")]]
$size_t mbsnrtowcs([[nullable]] wchar_t *dst,
                   [[nonnull]] char const **__restrict psrc, $size_t nmc, $size_t len,
                   [[nullable]] $mbstate_t *mbs);

[[wchar, section("{.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs}")]]
$size_t wcsnrtombs([[nullable]] char *dst,
                   [[nonnull]] wchar_t const **__restrict psrc, $size_t nwc, $size_t len,
                   [[nullable]] $mbstate_t *mbs);

[[wchar, section("{.text.crt.wchar.FILE.locked.access|.text.crt.dos.wchar.FILE.locked.access}")]]
$FILE *open_wmemstream(wchar_t **bufloc, $size_t *sizeloc);
%#endif /* __USE_XOPEN2K8 */

%
%#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)

[[guard, ATTR_WUNUSED, ATTR_PURE, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
$size_t wcsnlen([[nonnull]] wchar_t const *__restrict string, $size_t maxlen)
	%{generate(str2wcs)}

[[ATTR_WUNUSED, crt_dosname("_wcsdup")]]
[[ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC, wchar, guard, userimpl]]
[[section("{.text.crt.wchar.heap.strdup|.text.crt.dos.wchar.heap.strdup}")]]
wchar_t *wcsdup([[nonnull]] wchar_t const *__restrict string)
	%{generate(str2wcs)}

%#endif /* __USE_XOPEN2K8 || __USE_DOS */

%
%#ifdef __USE_XOPEN
[[section("{.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs}")]]
[[impl_include("<libc/unicode.h>"), userimpl, ATTR_CONST, ATTR_WUNUSED, wchar]]
int wcwidth(wchar_t ch) {
#if __SIZEOF_WCHAR_T__ == 2
	if (ch >= UTF16_HIGH_SURROGATE_MIN &&
	    ch <= UTF16_LOW_SURROGATE_MAX)
		return 0;
#endif /* __SIZEOF_WCHAR_T__ == 2 */
	if (@__libc_unicode_isprint@(ch))
		return 1;
	if (ch == 0)
		return 0;
	return -1;
}

[[ATTR_WUNUSED, wchar, userimpl, ATTR_PURE]]
[[section("{.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs}")]]
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
[[guard]] wcswcs(*) = wcsstr;
%#endif /* __USE_XOPEN || __USE_DOS */

%
%#ifdef __USE_GNU
@@Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found.
[[ATTR_PURE, ATTR_WUNUSED, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
wchar_t *wcschrnul([[nonnull]] wchar_t const *haystack, wchar_t needle)
	[([[nonnull]] wchar_t *__restrict haystack, wchar_t needle): wchar_t *]
	[([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle): wchar_t const *]
	%{generate(str2wcs)}



[[ATTR_RETNONNULL, wchar]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("mempcpyw")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("mempcpyl")]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
wchar_t *wmempcpy([[outp(num_chars)]] wchar_t *__restrict dst,
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

[[std, ATTR_RETNONNULL, wchar]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("mempmovew")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("mempmovel")]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
wmempmove:([[outp(num_chars)]] wchar_t *dst,
           [[inp(num_chars)]] wchar_t const *src,
           $size_t num_chars) -> wchar_t * {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)mempmovew(dst, src, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)mempmovel(dst, src, num_chars);
@@pp_else@@
	return (wchar_t *)mempmove(dst, src, num_chars * sizeof(wchar_t));
@@pp_endif@@
}

[[ATTR_PURE, ATTR_WUNUSED, wchar, export_alias("_wcstol_l", "__wcstol_l")]]
[[section("{.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert}")]]
long wcstol_l([[nonnull]] wchar_t const *__restrict nptr,
              wchar_t **endptr, int base, $locale_t locale)
	%{generate(str2wcs)}

[[ATTR_PURE, ATTR_WUNUSED, wchar, export_alias("_wcstoul_l", "__wcstoul_l")]]
[[section("{.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert}")]]
unsigned long wcstoul_l([[nonnull]] wchar_t const *__restrict nptr,
                        wchar_t **endptr, int base, $locale_t locale)
	%{generate(str2wcs)}

wcstoq(*) = wcstoll;
wcstouq(*) = wcstoull;

[[wchar, export_as("_wcstoll_l", "__wcstoll_l")]]
[[if(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("wcstol_l", "_wcstol_l", "__wcstol_l")]]
[[if(__SIZEOF_LONG_LONG__ == 8), alias("_wcstoi64_l")]]
[[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias("wcstoimax_l", "_wcstoimax_l", "__wcstoimax_l")]]
[[section("{.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert}")]]
__LONGLONG wcstoll_l([[nonnull]] wchar_t const *__restrict nptr,
                     [[nullable]] wchar_t **endptr, int base,
                     $locale_t locale)
	%{generate(str2wcs)}

[[wchar, export_alias("__wcstoull_l")]]
[[if(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("wcstoul_l", "_wcstoul_l", "__wcstoul_l")]]
[[if(__SIZEOF_LONG_LONG__ == 8), alias("_wcstoui64_l")]]
[[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias("wcstoumax_l", "_wcstoumax_l", "__wcstoumax_l")]]
[[section("{.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert}")]]
__ULONGLONG wcstoull_l([[nonnull]] wchar_t const *__restrict nptr,
                       [[nullable]] wchar_t **endptr, int base,
                       $locale_t locale)
	%{generate(str2wcs)}

%#ifndef __NO_FPU
[[ATTR_PURE, ATTR_WUNUSED, wchar, export_alias("_wcstof_l", "__wcstof_l")]]
[[section("{.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert}")]]
float wcstof_l([[nonnull]] wchar_t const *__restrict nptr,
               [[nullable]] wchar_t **endptr, $locale_t locale)
	%{generate(str2wcs)}

[[ATTR_PURE, ATTR_WUNUSED, wchar, export_alias("_wcstod_l", "__wcstod_l")]]
[[section("{.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert}")]]
double wcstod_l([[nonnull]] wchar_t const *__restrict nptr,
                [[nullable]] wchar_t **endptr, $locale_t locale)
	%{generate(str2wcs)}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[ATTR_PURE, ATTR_WUNUSED, wchar, export_alias("_wcstold_l", "__wcstold_l")]]
[[section("{.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert}")]]
__LONGDOUBLE wcstold_l([[nonnull]] wchar_t const *__restrict nptr,
                       [[nullable]] wchar_t **endptr, $locale_t locale)
	%{generate(str2wcs)}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__NO_FPU */

[[cp_stdio, wchar, requires_include("<__crt.h>")]]
[[userimpl, requires($has_function(fgetwc_unlocked) && !defined(__NO_STDSTREAMS))]]
[[section("{.text.crt.wchar.FILE.unlocked.read.getc|.text.crt.dos.wchar.FILE.unlocked.read.getc}")]]
$wint_t getwchar_unlocked() {
	return fgetwc_unlocked(stdin);
}

[[cp_stdio, wchar, requires_include("<__crt.h>")]]
[[userimpl, requires($has_function(fputwc_unlocked) && !defined(__NO_STDSTREAMS))]]
[[section("{.text.crt.wchar.FILE.unlocked.write.putc|.text.crt.dos.wchar.FILE.unlocked.write.putc}")]]
$wint_t putwchar_unlocked(wchar_t wc) {
	return fputwc_unlocked(wc, stdin);
}

getwc_unlocked(*) = fgetwc_unlocked;
putwc_unlocked(*) = fputwc_unlocked;

[[cp_stdio, wchar, crt_dosname("_fgetwc_nolock")]]
[[section("{.text.crt.wchar.FILE.unlocked.read.getc|.text.crt.dos.wchar.FILE.unlocked.read.getc}")]]
$wint_t fgetwc_unlocked([[nonnull]] $FILE *__restrict stream);

[[cp_stdio, wchar, crt_dosname("_fputwc_nolock")]]
[[section("{.text.crt.wchar.FILE.unlocked.write.putc|.text.crt.dos.wchar.FILE.unlocked.write.putc}")]]
$wint_t fputwc_unlocked(wchar_t wc, [[nonnull]] $FILE *__restrict stream);

[[cp_stdio, wchar, alias("fgetws"), crt_dosname("_fgetws_nolock")]]
[[section("{.text.crt.wchar.FILE.unlocked.read.read|.text.crt.dos.wchar.FILE.unlocked.read.read}")]]
[[userimpl, requires($has_function(fgetwc_unlocked) && $has_function(ungetwc_unlocked) && $has_function(ferror_unlocked))]]
[[impl_include("<asm/stdio.h>", "<parts/errno.h>")]]
wchar_t *fgetws_unlocked([[outp(bufsize)]] wchar_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize,
                         [[nonnull]] $FILE *__restrict stream) {
	$size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
#ifdef ERANGE
		__libc_seterrno(ERANGE);
#endif /* ERANGE */
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

[[section("{.text.crt.wchar.FILE.unlocked.write.write|.text.crt.dos.wchar.FILE.unlocked.write.write}")]]
[[cp_stdio, crt_dosname("_fputws_nolock"), wchar, userimpl, requires_function(file_wprinter_unlocked)]]
__STDC_INT_AS_SIZE_T fputws_unlocked([[nonnull]] wchar_t const *__restrict string,
                                     [[nonnull]] $FILE *__restrict stream) {
	__STDC_INT_AS_SIZE_T result;
	result = file_wprinter_unlocked(stream, string, wcslen(string));
	return result;
}


[[wchar, userimpl, export_alias("__wcsftime_l"), decl_prefix(DEFINE_STRUCT_TM)]]
[[section("{.text.crt.wchar.unicode.locale.format.strftime|.text.crt.dos.wchar.unicode.locale.format.strftime}")]]
$size_t wcsftime_l([[outp(maxsize)]] wchar_t *__restrict buf, $size_t maxsize,
                   [[nonnull]] wchar_t const *__restrict format,
                   [[nonnull]] __STRUCT_TM const *__restrict tp, $locale_t locale) {
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

%[default_impl_section(.text.crt.wchar.FILE.locked.write.write)]
@@For use with `format_printf()' and friends: Prints to a `FILE *' closure argument
[[cp_stdio, wchar, impl_include("<asm/stdio.h>")]]
[[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias("file_wprinter_unlocked")]]
[[alias("file_wprinter_unlocked")]]
[[userimpl, requires($has_function(fputwc))]]
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

%[default_impl_section(.text.crt.wchar.FILE.unlocked.write.write)]
@@Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG'
[[cp_stdio, wchar, impl_include("<asm/stdio.h>"), alias("file_wprinter")]]
[[userimpl, requires($has_function(fputwc_unlocked))]]
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


[[wchar, alias("ungetwc"), crt_dosname("_ungetwc_nolock")]]
[[section("{.text.crt.wchar.FILE.unlocked.write.putc|.text.crt.dos.wchar.FILE.unlocked.write.putc}")]]
$wint_t ungetwc_unlocked($wint_t ch, [[nonnull]] $FILE *__restrict stream);

[[cp_stdio, wchar, ATTR_LIBC_WPRINTF(2, 0)]]
[[section("{.text.crt.wchar.FILE.unlocked.write.printf|.text.crt.dos.wchar.FILE.unlocked.write.printf}")]]
[[userimpl, requires_dependent_function(file_wprinter_unlocked)]]
__STDC_INT_AS_SIZE_T vfwprintf_unlocked([[nonnull]] $FILE *__restrict stream,
                                        [[nonnull]] wchar_t const *__restrict format,
                                        $va_list args) {
	return (__STDC_INT_AS_SSIZE_T)format_vwprintf(&file_wprinter_unlocked,
	                                              stream, format, args);
}

[[cp_stdio, wchar, ATTR_LIBC_WPRINTF(2, 3)]]
[[section("{.text.crt.wchar.FILE.unlocked.write.printf|.text.crt.dos.wchar.FILE.unlocked.write.printf}")]]
__STDC_INT_AS_SIZE_T fwprintf_unlocked([[nonnull]] $FILE *__restrict stream,
                                       [[nonnull]] wchar_t const *__restrict format, ...)
	%{printf("vfwprintf_unlocked")}

[[cp_stdio, wchar, ATTR_LIBC_WPRINTF(1, 2)]]
[[section("{.text.crt.wchar.FILE.unlocked.write.printf|.text.crt.dos.wchar.FILE.unlocked.write.printf}")]]
__STDC_INT_AS_SIZE_T wprintf_unlocked([[nonnull]] wchar_t const *__restrict format, ...)
	%{printf("vwprintf_unlocked")}

[[cp_stdio, wchar, ATTR_LIBC_WPRINTF(1, 0)]]
[[requires_include("<__crt.h>"), impl_include("<local/stdstreams.h>")]]
[[userimpl, requires($has_function(vfwprintf_unlocked) && !defined(__NO_STDSTREAMS))]]
[[section("{.text.crt.wchar.FILE.unlocked.write.printf|.text.crt.dos.wchar.FILE.unlocked.write.printf}")]]
__STDC_INT_AS_SIZE_T vwprintf_unlocked([[nonnull]] wchar_t const *__restrict format, $va_list args) {
	return vfwprintf_unlocked(stdout, format, args);
}

%[default_impl_section("{.text.crt.wchar.FILE.unlocked.read.scanf|.text.crt.dos.wchar.FILE.unlocked.read.scanf}")]
[[cp_stdio, ATTR_WUNUSED, ATTR_LIBC_WSCANF(2, 0), wchar, alias("vfwscanf")]]
__STDC_INT_AS_SIZE_T vfwscanf_unlocked([[nonnull]] $FILE *__restrict stream,
                                       [[nonnull]] wchar_t const *__restrict format,
                                       $va_list args);
/* TODO: Inline implementation for `vfwscanf_unlocked()' */

[[cp_stdio, wchar, ATTR_LIBC_SCANF(1, 0), ATTR_WUNUSED, impl_include("<local/stdstreams.h>")]]
[[userimpl, requires($has_function(vfwscanf_unlocked) && !defined(__NO_STDSTREAMS))]]
__STDC_INT_AS_SIZE_T vwscanf_unlocked([[nonnull]] wchar_t const *__restrict format, $va_list args) {
	return vfwscanf_unlocked(stdin, format, args);
}

[[cp_stdio, wchar, ATTR_LIBC_SCANF(2, 3), ATTR_WUNUSED, userimpl]]
__STDC_INT_AS_SIZE_T
fwscanf_unlocked([[nonnull]] $FILE *__restrict stream,
                 [[nonnull]] wchar_t const *__restrict format, ...)
	%{printf("vfwscanf_unlocked")}

[[cp_stdio, wchar, ATTR_LIBC_SCANF(1, 2), ATTR_WUNUSED, userimpl]]
__STDC_INT_AS_SIZE_T
wscanf_unlocked:([[nonnull]] wchar_t const *__restrict format, ...)
	%{printf("vwscanf_unlocked")}


%
%
%
%



/* KOS String extension functions. */
@@Same as `STR+wcslen(STR)'
[[ATTR_WUNUSED, ATTR_PURE, wchar, ATTR_RETNONNULL]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
wchar_t *wcsend([[nonnull]] wchar_t const *__restrict string)
	[([[nonnull]] wchar_t *__restrict string): wchar_t *]
	[([[nonnull]] wchar_t const *__restrict string): wchar_t const *]
	%{generate(str2wcs)}

@@Same as `STR+wcsnlen(STR, MAX_CHARS)'
[[ATTR_WUNUSED, ATTR_PURE, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
wchar_t *wcsnend([[inp(maxlen)]] wchar_t const *__restrict string, $size_t maxlen)
	[([[inp(maxlen)]] wchar_t *__restrict string, $size_t maxlen): wchar_t *]
	[([[inp(maxlen)]] wchar_t const *__restrict string, $size_t maxlen): wchar_t const *]
	%{generate(str2wcs)}


[[wchar, ATTR_LEAF, ATTR_WUNUSED]]
[if(__SIZEOF_LONG__ == 4), alias(wcstol)]
[if(__SIZEOF_LONG_LONG__ == 4), alias(wcstoll, wcstoq)]
[if(__SIZEOF_INTMAX_T__ == 4), alias(wcstoimax)]
[section({.text.crt.wchar.unicode.static.convert|.text.crt.dos.wchar.unicode.static.convert})]
wcsto32:([[nonnull]] wchar_t const *__restrict nptr, [[nullable]] wchar_t **endptr, int base) -> $int32_t %{generate(str2wcs)}

[[wchar, ATTR_LEAF, ATTR_WUNUSED]]
[if(__SIZEOF_LONG__ == 4), alias(wcstoul)]
[if(__SIZEOF_LONG_LONG__ == 4), alias(wcstoull, wcstouq)]
[if(__SIZEOF_INTMAX_T__ == 4), alias(wcstoumax)]
[section({.text.crt.wchar.unicode.static.convert|.text.crt.dos.wchar.unicode.static.convert})]
wcstou32:([[nonnull]] wchar_t const *__restrict nptr, [[nullable]] wchar_t **endptr, int base) -> $uint32_t %{generate(str2wcs)}

%
%#ifdef __UINT64_TYPE__
[[wchar, ATTR_LEAF, ATTR_WUNUSED]][export_alias(_wcstoui64)]
[if(__SIZEOF_LONG__ == 8), alias(wcstoul)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(wcstoull), alias(wcstouq)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(wcstoumax)]
[section({.text.crt.wchar.unicode.static.convert|.text.crt.dos.wchar.unicode.static.convert})]
wcstou64:([[nonnull]] wchar_t const *__restrict nptr, [[nullable]] wchar_t **endptr, int base) -> $uint64_t %{generate(str2wcs)}

[[wchar, ATTR_LEAF, ATTR_WUNUSED]][export_alias(_wcstoi64)]
[if(__SIZEOF_LONG__ == 8), alias(wcstol)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(wcstoll), alias(wcstoq)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(wcstoimax)]
[section({.text.crt.wchar.unicode.static.convert|.text.crt.dos.wchar.unicode.static.convert})]
wcsto64:([[nonnull]] wchar_t const *__restrict nptr, [[nullable]] wchar_t **endptr, int base) -> $int64_t %{generate(str2wcs)}
%#endif /* __UINT64_TYPE__ */

%
%#ifdef __USE_XOPEN2K8
[[wchar, ATTR_LEAF, ATTR_WUNUSED]]
[if(__SIZEOF_LONG__ == 4), alias(wcstol_l, _wcstol_l, __wcstol_l)]
[if(__SIZEOF_LONG_LONG__ == 4), alias(wcstoll_l, _wcstoll_l, __wcstoll_l)]
[if(__SIZEOF_INTMAX_T__ == 4), alias(wcstoimax_l, _wcstoimax_l, __wcstoimax_l)]
[[section("{.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert}")]]
wcsto32_l:([[nonnull]] wchar_t const *__restrict nptr, [[nullable]] wchar_t **endptr, int base, $locale_t locale) -> $int32_t %{generate(str2wcs)}

[[wchar, ATTR_LEAF, ATTR_WUNUSED]]
[if(__SIZEOF_LONG__ == 4), alias(wcstoul_l, _wcstoul_l, __wcstoul_l)]
[if(__SIZEOF_LONG_LONG__ == 4), alias(wcstoull_l, _wcstoull_l, __wcstoull_l)]
[if(__SIZEOF_INTMAX_T__ == 4), alias(wcstoumax_l, _wcstoumax_l, __wcstoumax_l)]
[[section("{.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert}")]]
wcstou32_l:([[nonnull]] wchar_t const *__restrict nptr, [[nullable]] wchar_t **endptr, int base, $locale_t locale) -> $uint32_t %{generate(str2wcs)}

%
%#ifdef __UINT64_TYPE__
[[wchar, ATTR_LEAF, ATTR_WUNUSED]][alias(_wcstoi64_l)]
[if(__SIZEOF_LONG__ == 8), alias(wcstol_l, _wcstol_l, __wcstol_l)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(wcstoll_l, _wcstoll_l, __wcstoll_l)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(wcstoimax_l, _wcstoimax_l, __wcstoimax_l)]
[[section("{.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert}")]]
wcsto64_l:([[nonnull]] wchar_t const *__restrict nptr, [[nullable]] wchar_t **endptr, int base, $locale_t locale) -> $int64_t %{generate(str2wcs)}

[[wchar, ATTR_LEAF, ATTR_WUNUSED]][alias(_wcstoui64_l)]
[if(__SIZEOF_LONG__ == 8), alias(wcstoul_l, _wcstoul_l, __wcstoul_l)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(wcstoull_l, _wcstoull_l, __wcstoull_l)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(wcstoumax_l, _wcstoumax_l, __wcstoumax_l)]
[[section("{.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert}")]]
wcstou64_l:([[nonnull]] wchar_t const *__restrict nptr, [[nullable]] wchar_t **endptr, int base, $locale_t locale) -> $uint64_t %{generate(str2wcs)}
%#endif /* __UINT64_TYPE__ */
%#endif /* __USE_XOPEN2K8 */




%
[alias(_wcsncoll)][[ATTR_WUNUSED, ATTR_PURE, wchar]]
[[section("{.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory}")]]
wcsncoll:([[inp(maxlen)]] wchar_t const *s1, [[inp(maxlen)]] wchar_t const *s2, $size_t maxlen) -> int %{generate(str2wcs)}

[alias(_wcsicoll, wcsicoll, wcscasecmp, _wcsicmp, wcsicmp)][[wchar]]
[[ATTR_WUNUSED, ATTR_PURE]]
[[section("{.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory}")]]
wcscasecoll:([[nonnull]] wchar_t const *s1, [[nonnull]] wchar_t const *s2) -> int %{generate(str2wcs)}

[alias(_wcsnicoll, wcsncasecmp, _wcsnicmp, wcsnicmp)][[wchar]]
[[ATTR_WUNUSED, ATTR_PURE]]
[[section("{.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory}")]]
wcsncasecoll:([[inp(maxlen)]] wchar_t const *s1, [[inp(maxlen)]] wchar_t const *s2, $size_t maxlen) -> int %{generate(str2wcs)}

[[ATTR_RETNONNULL, wchar, ATTR_LEAF]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
wcsnrev:([inoutp(maxlen)] wchar_t *__restrict str, $size_t maxlen) -> wchar_t * {
#if __SIZEOF_WCHAR_T__ == 2
	return (wchar_t *)memrevw(str, wcsnlen(str, maxlen));
#elif __SIZEOF_WCHAR_T__ == 4
	return (wchar_t *)memrevl(str, wcsnlen(str, maxlen));
#else
	return (wchar_t *)memrev(str, wcsnlen(str, maxlen) * sizeof(wchar_t));
#endif
}

[[ATTR_RETNONNULL, ATTR_LEAF]]
[[section("{.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory}")]]
wcsnlwr:([inoutp(maxlen)] wchar_t *__restrict str, $size_t maxlen) -> wchar_t * %{generate(str2wcs)}

[[ATTR_RETNONNULL, wchar, ATTR_LEAF]]
[[section("{.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory}")]]
wcsnupr:([inoutp(maxlen)] wchar_t *__restrict str, $size_t maxlen) -> wchar_t * %{generate(str2wcs)}

[[ATTR_WUNUSED, ATTR_PURE]][alias(wcswcs)][[wchar]]
[[section("{.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory}")]]
wchar_t *wcscasestr([[nonnull]] wchar_t const *haystack, [[nonnull]] wchar_t const *needle)
	[([[nonnull]] wchar_t *haystack, [[nonnull]] wchar_t *needle): wchar_t *]
	[([[nonnull]] wchar_t const *haystack, [[nonnull]] wchar_t const *needle): wchar_t const *]
	%{generate(str2wcs)}

@@Same as wcscpy, but return a pointer after the last written character
[[ATTR_RETNONNULL, wchar, ATTR_LEAF]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
wchar_t *wcspcpy([[nonnull]] wchar_t *__restrict buf, [[nonnull]] wchar_t const *__restrict src) {
	return wmempcpy(buf, src, wcslen(src) + 1);
}

@@Same as wcsncpy, but return a pointer after the last written character
[[ATTR_RETNONNULL, wchar, ATTR_LEAF]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
wchar_t *wcspncpy([[outp(buflen)]] wchar_t *__restrict buf, [[nonnull]] wchar_t const *__restrict src, $size_t buflen) {
	$size_t srclen = wcsnlen(src, buflen);
	wmemcpy(buf, src, srclen);
	return wmempset(buf+srclen, '\0', buflen - srclen);
}

@@Same as wmemset, but return a pointer after the last written character
[[ATTR_RETNONNULL, wchar, ATTR_LEAF]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("mempsetw")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("mempsetl")]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
wchar_t *wmempset([[outp(num_chars)]] wchar_t *dst, wchar_t filler, $size_t num_chars) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)mempsetw(dst, (u16)filler, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)mempsetl(dst, (u32)filler, num_chars);
@@pp_else@@
	return (wchar_t *)mempset(dst, (int)filler, num_chars * sizeof(wchar_t));
@@pp_endif@@
}


@@Same as `wcschr', but don't exceed `MAX_CHARS' characters.
[[ATTR_WUNUSED, ATTR_PURE, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
wchar_t *wcsnchr([[inp(maxlen)]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen)
	[([[inp(maxlen)]] wchar_t *__restrict haystack, wchar_t needle, $size_t maxlen): wchar_t *]
	[([[inp(maxlen)]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen): wchar_t const *]
	%{generate(str2wcs)}

@@Same as `wcsrchr', but don't exceed `MAX_CHARS' characters.
[[ATTR_WUNUSED, ATTR_PURE, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
wchar_t *wcsnrchr([[inp(maxlen)]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen)
	[([[inp(maxlen)]] wchar_t *__restrict haystack, wchar_t needle, $size_t maxlen): wchar_t *]
	[([[inp(maxlen)]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen): wchar_t const *]
	%{generate(str2wcs)}

[[wchar, ATTR_LEAF]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
wchar_t *wcssep([[nonnull]] wchar_t **__restrict stringp,
                [[nonnull]] wchar_t const *__restrict delim)
	%{generate(str2wcs)}

[[ATTR_RETNONNULL, wchar, ATTR_LEAF]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
wchar_t *wcsfry([[nonnull]] wchar_t *__restrict string)
	%{generate(str2wcs)}

[[ATTR_WUNUSED, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC, wchar]]
[[userimpl, section("{.text.crt.wchar.heap.strdup|.text.crt.dos.wchar.heap.strdup}")]]
wchar_t *wcsndup([[inp(max_chars)]] wchar_t const *__restrict string, $size_t max_chars)
	%{generate(str2wcs)}


@@Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found.
[[ATTR_WUNUSED, ATTR_PURE, ATTR_RETNONNULL, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
wchar_t *wcsrchrnul([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle)
	[([[nonnull]] wchar_t *__restrict haystack, wchar_t needle): wchar_t *]
	[([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle): wchar_t const *]
	%{generate(str2wcs)}

@@Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found.
[[ATTR_WUNUSED, ATTR_PURE, ATTR_RETNONNULL, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
wchar_t *wcsnchrnul([[inp(maxlen)]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen)
	[([[inp(maxlen)]] wchar_t *__restrict haystack, wchar_t needle, $size_t maxlen): wchar_t *]
	[([[inp(maxlen)]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen): wchar_t const *]
	%{generate(str2wcs)}

@@Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found.
[[ATTR_WUNUSED, ATTR_PURE, ATTR_RETNONNULL, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
wchar_t *wcsnrchrnul([[inp(maxlen)]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen)
	[([[inp(maxlen)]] wchar_t *__restrict haystack, wchar_t needle, $size_t maxlen): wchar_t *]
	[([[inp(maxlen)]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen): wchar_t const *]
	%{generate(str2wcs)}

@@Same as `wcschrnul', but return the offset from `STR', rather than the actual address
[[ATTR_WUNUSED, ATTR_PURE, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
$size_t wcsoff([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle)
	%{generate(str2wcs)}

@@Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address
[[ATTR_WUNUSED, ATTR_PURE, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
$size_t wcsroff([[nonnull]] wchar_t const *__restrict haystack, wchar_t needle)
	%{generate(str2wcs)}

@@Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address
[[ATTR_WUNUSED, ATTR_PURE, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
$size_t wcsnoff([[inp(maxlen)]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen)
	%{generate(str2wcs)}

@@Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address
[[ATTR_WUNUSED, ATTR_PURE, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
$size_t wcsnroff([[inp(maxlen)]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen)
	%{generate(str2wcs)}

[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
[[impl_include("<parts/malloca.h>")]]
[[userimpl]][requires(!defined(__NO_MALLOCA))][export]
[[ATTR_WUNUSED, ATTR_PURE, wchar]]
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

[[ATTR_WUNUSED, ATTR_PURE, wchar, impl_include("<parts/malloca.h>")]]
[[userimpl, requires_function(fuzzy_wmemcmp)]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
$size_t fuzzy_wcscmp([[nonnull]] wchar_t const *s1, [[nonnull]] wchar_t const *s2) {
	return fuzzy_wmemcmp(s1, wcslen(s1), s2, wcslen(s2));
}

[[ATTR_WUNUSED, ATTR_PURE, wchar, impl_include("<parts/malloca.h>")]]
[[userimpl, requires_function(fuzzy_wmemcmp)]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
$size_t fuzzy_wcsncmp([[inp(s1_maxlen)]] wchar_t const *s1, $size_t s1_maxlen,
                      [[inp(s2_maxlen)]] wchar_t const *s2, $size_t s2_maxlen) {
	return fuzzy_wmemcmp(s1, wcsnlen(s1, s1_maxlen), s2, wcsnlen(s2, s2_maxlen));
}

[[ATTR_WUNUSED, ATTR_PURE, wchar, userimpl]]
[[section("{.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory}")]]
$size_t fuzzy_wmemcasecmp([[inp(s1_bytes)]] wchar_t const *s1, $size_t s1_bytes,
                          [[inp(s2_bytes)]] wchar_t const *s2, $size_t s2_bytes)
	%{generate(str2wcs("fuzzy_memcasecmp"))}

[[ATTR_WUNUSED, ATTR_PURE, wchar, impl_include("<parts/malloca.h>")]]
[[userimpl, requires_function(fuzzy_wmemcasecmp)]]
[[section("{.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory}")]]
fuzzy_wcscasecmp:([[nonnull]] wchar_t const *s1, [[nonnull]] wchar_t const *s2) -> $size_t {
	return fuzzy_wmemcasecmp(s1, wcslen(s1), s2, wcslen(s2));
}

[[ATTR_WUNUSED, ATTR_PURE, wchar, impl_include("<parts/malloca.h>")]]
[[userimpl, requires($has_function(fuzzy_wmemcasecmp))]]
[[section("{.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory}")]]
$size_t fuzzy_wcsncasecmp([[inp(s1_maxlen)]] wchar_t const *s1, $size_t s1_maxlen,
                          [[inp(s2_maxlen)]] wchar_t const *s2, $size_t s2_maxlen) {
	return fuzzy_wmemcasecmp(s1, wcsnlen(s1, s1_maxlen), s2, wcsnlen(s2, s2_maxlen));
}

[[ATTR_WUNUSED, ATTR_PURE, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
int wildwcscmp([[nonnull]] wchar_t const *pattern,
               [[nonnull]] wchar_t const *string)
	%{generate(str2wcs("wildstrcmp"))}

[[ATTR_WUNUSED, ATTR_PURE, wchar]]
[[section("{.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory}")]]
int wildwcscasecmp([[nonnull]] wchar_t const *pattern,
                   [[nonnull]] wchar_t const *string)
	%{generate(str2wcs("wildstrcasecmp"))}

[[ATTR_WUNUSED, ATTR_PURE, wchar]]
[[section("{.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory}")]]
int wcsverscmp([[nonnull]] wchar_t const *s1, [[nonnull]] wchar_t const *s2)
	%{generate(str2wcs)}






%
%#ifdef __USE_XOPEN2K8
[alias(_wcsncoll_l)][[ATTR_WUNUSED, ATTR_PURE, wchar]]
[[section("{.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory}")]]
wcsncoll_l:([[inp(maxlen)]] wchar_t const *s1,
            [[inp(maxlen)]] wchar_t const *s2,
            $size_t maxlen, $locale_t locale) -> int %{generate(str2wcs)}

[alias(_wcsicoll_l, wcscasecmp_l, _wcsicmp_l)]
[[ATTR_WUNUSED, ATTR_PURE, wchar]]
[[section("{.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory}")]]
wcscasecoll_l:([[nonnull]] wchar_t const *s1, [[nonnull]] wchar_t const *s2, $locale_t locale) -> int %{generate(str2wcs)}

[alias(_wcsnicoll_l, wcsncasecmp_l, _wcsnicmp_l)]
[[ATTR_WUNUSED, ATTR_PURE, wchar]]
[[section("{.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory}")]]
wcsncasecoll_l:([[inp(maxlen)]] wchar_t const *s1,
                [[inp(maxlen)]] wchar_t const *s2, $size_t maxlen, $locale_t locale) -> int %{generate(str2wcs)}

[alias(_wcslwr_l)][[ATTR_RETNONNULL, wchar]]
[[section("{.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory}")]]
wcslwr_l:([[nonnull]] wchar_t *__restrict str, $locale_t locale) -> wchar_t * %{generate(str2wcs)}

[alias(_wcsupr_l)][[ATTR_RETNONNULL, wchar]]
[[section("{.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory}")]]
wcsupr_l:([[nonnull]] wchar_t *__restrict str, $locale_t locale) -> wchar_t * %{generate(str2wcs)}

[[ATTR_RETNONNULL, wchar]]
[[section("{.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory}")]]
wcsnlwr_l:([inoutp(maxlen)] wchar_t *__restrict str, $size_t maxlen, $locale_t locale) -> wchar_t * %{generate(str2wcs)}

[[ATTR_RETNONNULL, wchar]]
[[section("{.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory}")]]
wcsnupr_l:([inoutp(maxlen)] wchar_t *__restrict str, $size_t maxlen, $locale_t locale) -> wchar_t * %{generate(str2wcs)}

[[ATTR_WUNUSED, ATTR_PURE]][alias(wcswcs)][[wchar]]
[[section("{.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory}")]]
wchar_t *wcscasestr_l([[nonnull]] wchar_t const *haystack, [[nonnull]] wchar_t const *needle, $locale_t locale)
	[([[nonnull]] wchar_t *haystack, [[nonnull]] wchar_t *needle, $locale_t locale): wchar_t *]
	[([[nonnull]] wchar_t const *haystack, [[nonnull]] wchar_t const *needle, $locale_t locale): wchar_t const *]
	%{generate(str2wcs)}

[[ATTR_WUNUSED, ATTR_PURE, wchar, userimpl]]
[[section("{.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory}")]]
$size_t fuzzy_wmemcasecmp_l([[inp(s1_bytes)]] wchar_t const *s1, $size_t s1_bytes,
                            [[inp(s2_bytes)]] wchar_t const *s2, $size_t s2_bytes, $locale_t locale)
	%{generate(str2wcs("fuzzy_memcasecmp_l"))}

[[ATTR_WUNUSED, ATTR_PURE]]
[[wchar, impl_include("<parts/malloca.h>")]]
[[userimpl]][requires($has_function(fuzzy_wmemcasecmp_l))][export]
[[section("{.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory}")]]
fuzzy_wcscasecmp_l:([[nonnull]] wchar_t const *s1, [[nonnull]] wchar_t const *s2, $locale_t locale) -> $size_t {
	return fuzzy_wmemcasecmp_l(s1, wcslen(s1), s2, wcslen(s2), locale);
}
[[ATTR_WUNUSED, ATTR_PURE]]
[[wchar, impl_include("<parts/malloca.h>")]]
[[userimpl]][requires($has_function(fuzzy_wmemcasecmp_l))][export]
[[section("{.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory}")]]
fuzzy_wcsncasecmp_l:([[inp(s1_maxlen)]] wchar_t const *s1, $size_t s1_maxlen,
                     [[inp(s2_maxlen)]] wchar_t const *s2, $size_t s2_maxlen, $locale_t locale) -> $size_t {
	return fuzzy_wmemcasecmp_l(s1, wcsnlen(s1, s1_maxlen), s2, wcsnlen(s2, s2_maxlen), locale);
}

[[ATTR_WUNUSED, ATTR_PURE, wchar]]
[[section("{.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory}")]]
wildwcscasecmp_l:([[nonnull]] wchar_t const *pattern, [[nonnull]] wchar_t const *string, $locale_t locale) -> int
	%{generate(str2wcs("wildstrcasecmp_l"))}

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

[[guard]] _wcsdup(*) = wcsdup;

%
%#ifdef __USE_DOS_SLIB
[[guard, wchar, section(".text.crt.dos.wchar.string.memory")]]
$errno_t wcscat_s([[nonnull]] wchar_t *dst, $size_t dstsize, [[nonnull]] wchar_t const *src)
	%{generate(str2wcs)}

[[guard, wchar, section(".text.crt.dos.wchar.string.memory")]]
$errno_t wcscpy_s([[nonnull]] wchar_t *dst, $rsize_t dstsize, [[nonnull]] wchar_t const *src)
	%{generate(str2wcs)}

%{
#ifndef __wcsnlen_s_defined
#define __wcsnlen_s_defined 1
__LOCAL __ATTR_WUNUSED __ATTR_PURE
__SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsnlen_s)(wchar_t const *__str, __SIZE_TYPE__ __maxlen) {
	return __str ? wcsnlen(__str, __maxlen) : 0;
}
#endif /* !__wcsnlen_s_defined */
}

[[wchar, guard, section(".text.crt.dos.wchar.string.memory")]]
$errno_t wcsncat_s(wchar_t *dst, $rsize_t dstsize, wchar_t const *src, $rsize_t maxlen)
	%{generate(str2wcs)}

[[wchar, guard, section(".text.crt.dos.wchar.string.memory")]]
$errno_t wcsncpy_s(wchar_t *dst, $rsize_t dstsize, wchar_t const *src, $rsize_t maxlen)
	%{generate(str2wcs)}

wcstok_s(*) = wcstok;

%#endif  /* __USE_DOS_SLIB */

%[default_impl_section(".text.crt.dos.wchar.errno")];
[[wchar, guard]] wchar_t *_wcserror(int errno_value);
[[wchar, guard]] $errno_t _wcserror_s(wchar_t *buf, $size_t bufsize, int errno_value);
[[wchar, guard]] wchar_t *__wcserror(wchar_t const *message);
[[wchar, guard]] $errno_t __wcserror_s(wchar_t *buf, $size_t bufsize, wchar_t const *message);

[[guard]] _wcsicmp(*) = wcscasecmp;
[[guard]] _wcsnicmp(*) = wcsncasecmp;
[[guard]] _wcsicmp_l(*) = wcscasecmp_l;
[[guard]] _wcsnicmp_l(*) = wcsncasecmp_l;

[[guard, wchar, section(".text.crt.dos.wchar.string.memory")]]
_wcsnset_s(*) %{generate(str2wcs("_strnset_s"))}

[[guard, wchar, section(".text.crt.dos.wchar.string.memory")]]
_wcsset_s(*) %{generate(str2wcs("_strset_s"))}

[[guard, wchar, section(".text.crt.dos.wchar.unicode.static.memory")]]
_wcslwr_s(*) %{generate(str2wcs("_strlwr_s"))}

[[guard, wchar, section(".text.crt.dos.wchar.unicode.static.memory")]]
_wcsupr_s(*) %{generate(str2wcs("_strupr_s"))}

[[guard, wchar, section(".text.crt.dos.wchar.unicode.locale.memory")]]
_wcslwr_s_l(*) %{generate(str2wcs("_strlwr_s_l"))}

[[guard, wchar, section(".text.crt.dos.wchar.unicode.locale.memory")]]
_wcsupr_s_l(*) %{generate(str2wcs("_strupr_s_l"))}

[[guard, wchar, section(".text.crt.dos.wchar.string.memory")]]
wmemcpy_s(*) %{generate(str2wcs("memcpy_s"))}

[[guard, wchar, section(".text.crt.dos.wchar.string.memory")]]
wmemmove_s(*) %{generate(str2wcs("memmove_s"))}

%
%
%

[[guard]] _wcsnset:(*) = wcsnset;
[[guard]] _wcsrev:(*) = wcsrev;
[[guard]] _wcsset:(*) = wcsset;
[[guard]] _wcslwr:(*) = wcslwr;
[[guard]] _wcsupr:(*) = wcsupr;
[[guard]] _wcslwr_l:(*) = wcslwr_l;
[[guard]] _wcsupr_l:(*) = wcsupr_l;
[[guard]] _wcsxfrm_l:(*) = wcsxfrm_l;
[[guard]] _wcscoll_l:(*) = wcscoll_l;
[[guard]] _wcsicoll:(*) = wcscasecoll;
[[guard]] _wcsicoll_l:(*) = wcscasecoll_l;
[[guard]] _wcsncoll:(*) = wcsncasecoll;
[[guard]] _wcsncoll_l:(*) = wcsncoll_l;
[[guard]] _wcsnicoll:(*) = wcsncasecoll;
[[guard]] _wcsnicoll_l:(*) = wcsncasecoll_l;

%
%
%

[[guard]] wcsicmp:(*) = wcscasecmp;
[[guard]] wcsnicmp:(*) = wcsncasecmp;
[[guard]] wcsicoll:(*) = wcscasecoll;

%#endif /* !_WSTRING_DEFINED */
%#endif /* __USE_DOS */


%#if defined(__USE_DOS) || defined(__USE_KOS)
[[wchar, guard, crt_dosname("_wcsnset"), section(".text.crt.dos.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsnset([[nonnull]] wchar_t *__restrict str, wchar_t ch, $size_t maxlen)
	%{generate(str2wcs)}

[[wchar, guard, crt_dosname("_wcsrev"), ATTR_RETNONNULL, ATTR_NONNULL((1))]]
[[section(".text.crt.dos.wchar.string.memory"), doc_alias("strrev")]]
wchar_t *wcsrev(wchar_t *__restrict str) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)memrevw(str, wcslen(str));
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)memrevl(str, wcslen(str));
@@pp_else@@
	return (wchar_t *)memrev(str, wcslen(str) * sizeof(wchar_t));
@@pp_endif@@
}


[[wchar, guard, crt_dosname("_wcsset")]]
[[section(".text.crt.dos.wchar.string.memory")]]
wcsset(*) %{generate(str2wcs)}

[[wchar, guard, crt_dosname("_wcslwr")]]
[[section(".text.crt.dos.wchar.unicode.static.memory")]]
wcslwr(*) %{generate(str2wcs)}

[[wchar, guard, crt_dosname("_wcsupr")]]
[[section(".text.crt.dos.wchar.unicode.static.memory")]]
wcsupr(*) %{generate(str2wcs)}

%#endif /* __USE_DOS || __USE_KOS */


%#ifdef __USE_DOS
%#ifndef _WSTDIO_DEFINED
%#define _WSTDIO_DEFINED 1

%#ifdef __USE_DOS_SLIB
%[default_impl_section(".text.crt.dos.wchar.FILE.locked.write.printf")]
[[guard]] vswprintf_s(*) = vswprintf;
[[guard]] swprintf_s(*) = swprintf;
[[guard]] vfwprintf_s(*) = vfwprintf;
[[guard]] fwprintf_s(*) = fwprintf;
[[guard]] vwprintf_s(*) = vwprintf;
[[guard]] wprintf_s(*) = wprintf;

%[default_impl_section(".text.crt.dos.wchar.FILE.locked.read.scanf")]
[[guard]] vswscanf_s(*) = vswscanf;
[[guard]] swscanf_s(*) = swscanf;
[[guard]] vfwscanf_s(*) = vfwscanf;
[[guard]] fwscanf_s(*) = fwscanf;
[[guard]] vwscanf_s(*) = vwscanf;
[[guard]] wscanf_s(*) = wscanf;

%#endif /* __USE_DOS_SLIB */

%[default_impl_section(".text.crt.dos.wchar.FILE.locked.write.printf")]
[[guard, wchar, ATTR_WUNUSED, userimpl]]
__STDC_INT_AS_SSIZE_T _vscwprintf([[nonnull]] wchar_t const *format, $va_list args) {
	return vswprintf(NULL, 0, format, args);
}

[[guard, wchar, ATTR_WUNUSED]]
int _scwprintf([[nonnull]] wchar_t const *format, ...)
	%{printf}

[[guard, wchar, ATTR_WUNUSED]]
__STDC_INT_AS_SSIZE_T _vscwprintf_p([[nonnull]] wchar_t const *format, $va_list args) {
	/* TODO */
	(void)format;
	(void)args;
	COMPILER_IMPURE();
	return 0;
}

[[guard, wchar, ATTR_WUNUSED]]
__STDC_INT_AS_SSIZE_T _scwprintf_p([[nonnull]] wchar_t const *format, ...)
	%{printf}

[[guard, wchar, ATTR_WUNUSED]]
__STDC_INT_AS_SSIZE_T _vscwprintf_l([[nonnull]] wchar_t const *format,
                                    [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return _vscwprintf(format, args);
}

[[guard, wchar, ATTR_WUNUSED]]
__STDC_INT_AS_SSIZE_T _scwprintf_l([[nonnull]] wchar_t const *format,
                                   [[nullable]] $locale_t locale, ...)
	%{printf}

[[guard, wchar, ATTR_WUNUSED]]
__STDC_INT_AS_SSIZE_T _vscwprintf_p_l([[nonnull]] wchar_t const *format,
                                      [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return _vscwprintf_p(format, args);
}

[[guard, wchar, ATTR_WUNUSED]]
__STDC_INT_AS_SSIZE_T _scwprintf_p_l([[nonnull]] wchar_t const *format,
                                     [[nullable]] $locale_t locale, ...)
	%{printf}

[[guard]] _vswprintf_c(*) = vswprintf;
[[guard]] _swprintf_c(*) = swprintf;

[[guard, wchar]]
__STDC_INT_AS_SSIZE_T _vsnwprintf_s([[outp_opt(min(return, bufsize, buflen))]] wchar_t *buf,
                                    $size_t bufsize, $size_t buflen,
                                    [[nonnull]] wchar_t const *format, $va_list args) {
	(void)buflen;
	return vswprintf(buf, bufsize, format, args);
}

[[guard, wchar]]
__STDC_INT_AS_SSIZE_T _snwprintf_s([[outp_opt(min(return, bufsize, buflen))]] wchar_t *buf, $size_t bufsize,
                                   $size_t buflen, [[nonnull]] wchar_t const *format, ...)
	%{printf}


[[guard, wchar, cp_stdio]]
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

[[guard, wchar, cp_stdio]]
__STDC_INT_AS_SSIZE_T _fwprintf_p([[nonnull]] $FILE *stream,
                                  [[nonnull]] wchar_t const *format, ...)
	%{printf}

[[guard, wchar, cp_stdio, impl_include("<local/stdstreams.h>")]]
[[userimpl, requires(!defined(__NO_STDSTREAMS) && $has_function(_vfwprintf_p))]]
__STDC_INT_AS_SSIZE_T _vwprintf_p([[nonnull]] wchar_t const *format, $va_list args) {
	return _vfwprintf_p(stdout, format, args);
}

[[guard, wchar, cp_stdio]]
__STDC_INT_AS_SSIZE_T _wprintf_p([[nonnull]] wchar_t const *format, ...)
	%{printf}

[[guard, wchar]]
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

[[guard, wchar]]
__STDC_INT_AS_SSIZE_T _swprintf_p([[outp(bufsize)]] wchar_t *dst, $size_t bufsize,
                                  [[nonnull]] wchar_t const *format, ...)
	%{printf}

[[guard, wchar, cp_stdio]]
[[userimpl, requires_function(vwprintf)]]
__STDC_INT_AS_SSIZE_T _vwprintf_l([[nonnull]] wchar_t const *format,
                                  [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return vwprintf(format, args);
}

[[guard, wchar, cp_stdio]]
__STDC_INT_AS_SSIZE_T _wprintf_l([[nonnull]] wchar_t const *format,
                                 [[nullable]] $locale_t locale, ...)
	%{printf}


[[guard, wchar, cp_stdio, userimpl, requires_function(_vwprintf_p)]]
__STDC_INT_AS_SSIZE_T _vwprintf_p_l([[nonnull]] wchar_t const *format,
                                    [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return _vwprintf_p(format, args);
}

[[guard, wchar, cp_stdio]]
__STDC_INT_AS_SSIZE_T _wprintf_p_l([[nonnull]] wchar_t const *format,
                                   [[nullable]] $locale_t locale, ...)
	%{printf}


[[guard, wchar, cp_stdio, userimpl, requires_function(vwprintf_s)]]
__STDC_INT_AS_SSIZE_T _vwprintf_s_l([[nonnull]] wchar_t const *format,
                                    [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return vwprintf_s(format, args);
}

[[guard, wchar, cp_stdio]]
__STDC_INT_AS_SSIZE_T _wprintf_s_l([[nonnull]] wchar_t const *format,
                                   [[nullable]] $locale_t locale, ...)
	%{printf}


[[guard, wchar, cp_stdio]]
[[userimpl, requires_function(vfwprintf)]]
__STDC_INT_AS_SSIZE_T _vfwprintf_l([[nonnull]] $FILE *stream, [[nonnull]] wchar_t const *format,
                                   [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return vfwprintf(stream, format, args);
}

[[guard, wchar, cp_stdio]]
__STDC_INT_AS_SSIZE_T _fwprintf_l([[nonnull]] $FILE *stream, [[nonnull]] wchar_t const *format,
                                  [[nullable]] $locale_t locale, ...)
	%{printf}


[[guard, wchar, cp_stdio]]
[[userimpl, requires_function(_vfwprintf_p)]]
__STDC_INT_AS_SSIZE_T _vfwprintf_p_l([[nonnull]] $FILE *stream,
                                     [[nonnull]] wchar_t const *format,
                                     [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return _vfwprintf_p(stream, format, args);
}

[[guard, wchar, cp_stdio]]
__STDC_INT_AS_SSIZE_T _fwprintf_p_l([[nonnull]] $FILE *stream,
                                    [[nonnull]] wchar_t const *format,
                                    [[nullable]] $locale_t locale, ...)
	%{printf}


[[guard, wchar, cp_stdio]]
[[userimpl, requires_function(vfwprintf_s)]]
__STDC_INT_AS_SSIZE_T _vfwprintf_s_l([[nonnull]] $FILE *stream,
                                     [[nonnull]] wchar_t const *format,
                                     [[nullable]] $locale_t locale,
                                     $va_list args) {
	(void)locale;
	return vfwprintf_s(stream, format, args);
}

[[guard, wchar, cp_stdio]]
__STDC_INT_AS_SSIZE_T _fwprintf_s_l([[nonnull]] $FILE *stream,
                                    [[nonnull]] wchar_t const *format,
                                    [[nullable]] $locale_t locale, ...)
	%{printf}


[[guard, wchar]]
__STDC_INT_AS_SSIZE_T _vswprintf_c_l([[outp(bufsize)]] wchar_t *dst, $size_t bufsize,
                                     [[nonnull]] wchar_t const *format,
                                     [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return _vswprintf_c(dst, bufsize, format, args);
}

[[guard, wchar]]
__STDC_INT_AS_SSIZE_T _swprintf_c_l([[outp(bufsize)]] wchar_t *dst, $size_t bufsize,
                                    [[nonnull]] wchar_t const *format,
                                    [[nullable]] $locale_t locale, ...)
	%{printf}


[[guard, wchar]]
__STDC_INT_AS_SSIZE_T _vswprintf_p_l([[outp(bufsize)]] wchar_t *dst, $size_t bufsize,
                                     [[nonnull]] wchar_t const *format,
                                     [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return _vswprintf_p(dst, bufsize, format, args);
}

[[guard, wchar]]
__STDC_INT_AS_SSIZE_T _swprintf_p_l([[outp(bufsize)]] wchar_t *dst, $size_t bufsize,
                                    [[nonnull]] wchar_t const *format,
                                    [[nullable]] $locale_t locale, ...)
	%{printf}


[[guard, wchar]]
__STDC_INT_AS_SSIZE_T _vswprintf_s_l([[outp(wchar_count)]] wchar_t *dst, $size_t wchar_count,
                                     [[nonnull]] wchar_t const *format,
                                     [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return vswprintf_s(dst, wchar_count, format, args);
}

[[guard, wchar]]
__STDC_INT_AS_SSIZE_T _swprintf_s_l([[outp(wchar_count)]] wchar_t *dst,
                                    $size_t wchar_count,
                                    [[nonnull]] wchar_t const *format,
                                    [[nullable]] $locale_t locale, ...)
	%{printf}


[[guard, wchar]]
__STDC_INT_AS_SSIZE_T _vsnwprintf_l([[outp(bufsize)]] wchar_t *dst, $size_t bufsize,
                                    [[nonnull]] wchar_t const *format,
                                    [[nullable]] $locale_t locale,
                                    $va_list args) {
	(void)locale;
	return vswprintf(dst, bufsize, format, args);
}

[[guard, wchar]]
__STDC_INT_AS_SSIZE_T _snwprintf_l([[outp(bufsize)]] wchar_t *dst, $size_t bufsize,
                                   [[nonnull]] wchar_t const *format,
                                   [[nullable]] $locale_t locale, ...)
	%{printf}


[[guard, wchar]]
__STDC_INT_AS_SSIZE_T _vsnwprintf_s_l([[outp(wchar_count)]] wchar_t *dst, $size_t wchar_count,
                                      $size_t bufsize, [[nonnull]] wchar_t const *format,
                                      [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return _vsnwprintf_s(dst, wchar_count, bufsize, format, args);
}

[[guard, wchar]]
__STDC_INT_AS_SSIZE_T _snwprintf_s_l([[outp(wchar_count)]] wchar_t *dst, $size_t wchar_count,
                                     $size_t bufsize, [[nonnull]] wchar_t const *format,
                                     [[nullable]] $locale_t locale, ...)
	%{printf}



%[default_impl_section(".text.crt.dos.wchar.FILE.locked.read.scanf")]

[[ignore, wchar, cp_stdio, ATTR_WUNUSED]]
[[userimpl, requires_function(vfwscanf)]]
__STDC_INT_AS_SSIZE_T _vfwscanf_l([[nonnull]] $FILE *stream, [[nonnull]] wchar_t const *format,
                                  [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return vfwscanf(stream, format, args);
}

[[guard, wchar, cp_stdio, ATTR_WUNUSED]]
__STDC_INT_AS_SSIZE_T _fwscanf_l([[nonnull]] $FILE *stream, [[nonnull]] wchar_t const *format,
                                 [[nullable]] $locale_t locale, ...)
	%{printf}

[[ignore]] _vfwscanf_s_l(*) = _vfwscanf_l;
[[guard]] _fwscanf_s_l(*) = _fwscanf_l;

[[ignore, wchar, ATTR_WUNUSED]]
__STDC_INT_AS_SSIZE_T _vswscanf_l([[nonnull]] wchar_t const *src,
                                  [[nonnull]] wchar_t const *format,
                                  [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return vswscanf(src, format, args);
}

[[guard, wchar, ATTR_WUNUSED]]
__STDC_INT_AS_SSIZE_T _swscanf_l([[nonnull]] wchar_t const *src,
                                 [[nonnull]] wchar_t const *format,
                                 [[nullable]] $locale_t locale, ...)
	%{printf}

[[ignore]] _vswscanf_s_l(*) = _vswscanf_l;
[[guard]] _swscanf_s_l(*) = _swscanf_l;

[[ignore, wchar, ATTR_WUNUSED]]
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

[[guard, wchar, ATTR_WUNUSED]]
__STDC_INT_AS_SSIZE_T _snwscanf([[inp(bufsize)]] wchar_t const *src, $size_t bufsize,
                                [[nonnull]] wchar_t const *format, ...)
	%{printf}

[[ignore, wchar, ATTR_WUNUSED]]
__STDC_INT_AS_SSIZE_T _vsnwscanf_l([[inp(bufsize)]] wchar_t const *src, $size_t bufsize,
                                   [[nonnull]] wchar_t const *format, [[nullable]] $locale_t locale,
                                   $va_list args) {
	(void)locale;
	return _vsnwscanf(src, bufsize, format, args);
}

[[guard, wchar, ATTR_WUNUSED]]
__STDC_INT_AS_SSIZE_T _snwscanf_l([[inp(bufsize)]] wchar_t const *src, $size_t bufsize,
                                  [[nonnull]] wchar_t const *format, [[nullable]] $locale_t locale, ...)
	%{printf}

[[ignore]] _vsnwscanf_s(*) = _vsnwscanf;
[[guard]] _snwscanf_s(*) = _snwscanf;

[[ignore, wchar, ATTR_WUNUSED, userimpl]]
__STDC_INT_AS_SSIZE_T _vsnwscanf_s_l([[inp(bufsize)]] wchar_t const *src, $size_t bufsize,
                                     [[nonnull]] wchar_t const *format, [[nullable]] $locale_t locale,
                                     $va_list args) {
	(void)locale;
	return _vsnwscanf_s(src, bufsize, format, args);
}

[[guard, wchar, ATTR_WUNUSED]]
__STDC_INT_AS_SSIZE_T _snwscanf_s_l([[inp(bufsize)]] wchar_t const *src, $size_t bufsize,
                                    [[nonnull]] wchar_t const *format, [[nullable]] $locale_t locale, ...)
	%{printf}

[[ignore, wchar, cp_stdio, ATTR_WUNUSED]]
[[userimpl, requires_function(vwscanf)]]
__STDC_INT_AS_SSIZE_T _vwscanf_l([[nonnull]] wchar_t const *format, [[nullable]] $locale_t locale, $va_list args) {
	(void)locale;
	return vwscanf(format, args);
}

[[guard, wchar, cp_stdio, ATTR_WUNUSED, userimpl]]
__STDC_INT_AS_SSIZE_T _wscanf_l([[nonnull]] wchar_t const *format,
                                [[nullable]] $locale_t locale, ...)
	%{printf}

[[ignore]] _vwscanf_s_l(*) = _vwscanf_l;
[[guard]] _wscanf_s_l(*) = _wscanf_l;


%[default_impl_section(".text.crt.dos.wchar.FILE.locked.access")]
[[guard, wchar, ATTR_WUNUSED]] _wfsopen:([[nonnull]] wchar_t const *filename, [[nonnull]] wchar_t const *mode, int sh_flag) -> $FILE *;
[[guard, wchar, ATTR_WUNUSED]] _wfdopen:($fd_t fd, [[nonnull]] wchar_t const *mode) -> $FILE *;
[[guard, wchar]] _wfopen_s:([[nonnull]] $FILE **pstream, [[nonnull]] wchar_t const *filename, [[nonnull]] wchar_t const *mode) -> $errno_t;
[[guard, wchar]] _wfreopen_s:([[nonnull]] $FILE **pstream, [[nonnull]] wchar_t const *filename, [[nonnull]] wchar_t const *mode, $FILE *stream) -> $errno_t;

[[guard]] _wfopen(*) = wfopen;
[[guard]] _wfreopen(*) = wfreopen;
[[guard]] _fgetwchar(*) = getwchar;
[[guard]] _fputwchar(*) = putwchar;


[[guard, wchar, requires_include("<__crt.h>")]]
[[section(".text.crt.dos.wchar.FILE.locked.read.read")]]
[[userimpl, requires($has_function(fgetws) && !defined(__NO_STDSTREAMS))]]
wchar_t *_getws_s(wchar_t *buf, $size_t buflen) {
	return fgetws(buf, buflen, stdin);
}

[[guard, wchar, requires_include("<__crt.h>")]]
[[section(".text.crt.dos.wchar.FILE.locked.write.write")]]
[[userimpl, requires($has_function(fputws) && !defined(__NO_STDSTREAMS))]]
__STDC_INT_AS_SIZE_T _putws([[nonnull]] wchar_t const *string) {
	return fputws(string, stdout);
}

[[guard, wchar, ATTR_WUNUSED]]
[[section(".text.crt.dos.wchar.fs.utility")]]
wchar_t *_wtempnam([[nullable]] wchar_t const *directory,
                   [[nullable]] wchar_t const *file_prefix);

%#ifndef _CRT_WPERROR_DEFINED
%#define _CRT_WPERROR_DEFINED
%[insert:extern(_wperror)]
%#endif  /* _CRT_WPERROR_DEFINED */

[[guard]] _wpopen:(*) = wpopen;
[[guard]] _wremove:(*) = wremove;

[[guard, wchar, section(".text.crt.dos.wchar.fs.utility")]]
$errno_t _wtmpnam_s([[outp(wchar_count)]] wchar_t *dst, $size_t wchar_count);

[[guard]] _fgetwc_nolock(*) = fgetwc_unlocked;
[[guard]] _fputwc_nolock(*) = fputwc_unlocked;
[[guard]] _ungetwc_nolock(*) = ungetwc_unlocked;
[[guard]] _getwc_nolock(*) = fgetwc_unlocked;
[[guard]] _putwc_nolock(*) = fputwc_unlocked;

%#endif /* !_WSTDIO_DEFINED */


%#ifndef _WSTDLIB_DEFINED
%#define _WSTDLIB_DEFINED
%[insert:extern(_wcstol_l)]
%[insert:extern(_wcstoul_l)]
%#ifndef __NO_FPU
%[insert:extern(_wcstof_l)]
%[insert:extern(_wcstod_l)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:extern(_wcstold_l)]
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
%[insert:extern(_wsystem)]
%[insert:extern(_wtoi)]
%[insert:extern(_wtol)]
%[insert:extern(_wtoi64)]
%[insert:extern(_wcstoi64)]
%[insert:extern(_wcstoui64)]
%[insert:extern(_wtoi_l)]
%[insert:extern(_wtol_l)]
%[insert:extern(_wtoi64_l)]
%[insert:extern(_wcstoi64_l)]
%[insert:extern(_wcstoui64_l)]
%#ifdef __LONGLONG
%[insert:extern(_wcstoll_l)]
%[insert:extern(_wcstoull_l)]
%[insert:extern(_wtoll)]
%[insert:extern(_wtoll_l)]
%#endif /* __LONGLONG */
%#endif /* !_WSTDLIB_DEFINED */


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

}

