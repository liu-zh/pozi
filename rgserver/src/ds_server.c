#include "../include/ds_server.h"

int asyn_accept_distribute(regist_linklist* head){
int servfd = server_listen(10999,320,1);
int epollfd;
struct meta_msg buf;
//struct regist_linklist *head;
//createList(&head);
struct regist_node *current = head;
epollfd = epoll_create(320);
struct epoll_event ev;
struct epoll_event events[100];

ev.events = EPOLLIN|EPOLLET;
ev.data.fd = servfd;
if(epoll_ctl(epollfd,EPOLL_CTL_ADD,servfd,&ev) < 0){
printf("could not add the listen fd into the epoll list %s\n",strerror(errno));
exit(-2);
}
int readyfd = 0;
struct sockaddr_in clientaddr;
socklen_t socklen = sizeof(struct sockaddr_in);
while(1){
readyfd = epoll_wait(epollfd,events,320,-1);
if(readyfd == -1){
printf("epoll wait error %s\n",strerror(errno));
exit(-1);
}
int i = 0;
for(;i<readyfd;i++){
if(events[i].data.fd == servfd){
int clientfd = accept(servfd,(struct sockaddr*)&clientaddr,&socklen);
if(clientfd == -1){
printf("accept error %s\n",strerror(errno));
continue;
                  }
else{
printf("accept connect from %s\n",inet_ntoa(clientaddr.sin_addr));
     }
}
else if(events[i].events&EPOLLIN){
/**************************
handle the read event 
************************/
memset(&buf,'\0',sizeof(struct meta_msg));
read(events[i].data.fd,&buf,sizeof(struct meta_msg));
if(buf.flag == 202){
memset(&buf,'\0',sizeof(struct meta_msg));
if(!current) current = head;
else{
current = current->next;
}
write(events[i].data.fd,current->value,sizeof(struct meta_msg));
}else
  printf("get server request command error\n");
                                   }
else if(events[i].events&EPOLLOUT){
/**********************
handle the write event
**********************/

                                   }
                   }
        }
close(servfd);
//destroyList(head);
}
