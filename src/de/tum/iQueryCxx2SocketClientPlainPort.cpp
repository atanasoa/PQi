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
#include "de/tum/iQueryCxx2SocketClientPlainPort.h"
#include <fcntl.h>

de::tum::iQueryCxx2SocketClientPlainPort::iQueryCxx2SocketClientPlainPort(std::string host,int port,int buffer_size):
     _buffer_size(buffer_size){
     _rcvBuffer=new char[_buffer_size];
     _sendBuffer=new char[_buffer_size];
     de::tum::iQueryCxx2SocketClientPlainPort::open(host,port,_sockfd,_newsockfd);

}
de::tum::iQueryCxx2SocketClientPlainPort::iQueryCxx2SocketClientPlainPort(int sockfd,int newsockfd,int buffer_size):
      _buffer_size(buffer_size),
      _sockfd(sockfd),
      _newsockfd(newsockfd){
     _rcvBuffer=new char[_buffer_size];
     _sendBuffer=new char[_buffer_size];

}
de::tum::iQueryCxx2SocketClientPlainPort::~iQueryCxx2SocketClientPlainPort(){
     delete [] _rcvBuffer;
     delete [] _sendBuffer;
     de::tum::iQueryCxx2SocketClientPlainPort::close(_sockfd,_newsockfd);
     
}


int de::tum::iQueryCxx2SocketClientPlainPort::getSockfd(){
     return _sockfd;
}
int de::tum::iQueryCxx2SocketClientPlainPort::getNewsockfd(){
     return _newsockfd;
}

void de::tum::iQueryCxx2SocketClientPlainPort::open(std::string hostname,int port,int &sockfd,int &newsockfd){
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

void de::tum::iQueryCxx2SocketClientPlainPort::sendData(char* data, size_t numberOfBytes, char* sendBuffer, int newsockfd,int bufferSize){
     char* data_ptr=(char*)data;
     int remaining_bytes_to_send=0,total_send_bytes=0,send_bytes=0,n=0;

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


void de::tum::iQueryCxx2SocketClientPlainPort::readData(char* data,size_t size_of_data,char* readBuffer,int newsockfd, int bufferSize){
          bzero(readBuffer,bufferSize);
          int bytes_received=0;
          int total_bytes_received=0;
          int local_bytes_received=0;
          int bytes_to_copy=0;
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
                    }
               }
               bytes_to_copy=(total_bytes_received+bytes_received>size_of_data)?size_of_data-total_bytes_received:bytes_received;
               memcpy(data_ptr,readBuffer,bytes_to_copy);
               data_ptr+=bytes_to_copy;
               total_bytes_received+=bytes_to_copy;
          }

}


void de::tum::iQueryCxx2SocketClientPlainPort::close(int &sockfd,int &newsockfd){
     if(newsockfd>=0)
         ::close(newsockfd);
     if(sockfd>=0)
         ::close(sockfd);
}
void de::tum::iQueryCxx2SocketClientPlainPort::requestAllComm(){
	 int flags;
	flags = fcntl(_newsockfd, F_GETFL, 0);
	flags ^= O_NONBLOCK;
	fcntl(_newsockfd, F_SETFL, flags);
    int methodId=0;
    std::cout<<"sending data:"<<methodId<<std::endl;
	sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);

}
void de::tum::iQueryCxx2SocketClientPlainPort::requestNumberOfParts(int& parts){
     //assert(_destination!=NULL);
     int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags ^= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);

     int methodId=2;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&parts,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);

     readData((char*)&parts,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);

}
void de::tum::iQueryCxx2SocketClientPlainPort::requestPartsInformation(double* offset, const int offset_len,double* size, const int size_len,int* dimensions, const int dimensions_len,int* identifiers, const int identifiers_len){
     //assert(_destination!=NULL);
     int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags ^= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);

     int methodId=3;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&offset_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)offset,sizeof(double)*offset_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&size_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)size,sizeof(double)*size_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&dimensions_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)dimensions,sizeof(int)*dimensions_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&identifiers_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)identifiers,sizeof(int)*identifiers_len,_sendBuffer,_newsockfd,_buffer_size);

     readData((char*)&offset_len,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
readData((char*)offset,sizeof(double)*offset_len,_rcvBuffer,_newsockfd,_buffer_size);
readData((char*)&size_len,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
readData((char*)size,sizeof(double)*size_len,_rcvBuffer,_newsockfd,_buffer_size);
readData((char*)&dimensions_len,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
readData((char*)dimensions,sizeof(int)*dimensions_len,_rcvBuffer,_newsockfd,_buffer_size);
readData((char*)&identifiers_len,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
readData((char*)identifiers,sizeof(int)*identifiers_len,_rcvBuffer,_newsockfd,_buffer_size);

}
