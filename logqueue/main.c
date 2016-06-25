#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "logqueue.h"

#define INSERT_INTERVAL 0
#define MAX_INSERT_NUM 1000

int insert_index = 0;

tls_log_queue *log_queue;

void *insert_queue_thread()
{
	while(1)
	{
		sleep(INSERT_INTERVAL);
	
		if(insert_index > MAX_INSERT_NUM)
		{
			printf("insert thread quit\n");
			
			return;
		}

		insert_index++;
		//printf("insert number %d\n",insert_index);
		insert_log_queue_node(log_queue,insert_index);
	}
}

void *get_queue_thread()
{
	while(1)
	{
		int data = delete_log_queue_node(log_queue);
		
		if(data != -1)
		{
			printf("get data is %d \n",data);
		}
	}
}


int main()
{
	/*init*/
	insert_index  = 0;
	log_queue = init_tls_log_queue();

	/*create thread*/
	pthread_t tid_insert,tid_get;

	int ret;

	ret = pthread_create(&tid_insert,NULL,insert_queue_thread,NULL);
	if(ret != 0)
	{
		perror("create insert thread error");
	}

	ret = pthread_create(&tid_get,NULL,get_queue_thread,NULL);
	if(ret != 0)
	{
		perror("create get thread error");
	}

	pthread_join(tid_insert,NULL);
	pthread_join(tid_get,NULL);
}
