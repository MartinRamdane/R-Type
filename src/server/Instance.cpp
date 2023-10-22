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
  _udpServer->setNbPlayers(1);
  _udpServer->setInstance(this);
  _threadPool.enqueue([this]()
                      { _io_service.run(); });
  // implement the main loop in thread
  _core = new Core(_udpServer);
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
    int nbPlayers = _udpServer->getNbPlayers();
    if (nbPlayers == 0)
    {
      continue; // TODO: destroy the instance
    }
    if (_core->isReset())
    {
      _core->setReset(false);
      Event evt;
      evt.ACTION_NAME = ACTION::RESET;
      evt.body = std::vector<uint8_t>();
      evt.body_size = sizeof(evt.body);
      _udpServer->sendEventToAllClients(evt);
    }
    _core->mainLoop(_events, _udpServer);
  }
}
