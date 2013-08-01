#ifndef DE_TUM_SIMNATIVE2NATIVEPLAINPORT_H_
#define DE_TUM_SIMNATIVE2NATIVEPLAINPORT_H_ 

#include "de/tum/Sim.h"
#include <jni.h> 
#include <iostream>

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_de_tum_SimNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_de_tum_SimNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_de_tum_SimNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif

namespace de { 
namespace tum { 
  
     class SimNative2NativePlainPort;
} 
}

class de::tum::SimNative2NativePlainPort: public de::tum::Sim{
  private:
    de::tum::Sim* _destination;
  public:
    SimNative2NativePlainPort();
    ~SimNative2NativePlainPort();
    
    void connect(de::tum::Sim*);
    void sim();
};

#endif
