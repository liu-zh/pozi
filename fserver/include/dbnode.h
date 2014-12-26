#ifndef _DBNODE_H_
#define _DBNODE_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mysql/mysql.h>
struct list_mysql_node{
struct list_mysql_node* prev;
struct list_mysql_node* next;
//struct mysql_node* value;
MYSQL* mysql;
long mills;
};
struct mysql_node{
MYSQL* mysql;
//int   connectnums;
long  mills;
char  isFree;
};
#endif
