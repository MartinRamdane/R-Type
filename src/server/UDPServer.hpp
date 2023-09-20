/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** UDPServer
*/

#pragma once
#include <asio.hpp>
#include <iostream>
#include <utility>
#include <chrono>
#include <thread>
#include "Mutex.hpp"
class ServerClass;
struct Client {
    asio::ip::udp::endpoint client;
    std::chrono::system_clock::time_point timestamp;
};

class UDPServer {
    public:
        UDPServer(asio::io_service& io_service, int port);
        ~UDPServer();
        void setServer(ServerClass *server) { _server = server;}
    private:
        void start_receive();
        void handler(const std::error_code& error, std::size_t bytes_recvd);
        void send_ping_to_clients();
        asio::ip::udp::socket socket_;
        asio::ip::udp::endpoint remote_endpoint_;
        std::vector<Client> clients_;
        std::array<char, 1024> recv_buffer_;
        std::thread ping_thread_;
        Mutex mutex_;
        ServerClass *_server;
};
