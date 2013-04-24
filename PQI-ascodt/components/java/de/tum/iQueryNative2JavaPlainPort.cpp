#include "de/tum/iQueryNative2JavaPlainPort.h"

JNIEXPORT void JNICALL Java_de_tum_iQueryNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  jobject self=env->NewGlobalRef(obj);
  
  de::tum::iQueryNative2JavaPlainPort *ref=new de::tum::iQueryNative2JavaPlainPort(jvm,self);
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
  
}

JNIEXPORT void JNICALL Java_de_tum_iQueryNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((de::tum::iQueryNative2JavaPlainPort*)ref);
  
}

de::tum::iQueryNative2JavaPlainPort::iQueryNative2JavaPlainPort(JavaVM* jvm,jobject obj):
     _jvm(jvm),
     _obj(obj){

}

de::tum::iQueryNative2JavaPlainPort::~iQueryNative2JavaPlainPort(){
  JNIEnv* env;
  _jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  env->DeleteGlobalRef(_obj);
}

void de::tum::iQueryNative2JavaPlainPort::requestNumberOfParts(int& parts){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lde/tum/iQueryDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lde/tum/iQueryDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"requestNumberOfParts","([I)V");
  
  if(mid){
     jintArray parts_jni=env->NewIntArray(1);
env->SetIntArrayRegion(parts_jni,0,1,(jint*)&parts);

     env->CallVoidMethod(_obj,mid,parts_jni);
     env->GetIntArrayRegion(parts_jni,0,1,(jint*)&parts);

  }
}
void de::tum::iQueryNative2JavaPlainPort::requestPartsInformation(double* offset, const int offset_len,double* size, const int size_len,int* dimensions, const int dimensions_len,int* identifiers, const int identifiers_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lde/tum/iQueryDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lde/tum/iQueryDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"requestPartsInformation","([D[D[I[I)V");
  
  if(mid){
     jdoubleArray offset_jni=env->NewDoubleArray(offset_len);
env->SetDoubleArrayRegion(offset_jni,0,offset_len,(jdouble*)offset);
jdoubleArray size_jni=env->NewDoubleArray(size_len);
env->SetDoubleArrayRegion(size_jni,0,size_len,(jdouble*)size);
jintArray dimensions_jni=env->NewIntArray(dimensions_len);
env->SetIntArrayRegion(dimensions_jni,0,dimensions_len,(jint*)dimensions);
jintArray identifiers_jni=env->NewIntArray(identifiers_len);
env->SetIntArrayRegion(identifiers_jni,0,identifiers_len,(jint*)identifiers);

     env->CallVoidMethod(_obj,mid,offset_jni,size_jni,dimensions_jni,identifiers_jni);
     env->GetDoubleArrayRegion(offset_jni,0,offset_len,(jdouble*)offset);
env->GetDoubleArrayRegion(size_jni,0,size_len,(jdouble*)size);
env->GetIntArrayRegion(dimensions_jni,0,dimensions_len,(jint*)dimensions);
env->GetIntArrayRegion(identifiers_jni,0,identifiers_len,(jint*)identifiers);

  }
}
