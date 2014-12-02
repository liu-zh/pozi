#ifndef _PO_SOCK_H_
#define _PO_SOCK_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
/***************
common accept the connect
from client 
and return the
file description of
server 
********************/
int server_listen(const int port,const int backlog,int nonblock);
int client_connect(const char* ipaddr,const int port);
int setnonblock(int sockfd);
#endif
