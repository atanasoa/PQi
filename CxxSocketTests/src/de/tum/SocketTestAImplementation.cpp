#ifndef PARALLEL
#include "SimpleView.h"
#include <vtkThreadedStreamingPipeline.h>
#include <vtkSmartPointer.h>
#include <vtkAlgorithm.h>
#include <QTimer>
#include <QApplication>
#include "MyTimer.hpp"
#else
#include "mpi.h"
#endif

#include <sys/time.h>

#include "de/tum/SocketTestAImplementation.h"
#include "de/tum/SocketTestAC2CxxProxy.h"
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

const double de::tum::SocketTestAImplementation::global_offset=0.0;
const double de::tum::SocketTestAImplementation::global_size=1.0;
const int de::tum::SocketTestAImplementation::global_dimension=257;


de::tum::SocketTestAImplementation::SocketTestAImplementation(){
	pthread_mutex_init(&_lock,NULL);
	_log_file.open("log_file.txt");
	_iter=-1;
	
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
	std::cout<<"destroying server"<<std::endl;
	delete [] _data;
	delete [] _distances;
	delete [] _timesteps;
	_log_file.flush();
	_log_file.close();
        pthread_mutex_destroy(&_lock);

}

//sinngemäße Implementierung. Form der Übergabe müsste angepasst werden
//example: hor=4, ver=2, 32*32 grid, new grid size:8*16
void de::tum::SocketTestAImplementation::initialiseParallel(int hor, int ver){
//std::cout << hor << " " << ver <<std::endl;
#ifdef PARALLEL	
	assert((global_dimension-1) % hor == 0 && (global_dimension-1) % ver == 0);
	int rank;
	int size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	assert(hor*ver > rank);
	assert(hor*ver > 0 && hor*ver==size);
	_size[0]=global_size/hor;
	_size[1]=global_size/ver;
	//_size[2]=0.0;
	_dimensions[0]=((global_dimension-1)/hor)+1;

	_dimensions[1]=((global_dimension-1)/ver)+1;

	//_dimensions[2]=1;

	//_offset[0]=(rank % (global_dimension-1)) / hor * _size[0];
_offset[0]=(rank % hor) * _size[0];
	_offset[1]=(rank / ver) * _size[1];

	//_offset[2]=0.0;

	_data= new double[_dimensions[0]*_dimensions[1]];
	_distances= new double[_dimensions[0]*_dimensions[1]];
	_timesteps =  new int[_dimensions[0]*_dimensions[1]];
	for(int i=0;i<_dimensions[0]*_dimensions[1];i++){
		_timesteps[i]=0;
		_distances[i]=20000000;
	}
#endif
}

void de::tum::SocketTestAImplementation::constructorToString(){
	int rank = 0;
	#ifdef PARALLEL
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	#endif
	std::cout <<rank << " - " << "global query: " << global_size << " "<< global_dimension << " " << global_offset << std::endl;
	std::cout <<rank  << " - " << "size: "<< _size[0] << " " << _size[1] << " " << _size[2] << std::endl;
	std::cout <<rank  << " - " << "dimensions: "<< _dimensions[0] << " " << _dimensions[1] << " " << _dimensions[2] << std::endl;
	std::cout <<rank  << " - " << "offset: "<< _offset[0] << " " << _offset[1] << " " << _offset[2] << std::endl;
}

void de::tum::SocketTestAImplementation::getNumberOfParts(int& parts){
 pthread_mutex_lock( &_lock );
#ifdef PARALLEL
	MPI_Comm_size(MPI_COMM_WORLD,&parts);  
#else
	parts=1;
#endif
        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        timeval end;
        gettimeofday(&end, 0);
	if(_iter>=0)
        _log_file << "rank:" << rank <<"#rid:" << _iter <<"#start_time:" << end.tv_sec << "." << end.tv_usec << std::endl;
	_iter++;
 pthread_mutex_unlock( &_lock );
}

//includes used for logging
#include <mpi.h>
#include <sys/time.h>
#include <fstream>

//array anpassen, aber oben in constructor
void de::tum::SocketTestAImplementation::forwardAnswer(
		const double* data,
		const int data_len,
		const double* distance,
		const int distance_len,
		const int* indices,
		const int indices_len,
		const int mid
		){
         timeval end;
         gettimeofday(&end, 0);
         int rank;
         MPI_Comm_rank(MPI_COMM_WORLD, &rank);
         _log_file << "rank:" << rank <<"#rid:" << mid <<"#end_time:" << end.tv_sec << "." << end.tv_usec <<"#size:"<<data_len<< std::endl;

	 pthread_mutex_lock( &_lock );
        
	//time logging after send
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
	double min = 1000000; 
	double max = -1000000;
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
for(int i = 0; i<argc; i++){
std::cout << argv[i] << " ";  
}
std::cout << std::endl;

#ifdef PARALLEL
  //int rank, numtasks;
  if (argc < 2) {
        /**
	  *  Tell the user how to run the program
	  *  If argv[0] is not name of executable, then correct indices
	  */
        std::cerr << "Usage: " << argv[1] << " number_x_split" << std::endl;
	std::cerr << "Usage: " << argv[2] << " number_y_split" << std::endl;
        return 1;
    }
    MPI_Init (NULL,NULL); 
#endif
    SOCKETTESTA_arg daemon_args;
    initialise_(daemon_args);

#ifdef PARALLEL
int hor = atoi(argv[1]);
int ver = atoi(argv[2]);
((de::tum::SocketTestAImplementation*)daemon_args.ref)->initialiseParallel(hor,ver);
((de::tum::SocketTestAImplementation*)daemon_args.ref)->constructorToString();
 while(true){};

#else

     /**
     *  vtk initalisation
     */
    vtkSmartPointer<vtkThreadedStreamingPipeline> streamingExec = vtkSmartPointer<vtkThreadedStreamingPipeline>::New();
    vtkAlgorithm::SetDefaultExecutivePrototype(streamingExec);
    streamingExec->FastDelete();
    vtkThreadedStreamingPipeline::SetAutoPropagatePush(true);
    
    /**
     * socket server initialisation
     */
    initialise_(daemon_args);

   /**
     * QT
     */ 
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
#endif


#ifdef PARALLEL   
    destroy_(daemon_args);
    MPI_Finalize();
    return 0;
#endif

	//socket_client_loop_();



}

