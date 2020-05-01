/* HASH CRC-32:0xa1143aa8 */
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
#ifndef __local_inet_addr_defined
#define __local_inet_addr_defined 1
#include <__crt.h>
#include <netinet/in.h>
/* Dependency: "inet_paton" from "arpa.inet" */
#ifndef ____localdep_inet_paton_defined
#define ____localdep_inet_paton_defined 1
#ifdef __CRT_HAVE_inet_paton
/* Same as `inet_aton()', but update `*pcp' to point after the address
 * Accepted notations are:
 *     a.b.c.d  (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd    (1.564)
 *     abcd     (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123    (hex)
 *     0123     (oct)
 * @param: network_addr: When non-zero, `*pcp' is a network address
 * @return: 0: Bad input format
 * @return: 1: Success */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_inet_paton,(char const **__restrict __pcp, struct in_addr *__restrict __inp, int __network_addr),inet_paton,(__pcp,__inp,__network_addr))
#else /* LIBC: inet_paton */
#include <local/arpa.inet/inet_paton.h>
/* Same as `inet_aton()', but update `*pcp' to point after the address
 * Accepted notations are:
 *     a.b.c.d  (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd    (1.564)
 *     abcd     (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123    (hex)
 *     0123     (oct)
 * @param: network_addr: When non-zero, `*pcp' is a network address
 * @return: 0: Bad input format
 * @return: 1: Success */
#define __localdep_inet_paton (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_paton))
#endif /* inet_paton... */
#endif /* !____localdep_inet_paton_defined */

__NAMESPACE_LOCAL_BEGIN
/* Convert Internet host address from numbers-and-dots
 * notation in CP into binary data in network byte order
 * Accepted notations are:
 *     a.b.c.d  (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd    (1.564)
 *     abcd     (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123    (hex)
 *     0123     (oct) */
__LOCAL_LIBC(inet_addr) __ATTR_PURE __ATTR_NONNULL((1)) in_addr_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(inet_addr))(char const *__restrict __cp) {
#line 124 "kos/src/libc/magic/arpa.inet.c"
	struct in_addr __addr;
	if (!__localdep_inet_paton((char const **)&__cp, &__addr, 0) || *__cp)
		return INADDR_NONE;
	return __addr.s_addr;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_inet_addr_defined */
