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
#ifndef GUARD_MODGDBSERVER_GDB_INFO_C
#define GUARD_MODGDBSERVER_GDB_INFO_C 1
#define _GNU_SOURCE 1

#include "gdb-info.h"

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/driver.h>
#include <kernel/handle.h>
#include <kernel/uname.h>
#include <kernel/vm.h>
#include <kernel/vm/exec.h>
#include <kernel/vm/library.h>
#include <sched/pid.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/unaligned.h>

#include <assert.h>
#include <errno.h>
#include <format-printer.h>
#include <inttypes.h>
#include <string.h>

#include <libcmdline/encode.h>

#include "gdb.h"
#include "server.h"
#include "thread-enum.h"

#define XML_VERSION_HEADER "<?xml version=\"1.0\"?>"

DECL_BEGIN

#define DO(expr)      do{ if ((temp = (expr)) < 0) goto err; result += temp; }__WHILE0
#define print(p, len) DO((*printer)(arg, p, len))
#define PRINT(str)    DO((*printer)(arg, str, COMPILER_STRLEN(str)))
#define PRINTF(...)   DO(format_printf(printer, arg, __VA_ARGS__))


/* NOTE: All of the following functions return negative ERRNO values on failure. */
/* Print a human-readable name for `thread' */
INTERN NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDBInfo_PrintThreadName)(pformatprinter printer, void *arg,
                                       struct task *__restrict thread) {
	ssize_t temp, result;
	pid_t pid, tid;
	result = GDBInfo_PrintThreadExecFile(printer, arg, thread, true);
	if unlikely(result < 0)
		goto done;
	pid = task_getrootpid_of_s(thread);
	tid = task_getroottid_of_s(thread);
	PRINT(" (");
	if (pid && tid && pid != tid)
		PRINTF("%u.%u:", pid, tid);
	else if (tid) {
		PRINTF("%u:", tid);
	}
	PRINTF("%p)", thread);
done:
	return result;
err:
	return temp;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintKernelFilename)(pformatprinter printer, void *arg,
                                           bool filename_only) {
	char const *str = filename_only
	                  ? kernel_driver.d_name
	                  : kernel_driver.d_filename;
	return (*printer)(arg, str, strlen(str));
}

/* Print the commandline of a given `thread' */
INTERN NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDBInfo_PrintThreadCommandline)(pformatprinter printer, void *arg,
                                              struct task *__restrict thread) {
	ssize_t result;
	if (GDBThread_IsKernelThread(thread)) {
		result = cmdline_encode(printer, arg,
		                        kernel_driver.d_argc,
		                        kernel_driver.d_argv);
	} else {
		/* TODO: Must eventually use the same trick as `/proc/[pid]/cmdline' */
		result = GDBInfo_PrintThreadExecFile(printer, arg, thread, false);
	}
	return result;
}


/* `qXfer:exec-file:read': Print the absolute filename for the original
 * binary passed to exec() when the process of `thread' was started.
 * (`/proc/${PID_OF(thread)}/exe') */
INTERN NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDBInfo_PrintThreadExecFile)(pformatprinter printer, void *arg,
                                           struct task *__restrict thread,
                                           bool filename_only) {
	ssize_t result;
	REF struct vm *v;
	REF struct directory_entry *dent;
	REF struct path            *path;
	if (task_getrootpid_of_s(thread) == 0 ||
	    task_getroottid_of_s(thread) == 0)
		return GDBInfo_PrintKernelFilename(printer, arg, filename_only);
	v = task_getvm(thread);
	if (v == &vm_kernel)
		result = GDBInfo_PrintKernelFilename(printer, arg, filename_only);
	else {
		if (GDBThread_IsAllStopModeActive) {
			dent = xincref(FORVM(v, thisvm_execinfo).ei_dent);
			path = xincref(FORVM(v, thisvm_execinfo).ei_path);
		} else {
			/* FIXME: What if one of the suspended threads is holding the VM lock?
			 *        We should have some kind of timeout here, and switch to all-stop
			 *        mode if the timeout expires. */
			sync_read(v);
			dent = xincref(FORVM(v, thisvm_execinfo).ei_dent);
			path = xincref(FORVM(v, thisvm_execinfo).ei_path);
			sync_endread(v);
		}
		if (filename_only && (dent || path)) {
			result = dent ? (*printer)(arg, dent->de_name, dent->de_namelen)
			              : (*printer)(arg, "?", 1);
			xdecref_unlikely(path);
			xdecref_unlikely(dent);
		} else if (dent && path) {
			result = path_printentex(path,
			                         dent->de_name,
			                         dent->de_namelen,
			                         printer,
			                         arg,
			                         PATH_PRINT_MODE_NORMAL,
			                         &vfs_kernel);
			decref_unlikely(path);
			decref_unlikely(dent);
		} else if (path) {
			result = path_printex(path, printer, arg,
			                      PATH_PRINT_MODE_INCTRAIL,
			                      &vfs_kernel);
			if likely(result >= 0) {
				ssize_t temp;
				temp = (*printer)(arg, "?", 1);
				if unlikely(temp < 0)
					result = temp;
				else {
					result += temp;
				}
			}
			decref_unlikely(path);
		} else if (dent) {
			result = (*printer)(arg,"/?/", 3);
			if likely(result >= 0) {
				ssize_t temp;
				temp = (*printer)(arg,
				                  dent->de_name,
				                  dent->de_namelen);
				if unlikely(temp < 0)
					result = temp;
				else {
					result += temp;
				}
			}
			decref_unlikely(dent);
		} else if (thread == &_boottask) {
			/* Workaround for early-boot (before the initial user-space exec()) */
			result = GDBInfo_PrintKernelFilename(printer, arg,
			                                     filename_only);
		} else {
			result = (*printer)(arg, "?", 1);
		}
	}
	decref_unlikely(v);
	return result;
}


PRIVATE NONNULL((1, 3)) ssize_t KCALL
GDB_PrintRemoteVMString(pformatprinter printer, void *arg,
                        struct vm *__restrict effective_vm,
                        USER CHECKED char const *string,
                        bool print_repr) {
	char buf[256];
	ssize_t temp, result = 0;
	for (;;) {
		size_t partlen, maxread;
		/* Stay within the same page when reading memory. */
		maxread = PAGESIZE - ((uintptr_t)string & PAGEMASK);
		if (maxread > sizeof(buf))
			maxread = sizeof(buf);
		vm_read(effective_vm, string, buf, maxread, true);
		partlen = strnlen(buf, maxread);
		assert(partlen <= maxread);
		DO(print_repr ? format_escape(printer, arg, buf, partlen, FORMAT_ESCAPE_FPRINTRAW)
		              : (*printer)(arg, buf, partlen));
		if (partlen < maxread)
			break;
		string += maxread;
	}
	return result;
err:
	return temp;
}

typedef struct {
	pformatprinter ll_printer; /* Printer. */
	void          *ll_arg;     /* Printer argument. */
} GDB_LibraryListPrinterData;

PRIVATE NONNULL((1, 2)) ssize_t KCALL
GDB_LibraryListPrinter(void *closure,
                       struct vm *__restrict effective_vm,
                       USER CHECKED char const *filename,
                       USER UNCHECKED void *UNUSED(loadaddr),
                       USER UNCHECKED void *loadstart,
                       bool UNUSED(filename_may_be_relative)) {
	ssize_t temp, result = 0;
	pformatprinter printer; void *arg;
	printer = ((GDB_LibraryListPrinterData *)closure)->ll_printer;
	arg     = ((GDB_LibraryListPrinterData *)closure)->ll_arg;
	PRINT("<library name=\"");
	TRY {
		DO(GDB_PrintRemoteVMString(printer, arg, effective_vm, filename, true));
	} EXCEPT {
	}
	PRINTF("\">"
	           "<segment address=\"%#" PRIxPTR "\"/>"
	       "</library>",
	       loadstart);
	return result;
err:
	return temp;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintKernelDriverList)(pformatprinter printer, void *arg) {
	size_t i; ssize_t temp, result = 0;
	REF struct driver_state *state;
	state = driver_get_state();
	for (i = 0; i < state->ds_count; ++i) {
		struct driver *d = state->ds_drivers[i];
		ElfW(Half) j;
		ElfW(Addr) lowest_segment_offset;
		size_t alignment_offset;
		/* One would expect that GDB wants `d_loadaddr', but that is incorrect.
		 * One might also thing that GDB wants `d_loadstart', and that is ~mostly~ correct.
		 * But what GDB actually wants is the absolute address of the first segment, meaning
		 * we need to adjust the driver load address for the sub-page offset of the segment
		 * with the lowest vaddr offset. */
		alignment_offset      = 0;
		lowest_segment_offset = (ElfW(Addr))-1;
		assert(d->d_phnum != 0);
		for (j = 0; j < d->d_phnum; ++j) {
			if (d->d_phdr[j].p_type != PT_LOAD)
				continue;
			if (d->d_phdr[j].p_vaddr >= lowest_segment_offset)
				continue;
			lowest_segment_offset = d->d_phdr[j].p_vaddr;
			alignment_offset      = d->d_phdr[j].p_offset & PAGEMASK;
		}
		if (d->d_filename) {
			PRINTF("<library name=\"%#q\">", d->d_filename);
		} else {
			REF struct driver_library_path_string *libpath;
			libpath = driver_library_path.get();
			if (!strrchr(libpath->dlp_path, ':')) {
				/* Only a single library path was defined.
				 * In this case, we can pretty much assume where the driver originates from. */
				size_t len;
				char const *path = libpath->dlp_path;
				while (*path == '/')
					++path;
				len = strlen(path);
				while (len && path[len - 1] == '/')
					--len;
				PRINTF("<library name=\"/%#$q/%#q\">", len, path, d->d_name);
				decref_unlikely(libpath);
			} else {
				decref_unlikely(libpath);
				PRINTF("<library name=\"%#q\">", d->d_name);
			}
		}
		PRINTF("<segment address=\"%#" PRIxPTR "\"/>"
		       "</library>",
		       d->d_loadstart + alignment_offset);
	}
	decref_unlikely(state);
	return result;
err:
	decref_unlikely(state);
	return temp;
}


/* `qXfer:libraries:read': Print the list of library loaded into the current process. */
INTERN NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintLibraryList)(pformatprinter printer, void *arg,
                                        struct task *__restrict thread) {
	ssize_t result;
	REF struct vm *v = task_getvm(thread);
	result = GDBInfo_PrintVMLibraryList(printer, arg, v);
	decref_unlikely(v);
	return result;
}

INTERN NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintVMLibraryList)(pformatprinter printer, void *arg,
                                          struct vm *__restrict effective_vm) {
	ssize_t temp, result = 0;
	GDB_LibraryListPrinterData data;
	data.ll_printer = printer;
	data.ll_arg     = arg;
	PRINTF(XML_VERSION_HEADER
	       "<!DOCTYPE target SYSTEM \"library-list.dtd\">"
	       "<library-list>"
	           "<library name=%q>"
	               "<segment address=\"%#" PRIxPTR "\"/>"
	           "</library>",
	       kernel_driver.d_filename,
	       kernel_driver.d_loadstart);
	DO(GDBInfo_PrintKernelDriverList(printer, arg));
	/* Print user-space library listings. */
	if (effective_vm != &vm_kernel) {
		TRY {
			DO(vm_library_enumerate(effective_vm, &GDB_LibraryListPrinter, &data));
		} EXCEPT {
		}
	}
	PRINT("</library-list>");
	return result;
err:
	return temp;
}



struct GDBInfo_PrintThreadList_Data {
	pformatprinter ptld_printer;
	void          *ptld_arg;
};

INTDEF char *
NOTHROW(FCALL GDBThread_EncodeThreadID)(char *buf,
                                        struct task *__restrict thread);
#if __SIZEOF_POINTER__ > 4
#define GDBTHREAD_ENCODETHREADID_MAXCHARS 37 /* p-123456789abcdef0.-123456789abcdef0\0 */
#else /* __SIZEOF_POINTER__ > 4 */
#define GDBTHREAD_ENCODETHREADID_MAXCHARS 21 /* p-12345678.-12345678\0 */
#endif /* __SIZEOF_POINTER__ <= 4 */


PRIVATE ssize_t
NOTHROW(FCALL GDBInfo_PrintThreadList_Callback)(void *closure,
                                                struct task *__restrict thread) {
	ssize_t temp, result = 0;
	pformatprinter printer; void *arg;
	char id_buf[GDBTHREAD_ENCODETHREADID_MAXCHARS], *id_end;
	char const *description;
	uintptr_t flags;
	/* Skip dead threads: If this check wasn't here, then GDB would think
	 *                    that following a thread/process-exited stop event,
	 *                    the thread's/process's TID/PID had been re-assigned
	 *                    immediately, and that the still-terminating thread
	 *                    was actually an entirely different thread. */
	if (ATOMIC_READ(thread->t_flags) & (TASK_FTERMINATED | TASK_FTERMINATING))
		return 0;
	printer = ((struct GDBInfo_PrintThreadList_Data *)closure)->ptld_printer;
	arg     = ((struct GDBInfo_PrintThreadList_Data *)closure)->ptld_arg;
	id_end = GDBThread_EncodeThreadID(id_buf, thread);
	assert((size_t)(id_end - id_buf) < GDBTHREAD_ENCODETHREADID_MAXCHARS);
	PRINTF("<thread id=\"%$s\" core=\"%u\" name=\"",
	       (size_t)(id_end - id_buf), id_buf,
	       thread->t_cpu->c_id);
	DO(GDBInfo_PrintThreadName(printer, arg, thread));
	flags = ATOMIC_READ(thread->t_flags);
	if (flags & TASK_FTERMINATED)
		description = "terminated";
	else if (flags & TASK_FTERMINATING)
		description = "terminating";
	else if (thread == &FORCPU(thread->t_cpu, thiscpu_idle))
		description = "idle";
	else if (flags & TASK_FRUNNING)
		description = "running";
	else {
		description = "?";
	}
	PRINTF("\">%s</thread>", description);
	return result;
err:
	return temp;
}


/* `qXfer:threads:read': Print the list of threads apart of the current process. */
INTERN NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintThreadList)(pformatprinter printer, void *arg) {
	ssize_t temp, result = 0;
	struct GDBInfo_PrintThreadList_Data data;
	PRINT(XML_VERSION_HEADER
	      "<threads>");
	data.ptld_printer = printer;
	data.ptld_arg     = arg;
	DO(GDBThread_Enumerate(&GDBInfo_PrintThreadList_Callback, &data));
	PRINT("</threads>");
	return result;
err:
	return temp;
}


PRIVATE ssize_t
NOTHROW(FCALL GDBInfo_PrintProcessList_Callback)(void *closure,
                                                 struct task *__restrict thread) {
	ssize_t temp, result = 0; upid_t pid;
	pformatprinter printer; void *arg;
	if (!task_isprocessleader_p(thread))
		goto done;
	if (GDBThread_IsKernelThread(thread))
		goto done;
	printer = ((struct GDBInfo_PrintThreadList_Data *)closure)->ptld_printer;
	arg     = ((struct GDBInfo_PrintThreadList_Data *)closure)->ptld_arg;
	pid = task_getrootpid_of_s(thread);
	PRINTF("<item>"
	       "<column name=\"pid\">%" PRIx32 "</column>"
	       "<column name=\"user\">root</column>"
	       "<column name=\"program\">", pid);
	DO(GDBInfo_PrintThreadExecFile(printer, arg, thread, false));
	PRINT("</column>"
	      "<column name=\"command\">");
	DO(GDBInfo_PrintThreadCommandline(printer, arg, thread));
	PRINT("</column>"
	      /* XXX: <column name="cores">1,2,3</column> */
	      "</item>");
done:
	return result;
err:
	return temp;
}


/* `qXfer:osdata:read:processes': Print the list of processes running on the system. */
PRIVATE NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintProcessList)(pformatprinter printer, void *arg) {
	struct GDBInfo_PrintThreadList_Data data;
	ssize_t temp, result = 0;
	PRINT(XML_VERSION_HEADER
	      "<!DOCTYPE target SYSTEM \"osdata.dtd\">"
	      "<osdata type=\"processes\">");
	PRINTF("<item>"
	       "<column name=\"pid\">%" PRIx32 "</column>"
	       "<column name=\"user\">root</column>"
	       "<column name=\"program\">%s</column>"
	       "<column name=\"command\">",
	       GDB_KERNEL_PID,
	       kernel_driver.d_filename);
	DO(cmdline_encode(printer, arg,
	                  kernel_driver.d_argc,
	                  kernel_driver.d_argv));
	PRINT("</column>"
	      "</item>");
	data.ptld_printer = printer;
	data.ptld_arg     = arg;
	DO(GDBThread_Enumerate(&GDBInfo_PrintProcessList_Callback, &data));
	PRINT("</osdata>");
	return result;
err:
	return temp;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) bool
NOTHROW(FCALL is_a_valid_driver)(struct driver *__restrict d,
                                 struct driver_state const *__restrict ds) {
	size_t i;
	if (d == &kernel_driver)
		return true;
	for (i = 0; i < ds->ds_count; ++i) {
		if (ds->ds_drivers[i] == d)
			return true;
	}
	return false;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintDriverListEntry)(pformatprinter printer, void *arg,
                                            struct driver *__restrict d,
                                            struct driver_state const *__restrict ds) {
	size_t i;
	ssize_t temp, result = 0;
	PRINTF("<item>"
	       "<column name=\"name\">%s</column>"
	       "<column name=\"file\">%s</column>"
	       "<column name=\"args\">",
	       d->d_name,
	       d->d_filename);
	DO(cmdline_encode(printer, arg, d->d_argc, d->d_argv));
	PRINTF("</column>"
	       "<column name=\"loadaddr\">%p</column>"
	       "<column name=\"loadstart\">%p</column>"
	       "<column name=\"loadend\">%p</column>"
	       "<column name=\"dependencies\">",
	       d->d_loadaddr,
	       d->d_loadstart,
	       d->d_loadend);
	for (i = 0; i < d->d_depcnt; ++i) {
		struct driver *dep = d->d_depvec[i];
		if (i != 0)
			PRINT(",");
		if (is_a_valid_driver(dep, ds)) {
			print(dep->d_name, strlen(dep->d_name));
		} else {
			PRINT("?");
		}
	}
	PRINT("</column>");
	PRINT("</item>");
	return result;
err:
	return temp;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintDriverList)(pformatprinter printer, void *arg) {
	size_t i;
	ssize_t temp, result = 0;
	REF struct driver_state *ds;
	ds = driver_get_state();
	PRINT("<osdata type=\"drivers\">");
	DO(GDBInfo_PrintDriverListEntry(printer, arg,
	                                &kernel_driver, ds));
	for (i = 0; i < ds->ds_count; ++i) {
		DO(GDBInfo_PrintDriverListEntry(printer, arg,
		                                ds->ds_drivers[i], ds));
	}
	PRINT("</osdata>");
	decref_unlikely(ds);
	return result;
err:
	decref_unlikely(ds);
	return temp;
}

PRIVATE ssize_t
NOTHROW(FCALL GDBInfo_PrintFdListEntry)(pformatprinter printer, void *arg,
                                        struct task *__restrict thread,
                                        upid_t pid, unsigned int fdno,
                                        struct handle *__restrict hnd) {
	ssize_t temp, result = 0;
	PRINTF("<item>"
	       "<column name=\"pid\">%" PRIx32 "</column>", pid);
	PRINT("<column name=\"command\">");
	DO(GDBInfo_PrintThreadCommandline(printer, arg, thread));
	PRINTF("</column>"
	       "<column name=\"file descriptor\">%u</column>"
	       "<column name=\"name\">", fdno);
	DO(handle_print(hnd, printer, arg));
	PRINT("</column>"
	      "</item>");
	return result;
err:
	return temp;
}

PRIVATE ssize_t
NOTHROW(FCALL GDBInfo_PrintFdList_Callback)(void *closure,
                                            struct task *__restrict thread) {
	ssize_t temp, result = 0; upid_t pid;
	pformatprinter printer; void *arg;
	REF struct handle_manager *hman;
	unsigned int i;
	if (!task_isprocessleader_p(thread))
		goto done;
	if (GDBThread_IsKernelThread(thread))
		goto done;
	printer = ((struct GDBInfo_PrintThreadList_Data *)closure)->ptld_printer;
	arg     = ((struct GDBInfo_PrintThreadList_Data *)closure)->ptld_arg;
	pid     = task_getrootpid_of_s(thread);
	hman    = task_gethandlemanager(thread);
	if (!GDBThread_IsAllStopModeActive) {
		/* FIXME: What if one of the suspended threads is holding the VM lock?
		 *        We should have some kind of timeout here, and switch to all-stop
		 *        mode if the timeout expires. */
		sync_read(&hman->hm_lock);
	}
	if (hman->hm_mode == HANDLE_MANAGER_MODE_LINEAR) {
		for (i = 0; i < hman->hm_linear.hm_alloc; ++i) {
			if (hman->hm_linear.hm_vector[i].h_type == HANDLE_TYPE_UNDEFINED)
				continue;
			DO(GDBInfo_PrintFdListEntry(printer, arg, thread, pid, i,
			                            &hman->hm_linear.hm_vector[i]));
		}
	} else {
		for (i = 0; i <= hman->hm_hashvector.hm_hashmsk; ++i) {
			unsigned int fd, index;
			fd = hman->hm_hashvector.hm_hashvec[i].hh_handle_id;
			if (fd == HANDLE_HASHENT_SENTINEL_ID)
				continue; /* Unused / Sentinel */
			index = hman->hm_hashvector.hm_hashvec[i].hh_vector_index;
			if (index == (unsigned int)-1)
				continue; /* Deleted */
			DO(GDBInfo_PrintFdListEntry(printer, arg, thread, pid, fd,
			                            &hman->hm_hashvector.hm_vector[index]));
		}
	}
	if (!GDBThread_IsAllStopModeActive)
		sync_endread(&hman->hm_lock);
	decref_unlikely(hman);
done:
	return result;
err:
	if (!GDBThread_IsAllStopModeActive)
		sync_endread(&hman->hm_lock);
	decref_unlikely(hman);
	return temp;
}


/* `qXfer:osdata:read:processes': Print the list of processes running on the system. */
PRIVATE NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintFdList)(pformatprinter printer, void *arg) {
	struct GDBInfo_PrintThreadList_Data data;
	ssize_t temp, result = 0;
	PRINT("<osdata type=\"files\">");
	data.ptld_printer = printer;
	data.ptld_arg     = arg;
	DO(GDBThread_Enumerate(&GDBInfo_PrintFdList_Callback, &data));
	PRINT("</osdata>");
	return result;
err:
	return temp;
}


/* `qXfer:osdata:read:processes': Print the list of processes running on the system. */
PRIVATE NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintUname)(pformatprinter printer, void *arg) {
#define FIELD(name)                            \
	"<item>"                                   \
	"<column name=\"field\">" name "</column>" \
	"<column name=\"value\">%s</column>"       \
	"</item>"
	return format_printf(printer, arg,
	                     "<osdata type=\"uname\">"
	                     FIELD("sysname")
	                     FIELD("nodename")
	                     FIELD("release")
	                     FIELD("version")
	                     FIELD("machine")
	                     FIELD("domainname")
	                     "</osdata>",
	                     kernel_uname.sysname,
	                     kernel_uname.nodename,
	                     kernel_uname.release,
	                     kernel_uname.version,
	                     kernel_uname.machine,
	                     kernel_uname.domainname);
#undef FIELD
}


PRIVATE ssize_t
NOTHROW(FCALL GDBInfo_PrintOSThreadList_Callback)(void *closure,
                                                  struct task *__restrict thread) {
	ssize_t temp, result = 0;
	pformatprinter printer; void *arg;
	intptr_t pid, tid;
	pid = (intptr_t)task_getrootpid_of_s(thread);
	tid = (intptr_t)task_getroottid_of_s(thread);
	if unlikely(!pid || !tid) {
		pid = GDB_KERNEL_PID; /* Kernel thread. */
		tid = GDB_KERNEL_TID(thread);
	}
	printer = ((struct GDBInfo_PrintThreadList_Data *)closure)->ptld_printer;
	arg     = ((struct GDBInfo_PrintThreadList_Data *)closure)->ptld_arg;
	PRINT("<item>"
	      "<column name=\"pid\">");
	if (pid < 0) {
		PRINT("-");
		pid = -pid;
	}
	PRINTF("%" PRIxPTR "</column>"
	       "<column name=\"tid\">",
	       (uintptr_t)pid);
	if (tid < 0) {
		PRINT("-");
		tid = -tid;
	}
	PRINTF("%" PRIxPTR "</column>"
	       "<column name=\"program\">",
	       (uintptr_t)tid);
	DO(GDBInfo_PrintThreadExecFile(printer, arg, thread, false));
	PRINT("</column>"
	      "<column name=\"command\">");
	DO(GDBInfo_PrintThreadCommandline(printer, arg, thread));
	PRINTF("</column>"
	       "<column name=\"core\">%u</column>"
	       "</item>",
	       ATOMIC_READ(thread->t_cpu)->c_id);
	return result;
err:
	return temp;
}


/* `qXfer:osdata:read:processes': Print the list of processes running on the system. */
PRIVATE NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintOSThreadList)(pformatprinter printer, void *arg) {
	struct GDBInfo_PrintThreadList_Data data;
	ssize_t temp, result = 0;
	PRINT("<osdata type=\"threads\">");
	data.ptld_printer = printer;
	data.ptld_arg     = arg;
	DO(GDBThread_Enumerate(&GDBInfo_PrintOSThreadList_Callback, &data));
	/* Unlike everywhere else, also include the GDB fallback host thread in here! */
	DO(GDBInfo_PrintOSThreadList_Callback(&data, GDBServer_FallbackHost));
	PRINT("</osdata>");
	return result;
err:
	return temp;
}

PRIVATE NONNULL((1, 2)) ssize_t KCALL
GDB_UserLibraryListPrinter(void *closure,
                           struct vm *__restrict effective_vm,
                           USER CHECKED char const *filename,
                           USER UNCHECKED void *loadaddr,
                           USER UNCHECKED void *loadstart,
                           bool UNUSED(filename_may_be_relative)) {
	ssize_t temp, result = 0;
	pformatprinter printer; void *arg;
	printer = ((GDB_LibraryListPrinterData *)closure)->ll_printer;
	arg     = ((GDB_LibraryListPrinterData *)closure)->ll_arg;
	PRINTF("<item>"
	       "<column name=\"loadaddr\">%p</column>"
	       "<column name=\"loadstart\">%p</column>"
	       "<column name=\"name\">",
	       loadaddr, loadstart);
	TRY {
		DO(GDB_PrintRemoteVMString(printer, arg, effective_vm, filename, true));
	} EXCEPT {
	}
	PRINT("</column>"
	      "</item>");
	return result;
err:
	return temp;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintUserLibraryListWithVM)(pformatprinter printer, void *arg,
                                                  struct vm *__restrict effective_vm) {
	ssize_t temp, result = 0;
	GDB_LibraryListPrinterData data;
	data.ll_printer = printer;
	data.ll_arg     = arg;
	PRINT("<osdata type=\"libraries\">");
	/* Print user-space library listings. */
	if (effective_vm != &vm_kernel) {
		TRY {
			DO(vm_library_enumerate(effective_vm, &GDB_UserLibraryListPrinter, &data));
		} EXCEPT {
		}
	}
	PRINT("</osdata>");
	return result;
err:
	return temp;
}

PRIVATE NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDBInfo_PrintUserLibraryList)(pformatprinter printer, void *arg,
                                            struct task *__restrict thread) {
	ssize_t result;
	REF struct vm *v = task_getvm(thread);
	result = GDBInfo_PrintUserLibraryListWithVM(printer, arg, v);
	decref_unlikely(v);
	return result;
}

PRIVATE NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDBInfo_PrintRegisters)(pformatprinter printer, void *arg,
                                      struct task *__restrict thread) {
	ssize_t temp, result = 0;
	uintptr_t regno;
	PRINT("<osdata type=\"regs\">");
	for (regno = 0; regno < GDB_REGISTER_COUNT; ++regno) {
		byte_t buf[GDB_REGISTER_MAXSIZE];
		size_t i, size;
		size = GDB_GetRegister(thread, regno, buf, sizeof(buf));
		if (!size || size > sizeof(buf))
			continue;
		/* Skip empty registers. */
		if ((buf[0] == 0 || buf[0] == 0xff) && size > 1) {
			for (i = 1; i < size; ++i) {
				if (buf[i] != buf[0])
					goto do_printer_register;
			}
			goto skip_register;
		}
do_printer_register:
		PRINT("<item><column name=\"name\">");
		DO(GDB_PrintRegisterName(regno, printer, arg));
		PRINT("</column><column name=\"value\">");
		if (size == 1) {
			PRINTF("%#" PRIx8, *(u8 *)buf);
		} else if (size == 2) {
			PRINTF("%#" PRIx16, UNALIGNED_GET16((u16 *)buf));
		} else if (size == 4) {
			PRINTF("%#" PRIx32, UNALIGNED_GET32((u32 *)buf));
		} else if (size == 8) {
			PRINTF("%#" PRIx64, UNALIGNED_GET64((u64 *)buf));
		} else {
			for (i = 0; i < size; ++i) {
				if (i != 0)
					PRINT(" ");
				PRINTF("%.2" PRIx8, buf[i]);
			}
		}
		PRINT("</column></item>");
skip_register:
		;
	}
	for (regno = 0; GDB_HasOsRegister(thread, regno); ++regno) {
		PRINT("<item><column name=\"name\">");
		DO(GDB_PrintOsRegisterName(thread, regno, printer, arg));
		PRINT("</column><column name=\"value\">");
		DO(GDB_PrintOsRegisterValue(thread, regno, printer, arg));
		PRINT("</column></item>");
	}
	for (regno = 0; GDB_HasArchRegister(thread, regno); ++regno) {
		PRINT("<item><column name=\"name\">");
		DO(GDB_PrintArchRegisterName(thread, regno, printer, arg));
		PRINT("</column><column name=\"value\">");
		DO(GDB_PrintArchRegisterValue(thread, regno, printer, arg));
		PRINT("</column></item>");
	}
	PRINT("</osdata>");
	return result;
err:
	return temp;
}


PRIVATE char const GDBInfo_OsDataOverview[] =
"<osdata type=\"types\">"
	"<item>"
		"<column name=\"Type\">processes</column>"
		"<column name=\"Description\">Processes</column>"
		"<column name=\"Title\">Listing of all processes</column>"
	"</item>"
	"<item>"
		"<column name=\"Type\">files</column>"
		"<column name=\"Description\">File descriptors</column>"
		"<column name=\"Title\">Listing of all file descriptors</column>"
	"</item>"
	"<item>"
		"<column name=\"Type\">drivers</column>"
		"<column name=\"Description\">Kernel drivers</column>"
		"<column name=\"Title\">Listing of all kernel drivers</column>"
	"</item>"
	"<item>"
		"<column name=\"Type\">uname</column>"
		"<column name=\"Description\">Kernel information</column>"
		"<column name=\"Title\">Information returned by uname()</column>"
	"</item>"
	"<item>"
		"<column name=\"Type\">threads</column>"
		"<column name=\"Description\">Threads</column>"
		"<column name=\"Title\">Listing of all threads</column>"
	"</item>"
	"<item>"
		"<column name=\"Type\">libraries</column>"
		"<column name=\"Description\">Libraries</column>"
		"<column name=\"Title\">List information about user-space libraries</column>"
	"</item>"
	"<item>"
		"<column name=\"Type\">regs</column>"
		"<column name=\"Description\">Registers</column>"
		"<column name=\"Title\">Enumerate _all_ registers</column>"
	"</item>"
"</osdata>";


/* `qXfer:osdata:read:<name>': Print os-specific data.
 * @return: -ENOENT: Invalid `name' */
INTERN NONNULL((1, 3, 4)) ssize_t
NOTHROW(FCALL GDBInfo_PrintOSData)(pformatprinter printer, void *arg,
                                   char const *__restrict name,
                                   struct task *__restrict thread) {
	ssize_t result;
	if (!*name) {
		result = (*printer)(arg,
		                    GDBInfo_OsDataOverview,
		                    COMPILER_STRLEN(GDBInfo_OsDataOverview));
	} else if (strcmp(name, "processes") == 0) {
		result = GDBInfo_PrintProcessList(printer, arg);
	} else if (strcmp(name, "drivers") == 0) {
		result = GDBInfo_PrintDriverList(printer, arg);
	} else if (strcmp(name, "files") == 0) {
		result = GDBInfo_PrintFdList(printer, arg);
	} else if (strcmp(name, "uname") == 0) {
		result = GDBInfo_PrintUname(printer, arg);
	} else if (strcmp(name, "threads") == 0) {
		result = GDBInfo_PrintOSThreadList(printer, arg);
	} else if (strcmp(name, "libraries") == 0) {
		result = GDBInfo_PrintUserLibraryList(printer, arg, thread);
	} else if (strcmp(name, "regs") == 0) {
		result = GDBInfo_PrintRegisters(printer, arg, thread);
	} else {
		result = -ENOENT;
	}
	return result;
}



#define GDB_FEATURES_DOCTYPE_FEATURE_SYSTEM_GDB_TARGET_DTD \
	"<!DOCTYPE feature SYSTEM \"gdb-target.dtd\">"

#ifdef __x86_64__
#define HAVE_GDBFeatures_target_xml 1
#define HAVE_GDBFeatures_64bit_sse_xml 1
#define HAVE_GDBFeatures_64bit_core_xml 1
#define HAVE_GDBFeatures_64bit_segments_xml 1
#define PRIVATE_GDB_TARGETX86_64_SUBFILE_PREFIX_LEN \
	COMPILER_STRLEN(XML_VERSION_HEADER GDB_FEATURES_DOCTYPE_FEATURE_SYSTEM_GDB_TARGET_DTD)
#define PRINT_GDBFeatures_target_xml()                                                                    \
	PRINT(GDBFeatures_target_xml1);                                                                       \
	print(GDBFeatures_64bit_core_xml + PRIVATE_GDB_TARGETX86_64_SUBFILE_PREFIX_LEN,                       \
	      COMPILER_STRLEN(GDBFeatures_64bit_core_xml) - PRIVATE_GDB_TARGETX86_64_SUBFILE_PREFIX_LEN);     \
	print(GDBFeatures_64bit_sse_xml + PRIVATE_GDB_TARGETX86_64_SUBFILE_PREFIX_LEN,                        \
	      COMPILER_STRLEN(GDBFeatures_64bit_sse_xml) - PRIVATE_GDB_TARGETX86_64_SUBFILE_PREFIX_LEN);      \
	print(GDBFeatures_64bit_segments_xml + PRIVATE_GDB_TARGETX86_64_SUBFILE_PREFIX_LEN,                   \
	      COMPILER_STRLEN(GDBFeatures_64bit_segments_xml) - PRIVATE_GDB_TARGETX86_64_SUBFILE_PREFIX_LEN); \
	PRINT(GDBFeatures_target_xml2);
PRIVATE char const GDBFeatures_target_xml1[] =
XML_VERSION_HEADER
"<!DOCTYPE target SYSTEM \"gdb-target.dtd\">"
"<target>"
	"<architecture>i386:x86-64</architecture>"
//	"<osabi>KOS</osabi>"
;
PRIVATE char const GDBFeatures_target_xml2[] =
"</target>";
#elif defined(__i386__)
#define HAVE_GDBFeatures_target_xml 1
#define HAVE_GDBFeatures_32bit_sse_xml 1
#define HAVE_GDBFeatures_32bit_core_xml 1
#define PRIVATE_GDB_TARGET386_SUBFILE_PREFIX_LEN \
	COMPILER_STRLEN(XML_VERSION_HEADER GDB_FEATURES_DOCTYPE_FEATURE_SYSTEM_GDB_TARGET_DTD)
#define PRINT_GDBFeatures_target_xml()                                                             \
	PRINT(GDBFeatures_target_xml1);                                                                \
	print(GDBFeatures_32bit_core_xml + PRIVATE_GDB_TARGET386_SUBFILE_PREFIX_LEN,                   \
	      COMPILER_STRLEN(GDBFeatures_32bit_core_xml) - PRIVATE_GDB_TARGET386_SUBFILE_PREFIX_LEN); \
	print(GDBFeatures_32bit_sse_xml + PRIVATE_GDB_TARGET386_SUBFILE_PREFIX_LEN,                    \
	      COMPILER_STRLEN(GDBFeatures_32bit_sse_xml) - PRIVATE_GDB_TARGET386_SUBFILE_PREFIX_LEN);  \
	PRINT(GDBFeatures_target_xml2);
PRIVATE char const GDBFeatures_target_xml1[] =
XML_VERSION_HEADER
"<!DOCTYPE target SYSTEM \"gdb-target.dtd\">"
"<target>"
	"<architecture>i386</architecture>"
//	"<osabi>KOS</osabi>"
;
STATIC_ASSERT(GDB_REGISTER_I386_FSBASE == 48);
STATIC_ASSERT(GDB_REGISTER_I386_GSBASE == 49);
PRIVATE char const GDBFeatures_target_xml2[] =
	"<feature name=\"de.kos.gdb.i386.sgbase\">"
		"<reg name=\"fs_base\" bitsize=\"32\" type=\"data_ptr\" regnum=\"48\"/>" /* GDB_REGISTER_I386_FSBASE */
		"<reg name=\"gs_base\" bitsize=\"32\" type=\"data_ptr\" regnum=\"49\"/>" /* GDB_REGISTER_I386_GSBASE */
	"</feature>"
"</target>";
#endif /* !__x86_64__ */


/* "<xi:include href=\"32bit-core.xml\"/>" */
#ifdef HAVE_GDBFeatures_32bit_core_xml
#define HAVE_GDB_XML 1
PRIVATE char const GDBFeatures_32bit_core_xml[] =
XML_VERSION_HEADER
//"<!-- Copyright (C) 2010-2019 Free Software Foundation, Inc.\n"
//"\n"
//"     Copying and distribution of this file, with or without modification,\n"
//"     are permitted in any medium without royalty provided the copyright\n"
//"     notice and this notice are preserved.  -->\n"
GDB_FEATURES_DOCTYPE_FEATURE_SYSTEM_GDB_TARGET_DTD
"<feature name=\"org.gnu.gdb.i386.core\">"
	"<flags id=\"i386_eflags\" size=\"4\">"
		"<field name=\"CF\" start=\"0\" end=\"0\"/>"
		"<field name=\"\" start=\"1\" end=\"1\"/>"
		"<field name=\"PF\" start=\"2\" end=\"2\"/>"
		"<field name=\"AF\" start=\"4\" end=\"4\"/>"
		"<field name=\"ZF\" start=\"6\" end=\"6\"/>"
		"<field name=\"SF\" start=\"7\" end=\"7\"/>"
		"<field name=\"TF\" start=\"8\" end=\"8\"/>"
		"<field name=\"IF\" start=\"9\" end=\"9\"/>"
		"<field name=\"DF\" start=\"10\" end=\"10\"/>"
		"<field name=\"OF\" start=\"11\" end=\"11\"/>"
		"<field name=\"NT\" start=\"14\" end=\"14\"/>"
		"<field name=\"RF\" start=\"16\" end=\"16\"/>"
		"<field name=\"VM\" start=\"17\" end=\"17\"/>"
		"<field name=\"AC\" start=\"18\" end=\"18\"/>"
		"<field name=\"VIF\" start=\"19\" end=\"19\"/>"
		"<field name=\"VIP\" start=\"20\" end=\"20\"/>"
		"<field name=\"ID\" start=\"21\" end=\"21\"/>"
	"</flags>"
	"<reg name=\"eax\" bitsize=\"32\" type=\"int32\"/>"
	"<reg name=\"ecx\" bitsize=\"32\" type=\"int32\"/>"
	"<reg name=\"edx\" bitsize=\"32\" type=\"int32\"/>"
	"<reg name=\"ebx\" bitsize=\"32\" type=\"int32\"/>"
	"<reg name=\"esp\" bitsize=\"32\" type=\"data_ptr\"/>"
	"<reg name=\"ebp\" bitsize=\"32\" type=\"data_ptr\"/>"
	"<reg name=\"esi\" bitsize=\"32\" type=\"int32\"/>"
	"<reg name=\"edi\" bitsize=\"32\" type=\"int32\"/>"
	"<reg name=\"eip\" bitsize=\"32\" type=\"code_ptr\"/>"
	"<reg name=\"eflags\" bitsize=\"32\" type=\"i386_eflags\"/>"
	"<reg name=\"cs\" bitsize=\"32\" type=\"int32\"/>"
	"<reg name=\"ss\" bitsize=\"32\" type=\"int32\"/>"
	"<reg name=\"ds\" bitsize=\"32\" type=\"int32\"/>"
	"<reg name=\"es\" bitsize=\"32\" type=\"int32\"/>"
	"<reg name=\"fs\" bitsize=\"32\" type=\"int32\"/>"
	"<reg name=\"gs\" bitsize=\"32\" type=\"int32\"/>"
	"<reg name=\"st0\" bitsize=\"80\" type=\"i387_ext\"/>"
	"<reg name=\"st1\" bitsize=\"80\" type=\"i387_ext\"/>"
	"<reg name=\"st2\" bitsize=\"80\" type=\"i387_ext\"/>"
	"<reg name=\"st3\" bitsize=\"80\" type=\"i387_ext\"/>"
	"<reg name=\"st4\" bitsize=\"80\" type=\"i387_ext\"/>"
	"<reg name=\"st5\" bitsize=\"80\" type=\"i387_ext\"/>"
	"<reg name=\"st6\" bitsize=\"80\" type=\"i387_ext\"/>"
	"<reg name=\"st7\" bitsize=\"80\" type=\"i387_ext\"/>"
	"<reg name=\"fctrl\" bitsize=\"32\" type=\"int\" group=\"float\"/>"
	"<reg name=\"fstat\" bitsize=\"32\" type=\"int\" group=\"float\"/>"
	"<reg name=\"ftag\" bitsize=\"32\" type=\"int\" group=\"float\"/>"
	"<reg name=\"fiseg\" bitsize=\"32\" type=\"int\" group=\"float\"/>"
	"<reg name=\"fioff\" bitsize=\"32\" type=\"int\" group=\"float\"/>"
	"<reg name=\"foseg\" bitsize=\"32\" type=\"int\" group=\"float\"/>"
	"<reg name=\"fooff\" bitsize=\"32\" type=\"int\" group=\"float\"/>"
	"<reg name=\"fop\" bitsize=\"32\" type=\"int\" group=\"float\"/>"
"</feature>";
#endif /* HAVE_GDBFeatures_32bit_core_xml */

/* "<xi:include href=\"32bit-sse.xml\"/>" */
#ifdef HAVE_GDBFeatures_32bit_sse_xml
#define HAVE_GDB_XML 1
PRIVATE char const GDBFeatures_32bit_sse_xml[] =
XML_VERSION_HEADER
//"<!-- Copyright (C) 2010-2019 Free Software Foundation, Inc.\n"
//"\n"
//"     Copying and distribution of this file, with or without modification,\n"
//"     are permitted in any medium without royalty provided the copyright\n"
//"     notice and this notice are preserved.  -->"
GDB_FEATURES_DOCTYPE_FEATURE_SYSTEM_GDB_TARGET_DTD
"<feature name=\"org.gnu.gdb.i386.sse\">"
	"<vector id=\"v4f\" type=\"ieee_single\" count=\"4\"/>"
	"<vector id=\"v2d\" type=\"ieee_double\" count=\"2\"/>"
	"<vector id=\"v16i8\" type=\"int8\" count=\"16\"/>"
	"<vector id=\"v8i16\" type=\"int16\" count=\"8\"/>"
	"<vector id=\"v4i32\" type=\"int32\" count=\"4\"/>"
	"<vector id=\"v2i64\" type=\"int64\" count=\"2\"/>"
	"<union id=\"vec128\">"
		"<field name=\"v4_float\" type=\"v4f\"/>"
		"<field name=\"v2_double\" type=\"v2d\"/>"
		"<field name=\"v16_int8\" type=\"v16i8\"/>"
		"<field name=\"v8_int16\" type=\"v8i16\"/>"
		"<field name=\"v4_int32\" type=\"v4i32\"/>"
		"<field name=\"v2_int64\" type=\"v2i64\"/>"
		"<field name=\"uint128\" type=\"uint128\"/>"
	"</union>"
	"<flags id=\"i386_mxcsr\" size=\"4\">"
		"<field name=\"IE\" start=\"0\" end=\"0\"/>"
		"<field name=\"DE\" start=\"1\" end=\"1\"/>"
		"<field name=\"ZE\" start=\"2\" end=\"2\"/>"
		"<field name=\"OE\" start=\"3\" end=\"3\"/>"
		"<field name=\"UE\" start=\"4\" end=\"4\"/>"
		"<field name=\"PE\" start=\"5\" end=\"5\"/>"
		"<field name=\"DAZ\" start=\"6\" end=\"6\"/>"
		"<field name=\"IM\" start=\"7\" end=\"7\"/>"
		"<field name=\"DM\" start=\"8\" end=\"8\"/>"
		"<field name=\"ZM\" start=\"9\" end=\"9\"/>"
		"<field name=\"OM\" start=\"10\" end=\"10\"/>"
		"<field name=\"UM\" start=\"11\" end=\"11\"/>"
		"<field name=\"PM\" start=\"12\" end=\"12\"/>"
		"<field name=\"FZ\" start=\"15\" end=\"15\"/>"
	"</flags>"
	"<reg name=\"xmm0\" bitsize=\"128\" type=\"vec128\" regnum=\"32\"/>"
	"<reg name=\"xmm1\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm2\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm3\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm4\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm5\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm6\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm7\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"mxcsr\" bitsize=\"32\" type=\"i386_mxcsr\" group=\"vector\"/>"
"</feature>";
#endif /* HAVE_GDBFeatures_32bit_sse_xml */


/* "<xi:include href=\"64bit-core.xml\"/>" */
#ifdef HAVE_GDBFeatures_64bit_core_xml
#define HAVE_GDB_XML 1
PRIVATE char const GDBFeatures_64bit_core_xml[] =
XML_VERSION_HEADER
//"<!-- Copyright (C) 2010-2019 Free Software Foundation, Inc.\n"
//"\n"
//"     Copying and distribution of this file, with or without modification,\n"
//"     are permitted in any medium without royalty provided the copyright\n"
//"     notice and this notice are preserved.  -->\n"
GDB_FEATURES_DOCTYPE_FEATURE_SYSTEM_GDB_TARGET_DTD
"<feature name=\"org.gnu.gdb.i386.core\">"
	"<flags id=\"i386_eflags\" size=\"4\">"
		"<field name=\"CF\" start=\"0\" end=\"0\"/>"
		"<field name=\"\" start=\"1\" end=\"1\"/>"
		"<field name=\"PF\" start=\"2\" end=\"2\"/>"
		"<field name=\"AF\" start=\"4\" end=\"4\"/>"
		"<field name=\"ZF\" start=\"6\" end=\"6\"/>"
		"<field name=\"SF\" start=\"7\" end=\"7\"/>"
		"<field name=\"TF\" start=\"8\" end=\"8\"/>"
		"<field name=\"IF\" start=\"9\" end=\"9\"/>"
		"<field name=\"DF\" start=\"10\" end=\"10\"/>"
		"<field name=\"OF\" start=\"11\" end=\"11\"/>"
		"<field name=\"NT\" start=\"14\" end=\"14\"/>"
		"<field name=\"RF\" start=\"16\" end=\"16\"/>"
		"<field name=\"VM\" start=\"17\" end=\"17\"/>"
		"<field name=\"AC\" start=\"18\" end=\"18\"/>"
		"<field name=\"VIF\" start=\"19\" end=\"19\"/>"
		"<field name=\"VIP\" start=\"20\" end=\"20\"/>"
		"<field name=\"ID\" start=\"21\" end=\"21\"/>"
	"</flags>"
	"<reg name=\"rax\" bitsize=\"64\" type=\"int64\"/>"
	"<reg name=\"rbx\" bitsize=\"64\" type=\"int64\"/>"
	"<reg name=\"rcx\" bitsize=\"64\" type=\"int64\"/>"
	"<reg name=\"rdx\" bitsize=\"64\" type=\"int64\"/>"
	"<reg name=\"rsi\" bitsize=\"64\" type=\"int64\"/>"
	"<reg name=\"rdi\" bitsize=\"64\" type=\"int64\"/>"
	"<reg name=\"rbp\" bitsize=\"64\" type=\"data_ptr\"/>"
	"<reg name=\"rsp\" bitsize=\"64\" type=\"data_ptr\"/>"
	"<reg name=\"r8\" bitsize=\"64\" type=\"int64\"/>"
	"<reg name=\"r9\" bitsize=\"64\" type=\"int64\"/>"
	"<reg name=\"r10\" bitsize=\"64\" type=\"int64\"/>"
	"<reg name=\"r11\" bitsize=\"64\" type=\"int64\"/>"
	"<reg name=\"r12\" bitsize=\"64\" type=\"int64\"/>"
	"<reg name=\"r13\" bitsize=\"64\" type=\"int64\"/>"
	"<reg name=\"r14\" bitsize=\"64\" type=\"int64\"/>"
	"<reg name=\"r15\" bitsize=\"64\" type=\"int64\"/>"
	"<reg name=\"rip\" bitsize=\"64\" type=\"code_ptr\"/>"
	"<reg name=\"eflags\" bitsize=\"32\" type=\"i386_eflags\"/>"
	"<reg name=\"cs\" bitsize=\"32\" type=\"int32\"/>"
	"<reg name=\"ss\" bitsize=\"32\" type=\"int32\"/>"
	"<reg name=\"ds\" bitsize=\"32\" type=\"int32\"/>"
	"<reg name=\"es\" bitsize=\"32\" type=\"int32\"/>"
	"<reg name=\"fs\" bitsize=\"32\" type=\"int32\"/>"
	"<reg name=\"gs\" bitsize=\"32\" type=\"int32\"/>"
	"<reg name=\"st0\" bitsize=\"80\" type=\"i387_ext\"/>"
	"<reg name=\"st1\" bitsize=\"80\" type=\"i387_ext\"/>"
	"<reg name=\"st2\" bitsize=\"80\" type=\"i387_ext\"/>"
	"<reg name=\"st3\" bitsize=\"80\" type=\"i387_ext\"/>"
	"<reg name=\"st4\" bitsize=\"80\" type=\"i387_ext\"/>"
	"<reg name=\"st5\" bitsize=\"80\" type=\"i387_ext\"/>"
	"<reg name=\"st6\" bitsize=\"80\" type=\"i387_ext\"/>"
	"<reg name=\"st7\" bitsize=\"80\" type=\"i387_ext\"/>"
	"<reg name=\"fctrl\" bitsize=\"32\" type=\"int\" group=\"float\"/>"
	"<reg name=\"fstat\" bitsize=\"32\" type=\"int\" group=\"float\"/>"
	"<reg name=\"ftag\" bitsize=\"32\" type=\"int\" group=\"float\"/>"
	"<reg name=\"fiseg\" bitsize=\"32\" type=\"int\" group=\"float\"/>"
	"<reg name=\"fioff\" bitsize=\"32\" type=\"int\" group=\"float\"/>"
	"<reg name=\"foseg\" bitsize=\"32\" type=\"int\" group=\"float\"/>"
	"<reg name=\"fooff\" bitsize=\"32\" type=\"int\" group=\"float\"/>"
	"<reg name=\"fop\" bitsize=\"32\" type=\"int\" group=\"float\"/>"
"</feature>";
#endif /* HAVE_GDBFeatures_64bit_core_xml */


/* "<xi:include href=\"64bit-sse.xml\"/>" */
#ifdef HAVE_GDBFeatures_64bit_sse_xml
#define HAVE_GDB_XML 1
PRIVATE char const GDBFeatures_64bit_sse_xml[] =
XML_VERSION_HEADER
//"<!-- Copyright (C) 2010-2019 Free Software Foundation, Inc.\n"
//"\n"
//"     Copying and distribution of this file, with or without modification,\n"
//"     are permitted in any medium without royalty provided the copyright\n"
//"     notice and this notice are preserved.  -->"
GDB_FEATURES_DOCTYPE_FEATURE_SYSTEM_GDB_TARGET_DTD
"<feature name=\"org.gnu.gdb.i386.sse\">"
	"<vector id=\"v4f\" type=\"ieee_single\" count=\"4\"/>"
	"<vector id=\"v2d\" type=\"ieee_double\" count=\"2\"/>"
	"<vector id=\"v16i8\" type=\"int8\" count=\"16\"/>"
	"<vector id=\"v8i16\" type=\"int16\" count=\"8\"/>"
	"<vector id=\"v4i32\" type=\"int32\" count=\"4\"/>"
	"<vector id=\"v2i64\" type=\"int64\" count=\"2\"/>"
	"<union id=\"vec128\">"
		"<field name=\"v4_float\" type=\"v4f\"/>"
		"<field name=\"v2_double\" type=\"v2d\"/>"
		"<field name=\"v16_int8\" type=\"v16i8\"/>"
		"<field name=\"v8_int16\" type=\"v8i16\"/>"
		"<field name=\"v4_int32\" type=\"v4i32\"/>"
		"<field name=\"v2_int64\" type=\"v2i64\"/>"
		"<field name=\"uint128\" type=\"uint128\"/>"
	"</union>"
	"<flags id=\"i386_mxcsr\" size=\"4\">"
		"<field name=\"IE\" start=\"0\" end=\"0\"/>"
		"<field name=\"DE\" start=\"1\" end=\"1\"/>"
		"<field name=\"ZE\" start=\"2\" end=\"2\"/>"
		"<field name=\"OE\" start=\"3\" end=\"3\"/>"
		"<field name=\"UE\" start=\"4\" end=\"4\"/>"
		"<field name=\"PE\" start=\"5\" end=\"5\"/>"
		"<field name=\"DAZ\" start=\"6\" end=\"6\"/>"
		"<field name=\"IM\" start=\"7\" end=\"7\"/>"
		"<field name=\"DM\" start=\"8\" end=\"8\"/>"
		"<field name=\"ZM\" start=\"9\" end=\"9\"/>"
		"<field name=\"OM\" start=\"10\" end=\"10\"/>"
		"<field name=\"UM\" start=\"11\" end=\"11\"/>"
		"<field name=\"PM\" start=\"12\" end=\"12\"/>"
		"<field name=\"FZ\" start=\"15\" end=\"15\"/>"
	"</flags>"
	"<reg name=\"xmm0\" bitsize=\"128\" type=\"vec128\" regnum=\"40\"/>"
	"<reg name=\"xmm1\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm2\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm3\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm4\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm5\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm6\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm7\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm8\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm9\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm10\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm11\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm12\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm13\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm14\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"xmm15\" bitsize=\"128\" type=\"vec128\"/>"
	"<reg name=\"mxcsr\" bitsize=\"32\" type=\"i386_mxcsr\" group=\"vector\"/>"
"</feature>";
#endif /* HAVE_GDBFeatures_64bit_sse_xml */


/* "<xi:include href=\"64bit-segments.xml\"/>" */
#ifdef HAVE_GDBFeatures_64bit_segments_xml
#define HAVE_GDB_XML 1
PRIVATE char const GDBFeatures_64bit_segments_xml[] =
XML_VERSION_HEADER
//"<!-- Copyright (C) 2010-2019 Free Software Foundation, Inc.\n"
//"\n"
//"     Copying and distribution of this file, with or without modification,\n"
//"     are permitted in any medium without royalty provided the copyright\n"
//"     notice and this notice are preserved.  -->"
GDB_FEATURES_DOCTYPE_FEATURE_SYSTEM_GDB_TARGET_DTD
"<feature name=\"org.gnu.gdb.i386.segments\">"
	"<reg name=\"fs_base\" bitsize=\"64\" type=\"int\"/>"
	"<reg name=\"gs_base\" bitsize=\"64\" type=\"int\"/>"
"</feature>";
#endif /* HAVE_GDBFeatures_64bit_segments_xml */



#ifdef HAVE_GDBFeatures_target_xml
#define HAVE_GDB_XML 1
#endif /* HAVE_GDBFeatures_target_xml */


/* `qXfer:features:read': Print the named features file `filename' */
INTERN NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDBInfo_PrintFeaturesFile)(pformatprinter printer, void *arg,
                                         char const *__restrict filename) {
#ifdef HAVE_GDB_XML
	ssize_t temp, result = 0;
	while (*filename == '/')
		++filename;
#ifdef HAVE_GDBFeatures_target_xml
	if (strcmp(filename, "target.xml") == 0) {
#ifdef PRINT_GDBFeatures_target_xml
		PRINT_GDBFeatures_target_xml();
#else /* PRINT_GDBFeatures_target_xml */
		PRINT(GDBFeatures_target_xml);
#endif /* !PRINT_GDBFeatures_target_xml */
	} else
#endif /* HAVE_GDBFeatures_target_xml */
#ifdef HAVE_GDBFeatures_32bit_sse_xml
	if (strcmp(filename, "32bit-sse.xml") == 0) {
		PRINT(GDBFeatures_32bit_sse_xml);
	} else
#endif /* HAVE_GDBFeatures_32bit_sse_xml */
#ifdef HAVE_GDBFeatures_32bit_core_xml
	if (strcmp(filename, "32bit-core.xml") == 0) {
		PRINT(GDBFeatures_32bit_core_xml);
	} else
#endif /* HAVE_GDBFeatures_32bit_core_xml */
#ifdef HAVE_GDBFeatures_64bit_sse_xml
	if (strcmp(filename, "64bit-sse.xml") == 0) {
		PRINT(GDBFeatures_64bit_sse_xml);
	} else
#endif /* HAVE_GDBFeatures_64bit_sse_xml */
#ifdef HAVE_GDBFeatures_64bit_core_xml
	if (strcmp(filename, "64bit-core.xml") == 0) {
		PRINT(GDBFeatures_64bit_core_xml);
	} else
#endif /* HAVE_GDBFeatures_64bit_core_xml */
#ifdef HAVE_GDBFeatures_64bit_segments_xml
	if (strcmp(filename, "64bit-segments.xml") == 0) {
		PRINT(GDBFeatures_64bit_segments_xml);
	} else
#endif /* HAVE_GDBFeatures_64bit_segments_xml */
	{
		result = -ENOENT;
	}
	return result;
err:
	return temp;
#else /* HAVE_GDB_XML */
	(void)printer;
	(void)arg;
	(void)filename;
	COMPILER_IMPURE();
	return -ENOENT;
#endif /* !HAVE_GDB_XML */
}


DECL_END

#endif /* !GUARD_MODGDBSERVER_GDB_INFO_C */
