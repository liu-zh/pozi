#ifndef _DIRLIST_H_
#define _DIRLIST_H_
#include <malloc.h>
struct dir_node_value{
char filename[256];
};
struct dir_list_node{
struct dir_list_node* prev;
struct dir_list_node* next;
struct dir_node_value value;
};
static int size = 0;
typedef struct dir_list_node directory_linklist;
void createDirList(struct dir_list_node**);
void insertNodeDir(struct dir_list_node*,struct dir_node_value*);
void insertDir(struct dir_list_node*,const char*);
void getDirNode(struct dir_list_node*,unsigned int,struct dir_node_value*);
void destroyDirList(struct dir_list_node*);
int dirsize();

#endif
