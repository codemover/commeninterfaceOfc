/*
 *2 binary search tree
 *data struct : list
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define VALUE_TYPE int

typedef struct search_tree_node
{
	VALUE_TYPE value;
	struct search_tree_node *l_child;
	struct search_tree_node *r_child;

}search_tree_node,*search_tree;

/*name: search_tree_init
 * *return:
 * search_tree 
 */

search_tree search_tree_init()
{
	return NULL;
}

/*
 * *name: search_tree_node_create
 * *return:
 * NULL failed else success
 */

search_tree_node *search_tree_node_create(VALUE_TYPE value)
{
	search_tree_node *node = (search_tree_node *)malloc(sizeof(search_tree_node));

	if(node == NULL)
	{
		return NULL;
	}

	node->l_child = NULL;
	node->r_child = NULL;
	node->value = value;
	
	return node;
}

/*
 * * name: search_tree_insert
 * * return:
 * 1 success -1 failed
 */

int search_tree_insert(search_tree *root,VALUE_TYPE value)
{
	if(root == NULL)
	{
		return -1;
	}

	search_tree_node **link = root; //to save the child node
	search_tree_node *current = NULL;

	while((current = *link) != NULL)
	{
		if(value == current->value)
		{
			return -1; //the value is already exist int the tree;
		}
		else
		{
			if(value < current->value)
			{
				link = &(current->l_child);
			}
			else
			{
				link = &(current->r_child);
			}
		}
	}
	
	*link = search_tree_node_create(value);
	
	return 1;
}

/*
 * *name: search_tree_find
 * *return:
 * 1 find -1 not find
 */

int search_tree_find(search_tree root,VALUE_TYPE value)
{
	if(root == NULL)
	{
		return -1;
	}

	search_tree_node *current = root;
	
	while(current != NULL)
	{
		if(value == current->value)
		{
			return 1;
		}
		else
		{
			if(value < current->value)
			{
				current = current->l_child;
			}
			else
			{
				current = current->r_child;
			}
		}
	}

	return -1;
}

/*
 * *name: search_tree_delete
 * *return:
 * 1 delete ok -1 delete failed
 */

int search_tree_delete(search_tree root,VALUE_TYPE value)
{
	if(root == NULL)
	{
		return -1;
	}

	search_tree_node **link = &root;
	search_tree_node *current = *link;
        int flag = 0;	

	while((current = *link) != NULL)
	{
		if(value == current->value)
		{
			flag = 1;
			break;
		}
		else
		{
			if(value < current->value)
			{
				link = &(current->l_child);
			}
			else
			{
				link = &(current->r_child);
			}
		}
	}

	if(flag == 0)
	{
		return -1; //the node is not exist 
	}
	
	if((*link)->l_child == NULL && (*link)->r_child == NULL)
	{//the node is leaf node
		free(*link);
		*link = NULL;	

		return 1;	
	}
	
	if((*link)->l_child != NULL && (*link)->r_child != NULL)
	{//the node has two child
		search_tree_node **link_sub = &((*link)->l_child);
		//search_tree_node *current_sub = *link_sub;
		
		search_tree_node *parent = NULL;
		while( ( (*link_sub)->r_child ) != NULL )
		{//find the left sub tree biggest node
			//link_sub = &(current_sub->r_child); //logic error, calculate a r_child node redundant
			parent = *link_sub;
			link_sub = &((*link_sub)->r_child);
		}
		
		(*link)->value = (*link_sub)->value; //change current sub tree root node value to left sub tree biggest node value
		
		if(parent != root && *link_sub != root)
		{
			parent->r_child = link_sub->l_child; //change node
		}
		
		free(*link_sub);
		*link_sub = NULL;

		return 1;		
	}	

	//the node just have one child
	search_tree_node *current_child;
	
	if((*link)->l_child != NULL)
	{//just have left child
		current_child = (*link)->l_child;
	}
	else
	{//just have right child 
		current_child = (*link)->r_child;
	}	

	free(*link);
	*link = current_child;
	
	return 1;

}


/*
 * *name:pre_order_tree
 */

void pre_order_tree(search_tree root,void (*search_tree_callback)(VALUE_TYPE value))
{
	if(root != NULL)
	{
		search_tree_callback(root->value);
		pre_order_tree(root->l_child,search_tree_callback);
		pre_order_tree(root->r_child,search_tree_callback);
	}
}

/*
 * *name:post_order_tree
 */

void post_order_tree(search_tree root,void (*search_tree_callback)(search_tree_node *current))
{
	if(root != NULL)
	{
		post_order_tree(root->l_child,search_tree_callback);
		post_order_tree(root->r_child,search_tree_callback);
		search_tree_callback(root);
	}
}

/*
 *name:print_node
 */

static void tree_node_print(VALUE_TYPE value)
{
	printf("%d ",value);
}


/*
 *name:free_node
 */

static void tree_node_free(search_tree_node *current)
{
	free(current);
}

/*
 * *name:search_tree_destroy
 */

void search_tree_destroy(search_tree *root)
{//use post traverse to free tree node
	if(root == NULL)
	{
		return;
	}

	search_tree_node *current = *root;
	
	post_order_tree(current,tree_node_free);

	*root = NULL;
}

int main()
{
	search_tree tree = search_tree_init();
	
	int i = 0;
	int value;
	
	for(i = 0; i < 10; i++)
	{
		scanf("%d",&value);
		
		search_tree_insert(&tree,value);
	}	

	pre_order_tree(tree,tree_node_print);
	printf("\n");

	scanf("%d",&value);
	search_tree_delete(tree,value);
	pre_order_tree(tree,tree_node_print);
	printf("\n");
	
	scanf("%d",&value);
	search_tree_delete(tree,value);
	pre_order_tree(tree,tree_node_print);
	printf("\n");
	
	scanf("%d",&value);
	search_tree_delete(tree,value);
	pre_order_tree(tree,tree_node_print);
	printf("\n");

	search_tree_destroy(&tree);
	pre_order_tree(tree,tree_node_print);

}
