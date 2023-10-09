/*
** EPITECH PROJECT, 2023
** UDPClient.cpp
** File description:
** UDPClient
*/

#include "UDPClient.hpp"
#include "Game.hpp"

std::string actionToString(ACTION action) {
    switch (action) {
      case ACTION::OK: return "OK";
      case ACTION::KO: return "KO";
      case ACTION::CONNECT: return "CONNECT";
      case ACTION::CREATE: return "CREATE";
      case ACTION::LIST: return "LIST";
      case ACTION::JOIN: return "JOIN";
      case ACTION::JOINED: return "JOINED";
      case ACTION::READY: return "READY";
      case ACTION::START: return "START";
      case ACTION::LEFT: return "LEFT";
      case ACTION::RIGHT: return "RIGHT";
      case ACTION::UP: return "UP";
      case ACTION::DOWN: return "DOWN";
      case ACTION::SHOOT: return "SHOOT";
      case ACTION::QUIT: return "QUIT";
      case ACTION::PING: return "PING";
      case ACTION::PONG: return "PONG";
      case ACTION::SPRITE: return "SPRITE";
      case ACTION::UNKNOWN: return "UNKNOWN";
      case ACTION::SHIELD: return "SHIELD";
    }
    return "";
  }

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

void UDPClient::connect_to(const std::string &host, int port)
{
    remote_endpoint_ = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(host), port);
    sendEvent({ACTION::JOIN, 2, "ok"});
    _port = port;
    _host = host;
    start_receive();
    _thread = std::thread([this]() { io_context_.run(); });
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
          [this](const std::error_code, std::size_t ) {
            _queue.push_back(temp_buffer);
            start_receive();
          });
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error starting receive: " << e.what() << std::endl;
    }
}

void UDPClient::HandleMessage(std::vector<uint8_t> &msg)
{
    EventHandler evt;
    Event event = evt.decodeMessage(msg);
    handleEvents(event);
}

void UDPClient::sendEvent(Event evt)
{
    std::vector<uint8_t> data = encodeEvent(evt);
    SendAsync(data, remote_endpoint_);
    std::cout << "added event : " << actionToString(evt.ACTION_NAME) << std::endl;
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
  Parser *parseRef = new Parser();
  RessourceManager ressourceManagerRef = _gameRef->getRessourceManager();
  std::tuple<int, Entity> res = parseRef->parseMessage(evt.body, ressourceManagerRef);
  if (std::get<0>(res) < 0)
    _gameRef->removeEntity(-std::get<0>(res));
  else
    _gameRef->addEntity(std::get<0>(res), std::get<1>(res));

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

void UDPClient::SendAsync(std::vector<uint8_t> data, boost::asio::ip::udp::endpoint endpoint)
{
    boost::asio::post(socket_.get_executor(), [this, data, endpoint]()
                      {
                          bool bWritingMessage = !_outQueue.empty();
                          _outQueue.push_back({data, endpoint});
                          if (!bWritingMessage)
                          {
                              processSendQueue();
                          }
                      });
}

void UDPClient::processSendQueue() {
  socket_.async_send_to(boost::asio::buffer(_outQueue.front().data), _outQueue.front().endpoint, [this](const std::error_code &error, std::size_t)
  {
      if (!error)
      {
          std::cout << "sent data" << std::endl;
          _outQueue.pop_front();
          if (!_outQueue.empty())
              processSendQueue();
      }
      else
      {
          std::cout << "error sending data" << std::endl;
      }
  });

}