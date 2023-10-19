/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Game.cpp
*/

#include "Game.hpp"
#include "TCPClientImpl.hpp"

Game::Game() : _threadPool(2)
{
    _ressourceManager = RessourceManager();
    _event_indicator = 0;
    _gameTitle = "game";
    _width = 850;
    _height = 478;
    _playerId = 0;
    closed = false;
}

void Game::createWindow(std::string name, int x, int y)
{
    _window.create(sf::VideoMode(1920, 1080), name);
    _window.setFramerateLimit(60);
    _view = sf::View(sf::FloatRect(0, 0, x, y));
}

void Game::run()
{
    while (closed == false)
    {
        if (_client->Incoming().empty() == false)
        {
            auto msg = _client->Incoming().pop_front().msg;
            _client->HandleMessage(msg);
        }
        if (isUDPClientConnected == true)
        {
            createWindow(_gameTitle, _width, _height);
            Event evt;
            evt.ACTION_NAME = ACTION::READY;
            evt.body_size = 0;
            evt.body = std::vector<uint8_t>();
            _udpClient->sendEvent(evt);
            _threadPool.enqueue([this]
                                { this->LoopUDPMessages(); });
            while (_window.isOpen())
            {
                if (_client->Incoming().empty() == false)
                {
                    auto msg = _client->Incoming().pop_front().msg;
                    _client->HandleMessage(msg);
                }
                // getinfos -> appel de parseMessage
                handleEvent();
                update();
            }
        }
    }
    exit(0);
}

void Game::LoopUDPMessages()
{
    while (1)
    {
        if (_udpClient->Incoming().empty() == false)
        {
            auto msg = _udpClient->Incoming().pop_front();
            _udpClient->HandleMessage(msg);
        }
    }
}

void Game::handleEvent()
{
    while (_window.pollEvent(_event))
    {
        if (_event.type == sf::Event::Closed)
        {
            _window.close();
            _client->Disconnect();
            closed = true;
        }
        if (_event.type == (sf::Event::KeyPressed))
        {
            if (_event.key.code == sf::Keyboard::R)
            {
                Event evt;
                std::string playerId = "p" + std::to_string(_playerId);
                ActionConfig actionConfig = {playerId};
                StructsMessages<ActionConfig> actionConfigStruct;
                std::vector<uint8_t> data = actionConfigStruct.serialize(actionConfig);
                evt.ACTION_NAME = ACTION::FLIP;
                evt.body = data;
                evt.body_size = sizeof(data);
                _udpClient->sendEvent(evt);
            }
        }
    }
    Event evt;
    std::string playerId = "p" + std::to_string(_playerId);
    if (_lastFrameTime.time_since_epoch().count() == 0)
        _lastFrameTime = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - _lastFrameTime).count() > 10)
    {
        _lastFrameTime = std::chrono::high_resolution_clock::now();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            ActionConfig actionConfig = {playerId};
            StructsMessages<ActionConfig> actionConfigStruct;
            std::vector<uint8_t> data = actionConfigStruct.serialize(actionConfig);
            evt.ACTION_NAME = ACTION::LEFT;
            evt.body_size = sizeof(data);
            evt.body = data;
            _udpClient->sendEvent(evt);
            _event_indicator = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            ActionConfig actionConfig = {playerId};
            StructsMessages<ActionConfig> actionConfigStruct;
            std::vector<uint8_t> data = actionConfigStruct.serialize(actionConfig);
            evt.ACTION_NAME = ACTION::RIGHT;
            evt.body_size = sizeof(data);
            evt.body = data;
            _udpClient->sendEvent(evt);
            _event_indicator = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            ActionConfig actionConfig = {playerId};
            StructsMessages<ActionConfig> actionConfigStruct;
            std::vector<uint8_t> data = actionConfigStruct.serialize(actionConfig);
            evt.ACTION_NAME = ACTION::UP;
            evt.body_size = data.size() * sizeof(uint8_t);
            evt.body = data;
            _udpClient->sendEvent(evt);
            _event_indicator = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            ActionConfig actionConfig = {playerId};
            StructsMessages<ActionConfig> actionConfigStruct;
            std::vector<uint8_t> data = actionConfigStruct.serialize(actionConfig);
            evt.ACTION_NAME = ACTION::DOWN;
            evt.body_size = sizeof(data);
            evt.body = data;
            _udpClient->sendEvent(evt);
            _event_indicator = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            ActionConfig actionConfig = {playerId};
            StructsMessages<ActionConfig> actionConfigStruct;
            std::vector<uint8_t> data = actionConfigStruct.serialize(actionConfig);
            evt.ACTION_NAME = ACTION::SHOOT;
            evt.body_size = sizeof(data);
            evt.body = data;
            _udpClient->sendEvent(evt);
            _event_indicator = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            _window.close();
            _client->Disconnect();
            closed = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            ActionConfig actionConfig = {playerId};
            StructsMessages<ActionConfig> actionConfigStruct;
            std::vector<uint8_t> data = actionConfigStruct.serialize(actionConfig);
            evt.ACTION_NAME = ACTION::SHIELD;
            evt.body_size = sizeof(data);
            evt.body = data;
            _udpClient->sendEvent(evt);
        }
    }
}

void Game::animate()
{
    std::map<int, Entity>::iterator it = _entities.begin();
    while (it != _entities.end())
    {
        if (it->second.getEventForm() == "loop")
            it->second.animateSprite(0, 100);
        if (it->second.getEventForm() == "once")
            it->second.animateSprite(3, 100);
        if (it->second.getEventForm() == "event" && _event_indicator == 0)
            it->second.setInitPos();
        if (it->second.getEventForm() == "paralaxe")
            it->second.animateSprite(4, 1);
        if (it->second.getEventForm() == "event" && _event_indicator == 1)
        {
            if (it->second.getSpritePosition().y > it->second.getOldPosY())
                it->second.animateSprite(2, 100);
            else if (it->second.getSpritePosition().y < it->second.getOldPosY())
                it->second.animateSprite(1, 100);
        }
        it++;
    }
}

void Game::draw()
{
    std::map<int, Entity>::iterator it = _entities.begin();
    while (it != _entities.end())
    {
        if (it->second.getType() == Entity::Type::TEXT)
        {
            it->second.setFont();
            _window.draw(it->second.getText());
        }
        else if (it->second.getType() == Entity::Type::SPRITE)
        {
            _window.draw(it->second.getSprite());
            std::string direction = it->second.getDirection();
            if (direction == "left" || direction == "right") {
                float speed = it->second.getSpeed();
                if (direction == "left") {
                    speed = speed * -1;
                }
                sf::Vector2f oldPos = it->second.getSpritePosition();
                sf::Vector2f newPos = sf::Vector2f(oldPos.x + speed, oldPos.y);
                it->second.setNextPos(newPos);
            }
        }
        it++;
    }
}

void Game::update()
{
    _window.clear();
    animate();
    draw();
    _window.setView(_view);
    _window.display();
    for (auto it = _entities.begin(); it != _entities.end();)
    {
        (*it).second.update();
        if ((*it).second.isDead())
        {
            Event evt;
            ActionConfig actionConfig = {std::to_string((*it).first)};
            StructsMessages<ActionConfig> actionConfigStruct;
            std::vector<uint8_t> data = actionConfigStruct.serialize(actionConfig);
            evt.ACTION_NAME = ACTION::DEAD;
            evt.body_size = sizeof(data);
            evt.body = data;
            _udpClient->sendEvent(evt);
            it = _entities.erase(it);
        }
        else
            it++;
    }
}

bool Game::connectToServer(std::string host, int port)
{
    _client = new TCPClientImpl();
    _client->setGame(this);
    bool connected = _client->Connect(host, port, this);
    _host = host;
    return connected;
}

bool Game::connectToUdpServer(std::string host, int port)
{
    _udpClient = new UDPClient();
    _udpClient->setGameRef(this);
    _udpClient->connect_to(host, port);
    isUDPClientConnected = true;
    std::cout << "UDP client connected" << std::endl;
    return true;
}

bool Game::findEntity(int id)
{
    std::map<int, Entity>::iterator it = _entities.begin();
    while (it != _entities.end())
    {
        if (it->first == id)
            return true;
        it++;
    }
    return false;
}

void Game::removeEntity(int id)
{
    _entities.erase(id);
}

void Game::addEntity(int id, Entity entity)
{
    if (findEntity(id) == true)
        _entities[id].setNextPos(entity.getNextPos());
    else
        _entities[id] = entity;
}

void Game::flipEntity(int id)
{
    _entities[id].flip();
}