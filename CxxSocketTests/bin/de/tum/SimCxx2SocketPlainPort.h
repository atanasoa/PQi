#ifndef DE_TUM_SIMCXX2SOCKETPLAINPORT_H_
#define DE_TUM_SIMCXX2SOCKETPLAINPORT_H_ 

#include "de/tum/Sim.h"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <winsock2.h>
#endif
namespace de { 
namespace tum { 
  
     class SimCxx2SocketPlainPort;
} 
}

class de::tum::SimCxx2SocketPlainPort: public de::tum::Sim{
  private:
    #ifdef _WIN32
    SOCKET
    #else
    int
    #endif 
    _sockfd;
    #ifdef _WIN32
    SOCKET
    #else
    int
    #endif
    _newsockfd;
    int _buffer_size;
    char *_rcvBuffer;
    char *_sendBuffer;
    void open_client(char* hostname,int port,
    #ifdef _WIN32
    SOCKET
    #else
    int
    #endif 
    &sockfd,
    #ifdef _WIN32
    SOCKET
    #else
    int
    #endif 
    &newsockfd);
    //void open_server(int port,int &sockfd,int &newsockfd);
    void sendData(char* data, size_t numberOfBytes, char* sendBuffer,
    #ifdef _WIN32
    SOCKET
    #else
    int
    #endif 
    newsockfd,int bufferSize);
    void readData(char* data,size_t size_of_data,char* readBuffer,
    #ifdef _WIN32
    SOCKET
    #else
    int
    #endif 
    newsockfd, int bufferSize);
    void close(
    #ifdef _WIN32
    SOCKET
    #else
    int
    #endif 
    &sockfd,
    #ifdef _WIN32
    SOCKET
    #else
    int
    #endif 
    &newsockfd);
  public:
    SimCxx2SocketPlainPort(char* host,int port,int buffer_size);
     SimCxx2SocketPlainPort(int port,int buffer_size);
    ~SimCxx2SocketPlainPort();
    //int getSockfd();
    //int getNewsockfd();
    
    void sim();
};

#endif
