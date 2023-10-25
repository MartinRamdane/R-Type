/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** EntitySDL.hpp
*/

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "../IEntity.hpp"

class EntitySDL : public IEntity
{
   public:
    EntitySDL();
    ~EntitySDL();
    // void setTexture(const std::string& path);
    // void setSpriteScale(float scaleX, float scaleY);
    // void setSpritePosition(float x, float y);
    // std::tuple<float, float> getSpritePosition() const;
    // void setSpriteRotation(const float angle);
    // void setSpriteOriginToCenter();
    // void setRect(int nb, int initRect = 0);
    // void animateSprite(const int ei, const int framerate);
    // void setInitPos();
    // void setTextString(std::string str);
    // void setType(int type);
    // void setTextInfo(int size, std::string color);
    // void setSpeed(float speed);
    // void setNextPos(float x, float y);
    // void setDirection(std::string direction);
    // void update();
    // void flip();
    // void setHit(bool touch);
    // bool isDead() const;
    // void setEventForm(std::string form);
    // void setObjectType(std::string type);

   private:
    SDL_Renderer* _renderer;
    SDL_Texture* _texture;
    SDL_Rect _sprite;
    int _nbRect;
    int _init_rect;
    std::string _direction;
    std::string _event_form;
    std::string _object_type;
    int _oldPosY;
    Type _type;
    float _speed;
    SDL_Rect _nextPos;
    bool _isHit = false;
    int _textureWidth;
    int _textureHeight;
};
