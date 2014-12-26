#ifndef _POLIST_H_
#define _POLIST_H_
#include <malloc.h>
#include "message.h"
/*
struct node_value{
char key[20];
char value[30];
};
struct list_node{
struct list_node* prev;
struct list_node* next;
struct node_value value;
};
*/
typedef struct list_node config_linklist;
void createList(struct list_node**);
void insert(struct list_node*,struct node_value*);
void getNodeByKey(struct list_node*,struct node_value*);
void getNode(struct list_node*,unsigned int,struct node_value*);
void destroyList(struct list_node*);

#endif
