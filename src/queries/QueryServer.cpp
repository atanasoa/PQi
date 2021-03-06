#include "queries/QueryServer.h"
//#include "peano/integration/dataqueries/CartesianGridWriterProxy.h"


#ifdef Parallel
#include "tarch/parallel/Node.h"
#include "tarch/parallel/NodePool.h"
#endif


#include "tarch/services/ServiceFactory.h"
#include "queries/records/Answer.h"
#include "peano/heap/Heap.h"
registerService(queries::QueryServer)


tarch::logging::Log queries::QueryServer::_log( "queries::QueryServer" );


queries::QueryServer::QueryServer():
  _pendingQueries(),
  _dataTag(-1),
  _managementTag(-1),
  _bufferSize(3),
  _finishedDataSendAcknowledgementsSinceLastReleaseCall(0) {
  #ifdef Parallel
  init=false;
  _dataTag       = tarch::parallel::Node::reserveFreeTag( "queries::QueryServer[data-tag]" );
  _managementTag = tarch::parallel::Node::reserveFreeTag( "queries::QueryServer[management-tag]" );
  #endif
  _timestep=0;
  _sendFlag=false; 	
}


queries::QueryServer::~QueryServer() {
}

void queries::QueryServer::synchronize(){
	
}

queries::QueryServer& queries::QueryServer::getInstance() {
  static QueryServer singleton;
  return singleton;
}


void queries::QueryServer::receiveDanglingMessages() {
  #ifdef Parallel
  if ( tarch::parallel::Node::getInstance().isGlobalMaster() ) {
      if(!init)
        queries::records::HeapQuery::initDatatype();
      init=true;
      //receiveIncomingQueryData();
  }
  else {
      if(!init)
              queries::records::HeapQuery::initDatatype();
            init=true;
      receiveNewQueries();
  }
  #endif
}


#ifdef Parallel
void queries::QueryServer::receiveIncomingQueryData() {
  int queryId;
  int source;
  /*CartesianGridWriterProxy::checkForPendingData(_dataTag,queryId, source);
  while (queryId>=0) {

    int affectedQuery = getIndexOfQuery(queryId);

    CartesianGridWriterProxy::receiveQueryData(
      _dataTag,
      source,
      *_pendingQueries[affectedQuery]._vertexDataWriter,
      _pendingQueries[affectedQuery]._queryDescription.getRecordsPerEntry()
    );
    CartesianGridWriterProxy::checkForPendingData(_dataTag,queryId, source);
  }
  if (queryId==-2) {

      _finishedDataSendAcknowledgementsSinceLastReleaseCall++;
  }*/
}


void queries::QueryServer::receiveNewQueries() {
  if (queries::records::HeapQuery::isMessageInQueue(_managementTag, true)) {
	queries::records::HeapQuery newQuery;
	newQuery.receive(tarch::parallel::Node::getGlobalMasterRank(),_managementTag, true);

    _pendingQueries.push_back(
	newQuery
    );
    _heapIds.push_back(peano::heap::Heap<queries::records::Answer>::getInstance().createData()); 
    _data.push_back(new __gnu_cxx::hash_map<int,std::pair<double,double> >);
  }
}
#endif


int queries::QueryServer::getNumberOfPendingQueries() const {
  return static_cast<int>(_pendingQueries.size());
}


queries::records::HeapQuery queries::QueryServer::getPendingQueryDescription( int queryNumber ) const {
  assertion( queryNumber >= 0 );
  assertion( queryNumber < getNumberOfPendingQueries() );
  return _pendingQueries[ queryNumber ];
}




int queries::QueryServer::getIndexOfQuery( int id ) {
  int i = 0;
  /*while (i<static_cast<int>(_pendingQueries.size())) {
	if (_pendingQueries[i].getId()==id) {
	  return i;
	}
    i++;
  }
  assertion(false);*/
  return -1;
}


void queries::QueryServer::addQuery(
  queries::records::HeapQuery newQuery,
  std::string mid
) {
  //newQuery.setId( getNumberOfPendingQueries() );
  _pendingQueries.push_back(
    newQuery
  );
  _heapIds.push_back(peano::heap::Heap<queries::records::Answer>::getInstance().createData()); 	
  _data.push_back(new __gnu_cxx::hash_map<int,std::pair<double,double> >);
  _mids.push_back(mid);
  _queryServer.push_back(NULL);
}


bool queries::QueryServer::intersectsWithQuery(int index,const tarch::la::Vector<2,double> voxelOffset,const tarch::la::Vector<2,double> voxelSize){
	return !((voxelOffset[0]<_pendingQueries[index].getOffset()[0]&& voxelOffset[0]+voxelSize[0]<_pendingQueries[index].getOffset()[0])||
	(voxelOffset[0]>_pendingQueries[index].getOffset()[0]+_pendingQueries[index].getSize()[0] && 
	 voxelOffset[0]+voxelSize[0]>_pendingQueries[index].getOffset()[0]+_pendingQueries[index].getSize()[0]
	)||
	(voxelOffset[1]<_pendingQueries[index].getOffset()[1]&& voxelOffset[1]+voxelSize[1]<_pendingQueries[index].getOffset()[1])||
	(voxelOffset[1]>_pendingQueries[index].getOffset()[1]+_pendingQueries[index].getSize()[1] && 
	 voxelOffset[1]+voxelSize[1]>_pendingQueries[index].getOffset()[1]+_pendingQueries[index].getSize()[1]
	));
}

bool queries::QueryServer::holdsFullQuery(int index, const tarch::la::Vector<2,double> voxelOffset,const tarch::la::Vector<2,double> voxelSize){
	return voxelOffset[0]<=_pendingQueries[index].getOffset()[0]&&voxelOffset[1]<=_pendingQueries[index].getOffset()[0]&&
		voxelOffset[0]+voxelSize[0]<=_pendingQueries[index].getOffset()[0]+_pendingQueries[index].getSize()[0]&&
	        voxelOffset[1]+voxelSize[1]<=_pendingQueries[index].getOffset()[1]+_pendingQueries[index].getSize()[1];
}
    
bool queries::QueryServer::isInVoxel(
		const tarch::la::Vector<2,double> &voxelOffset,
		const tarch::la::Vector<2,double> &voxelSize,
		double x,
		double y){

	return x<=voxelOffset[0]+voxelSize[0]&&x>=voxelOffset[0]&&
			y<=voxelOffset[1]+voxelSize[1]&&y>=voxelOffset[1];
}

void queries::QueryServer::swapBuffers(const int index){
	std::vector<queries::records::Answer>& answers=peano::heap::Heap<queries::records::Answer>::getInstance().getData(_heapIds[index]);	
	queries::records::Answer a;
        if(!_data[index]->empty())
	for(__gnu_cxx::hash_map< int,std::pair<double,double > >::iterator it=_data[index]->begin();it!=_data[index]->end();it++)
	{
		a.setData((*it).second.second);

		a.setPosition((*it).second.first);
		a.setDataIndex((*it).first);
		answers.push_back(a);
	}
}


void queries::QueryServer::sendData(const int index,
	const tarch::la::Vector<2,double> &voxelOffset,
	const int level){
         std::vector<queries::records::Answer>& masterAnswer = peano::heap::Heap<queries::records::Answer>::getInstance().getData(_heapIds[index]);

	peano::heap::Heap<queries::records::Answer>::getInstance().sendData(
		_heapIds[index],
		tarch::parallel::NodePool::getInstance().getMasterRank(),
		voxelOffset,level,peano::heap::MasterWorkerCommunication);

	
}

void queries::QueryServer::setSendFlag(bool flag){
	_sendFlag=flag;

}


void queries::QueryServer::close(){
	//if(_queryServer!=NULL){
	//	std::cout<<"qs closing"<<std::endl;
 	//	delete _queryServer;
	//}
}
void queries::QueryServer::receiveData(
	const int index,
	const tarch::la::Vector<2,double> &voxelOffset,
	const int level,
	const int worker){
	
	std::vector<queries::records::Answer> workerAnswer = peano::heap::Heap<queries::records::Answer>::getInstance().receiveData(
		worker,
		voxelOffset,
		level,
		peano::heap::MasterWorkerCommunication);
        std::vector<queries::records::Answer>& masterAnswer = peano::heap::Heap<queries::records::Answer>::getInstance().getData(_heapIds[index]);
        __gnu_cxx::hash_map<int,int> masterAnswerMap;
	for(unsigned int i=0;i<masterAnswer.size();i++)
		masterAnswerMap[masterAnswer[i].getDataIndex()]=i;
	for (unsigned int i=0;i<workerAnswer.size();i++){
		if(masterAnswerMap.find(workerAnswer[i].getDataIndex())!=masterAnswerMap.end()){
			if(masterAnswer[masterAnswerMap[workerAnswer[i].getDataIndex()]].getPosition()>workerAnswer[i].getPosition()){
				masterAnswer[masterAnswerMap[workerAnswer[i].getDataIndex()]].setData(workerAnswer[i].getData());
				masterAnswer[masterAnswerMap[workerAnswer[i].getDataIndex()]].setPosition(workerAnswer[i].getPosition());

			}
		}else{

			masterAnswer.push_back(workerAnswer[i]);
			masterAnswerMap[workerAnswer[i].getDataIndex()]=masterAnswer.size()-1;
		}
	}
}

void queries::QueryServer::clearHeapBuffer(const int index){
	peano::heap::Heap<queries::records::Answer>::getInstance().getData(_heapIds[index]).clear();
	
		
}

void queries::QueryServer::clearQueryBuffer(const int index){
		
   _data[index]->clear();
		
}
void queries::QueryServer::fireAnswers(const int index,int iter){
	if(_sendFlag){
	std::vector<queries::records::Answer>& masterAnswer = peano::heap::Heap<queries::records::Answer>::getInstance().getData(_heapIds[index]);
	unsigned int size=masterAnswer.size();	
	if(size>0){
		double *data = new double [size];
		double *dist = new double [size];
		int *indices = new int [size];
		for(unsigned int i=0;i<size;i++){
			data[i]=masterAnswer[i].getData();
			dist[i]=masterAnswer[i].getPosition();
			indices[i]=masterAnswer[i].getDataIndex();	
		}
		if(_queryServer[index]==NULL){
		     std::string hostname = _mids[index].substr(0,_mids[index].find(":"));
		     std::string port = _mids[index].substr(_mids[index].find(":")+1);
	     	     std::cout<<"establish fireworks for:"<<index<<" "<<hostname<<":"<<port<<std::endl;		
        	     _queryServer[index]=new de::tum::QueryCxx2SocketPlainPort((char*)hostname.c_str(),atoi(port.c_str()),8192);
	
		
		}
        	_queryServer[index]->forwardAnswer(data,size,dist,size,indices,size,iter);
		_timestep++;	
		delete []data;
		delete []dist;
		delete []indices;	
	}
	}

}
void queries::QueryServer::setData(
	const int index,
	const tarch::la::Vector<2,double> &voxelOffset,
	const tarch::la::Vector<2,double> &voxelSize,
	const double x){
	double dx=_pendingQueries[index].getSize()[0]/(double)(_pendingQueries[index].getDimenions()[0]-1);
	double dy=_pendingQueries[index].getSize()[1]/(double)(_pendingQueries[index].getDimenions()[1]-1);
        double ddx=0.0;
        double ddy=0.0;
	double dist=0.0;
        int starti=0;
	int startj=0;
        int endi=0;
	int endj=0;
	
        if(_pendingQueries[index].getOffset()[0]<voxelOffset[0])
		startj=(voxelOffset[0]-_pendingQueries[index].getOffset()[0])/dx;
	if(_pendingQueries[index].getOffset()[1]<voxelOffset[1])
                starti=(voxelOffset[1]-_pendingQueries[index].getOffset()[1])/dy;
	if(voxelOffset[0]+voxelSize[0]<=_pendingQueries[index].getOffset()[0]+_pendingQueries[index].getSize()[0])
		endj=(voxelOffset[0]+voxelSize[0]-_pendingQueries[index].getOffset()[0])/dx+1;
	if(voxelOffset[1]+voxelSize[1]<=_pendingQueries[index].getOffset()[1]+_pendingQueries[index].getSize()[1])
                endi=(voxelOffset[1]+voxelSize[1]-_pendingQueries[index].getOffset()[1])/dy+1;
	for(int i = starti ;i<endi;i++)
		for(int j = startj;j<endj;j++)
		{
			if(
				isInVoxel(
					  voxelOffset,
					  voxelSize,
					  _pendingQueries[index].getOffset()[0]+(double)j*dx,
					  _pendingQueries[index].getOffset()[1]+(double)i*dy)
		
                          ){
				ddx=(voxelOffset[0]-_pendingQueries[index].getOffset()[0]-(double)j*dx);
				ddy=(voxelOffset[1]-_pendingQueries[index].getOffset()[1]-(double)i*dy);
				dist=ddx*ddx+ddy*ddy;
				__gnu_cxx::hash_map< int,std::pair<double,double > >::const_iterator got
					=_data[index]->find(i*_pendingQueries[index].getDimenions()[0]+j);		
			  	if(got==_data[index]->end()){
					(*_data[index])[i*_pendingQueries[index].getDimenions()[0]+j]=std::make_pair<double,double>(0.0,0.0);
					(*_data[index])[i*_pendingQueries[index].getDimenions()[0]+j].second=x;
					(*_data[index])[i*_pendingQueries[index].getDimenions()[0]+j].first=sqrt(dist);
				}else{
					if(sqrt(dist)<(*_data[index])[i*_pendingQueries[index].getDimenions()[0]+j].first){
						(*_data[index])[i*_pendingQueries[index].getDimenions()[0]+j].second=x;
						(*_data[index])[i*_pendingQueries[index].getDimenions()[0]+j].first=sqrt(dist);
				        }
				}
                          }	
		}
}

void queries::QueryServer::setBufferSize(int bufferSize) {
  assertion( bufferSize>0 );
  _bufferSize = bufferSize;
}


void queries::QueryServer::commitQueries() {
  }



