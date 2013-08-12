
#include <iostream>
#include <string.h>
#include "de/tum/QueryC2CxxSocketPlainPort.h"
#include "de/tum/QueryCxx2SocketPlainPort.h"
#include "de/tum/Query.h"
extern "C" {

#ifdef _WIN32
void DE_TUM_QUERYC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void de_tum_queryc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif
   *ptr=(long long)new de::tum::QueryCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void DE_TUM_QUERYC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size){
#else
void de_tum_queryc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size){
#endif
   *ptr=(long long)new de::tum::QueryCxx2SocketPlainPort(
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void DE_TUM_QUERYC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long *ptr){
#else
void de_tum_queryc2socket_plain_port_destroy_instance_(long long *ptr){
#endif
     de::tum::QueryCxx2SocketPlainPort* c_ptr = (de::tum::QueryCxx2SocketPlainPort*)*ptr;
     if(c_ptr!=NULL){
         delete c_ptr;
         c_ptr = NULL;
     }
}




#ifdef _WIN32
void DE_TUM_QUERYC2SOCKET_PLAIN_PORT_GETNUMBEROFPARTS(long long* ref,int* parts){
     
     ((de::tum::QueryCxx2SocketPlainPort*)*ref)->getNumberOfParts(*parts);
}
#else
void de_tum_queryc2socket_plain_port_getnumberofparts_(long long* ref,int* parts){
     
     ((de::tum::QueryCxx2SocketPlainPort*)*ref)->getNumberOfParts(*parts);
}
#endif
#ifdef _WIN32
void DE_TUM_QUERYC2SOCKET_PLAIN_PORT_GETQUERYDESCRIPTION(long long* ref,double* offset, int* offset_len,double* size, int* size_len,int* resolution,int* resolution_len,int* mids,int* mids_len){
     
     ((de::tum::QueryCxx2SocketPlainPort*)*ref)->getQueryDescription(offset,*offset_len,size,*size_len,resolution,*resolution_len,mids,*mids_len);
}
#else
void de_tum_queryc2socket_plain_port_getquerydescription_(long long* ref,double* offset, int* offset_len,double* size, int* size_len,int* resolution,int* resolution_len,int* mids,int* mids_len){
     
     ((de::tum::QueryCxx2SocketPlainPort*)*ref)->getQueryDescription(offset,*offset_len,size,*size_len,resolution,*resolution_len,mids,*mids_len);
}
#endif
#ifdef _WIN32
void DE_TUM_QUERYC2SOCKET_PLAIN_PORT_FORWARDANSWER(long long* ref,double* data, int* data_len,double* distance, int* distance_len,int* indices,int* indices_len,int* rid){
     
     ((de::tum::QueryCxx2SocketPlainPort*)*ref)->forwardAnswer(data,*data_len,distance,*distance_len,indices,*indices_len,*rid);
}
#else
void de_tum_queryc2socket_plain_port_forwardanswer_(long long* ref,double* data, int* data_len,double* distance, int* distance_len,int* indices,int* indices_len,int* rid){
     
     ((de::tum::QueryCxx2SocketPlainPort*)*ref)->forwardAnswer(data,*data_len,distance,*distance_len,indices,*indices_len,*rid);
}
#endif
}
