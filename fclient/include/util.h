#ifndef _UTIL_H_
#define _UTIL_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include "polist.h"
#include "dirlist.h"
/******************
get the value after
the last a character
****************/
//char namebuf[256];
int last_index_of(char* src,const char* dest,int destlen,char a);
/*****************/
void analyze_config(const char*,config_linklist*);
/*****************/
int obtain_file_list(struct dir_list_node*,const char*);
/****************/
int recurve_scan_dir(struct dir_list_node*,const char*);
#endif
