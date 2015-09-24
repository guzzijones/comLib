#ifndef TODOFACTORY_H
#define TODOFACTORY_H

#include "todoExec.h"
#include <memory>


class todoFactory{

   // todoFactory()=default;
   public:
    // static std::unique_ptr<todoFactory> create(){return std::move(std::unique_ptr<todoFactory>(new todoFactory));};
     
     //create an exec object
      static std::unique_ptr<aTodo> createExec(std::string command) {return std::unique_ptr<aTodo>(new todoExec(command));};
   protected:

   private:



};
#endif
