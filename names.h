#ifndef __names_h__
#define __names_h__

#include "header.h"

void menu_add_name();
void menu_del_name();
void menu_print_names();

bool is_similary_name(const char *, const char *);
int add_list_name(void *, int , char **, char **);
int print_names(void *, int , char **, char **);

std::vector<std::pair<std::string,std::string> > get_names();

#endif
