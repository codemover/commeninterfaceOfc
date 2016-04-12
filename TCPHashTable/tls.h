#ifndef _TLS_H_
#define _TLS_H_

typedef struct tls_node
{
	char sourceIP[32];
	char destIP[32];
	int sourceport;
	int destport;

	int syn_time;

	struct tls_node *next;
}tls_node;

#endif
