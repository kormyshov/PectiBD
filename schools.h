#ifndef __schools_h__
#define __schools_h__

#include "header.h"

void menu_add_school();
void menu_del_school();
void menu_print_schools();

int add_school_name(void *, int , char **, char **);
int print_schools(void *, int , char **, char **);

bool is_similary_school(const char *, const char *);

#endif
