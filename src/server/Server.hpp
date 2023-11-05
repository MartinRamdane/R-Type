/*
** EPITECH PROJECT, 2023
** Server.hpp
** File description:
** Server
*/

#pragma once

#include <iostream>
#include <thread>
#include "../global/EventHandler.hpp"
#include "../global/ThreadPool.hpp"
#include "Instance.hpp"
#include "TCPServer.hpp"

class MyServer;  // Forward declaration
struct InstanceInfos {
    int id;
    int port;
};

class ServerClass {
   public:
    ServerClass();

    ~ServerClass();

    InstanceInfos createInstance(std::string gameName);

    void deleteInstance(int instanceId);

    int getPortInstance(int instanceId);

    int getNbPlayersInstance(int instanceId) {
        return _instances[instanceId]->getNbPlayers();
    }

    void interpretEvent(Event& event);

    int getInstancesNb() { return _instances.size(); }

    std::vector<Instance*> getInstances() { return _instances; }

    Instance* getInstance(int id) { return _instances[id]; }

    Instance* getInstanceByPort(int port);

    void loop();

   protected:
   private:
    boost::asio::io_service _io_service;
    ThreadPool _threadPool;
    MyServer* _server;
    std::vector<Instance*> _instances;
};
