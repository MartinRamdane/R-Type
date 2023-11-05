/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Sprite.hpp
*/

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <memory>
#include <string>
#include "../IEntity.hpp"
#include "RessourceManagerSDL.hpp"

class EntitySDL : public IEntity {
   public:
    EntitySDL(std::shared_ptr<RessourceManagerSDL> ressourceManager);
    ~EntitySDL();
    void setTexture(const std::string& path);
    void setSpriteScale(float scaleX, float scaleY);
    void setPosition(float x, float y);
    std::tuple<float, float> getSpritePosition() const;
    void setSpriteOriginToCenter();
    void setRect(int nb, int initRect = 0);
    void animateSprite(const int ei, const float framerate);
    void setInitPos();
    void setTextString(std::string str);
    void setType(IEntity::Type type);
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
    SDL_Color getColor(std::string color);
    IEntity::Type getType() const;
    void makePrediction();
    std::string getEventForm() const;
    void setFont();
    void draw(SDL_Renderer* renderer);
    void setSound(const std::string& path);

   public:
    SDL_Texture* _texture;
    SDL_Rect _destRect;
    SDL_Rect _animRect;
    SDL_Point _center;
    int _centerX;
    int _centerY;
    int _nbRect;
    int _initRect;
    int _textureWidth;
    int _textureHeight;
    std::string _direction;
    Uint64 _clock;
    std::string _eventForm;
    std::string _objectType;
    int _oldPosY;
    IEntity::Type _type;
    // sf::Text _text;
    TTF_Font* _font;
    float _speed;
    std::tuple<float, float> _nextPos;
    bool _isHit = false;
    std::shared_ptr<RessourceManagerSDL> _ressourceManager;
    float _scaleX;
    float _scaleY;
    unsigned int _framerate;
    unsigned int _framedelay;
    double _delta;
    bool _flip = false;
    std::string _text;
    std::string _textColor;
    int _size;
    SDL_Surface* _surface;
    SDL_Texture* _textureText;
    SDL_Rect _textRect;
    int _x, _y;
};