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
#include "EventHandler.hpp"

using boost::asio::ip::tcp;
using namespace boost::asio;

class TCPServerConnection : public boost::enable_shared_from_this<TCPServerConnection>
{
public:
  typedef boost::shared_ptr<TCPServerConnection> pointer;

  static pointer create(boost::asio::io_service &ios)
  {
    return pointer(new TCPServerConnection(ios));
  }

  tcp::socket &socket()
  {
    return _socket;
  }

  void start();

private:
  TCPServerConnection(boost::asio::io_service &io_service);
  void handleWrite(const boost::system::error_code &error);
  void handleRead(const boost::system::error_code &error);
  void read();
  tcp::socket _socket;
  std::string _message;
  enum { max_length = 1024 };
  std::vector<uint8_t> buffer = std::vector<uint8_t>(max_length);
};

#endif /* !HEADER_TCPCONNECTION */
