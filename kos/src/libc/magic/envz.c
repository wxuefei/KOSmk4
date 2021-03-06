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

%[default:section(".text.crt{|.dos}.string.envz")]

%{
#include <features.h>
#include <bits/types.h>
#include <argz.h>

/* Documentation is derived from GLibc: /usr/include/envz.h */
/* Routines for dealing with '\0' separated environment vectors
   Copyright (C) 1995-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__SYSDECL_BEGIN

#ifdef __CC__

}

%[define_replacement(error_t = __errno_t)]


@@Returns a pointer to the entry in `ENVZ' for `NAME', or `NULL' if there is none
@@Note that if `name' contains a `=' character, only characters leading up to this
@@position are actually compared!
[[wunused, ATTR_PURE, decl_include("<hybrid/typecore.h>")]]
char *envz_entry([inp_opt(envz_len)] char const *__restrict envz, size_t envz_len, [[nonnull]] char const *__restrict name)
	[([inp_opt(envz_len)] char *__restrict envz, size_t envz_len, [[nonnull]] char const *__restrict name): char *]
	[([inp_opt(envz_len)] char const *__restrict envz, size_t envz_len, [[nonnull]] char const *__restrict name): char const *]
{
	size_t namelen;
	char *envz_end = (char *)(envz + envz_len);
	namelen = stroff(name, '=');
	while (envz < envz_end) {
		if (memcmp(envz, name, namelen) == 0 &&
		    (envz[namelen] == '\0' || envz[namelen] == '='))
			return (char *)envz; /* Found it! */
		envz = strend(envz) + 1;
	}
	return NULL;
}

@@Returns a pointer to the value portion of the entry
@@in `ENVZ' for `NAME', or `NULL' if there is none.
[[wunused, ATTR_PURE, decl_include("<hybrid/typecore.h>")]]
char *envz_get([inp_opt(envz_len)] char const *__restrict envz, size_t envz_len, [[nonnull]] char const *__restrict name)
	[([inp_opt(envz_len)] char *__restrict envz, size_t envz_len, [[nonnull]] char const *__restrict name): char *]
	[([inp_opt(envz_len)] char const *__restrict envz, size_t envz_len, [[nonnull]] char const *__restrict name): char const *]
{
	char *result;
	result = (char *)envz_entry(envz, envz_len, name);
	if (result) {
		result = strchr(result, '=');
		if (result)
			++result; /* Point to the value-portion */
	}
	return result;
}

@@Adds an entry for `NAME' with value `VALUE' to `ENVZ & ENVZ_LEN'. If an entry
@@with the same name already exists in `ENVZ', it is removed. If `VALUE' is
@@`NULL', then the new entry will not have a value portion, meaning that `envz_get()'
@@will return `NULL', although `envz_entry()' will still return an entry. This is handy
@@because when merging with another envz, the null entry can override an
@@entry in the other one. Such entries can be removed with `envz_strip()'
[[impl_include("<parts/errno.h>"), decl_include("<hybrid/typecore.h>")]]
[[requires_function(realloc, argz_add)]]
error_t envz_add([[nonnull]] char **__restrict penvz,
                 [[nonnull]] size_t *__restrict penvz_len,
                 [[nonnull]] char const *__restrict name,
                 [[nullable]] char const *value) {
	char *new_envz;
	size_t namelen, valuelen, morelen;
	envz_remove(penvz, penvz_len, name);
	if (!value)
		return argz_add(penvz, penvz_len, name);
	/* Append a new string `name=value\0' */
	namelen  = strlen(name);
	valuelen = strlen(value);
	morelen  = namelen + 1 + valuelen + 1;
	new_envz = (char *)realloc(*penvz, (*penvz_len + morelen) * sizeof(char));
	if unlikely(!new_envz) {
@@pp_ifdef ENOMEM@@
		return ENOMEM;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	*penvz = new_envz;
	new_envz += *penvz_len;
	*penvz_len += morelen;
	new_envz = (char *)mempcpyc(new_envz, name, namelen, sizeof(char));
	*new_envz++ = '=';
	new_envz = (char *)mempcpyc(new_envz, value, valuelen, sizeof(char));
	*new_envz = '\0';
	return 0;
}

@@Adds each entry in `ENVZ2' to `ENVZ & ENVZ_LEN', as if with `envz_add()'.
@@If `OVERRIDE' is true, then values in `ENVZ2' will supersede those
@@with the same name in `ENV', otherwise they don't
[[requires_function(argz_append), decl_include("<hybrid/typecore.h>")]]
error_t envz_merge([[nonnull]] char **__restrict penvz,
                   [[nonnull]] size_t *__restrict penvz_len,
                   [[nonnull]] char const *__restrict envz2,
                   size_t envz2_len, int override_) {
	error_t result = 0;
	while (envz2_len && result == 0) {
		char *existing = envz_entry(*penvz, *penvz_len, envz2);
		size_t newlen  = strlen(envz2) + 1;
		if (!existing)
			result = argz_append(penvz, penvz_len, envz2, newlen);
		else if (override_) {
			argz_delete(penvz, penvz_len, existing);
			result = argz_append(penvz, penvz_len, envz2, newlen);
		}
		envz2     += newlen;
		envz2_len -= newlen;
	}
	return result;
}

@@Remove the entry for `NAME' from `ENVZ & ENVZ_LEN', if any
[[decl_include("<hybrid/typecore.h>")]]
void envz_remove([[nonnull]] char **__restrict penvz,
                 [[nonnull]] size_t *__restrict penvz_len,
                 [[nonnull]] char const *__restrict name) {
	char *entry;
	entry = envz_entry(*penvz, *penvz_len, name);
	if (entry)
		argz_delete(penvz, penvz_len, entry);
}


@@Remove entries that have no value attached
[[decl_include("<hybrid/typecore.h>")]]
void envz_strip([[nonnull]] char **__restrict penvz,
                [[nonnull]] size_t *__restrict penvz_len) {
	char *start, *ptr, *end;
	size_t oldlen, newlen;
	ptr = start = *penvz;
	end = ptr + (oldlen = *penvz_len);
	while (ptr < end) {
		char *next;
		size_t partlen;
		next = strchrnul(ptr, '=');
		if (*next) {
			ptr = strend(next) + 1;
			continue;
		}
		/* Remove this entry. */
		next = strend(next) + 1;
		partlen = (size_t)(end - next);
		memmovedownc(ptr, next, partlen, sizeof(char));
		end -= partlen;
	}
	newlen = (size_t)(end - start);
	if (newlen < oldlen) {
		*penvz_len = newlen;
@@pp_if $has_function(realloc)@@
		start = (char *)realloc(start, newlen);
		if likely(start)
			*penvz = start;
@@pp_endif@@
	}
}


%{

#endif /* __CC__ */

__SYSDECL_END

}