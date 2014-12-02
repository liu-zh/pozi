#ifndef _CONNPOOL_H_
#define _CONNPOOL_H_
#ifndef MAXCONN
#define MAXCONN 10
#endif
#include "dblist.h"
#include <pthread.h>
pool_linklist* nhead;
int connnum;
pthread_t pt;
int init_pool();
struct list_mysql_node* getConn();
void blockhere();
int releaseConn();
#endif
