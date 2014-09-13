/*
 * SchedulerApp.h
 *
 *  Created on: 2014Äê9ÔÂ13ÈÕ
 *      Author: liuzhenhua
 */

#ifndef SCHEDULERAPP_H_
#define SCHEDULERAPP_H_
#include "RegisterApp.h"
#include "DistriApp.h"
namespace server {

class SchedulerApp {
private:
	Logger _logger;
public:
	SchedulerApp();
	void startRegist(boost::shared_ptr<MultiVector> shared);
	void startDistri(boost::shared_ptr<MultiVector> shared);
	void startScheduler();

	virtual ~SchedulerApp();
};

} /* namespace server */

#endif /* SCHEDULERAPP_H_ */
