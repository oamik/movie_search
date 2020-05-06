#ifndef _TITLE_H_
#define _TITLE_H_


struct title_basics
{
	char *tconst;
	char *primaryTitle;
};


struct array_data *get_title( const char *path );
void build_ptindex(struct array_data *titles);
void build_tindex(struct array_data *titles);

struct title_basics *find_primary_title(struct array_data *titles, char *str);
struct title_basics *find_tconst(struct array_data *titles, char *str);


#endif
