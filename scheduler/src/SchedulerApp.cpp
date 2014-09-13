/*
 * SchedulerApp.cpp
 *
 *  Created on: 2014Äê9ÔÂ13ÈÕ
 *      Author: liuzhenhua
 */

#include "../include/SchedulerApp.h"

namespace server {

SchedulerApp::SchedulerApp() {
	// TODO Auto-generated constructor stub
	 PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("../config/log.properties"));
	 log4cplus::Logger::getRoot().setLogLevel(log4cplus::ALL_LOG_LEVEL);
	  _logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("FILE"));
}
void SchedulerApp::startScheduler(){
	 boost::shared_ptr<MultiVector> mv(new MultiVector());
	 try{
	 	boost::thread r(boost::bind(&SchedulerApp::startRegist,this,mv));
	 	boost::thread d(boost::bind(&SchedulerApp::startDistri,this,mv));
	     r.join();
	     d.join();
	 	}catch(exception& ex){
	 		cout<<"error occur: "<<ex.what()<<endl;
	 	}

}

void SchedulerApp::startRegist(boost::shared_ptr<MultiVector> shared){
	 RegisterApp regist;
	 regist.startRegist( shared);
}
	void SchedulerApp::startDistri(boost::shared_ptr<MultiVector> shared){
		DistriApp distri(6704);
		distri.startDistribute(  shared);
	}

SchedulerApp::~SchedulerApp() {
	// TODO Auto-generated destructor stub

}

} /* namespace server */
