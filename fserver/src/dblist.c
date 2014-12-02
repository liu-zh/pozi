#include "../include/dblist.h"
void createDBList(struct list_mysql_node** head){
*head = malloc(sizeof(struct list_mysql_node));
}
/********************/
void insertDB(struct list_mysql_node* head){
static int g = 0;
if(!head){
printf("Linklist be not initialized\n");
exit(-1);
}
struct list_mysql_node* p;
struct list_mysql_node* q;
p = head;
printf("----------and and here--------\n");
while(q = p->next){
printf("************song****%d*****\n",g++);
p = p->next;
}
printf("-----------and here--------\n");
struct list_mysql_node* n = 
       (struct list_mysql_node*)malloc(sizeof(struct list_mysql_node));
printf("----------here--------\n");
//n->value = v;
mysql_init(&n->mysql);
printf("%d\n",mysql_real_connect(&n->mysql,"192.168.1.120","pozi",
                  "pozi","pozi",3306,NULL,0));
time_t tt;
time(&tt);
n->mills = tt;
p->next = n;
current = p->next;
printf("ax %d\n",g++);
n->prev = p;
}
/*********************/
void destroyDBList(struct list_mysql_node* head){
struct list_mysql_node* curr = head;
while(curr){
struct list_mysql_node* n = curr->next;
free(curr);
//if(!curr->value)
//free(curr->value);
//if(curr->mysql)
mysql_close(&curr->mysql);
curr = n;
}
printf("destroy the list\n");
}
/*********************/
struct list_mysql_node* next_DB_node(struct list_mysql_node* head){
if(!current)
current = head->next;
return current;
}
/************************/
void travelDB(struct list_mysql_node* head){
printf("check connect alive every five minutes......\n");
struct list_mysql_node* curr = head->next;
while(curr){
maintain_connect(curr);
curr = curr->next;
}
}
