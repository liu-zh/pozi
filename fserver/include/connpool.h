#ifndef _CONNPOOL_H_
#define _CONNPOOL_H_
#ifndef MAXCONN
#define MAXCONN 10
#endif
#include "dblist.h"
#include <pthread.h>
//pool_linklist* head;
int connnum;
pthread_t pt;
int init_pool(pool_linklist**);
struct list_mysql_node* getConn(struct list_mysql_node*);
void blockhere();
int releaseConn(struct list_mysql_node*,struct list_mysql_node*);
#endif
