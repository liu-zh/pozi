#include "../include/dbaccess.h"
/***************************/
int execute_sql(const char* sql, struct list_mysql_node* mnode,
		void (*handleRes)(void*)) {
	MYSQL_RES* myr;
	if (mysql_query(mnode->mysql, sql)) {
		printf("execute error %s %s\n", sql, mysql_error(mnode->mysql));
		return 0;
	} else
		myr = mysql_store_result(mnode->mysql);
	time_t tt;
	time(&tt);
	mnode->mills = tt;
	handleRes(myr);
	return 1;
}
/************************/
int maintain_connect(struct list_mysql_node* mnode) {
	time_t tt;
	time(&tt);
	if ((tt - mnode->mills) > 300000)
		mysql_query(mnode->mysql, "select 1");
	mnode->mills = tt;
}

/************************

 int main(int argc,char** argv){
 MYSQL mysql;
 mysql_init(&mysql);
 mysql_real_connect(&mysql,"192.168.1.120","pozi",
 "pozi","pozi",3306,NULL,0);
 mysql_query(&mysql,"insert into pozi_upload_file(uf_path,uf_ipaddr,uf_jobid) values('/receive/20140524.dat','192.168.1.120','201400122321')");
 mysql_close(&mysql);
 return -1;
 }
 ************************/
