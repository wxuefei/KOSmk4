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


%[default:section(".text.crt{|.dos}.system.reboot")]

%{
#include <features.h>
#include <asm/reboot.h>

__SYSDECL_BEGIN

/* Linux compatibility header */
#ifdef __RB_AUTOBOOT
#define RB_AUTOBOOT __RB_AUTOBOOT /* Do a hard reset immediately. */
#endif /* __RB_AUTOBOOT */
#ifdef __RB_HALT_SYSTEM
#define RB_HALT_SYSTEM __RB_HALT_SYSTEM /* Halt the system. */
#endif /* __RB_HALT_SYSTEM */
#ifdef __RB_ENABLE_CAD
#define RB_ENABLE_CAD __RB_ENABLE_CAD /* Enable reboot with Ctrl-Alt-Delete. */
#endif /* __RB_ENABLE_CAD */
#ifdef __RB_DISABLE_CAD
#define RB_DISABLE_CAD __RB_DISABLE_CAD /* Disable reboot with Ctrl-Alt-Delete. */
#endif /* __RB_DISABLE_CAD */
#ifdef __RB_POWER_OFF
#define RB_POWER_OFF __RB_POWER_OFF /* halt and switch off power (if possible). */
#endif /* __RB_POWER_OFF */
#ifdef __RB_SW_SUSPEND
#define RB_SW_SUSPEND __RB_SW_SUSPEND /* Suspend the system using a software suspend. */
#endif /* __RB_SW_SUSPEND */
#ifdef __RB_KEXEC
#define RB_KEXEC __RB_KEXEC /* Reboot into new kernel (not supported currently). */
#endif /* __RB_KEXEC */

#ifdef __CC__

}

@@Reboot or halt the system
@@@param: howto: One of the `RB_*' constants above
[[decl_include("<features.h>")]]
int reboot(__STDC_INT_AS_UINT_T howto);

%{

#endif /* __CC__ */

__SYSDECL_END

}