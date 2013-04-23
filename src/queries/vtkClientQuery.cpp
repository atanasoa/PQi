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
	_query_client("localhost",5000,256){


}

queries::vtkClientQuery::~vtkClientQuery(){

}

void queries::vtkClientQuery::release(){
	_query_client.release();
}

int queries::vtkClientQuery::getScope(){
	int scope=0;
	_query_client.getScope(scope);
	return scope;
}
bool queries::vtkClientQuery::intersectsWithQuery(const tarch::la::Vector<DIMENSIONS,double> voxelOffset,const tarch::la::Vector<DIMENSIONS,double> voxelSize){
	bool result = false;
	//_query_client.intersectsWithQuery(voxelOffset.getData(),DIMENSIONS,voxelSize.getData(),DIMENSIONS,result);
	return result;
}

void queries::vtkClientQuery::setData(const tarch::la::Vector<DIMENSIONS,double> voxelOffset,const tarch::la::Vector<DIMENSIONS,double> voxelSize,double x){
	//_query_client.setData(voxelOffset.getData(),DIMENSIONS,voxelSize.getData(),DIMENSIONS,x);
}




