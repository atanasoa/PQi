#include "queries/records/AnswerConfiguration.h"

queries::records::AnswerConfiguration::PersistentRecords::PersistentRecords() {
   
}


queries::records::AnswerConfiguration::PersistentRecords::PersistentRecords(const int& qid, const int& scopeid, const int& card):
_qid(qid),
_scopeid(scopeid),
_card(card) {
   
}


 int queries::records::AnswerConfiguration::PersistentRecords::getQid() const  {
   return _qid;
}



 void queries::records::AnswerConfiguration::PersistentRecords::setQid(const int& qid)  {
   _qid = qid;
}



 int queries::records::AnswerConfiguration::PersistentRecords::getScopeid() const  {
   return _scopeid;
}



 void queries::records::AnswerConfiguration::PersistentRecords::setScopeid(const int& scopeid)  {
   _scopeid = scopeid;
}



 int queries::records::AnswerConfiguration::PersistentRecords::getCard() const  {
   return _card;
}



 void queries::records::AnswerConfiguration::PersistentRecords::setCard(const int& card)  {
   _card = card;
}


queries::records::AnswerConfiguration::AnswerConfiguration() {
   
}


queries::records::AnswerConfiguration::AnswerConfiguration(const PersistentRecords& persistentRecords):
_persistentRecords(persistentRecords._qid, persistentRecords._scopeid, persistentRecords._card) {
   
}


queries::records::AnswerConfiguration::AnswerConfiguration(const int& qid, const int& scopeid, const int& card):
_persistentRecords(qid, scopeid, card) {
   
}


queries::records::AnswerConfiguration::~AnswerConfiguration() { }


 int queries::records::AnswerConfiguration::getQid() const  {
   return _persistentRecords._qid;
}



 void queries::records::AnswerConfiguration::setQid(const int& qid)  {
   _persistentRecords._qid = qid;
}



 int queries::records::AnswerConfiguration::getScopeid() const  {
   return _persistentRecords._scopeid;
}



 void queries::records::AnswerConfiguration::setScopeid(const int& scopeid)  {
   _persistentRecords._scopeid = scopeid;
}



 int queries::records::AnswerConfiguration::getCard() const  {
   return _persistentRecords._card;
}



 void queries::records::AnswerConfiguration::setCard(const int& card)  {
   _persistentRecords._card = card;
}




std::string queries::records::AnswerConfiguration::toString() const {
   std::ostringstream stringstr;
   toString(stringstr);
   return stringstr.str();
}

void queries::records::AnswerConfiguration::toString (std::ostream& out) const {
   out << "("; 
   out << "qid:" << getQid();
   out << ",";
   out << "scopeid:" << getScopeid();
   out << ",";
   out << "card:" << getCard();
   out <<  ")";
}


queries::records::AnswerConfiguration::PersistentRecords queries::records::AnswerConfiguration::getPersistentRecords() const {
   return _persistentRecords;
}

queries::records::AnswerConfigurationPacked queries::records::AnswerConfiguration::convert() const{
   return AnswerConfigurationPacked(
      getQid(),
      getScopeid(),
      getCard()
   );
}

#ifdef Parallel
   tarch::logging::Log queries::records::AnswerConfiguration::_log( "queries::records::AnswerConfiguration" );
   
   MPI_Datatype queries::records::AnswerConfiguration::Datatype = 0;
   MPI_Datatype queries::records::AnswerConfiguration::FullDatatype = 0;
   
   
   void queries::records::AnswerConfiguration::initDatatype() {
      {
         AnswerConfiguration dummyAnswerConfiguration[2];
         
         const int Attributes = 4;
         MPI_Datatype subtypes[Attributes] = {
            MPI_INT,		 //qid
            MPI_INT,		 //scopeid
            MPI_INT,		 //card
            MPI_UB		 // end/displacement flag
         };
         
         int blocklen[Attributes] = {
            1,		 //qid
            1,		 //scopeid
            1,		 //card
            1		 // end/displacement flag
         };
         
         MPI_Aint     disp[Attributes];
         
         MPI_Aint base;
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfiguration[0]))), &base);
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfiguration[0]._persistentRecords._qid))), 		&disp[0] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfiguration[0]._persistentRecords._scopeid))), 		&disp[1] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfiguration[0]._persistentRecords._card))), 		&disp[2] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfiguration[1]._persistentRecords._qid))), 		&disp[3] );
         
         for (int i=1; i<Attributes; i++) {
            assertion1( disp[i] > disp[i-1], i );
         }
         for (int i=0; i<Attributes; i++) {
            disp[i] -= base;
         }
         MPI_Type_struct( Attributes, blocklen, disp, subtypes, &AnswerConfiguration::Datatype );
         MPI_Type_commit( &AnswerConfiguration::Datatype );
         
      }
      {
         AnswerConfiguration dummyAnswerConfiguration[2];
         
         const int Attributes = 4;
         MPI_Datatype subtypes[Attributes] = {
            MPI_INT,		 //qid
            MPI_INT,		 //scopeid
            MPI_INT,		 //card
            MPI_UB		 // end/displacement flag
         };
         
         int blocklen[Attributes] = {
            1,		 //qid
            1,		 //scopeid
            1,		 //card
            1		 // end/displacement flag
         };
         
         MPI_Aint     disp[Attributes];
         
         MPI_Aint base;
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfiguration[0]))), &base);
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfiguration[0]._persistentRecords._qid))), 		&disp[0] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfiguration[0]._persistentRecords._scopeid))), 		&disp[1] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfiguration[0]._persistentRecords._card))), 		&disp[2] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfiguration[1]._persistentRecords._qid))), 		&disp[3] );
         
         for (int i=1; i<Attributes; i++) {
            assertion1( disp[i] > disp[i-1], i );
         }
         for (int i=0; i<Attributes; i++) {
            disp[i] -= base;
         }
         MPI_Type_struct( Attributes, blocklen, disp, subtypes, &AnswerConfiguration::FullDatatype );
         MPI_Type_commit( &AnswerConfiguration::FullDatatype );
         
      }
      
   }
   
   
   void queries::records::AnswerConfiguration::shutdownDatatype() {
      MPI_Type_free( &AnswerConfiguration::Datatype );
      MPI_Type_free( &AnswerConfiguration::FullDatatype );
      
   }
   
   void queries::records::AnswerConfiguration::send(int destination, int tag, bool exchangeOnlyAttributesMarkedWithParallelise) {
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
         msg << "was not able to send message queries::records::AnswerConfiguration "
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
            msg << "testing for finished send task for queries::records::AnswerConfiguration "
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
            "queries::records::AnswerConfiguration",
            "send(int)", destination,tag,1
            );
            triggeredTimeoutWarning = true;
         }
         if (
            tarch::parallel::Node::getInstance().isTimeOutDeadlockEnabled() &&
            (clock()>timeOutShutdown)
         ) {
            tarch::parallel::Node::getInstance().triggerDeadlockTimeOut(
            "queries::records::AnswerConfiguration",
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
   
   
   
   void queries::records::AnswerConfiguration::receive(int source, int tag, bool exchangeOnlyAttributesMarkedWithParallelise) {
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
         msg << "failed to start to receive queries::records::AnswerConfiguration from node "
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
            msg << "testing for finished receive task for queries::records::AnswerConfiguration failed: "
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
            "queries::records::AnswerConfiguration",
            "receive(int)", source,tag,1
            );
            triggeredTimeoutWarning = true;
         }
         if (
            tarch::parallel::Node::getInstance().isTimeOutDeadlockEnabled() &&
            (clock()>timeOutShutdown)
         ) {
            tarch::parallel::Node::getInstance().triggerDeadlockTimeOut(
            "queries::records::AnswerConfiguration",
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
   
   
   
   bool queries::records::AnswerConfiguration::isMessageInQueue(int tag, bool exchangeOnlyAttributesMarkedWithParallelise) {
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
   
   int queries::records::AnswerConfiguration::getSenderRank() const {
      assertion( _senderRank!=-1 );
      return _senderRank;
      
   }
#endif


queries::records::AnswerConfigurationPacked::PersistentRecords::PersistentRecords() {
   
}


queries::records::AnswerConfigurationPacked::PersistentRecords::PersistentRecords(const int& qid, const int& scopeid, const int& card):
_qid(qid),
_scopeid(scopeid),
_card(card) {
   
}


 int queries::records::AnswerConfigurationPacked::PersistentRecords::getQid() const  {
   return _qid;
}



 void queries::records::AnswerConfigurationPacked::PersistentRecords::setQid(const int& qid)  {
   _qid = qid;
}



 int queries::records::AnswerConfigurationPacked::PersistentRecords::getScopeid() const  {
   return _scopeid;
}



 void queries::records::AnswerConfigurationPacked::PersistentRecords::setScopeid(const int& scopeid)  {
   _scopeid = scopeid;
}



 int queries::records::AnswerConfigurationPacked::PersistentRecords::getCard() const  {
   return _card;
}



 void queries::records::AnswerConfigurationPacked::PersistentRecords::setCard(const int& card)  {
   _card = card;
}


queries::records::AnswerConfigurationPacked::AnswerConfigurationPacked() {
   
}


queries::records::AnswerConfigurationPacked::AnswerConfigurationPacked(const PersistentRecords& persistentRecords):
_persistentRecords(persistentRecords._qid, persistentRecords._scopeid, persistentRecords._card) {
   
}


queries::records::AnswerConfigurationPacked::AnswerConfigurationPacked(const int& qid, const int& scopeid, const int& card):
_persistentRecords(qid, scopeid, card) {
   
}


queries::records::AnswerConfigurationPacked::~AnswerConfigurationPacked() { }


 int queries::records::AnswerConfigurationPacked::getQid() const  {
   return _persistentRecords._qid;
}



 void queries::records::AnswerConfigurationPacked::setQid(const int& qid)  {
   _persistentRecords._qid = qid;
}



 int queries::records::AnswerConfigurationPacked::getScopeid() const  {
   return _persistentRecords._scopeid;
}



 void queries::records::AnswerConfigurationPacked::setScopeid(const int& scopeid)  {
   _persistentRecords._scopeid = scopeid;
}



 int queries::records::AnswerConfigurationPacked::getCard() const  {
   return _persistentRecords._card;
}



 void queries::records::AnswerConfigurationPacked::setCard(const int& card)  {
   _persistentRecords._card = card;
}




std::string queries::records::AnswerConfigurationPacked::toString() const {
   std::ostringstream stringstr;
   toString(stringstr);
   return stringstr.str();
}

void queries::records::AnswerConfigurationPacked::toString (std::ostream& out) const {
   out << "("; 
   out << "qid:" << getQid();
   out << ",";
   out << "scopeid:" << getScopeid();
   out << ",";
   out << "card:" << getCard();
   out <<  ")";
}


queries::records::AnswerConfigurationPacked::PersistentRecords queries::records::AnswerConfigurationPacked::getPersistentRecords() const {
   return _persistentRecords;
}

queries::records::AnswerConfiguration queries::records::AnswerConfigurationPacked::convert() const{
   return AnswerConfiguration(
      getQid(),
      getScopeid(),
      getCard()
   );
}

#ifdef Parallel
   tarch::logging::Log queries::records::AnswerConfigurationPacked::_log( "queries::records::AnswerConfigurationPacked" );
   
   MPI_Datatype queries::records::AnswerConfigurationPacked::Datatype = 0;
   MPI_Datatype queries::records::AnswerConfigurationPacked::FullDatatype = 0;
   
   
   void queries::records::AnswerConfigurationPacked::initDatatype() {
      {
         AnswerConfigurationPacked dummyAnswerConfigurationPacked[2];
         
         const int Attributes = 4;
         MPI_Datatype subtypes[Attributes] = {
            MPI_INT,		 //qid
            MPI_INT,		 //scopeid
            MPI_INT,		 //card
            MPI_UB		 // end/displacement flag
         };
         
         int blocklen[Attributes] = {
            1,		 //qid
            1,		 //scopeid
            1,		 //card
            1		 // end/displacement flag
         };
         
         MPI_Aint     disp[Attributes];
         
         MPI_Aint base;
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfigurationPacked[0]))), &base);
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfigurationPacked[0]._persistentRecords._qid))), 		&disp[0] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfigurationPacked[0]._persistentRecords._scopeid))), 		&disp[1] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfigurationPacked[0]._persistentRecords._card))), 		&disp[2] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfigurationPacked[1]._persistentRecords._qid))), 		&disp[3] );
         
         for (int i=1; i<Attributes; i++) {
            assertion1( disp[i] > disp[i-1], i );
         }
         for (int i=0; i<Attributes; i++) {
            disp[i] -= base;
         }
         MPI_Type_struct( Attributes, blocklen, disp, subtypes, &AnswerConfigurationPacked::Datatype );
         MPI_Type_commit( &AnswerConfigurationPacked::Datatype );
         
      }
      {
         AnswerConfigurationPacked dummyAnswerConfigurationPacked[2];
         
         const int Attributes = 4;
         MPI_Datatype subtypes[Attributes] = {
            MPI_INT,		 //qid
            MPI_INT,		 //scopeid
            MPI_INT,		 //card
            MPI_UB		 // end/displacement flag
         };
         
         int blocklen[Attributes] = {
            1,		 //qid
            1,		 //scopeid
            1,		 //card
            1		 // end/displacement flag
         };
         
         MPI_Aint     disp[Attributes];
         
         MPI_Aint base;
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfigurationPacked[0]))), &base);
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfigurationPacked[0]._persistentRecords._qid))), 		&disp[0] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfigurationPacked[0]._persistentRecords._scopeid))), 		&disp[1] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfigurationPacked[0]._persistentRecords._card))), 		&disp[2] );
         MPI_Address( const_cast<void*>(static_cast<const void*>(&(dummyAnswerConfigurationPacked[1]._persistentRecords._qid))), 		&disp[3] );
         
         for (int i=1; i<Attributes; i++) {
            assertion1( disp[i] > disp[i-1], i );
         }
         for (int i=0; i<Attributes; i++) {
            disp[i] -= base;
         }
         MPI_Type_struct( Attributes, blocklen, disp, subtypes, &AnswerConfigurationPacked::FullDatatype );
         MPI_Type_commit( &AnswerConfigurationPacked::FullDatatype );
         
      }
      
   }
   
   
   void queries::records::AnswerConfigurationPacked::shutdownDatatype() {
      MPI_Type_free( &AnswerConfigurationPacked::Datatype );
      MPI_Type_free( &AnswerConfigurationPacked::FullDatatype );
      
   }
   
   void queries::records::AnswerConfigurationPacked::send(int destination, int tag, bool exchangeOnlyAttributesMarkedWithParallelise) {
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
         msg << "was not able to send message queries::records::AnswerConfigurationPacked "
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
            msg << "testing for finished send task for queries::records::AnswerConfigurationPacked "
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
            "queries::records::AnswerConfigurationPacked",
            "send(int)", destination,tag,1
            );
            triggeredTimeoutWarning = true;
         }
         if (
            tarch::parallel::Node::getInstance().isTimeOutDeadlockEnabled() &&
            (clock()>timeOutShutdown)
         ) {
            tarch::parallel::Node::getInstance().triggerDeadlockTimeOut(
            "queries::records::AnswerConfigurationPacked",
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
   
   
   
   void queries::records::AnswerConfigurationPacked::receive(int source, int tag, bool exchangeOnlyAttributesMarkedWithParallelise) {
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
         msg << "failed to start to receive queries::records::AnswerConfigurationPacked from node "
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
            msg << "testing for finished receive task for queries::records::AnswerConfigurationPacked failed: "
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
            "queries::records::AnswerConfigurationPacked",
            "receive(int)", source,tag,1
            );
            triggeredTimeoutWarning = true;
         }
         if (
            tarch::parallel::Node::getInstance().isTimeOutDeadlockEnabled() &&
            (clock()>timeOutShutdown)
         ) {
            tarch::parallel::Node::getInstance().triggerDeadlockTimeOut(
            "queries::records::AnswerConfigurationPacked",
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
   
   
   
   bool queries::records::AnswerConfigurationPacked::isMessageInQueue(int tag, bool exchangeOnlyAttributesMarkedWithParallelise) {
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
   
   int queries::records::AnswerConfigurationPacked::getSenderRank() const {
      assertion( _senderRank!=-1 );
      return _senderRank;
      
   }
#endif



