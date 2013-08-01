
#include <iostream>
#include <string.h>
#include "de/tum/SimC2CxxSocketPlainPort.h"
#include "de/tum/SimCxx2SocketPlainPort.h"
#include "de/tum/Sim.h"
extern "C" {

#ifdef _WIN32
void DE_TUM_SIMC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void de_tum_simc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif
   *ptr=(long long)new de::tum::SimCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void DE_TUM_SIMC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size){
#else
void de_tum_simc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size){
#endif
   *ptr=(long long)new de::tum::SimCxx2SocketPlainPort(
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void DE_TUM_SIMC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long *ptr){
#else
void de_tum_simc2socket_plain_port_destroy_instance_(long long *ptr){
#endif
     de::tum::SimCxx2SocketPlainPort* c_ptr = (de::tum::SimCxx2SocketPlainPort*)*ptr;
     if(c_ptr!=NULL){
         delete c_ptr;
         c_ptr = NULL;
     }
}




#ifdef _WIN32
void DE_TUM_SIMC2SOCKET_PLAIN_PORT_SIM(long long* ref){
     
     ((de::tum::SimCxx2SocketPlainPort*)*ref)->sim();
}
#else
void de_tum_simc2socket_plain_port_sim_(long long* ref){
     
     ((de::tum::SimCxx2SocketPlainPort*)*ref)->sim();
}
#endif
}
