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
#ifndef GUARD_LIBC_USER_NETDB_C
#define GUARD_LIBC_USER_NETDB_C 1

#include "../api.h"
#include "netdb.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc___h_errno_location,hash:CRC-32=0x907dfeca]]]*/
/* Function to get address of global `h_errno' variable */
INTERN ATTR_SECTION(".text.crt.net.db") ATTR_CONST ATTR_RETNONNULL WUNUSED int *
NOTHROW_NCX(LIBCCALL libc___h_errno_location)(void)
/*[[[body:libc___h_errno_location]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("__h_errno_location"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___h_errno_location]]]*/

/*[[[head:libc_herror,hash:CRC-32=0xd9c53514]]]*/
/* Print error indicated by `h_errno' variable on standard error.
 * STR, if non-null, is printed before the error string */
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_RPC(LIBCCALL libc_herror)(char const *str)
/*[[[body:libc_herror]]]*/
/*AUTO*/{
	(void)str;
	CRT_UNIMPLEMENTEDF("herror(%q)", str); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_herror]]]*/

/*[[[head:libc_hstrerror,hash:CRC-32=0x94220c1c]]]*/
/* Return string associated with error ERR_NUM */
INTERN ATTR_SECTION(".text.crt.net.db") ATTR_CONST WUNUSED char const *
NOTHROW_NCX(LIBCCALL libc_hstrerror)(int err_num)
/*[[[body:libc_hstrerror]]]*/
/*AUTO*/{
	(void)err_num;
	CRT_UNIMPLEMENTEDF("hstrerror(%x)", err_num); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_hstrerror]]]*/

/*[[[head:libc_sethostent,hash:CRC-32=0x53cb2b19]]]*/
/* Open host data base files and mark them as staying
 * open even after a later search if STAY_OPEN is non-zero */
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_RPC(LIBCCALL libc_sethostent)(int stay_open)
/*[[[body:libc_sethostent]]]*/
/*AUTO*/{
	(void)stay_open;
	CRT_UNIMPLEMENTEDF("sethostent(%x)", stay_open); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_sethostent]]]*/

/*[[[head:libc_endhostent,hash:CRC-32=0x7a91955f]]]*/
/* Close host data base files and clear `stay open' flag */
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endhostent)(void)
/*[[[body:libc_endhostent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endhostent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endhostent]]]*/

/*[[[head:libc_gethostent,hash:CRC-32=0xc2def0f7]]]*/
/* Get next entry from host data base file. Open data base if necessary */
INTERN ATTR_SECTION(".text.crt.net.db") struct hostent *
NOTHROW_RPC(LIBCCALL libc_gethostent)(void)
/*[[[body:libc_gethostent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("gethostent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_gethostent]]]*/

/*[[[head:libc_gethostbyaddr,hash:CRC-32=0xef9205c0]]]*/
/* Return entry from host data base which address match ADDR with length LEN and type TYPE */
INTERN ATTR_SECTION(".text.crt.net.db") struct hostent *
NOTHROW_RPC(LIBCCALL libc_gethostbyaddr)(void const *addr,
                                         socklen_t len,
                                         int type)
/*[[[body:libc_gethostbyaddr]]]*/
/*AUTO*/{
	(void)addr;
	(void)len;
	(void)type;
	CRT_UNIMPLEMENTEDF("gethostbyaddr(%p, %" PRIxN(__SIZEOF_SOCKLEN_T__) ", %x)", addr, len, type); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_gethostbyaddr]]]*/

/*[[[head:libc_gethostbyname,hash:CRC-32=0x3e234d41]]]*/
/* Return entry from host data base for host with NAME */
INTERN ATTR_SECTION(".text.crt.net.db") struct hostent *
NOTHROW_RPC(LIBCCALL libc_gethostbyname)(char const *name)
/*[[[body:libc_gethostbyname]]]*/
/*AUTO*/{
	(void)name;
	CRT_UNIMPLEMENTEDF("gethostbyname(%q)", name); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_gethostbyname]]]*/

/*[[[head:libc_gethostbyname2,hash:CRC-32=0x123e03d8]]]*/
/* Return entry from host data base for host with NAME. AF must be
 * set to the address type which is `AF_INET' for IPv4 or `AF_INET6'
 * for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") struct hostent *
NOTHROW_RPC(LIBCCALL libc_gethostbyname2)(char const *name,
                                          int af)
/*[[[body:libc_gethostbyname2]]]*/
/*AUTO*/{
	(void)name;
	(void)af;
	CRT_UNIMPLEMENTEDF("gethostbyname2(%q, %x)", name, af); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_gethostbyname2]]]*/

/*[[[head:libc_gethostent_r,hash:CRC-32=0xeaed6a12]]]*/
/* Reentrant versions of the functions above. The additional arguments
 * specify a buffer of BUFLEN starting at BUF. The last argument is a
 * pointer to a variable which gets the value which would be stored in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_gethostent_r)(struct hostent *__restrict result_buf,
                                        char *__restrict buf,
                                        size_t buflen,
                                        struct hostent **__restrict result,
                                        int *__restrict h_errnop)
/*[[[body:libc_gethostent_r]]]*/
/*AUTO*/{
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	(void)h_errnop;
	CRT_UNIMPLEMENTEDF("gethostent_r(%p, %q, %Ix, %p, %p)", result_buf, buf, buflen, result, h_errnop); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_gethostent_r]]]*/

/*[[[head:libc_gethostbyaddr_r,hash:CRC-32=0xdb3f3bdc]]]*/
/* Reentrant versions of the functions above. The additional arguments
 * specify a buffer of BUFLEN starting at BUF. The last argument is a
 * pointer to a variable which gets the value which would be stored in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_gethostbyaddr_r)(void const *__restrict addr,
                                           socklen_t len,
                                           int type,
                                           struct hostent *__restrict result_buf,
                                           char *__restrict buf,
                                           size_t buflen,
                                           struct hostent **__restrict result,
                                           int *__restrict h_errnop)
/*[[[body:libc_gethostbyaddr_r]]]*/
/*AUTO*/{
	(void)addr;
	(void)len;
	(void)type;
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	(void)h_errnop;
	CRT_UNIMPLEMENTEDF("gethostbyaddr_r(%p, %" PRIxN(__SIZEOF_SOCKLEN_T__) ", %x, %p, %q, %Ix, %p, %p)", addr, len, type, result_buf, buf, buflen, result, h_errnop); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_gethostbyaddr_r]]]*/

/*[[[head:libc_gethostbyname_r,hash:CRC-32=0x9821a433]]]*/
/* Reentrant versions of the functions above. The additional arguments
 * specify a buffer of BUFLEN starting at BUF. The last argument is a
 * pointer to a variable which gets the value which would be stored in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_gethostbyname_r)(char const *__restrict name,
                                           struct hostent *__restrict result_buf,
                                           char *__restrict buf,
                                           size_t buflen,
                                           struct hostent **__restrict result,
                                           int *__restrict h_errnop)
/*[[[body:libc_gethostbyname_r]]]*/
/*AUTO*/{
	(void)name;
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	(void)h_errnop;
	CRT_UNIMPLEMENTEDF("gethostbyname_r(%q, %p, %q, %Ix, %p, %p)", name, result_buf, buf, buflen, result, h_errnop); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_gethostbyname_r]]]*/

/*[[[head:libc_gethostbyname2_r,hash:CRC-32=0x805661e1]]]*/
/* Reentrant versions of the functions above. The additional arguments
 * specify a buffer of BUFLEN starting at BUF. The last argument is a
 * pointer to a variable which gets the value which would be stored in
 * the global variable `herrno' by the non-reentrant functions.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_gethostbyname2_r)(char const *__restrict name,
                                            int af,
                                            struct hostent *__restrict result_buf,
                                            char *__restrict buf,
                                            size_t buflen,
                                            struct hostent **__restrict result,
                                            int *__restrict h_errnop)
/*[[[body:libc_gethostbyname2_r]]]*/
/*AUTO*/{
	(void)name;
	(void)af;
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	(void)h_errnop;
	CRT_UNIMPLEMENTEDF("gethostbyname2_r(%q, %x, %p, %q, %Ix, %p, %p)", name, af, result_buf, buf, buflen, result, h_errnop); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_gethostbyname2_r]]]*/

/*[[[head:libc_setnetent,hash:CRC-32=0x3b38d087]]]*/
/* Open network data base files and mark them as staying
 * open even after a later search if STAY_OPEN is non-zero */
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_RPC(LIBCCALL libc_setnetent)(int stay_open)
/*[[[body:libc_setnetent]]]*/
/*AUTO*/{
	(void)stay_open;
	CRT_UNIMPLEMENTEDF("setnetent(%x)", stay_open); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_setnetent]]]*/

/*[[[head:libc_endnetent,hash:CRC-32=0xa7bef8a8]]]*/
/* Close network data base files and clear `stay open' flag */
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endnetent)(void)
/*[[[body:libc_endnetent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endnetent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endnetent]]]*/

/*[[[head:libc_getnetent,hash:CRC-32=0x66c5cdc2]]]*/
/* Get next entry from network data base file. Open data base if necessary */
INTERN ATTR_SECTION(".text.crt.net.db") struct netent *
NOTHROW_RPC(LIBCCALL libc_getnetent)(void)
/*[[[body:libc_getnetent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getnetent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getnetent]]]*/

/*[[[head:libc_getnetbyaddr,hash:CRC-32=0x3a26dd93]]]*/
/* Return entry from network data base which address match NET and type TYPE */
INTERN ATTR_SECTION(".text.crt.net.db") struct netent *
NOTHROW_RPC(LIBCCALL libc_getnetbyaddr)(uint32_t net,
                                        int type)
/*[[[body:libc_getnetbyaddr]]]*/
/*AUTO*/{
	(void)net;
	(void)type;
	CRT_UNIMPLEMENTEDF("getnetbyaddr(%" PRIx32 ", %x)", net, type); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getnetbyaddr]]]*/

/*[[[head:libc_getnetbyname,hash:CRC-32=0x784a3c4]]]*/
/* Return entry from network data base for network with NAME */
INTERN ATTR_SECTION(".text.crt.net.db") struct netent *
NOTHROW_RPC(LIBCCALL libc_getnetbyname)(char const *name)
/*[[[body:libc_getnetbyname]]]*/
/*AUTO*/{
	(void)name;
	CRT_UNIMPLEMENTEDF("getnetbyname(%q)", name); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getnetbyname]]]*/

/*[[[head:libc_getnetent_r,hash:CRC-32=0xfaa8d7bf]]]*/
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF. The last
 * argument is a pointer to a variable which gets the value which
 * would be stored in the global variable `herrno' by the
 * non-reentrant functions.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getnetent_r)(struct netent *__restrict result_buf,
                                       char *__restrict buf,
                                       size_t buflen,
                                       struct netent **__restrict result,
                                       int *__restrict h_errnop)
/*[[[body:libc_getnetent_r]]]*/
/*AUTO*/{
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	(void)h_errnop;
	CRT_UNIMPLEMENTEDF("getnetent_r(%p, %q, %Ix, %p, %p)", result_buf, buf, buflen, result, h_errnop); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getnetent_r]]]*/

/*[[[head:libc_getnetbyaddr_r,hash:CRC-32=0x5e9e8359]]]*/
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF. The last
 * argument is a pointer to a variable which gets the value which
 * would be stored in the global variable `herrno' by the
 * non-reentrant functions.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getnetbyaddr_r)(uint32_t net,
                                          int type,
                                          struct netent *__restrict result_buf,
                                          char *__restrict buf,
                                          size_t buflen,
                                          struct netent **__restrict result,
                                          int *__restrict h_errnop)
/*[[[body:libc_getnetbyaddr_r]]]*/
/*AUTO*/{
	(void)net;
	(void)type;
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	(void)h_errnop;
	CRT_UNIMPLEMENTEDF("getnetbyaddr_r(%" PRIx32 ", %x, %p, %q, %Ix, %p, %p)", net, type, result_buf, buf, buflen, result, h_errnop); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getnetbyaddr_r]]]*/

/*[[[head:libc_getnetbyname_r,hash:CRC-32=0xbf5aa7c0]]]*/
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF. The last
 * argument is a pointer to a variable which gets the value which
 * would be stored in the global variable `herrno' by the
 * non-reentrant functions.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getnetbyname_r)(char const *__restrict name,
                                          struct netent *__restrict result_buf,
                                          char *__restrict buf,
                                          size_t buflen,
                                          struct netent **__restrict result,
                                          int *__restrict h_errnop)
/*[[[body:libc_getnetbyname_r]]]*/
/*AUTO*/{
	(void)name;
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	(void)h_errnop;
	CRT_UNIMPLEMENTEDF("getnetbyname_r(%q, %p, %q, %Ix, %p, %p)", name, result_buf, buf, buflen, result, h_errnop); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getnetbyname_r]]]*/

/*[[[head:libc_setservent,hash:CRC-32=0x16f041eb]]]*/
/* Open service data base files and mark them as staying open even
 * after a later search if STAY_OPEN is non-zero */
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_RPC(LIBCCALL libc_setservent)(int stay_open)
/*[[[body:libc_setservent]]]*/
/*AUTO*/{
	(void)stay_open;
	CRT_UNIMPLEMENTEDF("setservent(%x)", stay_open); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_setservent]]]*/

/*[[[head:libc_endservent,hash:CRC-32=0x9d96b3ef]]]*/
/* Close service data base files and clear `stay open' flag */
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endservent)(void)
/*[[[body:libc_endservent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endservent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endservent]]]*/

/*[[[head:libc_getservent,hash:CRC-32=0x878000a0]]]*/
/* Get next entry from service data base file. Open data base if necessary */
INTERN ATTR_SECTION(".text.crt.net.db") struct servent *
NOTHROW_RPC(LIBCCALL libc_getservent)(void)
/*[[[body:libc_getservent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getservent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getservent]]]*/

/*[[[head:libc_getservbyname,hash:CRC-32=0x1adf8735]]]*/
/* Return entry from network data base for network with NAME and protocol PROTO */
INTERN ATTR_SECTION(".text.crt.net.db") struct servent *
NOTHROW_RPC(LIBCCALL libc_getservbyname)(char const *name,
                                         char const *proto)
/*[[[body:libc_getservbyname]]]*/
/*AUTO*/{
	(void)name;
	(void)proto;
	CRT_UNIMPLEMENTEDF("getservbyname(%q, %q)", name, proto); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getservbyname]]]*/

/*[[[head:libc_getservbyport,hash:CRC-32=0xbe3fdccb]]]*/
/* Return entry from service data base which matches port PORT and protocol PROTO */
INTERN ATTR_SECTION(".text.crt.net.db") struct servent *
NOTHROW_RPC(LIBCCALL libc_getservbyport)(int port,
                                         char const *proto)
/*[[[body:libc_getservbyport]]]*/
/*AUTO*/{
	(void)port;
	(void)proto;
	CRT_UNIMPLEMENTEDF("getservbyport(%x, %q)", port, proto); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getservbyport]]]*/

/*[[[head:libc_getservent_r,hash:CRC-32=0x8345736c]]]*/
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getservent_r)(struct servent *__restrict result_buf,
                                        char *__restrict buf,
                                        size_t buflen,
                                        struct servent **__restrict result)
/*[[[body:libc_getservent_r]]]*/
/*AUTO*/{
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getservent_r(%p, %q, %Ix, %p)", result_buf, buf, buflen, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getservent_r]]]*/

/*[[[head:libc_getservbyname_r,hash:CRC-32=0x7b6f10a5]]]*/
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getservbyname_r)(char const *__restrict name,
                                           char const *__restrict proto,
                                           struct servent *__restrict result_buf,
                                           char *__restrict buf,
                                           size_t buflen,
                                           struct servent **__restrict result)
/*[[[body:libc_getservbyname_r]]]*/
/*AUTO*/{
	(void)name;
	(void)proto;
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getservbyname_r(%q, %q, %p, %q, %Ix, %p)", name, proto, result_buf, buf, buflen, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getservbyname_r]]]*/

/*[[[head:libc_getservbyport_r,hash:CRC-32=0x2d25ca8e]]]*/
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getservbyport_r)(int port,
                                           char const *__restrict proto,
                                           struct servent *__restrict result_buf,
                                           char *__restrict buf,
                                           size_t buflen,
                                           struct servent **__restrict result)
/*[[[body:libc_getservbyport_r]]]*/
/*AUTO*/{
	(void)port;
	(void)proto;
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getservbyport_r(%x, %q, %p, %q, %Ix, %p)", port, proto, result_buf, buf, buflen, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getservbyport_r]]]*/

/*[[[head:libc_setprotoent,hash:CRC-32=0x13f87d91]]]*/
/* Open protocol data base files and mark them as staying open even
 * after a later search if STAY_OPEN is non-zero */
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_RPC(LIBCCALL libc_setprotoent)(int stay_open)
/*[[[body:libc_setprotoent]]]*/
/*AUTO*/{
	(void)stay_open;
	CRT_UNIMPLEMENTEDF("setprotoent(%x)", stay_open); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_setprotoent]]]*/

/*[[[head:libc_endprotoent,hash:CRC-32=0x4b42dd2f]]]*/
/* Close protocol data base files and clear `stay open' flag */
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endprotoent)(void)
/*[[[body:libc_endprotoent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endprotoent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endprotoent]]]*/

/*[[[head:libc_getprotoent,hash:CRC-32=0x3046364a]]]*/
/* Get next entry from protocol data base file. Open data base if necessary */
INTERN ATTR_SECTION(".text.crt.net.db") struct protoent *
NOTHROW_RPC(LIBCCALL libc_getprotoent)(void)
/*[[[body:libc_getprotoent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getprotoent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getprotoent]]]*/

/*[[[head:libc_getprotobyname,hash:CRC-32=0x479aeaf8]]]*/
/* Return entry from protocol data base for network with NAME */
INTERN ATTR_SECTION(".text.crt.net.db") struct protoent *
NOTHROW_RPC(LIBCCALL libc_getprotobyname)(char const *name)
/*[[[body:libc_getprotobyname]]]*/
/*AUTO*/{
	(void)name;
	CRT_UNIMPLEMENTEDF("getprotobyname(%q)", name); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getprotobyname]]]*/

/*[[[head:libc_getprotobynumber,hash:CRC-32=0x8263808a]]]*/
/* Return entry from protocol data base which number is PROTO */
INTERN ATTR_SECTION(".text.crt.net.db") struct protoent *
NOTHROW_RPC(LIBCCALL libc_getprotobynumber)(int proto)
/*[[[body:libc_getprotobynumber]]]*/
/*AUTO*/{
	(void)proto;
	CRT_UNIMPLEMENTEDF("getprotobynumber(%x)", proto); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getprotobynumber]]]*/

/*[[[head:libc_getprotoent_r,hash:CRC-32=0xe63372ee]]]*/
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getprotoent_r)(struct protoent *__restrict result_buf,
                                         char *__restrict buf,
                                         size_t buflen,
                                         struct protoent **__restrict result)
/*[[[body:libc_getprotoent_r]]]*/
/*AUTO*/{
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getprotoent_r(%p, %q, %Ix, %p)", result_buf, buf, buflen, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getprotoent_r]]]*/

/*[[[head:libc_getprotobyname_r,hash:CRC-32=0x8e3136cb]]]*/
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getprotobyname_r)(char const *__restrict name,
                                            struct protoent *__restrict result_buf,
                                            char *__restrict buf,
                                            size_t buflen,
                                            struct protoent **__restrict result)
/*[[[body:libc_getprotobyname_r]]]*/
/*AUTO*/{
	(void)name;
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getprotobyname_r(%q, %p, %q, %Ix, %p)", name, result_buf, buf, buflen, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getprotobyname_r]]]*/

/*[[[head:libc_getprotobynumber_r,hash:CRC-32=0x17f80fa9]]]*/
/* Reentrant versions of the functions above. The additional
 * arguments specify a buffer of BUFLEN starting at BUF.
 * These functions are not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getprotobynumber_r)(int proto,
                                              struct protoent *__restrict result_buf,
                                              char *__restrict buf,
                                              size_t buflen,
                                              struct protoent **__restrict result)
/*[[[body:libc_getprotobynumber_r]]]*/
/*AUTO*/{
	(void)proto;
	(void)result_buf;
	(void)buf;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getprotobynumber_r(%x, %p, %q, %Ix, %p)", proto, result_buf, buf, buflen, result); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getprotobynumber_r]]]*/

/*[[[head:libc_setnetgrent,hash:CRC-32=0x85bd8a47]]]*/
/* Establish network group NETGROUP for enumeration.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_setnetgrent)(char const *netgroup)
/*[[[body:libc_setnetgrent]]]*/
/*AUTO*/{
	(void)netgroup;
	CRT_UNIMPLEMENTEDF("setnetgrent(%q)", netgroup); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_setnetgrent]]]*/

/*[[[head:libc_endnetgrent,hash:CRC-32=0xbc5f4e60]]]*/
/* Free all space allocated by previous `setnetgrent' call.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endnetgrent)(void)
/*[[[body:libc_endnetgrent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endnetgrent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endnetgrent]]]*/

/*[[[head:libc_getnetgrent,hash:CRC-32=0x2b3e69eb]]]*/
/* Get next member of netgroup established by last `setnetgrent' call
 * and return pointers to elements in HOSTP, USERP, and DOMAINP.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getnetgrent)(char **__restrict hostp,
                                       char **__restrict userp,
                                       char **__restrict domainp)
/*[[[body:libc_getnetgrent]]]*/
/*AUTO*/{
	(void)hostp;
	(void)userp;
	(void)domainp;
	CRT_UNIMPLEMENTEDF("getnetgrent(%p, %p, %p)", hostp, userp, domainp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getnetgrent]]]*/

/*[[[head:libc_innetgr,hash:CRC-32=0x7f534e6d]]]*/
/* Test whether NETGROUP contains the triple (HOST, USER, DOMAIN).
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_innetgr)(char const *netgroup,
                                   char const *host,
                                   char const *user,
                                   char const *domain)
/*[[[body:libc_innetgr]]]*/
/*AUTO*/{
	(void)netgroup;
	(void)host;
	(void)user;
	(void)domain;
	CRT_UNIMPLEMENTEDF("innetgr(%q, %q, %q, %q)", netgroup, host, user, domain); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_innetgr]]]*/

/*[[[head:libc_getnetgrent_r,hash:CRC-32=0x6e7f9877]]]*/
/* Reentrant version of `getnetgrent' where result is placed in BUFFER.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getnetgrent_r)(char **__restrict hostp,
                                         char **__restrict userp,
                                         char **__restrict domainp,
                                         char *__restrict buf,
                                         size_t buflen)
/*[[[body:libc_getnetgrent_r]]]*/
/*AUTO*/{
	(void)hostp;
	(void)userp;
	(void)domainp;
	(void)buf;
	(void)buflen;
	CRT_UNIMPLEMENTEDF("getnetgrent_r(%p, %p, %p, %q, %Ix)", hostp, userp, domainp, buf, buflen); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getnetgrent_r]]]*/

/*[[[head:libc_rcmd,hash:CRC-32=0xd380dce0]]]*/
/* Call `rshd' at port RPORT on remote machine *AHOST to execute CMD.
 * The local user is LOCUSER, on the remote machine the command is
 * executed as REMUSER. In *FD2P the descriptor to the socket for the
 * connection is returned. The caller must have the right to use a
 * reserved port. When the function returns *AHOST contains the
 * official host name.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_rcmd)(char **__restrict ahost,
                                uint16_t rport,
                                char const *__restrict locuser,
                                char const *__restrict remuser,
                                char const *__restrict cmd,
                                int *__restrict fd2p)
/*[[[body:libc_rcmd]]]*/
/*AUTO*/{
	(void)ahost;
	(void)rport;
	(void)locuser;
	(void)remuser;
	(void)cmd;
	(void)fd2p;
	CRT_UNIMPLEMENTEDF("rcmd(%p, %" PRIx16 ", %q, %q, %q, %p)", ahost, rport, locuser, remuser, cmd, fd2p); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_rcmd]]]*/

/*[[[head:libc_rcmd_af,hash:CRC-32=0x1a90e0c3]]]*/
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_rcmd_af)(char **__restrict ahost,
                                   uint16_t rport,
                                   char const *__restrict locuser,
                                   char const *__restrict remuser,
                                   char const *__restrict cmd,
                                   int *__restrict fd2p,
                                   sa_family_t af)
/*[[[body:libc_rcmd_af]]]*/
/*AUTO*/{
	(void)ahost;
	(void)rport;
	(void)locuser;
	(void)remuser;
	(void)cmd;
	(void)fd2p;
	(void)af;
	CRT_UNIMPLEMENTEDF("rcmd_af(%p, %" PRIx16 ", %q, %q, %q, %p, %" PRIx16 ")", ahost, rport, locuser, remuser, cmd, fd2p, af); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_rcmd_af]]]*/

/*[[[head:libc_rexec,hash:CRC-32=0xa74cc23]]]*/
/* Call `rexecd' at port RPORT on remote machine *AHOST to execute
 * CMD. The process runs at the remote machine using the ID of user
 * NAME whose cleartext password is PASSWD. In *FD2P the descriptor
 * to the socket for the connection is returned. When the function
 * returns *AHOST contains the official host name.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_rexec)(char **__restrict ahost,
                                 int rport,
                                 char const *__restrict name,
                                 char const *__restrict pass,
                                 char const *__restrict cmd,
                                 int *__restrict fd2p)
/*[[[body:libc_rexec]]]*/
/*AUTO*/{
	(void)ahost;
	(void)rport;
	(void)name;
	(void)pass;
	(void)cmd;
	(void)fd2p;
	CRT_UNIMPLEMENTEDF("rexec(%p, %x, %q, %q, %q, %p)", ahost, rport, name, pass, cmd, fd2p); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_rexec]]]*/

/*[[[head:libc_rexec_af,hash:CRC-32=0xbc991207]]]*/
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_rexec_af)(char **__restrict ahost,
                                    int rport,
                                    char const *__restrict name,
                                    char const *__restrict pass,
                                    char const *__restrict cmd,
                                    int *__restrict fd2p,
                                    sa_family_t af)
/*[[[body:libc_rexec_af]]]*/
/*AUTO*/{
	(void)ahost;
	(void)rport;
	(void)name;
	(void)pass;
	(void)cmd;
	(void)fd2p;
	(void)af;
	CRT_UNIMPLEMENTEDF("rexec_af(%p, %x, %q, %q, %q, %p, %" PRIx16 ")", ahost, rport, name, pass, cmd, fd2p, af); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_rexec_af]]]*/

/*[[[head:libc_ruserok,hash:CRC-32=0x6ebc6ba8]]]*/
/* Check whether user REMUSER on system RHOST is allowed to login as LOCUSER.
 * If SUSER is not zero the user tries to become superuser. Return 0 if
 * it is possible.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_ruserok)(char const *rhost,
                                   int suser,
                                   char const *remuser,
                                   char const *locuser)
/*[[[body:libc_ruserok]]]*/
/*AUTO*/{
	(void)rhost;
	(void)suser;
	(void)remuser;
	(void)locuser;
	CRT_UNIMPLEMENTEDF("ruserok(%q, %x, %q, %q)", rhost, suser, remuser, locuser); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ruserok]]]*/

/*[[[head:libc_ruserok_af,hash:CRC-32=0xb4d26d2]]]*/
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_ruserok_af)(char const *rhost,
                                      int suser,
                                      char const *remuser,
                                      char const *locuser,
                                      sa_family_t af)
/*[[[body:libc_ruserok_af]]]*/
/*AUTO*/{
	(void)rhost;
	(void)suser;
	(void)remuser;
	(void)locuser;
	(void)af;
	CRT_UNIMPLEMENTEDF("ruserok_af(%q, %x, %q, %q, %" PRIx16 ")", rhost, suser, remuser, locuser, af); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ruserok_af]]]*/

/*[[[head:libc_iruserok,hash:CRC-32=0x6979ee8d]]]*/
/* Check whether user REMUSER on system indicated by IPv4 address
 * RADDR is allowed to login as LOCUSER. Non-IPv4 (e.g., IPv6) are
 * not supported. If SUSER is not zero the user tries to become
 * superuser. Return 0 if it is possible.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_iruserok)(uint32_t raddr,
                                    int suser,
                                    char const *remuser,
                                    char const *locuser)
/*[[[body:libc_iruserok]]]*/
/*AUTO*/{
	(void)raddr;
	(void)suser;
	(void)remuser;
	(void)locuser;
	CRT_UNIMPLEMENTEDF("iruserok(%" PRIx32 ", %x, %q, %q)", raddr, suser, remuser, locuser); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_iruserok]]]*/

/*[[[head:libc_iruserok_af,hash:CRC-32=0xf07f4c7d]]]*/
/* This is the equivalent function where the pfamiliy if the address
 * pointed to by RADDR is determined by the value of AF. It therefore
 * can be used for IPv6
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_iruserok_af)(void const *raddr,
                                       int suser,
                                       char const *remuser,
                                       char const *locuser,
                                       sa_family_t af)
/*[[[body:libc_iruserok_af]]]*/
/*AUTO*/{
	(void)raddr;
	(void)suser;
	(void)remuser;
	(void)locuser;
	(void)af;
	CRT_UNIMPLEMENTEDF("iruserok_af(%p, %x, %q, %q, %" PRIx16 ")", raddr, suser, remuser, locuser, af); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_iruserok_af]]]*/

/*[[[head:libc_rresvport,hash:CRC-32=0x527c813e]]]*/
/* Try to allocate reserved port, returning a descriptor for a socket opened
 * at this port or -1 if unsuccessful. The search for an available port
 * will start at ALPORT and continues with lower numbers.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_rresvport)(int *alport)
/*[[[body:libc_rresvport]]]*/
/*AUTO*/{
	(void)alport;
	CRT_UNIMPLEMENTEDF("rresvport(%p)", alport); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_rresvport]]]*/

/*[[[head:libc_rresvport_af,hash:CRC-32=0x4f55d766]]]*/
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_rresvport_af)(int *alport,
                                        sa_family_t af)
/*[[[body:libc_rresvport_af]]]*/
/*AUTO*/{
	(void)alport;
	(void)af;
	CRT_UNIMPLEMENTEDF("rresvport_af(%p, %" PRIx16 ")", alport, af); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_rresvport_af]]]*/

/*[[[head:libc_getaddrinfo,hash:CRC-32=0xdb36816d]]]*/
/* Translate name of a service location and/or a service name to set of socket addresses */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getaddrinfo)(char const *__restrict name,
                                       char const *__restrict service,
                                       struct addrinfo const *__restrict req,
                                       struct addrinfo **__restrict pai)
/*[[[body:libc_getaddrinfo]]]*/
/*AUTO*/{
	(void)name;
	(void)service;
	(void)req;
	(void)pai;
	CRT_UNIMPLEMENTEDF("getaddrinfo(%q, %q, %p, %p)", name, service, req, pai); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getaddrinfo]]]*/

/*[[[head:libc_freeaddrinfo,hash:CRC-32=0xf4375eff]]]*/
/* Free `addrinfo' structure AI including associated storage */
INTERN ATTR_SECTION(".text.crt.net.db") void
NOTHROW_NCX(LIBCCALL libc_freeaddrinfo)(struct addrinfo *ai)
/*[[[body:libc_freeaddrinfo]]]*/
/*AUTO*/{
	(void)ai;
	CRT_UNIMPLEMENTEDF("freeaddrinfo(%p)", ai); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_freeaddrinfo]]]*/

/*[[[head:libc_gai_strerror,hash:CRC-32=0x83e84d8f]]]*/
/* Convert error return from getaddrinfo() to a string */
INTERN ATTR_SECTION(".text.crt.net.db") ATTR_CONST WUNUSED char const *
NOTHROW_NCX(LIBCCALL libc_gai_strerror)(int ecode)
/*[[[body:libc_gai_strerror]]]*/
/*AUTO*/{
	(void)ecode;
	CRT_UNIMPLEMENTEDF("gai_strerror(%x)", ecode); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_gai_strerror]]]*/

/*[[[head:libc_getnameinfo,hash:CRC-32=0x68769ce0]]]*/
/* Translate a socket address to a location and service name */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getnameinfo)(struct sockaddr const *__restrict sa,
                                       socklen_t salen,
                                       char *__restrict host,
                                       socklen_t hostlen,
                                       char *__restrict serv,
                                       socklen_t servlen,
                                       int flags)
/*[[[body:libc_getnameinfo]]]*/
/*AUTO*/{
	(void)sa;
	(void)salen;
	(void)host;
	(void)hostlen;
	(void)serv;
	(void)servlen;
	(void)flags;
	CRT_UNIMPLEMENTEDF("getnameinfo(%p, %" PRIxN(__SIZEOF_SOCKLEN_T__) ", %q, %" PRIxN(__SIZEOF_SOCKLEN_T__) ", %q, %" PRIxN(__SIZEOF_SOCKLEN_T__) ", %x)", sa, salen, host, hostlen, serv, servlen, flags); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getnameinfo]]]*/

/*[[[head:libc_getaddrinfo_a,hash:CRC-32=0x913ca060]]]*/
/* Enqueue ENT requests from the LIST. If MODE is GAI_WAIT wait until all
 * requests are handled. If WAIT is GAI_NOWAIT return immediately after
 * queueing the requests and signal completion according to SIG.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_getaddrinfo_a)(int mode,
                                         struct gaicb *list[__restrict_arr],
                                         int ent,
                                         struct sigevent *__restrict sig)
/*[[[body:libc_getaddrinfo_a]]]*/
/*AUTO*/{
	(void)mode;
	(void)list;
	(void)ent;
	(void)sig;
	CRT_UNIMPLEMENTEDF("getaddrinfo_a(%x, %p, %x, %p)", mode, list, ent, sig); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getaddrinfo_a]]]*/

/*[[[head:libc_gai_suspend,hash:CRC-32=0xa8a25448]]]*/
/* Suspend execution of the thread until at least one of the ENT requests
 * in LIST is handled. If TIMEOUT is not a null pointer it specifies the
 * longest time the function keeps waiting before returning with an error.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_gai_suspend)(struct gaicb const *const list[],
                                       int ent,
                                       struct timespec const *timeout)
/*[[[body:libc_gai_suspend]]]*/
{
	(void)list;
	(void)ent;
	(void)timeout;
	CRT_UNIMPLEMENTED("gai_suspend"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:libc_gai_suspend]]]*/

/*[[[head:libc_gai_error,hash:CRC-32=0x9fb6f0c4]]]*/
/* Get the error status of the request REQ */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_NCX(LIBCCALL libc_gai_error)(struct gaicb *req)
/*[[[body:libc_gai_error]]]*/
/*AUTO*/{
	(void)req;
	CRT_UNIMPLEMENTEDF("gai_error(%p)", req); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_gai_error]]]*/

/*[[[head:libc_gai_cancel,hash:CRC-32=0x2e6f2ae5]]]*/
/* Cancel the requests associated with GAICBP */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_NCX(LIBCCALL libc_gai_cancel)(struct gaicb *gaicbp)
/*[[[body:libc_gai_cancel]]]*/
/*AUTO*/{
	(void)gaicbp;
	CRT_UNIMPLEMENTEDF("gai_cancel(%p)", gaicbp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_gai_cancel]]]*/

/*[[[head:libc_gai_suspend64,hash:CRC-32=0xb2d0ef4d]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_gai_suspend64, libc_gai_suspend);
#else /* MAGIC:alias */
/* Suspend execution of the thread until at least one of the ENT requests
 * in LIST is handled. If TIMEOUT is not a null pointer it specifies the
 * longest time the function keeps waiting before returning with an error.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
INTERN ATTR_SECTION(".text.crt.net.db") int
NOTHROW_RPC(LIBCCALL libc_gai_suspend64)(struct gaicb const *const list[],
                                         int ent,
                                         struct timespec64 const *timeout)
/*[[[body:libc_gai_suspend64]]]*/
{
	(void)list;
	(void)ent;
	(void)timeout;
	CRT_UNIMPLEMENTED("gai_suspend64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:libc_gai_suspend64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x3ad723b5]]]*/
DEFINE_PUBLIC_ALIAS(__h_errno_location, libc___h_errno_location);
DEFINE_PUBLIC_ALIAS(herror, libc_herror);
DEFINE_PUBLIC_ALIAS(hstrerror, libc_hstrerror);
DEFINE_PUBLIC_ALIAS(sethostent, libc_sethostent);
DEFINE_PUBLIC_ALIAS(endhostent, libc_endhostent);
DEFINE_PUBLIC_ALIAS(gethostent, libc_gethostent);
DEFINE_PUBLIC_ALIAS(gethostbyaddr, libc_gethostbyaddr);
DEFINE_PUBLIC_ALIAS(gethostbyname, libc_gethostbyname);
DEFINE_PUBLIC_ALIAS(gethostbyname2, libc_gethostbyname2);
DEFINE_PUBLIC_ALIAS(gethostent_r, libc_gethostent_r);
DEFINE_PUBLIC_ALIAS(gethostbyaddr_r, libc_gethostbyaddr_r);
DEFINE_PUBLIC_ALIAS(gethostbyname_r, libc_gethostbyname_r);
DEFINE_PUBLIC_ALIAS(gethostbyname2_r, libc_gethostbyname2_r);
DEFINE_PUBLIC_ALIAS(setnetent, libc_setnetent);
DEFINE_PUBLIC_ALIAS(endnetent, libc_endnetent);
DEFINE_PUBLIC_ALIAS(getnetent, libc_getnetent);
DEFINE_PUBLIC_ALIAS(getnetbyaddr, libc_getnetbyaddr);
DEFINE_PUBLIC_ALIAS(getnetbyname, libc_getnetbyname);
DEFINE_PUBLIC_ALIAS(getnetent_r, libc_getnetent_r);
DEFINE_PUBLIC_ALIAS(getnetbyaddr_r, libc_getnetbyaddr_r);
DEFINE_PUBLIC_ALIAS(getnetbyname_r, libc_getnetbyname_r);
DEFINE_PUBLIC_ALIAS(setservent, libc_setservent);
DEFINE_PUBLIC_ALIAS(endservent, libc_endservent);
DEFINE_PUBLIC_ALIAS(getservent, libc_getservent);
DEFINE_PUBLIC_ALIAS(getservbyname, libc_getservbyname);
DEFINE_PUBLIC_ALIAS(getservbyport, libc_getservbyport);
DEFINE_PUBLIC_ALIAS(getservent_r, libc_getservent_r);
DEFINE_PUBLIC_ALIAS(getservbyname_r, libc_getservbyname_r);
DEFINE_PUBLIC_ALIAS(getservbyport_r, libc_getservbyport_r);
DEFINE_PUBLIC_ALIAS(setprotoent, libc_setprotoent);
DEFINE_PUBLIC_ALIAS(endprotoent, libc_endprotoent);
DEFINE_PUBLIC_ALIAS(getprotoent, libc_getprotoent);
DEFINE_PUBLIC_ALIAS(getprotobyname, libc_getprotobyname);
DEFINE_PUBLIC_ALIAS(getprotobynumber, libc_getprotobynumber);
DEFINE_PUBLIC_ALIAS(getprotoent_r, libc_getprotoent_r);
DEFINE_PUBLIC_ALIAS(getprotobyname_r, libc_getprotobyname_r);
DEFINE_PUBLIC_ALIAS(getprotobynumber_r, libc_getprotobynumber_r);
DEFINE_PUBLIC_ALIAS(setnetgrent, libc_setnetgrent);
DEFINE_PUBLIC_ALIAS(endnetgrent, libc_endnetgrent);
DEFINE_PUBLIC_ALIAS(getnetgrent, libc_getnetgrent);
DEFINE_PUBLIC_ALIAS(innetgr, libc_innetgr);
DEFINE_PUBLIC_ALIAS(getnetgrent_r, libc_getnetgrent_r);
DEFINE_PUBLIC_ALIAS(rcmd, libc_rcmd);
DEFINE_PUBLIC_ALIAS(rcmd_af, libc_rcmd_af);
DEFINE_PUBLIC_ALIAS(rexec, libc_rexec);
DEFINE_PUBLIC_ALIAS(rexec_af, libc_rexec_af);
DEFINE_PUBLIC_ALIAS(ruserok, libc_ruserok);
DEFINE_PUBLIC_ALIAS(ruserok_af, libc_ruserok_af);
DEFINE_PUBLIC_ALIAS(iruserok, libc_iruserok);
DEFINE_PUBLIC_ALIAS(iruserok_af, libc_iruserok_af);
DEFINE_PUBLIC_ALIAS(rresvport, libc_rresvport);
DEFINE_PUBLIC_ALIAS(rresvport_af, libc_rresvport_af);
DEFINE_PUBLIC_ALIAS(getaddrinfo, libc_getaddrinfo);
DEFINE_PUBLIC_ALIAS(freeaddrinfo, libc_freeaddrinfo);
DEFINE_PUBLIC_ALIAS(gai_strerror, libc_gai_strerror);
DEFINE_PUBLIC_ALIAS(getnameinfo, libc_getnameinfo);
DEFINE_PUBLIC_ALIAS(getaddrinfo_a, libc_getaddrinfo_a);
DEFINE_PUBLIC_ALIAS(gai_suspend, libc_gai_suspend);
DEFINE_PUBLIC_ALIAS(gai_suspend64, libc_gai_suspend64);
DEFINE_PUBLIC_ALIAS(gai_error, libc_gai_error);
DEFINE_PUBLIC_ALIAS(gai_cancel, libc_gai_cancel);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_NETDB_C */
