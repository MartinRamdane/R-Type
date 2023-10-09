/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** UDPServer
*/

#include "UDPServer.hpp"
#include "Server.hpp"

UDPServer::UDPServer(boost::asio::io_service &io_service, int port) : socket_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
    _nbPlayers = 0;
    _clients = std::vector<Client>();
    try
    {
        std::cout << "Server listening on port " << port << std::endl;
        startReceive();
        ping_thread_ = std::thread(&UDPServer::sendPingToClient, this);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error during server initialization: " << e.what() << std::endl;
    }
}

UDPServer::~UDPServer()
{
}

void UDPServer::startReceive()
{
    try
    {
        socket_.async_receive_from(
            boost::asio::buffer(recv_buffer_), remote_endpoint_, [this](const std::error_code &error, std::size_t bytes_recvd)
            {
                handler(error, bytes_recvd);
                std::cout << "received data" << std::endl; });
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error starting receive: " << e.what() << std::endl;
    }
}

void UDPServer::processMessage(UDPMessage &msg)
{
    mutex_.lock();
    Event evt;
    EventHandler eventHandler;
    checkConnection(msg);
    evt = eventHandler.decodeMessage(msg.data);
    std::cout << "test player id: " << _playerEntities[1] << std::endl;
    std::cout << "Received data: " << evt.body << std::endl;
    auto client = std::find_if(clients_.begin(), clients_.end(), [this](const Client &c)
                               { return c.client.address() == remote_endpoint_.address() && c.client.port() == remote_endpoint_.port(); });
    if (evt.ACTION_NAME == ACTION::PONG)
    {
        client->timestamp = std::chrono::system_clock::now();
        std::cout << "updated timestamp for client " << client->client.address().to_string() << ":" << client->client.port() << std::endl;
    }
    else
    {
        handleEvents(evt, remote_endpoint_);
    }
    mutex_.unlock();
    std::cout << "unlocked mutex" << std::endl;
}

void UDPServer::checkConnection(UDPMessage &msg)
{
    Client client{msg.endpoint, std::chrono::system_clock::now()};
    Event evt;
    if (std::find_if(clients_.begin(), clients_.end(), [&client](const Client &c)
                     { return c.client.address() == client.client.address() && c.client.port() == client.client.port(); }) == clients_.end())
    {
        userJoined(client);
    }
}

void UDPServer::userJoined(Client client) {
    Event evt;
    clients_.push_back(client);
    std::cout << "New client connected: " << client.client.address().to_string() << ":" << client.client.port() << std::endl;
    Client newClient = {client.client, std::chrono::system_clock::now()};
    addClient(newClient);
    std::cout << "Connected at : " << std::chrono::system_clock::to_time_t(client.timestamp) << std::endl;
    std::cout << "vector size : " << clients_.size() << std::endl;
    std::shared_ptr<Engine> engineRef = _instanceRef->getCore()->getEngine();
    engineRef->openWindow();
    std::cout << "window info: " << engineRef->getWindowHeight() << engineRef->getWindowWidth() << engineRef->getWindowTitle() << std::endl;
    evt.ACTION_NAME = ACTION::JOINED;
    evt.body = engineRef->getWindowTitle() + " " + std::to_string(engineRef->getWindowWidth()) + " " + std::to_string(engineRef->getWindowHeight());
    evt.body_size = evt.body.size();
    _instanceRef->addAction(evt);
    sendEvent(evt, client.client.address().to_string(), client.client.port());
}

void UDPServer::handler(const std::error_code &error, std::size_t)
{
    if (!error)
    {
        _queue.push_back({recv_buffer_, remote_endpoint_});
        recv_buffer_.clear();
        recv_buffer_.resize(1024);
        startReceive();
    }
    else if (error.value() == boost::asio::error::eof)
    {
        mutex_.lock();
        auto it = std::find_if(clients_.begin(), clients_.end(), [this](const Client &c)
                               { return c.client.address() == remote_endpoint_.address() && c.client.port() == remote_endpoint_.port(); });
        if (it != clients_.end())
        {
            std::cout << "Client " << it->client.address().to_string() << ":" << it->client.port() << " disconnected." << std::endl;
            clients_.erase(it);
        }
        mutex_.unlock();
        startReceive();
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
        startReceive();
    }
}

void UDPServer::sendPingToClient()
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
                sendEvent({ACTION::PING, 0, ""}, it->client.address().to_string(), it->client.port());
                ++it;
            }
        }
        mutex_.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void UDPServer::addClient(Client client)
{
    _clients.push_back(client);
    _nbPlayers++;
}

void UDPServer::removeClient(Client client)
{
    _clients.erase(std::remove_if(_clients.begin(), _clients.end(), [&client](const Client &c)
                                  { return c.client.address() == client.client.address() && c.client.port() == client.client.port(); }));
    _nbPlayers--;
}

void UDPServer::processSendQueue()
{
    socket_.async_send_to(boost::asio::buffer(_toSendQueue.front().data), _toSendQueue.front().endpoint, [this](const std::error_code &error, std::size_t)
                          {
        if (!error) {
            std::cout << "sent data" << std::endl;
            _toSendQueue.pop_front();
            if (!_toSendQueue.empty())
                processSendQueue();
        }
        else {
            std::cout << "error sending data" << std::endl;
        } });
}

void UDPServer::sendEvent(Event evt, const std::string &host, int port)
{
    std::cout << "event msg : " << evt.body << std::endl;
    message<ACTION> msg;
    std::cout << "send event" << std::endl;
    std::vector<uint8_t> data = encodeEvent(evt);
    boost::asio::ip::udp::endpoint remote_endpoint(boost::asio::ip::address::from_string(host), port);
    sendAsync(data, remote_endpoint);
    std::cout << "pushed to queue" << std::endl;
}

void UDPServer::sendEventToAllClients(Event evt)
{
    for (auto it = _clients.begin(); it != _clients.end(); ++it)
    {
        sendEvent(evt, it->client.address().to_string(), it->client.port());
    }
}

void UDPServer::handleEngineEvents(std::string request)
{
    std::stringstream ss(request);
    std::string eventType;
    std::string body;
    ss >> eventType;
    ss >> body;
}

std::vector<uint8_t> UDPServer::encodeEvent(Event event)
{
    EventHandler evt;
    evt.addEvent(event.ACTION_NAME, event.body_size, event.body);
    return evt.encodeMessage();
}

void UDPServer::handleEvents(Event evt, boost::asio::ip::udp::endpoint endpoint)
{
    switch (evt.ACTION_NAME)
    {
    case ACTION::LEFT:
        std::cout << "Player go to left " << evt.body << std::endl;
        break;
    case ACTION::RIGHT:
        std::cout << "Player go to right" << std::endl;
        break;
    case ACTION::UP:
        std::cout << "Player go to up" << std::endl;
        sendEvent({ACTION::UP, 2, "ok"}, endpoint.address().to_string(), endpoint.port());
        break;
    case ACTION::DOWN:
        std::cout << "Player go to down" << std::endl;
        break;
    case ACTION::SHOOT:
        std::cout << "Player shoot" << std::endl;
        break;
    default:
        break;
    }
    _instanceRef->addAction(evt);
}

void UDPServer::sendAsync(std::vector<uint8_t> data, boost::asio::ip::udp::endpoint endpoint)
{
    boost::asio::post(socket_.get_executor(), [this, data, endpoint]()
                      {
        bool bWritingMessage = !_toSendQueue.empty();
        _toSendQueue.push_back({data, endpoint});
        if (!bWritingMessage)
        {
            processSendQueue();
        } });
}

void UDPServer::handleMessages(size_t maxMessages, bool bWait)
{
    if (bWait)
        _queue.wait();
    size_t nMessageCount = 0;
    while (nMessageCount < maxMessages && !_queue.empty())
    {
        auto msg = _queue.pop_front();
        processMessage(msg);
        nMessageCount++;
    }
}

void UDPServer::addPlayerEntity(int id, std::string entity) {
    _playerEntities[id] = entity;
}