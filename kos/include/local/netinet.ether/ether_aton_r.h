/* HASH CRC-32:0x96e426bc */
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
#ifndef __local_ether_aton_r_defined
#define __local_ether_aton_r_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: ether_paton_r from netinet.ether */
#ifndef __local___localdep_ether_paton_r_defined
#define __local___localdep_ether_paton_r_defined 1
#ifdef __CRT_HAVE_ether_paton_r
/* Convert ASCII string S to 48 bit Ethernet address */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),struct ether_addr *,__NOTHROW_NCX,__localdep_ether_paton_r,(char const **__restrict __pasc, struct ether_addr *__restrict __addr),ether_paton_r,(__pasc,__addr))
#else /* __CRT_HAVE_ether_paton_r */
__NAMESPACE_LOCAL_END
#include <local/netinet.ether/ether_paton_r.h>
__NAMESPACE_LOCAL_BEGIN
/* Convert ASCII string S to 48 bit Ethernet address */
#define __localdep_ether_paton_r __LIBC_LOCAL_NAME(ether_paton_r)
#endif /* !__CRT_HAVE_ether_paton_r */
#endif /* !__local___localdep_ether_paton_r_defined */
__NAMESPACE_LOCAL_END
#include <net/ethernet.h>
__NAMESPACE_LOCAL_BEGIN
/* Convert ASCII string S to 48 bit Ethernet address */
__LOCAL_LIBC(ether_aton_r) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) struct ether_addr *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ether_aton_r))(char const *__restrict __asc, struct ether_addr *__restrict __addr) {
	return __localdep_ether_paton_r((char const **)&__asc, __addr);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ether_aton_r_defined
#define __local___localdep_ether_aton_r_defined 1
#define __localdep_ether_aton_r __LIBC_LOCAL_NAME(ether_aton_r)
#endif /* !__local___localdep_ether_aton_r_defined */
#endif /* !__local_ether_aton_r_defined */
