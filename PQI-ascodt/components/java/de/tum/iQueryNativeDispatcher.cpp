#include "de/tum/iQueryNativeDispatcher.h"
#include <algorithm>

JNIEXPORT void JNICALL Java_de_tum_iQueryNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  de::tum::iQueryNativeDispatcher *ref=new de::tum::iQueryNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_de_tum_iQueryNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((de::tum::iQueryNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_de_tum_iQueryNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((de::tum::iQueryNativeDispatcher*)ref)->connect((de::tum::iQuery*)destination);
}

JNIEXPORT void JNICALL Java_de_tum_iQueryNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((de::tum::iQueryNativeDispatcher*)ref)->disconnect((de::tum::iQuery*)destination);
}


de::tum::iQueryNativeDispatcher::iQueryNativeDispatcher(){

}

de::tum::iQueryNativeDispatcher::~iQueryNativeDispatcher(){

}

void de::tum::iQueryNativeDispatcher::connect(de::tum::iQuery* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void de::tum::iQueryNativeDispatcher::disconnect(de::tum::iQuery* destination){
  std::vector<de::tum::iQuery*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

const bool de::tum::iQueryNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void de::tum::iQueryNativeDispatcher::requestNumberOfParts(int& parts){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->requestNumberOfParts(parts);
}
void de::tum::iQueryNativeDispatcher::requestPartsInformation(double* offset, const int offset_len,double* size, const int size_len,int* dimensions, const int dimensions_len,int* identifiers, const int identifiers_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->requestPartsInformation(offset,offset_len,size,size_len,dimensions,dimensions_len,identifiers,identifiers_len);
}

