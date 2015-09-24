#include "protocolCom.h"
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


