#include "../include/scheduler.h"
void* start_rg(void* args);
void* start_ds(void* args);

void* start_rg(void* args) {
	regist_linklist* rlist = (regist_linklist*) args;
	printf("start regist server threac!\n");
	asyn_accept_regist(rlist);
	return (void*) 0;
}
void* start_ds(void* args) {
	printf("start distribuet thread!\n");
	asyn_accept_distribute((regist_linklist*) args);
	return (void*) 0;
}
int scheduler() {
	pthread_t ptrg;
	pthread_t ptds;
	struct regist_linklist *head;
	createList(&head);

	pthread_create(&ptrg, NULL, start_rg, head);
	pthread_create(&ptds, NULL, start_ds, head);
	pthread_join(ptrg, NULL);
	pthread_join(ptds, NULL);
	return 1;
}
