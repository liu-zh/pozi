/*
 * DatabaseAccess.cpp
 *
 *  Created on: 2014年8月16日
 *      Author: liuzhenhua
 */

#include "../include/DatabaseAccess.h"

namespace server {

DatabaseAccess::DatabaseAccess() {
	// TODO Auto-generated constructor stub
    if(!mysql_init(&mysql)){
    	cout<<"mysql initialize failed!"<<endl;
    }
}
int DatabaseAccess::dbConn(const string &host,const string &db,const string &username,const string &passwd){
      if(!mysql_real_connect(&mysql,host.c_str(),username.c_str(),
    		  passwd.c_str(),db.c_str(),3306,NULL,0)){
    	  cout<<"connect failed!"<<endl;
    	  return -1;
      }else return 1;
}
 int DatabaseAccess::executeSQL(const string& sql){
      return mysql_query(&mysql,sql.c_str());
	 }
 int DatabaseAccess::dbClose(){
          mysql_close(&mysql);
          return 1;
	 }
DatabaseAccess::~DatabaseAccess() {
	// TODO Auto-generated destructor stub
}

} /* namespace server */
