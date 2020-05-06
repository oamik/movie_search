#ifndef _COMMON_H_
#define _COMMON_H_


#include <stdio.h>
#include <string.h>
#include <malloc.h>



struct array_data
{
	int nItem;
	void *array;	
	struct bst_node *root1;
	struct bst_node *root2;
};


void get_column(char *line, char *dest, int ncol);
void reverse(char *str);



#endif
