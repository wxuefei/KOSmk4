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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_SYSLOG_H
#define GUARD_KERNEL_INCLUDE_KERNEL_SYSLOG_H 1

#include <kernel/compiler.h>

#include <kernel/printk.h>
#include <kernel/types.h>

DECL_BEGIN

#ifndef CONFIG_SYSLOG_LINEMAX
#define CONFIG_SYSLOG_LINEMAX 498 /* Max length of a single syslog line */
#endif /* !CONFIG_SYSLOG_LINEMAX */

#define SYSLOG_LEVEL_EMERG   __CCAST(void *)0
#define SYSLOG_LEVEL_ALERT   __CCAST(void *)1
#define SYSLOG_LEVEL_CRIT    __CCAST(void *)2
#define SYSLOG_LEVEL_ERR     __CCAST(void *)3
#define SYSLOG_LEVEL_WARNING __CCAST(void *)4
#define SYSLOG_LEVEL_NOTICE  __CCAST(void *)5
#define SYSLOG_LEVEL_INFO    __CCAST(void *)6
#define SYSLOG_LEVEL_TRACE   __CCAST(void *)7
#define SYSLOG_LEVEL_DEBUG   __CCAST(void *)8
#define SYSLOG_LEVEL_DEFAULT __CCAST(void *)9
#define SYSLOG_LEVEL_RAW     __CCAST(void *)10
#define SYSLOG_LEVEL_COUNT   11

#define SYSLOG_SINK_DEFAULT_LEVELS __CCAST(uintptr_t)(-1)

#define OFFSET_SYSLOG_PACKET_TIME  0
#define OFFSET_SYSLOG_PACKET_NSEC  8
#define OFFSET_SYSLOG_PACKET_LEN   12
#define OFFSET_SYSLOG_PACKET_MSG   14
#ifdef __CC__

struct syslog_packet {
	time_t sp_time;                        /* Seconds since 01.01.1970T00:00:00 */
	u32    sp_nsec;                        /* Nano seconds added to `sp_time' (< 1_000_000_000). */
	u16    sp_len;                         /* Syslog message length (including the trailing '\n'-character). */
#ifdef SYSLOG_LINEMAX
	char   sp_msg[SYSLOG_LINEMAX];         /* Syslog message. */
#else /* SYSLOG_LINEMAX */
	COMPILER_FLEXIBLE_ARRAY(char, sp_msg); /* Syslog message (terminated by '\n'). */
#endif /* !SYSLOG_LINEMAX */
};

struct syslog_sink {
	WEAK refcnt_t  ss_refcnt; /* Reference counter. */
	WEAK uintptr_t ss_levels; /* Mask of log levels accepted by this sink (`ss_levels & (1 << SYSLOG_LEVEL_*)'). */
	/* [1..1] Sink packet processing handler.
	 * Called for each registered syslog sink every time that a packet is completed.
	 * WARNING: The implementation of this function must be aware that the contents of
	 *          `packet' may change before this function returns. In this case the
	 *          function's behavior must be weakly undefined, in that it may not cause
	 *          the kernel to crash.
	 *          However, if this happens, it may still be assumed that the `sp_msg'
	 *          buffer has sufficient size for holding `MAX(OLD(sp_len), NEW(sp_len))'
	 *          characters, meaning that sp_msg[0...ANY(sp_len)-1] can always be accessed
	 *          without fear of triggering a SEGFAULT. */
	NOBLOCK void /*NOTHROW*/ (FCALL *ss_sink)(struct syslog_sink *__restrict self,
	                                          struct syslog_packet const *__restrict packet,
	                                          unsigned int level);
	/* [0..1] Optional finalizer callback for when the sink is destroyed. */
	NOBLOCK void /*NOTHROW*/ (FCALL *ss_fini)(struct syslog_sink *__restrict self);
};

/* Same as the `ss_levels' field found in individual syslog sinks,
 * however this one affect system logging on a global level.
 * Be careful when tinkering with this, and don't accidentally
 * disable logging of some of the more important message types! */
DATDEF WEAK uintptr_t syslog_levels;

/* Destroy the given syslog sink */
FUNDEF NOBLOCK void NOTHROW(KCALL syslog_sink_destroy)(struct syslog_sink *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct syslog_sink, ss_refcnt, syslog_sink_destroy)

/* Register/Delete custom system log sinks
 * By default after boot, either 1 or 2 sinks are registered:
 *  - An arch-specific default logging sink
 *  - The kernel's dmesg buffer (usually 16384 (0x4000) bytes large)
 *    that contains a backlog of the last N written packets. */
FUNDEF bool KCALL syslog_sink_register(struct syslog_sink *__restrict self) THROWS(E_WOULDBLOCK, E_BAD_ARGUMENT);
FUNDEF bool KCALL syslog_sink_unregister(struct syslog_sink *__restrict self) THROWS(E_WOULDBLOCK, E_BAD_ARGUMENT);

/* Broadcast a given system log packet for all registered sinks to handle
 * Note that this function can be called from any context! */
FUNDEF NOBLOCK void
NOTHROW(FCALL syslog_packet_broadcast)(struct syslog_packet const *__restrict self,
                                       unsigned int level);

/* pformatprinter-compatible syslog printer, where `level' is `(void *)SYSLOG_LEVEL_*'
 * Writing text using this function will append to an internal buffer for the
 * given `level'. If this buffer overflows, it will be broadcast and reset the same
 * way it would be when being committed (using `\n'). The size of said buffer is an
 * implementation detail and should be sufficiently large such that users of this
 * function need not worry about its actual value.
 * Additionally the following control characters are recognized:
 *   - `\r': Clear the internal buffer for `level' (if not immediately followed by `\n')
 *   - `\n': Broadcast the contents of the internal buffer as a syslog
 *           packet (s.a. `syslog_packet_broadcast()') and clear the buffer.
 * @except: May only throw exceptions as the result of accessing memory in `*data'
 * @return: * : Always re-returns `datalen' */
FUNDEF ssize_t KCALL
syslog_printer(void *level,
               USER CHECKED char const *data,
               size_t datalen)
		THROWS(E_SEGFAULT);


#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_SYSLOG_H */