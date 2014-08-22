/*
 * MultiVector.cpp
 *
 *  Created on: 2014��8��16��
 *      Author: liuzhenhua
 */

#include "../include/MultiVector.h"


template <typename T>
MultiVector<T>::MultiVector() {
	// TODO Auto-generated constructor stub

}
template <typename T>
void MultiVector<T>::pushback(T t){
mut.lock();
vec.push_back(t);
mut.unlock();
}
template <typename T>
void MultiVector<T>::erase(){

}
template <typename T>
MultiVector<T>::~MultiVector() {
	// TODO Auto-generated destructor stub
}


