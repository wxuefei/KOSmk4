/* HASH CRC-32:0x98aa02aa */
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
#ifndef _KOS_FUTEXLOCK_H
#define _KOS_FUTEXLOCK_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <kos/bits/futex.h>
#include <bits/types.h>
#include <bits/timespec.h>
#include <hybrid/__atomic.h>
#ifndef __cplusplus
#include <hybrid/pp/__va_nargs.h>
#endif /* !__cplusplus */

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __lfutex_t_defined
#define __lfutex_t_defined 1
typedef __uintptr_t lfutex_t;
#endif /* !__lfutex_t_defined */

#if defined(__CRT_HAVE_lfutexlock64) && (defined(__USE_TIME_BITS64))
/* >> lfutexlock(2)
 * High-level wrapper around the lfutexlockat system call
 * This function behaves identical to the lfutex() system call, except that it takes
 * two futex addresses, where `ulockaddr' is used as a flag specifying that threads may
 * be waiting to be awoken once `LFUTEX_WAKE' is invoked on that memory location, whilst
 * the other futex address is used for the wait-while-condition checking, the same way
 * those checks would also be performed by the `lfutex() system call'
 * @param: command: One of:
 *    - LFUTEX_WAKE:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t count)
 *    - LFUTEX_NOP:               (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t ignored)
 *    - LFUTEX_WAIT:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutexlock ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `command'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `command' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_RPC,lfutexlock,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, __syscall_ulong_t __command, lfutex_t __val, /*struct timespec const *timeout, lfutex_t val2*/...),lfutexlock64,(__ulockaddr,__uaddr,__command,__val,))
#elif defined(__CRT_HAVE_lfutexlock) && (!defined(__USE_TIME_BITS64))
/* >> lfutexlock(2)
 * High-level wrapper around the lfutexlockat system call
 * This function behaves identical to the lfutex() system call, except that it takes
 * two futex addresses, where `ulockaddr' is used as a flag specifying that threads may
 * be waiting to be awoken once `LFUTEX_WAKE' is invoked on that memory location, whilst
 * the other futex address is used for the wait-while-condition checking, the same way
 * those checks would also be performed by the `lfutex() system call'
 * @param: command: One of:
 *    - LFUTEX_WAKE:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t count)
 *    - LFUTEX_NOP:               (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t ignored)
 *    - LFUTEX_WAIT:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutexlock ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `command'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `command' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__CDECLARE(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_RPC,lfutexlock,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, __syscall_ulong_t __command, lfutex_t __val, /*struct timespec const *timeout, lfutex_t val2*/...),(__ulockaddr,__uaddr,__command,__val,))
#elif (defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64))
#include <local/kos.futexlock/lfutexlock.h>
/* >> lfutexlock(2)
 * High-level wrapper around the lfutexlockat system call
 * This function behaves identical to the lfutex() system call, except that it takes
 * two futex addresses, where `ulockaddr' is used as a flag specifying that threads may
 * be waiting to be awoken once `LFUTEX_WAKE' is invoked on that memory location, whilst
 * the other futex address is used for the wait-while-condition checking, the same way
 * those checks would also be performed by the `lfutex() system call'
 * @param: command: One of:
 *    - LFUTEX_WAKE:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t count)
 *    - LFUTEX_NOP:               (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t ignored)
 *    - LFUTEX_WAIT:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutexlock ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `command'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `command' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__NAMESPACE_LOCAL_USING_OR_IMPL(lfutexlock, __FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_RPC(__LIBCCALL lfutexlock)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, __syscall_ulong_t __command, lfutex_t __val, /*struct timespec const *timeout, lfutex_t val2*/...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lfutexlock))(__ulockaddr, __uaddr, __command, __val, ); })
#endif /* lfutexlock... */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_lfutexlock64)
/* >> lfutexlock(2)
 * High-level wrapper around the lfutexlockat system call
 * This function behaves identical to the lfutex() system call, except that it takes
 * two futex addresses, where `ulockaddr' is used as a flag specifying that threads may
 * be waiting to be awoken once `LFUTEX_WAKE' is invoked on that memory location, whilst
 * the other futex address is used for the wait-while-condition checking, the same way
 * those checks would also be performed by the `lfutex() system call'
 * @param: command: One of:
 *    - LFUTEX_WAKE:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t count)
 *    - LFUTEX_NOP:               (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t ignored)
 *    - LFUTEX_WAIT:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutexlock ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `command'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `command' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__CDECLARE(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_RPC,lfutexlock64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, __syscall_ulong_t __command, lfutex_t __val, /*struct timespec64 const *timeout, lfutex_t val2*/...),(__ulockaddr,__uaddr,__command,__val,))
#elif defined(__CRT_HAVE_lfutexlock) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> lfutexlock(2)
 * High-level wrapper around the lfutexlockat system call
 * This function behaves identical to the lfutex() system call, except that it takes
 * two futex addresses, where `ulockaddr' is used as a flag specifying that threads may
 * be waiting to be awoken once `LFUTEX_WAKE' is invoked on that memory location, whilst
 * the other futex address is used for the wait-while-condition checking, the same way
 * those checks would also be performed by the `lfutex() system call'
 * @param: command: One of:
 *    - LFUTEX_WAKE:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t count)
 *    - LFUTEX_NOP:               (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t ignored)
 *    - LFUTEX_WAIT:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutexlock ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `command'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `command' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_RPC,lfutexlock64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, __syscall_ulong_t __command, lfutex_t __val, /*struct timespec64 const *timeout, lfutex_t val2*/...),lfutexlock,(__ulockaddr,__uaddr,__command,__val,))
#elif defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/lfutexlock64.h>
/* >> lfutexlock(2)
 * High-level wrapper around the lfutexlockat system call
 * This function behaves identical to the lfutex() system call, except that it takes
 * two futex addresses, where `ulockaddr' is used as a flag specifying that threads may
 * be waiting to be awoken once `LFUTEX_WAKE' is invoked on that memory location, whilst
 * the other futex address is used for the wait-while-condition checking, the same way
 * those checks would also be performed by the `lfutex() system call'
 * @param: command: One of:
 *    - LFUTEX_WAKE:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t count)
 *    - LFUTEX_NOP:               (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t ignored)
 *    - LFUTEX_WAIT:              (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutexlock ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:        (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `command'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    The given `command' is invalid
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__NAMESPACE_LOCAL_USING_OR_IMPL(lfutexlock64, __FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_RPC(__LIBCCALL lfutexlock64)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, __syscall_ulong_t __command, lfutex_t __val, /*struct timespec64 const *timeout, lfutex_t val2*/...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lfutexlock64))(__ulockaddr, __uaddr, __command, __val, ); })
#endif /* lfutexlock64... */
#endif /* __USE_TIME64 */
#if defined(__CRT_HAVE_futexlock_wake)
/* A more efficient variant of `futex_wake()' that can be used to wake up threads waiting
 * on some given futex-lock. - This method of waking is faster, since it doesn't invoke a
 * system call when no thread is waiting on the given lock */
__CDECLARE(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,futexlock_wake,(lfutex_t *__ulockaddr, __SIZE_TYPE__ __max_wake),(__ulockaddr,__max_wake))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <local/kos.futexlock/futexlock_wake.h>
/* A more efficient variant of `futex_wake()' that can be used to wake up threads waiting
 * on some given futex-lock. - This method of waking is faster, since it doesn't invoke a
 * system call when no thread is waiting on the given lock */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_wake, __FORCELOCAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL futexlock_wake)(lfutex_t *__ulockaddr, __SIZE_TYPE__ __max_wake) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_wake))(__ulockaddr, __max_wake); })
#endif /* futexlock_wake... */
#if defined(__CRT_HAVE_futexlock_wakeall)
/* A more efficient variant of `futex_wake()' that can be used to wake up threads waiting
 * on some given futex-lock. - This method of waking is faster, since it doesn't invoke a
 * system call when no thread is waiting on the given lock */
__CDECLARE(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,futexlock_wakeall,(lfutex_t *__ulockaddr),(__ulockaddr))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex) || defined(__CRT_HAVE_futexlock_wake)
#include <local/kos.futexlock/futexlock_wakeall.h>
/* A more efficient variant of `futex_wake()' that can be used to wake up threads waiting
 * on some given futex-lock. - This method of waking is faster, since it doesn't invoke a
 * system call when no thread is waiting on the given lock */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_wakeall, __FORCELOCAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL futexlock_wakeall)(lfutex_t *__ulockaddr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_wakeall))(__ulockaddr); })
#endif /* futexlock_wakeall... */
#if defined(__CRT_HAVE_futexlock_waitwhile)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value),(__ulockaddr,__uaddr,__equal_to_value))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_waitwhile.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_waitwhile, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_waitwhile))(__ulockaddr, __uaddr, __equal_to_value); })
#endif /* futexlock_waitwhile... */
#if defined(__CRT_HAVE_futexlock_waituntil)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waituntil,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value),(__ulockaddr,__uaddr,__not_equal_to_value))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_waituntil.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_waituntil, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waituntil)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_waituntil))(__ulockaddr, __uaddr, __not_equal_to_value); })
#endif /* futexlock_waituntil... */
#if defined(__CRT_HAVE_futexlock_waitwhile)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_equal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value),futexlock_waitwhile,(__ulockaddr,__uaddr,__equal_to_value))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_waitwhile.h>
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_equal)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_waitwhile))(__ulockaddr, __uaddr, __equal_to_value); }
#endif /* futexlock_waitwhile_equal... */
#if defined(__CRT_HAVE_futexlock_waituntil)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_notequal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value),futexlock_waituntil,(__ulockaddr,__uaddr,__not_equal_to_value))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_waituntil.h>
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_notequal)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_waituntil))(__ulockaddr, __uaddr, __not_equal_to_value); }
#endif /* futexlock_waitwhile_notequal... */
#if defined(__CRT_HAVE_futexlock_waitwhile_above)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_above,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_value),(__ulockaddr,__uaddr,__above_value))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_waitwhile_above.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_waitwhile_above, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_above)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_waitwhile_above))(__ulockaddr, __uaddr, __above_value); })
#endif /* futexlock_waitwhile_above... */
#if defined(__CRT_HAVE_futexlock_waitwhile_below)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_below,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_value),(__ulockaddr,__uaddr,__below_value))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_waitwhile_below.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_waitwhile_below, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_below)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_waitwhile_below))(__ulockaddr, __uaddr, __below_value); })
#endif /* futexlock_waitwhile_below... */
#if defined(__CRT_HAVE_futexlock_waitwhile_aboveequal)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_aboveequal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_equal_value),(__ulockaddr,__uaddr,__above_equal_value))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_waitwhile_aboveequal.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_waitwhile_aboveequal, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_aboveequal)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_equal_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_waitwhile_aboveequal))(__ulockaddr, __uaddr, __above_equal_value); })
#endif /* futexlock_waitwhile_aboveequal... */
#if defined(__CRT_HAVE_futexlock_waitwhile_belowequal)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_belowequal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_equal_value),(__ulockaddr,__uaddr,__below_equal_value))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_waitwhile_belowequal.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_waitwhile_belowequal, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_belowequal)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_equal_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_waitwhile_belowequal))(__ulockaddr, __uaddr, __below_equal_value); })
#endif /* futexlock_waitwhile_belowequal... */
#if defined(__CRT_HAVE_futexlock_waitwhile_cmpxch)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_cmpxch,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value),(__ulockaddr,__uaddr,__old_value,__new_value))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_waitwhile_cmpxch.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_waitwhile_cmpxch, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_cmpxch)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_waitwhile_cmpxch))(__ulockaddr, __uaddr, __old_value, __new_value); })
#endif /* futexlock_waitwhile_cmpxch... */
#if defined(__CRT_HAVE_futexlock_waituntil_cmpxch)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waituntil_cmpxch,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value),(__ulockaddr,__uaddr,__old_value,__new_value))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_waituntil_cmpxch.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_waituntil_cmpxch, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waituntil_cmpxch)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_waituntil_cmpxch))(__ulockaddr, __uaddr, __old_value, __new_value); })
#endif /* futexlock_waituntil_cmpxch... */
#if defined(__CRT_HAVE_futexlock_waitlock)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitlock,(lfutex_t *__ulockaddr, lfutex_t *__uaddr),(__ulockaddr,__uaddr))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_waitlock.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_waitlock, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitlock)(lfutex_t *__ulockaddr, lfutex_t *__uaddr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_waitlock))(__ulockaddr, __uaddr); })
#endif /* futexlock_waitlock... */
#if defined(__CRT_HAVE_futexlock_waitwhile_exactbits)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_exactbits,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask),(__ulockaddr,__uaddr,__bitmask,__setmask))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_waitwhile_exactbits.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_waitwhile_exactbits, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_exactbits)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_waitwhile_exactbits))(__ulockaddr, __uaddr, __bitmask, __setmask); })
#endif /* futexlock_waitwhile_exactbits... */
#if defined(__CRT_HAVE_futexlock_waituntil_exactbits)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waituntil_exactbits,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask),(__ulockaddr,__uaddr,__bitmask,__setmask))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_waituntil_exactbits.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_waituntil_exactbits, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waituntil_exactbits)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_waituntil_exactbits))(__ulockaddr, __uaddr, __bitmask, __setmask); })
#endif /* futexlock_waituntil_exactbits... */
#if defined(__CRT_HAVE_futexlock_waitwhile_anybit)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_anybit,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask),(__ulockaddr,__uaddr,__bitmask))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_waitwhile_anybit.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_waitwhile_anybit, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_anybit)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_waitwhile_anybit))(__ulockaddr, __uaddr, __bitmask); })
#endif /* futexlock_waitwhile_anybit... */
#if defined(__CRT_HAVE_futexlock_waitwhile_allbits)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_allbits,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask),(__ulockaddr,__uaddr,__bitmask))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_waitwhile_allbits.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_waitwhile_allbits, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_allbits)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_waitwhile_allbits))(__ulockaddr, __uaddr, __bitmask); })
#endif /* futexlock_waitwhile_allbits... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile64,(__ulockaddr,__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec *__rel_timeout),(__ulockaddr,__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile.h>
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitwhile, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile))(__ulockaddr, __uaddr, __equal_to_value, __rel_timeout); })
#endif /* futexlock_timedwaitwhile... */
#if defined(__CRT_HAVE_futexlock_timedwaituntil64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaituntil,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec *__rel_timeout),futexlock_timedwaituntil64,(__ulockaddr,__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaituntil) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaituntil,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec *__rel_timeout),(__ulockaddr,__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaituntil.h>
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaituntil, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaituntil)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaituntil))(__ulockaddr, __uaddr, __not_equal_to_value, __rel_timeout); })
#endif /* futexlock_timedwaituntil... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_equal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile64,(__ulockaddr,__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_equal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile,(__ulockaddr,__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile.h>
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_equal)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile))(__ulockaddr, __uaddr, __equal_to_value, __rel_timeout); }
#endif /* futexlock_timedwaitwhile_equal... */
#if defined(__CRT_HAVE_futexlock_timedwaituntil64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_notequal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec *__rel_timeout),futexlock_timedwaituntil64,(__ulockaddr,__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaituntil) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_notequal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec *__rel_timeout),futexlock_timedwaituntil,(__ulockaddr,__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaituntil.h>
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_notequal)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaituntil))(__ulockaddr, __uaddr, __not_equal_to_value, __rel_timeout); }
#endif /* futexlock_timedwaitwhile_notequal... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_above64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_above,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile_above64,(__ulockaddr,__uaddr,__above_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_above) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_above,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_value, struct timespec *__rel_timeout),(__ulockaddr,__uaddr,__above_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile_above.h>
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitwhile_above, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_above)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_above))(__ulockaddr, __uaddr, __above_value, __rel_timeout); })
#endif /* futexlock_timedwaitwhile_above... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_below64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_below,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile_below64,(__ulockaddr,__uaddr,__below_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_below) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_below,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_value, struct timespec *__rel_timeout),(__ulockaddr,__uaddr,__below_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile_below.h>
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitwhile_below, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_below)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_below))(__ulockaddr, __uaddr, __below_value, __rel_timeout); })
#endif /* futexlock_timedwaitwhile_below... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_aboveequal64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_aboveequal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile_aboveequal64,(__ulockaddr,__uaddr,__above_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_aboveequal) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_aboveequal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec *__rel_timeout),(__ulockaddr,__uaddr,__above_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile_aboveequal.h>
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitwhile_aboveequal, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_aboveequal)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_aboveequal))(__ulockaddr, __uaddr, __above_equal_value, __rel_timeout); })
#endif /* futexlock_timedwaitwhile_aboveequal... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_belowequal64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_belowequal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile_belowequal64,(__ulockaddr,__uaddr,__below_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_belowequal) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_belowequal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec *__rel_timeout),(__ulockaddr,__uaddr,__below_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile_belowequal.h>
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitwhile_belowequal, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_belowequal)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_belowequal))(__ulockaddr, __uaddr, __below_equal_value, __rel_timeout); })
#endif /* futexlock_timedwaitwhile_belowequal... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_cmpxch64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_cmpxch,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile_cmpxch64,(__ulockaddr,__uaddr,__old_value,__new_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_cmpxch) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_cmpxch,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value, struct timespec *__rel_timeout),(__ulockaddr,__uaddr,__old_value,__new_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile_cmpxch.h>
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitwhile_cmpxch, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_cmpxch)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_cmpxch))(__ulockaddr, __uaddr, __old_value, __new_value, __rel_timeout); })
#endif /* futexlock_timedwaitwhile_cmpxch... */
#if defined(__CRT_HAVE_futexlock_timedwaituntil_cmpxch64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaituntil_cmpxch,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value, struct timespec *__rel_timeout),futexlock_timedwaituntil_cmpxch64,(__ulockaddr,__uaddr,__old_value,__new_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaituntil_cmpxch) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaituntil_cmpxch,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value, struct timespec *__rel_timeout),(__ulockaddr,__uaddr,__old_value,__new_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaituntil_cmpxch.h>
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaituntil_cmpxch, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaituntil_cmpxch)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaituntil_cmpxch))(__ulockaddr, __uaddr, __old_value, __new_value, __rel_timeout); })
#endif /* futexlock_timedwaituntil_cmpxch... */
#if defined(__CRT_HAVE_futexlock_timedwaitlock64) && (defined(__USE_TIME_BITS64))
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitlock,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, struct timespec *__rel_timeout),futexlock_timedwaitlock64,(__ulockaddr,__uaddr,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitlock) && (!defined(__USE_TIME_BITS64))
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitlock,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, struct timespec *__rel_timeout),(__ulockaddr,__uaddr,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitlock.h>
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitlock, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitlock)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitlock))(__ulockaddr, __uaddr, __rel_timeout); })
#endif /* futexlock_timedwaitlock... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_exactbits64) && (defined(__USE_TIME_BITS64))
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_exactbits,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec *__rel_timeout),futexlock_timedwaitwhile_exactbits64,(__ulockaddr,__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_exactbits) && (!defined(__USE_TIME_BITS64))
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_exactbits,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec *__rel_timeout),(__ulockaddr,__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile_exactbits.h>
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitwhile_exactbits, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_exactbits)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_exactbits))(__ulockaddr, __uaddr, __bitmask, __setmask, __rel_timeout); })
#endif /* futexlock_timedwaitwhile_exactbits... */
#if defined(__CRT_HAVE_futexlock_timedwaituntil_exactbits64) && (defined(__USE_TIME_BITS64))
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaituntil_exactbits,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec *__rel_timeout),futexlock_timedwaituntil_exactbits64,(__ulockaddr,__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaituntil_exactbits) && (!defined(__USE_TIME_BITS64))
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaituntil_exactbits,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec *__rel_timeout),(__ulockaddr,__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaituntil_exactbits.h>
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaituntil_exactbits, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaituntil_exactbits)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaituntil_exactbits))(__ulockaddr, __uaddr, __bitmask, __setmask, __rel_timeout); })
#endif /* futexlock_timedwaituntil_exactbits... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_anybit64) && (defined(__USE_TIME_BITS64))
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_anybit,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec *__rel_timeout),futexlock_timedwaitwhile_anybit64,(__ulockaddr,__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_anybit) && (!defined(__USE_TIME_BITS64))
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_anybit,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec *__rel_timeout),(__ulockaddr,__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile_anybit.h>
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitwhile_anybit, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_anybit)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_anybit))(__ulockaddr, __uaddr, __bitmask, __rel_timeout); })
#endif /* futexlock_timedwaitwhile_anybit... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_allbits64) && (defined(__USE_TIME_BITS64))
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_allbits,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec *__rel_timeout),futexlock_timedwaitwhile_allbits64,(__ulockaddr,__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_allbits) && (!defined(__USE_TIME_BITS64))
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_allbits,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec *__rel_timeout),(__ulockaddr,__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile_allbits.h>
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitwhile_allbits, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_allbits)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_allbits))(__ulockaddr, __uaddr, __bitmask, __rel_timeout); })
#endif /* futexlock_timedwaitwhile_allbits... */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_futexlock_timedwaitwhile64)
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec64 *__rel_timeout),(__ulockaddr,__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec64 *__rel_timeout),futexlock_timedwaitwhile,(__ulockaddr,__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_timedwaitwhile64.h>
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitwhile64, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile64)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec64 *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile64))(__ulockaddr, __uaddr, __equal_to_value, __rel_timeout); })
#endif /* futexlock_timedwaitwhile64... */
#if defined(__CRT_HAVE_futexlock_timedwaituntil64)
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaituntil64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec64 *__rel_timeout),(__ulockaddr,__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaituntil) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaituntil64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec64 *__rel_timeout),futexlock_timedwaituntil,(__ulockaddr,__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_timedwaituntil64.h>
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaituntil64, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaituntil64)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec64 *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaituntil64))(__ulockaddr, __uaddr, __not_equal_to_value, __rel_timeout); })
#endif /* futexlock_timedwaituntil64... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile64)
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_equal64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec64 *__rel_timeout),futexlock_timedwaitwhile64,(__ulockaddr,__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_equal) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_equal64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec64 *__rel_timeout),futexlock_timedwaitwhile_equal,(__ulockaddr,__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_timedwaitwhile64.h>
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_equal64)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec64 *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile64))(__ulockaddr, __uaddr, __equal_to_value, __rel_timeout); }
#endif /* futexlock_timedwaitwhile_equal64... */
#if defined(__CRT_HAVE_futexlock_timedwaituntil64)
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_notequal64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec64 *__rel_timeout),futexlock_timedwaituntil64,(__ulockaddr,__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_notequal) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_notequal64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec64 *__rel_timeout),futexlock_timedwaitwhile_notequal,(__ulockaddr,__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_timedwaituntil64.h>
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_notequal64)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec64 *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaituntil64))(__ulockaddr, __uaddr, __not_equal_to_value, __rel_timeout); }
#endif /* futexlock_timedwaitwhile_notequal64... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_above64)
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_above64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_value, struct timespec64 *__rel_timeout),(__ulockaddr,__uaddr,__above_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_above) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_above64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_value, struct timespec64 *__rel_timeout),futexlock_timedwaitwhile_above,(__ulockaddr,__uaddr,__above_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_timedwaitwhile_above64.h>
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitwhile_above64, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_above64)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_value, struct timespec64 *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_above64))(__ulockaddr, __uaddr, __above_value, __rel_timeout); })
#endif /* futexlock_timedwaitwhile_above64... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_below64)
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_below64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_value, struct timespec64 *__rel_timeout),(__ulockaddr,__uaddr,__below_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_below) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_below64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_value, struct timespec64 *__rel_timeout),futexlock_timedwaitwhile_below,(__ulockaddr,__uaddr,__below_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_timedwaitwhile_below64.h>
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitwhile_below64, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_below64)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_value, struct timespec64 *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_below64))(__ulockaddr, __uaddr, __below_value, __rel_timeout); })
#endif /* futexlock_timedwaitwhile_below64... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_aboveequal64)
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_aboveequal64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec64 *__rel_timeout),(__ulockaddr,__uaddr,__above_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_aboveequal) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_aboveequal64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec64 *__rel_timeout),futexlock_timedwaitwhile_aboveequal,(__ulockaddr,__uaddr,__above_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_timedwaitwhile_aboveequal64.h>
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitwhile_aboveequal64, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_aboveequal64)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec64 *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_aboveequal64))(__ulockaddr, __uaddr, __above_equal_value, __rel_timeout); })
#endif /* futexlock_timedwaitwhile_aboveequal64... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_belowequal64)
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_belowequal64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec64 *__rel_timeout),(__ulockaddr,__uaddr,__below_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_belowequal) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_belowequal64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec64 *__rel_timeout),futexlock_timedwaitwhile_belowequal,(__ulockaddr,__uaddr,__below_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_timedwaitwhile_belowequal64.h>
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitwhile_belowequal64, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_belowequal64)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec64 *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_belowequal64))(__ulockaddr, __uaddr, __below_equal_value, __rel_timeout); })
#endif /* futexlock_timedwaitwhile_belowequal64... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_cmpxch64)
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_cmpxch64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value, struct timespec64 *__rel_timeout),(__ulockaddr,__uaddr,__old_value,__new_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_cmpxch) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_cmpxch64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value, struct timespec64 *__rel_timeout),futexlock_timedwaitwhile_cmpxch,(__ulockaddr,__uaddr,__old_value,__new_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_timedwaitwhile_cmpxch64.h>
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitwhile_cmpxch64, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_cmpxch64)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value, struct timespec64 *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_cmpxch64))(__ulockaddr, __uaddr, __old_value, __new_value, __rel_timeout); })
#endif /* futexlock_timedwaitwhile_cmpxch64... */
#if defined(__CRT_HAVE_futexlock_timedwaituntil_cmpxch64)
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaituntil_cmpxch64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value, struct timespec64 *__rel_timeout),(__ulockaddr,__uaddr,__old_value,__new_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaituntil_cmpxch) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaituntil_cmpxch64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value, struct timespec64 *__rel_timeout),futexlock_timedwaituntil_cmpxch,(__ulockaddr,__uaddr,__old_value,__new_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_timedwaituntil_cmpxch64.h>
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaituntil_cmpxch64, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaituntil_cmpxch64)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value, struct timespec64 *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaituntil_cmpxch64))(__ulockaddr, __uaddr, __old_value, __new_value, __rel_timeout); })
#endif /* futexlock_timedwaituntil_cmpxch64... */
#if defined(__CRT_HAVE_futexlock_timedwaitlock64)
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitlock64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, struct timespec64 *__rel_timeout),(__ulockaddr,__uaddr,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitlock) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitlock64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, struct timespec64 *__rel_timeout),futexlock_timedwaitlock,(__ulockaddr,__uaddr,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_timedwaitlock64.h>
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitlock64, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitlock64)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, struct timespec64 *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitlock64))(__ulockaddr, __uaddr, __rel_timeout); })
#endif /* futexlock_timedwaitlock64... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_exactbits64)
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_exactbits64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec64 *__rel_timeout),(__ulockaddr,__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_exactbits) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_exactbits64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec64 *__rel_timeout),futexlock_timedwaitwhile_exactbits,(__ulockaddr,__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_timedwaitwhile_exactbits64.h>
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitwhile_exactbits64, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_exactbits64)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec64 *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_exactbits64))(__ulockaddr, __uaddr, __bitmask, __setmask, __rel_timeout); })
#endif /* futexlock_timedwaitwhile_exactbits64... */
#if defined(__CRT_HAVE_futexlock_timedwaituntil_exactbits64)
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaituntil_exactbits64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec64 *__rel_timeout),(__ulockaddr,__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaituntil_exactbits) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaituntil_exactbits64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec64 *__rel_timeout),futexlock_timedwaituntil_exactbits,(__ulockaddr,__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_timedwaituntil_exactbits64.h>
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaituntil_exactbits64, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaituntil_exactbits64)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec64 *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaituntil_exactbits64))(__ulockaddr, __uaddr, __bitmask, __setmask, __rel_timeout); })
#endif /* futexlock_timedwaituntil_exactbits64... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_anybit64)
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_anybit64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec64 *__rel_timeout),(__ulockaddr,__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_anybit) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_anybit64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec64 *__rel_timeout),futexlock_timedwaitwhile_anybit,(__ulockaddr,__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_timedwaitwhile_anybit64.h>
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitwhile_anybit64, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_anybit64)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec64 *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_anybit64))(__ulockaddr, __uaddr, __bitmask, __rel_timeout); })
#endif /* futexlock_timedwaitwhile_anybit64... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_allbits64)
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_allbits64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec64 *__rel_timeout),(__ulockaddr,__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_allbits) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_timedwaitwhile_allbits64,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec64 *__rel_timeout),futexlock_timedwaitwhile_allbits,(__ulockaddr,__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock64) || defined(__CRT_HAVE_lfutexlock)
#include <local/kos.futexlock/futexlock_timedwaitwhile_allbits64.h>
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__NAMESPACE_LOCAL_USING_OR_IMPL(futexlock_timedwaitwhile_allbits64, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_timedwaitwhile_allbits64)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec64 *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_allbits64))(__ulockaddr, __uaddr, __bitmask, __rel_timeout); })
#endif /* futexlock_timedwaitwhile_allbits64... */
#endif /* __USE_TIME64 */

/* Provide overloads for the non-timed functions add an optional `rel_timeout'
 * argument that re-directly to the function's timed variant.
 * Because this overload is purely based on argument count, we can emulate
 * this portably both in C++ and C (using `__HYBRID_PP_VA_OVERLOAD') */
#ifdef __cplusplus
extern "C++" {
#if defined(__CRT_HAVE_futexlock_timedwaitwhile64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile64,(__ulockaddr,__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile,(__ulockaddr,__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile.h>
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile))(__ulockaddr, __uaddr, __equal_to_value, __rel_timeout); }
#endif /* futexlock_waitwhile... */
#if defined(__CRT_HAVE_futexlock_timedwaituntil64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waituntil,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec *__rel_timeout),futexlock_timedwaituntil64,(__ulockaddr,__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaituntil) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waituntil,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec *__rel_timeout),futexlock_timedwaituntil,(__ulockaddr,__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaituntil.h>
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waituntil)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaituntil))(__ulockaddr, __uaddr, __not_equal_to_value, __rel_timeout); }
#endif /* futexlock_waituntil... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_equal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile64,(__ulockaddr,__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_equal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile,(__ulockaddr,__uaddr,__equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile.h>
/* Wait if `*uaddr == equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_equal)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __equal_to_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile))(__ulockaddr, __uaddr, __equal_to_value, __rel_timeout); }
#endif /* futexlock_waitwhile_equal... */
#if defined(__CRT_HAVE_futexlock_timedwaituntil64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_notequal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec *__rel_timeout),futexlock_timedwaituntil64,(__ulockaddr,__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaituntil) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_notequal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec *__rel_timeout),futexlock_timedwaituntil,(__ulockaddr,__uaddr,__not_equal_to_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaituntil.h>
/* Wait if `*uaddr != not_equal_to_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_notequal)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __not_equal_to_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaituntil))(__ulockaddr, __uaddr, __not_equal_to_value, __rel_timeout); }
#endif /* futexlock_waitwhile_notequal... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_above64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_above,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile_above64,(__ulockaddr,__uaddr,__above_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_above) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_above,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile_above,(__ulockaddr,__uaddr,__above_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile_above.h>
/* Wait if `*uaddr > above_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_above)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_above))(__ulockaddr, __uaddr, __above_value, __rel_timeout); }
#endif /* futexlock_waitwhile_above... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_below64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_below,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile_below64,(__ulockaddr,__uaddr,__below_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_below) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_below,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile_below,(__ulockaddr,__uaddr,__below_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile_below.h>
/* Wait if `*uaddr < below_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_below)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_below))(__ulockaddr, __uaddr, __below_value, __rel_timeout); }
#endif /* futexlock_waitwhile_below... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_aboveequal64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_aboveequal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile_aboveequal64,(__ulockaddr,__uaddr,__above_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_aboveequal) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_aboveequal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile_aboveequal,(__ulockaddr,__uaddr,__above_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile_aboveequal.h>
/* Wait if `*uaddr >= above_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_aboveequal)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __above_equal_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_aboveequal))(__ulockaddr, __uaddr, __above_equal_value, __rel_timeout); }
#endif /* futexlock_waitwhile_aboveequal... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_belowequal64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_belowequal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile_belowequal64,(__ulockaddr,__uaddr,__below_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_belowequal) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_belowequal,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile_belowequal,(__ulockaddr,__uaddr,__below_equal_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile_belowequal.h>
/* Wait if `*uaddr <= below_equal_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_belowequal)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __below_equal_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_belowequal))(__ulockaddr, __uaddr, __below_equal_value, __rel_timeout); }
#endif /* futexlock_waitwhile_belowequal... */
#if defined(__CRT_HAVE_futexlock_timedwaitwhile_cmpxch64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_cmpxch,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile_cmpxch64,(__ulockaddr,__uaddr,__old_value,__new_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_cmpxch) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_cmpxch,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value, struct timespec *__rel_timeout),futexlock_timedwaitwhile_cmpxch,(__ulockaddr,__uaddr,__old_value,__new_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile_cmpxch.h>
/* Wait if `*uaddr == old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_cmpxch)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_cmpxch))(__ulockaddr, __uaddr, __old_value, __new_value, __rel_timeout); }
#endif /* futexlock_waitwhile_cmpxch... */
#if defined(__CRT_HAVE_futexlock_timedwaituntil_cmpxch64) && (defined(__USE_TIME_BITS64))
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waituntil_cmpxch,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value, struct timespec *__rel_timeout),futexlock_timedwaituntil_cmpxch64,(__ulockaddr,__uaddr,__old_value,__new_value,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaituntil_cmpxch) && (!defined(__USE_TIME_BITS64))
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waituntil_cmpxch,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value, struct timespec *__rel_timeout),futexlock_timedwaituntil_cmpxch,(__ulockaddr,__uaddr,__old_value,__new_value,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaituntil_cmpxch.h>
/* Wait if `*uaddr != old_value', and set `*uaddr = new_value'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waituntil_cmpxch)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaituntil_cmpxch))(__ulockaddr, __uaddr, __old_value, __new_value, __rel_timeout); }
#endif /* futexlock_waituntil_cmpxch... */
#if defined(__CRT_HAVE_futexlock_timedwaitlock64) && (defined(__USE_TIME_BITS64))
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitlock,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, struct timespec *__rel_timeout),futexlock_timedwaitlock64,(__ulockaddr,__uaddr,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitlock) && (!defined(__USE_TIME_BITS64))
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitlock,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, struct timespec *__rel_timeout),futexlock_timedwaitlock,(__ulockaddr,__uaddr,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitlock.h>
/* Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
 * @return: -1:ETIMEDOUT: The given `rel_timeout' has expired */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitlock)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitlock))(__ulockaddr, __uaddr, __rel_timeout); }
#endif /* futexlock_waitlock... */
#if defined(__CRT_HAVE_futexlock_waitwhile_exactbits64) && (defined(__USE_TIME_BITS64))
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_exactbits,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec *__rel_timeout),futexlock_waitwhile_exactbits64,(__ulockaddr,__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_waitwhile_exactbits) && (!defined(__USE_TIME_BITS64))
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_exactbits,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec *__rel_timeout),(__ulockaddr,__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_exactbits)
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_exactbits,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec *__rel_timeout),futexlock_timedwaitwhile_exactbits,(__ulockaddr,__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile_exactbits.h>
/* Wait if `(*uaddr & bitmask) == setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_exactbits)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_exactbits))(__ulockaddr, __uaddr, __bitmask, __setmask, __rel_timeout); }
#endif /* futexlock_waitwhile_exactbits... */
#if defined(__CRT_HAVE_futexlock_waituntil_exactbits64) && (defined(__USE_TIME_BITS64))
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waituntil_exactbits,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec *__rel_timeout),futexlock_waituntil_exactbits64,(__ulockaddr,__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_waituntil_exactbits) && (!defined(__USE_TIME_BITS64))
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waituntil_exactbits,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec *__rel_timeout),(__ulockaddr,__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaituntil_exactbits)
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waituntil_exactbits,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec *__rel_timeout),futexlock_timedwaituntil_exactbits,(__ulockaddr,__uaddr,__bitmask,__setmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaituntil_exactbits.h>
/* Wait if `(*uaddr & bitmask) != setmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waituntil_exactbits)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaituntil_exactbits))(__ulockaddr, __uaddr, __bitmask, __setmask, __rel_timeout); }
#endif /* futexlock_waituntil_exactbits... */
#if defined(__CRT_HAVE_futexlock_waitwhile_anybit64) && (defined(__USE_TIME_BITS64))
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_anybit,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec *__rel_timeout),futexlock_waitwhile_anybit64,(__ulockaddr,__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_waitwhile_anybit) && (!defined(__USE_TIME_BITS64))
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_anybit,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec *__rel_timeout),(__ulockaddr,__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_anybit)
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_anybit,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec *__rel_timeout),futexlock_timedwaitwhile_anybit,(__ulockaddr,__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile_anybit.h>
/* Wait if `(*uaddr & bitmask) != 0'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_anybit)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_anybit))(__ulockaddr, __uaddr, __bitmask, __rel_timeout); }
#endif /* futexlock_waitwhile_anybit... */
#if defined(__CRT_HAVE_futexlock_waitwhile_allbits64) && (defined(__USE_TIME_BITS64))
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_allbits,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec *__rel_timeout),futexlock_waitwhile_allbits64,(__ulockaddr,__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_waitwhile_allbits) && (!defined(__USE_TIME_BITS64))
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_allbits,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec *__rel_timeout),(__ulockaddr,__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_futexlock_timedwaitwhile_allbits)
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,futexlock_waitwhile_allbits,(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec *__rel_timeout),futexlock_timedwaitwhile_allbits,(__ulockaddr,__uaddr,__bitmask,__rel_timeout))
#elif defined(__CRT_HAVE_lfutexlock) || defined(__CRT_HAVE_lfutexlock64)
#include <local/kos.futexlock/futexlock_timedwaitwhile_allbits.h>
/* Wait if `(*uaddr & bitmask) == bitmask'
 * @return: 0: Did wait
 * @return: 1: Didn't wait
 * @return: -1:EFAULT: A faulty pointer was given
 * @return: -1:EINTR:  Operation was interrupted */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL futexlock_waitwhile_allbits)(lfutex_t *__ulockaddr, lfutex_t *__uaddr, lfutex_t __bitmask, struct timespec *__rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futexlock_timedwaitwhile_allbits))(__ulockaddr, __uaddr, __bitmask, __rel_timeout); }
#endif /* futexlock_waitwhile_allbits... */
} /* extern "C++" */
#else /* __cplusplus */
#define __PRIVATE_futexlock_waitwhile_2(ulockaddr, uaddr, equal_to_value)                            futexlock_waitwhile(ulockaddr, uaddr, equal_to_value)
#define __PRIVATE_futexlock_waitwhile_3(ulockaddr, uaddr, equal_to_value, rel_timeout)               futexlock_timedwaitwhile(ulockaddr, uaddr, equal_to_value, rel_timeout)
#define __PRIVATE_futexlock_waituntil_2(ulockaddr, uaddr, not_equal_to_value)                        futexlock_waituntil(ulockaddr, uaddr, not_equal_to_value)
#define __PRIVATE_futexlock_waituntil_3(ulockaddr, uaddr, not_equal_to_value, rel_timeout)           futexlock_timedwaituntil(ulockaddr, uaddr, not_equal_to_value, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_equal_2(ulockaddr, uaddr, equal_to_value)                      futexlock_waitwhile_equal(ulockaddr, uaddr, equal_to_value)
#define __PRIVATE_futexlock_waitwhile_equal_3(ulockaddr, uaddr, equal_to_value, rel_timeout)         futexlock_timedwaitwhile_equal(ulockaddr, uaddr, equal_to_value, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_notequal_2(ulockaddr, uaddr, not_equal_to_value)               futexlock_waitwhile_notequal(ulockaddr, uaddr, not_equal_to_value)
#define __PRIVATE_futexlock_waitwhile_notequal_3(ulockaddr, uaddr, not_equal_to_value, rel_timeout)  futexlock_timedwaitwhile_notequal(ulockaddr, uaddr, not_equal_to_value, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_above_2(ulockaddr, uaddr, above_value)                         futexlock_waitwhile_above(ulockaddr, uaddr, above_value)
#define __PRIVATE_futexlock_waitwhile_above_3(ulockaddr, uaddr, above_value, rel_timeout)            futexlock_timedwaitwhile_above(ulockaddr, uaddr, above_value, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_below_2(ulockaddr, uaddr, below_value)                         futexlock_waitwhile_below(ulockaddr, uaddr, below_value)
#define __PRIVATE_futexlock_waitwhile_below_3(ulockaddr, uaddr, below_value, rel_timeout)            futexlock_timedwaitwhile_below(ulockaddr, uaddr, below_value, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_aboveequal_2(ulockaddr, uaddr, above_equal_value)              futexlock_waitwhile_aboveequal(ulockaddr, uaddr, above_equal_value)
#define __PRIVATE_futexlock_waitwhile_aboveequal_3(ulockaddr, uaddr, above_equal_value, rel_timeout) futexlock_timedwaitwhile_aboveequal(ulockaddr, uaddr, above_equal_value, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_belowequal_2(ulockaddr, uaddr, below_equal_value)              futexlock_waitwhile_belowequal(ulockaddr, uaddr, below_equal_value)
#define __PRIVATE_futexlock_waitwhile_belowequal_3(ulockaddr, uaddr, below_equal_value, rel_timeout) futexlock_timedwaitwhile_belowequal(ulockaddr, uaddr, below_equal_value, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_cmpxch_3(ulockaddr, uaddr, old_value, new_value)               futexlock_waitwhile_cmpxch(ulockaddr, uaddr, old_value, new_value)
#define __PRIVATE_futexlock_waitwhile_cmpxch_4(ulockaddr, uaddr, old_value, new_value, rel_timeout)  futexlock_timedwaitwhile_cmpxch(ulockaddr, uaddr, old_value, new_value, rel_timeout)
#define __PRIVATE_futexlock_waituntil_cmpxch_3(ulockaddr, uaddr, old_value, new_value)               futexlock_waituntil_cmpxch(ulockaddr, uaddr, old_value, new_value)
#define __PRIVATE_futexlock_waituntil_cmpxch_4(ulockaddr, uaddr, old_value, new_value, rel_timeout)  futexlock_timedwaituntil_cmpxch(ulockaddr, uaddr, old_value, new_value, rel_timeout)
#define __PRIVATE_futexlock_waitlock_1(ulockaddr, uaddr)                                             futexlock_waitlock(ulockaddr, uaddr)
#define __PRIVATE_futexlock_waitlock_2(ulockaddr, uaddr, rel_timeout)                                futexlock_timedwaitlock(ulockaddr, uaddr, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_exactbits_3(ulockaddr, uaddr, bitmask, setmask)                futexlock_waitwhile_exactbits(ulockaddr, uaddr, bitmask, setmask)
#define __PRIVATE_futexlock_waitwhile_exactbits_4(ulockaddr, uaddr, bitmask, setmask, rel_timeout)   futexlock_timedwaitwhile_exactbits(ulockaddr, uaddr, bitmask, setmask, rel_timeout)
#define __PRIVATE_futexlock_waituntil_exactbits_3(ulockaddr, uaddr, bitmask, setmask)                futexlock_waituntil_exactbits(ulockaddr, uaddr, bitmask, setmask)
#define __PRIVATE_futexlock_waituntil_exactbits_4(ulockaddr, uaddr, bitmask, setmask, rel_timeout)   futexlock_timedwaituntil_exactbits(ulockaddr, uaddr, bitmask, setmask, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_anybit_2(ulockaddr, uaddr, bitmask)                            futexlock_waitwhile_anybit(ulockaddr, uaddr, bitmask)
#define __PRIVATE_futexlock_waitwhile_anybit_3(ulockaddr, uaddr, bitmask, rel_timeout)               futexlock_timedwaitwhile_anybit(ulockaddr, uaddr, bitmask, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_allbits_2(ulockaddr, uaddr, bitmask)                           futexlock_waitwhile_allbits(ulockaddr, uaddr, bitmask)
#define __PRIVATE_futexlock_waitwhile_allbits_3(ulockaddr, uaddr, bitmask, rel_timeout)              futexlock_timedwaitwhile_allbits(ulockaddr, uaddr, bitmask, rel_timeout)
#define futexlock_waitwhile(...)                      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waituntil(...)                      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waituntil_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_equal(...)                __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_equal_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_notequal(...)             __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_notequal_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_above(...)                __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_above_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_below(...)                __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_below_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_aboveequal(...)           __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_aboveequal_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_belowequal(...)           __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_belowequal_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_cmpxch(...)               __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_cmpxch_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waituntil_cmpxch(...)               __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waituntil_cmpxch_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitlock(...)                       __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitlock_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitlock(...)                       __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitlock_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_exactbits(...)            __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_exactbits_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waituntil_exactbits(...)            __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waituntil_exactbits_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_anybit(...)               __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_anybit_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_allbits(...)              __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_allbits_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* !__cplusplus */


#endif /* __CC__ */

__SYSDECL_END

#endif /* !_KOS_FUTEXLOCK_H */
