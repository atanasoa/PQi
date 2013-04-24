#ifndef DE_TUM_IQUERYNATIVEDISPATCHER_H_
#define DE_TUM_IQUERYNATIVEDISPATCHER_H_ 

#include "de/tum/iQuery.h"
#include <iostream>
#include <vector>

namespace de { 
namespace tum { 
  
     class iQueryNativeDispatcher;
} 
}

#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_de_tum_iQueryNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_de_tum_iQueryNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_de_tum_iQueryNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_de_tum_iQueryNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

class de::tum::iQueryNativeDispatcher: public de::tum::iQuery{
  private:
    std::vector<de::tum::iQuery*> _destinations;
  public:
    iQueryNativeDispatcher();
    ~iQueryNativeDispatcher();
    
    void connect(de::tum::iQuery* ref);
    void disconnect(de::tum::iQuery* ref);
    const bool isConnected() const;
    void requestNumberOfParts(int& parts);
    void requestPartsInformation(double* offset, const int offset_len,double* size, const int size_len,int* dimensions, const int dimensions_len,int* identifiers, const int identifiers_len);
};

#endif
