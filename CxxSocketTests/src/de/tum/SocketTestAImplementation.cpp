#include "de/tum/SocketTestAImplementation.h"
#include "de/tum/SocketTestAC2CxxProxy.h"
#include <vtkThreadedStreamingPipeline.h>
#include <vtkSmartPointer.h>
#include <vtkAlgorithm.h>
#include "SimpleView.h"
#include "MyTimer.hpp"
#include <pthread.h>
#include <QTimer>
#include <QApplication>
de::tum::SocketTestAImplementation::SocketTestAImplementation(){
	pthread_mutex_init(&_lock,NULL);
	_offset[0]=0.0;
	_offset[1]=0.0;
	_offset[2]=0.0;
	_size[0]=1.0;
	_size[1]=1.0;
	_size[2]=0.0;
	_dimensions[0]=33;

	_dimensions[1]=33;

	_dimensions[2]=1;

	_data= new double[_dimensions[0]*_dimensions[1]];
	_distances= new double[_dimensions[0]*_dimensions[1]];
	_timesteps =  new int[_dimensions[0]*_dimensions[1]];
	for(int i=0;i<_dimensions[0]*_dimensions[1];i++){
		_timesteps[i]=0;
		_distances[i]=20000000;
	}
}

double* de::tum::SocketTestAImplementation::getOffset(){
	return _offset;
}

double* de::tum::SocketTestAImplementation::getSize(){
	return _size;
}


int* de::tum::SocketTestAImplementation::getDimensions(){
	return _dimensions;
}

de::tum::SocketTestAImplementation::~SocketTestAImplementation(){
	delete [] _data;
	delete [] _distances;
	delete [] _timesteps;
	pthread_mutex_destroy(&_lock);

}

void de::tum::SocketTestAImplementation::getNumberOfParts(int& parts){
     parts=1;
}
void de::tum::SocketTestAImplementation::forwardAnswer(
		const double* data,
		const int data_len,
		const double* distance,
		const int distance_len,
		const int* indices,
		const int indices_len,
		const int mid
		){
	 pthread_mutex_lock( &_lock );
	 for(int i=0;i<indices_len;i++)
	 {
		 if(_timesteps[indices[i]]<mid && distance[i]<=_distances[indices[i]]){
			 _distances[indices[i]]=distance[i];
			 _data[indices[i]]=data[i];
			 _timesteps[indices[i]]=mid;
		 }
	 }
	 pthread_mutex_unlock( &_lock );
}

void de::tum::SocketTestAImplementation::cloneData(double* targetData){
	pthread_mutex_lock( &_lock );
	double min= 200000000;
	double max= -200000000;
	for(int i=0;i<_dimensions[0]*_dimensions[1];i++){
		targetData[i]=_data[i];
		if(min>_data[i])
			min=_data[i];
		if(max<_data[i])
			max=_data[i];
			
	}
	for(int i=0;i<_dimensions[0]*_dimensions[1];i++){
		targetData[i]=(_data[i]-min)/(max-min);
	}
	pthread_mutex_unlock( &_lock );
}
void de::tum::SocketTestAImplementation::getQueryDescription(double* offset, const int offset_len,double* size, const int size_len,int* resolution, const int resolution_len,int* mids, const int mids_len){
     for(int i=0;i<2;i++){
    	 offset[i]=_offset[i];

    	 size[i]=_size[i];

    	 resolution[i]=_dimensions[i];
     }
}

extern "C" void initialise_(SOCKETTESTA_arg& arg);

extern "C" void destroy_(SOCKETTESTA_arg& arg);

int main(int argc, char **argv){
	SOCKETTESTA_arg daemon_args;


    vtkSmartPointer<vtkThreadedStreamingPipeline> streamingExec = vtkSmartPointer<vtkThreadedStreamingPipeline>::New();
	vtkAlgorithm::SetDefaultExecutivePrototype(streamingExec);
  	streamingExec->FastDelete();
  	vtkThreadedStreamingPipeline::SetAutoPropagatePush(true);
  	initialise_(daemon_args);
    QApplication app( argc, argv );
    QTimer *timer = new QTimer;
    MyTimer t;
    QObject::connect(timer, SIGNAL(timeout()),&t, SLOT(update()));

  	SimpleView view;
  	t.setDataSource(((de::tum::SocketTestAImplementation*)(daemon_args.ref)));
  	t.setData(view.data);
  	t.setRenderer(view.renWin);
	view.data->SetOffset(((de::tum::SocketTestAImplementation*)(daemon_args.ref))->getOffset());

	view.data->SetBoundingBox(((de::tum::SocketTestAImplementation*)daemon_args.ref)->getSize());

	view.data->SetDimensions(((de::tum::SocketTestAImplementation*)daemon_args.ref)->getDimensions());
	view.show();
	timer->start(40);
	int exec_rv=app.exec();
 	destroy_(daemon_args);
	return exec_rv;
	//socket_client_loop_();
}
