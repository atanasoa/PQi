#include "de/tum/SimNative2JavaPlainPort.h"

JNIEXPORT void JNICALL Java_de_tum_SimNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  jobject self=env->NewGlobalRef(obj);
  
  de::tum::SimNative2JavaPlainPort *ref=new de::tum::SimNative2JavaPlainPort(jvm,self);
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
  
}

JNIEXPORT void JNICALL Java_de_tum_SimNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((de::tum::SimNative2JavaPlainPort*)ref);
  
}

de::tum::SimNative2JavaPlainPort::SimNative2JavaPlainPort(JavaVM* jvm,jobject obj):
     _jvm(jvm),
     _obj(obj){

}

de::tum::SimNative2JavaPlainPort::~SimNative2JavaPlainPort(){
  JNIEnv* env;
  _jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  env->DeleteGlobalRef(_obj);
}

void de::tum::SimNative2JavaPlainPort::sim(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lde/tum/SimDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lde/tum/SimDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"sim","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
