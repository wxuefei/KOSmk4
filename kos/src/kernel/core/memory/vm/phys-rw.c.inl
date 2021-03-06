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
#ifdef __INTELLISENSE__
#include "phys.c"
#define DEFINE_PHYS_READ 1
//#define DEFINE_PHYS_WRITE 1
#define DEFINE_PHYS_UNALIGNED 1
#endif /* __INTELLISENSE__ */

#include <hybrid/unaligned.h>

#if (defined(DEFINE_PHYS_READ) + defined(DEFINE_PHYS_WRITE)) != 1
#error "Must #define exactly one of `DEFINE_PHYS_READ', `DEFINE_PHYS_WRITE'"
#endif

#ifdef DEFINE_PHYS_UNALIGNED
#define FUNC3(x, y) x##y##_unaligned
#else /* DEFINE_PHYS_UNALIGNED */
#define FUNC3(x, y) x##y
#endif /* !DEFINE_PHYS_UNALIGNED */
#define FUNC2(x, y) FUNC3(x, y)
#ifdef DEFINE_PHYS_READ
#define FUNC(x)        FUNC2(vm_read, x)
#define IFELSERW(r, w) r
#define IFRD(...)      __VA_ARGS__
#define IFWR(...)      /* nothing */
#define RETURN_TYPE(T) T
#define VALUE_ARG(T)   /* nothing */
#elif defined(DEFINE_PHYS_WRITE)
#define IFELSERW(r, w) w
#define IFRD(...)      /* nothing */
#define IFWR(...)      __VA_ARGS__
#define FUNC(x)        FUNC2(vm_write, x)
#define RETURN_TYPE(T) void
#define VALUE_ARG(T)   , T value
#endif
#ifdef DEFINE_PHYS_UNALIGNED
#define IFELSEAL(al, ual) ual
#else /* DEFINE_PHYS_UNALIGNED */
#define IFELSEAL(al, ual) al
#endif /* !DEFINE_PHYS_UNALIGNED */

DECL_BEGIN

#define TRANSFER_RW(access_value, mapped_lvalue) \
	IFELSERW((access_value) = (mapped_lvalue),   \
	         (mapped_lvalue) = (access_value))

#define USED_PAGEDIR_PROT \
	IFELSERW(PAGEDIR_MAP_FREAD, PAGEDIR_MAP_FWRITE)

#define DORW_AND_RETURN(n_bits, virtaddr)                                \
	IFELSERW(                                                            \
	do {                                                                 \
		return IFELSEAL(*(u##n_bits *)(virtaddr),                        \
		                UNALIGNED_GET##n_bits((u##n_bits *)(virtaddr))); \
	} __WHILE0,                                                          \
	do {                                                                 \
		IFELSEAL(*(u##n_bits *)(virtaddr) = value,                       \
		         UNALIGNED_SET##n_bits((u##n_bits *)(virtaddr), value)); \
		return;                                                          \
	} __WHILE0)
#define DORW_AND_CONTINUE(n_bits, virtaddr)                                \
	IFELSERW(                                                              \
	do {                                                                   \
		result = IFELSEAL(*(u##n_bits *)(virtaddr),                        \
		                  UNALIGNED_GET##n_bits((u##n_bits *)(virtaddr))); \
	} __WHILE0,                                                            \
	do {                                                                   \
		IFELSEAL(*(u##n_bits *)(virtaddr) = value,                         \
		         UNALIGNED_SET##n_bits((u##n_bits *)(virtaddr), value));   \
	} __WHILE0)

#ifndef DEFINE_PHYS_UNALIGNED
PUBLIC NOBLOCK WUNUSED RETURN_TYPE(u8)
NOTHROW(KCALL FUNC(physb))(PHYS vm_phys_t addr VALUE_ARG(u8)) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	IFRD(u8 result);
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(addr, 1))
		DORW_AND_RETURN(8, PHYS_TO_IDENTITY(addr));
#endif /* !NO_PHYS_IDENTITY */
	tramp  = THIS_TRAMPOLINE_BASE;
	backup = pagedir_push_mapone(tramp,
	                             addr & ~PAGEMASK,
	                             USED_PAGEDIR_PROT);
	pagedir_syncone(tramp);
	/* Copy memory. */
	DORW_AND_CONTINUE(8, tramp + ((ptrdiff_t)addr & PAGEMASK));
	pagedir_pop_mapone(tramp, backup);
	IFRD(return result);
}
#endif /* !DEFINE_PHYS_UNALIGNED */

PUBLIC NOBLOCK WUNUSED RETURN_TYPE(u16)
NOTHROW(KCALL FUNC(physw))(PHYS vm_phys_t addr VALUE_ARG(u16)) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	IFRD(u16 result;)
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(addr, 2))
		DORW_AND_RETURN(16, PHYS_TO_IDENTITY(addr));
#endif /* !NO_PHYS_IDENTITY */
	tramp  = THIS_TRAMPOLINE_BASE;
	backup = pagedir_push_mapone(tramp,
	                             addr & ~PAGEMASK,
	                             USED_PAGEDIR_PROT);
	pagedir_syncone(tramp);
#ifdef DEFINE_PHYS_UNALIGNED
	if unlikely((size_t)(addr & PAGEMASK) >= PAGEMASK) {
		/* Read from 2 pages. */
		union {
			u16 word;
			u8 bytes[2];
		} buf;
		assert((size_t)(addr & PAGEMASK) == PAGEMASK);
		IFWR(buf.word = value);
		TRANSFER_RW(buf.bytes[0], *(u8 *)(tramp + PAGESIZE - 1));
		pagedir_mapone(tramp, addr + 1, USED_PAGEDIR_PROT); /* Next page */
		pagedir_syncone(tramp);
		TRANSFER_RW(buf.bytes[1], *(u8 *)tramp);
		IFRD(result = buf.word);
	} else
#endif /* DEFINE_PHYS_UNALIGNED */
	{
#ifndef DEFINE_PHYS_UNALIGNED
		assertf((addr & 1) == 0, "Unaligned address %I64p", (u64)addr);
#endif /* !DEFINE_PHYS_UNALIGNED */
		/* Copy memory. */
		DORW_AND_CONTINUE(16, tramp + ((ptrdiff_t)addr & PAGEMASK));
	}
	pagedir_pop_mapone(tramp, backup);
	IFRD(return result);
}

PUBLIC NOBLOCK WUNUSED RETURN_TYPE(u32)
NOTHROW(KCALL FUNC(physl))(PHYS vm_phys_t addr VALUE_ARG(u32)) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	IFRD(u32 result;)
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(addr, 4))
		DORW_AND_RETURN(32, PHYS_TO_IDENTITY(addr));
#endif /* !NO_PHYS_IDENTITY */
	tramp  = THIS_TRAMPOLINE_BASE;
	backup = pagedir_push_mapone(tramp,
	                             addr & ~PAGEMASK,
	                             USED_PAGEDIR_PROT);
	pagedir_syncone(tramp);
#ifdef DEFINE_PHYS_UNALIGNED
	if unlikely((size_t)(addr & PAGEMASK) >= (PAGESIZE - 3)) {
		/* Read from 2 pages. */
		union {
			u32 dword;
			u16 words[2];
			u8 bytes[4];
		} buf;
		size_t bytes_in_first_page;
		bytes_in_first_page = PAGESIZE - (size_t)(addr & PAGEMASK);
		assert(bytes_in_first_page >= 1);
		assert(bytes_in_first_page <= 3);
		IFWR(buf.dword = value);
		if (bytes_in_first_page == 1) {
			assert(((uintptr_t)addr & PAGEMASK) == PAGESIZE - 1);
			TRANSFER_RW(buf.bytes[0], *(u8 *)(tramp + PAGESIZE - 1));
			pagedir_mapone(tramp, addr + 1, USED_PAGEDIR_PROT);
			pagedir_syncone(tramp);
			TRANSFER_RW(buf.bytes[1], *(u8 *)tramp);
			IFELSERW(buf.words[1] = UNALIGNED_GET16((u16 *)(tramp + 1)),
			         UNALIGNED_SET16((u16 *)(tramp + 1), buf.words[1]));
		} else if (bytes_in_first_page == 2) {
			assert(((uintptr_t)addr & PAGEMASK) == PAGESIZE - 2);
			TRANSFER_RW(buf.words[0], *(u16 *)(tramp + (PAGESIZE - 2)));
			pagedir_mapone(tramp, addr + 2, USED_PAGEDIR_PROT);
			pagedir_syncone(tramp);
			TRANSFER_RW(buf.words[1], *(u16 *)tramp);
		} else {
			assert(bytes_in_first_page == 3);
			assert(((uintptr_t)addr & PAGEMASK) == PAGESIZE - 3);
			IFELSERW(buf.words[0] = UNALIGNED_GET16((u16 *)(tramp + (PAGESIZE - 3))),
			         UNALIGNED_SET16((u16 *)(tramp + (PAGESIZE - 3)), buf.words[0]));
			TRANSFER_RW(buf.bytes[2], *(u8 *)(tramp + PAGESIZE - 1));
			pagedir_mapone(tramp, addr + 3, USED_PAGEDIR_PROT);
			pagedir_syncone(tramp);
			TRANSFER_RW(buf.bytes[3], *(u8 *)tramp);
		}
		IFRD(result = buf.dword);
	} else
#endif /* DEFINE_PHYS_UNALIGNED */
	{
#ifndef DEFINE_PHYS_UNALIGNED
		assertf((addr & 3) == 0, "Unaligned address %I64p", (u64)addr);
#endif /* !DEFINE_PHYS_UNALIGNED */
		/* Copy memory. */
		DORW_AND_CONTINUE(32, tramp + ((ptrdiff_t)addr & PAGEMASK));
	}
	pagedir_pop_mapone(tramp, backup);
	IFRD(return result);
}

PUBLIC NOBLOCK WUNUSED RETURN_TYPE(u64)
NOTHROW(KCALL FUNC(physq))(PHYS vm_phys_t addr VALUE_ARG(u64)) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	IFRD(u64 result;)
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(addr, 8))
		DORW_AND_RETURN(64, PHYS_TO_IDENTITY(addr));
#endif /* !NO_PHYS_IDENTITY */
	tramp  = THIS_TRAMPOLINE_BASE;
	backup = pagedir_push_mapone(tramp,
	                             addr & ~PAGEMASK,
	                             USED_PAGEDIR_PROT);
	pagedir_syncone(tramp);
#ifdef DEFINE_PHYS_UNALIGNED
	if unlikely((size_t)(addr & PAGEMASK) >= (PAGESIZE - 7)) {
		/* Read from 2 pages. */
		union {
			u64 qword;
			u32 dwords[2];
			u16 words[4];
			u8 bytes[8];
		} buf;
		size_t bytes_in_first_page, offset;
		offset              = (size_t)(addr & PAGEMASK);
		bytes_in_first_page = PAGESIZE - offset;
		assert(bytes_in_first_page >= 1);
		assert(bytes_in_first_page <= 7);
		IFWR(buf.qword = value);
		IFELSERW(memcpy(buf.bytes, (void *)(tramp + offset), bytes_in_first_page),
		         memcpy((void *)(tramp + offset), buf.bytes, bytes_in_first_page));
		pagedir_mapone(tramp, (addr + 7) & ~PAGEMASK, USED_PAGEDIR_PROT);
		pagedir_syncone(tramp);
		IFELSERW(memcpy(buf.bytes + bytes_in_first_page, (void *)tramp, 8 - bytes_in_first_page),
		         memcpy((void *)tramp, buf.bytes + bytes_in_first_page, 8 - bytes_in_first_page));
		IFRD(result = buf.qword);
	} else
#endif /* DEFINE_PHYS_UNALIGNED */
	{
#ifndef DEFINE_PHYS_UNALIGNED
		assertf((addr & 7) == 0, "Unaligned address %I64p", (u64)addr);
#endif /* !DEFINE_PHYS_UNALIGNED */
		/* Copy memory. */
		DORW_AND_CONTINUE(64, tramp + ((ptrdiff_t)addr & PAGEMASK));
	}
	pagedir_pop_mapone(tramp, backup);
	IFRD(return result);
}



DECL_END

#undef IFELSERW
#undef IFRD
#undef IFWR
#undef RETURN_TYPE
#undef VALUE_ARG
#undef FUNC3
#undef FUNC2
#undef FUNC
#undef DORW_AND_RETURN
#undef DORW_AND_CONTINUE
#undef USED_PAGEDIR_PROT
#undef TRANSFER_RW
#undef IFELSEAL
#undef DEFINE_PHYS_WRITE
#undef DEFINE_PHYS_READ
#undef DEFINE_PHYS_UNALIGNED
