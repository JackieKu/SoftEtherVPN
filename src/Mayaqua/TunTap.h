// SoftEther VPN Source Code - Developer Edition Master Branch
// Mayaqua Kernel


#ifndef	TUNTAP_H
#define	TUNTAP_H

#ifdef	UNIX_LINUX
#include <linux/if_tun.h>
#else	// UNIX_LINUX

#ifdef	UNIX_SOLARIS

// -----------------------------------------------------------------
// Tap header for Solaris
// This header definitions are from Multithreaded STREAMS tun pseudo device driver
// written by Maxim Krasnyansky <max_mk@yahoo.com>.
// This definitions includes only types and constants definitions,
// and it does not include any programs.
// -----------------------------------------------------------------

#ifndef _SYS_IF_TUN_H
#define _SYS_IF_TUN_H

#ifdef _KERNEL
/* Uncomment to enable debugging */
/* #define TUN_DEBUG 1 */

#ifdef TUN_DEBUG
#define DBG      cmn_err
#else
#define DBG( a... )
#endif

/* PPA structure, one per TUN iface */ 
struct tunppa {
  unsigned int id;              /* Iface number         */
  queue_t *rq;                  /* Control Stream RQ    */
  struct tunstr * p_str;        /* Protocol Streams     */
}; 
#define TUNMAXPPA       20

/* Stream structure, one per Stream */
struct tunstr {
  struct tunstr *s_next;        /* next in streams list */
  struct tunstr *p_next;        /* next in ppa list */
  queue_t *rq;                  /* pointer to rq */

  struct tunppa *ppa;           /* assigned PPA */
  u_long flags;                 /* flags */
  u_long state;                 /* DL state */
  u_long sap;                   /* bound sap */
  u_long minor;                 /* minor device number */
};

/* Flags */
#define TUN_CONTROL     0x0001

#define TUN_RAW         0x0100
#define TUN_FAST        0x0200

#define TUN_ALL_PHY     0x0010
#define TUN_ALL_SAP     0x0020
#define TUN_ALL_MUL     0x0040

#define SNIFFER(a) ( (a & TUN_ALL_SAP) || (a & TUN_ALL_PHY) )

struct tundladdr {
  u_short sap;
};
#define TUN_ADDR_LEN    (sizeof(struct tundladdr))

#define TUN_QUEUE       0
#define TUN_DROP        1

#endif /* _KERNEL */

/* IOCTL defines */
#define TUNNEWPPA       (('T'<<16) | 0x0001)
#define TUNSETPPA       (('T'<<16) | 0x0002)

#endif  /* _SYS_IF_TUN_H */

#else	// UNIX_SOLARIS

#if	defined(UNIX_BSD) || (!defined(NO_VLAN) && defined(UNIX_MACOS))

// -----------------------------------------------------------------
// Tap header for FreeBSD
// -----------------------------------------------------------------
// -----------------------------------------------------------------
// Tap header For MacOS
// -----------------------------------------------------------------
/*      $NetBSD: if_tun.h,v 1.5 1994/06/29 06:36:27 cgd Exp $   */

/*
 * Copyright (c) 1988, Julian Onions <jpo@cs.nott.ac.uk>
 * Nottingham University 1987.
 *
 * This source may be freely distributed, however I would be interested
 * in any changes that are made.
 *
 * This driver takes packets off the IP i/f and hands them up to a
 * user process to have its wicked way with. This driver has it's
 * roots in a similar driver written by Phil Cockcroft (formerly) at
 * UCL. This driver is based much more on read/write/select mode of
 * operation though.
 *
 * $FreeBSD: src/sys/net/if_tun.h,v 1.17 2000/01/23 01:47:12 brian Exp $
 */

#ifndef _NET_IF_TUN_H_
#define _NET_IF_TUN_H_

#ifdef UNIX_MACOS
#ifndef _DARWIN_C_SOURCE
#define _DARWIN_C_SOURCE
#endif
#include <sys/types.h>
#endif

/* Refer to if_tunvar.h for the softc stuff */

/* Maximum transmit packet size (default) */
#define TUNMTU          1500

/* Maximum receive packet size (hard limit) */
#define TUNMRU          16384

struct tuninfo {
        int     baudrate;               /* linespeed */
        short   mtu;                    /* maximum transmission unit */
        u_char  type;                   /* ethernet, tokenring, etc. */
        u_char  dummy;                  /* place holder */
};

/* ioctl's for get/set debug */
#define TUNSDEBUG       _IOW('t', 90, int)
#define TUNGDEBUG       _IOR('t', 89, int)
#define TUNSIFINFO      _IOW('t', 91, struct tuninfo)
#define TUNGIFINFO      _IOR('t', 92, struct tuninfo)
#define TUNSLMODE       _IOW('t', 93, int)
#define TUNSIFMODE      _IOW('t', 94, int)
#define TUNSIFPID       _IO('t', 95)
#define TUNSIFHEAD      _IOW('t', 96, int)
#define TUNGIFHEAD      _IOR('t', 97, int)

#endif /* !_NET_IF_TUN_H_ */

#else	// UNIX_BSD

#endif	// defined(UNIX_BSD) || (!defined(NO_VLAN) && defined(UNIX_MACOS))

#endif	// UNIX_SOLARIS

#endif	// UNIX_LINUX

#endif	// TUNTAP_H
