/*
 * Counter.h
 *
 *  Created on: 2014Äê8ÔÂ23ÈÕ
 *      Author: liuzhenhua
 */

#ifndef COUNTER_H_
#define COUNTER_H_
#include <string>
using namespace std;
namespace server {

class Counter {
private:
	string ip;
	int count;
public:
	Counter();
	Counter(const string& ip,const int& count);
	void dec();
	void inc();
	string& getIP();
	bool operator==(Counter& c);
	virtual ~Counter();
};

} /* namespace server */

#endif /* COUNTER_H_ */
