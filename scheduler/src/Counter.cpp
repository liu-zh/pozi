/*
 * Counter.cpp
 *
 *  Created on: 2014Äê8ÔÂ23ÈÕ
 *      Author: liuzhenhua
 */

#include "../include/Counter.h"

namespace server {

Counter::Counter() {
	// TODO Auto-generated constructor stub

}
Counter::Counter(const string& ip,const int& count){
	this->ip = ip;
	this->count = count;
}
void Counter::dec(){
    this->count <= 0?this->count:this->count--;
}
bool Counter::operator==(Counter& c){
	return  this->ip.compare(c.ip) == 0;
}
string& Counter::getIP(){
	return this->ip;
}
void Counter::inc(){
    this->count++;
	}
Counter::~Counter() {
	// TODO Auto-generated destructor stub
}

} /* namespace server */
