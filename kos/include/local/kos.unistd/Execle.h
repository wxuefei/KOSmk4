/* HASH CRC-32:0xb5a786b6 */
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
#ifndef __local_Execle_defined
#define __local_Execle_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_Execve
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: Execve from kos.unistd */
#ifndef __local___localdep_Execve_defined
#define __local___localdep_Execve_defined 1
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT_VOID(__ATTR_NORETURN __ATTR_NONNULL((1, 2, 3)),__THROWING,__localdep_Execve,(char const *__restrict __path, __TARGV, __TENVP),Execve,(__path,___argv,___envp))
#endif /* !__local___localdep_Execve_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__LOCAL_LIBC(Execle) __ATTR_NORETURN __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) void
(__VLIBCCALL __LIBC_LOCAL_NAME(Execle))(char const *__restrict __path, char const *__args, ...) __THROWS(...) {
	__REDIRECT_XEXECLE(char, __localdep_Execve, __path, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_Execle_defined
#define __local___localdep_Execle_defined 1
#define __localdep_Execle __LIBC_LOCAL_NAME(Execle)
#endif /* !__local___localdep_Execle_defined */
#else /* __CRT_HAVE_Execve */
#undef __local_Execle_defined
#endif /* !__CRT_HAVE_Execve */
#endif /* !__local_Execle_defined */
