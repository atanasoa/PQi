#ifndef DE_TUM_QUERYCXX2SOCKETPLAINPORT_H_
#define DE_TUM_QUERYCXX2SOCKETPLAINPORT_H_ 

#include "de/tum/Query.h"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <winsock2.h>
#endif
namespace de { 
namespace tum { 
  
     class QueryCxx2SocketPlainPort;
} 
}

class de::tum::QueryCxx2SocketPlainPort: public de::tum::Query{
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
    QueryCxx2SocketPlainPort(char* host,int port,int buffer_size);
     QueryCxx2SocketPlainPort(int port,int buffer_size);
    ~QueryCxx2SocketPlainPort();
    //int getSockfd();
    //int getNewsockfd();
    
    void getNumberOfParts(int& parts);
    void getQueryDescription(double* offset, const int offset_len,double* size, const int size_len,int* resolution, const int resolution_len,int* mids, const int mids_len);
    void forwardAnswer(const double* data, const int data_len,const double* distance, const int distance_len,const int* indices, const int indices_len,const int rid);
};

#endif
