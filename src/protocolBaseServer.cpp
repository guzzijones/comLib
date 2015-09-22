#include "protocolBaseServer.h"
//create constructor no arguments to be used when it is a server

protocolBaseServer::protocolBaseServer(const int & sock){
   _sock=sock;
   if(testSocket()==false){
      throw std::runtime_error("socket not connected");
   }
      
   _validProtocol=true;
}
protocolBaseServer::protocolBaseServer(std::string ip,int port){
   int sockfd = 0;
   struct sockaddr_in serv_addr;

                                                          // data 
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
      printf("\n Error : Could not create socket \n");
      _validProtocol=false ;
    }
 
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  serv_addr.sin_addr.s_addr = inet_addr(ip.c_str());
   if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
       
      printf("\n Error : Connect Failed \n");
      _validProtocol=false;
      throw std::runtime_error("could not connect to socket");
    }
   _validProtocol=true; 
}
void protocolBaseServer::DoRead(){
//first get, size, type
//then get size, message
   int32_t dataLength;

   //read in todo
//   std::cout << "reading length now" << std::endl;
   protoService<int32_t>::DoRead(_sock,(char*)&dataLength,sizeof(int32_t));
   dataLength = ntohl(dataLength ); // Ensure host system byte order on the int;from the network will be network byte order
 //  std::cout << "data length: " << dataLength << std::endl;
   char rcvBuf[dataLength];    // Allocate a receive buffer
  // std::cout << "reading now" << std::endl;
   protoService<int32_t>::DoRead(_sock,rcvBuf,dataLength); // Receive the string data
  // std::cout << "rcvBuf: " << rcvBuf << std::endl;
  
   _totalMessage=std::string(rcvBuf);
  // std::cout << "totalMessage length: "  << _totalMessage.length() << " message: " << _totalMessage << std::endl;
  // std::cout << "read" << std::endl;
  
}

void protocolBaseServer::DoWrite( const std::string & inMessage){ 
   _totalMessage=inMessage;
  // std::cout << "totalMessage: " << _totalMessage << std::endl;
   int32_t dataLength=_totalMessage.length();
   int32_t orgdataLength=_totalMessage.length();

  // std::cout << "data length: " << orgdataLength << std::endl;
   //read in todo
   dataLength = htonl(dataLength ); // Ensure host system byte order on the int;from the network will be network byte order
  // std::cout << "writing length now" << std::endl;
   protoService<int32_t>::DoWrite(_sock,(char*)&dataLength,sizeof(int32_t));
  // std::cout << "written length" << std::endl;
  // std::cout << "writing :" << (char*)_totalMessage.c_str() << "end" << std::endl;
   protoService<int32_t>::DoWrite(_sock,(char*)_totalMessage.c_str(),orgdataLength); // send the string dataEE
  // std::cout << "wrote :" << _totalMessage << std::endl;

}

std::string protocolBaseServer::WriteRead(const std::string & in){
   DoRead();
   std::string result;
   DoWrite(result);
   return result;

}
bool protocolBaseServer::testSocket(){
   int error = 0;
   socklen_t len = sizeof (error);
   int retval = getsockopt (_sock, SOL_SOCKET, SO_ERROR, &error, &len);
   if (retval != 0) {
       /* there was a problem getting the error code */
       fprintf(stderr, "error getting socket error code: %s\n", strerror(retval));
       return false;
   }

   if (error != 0) {
       /* socket has a non zero error status */
       fprintf(stderr, "socket error: %s\n", strerror(error));
      return false;
   }
   return true;
}
