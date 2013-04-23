#include "queries/records/Answer.h"

queries::records::Answer::PersistentRecords::PersistentRecords() {
   
}


queries::records::Answer::PersistentRecords::PersistentRecords(const double& data, const int& dataIndex, const double& position):
_data(data),
_dataIndex(dataIndex),
_position(position) {
   
}


 double queries::records::Answer::PersistentRecords::getData() const  {
   return _data;
}



 void queries::records::Answer::PersistentRecords::setData(const double& data)  {
   _data = data;
}



 int queries::records::Answer::PersistentRecords::getDataIndex() const  {
   return _dataIndex;
}



 void queries::records::Answer::PersistentRecords::setDataIndex(const int& dataIndex)  {
   _dataIndex = dataIndex;
}



 double queries::records::Answer::PersistentRecords::getPosition() const  {
   return _position;
}



 void queries::records::Answer::PersistentRecords::setPosition(const double& position)  {
   _position = position;
}


queries::records::Answer::Answer() {
   
}


queries::records::Answer::Answer(const PersistentRecords& persistentRecords):
_persistentRecords(persistentRecords._data, persistentRecords._dataIndex, persistentRecords._position) {
   
}


queries::records::Answer::Answer(const double& data, const int& dataIndex, const double& position):
_persistentRecords(data, dataIndex, position) {
   
}


queries::records::Answer::~Answer() { }


 double queries::records::Answer::getData() const  {
   return _persistentRecords._data;
}



 void queries::records::Answer::setData(const double& data)  {
   _persistentRecords._data = data;
}



 int queries::records::Answer::getDataIndex() const  {
   return _persistentRecords._dataIndex;
}



 void queries::records::Answer::setDataIndex(const int& dataIndex)  {
   _persistentRecords._dataIndex = dataIndex;
}



 double queries::records::Answer::getPosition() const  {
   return _persistentRecords._position;
}



 void queries::records::Answer::setPosition(const double& position)  {
   _persistentRecords._position = position;
}




std::string queries::records::Answer::toString() const {
   std::ostringstream stringstr;
   toString(stringstr);
   return stringstr.str();
}

void queries::records::Answer::toString (std::ostream& out) const {
   out << "("; 
   out << "data:" << getData();
   out << ",";
   out << "data_index:" << getDataIndex();
   out << ",";
   out << "position:" << getPosition();
   out <<  ")";
}


queries::records::Answer::PersistentRecords queries::records::Answer::getPersistentRecords() const {
   return _persistentRecords;
}

queries::records::AnswerPacked queries::records::Answer::convert() const{
   return AnswerPacked(
      getData(),
      getDataIndex(),
      getPosition()
   );
}

#ifdef Parallel
   tarch::logging::Log queries::records::Answer::_log( "queries::records::Answer" );
   
   MPI_Datatype queries::records::Answer::Datatype = 0;
   MPI_Datatype queries::records::Answer::FullDatatype = 0;
   
   
   void queries::records::Answer::initDatatype() {
      {
         Answer dummyAnswer[2];
         
         const int Attributes = 4;
         MPI_Datatype subtypes[Attributes] = {
            MPI_DOUBLE,		 //data
            MPI_INT,		 //data_index
            MPI_DOUBLE,		 //position
            MPI_UB		 // end/displacement flag
         };
         
         int blocklen[Attributes] = {
            1,		 //data
            1,		 //data_index
            1,		 //position
            1		 // end/displacement flag
         };
         
         MPI_Aint     disp[Attributes];
         
         MPI_Aint base;
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswer[0]))), &base);
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswer[0]._persistentRecords._data))), 		&disp[0] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswer[0]._persistentRecords._dataIndex))), 		&disp[1] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswer[0]._persistentRecords._position))), 		&disp[2] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswer[1]._persistentRecords._data))), 		&disp[3] );
         
         for (int i=1; i<Attributes; i++) {
            assertion1( disp[i] > disp[i-1], i );
         }
         for (int i=0; i<Attributes; i++) {
            disp[i] -= base;
         }
         MPI_Type_struct( Attributes, blocklen, disp, subtypes, &Answer::Datatype );
         MPI_Type_commit( &Answer::Datatype );
         
      }
      {
         Answer dummyAnswer[2];
         
         const int Attributes = 4;
         MPI_Datatype subtypes[Attributes] = {
            MPI_DOUBLE,		 //data
            MPI_INT,		 //data_index
            MPI_DOUBLE,		 //position
            MPI_UB		 // end/displacement flag
         };
         
         int blocklen[Attributes] = {
            1,		 //data
            1,		 //data_index
            1,		 //position
            1		 // end/displacement flag
         };
         
         MPI_Aint     disp[Attributes];
         
         MPI_Aint base;
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswer[0]))), &base);
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswer[0]._persistentRecords._data))), 		&disp[0] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswer[0]._persistentRecords._dataIndex))), 		&disp[1] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswer[0]._persistentRecords._position))), 		&disp[2] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswer[1]._persistentRecords._data))), 		&disp[3] );
         
         for (int i=1; i<Attributes; i++) {
            assertion1( disp[i] > disp[i-1], i );
         }
         for (int i=0; i<Attributes; i++) {
            disp[i] -= base;
         }
         MPI_Type_struct( Attributes, blocklen, disp, subtypes, &Answer::FullDatatype );
         MPI_Type_commit( &Answer::FullDatatype );
         
      }
      
   }
   
   
   void queries::records::Answer::shutdownDatatype() {
      MPI_Type_free( &Answer::Datatype );
      MPI_Type_free( &Answer::FullDatatype );
      
   }
   
   void queries::records::Answer::send(int destination, int tag, bool exchangeOnlyAttributesMarkedWithParallelise) {
      MPI_Request* sendRequestHandle = new MPI_Request();
      MPI_Status   status;
      int          flag = 0;
      int          result;
      
      clock_t      timeOutWarning   = -1;
      clock_t      timeOutShutdown  = -1;
      bool         triggeredTimeoutWarning = false;
      
      #ifdef Asserts
      _senderRank = -1;
      #endif
      
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
         msg << "was not able to send message queries::records::Answer "
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
            msg << "testing for finished send task for queries::records::Answer "
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
            "queries::records::Answer",
            "send(int)", destination,tag,1
            );
            triggeredTimeoutWarning = true;
         }
         if (
            tarch::parallel::Node::getInstance().isTimeOutDeadlockEnabled() &&
            (clock()>timeOutShutdown)
         ) {
            tarch::parallel::Node::getInstance().triggerDeadlockTimeOut(
            "queries::records::Answer",
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
   
   
   
   void queries::records::Answer::receive(int source, int tag, bool exchangeOnlyAttributesMarkedWithParallelise) {
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
         msg << "failed to start to receive queries::records::Answer from node "
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
            msg << "testing for finished receive task for queries::records::Answer failed: "
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
            "queries::records::Answer",
            "receive(int)", source,tag,1
            );
            triggeredTimeoutWarning = true;
         }
         if (
            tarch::parallel::Node::getInstance().isTimeOutDeadlockEnabled() &&
            (clock()>timeOutShutdown)
         ) {
            tarch::parallel::Node::getInstance().triggerDeadlockTimeOut(
            "queries::records::Answer",
            "receive(int)", source,tag,1
            );
         }
         tarch::parallel::Node::getInstance().receiveDanglingMessages();
      }
      
      delete sendRequestHandle;
      
      _senderRank = status.MPI_SOURCE;
      #ifdef Debug
      _log.debug("receive(int,int)", "received " + toString() ); 
      #endif
      
   }
   
   
   
   bool queries::records::Answer::isMessageInQueue(int tag, bool exchangeOnlyAttributesMarkedWithParallelise) {
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
   
   int queries::records::Answer::getSenderRank() const {
      assertion( _senderRank!=-1 );
      return _senderRank;
      
   }
#endif


queries::records::AnswerPacked::PersistentRecords::PersistentRecords() {
   
}


queries::records::AnswerPacked::PersistentRecords::PersistentRecords(const double& data, const int& dataIndex, const double& position):
_data(data),
_dataIndex(dataIndex),
_position(position) {
   
}


 double queries::records::AnswerPacked::PersistentRecords::getData() const  {
   return _data;
}



 void queries::records::AnswerPacked::PersistentRecords::setData(const double& data)  {
   _data = data;
}



 int queries::records::AnswerPacked::PersistentRecords::getDataIndex() const  {
   return _dataIndex;
}



 void queries::records::AnswerPacked::PersistentRecords::setDataIndex(const int& dataIndex)  {
   _dataIndex = dataIndex;
}



 double queries::records::AnswerPacked::PersistentRecords::getPosition() const  {
   return _position;
}



 void queries::records::AnswerPacked::PersistentRecords::setPosition(const double& position)  {
   _position = position;
}


queries::records::AnswerPacked::AnswerPacked() {
   
}


queries::records::AnswerPacked::AnswerPacked(const PersistentRecords& persistentRecords):
_persistentRecords(persistentRecords._data, persistentRecords._dataIndex, persistentRecords._position) {
   
}


queries::records::AnswerPacked::AnswerPacked(const double& data, const int& dataIndex, const double& position):
_persistentRecords(data, dataIndex, position) {
   
}


queries::records::AnswerPacked::~AnswerPacked() { }


 double queries::records::AnswerPacked::getData() const  {
   return _persistentRecords._data;
}



 void queries::records::AnswerPacked::setData(const double& data)  {
   _persistentRecords._data = data;
}



 int queries::records::AnswerPacked::getDataIndex() const  {
   return _persistentRecords._dataIndex;
}



 void queries::records::AnswerPacked::setDataIndex(const int& dataIndex)  {
   _persistentRecords._dataIndex = dataIndex;
}



 double queries::records::AnswerPacked::getPosition() const  {
   return _persistentRecords._position;
}



 void queries::records::AnswerPacked::setPosition(const double& position)  {
   _persistentRecords._position = position;
}




std::string queries::records::AnswerPacked::toString() const {
   std::ostringstream stringstr;
   toString(stringstr);
   return stringstr.str();
}

void queries::records::AnswerPacked::toString (std::ostream& out) const {
   out << "("; 
   out << "data:" << getData();
   out << ",";
   out << "data_index:" << getDataIndex();
   out << ",";
   out << "position:" << getPosition();
   out <<  ")";
}


queries::records::AnswerPacked::PersistentRecords queries::records::AnswerPacked::getPersistentRecords() const {
   return _persistentRecords;
}

queries::records::Answer queries::records::AnswerPacked::convert() const{
   return Answer(
      getData(),
      getDataIndex(),
      getPosition()
   );
}

#ifdef Parallel
   tarch::logging::Log queries::records::AnswerPacked::_log( "queries::records::AnswerPacked" );
   
   MPI_Datatype queries::records::AnswerPacked::Datatype = 0;
   MPI_Datatype queries::records::AnswerPacked::FullDatatype = 0;
   
   
   void queries::records::AnswerPacked::initDatatype() {
      {
         AnswerPacked dummyAnswerPacked[2];
         
         const int Attributes = 4;
         MPI_Datatype subtypes[Attributes] = {
            MPI_DOUBLE,		 //data
            MPI_INT,		 //data_index
            MPI_DOUBLE,		 //position
            MPI_UB		 // end/displacement flag
         };
         
         int blocklen[Attributes] = {
            1,		 //data
            1,		 //data_index
            1,		 //position
            1		 // end/displacement flag
         };
         
         MPI_Aint     disp[Attributes];
         
         MPI_Aint base;
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerPacked[0]))), &base);
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerPacked[0]._persistentRecords._data))), 		&disp[0] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerPacked[0]._persistentRecords._dataIndex))), 		&disp[1] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerPacked[0]._persistentRecords._position))), 		&disp[2] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerPacked[1]._persistentRecords._data))), 		&disp[3] );
         
         for (int i=1; i<Attributes; i++) {
            assertion1( disp[i] > disp[i-1], i );
         }
         for (int i=0; i<Attributes; i++) {
            disp[i] -= base;
         }
         MPI_Type_struct( Attributes, blocklen, disp, subtypes, &AnswerPacked::Datatype );
         MPI_Type_commit( &AnswerPacked::Datatype );
         
      }
      {
         AnswerPacked dummyAnswerPacked[2];
         
         const int Attributes = 4;
         MPI_Datatype subtypes[Attributes] = {
            MPI_DOUBLE,		 //data
            MPI_INT,		 //data_index
            MPI_DOUBLE,		 //position
            MPI_UB		 // end/displacement flag
         };
         
         int blocklen[Attributes] = {
            1,		 //data
            1,		 //data_index
            1,		 //position
            1		 // end/displacement flag
         };
         
         MPI_Aint     disp[Attributes];
         
         MPI_Aint base;
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerPacked[0]))), &base);
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerPacked[0]._persistentRecords._data))), 		&disp[0] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerPacked[0]._persistentRecords._dataIndex))), 		&disp[1] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerPacked[0]._persistentRecords._position))), 		&disp[2] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerPacked[1]._persistentRecords._data))), 		&disp[3] );
         
         for (int i=1; i<Attributes; i++) {
            assertion1( disp[i] > disp[i-1], i );
         }
         for (int i=0; i<Attributes; i++) {
            disp[i] -= base;
         }
         MPI_Type_struct( Attributes, blocklen, disp, subtypes, &AnswerPacked::FullDatatype );
         MPI_Type_commit( &AnswerPacked::FullDatatype );
         
      }
      
   }
   
   
   void queries::records::AnswerPacked::shutdownDatatype() {
      MPI_Type_free( &AnswerPacked::Datatype );
      MPI_Type_free( &AnswerPacked::FullDatatype );
      
   }
   
   void queries::records::AnswerPacked::send(int destination, int tag, bool exchangeOnlyAttributesMarkedWithParallelise) {
      MPI_Request* sendRequestHandle = new MPI_Request();
      MPI_Status   status;
      int          flag = 0;
      int          result;
      
      clock_t      timeOutWarning   = -1;
      clock_t      timeOutShutdown  = -1;
      bool         triggeredTimeoutWarning = false;
      
      #ifdef Asserts
      _senderRank = -1;
      #endif
      
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
         msg << "was not able to send message queries::records::AnswerPacked "
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
            msg << "testing for finished send task for queries::records::AnswerPacked "
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
            "queries::records::AnswerPacked",
            "send(int)", destination,tag,1
            );
            triggeredTimeoutWarning = true;
         }
         if (
            tarch::parallel::Node::getInstance().isTimeOutDeadlockEnabled() &&
            (clock()>timeOutShutdown)
         ) {
            tarch::parallel::Node::getInstance().triggerDeadlockTimeOut(
            "queries::records::AnswerPacked",
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
   
   
   
   void queries::records::AnswerPacked::receive(int source, int tag, bool exchangeOnlyAttributesMarkedWithParallelise) {
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
         msg << "failed to start to receive queries::records::AnswerPacked from node "
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
            msg << "testing for finished receive task for queries::records::AnswerPacked failed: "
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
            "queries::records::AnswerPacked",
            "receive(int)", source,tag,1
            );
            triggeredTimeoutWarning = true;
         }
         if (
            tarch::parallel::Node::getInstance().isTimeOutDeadlockEnabled() &&
            (clock()>timeOutShutdown)
         ) {
            tarch::parallel::Node::getInstance().triggerDeadlockTimeOut(
            "queries::records::AnswerPacked",
            "receive(int)", source,tag,1
            );
         }
         tarch::parallel::Node::getInstance().receiveDanglingMessages();
      }
      
      delete sendRequestHandle;
      
      _senderRank = status.MPI_SOURCE;
      #ifdef Debug
      _log.debug("receive(int,int)", "received " + toString() ); 
      #endif
      
   }
   
   
   
   bool queries::records::AnswerPacked::isMessageInQueue(int tag, bool exchangeOnlyAttributesMarkedWithParallelise) {
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
   
   int queries::records::AnswerPacked::getSenderRank() const {
      assertion( _senderRank!=-1 );
      return _senderRank;
      
   }
#endif



