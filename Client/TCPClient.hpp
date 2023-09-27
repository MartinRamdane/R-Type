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
        TCPClient(std::string host, int port, Game *game, boost::asio::io_service &io_service);
        void connect();
        void send(std::vector<uint8_t> to_send);

    private:
        void handleConnect(TCPClientConnection::pointer new_connection, const boost::system::error_code &error);
        boost::asio::io_service &_io_service;
        tcp::endpoint _endpoint;
        Game *_game;
        TCPClientConnection *_connection;
};

#endif /* !HEADER_TCPCLIENT */