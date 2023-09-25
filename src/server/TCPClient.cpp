/*
** EPITECH PROJECT, 2023
** TCPClient.cpp
** File description:
** TCPClient
*/

#include "TCPClient.hpp"

TCPClient::TCPClient(boost::asio::io_service &io_service, tcp::endpoint &endpoint) : _io_service(io_service)
{
  connect(endpoint);
}

void TCPClient::connect(tcp::endpoint &endpoint)
{
  TCPConnection::pointer new_connection = TCPConnection::create(_io_service);
  tcp::socket &socket = new_connection->socket();
  socket.async_connect(endpoint, boost::bind(&TCPClient::handleConnect, this, new_connection, boost::asio::placeholders::error));
}

void TCPClient::handleConnect(TCPConnection::pointer new_connection, const boost::system::error_code &error)
{
  if (!error)
  {
    new_connection->start();
  } else {
    std::cout << "Error: " << error.message() << std::endl;
  }
}