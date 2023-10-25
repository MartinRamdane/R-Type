/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** DisplaySFML.cpp
*/

#include "DisplaySFML.hpp"
#include "Entity.hpp"

DisplaySFML::DisplaySFML()
{
    _eventIndicator = 0;
    _ressourceManager = std::make_shared<RessourceManager>();
    _playerId = 0;
}

DisplaySFML::~DisplaySFML() {}

void DisplaySFML::createWindow(std::string name, int x, int y)
{
  _window.create(sf::VideoMode(1920, 1080), name);
  _window.setFramerateLimit(60);
  _view = sf::View(sf::FloatRect(0, 0, x, y));
  _window.setView(_view);
}

void DisplaySFML::animate(std::map<int, std::shared_ptr<IEntity>> *_entities)
{
  std::map<int, std::shared_ptr<IEntity>>::iterator it = _entities->begin();
  while (it != _entities->end())
  {
    std::cout << "event form: " << it->second->getEventForm() << std::endl;
    if (it->second->getEventForm() == "loop") {
      std::cout << "loop here" << std::endl;
      it->second->animateSprite(0, 60);
    }if (it->second->getEventForm() == "once")
      it->second->animateSprite(3, 60);
    if (it->second->getEventForm() == "event" && _eventIndicator == 0)
      it->second->setInitPos();
    if (it->second->getEventForm() == "paralaxe")
      it->second->animateSprite(4, 1);
    it++;
  }
}

void DisplaySFML::draw(std::map<int, std::shared_ptr<IEntity>> *_entities)
{
  std::map<int, std::shared_ptr<IEntity>>::iterator it = _entities->begin();
  while (it != _entities->end())
  {
    auto entity = std::dynamic_pointer_cast<Entity>(it->second);
    entity->draw(_window);
    if (it->second->getType() == IEntity::Type::SPRITE)
      it->second->makePrediction();
    it++;
  }
}

void DisplaySFML::handleEvent(UDPClient* _udpClient, TCPClientImpl* _client) {
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) {
            _window.close();
            _client->Disconnect();
            closed = true;
        }
        if (_event.type == (sf::Event::KeyPressed)) {
            if (_event.key.code == sf::Keyboard::R) {
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
    if (std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - _lastFrameTime)
            .count() > 10) {
        _lastFrameTime = std::chrono::high_resolution_clock::now();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            evt.ACTION_NAME = ACTION::LEFT;
            evt.body = playerId;
            _udpClient->sendEvent(evt);
            _eventIndicator = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            evt.ACTION_NAME = ACTION::RIGHT;
            evt.body = playerId;
            _udpClient->sendEvent(evt);
            _eventIndicator = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            evt.ACTION_NAME = ACTION::UP;
            evt.body = playerId;
            _udpClient->sendEvent(evt);
            _eventIndicator = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            evt.ACTION_NAME = ACTION::DOWN;
            evt.body = playerId;
            _udpClient->sendEvent(evt);
            _eventIndicator = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            evt.ACTION_NAME = ACTION::SPACE;
            evt.body = playerId;
            _udpClient->sendEvent(evt);
            _eventIndicator = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            _window.close();
            _client->Disconnect();
            closed = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            evt.ACTION_NAME = ACTION::KEY_S;
            evt.body = playerId;
            _udpClient->sendEvent(evt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            evt.ACTION_NAME = ACTION::KEY_L;
            evt.body = playerId;
            _udpClient->sendEvent(evt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            evt.ACTION_NAME = ACTION::KEY_C;
            evt.body = playerId;
            _udpClient->sendEvent(evt);
        }
    }
}

void DisplaySFML::update(std::map<int, std::shared_ptr<IEntity>> *_entities, UDPClient *_udpClient)
{
    _window.clear();
    draw(_entities);
    animate(_entities);
    _window.display();
    for (auto it = _entities->begin(); it != _entities->end();)
    {
        (*it).second->update();
        if ((*it).second->isDead())
        {
            Event evt;
            evt.ACTION_NAME = ACTION::DEAD;
            evt.body = std::to_string((*it).first);
            _udpClient->sendEvent(evt);
            it = _entities->erase(it);
        } else
            it++;
    }
}

std::shared_ptr<IEntity> DisplaySFML::createEntity(IEntity::EntityInfos entityInfos)
{
  if (entityInfos.type == IEntity::Type::SPRITE)
    return createSprite(entityInfos);
  return createText(entityInfos);
}

std::shared_ptr<IEntity> DisplaySFML::createSprite(IEntity::EntityInfos entityInfos)
{
  std::shared_ptr<Entity> entity = std::make_shared<Entity>(_ressourceManager);
  entity->setTexture(entityInfos.path);
  entity->setPosition(entityInfos.x, entityInfos.y);
  entity->setSpriteScale(entityInfos.scaleX, entityInfos.scaleY);
  entity->setRect(entityInfos.nbRect, entityInfos.initRect);
  entity->setNextPos(entityInfos.nextX, entityInfos.nextY);
  entity->setSpeed(entityInfos.speed);
  entity->setDirection(entityInfos.direction);
  entity->setEventForm(entityInfos.eventForm);
  entity->setObjectType(entityInfos.objectType);
  entity->setType(entityInfos.type);
  return entity;
}
  std::shared_ptr<Entity> entity = std::make_shared<Entity>(_ressourceManager);
  entity->setFont();
  entity->setTextString(entityInfos.text);
  entity->setTextInfo(entityInfos.size, entityInfos.color);
  entity->setPosition(entityInfos.x, entityInfos.y);
  entity->setType(entityInfos.type);
  return entity;
}
