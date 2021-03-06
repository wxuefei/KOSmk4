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
#ifndef GUARD_LIBC_USER_SYS_AUXV_C
#define GUARD_LIBC_USER_SYS_AUXV_C 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <asm/pagesize.h>  /* __ARCH_PAGESIZE */
#include <kos/exec/elf.h>  /* ELF_ARCH_DATA */
#include <kos/exec/rtld.h> /* RTLD_PLATFORM */

#include <stddef.h> /* offsetafter */
#include <time.h>   /* CLK_TCK */
#include <unistd.h> /* preadall */

#include "../libc/dl.h"
#include "sys.auxv.h"

#if defined(__i386__) && !defined(__x86_64__)
#include <kos/syscalls.h> /* sys_uname() */
#include <sys/utsname.h>  /* uname */

#include <string.h> /* preadall */
#endif /* __i386__ && !__x86_64__ */

DECL_BEGIN

PRIVATE ATTR_SECTION(".rodata.crt.system.getauxval") char const
rtld_platform[] = RTLD_PLATFORM;

#ifdef __ARCH_PAGESIZE
#define OS_PAGESIZE __ARCH_PAGESIZE
#else /* __ARCH_PAGESIZE */
#define OS_PAGESIZE getpagesize()
#endif /* !__ARCH_PAGESIZE */


#if defined(__i386__) && !defined(__x86_64__)
PRIVATE ATTR_SECTION(".rodata.crt.system.getauxval") char const
elf_host_platform_string_x86_64[] = "x86_64";

/* Check if the kernel is running in 64-bit mode */
PRIVATE bool LIBCCALL libc_has_kernel64(void) {
	struct utsname uname;
	errno_t error;
	error = sys_uname(&uname);
	if unlikely(E_ISERR(error))
		return false; /* Shouldn't happen... */
	if (strcmp(uname.machine, elf_host_platform_string_x86_64) == 0)
		return true; /* Yup. It's an x86_64-kernel. */
	return false;
}
#endif /* __i386__ && !__x86_64__ */




/*[[[start:implementation]]]*/

/*[[[head:libc_getauxval,hash:CRC-32=0x71fb96a6]]]*/
/* Return the value associated with an Elf*_auxv_t type from the auxv list
 * passed to the program on startup.  If TYPE was not present in the auxv
 * list, returns zero and sets errno to ENOENT */
INTERN ATTR_SECTION(".text.crt.system.auxv") ulongptr_t
NOTHROW_NCX(LIBCCALL libc_getauxval)(ulongptr_t type)
/*[[[body:libc_getauxval]]]*/
{
	ulongptr_t result;
	switch (type) {
	case AT_IGNORE:
		result = 0;
		break;

	case AT_EXECFD:
		result = dlmodulefd(dlopen(NULL, 0));
		break;

	case AT_PHDR:
		result = (ulongptr_t)dlauxctrl(NULL, DLAUXCTRL_ELF_GET_PHDR, NULL, NULL);
		break;

	case AT_PHENT:
		result = sizeof(ElfW(Phdr));
		break;

	case AT_PHNUM: {
		size_t count;
		if (!dlauxctrl(NULL, DLAUXCTRL_ELF_GET_PHDR, NULL, &count))
			count = 0;
		result = (ulongptr_t)count;
	}	break;

	case AT_PAGESZ:
		result = OS_PAGESIZE;
		break;

	case AT_BASE: {
		void *libdl;
		libdl  = dlgetmodule("libdl", DLGETHANDLE_FNORMAL);
		result = (ulongptr_t)dlmodulebase(libdl);
	}	break;

	case AT_FLAGS: {
		ElfW(Dyn) *dyn;
		size_t i, dynum;
		dyn = (ElfW(Dyn) *)dlauxctrl(NULL, DLAUXCTRL_ELF_GET_DYN, NULL, &dynum);
		result = 0;
		for (i = 0; i < dynum; ++i) {
			if (dyn[i].d_tag != DT_FLAGS)
				continue;
			result = dyn[i].d_un.d_val;
			break;
		}
	}	break;

	case AT_ENTRY: {
		fd_t rootfd;
		byte_t ehdr_data[offsetafter(ElfW(Ehdr), e_entry)];
		ElfW(Ehdr) *ehdr = (ElfW(Ehdr) *)ehdr_data;
		rootfd = dlmodulefd(dlopen(NULL, 0));
		if (preadall(rootfd, ehdr_data, sizeof(ehdr_data), 0) < (ssize_t)sizeof(ehdr_data))
			goto not_found;
		if (ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
		    ehdr->e_ident[EI_MAG1] != ELFMAG1 ||
		    ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
		    ehdr->e_ident[EI_MAG3] != ELFMAG3)
			goto not_found;
		if unlikely(ehdr->e_ident[EI_CLASS] != ELF_ARCH_CLASS)
			goto not_found;
		if unlikely(ehdr->e_ident[EI_DATA] != ELF_ARCH_CLASS)
			goto not_found;
		if unlikely(ehdr->e_ident[EI_VERSION] != EV_CURRENT)
			goto not_found;
		if unlikely(ehdr->e_version != EV_CURRENT)
			goto not_found;
		if unlikely(ehdr->e_type != ET_EXEC)
			goto not_found;
		if unlikely(ehdr->e_machine != ELF_ARCH_MACHINE)
			goto not_found;
		result = ehdr->e_entry;
	}	break;

	case AT_NOTELF: {
		/* Check if the main executable image is an ELF image.
		 * If so, the we don't know the `AT_NOTELF' key.
		 * Otherwise, the `AT_NOTELF' key has a value of `1' */
		if (dlauxctrl(dlopen(NULL, 0), DLAUXCTRL_ELF_CHECK))
			goto not_found;
		result = 1;
	}	break;

	case AT_UID:
		result = getuid();
		break;

	case AT_EUID:
		result = geteuid();
		break;

	case AT_GID:
		result = getgid();
		break;

	case AT_EGID:
		result = getegid();
		break;

	case AT_CLKTCK:
		result = CLK_TCK;
		break;

	case AT_BASE_PLATFORM:
#if defined(__i386__) && !defined(__x86_64__)
		/* Special case: On i386, we may be running in compatibility mode. */
		if (libc_has_kernel64()) {
			result = (ulongptr_t)(void *)elf_host_platform_string_x86_64;
			break;
		}
		ATTR_FALLTHROUGH
#endif /* __i386__ && !__x86_64__ */

	case AT_PLATFORM:
		result = (ulongptr_t)(void *)rtld_platform;
		break;

	default:
not_found:
		libc_seterrno(ENOENT);
		result = 0;
		break;
	}
	return result;
}
/*[[[end:libc_getauxval]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x9d59b425]]]*/
DEFINE_PUBLIC_ALIAS(__getauxval, libc_getauxval);
DEFINE_PUBLIC_ALIAS(getauxval, libc_getauxval);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_AUXV_C */
