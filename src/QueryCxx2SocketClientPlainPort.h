#ifndef QUERIES_QUERYCXX2SOCKETCLIENTPLAINPORT_H_
#define QUERIES_QUERYCXX2SOCKETCLIENTPLAINPORT_H_ 

#include "queries/Query.h"
#include <iostream>
#include <string>

namespace queries { 

     class QueryCxx2SocketClientPlainPort;
}

class queries::QueryCxx2SocketClientPlainPort{
  private:
    int _sockfd;
    int _newsockfd;
    int _buffer_size;
    char *_rcvBuffer;
    char *_sendBuffer;
    void open(std::string hostname,int port,int &sockfd,int &newsockfd);
    void sendData(char* data, size_t numberOfBytes, char* sendBuffer, int newsockfd,size_t bufferSize);
    bool readData(char* data,size_t size_of_data,char* readBuffer,int newsockfd, size_t bufferSize);
    void close(int &sockfd,int &newsockfd);
  public:
    QueryCxx2SocketClientPlainPort(std::string host,int port,int buffer_size);
    QueryCxx2SocketClientPlainPort(int sockfd,int newsockfd,int buffer_size);
    ~QueryCxx2SocketClientPlainPort();
    int getSockfd();
    int getNewsockfd();
    
    void release();
    void getScope(int& scope);
    void intersectsWithQuery(const double* voxelOffset, const int voxelOffset_len,const double* voxelSize, const int voxelSize_len,bool& resulst);
    void setData(const double* voxelOffset, const int voxelOffset_len,const double* voxelSize, const int voxelSize_len,const double value);
};

#endif
