/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** UDPServer
*/

#include "UDPServer.hpp"
#include "Server.hpp"

/**
 * @brief Construct a new UDPServer::UDPServer object
 *
 * @param io_service service used for async ops
 * @param port port the server needs to listen on
 */

UDPServer::UDPServer(boost::asio::io_service &io_service, int port) : socket_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
    _nbPlayers = 0;
    _clients = std::vector<Client>();
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

/**
 * @brief Start receiving data from the client
 *
 */

void UDPServer::start_receive()
{
    try
    {
        socket_.async_receive_from(
            boost::asio::buffer(recv_buffer_), remote_endpoint_, [this](const std::error_code &error, std::size_t bytes_recvd)
            {
                handler(error, bytes_recvd);
                std::cout << "received data" << std::endl;
            });
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error starting receive: " << e.what() << std::endl;
    }
}

/**
 * @brief Process the message received from the client
 *
 * @param msg message received
 */

void UDPServer::ProcessMessage(UDPMessage &msg)
{
    mutex_.lock();
    Event evt;
    EventHandler eventHandler;
    checkConnection(msg);
    evt = eventHandler.decodeMessage(msg.data);
    std::cout << "Received data: " << evt.body << std::endl;
    auto client = std::find_if(clients_.begin(), clients_.end(), [this](const Client &c)
    { return c.client.address() == remote_endpoint_.address() && c.client.port() == remote_endpoint_.port(); });
    if (evt.ACTION_NAME == ACTION::PONG) {
        client->timestamp = std::chrono::system_clock::now();
        std::cout << "updated timestamp for client " << client->client.address().to_string() << ":" << client->client.port() << std::endl;
    }
    else {
        handleEvents(evt, remote_endpoint_);
    }
    mutex_.unlock();
    std::cout << "unlocked mutex" << std::endl;
}

/**
 * @brief Check if the client is still connected if so update the client list
 *
 * @param msg messages data
 */
void UDPServer::checkConnection(UDPMessage &msg)
{
    Client client{msg.endpoint, std::chrono::system_clock::now()};
    Event evt;
    if (std::find_if(clients_.begin(), clients_.end(), [&client](const Client &c)
                     { return c.client.address() == client.client.address() && c.client.port() == client.client.port(); }) == clients_.end())
    {
        clients_.push_back(client);
        std::cout << "New client connected: " << client.client.address().to_string() << ":" << client.client.port() << std::endl;
        // add the new client connected to this instance of the game in the instance client list
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
        sendEvent(evt, client.client.address().to_string(), client.client.port());
        evt.ACTION_NAME = ACTION::SPRITE;
        evt.body = "3 300 0 Spaceship2.png 0 1 1 ./config.json Spaceship";
        evt.body_size = evt.body.size();
        sendEvent(evt, client.client.address().to_string(), client.client.port());
    }
}

/**
 * @brief Handle received messages, it adds the message to the queue and restarts the receive
 *
 * @param error
 * @param bytes_recvd
 */
void UDPServer::handler(const std::error_code &error, std::size_t bytes_recvd)
{
    if (!error) {
        _queue.push_back({recv_buffer_, remote_endpoint_});
        recv_buffer_.clear();
        recv_buffer_.resize(1024);
        start_receive();
    }
    else if (error.value() == boost::asio::error::eof) {
        mutex_.lock();
        auto it = std::find_if(clients_.begin(), clients_.end(), [this](const Client &c)
        { return c.client.address() == remote_endpoint_.address() && c.client.port() == remote_endpoint_.port(); });
        if (it != clients_.end())
        {
            std::cout << "Client " << it->client.address().to_string() << ":" << it->client.port() << " disconnected." << std::endl;
            clients_.erase(it);
        }
        mutex_.unlock();
        start_receive();
    } else {
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

/**
 * @brief Send a ping to all the clients every 2 seconds
 *
 */
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
                sendEvent({ACTION::PING, 0, ""}, it->client.address().to_string(), it->client.port());
                ++it;
            }
        }
        mutex_.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

/**
 * @brief Adds client to the vector
 *
 */
void UDPServer::addClient(Client client)
{
    _clients.push_back(client);
    _nbPlayers++;
}

/**
 * @brief Removes client from the vector
 *
 */
void UDPServer::removeClient(Client client)
{
    _clients.erase(std::remove_if(_clients.begin(), _clients.end(), [&client](const Client &c)
    { return c.client.address() == client.client.address() && c.client.port() == client.client.port(); }));
    _nbPlayers--;
}

/**
 * @brief Process send queue and send data to the clients
 *
 */
void UDPServer::processSendQueue() {
    socket_.async_send_to(boost::asio::buffer(_toSendQueue.front().data), _toSendQueue.front().endpoint, [this](const std::error_code &error, std::size_t bytes_recvd)
    {
        if (!error) {
            std::cout << "sent data" << std::endl;
            _toSendQueue.pop_front();
            if (!_toSendQueue.empty())
                processSendQueue();
        }
        else {
            std::cout << "error sending data" << std::endl;
        }
    });

}

/**
 * @brief Adds event to the send queue
 *
 * @param evt event to send
 * @param host client's ip
 * @param port client's port
 */
void UDPServer::sendEvent(Event evt, const std::string &host, int port)
{
    std::cout << "event msg : " << evt.body << std::endl;
    message<ACTION> msg;
    std::cout << "send event" << std::endl;
    std::vector<uint8_t> data = encodeEvent(evt);
    boost::asio::ip::udp::endpoint remote_endpoint(boost::asio::ip::address::from_string(host), port);
    SendAsync(data, remote_endpoint);
    std::cout << "pushed to queue" << std::endl;
}

/**
 * @brief Sends event to all the clients (adds to the send queue)
 *
 * @param evt event to send
 */
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

/**
 * @brief Handles the events received from the client
 *
 * @param evt  event received
 * @param endpoint  client's endpoint
 */
void UDPServer::handleEvents(Event evt, boost::asio::ip::udp::endpoint endpoint)
{
    switch (evt.ACTION_NAME)
    {
    case ACTION::LEFT:
        std::cout << "Player go to left" << std::endl;
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
}

/**
 * @brief Send data to the client asynchronously
 *
 * @param data data to send
 * @param endpoint client's endpoint
 */
void UDPServer::SendAsync(std::vector<uint8_t> data, boost::asio::ip::udp::endpoint endpoint)
{
    boost::asio::post(socket_.get_executor(), [this, data, endpoint]() {
        bool bWritingMessage = !_toSendQueue.empty();
        _toSendQueue.push_back({data, endpoint});
        if (!bWritingMessage)
        {
            processSendQueue();
        }
    });
}