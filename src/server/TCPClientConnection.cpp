/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** TCPClientConnection
*/

#include "TCPClientConnection.hpp"

TCPClientConnection::TCPClientConnection(boost::asio::io_service &io_service) : _socket(io_service)
{

}

void TCPClientConnection::start()
{
    while (1) {
        EventHandler event(ACTION::OK, 3, "cvo" );
        std::vector<uint8_t> eventData = event.encodeMessage();
        boost::asio::async_write(_socket, boost::asio::buffer(eventData), boost::bind(&TCPClientConnection::handleWrite, shared_from_this(), boost::asio::placeholders::error));
        boost::asio::async_read(_socket, boost::asio::buffer(_message), boost::bind(&TCPClientConnection::handleRead, shared_from_this(), boost::asio::placeholders::error));
    }
}

void TCPClientConnection::handleWrite(const boost::system::error_code &error)
{
    if (error)
    {
        std::cout << "Error: " << error.message() << std::endl;
        // write here
    }
}

void TCPClientConnection::handleRead(const boost::system::error_code &error)
{
    if (!error)
    {
        std::cout << "Message: " << _message << std::endl;
        boost::asio::async_write(_socket, boost::asio::buffer(_message), boost::bind(&TCPClientConnection::handleWrite, shared_from_this(), boost::asio::placeholders::error));
    } else {
        std::cout << "Error: " << error.message() << std::endl;
    }
}