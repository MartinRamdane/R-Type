/*
** EPITECH PROJECT, 2023
** Instance.cpp
** File description:
** Instance
*/

#include "Instance.hpp"

Instance::Instance(int id) : _threadPool(1), _port((int)(4210 + id)), _udpServer(_io_service, (int)(4210 + id)), _id(id)
{
  _core = new Core();
  _udpServer.setInstance(this);
  _threadPool.enqueue([this]()
  { _io_service.run(); });
  // while (1) {
  //   std::vector<std::string> protocol = _core->mainLoop("rien");
  //   for (auto &p : protocol) {
  //     _udpServer.handleEngineEvents(p);
  //   }
  // }
}

Instance::~Instance()
{
}