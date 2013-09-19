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
#include <chrono>

#include "de/tum/SocketTestAImplementation.h"
#include "de/tum/SocketTestAC2CxxProxy.h"
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <algorithm>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>
#include <stdio.h>
#include <string.h>
const double de::tum::SocketTestAImplementation::global_offset=0.0;
const double de::tum::SocketTestAImplementation::global_size=1.0;
const int de::tum::SocketTestAImplementation::global_dimension=1025;


de::tum::SocketTestAImplementation::SocketTestAImplementation(){
	std::cout<<"constructor invocation"<<std::endl;
	pthread_mutex_init(&_lock,NULL);
	
        _start=std::chrono::high_resolution_clock::now();
	std::cout<<"time"<<std::endl;
	#ifdef PARALLEL
        	MPI_Comm_size(MPI_COMM_WORLD,&_pieces);
		MPI_Comm_rank(MPI_COMM_WORLD, &_rank);
		std::stringstream st;
		st<<"log_file_"<<_rank<<".txt";
		 _log_file.open(st.str().c_str());
		std::cout<<"rank:"<<_rank<<" pieces:"<<_pieces<<std::endl;
		if(_rank==0){
			_offset0.resize(2*_pieces);
                	_size0.resize(2*_pieces);
	             		_dimensions0.resize(2*_pieces);
			_iter=-1;
		}else
			_iter=0;
			 _offset.resize(2);
	                 _size.resize(2);
                	 _dimensions.resize(2);

		
	#else
        	_pieces=1;
		_rank=0;
		_offset.resize(2);
		_size.resize(2);
		_dimensions.resize(2);
	#endif
	std::cout<<"constructor finished"<<std::endl;
	
}

double* de::tum::SocketTestAImplementation::getOffset(){
	return &_offset[0];
}

double* de::tum::SocketTestAImplementation::getSize(){
	return &_size[0];
}


int* de::tum::SocketTestAImplementation::getDimensions(){
	return &_dimensions[0];
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
std::cout << hor << " " << ver <<std::endl;
#ifdef PARALLEL	
	assert((global_dimension-1) % hor == 0 && (global_dimension-1) % ver == 0);
	int rank;
	int size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	assert(hor*ver > rank);
	std::cout<<"hor*ver:"<<hor*ver<<" size:"<<size<<std::endl;
	assert(hor*ver > 0 && hor*ver==size);
	_size[0]=global_size/hor;
	_size[1]=global_size/ver;
	//_size[2]=0.0;
	_dimensions[0]=((global_dimension-1)/hor)+1;

	_dimensions[1]=((global_dimension-1)/ver)+1;

	//_dimensions[2]=1;

	//_offset[0]=(rank % (global_dimension-1)) / hor * _size[0];
	_offset[0]=(rank % hor) * _size[0];
	_offset[1]=(rank / hor) * _size[1];

	//_offset[2]=0.0;

	_data= new double[_dimensions[0]*_dimensions[1]];
	_distances= new double[_dimensions[0]*_dimensions[1]];
	_timesteps =  new int[_dimensions[0]*_dimensions[1]];
	for(int i=0;i<_dimensions[0]*_dimensions[1];i++){
		_timesteps[i]=0;
		_distances[i]=20000000;
	}
	std::cout<<"start gathering queries"<<std::endl;
     	MPI_Gather(&_offset[0],2, MPI_DOUBLE,&_offset0[0],2, MPI_DOUBLE, 0,MPI_COMM_WORLD);
     	MPI_Gather(&_size[0],2, MPI_DOUBLE, &_size0[0],2, MPI_DOUBLE, 0,MPI_COMM_WORLD);
     	MPI_Gather(&_dimensions[0],2, MPI_INT,& _dimensions0[0],2, MPI_INT, 0,MPI_COMM_WORLD);
     gatherMIds();	
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
	double t= std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::high_resolution_clock::now()-_start).count();
        std::cout<<"time of decomp:"<<t<<std::endl;

}

void de::tum::SocketTestAImplementation::getNumberOfParts(int& parts){
 pthread_mutex_lock( &_lock );
        parts=_pieces;
	double t= std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::high_resolution_clock::now()-_start).count();
	if(_iter>=0)
        _log_file << "rank:" << _rank <<"#rid:" << _iter <<"#start_time:" << t << std::endl;
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
         pthread_mutex_lock( &_lock );

         int rank;
         MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        double t= std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::high_resolution_clock::now()-_start).count(); 
        _log_file << "rank:" << rank <<"#rid:" << mid <<"#end_time:" << t <<"#size:"<<data_len<< std::endl; 
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

void de::tum::SocketTestAImplementation::gatherMIds(){
	int _sockfd = socket(AF_INET, SOCK_STREAM, 0);
	assert (_sockfd>=0);


	std::stringstream ss;
	std::string s;
	const char* daemon_port = getenv("SOCKETTESTA_DAEMON_PORT");

	ss << (atoi(daemon_port)+_rank);

	std::cout<<"looping through ni"<<std::endl;
	struct if_nameindex *curif, *ifs;
	struct ifreq req;
	std::string mid;
	ifs = if_nameindex();
	if(ifs) {
		for(curif = ifs; curif && curif->if_name; curif++) {
			strncpy(req.ifr_name, curif->if_name, IFNAMSIZ);
			req.ifr_name[IFNAMSIZ] = 0;
			if (ioctl(_sockfd, SIOCGIFADDR, &req) < 0)
				perror("ioctl");
			else{
				printf("%s: [%s]\n", curif->if_name,
                                                        inet_ntoa(((struct sockaddr_in*) &req.ifr_addr)->sin_addr));
				if(strcmp(curif->if_name,"ib0")==0)
				{
					mid=std::string(inet_ntoa(((struct sockaddr_in*) &req.ifr_addr)->sin_addr))+
						std::string(":")+ss.str();
					_mids.push_back(mid);
				}
			}
		}
		if_freenameindex(ifs);
	}
	close(_sockfd);
#ifdef PARALLEL
	if(_rank!=0){
		std::vector<char> bytes(mid.begin(), mid.end());
		bytes.push_back('\0');
		int num_of_bytes=(int)bytes.size();
		assert(num_of_bytes>0);
		MPI_Send(&num_of_bytes,1,MPI_INT,0,1000,MPI_COMM_WORLD);
		MPI_Send(&bytes[0],num_of_bytes,MPI_BYTE,0,1000,MPI_COMM_WORLD);
	}else{

		for(int i=1;i<_pieces;i++)
		{
			int number_of_bytes=0;
			MPI_Status status;
			MPI_Recv (&number_of_bytes,1, MPI_INT,i, 1000, MPI_COMM_WORLD,&status);
			assert(number_of_bytes>0);
			std::vector<char> buff(number_of_bytes);
			MPI_Recv (&buff[0],number_of_bytes,MPI_BYTE,i,1000,MPI_COMM_WORLD,&status);
			std::cout<<"rank:"<<i<<" mid:"<<std::string(&buff[0])<<std::endl;
			_mids.push_back(std::string(&buff[0]));
		}	
	}
#endif	
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
void de::tum::SocketTestAImplementation::getQueryDescription(double* offset, const int offset_len,double* size, const int size_len,int* resolution, const int resolution_len,std::string* mids, const int mids_len){
     for(int i=0;i<_pieces;i++){
    	 offset[i*2]=_offset0[i*2];
	 offset[i*2+1]=_offset0[i*2+1];
    	 size[i*2]=_size0[i*2];
         size[i*2+1]=_size0[i*2+1]; 
    	 resolution[i*2]=_dimensions0[i*2];
	 resolution[i*2+1]=_dimensions0[i*2+1];
	 mids[i]=_mids[i];
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
    MPI_Init (&argc,&argv); 
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

