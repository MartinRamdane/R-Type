/*
** EPITECH PROJECT, 2023
** TCPServer.cpp
** File description:
** TCPServer
*/

#include "TCPServer.hpp"

TCPServer::TCPServer(boost::asio::io_context &io_context, int port) : io_context_(io_context), _acceptor(io_context, tcp::endpoint(tcp::v4(), port))
{
  startAccept();
}

TCPServer::~TCPServer()
{
}

void TCPServer::startAccept()
{
  TCPServerConnection::pointer new_connection = TCPServerConnection::create(io_context_);

  _acceptor.async_accept(
    new_connection->socket(),
    [this, new_connection](const boost::system::error_code &error) {
      handleAccept(new_connection, error, _server);
    });
}

void TCPServer::handleAccept(TCPServerConnection::pointer new_connection, const boost::system::error_code &error, ServerClass *server)
{
  if (!error)
  {
    std::cout << "Client is connected" << std::endl;
    new_connection->start(server);
    startAccept();
  } else {
    std::cout << "[ERROR TCP Server]: " << error.message() << std::endl;
  }
}