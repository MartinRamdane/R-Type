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
#include "Game.hpp"

using boost::asio::ip::tcp;
using namespace boost::asio;
class Game;
template <typename T>
class TCPConnection : public std::enable_shared_from_this<TCPConnection<T>>
{
public:
    enum class owner
    {
        server,
        client
    };
    TCPConnection(owner parent, boost::asio::io_context& asioContext, boost::asio::ip::tcp::socket socket, ThreadSafeQueue<owned_message<T>>& qMessagesIn, Game *game = nullptr)
        : m_asioContext(asioContext), m_socket(std::move(socket)), m_qMessagesIn(qMessagesIn)
    {
        m_ownerType = parent;
        _game = game;
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
                ReadHeader();
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
                        std::cout << "[DEBUG] Connected to server: " << endpoint << std::endl;
                        // _game->setConnected(true);
                        ReadHeader();
                    } else {
                        std::cout << "[DEBUG] Failed to connect to server: " << ec.message() << std::endl;
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
                    WriteHeader();
                }
            });
    }

private:
    void WriteHeader() {
        boost::asio::async_write(m_socket, boost::asio::buffer(&m_qMessagesOut.front().header, sizeof(message_header<T>)), [this](std::error_code error, std::size_t lenght) {
            if (!error) {
                if (m_qMessagesOut.front().body.size() > 0) {
                    WriteBody();
                } else {
                    m_qMessagesOut.pop_front();
                    if (!m_qMessagesOut.empty()) {
                        WriteHeader();
                    }
                }
            } else {
                std::cout << "Write header failed" << std::endl;
            }
        });
    }
    void WriteBody() {
        boost::asio::async_write(m_socket, boost::asio::buffer(m_qMessagesOut.front().body, m_qMessagesOut.front().body.size()),
            [this](std::error_code ec, std::size_t length) {
                if (!ec) {
                    std::cout << "Sent: " << length << std::endl;
                    m_qMessagesOut.pop_front();
                    if (!m_qMessagesOut.empty()) {
                        WriteHeader();
                    }
                } else {
                    std::cout << "[ERROR] while writing data: " << ec.message() << std::endl;
                    m_socket.close();
                }
            }
        );
    }
    void ReadHeader() {
        boost::asio::async_read(m_socket, boost::asio::buffer(&m_msgTemporaryIn.header, sizeof(message_header<T>)),
            [this](const boost::system::error_code& error, std::size_t length) {
                if (!error) {
                    std::cout << "Received: " << length << std::endl;
                    if (m_msgTemporaryIn.header.size > 0) {
                        m_msgTemporaryIn.body.resize(m_msgTemporaryIn.header.size);
                        ReadBody();
                    } else {
                        AddToIncomingMessageQueue();
                    }
                } else {
                    std::cout << "[ERROR] while reading data: " << error.message() << std::endl;
                    m_socket.close();
                }
            }
        );
    }
    void ReadBody() {
        boost::asio::async_read(m_socket, boost::asio::buffer(m_msgTemporaryIn.body.data(), m_msgTemporaryIn.body.size()),
            [this](const boost::system::error_code& error, std::size_t length) {
                if (!error) {
                    std::cout << "[DEBUG] Received: " << length << std::endl;
                    AddToIncomingMessageQueue();
                } else {
                    std::cout << "[ERROR] while reading data: " << error.message() << std::endl;
                    m_socket.close();
                }
            }
        );
    }
    void AddToIncomingMessageQueue()
    {
        if(m_ownerType == owner::server)
            m_qMessagesIn.push_back({ this->shared_from_this(), m_msgTemporaryIn });
        else
            m_qMessagesIn.push_back({ nullptr, m_msgTemporaryIn });

        // We must now prime the asio context to receive the next message. It 
        // wil just sit and wait for bytes to arrive, and the message construction
        // process repeats itself. Clever huh?
        ReadHeader();
    }
protected:
    boost::asio::ip::tcp::socket m_socket;
    boost::asio::io_context& m_asioContext;
    ThreadSafeQueue<message<T>> m_qMessagesOut;
    ThreadSafeQueue<owned_message<T>>& m_qMessagesIn;
    message<T> m_msgTemporaryIn;
    owner m_ownerType = owner::server;
    uint32_t id = 0;
    Game *_game;
};

#endif /* !HEADER_TCPCONNECTION */