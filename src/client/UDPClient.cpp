/*
** EPITECH PROJECT, 2023
** UDPClient.cpp
** File description:
** UDPClient
*/

#include "UDPClient.hpp"
#include "Game.hpp"

std::string actionToString(ACTION action)
{
    switch (action)
    {
    case ACTION::OK:
        return "OK";
    case ACTION::KO:
        return "KO";
    case ACTION::CONNECT:
        return "CONNECT";
    case ACTION::CREATE:
        return "CREATE";
    case ACTION::LIST:
        return "LIST";
    case ACTION::JOIN:
        return "JOIN";
    case ACTION::JOINED:
        return "JOINED";
    case ACTION::READY:
        return "READY";
    case ACTION::START:
        return "START";
    case ACTION::LEFT:
        return "LEFT";
    case ACTION::RIGHT:
        return "RIGHT";
    case ACTION::UP:
        return "UP";
    case ACTION::DOWN:
        return "DOWN";
    case ACTION::SHOOT:
        return "SHOOT";
    case ACTION::QUIT:
        return "QUIT";
    case ACTION::PING:
        return "PING";
    case ACTION::PONG:
        return "PONG";
    case ACTION::SPRITE:
        return "SPRITE";
    case ACTION::UNKNOWN:
        return "UNKNOWN";
    case ACTION::SHIELD:
        return "SHIELD";
    case ACTION::TEXT:
        return "TEXT";
    case ACTION::DEAD:
        return "DEAD";
    case ACTION::FLIP:
        return "FLIP";
    case ACTION::RESET:
        return "RESET";
    case ACTION::MOVE:
        return "MOVE";
    case ACTION::WINDOW:
        return "WINDOW";
    case ACTION::CREATEINSTANCE:
        return "CREATEINSTANCE";
    }
    return "ACTION INCONNUE";
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
    StringConfig stringConfig = {"ok"};
    StructsMessages<StringConfig> stringConfigStruct;
    std::vector<uint8_t> serializedStringConfig = stringConfigStruct.serialize(stringConfig);
    Event evt = {ACTION::JOIN, serializedStringConfig.size(), serializedStringConfig};
    sendEvent(evt);
    _port = port;
    _host = host;
    start_receive();
    _thread = std::thread([this]()
                            { io_context_.run(); });
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
            [this](const std::error_code, std::size_t)
            {
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
}

std::vector<uint8_t> UDPClient::encodeEvent(Event event)
{
    EventHandler evt;
    evt.addEvent(event.ACTION_NAME, event.body_size, event.body);
    event.body_size = event.body.size();
    return evt.encodeMessage();
}

void UDPClient::joinGame(Event evt)
{
    StructsMessages<WindowConfig> windowConfigStruct;
    WindowConfig windowConfig = windowConfigStruct.deserialize(evt.body);
    _gameRef->setUDPConnected(true);
    _gameRef->setGameTitle(windowConfig.title);
    _gameRef->setWidth(windowConfig.width);
    _gameRef->setHeight(windowConfig.height);
}

void UDPClient::updateSprite(Event evt)
{
    Parser *parseRef = new Parser();
    RessourceManager ressourceManagerRef = _gameRef->getRessourceManager();
    std::tuple<int, Entity> res = parseRef->parseMessage(evt, ressourceManagerRef);
    if (std::get<0>(res) < 0)
        _gameRef->removeEntity(-std::get<0>(res));
    else
        _gameRef->addEntity(std::get<0>(res), std::get<1>(res));
}

void UDPClient::flipEntity(Event evt)
{
    StructsMessages<ActionConfig> flipConfigStruct;
    ActionConfig flipConfig = flipConfigStruct.deserialize(evt.body);
    _gameRef->flipEntity(std::stoi(flipConfig.id));
}

void UDPClient::handleEvents(Event evt)
{
    switch (evt.ACTION_NAME)
    {
    case ACTION::PING:
        sendEvent({ACTION::PONG, 0, std::vector<uint8_t>()});
        break;
    case ACTION::CREATE:
        updateSprite(evt);
        break;
    case ACTION::JOINED:
        joinGame(evt);
        break;
    case ACTION::SPRITE:
        updateSprite(evt);
        break;
    case ACTION::MOVE:
        updateSprite(evt);
        break;
    case ACTION::DEAD:
        updateSprite(evt);
        break;
    case ACTION::FLIP:
        flipEntity(evt);
        break;
    case ACTION::RESET:
        std::cout << "RESET GAME" << std::endl;
        _gameRef->clearEntities();
        break;
    default:
        std::cout << "ACTION NON GERE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        std::cout << "action : " << actionToString(evt.ACTION_NAME) << std::endl;
        break;
    }
}

void UDPClient::SendAsync(std::vector<uint8_t> data, boost::asio::ip::udp::endpoint endpoint)
{
    boost::asio::post(socket_.get_executor(), [this, data, endpoint]() {
        bool bWritingMessage = !_outQueue.empty();
        _outQueue.push_back({data, endpoint});
        if (!bWritingMessage)
        {
            processSendQueue();
        } });
}

void UDPClient::processSendQueue()
{
  socket_.async_send_to(boost::asio::buffer(_outQueue.front().data), _outQueue.front().endpoint, [this](const std::error_code &error, std::size_t)
    {
      if (!error)
      {
          _outQueue.pop_front();
          if (!_outQueue.empty())
              processSendQueue();
      }
      else
      {
          std::cout << "[ERROR] sending data" << std::endl;
      } });
}