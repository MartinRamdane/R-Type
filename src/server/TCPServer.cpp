/*
** EPITECH PROJECT, 2023
** TCPServer.cpp
** File description:
** TCPServer
*/

#include "TCPServer.hpp"

TCPServer::TCPServer(boost::asio::io_context &io_context, int port) : io_context_(io_context), _acceptor(io_context, tcp::endpoint(tcp::v4(), 13))
{
  startAccept();
}

TCPServer::~TCPServer()
{
}

void TCPServer::startAccept()
{
  TCPConnection::pointer new_connection = TCPConnection::create(io_context_);

  _acceptor.async_accept(new_connection->socket(), boost::bind(&TCPServer::handleAccept, this, new_connection, boost::asio::placeholders::error));
}

void TCPServer::handleAccept(TCPConnection::pointer new_connection, const boost::system::error_code &error)
{
  if (!error)
  {
    std::cout << "Client is connected" << std::endl;
    new_connection->start();
    startAccept();
  } else {
    std::cout << "Error: " << error.message() << std::endl;
  }
}