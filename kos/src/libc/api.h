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
#ifndef GUARD_LIBC_API_H
#define GUARD_LIBC_API_H 1

#define __BUILDING_LIBC   1
#define __CRT_KOS_PRIMARY 1
#define __CRT_KOS         1
#ifdef __KERNEL__
#define __CRT_KOS_KERNEL 1
#define __NO_STDSTREAMS  1
#endif /* __KERNEL__ */

#ifndef __OPTIMIZE_SIZE__
/* Enable system call inlining, causing calls to `sys_*' functions from <kos/syscalls.h>
 * to be inlined (as far as possible), rather than being declared as entry points to the
 * libc system call export table (libc also exports all system calls as `sys_*' symbols)
 * NOTE: When optimizing for size, we don't do this, in which case system calls used
 *       by libc library functions get linked against the system call wrappers that
 *       are always exported from libc unconditionally. */
#define __WANT_INLINE_SYSCALLS 1
#endif /* !__OPTIMIZE_SIZE__ */


/* Enable access to a variety of header functions normally
 * locked away behind various feature macros (us being libc,
 * we obviously want access to anything we intend on defining,
 * so we make our job simple by unlocking everything) */
#define _KOS_SOURCE             1
#define _KOS_KERNEL_SOURCE      1
#define _KOS_ALTERATIONS_SOURCE 1
#define _STRING_BWLQ_SOURCE     1
#define _STRING_XCHR_SOURCE     1
#define _CTYPE_MACRO_SOURCE     1
#define _DOS_SOURCE             1
#define _BSD_SOURCE             1
#define _SVID_SOURCE            1
#define _GNU_SOURCE             1
#define _LARGEFILE_SOURCE       1
#define __EXTENSIONS__          1

/* Must load headers in 32-bit time/file-offset mode, so-as to prevent
 * any symbol re-directions from happening, which might otherwise screw
 * up libc linkage. - Instead, libc itself must always explicitly specify
 * the *64 variants of functions (e.g. `mmap64()'; `mmap()' is always the
 * 32-bit variant) */
#undef _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE 1
#undef _TIME64_SOURCE
#define _TIME64_SOURCE 1
#undef _TIME_T_BITS
#define _TIME_T_BITS 32
#undef _FILE_OFFSET_BITS
#define _FILE_OFFSET_BITS 32

#include <__crt.h>

/* Pull in CRT feature definitions */
#ifdef __CC__
#include "crt-features.h" /* Auto-generated file (by generate_headers.dee) */
#ifndef __KERNEL__
/* The user-space libc provides exports for defined system calls (by name).
 * As such, these symbols also exists within the libc_* namespace, meaning
 * that we're allowed to advertise this fact while building libc itself. */
#include <crt-features/crt-kos-syscalls.h>
#else /* !__KERNEL__ */

#if defined(CONFIG_NO_ASSERT_RESTARTABLE) || defined(CONFIG_NO_DEBUGGER)
#undef __CRT_HAVE___acheck
#undef __CRT_HAVE___acheckf
#endif /* CONFIG_NO_ASSERT_RESTARTABLE || CONFIG_NO_DEBUGGER */

#endif /* __KERNEL__ */

/* Delete CRT features for stuff that we don't implement (yet)
 * TODO: Once we do implement this stuff, delete this part! */
#undef __CRT_HAVE___ctype_b_loc
#undef __CRT_HAVE___ctype_tolower_loc
#undef __CRT_HAVE___ctype_toupper_loc
#undef __CRT_HAVE___locale_ctype_ptr
#undef __CRT_HAVE___locale_ctype_ptr_l
#undef __CRT_HAVE__isctype

/* Do some quick probing if crt linkage was configured correctly */
#ifndef __CRT_HAVE_memmove
#error "Bad libc build environment"
#endif /* !__CRT_HAVE_memmove */

#endif /* __CC__ */

#include <features.h>
#include <hybrid/compiler.h>

/* We may define a couple of functions that are annotated as deprecated.
 * As such, prevent potential compiler warnings related to them, as we're
 * actually supposed to use/define them. */
#undef ATTR_DEPRECATED
#undef ATTR_DEPRECATED_
#undef __ATTR_DEPRECATED
#undef __ATTR_DEPRECATED_
#define ATTR_DEPRECATED(msg)   /* nothing */
#define ATTR_DEPRECATED_       /* nothing */
#define __ATTR_DEPRECATED(msg) /* nothing */
#define __ATTR_DEPRECATED_     /* nothing */


#include <hybrid/host.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/kernel/types.h>
#include <kos/types.h>

#include <inttypes.h>
#include <limits.h>
#include <stdarg.h>
#include <stddef.h>

/* Pull in arch-specific LIBC feature information */
#if defined(__i386__) || defined(__x86_64__)
#include "hybrid/arch/i386/config.h"
#endif /* ARCH... */


#ifdef __KERNEL__
#include <kernel/compiler.h>
#endif /* __KERNEL__ */

#define LIBCCALL  __LIBCCALL
#define LIBDCALL  __LIBDCALL
#define LIBKCALL  __LIBKCALL
#define VLIBCCALL __VLIBCCALL
#define VLIBDCALL __VLIBDCALL
#define VLIBKCALL __VLIBKCALL

#ifndef NOBLOCK
#define NOBLOCK __NOBLOCK
#endif /* !NOBLOCK */
#ifndef THROWS
#define THROWS __THROWS
#endif /* !THROWS */

#define ATTR_LIBC_PRINTF(a, b)    __ATTR_LIBC_PRINTF(a, b)
#define ATTR_LIBC_PRINTF_P(a, b)  __ATTR_LIBC_PRINTF_P(a, b)
#define ATTR_LIBC_SCANF(a, b)     __ATTR_LIBC_SCANF(a, b)
#define ATTR_LIBC_STRFMON(a, b)   __ATTR_LIBC_STRFMON(a, b)
#define ATTR_LIBC_WPRINTF(a, b)   __ATTR_LIBC_WPRINTF(a, b)
#define ATTR_LIBC_WPRINTF_P(a, b) __ATTR_LIBC_WPRINTF_P(a, b)
#define ATTR_LIBC_WSCANF(a, b)    __ATTR_LIBC_WSCANF(a, b)

#include <parts/dos/errno.h>
#include <parts/errno.h>
#include <parts/generic/errno.h>

#include <errno.h>

#define libc_seterrno_syserr(e) \
	(likely(!E_ISERR(e)) ? (e) : libc_seterrno((errno_t) - (syscall_slong_t)(syscall_ulong_t)(e)))
#define libc_seterrno_syserr2(e, ERR) \
	(likely(!E_ISERR(e)) ? (e) : (libc_seterrno((errno_t) - (syscall_slong_t)(syscall_ulong_t)(e)), (ERR)))
#define ISSEP(x)           ((x) == '/') /* TODO: In DOS-mode, `\\' must also be accepted */
#define GET_PATHLIST_SEP() ':'          /* TODO: In DOS-mode, `;' must be used */


#define ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALL_DEFAULT_ALIGNED
#define ATTR_MALL_PAGEALIGNED     __ATTR_MALL_PAGEALIGNED

/* Attribute for global data that is mostly read from */
#ifndef ATTR_READMOSTLY
#define ATTR_READMOSTLY ATTR_SECTION(".data.read_mostly")
#endif /* !ATTR_READMOSTLY */


/* Re-bind errno memory locations. */
#undef errno
#undef __errno
#undef __libc_geterrno
#undef __libc_geterrno_or
#undef __libc_seterrno
#define errno                   (*libc_errno_p())
#define __errno                 (*libc_errno_p())
#define __libc_geterrno         libc_geterrno
#define __libc_geterrno_or(alt) libc_geterrno()
#define __libc_seterrno         libc_seterrno

#undef ____errno_location_defined
#define ____errno_location_defined 1
#define __errno_location()         libc_errno_p()

#ifdef __CC__
DECL_BEGIN

#ifndef __locale_t_defined
#define __locale_t_defined 1
typedef __locale_t locale_t;
#endif /* !__locale_t_defined */

#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef __errno_t errno_t;
#endif /* !errno_t_defined */

#ifndef __KERNEL__
INTDEF NOBLOCK ATTR_CONST errno_t *NOTHROW(LIBCCALL libc_errno_p)(void);
INTDEF NOBLOCK ATTR_PURE errno_t NOTHROW(LIBCCALL libc_geterrno)(void);
INTDEF NOBLOCK ATTR_PURE errno_t NOTHROW(LIBCCALL libc_geterrno_safe)(void);
/* Always returns (syscall_slong_t)-1 */
INTDEF NOBLOCK syscall_slong_t NOTHROW(__FCALL libc_seterrno)(errno_t value);

#if 1
#define CONFIG_LOG_LIBC_UNIMPLEMENTED 1
INTDEF void LIBCCALL libc_unimplemented(char const *__restrict name);
INTDEF void VLIBCCALL libc_unimplementedf(char const *__restrict format, ...);
#define CRT_UNIMPLEMENTED(name) libc_unimplemented(name)
#define CRT_UNIMPLEMENTEDF(...) libc_unimplementedf(__VA_ARGS__)
#else
#define CRT_UNIMPLEMENTED(name) (void)0
#endif
#else /* !__KERNEL__ */
/* The kernel doesn't have an ERRNO binding */
#undef libc_seterrno_syserr
#undef libc_seterrno_syserr2
#undef errno
#undef __errno
#undef __libc_geterrno
#undef __libc_geterrno_or
#undef __libc_seterrno
#undef __errno_location
#define __libc_geterrno_or(alt) alt
#define __libc_seterrno(v)      (void)0
#endif /* __KERNEL__ */


DECL_END

#endif /* __CC__ */


#endif /* !GUARD_LIBC_API_H */
