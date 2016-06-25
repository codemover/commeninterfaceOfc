#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "logqueue.h"

/*
 *name: create_log_queue_node
 *
 *param:
 * data: queue node data
 *return:
 * success: new queue node; failed: NULL
 *
 *notice:
 * this is a inner interface can not use in other file
 */
static log_queue_node *create_log_queue_node(QUEUE_TYPE data)
{
	log_queue_node *node = (log_queue_node *)calloc(1,sizeof(log_queue_node));

	if(node == NULL)
	{
		perror("create log queue node error ---calloc");
		
		return NULL;
	}
	
	node->data = data;
	node->next = NULL;
}

/*
 *name: init_tls_log_queue
 *
 *return:
 * success: new log queue pointer; failed: NULL
 */
tls_log_queue *init_tls_log_queue()
{
	tls_log_queue *queue = (tls_log_queue *)calloc(1,sizeof(tls_log_queue));

	if(queue == NULL)
	{
		perror("init log queue error ---calloc");

		return NULL;
	}

	queue->front = queue->rear = create_log_queue_node(-2);
	//queue->front = queue->rear = create_log_queue_node(NULL);

	return queue;
}

/*
 *name: insert_log_queue_node
 *
 *param:
 * data: insert node data
 *
 *return:
 * void
 */
void insert_log_queue_node(tls_log_queue *log_queue,QUEUE_TYPE data)
{
	if(log_queue == NULL)
	{
#ifdef QUEUE_DEBUG
		printf("log queue have not be init\n");
#endif		
		return;
	}

	log_queue_node *node = create_log_queue_node(data);
	if(node == NULL)
	{
#ifdef QUEUE_DEBUG
		printf("create log queue node error in insert\n");
#endif		
		return;
	}

	/*insert node to rear*/
	log_queue->rear->next = node;
	log_queue->rear = node;
}

/*
 *name: delete_log_queue_node
 *
 *return:
 * logqueue head node's data
 */
QUEUE_TYPE delete_log_queue_node(tls_log_queue *log_queue)
{
	if(log_queue->front == log_queue->rear)
	{
#ifdef QUEUE_DEBUG
		printf("queue is empty\n");
#endif		
		return -1;
	}
	else
	{
		assert(log_queue->front->next != NULL); //to catch queue exception

		log_queue_node *node = log_queue->front->next;	
		
		if(node == log_queue->rear)
		{//set queue empty; notice:set derection can not opposite  
			log_queue->rear = log_queue->front;	
		}
		else
		{
			log_queue->front->next = node->next;
		}

		QUEUE_TYPE data = node->data;

		free(node);

		return data;
	}
}
