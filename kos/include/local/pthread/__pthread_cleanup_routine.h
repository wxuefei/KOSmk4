/* HASH CRC-32:0x5516fcd9 */
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
#ifndef __local___pthread_cleanup_routine_defined
#define __local___pthread_cleanup_routine_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Function called to call the cleanup handler. As an extern inline
 * function the compiler is free to decide inlining the change when
 * needed or fall back on the copy which must exist somewhere else */
__LOCAL_LIBC(__pthread_cleanup_routine) __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__pthread_cleanup_routine))(struct __pthread_cleanup_frame *__frame) {
	if (__frame->__do_it)
		(*__frame->__cancel_routine)(__frame->__cancel_arg);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___pthread_cleanup_routine_defined
#define __local___localdep___pthread_cleanup_routine_defined 1
#define __localdep___pthread_cleanup_routine __LIBC_LOCAL_NAME(__pthread_cleanup_routine)
#endif /* !__local___localdep___pthread_cleanup_routine_defined */
#endif /* !__local___pthread_cleanup_routine_defined */
