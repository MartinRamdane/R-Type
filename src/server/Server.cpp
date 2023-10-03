/*
** EPITECH PROJECT, 2023
** Server.cpp
** File description:
** Server
*/

#include "Server.hpp"
#include "ServerImpl.hpp"

ServerClass::ServerClass() : _threadPool(1)
{
    MyServer *server = new MyServer(4244, this);
    _server = server;
    _server->StartServer();
}

ServerClass::~ServerClass()
{
    _server->StopServer();
    std::cout << "[Server] is destroyed" << std::endl;
}

InstanceInfos ServerClass::createInstance()
{
    std::cout << "instances size: " << _instances.size() << std::endl;
    Instance *instance = new Instance(_instances.size());
    instance->setServer(this);
    _instances.push_back(instance);
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

int ServerClass::getPortInstance(int instanceId)
{
    return _instances[instanceId]->getPort();
}

void ServerClass::loop()
{
    _server->HandleMessages(-1, true);
}