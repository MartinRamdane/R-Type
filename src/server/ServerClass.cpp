/*
** EPITECH PROJECT, 2023
** Server.cpp
** File description:
** Server
*/

#include "ServerClass.hpp"

ServerClass::ServerClass() : _threadPool(1), _tcpServer(_io_service, 4242)
{
  _tcpServer.setServer(this);
  _threadPool.enqueue([this]() {
    _io_service.run();
  });
}

ServerClass::~ServerClass()
{
}

void ServerClass::createInstance()
{
}