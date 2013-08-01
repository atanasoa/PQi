#include "de/tum/SimNative2NativePlainPort.h"
#include <assert.h>


JNIEXPORT void JNICALL Java_de_tum_SimNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  de::tum::SimNative2NativePlainPort *ref=new de::tum::SimNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_de_tum_SimNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((de::tum::SimNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_de_tum_SimNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((de::tum::SimNative2NativePlainPort*)ref)->connect((de::tum::Sim*)destination);
}


de::tum::SimNative2NativePlainPort::SimNative2NativePlainPort():
     _destination(0){

}

de::tum::SimNative2NativePlainPort::~SimNative2NativePlainPort(){

}

void de::tum::SimNative2NativePlainPort::connect(de::tum::Sim* destination){
  _destination=destination;
}
void de::tum::SimNative2NativePlainPort::sim(){
     assert(_destination!=NULL);
     _destination->sim();
}

