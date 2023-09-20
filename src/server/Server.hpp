/*
** EPITECH PROJECT, 2023
** Server.hpp
** File description:
** Server
*/

#ifndef HEADER_SERVER
#define HEADER_SERVER
#include <iostream>
#include "UDPServer.hpp"
#include "ThreadPool.hpp"

class Server {
  public:
    Server();
    ~Server();
    void createInstance();

  protected:
  private:
    asio::io_service _io_service;
    ThreadPool _threadPool;
    UDPServer _udpServer;
};

#endif /* !HEADER_SERVER */
