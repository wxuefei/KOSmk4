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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(pid_t = __pid_t)]
%[define_replacement(key_t = __key_t)]
%[default:section(".text.crt{|.dos}.utility.shm")]

%{
#include <features.h>
#include <bits/shm.h>

#ifdef __USE_GLIBC
#include <sys/ipc.h>
#endif /* __USE_GLIBC */

__SYSDECL_BEGIN

#ifdef __CC__

#ifdef __USE_XOPEN
#ifndef __pid_t_defined
#define __pid_t_defined 1
typedef __pid_t pid_t;
#endif /* __pid_t_defined */
#endif /* __USE_XOPEN */

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __key_t_defined
#define __key_t_defined 1
typedef __key_t key_t;
#endif /* !__key_t_defined */

#ifndef __time_t_defined
#define __time_t_defined 1
typedef __TM_TYPE(time) time_t;
#endif /* !__time_t_defined */

};

[[decl_include("<features.h>")]]
int shmctl(int shmid, __STDC_INT_AS_UINT_T cmd, struct shmid_ds *buf);

[[decl_include("<features.h>")]]
int shmget(key_t key, size_t size, __STDC_INT_AS_UINT_T shmflg);

[[decl_include("<features.h>")]]
void *shmat(int shmid, void const *shmaddr, __STDC_INT_AS_UINT_T shmflg);

int shmdt(void const *shmaddr);

%{

#endif /* __CC__ */

__SYSDECL_END

}