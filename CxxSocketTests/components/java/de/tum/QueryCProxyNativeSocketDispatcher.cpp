
#include "de/tum/QueryNativeSocketDispatcher.h"
#include "de/tum/Query.h"
#include <stdio.h>
#include <string.h>
extern "C" {

#ifdef _WIN32
void DE_TUM_QUERY_F2C_NSD_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void de_tum_query_f2c_nsd_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif     
     *ptr=(long long)new de::tum::QueryNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
     

}




#ifdef _WIN32
void DE_TUM_QUERY_F2C_NSD_DESTROY_INSTANCE(long long* ptr){

#else
void de_tum_query_f2c_nsd_destroy_instance_(long long* ptr){
#endif
     de::tum::QueryNativeSocketDispatcher* dispatcher =
               ((de::tum::QueryNativeSocketDispatcher*)*ptr);
     if(dispatcher!=NULL){
          delete dispatcher;
          dispatcher=NULL;
     }
     

}

#ifdef _WIN32
void DE_TUM_QUERY_F2C_NSD_GETNUMBEROFPARTS(long long* ref,int* parts){
#else
void de_tum_query_f2c_nsd_getnumberofparts_(long long* ref,int* parts){
#endif
    
     
     ((de::tum::QueryNativeSocketDispatcher*)*ref)->getNumberOfParts(*parts);
}
#ifdef _WIN32
void DE_TUM_QUERY_F2C_NSD_GETQUERYDESCRIPTION(long long* ref,double* offset, int* offset_len,double* size, int* size_len,int* resolution,int* resolution_len,char** mids,int* mids_len){
#else
void de_tum_query_f2c_nsd_getquerydescription_(long long* ref,double* offset, int* offset_len,double* size, int* size_len,int* resolution,int* resolution_len,char** mids,int* mids_len){
#endif
    
     std::string* mids_str=new std::string[*mids_len];
for(int i=0;i<*mids_len;i++)
mids_str[i]=mids[i];

     ((de::tum::QueryNativeSocketDispatcher*)*ref)->getQueryDescription(offset,*offset_len,size,*size_len,resolution,*resolution_len,mids_str,*mids_len);
}
#ifdef _WIN32
void DE_TUM_QUERY_F2C_NSD_FORWARDANSWER(long long* ref,double* data, int* data_len,double* distance, int* distance_len,int* indices,int* indices_len,int* rid){
#else
void de_tum_query_f2c_nsd_forwardanswer_(long long* ref,double* data, int* data_len,double* distance, int* distance_len,int* indices,int* indices_len,int* rid){
#endif
    
     
     ((de::tum::QueryNativeSocketDispatcher*)*ref)->forwardAnswer(data,*data_len,distance,*distance_len,indices,*indices_len,*rid);
}


}
