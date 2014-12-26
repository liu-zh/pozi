#include "../include/ft_server.h"
/*******************
 create two process
 the parent process regist
 the child process
 ********************/

/*******************/
void sig_han() {
	config_linklist* confighead;
	createList(&confighead);
	analyze_config("config/server.ini", confighead);
	struct node_value nvport;
	strcpy(nvport.key, "server.port");
	getNodeByKey(confighead, &nvport);
	printf("server port: %s\n", nvport.value);

	struct node_value nvdir;
	strcpy(nvdir.key, "server.dir");
	getNodeByKey(confighead, &nvdir);
	printf("save file directory: %s\n", nvdir.value);

	struct node_value nvbacklog;
	strcpy(nvbacklog.key, "server.backlog");
	getNodeByKey(confighead, &nvbacklog);
	printf("backlog: %s\n", nvbacklog.value);

	init_server(nvdir.value);
	int fd = server_listen(atoi(nvport.value), atoi(nvbacklog.value), 0);
	init_server(nvdir.value);
	accept_fd(fd, nvdir.value);
	close(fd);
	destroyList(confighead);
}

/********************/
int start_server() {
	pid_t pt;
	int registfd;
	if ((registfd = regist_self())) {
		int filedes[2];
		char buffer[80];
		if (pipe(filedes) < 0) {
			printf("create pipeline error %s\n,strerror(errno)");
			exit(-2);
		}
		printf("create pipeline successfully\n");
		pt = fork();

		if (pt > 0) {
			/**this is the parent process***/
			close(filedes[0]);
			printf("this is the parent process\n");
			char tmpmsg[3] = "SND";
			write(filedes[1], tmpmsg, sizeof(tmpmsg));
			close(filedes[1]);

			struct meta_msg mmsg;

			time_t tm;
			time(&tm);
			time_t tt;
			while (1) {
				time(&tt);
				long inv = tt - tm;
//printf("check inteval %ld\n",inv);
				if (inv > 3) {
					printf("every 3 minutes executed \n");
					tm = tt;
					memset(&mmsg, '\0', sizeof(struct meta_msg));
					mmsg.flag = 204;
					if (write(registfd, &mmsg, sizeof(struct meta_msg)) < 0) {
						printf("write error %s\n", strerror(errno));
					}
					memset(&mmsg, '\0', sizeof(struct meta_msg));
					read(registfd, &mmsg, sizeof(struct meta_msg));
					printf("receive heartbeat %d\n", mmsg.flag);
				}
			}

		} else if (pt == 0) {
			/**this is the child process***/
			close(filedes[1]);
			printf("this the child procoss\n");
			char rdmsg[3];
			read(filedes[0], rdmsg, sizeof(rdmsg));
			printf("receive pipe msg %s\n", rdmsg);
			close(filedes[0]);
			if (strcmp(rdmsg, "SND")) {
				printf("file server is starting......\n");
				sig_han();
			}
		} else {
			printf("create process error %s\n", strerror(errno));
		}
	}
}
/******
 ***********/
