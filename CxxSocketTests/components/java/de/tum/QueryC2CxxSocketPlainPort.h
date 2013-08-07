#ifndef DE_TUM_QUERYC2SOCKETPLAINPORT_H_
#define DE_TUM_QUERYC2SOCKETPLAINPORT_H_ 

#include <map>
#include <string>

extern "C" {
#ifdef _WIN32
void DE_TUM_QUERYC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size);
void DE_TUM_QUERYC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size);
void DE_TUM_QUERYC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long* ptr);
#else
void de_tum_queryc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size);
void de_tum_queryc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size);
void de_tum_queryc2socket_plain_port_destroy_instance_(long long* ptr);
#endif
#ifdef _WIN32
void DE_TUM_QUERYC2SOCKET_PLAIN_PORT_GETNUMBEROFPARTS(long long* ref,int* parts);

#else
void de_tum_queryc2socket_plain_port_getnumberofparts_(long long* ref,int* parts);
#endif
#ifdef _WIN32
void DE_TUM_QUERYC2SOCKET_PLAIN_PORT_GETQUERYDESCRIPTION(long long* ref,double* offset, int* offset_len,double* size, int* size_len,int* resolution,int* resolution_len,int* mids,int* mids_len);

#else
void de_tum_queryc2socket_plain_port_getquerydescription_(long long* ref,double* offset, int* offset_len,double* size, int* size_len,int* resolution,int* resolution_len,int* mids,int* mids_len);
#endif
#ifdef _WIN32
void DE_TUM_QUERYC2SOCKET_PLAIN_PORT_FORWARDANSWER(long long* ref,double* data, int* data_len,double* distance, int* distance_len,int* indices,int* indices_len,int* rid);

#else
void de_tum_queryc2socket_plain_port_forwardanswer_(long long* ref,double* data, int* data_len,double* distance, int* distance_len,int* indices,int* indices_len,int* rid);
#endif
}
#endif
