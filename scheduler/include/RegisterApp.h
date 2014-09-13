/*
 * RegisterApp.h
 *
 *  Created on: 2014Äê8ÔÂ30ÈÕ
 *      Author: liuzhenhua
 */

#ifndef REGISTERAPP_H_
#define REGISTERAPP_H_
#include "RegistServer.h"
using namespace log4cplus;
using namespace log4cplus::helpers;
namespace server {

class RegisterApp {
private:
	  Logger _logger;
public:
	RegisterApp();
	void startRegist(boost::shared_ptr<MultiVector> shared);
	virtual ~RegisterApp();
};

} /* namespace server */

#endif /* REGISTERAPP_H_ */
