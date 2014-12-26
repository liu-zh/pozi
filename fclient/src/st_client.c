#include "../include/st_client.h"
#include "../include/util.h"

int send_file(int clientfd, const char* filepath) {
//char filename[60];
	memset(filename, '\0', sizeof(filename));
	int flen = strlen(filepath);
	last_index_of(filename, filepath, flen, '/');
	printf("send the file %s\n", filepath);
	int filed = open(filepath, O_RDONLY);
	if (filed == -1) {
		printf("can not open the file %s %s\n", filepath, strerror(errno));
		databuf.end = SENDEND;
		write(clientfd, &databuf, sizeof(databuf));
		return -1;
	}
	int rsize = 0;
	databuf.end = SENDNAME;
	strcpy(databuf.filename, filename);
	write(clientfd, &databuf, sizeof(databuf));
	while ((rsize = read(filed, databuf.buffer, 2048)) > 0) {
		databuf.size = rsize;
		databuf.end = SENDDATA;
		write(clientfd, &databuf, sizeof(databuf));
		printf("send %d bytes\n", rsize);
	}
	databuf.end = SENDEND;
	write(clientfd, &databuf, sizeof(databuf));
}

int send_fin(int clientfd) {
	memset(&databuf, '\0', sizeof(struct data_msg));
	databuf.end = SENDFIN;
	write(clientfd, &databuf, sizeof(databuf));
}
