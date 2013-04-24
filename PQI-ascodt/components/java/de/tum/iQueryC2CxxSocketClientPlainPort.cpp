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
#include "de/tum/iQueryC2CxxSocketClientPlainPort.h"
#include "de/tum/iQueryCxx2SocketClientPlainPort.h"
#include "de/tum/iQuery.h"
extern "C" {
std::map<std::string,std::pair<int,int> > _clientConn;

void de_tum_iqueryc2socket_client_plain_port_create_instance_(long long* ptr){
     std::map<std::string,std::pair<int,int> >::iterator it=_clientConn.find( std::string("localhost:50000"));
     if(it==_clientConn.end()){
           *ptr=(long long)new de::tum::iQueryCxx2SocketClientPlainPort(
               std::string("localhost"),
               50000,
               1024
            );
           _clientConn.insert(std::pair<std::string,std::pair<int,int> >(std::string("localhost:50000"),std::pair<int,int>(((de::tum::iQueryCxx2SocketClientPlainPort*)*ptr)->getSockfd(),((de::tum::iQueryCxx2SocketClientPlainPort*)*ptr)->getNewsockfd()) ));
     }else{
         
          *ptr=(long long)new de::tum::iQueryCxx2SocketClientPlainPort(
               (*it).second.first,
               (*it).second.second,
               1024
          );
     }

}



void de_tum_iqueryc2socket_client_plain_port_destroy_instance_(long long *ptr){
     //if(port!=NULL){
     //    delete *port;
     //     *port = NULL;
     //}
}




void de_tum_iqueryc2socket_client_plain_port_requestnumberofparts_(long long* ref,int* parts){
     
     ((de::tum::iQueryCxx2SocketClientPlainPort*)*ref)->requestNumberOfParts(*parts);
}
void de_tum_iqueryc2socket_client_plain_port_requestpartsinformation_(long long* ref,double* offset, int* offset_len,double* size, int* size_len,int* dimensions,int* dimensions_len,int* identifiers,int* identifiers_len){
     
     ((de::tum::iQueryCxx2SocketClientPlainPort*)*ref)->requestPartsInformation(offset,*offset_len,size,*size_len,dimensions,*dimensions_len,identifiers,*identifiers_len);
}
}
