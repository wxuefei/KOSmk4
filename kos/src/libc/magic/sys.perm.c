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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(ulongptr_t = __ULONGPTR_TYPE__)]
%[default_impl_section(.text.crt.system.ioperm)]

%{
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#ifdef __CC__
}

@@Change I/O port permissions for a specific I/O port range
ioperm:($ulongptr_t from, $ulongptr_t num, int turn_on) -> int;

@@Change I/O port permissions for all I/O ports
iopl:(int level) -> int;

%{
#endif /* __CC__ */

__SYSDECL_END

}