#include "common.h"
#include "binary.h"
#include "principals.h"
#include "title.h"
#include "name.h"




void add_node(struct bst_node **root, char **str, void *row)
{
	if (*root)
	{
		if (strcmp(*str, (*root)->key) < 0)
		{

			add_node( &((*root)->left), str, row );
		}
		else
		{

			add_node( &((*root)->right), str, row );
		}
	}
	else
	{
    	(*root) = malloc( sizeof( struct bst_node ) );
    	if ( ! *root )
    	{
    		fprintf(stderr, "Memory is full\n");
    		return;
    	}

    	(*root)->key = *str;
    	(*root)->data = row;
    	(*root)->left = NULL;
    	(*root)->right = NULL;
	}

}


void print_node1(struct bst_node *root)
{
	if (root)
	{
		printf("%s\n", root->key );
		printf("%s\t", ((struct title_basics *) root->data)->tconst);
		printf("%s\n", ((struct title_basics *) root->data)->primaryTitle );
		
		print_node1(root->left);
		print_node1(root->right);
	}
}

void print_node2(struct bst_node *root)
{
	if (root)
	{
		printf("%s\n", root->key );
		printf("%s\t",  ((struct name_basics *) root->data)->nconst);
		printf("%s\n",  ((struct name_basics *) root->data)->primaryName );
		
		print_node2(root->left);
		print_node2(root->right);
	}
}

void print_node3(struct bst_node *root)
{
	if (root)
	{
		printf("key: %s\n", root->key );
		printf("nc: %s\t",  ((struct title_principals *) root->data)->nconst);
		printf("tc: %s\t",  ((struct title_principals *) root->data)->tconst );
		printf("ch: %s\n",  ((struct title_principals *) root->data)->characters );
		
		print_node3(root->left);
		print_node3(root->right);
	}
}

struct bst_node *find_node(struct bst_node *root, char *str)
{
	if ( root )
	{
		if ( strcmp(root->key, str) == 0 )
		{
			return root;
		}
		else
		{
			if ( strcmp(str, root->key) < 0 )
			{
				return find_node(root->left, str);
			}
			else
			{
				return find_node(root->right, str);
			}
		}
	}
	else
	{
		return NULL;
	}
}

