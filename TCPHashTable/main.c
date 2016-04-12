#include <stdio.h>
#include <string.h>

#include "tls.h"
#include "tlshash.h"

int main()
{
	tls_hash_table *hash_table = init_tls_hash_table();
	
	/*
	char *arr_sip[6] = {
						"192.168.101.105",
						"192.168.101.104",
						"192.168.101.106",
						"192.168.101.103",
						"192.168.101.110",
						"192.168.100.111"
	};

	char *arr_dip[6] = {
						"192.168.100.10",
						"192.168.100.11",
						"192.168.100.12",
						"192.168.100.13",
						"192.168.100.14",
						"192.168.101.1"
	};

	int arr_source[6] = {100,200,300,80,443,556};
	int arr_dst[6] = {200,100,300,443,80,655};
	*/
	char *arr_sip[6] = {
						"192.168.101.105",
						"192.168.101.104",
						"192.168.101.105",
						"192.168.101.103",
						"192.168.101.110",
						"192.168.100.111"
	};

	char *arr_dip[6] = {
						"192.168.101.104",
						"192.168.101.105",
						"192.168.101.104",
						"192.168.100.104",
						"192.168.100.14",
						"192.168.101.1"
	};

	int arr_source[6] = {100,200,100,80,443,556};
	int arr_dst[6] = {200,100,200,443,80,655};
	int i = 0;

	//create hash table
	for(i = 0; i < 5; i++)
	{
		tls_node *node = NULL;
		
		node = create_tls_node(i,arr_sip[i],arr_dip[i],arr_source[i],arr_dst[i]); 
		insert_tls_hash_node(hash_table,node,arr_sip[i],arr_dip[i],arr_source[i],arr_dst[i]);
	}

	print_hash_table(hash_table);

	int index;
	while(1)
	{
		printf("input query index :\n");
		scanf("%d",&index);
		tls_node *node = NULL;
		node = query_tls_hash_node(hash_table,arr_sip[index],arr_dip[index],arr_source[index],arr_dst[index]);

		if(node != NULL)
		{
			printf("sip = %s dip = %s source = %d dst = %d syn_time = %d\n",node->sourceIP,node->destIP,node->sourceport,node->destport,node->syn_time);
		}
		else
		{
			printf("can not find the index tupple\n");
		}
		//print_hash_table(hash_table);
		
		printf("input delete index:\n");
		scanf("%d",&index);
		delete_tls_hash_node(hash_table,arr_sip[index],arr_dip[index],arr_source[index],arr_dst[index]);
		print_hash_table(hash_table);
	}


}
