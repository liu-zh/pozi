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
typedef struct dir_list_node config_linklist;
void createDirList(struct dir_list_node**);
void insertDir(struct dir_list_node*,struct dir_node_value*);
void getDirNodeByKey(struct dir_list_node*,struct dir_node_value*);
void getDirNode(struct dir_list_node*,unsigned int,struct dir_node_value*);
void destroyDirList(struct dir_list_node*);

#endif
