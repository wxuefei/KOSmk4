/* HASH CRC-32:0x6013b650 */
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
#ifndef __local_bsearch_defined
#define __local_bsearch_defined 1
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined 1
typedef int (__LIBCCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
/* Dependency: "bsearch_r" from "stdlib" */
#ifndef ____localdep_bsearch_r_defined
#define ____localdep_bsearch_r_defined 1
#if defined(__CRT_HAVE_bsearch_r)
__CREDIRECT(__ATTR_NONNULL((1, 2, 5)) __ATTR_WUNUSED,void *,__NOTHROW_NCX,__localdep_bsearch_r,(void const *__pkey, void const *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg),bsearch_r,(__pkey,__pbase,__item_count,__item_size,__cmp,__arg))
#else /* LIBC: bsearch_r */
#include <local/stdlib/bsearch_r.h>
#define __localdep_bsearch_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bsearch_r))
#endif /* bsearch_r... */
#endif /* !____localdep_bsearch_r_defined */

__NAMESPACE_LOCAL_BEGIN
#ifndef ____invoke_compare_helper_defined
#define ____invoke_compare_helper_defined 1
__PRIVATE int (__LIBCCALL __invoke_compare_helper)(void const *__a, void const *__b, void *__arg) {
	return (*(__compar_fn_t)__arg)(__a, __b);
}
#endif /* !____invoke_compare_helper_defined */
__LOCAL_LIBC(bsearch) __ATTR_NONNULL((1, 2, 5)) __ATTR_WUNUSED void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(bsearch))(void const *__pkey,
                                                     void const *__pbase,
                                                     __SIZE_TYPE__ __item_count,
                                                     __SIZE_TYPE__ __item_size,
                                                     __compar_fn_t __cmp) {
#line 441 "kos/src/libc/magic/stdlib.c"
	return __localdep_bsearch_r(__pkey, __pbase, __item_count, __item_size, &__invoke_compare_helper, (void *)__cmp);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_bsearch_defined */
