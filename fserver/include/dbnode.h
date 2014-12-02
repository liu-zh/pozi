#ifndef _DBNODE_H_
#define _DBNODE_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mysql/mysql.h>

struct mysql_node{
MYSQL* mysql;
int   connectnum;
long  mills;
};
#endif
