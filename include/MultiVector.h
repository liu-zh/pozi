/*
 * MultiVector.h
 *
 *  Created on: 2014��8��16��
 *      Author: liuzhenhua
 */

#ifndef MULTIVECTOR_H_
#define MULTIVECTOR_H_
#include <vector>
#include <boost/thread.hpp>
using namespace std;

template <typename T>
class MultiVector{
private:
	vector<T> vec;
	boost::mutex mut;
public:
	MultiVector();
	void pushback(T t);
	void erase();
	virtual ~MultiVector();
};



#endif /* MULTIVECTOR_H_ */
