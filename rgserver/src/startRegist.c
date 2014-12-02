#include "../include/startRegist.h"
void* startR(void* arg){
printf("start regist server threac!\n");
asyn_accept_regist((regist_linklist*)arg);
}
void* startD(void* arg){
printf("start distribuet thread!\n");
asyn_accept_distribute((regist_linklist*)arg);
}

void startServer(){
pthread_t pttr;
pthread_t pttd;
regist_linklist* head;
createRegistList(&head);
pthread_create(&pttr,NULL,startR,head);
pthread_create(&pttd,NULL,startD,head);
pthread_join(pttr,NULL);
pthread_join(pttd,NULL);
destroyRegistList(head);
}
