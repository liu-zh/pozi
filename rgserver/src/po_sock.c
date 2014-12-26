#include "../include/po_sock.h"
/***********************
listen the port
*********************/
int server_listen(const int port,const int backlog,int nonblock){

int servfd;
struct sockaddr_in servaddr;
if((servfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
printf("create socket fd error %s\n",strerror(errno));
exit(-2);
}

if(nonblock) setnonblock(servfd);
bzero(&servaddr,sizeof(struct sockaddr_in));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(port);
if(bind(servfd,(struct sockaddr*)&servaddr,sizeof(struct sockaddr_in)) == -1){
printf("st server bind error %s %d\n",strerror(errno),servfd);
close(servfd);
exit(-1);
}
printf("bind successfully\n");

if(listen(servfd,backlog) == -1){
printf("listen error %d %s\n",port,strerror(errno));
close(servfd);
exit(-1);
}
printf("start server on port %d\n",port);

return servfd;
}
/*****************************/
int client_connect(const char* ipaddr,const int port){
int cliefd;
struct sockaddr_in clieaddr;

if((cliefd = socket(AF_INET,SOCK_STREAM,0)) == -1){
printf("client create socket error %s\n",strerror(errno));
exit(-1);
}
bzero(&clieaddr,sizeof(struct sockaddr_in));

clieaddr.sin_family = AF_INET;
clieaddr.sin_addr.s_addr = inet_addr(ipaddr);
clieaddr.sin_port = htons(port);
if(connect(cliefd,(const struct sockaddr*)&clieaddr,sizeof(struct sockaddr_in)) == -1){
printf("connect to server failed! %s\n",strerror(errno));
exit(-1);
}

return cliefd;
}
/**********************************/
int setnonblock(int sockfd)
{
    if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1){
        return -1;
    }
    return 0;
}
