#ifndef DE_TUM_SOCKETTESTBABSTRACTIMPLEMENTATION_H_
#define DE_TUM_SOCKETTESTBABSTRACTIMPLEMENTATION_H_ 

//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
#include "de/tum/QueryNativeDispatcher.h"

#include "de/tum/Sim.h"

namespace de { 
namespace tum { 
  
     class SocketTestBAbstractImplementation;
} 
}



class de::tum::SocketTestBAbstractImplementation : public de::tum::Sim{
     protected:
       de::tum::QueryNativeDispatcher* _queryServer;
   
     public:
       SocketTestBAbstractImplementation();
       virtual ~SocketTestBAbstractImplementation();
       /**
        * @see Case class 
        */
       void connectqueryServer(de::tum::QueryNativeDispatcher* port);
       void disconnectqueryServer();
 
};     


#endif
