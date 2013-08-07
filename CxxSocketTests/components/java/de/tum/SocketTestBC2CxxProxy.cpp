#include "de/tum/SocketTestBC2CxxProxy.h"
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
	
#include "de/tum/SocketTestBImplementation.h"

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

void accept_on_server(
#ifdef _WIN32
SOCKET&
#else
int&
#endif
sockfd,
#ifdef _WIN32
SOCKET&
#else
int&
#endif
clientfd
){
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
     *ref = new de::tum::SocketTestBImplementation();
}

void invoker_destroy_instance(void** ref,int,int,char*,char*){
      delete ((de::tum::SocketTestBImplementation*)*ref);
  
}
#include "de/tum/QueryNativeSocketDispatcher.h"
#include "de/tum/QueryCxx2SocketPlainPort.h"
void invoker_create_client_port_for_queryServer(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer){
  long long portref=0;
  int port;
  int hostname_len=0;
  char* host;
  readData((char*)&hostname_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  host = new char[hostname_len];
  readData((char*)host,hostname_len,rcvBuffer,newsockfd,buffer_size);
  readData((char*)&port,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  portref=(long long)new de::tum::QueryCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
  delete [] host;
  sendData((char*)&portref,sizeof(long long),sendBuffer,newsockfd,buffer_size);
 
}
  

void invoker_connect_client_dispatcher_queryServer(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer){
  long long portref=0;
  int port;
  int hostname_len=0;
  char* host;
  readData((char*)&hostname_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  host = new char[hostname_len];

  readData((char*)host,hostname_len,rcvBuffer,newsockfd,buffer_size);
  readData((char*)&port,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  portref=(long long)new de::tum::QueryNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
  ((de::tum::SocketTestBImplementation*)*ref)->connectqueryServer((de::tum::QueryNativeSocketDispatcher*)portref);   
  delete[]host;
  sendData((char*)&portref,sizeof(long long),sendBuffer,newsockfd,buffer_size);
}




void invoker_disconnect_client_dispatcher_queryServer(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer){
 ((de::tum::SocketTestBImplementation*)*ref)->disconnectqueryServer();
}

void invoker_sim(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer){
  
  ((de::tum::SocketTestBImplementation*)*ref)->sim();
  
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


struct SOCKETTESTB_arg{
     void *ref;
     #ifdef _WIN32
     SOCKET
     #else
     int
     #endif
     serverfd;
     int buffer_size;
};


void socket_worker_loop(void* ref,
#ifdef _WIN32
SOCKET
#else
int
#endif
clientfd,int bufferSize){
     char *sendBuffer=new char[bufferSize];
     char *rcvBuffer=new char[bufferSize];
     void (*invokers[12])(void**,int,int,char*,char*);
     invokers[0]=invoker_create_instance;
     invokers[1]=invoker_destroy_instance;
     int methodId=0;
     invokers[4]=invoker_disconnect_client_dispatcher_queryServer;
invokers[3]=invoker_connect_client_dispatcher_queryServer;
invokers[2]=invoker_create_client_port_for_queryServer;
invokers[11]=invoker_sim;

     while(methodId!=1){
          readData((char*)&methodId,sizeof(int),rcvBuffer,clientfd,bufferSize);
          invokers[methodId](&ref,clientfd,bufferSize,rcvBuffer,sendBuffer);
     }
     delete [] sendBuffer;
     delete [] rcvBuffer;
#ifdef _WIN32
     closesocket(clientfd);
#else
     close(clientfd);    
#endif    
     
}


#ifdef _WIN32
DWORD WINAPI server_deamon_run(void* daemon_args){
      SOCKET clientfd;
#else  
void* server_deamon_run(void* daemon_args){
      int clientfd=0;
#endif
      
      accept_on_server(((SOCKETTESTB_arg*)daemon_args)->serverfd,clientfd);
      std::cout<<"server accepted"<<std::endl;
      socket_worker_loop(((SOCKETTESTB_arg*)daemon_args)->ref,clientfd,((SOCKETTESTB_arg*)daemon_args)->buffer_size);
}
extern "C"{



#ifdef _WIN32
void SOCKET_CLIENT_LOOP(){
#else
void socket_client_loop_(){
#endif
  
#ifdef _WIN32
SOCKET sockfd;
SOCKET clientfd;
#else
int sockfd=-1,clientfd=-1;
#endif
  SOCKETTESTB_arg daemon_args;
  daemon_args.ref=NULL;
  daemon_args.buffer_size=atoi(getenv("SOCKETTESTB_BUFFER_SIZE"));
  char* hostname;
  char* client_port;
  char* daemon_port;
  char* java_client_flag_as_str;
  bool java_client_flag=true;
  hostname=getenv("SOCKETTESTB_HOSTNAME");
  void (*invokers[2])(void**,int,int,char*,char*);
  invokers[0]=invoker_create_instance;
  invokers[1]=invoker_destroy_instance;
  client_port=getenv("SOCKETTESTB_PORT");
  daemon_port=getenv("SOCKETTESTB_DAEMON_PORT");
  java_client_flag_as_str=getenv("SOCKETTESTB_JAVA");
  if(hostname==NULL)
     hostname="localhost";
  if(client_port==NULL)
     client_port="50000";
  if(daemon_port==NULL)
     daemon_port="50001";
  if(java_client_flag_as_str!=NULL&&strcmp(java_client_flag_as_str,"off")==0)
     java_client_flag=false;
  if(java_client_flag)         
     open_client(hostname,client_port,sockfd,clientfd);
  bind_server(daemon_port,daemon_args.serverfd);
  invokers[0](&daemon_args.ref,clientfd,daemon_args.buffer_size,NULL,NULL);
  for(int i=0;i<5;i++){
#ifdef _WIN32    
     CreateThread(NULL, 0,server_deamon_run, &daemon_args, 0, NULL);
#else     
     pthread_t task;
     pthread_create(&task,NULL,server_deamon_run,&daemon_args);
#endif
  }
  if(java_client_flag)       
     socket_worker_loop(daemon_args.ref,clientfd,daemon_args.buffer_size);
#ifdef _WIN32
  closesocket(sockfd);
#else
  close(sockfd);
#endif
  
 
   
  #ifdef _WIN32
  WSACleanup();
  #endif   


    
}

#

}

