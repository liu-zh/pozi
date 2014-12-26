#include "../include/st_client.h"
#include "../include/util.h"

int send_file(const char* filepath, struct data_msg* buf) {
	char filename[60];
	int flen = strlen(filepath);
	last_index_of(filename, filepath, flen, '/');
	int filed = open(filepath, O_RDONLY);

}
/*
 int main(int argc,char** argv){
 int cliefd = client_connect("192.168.1.120",10010);

 return 0;
 }
 */
