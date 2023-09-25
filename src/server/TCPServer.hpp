/*
** EPITECH PROJECT, 2023
** TCPServer.hpp
** File description:
** TCPServer
*/

#ifndef HEADER_TCPServer
#define HEADER_TCPServer
#include "TCPConnection.hpp"

class TCPServer {
  public:
    TCPServer(boost::asio::io_context &io_context, int port);
    ~TCPServer();

  protected:
  private:
    void startAccept();
    void handleAccept(TCPConnection::pointer new_connection, const boost::system::error_code &error);
    tcp::acceptor _acceptor;
    boost::asio::io_context &io_context_;
};

#endif /* !HEADER_TCPServer */
