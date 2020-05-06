#include "common.h"
#include "name.h"
#include "binary.h"



struct array_data *get_name(const char *path)
{
	int len;
	int nActor;
	FILE *fp;
	char *full_path;
	const char *ending = "/name.basics.tsv";
	char line[1024];
	struct name_basics *actors;
	struct array_data *names_data;



	len = strlen(path) + strlen(ending) + 1;
	full_path = malloc(len);
	if ( !full_path )
	{
		fprintf( stderr, "Error: Memory is full\n");
		return NULL;
	}
	strcpy(full_path, path);
	strcat(full_path, ending);

	fp = fopen(full_path, "r");
	if( !fp )
	{
		fprintf( stderr, "Error: Could not open file\n");
		return NULL;
	}

	nActor = 0;
	while( fgets(line, sizeof(line), fp))
	{
		char col[100];
		get_column(line, col, 5);
		if ( strstr(col, "actor") || strstr(col, "actress"))
		{
			nActor++;
		}
	}
	actors = malloc(nActor * sizeof(struct name_basics));
	if( !actors )
	{
		fprintf( stderr, "Error: Memory is full\n");
		return NULL;
	}
	if ( fseek(fp, 0, SEEK_SET) )
	{
		fprintf( stderr, "Error: could not rewind file\n");
		return NULL;
	}
	for( int i = 0; fgets(line, sizeof(line), fp); )
	{
		char col1[100];
		char col2[100];
		char col5[100];
		get_column(line, col5, 5);
		if ( strstr(col5, "actor") || strstr(col5, "actress"))
		{
			get_column(line, col1, 1);
			get_column(line, col2, 2);
			actors[i].nconst = strdup(col1);
			reverse(actors[i].nconst);
			actors[i].primaryName = strdup(col2);
			i++;
		}
	}
	if (ferror(fp))
	{
		fprintf( stderr, "Error: reading file was unsuccessful\n");
		return NULL;
	}
	if( fclose( fp ))
	{
		fprintf( stderr, "Error: Can't close the file\n"); 
     	return NULL;
    }

    names_data = malloc(sizeof(struct array_data));
    if( !names_data )
	{
		fprintf( stderr, "Error: Memory is full\n");
		return NULL;
	}
	names_data->nItem = nActor;
	names_data->array = actors;
	names_data->root1 = NULL;
	names_data->root2 = NULL;


    free ( full_path );


    return names_data;
}

void build_nindex(struct array_data *names)
{
	struct name_basics *nb = names->array;

	for (int i = 0; i < names->nItem; ++i)
	{
		add_node( &names->root1, &(nb[i].primaryName), &(nb[i]));
	}
}

void build_pnindex(struct array_data *names)
{
	struct name_basics *nb = names->array;

	for (int i = 0; i < names->nItem; ++i)
	{
		add_node( &names->root2, &(nb[i].nconst), &(nb[i]));
	}
}

struct name_basics *find_primary_name(struct array_data *names, char *str)
{
	struct bst_node *node = find_node(names->root1, str);
	if (node)
	{
		return (struct name_basics *) node->data;
	}

	return NULL;
}

struct name_basics *find_nconst(struct array_data *names, char *str)
{
	struct bst_node *node = find_node(names->root2, str);
	if (node)
	{
		return (struct name_basics *) node->data;
	}

	return NULL;
}

