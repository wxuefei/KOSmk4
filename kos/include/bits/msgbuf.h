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
#ifndef _BITS_MSGBUF_H
#define _BITS_MSGBUF_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

/* Template for struct to be used as argument for `msgsnd' and `msgrcv'.  */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("mtype")
#pragma push_macro("mtext")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef mtype
#undef mtext

struct msgbuf {
	__syscall_slong_t               mtype;    /* type of received/sent message */
#ifdef __USE_KOS
	__COMPILER_FLEXIBLE_ARRAY(char, mtext);   /* text of the message */
#else /* __USE_KOS */
	char                            mtext[1]; /* text of the message */
#endif /* !__USE_KOS */
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("mtext")
#pragma pop_macro("mtype")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* _BITS_MSGBUF_H */
