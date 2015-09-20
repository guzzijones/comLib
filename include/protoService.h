#ifndef PROTOSERVICE_H
#define PROTOSERVICE_H

extern "C"
{
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
   #include <signal.h>
}

#include <cerrno>
#include <iostream>
#include <stdexcept>

template <class T>
class protoService{
private:

protected:

public:
//has static methods for send and receive

static void DoWrite(const int & sock,char * data,T size);
static void DoRead(const int & sock,char * data,T size);
};
#include "../src/protoService.cpp"
#endif
