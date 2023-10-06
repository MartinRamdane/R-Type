/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** UDPServer
*/

#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <utility>
#include <chrono>
#include <thread>
#include "Mutex.hpp"
#include "../global/EventHandler.hpp"
#include "ThreadSafeQueue.hpp"

class Instance;

struct Client
{
    boost::asio::ip::udp::endpoint client;
    std::chrono::system_clock::time_point timestamp;
};

struct UDPMessage
{
    std::vector<uint8_t> data;
    boost::asio::ip::udp::endpoint endpoint;
};

class UDPServer
{
public:
    UDPServer(boost::asio::io_service &io_service, int port);
    ~UDPServer();
    void setInstance(Instance *instance) { _instanceRef = instance; }
    void addClient(Client client);
    void removeClient(Client client);
    int getNbPlayers() const { return _nbPlayers; }
    void sendEvent(Event evt, const std::string &host, int port);
    std::vector<uint8_t> encodeEvent(Event event);
    void handleEvents(Event evt, boost::asio::ip::udp::endpoint endpoint);
    void sendEventToAllClients(Event evt);
    void handleEngineEvents(std::string request);
    void processSendQueue();
    void SendAsync(std::vector<uint8_t> data, boost::asio::ip::udp::endpoint endpoint);

private:
    void start_receive();
    void handler(const std::error_code &error, std::size_t bytes_recvd);
    void send_ping_to_clients();
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remote_endpoint_;
    std::vector<Client> clients_;
    std::thread ping_thread_;
    std::vector<Client> _clients;
    int _nbPlayers;
    Mutex mutex_;
    Instance *_instanceRef;
    ThreadSafeQueue<std::vector<uint8_t>> _queue;
    ThreadSafeQueue<UDPMessage> _toSendQueue;
    std::vector<uint8_t> recv_buffer_ = std::vector<uint8_t>(1024);
    std::vector<uint8_t> _tempMsg = {};
    bool bWritingMessage;
};
