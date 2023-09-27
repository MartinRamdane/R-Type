/*
** EPITECH PROJECT, 2023
** TCPClient.cpp
** File description:
** TCPClient
*/

#include "TCPClient.hpp"
#include "Game.hpp"

TCPClient::TCPClient(std::string host, int port, Game *game) : _game(game)
{
    tcp::endpoint endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host), port);
   // connect(endpoint);
}

void TCPClient::connect(tcp::endpoint &endpoint)
{
    TCPClientConnection::pointer new_connection = TCPClientConnection::create(_io_service);
    tcp::socket &socket = new_connection->socket();
    socket.async_connect(endpoint, boost::bind(&TCPClient::handleConnect, this, new_connection, boost::asio::placeholders::error));
    std::thread t(boost::bind(&boost::asio::io_service::run, &_io_service));
}

void TCPClient::handleConnect(TCPClientConnection::pointer new_connection, const boost::system::error_code &error)
{
    std::cout << "handle connect" << std::endl;
    if (!error)
    {
        new_connection->start();
    } else {
        std::cout << "Error: " << error.message() << std::endl;
    }
}