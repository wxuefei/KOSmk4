/* HASH CRC-32:0x68635163 */
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
#ifndef __local_strchr_defined
#define __local_strchr_defined 1
__NAMESPACE_LOCAL_BEGIN
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__LOCAL_LIBC(strchr) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strchr))(char const *__restrict __haystack,
                                                    int __needle) {
#line 216 "kos/src/libc/magic/string.c"
	for (; *__haystack; ++__haystack)
		if (*__haystack == (char)__needle)
			return (char *)__haystack;
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strchr_defined */
