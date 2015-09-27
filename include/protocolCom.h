#ifndef PROTOCOLCOM
#define PROTOCOLCOM
#include "aTodo.h"
#include "protocolBaseServer.h"

class protocolCom{

private:
   int _port;
   std::string _ip;

   static std::string readString(protocolBaseServer  inProtoConnection);
   static std::unique_ptr<aTodo> load(std::string const &s );
protected:

public:
   protocolCom(std::string ip="127.0.0.1",int port=3000){
      _ip=ip;
      _port=port;

   }
   static std::string save(std::unique_ptr<aTodo> & todoIn);

   static std::unique_ptr<aTodo>  WriteRead(std::unique_ptr<aTodo> & object,std::string ip, int port);
   std::unique_ptr<aTodo>  WriteRead(std::unique_ptr<aTodo> & object);

   static std::unique_ptr<aTodo> Read(protocolBaseServer in);
   static void Write(std::unique_ptr<aTodo> & object,protocolBaseServer);


};


#endif
