/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Sprite.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <memory>
#include <iostream>
#include <string>

class Entity
{
public:
    Entity();
    ~Entity(){};
    void setTexture(const std::string &path);
    void setSprite();
    void setSpriteScale(const sf::Vector2f &scale);
    void setSpritePosition(const sf::Vector2f &pos);
    void setSpriteOrigin();
    void setSpriteRotation(const float &rotation);
    void setRect(int nb, int init_rect = 0);
    void animateSprite(const int ei, const int framerate);
    void setInitPos();
    sf::Sprite getSprite() const;
    sf::Texture getTexture() const;
    sf::Vector2f getSpritePosition() const;
    int getRect() const;
    int getOldPosY() const { return _oldPosY; };
    void setOldPosY(int pos) { _oldPosY = pos; };
    std::string getEventForm() const { return _event_form; };
    void setEventForm(std::string form) { _event_form = form; };
    int getNbRect() const { return _nbRect; };
    void setNbRect(int nbRect) { _nbRect = nbRect; };
    int getInitRect() const { return _init_rect; };
    std::string getObjectType() const { return _object_type; };
    void setObjectType(std::string type) { _object_type = type; };

public:
    sf::Sprite _sprite;
    std::shared_ptr<sf::Texture> _texture;
    int _nbRect;
    int _init_rect;
    sf::Clock _clock;
    std::string _event_form;
    std::string _object_type;
    int _oldPosY;
};
