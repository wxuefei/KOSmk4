/* HASH CRC-32:0x6fef17ed */
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
#ifndef GUARD_LIBC_AUTO_UNISTD_C
#define GUARD_LIBC_AUTO_UNISTD_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/unistd.h"
#include "../user/fcntl.h"

DECL_BEGIN

#ifndef __KERNEL__
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/crt/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.fs.property") NONNULL((1)) longptr_t
NOTHROW_RPC(LIBCCALL libc_pathconf)(char const *path,
                                    __STDC_INT_AS_UINT_T name) {
	fd_t fd;
	longptr_t result;
	fd = libc_open(path, O_RDONLY);
	if unlikely(fd < 0)
		return -1;
	result = libc_fpathconf(fd, name);
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)
	libc_close(fd);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close */
	return result;
}
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
INTERN ATTR_SECTION(".text.crt.system.configuration") ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_getpagesize)(void) {
	return __ARCH_PAGESIZE;
}
INTERN ATTR_SECTION(".text.crt.system.configuration") ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_getdtablesize)(void) {
#if defined(__KOS__)
	return 0x7fffffff; /* INT_MAX */
#elif defined(__linux__) || defined(__linux) || defined(linux)
	return 0x10000;    /* UINT16_MAX + 1 */
#else
	return 256;        /* UINT8_MAX + 1 */
#endif
}
/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
INTERN ATTR_SECTION(".text.crt.string.memory") NONNULL((1, 2)) void
NOTHROW_NCX(LIBCCALL libc_swab)(void const *__restrict from,
                                void *__restrict to,
                                __STDC_INT_AS_SSIZE_T n_bytes) {
	n_bytes &= ~1;
	while (n_bytes >= 2) {
		byte_t a, b;
		a = ((byte_t *)from)[--n_bytes];
		b = ((byte_t *)from)[--n_bytes];
		((byte_t *)to)[n_bytes+0] = a;
		((byte_t *)to)[n_bytes+1] = b;
	}
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(pathconf, libc_pathconf);
DEFINE_PUBLIC_ALIAS(__getpagesize, libc_getpagesize);
DEFINE_PUBLIC_ALIAS(getpagesize, libc_getpagesize);
DEFINE_PUBLIC_ALIAS(getdtablesize, libc_getdtablesize);
DEFINE_PUBLIC_ALIAS(_swab, libc_swab);
DEFINE_PUBLIC_ALIAS(swab, libc_swab);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_UNISTD_C */
