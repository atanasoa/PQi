#ifndef __INCLUDE_GUARD_FULL_QUALIFIED_NAME__C2CXXPROXY_H_
#define __INCLUDE_GUARD_FULL_QUALIFIED_NAME__C2CXXPROXY_H_ 
extern "C"{
#ifdef _WIN32
void SOCKET_CLIENT_LOOP();
#else
void socket_client_loop_();
#endif
 

#ifdef _WIN32
void SOCKET_SERVER_LOOP();
#else
void socket_server_loop_();
#endif
}
#endif
