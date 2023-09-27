/*
** EPITECH PROJECT, 2023
** TCPClient.cpp
** File description:
** TCPClient
*/

#include "TCPClient.hpp"
#include "Game.hpp"

TCPClient::TCPClient(std::string host, int port, Game *game, boost::asio::io_service &io_service) : _game(game), _io_service(io_service)
{
    tcp::endpoint endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host), port);
    _endpoint = endpoint;
}

void TCPClient::connect()
{
    TCPClientConnection::pointer new_connection = TCPClientConnection::create(_io_service);
    _connection = new_connection.get();
    tcp::socket &socket = new_connection->socket();
    socket.async_connect(_endpoint, boost::bind(&TCPClient::handleConnect, this, new_connection, boost::asio::placeholders::error));
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

void TCPClient::send(std::vector<uint8_t> to_send) {
    _connection->addToSend(to_send);
    std::cout << "edited vector" << std::endl;
    _connection->write();
}