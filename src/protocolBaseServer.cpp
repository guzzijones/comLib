#include "protocolBaseServer.h"
protocolBaseServer::protocolBaseServer(const int & sock){
   _sock=sock;
 //  std::cout << "in protocolBaseServer" << std::endl;
  // try{
//   DoRead();
 //  }catch(std::exception &e){
  //    std::cout << "Error: " << e.what() << std::endl;
  // }
  _validProtocol=true;
}
protocolBaseServer::protocolBaseServer(std::string ip,int port){
   int sockfd = 0,n = 0;
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
    }
   _validProtocol=true; 
}
void protocolBaseServer::DoRead(){
//first get, size, type
//then get size, message
   int32_t dataLength;

   //read in todo
//   std::cout << "reading length now" << std::endl;
   protoService<int32_t>::DoRead(_sock,&dataLength,sizeof(int32_t));
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
   protoService<int32_t>::DoWrite(_sock,&dataLength,sizeof(int32_t));
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

