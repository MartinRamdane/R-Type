/*
** EPITECH PROJECT, 2023
** Server.hpp
** File description:
** Server
*/

#pragma once
#include <iostream>
#include "TCPServer.hpp"
#include "ThreadPool.hpp"
#include "EventHandler.hpp"
#include "Instance.hpp"
#include <thread>

struct InstanceInfos {
  int id;
  int port;
};

class ServerClass {
  public:
    ServerClass();
    ~ServerClass();
    InstanceInfos createInstance();
    int getPortInstance(int instanceId);
    int getNbPlayersInstance(int instanceId) { return _instances[instanceId]->getNbPlayers();}
    void interpretEvent(Event &event);
  protected:
  private:
    boost::asio::io_service _io_service;
    ThreadPool _threadPool;
    TCPServer _tcpServer;
    std::vector<Instance *> _instances;
};
