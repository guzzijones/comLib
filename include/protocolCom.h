#ifndef PROTOCOLCOM
#define PROTOCOLCOM
#include "aTodo.h"
#include "protocolBaseServer.h"

class protocolCom{

private:


   static std::string readString(protocolBaseServer  inProtoConnection);
   static std::unique_ptr<aTodo> load(std::string const &s );
protected:

public:

   static std::string save(std::unique_ptr<aTodo> & todoIn);

   static std::unique_ptr<aTodo>  WriteRead(std::unique_ptr<aTodo> & object,std::string ip, int port);

   static std::unique_ptr<aTodo> Read(protocolBaseServer in);
   static void Write(std::unique_ptr<aTodo> & object,protocolBaseServer);


};


#endif
