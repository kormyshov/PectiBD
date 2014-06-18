#ifndef __common_h__
#define __common_h__

#include "header.h"

extern std::string fname;
extern sqlite3 *db;

void print_string(const char *, int );
int DMcost(char , char );
int DMdistance(const char *, const char *);

#endif
