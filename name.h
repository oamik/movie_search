#ifndef  _NAME_H_
#define _NAME_H_


struct name_basics
{
	char *nconst;
	char *primaryName;
};


struct array_data *get_name(const char *);
void build_nindex(struct array_data *names);
void build_pnindex(struct array_data *names);
struct name_basics *find_primary_name(struct array_data *names, char *str);
struct name_basics *find_nconst(struct array_data *names, char *str);





#endif
