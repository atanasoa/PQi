#include "de/tum/QueryNative2NativePlainPort.h"
#include <assert.h>


JNIEXPORT void JNICALL Java_de_tum_QueryNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  de::tum::QueryNative2NativePlainPort *ref=new de::tum::QueryNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_de_tum_QueryNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((de::tum::QueryNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_de_tum_QueryNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((de::tum::QueryNative2NativePlainPort*)ref)->connect((de::tum::Query*)destination);
}


de::tum::QueryNative2NativePlainPort::QueryNative2NativePlainPort():
     _destination(0){

}

de::tum::QueryNative2NativePlainPort::~QueryNative2NativePlainPort(){

}

void de::tum::QueryNative2NativePlainPort::connect(de::tum::Query* destination){
  _destination=destination;
}
void de::tum::QueryNative2NativePlainPort::getNumberOfParts(int& parts){
     assert(_destination!=NULL);
     _destination->getNumberOfParts(parts);
}
void de::tum::QueryNative2NativePlainPort::getQueryDescription(double* offset, const int offset_len,double* size, const int size_len,int* resolution, const int resolution_len,int* mids, const int mids_len){
     assert(_destination!=NULL);
     _destination->getQueryDescription(offset,offset_len,size,size_len,resolution,resolution_len,mids,mids_len);
}
void de::tum::QueryNative2NativePlainPort::forwardAnswer(const double* data, const int data_len,const double* distance, const int distance_len,const int* indices, const int indices_len,const int rid){
     assert(_destination!=NULL);
     _destination->forwardAnswer(data,data_len,distance,distance_len,indices,indices_len,rid);
}

