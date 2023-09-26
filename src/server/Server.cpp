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
//  });
}

ServerClass::~ServerClass()
{
}

InstanceInfos ServerClass::createInstance()
{
    std::cout << "instances size: " << _instances.size() << std::endl;
    Instance *instance = new Instance(_instances.size());
    instance->setServer(this);
    _instances.push_back(instance);
    //TODO RENVOYER INFOS INSTANCE
    InstanceInfos instanceinfos;
    instanceinfos.id = instance->getId();
    instanceinfos.port = instance->getPort();
    std::cout << "creating instance !" << std::endl;
    return instanceinfos;
}

void ServerClass::interpretEvent(Event &event)
{
    if (event.ACTION_NAME == ACTION::CREATE) {
        std::cout << "CREATE" << std::endl;
    }
}