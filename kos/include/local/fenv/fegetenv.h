/* HASH CRC-32:0x73ef7cd */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fegetenv_defined
#define __local_fegetenv_defined 1
#include <bits/fenv-inline.h>
__NAMESPACE_LOCAL_BEGIN
/* Store the current floating-point environment in the object pointed to by ENVP */
__LOCAL_LIBC(fegetenv) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fegetenv))(fenv_t *___envp) {
#line 148 "kos/src/libc/magic/fenv.c"
	__inline_fegetenv(___envp);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_fegetenv_defined */