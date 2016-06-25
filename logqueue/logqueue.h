#ifndef _LOG_QUEUE_H_
#define _LOG_QUEUE_H_

//#include "tlshash.h"

#define QUEUE_TYPE int
//#define QUEUE_DEBUG

typedef struct log_queue_node
{
	QUEUE_TYPE data;
	struct log_queue_node *next;
}log_queue_node;

typedef struct tls_log_queue
{
	log_queue_node *front;
	log_queue_node *rear;
}tls_log_queue;

tls_log_queue *init_tls_log_queue();

void insert_log_queue_node(tls_log_queue *log_queue,QUEUE_TYPE data);

QUEUE_TYPE delete_log_queue_node(tls_log_queue *log_queue);

#endif
