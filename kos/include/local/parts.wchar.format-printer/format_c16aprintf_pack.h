/* HASH 0x49bef769 */
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
#ifndef __local_format_c16aprintf_pack_defined
#if ((__has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)) || defined(__CRT_HAVE_realloc))
#define __local_format_c16aprintf_pack_defined 1
#include <hybrid/__assert.h>

#include <hybrid/typecore.h>

#ifndef __format_c16aprintf_data_defined
#define __format_c16aprintf_data_defined 1
struct format_c16aprintf_data {
	__CHAR16_TYPE__      *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif /* !__format_waprintf_data_defined */
/* Dependency: "realloc" */
#ifndef ____localdep_realloc_defined
#define ____localdep_realloc_defined 1
#ifdef __std___localdep_realloc_defined
__NAMESPACE_STD_USING(__localdep_realloc)
#elif __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__FORCELOCAL __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL __localdep_realloc)(void *__mallptr, __SIZE_TYPE__ __n_bytes) { return __builtin_realloc(__mallptr, __n_bytes); }
#elif defined(__CRT_HAVE_realloc)
__CREDIRECT(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __n_bytes),realloc,(__mallptr,__n_bytes))
#else /* LIBC: realloc */
#undef ____localdep_realloc_defined
#endif /* realloc... */
#endif /* !____localdep_realloc_defined */

/* Dependency: "malloc" from "malloc" */
#ifndef ____localdep_malloc_defined
#define ____localdep_malloc_defined 1
#ifdef __std___localdep_malloc_defined
__NAMESPACE_STD_USING(__localdep_malloc)
#elif __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__FORCELOCAL __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL __localdep_malloc)(__SIZE_TYPE__ __n_bytes) { return __builtin_malloc(__n_bytes); }
#elif defined(__CRT_HAVE_malloc)
__CREDIRECT(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __n_bytes),malloc,(__n_bytes))
#elif (defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc))
#include <local/malloc/malloc.h>
#define __localdep_malloc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(malloc))
#else /* CUSTOM: malloc */
#undef ____localdep_malloc_defined
#endif /* malloc... */
#endif /* !____localdep_malloc_defined */

__NAMESPACE_LOCAL_BEGIN
/* Pack and finalize a given aprintf format printer
 * Together with `format_c16aprintf_printer()', the aprintf
 * format printer sub-system should be used as follows:
 * >> char *result; ssize_t error;
 * >> struct format_aprintf_data p = FORMAT_WAPRINTF_DATA_INIT;
 * >> error = format_c16printf(&format_c16aprintf_printer, &p, L"%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_waprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_c16aprintf_pack(&p, NULL);
 * >> return result;
 * WARNING: Note that `format_c16aprintf_pack()' is able to return `NULL' as well,
 *          but will finalize the given aprintf printer an all cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free()'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `c16len(return)' when NUL characters were
 *                  printed to the waprintf-printer at one point.
 *                  (e.g. `format_c16aprintf_printer(&my_printer, L"\0", 1)') */
__LOCAL_LIBC(format_c16aprintf_pack) __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_NONNULL((1)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(format_c16aprintf_pack))(struct format_c16aprintf_data *__restrict __self,
                                                                    __SIZE_TYPE__ *__pstrlen) {
#line 227 "kos/src/libc/magic/parts.wchar.format-printer.c"
	/* Free unused buffer memory. */
	__CHAR16_TYPE__ *__result;
	if (__self->ap_avail != 0) {
		__CHAR16_TYPE__ *__newbuf;
		__newbuf = (__CHAR16_TYPE__ *)__localdep_realloc(__self->ap_base,
		                         (__self->ap_used + 1) * sizeof(__CHAR16_TYPE__));
		if __likely(__newbuf)
			__self->ap_base = __newbuf;
	} else {
		if __unlikely(!__self->ap_used) {
			/* Special case: Nothing was printed. */
			__hybrid_assert(!__self->ap_base);
#ifdef __CRT_HAVE_malloc
			__self->ap_base = (__CHAR16_TYPE__ *)__localdep_malloc(1 * sizeof(__CHAR16_TYPE__));
#else /* __CRT_HAVE_malloc */
			__self->ap_base = (__CHAR16_TYPE__ *)__localdep_realloc(__NULLPTR, 1 * sizeof(__CHAR16_TYPE__));
#endif /* !__CRT_HAVE_malloc */
			if __unlikely(!__self->ap_base)
				return __NULLPTR;
		}
	}
	__result = __self->ap_base;
	__hybrid_assert(__result);
	__result[__self->ap_used] = '\0'; /* NUL-terminate */
	if (__pstrlen)
		*__pstrlen = __self->ap_used;
#ifndef __NDEBUG
#if __SIZEOF_POINTER__ == 4
	__self->ap_base  = (__CHAR16_TYPE__ *)__UINT32_C(0xcccccccc);
	__self->ap_avail = __UINT32_C(0xcccccccc);
	__self->ap_used  = __UINT32_C(0xcccccccc);
#elif __SIZEOF_POINTER__ == 8
	__self->ap_base  = (__CHAR16_TYPE__ *)__UINT64_C(0xcccccccccccccccc);
	__self->ap_avail = __UINT64_C(0xcccccccccccccccc);
	__self->ap_used  = __UINT64_C(0xcccccccccccccccc);
#endif /* __SIZEOF_POINTER__ == ... */
#endif /* !NDEBUG */
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* ((__has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)) || defined(__CRT_HAVE_realloc)) */
#endif /* !__local_format_c16aprintf_pack_defined */
