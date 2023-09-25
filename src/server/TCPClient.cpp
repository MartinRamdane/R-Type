/*
** EPITECH PROJECT, 2023
** TCPClient.cpp
** File description:
** TCPClient
*/

#include "TCPClient.hpp"

TCPClient::TCPClient(asio::io_service &io_service, tcp::endpoint &endpoint) : _io_service(io_service)
{
  connect(endpoint);
}

TCPClient::~TCPClient()
{
}

void TCPClient::connect(tcp::endpoint &endpoint)
{
  TCPConnection::pointer new_connection = TCPConnection::create(m_io_service);
  tcp::socket &socket = new_connection->socket();
  socket.async_connect(endpoint, bind(&TCPClient::handleConnect, this, new_connection, asio::placeholders::error));
}

void TCPClient::handle_connect(TCPConnection::pointer new_connection, const system::error_code &error)
{
  if (!error)
  {
    new_connection->read();
  }
}