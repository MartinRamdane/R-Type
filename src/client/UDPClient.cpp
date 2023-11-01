/*
** EPITECH PROJECT, 2023
** UDPClient.cpp
** File description:
** UDPClient
*/

#include "UDPClient.hpp"
#include "Game.hpp"

std::string actionToString(ACTION action) {
    switch (action) {
        case ACTION::OK:
            return "OK";
        case ACTION::KO:
            return "KO";
        case ACTION::CONNECT:
            return "CONNECT";
        case ACTION::CREATE:
            return "CREATE";
        case ACTION::LIST:
            return "LIST";
        case ACTION::JOIN:
            return "JOIN";
        case ACTION::JOINED:
            return "JOINED";
        case ACTION::READY:
            return "READY";
        case ACTION::START:
            return "START";
        case ACTION::LEFT:
            return "LEFT";
        case ACTION::RIGHT:
            return "RIGHT";
        case ACTION::UP:
            return "UP";
        case ACTION::DOWN:
            return "DOWN";
        case ACTION::SPACE:
            return "SPACE";
        case ACTION::QUIT:
            return "QUIT";
        case ACTION::PING:
            return "PING";
        case ACTION::PONG:
            return "PONG";
        case ACTION::SPRITE:
            return "SPRITE";
        case ACTION::UNKNOWN:
            return "UNKNOWN";
        case ACTION::KEY_S:
            return "KEY_S";
        case ACTION::TEXT:
            return "TEXT";
        case ACTION::DEAD:
            return "DEAD";
        case ACTION::FLIP:
            return "FLIP";
        case ACTION::RESET:
            return "RESET";
        case ACTION::KEY_L:
            return "KEY_L";
        case ACTION::KEY_C:
            return "KEY_C";
        case ACTION::CHECK:
            return "CHECK";
        case ACTION::SOUND:
            return "SOUND";
    }
    return "";
}

UDPClient::UDPClient() : io_context_(), socket_(io_context_) {
    socket_.open(boost::asio::ip::udp::v4());
    _host = "";
    _port = 0;
}

UDPClient::~UDPClient() {
    io_context_.stop();
    _thread.join();
    _queue.clear();
    _eventQueue.clear();
    _outQueue.clear();
    socket_.close();
}

void UDPClient::connect_to(const std::string& host, int port) {
    remote_endpoint_ =
        boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(host), port);
    sendEvent({ACTION::JOIN, "ok"});
    _port = port;
    _host = host;
    start_receive();
    _thread = std::thread([this]() { io_context_.run(); });
}

void UDPClient::start_receive() {
    try {
        socket_.async_receive_from(boost::asio::buffer(temp_buffer), sender_endpoint,
                                   [this](const std::error_code, std::size_t) {
                                       _queue.push_back(temp_buffer);
                                       start_receive();
                                   });
    } catch (const std::exception& e) {
        std::cerr << "Error starting receive: " << e.what() << std::endl;
    }
}

void UDPClient::HandleMessage(std::vector<uint8_t>& msg) {
    EventHandler evt;
    Event event = evt.decodeMessage(msg);
    _eventQueue.push_back(event);
}

void UDPClient::sendEvent(Event evt) {
    std::vector<uint8_t> data = encodeEvent(evt);
    SendAsync(data, remote_endpoint_);
}

std::vector<uint8_t> UDPClient::encodeEvent(Event event) {
    EventHandler evt;
    evt.addEvent(event.ACTION_NAME, event.body);
    return evt.encodeMessage();
}

void UDPClient::SendAsync(std::vector<uint8_t> data, boost::asio::ip::udp::endpoint endpoint) {
    boost::asio::post(socket_.get_executor(), [this, data, endpoint]() {
        bool bWritingMessage = !_outQueue.empty();
        _outQueue.push_back({data, endpoint});
        if (!bWritingMessage) {
            processSendQueue();
        }
    });
}

void UDPClient::processSendQueue() {
    socket_.async_send_to(boost::asio::buffer(_outQueue.front().data), _outQueue.front().endpoint,
                          [this](const std::error_code& error, std::size_t) {
                              if (!error) {
                                  _outQueue.pop_front();
                                  if (!_outQueue.empty())
                                      processSendQueue();
                              } else {
                                  std::cout << "[ERROR] sending data" << std::endl;
                              }
                          });
}

void UDPClient::addUnknownEntity(int id) {
    std::vector<int> unknownEntitiesCopy = unknownEntities;
    if (std::find(unknownEntitiesCopy.begin(), unknownEntitiesCopy.end(), id) ==
        unknownEntitiesCopy.end()) {
        std::cout << "Adding unknown entity " << id << std::endl;
        unknownEntities.push_back(id);
    }
}

void UDPClient::sendUnknownEntities() {
    if (_lastSentUnknownEntities.time_since_epoch().count() == 0) {
        _lastSentUnknownEntities = std::chrono::high_resolution_clock::now();
    }
    if (std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - _lastSentUnknownEntities)
            .count() < 1000) {
        return;
    }
    for (auto it = unknownEntities.begin(); it != unknownEntities.end(); ++it) {
        std::cout << "sent unknown entity " << *it << std::endl;
        sendEvent({ACTION::UNKNOWN, std::to_string(*it)});
    }
    unknownEntities.clear();
}