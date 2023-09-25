/*
** EPITECH PROJECT, 2023
** TCPConnection.hpp
** File description:
** TCPConnection
*/

#ifndef HEADER_TCPCONNECTION
#define HEADER_TCPCONNECTION
#include <iostream>
#include <boost/system/error_code.hpp>
#include <asio.hpp>

using asio::ip::tcp;

class TCPConnection : public std::enable_shared_from_this<TCPConnection>
{
public:
  typedef std::shared_ptr<TCPConnection> pointer;

  static pointer create(asio::io_service &ios)
  {
    return pointer(new TCPConnection(ios));
  }

  tcp::socket &socket()
  {
    return _socket;
  }

  void start();

private:
  TCPConnection(asio::io_service &io_service);
  void handleWrite(const boost::system::error_code &error);
  tcp::socket _socket;
  std::string _message;
};

#endif /* !HEADER_TCPCONNECTION */
