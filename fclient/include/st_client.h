#ifndef _ST_CLIENT_H_
#define _ST_CLIENT_H_
#include "po_sock.h"
#include "message.h"
#define SENDNAME 0x3
#define SENDDATA 0x7
#define SENDEND  0xf
#define SENDFIN  0x10
//char send_buffer[2048];
char filename[60];
struct data_msg databuf;
int send_file(int clientfd,const char*);
int send_fin(int clientfd);
#endif

