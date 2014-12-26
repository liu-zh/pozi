#include <stdio.h>
#include <string.h>
#include "../include/util.h"
#include "../include/connpool.h"
#include "../include/dbaccess.h"
#include "../include/ft_server.h"

void query_show(void* arg){
MYSQL_RES* res = (MYSQL_RES*)arg;
MYSQL_ROW row;
 while((row = mysql_fetch_row(res)))
        { 

             printf("id = %d \n",row[0]);
             printf("Type = %s \n",row[1]);
        }
 mysql_free_result(res);
}
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
//regist_self();
/*
if(!regist_self()) exit(-1);
int fd = server_listen(10100,320);
accept_fd(fd);
close(fd);
*/
/*
if(!regist_self()) exit(-1);
config_linklist* confighead;
createList(&confighead);
analyze_config("config/server.ini",confighead);
struct node_value nvport;
strcpy(nvport.key,"server.port");
getNodeByKey(confighead,&nvport);
printf("server port: %s\n",nvport.value);

struct node_value nvdir;
strcpy(nvdir.key,"server.dir");
getNodeByKey(confighead,&nvdir);
printf("save file directory: %s\n",nvdir.value);


struct node_value nvbacklog;
strcpy(nvbacklog.key,"server.backlog");
getNodeByKey(confighead,&nvbacklog);
printf("backlog: %s\n",nvbacklog.value);

init_server(nvdir.value);
int fd = server_listen(atoi(nvport.value),
                       atoi(nvbacklog.value),0);
init_server(nvdir.value);
accept_fd(fd,nvdir.value);
close(fd);
destroyList(confighead);
*/

/*
init_pool();
blockhere();
*/
/*
pool_linklist* head;
createDBList(&head);
int i = 0;
for(;i<10;i++){
insertDB(head);
}

destroyDBList(head);
*/
/*
int i = 0;
MYSQL mysql[10];
for(;i<10;i++){
printf("%d\n",mysql_init(&mysql[i]));
printf("%d\n",mysql_real_connect(&mysql[i],"10.100.30.154","pozi",
                  "pozi","pozi",3306,NULL,0));
}
pool_linklist* head;
createDBList(&head);
i = 0;
for(;i<10;i++){
insertDB(head,&mysql[i]);
}

sleep(20);
destroyDBList(head);
*/
/*
pool_linklist* head;
init_pool(&head);

struct list_mysql_node* lmn = getConn(head);
execute_sql("select pozi_id,pozi_name from pozi_test",lmn,query_show);
releaseConn(head,lmn);

blockhere();
*/
/***********
char ip[15];
getLocalIp(ip);
printf("local ip %s\n",ip);
************/
/*****
init_server("/home/hadoop/receive");
accept_fd();
*****/
start_server();
return 0;
}
