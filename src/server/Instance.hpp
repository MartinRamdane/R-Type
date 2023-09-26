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

class Server;

using boost::asio::ip::tcp;

class Instance
{
public:
  Instance(int _id);
  ~Instance(); // destroy the instance if nbPlayers === 0
  int getId() const { return _id; }
  UDPServer &getUDPServer() { return _udpServer; }
  void setServer(Server *server) { _serverRef = server; }
  int getNbPlayers() const { return _udpServer.getNbPlayers(); }

protected:
private:
  boost::asio::io_service _io_service;
  UDPServer _udpServer;
  int _id;
  int _port;
  Server *_serverRef;
  ThreadPool _threadPool;
};

#endif /* !HEADER_INSTANCE */
