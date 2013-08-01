#ifndef DE_TUM_SOCKETTESTBIMPLEMENTATION_H_
#define DE_TUM_SOCKETTESTBIMPLEMENTATION_H_ 

//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//

#include "de/tum/SocketTestBAbstractImplementation.h"
#include <string>
namespace de { 
namespace tum { 
  
     class SocketTestBImplementation;
} 
}

class de::tum::SocketTestBImplementation : public de::tum::SocketTestBAbstractImplementation{
     public:
          SocketTestBImplementation();
          ~SocketTestBImplementation();
          void sim();
};     


#endif
