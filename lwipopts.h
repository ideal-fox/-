/**
  ******************************************************************************
  * @file    lwipopts.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11/20/2009
  * @brief   lwIP Options Configuration.
  *          This file is based on Utilities\lwip-1.3.1\src\include\lwip\opt.h 
  *          and contains the lwIP configuration for the STM32F107 demonstration.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */

#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__
#include "ucos_ii.h"

#define TQ2440_LWIP_DEBUG
#if defined(TQ2440_LWIP_DEBUG)
/*
#define LWIP_DEBUG
#define MEM_DEBUG               LWIP_DBG_ON
#define MEMP_DEBUG              LWIP_DBG_ON
#define PBUF_DEBUG              LWIP_DBG_ON
#define API_LIB_DEBUG   LWIP_DBG_ON
#define API_MSG_DEBUG   LWIP_DBG_ON 
#define TCPIP_DEBUG             LWIP_DBG_ON
#define NETIF_DEBUG             LWIP_DBG_ON
#define SOCKETS_DEBUG   LWIP_DBG_ON
#define DEMO_DEBUG              LWIP_DBG_ON
#define IP_DEBUG                LWIP_DBG_ON
#define IP_REASS_DEBUG  LWIP_DBG_ON
#define RAW_DEBUG               LWIP_DBG_ON
#define ICMP_DEBUG              LWIP_DBG_ON
#define UDP_DEBUG               LWIP_DBG_ON
#define TCP_DEBUG               LWIP_DBG_ON
#define TCP_INPUT_DEBUG         LWIP_DBG_ON
#define TCP_OUTPUT_DEBUG        LWIP_DBG_ON
#define TCP_RTO_DEBUG   LWIP_DBG_ON
#define TCP_CWND_DEBUG  LWIP_DBG_ON
#define TCP_WND_DEBUG   LWIP_DBG_ON
#define TCP_FR_DEBUG    LWIP_DBG_ON
#define TCP_QLEN_DEBUG  LWIP_DBG_ON
#define TCP_RST_DEBUG   LWIP_DBG_ON
#define PPP_DEBUG   LWIP_DBG_ON
#define ETHARP_DEBUG                    LWIP_DBG_ON
#define NETIF_DEBUG                     LWIP_DBG_ON

#define DM9000IF_DEBUG LWIP_DBG_ON
#define DM9000_PACKET_DEBUG LWIP_DBG_ON
*/
#define LWIP_DEBUG

#define MEM_DEBUG               LWIP_DBG_ON
#define MEMP_DEBUG              LWIP_DBG_ON

#define LWIP_DBG_TYPES_ON    (LWIP_DBG_ON|LWIP_DBG_TRACE|LWIP_DBG_STATE|LWIP_DBG_FRESH|LWIP_DBG_HALT)
#endif

/**
 * DM9000IF_DEBUG: Enable debugging for DM9000 interface.
 */
#ifndef DM9000IF_DEBUG
#define DM9000IF_DEBUG                       LWIP_DBG_OFF
#endif
/**
 * DM9000_PACKET_DEBUG: Enable debugging for DM9000 packet.
 */
#ifndef DM9000_PACKET_DEBUG
#define DM9000_PACKET_DEBUG                  LWIP_DBG_OFF
#endif


/*----------------Thread Priority---------------------------------------------*/
#ifndef TCPIP_THREAD_PRIO
#define TCPIP_THREAD_PRIO			1
#endif
#undef  DEFAULT_THREAD_PRIO
#define DEFAULT_THREAD_PRIO			2


/**
 * SYS_LIGHTWEIGHT_PROT==1: if you want inter-task protection for certain
 * critical regions during buffer allocation, deallocation and memory
 * allocation and deallocation.
 */
#define SYS_LIGHTWEIGHT_PROT    0

/**
 * NO_SYS==1: Provides VERY minimal functionality. Otherwise,
 * use lwIP facilities.
 */
#define NO_SYS                  0 

/* ---------- Memory options ---------- */
/* MEM_ALIGNMENT: should be set to the alignment of the CPU for which
   lwIP is compiled. 4 byte alignment -> define MEM_ALIGNMENT to 4, 2
   byte alignment -> define MEM_ALIGNMENT to 2. */
#undef  MEM_ALIGNMENT
#define MEM_ALIGNMENT           4


/* MEM_SIZE: the size of the heap memory. If the application will send
a lot of data that needs to be copied, this should be set high. */
#undef MEM_SIZE
#define MEM_SIZE                40960/*(4096) */

/* MEMP_NUM_PBUF: the number of memp struct pbufs. If the application
   sends a lot of data out of ROM (or other static memory), this
   should be set high. */
#undef MEMP_NUM_PBUF
#define MEMP_NUM_PBUF           20
/* MEMP_NUM_UDP_PCB: the number of UDP protocol control blocks. One
   per active UDP "connection". */
#undef MEMP_NUM_UDP_PCB
#define MEMP_NUM_UDP_PCB        16
/* MEMP_NUM_TCP_PCB: the number of simulatenously active TCP
   connections. */
#undef MEMP_NUM_TCP_PCB
#define MEMP_NUM_TCP_PCB        128
/* MEMP_NUM_TCP_PCB_LISTEN: the number of listening TCP
   connections. */
#undef MEMP_NUM_TCP_PCB_LISTEN
#define MEMP_NUM_TCP_PCB_LISTEN 12
/* MEMP_NUM_TCP_SEG: the number of simultaneously queued TCP
   segments. */
#undef MEMP_NUM_TCP_SEG
#define MEMP_NUM_TCP_SEG        24
/* MEMP_NUM_SYS_TIMEOUT: the number of simulateously active
   timeouts. */

#define MEMP_NUM_SYS_TIMEOUT    10


/* ---------- Pbuf options ---------- */
/* PBUF_POOL_SIZE: the number of buffers in the pbuf pool. */
#undef PBUF_POOL_SIZE
#define PBUF_POOL_SIZE          1024

/* PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool. */
#undef PBUF_POOL_BUFSIZE
#define PBUF_POOL_BUFSIZE       1500 /* LWIP_MEM_ALIGN_SIZE(TCP_MSS+40+PBUF_LINK_HLEN) */


/* ---------- TCP options ---------- */
#define LWIP_TCP                1
#undef TCP_TTL
#define TCP_TTL                 255

#undef TCPIP_THREAD_STACKSIZE
#define TCPIP_THREAD_STACKSIZE                  LWIP_STK_SIZE

/* Controls if TCP should queue segments that arrive out of
   order. Define to 0 if your device is low on memory. */
#undef TCP_QUEUE_OOSEQ
#define TCP_QUEUE_OOSEQ         0

/**
 * TCPIP_MBOX_SIZE: The mailbox size for the tcpip thread messages
 * The queue size value itself is platform-dependent, but is passed to
 * sys_mbox_new() when tcpip_init is called.
 */
#undef TCPIP_MBOX_SIZE
#define TCPIP_MBOX_SIZE         MAX_QUEUE_ENTRIES

/**
 * DEFAULT_TCP_RECVMBOX_SIZE: The mailbox size for the incoming packets on a
 * NETCONN_TCP. The queue size value itself is platform-dependent, but is passed
 * to sys_mbox_new() when the recvmbox is created.
 */
#undef DEFAULT_TCP_RECVMBOX_SIZE
#define DEFAULT_TCP_RECVMBOX_SIZE       MAX_QUEUE_ENTRIES


/**
 * DEFAULT_ACCEPTMBOX_SIZE: The mailbox size for the incoming connections.
 * The queue size value itself is platform-dependent, but is passed to
 * sys_mbox_new() when the acceptmbox is created.
 */
#undef DEFAULT_ACCEPTMBOX_SIZE
#define DEFAULT_ACCEPTMBOX_SIZE         MAX_QUEUE_ENTRIES

/* TCP Maximum segment size. */
#undef TCP_MSS
#define TCP_MSS                 (1500 - 40)	  /* TCP_MSS = (Ethernet MTU - IP header size - TCP header size) */

/* TCP sender buffer space (bytes). */
#undef TCP_SND_BUF
#define TCP_SND_BUF             (4*TCP_MSS)

/* TCP sender buffer space (pbufs). This must be at least = 2 *
   TCP_SND_BUF/TCP_MSS for things to work. */
#undef TCP_SND_QUEUELEN
#define TCP_SND_QUEUELEN        (6 * TCP_SND_BUF)/TCP_MSS

/* TCP receive window. */
#undef TCP_WND
#define TCP_WND                 (2*TCP_MSS)


/* ---------- ICMP options ---------- */
#define LWIP_ICMP                       1


/* ---------- DHCP options ---------- */
/* Define LWIP_DHCP to 1 if you want DHCP configuration of
   interfaces. DHCP is not implemented in lwIP 0.5.1, however, so
   turning this on does currently not work. */
#define LWIP_DHCP               1


/* ---------- UDP options ---------- */
#define LWIP_UDP                1
#undef UDP_TTL
#define UDP_TTL                 255
#undef DEFAULT_UDP_RECVMBOX_SIZE
#define DEFAULT_UDP_RECVMBOX_SIZE       MAX_QUEUE_ENTRIES

/* -----------RAW options -----------*/
#undef DEFAULT_RAW_RECVMBOX_SIZE
#define DEFAULT_RAW_RECVMBOX_SIZE       MAX_QUEUE_ENTRIES
#define DEFAULT_ACCEPTMBOX_SIZE         MAX_QUEUE_ENTRIES

/* ---------- Statistics options ---------- */
#undef LWIP_STATS
#define LWIP_STATS 1/*0*/
#define LWIP_PROVIDE_ERRNO 1


/*
   --------------------------------------
   ---------- Checksum options ----------
   --------------------------------------
*/

/* 
The STM32F107 allows computing and verifying the IP, UDP, TCP and ICMP checksums by hardware:
 - To use this feature let the following define uncommented.
 - To disable it and process by CPU comment the  the checksum.
*/
#undef CHECKSUM_BY_HARDWARE 


#ifdef CHECKSUM_BY_HARDWARE
  /* CHECKSUM_GEN_IP==0: Generate checksums by hardware for outgoing IP packets.*/
  #undef CHECKSUM_GEN_IP
  #define CHECKSUM_GEN_IP                 0
  /* CHECKSUM_GEN_UDP==0: Generate checksums by hardware for outgoing UDP packets.*/
  #undef CHECKSUM_GEN_UDP
  #define CHECKSUM_GEN_UDP                0
  /* CHECKSUM_GEN_TCP==0: Generate checksums by hardware for outgoing TCP packets.*/
  #undef CHECKSUM_GEN_TCP
  #define CHECKSUM_GEN_TCP                0 
  /* CHECKSUM_CHECK_IP==0: Check checksums by hardware for incoming IP packets.*/
  #undef CHECKSUM_CHECK_IP
  #define CHECKSUM_CHECK_IP               0
  /* CHECKSUM_CHECK_UDP==0: Check checksums by hardware for incoming UDP packets.*/
  #undef CHECKSUM_CHECK_UDP
  #define CHECKSUM_CHECK_UDP              0
  /* CHECKSUM_CHECK_TCP==0: Check checksums by hardware for incoming TCP packets.*/
  #undef CHECKSUM_CHECK_TCP
  #define CHECKSUM_CHECK_TCP              0
#else
  /* CHECKSUM_GEN_IP==1: Generate checksums in software for outgoing IP packets.*/
  #define CHECKSUM_GEN_IP                 1
  /* CHECKSUM_GEN_UDP==1: Generate checksums in software for outgoing UDP packets.*/
  #define CHECKSUM_GEN_UDP                1
  /* CHECKSUM_GEN_TCP==1: Generate checksums in software for outgoing TCP packets.*/
  #define CHECKSUM_GEN_TCP                1
  /* CHECKSUM_CHECK_IP==1: Check checksums in software for incoming IP packets.*/
  #define CHECKSUM_CHECK_IP               1
  /* CHECKSUM_CHECK_UDP==1: Check checksums in software for incoming UDP packets.*/
  #define CHECKSUM_CHECK_UDP              1
  /* CHECKSUM_CHECK_TCP==1: Check checksums in software for incoming TCP packets.*/
  #define CHECKSUM_CHECK_TCP              1
#endif


/*
   ----------------------------------------------
   ---------- Sequential layer options ----------
   ----------------------------------------------
*/
/**
 * LWIP_NETCONN==1: Enable Netconn API (require to use api_lib.c)
 */
#define LWIP_NETCONN                    1
/*
   ------------------------------------
   ---------- Socket options ----------
   ------------------------------------
*/
/**
 * LWIP_SOCKET==1: Enable Socket API (require to use sockets.c)
 */
#define LWIP_SOCKET                     1

#define LWIP_COMPAT_MUTEX               1

#if not_used
/**
 * MEMCPY: override this if you have a faster implementation at hand than the
 * one included in your C library
 */
#ifndef MEMCPY
#define MEMCPY(dst,src,len)             OS_MemCopy((INT8U*)dst,(INT8U*)src,len)
#endif
#ifndef SMEMCPY
#define SMEMCPY(dst,src,len)            OS_MemCopy((INT8U*)dst,(INT8U*)src,len)
#endif
#endif

//#define MEM_USE_POOLS                   1
#define mem_free mem_free
#define mem_malloc mem_malloc
#define mem_calloc mem_calloc

#define printf Uart_Printf

#define MEMP_NUM_TCPIP_MSG_INPKT        64

#define MEMP_NUM_NETCONN                32
#define MEMP_NUM_TCPIP_MSG_API          64

#endif /* __LWIPOPTS_H__ */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
