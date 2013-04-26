#ifndef DE_TUM_IQUERYCXX2SOCKETCLIENTPLAINPORT_H_
#define DE_TUM_IQUERYCXX2SOCKETCLIENTPLAINPORT_H_ 

#include "de/tum/iQuery.h"
#include <iostream>
#include <string>

namespace de { 
namespace tum { 
  
     class iQueryCxx2SocketClientPlainPort;
} 
}

class de::tum::iQueryCxx2SocketClientPlainPort: public de::tum::iQuery{
  private:
    int _sockfd;
    int _newsockfd;
    int _buffer_size;
    char *_rcvBuffer;
    char *_sendBuffer;
    void open(std::string hostname,int port,int &sockfd,int &newsockfd);
    void sendData(char* data, size_t numberOfBytes, char* sendBuffer, int newsockfd,int bufferSize);
    void readData(char* data,size_t size_of_data,char* readBuffer,int newsockfd, int bufferSize);
    void close(int &sockfd,int &newsockfd);
  public:
    iQueryCxx2SocketClientPlainPort(std::string host,int port,int buffer_size);
    iQueryCxx2SocketClientPlainPort(int sockfd,int newsockfd,int buffer_size);
    ~iQueryCxx2SocketClientPlainPort();
    int getSockfd();
    int getNewsockfd();
    void requestAllComm();
    void requestNumberOfParts(int& parts);
    void requestPartsInformation(double* offset, const int offset_len,double* size, const int size_len,int* dimensions, const int dimensions_len,int* identifiers, const int identifiers_len);
};

#endif
