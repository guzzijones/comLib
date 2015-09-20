#ifndef PROTOCOLBASESERVER_H
#define PROTOCOLBASESERVER_H
#include <stdexcept>
#include "protoService.h"
#include <bitset>
class protocolBaseServer{
private:
   std::string _totalMessage;
   int  _sock;
   bool _validProtocol;
protected:

public:
   protocolBaseServer(std::string ip="127.0.0.1",int port =3000); 
   protocolBaseServer(const int & sock);
   //creates socket and sets two fields to be send
   //uses protoService::DoWrite to send both field
   bool getValidProtocol(){return _validProtocol;};
   std::string WriteRead(const std::string & in);
   void DoRead();
   void DoWrite(const std::string & in); 
   //uses protoService::DoRead to read 
   std::string getTotalMessage()const{return _totalMessage;};
   int getSock()const{return _sock;};
   void setMessage(const std::string & in){_totalMessage=in;};
   
};
#endif
