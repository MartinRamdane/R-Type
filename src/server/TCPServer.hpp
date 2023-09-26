/*
** EPITECH PROJECT, 2023
** TCPServer.hpp
** File description:
** TCPServer
*/

#ifndef HEADER_TCPServer
#define HEADER_TCPServer
#include "TCPServerConnection.hpp"

class ServerClass;

class TCPServer {
  public:
    TCPServer(boost::asio::io_context &io_context, int port);
    ~TCPServer();
    void setServer(ServerClass *server) { _server = server; }

  protected:
  private:
    void startAccept();
    void handleAccept(TCPServerConnection::pointer new_connection, const boost::system::error_code &error);
    tcp::acceptor _acceptor;
    boost::asio::io_context &io_context_;
    ServerClass *_server;
};

#endif /* !HEADER_TCPServer */
