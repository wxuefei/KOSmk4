/* HASH CRC-32:0x9f3cc2a */
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
#ifndef __local_tfind_defined
#define __local_tfind_defined 1
#include <__crt.h>
#ifndef ____compar_fn_t_defined
#define ____compar_fn_t_defined 1
typedef int (__LIBCCALL *__compar_fn_t)(void const *__a, void const *__b);
#endif /* !____compar_fn_t_defined */
__NAMESPACE_LOCAL_BEGIN
/* Search for an entry matching the given KEY in the tree pointed
 * to by *ROOTP. If no matching entry is available return NULL */
__LOCAL_LIBC(tfind) __ATTR_NONNULL((3)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(tfind))(void const *__key, void *const *__vrootp, __compar_fn_t __compar) {
	typedef struct __node_struct {
		void const           *__key;
		struct __node_struct *__left_node;
		struct __node_struct *__right_node;
		__UINTPTR_TYPE__      __is_red;
	} *__node;
	__node __root, *__rootp = (__node *)__vrootp;
	if (__rootp == __NULLPTR)
		return __NULLPTR;
	while ((__root = *__rootp) != __NULLPTR) {
		int __r = (*__compar)(__key, __root->__key);
		if (__r == 0)
			return __root;
		__rootp = __r < 0 ? &__root->__left_node
		              : &__root->__right_node;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tfind_defined
#define __local___localdep_tfind_defined 1
#define __localdep_tfind __LIBC_LOCAL_NAME(tfind)
#endif /* !__local___localdep_tfind_defined */
#endif /* !__local_tfind_defined */
