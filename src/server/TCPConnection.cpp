/*
** EPITECH PROJECT, 2023
** TCPConnection.cpp
** File description:
** TCPConnection
*/

#include "TCPConnection.hpp"

TCPConnection::TCPConnection(boost::asio::io_service &io_service) : _socket(io_service)
{
}

void TCPConnection::start()
{
  _message = "Bienvenue sur le serveur!";
  boost::asio::async_write(_socket, boost::asio::buffer(_message), boost::bind(&TCPConnection::handleWrite, shared_from_this(), boost::asio::placeholders::error));
}

void TCPConnection::handleWrite(const boost::system::error_code &error)
{
  if (error)
  {
    std::cout << "Error: " << error.message() << std::endl;
    // write here
  }
}