#ifndef ATODO_H
#define ATODO_H
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/unique_ptr.hpp>

#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include "protocolBaseServer.h"
#include "memory.h"
class aTodo{
  public: 
   virtual ~aTodo(){};
   virtual void Do()=0;

   //used for a client to send and then recieve result back
   std::unique_ptr<aTodo>  WriteRead(std::string ip, int port){

    protocolBaseServer protoConnection(ip, port);  
    std::string objToSendStr = this->save(); //save to a string
    protoConnection.DoWrite(objToSendStr);//send string off to server; server does some work
    protoConnection.DoRead();  //read back in the result from the server to a string in object protoConnection
    std::string returnedObjectStr= protoConnection.getTotalMessage(); //save the read bytes to a string
    std::unique_ptr<aTodo> objectReturned=this->load(returnedObjectStr);
    return objectReturned;
   }

   private:

   friend class boost::serialization::access;
   template  <class Ar>
   void serialize(Ar &, unsigned){};//every class that inherits from aTodo must have a serialize function

//save pointer to this to a string
   std::string save(){
         std::string out;
         {
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>>os(out);
            boost::archive::text_oarchive archive(os);

            archive << this;
         }
         return out;
   }
//write aTodo pointer from string
   std::unique_ptr<aTodo> load(std::string const &s ){
         std::unique_ptr<aTodo> p;
         {
            boost::iostreams::stream<boost::iostreams::array_source> is(boost::iostreams::array_source{s.data(),s.size()});
            boost::archive::text_iarchive archive(is);
            archive >> p;

         }
         return std::move(p);

  }


};
#endif
