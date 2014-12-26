#ifndef _RELIST_H_
#define _RELIST_H_
#include "message.h"
#include <stdio.h>
struct regist_node{
struct regist_node* prev;
struct regist_node* next;
struct meta_msg   value;
};
typedef struct regist_node regist_linklist;
void createRegistList(struct regist_node**);
void insertRegist(struct regist_node*,struct meta_msg*);
//void getNodeByKey(struct regist_node*,struct meta_msg*);
void getRegistNode(struct regist_node*,unsigned int,struct meta_msg*);
void destroyRegistList(struct regist_node*);
#endif
