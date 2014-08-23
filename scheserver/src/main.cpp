/*
 * main.cpp
 *
 *  Created on: 2014Äê8ÔÂ23ÈÕ
 *      Author: liuzhenhua
 */
#include "../include/ScheServer.h"

int main(){
    server::ScheServer server(6700,6704);
    server.execute();
	return 0;
}



