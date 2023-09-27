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

void TCPServerConnection::createInstance()
{
    InstanceInfos result = _server->createInstance();
    std::cout << "[DEBUG]: Instance " << result.id << " has been created." << std::endl;
    std::string response = std::to_string(result.port) + " " + std::to_string(result.id);
    EventHandler event(ACTION::OK, response.length(), response);
    std::vector<uint8_t> eventData = event.encodeMessage();
    to_send = eventData;
}

void TCPServerConnection::joinInstance(Event event)
{
    int targetInstanceId = std::atoi(event.body.c_str());
    std::cout << "[DEBUG]: Instance " << targetInstanceId << " try to be joined." << std::endl;
    int targetInstancePort = _server->getPortInstance(targetInstanceId);
    int instanceNbPlayers = _server->getNbPlayersInstance(targetInstanceId);
    std::cout << "[DEBUG]: Instance nb players " << instanceNbPlayers << std::endl;
    if (instanceNbPlayers >= 4)
    {
        std::cout << "CAN'T ADD AN ANOTHER PLAYER BECAUSE ITS FULL" << std::endl;
        EventHandler evt(ACTION::KO, 24, "Can't join this instance");
        std::vector<uint8_t> eventData = evt.encodeMessage();
        to_send = eventData;
        return;
    }
    EventHandler evt(ACTION::OK, 4, std::to_string(targetInstancePort));
    std::vector<uint8_t> eventData = evt.encodeMessage();
    to_send = eventData;
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
                createInstance();
            }
            if (event.ACTION_NAME == ACTION::JOIN) {
                joinInstance(event);
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
        std::cout << "write" << std::endl;
        to_send.clear();
        read();
    });
}