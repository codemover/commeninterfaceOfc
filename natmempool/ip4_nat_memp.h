#ifndef _IP4_NAT_MEMP_H
#define _IP4_NAT_MEMP_H

#include <linux/kernel.h>  
#include <linux/udp.h> 
#include <linux/tcp.h>             
#include <net/ipv6.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <asm/checksum.h>
#include <linux/netfilter.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/socket.h>/*PF_INET*/
#include <linux/netfilter_ipv4.h>/*NF_IP_PRE_FIRST*/
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/inet.h> /*in_aton()*/
#include <net/ip.h>
#include <net/tcp.h>                                                                                                                                         
#include <asm/io.h>


#define MEMORY_MAP_ADDRS 0x10000000
#define MEMORY_MAP_SIZE  900*1024*1024 

extern unsigned char  *mem_buffer;
//用于存储空闲nat转换记录的结构体
struct ip4_nat_memp{
	struct ip4_nat_memp *next;
};
#ifndef NULL
#define NULL 0
#endif 

void nat_memp_init(void *,unsigned long);
struct ip4_nat_record *nat_memp_malloc(void);
void nat_memp_free(struct ip4_nat_record *mem);

#endif	//_IP4_NAT_MEMP_H
