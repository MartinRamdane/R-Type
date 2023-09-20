/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** UDPClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include <iostream>
#include <asio.hpp>

class UDPClient {
public:
    UDPClient() : io_context_(), socket_(io_context_) {
        socket_.open(asio::ip::udp::v4());
    }


    ~UDPClient() {
        socket_.close();
    }

    void send_data(const std::string& data, const std::string& host, int port) {
        asio::ip::udp::endpoint remote_endpoint(asio::ip::address::from_string(host), port);
        socket_.send_to(asio::buffer(data), remote_endpoint);
    }
    void connect_to(const std::string& host, int port) {
        asio::ip::udp::resolver resolver(io_context_);
        asio::ip::udp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));
        asio::connect(socket_, endpoints);
        send_data("Hello", host, port);
    }

    std::string receive_data() {
        std::array<char, 1024> recv_buffer;
        asio::ip::udp::endpoint sender_endpoint;
        std::size_t bytes_received = socket_.receive_from(asio::buffer(recv_buffer), sender_endpoint);
        if (check_ping(std::string(recv_buffer.data(), bytes_received))) {
            send_data("Pong", sender_endpoint.address().to_string(), sender_endpoint.port());
        }
        return std::string(recv_buffer.data(), bytes_received);
    }
    bool check_ping(const std::string& data) {
        std::cout << "Received:3 " << data << std::endl;
        return data == "Ping";
    }

private:
    asio::io_context io_context_;
    asio::ip::udp::socket socket_;
};

#endif /* !UDPCLIENT_HPP_ */
