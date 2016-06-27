#include<linux/timer.h>
#include"ip4_nat.h"
#include"ip4_nat_memp.h"
#define _DEBUG

struct  ip4_nat_memp *nat_record_free = NULL;
spinlock_t nat4_memp_lock;
unsigned char  *mem_buffer;

//natת����¼�ڴ�ռ��ʼ��
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
		//��ͷ�����������
		memp->next = nat_record_free;
		nat_record_free = memp;
		memp = (struct ip4_nat_memp *)((unsigned char *)memp + size);	//ƫ��һ��sizeof(struct ip4_nat_record)����
#ifdef _DEBUG
		if(i==num_record-1)
			printk("last record:%p\n",memp);
#endif
	}

	//��ʼ���ڴ�������
	spin_lock_init(&nat4_memp_lock);
}

//Ϊnatת����¼����ռ�
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

//�ͷ�natת����¼���ڴ�ռ�
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









