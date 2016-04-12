#include <stdio.h>
#include <stdlib.h>

#include "iptrie.h"


int main()
{
	char sip[18];
	char dip[18];
	int i = 0;
	int isfind = 0;
	ip_trie_node *root = create_iptrie_node();

	while(1)
	{
		printf("insert a ip:\n");
		scanf("%s",sip);
		insert_iptrie_node(root,sip);
		
		printf("query a ip:\n");
		scanf("%s",dip);
		isfind = select_iptrie_node(root,dip);
		if(isfind == 1)
		{
			printf("find\n");
		}
		else
		{
			printf("not find\n");
		}
	}
}
