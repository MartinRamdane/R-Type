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
    _socket.async_read_some(boost::asio::buffer(buffer, 1024), [this, self](const boost::system::error_code &error, std::size_t length)
                            {
          if (!error) {
              std::cout << "Received: " << length << std::endl;
              EventHandler evt;
              Event event = evt.decodeMessage(buffer);
              std::cout << "Action: " << event.ACTION_NAME << std::endl;
              write();
          } else {
                std::cout << "Error: " << error.message() << std::endl;
          } });
    std::cout << "fin de read" << std::endl;
}

ACTION TCPClientConnection::stringToAction(std::string action)
{
    std::cout << "action to change: " << action << std::endl;
    if (action == "CREATE")
        return ACTION::CREATE;
    if (action == "JOIN")
        return ACTION::JOIN;
    if (action == "OK")
        return ACTION::OK;
    if (action == "KO")
        return ACTION::KO;
    if (action == "QUIT")
        return ACTION::QUIT;
    return ACTION::UNKNOWN;
}

void TCPClientConnection::write()
{
    auto self = shared_from_this();
    if (to_send.size() == 0 || sending)
        read();
    sending = true;
    boost::asio::async_write(_socket, boost::asio::buffer(to_send), [this, self](const boost::system::error_code &error, std::size_t length)
                             { std::cout << "write" << std::endl; to_send.clear(); read();});
}