
#ifndef IP4_NAT_H
#define IP4_NAT_H

#define NAT_ORIGNAL 0
#define NAT_REPLY 1
#define NAT_DIR_MAX 2
#define NAT_TABLE_SIZE 65535

#define ETHALEN 14 //MAC���ȣ���ҪΪÿ���ڵ��������MAC

#define DIRECT_IN  0 //���ڷ���
#define DIRECT_OUT 1 //���ⷽ��

/*���ڱ�־target snat�ĺ������أ�������ͬ�Ĵ���*/
#define FIND_BROTHER 2
#define FIND_NO_BROTHER 1

struct in4_nat_addr{
	uint32_t  in4;
};
//��һ�������Ԫ��
struct nat_tuple{
	struct in4_nat_addr src;
	struct in4_nat_addr dst;
	unsigned short sport;
	unsigned short dport;

	unsigned char nat_mac[ETHALEN];//��Ҫ�洢MACֵ���ڷ���ʹ��
	
	unsigned int hashIndex;
	unsigned int direct; //�����in����out��nat��¼���ڻذ�ʱ���ĸ�mac
	short ip_id;
	unsigned char tran_proto;
	struct nat_tuple *next;
	struct nat_tuple *prev;
	struct ip4_nat_record *me;	
};

//natת����¼
struct ip4_nat_record{
	struct nat_tuple nat_tuple[NAT_DIR_MAX];
	struct ip4_nat_record *brother; //ָ����һ��recoerd��ָ��
	struct timer_list timeout;
};


int target_src_nat(struct nat_tuple *tuple,struct nat_tuple *tuple_brother);
int target_dst_nat(struct nat_tuple *tuple);
void  print_nat_hash_table(void );
//#define _DEBUG

#define NUM_NAT_REC 100
#endif //IP4_NAT_H
