#include "de/tum/iQueryNative2NativePlainPort.h"
#include <assert.h>


JNIEXPORT void JNICALL Java_de_tum_iQueryNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  de::tum::iQueryNative2NativePlainPort *ref=new de::tum::iQueryNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_de_tum_iQueryNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((de::tum::iQueryNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_de_tum_iQueryNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((de::tum::iQueryNative2NativePlainPort*)ref)->connect((de::tum::iQuery*)destination);
}


de::tum::iQueryNative2NativePlainPort::iQueryNative2NativePlainPort():
     _destination(0){

}

de::tum::iQueryNative2NativePlainPort::~iQueryNative2NativePlainPort(){

}

void de::tum::iQueryNative2NativePlainPort::connect(de::tum::iQuery* destination){
  _destination=destination;
}
void de::tum::iQueryNative2NativePlainPort::requestNumberOfParts(int& parts){
     assert(_destination!=NULL);
     _destination->requestNumberOfParts(parts);
}
void de::tum::iQueryNative2NativePlainPort::requestPartsInformation(double* offset, const int offset_len,double* size, const int size_len,int* dimensions, const int dimensions_len,int* identifiers, const int identifiers_len){
     assert(_destination!=NULL);
     _destination->requestPartsInformation(offset,offset_len,size,size_len,dimensions,dimensions_len,identifiers,identifiers_len);
}

