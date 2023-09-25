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
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;

class TCPConnection : public boost::enable_shared_from_this<TCPConnection>
{
public:
  typedef boost::shared_ptr<TCPConnection> pointer;

  static pointer create(boost::asio::io_service &ios)
  {
    return pointer(new TCPConnection(ios));
  }

  tcp::socket &socket()
  {
    return _socket;
  }

  void start();

private:
  TCPConnection(boost::asio::io_service &io_service);
  void handleWrite(const boost::system::error_code &error);
  tcp::socket _socket;
  std::string _message;
};

#endif /* !HEADER_TCPCONNECTION */
