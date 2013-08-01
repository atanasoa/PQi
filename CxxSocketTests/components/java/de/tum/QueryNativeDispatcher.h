#ifndef DE_TUM_QUERYNATIVEDISPATCHER_H_
#define DE_TUM_QUERYNATIVEDISPATCHER_H_ 

#include "de/tum/Query.h"
#include <iostream>
#include <vector>

namespace de { 
namespace tum { 
  
     class QueryNativeDispatcher;
} 
}

#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_de_tum_QueryNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_de_tum_QueryNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_de_tum_QueryNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_de_tum_QueryNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

class de::tum::QueryNativeDispatcher: public de::tum::Query{
  protected:
    std::vector<de::tum::Query*> _destinations;
  public:
    QueryNativeDispatcher();
    virtual ~QueryNativeDispatcher();
    
    void connect(de::tum::Query* ref);
    void disconnect(de::tum::Query* ref);
    bool isConnected() const;
    void getNumberOfParts(int& parts);
    void getQueryDescription(double* offset, const int offset_len,double* size, const int size_len,int* resolution, const int resolution_len,int* mids, const int mids_len);
    void forwardAnswer(const double* data, const int data_len,const int rid);
};

#endif
