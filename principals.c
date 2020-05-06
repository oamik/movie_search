#include "common.h"
#include "principals.h"
#include "binary.h"




struct array_data *get_principals( const char *path )
{
	int len;
	int nPrincipal;
	FILE *fp;
	char *full_path;
	const char *ending = "/title.principals.tsv";
	char line[1024];
	struct title_principals *principals;
	struct array_data *principals_data;


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

	nPrincipal = 0;
	while( fgets(line, sizeof(line), fp))
	{
		char category[100];
		get_column(line, category, 4);
		// printf("%s\n", isAdult );
		if ( strstr(category, "actor"))
		{
			nPrincipal++;
		}
	}
		// fprintf( stderr, "nPrincipal: %d\n", nPrincipal);

	principals = malloc(nPrincipal * sizeof(struct title_principals));
	if( !principals )
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
		char tconst[100];
		char nconst[100];
		char category[100];
		char characters[1024];

		get_column(line, category, 4);
		
		if ( strstr(category, "actor") )
		{
			get_column(line, tconst, 1);
			get_column(line, nconst, 3);
			get_column(line, characters, 6);;

			principals[i].tconst = strdup(tconst);
			reverse(principals[i].tconst);

			principals[i].nconst = strdup(nconst);
			reverse(principals[i].nconst);

			principals[i].characters = strdup(characters);
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

    principals_data = malloc(sizeof(struct array_data));
    if( !principals_data )
	{
		fprintf( stderr, "Error: Memory is full\n");
		return NULL;
	}
	principals_data->nItem = nPrincipal;
	principals_data->array = principals;
	principals_data->root1 = NULL;
	principals_data->root2 = NULL;

    free ( full_path );


    return principals_data;
}

void build_tindex_tp(struct array_data *principals)
{
	struct title_principals *tps = principals->array;

	for (int i = 0; i < principals->nItem; ++i)
	{
		add_node( &principals->root1, &(tps[i].tconst), &(tps[i]));
	}
}

void build_nindex_tp(struct array_data *principals)
{
	struct title_principals *tps = principals->array;

	for (int i = 0; i < principals->nItem; ++i)
	{
		add_node( &principals->root2, &(tps[i].nconst), &(tps[i]));
	}
}


struct bst_node *find_nconst_tp(struct array_data *prin, char *str)
{
	struct bst_node *node = find_node(prin->root2, str);

	return node;
}


struct bst_node *find_tconst_tp(struct array_data *prin, char *str)
{
	struct bst_node *node = find_node(prin->root1, str);

	return node;
}


