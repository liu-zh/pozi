#include "../include/obtain_service.h"

int ob_service(struct meta_msg* resbuf,const char* ipaddr,const int port){
int cliefd = client_connect(/*"192.168.81.129",10999*/ipaddr,port);
struct meta_msg mmsg = 
      {"",0,202};
if(write(cliefd,&mmsg,sizeof(struct meta_msg)) < 0){
printf("write error %s\n",strerror(errno));
}
memset(&mmsg,'\0',sizeof(struct meta_msg));
if(read(cliefd,&mmsg,sizeof(struct meta_msg)) < 0){
printf("read error %s\n",strerror(errno));
}

if(mmsg.flag == 203){
printf("obtain service suceessfully,clientg is connecting to %s:%d\n",mmsg.ipaddr,mmsg.port);
return 1;
}else{
printf("could not obtain the service \n");
return 0;
}

}
