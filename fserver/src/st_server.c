#include "../include/st_server.h"
#include "../include/message.h"
struct thread_arg {
	int fd;
	char dirname[50];
};
void* syn_connect(void* arg);
int receive_file(int cfd, const char* receivedir);
/**************************/
void* syn_connect(void* arg) {
//int sfd = *((int*)arg);
	struct thread_arg* varg = (struct thread_arg*) arg;
	int sfd = varg->fd;
	printf("server start to handle the connect\n");
	receive_file(sfd, varg->dirname);
	free(arg);
	close(sfd);
	printf("connect be released!\n");
	return (void*) 0;
}
int receive_file(int cfd, const char* receivedir) {
	int rsize = 0;
	int localfd;
	char namebuf[256];
	while (1) {
		rsize = read(cfd, &databuf, sizeof(struct data_msg));
		if (rsize == -1) {
			printf("server read error %s\n", strerror(errno));
			exit(-2);
		}
		if (databuf.end == SENDNAME) {
			printf("client command %d\n", databuf.end);
			sprintf(namebuf, "%s/%s", receivedir, databuf.filename);
			printf("write to local: %s\n", namebuf);
			localfd = open(namebuf, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
			if (localfd == -1)
				break;
		} else if (databuf.end == SENDDATA) {
// printf("client command %d,read size %d\n",databuf.end,databuf.size);
			write(localfd, databuf.buffer, databuf.size);
		} else if (databuf.end == SENDEND) {
			printf("client command %d\n", databuf.end);
			close(localfd);
		} else if (databuf.end == SENDFIN) {

			printf("receive finish,Thread exit\n");
			break;
		}
		memset(&databuf, '\0', sizeof(struct data_msg));
	}
}
/**************************************/
int regist_self() {
	int registfd;
	if ((registfd = client_connect("127.0.0.1", 10998)) == -1) {
		printf("cannot connect to the regist server\n");
		exit(-1);
	}
	struct meta_msg buf;
	memset(&buf, '\0', sizeof(struct meta_msg));
	buf.flag = 201;
	getLocalIp(buf.ipaddr);
	buf.port = 10100;
	printf("send msg of itself\n");
	write(registfd, &buf, sizeof(struct meta_msg));
	read(registfd, &buf, sizeof(struct meta_msg));
//close(registfd);
	if (buf.flag == 202) {
		printf("file server regist to regist server successfully!\n");
		return registfd;
	} else {
		printf("file server regist failed!\n");
		return 0;
	}
}
/************************************/
int accept_fd(int serverfd, const char* name) {

	struct sockaddr_in clientaddr;
	pthread_t pht;
	int socklen_t = sizeof(struct sockaddr_in);
	int cfd;
	while (1) {

		cfd = accept(serverfd, (struct sockaddr*) &clientaddr, &socklen_t);
		if (cfd == -1) {
			printf("accept the connection error %s\n", strerror(errno));
			continue;
		} else {
			printf("st_server: accept cennnection from %s %d\n",
					inet_ntoa(clientaddr.sin_addr), cfd);
//int* clientfd = malloc(sizeof(int));
//*clientfd = cfd;
			struct thread_arg *targ = malloc(sizeof(struct thread_arg));
			targ->fd = cfd;
			printf("---------------\n");
			strcpy(targ->dirname, name);
			printf("start a thread......");
			pthread_create(&pht, NULL, syn_connect, targ);
		}
	}
}
/*******************/
int init_server(const char* receivedir) {
	getLocalIp(ip4);
	printf("local ip addr: %s\n", ip4);
	if (access(receivedir, R_OK | W_OK) == -1)
		createdir(receivedir);
	else
		printf("file %s exists!", receivedir);
	return 1;
}
/*******************/
