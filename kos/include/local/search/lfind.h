/* HASH CRC-32:0x528f218b */
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
#ifndef __local_lfind_defined
#define __local_lfind_defined 1
__NAMESPACE_LOCAL_BEGIN
/* Perform linear search for KEY by comparing by COMPAR in an array [BASE, BASE+NMEMB*SIZE) */
__LOCAL_LIBC(lfind) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(lfind))(void const *__key,
                                                   void const *__base,
                                                   __SIZE_TYPE__ *__nmemb,
                                                   __SIZE_TYPE__ __size,
                                                   __compar_fn_t __compar) {
#line 772 "kos/src/libc/magic/search.c"
	__SIZE_TYPE__ __i, __count = *__nmemb;
	void const *__result = __base;
	for (__i = 0; __i < __count; ++__i) {
		if ((*__compar)(__key, __result) == 0)
			return (void *)__result;
		__result = (__BYTE_TYPE__ *)__result + __size;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_lfind_defined */
