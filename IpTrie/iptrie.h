#ifndef _IP_TRIE_H_
#define _IP_TIRE_H_

#define SPLIT_SIGN "."
#define IP_BINARY_LEN 32

typedef struct ip_trie_node
{
	struct ip_trie_node *child[2]; //two child node
}ip_trie_node;

ip_trie_node *create_iptrie_node();

void insert_iptrie_node(ip_trie_node *root,char ip[]);

int select_iptrie_node(ip_trie_node *root,char ip[]);

#endif
