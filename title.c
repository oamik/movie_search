#include "common.h"
#include "title.h"
#include "binary.h"



struct array_data *get_title( const char *path )
{
	int len;
	int nTitle;
	FILE *fp;
	char *full_path;
	const char *ending = "/title.basics.tsv";
	char line[1024];
	struct title_basics *titles;
	struct array_data *titles_data;


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

	nTitle = 0;
	while( fgets(line, sizeof(line), fp))
	{
		char titleType[100];
		char isAdult[100];
		get_column(line, titleType, 2);
		get_column(line, isAdult, 5);
		if ( strstr(titleType, "movie") && strstr(isAdult, "0"))
		{
			nTitle++;
		}
	}

	titles = malloc(nTitle * sizeof(struct title_basics));
	if( !titles )
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
		char primaryTitle[1024];
		char titleType[100];
		char isAdult[100];

		get_column(line, titleType, 2);
		get_column(line, isAdult, 5);
		if ( strstr(titleType, "movie") && strstr(isAdult, "0"))
		{
			get_column(line, tconst, 1);
			get_column(line, primaryTitle, 3);

			titles[i].tconst = strdup(tconst);
			reverse( titles[i].tconst );
			titles[i].primaryTitle = strdup(primaryTitle);

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

    titles_data = malloc(sizeof(struct array_data));
    if( !titles_data )
	{
		fprintf( stderr, "Error: Memory is full\n");
		return NULL;
	}
	titles_data->nItem = nTitle;
	titles_data->array = titles;
	titles_data->root1 = NULL;
	titles_data->root2 = NULL;

    free ( full_path );


    return titles_data;
}

void build_ptindex(struct array_data *titles)
{
	struct title_basics *tb = titles->array;

	for (int i = 0; i < titles->nItem; ++i)
	{
		add_node( &titles->root1, &(tb[i].primaryTitle), &(tb[i]));
	}
}

void build_tindex(struct array_data *titles)
{
	struct title_basics *tb = titles->array;

	for (int i = 0; i < titles->nItem; ++i)
	{
		add_node( &titles->root2, &(tb[i].tconst), &(tb[i]));
	}
}

struct title_basics *find_primary_title(struct array_data *titles, char *str)
{
	struct bst_node *node = find_node(titles->root1, str);
	if (node)
	{
		return (struct title_basics *) node->data;
	}

	return NULL;
}

struct title_basics *find_tconst(struct array_data *titles, char *str)
{
	struct bst_node *node = find_node(titles->root2, str);
	if (node)
	{
		return (struct title_basics *) node->data;
	}

	return NULL;
}

