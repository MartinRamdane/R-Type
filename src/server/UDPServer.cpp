/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** UDPServer
*/

#include "UDPServer.hpp"

UDPServer::UDPServer(asio::io_service &io_service, int port) : socket_(io_service, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
{
    try
    {
        std::cout << "Server listening on port " << port << std::endl;
        start_receive();
        ping_thread_ = std::thread(&UDPServer::send_ping_to_clients, this);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error during server initialization: " << e.what() << std::endl;
    }
}

UDPServer::~UDPServer()
{
}

void UDPServer::start_receive()
{
    try
    {
        socket_.async_receive_from(
            asio::buffer(recv_buffer_), remote_endpoint_, [this](const std::error_code &error, std::size_t bytes_recvd)
            { handler(error, bytes_recvd); });
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error starting receive: " << e.what() << std::endl;
    }
}

void UDPServer::handler(const std::error_code &error, std::size_t bytes_recvd)
{
    if (!error)
    {
        mutex_.lock();
        Client client{remote_endpoint_, std::chrono::system_clock::now()};
        if (std::find_if(clients_.begin(), clients_.end(), [&client](const Client &c)
                         { return c.client.address() == client.client.address() && c.client.port() == client.client.port(); }) == clients_.end())
        {
            clients_.push_back(client);
            std::cout << "New client connected: " << client.client.address().to_string() << ":" << client.client.port() << std::endl;
            std::cout << "Connected at : " << std::chrono::system_clock::to_time_t(client.timestamp) << std::endl;
            std::cout << "vector size : " << clients_.size() << std::endl;
        }
        if (std::string(recv_buffer_.data(), bytes_recvd) == "Pong")
        {
            auto it = std::find_if(clients_.begin(), clients_.end(), [&client](const Client &c)
                                   { return c.client.address() == client.client.address() && c.client.port() == client.client.port(); });
            if (it != clients_.end())
            {
                it->timestamp = std::chrono::system_clock::now();
                std::cout << "updated timestamp for client " << it->client.address().to_string() << ":" << it->client.port() << std::endl;
            }
        }
        mutex_.unlock();
        start_receive();
    }
    else if (error == asio::error::eof)
    {
        // Connection was closed by the remote host (client left)
        // std::cout << "Client disconnected." << std::endl;
        mutex_.lock();
        auto it = std::find_if(clients_.begin(), clients_.end(), [this](const Client &c)
                               { return c.client.address() == remote_endpoint_.address() && c.client.port() == remote_endpoint_.port(); });
        if (it != clients_.end())
        {
            std::cout << "Client " << it->client.address().to_string() << ":" << it->client.port() << " disconnected." << std::endl;
            clients_.erase(it); // Erase the found element
        }
        mutex_.unlock();
        start_receive();
    }
    else
    {
        mutex_.lock();
        auto it = std::find_if(clients_.begin(), clients_.end(), [this](const Client &c)
                               { return c.client.address() == remote_endpoint_.address() && c.client.port() == remote_endpoint_.port(); });
        if (it != clients_.end())
        {
            std::cout << "Client " << it->client.address().to_string() << ":" << it->client.port() << " disconnected." << std::endl;
            clients_.erase(it); // Erase the found element
        }
        mutex_.unlock();
        start_receive();
    }
}

void UDPServer::send_ping_to_clients()
{
    while (true)
    {
        mutex_.lock();
        for (auto it = clients_.begin(); it != clients_.end();)
        {
            std::cout << "Client " << it->client.address().to_string() << ":" << it->client.port() << " last ping: " << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - it->timestamp).count() << std::endl;
            if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - it->timestamp).count() > 5)
            {
                std::cout << "Client " << it->client.address().to_string() << ":" << it->client.port() << " timed out." << std::endl;
                it = clients_.erase(it);
            }
            else
            {
                socket_.send_to(asio::buffer("Ping", 4), it->client);
                ++it;
            }
        }
        mutex_.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}