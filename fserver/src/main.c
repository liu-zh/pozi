#include <stdio.h>
#include <string.h>
#include "../include/util.h"
#include "../include/connpool.h"
int main(){
/************
char src[10];
char dest[] = "power /PC";
last_index_of(src,dest,strlen(dest),'/');
printf("%s\n",src);

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
*********/
/*
if(!regist_self()) exit(-1);
int fd = server_listen(10100,320);
accept_fd(fd);
close(fd);
*/
/*
init_pool();
blockhere();
*/

//struct mysql_node nodes[10];
pool_linklist* head;
createDBList(&head);
int i = 0;
for(;i<1;i++){
//insertDB(head,&nodes[i]);
insertDB(head);
}
destroyDBList(head);

/*
int i = 0;
MYSQL mysql[10];
for(;i<10;i++){
printf("%d\n",mysql_init(&mysql[i]));
printf("%d\n",mysql_real_connect(&mysql[i],"192.168.1.120","pozi",
                  "pozi","pozi",3306,NULL,0));
}
*/
return 0;
}
