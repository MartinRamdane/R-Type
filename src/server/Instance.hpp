/*
** EPITECH PROJECT, 2023
** Instance.hpp
** File description:
** Instance
*/

#ifndef HEADER_INSTANCE
#define HEADER_INSTANCE
#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include "UDPServer.hpp"
#include "ThreadPool.hpp"
#include "../engine/Core.hpp"

class ServerClass;

class Instance
{
public:
    Instance(int _id);
    Instance(const Instance &) = delete;
    ~Instance(); // destroy the instance if nbPlayers === 0
    int getId() const { return _id; }
    UDPServer &getUDPServer() { return _udpServer; }
    void setServer(ServerClass *server) { _serverRef = server; }
    int getNbPlayers() const { return _udpServer.getNbPlayers(); }
    int getPort() const { return _port; }

protected:
private:
    int _id;
    int _port;
    boost::asio::io_service _io_service;
    UDPServer _udpServer;
    ServerClass *_serverRef;
    ThreadPool _threadPool;
    Core _core;
};

#endif /* !HEADER_INSTANCE */
