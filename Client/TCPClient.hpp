/*
** EPITECH PROJECT, 2023
** TCPClient.hpp
** File description:
** TCPClient
*/

#ifndef HEADER_TCPCLIENT
#define HEADER_TCPCLIENT
#include "TCPClientConnection.hpp"
#include <thread>

class Game;
class TCPClient {
    public:
        TCPClient(std::string host, int port, Game *game);

    private:
        void connect(tcp::endpoint &endpoint);
        void handleConnect(TCPClientConnection::pointer new_connection, const boost::system::error_code &error);
        boost::asio::io_service _io_service;
        Game *_game;
};

#endif /* !HEADER_TCPCLIENT */