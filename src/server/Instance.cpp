/*
** EPITECH PROJECT, 2023
** Instance.cpp
** File description:
** Instance
*/

#include "Instance.hpp"

Instance::Instance(int id) : _id(id), _port((int)(4210 + id)), _threadPool(3)
{
  _udpServer = new UDPServer(_io_service, (int)(4210 + id));
  _core = new Core();
   _udpServer->setInstance(this);
   _threadPool.enqueue([this]()
                       { _io_service.run(); });
  //implement the main loop in thread
  _threadPool.enqueue([this]()
  { MessagesLoop(); });
  _threadPool.enqueue([this]()
  { EventLoop(); });
}

Instance::~Instance()
{
}

void Instance::MessagesLoop()
{
  while (1)
  {
    _udpServer->handleMessages(-1, true);
  }
}

void Instance::EventLoop()
{
  while (1)
  {
    if (_udpServer->getNbPlayers() == 0)
    {
      std::cout << "No players connected" << std::endl;
      continue;
    }
    std::vector<std::string> protocol = _core->mainLoop(_events);
    for (auto message : protocol)
    {
      Event evt;
      evt.ACTION_NAME  = ACTION::SPRITE;
      evt.body_size = message.size();
      evt.body = message;
      std::cout << "message: " << message << std::endl;
      _udpServer->sendEventToAllClients(evt);
    }
  }
}
