#ifndef _MESSAGE_H_
#define _MESSAGE_H_
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
