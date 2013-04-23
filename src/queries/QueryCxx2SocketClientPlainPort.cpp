#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include "queries/QueryCxx2SocketClientPlainPort.h"


queries::QueryCxx2SocketClientPlainPort::QueryCxx2SocketClientPlainPort(std::string host,int port,int buffer_size):
     _buffer_size(buffer_size){
     _rcvBuffer=new char[_buffer_size];
     _sendBuffer=new char[_buffer_size];
     queries::QueryCxx2SocketClientPlainPort::open(host,port,_sockfd,_newsockfd);
     std::cout<<"conn. channel openned"<<std::endl;

}
queries::QueryCxx2SocketClientPlainPort::QueryCxx2SocketClientPlainPort(int sockfd,int newsockfd,int buffer_size):
	_sockfd(sockfd),
	_newsockfd(newsockfd),
    _buffer_size(buffer_size)
     {
     _rcvBuffer=new char[_buffer_size];
     _sendBuffer=new char[_buffer_size];

}
queries::QueryCxx2SocketClientPlainPort::~QueryCxx2SocketClientPlainPort(){
     delete [] _rcvBuffer;
     delete [] _sendBuffer;
     queries::QueryCxx2SocketClientPlainPort::close(_sockfd,_newsockfd);
     
}


int queries::QueryCxx2SocketClientPlainPort::getSockfd(){
     return _sockfd;
}
int queries::QueryCxx2SocketClientPlainPort::getNewsockfd(){
     return _newsockfd;
}

void queries::QueryCxx2SocketClientPlainPort::open(std::string hostname,int port,int &sockfd,int &newsockfd){
          struct sockaddr_in serv_addr;
          struct hostent *server;

          _sockfd = socket(AF_INET, SOCK_STREAM, 0);
          assert(sockfd >= 0);
          server = gethostbyname(hostname.c_str());
          assert(server>=0);
          bzero((char *) &serv_addr, sizeof(serv_addr));
          serv_addr.sin_family = AF_INET;
          bcopy((char *)server->h_addr,
                    (char *)&serv_addr.sin_addr.s_addr,
                    server->h_length);
          serv_addr.sin_port = htons(port);
          int tries=60;
                while(tries>0){
               if (connect(_sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) >= 0)
                    break;
                         tries--;
               sleep(1);
                }   
         newsockfd=sockfd;
}

void queries::QueryCxx2SocketClientPlainPort::sendData(char* data, size_t numberOfBytes, char* sendBuffer, int newsockfd,size_t bufferSize){
     char* data_ptr=(char*)data;
     size_t remaining_bytes_to_send=0,total_send_bytes=0,send_bytes=0,n=0;

     //clear buffer
     bzero(sendBuffer,bufferSize);
     while(total_send_bytes<numberOfBytes){
          remaining_bytes_to_send=(numberOfBytes-send_bytes<=bufferSize)?numberOfBytes-send_bytes:bufferSize;
          memcpy(sendBuffer,data_ptr,remaining_bytes_to_send);
          send_bytes=0;
          char* send_buffer_ptr=sendBuffer;
          while(send_bytes<bufferSize){
               n = write(newsockfd,send_buffer_ptr,bufferSize-send_bytes);
               if(n>0){
                    send_bytes+=n;
                    send_buffer_ptr+=n;
               }
          }
          total_send_bytes+=send_bytes;
          data_ptr+=send_bytes;
     }

}


bool queries::QueryCxx2SocketClientPlainPort::readData(char* data,size_t size_of_data,char* readBuffer,int newsockfd, size_t bufferSize){
          bzero(readBuffer,bufferSize);
          size_t bytes_received=0;
          size_t total_bytes_received=0;
          size_t local_bytes_received=0;
          size_t bytes_to_copy=0;
          char* data_ptr=data;
          char* buffer_ptr;

          while(total_bytes_received<size_of_data){
               bytes_received=0;
               buffer_ptr=readBuffer;
               while(bytes_received<bufferSize){
                    local_bytes_received = read(newsockfd,buffer_ptr,bufferSize-bytes_received);
                    if(local_bytes_received>0){
                         bytes_received+=local_bytes_received;
                         buffer_ptr+=local_bytes_received;
                    }else
                         return false;
               }
               bytes_to_copy=(total_bytes_received+bytes_received>size_of_data)?size_of_data-total_bytes_received:bytes_received;
               memcpy(data_ptr,readBuffer,bytes_to_copy);
               data_ptr+=bytes_to_copy;
               total_bytes_received+=bytes_to_copy;
          }
          return true;

}


void queries::QueryCxx2SocketClientPlainPort::close(int &sockfd,int &newsockfd){
     std::cout<<"closing client"<<std::endl;
	 if(newsockfd>=0)
         ::close(newsockfd);
     if(sockfd>=0)
         ::close(sockfd);
}

void queries::QueryCxx2SocketClientPlainPort::release(){
     //assert(_destination!=NULL);
     int methodId=0;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
}
void queries::QueryCxx2SocketClientPlainPort::getScope(int& scope){
     //assert(_destination!=NULL);
     int methodId=1;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&scope,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);

     readData((char*)&scope,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);

}
void queries::QueryCxx2SocketClientPlainPort::intersectsWithQuery(const double* voxelOffset, const int voxelOffset_len,const double* voxelSize, const int voxelSize_len,bool& resulst){
     //assert(_destination!=NULL);
     int methodId=2;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&voxelOffset_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)voxelOffset,sizeof(double)*voxelOffset_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&voxelSize_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)voxelSize,sizeof(double)*voxelSize_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&resulst,sizeof(bool),_sendBuffer,_newsockfd,_buffer_size);

     readData((char*)&resulst,sizeof(bool),_rcvBuffer,_newsockfd,_buffer_size);

}
void queries::QueryCxx2SocketClientPlainPort::setData(const double* voxelOffset, const int voxelOffset_len,const double* voxelSize, const int voxelSize_len,const double value){
     //assert(_destination!=NULL);
     int methodId=3;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&voxelOffset_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)voxelOffset,sizeof(double)*voxelOffset_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&voxelSize_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)voxelSize,sizeof(double)*voxelSize_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&value,sizeof(double),_sendBuffer,_newsockfd,_buffer_size);

     
}
