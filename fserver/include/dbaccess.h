#ifndef _DBACCESS_H_
#define _DBACCESS_H_
#include "dbnode.h"
#include "dblist.h"
#ifndef CONNINTERVAL
#define CONNINTERVAL 1000*60*5;
#endif
int execute_sql(const char*,struct list_mysql_node*);

int maintain_connect(struct list_mysql_node*);
#endif
