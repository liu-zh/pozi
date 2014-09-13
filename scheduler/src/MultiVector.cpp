/*
 * MultiVector.cpp
 *
 *  Created on: 2014年8月30日
 *      Author: liuzhenhua
 */

#include "../include/MultiVector.h"

namespace server {

MultiVector::MultiVector() {
	// TODO Auto-generated constructor stub
	  _logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("FILE"));
	     pthread_mutex_init(&pmt,NULL);
	     //cout<<"初始化共享资源队列的锁"<<endl;
	      LOG4CPLUS_INFO(_logger,"initialize the lock of share resource");
}
void MultiVector::push(Counter t){
        pthread_mutex_lock(&pmt);
        bool isHave = false;
        int i = 0;
        for(;i < vec.size();i++){
        	if(vec[i] == t){
        		isHave = true;
        		break;
        	}
        }
        if(!isHave)
		  vec.push_back(t);
        pthread_mutex_unlock(&pmt);
	}
	Counter& MultiVector::next(){
		Counter cnt;
		pthread_mutex_lock(&pmt);
		//cnt = vec[number++%vec.size()].dec();
		vec[number%vec.size()].dec();
		cnt = vec[number++%vec.size()];
		pthread_mutex_unlock(&pmt);
		return cnt;
	}
	bool  MultiVector::release(Counter t){
			  bool isFind = false;
			 pthread_mutex_lock(&pmt);
			   int i = 0;
			   for(;i < vec.size();i++){
	           if(vec[i] == t){
	        	   vec[i].inc();
	        	   isFind = true;
	        	   break;
	           }
			   }
			 pthread_mutex_unlock(&pmt);
	        return isFind;
		}
	 /*
	 bool  increase(Counter t){
		  bool isFind = false;
		 pthread_mutex_lock(&pmt);
		   int i = 0;
		   for(;i < vec.size();i++){
           if(vec[i] == t){
        	   vec[i].inc();
        	   isFind = true;
        	   break;
           }
		   }
		 pthread_mutex_unlock(&pmt);
        return isFind;
	}

	 bool decrease(Counter t){
		 bool isFind = false;
				 pthread_mutex_lock(&pmt);
				   int i = 0;
				   for(;i < vec.size();i++){
		           if(vec[i] == t){
		        	   vec[i].inc();
		        	   isFind = true;
		        	   break;
		           }
				   }
				 pthread_mutex_unlock(&pmt);
		        return isFind;
	 }
      */
	 int MultiVector::size(){
		 return vec.size();
	 }
	 bool MultiVector::set(string ip){
			 bool isFind = false;
					 pthread_mutex_lock(&pmt);
					   int i = 0;
					   for(;i < vec.size();i++){
			           if(!vec[i].getIP().compare(ip)){
			        	   vec[i].inc();
			        	   isFind = true;
			        	   break;
			           }
					   }
					 pthread_mutex_unlock(&pmt);
			        return isFind;
		 }
	 Counter& MultiVector::get(int i){
		 Counter cnt;
		 pthread_mutex_lock(&pmt);
		     vec[i].dec();
		     cnt = vec[i];
		  pthread_mutex_unlock(&pmt);
		  return cnt;
	 }
MultiVector::~MultiVector() {
	// TODO Auto-generated destructor stub
}

} /* namespace server */
