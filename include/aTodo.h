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

   private:

   friend class boost::serialization::access;
   template  <class Ar>
   void serialize(Ar &, unsigned){};//every class that inherits from aTodo must have a serialize function


};
#endif
