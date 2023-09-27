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
    std::cout << "Enter message: "; // remove this for prod, we should get the _message from arguments
    std::getline(std::cin, _message);
    std::string command;
    int bodySize = 0;
    std::string bodyMessage;
    // PUT THIS IN A METHOD
    std::stringstream ss(_message);
    std::string token;
    std::vector<std::string> tokens;
    while (getline(ss, token, ','))
    {
        tokens.push_back(token);
    }

    for (auto &t : tokens)
    {
        t.erase(0, t.find_first_not_of(" \t"));
        t.erase(t.find_last_not_of(" \t") + 1);
    }

    if (tokens.size() == 3)
    {
        command = tokens[0];
        bodySize = std::stoi(tokens[1]);
        bodyMessage = tokens[2];
    }
    else
    {
        std::cout << "[ERROR]: Bad request" << std::endl; // TODO: exception
        read();
    }
    ACTION action = stringToAction(command);
    EventHandler event(ACTION::KO, 11, "Bad request");
    if (action != ACTION::UNKNOWN)
    {
        event = EventHandler(action, bodySize, bodyMessage);
    }
    else
    {
        std::cout << "[ERROR]: Bad request" << std::endl; // TODO: exception
        read();
    }
    std::vector<uint8_t> eventData = event.encodeMessage();
    to_send = eventData;
    if (to_send.size() == 0)
        read();
    boost::asio::async_write(_socket, boost::asio::buffer(to_send), [this, self](const boost::system::error_code &error, std::size_t length)
                             { std::cout << "write" << std::endl; });
    read();
}