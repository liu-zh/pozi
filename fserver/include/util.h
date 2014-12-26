#ifndef _UTIL_H_
#define _UTIL_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "polist.h"
/******************
 get the value after
 the last a character
 ****************/
int last_index_of(char* src, const char* dest, int destlen, char a);
/*****************/
void analyze_config(const char*, config_linklist*);
/****************/
int getLocalIp(char*);
/****************/
int createdir(const char*);
#endif
