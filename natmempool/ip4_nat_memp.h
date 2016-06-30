#ifndef _IP4_NAT_MEMP_H
#define _IP4_NAT_MEMP_H

#define MEMORY_MAP_ADDRS 0x10000000
#define MEMORY_MAP_SIZE  900*1024*1024 

extern unsigned char  *mem_buffer;
//用于存储空闲nat转换记录的结构体
struct ip4_nat_memp{
	struct ip4_nat_memp *next;
};

void nat_memp_init(void *,unsigned long);
struct ip4_nat_record *nat_memp_malloc(void);
void nat_memp_free(struct ip4_nat_record *mem);

#endif	//_IP4_NAT_MEMP_H
