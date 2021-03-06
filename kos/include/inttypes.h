/* HASH CRC-32:0x1df03 */
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
#ifndef _INTTYPES_H
#define _INTTYPES_H 1

#ifdef _CXX_STDONLY_CINTTYPES
#ifdef __CXX_SYSTEM_HEADER
#undef _INTTYPES_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "inttypes.h" after "cinttypes" */
#ifndef __imaxdiv_t_defined
#define __imaxdiv_t_defined 1
__NAMESPACE_STD_USING(imaxdiv_t)
#endif /* !__imaxdiv_t_defined */
__NAMESPACE_STD_USING(imaxabs)
__NAMESPACE_STD_USING(imaxdiv)
__NAMESPACE_STD_USING(strtoimax)
__NAMESPACE_STD_USING(strtoumax)
__NAMESPACE_STD_USING(wcstoimax)
__NAMESPACE_STD_USING(wcstoumax)
#undef _CXX_STDONLY_CINTTYPES
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CINTTYPES */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/__va_size.h>
#include <hybrid/typecore.h>

#include <bits/crt/inttypes.h>

#include <stdint.h>

#ifdef __USE_DOS
#include <xlocale.h>
#endif /* __USE_DOS */

__SYSDECL_BEGIN

#ifndef ____gwchar_t_defined
#define ____gwchar_t_defined 1
#define __gwchar_t __WCHAR_TYPE__
#endif /* !____gwchar_t_defined */

/* printf(): (u)int8_t */
#define PRId8          __PRI1_PREFIX "d" /* I8d */
#define PRIi8          __PRI1_PREFIX "i" /* I8i */
#define PRIo8          __PRI1_PREFIX "o" /* I8o */
#define PRIu8          __PRI1_PREFIX "u" /* I8u */
#define PRIx8          __PRI1_PREFIX "x" /* I8x */
#define PRIX8          __PRI1_PREFIX "X" /* I8X */

/* printf(): (u)int16_t */
#define PRId16         __PRI2_PREFIX "d" /* I16d */
#define PRIi16         __PRI2_PREFIX "i" /* I16i */
#define PRIo16         __PRI2_PREFIX "o" /* I16o */
#define PRIu16         __PRI2_PREFIX "u" /* I16u */
#define PRIx16         __PRI2_PREFIX "x" /* I16x */
#define PRIX16         __PRI2_PREFIX "X" /* I16X */

/* printf(): (u)int32_t */
#define PRId32         __PRI4_PREFIX "d" /* I32d */
#define PRIi32         __PRI4_PREFIX "i" /* I32i */
#define PRIo32         __PRI4_PREFIX "o" /* I32o */
#define PRIu32         __PRI4_PREFIX "u" /* I32u */
#define PRIx32         __PRI4_PREFIX "x" /* I32x */
#define PRIX32         __PRI4_PREFIX "X" /* I32X */

/* printf(): (u)int64_t */
#define PRId64         __PRI8_PREFIX "d" /* I64d */
#define PRIi64         __PRI8_PREFIX "i" /* I64i */
#define PRIo64         __PRI8_PREFIX "o" /* I64o */
#define PRIu64         __PRI8_PREFIX "u" /* I64u */
#define PRIx64         __PRI8_PREFIX "x" /* I64x */
#define PRIX64         __PRI8_PREFIX "X" /* I64X */

/* printf(): (u)int_least8_t */
#define PRIdLEAST8     __PRIL1_PREFIX "d"
#define PRIiLEAST8     __PRIL1_PREFIX "i"
#define PRIoLEAST8     __PRIL1_PREFIX "o"
#define PRIuLEAST8     __PRIL1_PREFIX "u"
#define PRIxLEAST8     __PRIL1_PREFIX "x"
#define PRIXLEAST8     __PRIL1_PREFIX "X"

/* printf(): (u)int_least16_t */
#define PRIdLEAST16    __PRIL2_PREFIX "d"
#define PRIiLEAST16    __PRIL2_PREFIX "i"
#define PRIoLEAST16    __PRIL2_PREFIX "o"
#define PRIuLEAST16    __PRIL2_PREFIX "u"
#define PRIxLEAST16    __PRIL2_PREFIX "x"
#define PRIXLEAST16    __PRIL2_PREFIX "X"

/* printf(): (u)int_least32_t */
#define PRIdLEAST32    __PRIL4_PREFIX "d"
#define PRIiLEAST32    __PRIL4_PREFIX "i"
#define PRIoLEAST32    __PRIL4_PREFIX "o"
#define PRIuLEAST32    __PRIL4_PREFIX "u"
#define PRIxLEAST32    __PRIL4_PREFIX "x"
#define PRIXLEAST32    __PRIL4_PREFIX "X"

/* printf(): (u)int_least64_t */
#define PRIdLEAST64    __PRIL8_PREFIX "d"
#define PRIiLEAST64    __PRIL8_PREFIX "i"
#define PRIoLEAST64    __PRIL8_PREFIX "o"
#define PRIuLEAST64    __PRIL8_PREFIX "u"
#define PRIxLEAST64    __PRIL8_PREFIX "x"
#define PRIXLEAST64    __PRIL8_PREFIX "X"

/* printf(): (u)int_fast8_t */
#define PRIdFAST8      __PRIF1_PREFIX "d"
#define PRIiFAST8      __PRIF1_PREFIX "i"
#define PRIoFAST8      __PRIF1_PREFIX "o"
#define PRIuFAST8      __PRIF1_PREFIX "u"
#define PRIxFAST8      __PRIF1_PREFIX "x"
#define PRIXFAST8      __PRIF1_PREFIX "X"

/* printf(): (u)int_fast16_t */
#define PRIdFAST16     __PRIF2_PREFIX "d"
#define PRIiFAST16     __PRIF2_PREFIX "i"
#define PRIoFAST16     __PRIF2_PREFIX "o"
#define PRIuFAST16     __PRIF2_PREFIX "u"
#define PRIxFAST16     __PRIF2_PREFIX "x"
#define PRIXFAST16     __PRIF2_PREFIX "X"

/* printf(): (u)int_fast32_t */
#define PRIdFAST32     __PRIF4_PREFIX "d"
#define PRIiFAST32     __PRIF4_PREFIX "i"
#define PRIoFAST32     __PRIF4_PREFIX "o"
#define PRIuFAST32     __PRIF4_PREFIX "u"
#define PRIxFAST32     __PRIF4_PREFIX "x"
#define PRIXFAST32     __PRIF4_PREFIX "X"

/* printf(): (u)int_fast64_t */
#define PRIdFAST64     __PRIF8_PREFIX "d"
#define PRIiFAST64     __PRIF8_PREFIX "i"
#define PRIoFAST64     __PRIF8_PREFIX "o"
#define PRIuFAST64     __PRIF8_PREFIX "u"
#define PRIxFAST64     __PRIF8_PREFIX "x"
#define PRIXFAST64     __PRIF8_PREFIX "X"

/* printf(): (u)intmax_t */
#define PRIdMAX        __PRI8_PREFIX "d"
#define PRIiMAX        __PRI8_PREFIX "i"
#define PRIoMAX        __PRI8_PREFIX "o"
#define PRIuMAX        __PRI8_PREFIX "u"
#define PRIxMAX        __PRI8_PREFIX "x"
#define PRIXMAX        __PRI8_PREFIX "X"

/* printf(): (u)intptr_t / void * */
#ifdef __PRIP_PREFIX
#define PRIdPTR        __PRIP_PREFIX "d" /* Id */
#define PRIiPTR        __PRIP_PREFIX "i" /* Ii */
#define PRIoPTR        __PRIP_PREFIX "o" /* Io */
#define PRIuPTR        __PRIP_PREFIX "u" /* Iu */
#define PRIxPTR        __PRIP_PREFIX "x" /* Ix */
#define PRIXPTR        __PRIP_PREFIX "X" /* IX */
#else /* __PRIP_PREFIX */
#define PRIdPTR        "td" /* ptrdiff_t */
#define PRIiPTR        "ti" /* ptrdiff_t */
#define PRIoPTR        "zo" /* size_t */
#define PRIuPTR        "zu" /* size_t */
#define PRIxPTR        "zx" /* size_t */
#define PRIXPTR        "zX" /* size_t */
#endif /* !__PRIP_PREFIX */

#ifdef __USE_KOS
/* printf(): (s)size_t */
#ifdef __PRIP_PREFIX
#define PRIdSIZ        __PRIP_PREFIX "d" /* Id */
#define PRIiSIZ        __PRIP_PREFIX "i" /* Ii */
#define PRIoSIZ        __PRIP_PREFIX "o" /* Io */
#define PRIuSIZ        __PRIP_PREFIX "u" /* Iu */
#define PRIxSIZ        __PRIP_PREFIX "x" /* Ix */
#define PRIXSIZ        __PRIP_PREFIX "X" /* IX */
#else /* __PRIP_PREFIX */
#define PRIdSIZ        "td" /* ptrdiff_t */
#define PRIiSIZ        "ti" /* ptrdiff_t */
#define PRIoSIZ        "zo" /* size_t */
#define PRIuSIZ        "zu" /* size_t */
#define PRIxSIZ        "zx" /* size_t */
#define PRIXSIZ        "zX" /* size_t */
#endif /* !__PRIP_PREFIX */

/* printf(): Custom size (use __SIZEOF_xxx__ macros with these) */
#define PRIdN(sizeof)  __PRIN_PREFIX(sizeof) "d"
#define PRIiN(sizeof)  __PRIN_PREFIX(sizeof) "i"
#define PRIoN(sizeof)  __PRIN_PREFIX(sizeof) "o"
#define PRIuN(sizeof)  __PRIN_PREFIX(sizeof) "u"
#define PRIxN(sizeof)  __PRIN_PREFIX(sizeof) "x"
#define PRIXN(sizeof)  __PRIN_PREFIX(sizeof) "X"
#endif /* __USE_KOS */




/* scanf(): (u)int8_t */
#define SCNd8          __SCA1_PREFIX "d"
#define SCNi8          __SCA1_PREFIX "i"
#define SCNu8          __SCA1_PREFIX "u"
#define SCNo8          __SCA1_PREFIX "o"
#define SCNx8          __SCA1_PREFIX "x"

/* scanf(): (u)int16_t */
#define SCNd16         __SCA2_PREFIX "d"
#define SCNi16         __SCA2_PREFIX "i"
#define SCNu16         __SCA2_PREFIX "u"
#define SCNo16         __SCA2_PREFIX "o"
#define SCNx16         __SCA2_PREFIX "x"

/* scanf(): (u)int32_t */
#define SCNd32         __SCA4_PREFIX "d"
#define SCNi32         __SCA4_PREFIX "i"
#define SCNu32         __SCA4_PREFIX "u"
#define SCNo32         __SCA4_PREFIX "o"
#define SCNx32         __SCA4_PREFIX "x"

/* scanf(): (u)int64_t */
#define SCNd64         __SCA8_PREFIX "d"
#define SCNi64         __SCA8_PREFIX "i"
#define SCNu64         __SCA8_PREFIX "u"
#define SCNo64         __SCA8_PREFIX "o"
#define SCNx64         __SCA8_PREFIX "x"

/* scanf(): (u)int_least8_t */
#define SCNdLEAST8     __SCAL1_PREFIX "d"
#define SCNiLEAST8     __SCAL1_PREFIX "i"
#define SCNuLEAST8     __SCAL1_PREFIX "u"
#define SCNoLEAST8     __SCAL1_PREFIX "o"
#define SCNxLEAST8     __SCAL1_PREFIX "x"

/* scanf(): (u)int_least16_t */
#define SCNdLEAST16    __SCAL2_PREFIX "d"
#define SCNiLEAST16    __SCAL2_PREFIX "i"
#define SCNuLEAST16    __SCAL2_PREFIX "u"
#define SCNoLEAST16    __SCAL2_PREFIX "o"
#define SCNxLEAST16    __SCAL2_PREFIX "x"

/* scanf(): (u)int_least32_t */
#define SCNdLEAST32    __SCAL4_PREFIX "d"
#define SCNiLEAST32    __SCAL4_PREFIX "i"
#define SCNuLEAST32    __SCAL4_PREFIX "u"
#define SCNoLEAST32    __SCAL4_PREFIX "o"
#define SCNxLEAST32    __SCAL4_PREFIX "x"

/* scanf(): (u)int_least64_t */
#define SCNdLEAST64    __SCAL8_PREFIX "d"
#define SCNiLEAST64    __SCAL8_PREFIX "i"
#define SCNuLEAST64    __SCAL8_PREFIX "u"
#define SCNoLEAST64    __SCAL8_PREFIX "o"
#define SCNxLEAST64    __SCAL8_PREFIX "x"

/* scanf(): (u)int_fast8_t */
#define SCNdFAST8      __SCAF1_PREFIX "d"
#define SCNiFAST8      __SCAF1_PREFIX "i"
#define SCNuFAST8      __SCAF1_PREFIX "u"
#define SCNoFAST8      __SCAF1_PREFIX "o"
#define SCNxFAST8      __SCAF1_PREFIX "x"

/* scanf(): (u)int_fast16_t */
#define SCNdFAST16     __SCAF2_PREFIX "d"
#define SCNiFAST16     __SCAF2_PREFIX "i"
#define SCNuFAST16     __SCAF2_PREFIX "u"
#define SCNoFAST16     __SCAF2_PREFIX "o"
#define SCNxFAST16     __SCAF2_PREFIX "x"

/* scanf(): (u)int_fast32_t */
#define SCNdFAST32     __SCAF4_PREFIX "d"
#define SCNiFAST32     __SCAF4_PREFIX "i"
#define SCNuFAST32     __SCAF4_PREFIX "u"
#define SCNoFAST32     __SCAF4_PREFIX "o"
#define SCNxFAST32     __SCAF4_PREFIX "x"

/* scanf(): (u)int_fast64_t */
#define SCNdFAST64     __SCAF8_PREFIX "d"
#define SCNiFAST64     __SCAF8_PREFIX "i"
#define SCNuFAST64     __SCAF8_PREFIX "u"
#define SCNoFAST64     __SCAF8_PREFIX "o"
#define SCNxFAST64     __SCAF8_PREFIX "x"

/* scanf(): (u)intmax_t */
#define SCNdMAX        __SCA8_PREFIX "d"
#define SCNiMAX        __SCA8_PREFIX "i"
#define SCNuMAX        __SCA8_PREFIX "u"
#define SCNoMAX        __SCA8_PREFIX "o"
#define SCNxMAX        __SCA8_PREFIX "x"

/* scanf(): (u)intptr_t / void * */
#define SCNdPTR        __SCAP_PREFIX "d"
#define SCNiPTR        __SCAP_PREFIX "i"
#define SCNuPTR        __SCAP_PREFIX "u"
#define SCNoPTR        __SCAP_PREFIX "o"
#define SCNxPTR        __SCAP_PREFIX "x"

#ifdef __USE_KOS
/* scanf(): (s)size_t */
#define SCNdSIZ        __SCAP_PREFIX "d"
#define SCNiSIZ        __SCAP_PREFIX "i"
#define SCNuSIZ        __SCAP_PREFIX "u"
#define SCNoSIZ        __SCAP_PREFIX "o"
#define SCNxSIZ        __SCAP_PREFIX "x"

/* scanf(): Custom size (use __SIZEOF_xxx__ macros with these) */
#define SCNdN(sizeof)  __SCAN_PREFIX(sizeof) "d"
#define SCNiN(sizeof)  __SCAN_PREFIX(sizeof) "i"
#define SCNuN(sizeof)  __SCAN_PREFIX(sizeof) "u"
#define SCNoN(sizeof)  __SCAN_PREFIX(sizeof) "o"
#define SCNxN(sizeof)  __SCAN_PREFIX(sizeof) "x"

/* U-scan command:
 *    Unsigned integer, where the radix is automatically detected,
 *    using the same syntax as a C compiler would accept:
 *       "1234":      Decimal
 *       "0777":      Octal
 *       "0xDEAD":    Hex    (casing is ignored)
 *       "0b010011":  Binary (extension; casing is ignored) */
#define SCNU8          __SCA1_PREFIX "U"
#define SCNU16         __SCA2_PREFIX "U"
#define SCNU32         __SCA4_PREFIX "U"
#define SCNU64         __SCA8_PREFIX "U"
#define SCNULEAST8     __SCAL1_PREFIX "U"
#define SCNULEAST16    __SCAL2_PREFIX "U"
#define SCNULEAST32    __SCAL4_PREFIX "U"
#define SCNULEAST64    __SCAL8_PREFIX "U"
#define SCNUFAST8      __SCAF1_PREFIX "U"
#define SCNUFAST16     __SCAF2_PREFIX "U"
#define SCNUFAST32     __SCAF4_PREFIX "U"
#define SCNUFAST64     __SCAF8_PREFIX "U"
#define SCNUMAX        __SCA8_PREFIX "U"
#define SCNUPTR        __SCAP_PREFIX "U"
#define SCNUSIZ        __SCAP_PREFIX "U"
#define SCNUN(sizeof)  __SCAN_PREFIX(sizeof) "U"
#endif /* __USE_KOS */



#ifdef __CC__

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("quot")
#pragma push_macro("rem")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef quot
#undef rem
struct __imaxdiv_struct {
	__INTMAX_TYPE__ quot; /* Quotient. */
	__INTMAX_TYPE__ rem;  /* Remainder. */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("rem")
#pragma pop_macro("quot")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#ifndef __std_imaxdiv_t_defined
#define __std_imaxdiv_t_defined 1
__NAMESPACE_STD_BEGIN
typedef struct __imaxdiv_struct imaxdiv_t;
__NAMESPACE_STD_END
#endif /* !__std_imaxdiv_t_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __imaxdiv_t_defined
#define __imaxdiv_t_defined 1
__NAMESPACE_STD_USING(imaxdiv_t)
#endif /* !__imaxdiv_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

__NAMESPACE_STD_BEGIN
#if __has_builtin(__builtin_imaxabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_imaxabs)
__CEIDECLARE(__ATTR_CONST,__INTMAX_TYPE__,__NOTHROW,imaxabs,(__INTMAX_TYPE__ __x),{ return __builtin_imaxabs(__x); })
#elif defined(__CRT_HAVE_imaxabs)
__CDECLARE(__ATTR_CONST,__INTMAX_TYPE__,__NOTHROW,imaxabs,(__INTMAX_TYPE__ __x),(__x))
#elif defined(__CRT_HAVE_abs) && __SIZEOF_INTMAX_T__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST,__INTMAX_TYPE__,__NOTHROW,imaxabs,(__INTMAX_TYPE__ __x),abs,(__x))
#elif defined(__CRT_HAVE_labs) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST,__INTMAX_TYPE__,__NOTHROW,imaxabs,(__INTMAX_TYPE__ __x),labs,(__x))
#elif defined(__CRT_HAVE_llabs) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST,__INTMAX_TYPE__,__NOTHROW,imaxabs,(__INTMAX_TYPE__ __x),llabs,(__x))
#elif defined(__CRT_HAVE__abs64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_CONST,__INTMAX_TYPE__,__NOTHROW,imaxabs,(__INTMAX_TYPE__ __x),_abs64,(__x))
#elif __SIZEOF_INTMAX_T__ == __SIZEOF_INT__
__NAMESPACE_STD_END
#include <local/stdlib/abs.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __INTMAX_TYPE__ __NOTHROW(__LIBCCALL imaxabs)(__INTMAX_TYPE__ __x) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(abs))((int)__x); }
#elif __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__NAMESPACE_STD_END
#include <local/stdlib/labs.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __INTMAX_TYPE__ __NOTHROW(__LIBCCALL imaxabs)(__INTMAX_TYPE__ __x) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(labs))((long)__x); }
#elif __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__NAMESPACE_STD_END
#include <local/stdlib/llabs.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __INTMAX_TYPE__ __NOTHROW(__LIBCCALL imaxabs)(__INTMAX_TYPE__ __x) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llabs))((__LONGLONG)__x); }
#else /* ... */
__NAMESPACE_STD_END
#include <local/inttypes/imaxabs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(imaxabs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __INTMAX_TYPE__ __NOTHROW(__LIBCCALL imaxabs)(__INTMAX_TYPE__ __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(imaxabs))(__x); })
#endif /* !... */
#ifdef __CRT_HAVE_imaxdiv
__CDECLARE(__ATTR_CONST,imaxdiv_t,__NOTHROW,imaxdiv,(__INTMAX_TYPE__ __numer, __INTMAX_TYPE__ __denom),(__numer,__denom))
#elif defined(__CRT_HAVE_div) && __SIZEOF_INTMAX_T__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST,imaxdiv_t,__NOTHROW,imaxdiv,(__INTMAX_TYPE__ __numer, __INTMAX_TYPE__ __denom),div,(__numer,__denom))
#elif defined(__CRT_HAVE_ldiv) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST,imaxdiv_t,__NOTHROW,imaxdiv,(__INTMAX_TYPE__ __numer, __INTMAX_TYPE__ __denom),ldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_lldiv) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST,imaxdiv_t,__NOTHROW,imaxdiv,(__INTMAX_TYPE__ __numer, __INTMAX_TYPE__ __denom),lldiv,(__numer,__denom))
#else /* ... */
__NAMESPACE_STD_END
#include <local/inttypes/imaxdiv.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(imaxdiv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST imaxdiv_t __NOTHROW(__LIBCCALL imaxdiv)(__INTMAX_TYPE__ __numer, __INTMAX_TYPE__ __denom) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(imaxdiv))(__numer, __denom); })
#endif /* !... */
#ifdef __CRT_HAVE_strtoimax
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto32) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto32,(__nptr,__endptr,__base))
#elif __SIZEOF_INTMAX_T__ == 8
__NAMESPACE_STD_END
#include <local/stdlib/strto64.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL strtoimax)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64))(__nptr, __endptr, __base); }
#elif __SIZEOF_INTMAX_T__ == 4
__NAMESPACE_STD_END
#include <local/stdlib/strto32.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL strtoimax)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32))(__nptr, __endptr, __base); }
#else /* ... */
__NAMESPACE_STD_END
#include <local/inttypes/strtoimax.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoimax, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL strtoimax)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoimax))(__nptr, __endptr, __base); })
#endif /* !... */
#ifdef __CRT_HAVE_strtoumax
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou32) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou32,(__nptr,__endptr,__base))
#elif __SIZEOF_INTMAX_T__ == 8
__NAMESPACE_STD_END
#include <local/stdlib/strtou64.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL strtoumax)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64))(__nptr, __endptr, __base); }
#elif __SIZEOF_INTMAX_T__ == 4
__NAMESPACE_STD_END
#include <local/stdlib/strtou32.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL strtoumax)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32))(__nptr, __endptr, __base); }
#else /* ... */
__NAMESPACE_STD_END
#include <local/inttypes/strtoumax.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoumax, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL strtoumax)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoumax))(__nptr, __endptr, __base); })
#endif /* !... */
#ifdef __CRT_HAVE_wcstoimax
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif __SIZEOF_INTMAX_T__ == 8
__NAMESPACE_STD_END
#include <local/wchar/wcsto64.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstoimax)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#elif __SIZEOF_INTMAX_T__ == 4
__NAMESPACE_STD_END
#include <local/wchar/wcsto32.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstoimax)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
__NAMESPACE_STD_END
#include <local/inttypes/wcstoimax.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoimax, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstoimax)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoimax))(__nptr, __endptr, __base); })
#endif /* !... */
#ifdef __CRT_HAVE_wcstoumax
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif __SIZEOF_INTMAX_T__ == 8
__NAMESPACE_STD_END
#include <local/wchar/wcstou64.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstoumax)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#elif __SIZEOF_INTMAX_T__ == 4
__NAMESPACE_STD_END
#include <local/wchar/wcstou32.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstoumax)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
__NAMESPACE_STD_END
#include <local/inttypes/wcstoumax.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoumax, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstoumax)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoumax))(__nptr, __endptr, __base); })
#endif /* !... */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(imaxabs)
__NAMESPACE_STD_USING(imaxdiv)
__NAMESPACE_STD_USING(strtoimax)
__NAMESPACE_STD_USING(strtoumax)
__NAMESPACE_STD_USING(wcstoimax)
__NAMESPACE_STD_USING(wcstoumax)
#endif /* !__CXX_SYSTEM_HEADER */




#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_strtoimax_l
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoimax_l)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoi64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto32_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strto32_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_INTMAX_T__ == 8
#include <local/stdlib/strto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL strtoimax_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_INTMAX_T__ == 4
#include <local/stdlib/strto32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL strtoimax_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <local/inttypes/strtoimax_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoimax_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL strtoimax_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoimax_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_strtoumax_l
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoumax_l)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoui64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou32_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtou32_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_INTMAX_T__ == 8
#include <local/stdlib/strtou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL strtoumax_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_INTMAX_T__ == 4
#include <local/stdlib/strtou32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL strtoumax_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <local/inttypes/strtoumax_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoumax_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL strtoumax_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoumax_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcstoimax_l
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto32_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto32_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_INTMAX_T__ == 8
#include <local/wchar/wcsto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstoimax_l)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#elif __SIZEOF_INTMAX_T__ == 4
#include <local/wchar/wcsto32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstoimax_l)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <local/inttypes/wcstoimax_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoimax_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstoimax_l)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoimax_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcstoumax_l
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou32_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou32_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_INTMAX_T__ == 8
#include <local/wchar/wcstou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstoumax_l)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#elif __SIZEOF_INTMAX_T__ == 4
#include <local/wchar/wcstou32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstoumax_l)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <local/inttypes/wcstoumax_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoumax_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstoumax_l)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoumax_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#endif /* __USE_XOPEN2K8 */
#endif /* __USE_KOS */



#ifdef __USE_DOS
#ifdef __CRT_HAVE_strtoimax_l
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoimax_l)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoi64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto32_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_strtoimax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strto32_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_INTMAX_T__ == 8
#include <local/stdlib/strto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL _strtoimax_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_INTMAX_T__ == 4
#include <local/stdlib/strto32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL _strtoimax_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <local/inttypes/strtoimax_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL _strtoimax_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoimax_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_strtoumax_l
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoumax_l)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoui64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou32_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtou32_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_INTMAX_T__ == 8
#include <local/stdlib/strtou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL _strtoumax_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64_l))(__nptr, __endptr, __base, __locale); }
#elif __SIZEOF_INTMAX_T__ == 4
#include <local/stdlib/strtou32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL _strtoumax_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32_l))(__nptr, __endptr, __base, __locale); }
#else /* ... */
#include <local/inttypes/strtoumax_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL _strtoumax_l)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoumax_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_wcstoimax_l
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto32_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,_wcstoimax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto32_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_INTMAX_T__ == 8
#include <local/wchar/wcsto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoimax_l)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#elif __SIZEOF_INTMAX_T__ == 4
#include <local/wchar/wcsto32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoimax_l)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__INTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <local/inttypes/wcstoimax_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoimax_l)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoimax_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_wcstoumax_l
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou32_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,_wcstoumax_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou32_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_INTMAX_T__ == 8
#include <local/wchar/wcstou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoumax_l)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#elif __SIZEOF_INTMAX_T__ == 4
#include <local/wchar/wcstou32_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoumax_l)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <local/inttypes/wcstoumax_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoumax_l)(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoumax_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#endif /* __USE_DOS */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_INTTYPES_H)
#include <parts/uchar/inttypes.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_INTTYPES_H */
#endif /* __USE_UTF */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CINTTYPES 1
#undef _INTTYPES_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CINTTYPES */
#endif /* !_INTTYPES_H */
