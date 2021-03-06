/* HASH CRC-32:0x99041910 */
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
#ifndef __local_wait3_64_defined
#define __local_wait3_64_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_wait3
#include <bits/types.h>
#include <features.h>
#include <bits/rusage-struct.h>
#include <parts/waitmacros.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wait3_32 from sys.wait */
#ifndef __local___localdep_wait3_32_defined
#define __local___localdep_wait3_32_defined 1
/* Same as `waitpid(-1, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(,__pid_t,__NOTHROW_RPC,__localdep_wait3_32,(__WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct __rusage32 *__usage),wait3,(__stat_loc,__options,__usage))
#endif /* !__local___localdep_wait3_32_defined */
__NAMESPACE_LOCAL_END
#include <bits/rusage-convert.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `waitpid(-1, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__LOCAL_LIBC(wait3_64) __pid_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wait3_64))(__WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct __rusage64 *__usage) {
	__pid_t __result;
	struct __rusage32 __ru32;
	__result = __localdep_wait3_32(__stat_loc, __options, __usage ? &__ru32 : __NULLPTR);
	if (__result >= 0 && __usage)
		rusage32_to_rusage64(&__ru32, __usage);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wait3_64_defined
#define __local___localdep_wait3_64_defined 1
#define __localdep_wait3_64 __LIBC_LOCAL_NAME(wait3_64)
#endif /* !__local___localdep_wait3_64_defined */
#else /* __CRT_HAVE_wait3 */
#undef __local_wait3_64_defined
#endif /* !__CRT_HAVE_wait3 */
#endif /* !__local_wait3_64_defined */
