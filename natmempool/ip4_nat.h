
#ifndef IP4_NAT_H
#define IP4_NAT_H

#define NAT_ORIGNAL 0
#define NAT_REPLY 1
#define NAT_DIR_MAX 2
#define NAT_TABLE_SIZE 65535

#define ETHALEN 14 //MAC长度，需要为每个节点存容器的MAC

#define DIRECT_IN  0 //境内方向
#define DIRECT_OUT 1 //境外方向

/*用于标志target snat的函数返回，已做不同的处理*/
#define FIND_BROTHER 2
#define FIND_NO_BROTHER 1

struct in4_nat_addr{
	uint32_t  in4;
};
//单一方向的四元组
struct nat_tuple{
	struct in4_nat_addr src;
	struct in4_nat_addr dst;
	unsigned short sport;
	unsigned short dport;

	unsigned char nat_mac[ETHALEN];//需要存储MAC值用于发包使用
	
	unsigned int hashIndex;
	unsigned int direct; //标记是in还是out的nat记录用于回包时填哪个mac
	short ip_id;
	unsigned char tran_proto;
	struct nat_tuple *next;
	struct nat_tuple *prev;
	struct ip4_nat_record *me;	
};

//nat转换记录
struct ip4_nat_record{
	struct nat_tuple nat_tuple[NAT_DIR_MAX];
	struct ip4_nat_record *brother; //指向另一个recoerd的指针
	struct timer_list timeout;
};


int target_src_nat(struct nat_tuple *tuple,struct nat_tuple *tuple_brother);
int target_dst_nat(struct nat_tuple *tuple);
void  print_nat_hash_table(void );
//#define _DEBUG

#define NUM_NAT_REC 100
#endif //IP4_NAT_H
