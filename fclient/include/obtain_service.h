#ifndef _OBTAIN_SERVICE_H_
#define _OBTAIN_SERVICE_H_
#include "message.h"
#include "po_sock.h"

int ob_service(struct meta_msg* resbuf,const char* ipaddr,const int port);
#endif
