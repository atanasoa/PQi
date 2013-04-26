#include "de/tum/PQIDispatcherImplementation.h"

#ifdef Parallel
#include "mpi.h"
#endif


de::tum::PQIDispatcherImplementation::PQIDispatcherImplementation(){

}


de::tum::PQIDispatcherImplementation::~PQIDispatcherImplementation(){

}

void de::tum::PQIDispatcherImplementation::requestNumberOfParts(int& parts){
#ifdef Parallel
	int rank,size;
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	size=1;
	std::cout<<"PQIDispatcherImplementation::requestNumberOfParts rank:"<<rank<<std::endl;
	MPI_Reduce( &size,&parts, 1, MPI_INT, MPI_SUM, 0,MPI_COMM_WORLD);
#else
	parts=1;
#endif
}
void de::tum::PQIDispatcherImplementation::requestPartsInformation(double* offset, const int offset_len,double* size, const int size_len,int* dimensions, const int dimensions_len,int* identifiers, const int identifiers_len){
     // @todo Insert your code here
	std::cout<<"calling requestPartsInformation"<<std::endl;
}

void initialize_mpi(int argc, char** argv){
#ifdef Parallel
	MPI_Init( &argc, &argv );
#endif
}
void destroy_mpi(){
#ifdef Parallel
	MPI_Finalize();
#endif
}
extern "C"{
	void master_socket_loop_();
	void slave_socket_loop_();
}
int main(int argc, char** argv){
	initialize_mpi(argc,argv);

#ifdef Parallel
	int rank;
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	std::cout<<"PQi Dispatcher started on rank ::"<<rank<<std::endl;
	if(rank==0)
		master_socket_loop_();
	else
		slave_socket_loop_();
#else
	master_socket_loop_();
#endif

	destroy_mpi();

	// do stuff


	return 1;
}
