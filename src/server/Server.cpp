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
    _playerIdToGive = 1;
}

ServerClass::~ServerClass()
{
    _server->StopServer();
}

InstanceInfos ServerClass::createInstance()
{
    Instance *instance = new Instance(_instances.size());
    instance->setServer(this);
    _instances.push_back(instance);
    InstanceInfos instanceinfos;
    instanceinfos.id = instance->getId();
    instanceinfos.port = instance->getPort();
    return instanceinfos;
}

void ServerClass::interpretEvent(Event &event)
{
    if (event.ACTION_NAME == ACTION::CREATE)
    {
        std::cout << "CREATE" << std::endl;
    }
}

int ServerClass::getPortInstance(int instanceId)
{
    return _instances[instanceId]->getPort();
}

void ServerClass::loop()
{
    while (1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        _server->HandleMessages(-1, true);
    }
}