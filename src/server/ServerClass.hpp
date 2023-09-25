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

class ServerClass {
  public:
    ServerClass();
    ~ServerClass();
    void createInstance();

  protected:
  private:
    boost::asio::io_service _io_service;
    ThreadPool _threadPool;
    TCPServer _tcpServer;
};
