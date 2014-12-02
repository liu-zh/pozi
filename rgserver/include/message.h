#ifndef _MESSAGE_H_
#define _MESSAGE_H_

struct node_value{
char key[20];
char value[30];
};
struct list_node{
struct list_node* prev;
struct list_node* next;
struct node_value value;
};
/****************
communicate the
metadata with 
register server
***************/
/**************
flag 201   file server regist request
flag 301   file server regist response
flag 202   file client server request
flag 203   file client release request
*************/
struct meta_msg{
char ipaddr[15];
int port;
int flag;
};
/****************
conmmunicate 
file data 
with st_server
*****************/
struct data_msg{
unsigned long size;
char start;
char filename[60];
char buffer[2048];
};

#endif
