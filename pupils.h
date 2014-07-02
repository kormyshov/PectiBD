#ifndef __pupils_h__
#define __pupils_h__

#include "header.h"

int print_similary_pupil(void *, int , char **, char **);
void menu_add_pupil();

void menu_load_pupil();
void add_pupil(char[], char[], char[], char[], char[], char[], char[], int);

bool is_similary_surname(const char*, const char*);

int add_surname(void *, int , char **, char **);
std::vector<std::pair<std::string, std::string> > get_surnames();

#endif

