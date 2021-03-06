/* HASH CRC-32:0xdb768eed */
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
#ifndef __local_getexecname_defined
#define __local_getexecname_defined 1
#include <__crt.h>
#include <local/program_invocation_name.h>
#ifdef __LOCAL_program_invocation_name
__NAMESPACE_LOCAL_BEGIN
/* Returns the absolute filename of the main executable (s.a. `program_invocation_name') */
__LOCAL_LIBC(getexecname) __ATTR_CONST __ATTR_WUNUSED char const *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getexecname))(void) {
	return __LOCAL_program_invocation_name;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getexecname_defined
#define __local___localdep_getexecname_defined 1
#define __localdep_getexecname __LIBC_LOCAL_NAME(getexecname)
#endif /* !__local___localdep_getexecname_defined */
#else /* __LOCAL_program_invocation_name */
#undef __local_getexecname_defined
#endif /* !__LOCAL_program_invocation_name */
#endif /* !__local_getexecname_defined */
