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
    write();
}


void TCPClientConnection::read()
{
    auto self = shared_from_this();
    std::cout << "read" << std::endl;
    _socket.async_read_some(boost::asio::buffer(buffer, 1024), [this, self](const boost::system::error_code& error, std::size_t length) {
          if (!error) {
              std::cout << "Received: " << length << std::endl;
              EventHandler evt;
              Event event = evt.decodeMessage(buffer);
              std::cout << "Action: " << event.ACTION_NAME << std::endl;
              write();
          } else {
                std::cout << "Error: " << error.message() << std::endl;
          }
      }
      );
}

void TCPClientConnection::write()
{
    auto self = shared_from_this();
    std::cout << "Enter message: ";
    std::getline(std::cin, _message);
    EventHandler event(ACTION::OK, 3, "cvo" );
    if (_message == "create") {
        event = EventHandler(ACTION::CREATE, 4, "4343" );
    } else {
        event = EventHandler(ACTION::CREATE, 4, "4343" );
    }
    std::vector<uint8_t> eventData = event.encodeMessage();
    to_send = eventData;
    if (to_send.size() == 0)
        read();
    boost::asio::async_write(_socket, boost::asio::buffer(to_send), [this, self](const boost::system::error_code& error, std::size_t length) {
        std::cout << "write" << std::endl;
    });
    read();
}