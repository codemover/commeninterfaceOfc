#ifndef _TLS_HASH_H_
#define _TLS_HASH_H_

#include <pthread.h>

#include "tls.h"

#define TLS_HASH_TABLE_SIZE 65535

typedef struct tls_hash_table
{
	tls_node *tls_table[TLS_HASH_TABLE_SIZE];
	pthread_mutex_t table_mutex[TLS_HASH_TABLE_SIZE];
	int count;

}tls_hash_table;


tls_hash_table *init_tls_hash_table();

tls_node *create_tls_node(int syn_time,char *sip,char *dip,int source,int dst);

void insert_tls_hash_node(tls_hash_table *hash_table,tls_node *node,char *sip,char *dip,int source,int dst);

tls_node *query_tls_hash_node(tls_hash_table *hash_table,char *sip,char *dip,int source,int dst);

void delete_tls_hash_node(tls_hash_table *hash_table,char *sip,char *dip,int source,int dst);

void print_hash_table(tls_hash_table *hash_table);

#endif
