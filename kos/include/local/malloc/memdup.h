/* HASH CRC-32:0x76906f48 */
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
#ifndef __local_memdup_defined
#if ((defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)) || (__has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)) || defined(__CRT_HAVE_malloc))
#define __local_memdup_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "malloc" from "stdlib" */
#ifndef ____localdep_malloc_defined
#define ____localdep_malloc_defined 1
#ifdef __std___localdep_malloc_defined
__NAMESPACE_STD_USING(__localdep_malloc)
#elif __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL __localdep_malloc)(__SIZE_TYPE__ __n_bytes) { return __builtin_malloc(__n_bytes); }
#elif defined(__CRT_HAVE_malloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __n_bytes),malloc,(__n_bytes))
#elif (defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc))
#include <local/stdlib/malloc.h>
#define __localdep_malloc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(malloc))
#else /* CUSTOM: malloc */
#undef ____localdep_malloc_defined
#endif /* malloc... */
#endif /* !____localdep_malloc_defined */

/* Dependency: "memcpy" from "string" */
#ifndef ____localdep_memcpy_defined
#define ____localdep_memcpy_defined 1
#if defined(__fast_memcpy_defined)
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpy (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))
#elif defined(__CRT_HAVE_memcpy)
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* LIBC: memcpy */
#include <local/string/memcpy.h>
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy))
#endif /* memcpy... */
#endif /* !____localdep_memcpy_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memdup) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memdup))(void const *__restrict __ptr,
                                                    __SIZE_TYPE__ __n_bytes) {
#line 160 "kos/src/libc/magic/malloc.c"
	void *__result;
	__result = __localdep_malloc(__n_bytes);
	if __likely(__result)
		__localdep_memcpy(__result, __ptr, __n_bytes);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* ((defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)) || (__has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)) || defined(__CRT_HAVE_malloc)) */
#endif /* !__local_memdup_defined */
