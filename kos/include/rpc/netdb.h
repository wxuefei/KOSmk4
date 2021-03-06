/* HASH CRC-32:0xe78bed89 */
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
#ifndef _RPC_NETDB_H
#define _RPC_NETDB_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <bits/types.h>
#include <bits/crt/db/rpcent.h>

__SYSDECL_BEGIN

/* Comments and definitions are derived from GNU C /usr/include/i386-linux-gnu/sys/times.h: */
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

__CDECLARE_VOID_OPT(,__NOTHROW_RPC_KOS,setrpcent,(int __stayopen),(__stayopen))
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,endrpcent,(void),())
__CDECLARE_OPT(,struct rpcent *,__NOTHROW_RPC_KOS,getrpcbyname,(char const *__name),(__name))
__CDECLARE_OPT(,struct rpcent *,__NOTHROW_RPC_KOS,getrpcbynumber,(int __number),(__number))
__CDECLARE_OPT(,struct rpcent *,__NOTHROW_RPC_KOS,getrpcent,(void),())

#ifdef __USE_MISC
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,getrpcbyname_r,(char const *__name, struct rpcent *__result_buf, char *__buffer, size_t __buflen, struct rpcent **__result),(__name,__result_buf,__buffer,__buflen,__result))
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,getrpcbynumber_r,(int __number, struct rpcent *__result_buf, char *__buffer, size_t __buflen, struct rpcent **__result),(__number,__result_buf,__buffer,__buflen,__result))
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,getrpcent_r,(struct rpcent *__result_buf, char *__buffer, size_t __buflen, struct rpcent **__result),(__result_buf,__buffer,__buflen,__result))
#endif /* __USE_MISC */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_RPC_NETDB_H */
