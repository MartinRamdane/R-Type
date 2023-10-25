/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** EntitySDL.cpp
*/

#include "EntitySDL.hpp"

EntitySDL::EntitySDL()
{
    ;
}

void EntitySDL::setTexture(const std::string &path)
{
    if (_texture)
    {
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
    }

    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface)
    {
        _texture = SDL_CreateTextureFromSurface(_renderer, surface);
        _textureWidth = surface->w;
        _textureHeight = surface->h;
        SDL_FreeSurface(surface);
    }
    // Gérer les erreurs si nécessaire
}

void EntitySDL::setSprite()
{
    ;
}

void EntitySDL::setSpriteScale(const SDL_Rect &scale)
{
    _sprite.w = _sprite.w * scale.w;
    _sprite.h = _sprite.h * scale.h;
}

void EntitySDL::setSpritePosition(const SDL_Rect &pos)
{
    _oldPosY = _sprite.y;
    _sprite.x = pos.x;
    _sprite.y = pos.y;
}

void EntitySDL::setSpriteRotation(const double &rotation)
{
    // En SDL, vous pouvez ajuster la rotation lors du rendu avec SDL_RenderCopyEx
    SDL_RenderCopyEx(_renderer, _texture, nullptr, &_sprite, rotation, nullptr, SDL_FLIP_NONE);
}

void EntitySDL::setRect(int nb, int init_rect)
{
    _nbRect = nb;
    _init_rect = init_rect;
    int width = _textureWidth / nb;
    _sprite.w = width;
    _sprite.h = _textureHeight;
    _sprite.x = init_rect * width;
    _sprite.y = 0;
}

void EntitySDL::animateSprite(const int ei, const int framerate)
{
    // Vous devrez implémenter l'animation en fonction de votre structure de texture SDL
    // Cela peut nécessiter de déplacer la source de texture en ajustant le SDL_Rect
    // en fonction du temps et de la vitesse de l'animation.
}

void EntitySDL::setInitPos()
{
    // Vous devrez également implémenter cette fonction en fonction de votre logique spécifique
}

SDL_Texture* EntitySDL::getTexture() const
{
    return _texture;
}

SDL_Rect EntitySDL::getSpritePosition() const
{
    return _spriteRect;
}

int EntitySDL::getRect() const
{
    return _nbRect;
}

bool EntitySDL::isDead() const
{
    // Vous devrez implémenter cette fonction en fonction de votre logique spécifique
    return false;
}

void EntitySDL::setTextString(std::string str)
{
    // Vous devrez implémenter cette fonction en fonction de votre logique spécifique
}

void EntitySDL::setFont(const std::string &fontPath, int fontSize)
{
    // Vous devrez implémenter cette fonction en fonction de votre logique spécifique
}

void EntitySDL::setTextPosition(SDL_Rect pos)
{
    // Vous devrez implémenter cette fonction en fonction de votre logique spécifique
}

SDL_Texture* EntitySDL::getTextTexture() const
{
    // Vous devrez implémenter cette fonction en fonction de votre logique spécifique
    return nullptr;
}

void EntitySDL::setTextInfo(int size, std::string color)
{
    // Vous devrez implémenter cette fonction en fonction de votre logique spécifique
}

void EntitySDL::update()
{
    // Vous devrez implémenter cette fonction en fonction de votre logique spécifique
}

void EntitySDL::flip()
{
    // Vous devrez implémenter cette fonction en fonction de votre logique spécifique
}

void EntitySDL::setHit(bool touch)
{
    // Vous devrez implémenter cette fonction en fonction de votre logique spécifique
}

bool EntitySDL::getHit() const
{
    // Vous devrez implémenter cette fonction en fonction de votre logique spécifique
    return false;
}

void EntitySDL::setSpeed(float speed)
{
    // Vous devrez implémenter cette fonction en fonction de votre logique spécifique
}

float EntitySDL::getSpeed() const
{
    // Vous devrez implémenter cette fonction en fonction de votre logique spécifique
    return 0;
}

void EntitySDL::setNextPos(SDL_Rect pos)
{
    // Vous devrez implémenter cette fonction en fonction de votre logique spécifique
}

SDL_Rect EntitySDL::getNextPos() const
{
    // Vous devrez implémenter cette fonction en fonction de votre logique spécifique
    return SDL_Rect();
}

void EntitySDL::setDirection(std::string direction)
{
    // Vous devrez implémenter cette fonction en fonction de votre logique spécifique
}

std::string EntitySDL::getDirection()
{
    // Vous devrez implémenter cette fonction en fonction de votre logique spécifique
    return std::string();
}

EntitySDL::EntitySDL(SDL_Renderer* renderer)
{
    _renderer = renderer;
}

EntitySDL::~EntitySDL()
{
    if (_texture)
        SDL_DestroyTexture(_texture);
}

