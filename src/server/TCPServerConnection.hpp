/*
** EPITECH PROJECT, 2023
** TCPConnection.hpp
** File description:
** TCPConnection
*/

#ifndef HEADER_TCPCONNECTION
#define HEADER_TCPCONNECTION
#include <iostream>
#include <boost/system/error_code.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "EventHandler.hpp"
#include "ThreadSafeQueue.hpp"
#include "Messages.hpp"

class ServerClass;
using boost::asio::ip::tcp;
using namespace boost::asio;

template <typename T>
class TCPConnection : public boost::enable_shared_from_this<TCPConnection<T>>
{
public:
    enum class owner
    {
        server,
        client
    };
    TCPConnection(owner parent, boost::asio::io_context& asioContext, boost::asio::ip::tcp::socket socket, ThreadSafeQueue<message<T>>& qMessagesIn)
        : m_socket(asioContext), m_socket(std::move(socket)),m_asioContext(asioContext), m_qMessagesIn(qMessagesIn)
    {
        m_ownerType = parent;
    }
    virtual ~TCPConnection() {}
    uint32_t GetID() const
    {
        return id;
    }
    void ConnectToClient(uint32_t uid = 0) {
        if (m_ownerType == owner::server)
        {
            if (m_socket.is_open())
            {
                id = uid;
                ReadData();
            }
        }
    }
    void ConnectToServer(const tcp::resolver::results_type& endpoints)
    {
        if (m_ownerType == owner::client)
        {
            boost::asio::async_connect(m_socket, endpoints,
                [this](const boost::system::error_code& ec, tcp::endpoint endpoint)
                {
                    if (!ec)
                    {
                        ReadData();
                    }
                });
        }
    }
    void Disconnect()
    {
        if (IsConnected())
            boost::asio::post(m_asioContext, [this]() { m_socket.close(); });
    }
    bool IsConnected() const
    {
        return m_socket.is_open();
    }
    void SendAsync(const message<T>& msg)
    {
        boost::asio::post(m_asioContext,
            [this, msg]()
            {
                bool bWritingMessage = !m_qMessagesOut.empty();
                m_qMessagesOut.push_back(msg);
                if (!bWritingMessage)
                {
                    WriteData();
                }
            });
    }
    vo

private:
    void WriteData() {
        boost::asio::async_write(m_socket, boost::asio::buffer(m_qMessagesOut.front(), m_qMessagesOut.front().size()),
            [this](const boost::system::error_code& error, std::size_t length) {
                if (!error) {
                    std::cout << "Sent: " << length << std::endl;
                    m_qMessagesOut.pop_front();
                    if (!m_qMessagesOut.empty()) {
                        WriteData();
                    }
                } else {
                    std::cout << "[ERROR] while writing data: " << error.message() << std::endl;
                    m_socket.close();
                }
            }
        );
    }
    void ReadData() {
        boost::asio::async_read(m_socket, boost::asio::buffer(m_msgTemporaryIn, 1024),
            [this](const boost::system::error_code& error, std::size_t length) {
                if (!error) {
                    std::cout << "Received: " << length << std::endl;
                    if (length == 0)
                        Disconnect();
                    m_qMessagesIn.push_back({this->shared_from_this(), m_msgTemporaryIn});
                    ReadData();
                } else {
                    std::cout << "[ERROR] while reading data: " << error.message() << std::endl;
                    m_socket.close();
                }
            }
        );
    }
    void AddToIncomingMessageQueue()
    {
        if (m_ownerType == owner::server)
            m_qMessagesIn.push_back({ this->shared_from_this(), m_msgTemporaryIn });
        else
            m_qMessagesIn.push_back({ nullptr, m_msgTemporaryIn });
        ReadData();
    }
    boost::asio::ip::tcp::socket m_socket;
    boost::asio::io_context& m_asioContext;
    ThreadSafeQueue<message<T>> m_qMessagesOut;
    ThreadSafeQueue<owned_message<T>>& m_qMessagesIn;
    message<T> m_msgTemporaryIn;
    owner m_ownerType = owner::server;
    uint32_t id = 0;
};

#endif /* !HEADER_TCPCONNECTION */
