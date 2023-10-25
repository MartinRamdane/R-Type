/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Sprite.hpp
*/

#pragma once
#include "../IEntity.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <memory>
#include <iostream>
#include <string>

class Entity: public IEntity
{
public:
    Entity();
    ~Entity();
    void setTexture(const std::string& path);
    void setSpriteScale(float scaleX, float scaleY);
    void setSpritePosition(float x, float y);
    std::tuple<float, float> getSpritePosition() const;
    void setSpriteRotation(const float angle);
    void setSpriteOriginToCenter();
    void setRect(int nb, int initRect = 0);
    void animateSprite(const int ei, const int framerate);
    void setInitPos();
    void setTextString(std::string str);
    void setType(int type);
    void setTextInfo(int size, std::string color);
    void setSpeed(float speed);
    void setNextPos(float x, float y);
    void setDirection(std::string direction);
    void update();
    void flip();
    void setHit(bool touch);
    bool isDead() const;
    void setEventForm(std::string form);
    void setObjectType(std::string type);
    sf::Color getColor(std::string color);

public:
    sf::Sprite _sprite;
    std::shared_ptr<sf::Texture> _texture;
    int _nbRect;
    int _initRect;
    std::string _direction;
    sf::Clock _clock;
    std::string _eventForm;
    std::string _objectType;
    int _oldPosY;
    Type _type;
    sf::Text _text;
    sf::Font _font;
    float _speed;
    sf::Vector2f _nextPos;
    bool _isHit = false;
};

// ecreate id x y text size color