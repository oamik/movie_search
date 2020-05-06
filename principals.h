#ifndef _PRINCIPALS_H_
#define _PRINCIPALS_H_


struct title_principals
{
	char *tconst;
	char *nconst;
	char *characters;
};

struct array_data *get_principals( const char *path );
void build_tindex_tp(struct array_data *principals);
void build_nindex_tp(struct array_data *principals);
struct bst_node *find_nconst_tp(struct array_data *prin, char *str);
struct bst_node *find_tconst_tp(struct array_data *prin, char *str);




#endif
