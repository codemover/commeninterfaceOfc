#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iptrie.h"

/*
 *name: itobinary
 *
 *param:
 * num: orignal number; binary_str: dest string; index: the binary str copy index
 *
 *return:
 * void
 */
void itobinary(int num,char binary_str[],int index)
{
	if(binary_str == NULL)
	{
		return;
	}

	int i,bit = 0x01;
	for(i = 0; i < 8; i++)
	{//conver integer to 8 bit binary str
		if((num & bit) != 0)
		{//oprater & is lower than != 
			binary_str[index + 7 - i] = '1';
		}
		else
		{
			binary_str[index + 7 - i] = '0';
		}
		
		bit <<= 1; //bit * 2
	}
}

/*
 *name: convert_ip_binary
 *
 *param:
 * ip:orign ip string; binary_str:dest binary string
 *
 *return:
 * void
 */
void convert_ip_binary(char ip[],char binary_str[])
{
	if(ip == NULL || binary_str == NULL)
	{
		return;
	}
	
	/*为确保正确性在进行转换之前可以进一步进行IP格式校验*/

	char *ip_sub = NULL;
	int i,index =0;
	
	ip_sub = strtok(ip,SPLIT_SIGN); //slit ip by .

	itobinary(atoi(ip_sub),binary_str,index);

	for(i = 0; i < 3; i++)
	{//need to ip legal detect to pretend error
		ip_sub = strtok(NULL,SPLIT_SIGN);
		
		index += 8;
		itobinary(atoi(ip_sub),binary_str,index);
	}

}

/*
 *name: create_iptrie_node
 *
 *return:
 * new ip trie node
 */
ip_trie_node *create_iptrie_node()
{
	ip_trie_node *node = (ip_trie_node *)calloc(1,sizeof(ip_trie_node));

	if(node == NULL)
	{
		perror("create ip trie node error -- calloc");
	}
	else
	{
		node->child[0] = NULL;
		node->child[1] = NULL;
	}

	return node;
}

/*
 *name: insert_iptrie_node
 *
 *param:
 * root: trie root; ip: orignal ip string
 * 
 *return:
 * void
 *
 *notice:
 * this function call strtok it will change input ip
 * so if input ip need to use at other position
 * you shold input a copy of ip
 */
void insert_iptrie_node(ip_trie_node *root,char ip[])
{
	if(root == NULL)
	{
		printf("trie have not init\n");
		
		return;
	}

	if(ip == NULL)
	{
		return;
	}

	char binary_str[IP_BINARY_LEN + 1];
	int i,child_index;
	
	memset(binary_str,0,IP_BINARY_LEN + 1);
	
	convert_ip_binary(ip,binary_str); //to binary string

	for(i = 0; i < IP_BINARY_LEN; i++)
	{
		child_index = binary_str[i] - '0'; //child is 0 or 1
		if(root->child[child_index] == NULL)
		{
			root->child[child_index] = create_iptrie_node();
		}
		
		root = root->child[child_index];
	}
}

/*
 *name: select_iptrie_node
 *
 *param: 
 * root: trie root; ip: orignal ip string
 *
 *return:
 * 0 :not find; 1:find
 *
 *notice:
 * this function call strtok it will change input ip
 * so if input ip need to use at other position
 * you shold input a copy of ip
 */
int select_iptrie_node(ip_trie_node *root,char ip[])
{
	if(root == NULL)
	{
		printf("trie have not init\n");
		return 0;
	}

	if(ip == NULL)
	{
		return 0;
	}

	int i;
	char binary_str[IP_BINARY_LEN + 1];

	memset(binary_str,0,IP_BINARY_LEN + 1);

	convert_ip_binary(ip,binary_str); //to binary string

	int child_index;
	for(i = 0; i < IP_BINARY_LEN; i++)
	{
		child_index = binary_str[i] - '0';
		
		if(root->child[child_index] == NULL)
		{
			return 0;
		}

		root = root->child[child_index];
	}

	return 1;
}

