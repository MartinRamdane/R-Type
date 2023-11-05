/*
** EPITECH PROJECT, 2023
** TCPClient.hpp
** File description:
** TCPClient
*/

#ifndef HEADER_TCPCLIENT
#define HEADER_TCPCLIENT
#include "TCPServerConnection.hpp"

template <typename T>
class TCPClient {
   public:
    TCPClient(){};
    virtual ~TCPClient() { Disconnect(); };
    bool Connect(const std::string& host, int port) {
        try {
            boost::asio::ip::tcp::resolver resolver(m_context);
            boost::asio::ip::tcp::resolver::results_type endpoints =
                resolver.resolve(host, std::to_string(port));
            m_connection = std::make_unique<TCPConnection<T>>(
                TCPConnection<T>::owner::client, m_context, boost::asio::ip::tcp::socket(m_context),
                m_qMessagesIn);
            m_connection->ConnectToServer(endpoints);
            thrContext = std::thread([this]() { m_context.run(); });
        } catch (std::exception& e) {
            std::cerr << "[ERROR TCP CLI]: " << e.what() << std::endl;
            return false;
        }
        return true;
    };
    void Disconnect() {
        if (isConnected()) {
            m_connection->Disconnect();
        }
        m_context.stop();
        if (thrContext.joinable())
            thrContext.join();
        m_connection.release();
    }
    bool isConnected() {
        if (m_connection)
            return m_connection->IsConnected();
        return false;
    }
    void Send(const message<T>& msg) {
        if (isConnected())
            m_connection->SendAsync(msg);
    }
    ThreadSafeQueue<owned_message<T>>& Incoming() { return m_qMessagesIn; }

   protected:
    boost::asio::io_context m_context;
    std::thread thrContext;
    std::unique_ptr<TCPConnection<T>> m_connection;

   private:
    ThreadSafeQueue<owned_message<T>> m_qMessagesIn;
};

#endif /* !HEADER_TCPCLIENT */
