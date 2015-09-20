#include "client.h"

client::client(std::string ip,int port){ 


   protocolBaseServer pclient(ip,port);//initiate client socket
   _connection=pclient;
   _tmpTodoFactory=todoFactory::create(); //create factory
   _successConnect=true;

   } 

/*
   //sample of how to call within program
   auto anExecTodo=client._tmpTodoFactory->createExec(commandAsString); //create ExecTodo from factory
   auto anExecReturned = client.send(anExecTodo)
*/

std::unique_ptr<aTodo> client::send(std::unique_ptr<aTodo> in ){
   std::string toSend= _tmpTodoFactory->save(in);//convert object to a string

   _connection.DoWrite(toSend);//write to the socket

   //read the object sent back
   std::string received;
   _connection.DoRead();

   auto returned = _tmpTodoFactory->load(_connection.getTotalMessage()); //load back into a an exec object
   return returned; 
}


