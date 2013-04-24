#ifndef DE_TUM_IQUERYNATIVE2NATIVEPLAINPORT_H_
#define DE_TUM_IQUERYNATIVE2NATIVEPLAINPORT_H_ 

#include "de/tum/iQuery.h"
#include <jni.h> 
#include <iostream>

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_de_tum_iQueryNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_de_tum_iQueryNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_de_tum_iQueryNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif

namespace de { 
namespace tum { 
  
     class iQueryNative2NativePlainPort;
} 
}

class de::tum::iQueryNative2NativePlainPort: public de::tum::iQuery{
  private:
    de::tum::iQuery* _destination;
  public:
    iQueryNative2NativePlainPort();
    ~iQueryNative2NativePlainPort();
    
    void connect(de::tum::iQuery*);
    void requestNumberOfParts(int& parts);
    void requestPartsInformation(double* offset, const int offset_len,double* size, const int size_len,int* dimensions, const int dimensions_len,int* identifiers, const int identifiers_len);
};

#endif
