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
#ifndef __assertion_failed
#include "../__stdinc.h"
#ifndef __CC__
#define __assertion_failed(expr_str)                            /* nothing */
#define __assertion_failedf(expr_str, ...)                      /* nothing */
#define __assertion_failed_at(expr_str, file, line, func)       /* nothing */
#define __assertion_failedf_at(expr_str, file, line, func, ...) /* nothing */
#else /* !__CC__ */
#include "../features.h"
#include "../__crt.h"
__SYSDECL_BEGIN
__NAMESPACE_INT_BEGIN
#ifdef __INTELLISENSE__
extern void (__check_assertion)(__BOOL __expr);
extern void (__check_assertionf)(__BOOL __expr, char const *__restrict __format, ...);
#endif /* __INTELLISENSE__ */
#if defined(__CRT_HAVE___afail) && !defined(__NO_FUNCTION__)
__CDECLARE_VOID(__ATTR_COLD __ATTR_NORETURN,,__afail,(char const *__expr, char const *__file, unsigned int __line, char const *__func),(__expr,__file,__line,__func))
#define __assertion_failed(expr_str) (__NAMESPACE_INT_SYM __afail)(expr_str, __FILE__, __LINE__, __FUNCTION__)
#define __assertion_failed_at(expr_str, file, line, func) (__NAMESPACE_INT_SYM __afail)(expr_str, file, line, func)
#elif defined(__CRT_HAVE___assert_fail) && !defined(__NO_FUNCTION__)
__CDECLARE_VOID(__ATTR_COLD __ATTR_NORETURN,,__assert_fail,(char const *__restrict __expr, char const *__restrict __file, unsigned int __line, char const *__func),(__expr,__file,__line,__func))
#define __assertion_failed(expr_str) (__NAMESPACE_INT_SYM __assert_fail)(expr_str, __FILE__, __LINE__, __FUNCTION__)
#define __assertion_failed_at(expr_str, file, line, func) (__NAMESPACE_INT_SYM __assert_fail)(expr_str, file, line, func)
#elif defined(__CRT_HAVE___assert_func) && !defined(__NO_FUNCTION__)
__CDECLARE_VOID(__ATTR_COLD __ATTR_NORETURN,,__assert_func,(char const *__file, unsigned int __line, char const *__func, char const *__expr),(__file,__line,__func,__expr))
#define __assertion_failed(expr_str) (__NAMESPACE_INT_SYM __assert_func)(__FILE__, __LINE__, __FUNCTION__, expr_str)
#define __assertion_failed_at(expr_str, file, line, func) (__NAMESPACE_INT_SYM __assert_func)(file, line, func, expr_str)
#elif defined(__CRT_HAVE___assertfail) && !defined(__NO_FUNCTION__)
#include <hybrid/typecore.h>
__CDECLARE_VOID(__ATTR_COLD __ATTR_NORETURN,,__assertfail,(char const *__expr, char const *__file, unsigned int __line, char const *__func, __SIZE_TYPE__ __charsize),(__expr,__file,__line,__func,__charsize))
#define __assertion_failed(expr_str) (__NAMESPACE_INT_SYM __assertfail)(expr_str, __FILE__, __LINE__, __FUNCTION__, sizeof(char))
#define __assertion_failed_at(expr_str, file, line, func) (__NAMESPACE_INT_SYM __assertfail)(expr_str, file, line, func, sizeof(char))
#elif defined(__CRT_HAVE__assert)
__CDECLARE_VOID(__ATTR_COLD __ATTR_NORETURN,,_assert,(char const *__restrict __expr, char const *__restrict __file, unsigned int __line),(__expr,__file,__line))
#define __assertion_failed(expr_str) (__NAMESPACE_INT_SYM _assert)(expr_str, __FILE__, __LINE__)
#define __assertion_failed_at(expr_str, file, line, func) (__NAMESPACE_INT_SYM _assert)(expr_str, file, line)
#elif defined(__CRT_HAVE___assert)
__CDECLARE_VOID(__ATTR_COLD __ATTR_NORETURN,,__assert,(char const *__restrict __file, unsigned int __line, char const *__restrict __expr),(__file,__line,__expr))
#define __assertion_failed(expr_str) (__NAMESPACE_INT_SYM __assert)(__FILE__, __LINE__, expr_str)
#define __assertion_failed_at(expr_str, file, line, func) (__NAMESPACE_INT_SYM __assert)(file, line, expr_str)
#elif defined(__CRT_HAVE___afail)
__CDECLARE_VOID(__ATTR_COLD __ATTR_NORETURN,,__afail,(char const *__expr, char const *__file, unsigned int __line, char const *__func),(__expr,__file,__line,__func))
#define __assertion_failed(expr_str) (__NAMESPACE_INT_SYM __afail)(expr_str, __FILE__, __LINE__, __NULLPTR)
#define __assertion_failed_at(expr_str, file, line, func) (__NAMESPACE_INT_SYM __afail)(expr_str, file, line, func)
#elif defined(__CRT_HAVE___assert_fail)
__CDECLARE_VOID(__ATTR_COLD __ATTR_NORETURN,,__assert_fail,(char const *__restrict __expr, char const *__restrict __file, unsigned int __line, char const *__func),(__expr,__file,__line,__func))
#define __assertion_failed(expr_str) (__NAMESPACE_INT_SYM __assert_fail)(expr_str, __FILE__, __LINE__, __NULLPTR)
#define __assertion_failed_at(expr_str, file, line, func) (__NAMESPACE_INT_SYM __assert_fail)(expr_str, file, line, func)
#elif defined(__CRT_HAVE___assert_func)
__CDECLARE_VOID(__ATTR_COLD __ATTR_NORETURN,,__assert_func,(char const *__file, unsigned int __line, char const *__func, char const *__expr),(__file,__line,__func,__expr))
#define __assertion_failed(expr_str) (__NAMESPACE_INT_SYM __assert_func)(__FILE__, __LINE__, __NULLPTR, expr_str)
#define __assertion_failed_at(expr_str, file, line, func) (__NAMESPACE_INT_SYM __assert_func)(file, line, func, func, expr_str)
#elif defined(__CRT_HAVE___assertfail)
#include <hybrid/typecore.h>
__CDECLARE_VOID(__ATTR_COLD __ATTR_NORETURN,,__assertfail,(char const *__expr, char const *__file, unsigned int __line, char const *__func, __SIZE_TYPE__ __charsize),(__expr,__file,__line,__func,__charsize))
#define __assertion_failed(expr_str) (__NAMESPACE_INT_SYM __assertfail)(expr_str, __FILE__, __LINE__, __NULLPTR, sizeof(char))
#define __assertion_failed_at(expr_str, file, line, func) (__NAMESPACE_INT_SYM __assertfail)(expr_str, file, line, func, sizeof(char))
#else /* ... */
#define __assertion_failed(expr_str) (__NAMESPACE_INT_SYM __fallback_assert_fail)()
#define __assertion_failed_at(expr_str, file, line, func) (__NAMESPACE_INT_SYM __fallback_assert_fail)()
__LOCAL_LIBC(__fallback_assert_fail) __ATTR_COLD __ATTR_NORETURN
void (__LIBCCALL __fallback_assert_fail)(void) {
	/* This is the best we can do here... */
	for (;;) {
	}
}
#endif /* !... */

#ifdef __CRT_HAVE___acheck
__CDECLARE(__ATTR_COLD,__BOOL,,__acheck,(char const *__expr, char const *__file, unsigned int __line, char const *__func),(__expr,__file,__line,__func))
#define __assertion_check(expr_str) (__NAMESPACE_INT_SYM __acheck)(expr_str, __FILE__, __LINE__, __FUNCTION__)
#define __assertion_check_at(expr_str, file, line, func) (__NAMESPACE_INT_SYM __acheck)(expr_str, file, line, func)
#endif /* __CRT_HAVE___acheck */

#ifdef __CRT_HAVE___acheckf
__LIBC __ATTR_COLD __BOOL (__VLIBCCALL __acheckf)(char const *__expr, char const *__file, unsigned int __line, char const *__func, char const *__format, ...) __CASMNAME_SAME("__acheckf");
#define __assertion_checkf(expr_str, ...) (__NAMESPACE_INT_SYM __acheckf)(expr_str, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define __assertion_checkf_at(expr_str, file, line, func, ...) (__NAMESPACE_INT_SYM __acheckf)(expr_str, file, line, func, __VA_ARGS__)
#elif defined(__assertion_check)
#define __assertion_checkf(expr_str, ...) __assertion_check(expr_str)
#define __assertion_checkf_at(expr_str, file, line, func, ...) __assertion_check_at(expr_str, file, line, func)
#endif /* __CRT_HAVE___acheckf */

#ifdef __CRT_HAVE___afailf
__LIBC __ATTR_COLD __ATTR_NORETURN void (__VLIBCCALL __afailf)(char const *__expr, char const *__file, unsigned int __line, char const *__func, char const *__format, ...) __CASMNAME_SAME("__afailf");
#define __assertion_failedf(expr_str, ...) (__NAMESPACE_INT_SYM __afailf)(expr_str, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define __assertion_failedf_at(expr_str, file, line, func, ...) (__NAMESPACE_INT_SYM __afailf)(expr_str, file, line, func, __VA_ARGS__)
#else /* __CRT_HAVE___afailf */
#define __assertion_failedf(expr_str, ...) __assertion_failed(expr_str)
#define __assertion_failedf_at(expr_str, file, line, func, ...) __assertion_failed_at(expr_str, file, line, func)
#endif /* !__CRT_HAVE___afailf */

__NAMESPACE_INT_END
__SYSDECL_END
#endif /* __CC__ */
#endif /* !__assertion_failed */