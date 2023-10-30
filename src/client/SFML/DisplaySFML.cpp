/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** DisplaySFML.cpp
*/

#include "DisplaySFML.hpp"
#include "Entity.hpp"

DisplaySFML::DisplaySFML() {
    _ressourceManager = std::make_shared<RessourceManager>();
}

DisplaySFML::~DisplaySFML() {}

void DisplaySFML::createWindow(std::string name, int x, int y) {
    _window.create(sf::VideoMode(1920, 1080), name);
    _window.setFramerateLimit(60);
    _view = sf::View(sf::FloatRect(0, 0, x, y));
    _window.setView(_view);
}

void DisplaySFML::draw(std::map<int, std::shared_ptr<IEntity>>* _entities) {
    _window.clear();
    std::map<int, std::shared_ptr<IEntity>>::iterator it = _entities->begin();
    while (it != _entities->end()) {
        auto entity = std::dynamic_pointer_cast<Entity>(it->second);
        entity->draw(_window);
        it++;
    }
    _window.display();
}

void DisplaySFML::handleEvent() {
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) {
            _events.push_back("close");
            _window.close();
            closed = true;
        }
        if (_event.type == (sf::Event::KeyPressed)) {
            if (_event.key.code == sf::Keyboard::R)
                _events.push_back("r");
        }
    }
    if (_lastFrameTime.time_since_epoch().count() == 0)
        _lastFrameTime = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - _lastFrameTime)
            .count() > 10) {
        _lastFrameTime = std::chrono::high_resolution_clock::now();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            _events.push_back("left");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            _events.push_back("right");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            _events.push_back("up");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            _events.push_back("down");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            _events.push_back("space");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            _events.push_back("s");
    }
}

std::vector<std::string> DisplaySFML::getEvents() {
    std::vector<std::string> events = _events;
    _events.clear();
    return events;
}

std::shared_ptr<IEntity> DisplaySFML::createEntity(IEntity::EntityInfos entityInfos) {
    if (entityInfos.type == IEntity::Type::SPRITE) {
        return createSprite(entityInfos);
    } else if (entityInfos.type == IEntity::Type::TEXT) {
        return createText(entityInfos);
    } else {
        return nullptr;
    }
}

std::shared_ptr<IEntity> DisplaySFML::createSprite(IEntity::EntityInfos entityInfos) {
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
    entity->setSpriteOriginToCenter();
    return entity;
}

std::shared_ptr<IEntity> DisplaySFML::createText(IEntity::EntityInfos entityInfos) {
    std::shared_ptr<Entity> entity = std::make_shared<Entity>(_ressourceManager);
    entity->setFont();
    entity->setTextString(entityInfos.text);
    entity->setTextInfo(entityInfos.size, entityInfos.color);
    entity->setPosition(entityInfos.x, entityInfos.y);
    entity->setType(entityInfos.type);
    return entity;
}
