/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** UDPClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include <boost/asio.hpp>
#include <iostream>
#include "../global/EventHandler.hpp"
#include "ThreadSafeQueue.hpp"

class Game;
struct UDPMessage {
    std::vector<uint8_t> data;
    boost::asio::ip::udp::endpoint endpoint;
};
class UDPClient {
   public:
    UDPClient();
    ~UDPClient();
    void connect_to(const std::string& host, int port);
    void start_receive();
    void HandleMessage(std::vector<uint8_t>& msg);
    void sendEvent(Event evt);
    std::vector<uint8_t> encodeEvent(Event event);
    std::string getHost() const { return _host; }
    int getPort() const { return _port; }
    void SendAsync(std::vector<uint8_t> data, boost::asio::ip::udp::endpoint endpoint);
    ThreadSafeQueue<std::vector<uint8_t>>& Incoming() { return _queue; }
    ThreadSafeQueue<Event>& getEventQueue() { return _eventQueue; }
    void processSendQueue();
    void addUnknownEntity(int id);
    void sendUnknownEntities();

   private:
    boost::asio::io_context io_context_;
    boost::asio::ip::udp::socket socket_;
    std::string _host;
    ThreadSafeQueue<std::vector<uint8_t>> _queue;
    ThreadSafeQueue<UDPMessage> _outQueue;
    ThreadSafeQueue<Event> _eventQueue;
    std::vector<int> unknownEntities = std::vector<int>();
    std::vector<uint8_t> temp_buffer = std::vector<uint8_t>(1024);
    boost::asio::ip::udp::endpoint remote_endpoint_;
    boost::asio::ip::udp::endpoint sender_endpoint;
    int _port;
    std::chrono::high_resolution_clock::time_point _lastSentUnknownEntities;
    std::thread _thread;
};

#endif /* !UDPCLIENT_HPP_ */