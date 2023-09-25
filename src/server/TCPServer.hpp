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
    TCPServer(asio::io_service &io_service, int port);
    ~TCPServer();

  protected:
  private:
    void startAccept();
    void handleAccept(TCPConnection &new_connection, const system::error_code &error)
    tcp::acceptor _acceptor;
};

#endif /* !HEADER_TCPServer */
