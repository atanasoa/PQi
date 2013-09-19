#include "de/tum/QueryNative2JavaPlainPort.h"

JNIEXPORT void JNICALL Java_de_tum_QueryNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  jobject self=env->NewGlobalRef(obj);
  
  de::tum::QueryNative2JavaPlainPort *ref=new de::tum::QueryNative2JavaPlainPort(jvm,self);
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
  
}

JNIEXPORT void JNICALL Java_de_tum_QueryNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((de::tum::QueryNative2JavaPlainPort*)ref);
  
}

de::tum::QueryNative2JavaPlainPort::QueryNative2JavaPlainPort(JavaVM* jvm,jobject obj):
     _jvm(jvm),
     _obj(obj){

}

de::tum::QueryNative2JavaPlainPort::~QueryNative2JavaPlainPort(){
  JNIEnv* env;
  _jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  env->DeleteGlobalRef(_obj);
}

void de::tum::QueryNative2JavaPlainPort::getNumberOfParts(int& parts){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lde/tum/QueryDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lde/tum/QueryDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"getNumberOfParts","([I)V");
  
  if(mid){
     jintArray parts_jni=env->NewIntArray(1);
env->SetIntArrayRegion(parts_jni,0,1,(jint*)&parts);

     env->CallVoidMethod(_obj,mid,parts_jni);
     env->GetIntArrayRegion(parts_jni,0,1,(jint*)&parts);

  }
}
void de::tum::QueryNative2JavaPlainPort::getQueryDescription(double* offset, const int offset_len,double* size, const int size_len,int* resolution, const int resolution_len,std::string* mids, const int mids_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lde/tum/QueryDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lde/tum/QueryDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"getQueryDescription","([D[D[I[Ljava/lang/String;)V");
  
  if(mid){
     jdoubleArray offset_jni=env->NewDoubleArray(offset_len);
env->SetDoubleArrayRegion(offset_jni,0,offset_len,(jdouble*)offset);
jdoubleArray size_jni=env->NewDoubleArray(size_len);
env->SetDoubleArrayRegion(size_jni,0,size_len,(jdouble*)size);
jintArray resolution_jni=env->NewIntArray(resolution_len);
env->SetIntArrayRegion(resolution_jni,0,resolution_len,(jint*)resolution);
jobjectArray mids_jni=env->NewObjectArray(mids_len,env->FindClass("Ljava/lang/String;"),0);
for(int i=0;i<mids_len;i++)
	env->SetObjectArrayElement(mids_jni,i, env->NewStringUTF(mids[i].c_str()));

     env->CallVoidMethod(_obj,mid,offset_jni,size_jni,resolution_jni,mids_jni);
     env->GetDoubleArrayRegion(offset_jni,0,offset_len,(jdouble*)offset);
env->GetDoubleArrayRegion(size_jni,0,size_len,(jdouble*)size);
env->GetIntArrayRegion(resolution_jni,0,resolution_len,(jint*)resolution);

  }
}
void de::tum::QueryNative2JavaPlainPort::forwardAnswer(const double* data, const int data_len,const double* distance, const int distance_len,const int* indices, const int indices_len,const int rid){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lde/tum/QueryDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lde/tum/QueryDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"forwardAnswer","([D[D[II)V");
  
  if(mid){
     jdoubleArray data_jni=env->NewDoubleArray(data_len);
env->SetDoubleArrayRegion(data_jni,0,data_len,(jdouble*)data);
jdoubleArray distance_jni=env->NewDoubleArray(distance_len);
env->SetDoubleArrayRegion(distance_jni,0,distance_len,(jdouble*)distance);
jintArray indices_jni=env->NewIntArray(indices_len);
env->SetIntArrayRegion(indices_jni,0,indices_len,(jint*)indices);
jint rid_jni=rid;

     env->CallVoidMethod(_obj,mid,data_jni,distance_jni,indices_jni,rid_jni);
     
  }
}
