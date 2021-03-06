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

%[default:section(".text.crt{|.dos}.utility.monetary")]


%{
#include <features.h>
#include <bits/types.h>
#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __ssize_t_defined
#define __ssize_t_defined 1
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

}

[[ATTR_LIBC_STRFMON(3, 4)]]
ssize_t strfmon([[nonnull]] char *__restrict s, size_t maxsize,
                [[nonnull]] char const *__restrict format, ...);

%#ifdef __USE_XOPEN2K8
[[ATTR_LIBC_STRFMON(4, 5), export_alias("__strfmon_l")]]
ssize_t strfmon_l([[nonnull]] char *__restrict s, size_t maxsize, $locale_t loc,
                  [[nonnull]] const char *__restrict format, ...);
%#endif /* __USE_XOPEN2K8 */


%{
#endif /* __CC__ */

__SYSDECL_END

}