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

void UDPClient::send_data(const std::string &data, const std::string &host, int port)
{
  boost::asio::ip::udp::endpoint remote_endpoint(boost::asio::ip::address::from_string(host), port);
  socket_.send_to(boost::asio::buffer(data), remote_endpoint);
}
void UDPClient::connect_to(const std::string &host, int port)
{
  // send_data("Hello", host, port);
  sendEvent({ACTION::JOIN, 2, "ok"}, host, port);
  _port = port;
  _host = host;
  std::cout << "new server infos: " << _host << " " << _port << std::endl;
}

void UDPClient::setGameRef(Game *gameRef)
{
  _gameRef = gameRef;
}

void UDPClient::receive_data()
{
  std::cout << "receive data" << std::endl;
  boost::asio::ip::udp::endpoint sender_endpoint;
  std::size_t bytes_received = socket_.receive_from(boost::asio::buffer(recv_buffer_), sender_endpoint);
  Event evt;
  EventHandler eventHandler;
  evt = eventHandler.decodeMessage(recv_buffer_);
  std::cout << "Received: " << evt.body << std::endl;
  handleEvents(evt);
}
bool UDPClient::check_ping(const std::string &data)
{
  std::cout << "Received:3 " << data << std::endl;
  return data == "Ping";
}

void UDPClient::sendEvent(Event evt, const std::string &host, int port)
{
  std::vector<uint8_t> data = encodeEvent(evt);
  boost::asio::ip::udp::endpoint remote_endpoint(boost::asio::ip::address::from_string(host), port);
  socket_.send_to(boost::asio::buffer(data), remote_endpoint);
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
    sendEvent({ACTION::PONG, 0, ""}, _host, _port);
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
