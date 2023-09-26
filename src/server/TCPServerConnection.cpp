/*
** EPITECH PROJECT, 2023
** TCPConnection.cpp
** File description:
** TCPConnection
*/

#include "TCPServerConnection.hpp"
#include "Server.hpp"

TCPServerConnection::TCPServerConnection(boost::asio::io_service &io_service) : _socket(io_service)
{
}

void TCPServerConnection::start(ServerClass *server)
{
    _message = "Bienvenue sur le serveur!";
    _server = server;
    read();
}

void TCPServerConnection::handleWrite(const boost::system::error_code &error)
{
    if (error)
    {
        std::cout << "Error: " << error.message() << std::endl;
        // write here
    }
}

void TCPServerConnection::read()
{
  auto self = shared_from_this();

  _socket.async_read_some(boost::asio::buffer(buffer, 1024), [this, self](const boost::system::error_code& error, std::size_t length) {
        if (!error) {
            std::cout << "Received: " << length << std::endl;
            if (length == 0)
                write();
            EventHandler evt;
            Event event = evt.decodeMessage(buffer);
            if (event.ACTION_NAME == ACTION::CREATE) {
                InstanceInfos result = _server->createInstance();
                std::cout << "created instance !" << std::endl;
                std::string response = std::to_string(result.port) + " " + std::to_string(result.id);
                EventHandler event(ACTION::OK, response.length(), response);
                std::vector<uint8_t> eventData = event.encodeMessage();
                to_send = eventData;
            }
            write();
            // Echo the data back to the client
        }
    }
    );
}

void TCPServerConnection::write()
{
    if (to_send.size() == 0)
        read();
    auto self = shared_from_this();
    boost::asio::async_write(_socket, boost::asio::buffer(to_send), [this, self](const boost::system::error_code& error, std::size_t length) {
        to_send.clear();
        std::cout << "write" << std::endl;
    });
    read();
}