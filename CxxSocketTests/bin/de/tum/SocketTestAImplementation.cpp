#include "de/tum/SocketTestAImplementation.h"
#include "de/tum/SocketTestAC2CxxProxy.h"
#include <pthread.h>
de::tum::SocketTestAImplementation::SocketTestAImplementation(){
	pthread_mutex_init(&_lock,NULL);
	_offset[0]=0.0;
	_offset[1]=0.0;
	_size[0]=1.0;
	_size[1]=1.0;
	_dimensions[0]=33;

	_dimensions[1]=33;
}

de::tum::SocketTestAImplementation::~SocketTestAImplementation(){
	pthread_mutex_destroy(&_lock);
}

void de::tum::SocketTestAImplementation::getNumberOfParts(int& parts){
     parts=1;
}
void de::tum::SocketTestAImplementation::forwardAnswer(const double* data,const int data_len,const int mid){
	 pthread_mutex_lock( &_lock );
	 pthread_mutex_unlock( &_lock );
}
void de::tum::SocketTestAImplementation::getQueryDescription(double* offset, const int offset_len,double* size, const int size_len,int* resolution, const int resolution_len,int* mids, const int mids_len){
     for(int i=0;i<2;i++){
    	 offset[i]=_offset[i];

    	 size[i]=size[i];

    	 resolution[i]=_dimensions[i];
     }
}

int main(){
	socket_client_loop_();
}
