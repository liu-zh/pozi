#ifndef _ST_SERVER_H_
#define _ST_SERVER_H_
#include "po_sock.h"
#include "message.h"
#include "util.h"
#include <pthread.h>
#define SENDNAME 0x3
#define SENDDATA 0x7
#define SENDEND  0xf
#define SENDFIN  0x10
#ifndef STPORT
#define STPORT 10010
#endif
#ifndef STBACKLOG
#define STBACKLOG 100
#endif
char ip4[15];
struct data_msg databuf;
/**************************/
int regist_self();
/************************/
int accept_fd(int serverfd,const char*);
/************************/
int init_server(const char* receivedir);
/*************************/
#endif
