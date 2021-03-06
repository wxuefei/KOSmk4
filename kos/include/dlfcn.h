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
#ifndef _DLFCN_H
#define _DLFCN_H 1

#include "__crt.h"
#include "__stdinc.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <libdl/asm/dlfcn.h>
#include <libdl/bits/dlfcn.h>
#include <bits/types.h>

/* NOTE: To use anything from this file, you must link with '-ldl',
 *       Though also note that then using the gcc from the KOS toolchain,
 *       -ldl will be included as one of the default libraries to link
 *       against, the same way that -lc is also one of those default
 *       libraries. */


#if (defined(__USE_KOS) && defined(__DLCACHES_SECTION_NAME) && \
     defined(__ELF__) && !defined(__KERNEL__))
#include <hybrid/__asm.h>
#include <hybrid/typecore.h>

#include <asm/asmword.h> /* .wordrel */

/* Register a cache-clear function to-be invoked
 * when system/application memory starts to run out.
 * The prototype of such a function looks like:
 * >> DECL_BEGIN // Needs to be declared with `extern "C"' in c++-mode
 * >> DL_REGISTER_CACHE(my_cache_clear_function);
 * >> PRIVATE int my_cache_clear_function(void) {
 * >>     if (clear_my_caches() != NO_CACHES_CLEARED)
 * >>         return 1; // Hint that memory may have become available.
 * >>     return 0;     // Hint that no additional memory became available.
 * >> }
 * >> DECL_END
 * Functions registered like this from all loaded modules will be executed
 * when `dlclearcaches()' is called (which is called when mmap() fails due
 * to lack of memory, which itself is called when malloc() needs to allocate
 * more memory, where failure to acquire some would normally result in it
 * returning NULL. - So long as any one of the DL-cache functions returns
 * non-zero, the mmap() operation will be re-attempted a limited number of
 * times) */
#define DL_REGISTER_CACHE(func)                       \
	__ASM_BEGIN                                       \
	__ASM_L(.pushsection __DLCACHES_SECTION_NAME, "") \
	__ASM_L(	.align __SIZEOF_POINTER__)            \
	__ASM_L(	.wordrel func)                        \
	__ASM_L(.popsection)                              \
	__ASM_END                                         \
	__PRIVATE __ATTR_USED int (func)(void)
#endif /* __USE_KOS && __DLCACHES_SECTION_NAME && __ELF__ && !__KERNEL__ */

#ifndef __DLFCN_CC
#define __DLFCN_CC  __LIBCCALL
#define __DLFCN_VCC __VLIBCCALL
#endif /* !__DLFCN_CC */

/* The MODE argument to `dlopen(3)' must contain one of the following: */
#ifdef __RTLD_LAZY
#define RTLD_LAZY __RTLD_LAZY /* Lazy function call binding. */
#endif /* __RTLD_LAZY */
#ifdef __RTLD_NOW
#define RTLD_NOW __RTLD_NOW /* Immediate function call binding. */
#endif /* __RTLD_NOW */
#ifdef __RTLD_BINDING_MASK
#define RTLD_BINDING_MASK __RTLD_BINDING_MASK /* Mask of binding time value. */
#endif /* __RTLD_BINDING_MASK */


/* The MODE argument to `dlopen(3)' must contain one of the following: */
#ifdef __RTLD_GLOBAL
#define RTLD_GLOBAL __RTLD_GLOBAL /* If the following bit is set in the MODE argument to `dlopen',
                                   * the symbols of the loaded object and its dependencies are made
                                   * visible as if the object were linked directly into the program. */
#endif /* __RTLD_GLOBAL */
#ifdef __RTLD_LOCAL
#define RTLD_LOCAL __RTLD_LOCAL /* Unix98 demands the following flag which is the inverse to RTLD_GLOBAL. */
#endif /* __RTLD_LOCAL */



/* The MODE argument to `dlopen(3)' may optionally contain any of the following: */
#ifdef __RTLD_NOLOAD
#define RTLD_NOLOAD __RTLD_NOLOAD /* Do not load the object. */
#endif /* __RTLD_NOLOAD */

/* If the associated library uses a symbol that it itself also defines,
 * the the library will use its own symbol, rather than go through the
 * global scope to find the first (primary) definition of some symbol.
 * e.g.:
 *    - libfoo: (linked against `libc.so')
 *       >> PUBLIC void *memcpy(void *dst, void const *src, size_t num_bytes) { ... }
 *       >> PUBLIC void foo() {
 *       >>     memcpy(a, b, 42);
 *       >> }
 *    - libc:
 *       >> PUBLIC void *memcpy(void *dst, void const *src, size_t num_bytes) { ... }
 * - When `libfoo' is loaded without `RTLD_DEEPBIND', its function
 *   `foo' will be using the memcpy() function provided by libc.so
 * - When `libfoo' is loaded with `RTLD_DEEPBIND', its function
 *   `foo' will be using the memcpy() function it defines itself.
 * NOTE: This is the same as the ELF tag `DF_SYMBOLIC' */
#ifdef __RTLD_DEEPBIND
#define RTLD_DEEPBIND __RTLD_DEEPBIND /* Use deep binding. */
#endif /* __RTLD_DEEPBIND */

#ifdef __RTLD_NODELETE
#define RTLD_NODELETE __RTLD_NODELETE /* Do not delete object when closed. */
#endif /* __RTLD_NODELETE */

#ifdef __USE_KOS
#ifdef __RTLD_NOINIT
#define RTLD_NOINIT __RTLD_NOINIT /* KOS Extension: Don't run module initializers, and consequently
                                   *                skip running finalizers as well.
                                   * When set, `dlopen()' will immeditaly return to the caller upon success,
                                   * rather than running initializers of all affected libraries first.
                                   * HINT: You may run initializers (and finalizers during exit()) at a
                                   *       later time by calling `dlopen()' again without passing this flag.
                                   * WARNING: Initializers of newly loaded dependencies will not be executed either! */
#endif /* __RTLD_NOINIT */
#endif /* __USE_KOS */


#ifdef __USE_GNU
/* If the first argument of `dlsym' or `dlvsym' is set to RTLD_NEXT
 * the run-time address of the symbol called NAME in the next shared
 * object is returned. The "next" relation is defined by the order
 * the shared objects were loaded.
 * Or for the C-savvy:
 *     `RTLD_DEFAULT' <==> `#include'
 *     `RTLD_NEXT'    <==> `#include_next' */
#ifdef __RTLD_NEXT
#define RTLD_NEXT __RTLD_NEXT
#endif /* __RTLD_NEXT */

/* If the first argument to `dlsym' or `dlvsym' is set to RTLD_DEFAULT
 * the run-time address of the symbol called NAME in the global scope
 * is returned.
 * HINT: The global scope is the same as that of the root executable, as seen
 *       under /proc/PID/exe (or as returned by `dlmodulename(dlopen(NULL, 0))'. */
#ifdef __RTLD_DEFAULT
#define RTLD_DEFAULT __RTLD_DEFAULT
#endif /* __RTLD_DEFAULT */

/* Special namespace ID values. */
#ifdef __LM_ID_BASE
#define LM_ID_BASE __LM_ID_BASE /* Initial namespace. */
#endif /* __LM_ID_BASE */
#ifdef __LM_ID_NEWLM
#define LM_ID_NEWLM __LM_ID_NEWLM /* For dlmopen: request new namespace. */
#endif /* __LM_ID_NEWLM */
#endif /* __USE_GNU */



__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifdef __USE_GNU
/* Type for namespace indices. */
#ifdef __Lmid_t
typedef __Lmid_t Lmid_t;
#endif /* __Lmid_t */
#endif /* __USE_GNU */


/* Lazily load a shared library file, and return a handle to said file.
 * @param: FILENAME: The filename of the shared library.
 *                   If this string contains at least 1 '/'-character,
 *                   the string will be interpreted as a raw filename,
 *                   such that passing it to open(2) would return a file
 *                   handle for the named library file.
 *                   In this case, `FILENAME' may either be an absolute path,
 *                   or a path relative to the current working directory, as
 *                   set by `chdir(2)'
 *                   If `FILENAME' doesn't contain any '/'-characters, the string
 *                   is the filename of the library (e.g. "libc.so"), and will be
 *                   searched for in the set of system library locations, as specified
 *                   by a ':'-separated string read from `getenv("LD_LIBRARY_PATH")'
 *                   at the time of the process having been started, or defaulting to
 *                   a set of paths that include at least "/usr/lib:/lib" in that order.
 *                   When `NULL' is passed for this argument, a handle for the main
 *                   executable module (i.e. the `readlink /proc/self/exe` binary) is
 *                   returned.
 * @param: MODE:     Exactly one of [RTLD_LAZY, RTLD_NOW], or'd with
 *                   exactly one of [RTLD_GLOBAL, RTLD_LOCAL], optionally
 *                   or'd with any of the other `RTLD_*' flags.
 * @return: * :   A handle to the library that got loaded.
 * @return: NULL: Failed to load the library. - Call `dlerror()' to get an error message. */
#ifdef __CRT_HAVE_dlopen
__IMPDEF __ATTR_WUNUSED void *__NOTHROW_NCX(__DLFCN_CC dlopen)(char const *__filename, int __mode);
#endif /* __CRT_HAVE_dlopen */

/* Close a previously opened dynamic module handle, as returned by
 * `dlopen()', and some of the other functions found in this file.
 * Note that this call is implemented as a decref() operation, since
 * multiple calls to `dlopen()' for the same library will try to ensure
 * that only a single instance of some unique library is ever loaded
 * at the same time. However, every call to `dlopen()' should eventually
 * be followed by a call to `dlclose()' with that same handle, such that
 * once some specific handle is closed for the last time, the library can
 * be unloaded.
 * Note also that if this function does actually unload a library, user-
 * defined callbacks may be invoked, including `__attribute__((destructor))'
 * callbacks, as well as callbacks registered dynamically through use of
 * `DLAUXCTRL_ADD_FINALIZER' (which in turn is used by `__cxa_atexit()')
 * @return: 0 : Successfully closed the given HANDLE.
 * @return: * : Failed to close the handle (which is likely to simply be
 *              invalid; s.a. `dlerror()') Warning: Don't just willy-nilly
 *              pass invalid handles to this function. Depending on how
 *              libdl was configured, only minimal validation may be
 *              performed. The only guaranty made is that NULL-handles
 *              are always handled as fail-safe! */
#ifdef __CRT_HAVE_dlclose
__IMPDEF __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__DLFCN_CC dlclose)(void *__handle);
#endif /* __CRT_HAVE_dlclose */

/* Lookup the load address of a symbol within a shared library `HANDLE',
 * given its `SYMBOL_NAME'. If no such symbol exists, `NULL' is returned,
 * and `dlerror()' is modified to return a human-readable error message.
 * WARNING: If the actual address of the symbol is `NULL', then this
 *          function will still return `NULL', though will not modify
 *          the return value of `dlerror()'.
 *          In normal applications, this would normally never be the case,
 *          as libdl, as well as `ld' will take care not to link object
 *          files such that symbols could end up overlapping with `NULL'.
 *          However, with the existence of `STT_GNU_IFUNC' (as usable
 *          via `__attribute__((ifunc("resolver")))'), it is easily possible
 *          to force some symbol to overlap with NULL.
 *          Also note that upon success, `dlerror()' will not have been
 *          modified, meaning that if a prior error has yet to be consumed,
 *          a NULL return value, and a non-NULL `dlerror()' may still not
 *          guaranty that the symbol really doesn't exist. To be absolutely
 *          certain that NULL would be correct, use the following:
 *          >> void *result;
 *          >> dlerror();
 *          >> result = dlsym(handle, symbol_name);
 *          >> if (result == NULL) {
 *          >>     char *message = dlerror();
 *          >>     if (message != NULL) // Symbol lookup really failed.
 *          >>         fprintf(stderr, "dlerror: %s\n", message);
 *          >> }
 * @param: HANDLE: The dynamic library handle of the library which should be
 *                 search for the specified `SYMBOL_NAME', before moving on
 *                 to also search all of that libraries dependencies for the
 *                 same `SYMBOL_NAME', and moving on to search those libraries
 *                 dependencies, following a breadth-first search approach.
 *                 Alternatively, you may also pass `RTLD_DEFAULT' or `RTLD_NEXT'
 *                 to make use of special symbol lookup resolutions documented
 *                 more extensively alongside these constants.
 * @return: * :    The address of the symbol in question.
 * @return: NULL:  No such symbol (dlerror() != NULL), or the symbol has been
 *                 linked to be loaded at the address `NULL' (dlerror() == NULL) */
#ifdef __CRT_HAVE_dlsym
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((2)) void *
__NOTHROW_NCX(__DLFCN_CC dlsym)(void *__handle, char const *__restrict __symbol_name);
#elif defined(__CRT_HAVE_dlfunc)
__COMPILER_REDIRECT(__IMPDEF,__ATTR_WUNUSED __ATTR_NONNULL((2)),void *,__NOTHROW_NCX,__DLFCN_CC,
                    dlsym,(void *__handle, char const *__restrict __symbol_name),dlfunc,(__handle,__symbol_name))
#endif /* ... */

/* Return and clear the current libdl error message string, such that for
 * any error that occurs, this function will only returns non-NULL once.
 * The returned string has a human-readable format and is generated dynamically,
 * meaning that it may contain information that is more specific than a simple
 * `File or directory not found' message, but rather something along the lines
 * of `Symbol "foo" could not be found in library "libfoo.so"'.
 * The implementation of this function looks like:
 * >> return ATOMIC_XCH(error_message_pointer, NULL);
 * Where internally, libdl will set `error_message_pointer' to a non-NULL pointer
 * when an error happens.
 * @return: * :   A pointer to a volatile (as in: the same memory area may be
 *                overwritten once the next dl-error happens in either the calling,
 *                !_or any other thread_!), human-readable description of the last
 *                error that happened during execution of any of the functions
 *                exported from libdl.
 * @return: NULL: No error happened, or the last error has already been consumed. */
#ifdef __CRT_HAVE_dlerror
__IMPDEF __ATTR_WUNUSED char *__NOTHROW_NCX(__DLFCN_CC dlerror)(void);
#endif /* __CRT_HAVE_dlerror */


#ifdef __USE_BSD
struct __dlfunc_arg { int __dlfunc_dummy; };
typedef void (*dlfunc_t)(struct __dlfunc_arg);

/* Alias for `dlsym()' that allows the return value to be cast to a function
 * prototype without resulting in a compiler warning due to a non-compliance
 * with official C standards (since C says that casting between a function
 * pointer and a data-pointer (such as `void *') results in undefined behavior,
 * though also note that the POSIX standard (due to this exact short-coming)
 * extends upon this by specifying that no data is lost when such a cast is
 * performed) */
#ifdef __CRT_HAVE_dlsym
__COMPILER_REDIRECT(__IMPDEF,__ATTR_WUNUSED __ATTR_NONNULL((2)),dlfunc_t,__NOTHROW_NCX,__DLFCN_CC,
                    dlfunc,(void *__handle, char const *__restrict __symbol_name),dlsym,(__handle,__symbol_name))
#elif defined(__CRT_HAVE_dlfunc)
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((2)) dlfunc_t
__NOTHROW_NCX(__DLFCN_CC dlfunc)(void *__handle, char const *__restrict __symbol_name);
#endif /* ... */
#endif /* __USE_BSD */

/* BSD also has a function `fdlopen()' that does the same as our's does. */
#if defined(__USE_KOS) || defined(__USE_BSD)
/* Open a library, given a file descriptor previously acquired by `open()'
 * NOTE: This function will inherit the given `FD' on success.
 * @param: FD:   The file descriptor to use & inhert for the shared library
 * @param: MODE: Exactly one of [RTLD_LAZY, RTLD_NOW], or'd with
 *               exactly one of [RTLD_GLOBAL, RTLD_LOCAL], optionally
 *               or'd with any of the other `RTLD_*' flags. */
#ifdef __CRT_HAVE_dlfopen
__COMPILER_REDIRECT(__IMPDEF,__ATTR_WUNUSED,void *,__NOTHROW_NCX,__DLFCN_CC,
                    fdlopen,(/*inherit(on_success)*/ __fd_t __fd, int __mode),dlfopen,(__fd,__mode))
#elif defined(__CRT_HAVE_fdlopen)
__IMPDEF __ATTR_WUNUSED void *__NOTHROW_NCX(__DLFCN_CC fdlopen)(/*inherit(on_success)*/ __fd_t __fd, int __mode);
#endif /* ... */
#endif /* __USE_KOS || __USE_BSD */


#ifdef __USE_KOS
/* New DL Functions added with KOSmk4 */

/* Check if a given module is exception aware.
 * TODO: Figure out how we want to detect this condition...
 * @param: HANDLE: The module to check
 * @return: 1 : The given module is exception aware
 * @return: 0 : The given module isn't exception aware
 * @return: * : The given module handler is invalid (s.a. `dlerror()') */
#ifdef __CRT_HAVE_dlexceptaware
__IMPDEF __ATTR_WUNUSED int
__NOTHROW_NCX(__DLFCN_CC dlexceptaware)(void *__handle);
#endif /* __CRT_HAVE_dlexceptaware */


#if (defined(__CRT_HAVE_dlgethandle) || defined(__CRT_HAVE_dlgetmodule) || \
     defined(__CRT_HAVE_dlsectionmodule))
#define DLGETHANDLE_FNORMAL 0x0000 /* Return weak pointer to a module handle */
#define DLGETHANDLE_FINCREF 0x0001 /* Return a new reference, that must be closed by `dlclose(return)' */
#ifdef __CRT_HAVE_dlgetmodule
#define DLGETHANDLE_FNOCASE 0x0002 /* For `dlgetmodule()': Ignore casing when comparing module names. */
#endif /* __CRT_HAVE_dlgetmodule */
#endif /* ... */

/* Return the handle of an already loaded library, given a static data/text pointer
 * @param: FLAGS: Set of `DLGETHANDLE_F*' */
#ifdef __CRT_HAVE_dlgethandle
__IMPDEF __ATTR_WUNUSED void *
__NOTHROW_NCX(__DLFCN_CC dlgethandle)(void const *__static_pointer,
                                      unsigned int __flags __DFL(DLGETHANDLE_FNORMAL));
#endif /* __CRT_HAVE_dlgethandle */

/* Return the handle of an already loaded library, given its name
 * @param: NAME:  One of the following (checked in this order):
 *                 - "/lib/libc.so"
 *                 - "libc.so"
 *                 - "libc"
 *                 - "c"
 *                 - "/LIB/LIBC.SO"  (requires `DLGETHANDLE_FNOCASE')
 *                 - "LIBC.SO"       (requires `DLGETHANDLE_FNOCASE')
 *                 - "LIBC"          (requires `DLGETHANDLE_FNOCASE')
 *                 - "C"             (requires `DLGETHANDLE_FNOCASE')
 *                Alternatively, `NULL' can be passed to return a handle for the caller's module.
 * @param: FLAGS: Set of `DLGETHANDLE_F*' */
#ifdef __CRT_HAVE_dlgetmodule
__IMPDEF __ATTR_WUNUSED void *
__NOTHROW_NCX(__DLFCN_CC dlgetmodule)(char const *__name,
                                      unsigned int __flags __DFL(DLGETHANDLE_FNORMAL));
#endif /* __CRT_HAVE_dlgetmodule */

/* Return the internally used file descriptor for the given module `HANDLE'
 * Note however that this descriptor is usually only opened for reading!
 * @param: HANDLE: A handle returned by `dlopen()'.
 * @return: * : An open file descriptor for the given module `HANDLE'
 *              WARNING: Attempting to close() this handle may cause future
 *                       operations performed with the associated module to fail!
 *                       Additionally, using dlclose() to close `HANDLE' after the
 *                       module's FD was already closed will attempt to re-close
 *                       that same FD, possibly closing some other handle if the
 *                       same slot was re-used in the mean time.
 * @return: * : Error (s.a. `dlerror()') */
#ifdef __CRT_HAVE_dlmodulefd
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t
__NOTHROW_NCX(__DLFCN_CC dlmodulefd)(void *__handle);
#endif /* __CRT_HAVE_dlmodulefd */

/* Return the internally used filename for the given module `HANDLE'
 * Note that this path is an absolute, canonical (realpath()) filename.
 * @param: HANDLE: A handle returned by `dlopen()'.
 * @return: * :    The absolute, unambiguous filename for the given module `HANDLE'
 * @return: NULL:  Error (s.a. `dlerror()') */
#ifdef __CRT_HAVE_dlmodulename
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *
__NOTHROW_NCX(__DLFCN_CC dlmodulename)(void *__handle);
#endif /* __CRT_HAVE_dlmodulename */

/* Return the base address offset chosen by ASLR, which is added to addresses of the given module `HANDLE'.
 * WARNING: This function usually returns `NULL' for the root executable, in which case dlerror()
 *          is not modified, meaning that in order to safely use this function, you must first
 *          call `dlerror()' in order to clear any existing errors, then invoke this function,
 *          and call `dlerror()' again when NULL is returned to check if an error really occurred.
 *          Or alternatively, you can simply make sure that `HANDLE' isn't invalid, since the
 *          only case when this function can ever fail is when `HANDLE' was already closed, is
 *         `NULL', or isn't a pointer returned by `dlopen()', `dlgetmodule()' or `dlgethandle()'
 * @param: HANDLE: A handle returned by `dlopen()'.
 * @return: * :    The load address / module base for the given `HANDLE'.
 * @return: NULL:  Error (s.a. `dlerror()') */
#ifdef __CRT_HAVE_dlmodulebase
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__DLFCN_CC dlmodulebase)(void *__handle);
#endif /* __CRT_HAVE_dlmodulebase */



#if (defined(__CRT_HAVE_dllocksection) || defined(__CRT_HAVE_dlunlocksection) || \
     defined(__CRT_HAVE_dlsectionname) || defined(__CRT_HAVE_dlsectionindex) ||  \
     defined(__CRT_HAVE_dlsectionmodule))
#ifndef __dl_section_defined
#define __dl_section_defined 1
struct dl_section {
	void       *const ds_data;    /* [0..ds_size][const] Memory mapping for the section's contents. */
	__size_t    const ds_size;    /* [const] Size of the section (in bytes) */
	__size_t    const ds_entsize; /* [const] Section entity size (or 0 if unknown) */
	__uintptr_t const ds_link;    /* [const] Index of another section that is linked by this one (or `0' if unused) */
	__uintptr_t const ds_info;    /* [const] Index of another section that is linked by this one (or `0' if unused) */
	__uintptr_t const ds_flags;   /* [const] Section flags (set of `SHF_*') */
};
#endif /* !__dl_section_defined */


#ifdef __CRT_HAVE_dllocksection
#define DLLOCKSECTION_FNORMAL   0x0000 /* Normal section locking flags. */
#define DLLOCKSECTION_FINDEX    0x0001 /* The given `NAME' is actually the `(uintptr_t)NAME' index of the section */
#define DLLOCKSECTION_FNODATA   0x0002 /* Do not lock section data into memory, though if the section had already
                                        * been loaded, then this flag is simply ignored. */

/* Lock a named section of a given dynamic library into memory.
 * @param: HANDLE: Handle for the library who's section `NAME' should be locked & loaded.
 * @param: NAME:   Name of the section to load into memory.
 * @return: * :    A reference to a locked section object (s.a. exposed portion of the section above),
 *                 and allows the user to access the contents of the section, as it is loaded in memory.
 *                 Note however that the actual section data is usually mapped as read-only!
 * @return: NULL:  Error (s.a. `dlerror()'; usually: unknown section) */
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) /*REF*/ struct dl_section *
__NOTHROW_NCX(__DLFCN_CC dllocksection)(void *__handle,
                                        char const *__restrict __name,
                                        unsigned int __flags __DFL(DLLOCKSECTION_FNORMAL));
#endif /* __CRT_HAVE_dllocksection */

/* Unlock a locked section, as previously returned by `dllocksection()'
 * HINT: Think of this function as a decref(), where `dllocksection()'
 *       returns a reference you inherit as the caller
 * @return: 0 : Successfully unlocked the given section `SECT'
 * @return: * : Error (s.a. `dlerror()') */
#ifdef __CRT_HAVE_dlunlocksection
__IMPDEF __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__DLFCN_CC dlunlocksection)(/*REF*/ struct dl_section *__sect);
#endif /* __CRT_HAVE_dlunlocksection */

/* Return the name of a given section, or NULL on error
 * WARNING: The name of a section can no longer be queried after the associated
 *          module has been unloaded! If this has happened, NULL is returned
 *          and dlerror() is set accordingly.
 *          Because the names of sections are stored alongside the module, if
 *          you can't guaranty that the module associated with the section doesn't
 *          get unloaded while you're accessing the section's name, you must first
 *          acquire your own reference to that module through use of `dlsectionmodule()':
 *          >> void *mod = dlsectionmodule(my_sect, DLGETHANDLE_FINCREF);
 *          >> char const *name = dlsectionname(my_sect);
 *          >> // Make use of `name' (also check if `name' is NULL; if it is, `mod'
 *          >> // will probably also be NULL if the module had already been unloaded)
 *          >> ...
 *          >> dlclose(mod); */
#ifdef __CRT_HAVE_dlsectionname
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *
__NOTHROW_NCX(__DLFCN_CC dlsectionname)(struct dl_section *__sect);
#endif /* __CRT_HAVE_dlsectionname */

/* Returns the index of a given section, or (size_t)-1 on error. */
#ifdef __CRT_HAVE_dlsectionindex
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) __size_t
__NOTHROW_NCX(__DLFCN_CC dlsectionindex)(struct dl_section *__sect);
#endif /* __CRT_HAVE_dlsectionindex */

/* Return the module associated with a given section, or NULL on error.
 * @param: FLAGS: Set of `DLGETHANDLE_F*' 
 * @return: * :   A pointer, or reference to the module handle (when `DLGETHANDLE_FINCREF' was given)
 * @return: NULL: Error (s.a. `dlerror()'; usually, the module was already unloaded) */
#ifdef __CRT_HAVE_dlsectionmodule
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__DLFCN_CC dlsectionmodule)(struct dl_section *__sect,
                                          unsigned int __flags __DFL(DLGETHANDLE_FNORMAL));
#endif /* __CRT_HAVE_dlsectionmodule */
#endif /* ... */


/* Clear internal caches used by loaded modules in order to free up available memory.
 * This function is automatically called by libc when mmap() fails due to lack
 * of available virtual or physical memory.
 * For more information, see `DL_REGISTER_CACHE()'
 * @return: 0: No optional memory could be released.
 * @return: 1: Some optional memory was released. */
#ifdef __CRT_HAVE_dlclearcaches
__IMPDEF int __NOTHROW_NCX(__DLFCN_CC dlclearcaches)(void);
#endif /* __CRT_HAVE_dlclearcaches */

/* Allocate/Free a static TLS segment
 * These functions are called by by libc in order to safely create a new thread, such that
 * all current and future modules are able to store thread-local storage within that thread.
 * NOTE: The caller is responsible to store the returned segment to the appropriate TLS register.
 * @return: * :   Pointer to the newly allocated TLS segment.
 * @return: NULL: Error (s.a. dlerror()) */
#ifdef __CRT_HAVE_dltlsallocseg
__IMPDEF void *__NOTHROW_NCX(__DLFCN_CC dltlsallocseg)(void);
#endif /* __CRT_HAVE_dltlsallocseg */

/* Free a previously allocated static TLS segment (usually called by `pthread_exit()' and friends). */
#ifdef __CRT_HAVE_dltlsfreeseg
__IMPDEF __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__DLFCN_CC dltlsfreeseg)(void *__ptr);
#endif /* __CRT_HAVE_dltlsfreeseg */

/* DL-based TLS memory management API.
 * These functions may be used to dynamically allocate TLS memory that works everywhere where
 * ATTR_THREAD-based TLS memory also works. - However using these functions, TLS memory can
 * be allocated dynamically at runtime (behaving the same as a call to dlopen() loading a
 * module containing a TLS segment would).
 * @param: NUM_BYTES:      The size of the TLS segment (in bytes)
 * @param: MIN_ALIGNMENT:  The minimum alignment requirements for the TLS segment base address.
 * @param: TEMPLATE_DATA:  Base address of an initialization template.
 *                         The first `TEMPLATE_SIZE' bytes of any per-thread data segment
 *                         that gets allocated will be initialized to the contents of these
 *                         values before `PERTHREAD_INIT' is optionally invoked in order to
 *                         perform additional initialization.
 * @param: TEMPLATE_SIZE:  The size of `TEMPLATE_DATA' in bytes, indicating the number of
 *                         leading bytes within the TLS segment that should be pre-defined
 *                         to mirror the contents of `TEMPLATE_DATA' at the time of a call
 *                         to this function (`TEMPLATE_DATA' need not remain valid or
 *                         accessible after this function returns)
 *                         Any memory after `TEMPLATE_SIZE', but before `NUM_BYTES' is initialized
 *                         to all ZEROes, however `TEMPLATE_SIZE' must not be greater than
 *                        `NUM_BYTES', and if it is, this function returns `NULL' and sets
 *                        `dlerror()' accordingly.
 * @param: PERTHREAD_INIT: An optional callback that will be invoked on a per-thread basis
 *                         in order to perform additional initialization of the associated
 *                         TLS segment within the associated thread.
 *                         This function will be called upon first access of the segment
 *                         within the thread using the data (s.a. `dltlsaddr()')
 *                         @param: ARG:  The value of `PERTHREAD_CALLBACK_ARG' passed to `dltlsalloc'
 *                         @param: BASE: The base address of the associated segment within the calling
 *                                       thread (same as the return value of `dltlsaddr()')
 * @param: PERTHREAD_FINI: An optional callback that behaves similar to `PERTHREAD_INIT',
 *                         but called by `pthread_exit()' or any other thread finalizer
 *                        (more specifically: by `dltlsfreeseg()') within any thread that
 *                         has been seen using the associated segment, and causing it to
 *                         be allocated and initialized for that thread.
 * @param: PERTHREAD_CALLBACK_ARG: A user-specified argument passed to the init/fini callbacks.
 * @return: * :            An opaque handle for the newly created TLS segment.
 *                         This handle may be used in future calls to `dltlsaddr()', and can be
 *                         destroyed (causing all threads that had previously allocated the
 *                         segment to delete it and optionally invoke finalizer callbacks) by
 *                         passing it to `dltlsfree()'
 * @return: NULL:          Failed to allocate the TLS segment (s.a. `dlerror()') */
#ifdef __CRT_HAVE_dltlsalloc
__IMPDEF __ATTR_WUNUSED void *
__NOTHROW_NCX(__DLFCN_CC dltlsalloc)(__size_t __num_bytes, __size_t __min_alignment,
                                       void const *__template_data, __size_t __template_size,
                                       void (__LIBCCALL *__perthread_init)(void *__arg, void *__base),
                                       void (__LIBCCALL *__perthread_fini)(void *__arg, void *__base),
                                       void *__perthread_callback_arg);
#endif /* __CRT_HAVE_dltlsalloc */

/* Free a TLS segment previously allocated with `dltlsalloc' */
#ifdef __CRT_HAVE_dltlsfree
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__DLFCN_CC dltlsfree)(void *__tls_handle);
#endif /* __CRT_HAVE_dltlsfree */

/* Return the calling thread's base address of the TLS segment associated with `TLS_HANDLE'
 * NOTE: TLS Segments are allocated and initialized lazily, meaning that the initializer
 *       passed to `dltlsalloc()' will be called by this function upon the first use of
 *       that segment within each individual thread, also causing the finalizer to be
 *       enqueued for invocation when the calling thread exists.
 * WARNING: The order in which TLS finalizers are invoked is entirely UNDEFINED!
 * NOTE: the given `TLS_HANDLE' may also be a module handle, as returned by `dlopen()',
 *       in which case this function returns a pointer to the TLS segment of that module for
 *       the calling thread (e.g.: Such a pointer is needed by `unwind_emulator_t::sm_tlsbase')
 * @return: * :   Pointer to the base of the TLS segment associated with `TLS_HANDLE' within the calling thread.
 * @return: NULL: Invalid `TLS_HANDLE', or allocation/initialization failed. (s.a. `dlerror()') */
#ifdef __CRT_HAVE_dltlsaddr
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__DLFCN_CC dltlsaddr)(void *__tls_handle);
#endif /* __CRT_HAVE_dltlsaddr */


/* Perform an auxiliary control command about a given module `HANDLE'
 * This function is used internally, and invocation requirements for different values
 * for `CMD' may change in the future. - It's purpose is to provide access to binary-
 * specific information about loaded modules.
 * @param: HANDLE:   Handle of the module for which to query information,
 *                   or NULL to query for the root application.
 *                   Some commands may not make use of this argument.
 * @param: CMD:      The command with which information should be requested.
 * @return: NULL: No information available, or no buffer was provided (depending on `CMD')
 * @return: NULL: Error: Unknown `CMD' (s.a. dlerror())
 * @return: NULL: Error: Invalid `HANDLE' (s.a. dlerror()) */
#ifdef __CRT_HAVE_dlauxctrl
__IMPDEF void *
__NOTHROW_NCX(__DLFCN_VCC dlauxctrl)(void *__handle,
                                     unsigned int __cmd,
                                     ...);

#define DLAUXCTRL_RUNFINI            0xd101 /* Run all library finalizers. `HANDLE' should be any valid module handle, or `NULL',
                                             * and all other arguments are ignored; always returns `NULL', but doesn't set an error */
#define DLAUXCTRL_RUNTLSFINI         0xd102 /* Run TLS library finalizers for the calling thread. `HANDLE' should be any valid
                                             * module handle, or alternatively `NULL' for the root application, and all other
                                             * arguments are ignored. Always returns `NULL', but doesn't set an error */
#define DLAUXCTRL_ADD_FINALIZER      0xd103 /* Register a dynamic finalizer callback for `HANDLE':
                                             * >> CALLBACK = va_arg(void(__DLFCN_CC *)(void *));
                                             * >> ARG      = va_arg(void *);
                                             * NOTE: When returning `HANDLE', and `HANDLE' was `NULL', the
                                             *       handle for the root application is returned instead.
                                             * @return: HANDLE: Re-returns `HANDLE' upon success.
                                             * @return: HANDLE: Module finalizers have already been invoked.
                                             *                  In this case, CALLBACK was invoked prior to returning
                                             * @return: NULL:   Invalid `HANDLE' (dlerror() is modified)
                                             * @return: NULL:   Failed to allocate additional memory for registering `CALLBACK'. */
#define DLAUXCTRL_REGISTER_EXTENSION 0xd201 /* Register an extension to libdl:
                                             * >> extension              = va_arg(struct dlmodule_format *);
                                             * >> sizeof_dlmodule_format = va_arg(size_t);
                                             * >> sizeof_dlcore_ops      = va_arg(size_t);
                                             * NOTE: When returning `HANDLE', and `HANDLE' was `NULL', the
                                             *       handle for the root application is returned instead.
                                             * @return: HANDLE: Re-returns `HANDLE' upon success.
                                             * @return: NULL:   Invalid `HANDLE' (dlerror() is modified)
                                             * @return: NULL:   `extension' is an invalid pointer
                                             * @return: NULL:   Unsupported value for `sizeof_dlmodule_format' (dlerror() is modified)
                                             * @return: NULL:   Unsupported value for `sizeof_dlcore_ops' (dlerror() is modified)
                                             * @return: NULL:   `extension->df_open' does not map to a static memory segment (dlerror() is modified)
                                             * NOTE: Upon success, the module containing `extension->df_open' becomes undeletable. */
#define DLAUXCTRL_GET_DEPENDS        0xd202 /* [size_t *pcount [0..1]] Returns the module's vector of module dependencies (`MODULE **') */
#define DLAUXCTRL_ELF_CHECK          0xef00 /* Check if this module is an ELF module (re-returns `HANDLE' if so, otherwise returns `NULL' but leaves `dlerror()' unmodified) */
#define DLAUXCTRL_ELF_GET_PHDR       0xef01 /* [size_t *pcount [0..1]] Returns the module's vector of program headers (`ElfW(Phdr) *') */
#define DLAUXCTRL_ELF_GET_SHDR       0xef02 /* [size_t *pcount [0..1]] Returns the module's vector of section headers (`ElfW(Shdr) *') */
#define DLAUXCTRL_ELF_GET_DYN        0xef03 /* [size_t *pcount [0..1]] Returns the module's vector of dynamic tags (`ElfW(Dyn) *') */
#define DLAUXCTRL_ELF_GET_DYNSYM     0xef04 /* [size_t *pcount [0..1]] Returns the module's vector of dynamic symbol table (`ElfW(Sym) *')
                                             * If the number of symbols is unknown, `(size_t)-1' written to `*pcount'. */
#define DLAUXCTRL_ELF_GET_DYNSTR     0xef05 /* Returns the module's dynamic string table (`char const *') */
#define DLAUXCTRL_ELF_GET_SHSTRTAB   0xef06 /* Returns the module's section header name string table (`char const *') */
#endif /* __CRT_HAVE_dlauxctrl */

#endif /* __USE_KOS */





#ifdef __USE_GNU

#ifdef __CRT_HAVE_dladdr
#ifndef __Dl_info_defined
#define __Dl_info_defined 1
typedef struct __dl_info_struct Dl_info;
#endif /* !__Dl_info_defined */

__IMPDEF __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__DLFCN_CC dladdr)(void const *__address,
                                 Dl_info *__info);
#endif /* __CRT_HAVE_dladdr */

#if defined(__CRT_HAVE_dlmopen) && defined(__Lmid_t)
__IMPDEF void *(__DLFCN_CC dlmopen)(__Lmid_t __nsid, char const *__file, int __mode);
#endif /* __CRT_HAVE_dlmopen && __Lmid_t */

#ifdef __CRT_HAVE_dlvsym
__IMPDEF __ATTR_NONNULL((2, 3)) void *
__NOTHROW_NCX(__DLFCN_CC dlvsym)(void *__restrict __handle,
                                 char const *__name,
                                 char const *__version);
#endif /* __CRT_HAVE_dlvsym */

#ifdef __CRT_HAVE_dladdr1
enum {
	RTLD_DL_SYMENT  = 1,
	RTLD_DL_LINKMAP = 2
};
#ifndef __Dl_info_defined
#define __Dl_info_defined 1
typedef struct __dl_info_struct Dl_info;
#endif /* !__Dl_info_defined */

__IMPDEF __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__DLFCN_CC dladdr1)(void const *__address, Dl_info *__info,
                                  void **__extra_info, int __flags);
#endif /* __CRT_HAVE_dladdr1 */

#ifdef __CRT_HAVE_dlinfo
enum {
	RTLD_DI_LMID        = 1,
	RTLD_DI_LINKMAP     = 2,
	RTLD_DI_CONFIGADDR  = 3,
	RTLD_DI_SERINFO     = 4,
	RTLD_DI_SERINFOSIZE = 5,
	RTLD_DI_ORIGIN      = 6,
	RTLD_DI_PROFILENAME = 7,
	RTLD_DI_PROFILEOUT  = 8,
	RTLD_DI_TLS_MODID   = 9,
	RTLD_DI_TLS_DATA    = 10,
	RTLD_DI_MAX         = 10
};

typedef struct {
	char        *dls_name;
	unsigned int dls_flags;
} Dl_serpath;

typedef struct {
	size_t          dls_size;
	__UINT32_TYPE__ dls_cnt;
	Dl_serpath      dls_serpath[1];
} Dl_serinfo;

__IMPDEF __ATTR_NONNULL((1, 3)) int
__NOTHROW_NCX(__DLFCN_CC dlinfo)(void *__restrict __handle,
                                 int __request,
                                 void *__arg);
#endif /* __CRT_HAVE_dlinfo */


#ifndef DL_CALL_FCT
/* To support profiling of shared objects it is a good idea to call
 * the function found using `dlsym' using the following macro since
 * these calls do not use the PLT. But this would mean the dynamic
 * loader has no chance to find out when the function is called. The
 * macro applies the necessary magic so that profiling is possible.
 * Rewrite
 *  foo = (*fctp)(arg1, arg2);
 * into
 *      foo = DL_CALL_FCT(fctp, (arg1, arg2));
 */
#ifdef __CRT_HAVE__dl_mcount_wrapper_check
#define DL_CALL_FCT(fctp, args) \
	(_dl_mcount_wrapper_check((void *)(fctp)), (*(fctp))args)
__IMPDEF void __NOTHROW_NCX(__DLFCN_CC _dl_mcount_wrapper_check)(void *__selfpc);
#else /* __CRT_HAVE__dl_mcount_wrapper_check */
#define DL_CALL_FCT(fctp, args) (*(fctp)) args)
#endif /* !__CRT_HAVE__dl_mcount_wrapper_check */
#endif /* !DL_CALL_FCT */
#endif /* __USE_GNU */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_DLFCN_H */
