/*
** EPITECH PROJECT, 2023
** TCPConnection.cpp
** File description:
** TCPConnection
*/

#include "TCPServerConnection.hpp"

TCPServerConnection::TCPServerConnection(boost::asio::io_service &io_service) : _socket(io_service)
{
}

void TCPServerConnection::start()
{
  _message = "Bienvenue sur le serveur!";
  read();
}

void TCPServerConnection::handleWrite(const boost::system::error_code &error)
{
  if (error)
  {
    std::cout << "Error: " << error.message() << std::endl;
    // write here
  }
}

void TCPServerConnection::handleRead(const boost::system::error_code &error)
{
  if (!error)
  {
    std::cout << "Message: " << _message << std::endl;
    boost::asio::async_write(_socket, boost::asio::buffer(_message), boost::bind(&TCPServerConnection::handleWrite, shared_from_this(), boost::asio::placeholders::error));
  } else {
    std::cout << "Error: " << error.message() << std::endl;
  }
}

void TCPServerConnection::read()
{
  auto self = shared_from_this();
  buffer.clear();
  _socket.async_read_some(boost::asio::buffer(buffer, 1024), [this, self](const boost::system::error_code& error, std::size_t length) {
        if (!error) {
            std::cout << "Received: " << length << std::endl;
            EventHandler evt;
            evt.decodeMessage(buffer);
            std::string response = "Got message";
            boost::asio::async_write(_socket, boost::asio::buffer(response), boost::bind(&TCPServerConnection::handleWrite, shared_from_this(), boost::asio::placeholders::error));
            read();
        }
    }
    );
}