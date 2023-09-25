/*
** EPITECH PROJECT, 2023
** Server.hpp
** File description:
** Server
*/

#pragma once
#include <iostream>
#include "UDPServer.hpp"
#include "ThreadPool.hpp"

class ServerClass {
  public:
    ServerClass();
    ~ServerClass();
    void createInstance();

  protected:
  private:
    boost::asio::io_service _io_service;
    ThreadPool _threadPool;
    UDPServer _udpServer;
};
