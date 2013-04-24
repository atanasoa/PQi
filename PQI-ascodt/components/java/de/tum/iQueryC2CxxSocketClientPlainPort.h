#ifndef DE_TUM_IQUERYC2SOCKETCLIENTPLAINPORT_H_
#define DE_TUM_IQUERYC2SOCKETCLIENTPLAINPORT_H_ 

#include <map>
#include <string>

extern "C" {
void de_tum_iqueryc2socket_client_plain_port_create_instance_(long long* ptr);
void de_tum_iqueryc2socket_client_plain_port_destroy_instance_(long long* ptr);
extern std::map<std::string,std::pair<int,int> > _clientConn;
void de_tum_iqueryc2socket_client_plain_port_requestnumberofparts_(long long* ref,int* parts);
void de_tum_iqueryc2socket_client_plain_port_requestpartsinformation_(long long* ref,double* offset, int* offset_len,double* size, int* size_len,int* dimensions,int* dimensions_len,int* identifiers,int* identifiers_len);
}
#endif
