#ifndef CLIENT_H
#define CLIENT_H

extern "C"{
#if defined(_WIN32) 
    #include <winsock.h>
#elif defined(__unix__)
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netdb.h>
    #include <arpa/inet.h>
#endif
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
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
