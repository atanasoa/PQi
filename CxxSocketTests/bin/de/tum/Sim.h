#ifndef DE_TUM_SIM_H_
#define DE_TUM_SIM_H_ 

//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//

#include <iostream>
#include <string>



namespace de { 
namespace tum { 
  
     class Sim;
} 
}

class de::tum::Sim {
  public:
    virtual ~Sim(){}
     virtual void sim()=0;


};

#endif
