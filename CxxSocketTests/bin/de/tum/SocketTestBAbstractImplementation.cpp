#include "/work_fast/atanasoa/Programme/runtime-HelloSocketFortran/CxxSocketTests/components/java/de/tum/SocketTestBAbstractImplementation.h"

de::tum::SocketTestBAbstractImplementation::SocketTestBAbstractImplementation(){
     _queryServer = 0;

}

de::tum::SocketTestBAbstractImplementation::~SocketTestBAbstractImplementation(){

}

/**
 * @see Case class 
 */
 void de::tum::SocketTestBAbstractImplementation::connectqueryServer(de::tum::QueryNativeDispatcher* port){
   _queryServer = port; 
 }
 
 void de::tum::SocketTestBAbstractImplementation::disconnectqueryServer(){
    delete _queryServer;
    _queryServer=NULL;
 }
 
