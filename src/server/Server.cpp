/*
** EPITECH PROJECT, 2023
** Server.cpp
** File description:
** Server
*/

#include "Server.hpp"
#include "ServerImpl.hpp"

ServerClass::ServerClass() : _threadPool(1) {
    MyServer* server = new MyServer(4244, this);
    _server = server;
    _server->StartServer();
}

ServerClass::~ServerClass() {
    _server->StopServer();
}

InstanceInfos ServerClass::createInstance(std::string gameName) {
    Instance* instance = new Instance(_instances.size(), gameName);
    instance->setServer(this);
    _instances.push_back(instance);
    InstanceInfos instanceinfos;
    instanceinfos.id = instance->getId();
    instanceinfos.port = instance->getPort();
    return instanceinfos;
}

void ServerClass::interpretEvent(Event& event) {
    if (event.ACTION_NAME == ACTION::CREATE) {
        std::cout << "CREATE" << std::endl;
    }
}

int ServerClass::getPortInstance(int instanceId) {
    return _instances[instanceId]->getPort();
}

void ServerClass::loop() {
    while (1) {
        _server->HandleMessages(-1, true);
    }
}

Instance* ServerClass::getInstanceByPort(int port) {
    for (auto instance : _instances) {
        if (instance->getPort() == port)
            return instance;
    }
    return nullptr;
}

void ServerClass::deleteInstance(int instanceId) {
    Instance* instance = _instances[instanceId];
    _instances.erase(_instances.begin() + instanceId);
    delete instance;
}