/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** UDPClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include <iostream>
#include <boost/asio.hpp>
#include "../global/EventHandler.hpp"
#include "ThreadSafeQueue.hpp"
#include "../global/StructsMessages.hpp"

class Game;
struct UDPMessage
{
    std::vector<uint8_t> data;
    boost::asio::ip::udp::endpoint endpoint;
};
class UDPClient
{
public:
    UDPClient();
    ~UDPClient();
    void connect_to(const std::string &host, int port);
    void setGameRef(Game *gameRef);
    void start_receive();
    void HandleMessage(std::vector<uint8_t> &msg);
    void sendEvent(Event evt);
    std::vector<uint8_t> encodeEvent(Event event);
    std::string getHost() const { return _host; }
    int getPort() const { return _port; }
    void handleEvents(Event evt);
    void joinGame(Event evt);
    void updateSprite(Event evt);
    void SendAsync(std::vector<uint8_t> data, boost::asio::ip::udp::endpoint endpoint);
    ThreadSafeQueue<std::vector<uint8_t>> &Incoming() { return _queue; }
    void processSendQueue();
    void flipEntity(Event evt);

private:
    boost::asio::io_context io_context_;
    boost::asio::ip::udp::socket socket_;
    std::string _host;
    ThreadSafeQueue<std::vector<uint8_t>> _queue;
    ThreadSafeQueue<UDPMessage> _outQueue;
    std::vector <uint8_t> temp_buffer = std::vector<uint8_t>(1024);
    boost::asio::ip::udp::endpoint remote_endpoint_;
    boost::asio::ip::udp::endpoint sender_endpoint;
    int _port;
    std::thread _thread;
    Game *_gameRef;
};

#endif /* !UDPCLIENT_HPP_ */