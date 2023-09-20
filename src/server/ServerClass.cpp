/*
** EPITECH PROJECT, 2023
** Server.cpp
** File description:
** Server
*/

#include "ServerClass.hpp"

ServerClass::ServerClass() : _threadPool(1), _udpServer(_io_service, 4241)
{
  _udpServer.setServer(this);
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