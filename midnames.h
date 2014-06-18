#ifndef __midnames_h__
#define __midnames_h__

#include "header.h"

void menu_add_midname();
void menu_del_midname();
void menu_print_midnames();

bool is_similary_midname(const char *, const char *);
int add_list_midname(void *, int , char **, char **);
int print_midnames(void *, int , char **, char **);

#endif

