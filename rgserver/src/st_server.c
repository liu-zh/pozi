#include "../include/st_server.h"
void* syn_connect(void* arg);
/**************************/
void* syn_connect(void* arg){
int sfd = *((int*)arg);
printf("server start to handle the connect\n");
write(sfd,"response",strlen("response"));
free(arg);
close(sfd);
return (void*)0;
}

int accept_fd(int serverfd){

struct sockaddr_in clientaddr;
pthread_t pht;
int socklen_t = sizeof(struct sockaddr_in);
int cfd;
while(1){

cfd = accept(serverfd,(struct sockaddr*)&clientaddr,&socklen_t);
if(cfd == -1){
printf("accept the connection error %s\n",strerror(errno));
continue;
}else{
printf("accept cennnection from %s %d\n",inet_ntoa(clientaddr.sin_addr),cfd);
int* clientfd = malloc(sizeof(int));
*clientfd = cfd;
pthread_create(&pht,NULL,syn_connect,clientfd);
}
}
}
/*******************/

/*******************
int main(int argc,char** argv){

int fd = server_listen(STPORT,STBACKLOG);
accept_fd(fd);
close(fd);


return 0;
}
*/
