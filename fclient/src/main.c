#include <stdio.h>
#include <string.h>
#include "../include/util.h"
int main(){
/************
char src[10];
char dest[] = "power /PC";
last_index_of(src,dest,strlen(dest),'/');
printf("%s\n",src);
*************/
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
return 0;
}
