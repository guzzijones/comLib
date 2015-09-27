#include "protocolCom.h"
std::unique_ptr<aTodo>  protocolCom::WriteRead(std::unique_ptr<aTodo> & object){

    protocolBaseServer protoConnection(_ip, _port);  
    Write(object,protoConnection);
    std::unique_ptr<aTodo> objectReturned=Read(protoConnection);
    return objectReturned;
}

//static
std::string protocolCom::save(std::unique_ptr<aTodo> & todoIn){
   std::string out;
   boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>>os(out);
   boost::archive::text_oarchive archive(os);

   archive << todoIn;
   return out;

}

std::unique_ptr<aTodo> protocolCom::load(std::string const &s ){
   std::unique_ptr<aTodo> p;
   boost::iostreams::stream<boost::iostreams::array_source> is(boost::iostreams::array_source{s.data(),s.size()});
   boost::archive::text_iarchive archive(is);
   archive >> p;

   return std::move(p);

}

std::unique_ptr<aTodo>  protocolCom::WriteRead(std::unique_ptr<aTodo> & object,std::string ip, int port){

    protocolBaseServer protoConnection(ip, port);  
    Write(object,protoConnection);
    std::unique_ptr<aTodo> objectReturned=Read(protoConnection);
    return objectReturned;
}


std::unique_ptr<aTodo> protocolCom::Read(protocolBaseServer inProtoBaseServer){

   std::string returnedObjectStr=readString(inProtoBaseServer);
   std::unique_ptr<aTodo> objectReturned=load(returnedObjectStr);
   
    return objectReturned; 
}

void protocolCom::Write(std::unique_ptr<aTodo> & object,protocolBaseServer protoConnection){
    std::string objToSendStr = save(object); //save to a string
    protoConnection.DoWrite(objToSendStr);//send string off to server; server does some work
    //return bool above and return results
}

//////////////
////private
//////////////
std::string protocolCom::readString(protocolBaseServer inProtoConnection){

    inProtoConnection.DoRead();  //read back in the result from the server to a string in object protoConnection
    //should return a bool here
    //throw exception otherwise
    std::string returnedObjectStr= inProtoConnection.getTotalMessage(); //save the read bytes to a string
   return returnedObjectStr; 
}

