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
#ifndef GUARD_LIBC_USER_UTIME_C
#define GUARD_LIBC_USER_UTIME_C 1

#include "../api.h"
#include "utime.h"
#include <fcntl.h>
#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_utime,hash:CRC-32=0xd118af7a]]]*/
INTERN ATTR_SECTION(".text.crt.fs.modify_time") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_utime)(char const *filename,
                                 struct utimbuf const *file_times)
/*[[[body:libc_utime]]]*/
{
	errno_t error;
#ifdef __NR_utime
	error = sys_utime(filename, file_times);
#else /* __NR_utime */
	if (file_times) {
		struct timeval tv[2];
		tv[0].tv_sec  = file_times->actime;
		tv[0].tv_usec = 0;
		tv[1].tv_sec  = file_times->modtime;
		tv[1].tv_usec = 0;
		error = sys_futimesat(AT_FDCWD, filename, tv);
	} else {
		error = sys_futimesat(AT_FDCWD, filename, NULL);
	}
#endif /* !__NR_utime */
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_utime]]]*/

/*[[[head:libc_utime64,hash:CRC-32=0x346a4a39]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_utime64, libc_utime);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_utime64)(char const *filename,
                                   struct utimbuf64 const *file_times)
/*[[[body:libc_utime64]]]*/
{
	errno_t error;
#ifdef __NR_utime64
	error = sys_utime64(filename, file_times);
#else /* __NR_utime64 */
	if (file_times) {
		struct timeval64 tv[2];
		tv[0].tv_sec  = file_times->actime;
		tv[0].tv_usec = 0;
		tv[1].tv_sec  = file_times->modtime;
		tv[1].tv_usec = 0;
		error = sys_futimesat64(AT_FDCWD, filename, tv);
	} else {
		error = sys_futimesat64(AT_FDCWD, filename, NULL);
	}
#endif /* !__NR_utime64 */
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_utime64]]]*/

/*[[[head:libc_futime,hash:CRC-32=0xc0caffa1]]]*/
INTERN ATTR_SECTION(".text.crt.fs.modify_time") int
NOTHROW_RPC(LIBCCALL libc_futime)(fd_t fd,
                                  struct utimbuf const *file_times)
/*[[[body:libc_futime]]]*/
{
	errno_t error;
	if (file_times) {
		struct timeval tv[2];
		tv[0].tv_sec  = file_times->actime;
		tv[0].tv_usec = 0;
		tv[1].tv_sec  = file_times->modtime;
		tv[1].tv_usec = 0;
		error = sys_futimesat(fd, NULL, tv);
	} else {
		error = sys_futimesat(fd, NULL, NULL);
	}
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_futime]]]*/

/*[[[head:libc_futime64,hash:CRC-32=0xeeb79d64]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_futime64, libc_futime);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.fs.modify_time") int
NOTHROW_RPC(LIBCCALL libc_futime64)(fd_t fd,
                                    struct utimbuf64 const *file_times)
/*[[[body:libc_futime64]]]*/
{
	errno_t error;
	if (file_times) {
		struct timeval64 tv[2];
		tv[0].tv_sec  = file_times->actime;
		tv[0].tv_usec = 0;
		tv[1].tv_sec  = file_times->modtime;
		tv[1].tv_usec = 0;
		error = sys_futimesat64(fd, NULL, tv);
	} else {
		error = sys_futimesat64(fd, NULL, NULL);
	}
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_futime64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xbe3d13f6]]]*/
DEFINE_PUBLIC_ALIAS(_utime32, libc_utime);
DEFINE_PUBLIC_ALIAS(utime, libc_utime);
DEFINE_PUBLIC_ALIAS(_utime64, libc_utime64);
DEFINE_PUBLIC_ALIAS(utime64, libc_utime64);
DEFINE_PUBLIC_ALIAS(_futime32, libc_futime);
DEFINE_PUBLIC_ALIAS(futime, libc_futime);
DEFINE_PUBLIC_ALIAS(_futime64, libc_futime64);
DEFINE_PUBLIC_ALIAS(futime64, libc_futime64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_UTIME_C */
