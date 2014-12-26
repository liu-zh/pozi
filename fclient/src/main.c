#include <stdio.h>
#include <string.h>
#include "../include/util.h"
#include "../include/obtain_service.h"
int main(int argc,char* argv[]){
/************
char src[10];
char dest[] = "power /PC";
last_index_of(src,dest,strlen(dest),'/');
printf("%s\n",src);
*************/
/***************
config_linklist* head;
createList(&head);
analyze_config("config/server.ini",head);
struct node_value nv;
strcpy(nv.key,"server.port");
getNodeByKey(head,&nv);
printf("%s\n",nv.value);
strcpy(nv.key,"backlog");
getNodeByKey(head,&nv);
printf("%s\n",nv.value);
destroyList(head);
****************/
struct meta_msg mmsg;
if(!ob_service(&mmsg,"192.168.81.129",10999)){
printf("obtain service failed!\n");
exit(-3);
};
printf("obtain service to %s,%d\n",mmsg.ipaddr,mmsg.port);
directory_linklist *head;
createDirList(&head);
obtain_file_list(head,"/home/hadoop/pozi");
int cliefd = client_connect("192.168.81.129",10010);
printf("finished!\n");
if(head){
struct dir_list_node* cur = head->next;
int index = 0;
while(cur&&index++<dirsize()){
printf("%s\n",cur->value.filename);
send_file(cliefd,cur->value.filename);
cur = cur->next;
}
}
close(cliefd);
destroyDirList(head);

/*********
if(argc != 2){
printf("Usage ./st_client fullfilepath\n");
exit(-2);
}
int cliefd = client_connect("192.168.81.129",10010);
send_file(cliefd,argv[1]);
send_fin(cliefd);
close(cliefd);
*********/

return 0;
}
