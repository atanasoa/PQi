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

struct SOCKETTESTA_arg{
     void *ref;
     #ifdef _WIN32
     SOCKET
     #else
     int
     #endif
     java_serverfd;
     #ifdef _WIN32
     SOCKET
     #else
     int
     #endif
     java_clientfd;
     #ifdef _WIN32
     SOCKET
     #else
     int
     #endif
     daemon_serverfd;
     #ifdef _WIN32
     SOCKET
     #else
     int
     #endif
     daemon_clientfd;
     int buffer_size;
     const char* hostname;
     const char* client_port;
     const char* daemon_port;
     bool java_client_flag;
};
}
#endif
