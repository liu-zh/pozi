/*
 * main.cpp
 *
 *  Created on: 2014/08/09
 *      Author: liuzhenhua
 */


#include "../include/FileServer.h"

int main(){
    server::FileServer fileserver(10100);
    fileserver.startFileServer();
	return 0;
}


