#include "../include/connpool.h"
void* checkAlive(void* nhead);

void* checkAlive(void* nhead){
pool_linklist* pl = (pool_linklist*)nhead;
time_t tm;
time(&tm);
time_t tt;
while(1){
time(&tt);
long inv = tt - tm;
if(inv > 300000){
tm = tt;
travelDB(pl);
                            }
        }
}
int init_pool(){

createDBList(&nhead);
int i = 0;

struct mysql_node mnode[MAXCONN];
//     = malloc(MAXCONN * sizeof(int));

time_t tt;
time(&tt);
printf("current time %ld\n",tt);
MYSQL mysql[MAXCONN];
int res = 0;
for(;i < MAXCONN;i++){
/*
printf("%d\n",mysql_init(&mysql[i]));

printf("%d\n",mysql_real_connect(&mysql[i],"192.168.1.120","pozi",
                  "pozi","pozi",3306,NULL,0));
*/

//mnode[i] = (struct mysql_node*)malloc(sizeof(struct mysql_node));
/*
mnode[i].mysql = &mysql[i];
mnode[i].mills = tt;
printf("construct node complete\n");
*/
insertDB(nhead);
printf("insert finished!\n");
}
connnum = MAXCONN;
printf("create %d connections\n",MAXCONN);
pthread_create(&pt,NULL,checkAlive,nhead);
//pthread_join(pt,NULL);
}
void blockhere(){
pthread_join(pt,NULL);
}
struct list_mysql_node* getConn(){
if(connnum-- <= 0) return NULL;
return next_DB_node(nhead);
}
int releaseConn(){
connnum++;
}
