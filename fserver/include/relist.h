#ifndef _RELIST_H_
#define _RELIST_H_
#include "message.h"
struct list_node {
	struct list_node* prev;
	struct list_node* next;
	struct meta_msg value;
};
typedef struct list_node regist_linklist;
void createList(struct list_node**);
void insert(struct list_node*, struct meta_msg*);
//void getNodeByKey(struct list_node*,struct meta_msg*);
void getNode(struct list_node*, unsigned int, struct meta_msg*);
void destroyList(struct list_node*);
#endif
