#include "de/tum/SimNativeDispatcher.h"
#include <algorithm>

JNIEXPORT void JNICALL Java_de_tum_SimNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  de::tum::SimNativeDispatcher *ref=new de::tum::SimNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_de_tum_SimNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((de::tum::SimNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_de_tum_SimNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((de::tum::SimNativeDispatcher*)ref)->connect((de::tum::Sim*)destination);
}

JNIEXPORT void JNICALL Java_de_tum_SimNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((de::tum::SimNativeDispatcher*)ref)->disconnect((de::tum::Sim*)destination);
}


de::tum::SimNativeDispatcher::SimNativeDispatcher(){

}

de::tum::SimNativeDispatcher::~SimNativeDispatcher(){

}

void de::tum::SimNativeDispatcher::connect(de::tum::Sim* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void de::tum::SimNativeDispatcher::disconnect(de::tum::Sim* destination){
  std::vector<de::tum::Sim*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool de::tum::SimNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void de::tum::SimNativeDispatcher::sim(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->sim();
}

