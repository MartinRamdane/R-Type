/*
** EPITECH PROJECT, 2023
** TCPClient.hpp
** File description:
** TCPClient
*/

#ifndef HEADER_TCPCLIENT
#define HEADER_TCPCLIENT
#include "TCPConnection.hpp"

class TCPClient
{
public:
  TCPClient(boost::asio::io_service &io_service, tcp::endpoint &endpoint);

private:
  void connect(tcp::endpoint &endpoint);
  void handleConnect(TCPConnection::pointer new_connection, const boost::system::error_code &error);
  boost::asio::io_service &_io_service;
};

#endif /* !HEADER_TCPCLIENT */
