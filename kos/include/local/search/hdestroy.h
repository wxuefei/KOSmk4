/* HASH CRC-32:0x7cc44479 */
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
#ifndef __local_hdestroy_defined
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE_hdestroy_r)
#define __local_hdestroy_defined 1
#include <__crt.h>
#ifndef __hsearch_data_defined
#define __hsearch_data_defined 1
struct _ENTRY;
struct hsearch_data {
	struct _ENTRY *table;
	unsigned int     size;
	unsigned int     filled;
};
#endif /* !__hsearch_data_defined */
/* Dependency: "hdestroy_r" from "search" */
#ifndef ____localdep_hdestroy_r_defined
#define ____localdep_hdestroy_r_defined 1
#ifdef __CRT_HAVE_hdestroy_r
/* Reentrant versions which can handle multiple hashing tables at the same time */
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_hdestroy_r,(struct hsearch_data *__htab),hdestroy_r,(__htab))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
#include <local/search/hdestroy_r.h>
/* Reentrant versions which can handle multiple hashing tables at the same time */
#define __localdep_hdestroy_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hdestroy_r))
#else /* CUSTOM: hdestroy_r */
#undef ____localdep_hdestroy_r_defined
#endif /* hdestroy_r... */
#endif /* !____localdep_hdestroy_r_defined */

__NAMESPACE_LOCAL_BEGIN
#ifndef __local_htab_defined
#define __local_htab_defined 1
__LOCAL_LIBC_DATA(__htab) struct hsearch_data __htab = {__NULLPTR, 0, 0};
#endif /* !__local_htab_defined */
/* Destroy current internal hashing table */
__LOCAL_LIBC(hdestroy) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(hdestroy))(void) {
#line 234 "kos/src/libc/magic/search.c"
	__localdep_hdestroy_r(&__htab);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE_hdestroy_r */
#endif /* !__local_hdestroy_defined */
