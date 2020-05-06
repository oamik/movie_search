#ifndef _BINARY_H_
#define _BINARY_H_



struct bst_node
{
	char *key;
	void *data;
	struct bst_node *left;
	struct bst_node *right;
};


void add_node(struct bst_node **root, char **str, void *row);
struct bst_node *find_node(struct bst_node *root, char *str );

void print_node1(struct bst_node *root);
void print_node2(struct bst_node *root);
void print_node3(struct bst_node *root);


#endif