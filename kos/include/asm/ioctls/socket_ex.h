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
#ifndef _ASM_IOCTLS_SOCKET_EX_H
#define _ASM_IOCTLS_SOCKET_EX_H 1

/* DISCLAIMER: _STRONGLY_ Based on '/usr/include/i386-linux-gnu/bits/ioctls.h' */

#include <__stdinc.h>

#include <asm/ioctl.h>
#include <asm/ioctls/socket.h> /* Basic socket ioctls */
#include <asm/ioctls/tty.h>    /* FIONREAD, TIOCOUTQ */

/* Copyright (C) 1996-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifdef FIONREAD
#define SIOCINQ  FIONREAD
#endif /* FIONREAD */
#ifdef TIOCOUTQ
#define SIOCOUTQ TIOCOUTQ /* output queue size (not sent + not acked) */
#endif /* TIOCOUTQ */

#if defined(__KOS__) || defined(__linux__)
/*      FIOSETOWN          _IO(0x89, 0x01)  * ... */
/*      SIOCSPGRP          _IO(0x89, 0x02)  * ... */
/*      FIOGETOWN          _IO(0x89, 0x03)  * ... */
/*      SIOCGPGRP          _IO(0x89, 0x04)  * ... */
/*      SIOCATMARK         _IO(0x89, 0x05)  * ... */
/*      SIOCGSTAMP         _IO(0x89, 0x06)  * [struct timeval *arg] Get stamp */
/*      SIOCGSTAMPNS       _IO(0x89, 0x07)  * [struct timespec *arg] Get stamp */

/* Routing table calls. */
#define SIOCADDRT          _IO(0x89, 0x0b) /* add routing table entry. */
#define SIOCDELRT          _IO(0x89, 0x0c) /* delete routing table entry. */
#define SIOCRTMSG          _IO(0x89, 0x0d) /* call to routing system. */

/* Socket configuration controls. */
#define SIOCGIFNAME        _IO(0x89, 0x10) /* get iface name. */
#define SIOCSIFLINK        _IO(0x89, 0x11) /* set iface channel. */
#define SIOCGIFCONF        _IO(0x89, 0x12) /* get iface list. */
#define SIOCGIFFLAGS       _IO(0x89, 0x13) /* get flags. */
#define SIOCSIFFLAGS       _IO(0x89, 0x14) /* set flags. */
#define SIOCGIFADDR        _IO(0x89, 0x15) /* get PA address. */
#define SIOCSIFADDR        _IO(0x89, 0x16) /* set PA address. */
#define SIOCGIFDSTADDR     _IO(0x89, 0x17) /* get remote PA address. */
#define SIOCSIFDSTADDR     _IO(0x89, 0x18) /* set remote PA address. */
#define SIOCGIFBRDADDR     _IO(0x89, 0x19) /* get broadcast PA address. */
#define SIOCSIFBRDADDR     _IO(0x89, 0x1a) /* set broadcast PA address. */
#define SIOCGIFNETMASK     _IO(0x89, 0x1b) /* get network PA mask. */
#define SIOCSIFNETMASK     _IO(0x89, 0x1c) /* set network PA mask. */
#define SIOCGIFMETRIC      _IO(0x89, 0x1d) /* get metric. */
#define SIOCSIFMETRIC      _IO(0x89, 0x1e) /* set metric. */
#define SIOCGIFMEM         _IO(0x89, 0x1f) /* get memory address (BSD). */
#define SIOCSIFMEM         _IO(0x89, 0x20) /* set memory address (BSD). */
#define SIOCGIFMTU         _IO(0x89, 0x21) /* get MTU size. */
#define SIOCSIFMTU         _IO(0x89, 0x22) /* set MTU size. */
#define SIOCSIFNAME        _IO(0x89, 0x23) /* set interface name. */
#define SIOCSIFHWADDR      _IO(0x89, 0x24) /* set hardware address. */
#define SIOCGIFENCAP       _IO(0x89, 0x25) /* get/set encapsulations. */
#define SIOCSIFENCAP       _IO(0x89, 0x26)
#define SIOCGIFHWADDR      _IO(0x89, 0x27) /* Get hardware address. */
#define SIOCGIFSLAVE       _IO(0x89, 0x29) /* Driver slaving support. */
#define SIOCSIFSLAVE       _IO(0x89, 0x30)
#define SIOCADDMULTI       _IO(0x89, 0x31) /* Multicast address lists. */
#define SIOCDELMULTI       _IO(0x89, 0x32)
#define SIOCGIFINDEX       _IO(0x89, 0x33) /* name -> if_index mapping. */
#define SIOGIFINDEX        SIOCGIFINDEX
#define SIOCSIFPFLAGS      _IO(0x89, 0x34) /* set/get extended flags set. */
#define SIOCGIFPFLAGS      _IO(0x89, 0x35)
#define SIOCDIFADDR        _IO(0x89, 0x36) /* delete PA address. */
#define SIOCSIFHWBROADCAST _IO(0x89, 0x37) /* set hardware broadcast addr. */
#define SIOCGIFCOUNT       _IO(0x89, 0x38) /* get number of devices. */

#define SIOCGIFBR          _IO(0x89, 0x40) /* Bridging support. */
#define SIOCSIFBR          _IO(0x89, 0x41) /* Set bridging options. */

#define SIOCGIFTXQLEN      _IO(0x89, 0x42) /* Get the tx queue length. */
#define SIOCSIFTXQLEN      _IO(0x89, 0x43) /* Set the tx queue length. */
#endif /* __KOS__ || __linux__ */

#ifdef __linux__
/*      SIOCGIFDIVERT      _IO(0x89, 0x44)  * Frame diversion support */
/*      SIOCSIFDIVERT      _IO(0x89, 0x45)  * Set frame diversion options */
#define SIOCETHTOOL        _IO(0x89, 0x46) /* Ethtool interface */
#define SIOCGMIIPHY        _IO(0x89, 0x47) /* Get address of MII PHY in use. */
#define SIOCGMIIREG        _IO(0x89, 0x48) /* Read MII PHY register. */
#define SIOCSMIIREG        _IO(0x89, 0x49) /* Write MII PHY register. */
#define SIOCWANDEV         _IO(0x89, 0x4a) /* get/set netdev parameters */
#define SIOCOUTQNSD        _IO(0x89, 0x4b) /* output queue size (not sent only) */
#endif /* __linux__ */



#if defined(__KOS__) || defined(__linux__)
/* ARP cache control calls. */
/*                         _IO(0x89, 0x50)  * obsolete call, don't re-use. */
/*                         _IO(0x89, 0x51)  * obsolete call, don't re-use. */
/*                         _IO(0x89, 0x52)  * obsolete call, don't re-use. */
#define SIOCDARP           _IO(0x89, 0x53) /* delete ARP table entry. */
#define SIOCGARP           _IO(0x89, 0x54) /* get ARP table entry. */
#define SIOCSARP           _IO(0x89, 0x55) /* set ARP table entry. */

/* RARP cache control calls. */
#define SIOCDRARP          _IO(0x89, 0x60) /* delete RARP table entry. */
#define SIOCGRARP          _IO(0x89, 0x61) /* get RARP table entry. */
#define SIOCSRARP          _IO(0x89, 0x62) /* set RARP table entry. */

/* Driver configuration calls */
#define SIOCGIFMAP         _IO(0x89, 0x70) /* Get device parameters. */
#define SIOCSIFMAP         _IO(0x89, 0x71) /* Set device parameters. */

/* DLCI configuration calls */
#define SIOCADDDLCI        _IO(0x89, 0x80) /* Create new DLCI device. */
#define SIOCDELDLCI        _IO(0x89, 0x81) /* Delete DLCI device. */
#endif /* __KOS__ || __linux__ */

#ifdef __linux__
#define SIOCGIFVLAN        _IO(0x89, 0x82) /* 802.1Q VLAN support */
#define SIOCSIFVLAN        _IO(0x89, 0x83) /* Set 802.1Q VLAN options */
#endif /* __linux__ */

#ifdef __linux__
/* bonding calls */
#define SIOCBONDENSLAVE        _IO(0x89, 0x90) /* enslave a device to the bond */
#define SIOCBONDRELEASE        _IO(0x89, 0x91) /* release a slave from the bond */
#define SIOCBONDSETHWADDR      _IO(0x89, 0x92) /* set the hw addr of the bond */
#define SIOCBONDSLAVEINFOQUERY _IO(0x89, 0x93) /* rtn info about slave state */
#define SIOCBONDINFOQUERY      _IO(0x89, 0x94) /* rtn info about bond state */
#define SIOCBONDCHANGEACTIVE   _IO(0x89, 0x95) /* update to a new active slave */
#endif /* __linux__ */

#ifdef __linux__
/* bridge calls */
#define SIOCBRADDBR        _IO(0x89, 0xa0) /* create new bridge device */
#define SIOCBRDELBR        _IO(0x89, 0xa1) /* remove bridge device */
#define SIOCBRADDIF        _IO(0x89, 0xa2) /* add interface to bridge */
#define SIOCBRDELIF        _IO(0x89, 0xa3) /* remove interface from bridge */
#endif /* __linux__ */

#ifdef __linux__
/* hardware time stamping */
#define SIOCSHWTSTAMP      _IO(0x89, 0xb0) /* set and get config */
#define SIOCGHWTSTAMP      _IO(0x89, 0xb1) /* get config */
#endif /* __linux__ */


#if defined(__KOS__) || defined(__linux__)
/* Device private ioctl calls. */
#define SIOCDEVPRIVATE     _IO(0x89, 0xf0) /* to _IO(0x89, 0xff) */
/* These 16 ioctl calls are protocol private */
#define SIOCPROTOPRIVATE   _IO(0x89, 0xe0) /* to _IO(0x89, 0xef) */
#endif /* __KOS__ || __linux__ */


#endif /* !_ASM_IOCTLS_SOCKET_EX_H */
