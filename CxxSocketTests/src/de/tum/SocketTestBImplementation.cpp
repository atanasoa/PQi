#include "de/tum/SocketTestBImplementation.h"
extern "C" void socket_client_loop_();
de::tum::SocketTestBImplementation::SocketTestBImplementation(){

}

de::tum::SocketTestBImplementation::~SocketTestBImplementation(){

}
void de::tum::SocketTestBImplementation::sim(){
	int parts=-1;
	_queryServer->getNumberOfParts(parts);
	std::cout<<"query parts:"<<parts<<std::endl;
	double offset[2];
	double size[2];
	int res[2];
	int *mids=new int[parts];
	_queryServer->getQueryDescription(offset,2,size,2,res,2,mids,1);
	std::cout<<"qo:"<<offset[0]<<" " <<offset[1]<<std::endl;
	std::cout<<"qs:"<<size[0]<<" " <<size[1]<<std::endl;
	std::cout<<"qr:"<<res[0]<<" " <<res[1]<<std::endl;
	delete []mids;
}
int main(){
	socket_client_loop_();
}
