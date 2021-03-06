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

%[define_replacement(fd_t       = __fd_t)]
%[define_replacement(atflag_t   = __atflag_t)]
%[define_replacement(mode_t     = __mode_t)]
%[define_replacement(dev_t      = __dev_t)]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(time_t     = "__TM_TYPE(time)")]
%[define_replacement(time32_t   = __time32_t)]
%[define_replacement(time64_t   = __time64_t)]

%[define_replacement(S_IFMT      = __S_IFMT)]
%[define_replacement(S_IFDIR     = __S_IFDIR)]
%[define_replacement(S_IFCHR     = __S_IFCHR)]
%[define_replacement(S_IFBLK     = __S_IFBLK)]
%[define_replacement(S_IFREG     = __S_IFREG)]
%[define_replacement(S_IFIFO     = __S_IFIFO)]
%[define_replacement(S_IFLNK     = __S_IFLNK)]
%[define_replacement(S_IFSOCK    = __S_IFSOCK)]
%[define_replacement(S_ISDIR     = __S_ISDIR)]
%[define_replacement(S_ISCHR     = __S_ISCHR)]
%[define_replacement(S_ISBLK     = __S_ISBLK)]
%[define_replacement(S_ISREG     = __S_ISREG)]
%[define_replacement(S_ISFIFO    = __S_ISFIFO)]
%[define_replacement(S_ISLNK     = __S_ISLNK)]
%[define_replacement(S_ISDEV     = __S_ISDEV)]
%[define_replacement(S_TYPEISMQ  = __S_TYPEISMQ)]
%[define_replacement(S_TYPEISSEM = __S_TYPEISSEM)]
%[define_replacement(S_TYPEISSHM = __S_TYPEISSHM)]
%[define_replacement(S_ISUID     = __S_ISUID)]
%[define_replacement(S_ISGID     = __S_ISGID)]
%[define_replacement(S_ISVTX     = __S_ISVTX)]
%[define_replacement(S_IREAD     = 0400)]
%[define_replacement(S_IWRITE    = 0200)]
%[define_replacement(S_IEXEC     = 0100)]
%[define_replacement(UTIME_NOW   = __UTIME_NOW)]
%[define_replacement(UTIME_OMIT  = __UTIME_OMIT)]

%[declare_known_section(".text.crt{|.dos}.fs.stat")]
%[declare_known_section(".text.crt{|.dos}.fs.stat_glc")]

/* KOS's stat function family */
%[declare_user_export("kstat", "kstat64")]
%[declare_user_export("klstat", "klstat64")]
%[declare_user_export("kfstat", "kfstat64")]
%[declare_user_export("kfstatat", "kfstatat64")]

/* Cygwin's stat function family */
%[declare_user_export("DOS$stat", "DOS$stat64")]
%[declare_user_export("DOS$lstat", "DOS$lstat64")]
%[declare_user_export("DOS$fstat", "DOS$fstat64")]
%[declare_user_export("DOS$fstatat", "DOS$fstatat64")]

/* GLibc's stat function family */
%[declare_user_export("stat", "stat64")]
%[declare_user_export("lstat", "lstat64")]
%[declare_user_export("fstat", "fstat64")]
%[declare_user_export("fstatat", "fstatat64")]

/* DOS's stat function family */
%[declare_user_export("_fstat")]
%[declare_user_export("_fstat32")]
%[declare_user_export("_fstati64")]
%[declare_user_export("_fstat32i64")]
%[declare_user_export("_fstat64")]
%[declare_user_export("_fstat64i32")]
%[declare_user_export("_stat")]
%[declare_user_export("_stat32")]
%[declare_user_export("_stati64")]
%[declare_user_export("_stat32i64")]
%[declare_user_export("_stat64")]
%[declare_user_export("_stat64i32")]



%{
#include <features.h>

#include <asm/stat.h>
#include <bits/stat.h>
#include <bits/timespec.h>
#include <bits/types.h>

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#include <time.h>
#endif /* __USE_XOPEN || __USE_XOPEN2K */

__SYSDECL_BEGIN

#ifdef __CC__

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __dev_t_defined
#define __dev_t_defined 1
typedef __typedef_dev_t dev_t;
#endif /* __dev_t_defined */

#ifndef __gid_t_defined
#define __gid_t_defined 1
typedef __gid_t gid_t;
#endif /* __gid_t_defined */

#ifndef __ino_t_defined
#define __ino_t_defined 1
typedef __typedef_ino_t ino_t;  /* INode number */
#endif /* __ino_t_defined */

#ifndef __mode_t_defined
#define __mode_t_defined 1
typedef __mode_t mode_t; /* INode type (Set of `S_*' from `<fcntl.h>' or `<sys/stat.h>') */
#endif /* __mode_t_defined */

#ifndef __nlink_t_defined
#define __nlink_t_defined 1
typedef __nlink_t nlink_t;
#endif /* __nlink_t_defined */

#ifndef __off_t_defined
#define __off_t_defined 1
typedef __typedef_off_t off_t;
#endif /* __off_t_defined */

#ifndef __uid_t_defined
#define __uid_t_defined 1
typedef __uid_t uid_t;
#endif /* __uid_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifdef __USE_UNIX98
#ifndef __blkcnt_t_defined
#define __blkcnt_t_defined 1
typedef __FS_TYPE(blkcnt)   blkcnt_t;
#endif /* __blkcnt_t_defined */

#ifndef __blksize_t_defined
#define __blksize_t_defined 1
typedef __blksize_t blksize_t;
#endif /* __blksize_t_defined */
#endif /* __USE_UNIX98 */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#if !defined(S_IFMT) && defined(__S_IFMT)
#define S_IFMT  __S_IFMT /* These bits determine file type. */
#endif /* !S_IFMT && __S_IFMT */
#if !defined(S_IFDIR) && defined(__S_IFDIR)
#define S_IFDIR __S_IFDIR /* Directory. */
#endif /* !S_IFDIR && __S_IFDIR */
#if !defined(S_IFCHR) && defined(__S_IFCHR)
#define S_IFCHR __S_IFCHR /* Character device. */
#endif /* !S_IFCHR && __S_IFCHR */
#if !defined(S_IFBLK) && defined(__S_IFBLK)
#define S_IFBLK __S_IFBLK /* Block device. */
#endif /* !S_IFBLK && __S_IFBLK */
#if !defined(S_IFREG) && defined(__S_IFREG)
#define S_IFREG __S_IFREG /* Regular file. */
#endif /* !S_IFREG && __S_IFREG */
#if !defined(S_IFIFO) && defined(__S_IFIFO)
#define S_IFIFO __S_IFIFO /* FIFO. */
#endif /* !S_IFIFO && __S_IFIFO */
#if !defined(S_IFLNK) && defined(__S_IFLNK)
#define S_IFLNK __S_IFLNK /* Symbolic link. */
#endif /* !S_IFLNK && __S_IFLNK */
#if ((defined(__USE_MISC) || defined(__USE_UNIX98)) && \
     !defined(S_IFSOCK) && defined(__S_IFSOCK))
#define S_IFSOCK __S_IFSOCK /* Socket. */
#endif /* (__USE_MISC || __USE_UNIX98) && !S_IFSOCK && __S_IFSOCK */
#endif /* __USE_MISC || __USE_XOPEN */

#if !defined(__S_ISTYPE) && defined(__S_IFMT)
#define __S_ISTYPE(mode, mask) (((mode) & __S_IFMT) == (mask))
#endif /* !__S_ISTYPE && __S_IFMT */

/* File mode test macros. */
#if !defined(S_ISDIR) && defined(__S_ISDIR)
#define S_ISDIR(mode) __S_ISDIR(mode) /* Directory. */
#endif /* !S_ISDIR && __S_ISDIR */
#if !defined(S_ISCHR) && defined(__S_ISCHR)
#define S_ISCHR(mode) __S_ISCHR(mode) /* Character device. */
#endif /* !S_ISCHR && __S_ISCHR */
#if !defined(S_ISBLK) && defined(__S_ISBLK)
#define S_ISBLK(mode) __S_ISBLK(mode) /* Block device. */
#endif /* !S_ISBLK && __S_ISBLK */
#if !defined(S_ISREG) && defined(__S_ISREG)
#define S_ISREG(mode) __S_ISREG(mode) /* Regular file. */
#endif /* !S_ISREG && __S_ISREG */

#if defined(__USE_KOS) && !defined(S_ISDEV) && defined(__S_ISDEV)
#define S_ISDEV(mode) __S_ISDEV(mode) /* S_ISCHR(mode) || S_ISBLK(mode) */
#endif /* __USE_KOS && !S_ISDEV && __S_ISDEV */

#if !defined(S_ISFIFO) && defined(__S_ISFIFO)
#define S_ISFIFO(mode) __S_ISFIFO(mode) /* FIFO. */
#endif /* !S_ISFIFO && __S_ISFIFO */

#ifndef S_ISLNK
#ifdef __S_ISLNK
#define S_ISLNK(mode) __S_ISLNK(mode) /* Symbolic link. */
#elif defined(__USE_MISC)
#define S_ISLNK(mode) 0               /* Symbolic link. */
#endif /* ... */
#endif /* !S_ISLNK */

#ifndef S_ISSOCK
#if ((defined(__USE_UNIX98) || defined(__USE_XOPEN2K)) && defined(__S_ISSOCK))
#define S_ISSOCK(mode) __S_ISSOCK(x) /* Socket. */
#elif defined(__USE_XOPEN2K)
#define S_ISSOCK(mode) 0             /* Socket. */
#endif /* ... */
#endif /* !S_ISSOCK */

#ifdef __USE_POSIX199309
#ifndef S_TYPEISMQ
#ifdef __S_TYPEISMQ
#define S_TYPEISMQ(buf) __S_TYPEISMQ(buf)
#else /* __S_TYPEISMQ */
#define S_TYPEISMQ(buf) ((buf)->st_mode, 0)
#endif /* !__S_TYPEISMQ */
#endif /* !S_TYPEISMQ */

#ifndef S_TYPEISSEM
#ifdef __S_TYPEISSEM
#define S_TYPEISSEM(buf) __S_TYPEISSEM(buf)
#else /* __S_TYPEISSEM */
#define S_TYPEISSEM(buf) ((buf)->st_mode, 0)
#endif /* !__S_TYPEISSEM */
#endif /* !S_TYPEISSEM */

#ifndef S_TYPEISSHM
#ifdef __S_TYPEISSHM
#define S_TYPEISSHM(buf) __S_TYPEISSHM(buf)
#else /* __S_TYPEISSHM */
#define S_TYPEISSHM(buf) ((buf)->st_mode, 0)
#endif /* !__S_TYPEISSHM */
#endif /* !S_TYPEISSHM */
#endif /* __USE_POSIX199309 */

#if !defined(S_ISUID) && defined(__S_ISUID)
#define S_ISUID __S_ISUID /* Set user ID on execution. */
#endif /* !S_ISUID && __S_ISUID */

#if !defined(S_ISGID) && defined(__S_ISGID)
#define S_ISGID __S_ISGID /* Set group ID on execution. */
#endif /* !S_ISGID && __S_ISGID */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifndef S_ISVTX
#define S_ISVTX __S_ISVTX
#endif /* !S_ISVTX */
#endif /* __USE_MISC || __USE_XOPEN */

#ifndef S_IRUSR
#define S_IRUSR 0400 /* Read by owner. */
#define S_IWUSR 0200 /* Write by owner. */
#define S_IXUSR 0100 /* Execute by owner. */
#define S_IRWXU 0700
#define S_IRGRP 0040 /* Read by group. */
#define S_IWGRP 0020 /* Write by group. */
#define S_IXGRP 0010 /* Execute by group. */
#define S_IRWXG 0070
#define S_IROTH 0004 /* Read by others. */
#define S_IWOTH 0002 /* Write by others. */
#define S_IXOTH 0001 /* Execute by others. */
#define S_IRWXO 0007
#endif /* !S_IRWXO */



#ifdef __USE_KOS
/* As also seen in the linux kernel headers. */
#ifndef S_IRWXUGO
#define S_IRWXUGO 0777
#endif /* !S_IRWXUGO */
#ifndef S_IALLUGO
#define S_IALLUGO 07777
#endif /* !S_IALLUGO */
#ifndef S_IRUGO
#define S_IRUGO 0444
#endif /* !S_IRUGO */
#ifndef S_IWUGO
#define S_IWUGO 0222
#endif /* !S_IWUGO */
#ifndef S_IXUGO
#define S_IXUGO 0111
#endif /* !S_IXUGO */
#endif /* __USE_KOS */

#ifdef __USE_MISC
#ifndef ACCESSPERMS
#define ACCESSPERMS 0777 /* S_IRWXU | S_IRWXG | S_IRWXO */
#endif /* !ACCESSPERMS */
#ifndef ALLPERMS
#define ALLPERMS 07777 /* S_ISUID | S_ISGID | S_ISVTX | S_IRWXU | S_IRWXG | S_IRWXO */
#endif /* !ALLPERMS */
#ifndef DEFFILEMODE
#define DEFFILEMODE 0666 /* S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH */
#endif /* !DEFFILEMODE */
#ifndef S_BLKSIZE
#define S_BLKSIZE 512 /* Block size for `st_blocks'. */
#endif /* !S_BLKSIZE */
#endif /* __USE_MISC */

#ifdef __USE_DOS
#ifdef __S_IFMT
#define _S_IFMT   __S_IFMT
#endif /* __S_IFMT */
#ifdef __S_IFDIR
#define _S_IFDIR  __S_IFDIR
#endif /* __S_IFDIR */
#ifdef __S_IFCHR
#define _S_IFCHR  __S_IFCHR
#endif /* __S_IFCHR */
#ifdef __S_IFIFO
#define _S_IFIFO  __S_IFIFO
#endif /* __S_IFIFO */
#ifdef __S_IFREG
#define _S_IFREG  __S_IFREG
#endif /* __S_IFREG */
#define _S_IREAD  0400
#define _S_IWRITE 0200
#define _S_IEXEC  0100
#endif /* __USE_DOS */

#undef stat
#undef fstat
#undef lstat
#ifdef __USE_LARGEFILE64
#undef stat64
#undef fstat64
#undef lstat64
#endif /* __USE_LARGEFILE64 */

}

/* Recognized & known stat() structures and assembly names.
 *
 * __CRT_KOS: (Used by default)
 * >> int CDECL kfstat(fd_t fd, struct __kos_stat *buf);
 * >> int CDECL kfstat64(fd_t fd, struct __kos_stat *buf);
 * >> int CDECL kstat(char const *filename, struct __kos_stat *buf);
 * >> int CDECL kstat64(char const *filename, struct __kos_stat *buf);
 * >> int CDECL kfstatat(fd_t dirfd, char const *filename, struct __kos_stat *buf, atflag_t flags);
 * >> int CDECL kfstatat64(fd_t dirfd, char const *filename, struct __kos_stat *buf, atflag_t flags);
 * >> int CDECL klstat(char const *filename, struct __kos_stat *buf);
 * >> int CDECL klstat64(char const *filename, struct __kos_stat *buf);
 *
 * __CRT_GLC: (__GLC_COMPAT__)
 * >> int CDECL fstat(fd_t fd, struct __glc_stat *buf);
 * >> int CDECL fstat64(fd_t fd, struct __glc_stat64 *buf);
 * >> int CDECL stat(char const *filename, struct __glc_stat *buf);
 * >> int CDECL stat64(char const *filename, struct __glc_stat64 *buf);
 * >> int CDECL fstatat(fd_t dirfd, char const *filename, struct __glc_stat *buf, atflag_t flags);
 * >> int CDECL fstatat64(fd_t dirfd, char const *filename, struct __glc_stat64 *buf, atflag_t flags);
 * >> int CDECL lstat(char const *filename, struct __glc_stat *buf);
 * >> int CDECL lstat64(char const *filename, struct __glc_stat64 *buf);
 *
 * __CRT_DOS: (__DOS_COMPAT__)
 * >> int CDECL [OLD: _fstat,    NEW:_fstat32] (fd_t fd, struct __dos_stat32 *buf);
 * >> int CDECL [OLD: _fstati64, NEW:_fstat32i64] (fd_t fd, struct __dos_stat32i64 *buf);
 * >> int CDECL [OLD: _stat,     NEW:_stat32] (char const *filename, struct __dos_stat32 *buf);
 * >> int CDECL [OLD: _stati64,  NEW:_stat32i64] (char const *filename, struct __dos_stat32i64 *buf);
 * >> int CDECL _fstat64(fd_t fd, struct __dos_stat64 *buf);
 * >> int CDECL _stat64(char const *filename, struct __dos_stat64 *buf);
 * >> int CDECL [NEW: _fstat64i32](fd_t fd, struct __dos_stat64i32 *buf) = _fstat64;
 * >> int CDECL [NEW: _stat64i32](char const *filename, struct __dos_stat64i32 *buf) = _stat64;
 *
 * NOTE: Since KOS uses a different `stat' buffer than glibc, but still wants to
 *       maintain binary compatibility, the `stat()' function provided internally
 *       accepts a glibc-compatible stat buffer, while the functions making use
 *       of what we (and the kernel) defines as its stat()-buffer are actually
 *       named 'kstat()' */


/* When running as `__CRT_DOS_PRIMARY':
 *   `struct stat' is:
 *       [                                       ] = struct __dos_stat32
 *       [__USE_TIME_BITS64                      ] = struct __dos_stat64i32 == struct __dos_stat64
 *       [__USE_FILE_OFFSET64                    ] = struct __dos_stat32i64
 *       [__USE_TIME_BITS64 + __USE_FILE_OFFSET64] = struct __dos_stat64
 *   `struct stat64' is:
 *       [                 ]                       = struct __dos_stat32i64
 *       [__USE_TIME_BITS64]                       = struct __dos_stat64
 * When running as `__CRT_KOS_PRIMARY':
 *   `struct stat' is:                             = struct __kos_stat
 *   `struct stat64' is:                           = struct __kos_stat
 * When running as `__CRT_GLC_PRIMARY':
 *   `struct stat' is:
 *       [                   ]                     = struct __cyg_stat
 *       [__USE_FILE_OFFSET64]                     = struct __glc_stat64
 *   `struct stat64' is:                           = struct __glc_stat64
 * When running as `__CRT_CYG_PRIMARY':
 *   `struct stat' is:                             = struct __cyg_stat
 *   `struct stat64' is:                           = struct __cyg_stat
 * Otherwise, `struct stat' uses a totally generic layout.
 */

%[default:section(".text.crt{|.dos}.fs.stat")];

/* Name format: `<N_TIME_BITS>i<N_FILE_BITS>' */
[[ignore, nocrt, alias("_stat", "_stat32")]]
int dos_stat32i32([[nonnull]] char const *__restrict filename,
                  [[nonnull]] struct __dos_stat32 *__restrict buf);

[[ignore, nocrt, alias("_stati64", "_stat32i64")]]
int dos_stat32i64([[nonnull]] char const *__restrict filename,
                  [[nonnull]] struct __dos_stat32i64 *__restrict buf);

[[ignore, nocrt, alias("_stat64", "_stat64i32")]]
int dos_stat64i32([[nonnull]] char const *__restrict filename,
                  [[nonnull]] struct __dos_stat64i32 *__restrict buf);

[[ignore, nocrt, alias("_stat64", "_stat64i32")]]
int dos_stat64i64([[nonnull]] char const *__restrict filename,
                  [[nonnull]] struct __dos_stat64 *__restrict buf);

[[ignore, nocrt, alias("_fstat", "_fstat32")]]
int dos_fstat32i32($fd_t fd, [[nonnull]] struct __dos_stat32 *__restrict buf);

[[ignore, nocrt, alias("_fstati64", "_fstat32i64")]]
int dos_fstat32i64($fd_t fd, [[nonnull]] struct __dos_stat32i64 *__restrict buf);

[[ignore, nocrt, alias("_fstat64", "_fstat64i32")]]
int dos_fstat64i32($fd_t fd, [[nonnull]] struct __dos_stat64i32 *__restrict buf);

[[ignore, nocrt, alias("_fstat64", "_fstat64i32")]]
int dos_fstat64i64($fd_t fd, [[nonnull]] struct __dos_stat64 *__restrict buf);


//[[ignore, nocrt, alias("stat")]]    int glibc_stat([[nonnull]] char const *__restrict filename, [[nonnull]] struct __glc_stat *__restrict buf);
//[[ignore, nocrt, alias("stat64")]]  int glibc_stat64([[nonnull]] char const *__restrict filename, [[nonnull]] struct __glc_stat64 *__restrict buf);
//[[ignore, nocrt, alias("lstat")]]   int glibc_lstat([[nonnull]] char const *__restrict filename, [[nonnull]] struct __glc_stat *__restrict buf);
//[[ignore, nocrt, alias("lstat64")]] int glibc_lstat64([[nonnull]] char const *__restrict filename, [[nonnull]] struct __glc_stat64 *__restrict buf);
//[[ignore, nocrt, alias("fstat")]]   int glibc_fstat($fd_t fd, [[nonnull]] struct __glc_stat *__restrict buf);
//[[ignore, nocrt, alias("fstat64")]] int glibc_fstat64($fd_t fd, [[nonnull]] struct __glc_stat64 *__restrict buf);


[[no_crt_impl, no_crt_self_import]]
[[if(defined(__CRT_KOS_PRIMARY)), preferred_alias("kstat", "kstat64")]]
[[if(defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)), preferred_alias("_stat64", "_stat64i32")]]
[[if(defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)), preferred_alias("_stati64", "_stat32i64")]]
[[if(defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)), preferred_alias("_stat", "_stat32")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("stat64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("stat")]]
int stat([[nonnull]] char const *__restrict filename,
         [[nonnull]] struct stat *__restrict buf);
/* TODO: Emulate stat() for __USE_TIME_BITS64 compatibility! */


%
;
[[no_crt_impl, no_crt_self_import]]
[[if(defined(__CRT_KOS_PRIMARY)), preferred_alias("kfstat", "kfstat64")]]
[[if(defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)), preferred_alias("_fstat64", "_fstat64i32")]]
[[if(defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)), preferred_alias("_fstati64", "_fstat32i64")]]
[[if(defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)), preferred_alias("_fstat", "_fstat32")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("fstat64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("fstat")]]
int fstat($fd_t fd, [[nonnull]] struct stat *__restrict buf);

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
;

[[no_crt_impl, no_crt_self_import]]
[[if(defined(__CRT_KOS_PRIMARY)), preferred_alias("klstat", "klstat64")]]
[[if(defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)), preferred_alias("_stat64", "_stat64i32")]]
[[if(defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)), preferred_alias("_stati64", "_stat32i64")]]
[[if(defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)), preferred_alias("_stat", "_stat32")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("lstat64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("lstat")]]
int lstat([[nonnull]] char const *__restrict filename,
          [[nonnull]] struct stat *__restrict buf);
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

%
%#ifdef __USE_LARGEFILE64
;

[[no_crt_impl, no_crt_self_import]]
[[if(defined(__CRT_KOS_PRIMARY)), preferred_alias("kstat", "kstat64")]]
[[if(defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)), preferred_alias("_stat64", "_stat64i32")]]
[[if(defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)), preferred_alias("_stati64", "_stat32i64")]]
[[preferred_alias("stat64")]]
int stat64([[nonnull]] char const *__restrict filename,
           [[nonnull]] struct stat64 *__restrict buf);

%
;
[[no_crt_impl, no_crt_self_import]]
[[if(defined(__CRT_KOS_PRIMARY)), preferred_alias("kfstat", "kfstat64")]]
[[if(defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)), preferred_alias("_fstat64", "_fstat64i32")]]
[[if(defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)), preferred_alias("_fstati64", "_fstat32i64")]]
[[preferred_alias("fstat64")]]
int fstat64($fd_t fd, [[nonnull]] struct stat64 *__restrict buf);

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
[[no_crt_impl, no_crt_self_import]]
[[if(defined(__CRT_KOS_PRIMARY)), preferred_alias("klstat", "klstat64")]]
[[if(defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)), preferred_alias("_stat64", "_stat64i32")]]
[[if(defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)), preferred_alias("_stati64", "_stat32i64")]]
[[preferred_alias("lstat64")]]
int lstat64([[nonnull]] char const *__restrict filename,
            [[nonnull]] struct stat64 *__restrict buf);
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */
%#endif /* __USE_LARGEFILE64 */

%
%



%(user){
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_kos_fstat)(fd_t fd, struct __kos_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_kos_stat)(char const *__restrict filename, struct __kos_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_kos_lstat)(char const *__restrict filename, struct __kos_stat *__restrict buf);
INTDEF NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_kos_fstatat)(fd_t dirfd, char const *__restrict filename, struct __kos_stat *__restrict buf, atflag_t flags);

INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_cyg_fstat)(fd_t fd, struct __cyg_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_cyg_stat)(char const *__restrict filename, struct __cyg_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_cyg_lstat)(char const *__restrict filename, struct __cyg_stat *__restrict buf);
INTDEF NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_cyg_fstatat)(fd_t dirfd, char const *__restrict filename, struct __cyg_stat *__restrict buf, atflag_t flags);

INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_glc_fstat)(fd_t fd, struct __glc_stat *__restrict buf);
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_glc_fstat64)(fd_t fd, struct __glc_stat64 *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_glc_stat)(char const *__restrict filename, struct __glc_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_glc_stat64)(char const *__restrict filename, struct __glc_stat64 *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_glc_lstat)(char const *__restrict filename, struct __glc_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_glc_lstat64)(char const *__restrict filename, struct __glc_stat64 *__restrict buf);
INTDEF NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_glc_fstatat)(fd_t dirfd, char const *__restrict filename, struct __glc_stat *__restrict buf, atflag_t flags);
INTDEF NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_glc_fstatat64)(fd_t dirfd, char const *__restrict filename, struct __glc_stat64 *__restrict buf, atflag_t flags);

INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_dos_fstat32)(fd_t fd, struct __dos_stat32 *__restrict buf); /* _fstat, _fstat32 */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_dos_fstat32i64)(fd_t fd, struct __dos_stat32i64 *__restrict buf); /* _fstati64, _fstat32i64 */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_dos_fstat64)(fd_t fd, struct __dos_stat64 *__restrict buf); /* _fstat64, _fstat64i32 */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dos_stat32)(char const *__restrict filename, struct __dos_stat32 *__restrict buf); /* _stat, _stat32 */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dos_stat32i64)(char const *__restrict filename, struct __dos_stat32i64 *__restrict buf); /* _stati64, _stat32i64 */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dos_stat64)(char const *__restrict filename, struct __dos_stat64 *__restrict buf); /* _stat64, _stat64i32 */


}


%
%#ifdef __USE_ATFILE

@@@param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH'
[[no_crt_impl, no_crt_self_import]]
[[if(defined(__CRT_KOS_PRIMARY)), preferred_alias("kfstatat", "kfstatat64")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("fstatat64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("fstatat")]]
int fstatat($fd_t dirfd, [[nonnull]] char const *__restrict filename,
            [[nonnull]] struct stat *__restrict buf, $atflag_t flags);

%#ifdef __USE_LARGEFILE64
@@@param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH'
[[no_crt_impl, no_crt_self_import]]
[[if(defined(__CRT_KOS_PRIMARY)), preferred_alias("kfstatat", "kfstatat64")]]
int fstatat64($fd_t dirfd, [[nonnull]] char const *__restrict filename,
              [[nonnull]] struct stat *__restrict buf, $atflag_t flags);
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_ATFILE */

%[default:section(".text.crt{|.dos}.fs.modify")];

[[cp, ignore, nocrt, alias("_mkdir")]]
int dos_mkdir([[nonnull]] char const *pathname);

%
;

[[cp, guard, userimpl]]
[[requires(defined(__CRT_DOS_PRIMARY) && $has_function(dos_mkdir))]]
int mkdir([[nonnull]] char const *pathname, $mode_t mode) {
	(void)mode;
	return dos_mkdir(pathname);
}

%
;

[[cp, guard, export_alias("_chmod")]]
int chmod([[nonnull]] char const *filename, $mode_t mode);


%
%#ifdef __USE_MISC
;

[[cp, guard]]
[[if(defined(__CRT_DOS_PRIMARY)), alias("_chmod", "chmod")]]
int lchmod([[nonnull]] char const *filename, $mode_t mode);
%#endif /* __USE_MISC */

%[default:section(".text.crt{|.dos}.fs.basic_property")];

%
;

[[guard, export_alias("_umask")]]
$mode_t umask($mode_t mode);


%
%#ifdef __USE_GNU
@@Return the current umask.
@@WARNING: This function isn't thread-safe
[[userimpl, requires_function(umask)]]
$mode_t getumask() {
	$mode_t result;
	result = umask(0);
	umask(result);
	return result;
}
%#endif /* __USE_GNU */

%[default:section(".text.crt{|.dos}.fs.modify")];

%
%#if defined(__USE_KOS) && defined(__USE_ATFILE)
@@@param flags: Set of `0 | AT_DOSPATH'
[[cp]]
int fmkdirat($fd_t dirfd,
             [[nonnull]] char const *pathname,
             $mode_t mode, $atflag_t flags);

@@@param flags: Set of `0 | AT_DOSPATH'
[[cp]]
int fmknodat($fd_t dirfd, [[nonnull]] char const *nodename,
             $mode_t mode, $dev_t dev, $atflag_t flags);
%#endif


%
;

[[cp]]
int mkfifo([[nonnull]] char const *fifoname, $mode_t mode);

%
%#ifdef __USE_ATFILE
@@@param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH'
[[cp]] int fchmodat($fd_t dirfd, [[nonnull]] char const *filename, $mode_t mode, $atflag_t flags);
[[cp]] int mkdirat($fd_t dirfd, [[nonnull]] char const *pathname, $mode_t mode);
[[cp]] int mkfifoat($fd_t dirfd, [[nonnull]] char const *fifoname, $mode_t mode);
%#endif /* __USE_ATFILE */

%
%#ifdef __USE_POSIX
[[cp]] int fchmod($fd_t fd, $mode_t mode);
%#endif /* __USE_POSIX */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
[[cp]] int mknod([[nonnull]] char const *nodename, $mode_t mode, $dev_t dev);
%#ifdef __USE_ATFILE
[[cp]] int mknodat($fd_t dirfd, [[nonnull]] char const *nodename, $mode_t mode, $dev_t dev);
%#endif /* __USE_ATFILE */
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%[default:section(".text.crt{|.dos}.fs.modify_time")];

[[cp, ignore, doc_alias("utimensat"), nocrt, alias("utimensat")]]
int utimensat32($fd_t dirfd, [[nonnull]] char const *filename,
                [[nullable]] struct timespec const times[2 /*or:3*/],
                $atflag_t flags);


%
%#ifdef __USE_ATFILE
@@@param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH'
[[cp, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("utimensat64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("utimensat")]]
[[userimpl, requires($has_function(utimensat32) || $has_function(utimensat64))]]
[[impl_include("<asm/fcntl.h>")]]
int utimensat($fd_t dirfd, [[nonnull]] char const *filename,
              [[nullable]] struct timespec const times[2 /*or:3*/],
              $atflag_t flags) {
@@pp_if $has_function(utimensat64)@@
@@pp_ifdef __AT_CHANGE_CTIME@@
	struct timespec64 tms[3];
	if (!times)
		return utimensat64(dirfd, filename, NULL, flags);
	tms[0].tv_sec  = (__time64_t)times[0].tv_sec;
	tms[0].tv_nsec = times[0].tv_nsec;
	tms[1].tv_sec  = (__time64_t)times[1].tv_sec;
	tms[1].tv_nsec = times[1].tv_nsec;
	if (flags & __AT_CHANGE_CTIME) {
		tms[2].tv_sec  = (__time64_t)times[2].tv_sec;
		tms[2].tv_nsec = times[2].tv_nsec;
	}
	return utimensat64(dirfd, filename, tms, flags);
@@pp_else@@
	struct timespec64 tms[2];
	if (!times)
		return utimensat64(dirfd, filename, NULL, flags);
	tms[0].tv_sec  = (__time64_t)times[0].tv_sec;
	tms[0].tv_nsec = times[0].tv_nsec;
	tms[1].tv_sec  = (__time64_t)times[1].tv_sec;
	tms[1].tv_nsec = times[1].tv_nsec;
	return utimensat64(dirfd, filename, tms, flags);
@@pp_endif@@
@@pp_else@@
@@pp_ifdef __AT_CHANGE_CTIME@@
	struct @__timespec32@ tms[3];
	if (!times)
		return utimensat32(dirfd, filename, NULL, flags);
	tms[0].tv_sec  = (__time32_t)times[0].tv_sec;
	tms[0].tv_nsec = times[0].tv_nsec;
	tms[1].tv_sec  = (__time32_t)times[1].tv_sec;
	tms[1].tv_nsec = times[1].tv_nsec;
	if (flags & __AT_CHANGE_CTIME) {
		tms[2].tv_sec  = (__time32_t)times[2].tv_sec;
		tms[2].tv_nsec = times[2].tv_nsec;
	}
	return utimensat32(dirfd, filename, tms, flags);
@@pp_else@@
	struct @__timespec32@ tms[2];
	if (!times)
		return utimensat32(dirfd, filename, NULL, flags);
	tms[0].tv_sec  = (__time32_t)times[0].tv_sec;
	tms[0].tv_nsec = times[0].tv_nsec;
	tms[1].tv_sec  = (__time32_t)times[1].tv_sec;
	tms[1].tv_nsec = times[1].tv_nsec;
	return utimensat32(dirfd, filename, tms, flags);
@@pp_endif@@
@@pp_endif@@
}

%#ifdef __USE_TIME64
[[cp, time64_variant_of(utimensat)]]
[[userimpl, requires_function(utimensat32)]]
[[impl_include("<asm/fcntl.h>")]]
int utimensat64($fd_t dirfd, [[nonnull]] char const *filename,
                [[nullable]] struct timespec64 const times[2 /*or:3*/], $atflag_t flags) {
@@pp_ifdef __AT_CHANGE_CTIME@@
	struct timespec32 tms[3];
	if (!times)
		return utimensat32(dirfd, filename, NULL, flags);
	tms[0].tv_sec  = (__time32_t)times[0].tv_sec;
	tms[0].tv_nsec = times[0].tv_nsec;
	tms[1].tv_sec  = (__time32_t)times[1].tv_sec;
	tms[1].tv_nsec = times[1].tv_nsec;
	if (flags & 0x0200) /* AT_CHANGE_CTIME */ {
		tms[2].tv_sec  = (__time32_t)times[2].tv_sec;
		tms[2].tv_nsec = times[2].tv_nsec;
	}
	return utimensat32(dirfd, filename, tms, flags);
@@pp_else@@
	struct timespec32 tms[2];
	if (!times)
		return utimensat32(dirfd, filename, NULL, flags);
	tms[0].tv_sec  = (__time32_t)times[0].tv_sec;
	tms[0].tv_nsec = times[0].tv_nsec;
	tms[1].tv_sec  = (__time32_t)times[1].tv_sec;
	tms[1].tv_nsec = times[1].tv_nsec;
	return utimensat32(dirfd, filename, tms, flags);
@@pp_endif@@
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_ATFILE */

[[cp, ignore, nocrt, alias("futimens")]]
int futimens32($fd_t fd, [[nullable]] struct timespec const times[2 /*or:3*/]);

%
%#ifdef __USE_XOPEN2K8
[[cp, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(futimens64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(futimens)]]
[[userimpl, requires($has_function(futimens32) || $has_function(futimens64))]]
int futimens($fd_t fd, [[nullable]] struct timespec const times[2 /*or:3*/]) {
@@pp_if $has_function(futimens64)@@
	struct timespec64 tms[2];
	if (!times)
		return futimens64(fd, NULL);
	tms[0].tv_sec  = (__time64_t)times[0].tv_sec;
	tms[0].tv_nsec = times[0].tv_nsec;
	tms[1].tv_sec  = (__time64_t)times[1].tv_sec;
	tms[1].tv_nsec = times[1].tv_nsec;
	return futimens64(fd, tms);
@@pp_else@@
	struct timespec32 tms[2];
	if (!times)
		return futimens32(fd, NULL);
	tms[0].tv_sec  = (__time32_t)times[0].tv_sec;
	tms[0].tv_nsec = times[0].tv_nsec;
	tms[1].tv_sec  = (__time32_t)times[1].tv_sec;
	tms[1].tv_nsec = times[1].tv_nsec;
	return futimens32(fd, tms);
@@pp_endif@@
}

%#ifdef __USE_TIME64
[[cp, time64_variant_of(futimens)]]
[[userimpl, requires_function(futimens32)]]
int futimens64($fd_t fd, [[nullable]] struct timespec64 const times[2 /*or:3*/]) {
	struct timespec32 tms[2];
	if (!times)
		return futimens32(fd, NULL);
	tms[0].tv_sec  = (__time32_t)times[0].tv_sec;
	tms[0].tv_nsec = times[0].tv_nsec;
	tms[1].tv_sec  = (__time32_t)times[1].tv_sec;
	tms[1].tv_nsec = times[1].tv_nsec;
	return futimens32(fd, tms);
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_XOPEN2K8 */

%
%
%/* Define DOS's redundant stat() functions. */
%#ifdef __USE_DOS

%[default:section(".text.crt.dos.wchar.fs.stat")];

/* TODO: Emulate these functions when not running under DOS-CRT */
[[nocrt, alias("_stat", "_stat32")]]         int _stat32([[nonnull]] char const *__restrict filename, [[nonnull]] struct __dos_stat32 *__restrict buf);
[[nocrt, alias("_stati64", "_stat32i64")]]   int _stat32i64([[nonnull]] char const *__restrict filename, [[nonnull]] struct __dos_stat32i64 *__restrict buf);
[[nocrt, alias("_stat64", "_stat64i32")]]    int _stat64i32([[nonnull]] char const *__restrict filename, [[nonnull]] struct __dos_stat64i32 *__restrict buf);
[[nocrt, alias("_stat64", "_stat64i32")]]    int _stat64([[nonnull]] char const *__restrict filename, [[nonnull]] struct __dos_stat64 *__restrict buf);
[[nocrt, alias("_fstat", "_fstat32")]]       int _fstat32($fd_t fd, [[nonnull]] struct __dos_stat32 *__restrict buf);
[[nocrt, alias("_fstati64", "_fstat32i64")]] int _fstat32i64($fd_t fd, [[nonnull]] struct __dos_stat32i64 *__restrict buf);
[[nocrt, alias("_fstat64", "_fstat64i32")]]  int _fstat64i32($fd_t fd, [[nonnull]] struct __dos_stat64i32 *__restrict buf);
[[nocrt, alias("_fstat64", "_fstat64i32")]]  int _fstat64($fd_t fd, [[nonnull]] struct __dos_stat64 *__restrict buf);
[[wchar]] int _wstat32([[nonnull]] $wchar_t const *filename, [[nonnull]] struct __dos_stat32 *buf);
[[wchar]] int _wstat64([[nonnull]] $wchar_t const *filename, [[nonnull]] struct __dos_stat64 *buf);
[[wchar]] int _wstat32i64([[nonnull]] $wchar_t const *filename, [[nonnull]] struct __dos_stat32i64 *buf);
[[wchar]] int _wstat64i32([[nonnull]] $wchar_t const *filename, [[nonnull]] struct __dos_stat64i32 *buf);

%#endif /* __USE_DOS */


%{

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_KOS
#if defined(_WCHAR_H) && !defined(_PARTS_WCHAR_SYS_STAT_H)
#include <parts/wchar/sys/stat.h>
#endif /* _WCHAR_H && !_PARTS_WCHAR_SYS_STAT_H */
#endif /* __USE_KOS */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_SYS_STAT_H)
#include <parts/uchar/sys/stat.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_SYS_STAT_H */
#endif /* __USE_UTF */

}