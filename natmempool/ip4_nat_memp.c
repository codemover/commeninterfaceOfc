#include<linux/timer.h>
#include"ip4_nat.h"
#include"ip4_nat_memp.h"
#define _DEBUG

struct  ip4_nat_memp *nat_record_free = NULL;
spinlock_t nat4_memp_lock;
unsigned char  *mem_buffer;

//nat转换记录内存空间初始化
void nat_memp_init(void *nat_memp_memory,unsigned long memsize)
{
	struct ip4_nat_memp *memp;
	int i,size;
	unsigned long num_record;
	memp = nat_memp_memory;
	
	size = sizeof(struct ip4_nat_record);
	num_record = memsize/size;
	printk("nat_memp_init: num_record=%ld\n",num_record);
	
	for(i=0; i<num_record;i++){
		//从头插入空闲链表
		memp->next = nat_record_free;
		nat_record_free = memp;
		memp = (struct ip4_nat_memp *)((unsigned char *)memp + size);	//偏移一个sizeof(struct ip4_nat_record)长度
#ifdef _DEBUG
		if(i==num_record-1)
			printk("last record:%p\n",memp);
#endif
	}

	//初始化内存自旋锁
	spin_lock_init(&nat4_memp_lock);
}

//为nat转换记录申请空间
struct ip4_nat_record* nat_memp_malloc(void)
{
	struct ip4_nat_memp *memp;
	spin_lock_bh(&nat4_memp_lock);
	memp = nat_record_free;
	if(memp!=NULL){
		nat_record_free = memp->next;
	}
	else
	{
		printk("***there is no space in mem pool \n\n");
	}
	spin_unlock_bh(&nat4_memp_lock);
	return (struct ip4_nat_record *)memp;
}

//释放nat转换记录的内存空间
void nat_memp_free(struct ip4_nat_record *mem)
{
	struct ip4_nat_memp *memp;
	if(mem==NULL){
		return ;
	}
	spin_lock_bh(&nat4_memp_lock);
	memp = (struct ip4_nat_memp *)mem;
	memp->next = nat_record_free;
	nat_record_free = memp;
	spin_unlock_bh(&nat4_memp_lock);
}









