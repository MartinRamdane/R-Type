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
            boost::asio::buffer(recv_buffer_), remote_endpoint_, [this](const std::error_code &error, std::size_t bytes_recvd)
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
        Event evt;
        EventHandler eventHandler;
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
            std::string buffer = engineRef->getWindowTitle() + " " + std::to_string(engineRef->getWindowWidth()) + " " + std::to_string(engineRef->getWindowHeight());
            evt.ACTION_NAME = ACTION::JOINED;
            evt.body_size = buffer.size();
            evt.body = buffer;
            sendEvent(evt, client.client.address().to_string(), client.client.port());
            evt.ACTION_NAME = ACTION::SPRITE;
            buffer.clear();
            buffer = "3 300 0 Spaceship2.png 0 1 1 ./config.json Spaceship";
            evt.body_size = buffer.size();
            evt.body = buffer;
            sendEvent(evt, client.client.address().to_string(), client.client.port());
        }
        evt = eventHandler.decodeMessage(recv_buffer_);
        std::cout << "Received data: " << evt.body << std::endl;

        if (evt.ACTION_NAME == ACTION::PONG)
        {
            auto it = std::find_if(clients_.begin(), clients_.end(), [&client](const Client &c)
                                   { return c.client.address() == client.client.address() && c.client.port() == client.client.port(); });
            if (it != clients_.end())
            {
                it->timestamp = std::chrono::system_clock::now();
                std::cout << "updated timestamp for client " << it->client.address().to_string() << ":" << it->client.port() << std::endl;
            }
        }
        else
        {
            handleEvents(evt, remote_endpoint_);
        }
        mutex_.unlock();
        start_receive();
    }
    else if (error.value() == boost::asio::error::eof)
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

void UDPServer::sendEvent(Event evt, const std::string &host, int port)
{
    message<ACTION> msg;
    std::cout << "send event" << std::endl;
    std::vector<uint8_t> data = encodeEvent(evt);
    boost::asio::ip::udp::endpoint remote_endpoint(boost::asio::ip::address::from_string(host), port);
    socket_.async_send_to(boost::asio::buffer(data), remote_endpoint, [this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/) {
        std::cout << "sent" << std::endl;
    });
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