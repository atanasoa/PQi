#include "de/tum/QueryNativeDispatcher.h"
#include <algorithm>

JNIEXPORT void JNICALL Java_de_tum_QueryNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  de::tum::QueryNativeDispatcher *ref=new de::tum::QueryNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_de_tum_QueryNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((de::tum::QueryNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_de_tum_QueryNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((de::tum::QueryNativeDispatcher*)ref)->connect((de::tum::Query*)destination);
}

JNIEXPORT void JNICALL Java_de_tum_QueryNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((de::tum::QueryNativeDispatcher*)ref)->disconnect((de::tum::Query*)destination);
}


de::tum::QueryNativeDispatcher::QueryNativeDispatcher(){

}

de::tum::QueryNativeDispatcher::~QueryNativeDispatcher(){

}

void de::tum::QueryNativeDispatcher::connect(de::tum::Query* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void de::tum::QueryNativeDispatcher::disconnect(de::tum::Query* destination){
  std::vector<de::tum::Query*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool de::tum::QueryNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void de::tum::QueryNativeDispatcher::getNumberOfParts(int& parts){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->getNumberOfParts(parts);
}
void de::tum::QueryNativeDispatcher::getQueryDescription(double* offset, const int offset_len,double* size, const int size_len,int* resolution, const int resolution_len,int* mids, const int mids_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->getQueryDescription(offset,offset_len,size,size_len,resolution,resolution_len,mids,mids_len);
}
void de::tum::QueryNativeDispatcher::forwardAnswer(const double* data, const int data_len,const int rid){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->forwardAnswer(data,data_len,rid);
}

