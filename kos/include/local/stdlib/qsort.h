/* HASH CRC-32:0x11611525 */
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
#ifndef __local_qsort_defined
#define __local_qsort_defined 1
#include <__crt.h>
#ifndef ____compar_fn_t_defined
#define ____compar_fn_t_defined 1
typedef int (__LIBCCALL *__compar_fn_t)(void const *__a, void const *__b);
#endif /* !____compar_fn_t_defined */
#include <kos/anno.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: qsort_r from stdlib */
#ifndef __local___localdep_qsort_r_defined
#define __local___localdep_qsort_r_defined 1
#ifdef __CRT_HAVE_qsort_r
__NAMESPACE_LOCAL_END
#ifndef __compar_d_fn_t_defined
#define __compar_d_fn_t_defined 1
typedef int (__LIBKCALL *__compar_d_fn_t)(void const *__a, void const *__b, void *__arg);
#endif /* !__compar_d_fn_t_defined */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NONNULL((1, 4)),__THROWING,__localdep_qsort_r,(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_d_fn_t __cmp, void *__arg),qsort_r,(__pbase,__item_count,__item_size,__cmp,__arg))
#else /* __CRT_HAVE_qsort_r */
__NAMESPACE_LOCAL_END
#include <local/stdlib/qsort_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_qsort_r __LIBC_LOCAL_NAME(qsort_r)
#endif /* !__CRT_HAVE_qsort_r */
#endif /* !__local___localdep_qsort_r_defined */
__NAMESPACE_LOCAL_END
#ifndef __LIBCCALL_CALLER_CLEANUP
#ifndef ____invoke_compare_helper_defined
__NAMESPACE_LOCAL_BEGIN
#define ____invoke_compare_helper_defined 1
__LOCAL_LIBC(__invoke_compare_helper) int
(__LIBCCALL __invoke_compare_helper)(void const *__a, void const *__b, void *__arg) {
	return (*(__compar_fn_t)__arg)(__a, __b);
}
__NAMESPACE_LOCAL_END
#endif /* !____invoke_compare_helper_defined */
#endif /* !__LIBCCALL_CALLER_CLEANUP */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(qsort) __ATTR_NONNULL((1, 4)) void
(__LIBCCALL __LIBC_LOCAL_NAME(qsort))(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, __compar_fn_t __cmp) __THROWS(...) {
#ifdef __LIBCCALL_CALLER_CLEANUP
	__localdep_qsort_r(__pbase, __item_count, __item_size,
	        (int(__LIBCCALL *)(void const *, void const *, void *))(void *)__cmp,
	        __NULLPTR);
#else /* __LIBCCALL_CALLER_CLEANUP */
	__localdep_qsort_r(__pbase, __item_count, __item_size,
	        &__NAMESPACE_LOCAL_SYM __invoke_compare_helper,
	        (void *)__cmp);
#endif /* !__LIBCCALL_CALLER_CLEANUP */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_qsort_defined
#define __local___localdep_qsort_defined 1
#define __localdep_qsort __LIBC_LOCAL_NAME(qsort)
#endif /* !__local___localdep_qsort_defined */
#endif /* !__local_qsort_defined */
