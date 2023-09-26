/*
** EPITECH PROJECT, 2023
** Server.cpp
** File description:
** Server
*/

#include "Server.hpp"

ServerClass::ServerClass() : _threadPool(1), _tcpServer(_io_service, 4244)
{
  _tcpServer.setServer(this);
  //TODO : CRASH QUAND ON DECOMMENTE
//   _threadPool.enqueue([this]() {
    _io_service.run();
//   });
}

ServerClass::~ServerClass()
{
}

InstanceInfos ServerClass::createInstance()
{
    // _instances.emplace_back(_instances.size());
    // _instances.back().setServer(this);
    //TODO RENVOYER INFOS INSTANCE 
    InstanceInfos instanceinfos;
    instanceinfos.id = 12;
    instanceinfos.port = 12;
    std::cout << "creating instance !" << std::endl;
    return instanceinfos;
}

void ServerClass::interpretEvent(Event &event)
{
    if (event.ACTION_NAME == ACTION::CREATE) {
        std::cout << "CREATE" << std::endl;
    }
}