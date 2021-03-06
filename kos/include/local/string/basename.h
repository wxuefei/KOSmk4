/* HASH CRC-32:0x286c946c */
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
#ifndef __local_basename_defined
#define __local_basename_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(basename) __ATTR_PURE __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(basename))(char const *__filename) {
	char __ch, *__iter = (char *)__filename, *__result = __NULLPTR;
	if (!__filename || !*__filename)
		return (char *)__filename;
	do {
		__ch = *__iter++;
#ifdef _WIN32
		if (__ch == '/' || __ch == '\\')
			__result = __iter;
#else /* _WIN32 */
		if (__ch == '/')
			__result = __iter;
#endif /* !_WIN32 */
	} while (__ch);
	if __unlikely(!__result)
		return (char *)__filename; /* Path doesn't contain '/'. */
	if (*__result)
		return __result; /* Last character isn't a '/'. */
	__iter = __result;
#ifdef _WIN32
	while (__iter != __filename && (__iter[-1] == '/' || __iter[-1] == '\\'))
		--__iter;
#else /* _WIN32 */
	while (__iter != __filename && __iter[-1] == '/')
		--__iter;
#endif /* !_WIN32 */
	if (__iter == __filename)
		return __result-1; /* Only `'/'"-characters. */
	//*iter = '\0'; /* Trim all ending `'/'"-characters. */
#ifdef _WIN32
	while (__iter != __filename && (__iter[-1] != '/' || __iter[-1] != '\\'))
		--__iter; /* Scan until the previous '/'. */
#else /* _WIN32 */
	while (__iter != __filename && __iter[-1] != '/')
		--__iter; /* Scan until the previous '/'. */
#endif /* !_WIN32 */
	return __iter; /* Returns string after previous '/'. */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_basename_defined
#define __local___localdep_basename_defined 1
#define __localdep_basename __LIBC_LOCAL_NAME(basename)
#endif /* !__local___localdep_basename_defined */
#endif /* !__local_basename_defined */
