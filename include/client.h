#ifndef CLIENT_H
#define CLIENT_H

extern "C"{
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
}
#include <string>
#include <iostream>
#include "protocolBaseServer.h"
#include "todoFactory.h"
BOOST_SERIALIZATION_ASSUME_ABSTRACT(atodo)
BOOST_CLASS_EXPORT(todoExec)


#include <memory>

class client
{
   private:
   bool _successConnect;
   protocolBaseServer _connection;
   std::unique_ptr<todoFactory> _tmpTodoFactory;

   public:
   client(std::string, int);
   std::unique_ptr<aTodo> send(std::unique_ptr<aTodo> in );
   
};

#endif
