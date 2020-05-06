#include "common.h"
#include "name.h"
#include "title.h"
#include "principals.h"
#include "binary.h"




int main(int argc, char const *argv[])
{
	struct name_basics *name;
	struct title_basics *title;
	struct title_principals *princpl;

	struct array_data *pname;
	struct array_data *ptitle;
	struct array_data *pprincipals;

	if (argc != 2)
	{
		fprintf( stderr, "Usage: %s directory\n", argv[0] );
		return -1;
	}

	pname = get_name(argv[1]);
	ptitle = get_title(argv[1]);
	pprincipals = get_principals(argv[1]);


	build_ptindex(ptitle); 

	build_nindex(pname);

	build_tindex(ptitle);

	build_pnindex(pname);

	build_tindex_tp(pprincipals);

	build_nindex_tp(pprincipals);


struct bst_node *found = NULL;
title = NULL;
princpl = NULL;
name = NULL;

int choice = 0;
char line[1024];
char nameOrTitle[1024];

printf("> ");
fgets( line, sizeof(line), stdin );


char *cmd = line;
while(*cmd)
{
	if(*cmd != ' ') break;
	cmd++;
}

if (*cmd == 'n')
{
	choice = 1;
	cmd += 4;
}
else if (*cmd = 't')
{
	choice = 0;
	cmd += 5;
}
else{
	fprintf(stderr, "Error: Wrong input\n");
	return 1;
}

while(*cmd)
{
	if(*cmd != ' ') break;
	cmd++;
}

int i, k;
for(i = 0; *cmd != '\n'; ++i)
{
	nameOrTitle[i] = *cmd;
	cmd++;
}
nameOrTitle[i] = '\0';
cmd--;

for (k = i-1; *cmd == ' '; k--)
{
	cmd--;
}
nameOrTitle[k+1] = '\0';

char *arg = strdup(nameOrTitle);

if( choice == 0 ){

	title = find_primary_title( ptitle, nameOrTitle );
	if(title)
	{
		found = find_tconst_tp(pprincipals, title->tconst);
		while(found)
		{
			name = NULL;
			princpl = NULL;

	 		princpl = found->data;

	 		if (princpl)
	 		{
	 			name = find_nconst(pname, princpl->nconst);
	 		}
	 		if (name)
	 		{
				printf( "%s : %s\n", name->primaryName, princpl->characters );
	 		}


			found = find_node(found->right, title->tconst);
		}

	}
}
else if (choice == 1)
{
	name = find_primary_name( pname, nameOrTitle);
	if(name)
	{
		found = find_nconst_tp( pprincipals, name->nconst );
		
		while(found)
		{
			title = NULL;
			princpl = NULL;
			princpl = found->data;

			if(princpl)
			{
				title = find_tconst( ptitle, princpl->tconst );
			}
			if(title)
			{
				printf( "%s : %s\n", title->primaryTitle, princpl->characters );
			}

			found = find_node( found->right, name->nconst );
		}
	} 	
}	

	return 0;
}
