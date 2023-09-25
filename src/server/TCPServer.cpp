/*
** EPITECH PROJECT, 2023
** TCPServer.cpp
** File description:
** TCPServer
*/

#include "TCPServer.hpp"

TCPServer::TCPServer(asio::io_service &io_service, int port) : _acceptor(io_service, tcp::endpoint(tcp::v4(), port)
{
  startAccept();
}

TCPServer::~TCPServer()
{
}

void TCPServer::startAccept()
{
  TCPConnection::pointer new_connection = TCPConnection::create(_acceptor.io_service());

  _acceptor.async_accept(new_connection->socket(), bind(&TCPServer::handleAccept, this, new_connection, asio::placeholders::error));
}

void TCPServer::handleAccept(TCPConnection &new_connection, const system::error_code &error)
{
  if (!error)
  {
    std::cout << "Client is connected" << std::endl;
    new_connection.start();
    start_accept();
  }
}