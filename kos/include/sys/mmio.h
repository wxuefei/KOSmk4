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
#ifndef _SYS_MMIO_H
#define _SYS_MMIO_H 1

#include <__stdinc.h>
#include <__crt.h>

#include <hybrid/typecore.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __COMPILER_ASM_BUFFER
#define __COMPILER_ASM_BUFFER(T, s, p) (*(T *)(p))
#endif /* !__COMPILER_ASM_BUFFER */

#ifndef __MEMPORT_T
#define __MEMPORT_T __UINTPTR_TYPE__
#endif /* !__MEMPORT_T */

#ifndef __MEMPORT_CONST_T
#define __MEMPORT_CONST_T __MEMPORT_T
#endif /* !__MEMPORT_CONST_T */

#if defined(__INTELLISENSE__) && defined(__cplusplus)
#undef __MEMPORT_T
#undef __MEMPORT_CONST_T
#define __MEMPORT_T       __NAMESPACE_INT_SYM ____INTELLISENSE_memport_t
#define __MEMPORT_CONST_T __NAMESPACE_INT_SYM ____INTELLISENSE_memport_const_t
__NAMESPACE_INT_BEGIN
extern "C++" {
class ____INTELLISENSE_memport_t {
public:
	template<class __T> ____INTELLISENSE_memport_t(__T *);
	____INTELLISENSE_memport_t(__UINTPTR_TYPE__);
};
class ____INTELLISENSE_memport_const_t {
public:
	template<class __T> ____INTELLISENSE_memport_const_t(__T const *);
	____INTELLISENSE_memport_const_t(__UINTPTR_TYPE__);
};
}
__NAMESPACE_INT_END

__UINT8_TYPE__ __NOTHROW(__LIBCCALL peekb)(__MEMPORT_T __addr);
void __NOTHROW(__LIBCCALL pokeb)(__MEMPORT_T __addr, __UINT8_TYPE__ __val);
__ATTR_NONNULL((2)) void __NOTHROW(__LIBCCALL peeksb)(__MEMPORT_T __addr, void *__buf, __SIZE_TYPE__ __n_bytes);
__ATTR_NONNULL((2)) void __NOTHROW(__LIBCCALL pokesb)(__MEMPORT_T __addr, void const *__buf, __SIZE_TYPE__ __n_bytes);
#if __SIZEOF_BUSINT__ >= 2
__UINT16_TYPE__ __NOTHROW(__LIBCCALL peekw)(__MEMPORT_T __addr);
void __NOTHROW(__LIBCCALL pokew)(__MEMPORT_T __addr, __UINT16_TYPE__ __val);
__ATTR_NONNULL((2)) void __NOTHROW(__LIBCCALL peeksw)(__MEMPORT_T __addr, void *__buf, __SIZE_TYPE__ __n_words);
__ATTR_NONNULL((2)) void __NOTHROW(__LIBCCALL pokesw)(__MEMPORT_T __addr, void const *__buf, __SIZE_TYPE__ __n_words);
#endif /* __SIZEOF_BUSINT__ >= 2 */
#if __SIZEOF_BUSINT__ >= 4
__UINT32_TYPE__ __NOTHROW(__LIBCCALL peekl)(__MEMPORT_T __addr);
void __NOTHROW(__LIBCCALL pokel)(__MEMPORT_T __addr, __UINT32_TYPE__ __val);
__ATTR_NONNULL((2)) void __NOTHROW(__LIBCCALL peeksl)(__MEMPORT_T __addr, void *__buf, __SIZE_TYPE__ __n_dwords);
__ATTR_NONNULL((2)) void __NOTHROW(__LIBCCALL pokesl)(__MEMPORT_T __addr, void const *__buf, __SIZE_TYPE__ __n_dwords);
#endif /* __SIZEOF_BUSINT__ >= 4 */
#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
__UINT64_TYPE__ __NOTHROW(__LIBCCALL peekq)(__MEMPORT_T __addr);
__ATTR_NONNULL((2)) void __NOTHROW(__LIBCCALL peeksq)(__MEMPORT_T __addr, void *__buf, __SIZE_TYPE__ __n_qword);
void __NOTHROW(__LIBCCALL pokeq)(__MEMPORT_T __addr, __UINT64_TYPE__ __val);
__ATTR_NONNULL((2)) void __NOTHROW(__LIBCCALL pokesq)(__MEMPORT_T __addr, void const *__buf, __SIZE_TYPE__ __n_qword);
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */

#else /* __INTELLISENSE__ && __cplusplus */

#define peekb(port) peekb((__MEMPORT_T)(port))
__FORCELOCAL __UINT8_TYPE__
__NOTHROW_NCX(__LIBCCALL peekb)(__MEMPORT_T __addr) {
	__COMPILER_READ_BARRIER();
	return *(__UINT8_TYPE__ volatile const *)__addr;
}

#define peeksb(port, addr, num_bytes) peeksb((__MEMPORT_T)(port), addr, num_bytes)
__FORCELOCAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(__LIBCCALL peeksb)(__MEMPORT_T __addr,
                                 void *__buf,
                                 __SIZE_TYPE__ __num_bytes) {
	__COMPILER_READ_BARRIER();
	for (; __num_bytes; --__num_bytes, __buf = (__UINT8_TYPE__ *)__buf + 1) {
		*(__UINT8_TYPE__ *)__buf = *(__UINT8_TYPE__ volatile const *)__addr;
	}
}

#define pokeb(port, val) pokeb((__MEMPORT_T)(port), val)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL pokeb)(__MEMPORT_T __addr, __UINT8_TYPE__ __val) {
	*(__UINT8_TYPE__ volatile *)__addr = __val;
	__COMPILER_WRITE_BARRIER();
}

#define pokesb(port, addr, num_bytes) pokesb((__MEMPORT_T)(port), addr, num_bytes)
__FORCELOCAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(__LIBCCALL pokesb)(__MEMPORT_T __addr,
                                 void const *__buf,
                                 __SIZE_TYPE__ __num_bytes) {
	for (; __num_bytes; --__num_bytes, __buf = (__UINT8_TYPE__ *)__buf + 1) {
		*(__UINT8_TYPE__ volatile *)__addr = *(__UINT8_TYPE__ *)__buf;
	}
	__COMPILER_WRITE_BARRIER();
}

#if __SIZEOF_BUSINT__ >= 2
#define peekw(port) peekw((__MEMPORT_T)(port))
__FORCELOCAL __UINT16_TYPE__
__NOTHROW_NCX(__LIBCCALL peekw)(__MEMPORT_T __addr) {
	__COMPILER_READ_BARRIER();
	return *(__UINT16_TYPE__ volatile const *)__addr;
}

#define peeksw(port, addr, num_words) peeksw((__MEMPORT_T)(port), addr, num_words)
__FORCELOCAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(__LIBCCALL peeksw)(__MEMPORT_T __addr,
                                 void *__buf,
                                 __SIZE_TYPE__ __num_words) {
	__COMPILER_READ_BARRIER();
	for (; __num_words; --__num_words, __buf = (__UINT16_TYPE__ *)__buf + 1) {
		*(__UINT16_TYPE__ *)__buf = *(__UINT16_TYPE__ volatile const *)__addr;
	}
}

#define pokew(port, val) pokew((__MEMPORT_T)(port), val)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL pokew)(__MEMPORT_T __addr, __UINT16_TYPE__ __val) {
	*(__UINT16_TYPE__ volatile *)__addr = __val;
	__COMPILER_WRITE_BARRIER();
}

#define pokesw(port, addr, num_words) pokesw((__MEMPORT_T)(port), addr, num_words)
__FORCELOCAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(__LIBCCALL pokesw)(__MEMPORT_T __addr,
                                 void const *__buf,
                                 __SIZE_TYPE__ __num_words) {
	for (; __num_words; --__num_words, __buf = (__UINT16_TYPE__ *)__buf + 1) {
		*(__UINT16_TYPE__ volatile *)__addr = *(__UINT16_TYPE__ *)__buf;
	}
	__COMPILER_WRITE_BARRIER();
}
#endif /* __SIZEOF_BUSINT__ >= 2 */

#if __SIZEOF_BUSINT__ >= 4
#define peekl(port) peekl((__MEMPORT_T)(port))
__FORCELOCAL __UINT32_TYPE__
__NOTHROW_NCX(__LIBCCALL peekl)(__MEMPORT_T __addr) {
	__COMPILER_READ_BARRIER();
	return *(__UINT32_TYPE__ volatile const *)__addr;
}

#define peeksl(port, addr, num_dwords) peeksl((__MEMPORT_T)(port), addr, num_dwords)
__FORCELOCAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(__LIBCCALL peeksl)(__MEMPORT_T __addr,
                                 void *__buf,
                                 __SIZE_TYPE__ __num_dwords) {
	__COMPILER_READ_BARRIER();
	for (; __num_dwords; --__num_dwords, __buf = (__UINT32_TYPE__ *)__buf + 1) {
		*(__UINT32_TYPE__ *)__buf = *(__UINT32_TYPE__ volatile const *)__addr;
	}
}

#define pokel(port, val) pokel((__MEMPORT_T)(port), val)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL pokel)(__MEMPORT_T __addr, __UINT32_TYPE__ __val) {
	*(__UINT32_TYPE__ volatile *)__addr = __val;
	__COMPILER_WRITE_BARRIER();
}

#define pokesl(port, addr, num_dwords) pokesl((__MEMPORT_T)(port), addr, num_dwords)
__FORCELOCAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(__LIBCCALL pokesl)(__MEMPORT_T __addr,
                                 void const *__buf,
                                 __SIZE_TYPE__ __num_dwords) {
	for (; __num_dwords; --__num_dwords, __buf = (__UINT32_TYPE__ *)__buf + 1) {
		*(__UINT32_TYPE__ volatile *)__addr = *(__UINT32_TYPE__ *)__buf;
	}
	__COMPILER_WRITE_BARRIER();
}
#endif /* __SIZEOF_BUSINT__ >= 4 */

#if __SIZEOF_BUSINT__ >= 8 && defined(__UINT64_TYPE__)
#define peekq(port) peekq((__MEMPORT_T)(port))
__FORCELOCAL __UINT64_TYPE__
__NOTHROW_NCX(__LIBCCALL peekq)(__MEMPORT_T __addr) {
	__COMPILER_READ_BARRIER();
	return *(__UINT64_TYPE__ volatile const *)__addr;
}

#define peeksq(port, addr, num_qwords) peeksq((__MEMPORT_T)(port), addr, num_qwords)
__FORCELOCAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(__LIBCCALL peeksq)(__MEMPORT_T __addr,
                                 void *__buf,
                                 __SIZE_TYPE__ __num_qwords) {
	__COMPILER_READ_BARRIER();
	for (; __num_qwords; --__num_qwords, __buf = (__UINT64_TYPE__ *)__buf + 1) {
		*(__UINT64_TYPE__ *)__buf = *(__UINT64_TYPE__ volatile const *)__addr;
	}
}

#define pokeq(port, val) pokeq((__MEMPORT_T)(port), val)
__FORCELOCAL void
__NOTHROW_NCX(__LIBCCALL pokeq)(__MEMPORT_T __addr, __UINT64_TYPE__ __val) {
	*(__UINT64_TYPE__ volatile *)__addr = __val;
	__COMPILER_WRITE_BARRIER();
}

#define pokesq(port, addr, num_qwords) pokesq((__MEMPORT_T)(port), addr, num_qwords)
__FORCELOCAL __ATTR_NONNULL((2)) void
__NOTHROW_NCX(__LIBCCALL pokesq)(__MEMPORT_T __addr,
                                 void const *__buf,
                                 __SIZE_TYPE__ __num_qwords) {
	for (; __num_qwords; --__num_qwords, __buf = (__UINT64_TYPE__ *)__buf + 1) {
		*(__UINT64_TYPE__ volatile *)__addr = *(__UINT64_TYPE__ *)__buf;
	}
	__COMPILER_WRITE_BARRIER();
}
#endif /* __SIZEOF_BUSINT__ >= 8 && __UINT64_TYPE__ */

#endif /* !__INTELLISENSE__ || !__cplusplus */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_MMIO_H */