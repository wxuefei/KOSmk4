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
#ifndef _I386_KOS_KOS_KERNEL_CPU_STATE_HELPERS32_H
#define _I386_KOS_KOS_KERNEL_CPU_STATE_HELPERS32_H 1

#include <hybrid/__assert.h>
#include <hybrid/host.h>

#include <asm/intrin.h>
#include <bits/types.h>
#include <kos/anno.h>
#include <kos/kernel/gdt.h>

#include <libc/string.h>

#include "cpu-state32.h"

#if defined(__KERNEL__) && !defined(__x86_64__)
#include <sched/arch/task.h>
#endif /* __KERNEL__ && !__x86_64__ */

#if defined(__i386__) && !defined(__x86_64__)
#include <hybrid/__asm.h>
/* TODO: CFI helpers */
#endif /* __i386__ && !__x86_64 */

#ifdef __CC__
__DECL_BEGIN

/************************************************************************/
/* `struct gpregs32'                                                    */
/************************************************************************/
#define gpregs32_getedi(self)        ((__u32)(self)->gp_edi)
#define gpregs32_setedi(self, value) ((self)->gp_edi = (value))
#define gpregs32_getesi(self)        ((__u32)(self)->gp_esi)
#define gpregs32_setesi(self, value) ((self)->gp_esi = (value))
#define gpregs32_getebp(self)        ((__u32)(self)->gp_ebp)
#define gpregs32_setebp(self, value) ((self)->gp_ebp = (value))
#define gpregs32_getesp(self)        ((__u32)(self)->gp_esp)
#define gpregs32_setesp(self, value) ((self)->gp_esp = (value))
#define gpregs32_getebx(self)        ((__u32)(self)->gp_ebx)
#define gpregs32_setebx(self, value) ((self)->gp_ebx = (value))
#define gpregs32_getedx(self)        ((__u32)(self)->gp_edx)
#define gpregs32_setedx(self, value) ((self)->gp_edx = (value))
#define gpregs32_getecx(self)        ((__u32)(self)->gp_ecx)
#define gpregs32_setecx(self, value) ((self)->gp_ecx = (value))
#define gpregs32_geteax(self)        ((__u32)(self)->gp_eax)
#define gpregs32_seteax(self, value) ((self)->gp_eax = (value))
#define gpregs32_to_gpregs32(self, result)                           \
	__libc_memcpy(__COMPILER_REQTYPE(struct gpregs32 *, result),     \
	              __COMPILER_REQTYPE(struct gpregs32 const *, self), \
	              sizeof(struct gpregs32))
/************************************************************************/




/************************************************************************/
/* `struct irregs32'                                                    */
/************************************************************************/
#if defined(__KERNEL__) && !defined(__x86_64__)
#define irregs32_isvm86(self)            (irregs_isvm86)((struct irregs_kernel const *)(self))
#define irregs32_isuser(self)            (irregs_isuser)((struct irregs_kernel const *)(self))
#define irregs32_isuser_novm86(self)     (irregs_isuser_novm86)((struct irregs_kernel const *)(self))
#define irregs32_iskernel(self)          (!(irregs_isuser)((struct irregs_kernel const *)(self)))
#define irregs32_geteip(self)            (irregs_rdip)((struct irregs_kernel const *)(self))
#define irregs32_seteip(self, value)     (irregs_wrip)((struct irregs_kernel *)(self), value)
#define irregs32_getcs(self)             (irregs_rdcs)((struct irregs_kernel const *)(self))
#define irregs32_setcs(self, value)      (irregs_wrcs)((struct irregs_kernel *)(self), value)
#define irregs32_geteflags(self)         (irregs_rdflags)((struct irregs_kernel const *)(self))
#define irregs32_seteflags(self, value)  (irregs_wrflags)((struct irregs_kernel *)(self), value)
#define irregs32_mskeflags(self, mask, flags) (irregs_mskflags)((struct irregs_kernel *)(self), mask, flags)
#define irregs32_getesp(self)            (irregs_rdsp)((struct irregs_kernel const *)(self))
#else /* __KERNEL__ && !__x86_64__ */
#define irregs32_isvm86(self)            ((self)->ir_eflags & 0x20000)
#define irregs32_isuser_novm86(self)     ((self)->ir_cs16 & 3)
#define irregs32_isuser(self)            (((self)->ir_cs16 & 3) || irregs32_isvm86(self))
#define irregs32_iskernel(self)          (!((self)->ir_cs16 & 3) && !irregs32_isvm86(self))
#define irregs32_geteip(self)            ((__u32)(self)->ir_eip)
#define irregs32_seteip(self, value)     ((self)->ir_eip = (value))
#define irregs32_getcs(self)             ((__u16)(self)->ir_cs16)
#define irregs32_setcs(self, value)      ((self)->ir_cs = (value))
#define irregs32_geteflags(self)         ((__u32)(self)->ir_eflags)
#define irregs32_seteflags(self, value)  ((self)->ir_eflags = (value))
#define irregs32_mskeflags(self, mask, flags) ((self)->ir_eflags = ((self)->ir_eflags & (mask)) | (flags))
#define irregs32_getesp(self)            (irregs32_isuser(self) ? irregs32_getuseresp(self) : irregs32_getkernelesp(self))
#endif /* !__KERNEL__ || __x86_64__ */
#define irregs32_getuseresp(self)        ((struct irregs32_user const *)(self))->ir_esp
#define irregs32_setuseresp(self, value) (((struct irregs32_user *)(self))->ir_esp=(value))
#define irregs32_getuserss(self)         ((struct irregs32_user const *)(self))->ir_ss16
#define irregs32_setuserss(self, value)  (((struct irregs32_user *)(self))->ir_ss=(value))
#define irregs32_getkernelesp(self)      ((__u32)((__uintptr_t)(self) + SIZEOF_IRREGS32_KERNEL))
#define irregs32_getkernelss(self)       SEGMENT_KERNEL_DATA
#define irregs32_getss(self)             (irregs32_isuser(self) ? irregs32_getuserss(self) : irregs32_getkernelss(self))
#define irregs32_trysetesp(self, value)  (irregs32_isuser(self) ? (irregs32_setuseresp(self, value), 1) : (irregs32_getkernelesp(self) == (value)))
#define irregs32_trysetss(self, value)   (irregs32_isuser(self) ? (irregs32_setuserss(self, value), 1) : (irregs32_getkernelss(self) == (value)))

/* Returns the total size of the given CPU state. */
#define irregs32_sizeof(self) \
	(irregs32_isvm86(self)    \
	 ? SIZEOF_IRREGS32_VM86   \
	 : ((self)->ir_cs16 & 3)  \
	   ? SIZEOF_IRREGS32_USER \
	   : SIZEOF_IRREGS32_KERNEL)
/************************************************************************/




/************************************************************************/
/* `struct lcpustate32'                                                 */
/************************************************************************/
#define lcpustate32_geteip(self)        ((__u32)(self)->lcs_eip)
#define lcpustate32_seteip(self, value) ((self)->lcs_eip = (value))
#define lcpustate32_getesp(self)        ((__u32)(self)->lcs_esp)
#define lcpustate32_setesp(self, value) ((self)->lcs_esp = (value))
#define lcpustate32_to_lcpustate32(self, result)                        \
	__libc_memcpy(__COMPILER_REQTYPE(struct lcpustate32 *, result),     \
	              __COMPILER_REQTYPE(struct lcpustate32 const *, self), \
	              sizeof(struct lcpustate32))
#ifndef __x86_64__
__FORCELOCAL void __FCALL lcpustate32_current(struct lcpustate32 *__restrict __result) {
	__asm__("movl %%edi, %0\n\t"
			"movl %%esi, %1\n\t"
			"movl %%ebp, %2\n\t"
			"movl %%esp, %3\n\t"
			"movl %%ebx, %4\n\t"
#if (defined(__pic__) || defined(__PIC__) || \
     defined(__pie__) || defined(__PIE__)) && 0
			"call 991f\n\t"
			"991: .cfi_adjust_cfa_offset 4\n\t"
			"popl %5\n\t"
			".cfi_adjust_cfa_offset -4"
#else
			"movl $991f, %5\n\t"
			"991:"
#endif
			: "=m" (__result->lcs_edi)
			, "=m" (__result->lcs_esi)
			, "=m" (__result->lcs_ebp)
			, "=m" (__result->lcs_esp)
			, "=m" (__result->lcs_ebx)
			, "=m" (__result->lcs_eip));
}
#endif /* !__x86_64__ */
__LOCAL __NOBLOCK void
__NOTHROW_NCX(lcpustate32_to_gpregs32_ex)(struct lcpustate32 const *__restrict __self,
                                          struct gpregs32 *__restrict __result,
                                          __u32 __v_edx, __u32 __v_ecx, __u32 __v_eax) {
	__result->gp_edi = __self->lcs_edi;
	__result->gp_esi = __self->lcs_esi;
	__result->gp_ebp = __self->lcs_ebp;
	__result->gp_esp = __self->lcs_esp;
	__result->gp_ebx = __self->lcs_ebx;
	__result->gp_edx = __v_edx;
	__result->gp_ecx = __v_ecx;
	__result->gp_eax = __v_eax;
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(lcpustate32_to_gpregs32)(struct lcpustate32 const *__restrict __self,
                                       struct gpregs32 *__restrict __result) {
	lcpustate32_to_gpregs32_ex(__self, __result, 0, 0, 0);
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(lcpustate32_to_ucpustate32_ex)(struct lcpustate32 const *__restrict __self,
                                             struct ucpustate32 *__restrict __result,
                                             __u32 __v_edx, __u32 __v_ecx, __u32 __v_eax,
                                             __u16 __v_gs, __u16 __v_fs, __u16 __v_es, __u16 __v_ds,
                                             __u16 __v_cs, __u16 __v_ss, __u32 __v_eflags) {
	lcpustate32_to_gpregs32_ex(__self, &__result->ucs_gpregs, __v_edx, __v_ecx, __v_eax);
	__result->ucs_sgregs.sg_gs  = __v_gs;
	__result->ucs_sgregs.sg_fs  = __v_fs;
	__result->ucs_sgregs.sg_es  = __v_es;
	__result->ucs_sgregs.sg_ds  = __v_ds;
	__result->ucs_cs            = __v_cs;
	__result->ucs_ss            = __v_ss;
	__result->ucs_eflags        = __v_eflags;
	__result->ucs_eip           = __self->lcs_eip;
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(lcpustate32_to_ucpustate32)(struct lcpustate32 const *__restrict __self,
                                          struct ucpustate32 *__restrict __result) {
	lcpustate32_to_ucpustate32_ex(__self, __result, 0, 0, 0,
	                              __rdgs(),
#if defined(__KERNEL__) && !defined(__x86_64__)
	                              SEGMENT_KERNEL_FSBASE,
	                              SEGMENT_USER_DATA_RPL,
	                              SEGMENT_USER_DATA_RPL,
#else /* __KERNEL__ && !__x86_64__ */
	                              __rdfs(), __rdes(), __rdds(),
#endif /* !__KERNEL__ || __x86_64__ */
	                              SEGMENT_CURRENT_CODE_RPL,
	                              SEGMENT_CURRENT_DATA_RPL,
	                              (__u32)__rdflags());
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(lcpustate32_to_kcpustate32_ex)(struct lcpustate32 const *__restrict __self,
                                             struct kcpustate32 *__restrict __result,
                                             __u32 __v_edx, __u32 __v_ecx, __u32 __v_eax,
                                             __u32 __v_eflags) {
	lcpustate32_to_gpregs32_ex(__self, &__result->kcs_gpregs, __v_edx, __v_ecx, __v_eax);
	__result->kcs_eflags = __v_eflags;
	__result->kcs_eip    = __self->lcs_eip;
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(lcpustate32_to_kcpustate32)(struct lcpustate32 const *__restrict __self,
                                          struct kcpustate32 *__restrict __result) {
	lcpustate32_to_kcpustate32_ex(__self, __result, 0, 0, 0, (__u32)__rdflags());
}
/************************************************************************/




/************************************************************************/
/* `struct kcpustate32'                                                 */
/************************************************************************/
#define kcpustate32_geteip(self)           ((__u32)(self)->kcs_eip)
#define kcpustate32_seteip(self, value)    ((self)->kcs_eip = (value))
#define kcpustate32_getesp(self)           ((__u32)(self)->kcs_gpregs.gp_esp)
#define kcpustate32_setesp(self, value)    ((self)->kcs_gpregs.gp_esp = (value))
#define kcpustate32_geteflags(self)        ((__u32)(self)->kcs_eflags)
#define kcpustate32_seteflags(self, value) ((self)->kcs_eflags = (value))
#define kcpustate32_to_kcpustate32(self, result)                        \
	__libc_memcpy(__COMPILER_REQTYPE(struct kcpustate32 *, result),     \
	              __COMPILER_REQTYPE(struct kcpustate32 const *, self), \
	              sizeof(struct kcpustate32))
__LOCAL __NOBLOCK void
__NOTHROW_NCX(kcpustate32_to_ucpustate32_ex)(struct kcpustate32 const *__restrict __self,
                                             struct ucpustate32 *__restrict __result,
                                             __u16 __v_gs, __u16 __v_fs, __u16 __v_es,
                                             __u16 __v_ds, __u16 __v_cs, __u16 __v_ss) {
	__result->ucs_gpregs       = __self->kcs_gpregs;
	__result->ucs_sgregs.sg_gs = __v_gs;
	__result->ucs_sgregs.sg_fs = __v_fs;
	__result->ucs_sgregs.sg_es = __v_es;
	__result->ucs_sgregs.sg_ds = __v_ds;
	__result->ucs_cs           = __v_cs;
	__result->ucs_ss           = __v_ss;
	__result->ucs_eflags       = __self->kcs_eflags;
	__result->ucs_eip          = __self->kcs_eip;
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(kcpustate32_to_ucpustate32)(struct kcpustate32 const *__restrict __self,
                                          struct ucpustate32 *__restrict __result) {
	kcpustate32_to_ucpustate32_ex(__self, __result,
	                              __rdgs(),
#if defined(__KERNEL__) && !defined(__x86_64__)
	                              SEGMENT_KERNEL_FSBASE,
	                              SEGMENT_USER_DATA_RPL,
	                              SEGMENT_USER_DATA_RPL,
#else /* __KERNEL__ && !__x86_64__ */
	                              __rdfs(), __rdes(), __rdds(),
#endif /* !__KERNEL__ || __x86_64__ */
	                              SEGMENT_CURRENT_CODE_RPL,
	                              SEGMENT_CURRENT_DATA_RPL);
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(kcpustate32_to_lcpustate32)(struct kcpustate32 const *__restrict __self,
                                          struct lcpustate32 *__restrict __result) {
	__result->lcs_edi = __self->kcs_gpregs.gp_edi;
	__result->lcs_esi = __self->kcs_gpregs.gp_esi;
	__result->lcs_ebp = __self->kcs_gpregs.gp_ebp;
	__result->lcs_esp = __self->kcs_gpregs.gp_esp;
	__result->lcs_ebx = __self->kcs_gpregs.gp_ebx;
	__result->lcs_eip = __self->kcs_eip;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct scpustate32 *
__NOTHROW_NCX(kcpustate32_to_scpustate32_p_ex)(struct kcpustate32 const *__restrict __self,
                                               void *__restrict __kernel_esp,
                                               __u16 __v_gs, __u16 __v_fs, __u16 __v_es,
                                               __u16 __v_ds, __u16 __v_cs, __u16 __v_ss) {
	struct scpustate32 *__result;
	if (__self->kcs_eflags & 0x20000) {
		__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
		                                  OFFSET_SCPUSTATE32_IRREGS +
		                                  SIZEOF_IRREGS32_VM86);
		__result->scs_irregs_v.ir_esp = __self->kcs_gpregs.gp_esp;
		__result->scs_irregs_v.ir_ss  = __v_ss;
		__result->scs_irregs_v.ir_es  = __v_es;
		__result->scs_irregs_v.ir_ds  = __v_ds;
		__result->scs_irregs_v.ir_fs  = __v_fs;
		__result->scs_irregs_v.ir_gs  = __v_gs;
		__result->scs_sgregs.sg_ds = SEGMENT_USER_DATA_RPL;
		__result->scs_sgregs.sg_es = SEGMENT_USER_DATA_RPL;
#ifdef __x86_64__
		__result->scs_sgregs.sg_fs = SEGMENT_USER_DATA_RPL;
		__result->scs_sgregs.sg_gs = SEGMENT_USER_DATA_RPL;
#else /* __x86_64__ */
		__result->scs_sgregs.sg_fs = SEGMENT_USER_FSBASE_RPL;
		__result->scs_sgregs.sg_gs = SEGMENT_USER_GSBASE_RPL;
#endif /* !__x86_64__ */
	} else {
		if (__v_cs & 3) {
			__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
			                                  OFFSET_SCPUSTATE32_IRREGS +
			                                  SIZEOF_IRREGS32_USER);
			__result->scs_irregs_u.ir_esp = __self->kcs_gpregs.gp_esp;
			__result->scs_irregs_u.ir_ss  = __v_ss;
		} else {
			__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
			                                  OFFSET_SCPUSTATE32_IRREGS +
			                                  SIZEOF_IRREGS32_KERNEL);
		}
		__result->scs_sgregs.sg_fs = __v_fs;
		__result->scs_sgregs.sg_gs = __v_gs;
		__result->scs_sgregs.sg_es = __v_es;
		__result->scs_sgregs.sg_ds = __v_ds;
	}
	__result->scs_irregs.ir_eip    = __self->kcs_eip;
	__result->scs_irregs.ir_eflags = __self->kcs_eflags;
	__result->scs_irregs.ir_cs     = __v_cs;
	__result->scs_gpregs           = __self->kcs_gpregs;
	return __result;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct scpustate32 *
__NOTHROW_NCX(kcpustate32_to_scpustate32_p)(struct kcpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	return kcpustate32_to_scpustate32_p_ex(__self, __kernel_esp,
	                                       __rdgs(),
#if defined(__KERNEL__) && !defined(__x86_64__)
	                                       SEGMENT_KERNEL_FSBASE,
	                                       SEGMENT_USER_DATA_RPL,
	                                       SEGMENT_USER_DATA_RPL,
#else /* __KERNEL__ && !__x86_64__ */
	                                       __rdfs(), __rdes(), __rdds(),
#endif /* !__KERNEL__ || __x86_64__ */
	                                       SEGMENT_CURRENT_CODE_RPL,
	                                       SEGMENT_CURRENT_DATA_RPL);
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct icpustate32 *
__NOTHROW_NCX(kcpustate32_to_icpustate32_p_ex)(struct kcpustate32 const *__restrict __self,
                                               void *__restrict __kernel_esp,
                                               __u16 __v_gs_vm86, __u16 __v_fs, __u16 __v_es,
                                               __u16 __v_ds, __u16 __v_cs, __u16 __v_ss) {
	struct icpustate32 *__result;
	if (__self->kcs_eflags & 0x20000) {
		__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
		                                  OFFSET_ICPUSTATE32_IRREGS +
		                                  SIZEOF_IRREGS32_VM86);
		__result->ics_irregs_v.ir_esp = __self->kcs_gpregs.gp_esp;
		__result->ics_irregs_v.ir_ss  = __v_ss;
		__result->ics_irregs_v.ir_es  = __v_es;
		__result->ics_irregs_v.ir_ds  = __v_ds;
		__result->ics_irregs_v.ir_fs  = __v_fs;
		__result->ics_irregs_v.ir_gs  = __v_gs_vm86;
		__result->ics_ds = SEGMENT_USER_DATA_RPL;
		__result->ics_es = SEGMENT_USER_DATA_RPL;
#ifdef __x86_64__
		__result->ics_fs = SEGMENT_USER_DATA_RPL;
#else /* __x86_64__ */
		__result->ics_fs = SEGMENT_USER_FSBASE_RPL;
#endif /* !__x86_64__ */
	} else {
		if (__v_cs & 3) {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  OFFSET_ICPUSTATE32_IRREGS +
			                                  SIZEOF_IRREGS32_USER);
			__result->ics_irregs_u.ir_esp = __self->kcs_gpregs.gp_esp;
			__result->ics_irregs_u.ir_ss  = __v_ss;
		} else {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  OFFSET_ICPUSTATE32_IRREGS +
			                                  SIZEOF_IRREGS32_KERNEL);
		}
		__result->ics_fs = __v_fs;
		__result->ics_es = __v_es;
		__result->ics_ds = __v_ds;
	}
	__result->ics_irregs.ir_eip    = __self->kcs_eip;
	__result->ics_irregs.ir_eflags = __self->kcs_eflags;
	__result->ics_irregs.ir_cs     = __v_cs;
	__result->ics_gpregs           = __self->kcs_gpregs;
	return __result;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct icpustate32 *
__NOTHROW_NCX(kcpustate32_to_icpustate32_p)(struct kcpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	return kcpustate32_to_icpustate32_p_ex(__self, __kernel_esp,
	                                       0,
#if defined(__KERNEL__) && !defined(__x86_64__)
	                                       SEGMENT_KERNEL_FSBASE,
	                                       SEGMENT_USER_DATA_RPL,
	                                       SEGMENT_USER_DATA_RPL,
#else /* __KERNEL__ && !__x86_64__ */
	                                       __rdfs(), __rdes(), __rdds(),
#endif /* !__KERNEL__ || __x86_64__ */
	                                       SEGMENT_CURRENT_CODE_RPL,
	                                       SEGMENT_CURRENT_DATA_RPL);
}
/************************************************************************/




/************************************************************************/
/* `struct icpustate32'                                                 */
/************************************************************************/
#define icpustate32_isvm86(self)                 irregs32_isvm86(&(self)->ics_irregs)
#define icpustate32_isuser_novm86(self)          irregs32_isuser_novm86(&(self)->ics_irregs)
#define icpustate32_isuser(self)                 irregs32_isuser(&(self)->ics_irregs)
#define icpustate32_iskernel(self)               irregs32_iskernel(&(self)->ics_irregs)
#define icpustate32_geteip(self)                 irregs32_geteip(&(self)->ics_irregs)
#define icpustate32_seteip(self, value)          irregs32_seteip(&(self)->ics_irregs, value)
#define icpustate32_getesp(self)                 irregs32_getesp(&(self)->ics_irregs)
#define icpustate32_getuseresp(self)             irregs32_getuseresp(&(self)->ics_irregs)
#define icpustate32_setuseresp(self, value)      irregs32_setuseresp(&(self)->ics_irregs, value)
#define icpustate32_getuserss(self)              irregs32_getuserss(&(self)->ics_irregs)
#define icpustate32_setuserss(self, value)       irregs32_setuserss(&(self)->ics_irregs, value)
#define icpustate32_getkernelss(self)            irregs32_getkernelss(&(self)->ics_irregs)
#define icpustate32_getkernelesp(self)           irregs32_getkernelesp(&(self)->ics_irregs)
#define icpustate32_getds(self)                  (icpustate32_isvm86(self) ? (self)->ics_irregs_v.ir_ds16 : (self)->ics_ds16)
#define icpustate32_setds(self, value)           (icpustate32_isvm86(self) ? ((self)->ics_irregs_v.ir_ds = (value)) : ((self)->ics_ds = (value)))
#define icpustate32_getes(self)                  (icpustate32_isvm86(self) ? (self)->ics_irregs_v.ir_es16 : (self)->ics_es16)
#define icpustate32_setes(self, value)           (icpustate32_isvm86(self) ? ((self)->ics_irregs_v.ir_es = (value)) : ((self)->ics_es = (value)))
#define icpustate32_getfs(self)                  (icpustate32_isvm86(self) ? (self)->ics_irregs_v.ir_fs16 : (self)->ics_fs16)
#define icpustate32_setfs(self, value)           (icpustate32_isvm86(self) ? ((self)->ics_irregs_v.ir_fs = (value)) : ((self)->ics_fs = (value)))
#define icpustate32_getgs_ex(self, v_nonvm86_gs) (icpustate32_isvm86(self) ? (self)->ics_irregs_v.ir_gs16 : (v_nonvm86_gs))
#define icpustate32_getgs(self)                  icpustate32_getgs_ex(self, __rdgs())
#define icpustate32_setgs(self, value)           (icpustate32_isvm86(self) ? (void)((self)->ics_irregs_v.ir_gs = (value)) : __wrgs(value))
#define icpustate32_getds_novm86(self)           ((__u16)(self)->ics_ds16)
#define icpustate32_setds_novm86(self, value)    ((self)->ics_ds = (value))
#define icpustate32_getes_novm86(self)           ((__u16)(self)->ics_es16)
#define icpustate32_setes_novm86(self, value)    ((self)->ics_es = (value))
#define icpustate32_getfs_novm86(self)           ((__u16)(self)->ics_fs16)
#define icpustate32_setfs_novm86(self, value)    ((self)->ics_fs = (value))
#define icpustate32_getgs_novm86(self)           __rdgs()
#define icpustate32_setgs_novm86(self, value)    __wrgs(value)
#define icpustate32_geteflags(self)              irregs32_geteflags(&(self)->ics_irregs)
#define icpustate32_seteflags(self, value)       irregs32_seteflags(&(self)->ics_irregs, value)
#define icpustate32_mskeflags(self, mask, value) irregs32_mskeflags(&(self)->ics_irregs, mask, value)
#define icpustate32_getcs(self)                  irregs32_getcs(&(self)->ics_irregs)
#define icpustate32_setcs(self, value)           irregs32_setcs(&(self)->ics_irregs, value)
#define icpustate32_getss(self)                  irregs32_getss(&(self)->ics_irregs)
#define icpustate32_trysetss(self, value)        irregs32_trysetss(&(self)->ics_irregs, value)
#define icpustate32_trysetesp(self, value)       irregs32_trysetesp(&(self)->ics_irregs, value)
#define icpustate32_sizeof(self)                 (irregs32_sizeof(&(self)->ics_irregs) + OFFSET_ICPUSTATE32_IRREGS)
__LOCAL __NOBLOCK __ATTR_WUNUSED struct icpustate32 *
__NOTHROW_NCX(icpustate32_setesp_p)(struct icpustate32 *__restrict __self,
                                    __u32 __v_esp) {
	if (icpustate32_isuser(__self)) {
		icpustate32_setuseresp(__self, __v_esp);
	} else {
		struct icpustate32 *__result;
		__result = (struct icpustate32 *)(__v_esp - (OFFSET_ICPUSTATE32_IRREGS +
		                                             SIZEOF_IRREGS32_KERNEL));
		__libc_memmove(__result, __self,
		               OFFSET_ICPUSTATE32_IRREGS +
		               SIZEOF_IRREGS32_KERNEL);
		__self = __result;
	}
	return __self;
}

__LOCAL __NOBLOCK void
__NOTHROW_NCX(icpustate32_to_ucpustate32_ex)(struct icpustate32 const *__restrict __self,
                                             struct ucpustate32 *__restrict __result,
                                             __u16 __v_nonvm86_gs) {
	__result->ucs_gpregs = __self->ics_gpregs;
	__result->ucs_eip    = icpustate32_geteip(__self);
	__result->ucs_eflags = icpustate32_geteflags(__self);
	__result->ucs_cs     = icpustate32_getcs(__self);
	if (icpustate32_isvm86(__self)) {
		__result->ucs_gpregs.gp_esp = icpustate32_getuseresp(__self);
		__result->ucs_ss            = icpustate32_getuserss(__self);
		__result->ucs_sgregs.sg_ds  = __self->ics_irregs_v.ir_ds;
		__result->ucs_sgregs.sg_es  = __self->ics_irregs_v.ir_es;
		__result->ucs_sgregs.sg_fs  = __self->ics_irregs_v.ir_fs;
		__result->ucs_sgregs.sg_gs  = __self->ics_irregs_v.ir_gs;
	} else {
		__result->ucs_sgregs.sg_ds = __self->ics_ds;
		__result->ucs_sgregs.sg_es = __self->ics_es;
		__result->ucs_sgregs.sg_fs = __self->ics_fs;
		__result->ucs_sgregs.sg_gs = __v_nonvm86_gs;
		if (icpustate32_isuser(__self)) {
			__result->ucs_gpregs.gp_esp = icpustate32_getuseresp(__self);
			__result->ucs_ss            = icpustate32_getuserss(__self);
		} else {
			__result->ucs_gpregs.gp_esp = icpustate32_getkernelesp(__self);
			__result->ucs_ss            = icpustate32_getkernelss(__self);
		}
	}
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(icpustate32_user_to_ucpustate32_ex)(struct icpustate32 const *__restrict __self,
                                                  struct ucpustate32 *__restrict __result,
                                                  __u16 __v_nonvm86_gs) {
	__hybrid_assert(icpustate32_isuser(__self));
	__result->ucs_gpregs = __self->ics_gpregs;
	__result->ucs_eip    = icpustate32_geteip(__self);
	__result->ucs_eflags = icpustate32_geteflags(__self);
	__result->ucs_cs     = icpustate32_getcs(__self);
	if (icpustate32_isvm86(__self)) {
		__result->ucs_gpregs.gp_esp = icpustate32_getuseresp(__self);
		__result->ucs_ss            = icpustate32_getuserss(__self);
		__result->ucs_sgregs.sg_ds  = __self->ics_irregs_v.ir_ds;
		__result->ucs_sgregs.sg_es  = __self->ics_irregs_v.ir_es;
		__result->ucs_sgregs.sg_fs  = __self->ics_irregs_v.ir_fs;
		__result->ucs_sgregs.sg_gs  = __self->ics_irregs_v.ir_gs;
	} else {
		__result->ucs_sgregs.sg_ds  = __self->ics_ds;
		__result->ucs_sgregs.sg_es  = __self->ics_es;
		__result->ucs_sgregs.sg_fs  = __self->ics_fs;
		__result->ucs_sgregs.sg_gs  = __v_nonvm86_gs;
		__result->ucs_gpregs.gp_esp = icpustate32_getuseresp(__self);
		__result->ucs_ss            = icpustate32_getuserss(__self);
	}
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(icpustate32_to_ucpustate32)(struct icpustate32 const *__restrict __self,
                                          struct ucpustate32 *__restrict __result) {
	icpustate32_to_ucpustate32_ex(__self, __result, __rdgs());
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(icpustate32_user_to_ucpustate32)(struct icpustate32 const *__restrict __self,
                                               struct ucpustate32 *__restrict __result) {
	icpustate32_user_to_ucpustate32_ex(__self, __result, __rdgs());
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(icpustate32_to_kcpustate32)(struct icpustate32 const *__restrict __self,
                                          struct kcpustate32 *__restrict __result) {
	__result->kcs_gpregs        = __self->ics_gpregs;
	__result->kcs_eip           = icpustate32_geteip(__self);
	__result->kcs_eflags        = icpustate32_geteflags(__self);
	__result->kcs_gpregs.gp_esp = icpustate32_getesp(__self);
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(icpustate32_user_to_kcpustate32)(struct icpustate32 const *__restrict __self,
                                               struct kcpustate32 *__restrict __result) {
	__hybrid_assert(icpustate32_isuser(__self));
	__result->kcs_gpregs        = __self->ics_gpregs;
	__result->kcs_eip           = icpustate32_geteip(__self);
	__result->kcs_eflags        = icpustate32_geteflags(__self);
	__result->kcs_gpregs.gp_esp = icpustate32_getuseresp(__self);
}
/* Create a new scheduler cpu-state from a given interrupt cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct scpustate32 *
__NOTHROW_NCX(icpustate32_to_scpustate32_p_ex)(struct icpustate32 const *__restrict __self,
                                               void *__restrict __kernel_esp,
                                               __u16 __v_nonvm86_gs) {
	struct scpustate32 *__result;
	__u16 __v_cs     = icpustate32_getcs(__self);
	__u32 __v_eflags = icpustate32_geteflags(__self);
	if (__v_eflags & 0x20000) {
		__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
		                                  OFFSET_SCPUSTATE32_IRREGS +
		                                  SIZEOF_IRREGS32_VM86);
		__result->scs_irregs_v.ir_esp = icpustate32_getuseresp(__self);
		__result->scs_irregs_v.ir_ss  = icpustate32_getuserss(__self);
		__result->scs_irregs_v.ir_es  = __self->ics_irregs_v.ir_es16;
		__result->scs_irregs_v.ir_ds  = __self->ics_irregs_v.ir_ds16;
		__result->scs_irregs_v.ir_fs  = __self->ics_irregs_v.ir_fs16;
		__result->scs_irregs_v.ir_gs  = __self->ics_irregs_v.ir_gs16;
		__result->scs_sgregs.sg_ds    = __self->ics_ds16;
		__result->scs_sgregs.sg_es    = __self->ics_es16;
		__result->scs_sgregs.sg_fs    = __self->ics_fs16;
		__result->scs_sgregs.sg_gs    = __v_nonvm86_gs;
	} else {
		if (__v_cs & 3) {
			__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
			                                  OFFSET_SCPUSTATE32_IRREGS +
			                                  SIZEOF_IRREGS32_USER);
			__result->scs_irregs_u.ir_esp = icpustate32_getuseresp(__self);
			__result->scs_irregs_u.ir_ss  = icpustate32_getuserss(__self);
		} else {
			__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
			                                  OFFSET_SCPUSTATE32_IRREGS +
			                                  SIZEOF_IRREGS32_KERNEL);
		}
		__result->scs_sgregs.sg_gs = __v_nonvm86_gs;
		__result->scs_sgregs.sg_fs = __self->ics_fs16;
		__result->scs_sgregs.sg_es = __self->ics_es16;
		__result->scs_sgregs.sg_ds = __self->ics_ds16;
	}
	__result->scs_irregs.ir_eip    = icpustate32_geteip(__self);
	__result->scs_irregs.ir_eflags = __v_eflags;
	__result->scs_irregs.ir_cs     = __v_cs;
	__result->scs_gpregs           = __self->ics_gpregs;
	return __result;
}
/* Create a new scheduler cpu-state from a given interrupt cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct scpustate32 *
__NOTHROW_NCX(icpustate32_user_to_scpustate32_p_ex)(struct icpustate32 const *__restrict __self,
                                                    void *__restrict __kernel_esp,
                                                    __u16 __v_nonvm86_gs) {
	struct scpustate32 *__result;
	__u32 __v_eflags = icpustate32_geteflags(__self);
	if (__v_eflags & 0x20000) {
		__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
		                                  OFFSET_SCPUSTATE32_IRREGS +
		                                  SIZEOF_IRREGS32_VM86);
		__result->scs_irregs_v.ir_esp = icpustate32_getuseresp(__self);
		__result->scs_irregs_v.ir_ss  = icpustate32_getuserss(__self);
		__result->scs_irregs_v.ir_es  = __self->ics_irregs_v.ir_es16;
		__result->scs_irregs_v.ir_ds  = __self->ics_irregs_v.ir_ds16;
		__result->scs_irregs_v.ir_fs  = __self->ics_irregs_v.ir_fs16;
		__result->scs_irregs_v.ir_gs  = __self->ics_irregs_v.ir_gs16;
		__result->scs_sgregs.sg_ds    = __self->ics_ds16;
		__result->scs_sgregs.sg_es    = __self->ics_es16;
		__result->scs_sgregs.sg_fs    = __self->ics_fs16;
		__result->scs_sgregs.sg_gs    = __v_nonvm86_gs;
	} else {
		__hybrid_assert(icpustate32_getcs(__self) & 3);
		__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
		                                  OFFSET_SCPUSTATE32_IRREGS +
		                                  SIZEOF_IRREGS32_USER);
		__result->scs_irregs_u.ir_esp = icpustate32_getuseresp(__self);
		__result->scs_irregs_u.ir_ss  = icpustate32_getuserss(__self);
		__result->scs_sgregs.sg_gs = __v_nonvm86_gs;
		__result->scs_sgregs.sg_fs = __self->ics_fs16;
		__result->scs_sgregs.sg_es = __self->ics_es16;
		__result->scs_sgregs.sg_ds = __self->ics_ds16;
	}
	__result->scs_irregs.ir_eip    = icpustate32_geteip(__self);
	__result->scs_irregs.ir_eflags = __v_eflags;
	__result->scs_irregs.ir_cs     = icpustate32_getcs(__self);
	__result->scs_gpregs           = __self->ics_gpregs;
	return __result;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct scpustate32 *
__NOTHROW_NCX(icpustate32_to_scpustate32_p)(struct icpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	return icpustate32_to_scpustate32_p_ex(__self, __kernel_esp, __rdgs());
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct scpustate32 *
__NOTHROW_NCX(icpustate32_user_to_scpustate32_p)(struct icpustate32 const *__restrict __self,
                                                 void *__restrict __kernel_esp) {
	return icpustate32_user_to_scpustate32_p_ex(__self, __kernel_esp, __rdgs());
}
/* Create a duplicate of the given interrupt cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct icpustate32 *
__NOTHROW_NCX(icpustate32_to_icpustate32_p)(struct icpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	struct icpustate32 *__result;
	__u16 __v_cs     = icpustate32_getcs(__self);
	__u32 __v_eflags = icpustate32_geteflags(__self);
	if (__v_eflags & 0x20000) {
		__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
		                                  OFFSET_ICPUSTATE32_IRREGS +
		                                  SIZEOF_IRREGS32_VM86);
		__result->ics_irregs_v.ir_esp = icpustate32_getuseresp(__self);
		__result->ics_irregs_v.ir_ss  = icpustate32_getuserss(__self);
		__result->ics_irregs_v.ir_es  = __self->ics_irregs_v.ir_es16;
		__result->ics_irregs_v.ir_ds  = __self->ics_irregs_v.ir_ds16;
		__result->ics_irregs_v.ir_fs  = __self->ics_irregs_v.ir_fs16;
		__result->ics_irregs_v.ir_gs  = __self->ics_irregs_v.ir_gs16;
		__result->ics_ds              = __self->ics_ds16;
		__result->ics_es              = __self->ics_es16;
		__result->ics_fs              = __self->ics_fs16;
	} else {
		if (__v_cs & 3) {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  OFFSET_ICPUSTATE32_IRREGS +
			                                  SIZEOF_IRREGS32_USER);
			__result->ics_irregs_u.ir_esp = icpustate32_getuseresp(__self);
			__result->ics_irregs_u.ir_ss  = icpustate32_getuserss(__self);
		} else {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  OFFSET_ICPUSTATE32_IRREGS +
			                                  SIZEOF_IRREGS32_KERNEL);
		}
		__result->ics_fs = __self->ics_fs16;
		__result->ics_es = __self->ics_es16;
		__result->ics_ds = __self->ics_ds16;
	}
	__result->ics_irregs.ir_eip    = icpustate32_geteip(__self);
	__result->ics_irregs.ir_eflags = __v_eflags;
	__result->ics_irregs.ir_cs     = __v_cs;
	__result->ics_gpregs           = __self->ics_gpregs;
	return __result;
}
/* Create a duplicate of the given interrupt cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct icpustate32 *
__NOTHROW_NCX(icpustate32_user_to_icpustate32_p)(struct icpustate32 const *__restrict __self,
                                                 void *__restrict __kernel_esp) {
	struct icpustate32 *__result;
	__u32 __v_eflags = icpustate32_geteflags(__self);
	if (__v_eflags & 0x20000) {
		__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
		                                  OFFSET_ICPUSTATE32_IRREGS +
		                                  SIZEOF_IRREGS32_VM86);
		__result->ics_irregs_v.ir_esp = icpustate32_getuseresp(__self);
		__result->ics_irregs_v.ir_ss  = icpustate32_getuserss(__self);
		__result->ics_irregs_v.ir_es  = __self->ics_irregs_v.ir_es16;
		__result->ics_irregs_v.ir_ds  = __self->ics_irregs_v.ir_ds16;
		__result->ics_irregs_v.ir_fs  = __self->ics_irregs_v.ir_fs16;
		__result->ics_irregs_v.ir_gs  = __self->ics_irregs_v.ir_gs16;
		__result->ics_ds              = __self->ics_ds16;
		__result->ics_es              = __self->ics_es16;
		__result->ics_fs              = __self->ics_fs16;
	} else {
		__hybrid_assert(icpustate32_getcs(__self) & 3);
		__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
		                                  OFFSET_ICPUSTATE32_IRREGS +
		                                  SIZEOF_IRREGS32_USER);
		__result->ics_irregs_u.ir_esp = icpustate32_getuseresp(__self);
		__result->ics_irregs_u.ir_ss  = icpustate32_getuserss(__self);
		__result->ics_fs = __self->ics_fs16;
		__result->ics_es = __self->ics_es16;
		__result->ics_ds = __self->ics_ds16;
	}
	__result->ics_irregs.ir_eip    = icpustate32_geteip(__self);
	__result->ics_irregs.ir_eflags = __v_eflags;
	__result->ics_irregs.ir_cs     = icpustate32_getcs(__self);
	__result->ics_gpregs           = __self->ics_gpregs;
	return __result;
}
/************************************************************************/




/************************************************************************/
/* `struct scpustate32'                                                 */
/************************************************************************/
#define scpustate32_isvm86(self)                 ((self)->scs_irregs.ir_eflags & 0x20000)
#define scpustate32_isuser_novm86(self)          ((self)->scs_irregs.ir_cs16 & 3)
#define scpustate32_isuser(self)                 (((self)->scs_irregs.ir_cs16 & 3) || scpustate32_isvm86(self))
#define scpustate32_iskernel(self)               (!((self)->scs_irregs.ir_cs16 & 3) && !scpustate32_isvm86(self))
#define scpustate32_geteip(self)                 ((__u32)(self)->scs_irregs.ir_eip)
#define scpustate32_seteip(self, value)          ((self)->scs_irregs.ir_eip = (value))
#define scpustate32_getuseresp(self)             ((__u32)(self)->scs_irregs_u.ir_esp)
#define scpustate32_setuseresp(self, value)      ((self)->scs_irregs_u.ir_esp = (value))
#define scpustate32_getuserss(self)              ((__u32)(self)->scs_irregs_u.ir_ss16)
#define scpustate32_setuserss(self, value)       ((self)->scs_irregs_u.ir_ss = (value))
#define scpustate32_getkernelss(self)            SEGMENT_KERNEL_DATA
#define scpustate32_getkernelesp(self)           ((__u32)(__uintptr_t)(&(self)->scs_irregs_k + 1))
#define scpustate32_getds(self)                  (scpustate32_isvm86(self) ? (self)->scs_irregs_v.ir_ds16 : (self)->scs_sgregs.sg_ds16)
#define scpustate32_setds(self, value)           (scpustate32_isvm86(self) ? ((self)->scs_irregs_v.ir_ds = (value)) : ((self)->scs_sgregs.sg_ds = (value)))
#define scpustate32_getes(self)                  (scpustate32_isvm86(self) ? (self)->scs_irregs_v.ir_es16 : (self)->scs_sgregs.sg_es16)
#define scpustate32_setes(self, value)           (scpustate32_isvm86(self) ? ((self)->scs_irregs_v.ir_es = (value)) : ((self)->scs_sgregs.sg_es = (value)))
#define scpustate32_getfs(self)                  (scpustate32_isvm86(self) ? (self)->scs_irregs_v.ir_fs16 : (self)->scs_sgregs.sg_fs16)
#define scpustate32_setfs(self, value)           (scpustate32_isvm86(self) ? ((self)->scs_irregs_v.ir_fs = (value)) : ((self)->scs_sgregs.sg_fs = (value)))
#define scpustate32_getgs(self)                  (scpustate32_isvm86(self) ? (self)->scs_irregs_v.ir_gs16 : (self)->scs_sgregs.sg_gs16)
#define scpustate32_setgs(self, value)           (scpustate32_isvm86(self) ? ((self)->scs_irregs_v.ir_gs = (value)) : ((self)->scs_sgregs.sg_gs = (value)))
#define scpustate32_getds_novm86(self)           ((__u16)(self)->scs_ds16)
#define scpustate32_setds_novm86(self, value)    ((self)->scs_ds = (value))
#define scpustate32_getes_novm86(self)           ((__u16)(self)->scs_es16)
#define scpustate32_setes_novm86(self, value)    ((self)->scs_es = (value))
#define scpustate32_getfs_novm86(self)           ((__u16)(self)->scs_fs16)
#define scpustate32_setfs_novm86(self, value)    ((self)->scs_fs = (value))
#define scpustate32_getgs_novm86(self)           ((__u16)(self)->scs_gs16)
#define scpustate32_setgs_novm86(self, value)    ((self)->scs_gs = (value))
#define scpustate32_geteflags(self)              ((__u32)(self)->scs_irregs.ir_eflags)
#define scpustate32_seteflags(self, value)       ((self)->scs_irregs.ir_eflags = (value))
#define scpustate32_mskeflags(self, mask, value) ((self)->scs_irregs.ir_eflags = ((self)->scs_irregs.ir_eflags & (mask)) | (flags))
#define scpustate32_getcs(self)                  ((__u16)(self)->scs_irregs.ir_cs16)
#define scpustate32_setcs(self, value)           ((self)->scs_irregs.ir_cs = (value))
#define scpustate32_getesp(self)                 (scpustate32_isuser(self) ? scpustate32_getuseresp(self) : scpustate32_getkernelesp(self))
#define scpustate32_getss(self)                  (scpustate32_isuser(self) ? scpustate32_getuserss(self) : scpustate32_getkernelss(self))
#define scpustate32_trysetesp(self, value)       (scpustate32_isuser(self) ? (scpustate32_setuseresp(self, value), 1) : (scpustate32_getkernelesp(self) == (value)))
#define scpustate32_trysetss(self, value)        (scpustate32_isuser(self) ? (scpustate32_setuserss(self, value), 1) : (scpustate32_getkernelss(self) == (value)))
#define scpustate32_sizeof(self)                            \
	(scpustate32_isvm86(self)                               \
	 ? (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_VM86)   \
	 : ((self)->scs_irregs.ir_cs16 & 3)                     \
	   ? (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_USER) \
	   : (OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_KERNEL))

__LOCAL __NOBLOCK __ATTR_WUNUSED struct scpustate32 *
__NOTHROW_NCX(scpustate32_setesp_p)(struct scpustate32 *__restrict __self,
                                    __u32 __v_esp) {
	if (scpustate32_isuser(__self)) {
		scpustate32_setuseresp(__self, __v_esp);
	} else {
		struct scpustate32 *__result;
		__result = (struct scpustate32 *)(__v_esp - (OFFSET_SCPUSTATE32_IRREGS +
		                                             SIZEOF_IRREGS32_KERNEL));
		__libc_memmove(__result, __self,
		               OFFSET_SCPUSTATE32_IRREGS +
		               SIZEOF_IRREGS32_KERNEL);
		__self = __result;
	}
	return __self;
}

__LOCAL __NOBLOCK void
__NOTHROW_NCX(scpustate32_to_ucpustate32)(struct scpustate32 const *__restrict __self,
                                          struct ucpustate32 *__restrict __result) {
	__result->ucs_gpregs = __self->scs_gpregs;
	__result->ucs_eip    = scpustate32_geteip(__self);
	__result->ucs_eflags = scpustate32_geteflags(__self);
	__result->ucs_cs     = scpustate32_getcs(__self);
	if (scpustate32_isvm86(__self)) {
		__result->ucs_gpregs.gp_esp = scpustate32_getuseresp(__self);
		__result->ucs_ss            = scpustate32_getuserss(__self);
		__result->ucs_sgregs.sg_ds  = __self->scs_irregs_v.ir_ds16;
		__result->ucs_sgregs.sg_es  = __self->scs_irregs_v.ir_es16;
		__result->ucs_sgregs.sg_fs  = __self->scs_irregs_v.ir_fs16;
		__result->ucs_sgregs.sg_gs  = __self->scs_irregs_v.ir_gs16;
	} else {
		__result->ucs_sgregs = __self->scs_sgregs;
		if (scpustate32_isuser(__self)) {
			__result->ucs_gpregs.gp_esp = scpustate32_getuseresp(__self);
			__result->ucs_ss            = scpustate32_getuserss(__self);
		} else {
			__result->ucs_gpregs.gp_esp = scpustate32_getkernelesp(__self);
			__result->ucs_ss            = scpustate32_getkernelss(__self);
		}
	}
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(scpustate32_user_to_ucpustate32)(struct scpustate32 const *__restrict __self,
                                               struct ucpustate32 *__restrict __result) {
	__hybrid_assert(scpustate32_isuser(__self));
	__result->ucs_gpregs = __self->scs_gpregs;
	__result->ucs_eip    = scpustate32_geteip(__self);
	__result->ucs_eflags = scpustate32_geteflags(__self);
	__result->ucs_cs     = scpustate32_getcs(__self);
	if (scpustate32_isvm86(__self)) {
		__result->ucs_gpregs.gp_esp = scpustate32_getuseresp(__self);
		__result->ucs_ss            = scpustate32_getuserss(__self);
		__result->ucs_sgregs.sg_ds  = __self->scs_irregs_v.ir_ds16;
		__result->ucs_sgregs.sg_es  = __self->scs_irregs_v.ir_es16;
		__result->ucs_sgregs.sg_fs  = __self->scs_irregs_v.ir_fs16;
		__result->ucs_sgregs.sg_gs  = __self->scs_irregs_v.ir_gs16;
	} else {
		__result->ucs_sgregs        = __self->scs_sgregs;
		__result->ucs_gpregs.gp_esp = scpustate32_getuseresp(__self);
		__result->ucs_ss            = scpustate32_getuserss(__self);
	}
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(scpustate32_to_kcpustate32)(struct scpustate32 const *__restrict __self,
                                          struct kcpustate32 *__restrict __result) {
	__result->kcs_gpregs        = __self->scs_gpregs;
	__result->kcs_eip           = scpustate32_geteip(__self);
	__result->kcs_eflags        = scpustate32_geteflags(__self);
	__result->kcs_gpregs.gp_esp = scpustate32_getesp(__self);
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(scpustate32_user_to_kcpustate32)(struct scpustate32 const *__restrict __self,
                                               struct kcpustate32 *__restrict __result) {
	__hybrid_assert(scpustate32_isuser(__self));
	__result->kcs_gpregs        = __self->scs_gpregs;
	__result->kcs_eip           = scpustate32_geteip(__self);
	__result->kcs_eflags        = scpustate32_geteflags(__self);
	__result->kcs_gpregs.gp_esp = scpustate32_getuseresp(__self);
}
/* Create a new interrupt cpu-state from a given scheduler cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct icpustate32 *
__NOTHROW_NCX(scpustate32_to_icpustate32_p)(struct scpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	struct icpustate32 *__result;
	__u16 __v_cs     = scpustate32_getcs(__self);
	__u32 __v_eflags = scpustate32_geteflags(__self);
	if (__v_eflags & 0x20000) {
		__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
		                                  OFFSET_ICPUSTATE32_IRREGS +
		                                  SIZEOF_IRREGS32_VM86);
		__result->ics_irregs_v.ir_esp = scpustate32_getuseresp(__self);
		__result->ics_irregs_v.ir_ss  = scpustate32_getuserss(__self);
		__result->ics_irregs_v.ir_es  = __self->scs_irregs_v.ir_es16;
		__result->ics_irregs_v.ir_ds  = __self->scs_irregs_v.ir_ds16;
		__result->ics_irregs_v.ir_fs  = __self->scs_irregs_v.ir_fs16;
		__result->ics_irregs_v.ir_gs  = __self->scs_irregs_v.ir_gs16;
		__result->ics_ds              = __self->scs_sgregs.sg_ds16;
		__result->ics_es              = __self->scs_sgregs.sg_es16;
		__result->ics_fs              = __self->scs_sgregs.sg_fs16;
	} else {
		if (__v_cs & 3) {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  OFFSET_ICPUSTATE32_IRREGS +
			                                  SIZEOF_IRREGS32_USER);
			__result->ics_irregs_u.ir_esp = scpustate32_getuseresp(__self);
			__result->ics_irregs_u.ir_ss  = scpustate32_getuserss(__self);
		} else {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  OFFSET_ICPUSTATE32_IRREGS +
			                                  SIZEOF_IRREGS32_KERNEL);
		}
		__result->ics_fs = __self->scs_sgregs.sg_fs16;
		__result->ics_es = __self->scs_sgregs.sg_es16;
		__result->ics_ds = __self->scs_sgregs.sg_ds16;
	}
	__result->ics_irregs.ir_eip    = scpustate32_geteip(__self);
	__result->ics_irregs.ir_eflags = __v_eflags;
	__result->ics_irregs.ir_cs     = __v_cs;
	__result->ics_gpregs           = __self->scs_gpregs;
	return __result;
}
/* Create a new interrupt cpu-state from a given scheduler cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct icpustate32 *
__NOTHROW_NCX(scpustate32_user_to_icpustate32_p)(struct scpustate32 const *__restrict __self,
                                                 void *__restrict __kernel_esp) {
	struct icpustate32 *__result;
	__u32 __v_eflags = scpustate32_geteflags(__self);
	if (__v_eflags & 0x20000) {
		__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
		                                  OFFSET_ICPUSTATE32_IRREGS +
		                                  SIZEOF_IRREGS32_VM86);
		__result->ics_irregs_v.ir_esp = scpustate32_getuseresp(__self);
		__result->ics_irregs_v.ir_ss  = scpustate32_getuserss(__self);
		__result->ics_irregs_v.ir_es  = __self->scs_irregs_v.ir_es16;
		__result->ics_irregs_v.ir_ds  = __self->scs_irregs_v.ir_ds16;
		__result->ics_irregs_v.ir_fs  = __self->scs_irregs_v.ir_fs16;
		__result->ics_irregs_v.ir_gs  = __self->scs_irregs_v.ir_gs16;
		__result->ics_ds              = __self->scs_sgregs.sg_ds16;
		__result->ics_es              = __self->scs_sgregs.sg_es16;
		__result->ics_fs              = __self->scs_sgregs.sg_fs16;
	} else {
		__hybrid_assert(scpustate32_getcs(__self) & 3);
		__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
		                                  OFFSET_ICPUSTATE32_IRREGS +
		                                  SIZEOF_IRREGS32_USER);
		__result->ics_irregs_u.ir_esp = scpustate32_getuseresp(__self);
		__result->ics_irregs_u.ir_ss  = scpustate32_getuserss(__self);
		__result->ics_fs = __self->scs_sgregs.sg_fs16;
		__result->ics_es = __self->scs_sgregs.sg_es16;
		__result->ics_ds = __self->scs_sgregs.sg_ds16;
	}
	__result->ics_irregs.ir_eip    = scpustate32_geteip(__self);
	__result->ics_irregs.ir_eflags = __v_eflags;
	__result->ics_irregs.ir_cs     = scpustate32_getcs(__self);
	__result->ics_gpregs           = __self->scs_gpregs;
	return __result;
}
/* Create a duplicate of the given interrupt cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct scpustate32 *
__NOTHROW_NCX(scpustate32_to_scpustate32_p)(struct scpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	__size_t __result_size;
	struct scpustate32 *__result;
	if (scpustate32_isvm86(__self))
		__result_size = OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_VM86;
	else if (scpustate32_isuser_novm86(__self))
		__result_size = OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_USER;
	else {
		__result_size = OFFSET_SCPUSTATE32_IRREGS + SIZEOF_IRREGS32_KERNEL;
	}
	__result = (struct scpustate32 *)((__byte_t *)__kernel_esp - __result_size);
	__libc_memcpy(__result, __self, __result_size);
	return __result;
}
/* Create a duplicate of the given interrupt cpu state. */
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct scpustate32 *
__NOTHROW_NCX(scpustate32_user_to_scpustate32_p)(struct scpustate32 const *__restrict __self,
                                                 void *__restrict __kernel_esp) {
	struct scpustate32 *__result;
	__u32 __v_eflags = scpustate32_geteflags(__self);
	if (__v_eflags & 0x20000) {
		__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
		                                  OFFSET_SCPUSTATE32_IRREGS +
		                                  SIZEOF_IRREGS32_VM86);
		__result->scs_irregs_v.ir_esp = scpustate32_getuseresp(__self);
		__result->scs_irregs_v.ir_ss  = scpustate32_getuserss(__self);
		__result->scs_irregs_v.ir_es  = __self->scs_irregs_v.ir_es16;
		__result->scs_irregs_v.ir_ds  = __self->scs_irregs_v.ir_ds16;
		__result->scs_irregs_v.ir_fs  = __self->scs_irregs_v.ir_fs16;
		__result->scs_irregs_v.ir_gs  = __self->scs_irregs_v.ir_gs16;
		__result->scs_sgregs          = __self->scs_sgregs;
	} else {
		__hybrid_assert(scpustate32_getcs(__self) & 3);
		__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
		                                  OFFSET_SCPUSTATE32_IRREGS +
		                                  SIZEOF_IRREGS32_USER);
		__result->scs_irregs_u.ir_esp = scpustate32_getuseresp(__self);
		__result->scs_irregs_u.ir_ss  = scpustate32_getuserss(__self);
		__result->scs_sgregs = __self->scs_sgregs;
	}
	__result->scs_irregs.ir_eip    = scpustate32_geteip(__self);
	__result->scs_irregs.ir_eflags = __v_eflags;
	__result->scs_irregs.ir_cs     = scpustate32_getcs(__self);
	__result->scs_gpregs           = __self->scs_gpregs;
	return __result;
}
/************************************************************************/




/************************************************************************/
/* `struct ucpustate32'                                                 */
/************************************************************************/
#define ucpustate32_isvm86(self)           ((self)->ucs_eflags & 0x20000)
#define ucpustate32_isuser_novm86(self)    ((self)->ucs_cs16 & 3)
#define ucpustate32_isuser(self)           (((self)->ucs_cs16 & 3) || ucpustate32_isvm86(self))
#define ucpustate32_iskernel(self)         (!((self)->ucs_cs16 & 3) && !ucpustate32_isvm86(self))
#define ucpustate32_geteip(self)           ((__u32)(self)->ucs_eip)
#define ucpustate32_seteip(self, value)    ((self)->ucs_eip = (value))
#define ucpustate32_getesp(self)           ((__u32)(self)->ucs_gpregs.gp_esp)
#define ucpustate32_setesp(self, value)    ((self)->ucs_gpregs.gp_esp = (value))
#define ucpustate32_geteflags(self)        ((__u32)(self)->ucs_eflags)
#define ucpustate32_seteflags(self, value) ((self)->ucs_eflags = (value))
#define ucpustate32_to_ucpustate32(self, result)                        \
	__libc_memcpy(__COMPILER_REQTYPE(struct ucpustate32 *, result),     \
	              __COMPILER_REQTYPE(struct ucpustate32 const *, self), \
	              sizeof(struct ucpustate32))
__LOCAL __NOBLOCK void
__NOTHROW_NCX(ucpustate32_to_kcpustate32)(struct ucpustate32 const *__restrict __self,
                                          struct kcpustate32 *__restrict __result) {
	__result->kcs_gpregs = __self->ucs_gpregs;
	__result->kcs_eflags = __self->ucs_eflags;
	__result->kcs_eip    = __self->ucs_eip;
}
/* NOTE: `KERNEL_ESP' should point onto the kernel-stack where the cpu-state should
 *       be allocated, and will be initial ESP during execution (note that this last
 *       part is specific to icpustate32/scpustate32, as the 64-bit variants do not
 *       make this distinction).
 * WARNING: The `%gs' register is not applied this function, and must therefor be
 *          set manually by the caller if this is the intend (note that the absence
 *          of the `%gs' register is what differentiates icpustate32 from scpustate32) */
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct icpustate32 *
__NOTHROW_NCX(ucpustate32_to_icpustate32_p)(struct ucpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	struct icpustate32 *__result;
	if (ucpustate32_isvm86(__self)) {
		__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
		                                  OFFSET_ICPUSTATE32_IRREGS +
		                                  SIZEOF_IRREGS32_VM86);
		__result->ics_irregs_v.ir_esp = __self->ucs_gpregs.gp_esp;
		__result->ics_irregs_v.ir_ss  = __self->ucs_ss16;
		__result->ics_irregs_v.ir_es  = __self->ucs_sgregs.sg_es16;
		__result->ics_irregs_v.ir_ds  = __self->ucs_sgregs.sg_ds16;
		__result->ics_irregs_v.ir_fs  = __self->ucs_sgregs.sg_fs16;
		__result->ics_irregs_v.ir_gs  = __self->ucs_sgregs.sg_gs16;
		__result->ics_ds = SEGMENT_USER_DATA_RPL;
		__result->ics_es = SEGMENT_USER_DATA_RPL;
#ifdef __x86_64__
		__result->ics_fs = SEGMENT_USER_DATA_RPL;
#else /* __x86_64__ */
		__result->ics_fs = SEGMENT_USER_FSBASE_RPL;
#endif /* !__x86_64__ */
	} else {
		if (ucpustate32_isuser_novm86(__self)) {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  OFFSET_ICPUSTATE32_IRREGS +
			                                  SIZEOF_IRREGS32_USER);
			__result->ics_irregs_u.ir_esp = __self->ucs_gpregs.gp_esp;
			__result->ics_irregs_u.ir_ss  = __self->ucs_ss16;
		} else {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  OFFSET_ICPUSTATE32_IRREGS +
			                                  SIZEOF_IRREGS32_KERNEL);
		}
		__result->ics_ds = __self->ucs_sgregs.sg_ds16;
		__result->ics_es = __self->ucs_sgregs.sg_es16;
		__result->ics_fs = __self->ucs_sgregs.sg_fs16;
	}
	__result->ics_irregs.ir_eip    = __self->ucs_eip;
	__result->ics_irregs.ir_eflags = __self->ucs_eflags;
	__result->ics_irregs.ir_cs     = __self->ucs_cs16;
	__result->ics_gpregs = __self->ucs_gpregs;
	return __result;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct scpustate32 *
__NOTHROW_NCX(ucpustate32_to_scpustate32_p)(struct ucpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	struct scpustate32 *__result;
	if (ucpustate32_isvm86(__self)) {
		__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
		                                  OFFSET_SCPUSTATE32_IRREGS +
		                                  SIZEOF_IRREGS32_VM86);
		__result->scs_irregs_v.ir_esp = __self->ucs_gpregs.gp_esp;
		__result->scs_irregs_v.ir_ss  = __self->ucs_ss16;
		__result->scs_irregs_v.ir_es  = __self->ucs_sgregs.sg_es16;
		__result->scs_irregs_v.ir_ds  = __self->ucs_sgregs.sg_ds16;
		__result->scs_irregs_v.ir_fs  = __self->ucs_sgregs.sg_fs16;
		__result->scs_irregs_v.ir_gs  = __self->ucs_sgregs.sg_gs16;
		__result->scs_sgregs.sg_ds = SEGMENT_USER_DATA_RPL;
		__result->scs_sgregs.sg_es = SEGMENT_USER_DATA_RPL;
#ifdef __x86_64__
		__result->scs_sgregs.sg_fs = SEGMENT_USER_DATA_RPL;
		__result->scs_sgregs.sg_gs = SEGMENT_USER_DATA_RPL;
#else /* __x86_64__ */
		__result->scs_sgregs.sg_fs = SEGMENT_USER_FSBASE_RPL;
		__result->scs_sgregs.sg_gs = SEGMENT_USER_GSBASE_RPL;
#endif /* !__x86_64__ */
	} else {
		if (ucpustate32_isuser_novm86(__self)) {
			__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
			                                  OFFSET_SCPUSTATE32_IRREGS +
			                                  SIZEOF_IRREGS32_USER);
			__result->scs_irregs_u.ir_esp = __self->ucs_gpregs.gp_esp;
			__result->scs_irregs_u.ir_ss  = __self->ucs_ss16;
		} else {
			__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
			                                  OFFSET_SCPUSTATE32_IRREGS +
			                                  SIZEOF_IRREGS32_KERNEL);
		}
		__result->scs_sgregs = __self->ucs_sgregs;
	}
	__result->scs_irregs.ir_eip    = __self->ucs_eip;
	__result->scs_irregs.ir_eflags = __self->ucs_eflags;
	__result->scs_irregs.ir_cs     = __self->ucs_cs16;
	__result->scs_gpregs = __self->ucs_gpregs;
	return __result;
}
/************************************************************************/




/************************************************************************/
/* `struct fcpustate32'                                                 */
/************************************************************************/
#define fcpustate32_isvm86(self)           ((self)->fcs_eflags & 0x20000)
#define fcpustate32_isuser_novm86(self)    ((self)->fcs_sgregs.sg_cs16 & 3)
#define fcpustate32_isuser(self)           (((self)->fcs_sgregs.sg_cs16 & 3) || fcpustate32_isvm86(self))
#define fcpustate32_iskernel(self)         (!((self)->fcs_sgregs.sg_cs16 & 3) && !fcpustate32_isvm86(self))
#define fcpustate32_geteip(self)           ((__u32)(self)->fcs_eip)
#define fcpustate32_seteip(self, value)    ((self)->fcs_eip = (value))
#define fcpustate32_getesp(self)           ((__u32)(self)->fcs_gpregs.gp_esp)
#define fcpustate32_setesp(self, value)    ((self)->fcs_gpregs.gp_esp = (value))
#define fcpustate32_geteflags(self)        ((__u32)(self)->fcs_eflags)
#define fcpustate32_seteflags(self, value) ((self)->fcs_eflags = (value))
#define fcpustate32_to_fcpustate32(self, result)                        \
	__libc_memcpy(__COMPILER_REQTYPE(struct fcpustate32 *, result),     \
	              __COMPILER_REQTYPE(struct fcpustate32 const *, self), \
	              sizeof(struct fcpustate32))
__LOCAL __NOBLOCK void
__NOTHROW_NCX(fcpustate32_to_lcpustate32)(struct fcpustate32 const *__restrict __self,
                                          struct lcpustate32 *__restrict __result) {
	__result->lcs_edi = __self->fcs_gpregs.gp_edi;
	__result->lcs_esi = __self->fcs_gpregs.gp_esi;
	__result->lcs_ebp = __self->fcs_gpregs.gp_ebp;
	__result->lcs_esp = __self->fcs_gpregs.gp_esp;
	__result->lcs_ebx = __self->fcs_gpregs.gp_ebx;
	__result->lcs_eip = __self->fcs_eip;
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(fcpustate32_to_kcpustate32)(struct fcpustate32 const *__restrict __self,
                                          struct kcpustate32 *__restrict __result) {
	__result->kcs_gpregs = __self->fcs_gpregs;
	__result->kcs_eip    = __self->fcs_eip;
	__result->kcs_eflags = __self->fcs_eflags;
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(fcpustate32_to_ucpustate32)(struct fcpustate32 const *__restrict __self,
                                          struct ucpustate32 *__restrict __result) {
	__result->ucs_gpregs       = __self->fcs_gpregs;
	__result->ucs_eip          = __self->fcs_eip;
	__result->ucs_eflags       = __self->fcs_eflags;
	__result->ucs_sgregs.sg_gs = __self->fcs_sgregs.sg_gs;
	__result->ucs_sgregs.sg_fs = __self->fcs_sgregs.sg_fs;
	__result->ucs_sgregs.sg_es = __self->fcs_sgregs.sg_es;
	__result->ucs_sgregs.sg_ds = __self->fcs_sgregs.sg_ds;
	__result->ucs_cs           = __self->fcs_sgregs.sg_cs;
	__result->ucs_ss           = __self->fcs_sgregs.sg_ss;
}

/* Assign fields from `DATA' (but leave fields not defined by `DATA' as unchanged) */
__LOCAL __NOBLOCK void
__NOTHROW_NCX(fcpustate32_assign_ucpustate32)(struct fcpustate32 *__restrict __self,
                                              struct ucpustate32 const *__restrict __data) {
	__self->fcs_gpregs       = __data->ucs_gpregs;
	__self->fcs_eip          = __data->ucs_eip;
	__self->fcs_eflags       = __data->ucs_eflags;
	__self->fcs_sgregs.sg_gs = __data->ucs_sgregs.sg_gs;
	__self->fcs_sgregs.sg_fs = __data->ucs_sgregs.sg_fs;
	__self->fcs_sgregs.sg_es = __data->ucs_sgregs.sg_es;
	__self->fcs_sgregs.sg_ds = __data->ucs_sgregs.sg_ds;
	__self->fcs_sgregs.sg_cs = __data->ucs_cs;
	__self->fcs_sgregs.sg_ss = __data->ucs_ss;
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(fcpustate32_assign_scpustate32)(struct fcpustate32 *__restrict __self,
                                              struct scpustate32 const *__restrict __data) {
	__self->fcs_gpregs       = __data->scs_gpregs;
	__self->fcs_eip          = scpustate32_geteip(__data);
	__self->fcs_eflags       = scpustate32_geteflags(__data);
	__self->fcs_sgregs.sg_cs = scpustate32_getcs(__data);
	if (__self->fcs_eflags & 0x20000) {
		__self->fcs_sgregs.sg_gs  = __data->scs_irregs_v.ir_gs16;
		__self->fcs_sgregs.sg_fs  = __data->scs_irregs_v.ir_fs16;
		__self->fcs_sgregs.sg_es  = __data->scs_irregs_v.ir_es16;
		__self->fcs_sgregs.sg_ds  = __data->scs_irregs_v.ir_ds16;
		__self->fcs_sgregs.sg_ss  = scpustate32_getuserss(__data);
		__self->fcs_gpregs.gp_esp = scpustate32_getuseresp(__data);
	} else {
		if (__self->fcs_sgregs.sg_cs & 3) {
			__self->fcs_sgregs.sg_ss  = scpustate32_getuserss(__data);
			__self->fcs_gpregs.gp_esp = scpustate32_getuseresp(__data);
		} else {
			__self->fcs_sgregs.sg_ss  = scpustate32_getkernelss(__data);
			__self->fcs_gpregs.gp_esp = scpustate32_getkernelesp(__data);
		}
		__self->fcs_sgregs.sg_gs = __data->scs_sgregs.sg_gs16;
		__self->fcs_sgregs.sg_fs = __data->scs_sgregs.sg_fs16;
		__self->fcs_sgregs.sg_es = __data->scs_sgregs.sg_es16;
		__self->fcs_sgregs.sg_ds = __data->scs_sgregs.sg_ds16;
	}
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(fcpustate32_assign_icpustate32_ex)(struct fcpustate32 *__restrict __self,
                                                 struct icpustate32 const *__restrict __data,
                                                 __u16 __v_nonvm86_gs) {
	__self->fcs_gpregs       = __data->ics_gpregs;
	__self->fcs_eip          = icpustate32_geteip(__data);
	__self->fcs_eflags       = icpustate32_geteflags(__data);
	__self->fcs_sgregs.sg_cs = icpustate32_getcs(__data);
	if (__self->fcs_eflags & 0x20000) {
		__self->fcs_sgregs.sg_gs  = __data->ics_irregs_v.ir_gs16;
		__self->fcs_sgregs.sg_fs  = __data->ics_irregs_v.ir_fs16;
		__self->fcs_sgregs.sg_es  = __data->ics_irregs_v.ir_es16;
		__self->fcs_sgregs.sg_ds  = __data->ics_irregs_v.ir_ds16;
		__self->fcs_sgregs.sg_ss  = icpustate32_getuserss(__data);
		__self->fcs_gpregs.gp_esp = icpustate32_getuseresp(__data);
	} else {
		if (__self->fcs_sgregs.sg_cs & 3) {
			__self->fcs_sgregs.sg_ss  = icpustate32_getuserss(__data);
			__self->fcs_gpregs.gp_esp = icpustate32_getuseresp(__data);
		} else {
			__self->fcs_sgregs.sg_ss  = icpustate32_getkernelss(__data);
			__self->fcs_gpregs.gp_esp = icpustate32_getkernelesp(__data);
		}
		__self->fcs_sgregs.sg_gs = __v_nonvm86_gs;
		__self->fcs_sgregs.sg_fs = __data->ics_fs16;
		__self->fcs_sgregs.sg_es = __data->ics_es16;
		__self->fcs_sgregs.sg_ds = __data->ics_ds16;
	}
}
__LOCAL __NOBLOCK void
__NOTHROW_NCX(fcpustate32_assign_icpustate32)(struct fcpustate32 *__restrict __self,
                                              struct icpustate32 const *__restrict __data) {
	fcpustate32_assign_icpustate32_ex(__self, __data, __rdgs());
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct icpustate32 *
__NOTHROW_NCX(fcpustate32_to_icpustate32_p)(struct fcpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	struct icpustate32 *__result;
	if (fcpustate32_isvm86(__self)) {
		__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
		                                  OFFSET_ICPUSTATE32_IRREGS +
		                                  SIZEOF_IRREGS32_VM86);
		__result->ics_irregs_v.ir_esp = __self->fcs_gpregs.gp_esp;
		__result->ics_irregs_v.ir_ss  = __self->fcs_sgregs.sg_ss16;
		__result->ics_irregs_v.ir_es  = __self->fcs_sgregs.sg_es16;
		__result->ics_irregs_v.ir_ds  = __self->fcs_sgregs.sg_ds16;
		__result->ics_irregs_v.ir_fs  = __self->fcs_sgregs.sg_fs16;
		__result->ics_irregs_v.ir_gs  = __self->fcs_sgregs.sg_gs16;
		__result->ics_ds = SEGMENT_USER_DATA_RPL;
		__result->ics_es = SEGMENT_USER_DATA_RPL;
#ifdef __x86_64__
		__result->ics_fs = SEGMENT_USER_DATA_RPL;
#else /* __x86_64__ */
		__result->ics_fs = SEGMENT_USER_FSBASE_RPL;
#endif /* !__x86_64__ */
	} else {
		if (fcpustate32_isuser_novm86(__self)) {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  OFFSET_ICPUSTATE32_IRREGS +
			                                  SIZEOF_IRREGS32_USER);
			__result->ics_irregs_u.ir_esp = __self->fcs_gpregs.gp_esp;
			__result->ics_irregs_u.ir_ss  = __self->fcs_sgregs.sg_ss16;
		} else {
			__result = (struct icpustate32 *)((__byte_t *)__kernel_esp -
			                                  OFFSET_ICPUSTATE32_IRREGS +
			                                  SIZEOF_IRREGS32_KERNEL);
		}
		__result->ics_ds = __self->fcs_sgregs.sg_ds16;
		__result->ics_es = __self->fcs_sgregs.sg_es16;
		__result->ics_fs = __self->fcs_sgregs.sg_fs16;
	}
	__result->ics_irregs.ir_eip    = __self->fcs_eip;
	__result->ics_irregs.ir_eflags = __self->fcs_eflags;
	__result->ics_irregs.ir_cs     = __self->fcs_sgregs.sg_cs16;
	__result->ics_gpregs = __self->fcs_gpregs;
	return __result;
}
__LOCAL __NOBLOCK __ATTR_RETNONNULL struct scpustate32 *
__NOTHROW_NCX(fcpustate32_to_scpustate32_p)(struct fcpustate32 const *__restrict __self,
                                            void *__restrict __kernel_esp) {
	struct scpustate32 *__result;
	if (fcpustate32_isvm86(__self)) {
		__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
		                                  OFFSET_SCPUSTATE32_IRREGS +
		                                  SIZEOF_IRREGS32_VM86);
		__result->scs_irregs_v.ir_esp = __self->fcs_gpregs.gp_esp;
		__result->scs_irregs_v.ir_ss  = __self->fcs_sgregs.sg_ss16;
		__result->scs_irregs_v.ir_es  = __self->fcs_sgregs.sg_es16;
		__result->scs_irregs_v.ir_ds  = __self->fcs_sgregs.sg_ds16;
		__result->scs_irregs_v.ir_fs  = __self->fcs_sgregs.sg_fs16;
		__result->scs_irregs_v.ir_gs  = __self->fcs_sgregs.sg_gs16;
		__result->scs_sgregs.sg_ds = SEGMENT_USER_DATA_RPL;
		__result->scs_sgregs.sg_es = SEGMENT_USER_DATA_RPL;
#ifdef __x86_64__
		__result->scs_sgregs.sg_fs = SEGMENT_USER_DATA_RPL;
		__result->scs_sgregs.sg_gs = SEGMENT_USER_DATA_RPL;
#else /* __x86_64__ */
		__result->scs_sgregs.sg_fs = SEGMENT_USER_FSBASE_RPL;
		__result->scs_sgregs.sg_gs = SEGMENT_USER_GSBASE_RPL;
#endif /* !__x86_64__ */
	} else {
		if (fcpustate32_isuser_novm86(__self)) {
			__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
			                                  OFFSET_SCPUSTATE32_IRREGS +
			                                  SIZEOF_IRREGS32_USER);
			__result->scs_irregs_u.ir_esp = __self->fcs_gpregs.gp_esp;
			__result->scs_irregs_u.ir_ss  = __self->fcs_sgregs.sg_ss16;
		} else {
			__result = (struct scpustate32 *)((__byte_t *)__kernel_esp -
			                                  OFFSET_SCPUSTATE32_IRREGS +
			                                  SIZEOF_IRREGS32_KERNEL);
		}
		__result->scs_sgregs.sg_gs = __self->fcs_sgregs.sg_gs16;
		__result->scs_sgregs.sg_fs = __self->fcs_sgregs.sg_fs16;
		__result->scs_sgregs.sg_es = __self->fcs_sgregs.sg_es16;
		__result->scs_sgregs.sg_ds = __self->fcs_sgregs.sg_ds16;
	}
	__result->scs_irregs.ir_eip    = __self->fcs_eip;
	__result->scs_irregs.ir_eflags = __self->fcs_eflags;
	__result->scs_irregs.ir_cs     = __self->fcs_sgregs.sg_cs16;
	__result->scs_gpregs = __self->fcs_gpregs;
	return __result;
}
/************************************************************************/







#ifndef __x86_64__
#define gpregs_getpdi                       gpregs32_getedi
#define gpregs_setpdi                       gpregs32_setedi
#define gpregs_getpsi                       gpregs32_getesi
#define gpregs_setpsi                       gpregs32_setesi
#define gpregs_getpbp                       gpregs32_getebp
#define gpregs_setpbp                       gpregs32_setebp
#define gpregs_getpsp                       gpregs32_getesp
#define gpregs_setpsp                       gpregs32_setesp
#define gpregs_getpbx                       gpregs32_getebx
#define gpregs_setpbx                       gpregs32_setebx
#define gpregs_getpdx                       gpregs32_getedx
#define gpregs_setpdx                       gpregs32_setedx
#define gpregs_getpcx                       gpregs32_getecx
#define gpregs_setpcx                       gpregs32_setecx
#define gpregs_getpax                       gpregs32_geteax
#define gpregs_setpax                       gpregs32_seteax
#define gpregs_to_gpregs                    gpregs32_to_gpregs32
#define gpregs_to_gpregs32                  gpregs32_to_gpregs32
#define gpregs32_to_gpregs                  gpregs32_to_gpregs32
#define gpregs_to_gpregsnsp                 gpregs32_to_gpregs32
#define gpregs_to_gpregsnsp32               gpregs32_to_gpregs32
#define gpregs32_to_gpregsnsp               gpregs32_to_gpregs32

#define irregs_isvm86(self)                 irregs32_isvm86(self)
#define irregs_isuser_novm86(self)          irregs32_isuser_novm86(self)
#define irregs_isuser(self)                 irregs32_isuser(self)
#define irregs_iskernel(self)               irregs32_iskernel(self)
#define irregs_is32bit(self)                1
#define irregs_is64bit(self)                0
#define irregs_isnative(self)               1
#define irregs_iscompat(self)               0
#define irregs_getpc                        irregs32_geteip
#define irregs_setpc                        irregs32_seteip
#define irregs_getcs                        irregs32_getcs
#define irregs_setcs                        irregs32_setcs
#define irregs_getpflags                    irregs32_geteflags
#define irregs_setpflags                    irregs32_seteflags
#define irregs_mskpflags                    irregs32_mskeflags
#define irregs_getsp                        irregs32_getesp
#define irregs_getuserpsp                   irregs32_getuseresp
#define irregs_setuserpsp                   irregs32_setuseresp
#define irregs_getuserss                    irregs32_getuserss
#define irregs_setuserss                    irregs32_setuserss
#define irregs_getkernelpsp                 irregs32_getkernelesp
#define irregs_getkernelss                  irregs32_getkernelss
#define irregs_getss                        irregs32_getss
#define irregs_trysetss                     irregs32_trysetss
#define irregs_trysetesp                    irregs32_trysetesp
#define irregs_sizeof                       irregs32_sizeof

#define lcpustate_getpc                     lcpustate32_geteip
#define lcpustate_setpc                     lcpustate32_seteip
#define lcpustate_getsp                     lcpustate32_getesp
#define lcpustate_setsp                     lcpustate32_setesp
#define lcpustate_to_lcpustate              lcpustate32_to_lcpustate32
#define lcpustate_to_lcpustate32            lcpustate32_to_lcpustate32
#define lcpustate32_to_lcpustate            lcpustate32_to_lcpustate32
#define lcpustate_current                   lcpustate32_current
#define lcpustate_to_gpregs_ex              lcpustate32_to_gpregs32_ex
#define lcpustate_to_gpregs32_ex            lcpustate32_to_gpregs32_ex
#define lcpustate32_to_gpregs_ex            lcpustate32_to_gpregs32_ex
#define lcpustate_to_gpregs                 lcpustate32_to_gpregs32
#define lcpustate_to_gpregs32               lcpustate32_to_gpregs32
#define lcpustate32_to_gpregs               lcpustate32_to_gpregs32
#define lcpustate_to_ucpustate_ex           lcpustate32_to_ucpustate32_ex
#define lcpustate_to_ucpustate32_ex         lcpustate32_to_ucpustate32_ex
#define lcpustate32_to_ucpustate_ex         lcpustate32_to_ucpustate32_ex
#define lcpustate_to_ucpustate              lcpustate32_to_ucpustate32
#define lcpustate_to_ucpustate32            lcpustate32_to_ucpustate32
#define lcpustate32_to_ucpustate            lcpustate32_to_ucpustate32
#define lcpustate_to_kcpustate_ex           lcpustate32_to_kcpustate32_ex
#define lcpustate_to_kcpustate32_ex         lcpustate32_to_kcpustate32_ex
#define lcpustate32_to_kcpustate_ex         lcpustate32_to_kcpustate32_ex
#define lcpustate_to_kcpustate              lcpustate32_to_kcpustate32
#define lcpustate_to_kcpustate32            lcpustate32_to_kcpustate32
#define lcpustate32_to_kcpustate            lcpustate32_to_kcpustate32

#define kcpustate_getpc                     kcpustate32_geteip
#define kcpustate_setpc                     kcpustate32_seteip
#define kcpustate_getsp                     kcpustate32_getesp
#define kcpustate_setsp                     kcpustate32_setesp
#define kcpustate_getpflags                 kcpustate32_geteflags
#define kcpustate_setpflags                 kcpustate32_seteflags
#define kcpustate_to_kcpustate              kcpustate32_to_kcpustate32
#define kcpustate_to_kcpustate32            kcpustate32_to_kcpustate32
#define kcpustate32_to_kcpustate            kcpustate32_to_kcpustate32
#define kcpustate_to_ucpustate_ex           kcpustate32_to_ucpustate32_ex
#define kcpustate_to_ucpustate32_ex         kcpustate32_to_ucpustate32_ex
#define kcpustate32_to_ucpustate_ex         kcpustate32_to_ucpustate32_ex
#define kcpustate_to_ucpustate              kcpustate32_to_ucpustate32
#define kcpustate_to_ucpustate32            kcpustate32_to_ucpustate32
#define kcpustate32_to_ucpustate            kcpustate32_to_ucpustate32
#define kcpustate_to_lcpustate              kcpustate32_to_lcpustate32
#define kcpustate_to_lcpustate32            kcpustate32_to_lcpustate32
#define kcpustate32_to_lcpustate            kcpustate32_to_lcpustate32
#define kcpustate_to_scpustate_p_ex         kcpustate32_to_scpustate32_p_ex
#define kcpustate_to_scpustate32_p_ex       kcpustate32_to_scpustate32_p_ex
#define kcpustate32_to_scpustate_p_ex       kcpustate32_to_scpustate32_p_ex
#define kcpustate_to_scpustate_p            kcpustate32_to_scpustate32_p
#define kcpustate_to_scpustate32_p          kcpustate32_to_scpustate32_p
#define kcpustate32_to_scpustate_p          kcpustate32_to_scpustate32_p
#define kcpustate_to_icpustate_p_ex         kcpustate32_to_icpustate32_p_ex
#define kcpustate_to_icpustate32_p_ex       kcpustate32_to_icpustate32_p_ex
#define kcpustate32_to_icpustate_p_ex       kcpustate32_to_icpustate32_p_ex
#define kcpustate_to_icpustate_p            kcpustate32_to_icpustate32_p
#define kcpustate_to_icpustate32_p          kcpustate32_to_icpustate32_p
#define kcpustate32_to_icpustate_p          kcpustate32_to_icpustate32_p

#define icpustate_getpc                     icpustate32_geteip
#define icpustate_setpc                     icpustate32_seteip
#define icpustate_getsp                     icpustate32_getesp
#define icpustate_trysetsp                  icpustate32_trysetesp
#define icpustate_setsp_p                   icpustate32_setesp_p
#define icpustate_isvm86                    icpustate32_isvm86
#define icpustate_isuser_novm86             icpustate32_isuser_novm86
#define icpustate_isuser                    icpustate32_isuser
#define icpustate_iskernel                  icpustate32_iskernel
#define icpustate_is32bit(self)             1
#define icpustate_is64bit(self)             0
#define icpustate_isnative(self)            1
#define icpustate_iscompat(self)            0
#define icpustate_getuserpsp                icpustate32_getuseresp
#define icpustate_setuserpsp                icpustate32_setuseresp
#define icpustate_getuserss                 icpustate32_getuserss
#define icpustate_setuserss                 icpustate32_setuserss
#define icpustate_getkernelss               icpustate32_getkernelss
#define icpustate_getkernelpsp              icpustate32_getkernelesp
#define icpustate_getds                     icpustate32_getds
#define icpustate_setds                     icpustate32_setds
#define icpustate_getes                     icpustate32_getes
#define icpustate_setes                     icpustate32_setes
#define icpustate_getfs                     icpustate32_getfs
#define icpustate_setfs                     icpustate32_setfs
#define icpustate_getgs_ex                  icpustate32_getgs_ex
#define icpustate_getgs                     icpustate32_getgs
#define icpustate_setgs                     icpustate32_setgs
#define icpustate_getds_novm86              icpustate32_getds_novm86
#define icpustate_setds_novm86              icpustate32_setds_novm86
#define icpustate_getes_novm86              icpustate32_getes_novm86
#define icpustate_setes_novm86              icpustate32_setes_novm86
#define icpustate_getfs_novm86              icpustate32_getfs_novm86
#define icpustate_setfs_novm86              icpustate32_setfs_novm86
#define icpustate_getgs_novm86              icpustate32_getgs_novm86
#define icpustate_setgs_novm86              icpustate32_setgs_novm86
#define icpustate_getpflags                 icpustate32_geteflags
#define icpustate_setpflags                 icpustate32_seteflags
#define icpustate_mskpflags                 icpustate32_mskeflags
#define icpustate_getcs                     icpustate32_getcs
#define icpustate_setcs                     icpustate32_setcs
#define icpustate_getss                     icpustate32_getss
#define icpustate_trysetss                  icpustate32_trysetss
#define icpustate_sizeof                    icpustate32_sizeof
#define icpustate_to_ucpustate_ex           icpustate32_to_ucpustate32_ex
#define icpustate_to_ucpustate32_ex         icpustate32_to_ucpustate32_ex
#define icpustate32_to_ucpustate_ex         icpustate32_to_ucpustate32_ex
#define icpustate_to_ucpustate              icpustate32_to_ucpustate32
#define icpustate_to_ucpustate32            icpustate32_to_ucpustate32
#define icpustate32_to_ucpustate            icpustate32_to_ucpustate32
#define icpustate_user_to_ucpustate_ex      icpustate32_user_to_ucpustate32_ex
#define icpustate_user_to_ucpustate32_ex    icpustate32_user_to_ucpustate32_ex
#define icpustate32_user_to_ucpustate_ex    icpustate32_user_to_ucpustate32_ex
#define icpustate_user_to_ucpustate         icpustate32_user_to_ucpustate32
#define icpustate_user_to_ucpustate32       icpustate32_user_to_ucpustate32
#define icpustate32_user_to_ucpustate       icpustate32_user_to_ucpustate32
#define icpustate_to_kcpustate              icpustate32_to_kcpustate32
#define icpustate_to_kcpustate32            icpustate32_to_kcpustate32
#define icpustate32_to_kcpustate            icpustate32_to_kcpustate32
#define icpustate_user_to_kcpustate         icpustate32_user_to_kcpustate32
#define icpustate_user_to_kcpustate32       icpustate32_user_to_kcpustate32
#define icpustate32_user_to_kcpustate       icpustate32_user_to_kcpustate32
#define icpustate_to_scpustate_p_ex         icpustate32_to_scpustate32_p_ex
#define icpustate_to_scpustate32_p_ex       icpustate32_to_scpustate32_p_ex
#define icpustate32_to_scpustate_p_ex       icpustate32_to_scpustate32_p_ex
#define icpustate_user_to_scpustate_p_ex    icpustate32_user_to_scpustate32_p_ex
#define icpustate_user_to_scpustate32_p_ex  icpustate32_user_to_scpustate32_p_ex
#define icpustate32_user_to_scpustate_p_ex  icpustate32_user_to_scpustate32_p_ex
#define icpustate_to_scpustate_p            icpustate32_to_scpustate32_p
#define icpustate_to_scpustate32_p          icpustate32_to_scpustate32_p
#define icpustate32_to_scpustate_p          icpustate32_to_scpustate32_p
#define icpustate_user_to_scpustate_p       icpustate32_user_to_scpustate32_p
#define icpustate_user_to_scpustate32_p     icpustate32_user_to_scpustate32_p
#define icpustate32_user_to_scpustate_p     icpustate32_user_to_scpustate32_p
#define icpustate_to_icpustate_p            icpustate32_to_icpustate32_p
#define icpustate_to_icpustate32_p          icpustate32_to_icpustate32_p
#define icpustate32_to_icpustate_p          icpustate32_to_icpustate32_p
#define icpustate_user_to_icpustate_p       icpustate32_user_to_icpustate32_p
#define icpustate_user_to_icpustate32_p     icpustate32_user_to_icpustate32_p
#define icpustate32_user_to_icpustate_p     icpustate32_user_to_icpustate32_p

#define scpustate_getpc                     scpustate32_geteip
#define scpustate_setpc                     scpustate32_seteip
#define scpustate_getsp                     scpustate32_getesp
#define scpustate_trysetsp                  scpustate32_trysetesp
#define scpustate_setsp_p                   scpustate32_setesp_p
#define scpustate_isvm86                    scpustate32_isvm86
#define scpustate_isuser_novm86             scpustate32_isuser_novm86
#define scpustate_isuser                    scpustate32_isuser
#define scpustate_iskernel                  scpustate32_iskernel
#define scpustate_is32bit(self)             1
#define scpustate_is64bit(self)             0
#define scpustate_isnative(self)            1
#define scpustate_iscompat(self)            0
#define scpustate_getuserpsp                scpustate32_getuseresp
#define scpustate_setuserpsp                scpustate32_setuseresp
#define scpustate_getuserss                 scpustate32_getuserss
#define scpustate_setuserss                 scpustate32_setuserss
#define scpustate_getkernelss               scpustate32_getkernelss
#define scpustate_getkernelpsp              scpustate32_getkernelesp
#define scpustate_getds                     scpustate32_getds
#define scpustate_setds                     scpustate32_setds
#define scpustate_getes                     scpustate32_getes
#define scpustate_setes                     scpustate32_setes
#define scpustate_getfs                     scpustate32_getfs
#define scpustate_setfs                     scpustate32_setfs
#define scpustate_getgs                     scpustate32_getgs
#define scpustate_setgs                     scpustate32_setgs
#define scpustate_getds_novm86              scpustate32_getds_novm86
#define scpustate_setds_novm86              scpustate32_setds_novm86
#define scpustate_getes_novm86              scpustate32_getes_novm86
#define scpustate_setes_novm86              scpustate32_setes_novm86
#define scpustate_getfs_novm86              scpustate32_getfs_novm86
#define scpustate_setfs_novm86              scpustate32_setfs_novm86
#define scpustate_getgs_novm86              scpustate32_getgs_novm86
#define scpustate_setgs_novm86              scpustate32_setgs_novm86
#define scpustate_getpflags                 scpustate32_geteflags
#define scpustate_setpflags                 scpustate32_seteflags
#define scpustate_mskpflags                 scpustate32_mskeflags
#define scpustate_getcs                     scpustate32_getcs
#define scpustate_setcs                     scpustate32_setcs
#define scpustate_getss                     scpustate32_getss
#define scpustate_trysetss                  scpustate32_trysetss
#define scpustate_sizeof                    scpustate32_sizeof
#define scpustate_to_ucpustate              scpustate32_to_ucpustate32
#define scpustate_to_ucpustate32            scpustate32_to_ucpustate32
#define scpustate32_to_ucpustate            scpustate32_to_ucpustate32
#define scpustate_user_to_ucpustate         scpustate32_user_to_ucpustate32
#define scpustate_user_to_ucpustate32       scpustate32_user_to_ucpustate32
#define scpustate32_user_to_ucpustate       scpustate32_user_to_ucpustate32
#define scpustate_to_kcpustate              scpustate32_to_kcpustate32
#define scpustate_to_kcpustate32            scpustate32_to_kcpustate32
#define scpustate32_to_kcpustate            scpustate32_to_kcpustate32
#define scpustate_user_to_kcpustate         scpustate32_user_to_kcpustate32
#define scpustate_user_to_kcpustate32       scpustate32_user_to_kcpustate32
#define scpustate32_user_to_kcpustate       scpustate32_user_to_kcpustate32
#define scpustate_to_icpustate_p            scpustate32_to_icpustate32_p
#define scpustate_to_icpustate32_p          scpustate32_to_icpustate32_p
#define scpustate32_to_icpustate_p          scpustate32_to_icpustate32_p
#define scpustate_user_to_icpustate_p       scpustate32_user_to_icpustate32_p
#define scpustate_user_to_icpustate32_p     scpustate32_user_to_icpustate32_p
#define scpustate32_user_to_icpustate_p     scpustate32_user_to_icpustate32_p
#define scpustate_to_scpustate_p            scpustate32_to_scpustate32_p
#define scpustate_to_scpustate32_p          scpustate32_to_scpustate32_p
#define scpustate32_to_scpustate_p          scpustate32_to_scpustate32_p
#define scpustate_user_to_scpustate_p       scpustate32_user_to_scpustate32_p
#define scpustate_user_to_scpustate32_p     scpustate32_user_to_scpustate32_p
#define scpustate32_user_to_scpustate_p     scpustate32_user_to_scpustate32_p

#define ucpustate_isvm86                    ucpustate32_isvm86
#define ucpustate_isuser_novm86             ucpustate32_isuser_novm86
#define ucpustate_isuser                    ucpustate32_isuser
#define ucpustate_iskernel                  ucpustate32_iskernel
#define ucpustate_is32bit(self)             1
#define ucpustate_is64bit(self)             0
#define ucpustate_isnative(self)            1
#define ucpustate_iscompat(self)            0
#define ucpustate_getpc                     ucpustate32_geteip
#define ucpustate_setpc                     ucpustate32_seteip
#define ucpustate_getsp                     ucpustate32_getesp
#define ucpustate_setsp                     ucpustate32_setesp
#define ucpustate_getpflags                 ucpustate32_geteflags
#define ucpustate_setpflags                 ucpustate32_seteflags
#define ucpustate_to_ucpustate              ucpustate32_to_ucpustate32
#define ucpustate_to_ucpustate32            ucpustate32_to_ucpustate32
#define ucpustate32_to_ucpustate            ucpustate32_to_ucpustate32
#define ucpustate_to_kcpustate              ucpustate32_to_kcpustate32
#define ucpustate_to_kcpustate32            ucpustate32_to_kcpustate32
#define ucpustate32_to_kcpustate            ucpustate32_to_kcpustate32
#define ucpustate_to_icpustate_p            ucpustate32_to_icpustate32_p
#define ucpustate_to_icpustate32_p          ucpustate32_to_icpustate32_p
#define ucpustate32_to_icpustate_p          ucpustate32_to_icpustate32_p
#define ucpustate_to_scpustate_p            ucpustate32_to_scpustate32_p
#define ucpustate_to_scpustate32_p          ucpustate32_to_scpustate32_p
#define ucpustate32_to_scpustate_p          ucpustate32_to_scpustate32_p

#define fcpustate_isvm86                    fcpustate32_isvm86
#define fcpustate_isuser_novm86             fcpustate32_isuser_novm86
#define fcpustate_isuser                    fcpustate32_isuser
#define fcpustate_iskernel                  fcpustate32_iskernel
#define fcpustate_is32bit(self)             1
#define fcpustate_is64bit(self)             0
#define fcpustate_isnative(self)            1
#define fcpustate_iscompat(self)            0
#define fcpustate_getpc                     fcpustate32_geteip
#define fcpustate_setpc                     fcpustate32_seteip
#define fcpustate_getsp                     fcpustate32_getesp
#define fcpustate_setsp                     fcpustate32_setesp
#define fcpustate_getpflags                 fcpustate32_geteflags
#define fcpustate_setpflags                 fcpustate32_seteflags
#define fcpustate_to_fcpustate              fcpustate32_to_fcpustate32
#define fcpustate_to_fcpustate32            fcpustate32_to_fcpustate32
#define fcpustate32_to_fcpustate            fcpustate32_to_fcpustate32
#define fcpustate_to_lcpustate              fcpustate32_to_lcpustate32
#define fcpustate_to_lcpustate32            fcpustate32_to_lcpustate32
#define fcpustate32_to_lcpustate            fcpustate32_to_lcpustate32
#define fcpustate_to_kcpustate              fcpustate32_to_kcpustate32
#define fcpustate_to_kcpustate32            fcpustate32_to_kcpustate32
#define fcpustate32_to_kcpustate            fcpustate32_to_kcpustate32
#define fcpustate_to_ucpustate              fcpustate32_to_ucpustate32
#define fcpustate_to_ucpustate32            fcpustate32_to_ucpustate32
#define fcpustate32_to_ucpustate            fcpustate32_to_ucpustate32
#define fcpustate_assign_ucpustate          fcpustate32_assign_ucpustate32
#define fcpustate_assign_ucpustate32        fcpustate32_assign_ucpustate32
#define fcpustate32_assign_ucpustate        fcpustate32_assign_ucpustate32
#define fcpustate_assign_scpustate          fcpustate32_assign_scpustate32
#define fcpustate_assign_scpustate32        fcpustate32_assign_scpustate32
#define fcpustate32_assign_scpustate        fcpustate32_assign_scpustate32
#define fcpustate_assign_icpustate_ex       fcpustate32_assign_icpustate32_ex
#define fcpustate_assign_icpustate32_ex     fcpustate32_assign_icpustate32_ex
#define fcpustate32_assign_icpustate_ex     fcpustate32_assign_icpustate32_ex
#define fcpustate_assign_icpustate          fcpustate32_assign_icpustate32
#define fcpustate_assign_icpustate32        fcpustate32_assign_icpustate32
#define fcpustate32_assign_icpustate        fcpustate32_assign_icpustate32
#define fcpustate_to_icpustate_p            fcpustate32_to_icpustate32_p
#define fcpustate_to_icpustate32_p          fcpustate32_to_icpustate32_p
#define fcpustate32_to_icpustate_p          fcpustate32_to_icpustate32_p
#define fcpustate_to_scpustate_p            fcpustate32_to_scpustate32_p
#define fcpustate_to_scpustate32_p          fcpustate32_to_scpustate32_p
#define fcpustate32_to_scpustate_p          fcpustate32_to_scpustate32_p

#endif /* !__x86_64__ */

__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_KOS_KERNEL_CPU_STATE_HELPERS32_H */