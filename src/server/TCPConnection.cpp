/*
** EPITECH PROJECT, 2023
** TCPConnection.cpp
** File description:
** TCPConnection
*/

#include "TCPConnection.hpp"

TCPConnection::TCPConnection(asio::io_service &io_service) : _socket(io_service)
{
}

TCPConnection::~TCPConnection()
{
}

void TCPConnection::start()
{
  _message = "Bienvenue sur le serveur!";

  asio::async_write(_socket, asio::buffer(m_message), bind(&TCPConnection::handleWrite, shared_from_this(), asio::placeholders::error));
}

void TCPConnection::handleWrite(const system::error_code &error)
{
  if (!error)
  {
    std::cout << "Error: " << error.message() << std::endl;
  }
}