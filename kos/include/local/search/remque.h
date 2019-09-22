/* HASH CRC-32:0x2a32cb92 */
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
#ifndef __local_remque_defined
#define __local_remque_defined 1
/* Dependency: "link" from "unistd" */
#ifndef ____localdep_link_defined
#define ____localdep_link_defined 1
#if defined(__CRT_HAVE_link)
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_link,(char const *__from, char const *__to),link,(__from,__to))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_linkat)
#include <local/unistd/link.h>
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
#define __localdep_link (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(link))
#else /* CUSTOM: link */
#undef ____localdep_link_defined
#endif /* link... */
#endif /* !____localdep_link_defined */

__NAMESPACE_LOCAL_BEGIN
/* Unlink ELEM from the doubly-linked list that it is in */
__LOCAL_LIBC(remque) __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(remque))(void *__restrict __elem) {
#line 128 "kos/src/libc/magic/search.c"
	struct __localdep_link {
		struct __localdep_link *__l_forw; /* [0..1] Forward link */
		struct __localdep_link *__l_back; /* [0..1] Backward link */
	};
	struct __localdep_link *__prev, *__next;
	__prev = ((struct __localdep_link *)__elem)->__l_back;
	__next = ((struct __localdep_link *)__elem)->__l_forw;
	if (__prev)
		__prev->__l_forw = __next;
	if (__next)
		__next->__l_back = __prev;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_remque_defined */
