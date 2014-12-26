#include "../include/dblist.h"
void createDBList(struct list_mysql_node** head){
numbers = 0;
pthread_mutex_init(&pmt);
pthread_mutex_lock(&pmt);
*head = malloc(sizeof(struct list_mysql_node));
pthread_mutex_unlock(&pmt);
}
/********************/
void insertDB(struct list_mysql_node* head,MYSQL* msql){

if(!head){
printf("Linklist be not initialized\n");
exit(-1);
}
pthread_mutex_lock(&pmt);
struct list_mysql_node* p;
struct list_mysql_node* q;
p = head;
while(q = p->next){
p = p->next;
}
struct list_mysql_node* n = 
       (struct list_mysql_node*)malloc(sizeof(struct list_mysql_node));
n->mysql = msql;

time_t tt;
time(&tt);
n->mills = tt;
p->next = n;
current = p->next;
numbers++;
n->prev = p;
pthread_mutex_unlock(&pmt);
}
/*********************/
void destroyDBList(struct list_mysql_node* head){
pthread_mutex_lock(&pmt);
struct list_mysql_node* curr = head;
while(curr){
struct list_mysql_node* n = curr->next;
free(curr);
mysql_close(curr->mysql);
curr = n;
}
printf("destroy the list\n");
pthread_mutex_unlock(&pmt);
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
//printf("-----------------------\n");
}
}
/*****************************/
struct list_mysql_node* get_free_node(struct list_mysql_node* head){
pthread_mutex_lock(&pmt);
if(!head) return NULL;
if(!head->next) return NULL;
struct list_mysql_node* release_node = head->next;
head->next = head->next->next;
release_node->next = NULL;
pthread_mutex_unlock(&pmt);
return release_node;
}
/*****************************/
void insertDBNode(struct list_mysql_node* head,struct list_mysql_node* nd){
if(!head){
printf("Linklist be not initialized\n");
exit(-1);
}
pthread_mutex_lock(&pmt);
struct list_mysql_node* p;
struct list_mysql_node* q;
p = head;
while(q = p->next){
p = p->next;
}
p->next = nd;
current = p->next;
numbers++;
nd->prev = p;
pthread_mutex_unlock(&pmt);
}
unsigned int db_size(){
return numbers;
}
