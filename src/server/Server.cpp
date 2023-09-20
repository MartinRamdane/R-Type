/*
** EPITECH PROJECT, 2023
** Server.cpp
** File description:
** Server
*/

#include "Server.hpp"

Server::Server() : _threadPool(1), _udpServer(_io_service, 4241, *this)
{
  _threadPool.enqueue([this]() {
    _io_service.run();
  });
}

Server::~Server()
{
}

void Server::createInstance()
{
}