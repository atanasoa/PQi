/*
 * vtkClientQuery.cpp
 *
 *  Created on: Jan 31, 2013
 *      Author: atanasoa
 */

#include "queries/vtkClientQuery.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <arpa/inet.h>


queries::vtkClientQuery::vtkClientQuery():
_query("localhost",50000,1024){
	std::cout<<"query client connection established"<<std::endl;

}

queries::vtkClientQuery::~vtkClientQuery(){

}

void queries::vtkClientQuery::synchronize(){
	int numberOfParts=0;
	std::cout<<"starting sync"<<std::endl;
	_query.requestAllComm();
	_query.requestNumberOfParts(numberOfParts);
	assert(numberOfParts>0);
}







