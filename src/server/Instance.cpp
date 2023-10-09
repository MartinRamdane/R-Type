/*
** EPITECH PROJECT, 2023
** Instance.cpp
** File description:
** Instance
*/

#include "Instance.hpp"

Instance::Instance(int id) : _threadPool(2), _port((int)(4210 + id)), _udpServer(_io_service, (int)(4210 + id)), _id(id)
{
  _core = new Core();
   _udpServer.setInstance(this);
   _threadPool.enqueue([this]()
                       { _io_service.run(); });
  //implement the main loop in thread
  _threadPool.enqueue([this]()
                      { mainLoop(); });
}

Instance::~Instance()
{
}

void Instance::mainLoop()
{
  while (1)
  {
    _udpServer.handleMessages(-1, true);
    std::vector<std::string> protocol = _core->mainLoop("");
    for (auto message : protocol)
    {
      Event evt;
      evt.ACTION_NAME  = ACTION::SPRITE;
      evt.body_size = message.size();
      evt.body = message;
      std::cout << "message: " << message << std::endl;
      _udpServer.sendEventToAllClients(evt);
    }
  }
}
