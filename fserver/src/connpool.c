#include "../include/connpool.h"
void* checkAlive(void* nhead);

void* checkAlive(void* nhead) {
	pool_linklist* pl = (pool_linklist*) nhead;
	time_t tm;
	time(&tm);
	time_t tt;
	while (1) {
		time(&tt);
		long inv = tt - tm;
//printf("check inteval %ld\n",inv);
		if (inv > 3) {
			printf("every 3 minutes executed \n");
			tm = tt;
			travelDB(pl);
		}
	}
}
int init_pool(pool_linklist** head) {

	createDBList(head);
	int i = 0;
	MYSQL mysql[MAXCONN];

	for (; i < MAXCONN; i++) {
		printf("init mysql %d\n", mysql_init(&mysql[i]));
		if (!mysql_real_connect(&mysql[i], "10.100.30.154", "pozi", "pozi",
				"pozi", 3306, NULL, 0)) {
			printf("can not connect to mysql\n");
			exit(-3);
		}
	}
	i = 0;
	for (; i < MAXCONN; i++) {
		insertDB(*head, &mysql[i]);
	}
	connnum = MAXCONN;
	pthread_create(&pt, NULL, checkAlive, *head);
}
/************************************/
void blockhere() {
	pthread_join(pt, NULL);
}
/*************************/
struct list_mysql_node* getConn(struct list_mysql_node* head) {
	if (connnum-- <= 0)
		return NULL;
	printf("get connetion from pool %d\n", connnum);
	return get_free_node(head);
}
int releaseConn(struct list_mysql_node* head, struct list_mysql_node* nd) {
	insertDBNode(head, nd);
	connnum++;
	printf("release connection to pool %d\n", connnum);
}
