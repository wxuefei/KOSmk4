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

%[declare_user_export(environ, _environ, __environ)]
%[declare_user_export(__peb, __argc, __argv, _pgmptr)]
%[declare_user_export(program_invocation_name, __progname_full)]
%[declare_user_export(program_invocation_short_name, __progname)]


%{
#include <features.h>

#include <kos/anno.h>

#include <unistd.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __pos_t_defined
#define __pos_t_defined 1
typedef __FS_TYPE(pos) pos_t; /* File/device position */
#endif /* !__pos_t_defined */

#ifdef __USE_LARGEFILE64
#ifndef __pos64_t_defined
#define __pos64_t_defined 1
typedef __pos64_t pos64_t; /* File/device position */
#endif /* !__pos64_t_defined */
#endif /* __USE_LARGEFILE64 */

}

%[default:section(".text.crt{|.dos}.except.fs.exec.exec")];

[[cp, throws, ATTR_NORETURN, doc_alias(execv), argument_names(path, ___argv)]]
void Execv([[nonnull]] char const *__restrict path, [[nonnull]] __TARGV);
[[cp, throws, ATTR_NORETURN, doc_alias(execve), argument_names(path, ___argv, ___envp)]]
void Execve([[nonnull]] char const *__restrict path, [[nonnull]] __TARGV, [[nonnull]] __TENVP);
[[cp, throws, ATTR_NORETURN, doc_alias(execvp), argument_names(file, ___argv)]]
void Execvp([[nonnull]] char const *__restrict file, [[nonnull]] __TARGV);

[[cp, throws, userimpl, impl_include("<parts/redirect-exec.h>"), doc_alias(execl)]]
[[requires_dependent_function(Execv), ATTR_SENTINEL, ATTR_NORETURN]]
void Execl([[nonnull]] char const *__restrict path, char const *args, ... /*, (char *)NULL*/) {
	__REDIRECT_XEXECL(char, Execv, path, args)
}

[[cp, throws, userimpl, impl_include("<parts/redirect-exec.h>"), doc_alias(execle)]]
[[requires_dependent_function(Execve), ATTR_SENTINEL_O(1), ATTR_NORETURN]]
void Execle([[nonnull]] char const *__restrict path, char const *args, ... /*, (char *)NULL, (char **)environ*/) {
	__REDIRECT_XEXECLE(char, Execve, path, args)
}

[[cp, throws, userimpl, impl_include("<parts/redirect-exec.h>"), doc_alias(execlp)]]
[[requires_dependent_function(Execvp), ATTR_SENTINEL, ATTR_NORETURN]]
void Execpl([[nonnull]] char const *__restrict file, char const *args, ... /*, (char *)NULL*/) {
	__REDIRECT_XEXECL(char, Execvp, file, args)
}

[[cp, throws, userimpl, impl_include("<parts/redirect-exec.h>"), doc_alias(execle)]]
[[requires_dependent_function(Execvpe), ATTR_SENTINEL_O(1), ATTR_NORETURN]]
void Execlpe([[nonnull]] char const *__restrict file, char const *args, ... /*, (char *)NULL, (char **)environ*/) {
	__REDIRECT_XEXECLE(char, Execvpe, file, args)
}


%
[[throws, doc_alias("pipe"), section(".text.crt{|.dos}.except.io.access")]]
void Pipe([[nonnull]] $fd_t pipedes[2]);


%
[[cp, throws, decl_include("<bits/types.h>"), doc_alias("fsync"), userimpl]]
[[alias("FDataSync"), section(".text.crt{|.dos}.except.io.sync")]]
void FSync($fd_t fd) {
	(void)fd;
	/* No-Op */
}


%[default:section(".text.crt{|.dos}.except.sched.process")]

%
[[throws, doc_alias("setpgid"), decl_include("<bits/types.h>")]]
void SetPGid($pid_t pid, $pid_t pgid);


%
[[throws, doc_alias("setsid"), decl_include("<bits/types.h>")]]
$pid_t SetSid();

%
[[throws, doc_alias("setuid"), decl_include("<bits/types.h>")]]
void SetUid($uid_t uid);

%
[[throws, doc_alias("setgid"), decl_include("<bits/types.h>")]]
void SetGid($gid_t gid);

%
[[throws, wunused, decl_include("<bits/types.h>"), doc_alias("fork")]]
[[section(".text.crt{|.dos}.except.sched.access")]]
$pid_t Fork();

%[default:section(".text.crt{|.dos}.except.fs.modify")]

%
[[cp, throws, decl_include("<bits/types.h>"), doc_alias("chown")]]
[[userimpl, requires(defined(__CRT_AT_FDCWD) && $has_function(FChownAt))]]
void Chown([[nonnull]] char const *file, $uid_t owner, $gid_t group) {
	FChownAt(__CRT_AT_FDCWD, file, owner, group, 0);
}

%
[[cp, throws, doc_alias("link")]]
[[userimpl, requires(defined(__CRT_AT_FDCWD) && $has_function(LinkAt))]]
void Link([[nonnull]] char const *from, [[nonnull]] char const *to) {
	LinkAt(__CRT_AT_FDCWD, from, __CRT_AT_FDCWD, to, 0);
}

%
[[cp, throws, decl_include("<bits/types.h>")]]
[[doc_alias("read"), section(".text.crt{|.dos}.except.io.read")]]
size_t Read($fd_t fd, [[outp(bufsize)]] void *buf, size_t bufsize);

%
[[cp, throws, decl_include("<bits/types.h>")]]
[[doc_alias("write"), section(".text.crt{|.dos}.except.io.write")]]
size_t Write($fd_t fd, [[inp(bufsize)]] void const *buf, size_t bufsize);

%
%#ifdef __USE_KOS
[[cp, throws, decl_include("<bits/types.h>")]]
[[doc_alias("readall"), section(".text.crt{|.dos}.except.io.read")]]
[[userimpl, requires_function(Read, lseek)]]
[[impl_include("<parts/errno.h>", "<kos/except.h>")]]
size_t ReadAll($fd_t fd, [[outp(bufsize)]] void *buf, size_t bufsize) {
	size_t result, temp;
	result = Read(fd, buf, bufsize);
	if (result != 0 && result < bufsize) {
		/* Keep on reading */
		for (;;) {
			@TRY@ {
				temp = Read(fd,
				           (byte_t *)buf + (size_t)result,
				            bufsize - (size_t)result);
			} @EXCEPT@ {
@@pp_ifdef __libc_geterrno@@
				int old_error = __libc_geterrno();
@@pp_endif@@
				/* Try to un-read data that had already been loaded. */
				lseek(fd, -(off_t)(pos_t)result, SEEK_CUR);
@@pp_ifdef __libc_geterrno@@
				__libc_seterrno(old_error);
@@pp_endif@@
				@RETHROW@();
			}
			if (!temp) {
				result = 0;
				break;
			}
			result += temp;
			if (result >= bufsize)
				break;
		}
	}
	return result;
}
%#endif /* __USE_KOS */


[[throws, decl_include("<bits/types.h>")]]
[[doc_alias("lseek32"), ignore, nocrt, alias("LSeek")]]
$pos32_t LSeek32($fd_t fd, $off32_t offset, int whence);

%
[[throws, decl_include("<bits/types.h>")]]
[[doc_alias(lseek), no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("LSeek64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("LSeek")]]
[[userimpl, requires($has_function(LSeek32) || $has_function(LSeek64))]]
[[section(".text.crt{|.dos}.except.io.seek")]]
$pos_t LSeek($fd_t fd, $off_t offset, int whence) {
@@pp_if $has_function(LSeek32)@@
	return LSeek32(fd, ($off32_t)offset, whence);
@@pp_else@@
	return LSeek64(fd, ($off64_t)offset, whence);
@@pp_endif@@
}

%
[[throws, decl_include("<bits/types.h>")]]
[[doc_alias("dup2"), section(".text.crt{|.dos}.except.io.access")]]
$fd_t Dup2($fd_t oldfd, $fd_t newfd);

%
[[throws, wunused, decl_include("<bits/types.h>")]]
[[doc_alias("dup"), section(".text.crt{|.dos}.except.io.access")]]
$fd_t Dup($fd_t fd);

%
[[cp, throws, doc_alias("chdir")]]
[[section(".text.crt{|.dos}.except.fs.basic_property")]]
void Chdir([[nonnull]] char const *path);

%
[[cp, throws, doc_alias("getcwd"), decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.except.fs.basic_property")]]
char *GetCwd([[outp_opt(bufsize)]] char *buf, size_t bufsize);

%[default:section(".text.crt{|.dos}.fs.modify")]

%
[[cp, throws, doc_alias("unlink")]]
[[userimpl, requires(defined(__CRT_AT_FDCWD) && $has_function(UnlinkAt))]]
void Unlink([[nonnull]] char const *file) {
	UnlinkAt(__CRT_AT_FDCWD, file, 0);
}

%
[[cp, throws, doc_alias("rmdir")]]
[[userimpl, requires(defined(__CRT_AT_FDCWD) && $has_function(UnlinkAt))]]
void Rmdir([[nonnull]] char const *path) {
	UnlinkAt(__CRT_AT_FDCWD, path, 0x0200); /* AT_REMOVEDIR */
}

%
%#ifdef __USE_ATFILE
%[default:section(".text.crt{|.dos}.except.fs.modify")]

%
[[cp, throws, doc_alias("fchownat"), decl_include("<bits/types.h>")]]
void FChownAt($fd_t dfd, [[nonnull]] char const *file,
              $uid_t owner, $gid_t group, $atflag_t flags);

%
[[cp, throws, doc_alias("linkat"), decl_include("<bits/types.h>")]]
void LinkAt($fd_t fromfd, [[nonnull]] char const *from,
            $fd_t tofd, [[nonnull]] char const *to,
            $atflag_t flags);

%
[[cp, throws, doc_alias("symlinkat"), decl_include("<bits/types.h>")]]
void SymlinkAt([[nonnull]] char const *link_text, $fd_t tofd,
               [[nonnull]] char const *target_path);

%[default:section(".text.crt{|.dos}.except.fs.property")]

%
[[cp, throws, doc_alias("readlinkat"), decl_include("<bits/types.h>")]]
size_t ReadlinkAt($fd_t dfd, [[nonnull]] char const *__restrict path,
                  [[outp(buflen)]] char *__restrict buf, size_t buflen);

%
%#ifdef __USE_KOS
[[cp, throws, doc_alias("freadlinkat"), decl_include("<bits/types.h>")]]
size_t FReadlinkAt($fd_t dfd, [[nonnull]] char const *__restrict path,
                   [[outp(buflen)]] char *__restrict buf, size_t buflen, $atflag_t flags);
%#endif /* __USE_KOS */

%[default:section(".text.crt{|.dos}.except.fs.modify")]

%
[[cp, throws, doc_alias("unlinkat"), decl_include("<bits/types.h>")]]
void UnlinkAt($fd_t dfd, [[nonnull]] char const *name, $atflag_t flags);
%#endif /* __USE_ATFILE */


%
%
%#ifdef __USE_LARGEFILE64
[[throws, decl_include("<bits/types.h>")]]
[[doc_alias("lseek64"), off64_variant_of(LSeek)]]
[[userimpl, requires_function(LSeek32)]]
[[section(".text.crt{|.dos}.except.io.large.seek")]]
$pos64_t LSeek64($fd_t fd, $off64_t offset, int whence) {
	return LSeek32(fd, (__off32_t)offset, whence);
}
%#endif /* __USE_LARGEFILE64 */


%
%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)

%
[[cp, throws, decl_include("<bits/types.h>")]]
[[doc_alias("pread"), no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("PRead64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("PRead")]]
[[section(".text.crt{|.dos}.except.io.read")]]
[[userimpl, requires($has_function(PRead32) || $has_function(PRead64))]]
size_t PRead($fd_t fd, [[outp(bufsize)]] void *buf, size_t bufsize, pos_t offset) {
@@pp_if $has_function(PRead32)@@
	return PRead32(fd, buf, bufsize, (pos32_t)offset);
@@pp_else@@
	return PRead64(fd, buf, bufsize, (pos64_t)offset);
@@pp_endif@@
}

[[cp, throws, decl_include("<bits/types.h>")]]
[[doc_alias("pwrite"), no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("PWrite64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("PWrite")]]
[[userimpl, requires($has_function(PWrite32) || $has_function(PWrite64))]]
[[section(".text.crt{|.dos}.except.io.write")]]
size_t PWrite($fd_t fd, [[inp(bufsize)]] void const *buf, size_t bufsize, pos_t offset) {
@@pp_if $has_function(PWrite32)@@
	return PWrite32(fd, buf, bufsize, (pos32_t)offset);
@@pp_else@@
	return PWrite64(fd, buf, bufsize, (pos64_t)offset);
@@pp_endif@@
}


%
%#ifdef __USE_KOS
[[cp, throws, decl_include("<bits/types.h>")]]
[[doc_alias("preadall"), no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("PReadAll64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("PReadAll")]]
[[userimpl, requires($has_function(PReadAll32) || $has_function(PReadAll64))]]
[[section(".text.crt{|.dos}.except.io.read")]]
size_t PReadAll($fd_t fd, [[outp(bufsize)]] void *buf, size_t bufsize, pos_t offset) {
@@pp_if $has_function(PReadAll32)@@
	return PReadAll32(fd, buf, bufsize, (pos32_t)offset);
@@pp_else@@
	return PReadAll64(fd, buf, bufsize, (pos64_t)offset);
@@pp_endif@@
}
%#endif /* __USE_KOS */

%
%#ifdef __USE_LARGEFILE64

[[cp, throws, ignore, nocrt, alias("PRead"), decl_include("<bits/types.h>")]]
size_t PRead32($fd_t fd, [[outp(bufsize)]] void *buf, size_t bufsize, $pos32_t offset);

[[cp, throws, ignore, nocrt, alias("PWrite"), decl_include("<bits/types.h>")]]
size_t PWrite32($fd_t fd, [[inp(bufsize)]] void const *buf, size_t bufsize, $pos32_t offset);

[[cp, throws, decl_include("<bits/types.h>")]]
[[doc_alias("pread64"), off64_variant_of(PRead)]]
[[userimpl, requires_function(PRead32), section(".text.crt{|.dos}.except.io.large.read")]]
size_t PRead64($fd_t fd, [[outp(bufsize)]] void *buf, size_t bufsize, pos64_t offset) {
	return PRead32(fd, buf, bufsize, (pos32_t)offset);
}

[[cp, throws, decl_include("<bits/types.h>")]]
[[doc_alias("pwrite64"), off64_variant_of(PWrite)]]
[[userimpl, requires_function(PWrite32), section(".text.crt{|.dos}.except.io.large.write")]]
size_t PWrite64($fd_t fd, [[outp(bufsize)]] void *buf, size_t bufsize, pos64_t offset) {
	return PWrite32(fd, buf, bufsize, (pos32_t)offset);
}

%
%#ifdef __USE_KOS
[[cp, throws, decl_include("<bits/types.h>")]]
[[ignore, nocrt, alias("PReadAll")]]
size_t PReadAll32($fd_t fd, [[outp(bufsize)]] void *buf, size_t bufsize, $pos32_t offset);

[[cp, throws, decl_include("<bits/types.h>")]]
[[doc_alias("preadall64"), off64_variant_of(PReadAll)]]
[[userimpl, requires_function(PRead64), section(".text.crt{|.dos}.except.io.large.read")]]
size_t PReadAll64($fd_t fd, [[inp(bufsize)]] void *buf, size_t bufsize, pos64_t offset) {
	size_t result, temp;
	result = PRead64(fd, buf, bufsize, offset);
	if (result != 0 && (size_t)result < bufsize) {
		/* Keep on reading */
		for (;;) {
			temp = PRead64(fd,
			              (byte_t *)buf + result,
			               bufsize - result,
			               offset + result);
			if (!temp) {
				result = 0;
				break;
			}
			result += temp;
			if (result >= bufsize)
				break;
		}
	}
	return result;
}
%#endif /* __USE_KOS */

%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

%
%
%#ifdef __USE_GNU

[[throws, decl_include("<bits/types.h>")]]
[[doc_alias("pipe2"), section(".text.crt{|.dos}.except.io.access")]]
void Pipe2([[nonnull]] $fd_t pipedes[2], $oflag_t flags);

[[throws, decl_include("<bits/types.h>")]]
[[doc_alias("dup3"), section(".text.crt{|.dos}.except.io.access")]]
$fd_t Dup3($fd_t oldfd, $fd_t newfd, $oflag_t flags);

[[cp, throws, doc_alias("get_current_dir_name"), decl_include("<bits/types.h>")]]
[[userimpl, requires_function(GetCwd), section(".text.crt{|.dos}.except.fs.basic_property")]]
GetCurrentDirName() -> [[nonnull, malloc]] char * {
	return GetCwd(NULL, 0);
}

[[cp, throws, decl_include("<bits/types.h>")]]
[[userimpl, section(".text.crt{|.dos}.except.fs.modify")]]
void SyncFs($fd_t fd) {
	(void)fd;
	/* NO-OP */
}

%[default:section(".text.crt{|.dos}.except.sched.user")];

[[throws, decl_include("<bits/types.h>")]]
void GetResUid($uid_t *ruid, $uid_t *euid, $uid_t *suid);

[[throws, decl_include("<bits/types.h>")]]
void GetResGid($gid_t *rgid, $gid_t *egid, $gid_t *sgid);

[[throws, decl_include("<bits/types.h>")]]
void SetResUid($uid_t ruid, $uid_t euid, $uid_t suid);

[[throws, decl_include("<bits/types.h>")]]
void SetResGid($gid_t rgid, $gid_t egid, $gid_t sgid);
%#endif /* __USE_GNU */

%#if (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8)) || \
%     defined(__USE_MISC)
[[ATTR_RETURNS_TWICE, wunused, decl_include("<bits/types.h>")]]
[[throws, doc_alias("vfork"), section(".text.crt{|.dos}.sched.access")]]
$pid_t VFork();
%#endif


%
[[cp, throws, decl_include("<bits/types.h>")]]
[[doc_alias("fchown"), section(".text.crt{|.dos}.except.fs.modify")]]
void FChown($fd_t fd, $uid_t owner, $gid_t group);

%
[[cp, throws, decl_include("<bits/types.h>")]]
[[doc_alias("fchdir"), section(".text.crt{|.dos}.except.fs.basic_property")]]
void FChdir($fd_t fd);

%
[[throws, decl_include("<bits/types.h>")]]
[[wunused, doc_alias("getpgid"), section(".text.crt{|.dos}.except.sched.user")]]
$pid_t GetPGid($pid_t pid);

%
[[throws, decl_include("<bits/types.h>")]]
[[wunused, doc_alias("getsid"), section(".text.crt{|.dos}.except.sched.process")]]
$pid_t GetSid($pid_t pid);

%
[[cp, throws, decl_include("<bits/types.h>")]]
[[doc_alias("lchown"), section(".text.crt{|.dos}.except.fs.modify")]]
[[userimpl, requires(defined(__CRT_AT_FDCWD) && $has_function(FChownAt))]]
void LChown([[nonnull]] char const *file, $uid_t owner, $gid_t group) {
	FChownAt(__CRT_AT_FDCWD, file, owner, group, 0x0100); /* AT_SYMLINK_NOFOLLOW */
}


%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)

%
[[throws, decl_include("<bits/types.h>")]]
[[doc_alias("truncate"), no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("Truncate64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("Truncate")]]
[[section(".text.crt{|.dos}.except.fs.modify")]]
[[userimpl, requires($has_function(Truncate32) || $has_function(Truncate64))]]
void Truncate([[nonnull]] char const *file, pos_t length) {
@@pp_if $has_function(Truncate32)@@
	Truncate64(file, (__pos64_t)length);
@@pp_else@@
	Truncate32(file, (__pos32_t)length);
@@pp_endif@@
}

[[doc_alias("Truncate"), ignore, nocrt, alias("Truncate")]]
[[throws, decl_include("<bits/types.h>")]]
vodi Truncate32([[nonnull]] char const *file, $pos32_t length);

%
%#ifdef __USE_LARGEFILE64
[[throws, decl_include("<bits/types.h>")]]
[[doc_alias("truncate64"), off64_variant_of(Truncate)]]
[[userimpl, requires_function(Truncate32), section(".text.crt{|.dos}.except.fs.modify")]]
void Truncate64([[nonnull]] char const *file, pos64_t length) {
	Truncate32(file, (__pos32_t)length);
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */
%

%#ifdef __USE_XOPEN2K8

%
[[guard, ATTR_NORETURN, doc_alias("fexecve")]]
[[cp, throws, decl_include("<bits/types.h>")]]
[[argument_names(fd, ___argv, ___envp), section(".text.crt{|.dos}.except.fs.exec.exec")]]
void FExecve($fd_t fd, [[nonnull]] __TARGV, [[nonnull]] __TENVP);

%#endif /* __USE_XOPEN2K8 */

%#ifdef __USE_GNU
[[cp, throws, ATTR_NORETURN, doc_alias("execvpe")]]
[[argument_names(file, ___argv, ___envp), section(".text.crt{|.dos}.except.fs.exec.exec")]]
void Execvpe([[nonnull]] char const *__restrict file, [[nonnull]] __TARGV, [[nonnull]] __TENVP);
%#endif /* __USE_GNU */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN)
[[throws, userimpl, section(".text.crt{|.dos}.except.sched.param")]]
int Nice(int inc) {
	(void)inc;
	/* It should be sufficient to emulate this is a no-op. */
	return 0;
}
%#endif /* __USE_MISC || __USE_XOPEN */


%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
[[throws, doc_alias(setpgrp), section(".text.crt{|.dos}.except.sched.process")]]
void SetPGrp();

[[doc_alias(setreuid), section(".text.crt{|.dos}.except.sched.user")]]
[[throws, decl_include("<bits/types.h>")]]
void SetReUid($uid_t ruid, $uid_t euid);

[[doc_alias(setregid), section(".text.crt{|.dos}.except.sched.user")]]
[[throws, decl_include("<bits/types.h>")]]
void SetReGid($gid_t rgid, $gid_t egid);
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%
%#ifdef __USE_XOPEN2K
[[doc_alias(seteuid), section(".text.crt{|.dos}.except.sched.user")]]
[[throws, decl_include("<bits/types.h>")]]
void SetEUid($uid_t euid);

[[doc_alias(setegid), section(".text.crt{|.dos}.except.sched.user")]]
[[throws, decl_include("<bits/types.h>")]]
void SetEGid($gid_t egid);
%#endif /* __USE_XOPEN2K */

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
[[cp, throws, doc_alias("symlink"), section(".text.crt{|.dos}.except.fs.modify")]]
[[userimpl, requires(defined(__CRT_AT_FDCWD) && $has_function(SymlinkAt))]]
void Symlink([[nonnull]] char const *link_text,
             [[nonnull]] char const *target_path) {
	SymlinkAt(link_text, __CRT_AT_FDCWD, target_path);
}

%
[[cp, doc_alias("readlink"), section(".text.crt{|.dos}.except.fs.property")]]
[[userimpl, requires(defined(__CRT_AT_FDCWD) && $has_function(ReadlinkAt))]]
[[throws, decl_include("<hybrid/typecore.h>")]]
size_t Readlink([[nonnull]] char const *__restrict path,
                [[outp(buflen)]] char *__restrict buf, size_t buflen) {
	ReadlinkAt(__CRT_AT_FDCWD, path, buf, buflen);
}

%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
[[doc_alias("gethostname")]]
[[section(".text.crt{|.dos}.except.system.configuration")]]
[[throws, decl_include("<hybrid/typecore.h>")]]
void GetHostName([[outp(buflen)]] char *name, size_t buflen);
%#endif /* __USE_UNIX98 || __USE_XOPEN2K */


%
%#ifdef __USE_MISC
%
[[doc_alias("sethostname"), section(".text.crt{|.dos}.except.system.configuration")]]
[[throws, decl_include("<hybrid/typecore.h>")]]
void SetHostName([[inp(len)]] char const *name, size_t len);

%
[[doc_alias("getdomainname"), section(".text.crt{|.dos}.except.system.configuration")]]
[[throws, decl_include("<hybrid/typecore.h>")]]
void GetDomainName([[outp(buflen)]] char *name, size_t buflen);

%
[[doc_alias("setdomainname"), section(".text.crt{|.dos}.except.system.configuration")]]
[[throws, decl_include("<hybrid/typecore.h>")]]
void SetDomainName([[inp(len)]] char const *name, size_t len);

[[cp, throws, section(".text.crt{|.dos}.except.system.utility")]]
[[vartypes($syscall_ulong_t, $syscall_ulong_t, $syscall_ulong_t,
           $syscall_ulong_t, $syscall_ulong_t, $syscall_ulong_t)]]
[[decl_include("<bits/types.h>")]]
__syscall_slong_t Syscall($syscall_ulong_t sysno, ...);

%#ifdef __USE_KOS
[[section(".text.crt{|.dos}.except.system.utility"), preferred_alias("Syscall")]]
[[cp, throws, decl_include("<bits/types.h>")]]
[[vartypes($syscall_ulong_t, $syscall_ulong_t, $syscall_ulong_t,
           $syscall_ulong_t, $syscall_ulong_t, $syscall_ulong_t)]]
__LONG64_TYPE__ Syscall64($syscall_ulong_t sysno, ...);
%#endif /* __USE_KOS */

%#endif /* __USE_MISC */

%
%#if defined(__USE_MISC) || \
%   (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
[[cp, throws, doc_alias("chroot"), section(".text.crt{|.dos}.except.fs.utility")]]
void ChRoot([[nonnull]] char const *__restrict path);
%#endif /* ... */


%
%#if defined(__USE_POSIX199309) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
[[doc_alias("ftruncate32"), ignore, nocrt, alias("FTruncate")]]
[[throws, decl_include("<bits/types.h>")]]
int FTruncate32($fd_t fd, __pos32_t length);

[[throws, doc_alias("ftruncate"), no_crt_self_import]]
[[if("defined(__USE_FILE_OFFSET64)"), preferred_alias("FTruncate64")]]
[[if("!defined(__USE_FILE_OFFSET64)"), preferred_alias("FTruncate")]]
[[userimpl, requires($has_function(FTruncate32) || $has_function(FTruncate64))]]
[[section(".text.crt{|.dos}.except.io.write"), decl_include("<bits/types.h>")]]
void FTruncate($fd_t fd, pos_t length) {
@@pp_if $has_function(FTruncate32)@@
	FTruncate32(fd, (__pos32_t)length);
@@pp_else@@
	FTruncate64(fd, (__pos64_t)length);
@@pp_endif@@
}

%
%#ifdef __USE_LARGEFILE64
[[throws, doc_alias("ftruncate64"), off64_variant_of(FTruncate)]]
[[section(".text.crt{|.dos}.except.io.large.write")]]
[[userimpl, requires_function(FTruncate32), decl_include("<bits/types.h>")]]
void FTruncate64($fd_t fd, pos64_t length) {
	FTruncate32(fd, (pos32_t)length);
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_POSIX199309 || __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

%
%#if defined(__USE_POSIX199309) || defined(__USE_UNIX98)
[[cp, throws, doc_alias("fdatasync"), userimpl, decl_include("<bits/types.h>")]]
[[alias("FSync"), section(".text.crt{|.dos}.except.io.sync")]]
void FDataSync($fd_t fd) {
	(void)fd;
	/* No-Op */
}
%#endif /* __USE_POSIX199309 || __USE_UNIX98 */


%{

#endif /* __CC__ */

__SYSDECL_END

}