/*
 * DatabaseAccess.h
 *
 *  Created on: 2014年8月16日
 *      Author: liuzhenhua
 */

#ifndef DATABASEACCESS_H_
#define DATABASEACCESS_H_
#include <winsock.h>
#include <mysql/mysql.h>
#include <string>
#include <iostream>

using namespace std;
namespace server {

class DatabaseAccess {
private:
	MYSQL mysql;
public:
	DatabaseAccess();
	int dbConn(const string &host,const string &db,const string &username,const string &passw);
	 int executeSQL(const string& sql);
	 int dbClose();

	virtual ~DatabaseAccess();
};

} /* namespace server */

#endif /* DATABASEACCESS_H_ */
