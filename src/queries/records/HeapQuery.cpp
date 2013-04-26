#include "queries/records/HeapQuery.h"

queries::records::HeapQuery::PersistentRecords::PersistentRecords() {
   
}


queries::records::HeapQuery::PersistentRecords::PersistentRecords(const tarch::la::Vector<3,double>& offset, const tarch::la::Vector<3,double>& size, const tarch::la::Vector<3,int>& dimenions, const int& queriyId, const int& mId):
_offset(offset),
_size(size),
_dimenions(dimenions),
_queriyId(queriyId),
_mId(mId) {
   
}


 tarch::la::Vector<3,double> queries::records::HeapQuery::PersistentRecords::getOffset() const  {
   return _offset;
}



 void queries::records::HeapQuery::PersistentRecords::setOffset(const tarch::la::Vector<3,double>& offset)  {
   _offset = (offset);
}



 tarch::la::Vector<3,double> queries::records::HeapQuery::PersistentRecords::getSize() const  {
   return _size;
}



 void queries::records::HeapQuery::PersistentRecords::setSize(const tarch::la::Vector<3,double>& size)  {
   _size = (size);
}



 tarch::la::Vector<3,int> queries::records::HeapQuery::PersistentRecords::getDimenions() const  {
   return _dimenions;
}



 void queries::records::HeapQuery::PersistentRecords::setDimenions(const tarch::la::Vector<3,int>& dimenions)  {
   _dimenions = (dimenions);
}



 int queries::records::HeapQuery::PersistentRecords::getQueriyId() const  {
   return _queriyId;
}



 void queries::records::HeapQuery::PersistentRecords::setQueriyId(const int& queriyId)  {
   _queriyId = queriyId;
}



 int queries::records::HeapQuery::PersistentRecords::getMId() const  {
   return _mId;
}



 void queries::records::HeapQuery::PersistentRecords::setMId(const int& mId)  {
   _mId = mId;
}


queries::records::HeapQuery::HeapQuery() {
   
}


queries::records::HeapQuery::HeapQuery(const PersistentRecords& persistentRecords):
_persistentRecords(persistentRecords._offset, persistentRecords._size, persistentRecords._dimenions, persistentRecords._queriyId, persistentRecords._mId) {
   
}


queries::records::HeapQuery::HeapQuery(const tarch::la::Vector<3,double>& offset, const tarch::la::Vector<3,double>& size, const tarch::la::Vector<3,int>& dimenions, const int& queriyId, const int& mId):
_persistentRecords(offset, size, dimenions, queriyId, mId) {
   
}


queries::records::HeapQuery::~HeapQuery() { }


 tarch::la::Vector<3,double> queries::records::HeapQuery::getOffset() const  {
   return _persistentRecords._offset;
}



 void queries::records::HeapQuery::setOffset(const tarch::la::Vector<3,double>& offset)  {
   _persistentRecords._offset = (offset);
}



 double queries::records::HeapQuery::getOffset(int elementIndex) const  {
   assertion(elementIndex>=0);
   assertion(elementIndex<3);
   return _persistentRecords._offset[elementIndex];
   
}



 void queries::records::HeapQuery::setOffset(int elementIndex, const double& offset)  {
   assertion(elementIndex>=0);
   assertion(elementIndex<3);
   _persistentRecords._offset[elementIndex]= offset;
   
}



 tarch::la::Vector<3,double> queries::records::HeapQuery::getSize() const  {
   return _persistentRecords._size;
}



 void queries::records::HeapQuery::setSize(const tarch::la::Vector<3,double>& size)  {
   _persistentRecords._size = (size);
}



 double queries::records::HeapQuery::getSize(int elementIndex) const  {
   assertion(elementIndex>=0);
   assertion(elementIndex<3);
   return _persistentRecords._size[elementIndex];
   
}



 void queries::records::HeapQuery::setSize(int elementIndex, const double& size)  {
   assertion(elementIndex>=0);
   assertion(elementIndex<3);
   _persistentRecords._size[elementIndex]= size;
   
}



 tarch::la::Vector<3,int> queries::records::HeapQuery::getDimenions() const  {
   return _persistentRecords._dimenions;
}



 void queries::records::HeapQuery::setDimenions(const tarch::la::Vector<3,int>& dimenions)  {
   _persistentRecords._dimenions = (dimenions);
}



 int queries::records::HeapQuery::getDimenions(int elementIndex) const  {
   assertion(elementIndex>=0);
   assertion(elementIndex<3);
   return _persistentRecords._dimenions[elementIndex];
   
}



 void queries::records::HeapQuery::setDimenions(int elementIndex, const int& dimenions)  {
   assertion(elementIndex>=0);
   assertion(elementIndex<3);
   _persistentRecords._dimenions[elementIndex]= dimenions;
   
}



 int queries::records::HeapQuery::getQueriyId() const  {
   return _persistentRecords._queriyId;
}



 void queries::records::HeapQuery::setQueriyId(const int& queriyId)  {
   _persistentRecords._queriyId = queriyId;
}



 int queries::records::HeapQuery::getMId() const  {
   return _persistentRecords._mId;
}



 void queries::records::HeapQuery::setMId(const int& mId)  {
   _persistentRecords._mId = mId;
}




std::string queries::records::HeapQuery::toString() const {
   std::ostringstream stringstr;
   toString(stringstr);
   return stringstr.str();
}

void queries::records::HeapQuery::toString (std::ostream& out) const {
   out << "("; 
   out << "offset:[";
   for (int i = 0; i < 3-1; i++) {
      out << getOffset(i) << ",";
   }
   out << getOffset(3-1) << "]";
   out << ",";
   out << "size:[";
   for (int i = 0; i < 3-1; i++) {
      out << getSize(i) << ",";
   }
   out << getSize(3-1) << "]";
   out << ",";
   out << "dimenions:[";
   for (int i = 0; i < 3-1; i++) {
      out << getDimenions(i) << ",";
   }
   out << getDimenions(3-1) << "]";
   out << ",";
   out << "queriy_id:" << getQueriyId();
   out << ",";
   out << "m_id:" << getMId();
   out <<  ")";
}


queries::records::HeapQuery::PersistentRecords queries::records::HeapQuery::getPersistentRecords() const {
   return _persistentRecords;
}

queries::records::HeapQueryPacked queries::records::HeapQuery::convert() const{
   return HeapQueryPacked(
      getOffset(),
      getSize(),
      getDimenions(),
      getQueriyId(),
      getMId()
   );
}

#ifdef Parallel
   tarch::logging::Log queries::records::HeapQuery::_log( "queries::records::HeapQuery" );
   
   MPI_Datatype queries::records::HeapQuery::Datatype = 0;
   MPI_Datatype queries::records::HeapQuery::FullDatatype = 0;
   
   
   void queries::records::HeapQuery::initDatatype() {
      {
         HeapQuery dummyHeapQuery[2];
         
         const int Attributes = 4;
         MPI_Datatype subtypes[Attributes] = {
            MPI_DOUBLE,		 //offset
            MPI_DOUBLE,		 //size
            MPI_INT,		 //dimenions
            MPI_UB		 // end/displacement flag
         };
         
         int blocklen[Attributes] = {
            3,		 //offset
            3,		 //size
            3,		 //dimenions
            1		 // end/displacement flag
         };
         
         MPI_Aint     disp[Attributes];
         
         MPI_Aint base;
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQuery[0]))), &base);
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQuery[0]._persistentRecords._offset[0]))), 		&disp[0] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQuery[0]._persistentRecords._size[0]))), 		&disp[1] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQuery[0]._persistentRecords._dimenions[0]))), 		&disp[2] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&dummyHeapQuery[1]._persistentRecords._offset[0])), 		&disp[3] );
         
         for (int i=1; i<Attributes; i++) {
            assertion1( disp[i] > disp[i-1], i );
         }
         for (int i=0; i<Attributes; i++) {
            disp[i] -= base;
         }
         MPI_Type_struct( Attributes, blocklen, disp, subtypes, &HeapQuery::Datatype );
         MPI_Type_commit( &HeapQuery::Datatype );
         
      }
      {
         HeapQuery dummyHeapQuery[2];
         
         const int Attributes = 6;
         MPI_Datatype subtypes[Attributes] = {
            MPI_DOUBLE,		 //offset
            MPI_DOUBLE,		 //size
            MPI_INT,		 //dimenions
            MPI_INT,		 //queriy_id
            MPI_INT,		 //m_id
            MPI_UB		 // end/displacement flag
         };
         
         int blocklen[Attributes] = {
            3,		 //offset
            3,		 //size
            3,		 //dimenions
            1,		 //queriy_id
            1,		 //m_id
            1		 // end/displacement flag
         };
         
         MPI_Aint     disp[Attributes];
         
         MPI_Aint base;
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQuery[0]))), &base);
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQuery[0]._persistentRecords._offset[0]))), 		&disp[0] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQuery[0]._persistentRecords._size[0]))), 		&disp[1] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQuery[0]._persistentRecords._dimenions[0]))), 		&disp[2] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQuery[0]._persistentRecords._queriyId))), 		&disp[3] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQuery[0]._persistentRecords._mId))), 		&disp[4] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&dummyHeapQuery[1]._persistentRecords._offset[0])), 		&disp[5] );
         
         for (int i=1; i<Attributes; i++) {
            assertion1( disp[i] > disp[i-1], i );
         }
         for (int i=0; i<Attributes; i++) {
            disp[i] -= base;
         }
         MPI_Type_struct( Attributes, blocklen, disp, subtypes, &HeapQuery::FullDatatype );
         MPI_Type_commit( &HeapQuery::FullDatatype );
         
      }
      
   }
   
   
   void queries::records::HeapQuery::shutdownDatatype() {
      MPI_Type_free( &HeapQuery::Datatype );
      MPI_Type_free( &HeapQuery::FullDatatype );
      
   }
   
   void queries::records::HeapQuery::send(int destination, int tag, bool exchangeOnlyAttributesMarkedWithParallelise) {
      MPI_Request* sendRequestHandle = new MPI_Request();
      MPI_Status   status;
      int          flag = 0;
      int          result;
      
      clock_t      timeOutWarning   = -1;
      clock_t      timeOutShutdown  = -1;
      bool         triggeredTimeoutWarning = false;
      
      if (exchangeOnlyAttributesMarkedWithParallelise) {
         result = MPI_Isend(
            this, 1, Datatype, destination,
            tag, tarch::parallel::Node::getInstance().getCommunicator(),
            sendRequestHandle
         );
         
      }
      else {
         result = MPI_Isend(
            this, 1, FullDatatype, destination,
            tag, tarch::parallel::Node::getInstance().getCommunicator(),
            sendRequestHandle
         );
         
      }
      if  (result!=MPI_SUCCESS) {
         std::ostringstream msg;
         msg << "was not able to send message queries::records::HeapQuery "
         << toString()
         << " to node " << destination
         << ": " << tarch::parallel::MPIReturnValueToString(result);
         _log.error( "send(int)",msg.str() );
      }
      result = MPI_Test( sendRequestHandle, &flag, &status );
      while (!flag) {
         if (timeOutWarning==-1)   timeOutWarning   = tarch::parallel::Node::getInstance().getDeadlockWarningTimeStamp();
         if (timeOutShutdown==-1)  timeOutShutdown  = tarch::parallel::Node::getInstance().getDeadlockTimeOutTimeStamp();
         result = MPI_Test( sendRequestHandle, &flag, &status );
         if (result!=MPI_SUCCESS) {
            std::ostringstream msg;
            msg << "testing for finished send task for queries::records::HeapQuery "
            << toString()
            << " sent to node " << destination
            << " failed: " << tarch::parallel::MPIReturnValueToString(result);
            _log.error("send(int)", msg.str() );
         }
         
         // deadlock aspect
         if (
            tarch::parallel::Node::getInstance().isTimeOutWarningEnabled() &&
            (clock()>timeOutWarning) &&
            (!triggeredTimeoutWarning)
         ) {
            tarch::parallel::Node::getInstance().writeTimeOutWarning(
            "queries::records::HeapQuery",
            "send(int)", destination,tag,1
            );
            triggeredTimeoutWarning = true;
         }
         if (
            tarch::parallel::Node::getInstance().isTimeOutDeadlockEnabled() &&
            (clock()>timeOutShutdown)
         ) {
            tarch::parallel::Node::getInstance().triggerDeadlockTimeOut(
            "queries::records::HeapQuery",
            "send(int)", destination,tag,1
            );
         }
         tarch::parallel::Node::getInstance().receiveDanglingMessages();
      }
      
      delete sendRequestHandle;
      #ifdef Debug
      _log.debug("send(int,int)", "sent " + toString() );
      #endif
      
   }
   
   
   
   void queries::records::HeapQuery::receive(int source, int tag, bool exchangeOnlyAttributesMarkedWithParallelise) {
      MPI_Request* sendRequestHandle = new MPI_Request();
      MPI_Status   status;
      int          flag = 0;
      int          result;
      
      clock_t      timeOutWarning   = -1;
      clock_t      timeOutShutdown  = -1;
      bool         triggeredTimeoutWarning = false;
      
      if (exchangeOnlyAttributesMarkedWithParallelise) {
         result = MPI_Irecv(
            this, 1, Datatype, source, tag,
            tarch::parallel::Node::getInstance().getCommunicator(), sendRequestHandle
         );
         
      }
      else {
         result = MPI_Irecv(
            this, 1, FullDatatype, source, tag,
            tarch::parallel::Node::getInstance().getCommunicator(), sendRequestHandle
         );
         
      }
      if ( result != MPI_SUCCESS ) {
         std::ostringstream msg;
         msg << "failed to start to receive queries::records::HeapQuery from node "
         << source << ": " << tarch::parallel::MPIReturnValueToString(result);
         _log.error( "receive(int)", msg.str() );
      }
      
      result = MPI_Test( sendRequestHandle, &flag, &status );
      while (!flag) {
         if (timeOutWarning==-1)   timeOutWarning   = tarch::parallel::Node::getInstance().getDeadlockWarningTimeStamp();
         if (timeOutShutdown==-1)  timeOutShutdown  = tarch::parallel::Node::getInstance().getDeadlockTimeOutTimeStamp();
         result = MPI_Test( sendRequestHandle, &flag, &status );
         if (result!=MPI_SUCCESS) {
            std::ostringstream msg;
            msg << "testing for finished receive task for queries::records::HeapQuery failed: "
            << tarch::parallel::MPIReturnValueToString(result);
            _log.error("receive(int)", msg.str() );
         }
         
         // deadlock aspect
         if (
            tarch::parallel::Node::getInstance().isTimeOutWarningEnabled() &&
            (clock()>timeOutWarning) &&
            (!triggeredTimeoutWarning)
         ) {
            tarch::parallel::Node::getInstance().writeTimeOutWarning(
            "queries::records::HeapQuery",
            "receive(int)", source,tag,1
            );
            triggeredTimeoutWarning = true;
         }
         if (
            tarch::parallel::Node::getInstance().isTimeOutDeadlockEnabled() &&
            (clock()>timeOutShutdown)
         ) {
            tarch::parallel::Node::getInstance().triggerDeadlockTimeOut(
            "queries::records::HeapQuery",
            "receive(int)", source,tag,1
            );
         }
         tarch::parallel::Node::getInstance().receiveDanglingMessages();
      }
      
      delete sendRequestHandle;
      
      #ifdef Debug
      _log.debug("receive(int,int)", "received " + toString() ); 
      #endif
      
   }
   
   
   
   bool queries::records::HeapQuery::isMessageInQueue(int tag, bool exchangeOnlyAttributesMarkedWithParallelise) {
      MPI_Status status;
      int  flag        = 0;
      MPI_Iprobe(
         MPI_ANY_SOURCE, tag,
         tarch::parallel::Node::getInstance().getCommunicator(), &flag, &status
      );
      if (flag) {
         int  messageCounter;
         if (exchangeOnlyAttributesMarkedWithParallelise) {
            MPI_Get_count(&status, Datatype, &messageCounter);
         }
         else {
            MPI_Get_count(&status, FullDatatype, &messageCounter);
         }
         return messageCounter > 0;
      }
      else return false;
      
   }
   
   
#endif


queries::records::HeapQueryPacked::PersistentRecords::PersistentRecords() {
   
}


queries::records::HeapQueryPacked::PersistentRecords::PersistentRecords(const tarch::la::Vector<3,double>& offset, const tarch::la::Vector<3,double>& size, const tarch::la::Vector<3,int>& dimenions, const int& queriyId, const int& mId):
_offset(offset),
_size(size),
_dimenions(dimenions),
_queriyId(queriyId),
_mId(mId) {
   
}


 tarch::la::Vector<3,double> queries::records::HeapQueryPacked::PersistentRecords::getOffset() const  {
   return _offset;
}



 void queries::records::HeapQueryPacked::PersistentRecords::setOffset(const tarch::la::Vector<3,double>& offset)  {
   _offset = (offset);
}



 tarch::la::Vector<3,double> queries::records::HeapQueryPacked::PersistentRecords::getSize() const  {
   return _size;
}



 void queries::records::HeapQueryPacked::PersistentRecords::setSize(const tarch::la::Vector<3,double>& size)  {
   _size = (size);
}



 tarch::la::Vector<3,int> queries::records::HeapQueryPacked::PersistentRecords::getDimenions() const  {
   return _dimenions;
}



 void queries::records::HeapQueryPacked::PersistentRecords::setDimenions(const tarch::la::Vector<3,int>& dimenions)  {
   _dimenions = (dimenions);
}



 int queries::records::HeapQueryPacked::PersistentRecords::getQueriyId() const  {
   return _queriyId;
}



 void queries::records::HeapQueryPacked::PersistentRecords::setQueriyId(const int& queriyId)  {
   _queriyId = queriyId;
}



 int queries::records::HeapQueryPacked::PersistentRecords::getMId() const  {
   return _mId;
}



 void queries::records::HeapQueryPacked::PersistentRecords::setMId(const int& mId)  {
   _mId = mId;
}


queries::records::HeapQueryPacked::HeapQueryPacked() {
   
}


queries::records::HeapQueryPacked::HeapQueryPacked(const PersistentRecords& persistentRecords):
_persistentRecords(persistentRecords._offset, persistentRecords._size, persistentRecords._dimenions, persistentRecords._queriyId, persistentRecords._mId) {
   
}


queries::records::HeapQueryPacked::HeapQueryPacked(const tarch::la::Vector<3,double>& offset, const tarch::la::Vector<3,double>& size, const tarch::la::Vector<3,int>& dimenions, const int& queriyId, const int& mId):
_persistentRecords(offset, size, dimenions, queriyId, mId) {
   
}


queries::records::HeapQueryPacked::~HeapQueryPacked() { }


 tarch::la::Vector<3,double> queries::records::HeapQueryPacked::getOffset() const  {
   return _persistentRecords._offset;
}



 void queries::records::HeapQueryPacked::setOffset(const tarch::la::Vector<3,double>& offset)  {
   _persistentRecords._offset = (offset);
}



 double queries::records::HeapQueryPacked::getOffset(int elementIndex) const  {
   assertion(elementIndex>=0);
   assertion(elementIndex<3);
   return _persistentRecords._offset[elementIndex];
   
}



 void queries::records::HeapQueryPacked::setOffset(int elementIndex, const double& offset)  {
   assertion(elementIndex>=0);
   assertion(elementIndex<3);
   _persistentRecords._offset[elementIndex]= offset;
   
}



 tarch::la::Vector<3,double> queries::records::HeapQueryPacked::getSize() const  {
   return _persistentRecords._size;
}



 void queries::records::HeapQueryPacked::setSize(const tarch::la::Vector<3,double>& size)  {
   _persistentRecords._size = (size);
}



 double queries::records::HeapQueryPacked::getSize(int elementIndex) const  {
   assertion(elementIndex>=0);
   assertion(elementIndex<3);
   return _persistentRecords._size[elementIndex];
   
}



 void queries::records::HeapQueryPacked::setSize(int elementIndex, const double& size)  {
   assertion(elementIndex>=0);
   assertion(elementIndex<3);
   _persistentRecords._size[elementIndex]= size;
   
}



 tarch::la::Vector<3,int> queries::records::HeapQueryPacked::getDimenions() const  {
   return _persistentRecords._dimenions;
}



 void queries::records::HeapQueryPacked::setDimenions(const tarch::la::Vector<3,int>& dimenions)  {
   _persistentRecords._dimenions = (dimenions);
}



 int queries::records::HeapQueryPacked::getDimenions(int elementIndex) const  {
   assertion(elementIndex>=0);
   assertion(elementIndex<3);
   return _persistentRecords._dimenions[elementIndex];
   
}



 void queries::records::HeapQueryPacked::setDimenions(int elementIndex, const int& dimenions)  {
   assertion(elementIndex>=0);
   assertion(elementIndex<3);
   _persistentRecords._dimenions[elementIndex]= dimenions;
   
}



 int queries::records::HeapQueryPacked::getQueriyId() const  {
   return _persistentRecords._queriyId;
}



 void queries::records::HeapQueryPacked::setQueriyId(const int& queriyId)  {
   _persistentRecords._queriyId = queriyId;
}



 int queries::records::HeapQueryPacked::getMId() const  {
   return _persistentRecords._mId;
}



 void queries::records::HeapQueryPacked::setMId(const int& mId)  {
   _persistentRecords._mId = mId;
}




std::string queries::records::HeapQueryPacked::toString() const {
   std::ostringstream stringstr;
   toString(stringstr);
   return stringstr.str();
}

void queries::records::HeapQueryPacked::toString (std::ostream& out) const {
   out << "("; 
   out << "offset:[";
   for (int i = 0; i < 3-1; i++) {
      out << getOffset(i) << ",";
   }
   out << getOffset(3-1) << "]";
   out << ",";
   out << "size:[";
   for (int i = 0; i < 3-1; i++) {
      out << getSize(i) << ",";
   }
   out << getSize(3-1) << "]";
   out << ",";
   out << "dimenions:[";
   for (int i = 0; i < 3-1; i++) {
      out << getDimenions(i) << ",";
   }
   out << getDimenions(3-1) << "]";
   out << ",";
   out << "queriy_id:" << getQueriyId();
   out << ",";
   out << "m_id:" << getMId();
   out <<  ")";
}


queries::records::HeapQueryPacked::PersistentRecords queries::records::HeapQueryPacked::getPersistentRecords() const {
   return _persistentRecords;
}

queries::records::HeapQuery queries::records::HeapQueryPacked::convert() const{
   return HeapQuery(
      getOffset(),
      getSize(),
      getDimenions(),
      getQueriyId(),
      getMId()
   );
}

#ifdef Parallel
   tarch::logging::Log queries::records::HeapQueryPacked::_log( "queries::records::HeapQueryPacked" );
   
   MPI_Datatype queries::records::HeapQueryPacked::Datatype = 0;
   MPI_Datatype queries::records::HeapQueryPacked::FullDatatype = 0;
   
   
   void queries::records::HeapQueryPacked::initDatatype() {
      {
         HeapQueryPacked dummyHeapQueryPacked[2];
         
         const int Attributes = 4;
         MPI_Datatype subtypes[Attributes] = {
            MPI_DOUBLE,		 //offset
            MPI_DOUBLE,		 //size
            MPI_INT,		 //dimenions
            MPI_UB		 // end/displacement flag
         };
         
         int blocklen[Attributes] = {
            3,		 //offset
            3,		 //size
            3,		 //dimenions
            1		 // end/displacement flag
         };
         
         MPI_Aint     disp[Attributes];
         
         MPI_Aint base;
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQueryPacked[0]))), &base);
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQueryPacked[0]._persistentRecords._offset[0]))), 		&disp[0] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQueryPacked[0]._persistentRecords._size[0]))), 		&disp[1] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQueryPacked[0]._persistentRecords._dimenions[0]))), 		&disp[2] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&dummyHeapQueryPacked[1]._persistentRecords._offset[0])), 		&disp[3] );
         
         for (int i=1; i<Attributes; i++) {
            assertion1( disp[i] > disp[i-1], i );
         }
         for (int i=0; i<Attributes; i++) {
            disp[i] -= base;
         }
         MPI_Type_struct( Attributes, blocklen, disp, subtypes, &HeapQueryPacked::Datatype );
         MPI_Type_commit( &HeapQueryPacked::Datatype );
         
      }
      {
         HeapQueryPacked dummyHeapQueryPacked[2];
         
         const int Attributes = 6;
         MPI_Datatype subtypes[Attributes] = {
            MPI_DOUBLE,		 //offset
            MPI_DOUBLE,		 //size
            MPI_INT,		 //dimenions
            MPI_INT,		 //queriy_id
            MPI_INT,		 //m_id
            MPI_UB		 // end/displacement flag
         };
         
         int blocklen[Attributes] = {
            3,		 //offset
            3,		 //size
            3,		 //dimenions
            1,		 //queriy_id
            1,		 //m_id
            1		 // end/displacement flag
         };
         
         MPI_Aint     disp[Attributes];
         
         MPI_Aint base;
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQueryPacked[0]))), &base);
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQueryPacked[0]._persistentRecords._offset[0]))), 		&disp[0] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQueryPacked[0]._persistentRecords._size[0]))), 		&disp[1] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQueryPacked[0]._persistentRecords._dimenions[0]))), 		&disp[2] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQueryPacked[0]._persistentRecords._queriyId))), 		&disp[3] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyHeapQueryPacked[0]._persistentRecords._mId))), 		&disp[4] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&dummyHeapQueryPacked[1]._persistentRecords._offset[0])), 		&disp[5] );
         
         for (int i=1; i<Attributes; i++) {
            assertion1( disp[i] > disp[i-1], i );
         }
         for (int i=0; i<Attributes; i++) {
            disp[i] -= base;
         }
         MPI_Type_struct( Attributes, blocklen, disp, subtypes, &HeapQueryPacked::FullDatatype );
         MPI_Type_commit( &HeapQueryPacked::FullDatatype );
         
      }
      
   }
   
   
   void queries::records::HeapQueryPacked::shutdownDatatype() {
      MPI_Type_free( &HeapQueryPacked::Datatype );
      MPI_Type_free( &HeapQueryPacked::FullDatatype );
      
   }
   
   void queries::records::HeapQueryPacked::send(int destination, int tag, bool exchangeOnlyAttributesMarkedWithParallelise) {
      MPI_Request* sendRequestHandle = new MPI_Request();
      MPI_Status   status;
      int          flag = 0;
      int          result;
      
      clock_t      timeOutWarning   = -1;
      clock_t      timeOutShutdown  = -1;
      bool         triggeredTimeoutWarning = false;
      
      if (exchangeOnlyAttributesMarkedWithParallelise) {
         result = MPI_Isend(
            this, 1, Datatype, destination,
            tag, tarch::parallel::Node::getInstance().getCommunicator(),
            sendRequestHandle
         );
         
      }
      else {
         result = MPI_Isend(
            this, 1, FullDatatype, destination,
            tag, tarch::parallel::Node::getInstance().getCommunicator(),
            sendRequestHandle
         );
         
      }
      if  (result!=MPI_SUCCESS) {
         std::ostringstream msg;
         msg << "was not able to send message queries::records::HeapQueryPacked "
         << toString()
         << " to node " << destination
         << ": " << tarch::parallel::MPIReturnValueToString(result);
         _log.error( "send(int)",msg.str() );
      }
      result = MPI_Test( sendRequestHandle, &flag, &status );
      while (!flag) {
         if (timeOutWarning==-1)   timeOutWarning   = tarch::parallel::Node::getInstance().getDeadlockWarningTimeStamp();
         if (timeOutShutdown==-1)  timeOutShutdown  = tarch::parallel::Node::getInstance().getDeadlockTimeOutTimeStamp();
         result = MPI_Test( sendRequestHandle, &flag, &status );
         if (result!=MPI_SUCCESS) {
            std::ostringstream msg;
            msg << "testing for finished send task for queries::records::HeapQueryPacked "
            << toString()
            << " sent to node " << destination
            << " failed: " << tarch::parallel::MPIReturnValueToString(result);
            _log.error("send(int)", msg.str() );
         }
         
         // deadlock aspect
         if (
            tarch::parallel::Node::getInstance().isTimeOutWarningEnabled() &&
            (clock()>timeOutWarning) &&
            (!triggeredTimeoutWarning)
         ) {
            tarch::parallel::Node::getInstance().writeTimeOutWarning(
            "queries::records::HeapQueryPacked",
            "send(int)", destination,tag,1
            );
            triggeredTimeoutWarning = true;
         }
         if (
            tarch::parallel::Node::getInstance().isTimeOutDeadlockEnabled() &&
            (clock()>timeOutShutdown)
         ) {
            tarch::parallel::Node::getInstance().triggerDeadlockTimeOut(
            "queries::records::HeapQueryPacked",
            "send(int)", destination,tag,1
            );
         }
         tarch::parallel::Node::getInstance().receiveDanglingMessages();
      }
      
      delete sendRequestHandle;
      #ifdef Debug
      _log.debug("send(int,int)", "sent " + toString() );
      #endif
      
   }
   
   
   
   void queries::records::HeapQueryPacked::receive(int source, int tag, bool exchangeOnlyAttributesMarkedWithParallelise) {
      MPI_Request* sendRequestHandle = new MPI_Request();
      MPI_Status   status;
      int          flag = 0;
      int          result;
      
      clock_t      timeOutWarning   = -1;
      clock_t      timeOutShutdown  = -1;
      bool         triggeredTimeoutWarning = false;
      
      if (exchangeOnlyAttributesMarkedWithParallelise) {
         result = MPI_Irecv(
            this, 1, Datatype, source, tag,
            tarch::parallel::Node::getInstance().getCommunicator(), sendRequestHandle
         );
         
      }
      else {
         result = MPI_Irecv(
            this, 1, FullDatatype, source, tag,
            tarch::parallel::Node::getInstance().getCommunicator(), sendRequestHandle
         );
         
      }
      if ( result != MPI_SUCCESS ) {
         std::ostringstream msg;
         msg << "failed to start to receive queries::records::HeapQueryPacked from node "
         << source << ": " << tarch::parallel::MPIReturnValueToString(result);
         _log.error( "receive(int)", msg.str() );
      }
      
      result = MPI_Test( sendRequestHandle, &flag, &status );
      while (!flag) {
         if (timeOutWarning==-1)   timeOutWarning   = tarch::parallel::Node::getInstance().getDeadlockWarningTimeStamp();
         if (timeOutShutdown==-1)  timeOutShutdown  = tarch::parallel::Node::getInstance().getDeadlockTimeOutTimeStamp();
         result = MPI_Test( sendRequestHandle, &flag, &status );
         if (result!=MPI_SUCCESS) {
            std::ostringstream msg;
            msg << "testing for finished receive task for queries::records::HeapQueryPacked failed: "
            << tarch::parallel::MPIReturnValueToString(result);
            _log.error("receive(int)", msg.str() );
         }
         
         // deadlock aspect
         if (
            tarch::parallel::Node::getInstance().isTimeOutWarningEnabled() &&
            (clock()>timeOutWarning) &&
            (!triggeredTimeoutWarning)
         ) {
            tarch::parallel::Node::getInstance().writeTimeOutWarning(
            "queries::records::HeapQueryPacked",
            "receive(int)", source,tag,1
            );
            triggeredTimeoutWarning = true;
         }
         if (
            tarch::parallel::Node::getInstance().isTimeOutDeadlockEnabled() &&
            (clock()>timeOutShutdown)
         ) {
            tarch::parallel::Node::getInstance().triggerDeadlockTimeOut(
            "queries::records::HeapQueryPacked",
            "receive(int)", source,tag,1
            );
         }
         tarch::parallel::Node::getInstance().receiveDanglingMessages();
      }
      
      delete sendRequestHandle;
      
      #ifdef Debug
      _log.debug("receive(int,int)", "received " + toString() ); 
      #endif
      
   }
   
   
   
   bool queries::records::HeapQueryPacked::isMessageInQueue(int tag, bool exchangeOnlyAttributesMarkedWithParallelise) {
      MPI_Status status;
      int  flag        = 0;
      MPI_Iprobe(
         MPI_ANY_SOURCE, tag,
         tarch::parallel::Node::getInstance().getCommunicator(), &flag, &status
      );
      if (flag) {
         int  messageCounter;
         if (exchangeOnlyAttributesMarkedWithParallelise) {
            MPI_Get_count(&status, Datatype, &messageCounter);
         }
         else {
            MPI_Get_count(&status, FullDatatype, &messageCounter);
         }
         return messageCounter > 0;
      }
      else return false;
      
   }
   
   
#endif



