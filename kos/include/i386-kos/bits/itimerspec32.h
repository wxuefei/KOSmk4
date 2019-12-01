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
#ifndef _I386_KOS_BITS_ITIMERSPEC32_H
#define _I386_KOS_BITS_ITIMERSPEC32_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include "timespec32.h"

#ifdef __x86_64__
#define itimerspecx32    __itimerspecx32
#define itimerspecx32_64 __itimerspecx32_64
#else /* __x86_64__ */
#include <features.h>
#ifdef __USE_TIME_BITS64
/* Configure:
 *   - `itimerspecx32_64' as `itimerspec'
 *   - `itimerspecx32' as `__itimerspec32' */

#define itimerspecx32      __itimerspec32
#define itimerspecx32_64   itimerspec
#define __itimerspecx32    __itimerspec32
#define __itimerspecx32_64 itimerspec
#define __itimerspec32     __itimerspec32
#define __itimerspec64     itimerspec
#define __itimerspec_alt   __itimerspec32
#ifdef __USE_KOS
#define itimerspec32       __itimerspec32
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#define itimerspec64       itimerspec
#endif /* __USE_TIME64 */

#define __OFFSET_ITIMERSPEC_INTERVAL   __OFFSET_ITIMERSPECX32_64_INTERVAL
#define __OFFSET_ITIMERSPEC_VALUE      __OFFSET_ITIMERSPECX32_64_VALUE
#define __SIZEOF_ITIMERSPEC            __SIZEOF_ITIMERSPECX32_64
#define __OFFSET_ITIMERSPEC64_INTERVAL __OFFSET_ITIMERSPECX32_64_INTERVAL
#define __OFFSET_ITIMERSPEC64_VALUE    __OFFSET_ITIMERSPECX32_64_VALUE
#define __SIZEOF_ITIMERSPEC64          __SIZEOF_ITIMERSPECX32_64

#else /* __USE_TIME_BITS64 */
/* Configure:
 *   - `itimerspecx32_64' as `itimerspec64' or `__itimerspec64'
 *   - `itimerspecx32' as `itimerspec' */
#define itimerspecx32      itimerspec
#define __itimerspec32     itimerspec
#define __itimerspecx32    itimerspec
#ifdef __USE_TIME64
#define __itimerspecx32_64 itimerspec64
#define itimerspecx32_64   itimerspec64
#define __itimerspec64     itimerspec64
#define __itimerspec_alt   itimerspec64
#else /* __USE_TIME64 */
#define __itimerspecx32_64 __itimerspec64
#define itimerspecx32_64   __itimerspec64
#define __itimerspec64     __itimerspec64
#define __itimerspec_alt   __itimerspec64
#endif /* __USE_TIME64 */
#ifdef __USE_KOS
#define itimerspec32       itimerspec
#endif /* __USE_KOS */

#define __OFFSET_ITIMERSPEC_INTERVAL   __OFFSET_ITIMERSPECX32_INTERVAL
#define __OFFSET_ITIMERSPEC_VALUE      __OFFSET_ITIMERSPECX32_VALUE
#define __SIZEOF_ITIMERSPEC            __SIZEOF_ITIMERSPECX32
#define __OFFSET_ITIMERSPEC64_INTERVAL __OFFSET_ITIMERSPECX32_64_INTERVAL
#define __OFFSET_ITIMERSPEC64_VALUE    __OFFSET_ITIMERSPECX32_64_VALUE
#define __SIZEOF_ITIMERSPEC64          __SIZEOF_ITIMERSPECX32_64

#endif /* !__USE_TIME_BITS64 */
#define __itimerspec_defined 1
#endif /* !__x86_64__ */


#define __OFFSET_ITIMERSPECX32_INTERVAL    0
#define __OFFSET_ITIMERSPECX32_VALUE       8
#define __SIZEOF_ITIMERSPECX32             16
#define __OFFSET_ITIMERSPECX32_64_INTERVAL 0
#define __OFFSET_ITIMERSPECX32_64_VALUE    16
#define __SIZEOF_ITIMERSPECX32_64          32

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("it_interval")
#pragma push_macro("it_value")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef it_interval
#undef it_value

/* 32-bit itimerspec for i386 */
struct itimerspecx32 /*[PREFIX(it_)]*/ {
	struct __timespecx32 it_interval;
	struct __timespecx32 it_value;
};

/* 64-bit itimerspec for i386 */
struct itimerspecx32_64 /*[PREFIX(it_)]*/ {
	struct __timespecx32_64 it_interval;
	struct __timespecx32_64 it_value;
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("it_value")
#pragma pop_macro("it_interval")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS
#undef itimerspecx32
#undef itimerspecx32_64
#endif /* !__USE_KOS */

#endif /* !_I386_KOS_BITS_ITIMERSPEC32_H */