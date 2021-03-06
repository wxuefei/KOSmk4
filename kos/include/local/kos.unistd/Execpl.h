/* HASH CRC-32:0x99ffa95d */
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
#ifndef __local_Execpl_defined
#define __local_Execpl_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_Execvp
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: Execvp from kos.unistd */
#ifndef __local___localdep_Execvp_defined
#define __local___localdep_Execvp_defined 1
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT_VOID(__ATTR_NORETURN __ATTR_NONNULL((1, 2)),__THROWING,__localdep_Execvp,(char const *__restrict __file, __TARGV),Execvp,(__file,___argv))
#endif /* !__local___localdep_Execvp_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__LOCAL_LIBC(Execpl) __ATTR_NORETURN __ATTR_SENTINEL __ATTR_NONNULL((1)) void
(__VLIBCCALL __LIBC_LOCAL_NAME(Execpl))(char const *__restrict __file, char const *__args, ...) __THROWS(...) {
	__REDIRECT_XEXECL(char, __localdep_Execvp, __file, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_Execpl_defined
#define __local___localdep_Execpl_defined 1
#define __localdep_Execpl __LIBC_LOCAL_NAME(Execpl)
#endif /* !__local___localdep_Execpl_defined */
#else /* __CRT_HAVE_Execvp */
#undef __local_Execpl_defined
#endif /* !__CRT_HAVE_Execvp */
#endif /* !__local_Execpl_defined */
