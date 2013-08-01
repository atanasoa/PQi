#include "de/tum/SocketTestAC2CxxProxy.h"
#ifdef _WIN32
	#include <winsock2.h>
	#include <ws2tcpip.h>
	
	#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  
	#define bcopy(b1,b2,len) (memmove((b2), (b1), (len)), (void) 0)
	#pragma comment(lib, "Ws2_32.lib")
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <unistd.h>
	#include <arpa/inet.h>
#endif

#include <stdio.h>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <stdlib.h>
	
#include "de/tum/SocketTestAImplementation.h"

void open_client(const char* hostname,const char* port,
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
&newsockfd){
#ifdef _WIN32
		 WSADATA wsaData;
		 int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	     assert (iResult == 0);
#endif
          struct addrinfo *result = NULL,
     	                   hints;
          bzero( &hints, sizeof(hints) );
          hints.ai_family = AF_UNSPEC;
          hints.ai_socktype = SOCK_STREAM;
          hints.ai_protocol = IPPROTO_TCP;
          getaddrinfo(hostname, port, &hints, &result);
          sockfd = socket(result->ai_family, result->ai_socktype, 
            result->ai_protocol);
          assert(sockfd >= 0);
          
          int tries=60;
                while(tries>0){
                 if (connect(sockfd, result->ai_addr, (int)result->ai_addrlen)==0)
                    break;
                         tries--;
#ifdef _WIN32
						 Sleep(1000);
#else
						 sleep(1);
#endif	
                }   
         newsockfd=sockfd;
}

void bind_server(const char* port,
#ifdef _WIN32
SOCKET
#else
int
#endif 
&sockfd
){


#ifdef _WIN32
		 WSADATA wsaData;
		 int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	     assert (iResult == 0);
#endif
          struct addrinfo hints;
	      struct addrinfo *result = NULL;
         

          bzero(&hints, sizeof(hints));
          hints.ai_family = AF_INET;
          hints.ai_socktype = SOCK_STREAM;
		  hints.ai_protocol = IPPROTO_TCP;
		  hints.ai_flags = AI_PASSIVE;
          getaddrinfo(NULL, port, &hints, &result);
		  
		  sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
          assert (sockfd>=0);
          bind(sockfd, result->ai_addr, (int)result->ai_addrlen);
		  
          listen(sockfd,5);
         
        
}

void accept_on_server(int& sockfd,int& clientfd){
           clientfd = accept(sockfd,
                    NULL,
                    NULL);
          assert (clientfd >= 0);
}

void sendData(char* data, size_t numberOfBytes, char* sendBuffer,
#ifdef _WIN32
SOCKET
#else
int
#endif 
newsockfd,int bufferSize){
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
               n = 
#ifdef _WIN32
				   send(
#else

				   write(
#endif
				   newsockfd,send_buffer_ptr,bufferSize-send_bytes
#ifdef _WIN32
				   ,0
#else

#endif
				   );
               if(n>0){
                    send_bytes+=n;
                    send_buffer_ptr+=n;
               }
          }
          total_send_bytes+=send_bytes;
          data_ptr+=send_bytes;
     }

}


void readData(char* data,size_t size_of_data,char* readBuffer,
#ifdef _WIN32
SOCKET
#else
int
#endif 
newsockfd, int bufferSize){
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
                    local_bytes_received = 
#ifdef _WIN32
						recv(
#else
						read(
#endif
							newsockfd,buffer_ptr,bufferSize-bytes_received
#ifdef _WIN32
							,0
#else
#endif
							);
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

void invoker_create_instance(void** ref,int,int,char*,char*){
     *ref = new de::tum::SocketTestAImplementation();
}

void invoker_destroy_instance(void** ref,int,int,char*,char*){
      delete ((de::tum::SocketTestAImplementation*)*ref);
  
}
void invoker_forwardAnswer(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer){
  int data_len=0;
readData((char*)&data_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* data=new double[data_len];
readData((char*)data,sizeof(double)*data_len,rcvBuffer,newsockfd,buffer_size);
int rid;
readData((char*)&rid,sizeof(int),rcvBuffer,newsockfd,buffer_size);

  ((de::tum::SocketTestAImplementation*)*ref)->forwardAnswer(data,data_len,rid);
  
}
void invoker_getQueryDescription(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer){
  int offset_len=0;
readData((char*)&offset_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* offset=new double[offset_len];
readData((char*)offset,sizeof(double)*offset_len,rcvBuffer,newsockfd,buffer_size);
int size_len=0;
readData((char*)&size_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* size=new double[size_len];
readData((char*)size,sizeof(double)*size_len,rcvBuffer,newsockfd,buffer_size);
int resolution_len=0;
readData((char*)&resolution_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
int* resolution=new int[resolution_len];
readData((char*)resolution,sizeof(int)*resolution_len,rcvBuffer,newsockfd,buffer_size);
int mids_len=0;
readData((char*)&mids_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
int* mids=new int[mids_len];
readData((char*)mids,sizeof(int)*mids_len,rcvBuffer,newsockfd,buffer_size);

  ((de::tum::SocketTestAImplementation*)*ref)->getQueryDescription(offset,offset_len,size,size_len,resolution,resolution_len,mids,mids_len);
  sendData((char*)&offset_len,sizeof(int),sendBuffer,newsockfd,buffer_size);
sendData((char*)offset,sizeof(double)*offset_len,sendBuffer,newsockfd,buffer_size);
sendData((char*)&size_len,sizeof(int),sendBuffer,newsockfd,buffer_size);
sendData((char*)size,sizeof(double)*size_len,sendBuffer,newsockfd,buffer_size);
sendData((char*)&resolution_len,sizeof(int),sendBuffer,newsockfd,buffer_size);
sendData((char*)resolution,sizeof(int)*resolution_len,sendBuffer,newsockfd,buffer_size);
sendData((char*)&mids_len,sizeof(int),sendBuffer,newsockfd,buffer_size);
sendData((char*)mids,sizeof(int)*mids_len,sendBuffer,newsockfd,buffer_size);

}
void invoker_getNumberOfParts(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer){
  int parts;
readData((char*)&parts,sizeof(int),rcvBuffer,newsockfd,buffer_size);

  ((de::tum::SocketTestAImplementation*)*ref)->getNumberOfParts(parts);
  sendData((char*)&parts,sizeof(int),sendBuffer,newsockfd,buffer_size);

}

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
&newsockfd){
#ifdef _WIN32
	 if(newsockfd>=0)
         closesocket(newsockfd);
     if(sockfd>=0)
         closesocket(sockfd);
#else

     if(newsockfd>=0)
         close(newsockfd);
     if(sockfd>=0)
         close(sockfd);
#endif
}

struct SOCKETTESTA_arg{
     void *ref;
     int serverfd;
     int buffer_size;
};
void socket_worker_loop(void* ref,int clientfd,int bufferSize){
     char *sendBuffer=new char[bufferSize];
     char *rcvBuffer=new char[bufferSize];
     void (*invokers[12])(void**,int,int,char*,char*);
     invokers[0]=invoker_create_instance;
     invokers[1]=invoker_destroy_instance;
     int methodId=0;
     invokers[7]=invoker_forwardAnswer;
invokers[6]=invoker_getQueryDescription;
invokers[5]=invoker_getNumberOfParts;

     while(methodId!=1){
          readData((char*)&methodId,sizeof(int),rcvBuffer,clientfd,bufferSize);
          invokers[methodId](&ref,clientfd,bufferSize,rcvBuffer,sendBuffer);
     }
     delete [] sendBuffer;
     delete [] rcvBuffer;
     close(clientfd);    
     
}


void* server_deamon_run(void* daemon_args){
      int clientfd=0;
      accept_on_server(((SOCKETTESTA_arg*)daemon_args)->serverfd,clientfd);
      std::cout<<"server accepted"<<std::endl;
      socket_worker_loop(((SOCKETTESTA_arg*)daemon_args)->ref,clientfd,((SOCKETTESTA_arg*)daemon_args)->buffer_size);
}
extern "C"{



#ifdef _WIN32
void SOCKET_CLIENT_LOOP(){
#else
void socket_client_loop_(){
#endif
  
#ifdef _WIN32
SOCKET sockfd;
SOCKET newsockfd;
#else
int sockfd=-1,clientfd=-1;
#endif
  SOCKETTESTA_arg daemon_args;
  daemon_args.ref=NULL;
  daemon_args.buffer_size=atoi(getenv("SOCKETTESTA_BUFFER_SIZE"));
  char* hostname;
  char* client_port;
  char* daemon_port;
  
  hostname=getenv("SOCKETTESTA_HOSTNAME");
  void (*invokers[2])(void**,int,int,char*,char*);
  invokers[0]=invoker_create_instance;
  invokers[1]=invoker_destroy_instance;
  client_port=getenv("SOCKETTESTA_PORT");
  daemon_port=getenv("SOCKETTESTA_DAEMON_PORT");
  open_client(hostname,client_port,sockfd,clientfd);
  bind_server(daemon_port,daemon_args.serverfd);
  invokers[0](&daemon_args.ref,clientfd,daemon_args.buffer_size,NULL,NULL);
  for(int i=0;i<5;i++){
     pthread_t task;
     pthread_create(&task,NULL,server_deamon_run,&daemon_args);
  }
  socket_worker_loop(daemon_args.ref,clientfd,daemon_args.buffer_size);
  close(sockfd);
  
 
   
  #ifdef _WIN32
  WSACleanup();
  #endif   


    
}

#ifdef _WIN32
void SOCKET_SERVER_LOOP(){
#else
void socket_server_loop_(){
#endif
  void* ref=NULL;
#ifdef _WIN32
SOCKET sockfd;
SOCKET newsockfd;
#else
int sockfd=-1,newsockfd=-1;
#endif
 
  int methodId=0;
  int bufferSize=atoi(getenv("SOCKETTESTA_BUFFER_SIZE"));
  char *sendBuffer=new char[bufferSize];
  char *rcvBuffer=new char[bufferSize];
  char* port_str;
  port_str=getenv("SOCKETTESTA_PORT");
  void (*invokers[12])(void**,int,int,char*,char*);
  invokers[0]=invoker_create_instance;
  invokers[1]=invoker_destroy_instance;
  invokers[7]=invoker_forwardAnswer;
invokers[6]=invoker_getQueryDescription;
invokers[5]=invoker_getNumberOfParts;

  //open_server(port_str,sockfd,newsockfd);
  
  
  invokers[0](&ref,newsockfd,bufferSize,rcvBuffer,sendBuffer);
  while(methodId!=1){
     readData((char*)&methodId,sizeof(int),rcvBuffer,newsockfd,bufferSize);
     invokers[methodId](&ref,newsockfd,bufferSize,rcvBuffer,sendBuffer);
     
  }
  close(sockfd,newsockfd);   
  #ifdef _WIN32
  WSACleanup();
  #endif  


  delete [] sendBuffer;
  delete [] rcvBuffer;    
}

}

