/* HASH CRC-32:0x49f5b0dc */
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
#ifndef __local__recalloc_dbg_defined
#if defined(__CRT_HAVE__recalloc)
#define __local__recalloc_dbg_defined 1
/* Dependency: "_recalloc" */
#ifndef ____localdep__recalloc_defined
#define ____localdep__recalloc_defined 1
#if defined(__CRT_HAVE__recalloc)
__CREDIRECT(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,__localdep__recalloc,(void *__mptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes),_recalloc,(__mptr,__count,__num_bytes))
#else /* LIBC: _recalloc */
#undef ____localdep__recalloc_defined
#endif /* _recalloc... */
#endif /* !____localdep__recalloc_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_recalloc_dbg) __ATTR_ALLOC_SIZE((2, 3)) __ATTR_WUNUSED void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_recalloc_dbg))(void *__ptr,
                                                           __SIZE_TYPE__ __count,
                                                           __SIZE_TYPE__ __num_bytes,
                                                           int __block_type,
                                                           char const *__filename,
                                                           int __line) {
#line 314 "kos/src/libc/magic/crtdbg.c"
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return __localdep__recalloc(__ptr, __count, __num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE__recalloc) */
#endif /* !__local__recalloc_dbg_defined */