#ifndef _ST_SERVER_H_
#define _ST_SERVER_H_
#include "po_sock.h"
#include "message.h"
#include <pthread.h>
#ifndef STPORT
#define STPORT 10010
#endif
#ifndef STBACKLOG
#define STBACKLOG 100
#endif
int accept_fd(int serverfd);
int handle_server_fd(int clientfd);
#endif
