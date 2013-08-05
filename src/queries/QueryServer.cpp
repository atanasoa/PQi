#include "queries/QueryServer.h"
//#include "peano/integration/dataqueries/CartesianGridWriterProxy.h"


#ifdef Parallel
#include "tarch/parallel/Node.h"
#include "tarch/parallel/NodePool.h"
#endif


#include "tarch/services/ServiceFactory.h"
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
      receiveIncomingQueryData();
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
  queries::records::HeapQuery newQuery
) {
  if(!init)
#ifdef Parallel
        queries::records::HeapQuery::initDatatype();
#endif
        init=true;
  //newQuery.setId( getNumberOfPendingQueries() );
  _pendingQueries.push_back(
    newQuery
  );
  #ifdef Parallel
  assertion( tarch::parallel::Node::getInstance().isGlobalMaster() );
  tarch::parallel::NodePool::getInstance().broadcastToWorkingNodes(newQuery, _managementTag);
  #endif
}


void queries::QueryServer::setBufferSize(int bufferSize) {
  assertion( bufferSize>0 );
  _bufferSize = bufferSize;
}


void queries::QueryServer::commitQueries() {
  if(!init)
#ifdef Parallel
        queries::records::HeapQuery::initDatatype();
#endif
        init=true;
  #ifdef Parallel
  if ( tarch::parallel::Node::getInstance().isGlobalMaster() ) {
    while (_finishedDataSendAcknowledgementsSinceLastReleaseCall < tarch::parallel::NodePool::getInstance().getNumberOfWorkingNodes()) {
      receiveDanglingMessages();
    }
    /*for (std::vector<queries::records::HeapQuery>::iterator p = _pendingQueries.begin(); p!=_pendingQueries.end(); p++) {

        p->closeAndDeleteDataWriter();
    }*/
    _pendingQueries.clear();

    _finishedDataSendAcknowledgementsSinceLastReleaseCall = 0;
  }
  else {

    /*for (std::vector<queries::records::HeapQuery>::iterator p = _pendingQueries.begin(); p!=_pendingQueries.end(); p++) {
      p->closeAndDeleteDataWriter();
    }*/

    _pendingQueries.clear();
    //CartesianGridWriterProxy::sendFinishedAcknowledgment(_dataTag);
  }
  #else
    //for (std::vector<Query>::iterator p = _pendingQueries.begin(); p!=_pendingQueries.end(); p++) {
    //  p->closeAndDeleteDataWriter();
    //}
    _pendingQueries.clear();
  #endif
}



