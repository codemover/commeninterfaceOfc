#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>

#include "tlshash.h"


/*
 * *name: compare_tupple
 * return:
 * 1 same -1 diffirent
 */

static int compare_tupple(const tls_node *node,char *sip,char *dip,uint16_t source,uint16_t dst)
{
	//c->s
	if( (strcmp(node->sourceIP,sip) == 0) && (strcmp(node->destIP,dip) == 0) )
	{
		if( (node->sourceport == source) && (node->destport == dst) )
		{
			return 1;
		}
	}
	//s->c
	
	if( (strcmp(node->sourceIP,dip) == 0) && (strcmp(node->destIP,sip) == 0) )
	{
		if( (node->sourceport == dst) && (node->destport == source) )
		{
			return 1;
		}
	}

	return -1;
}

/*
 * *name: cal_hash_value
 * *retrurn:
 * hash value
 */

static uint32_t cal_hash_value(const char *sip,const char *dip,uint16_t source,uint16_t dst)
{
	uint32_t uint_sip = inet_addr(sip);
	uint32_t uint_dip = inet_addr(dip);

	uint32_t hash_value = (uint_sip ^ source) ^ (uint_dip ^ dst);
	
	hash_value ^= hash_value >> 16;
	hash_value ^= hash_value >> 8;

	return hash_value % TLS_HASH_TABLE_SIZE;

}

/*
 * *name: init_tls_hash_table
 * *return:
 * NULL failed else success
 */

tls_hash_table *init_tls_hash_table()
{
	tls_hash_table *hash_table = (tls_hash_table *)calloc(1,sizeof(tls_hash_table));

	if(hash_table == NULL)
	{
		perror("tls hash table init error--calloc memory");

		return NULL;
	}

	int i;

	for(i = 0; i < TLS_HASH_TABLE_SIZE; i++)
	{
		hash_table->tls_table[i] = NULL;

		pthread_mutex_init(&(hash_table->table_mutex[i]),NULL);
	}

	return hash_table;
}

/*
 * *name: create_tls_node
 *
 * param:
 * syn_time : syn packet start time
 *
 * *return:
 * NULL failed else success
 */

tls_node *create_tls_node(int syn_time,char *sip,char *dip,int source,int dst)
{
	tls_node *node = (tls_node *)calloc(1,sizeof(tls_node));

	if(node == NULL)
	{
		perror("create tls node error--calloc memory");

		return NULL;
	}

	node->syn_time = syn_time; //record start time for node
	/*record tupple*/
	strcpy(node->sourceIP,sip);
	strcpy(node->destIP,dip);
	node->sourceport = source;
	node->destport = dst;

	node->next = NULL;

	return node;
}

/*
 * *name: insert_tls_hash_node
 * *return:
 * void
 */

void insert_tls_hash_node(tls_hash_table *hash_table,tls_node *node,char *sip,char *dip,int source,int dst)
{
	uint32_t hash_value = cal_hash_value(sip,dip,source,dst); 
	
	pthread_mutex_lock(&(hash_table->table_mutex[hash_value])); //lock the tls node list
	
	int find_flag = 0;
	tls_node **current = &(hash_table->tls_table[hash_value]);

	while(*current != NULL)
	{//cal list tail
		if(compare_tupple(*current,sip,dip,source,dst) == 1)
		{//find the same node
			printf("there is already the same node in the hash table\n");
			
			find_flag = 1;
			break;
		}
		
		//*current = (*current)->next;
		current = &((*current)->next);//use last line current can not point to the right position
	}

	if(find_flag == 0)
	{
		*current = node;//add node to tail
	}

	pthread_mutex_unlock(&(hash_table->table_mutex[hash_value]));//unlock the tls node list
	
}

/*
 * *name: query_tls_hash_node
 * *return:
 * NULL do have this tupple node else the tls node pointer
 */

tls_node *query_tls_hash_node(tls_hash_table *hash_table,char *sip,char *dip,int source,int dst)
{

	int hash_value = cal_hash_value(sip,dip,source,dst);
	
	pthread_mutex_lock(&(hash_table->table_mutex[hash_value])); //lock the tls node list

	tls_node *node = hash_table->tls_table[hash_value];
	while(node != NULL)
	{
		if(compare_tupple(node,sip,dip,source,dst) == 1)
		{//find the same node in tls node list
			//return node; //make the lock can not release if return here
			break;
		}
		
		node = node->next;
	}

	pthread_mutex_unlock(&(hash_table->table_mutex[hash_value]));//unlock the tls node list
	
	return node;
}

/*
 * *name: delete_tls_hash_node
 * *return:
 * void 
 */

void delete_tls_hash_node(tls_hash_table *hash_table,char *sip,char *dip,int source,int dst)
{
	int hash_value = cal_hash_value(sip,dip,source,dst);

	pthread_mutex_lock(&(hash_table->table_mutex[hash_value])); //lock the tls node list
	
	tls_node *current_node,*pre_node;
	
	current_node = pre_node = hash_table->tls_table[hash_value];
	
	while( current_node != NULL)
	{

		if(compare_tupple(current_node,sip,dip,source,dst) == 1)
		{//find the tls node by tupple and delete node
			if(current_node == hash_table->tls_table[hash_value])
			{//find tupple node is head
				hash_table->tls_table[hash_value] = current_node->next;
			}
			else
			{//tht tupple node is not head 
				pre_node->next = current_node->next;
			}
			
			free(current_node);
			break;
		}

		pre_node = current_node;//record pre tls node
		current_node = current_node->next;
	}
	
	pthread_mutex_unlock(&(hash_table->table_mutex[hash_value]));//unlock the tls node list
}


/*
 * *name:print_hash_table
 *
 * purpose:
 * to checkout if the hash table is save right
 *
 * return:
 * void
 */

void print_hash_table(tls_hash_table *hash_table)
{
	int i;

	for(i = 0; i < TLS_HASH_TABLE_SIZE; i++)
	{
		tls_node *node = hash_table->tls_table[i];

		if(node != NULL)
		{
			printf("list %d is:\n",i);
		
			while(node != NULL)
			{
				printf("sip = %s ",node->sourceIP);
				printf("dip = %s ",node->destIP);
				printf("sport = %d ",node->sourceport);
				printf("dport = %d ",node->destport);
				printf("syb_time = %d ",node->syn_time);	
				node = node->next;
			}

			printf("\n");
		}
	}
}
