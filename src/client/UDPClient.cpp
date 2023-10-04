/*
** EPITECH PROJECT, 2023
** UDPClient.cpp
** File description:
** UDPClient
*/

#include "UDPClient.hpp"
#include "Game.hpp"

UDPClient::UDPClient() : io_context_(), socket_(io_context_)
{
  socket_.open(boost::asio::ip::udp::v4());
  _host = "";
  _port = 0;
}

UDPClient::~UDPClient()
{
  socket_.close();
}

void UDPClient::send_data(const std::string &data)
{
  socket_.async_send_to(boost::asio::buffer(data), remote_endpoint_,
  [this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/) {
        //std::cout << "data sent" << std::endl;
    });
}
void UDPClient::connect_to(const std::string &host, int port)
{
    remote_endpoint_ = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(host), port);
    sendEvent({ACTION::JOIN, 2, "ok"});
    _port = port;
    _host = host;
    //std::cout << "new server infos: " << _host << " " << _port << std::endl;
    start_receive();
    _thread = std::thread([this]() { io_context_.run(); });
    //std::cout << "did connect" << std::endl;
}

void UDPClient::setGameRef(Game *gameRef)
{
  _gameRef = gameRef;
}

void UDPClient::start_receive()
{
    try
    {
      socket_.async_receive_from(
          boost::asio::buffer(temp_buffer), sender_endpoint,
          [this](const std::error_code &error, std::size_t bytes_recvd) {
            // handler(error, bytes_recvd);
            _queue.push_back(temp_buffer);
            start_receive();
          });
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error starting receive: " << e.what() << std::endl;
    }
}

void UDPClient::handler()
{
    if (_queue.empty())
        return;
    while (!_queue.empty())
    {
        temp_buffer = _queue.front();
        Event evt;
        EventHandler eventHandler;
        evt = eventHandler.decodeMessage(temp_buffer);
        handleEvents(evt);
        _queue.pop_front();
    }
}

void UDPClient::sendEvent(Event evt)
{
    std::vector<uint8_t> data = encodeEvent(evt);
    socket_.async_send_to(boost::asio::buffer(data), remote_endpoint_, [this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/) {
        std::cout << "data sent" << std::endl;
    });
}

std::vector<uint8_t> UDPClient::encodeEvent(Event event)
{
    EventHandler evt;
    evt.addEvent(event.ACTION_NAME, event.body_size, event.body);
    return evt.encodeMessage();
}

void UDPClient::joinGame(Event evt)
{
    std::stringstream ss(evt.body);
    std::string gameTitle;
    std::string width;
    std::string height;
    ss >> gameTitle;
    ss >> width;
    ss >> height;
    std::cout << "window should be created: " << gameTitle << " " << std::stoi(width) << " " << std::stoi(height) << std::endl;
    _gameRef->setUDPConnected(true);
    _gameRef->setGameTitle(gameTitle);
    _gameRef->setWidth(std::stoi(width));
    _gameRef->setHeight(std::stoi(height));
}

void UDPClient::updateSprite(Event evt)
{
  std::stringstream ss(evt.body);
  std::string id;
  std::string x;
  std::string y;
  std::string sprite;
  std::string jsonPath;
  std::string objectType;
  ss >> id;
  ss >> x;
  ss >> y;
  ss >> sprite;
  ss >> jsonPath;
  ss >> objectType;
  std::cout << "update sprite message: " << evt.body << std::endl;
  Parser *parseRef = _gameRef->getParser();
  RessourceManager ressourceManagerRef = _gameRef->getRessourceManager();
  parseRef->parseMessage(evt, evt.body, ressourceManagerRef);
}

void UDPClient::handleEvents(Event evt)
{
  switch (evt.ACTION_NAME)
  {
  case ACTION::PING:
    sendEvent({ACTION::PONG, 0, ""});
    break;
  case ACTION::JOINED:
    joinGame(evt);
    break;
  case ACTION::SPRITE:
    updateSprite(evt);
    break;
  default:
    break;
  }
}
