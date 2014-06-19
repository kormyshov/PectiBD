#ifndef __seasons_h__
#define __seasons_h__

#include "header.h"

void menu_add_season();
void menu_del_season();
void menu_print_seasons();

int print_seasons(void *, int , char **, char **);

int add_season(void *, int , char **, char **);
std::vector<std::pair<std::string,std::string> > get_seasons();

#endif


