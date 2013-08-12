#ifndef DE_TUM_QUERYNATIVE2NATIVEPLAINPORT_H_
#define DE_TUM_QUERYNATIVE2NATIVEPLAINPORT_H_ 

#include "de/tum/Query.h"
#include <jni.h> 
#include <iostream>

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_de_tum_QueryNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_de_tum_QueryNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_de_tum_QueryNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif

namespace de { 
namespace tum { 
  
     class QueryNative2NativePlainPort;
} 
}

class de::tum::QueryNative2NativePlainPort: public de::tum::Query{
  private:
    de::tum::Query* _destination;
  public:
    QueryNative2NativePlainPort();
    ~QueryNative2NativePlainPort();
    
    void connect(de::tum::Query*);
    void getNumberOfParts(int& parts);
    void getQueryDescription(double* offset, const int offset_len,double* size, const int size_len,int* resolution, const int resolution_len,int* mids, const int mids_len);
    void forwardAnswer(const double* data, const int data_len,const double* distance, const int distance_len,const int* indices, const int indices_len,const int rid);
};

#endif
