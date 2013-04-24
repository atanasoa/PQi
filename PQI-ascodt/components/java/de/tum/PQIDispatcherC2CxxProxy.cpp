//#include "de/tum/PQIDispatcherJNIProxy.h"
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
#include "de/tum/PQIDispatcherImplementation.h"

void open(int port,int &sockfd,int &newsockfd){
          socklen_t clilen;

          struct sockaddr_in serv_addr, cli_addr;

          sockfd = socket(AF_INET, SOCK_STREAM, 0);
          assert (sockfd>=0);

          bzero((char *) &serv_addr, sizeof(serv_addr));
          serv_addr.sin_family = AF_INET;
          serv_addr.sin_addr.s_addr = INADDR_ANY;
          serv_addr.sin_port = htons(port);
          assert (bind(sockfd, (struct sockaddr *) &serv_addr,
                    sizeof(serv_addr)) >= 0);
          listen(sockfd,5);
          clilen = sizeof(cli_addr);
          newsockfd = accept(sockfd,
                    (struct sockaddr *) &cli_addr,
                    &clilen);
          assert (newsockfd >= 0);
}

void sendData(char* data, size_t numberOfBytes, char* sendBuffer, int newsockfd,int bufferSize){
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


void readData(char* data,size_t size_of_data,char* readBuffer,int newsockfd, int bufferSize){
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

void invoker_create_instance(void* ref,int,int,int,char*,char*){
     ref =new de::tum::PQIDispatcherImplementation();
  
}

void invoker_destroy_instance(void* ref,int,int,int,char*,char*){
     delete ref;
  
}


void invoker_requestPartsInformation(void* ref,int sockfd,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer){
  int offset_len=0;
readData((char*)&offset_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* offset=new double[offset_len];
readData((char*)offset,sizeof(double)*offset_len,rcvBuffer,newsockfd,buffer_size);
int size_len=0;
readData((char*)&size_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* size=new double[size_len];
readData((char*)size,sizeof(double)*size_len,rcvBuffer,newsockfd,buffer_size);
int dimensions_len=0;
readData((char*)&dimensions_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
int* dimensions=new int[dimensions_len];
readData((char*)dimensions,sizeof(int)*dimensions_len,rcvBuffer,newsockfd,buffer_size);
int identifiers_len=0;
readData((char*)&identifiers_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
int* identifiers=new int[identifiers_len];
readData((char*)identifiers,sizeof(int)*identifiers_len,rcvBuffer,newsockfd,buffer_size);

  
  ((de::tum::PQIDispatcherImplementation*) ref)->requestPartsInformation(offset,offset_len,size,size_len,dimensions,dimensions_len,identifiers,identifiers_len);
  
  sendData((char*)&offset_len,sizeof(int),sendBuffer,newsockfd,buffer_size);
sendData((char*)offset,sizeof(double)*offset_len,sendBuffer,newsockfd,buffer_size);
sendData((char*)&size_len,sizeof(int),sendBuffer,newsockfd,buffer_size);
sendData((char*)size,sizeof(double)*size_len,sendBuffer,newsockfd,buffer_size);
sendData((char*)&dimensions_len,sizeof(int),sendBuffer,newsockfd,buffer_size);
sendData((char*)dimensions,sizeof(int)*dimensions_len,sendBuffer,newsockfd,buffer_size);
sendData((char*)&identifiers_len,sizeof(int),sendBuffer,newsockfd,buffer_size);
sendData((char*)identifiers,sizeof(int)*identifiers_len,sendBuffer,newsockfd,buffer_size);

}


void invoker_requestNumberOfParts(void* ref,int sockfd,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer){
  int parts;
readData((char*)&parts,sizeof(int),rcvBuffer,newsockfd,buffer_size);

  
  ((de::tum::PQIDispatcherImplementation*) ref)->requestNumberOfParts(parts);
  
  sendData((char*)&parts,sizeof(int),sendBuffer,newsockfd,buffer_size);

}

void close(int &sockfd,int &newsockfd){
     if(newsockfd>=0)
         close(newsockfd);
     if(sockfd>=0)
         close(sockfd);
}

extern "C"{
void socket_loop_(){
  void* ref=NULL;
  int sockfd=-1,newsockfd=-1;
  int methodId=0;
  int bufferSize=1024;
  char *sendBuffer=new char[bufferSize];
  char *rcvBuffer=new char[bufferSize];
  void (*invokers[4])(void*,int,int,int,char*,char*);
  invokers[0]=invoker_create_instance;
  invokers[1]=invoker_destroy_instance;
  invokers[3]=invoker_requestPartsInformation;
invokers[2]=invoker_requestNumberOfParts;

  open(50000,sockfd,newsockfd);
  
  
  invokers[0](&ref,sockfd,newsockfd,bufferSize,rcvBuffer,sendBuffer);
  while(methodId!=-1){
     readData((char*)&methodId,sizeof(int),rcvBuffer,newsockfd,bufferSize);
     invokers[methodId+2](ref,sockfd,newsockfd,bufferSize,rcvBuffer,sendBuffer);
     
  }
  invokers[1](ref,sockfd,newsockfd,bufferSize,rcvBuffer,sendBuffer);
  close(sockfd,newsockfd);   
     


  delete [] sendBuffer;
  delete [] rcvBuffer;    
}
}

