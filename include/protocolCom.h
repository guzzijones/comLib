#ifndef PROTOCOLCOM
#define PROTOCOLCOM
#include "aTodo.h"
#include "protocolBaseServer.h"

class protocolCom{

private:


protected:

public:

   static std::string save(std::unique_ptr<aTodo> & todoIn);
   static std::unique_ptr<aTodo> load(std::string const &s );
   static std::unique_ptr<aTodo>  WriteRead(std::unique_ptr<aTodo> & object,std::string ip, int port);



};


#endif
