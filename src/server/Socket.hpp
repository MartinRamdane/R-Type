#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <asio.hpp>
#include <iostream>
#include <string>

class Socket {
public:
    Socket(asio::io_context& io_context) : socket_(io_context), io_context_(io_context) {}
    ~Socket();

    void connect_to(const std::string& host, int port);
    void Bind(int port);
    // void AcceptClient();
    void receive_data() {
        socket_.async_receive_from(asio::buffer(recv_buffer_), remote_endpoint_,
            [this](const std::error_code& error, std::size_t bytes_received) {
                std::cout << "Received: " << std::string(recv_buffer_.data(), bytes_received) << std::endl;
                if (!error) {
                    receive_data();
                } else {
                    std::cerr << "Error receiving data: " << error.message() << std::endl;
                }
            }
        );
    }
    std::size_t receive_data_blocking() {
        std::size_t bytes_received = socket_.receive_from(asio::buffer(recv_buffer_), sender_endpoint_);
        std::cout << "Received: " << std::string(recv_buffer_.data(), bytes_received) << std::endl;
        return bytes_received;
    }
    void send_data(const std::string& data) {
        try {
        std::size_t bytes_sent = socket_.send_to(asio::buffer(data), sender_endpoint_);
        // Handle the number of bytes sent if needed.
        } catch (std::exception& e) {
            std::cerr << "Error sending data: " << e.what() << std::endl;
        }
    }

private:
    asio::ip::udp::socket socket_;
    asio::io_context& io_context_;
    std::array<char, 1024> recv_buffer_;
    asio::ip::udp::endpoint remote_endpoint_;
    asio::ip::udp::endpoint sender_endpoint_;
};

#endif /* !SOCKET_HPP_ */
