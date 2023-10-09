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
    /**
     * @brief Construct a new UDPServer::UDPServer object
     *
     * @param io_service service used for async ops
     * @param port port the server needs to listen on
     */
    UDPServer(boost::asio::io_service &io_service, int port);

    /**
     * @brief Destroy the UDPServer::UDPServer object
     *
     */
    ~UDPServer();

    /**
     * @brief Adds client to the vector
     *
     */
    void addClient(Client client);

    /**
     * @brief Check if the client is still connected if so update the client list
     *
     * @param msg messages data
     */
    void checkConnection(UDPMessage &msg);

    /**
     * @brief Removes client from the vector
     *
     */
    void removeClient(Client client);

    /**
     * @brief Adds event to the send queue
     *
     * @param evt event to send
     * @param host client's ip
     * @param port client's port
     */
    void sendEvent(Event evt, const std::string &host, int port);

    /**
     * @brief Sends event to all the clients (adds to the send queue)
     *
     * @param evt event to send
     */
    void sendEventToAllClients(Event evt);

    std::vector<uint8_t> encodeEvent(Event event);
    /**
     * @brief Handles the events received from the client
     *
     * @param evt  event received
     * @param endpoint  client's endpoint
     */
    void handleEvents(Event evt, boost::asio::ip::udp::endpoint endpoint);

    /**
     * @brief Process send queue and send data to the clients
     *
     */
    void processSendQueue();

    /**
     * @brief Process the message received from the client
     *
     * @param msg message received
     */
    void processMessage(UDPMessage &msg);

    /**
     * @brief Send data to the client asynchronously
     *
     * @param data data to send
     * @param endpoint client's endpoint
     */
    void sendAsync(std::vector<uint8_t> data, boost::asio::ip::udp::endpoint endpoint);

    /**
     * @brief A client want to join the UDP Server
     *
     * @param client the class of client
     */
    void userJoined(Client client);

    void setInstance(Instance *instance) { _instanceRef = instance; }
    ThreadSafeQueue<UDPMessage> &incoming() { return _queue; }
    void handleEngineEvents(std::string request);
    void handleMessages(size_t maxMessages = -1, bool bWait = false);
    int getNbPlayers() const { return _nbPlayers; }

private:
    /**
     * @brief Start receiving data from the client
     *
     */
    void startReceive();

    /**
     * @brief Handle received messages, it adds the message to the queue and restarts the receive
     *
     * @param error
     * @param bytes_recvd
     */
    void handler(const std::error_code &error, std::size_t bytes_recvd);

    /**
     * @brief Send a ping to all the clients every 2 seconds
     *
     */
    void sendPingToClient();

    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remote_endpoint_;
    std::vector<Client> clients_;
    std::thread ping_thread_;
    std::vector<Client> _clients;
    int _nbPlayers;
    Mutex mutex_;
    Instance *_instanceRef;
    ThreadSafeQueue<UDPMessage> _queue;
    ThreadSafeQueue<UDPMessage> _toSendQueue;
    std::vector<uint8_t> recv_buffer_ = std::vector<uint8_t>(1024);
    std::vector<uint8_t> _tempMsg = {};
    bool bWritingMessage;
};
