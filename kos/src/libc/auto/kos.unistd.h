/* HASH CRC-32:0x6e6f1a3b */
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
#ifndef GUARD_LIBC_AUTO_KOS_UNISTD_H
#define GUARD_LIBC_AUTO_KOS_UNISTD_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/unistd.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTDEF ATTR_NORETURN NONNULL((1, 2)) void (LIBDCALL libd_Execv)(char const *__restrict path, __TARGV) THROWS(...);
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTDEF ATTR_NORETURN NONNULL((1, 2, 3)) void (LIBDCALL libd_Execve)(char const *__restrict path, __TARGV, __TENVP) THROWS(...);
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTDEF ATTR_NORETURN NONNULL((1, 2)) void (LIBDCALL libd_Execvp)(char const *__restrict file, __TARGV) THROWS(...);
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer) */
INTDEF NONNULL((1)) void (LIBDCALL libd_Pipe)(fd_t pipedes[2]) THROWS(...);
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
INTDEF void (LIBDCALL libd_FSync)(fd_t fd) THROWS(...);
/* >> setpgid(2)
 * Change the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `PID' is ZERO(0), use `gettid()' for it instead.
 * When `PGID' is ZERO(0), use `PID' (after it was substituted) for instead */
INTDEF void (LIBDCALL libd_SetPGid)(pid_t pid, pid_t pgid) THROWS(...);
/* >> setuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `UID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF void (LIBDCALL libd_SetUid)(uid_t uid) THROWS(...);
/* >> setgid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `GID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF void (LIBDCALL libd_SetGid)(gid_t gid) THROWS(...);
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
INTDEF NONNULL((1)) void (LIBDCALL libd_Chown)(char const *file, uid_t owner, gid_t group) THROWS(...);
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
INTDEF NONNULL((1, 2)) void (LIBDCALL libd_Link)(char const *from, char const *to) THROWS(...);
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
INTDEF NONNULL((2)) size_t (LIBDCALL libd_Read)(fd_t fd, void *buf, size_t bufsize) THROWS(...);
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
INTDEF NONNULL((2)) size_t (LIBDCALL libd_Write)(fd_t fd, void const *buf, size_t bufsize) THROWS(...);
/* >> readall(3)
 * Same as `read(2)', however keep on reading until `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If an error occurs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
INTDEF NONNULL((2)) size_t (LIBDCALL libd_ReadAll)(fd_t fd, void *buf, size_t bufsize) THROWS(...);
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
INTDEF pos_t (LIBDCALL libd_LSeek)(fd_t fd, off_t offset, int whence) THROWS(...);
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
INTDEF fd_t (LIBDCALL libd_Dup2)(fd_t oldfd, fd_t newfd) THROWS(...);
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `FD' and return its duplicated handle number */
INTDEF WUNUSED fd_t (LIBDCALL libd_Dup)(fd_t fd) THROWS(...);
/* >> chdir(2)
 * Change the current working directory to `PATH' */
INTDEF NONNULL((1)) void (LIBDCALL libd_Chdir)(char const *path) THROWS(...);
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTDEF char *(LIBDCALL libd_GetCwd)(char *buf, size_t bufsize) THROWS(...);
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
INTDEF NONNULL((1)) void (LIBDCALL libd_Unlink)(char const *file) THROWS(...);
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
INTDEF NONNULL((1)) void (LIBDCALL libd_Rmdir)(char const *path) THROWS(...);
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
INTDEF NONNULL((2)) void (LIBDCALL libd_FChownAt)(fd_t dfd, char const *file, uid_t owner, gid_t group, atflag_t flags) THROWS(...);
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
INTDEF NONNULL((2, 4)) void (LIBDCALL libd_LinkAt)(fd_t fromfd, char const *from, fd_t tofd, char const *to, atflag_t flags) THROWS(...);
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
INTDEF NONNULL((1, 3)) void (LIBDCALL libd_SymlinkAt)(char const *link_text, fd_t tofd, char const *target_path) THROWS(...);
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTDEF NONNULL((2, 3)) size_t (LIBDCALL libd_ReadlinkAt)(fd_t dfd, char const *__restrict path, char *__restrict buf, size_t buflen) THROWS(...);
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
INTDEF NONNULL((2, 3)) size_t (LIBDCALL libd_FReadlinkAt)(fd_t dfd, char const *__restrict path, char *__restrict buf, size_t buflen, atflag_t flags) THROWS(...);
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
INTDEF NONNULL((2)) void (LIBDCALL libd_UnlinkAt)(fd_t dfd, char const *name, atflag_t flags) THROWS(...);
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
INTDEF pos64_t (LIBDCALL libd_LSeek64)(fd_t fd, off64_t offset, int whence) THROWS(...);
/* >> pread(2)
 * Read data from a file at a specific offset */
INTDEF NONNULL((2)) size_t (LIBDCALL libd_PRead)(fd_t fd, void *buf, size_t bufsize, pos_t offset) THROWS(...);
/* >> pwrite(2)
 * Write data to a file at a specific offset */
INTDEF NONNULL((2)) size_t (LIBDCALL libd_PWrite)(fd_t fd, void const *buf, size_t bufsize, pos_t offset) THROWS(...);
/* >> preadall(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
INTDEF NONNULL((2)) size_t (LIBDCALL libd_PReadAll)(fd_t fd, void *buf, size_t bufsize, pos_t offset) THROWS(...);
/* >> pread64(2)
 * Read data from a file at a specific offset */
INTDEF NONNULL((2)) size_t (LIBDCALL libd_PRead64)(fd_t fd, void *buf, size_t bufsize, pos64_t offset) THROWS(...);
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
INTDEF NONNULL((2)) size_t (LIBDCALL libd_PWrite64)(fd_t fd, void *buf, size_t bufsize, pos64_t offset) THROWS(...);
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
INTDEF NONNULL((2)) size_t (LIBDCALL libd_PReadAll64)(fd_t fd, void *buf, size_t bufsize, pos64_t offset) THROWS(...);
INTDEF NONNULL((1)) void (LIBDCALL libd_Pipe2)(fd_t pipedes[2], oflag_t flags) THROWS(...);
INTDEF fd_t (LIBDCALL libd_Dup3)(fd_t oldfd, fd_t newfd, oflag_t flags) THROWS(...);
INTDEF void (LIBDCALL libd_SyncFs)(fd_t fd) THROWS(...);
INTDEF void (LIBDCALL libd_GetResUid)(uid_t *ruid, uid_t *euid, uid_t *suid) THROWS(...);
INTDEF void (LIBDCALL libd_GetResGid)(gid_t *rgid, gid_t *egid, gid_t *sgid) THROWS(...);
INTDEF void (LIBDCALL libd_SetResUid)(uid_t ruid, uid_t euid, uid_t suid) THROWS(...);
INTDEF void (LIBDCALL libd_SetResGid)(gid_t rgid, gid_t egid, gid_t sgid) THROWS(...);
/* >> fchown(2)
 * Change the ownership of a given `FD' to `GROUP:OWNER' */
INTDEF void (LIBDCALL libd_FChown)(fd_t fd, uid_t owner, gid_t group) THROWS(...);
/* >> chdir(2)
 * Change the current working directory to `PATH' */
INTDEF void (LIBDCALL libd_FChdir)(fd_t fd) THROWS(...);
/* >> getpgid(2)
 * Return the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `PID' is ZERO(0), use `gettid()' for it instead */
INTDEF WUNUSED pid_t (LIBDCALL libd_GetPGid)(pid_t pid) THROWS(...);
/* >> getsid(2)
 * Return the ID of the session which a process `PID' is apart of.
 * return THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID; */
INTDEF WUNUSED pid_t (LIBDCALL libd_GetSid)(pid_t pid) THROWS(...);
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
INTDEF NONNULL((1)) void (LIBDCALL libd_LChown)(char const *file, uid_t owner, gid_t group) THROWS(...);
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTDEF NONNULL((1)) void (LIBDCALL libd_Truncate)(char const *file, pos_t length) THROWS(...);
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTDEF NONNULL((1)) void (LIBDCALL libd_Truncate64)(char const *file, pos64_t length) THROWS(...);
/* >> fexecve(2)
 * Replace the calling process with the application image referred to by `FD' and
 * execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTDEF ATTR_NORETURN NONNULL((2, 3)) void (LIBDCALL libd_FExecve)(fd_t fd, __TARGV, __TENVP) THROWS(...);
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTDEF ATTR_NORETURN NONNULL((1, 2, 3)) void (LIBDCALL libd_Execvpe)(char const *__restrict file, __TARGV, __TENVP) THROWS(...);
INTDEF int (LIBDCALL libd_Nice)(int inc) THROWS(...);
INTDEF void (LIBDCALL libd_SetReUid)(uid_t ruid, uid_t euid) THROWS(...);
INTDEF void (LIBDCALL libd_SetReGid)(gid_t rgid, gid_t egid) THROWS(...);
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EUID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF void (LIBDCALL libd_SetEUid)(uid_t euid) THROWS(...);
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EGID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF void (LIBDCALL libd_SetEGid)(gid_t egid) THROWS(...);
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
INTDEF NONNULL((1, 2)) void (LIBDCALL libd_Symlink)(char const *link_text, char const *target_path) THROWS(...);
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTDEF NONNULL((1, 2)) size_t (LIBDCALL libd_Readlink)(char const *__restrict path, char *__restrict buf, size_t buflen) THROWS(...);
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
INTDEF NONNULL((1)) void (LIBDCALL libd_GetHostName)(char *name, size_t buflen) THROWS(...);
/* >> sethostname(2)
 * Set the name of the hosting machine */
INTDEF NONNULL((1)) void (LIBDCALL libd_SetHostName)(char const *name, size_t len) THROWS(...);
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
INTDEF NONNULL((1)) void (LIBDCALL libd_GetDomainName)(char *name, size_t buflen) THROWS(...);
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
INTDEF NONNULL((1)) void (LIBDCALL libd_SetDomainName)(char const *name, size_t len) THROWS(...);
INTDEF __syscall_slong_t (VLIBDCALL libd_Syscall)(syscall_ulong_t sysno, ...) THROWS(...);
INTDEF __LONG64_TYPE__ (VLIBDCALL libd_Syscall64)(syscall_ulong_t sysno, ...) THROWS(...);
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
INTDEF NONNULL((1)) void (LIBDCALL libd_ChRoot)(char const *__restrict path) THROWS(...);
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
INTDEF void (LIBDCALL libd_FTruncate)(fd_t fd, pos_t length) THROWS(...);
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
INTDEF void (LIBDCALL libd_FTruncate64)(fd_t fd, pos64_t length) THROWS(...);
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps, and its size), meaning that changes are written to disk */
INTDEF void (LIBDCALL libd_FDataSync)(fd_t fd) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_KOS_UNISTD_H */
