/* HASH CRC-32:0x1ffed497 */
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
#ifndef __local__expand_dbg_defined
#if (defined(__CRT_HAVE_realloc_in_place) || defined(__CRT_HAVE__expand))
#define __local__expand_dbg_defined 1
/* Dependency: "realloc_in_place" */
#ifndef ____localdep_realloc_in_place_defined
#define ____localdep_realloc_in_place_defined 1
#if defined(__CRT_HAVE_realloc_in_place)
/* @EXCEPT: `realloc_in_place()' will return `NULL' if the reallocation isn't
 *           possible due to the requested memory above `MALLPTR' already being
 *           in use. However, an `E_BADALLOC' exception is thrown if insufficient
 *           memory (for internal control structures) is available to complete
 *           the operation */
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc_in_place,(void *__restrict __mallptr, __SIZE_TYPE__ __n_bytes),realloc_in_place,(__mallptr,__n_bytes))
#elif defined(__CRT_HAVE__expand)
/* @EXCEPT: `realloc_in_place()' will return `NULL' if the reallocation isn't
 *           possible due to the requested memory above `MALLPTR' already being
 *           in use. However, an `E_BADALLOC' exception is thrown if insufficient
 *           memory (for internal control structures) is available to complete
 *           the operation */
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc_in_place,(void *__restrict __mallptr, __SIZE_TYPE__ __n_bytes),_expand,(__mallptr,__n_bytes))
#else /* LIBC: realloc_in_place */
#undef ____localdep_realloc_in_place_defined
#endif /* realloc_in_place... */
#endif /* !____localdep_realloc_in_place_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_expand_dbg) __ATTR_ALLOC_SIZE((2)) __ATTR_WUNUSED __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_expand_dbg))(void *__ptr,
                                                         __SIZE_TYPE__ __num_bytes,
                                                         int __block_type,
                                                         char const *__filename,
                                                         int __line) {
#line 324 "kos/src/libc/magic/crtdbg.c"
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return __localdep_realloc_in_place(__ptr, __num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_realloc_in_place) || defined(__CRT_HAVE__expand)) */
#endif /* !__local__expand_dbg_defined */