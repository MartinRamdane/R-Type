/*
** EPITECH PROJECT, 2023
** TCPServer.hpp
** File description:
** TCPServer
*/

#ifndef HEADER_TCPServer
#define HEADER_TCPServer
#include "TCPServerConnection.hpp"
#include "ThreadSafeQueue.hpp"
#include "Messages.hpp"

class ServerClass;
template<typename T>
class TCPServer {
  public:
    TCPServer(int port) : _acceptor(io_context_, tcp::endpoint(tcp::v4(), port)) {
    }
    virtual ~TCPServer() {StopServer();};
    bool StartServer() {
      try {
        WaitForClientAsync();
        context_thread_ = std::thread([this]() { io_context_.run(); });
      } catch (std::exception &e) {
        std::cerr << "[ERROR]: " << e.what() << std::endl;
        return false;
      }
      std::cout << "[DEBUG] Server started" << std::endl;
      return true;
    }
    void StopServer() {
      io_context_.stop();
      if (context_thread_.joinable())
        context_thread_.join();
      std::cout << "[DEBUG] TCP Server stopped" << std::endl;
    }
    void WaitForClientAsync() {
      _acceptor.async_accept(
        [this](const boost::system::error_code &error, tcp::socket socket) {
          if (!error) {
            std::shared_ptr<TCPConnection<T>> new_connection = std::make_shared<TCPConnection<T>>(TCPConnection<T>::owner::server, io_context_, std::move(socket), _messagesIn);
            if (OnClientconnect(new_connection)) {
              m_deqConnections.push_back(std::move(new_connection));
              m_deqConnections.back()->ConnectToClient(IDCounter++);
              std::cout << "Client connected" << std::endl;
            } else {
              std::cout << "Connection Denied" << std::endl;
            }
          } else {
            std::cout << "[ERROR TCP Server]: " << error.message() << std::endl;
          }
          WaitForClientAsync();
        });
    }
    void SendMessageAsync(std::shared_ptr<TCPConnection<T>> client , const message<T> &msg) {
      if (client && client->IsConnected()) {
        client->SendAsync(msg);
      } else {
        OnClientdisconnect(client);
        client.reset();
        // utilise bcp de ressource
        m_deqConnections.erase(std::remove(m_deqConnections.begin(), m_deqConnections.end(), client), m_deqConnections.end());
      }
    }
    void SendMessageToAllAsync(message<T> &msg) {
      for (auto &client : m_deqConnections) {
        if (client && client->IsConnected()) {
          client->SendAsync(msg);
        } else {
          OnClientdisconnect(client);
          client.reset();
          // utilise bcp de ressource
          m_deqConnections.erase(std::remove(m_deqConnections.begin(), m_deqConnections.end(), client), m_deqConnections.end());
        }
      }
    }
    void setServer(ServerClass *server) { _server = server; }
    void HandleMessages(size_t maxMessages = -1) {
      size_t nMessageCount = 0;
      while (nMessageCount < maxMessages && !_messagesIn.empty()) {
        auto msg = _messagesIn.pop_front();
        OnMessage(msg.remote, msg.msg);
        nMessageCount++;
      }
    }
  protected:
    virtual bool OnClientconnect(std::shared_ptr<TCPConnection<T>> client) {
      return true;
    }
    virtual void OnClientdisconnect(std::shared_ptr<TCPConnection<T>> client) {
      std::cout << "Client disconnected" << std::endl;
    }
    virtual void OnMessage(std::shared_ptr<TCPConnection<T>> client, message<T>& msg) {
      std::cout << "Client read: " << msg.body.size() << std::endl;
    }
  private:
    boost::asio::io_context io_context_;
    std::thread context_thread_;
    ThreadSafeQueue<owned_message<T>> _messagesIn;
    tcp::acceptor _acceptor;
    ServerClass *_server;
    EventHandler _eventHandler;
    std::deque<std::shared_ptr<TCPConnection<T>>> m_deqConnections;
    uint32_t IDCounter = 10000;
};

#endif /* !HEADER_TCPServer */
