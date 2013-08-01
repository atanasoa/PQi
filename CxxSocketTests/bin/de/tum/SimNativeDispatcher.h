#ifndef DE_TUM_SIMNATIVEDISPATCHER_H_
#define DE_TUM_SIMNATIVEDISPATCHER_H_ 

#include "de/tum/Sim.h"
#include <iostream>
#include <vector>

namespace de { 
namespace tum { 
  
     class SimNativeDispatcher;
} 
}

#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_de_tum_SimNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_de_tum_SimNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_de_tum_SimNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_de_tum_SimNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

class de::tum::SimNativeDispatcher: public de::tum::Sim{
  protected:
    std::vector<de::tum::Sim*> _destinations;
  public:
    SimNativeDispatcher();
    virtual ~SimNativeDispatcher();
    
    void connect(de::tum::Sim* ref);
    void disconnect(de::tum::Sim* ref);
    bool isConnected() const;
    void sim();
};

#endif
