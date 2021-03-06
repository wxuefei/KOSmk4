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
#ifndef GUARD_LIBC_USER_SYS_RESOURCE_C
#define GUARD_LIBC_USER_SYS_RESOURCE_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include "sys.resource.h"

DECL_BEGIN


/*[[[head:libc_prlimit,hash:CRC-32=0xcc2a3cc6]]]*/
INTERN ATTR_SECTION(".text.crt.sched.resource") int
NOTHROW_NCX(LIBCCALL libc_prlimit)(pid_t pid,
                                   __rlimit_resource_t resource,
                                   struct rlimit const *new_limit,
                                   struct rlimit *old_limit)
/*[[[body:libc_prlimit]]]*/
{
	errno_t error;
#if __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__
	error = sys_prlimit64(pid, (syscall_ulong_t)resource,
	                      (struct rlimit64 const *)new_limit,
	                      (struct rlimit64 *)old_limit);
#else /* __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__ */
	struct rlimit64 nl, ol;
	if (new_limit) {
		nl.rlim_cur = (rlim64_t)new_limit->rlim_cur;
		nl.rlim_max = (rlim64_t)new_limit->rlim_max;
	}
	error = sys_prlimit64(pid, (syscall_ulong_t)resource,
	                      new_limit ? &nl : NULL,
	                      old_limit ? &ol : NULL);
	if (old_limit && E_ISOK(error)) {
		old_limit->rlim_cur = (rlim_t)ol.rlim_cur;
		old_limit->rlim_max = (rlim_t)ol.rlim_max;
	}
#endif /* __SIZEOF_RLIM32_T__ != __SIZEOF_RLIM64_T__ */
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_prlimit]]]*/

/*[[[head:libc_prlimit64,hash:CRC-32=0x61d945b2]]]*/
#if __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__
DEFINE_INTERN_ALIAS(libc_prlimit64, libc_prlimit);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.sched.resource") int
NOTHROW_NCX(LIBCCALL libc_prlimit64)(pid_t pid,
                                     __rlimit_resource_t resource,
                                     struct rlimit64 const *new_limit,
                                     struct rlimit64 *old_limit)
/*[[[body:libc_prlimit64]]]*/
{
	errno_t error;
	error = sys_prlimit64(pid, (syscall_ulong_t)resource, new_limit, old_limit);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_prlimit64]]]*/

/*[[[head:libc_getrlimit,hash:CRC-32=0x183c9dc8]]]*/
/* Put the soft and hard limits for RESOURCE in *RLIMITS.
 * Returns 0 if successful, -1 if not (and sets errno) */
INTERN ATTR_SECTION(".text.crt.sched.resource") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_getrlimit)(__rlimit_resource_t resource,
                                     struct rlimit *rlimits)
/*[[[body:libc_getrlimit]]]*/
{
	errno_t error;
	error = sys_getrlimit((syscall_ulong_t)resource, rlimits);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_getrlimit]]]*/

/*[[[head:libc_setrlimit,hash:CRC-32=0xec5181e9]]]*/
/* Set the soft and hard limits for RESOURCE to *RLIMITS.
 * Only the super-user can increase hard limits.
 * Return 0 if successful, -1 if not (and sets errno) */
INTERN ATTR_SECTION(".text.crt.sched.resource") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_setrlimit)(__rlimit_resource_t resource,
                                     struct rlimit const *rlimits)
/*[[[body:libc_setrlimit]]]*/
{
	errno_t error;
	error = sys_setrlimit((syscall_ulong_t)resource, rlimits);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_setrlimit]]]*/

/*[[[head:libc_getrusage,hash:CRC-32=0xfd6e5154]]]*/
/* Return resource usage information on process indicated by WHO
 * and put it in *USAGE. Returns 0 for success, -1 for failure */
INTERN ATTR_SECTION(".text.crt.sched.resource") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_getrusage)(__rusage_who_t who,
                                     struct rusage *usage)
/*[[[body:libc_getrusage]]]*/
{
	errno_t error;
	error = sys_getrusage((syscall_slong_t)who, usage);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_getrusage]]]*/

/*[[[head:libc_getrusage64,hash:CRC-32=0x1e7c6b14]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_getrusage64, libc_getrusage);
#else /* MAGIC:alias */
/* Return resource usage information on process indicated by WHO
 * and put it in *USAGE. Returns 0 for success, -1 for failure */
INTERN ATTR_SECTION(".text.crt.sched.resource") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_getrusage64)(__rusage_who_t who,
                                       struct rusage64 *usage)
/*[[[body:libc_getrusage64]]]*/
/*AUTO*/{
	(void)who;
	(void)usage;
	CRT_UNIMPLEMENTEDF("getrusage64(%x, %p)", who, usage); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_getrusage64]]]*/

/*[[[head:libc_getpriority,hash:CRC-32=0xb9800c80]]]*/
/* Return the highest priority of any process specified by WHICH and
 * WHO (see above); if WHO is zero, the current process, process group,
 * or user (as specified by WHO) is used.  A lower priority number means
 * higher priority. Priorities range from PRIO_MIN to PRIO_MAX (above) */
INTERN ATTR_SECTION(".text.crt.sched.resource") int
NOTHROW_NCX(LIBCCALL libc_getpriority)(__priority_which_t which,
                                       id_t who)
/*[[[body:libc_getpriority]]]*/
{
	syscall_slong_t result;
	result = sys_getpriority((syscall_ulong_t)which, who);
	if unlikely(E_ISERR(result)) {
		libc_seterrno(-result);
		return -1;
	}
	return (int)(20 - result);
}
/*[[[end:libc_getpriority]]]*/

/*[[[head:libc_setpriority,hash:CRC-32=0xf4c0f8e0]]]*/
/* Set the priority of all processes specified by WHICH and WHO (see above) to PRIO.
 * Returns 0 on success, -1 on errors */
INTERN ATTR_SECTION(".text.crt.sched.resource") int
NOTHROW_NCX(LIBCCALL libc_setpriority)(__priority_which_t which,
                                       id_t who,
                                       int prio)
/*[[[body:libc_setpriority]]]*/
{
	errno_t error;
	error = sys_setpriority((syscall_ulong_t)which, who, (syscall_ulong_t)(20 - prio));
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_setpriority]]]*/

/*[[[head:libc_getrlimit64,hash:CRC-32=0xd1409457]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_getrlimit64, libc_getrlimit);
#else /* MAGIC:alias */
/* Put the soft and hard limits for RESOURCE in *RLIMITS.
 * Returns 0 if successful, -1 if not (and sets errno) */
INTERN ATTR_SECTION(".text.crt.sched.resource") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_getrlimit64)(__rlimit_resource_t resource,
                                       struct rlimit64 *rlimits)
/*[[[body:libc_getrlimit64]]]*/
/*AUTO*/{
	(void)resource;
	(void)rlimits;
	CRT_UNIMPLEMENTEDF("getrlimit64(%x, %p)", resource, rlimits); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_getrlimit64]]]*/

/*[[[head:libc_setrlimit64,hash:CRC-32=0xb198cd0b]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_setrlimit64, libc_setrlimit);
#else /* MAGIC:alias */
/* Set the soft and hard limits for RESOURCE to *RLIMITS.
 * Only the super-user can increase hard limits.
 * Return 0 if successful, -1 if not (and sets errno) */
INTERN ATTR_SECTION(".text.crt.sched.resource") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_setrlimit64)(__rlimit_resource_t resource,
                                       struct rlimit64 const *rlimits)
/*[[[body:libc_setrlimit64]]]*/
/*AUTO*/{
	(void)resource;
	(void)rlimits;
	CRT_UNIMPLEMENTEDF("setrlimit64(%x, %p)", resource, rlimits); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_setrlimit64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x87c1c3e3]]]*/
DEFINE_PUBLIC_ALIAS(prlimit, libc_prlimit);
DEFINE_PUBLIC_ALIAS(prlimit64, libc_prlimit64);
DEFINE_PUBLIC_ALIAS(__getrlimit, libc_getrlimit);
DEFINE_PUBLIC_ALIAS(getrlimit, libc_getrlimit);
DEFINE_PUBLIC_ALIAS(setrlimit, libc_setrlimit);
DEFINE_PUBLIC_ALIAS(getrusage, libc_getrusage);
DEFINE_PUBLIC_ALIAS(getrusage64, libc_getrusage64);
DEFINE_PUBLIC_ALIAS(getpriority, libc_getpriority);
DEFINE_PUBLIC_ALIAS(setpriority, libc_setpriority);
DEFINE_PUBLIC_ALIAS(getrlimit64, libc_getrlimit64);
DEFINE_PUBLIC_ALIAS(setrlimit64, libc_setrlimit64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_RESOURCE_C */
