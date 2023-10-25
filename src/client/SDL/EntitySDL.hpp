/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** EntitySDL.hpp
*/

#pragma once
#include "../IEntity.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class EntitySDL: public IEntity
{
public:
    enum Type
    {
        SPRITE,
        TEXT,
    };

    EntitySDL(SDL_Renderer* renderer);
    ~EntitySDL();
    void setTexture(const std::string &path) override;
    void setSprite() override;
    void setSpriteScale(const SDL_Rect &scale) override;
    void setSpritePosition(const SDL_Rect &pos) override;
    void setSpriteRotation(const double &rotation) override;
    void setRect(int nb, int init_rect = 0) override;
    void animateSprite(const int ei, const int framerate) override;
    void setInitPos() override;
    SDL_Texture* getTexture() const;
    SDL_Rect getSpritePosition() const;
    int getRect() const;
    int getOldPosY() const { return _oldPosY; };
    void setOldPosY(int pos) { _oldPosY = pos; };
    std::string getEventForm() const { return _event_form; };
    void setEventForm(std::string form) { _event_form = form; };
    int getNbRect() const { return _nbRect; };
    void setNbRect(int nbRect) { _nbRect = nbRect; };
    std::string getObjectType() const { return _object_type; };
    void setObjectType(std::string type) { _object_type = type; };
    bool isDead() const;
    Type getType() const { return _type; };
    void setTextString(std::string str) override;
    void setFont(const std::string &fontPath, int fontSize);
    void setTextPosition(SDL_Rect pos);
    SDL_Texture* getTextTexture() const;
    void setType(Type type) override { _type = type; };
    void setTextInfo(int size, std::string color);
    void setSpeed(float speed) override { this->speed = speed; };
    float getSpeed() const { return speed; };
    void setNextPos(SDL_Rect pos) override { _nextPos = pos; };
    SDL_Rect getNextPos() const { return _nextPos; };
    void setDirection(std::string direction) override { _direction = direction; };
    std::string getDirection() { return _direction; };
    void update() override;
    void flip() override;
    void setHit(bool touch) override { _isHit = touch; };
    bool getHit() const override { return _isHit; };

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
