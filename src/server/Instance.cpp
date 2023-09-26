/*
** EPITECH PROJECT, 2023
** Instance.cpp
** File description:
** Instance
*/

#include "Instance.hpp"

Instance::Instance(int id) : _threadPool(1), _port((int)(4210 + id)), _udpServer(_io_service, (int)(4210 + id)), _id(id)
{
  // use _serverRef to send the UDP server port to the client
  _udpServer.setInstance(this);
  _threadPool.enqueue([this]() {
    _io_service.run();
  });
  // _udpServer handle a new connection from the first client who has created the instance
  // _nbPlayers should be incremented and the client should be added to the _clients vector
  std::cout << "nb players in UDP Server: " << _udpServer.getNbPlayers() << std::endl;
}

Instance::~Instance()
{
}