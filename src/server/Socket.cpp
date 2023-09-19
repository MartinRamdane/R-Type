#include "Socket.hpp"

Socket::~Socket() {
    socket_.close();
}

void Socket::connect_to(const std::string& host, int port) {
    // asio::ip::udp::resolver resolver(io_context_);
    // asio::ip::udp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));
    // asio::connect(socket_, endpoints);
}

void Socket::Bind(int port) {
    try {
        asio::ip::udp::endpoint endpoint(asio::ip::udp::v4(), port);
        socket_.open(endpoint.protocol());
        socket_.bind(endpoint);
    } catch (const std::exception& e) {
        std::cerr << "Error binding UDP socket: " << e.what() << std::endl;
        // Handle the error as needed.
    }
}