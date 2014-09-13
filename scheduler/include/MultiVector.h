/*
 * MultiVector.h
 *
 *  Created on: 2014年8月30日
 *      Author: liuzhenhua
 */

#ifndef MULTIVECTOR_H_
#define MULTIVECTOR_H_
#include <pthread.h>
#include <vector>
#include "log.h"
#include "Counter.h"
using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;
namespace server {
/**************************
 * 共享资源队列
 * */
class MultiVector {
private:
	pthread_mutex_t pmt;
	vector<Counter> vec;
	 int number  ;
	 Logger _logger;
public:
	MultiVector();
	void  push(Counter t);
	Counter& next();
	int  size();
	bool   release(Counter t);
	bool set(string ip);
	Counter&  get(int i);
	virtual ~MultiVector();
};

} /* namespace server */

#endif /* MULTIVECTOR_H_ */
