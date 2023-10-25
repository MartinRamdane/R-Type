/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** DisplaySFML.cpp
*/

#include "DisplaySFML.hpp"

DisplaySFML::DisplaySFML()
{
    _event_indicator = 0;
    _ressourceManager = RessourceManager();
    _playerId = 0;
}

DisplaySFML::~DisplaySFML() {}

void DisplaySFML::createWindow(std::string name, int x, int y)
{
  _window.create(sf::VideoMode(1920, 1080), name);
  _window.setFramerateLimit(60);
  _view = sf::View(sf::FloatRect(0, 0, x, y));
}

void DisplaySFML::animate(std::map<int, Entity>* _entities)
{
  std::map<int, Entity>::iterator it = _entities->begin();
  while (it != _entities->end())
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

void DisplaySFML::draw(std::map<int, Entity>* _entities)
{
  
  std::map<int, Entity>::iterator it = _entities->begin();
  while (it != _entities->end())
  {
    if (it->second.getType() == Entity::Type::TEXT)
    {
      it->second.setFont();
      _window.draw(it->second.getText());
    } else if (it->second.getType() == Entity::Type::SPRITE)
    {
      _window.draw(it->second.getSprite());
      std::string direction = it->second.getDirection();
      if (direction == "left" || direction == "right")
      {
        float speed = it->second.getSpeed();
        if (direction == "left")
        {
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

void DisplaySFML::handleEvent(UDPClient *_udpClient, TCPClientImpl *_client)
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
                evt.ACTION_NAME = ACTION::FLIP;
                evt.body = playerId;
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
            evt.ACTION_NAME = ACTION::LEFT;
            evt.body = playerId;
            _udpClient->sendEvent(evt);
            _event_indicator = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            evt.ACTION_NAME = ACTION::RIGHT;
            evt.body = playerId;
            _udpClient->sendEvent(evt);
            _event_indicator = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            evt.ACTION_NAME = ACTION::UP;
            evt.body = playerId;
            _udpClient->sendEvent(evt);
            _event_indicator = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            evt.ACTION_NAME = ACTION::DOWN;
            evt.body = playerId;
            _udpClient->sendEvent(evt);
            _event_indicator = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            evt.ACTION_NAME = ACTION::SHOOT;
            evt.body = playerId;
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
            evt.ACTION_NAME = ACTION::SHIELD;
            evt.body = playerId;
            _udpClient->sendEvent(evt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            evt.ACTION_NAME = ACTION::LAUNCH;
            evt.body_size = playerId.size();
            evt.body = playerId;
            _udpClient->sendEvent(evt);
        }
    }
}

void DisplaySFML::update(std::map<int, Entity>* _entities, UDPClient *_udpClient)
{
    _window.clear();
    draw(_entities);
    animate(_entities);
    _window.setView(_view);
    _window.display();
    for (auto it = _entities->begin(); it != _entities->end();)
    {
        (*it).second.update();
        if ((*it).second.isDead())
        {
            Event evt;
            evt.ACTION_NAME = ACTION::DEAD;
            evt.body = std::to_string((*it).first);
            _udpClient->sendEvent(evt);
            it = _entities->erase(it);
        }
        else
            it++;
    }
}

void DisplaySFML::run(std::map<int, Entity>* _entities, UDPClient *_udpClient, TCPClientImpl *_client)
{
    while (_window.isOpen())
    {
        if (_client->Incoming().empty() == false)
        {
            auto msg = _client->Incoming().pop_front().msg;
            _client->HandleMessage(msg);
        }
        handleEvent(_udpClient, _client);
        update(_entities, _udpClient);
    }
}
