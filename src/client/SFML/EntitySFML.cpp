/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Sprite.cpp
*/

#include "EntitySFML.hpp"

EntitySFML::EntitySFML(std::shared_ptr<RessourceManagerSFML> ressourceManager)
    : _ressourceManager(ressourceManager) {
    _clock.restart();
}

EntitySFML::~EntitySFML() {}

void EntitySFML::setTexture(const std::string& path) {
    std::map<std::string, std::shared_ptr<sf::Texture>> textures = _ressourceManager->getTextures();
    std::map<std::string, std::shared_ptr<sf::Texture>>::iterator it = textures.begin();
    while (it != textures.end()) {
        if (it->first == path) {
            _texture = it->second;
            _sprite.setTexture(*_texture);
            break;
        }
        it++;
    }
}

void EntitySFML::setSpriteScale(float scaleX, float scaleY) {
    _sprite.setScale(sf::Vector2f(scaleX, scaleY));
}

void EntitySFML::setPosition(float x, float y) {
    _oldPosY = _sprite.getPosition().y;
    _sprite.setPosition(sf::Vector2f(x, y));
    _text.setPosition((sf::Vector2f(x, y)));
}

std::tuple<float, float> EntitySFML::getSpritePosition() const {
    return std::make_tuple(_sprite.getPosition().x, _sprite.getPosition().y);
}

void EntitySFML::setSpriteOriginToCenter() {
    sf::Vector2f size = sf::Vector2f(_texture->getSize().x / _nbRect, _texture->getSize().y);
    _sprite.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
}

void EntitySFML::setRect(int nb, int initRect) {
    _nbRect = nb;
    _initRect = initRect;
    float size = _texture->getSize().x / nb;
    sf::IntRect rect(0, 0, size, _texture->getSize().y);
    rect.left = size * initRect;
    _sprite.setTextureRect(rect);
}

void EntitySFML::animateSprite(const int ei, const float framerate) {
    if (_type != IEntity::Type::SPRITE)
        return;
    float size = _texture->getSize().x / _nbRect;
    sf::IntRect rect = _sprite.getTextureRect();
    if (_clock.getElapsedTime().asMilliseconds() > framerate) {
        if (ei == 0) {
            if (rect.left == size * (_nbRect - 1))
                rect.left = size * _initRect;
            else
                rect.left += size;
        } else if (ei == 1) {
            if (rect.left != size * (_nbRect - 1))
                rect.left += size;
        } else if (ei == 2) {
            if (rect.left != 0)
                rect.left -= size;
        } else if (ei == 3) {
            if (rect.left == size * (_nbRect - 1) || rect.left < size * _initRect)
                rect.left = size * _initRect - size;
            else
                rect.left += size;
        } else if (ei == 4) {
            if (rect.left >= size * (_nbRect - 1))
                rect.left = size * _initRect;
            else
                rect.left += 1;
        }
        _sprite.setTextureRect(rect);
        _clock.restart();
    }
}

void EntitySFML::setInitPos() {
    float size = _texture->getSize().x / _nbRect;
    sf::IntRect rect = _sprite.getTextureRect();
    if (_clock.getElapsedTime().asMilliseconds() > 100) {
        if (rect.left > size * _initRect)
            rect.left -= size;
        else if (rect.left < size * _initRect)
            rect.left += size;

        _sprite.setTextureRect(rect);
        _clock.restart();
    }
}

void EntitySFML::setTextString(std::string str) {
    _text.setString(str);
}

void EntitySFML::setType(IEntity::Type type) {
    _type = type;
}

void EntitySFML::setTextInfo(int size, std::string color) {
    _text.setCharacterSize(size);
    _text.setFillColor(getColor(color));
}

void EntitySFML::setSpeed(float speed) {
    _speed = speed;
}

void EntitySFML::setNextPos(float x, float y) {
    _nextPos = sf::Vector2f(x, y);
}

void EntitySFML::setDirection(std::string direction) {
    _direction = direction;
}

void EntitySFML::update() {
    if (_type == IEntity::Type::SPRITE)
        makePrediction();
    sf::Vector2f pos = _sprite.getPosition();
    if (pos.x == _nextPos.x && pos.y == _nextPos.y) {
        if (_eventForm == "event")
            setInitPos();
        return;
    }
    if (pos.x < _nextPos.x)
        pos.x += _speed;
    else if (pos.x > _nextPos.x)
        pos.x -= _speed;
    if (pos.y < _nextPos.y) {
        pos.y += _speed;
        if (_eventForm == "event")
            animateSprite(2, 100);
    } else if (pos.y > _nextPos.y) {
        pos.y -= _speed;
        if (_eventForm == "event")
            animateSprite(1, 100);
    }
    if (pos.x + _speed > _nextPos.x && pos.x - _speed < _nextPos.x)
        pos.x = _nextPos.x;
    if (pos.y + _speed > _nextPos.y && pos.y - _speed < _nextPos.y)
        pos.y = _nextPos.y;
    if (_sprite.getPosition().y > _oldPosY)
        animateSprite(2, 100);
    else if (_sprite.getPosition().y < _oldPosY)
        animateSprite(1, 100);
    _sprite.setPosition(pos);
}

void EntitySFML::flip() {
    auto scale = _sprite.getScale();
    scale.x *= -1;
    _sprite.setScale(scale);
}

void EntitySFML::setHit(bool touch) {
    _isHit = touch;
}

bool EntitySFML::isDead() const {
    if (_eventForm == "once") {
        float size = _texture->getSize().x / _nbRect;
        sf::IntRect rect = _sprite.getTextureRect();
        if (rect.left == size * (_nbRect - 1) || rect.left < size * _initRect)
            return true;
    }
    if (_type == IEntity::Type::SOUND && _sound.getStatus() == sf::Sound::Stopped)
        return true;
    return false;
}

void EntitySFML::setEventForm(std::string form) {
    _eventForm = form;
}

void EntitySFML::setObjectType(std::string type) {
    _objectType = type;
}

sf::Color EntitySFML::getColor(std::string color) {
    if (color == "red")
        return sf::Color::Red;
    if (color == "blue")
        return sf::Color::Blue;
    if (color == "green")
        return sf::Color::Green;
    if (color == "white")
        return sf::Color::White;
    if (color == "black")
        return sf::Color::Black;
    if (color == "yellow")
        return sf::Color::Yellow;
    if (color == "magenta")
        return sf::Color::Magenta;
    if (color == "cyan")
        return sf::Color::Cyan;
    return sf::Color::White;
}

IEntity::Type EntitySFML::getType() const {
    return _type;
}

void EntitySFML::makePrediction() {
    if (_direction == "left" || _direction == "right" || _direction == "up" || _direction == "down") {
        float speed = _speed;
        if (_direction == "left" || _direction == "up") {
            speed = _speed * -1;
        }
        sf::Vector2f oldPos = _sprite.getPosition();
        setNextPos(oldPos.x + speed, oldPos.y);
    }
}

std::string EntitySFML::getEventForm() const {
    return _eventForm;
}

void EntitySFML::setFont() {
    _font.loadFromFile("font/pixel.ttf");
    _text.setFont(_font);
}

void EntitySFML::draw(sf::RenderWindow& window) {
    if (_type == IEntity::Type::SPRITE)
        window.draw(_sprite);
    else if (_type == IEntity::Type::TEXT)
        window.draw(_text);
}

sf::Sprite EntitySFML::getSprite() const {
    return _sprite;
}

void EntitySFML::setSound(const std::string& path) {
    std::map<std::string, std::shared_ptr<sf::SoundBuffer>> sounds = _ressourceManager->getSounds();
    std::map<std::string, std::shared_ptr<sf::SoundBuffer>>::iterator it = sounds.begin();
    while (it != sounds.end()) {
        if (it->first == path) {
            _sound.setBuffer(*it->second);
            _sound.play();
            break;
        }
        it++;
    }
}

void EntitySFML::setSpriteColor(sf::Color color) {
    _sprite.setColor(color);
}
