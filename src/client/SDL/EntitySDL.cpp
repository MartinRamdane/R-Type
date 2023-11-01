/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Sprite.cpp
*/

#include "EntitySDL.hpp"

EntitySDL::EntitySDL(std::shared_ptr<RessourceManagerSDL> ressourceManager)
    : _ressourceManager(ressourceManager) {
    _clock = SDL_GetPerformanceCounter();
    _framerate = SDL_GetTicks();
    _framedelay = SDL_GetTicks();
    _delta = 0;
}

EntitySDL::~EntitySDL() {}

void EntitySDL::setTexture(const std::string& path) {
    std::map<std::string, SDL_Texture*> textures = _ressourceManager->getTextures();
    std::map<std::string, SDL_Texture*>::iterator it = textures.begin();
    while (it != textures.end()) {
        if (it->first == path) {
            _texture = it->second;
            break;
        }
        it++;
    }
}

void EntitySDL::setSpriteScale(float scaleX, float scaleY) {
    _scaleX = scaleX;
    _scaleY = scaleY;
    SDL_QueryTexture(_texture, NULL, NULL, &_textureWidth, &_textureHeight);
    _textureWidth = _textureWidth / _nbRect;
    _destRect.w = _textureWidth;
    _destRect.h = _textureHeight;
    _animRect.w = _textureWidth;
    _animRect.h = _textureHeight;
    _animRect.x = _animRect.w * (_initRect);
    _animRect.y = 0;
}

void EntitySDL::setPosition(float x, float y) {
    _oldPosY = _destRect.y;
    _destRect.x = x;
    _destRect.y = y;
    _x = x, _y = y;
}

std::tuple<float, float> EntitySDL::getSpritePosition() const {
    return std::make_tuple(_destRect.x, _destRect.y);
}

void EntitySDL::setSpriteOriginToCenter() {
}

void EntitySDL::setRect(int nb, int initRect) {
    _nbRect = nb;
    _initRect = initRect;
}

void EntitySDL::animateSprite(const int ei, const float framerate) {
    if (_type != IEntity::Type::SPRITE)
        return;
    Uint64 end = SDL_GetPerformanceCounter();
    double elapsed = (end - _clock) / (double)SDL_GetPerformanceFrequency();
    float newFramerate = framerate;
    if (framerate <= 100 && framerate > 1)
        newFramerate = framerate - 40;
    if (elapsed > newFramerate / 100) {
        if (ei == 0) {
            if (_animRect.x == _textureWidth * (_nbRect - 1))
                _animRect.x = _textureWidth * _initRect;
            else
                _animRect.x += _textureWidth;
        } else if (ei == 1) {
            if (_animRect.x != _textureWidth * (_nbRect - 1))
                _animRect.x += _textureWidth;
        } else if (ei == 2) {
            if (_animRect.x != 0)
                _animRect.x -= _textureWidth;
        } else if (ei == 3) {
            if (_animRect.x == _textureWidth * (_nbRect - 1) || _animRect.x < _textureWidth * _initRect)
                _animRect.x = _textureWidth * _initRect - _textureWidth;
            else
                _animRect.x += _textureWidth;
        } else if (ei == 4) {
            if (_animRect.x >= _textureWidth * (_nbRect - 1))
                _animRect.x = _textureWidth * _initRect;
            else
                _animRect.x += 1;
        }
        _clock = SDL_GetPerformanceCounter();
    }
}

void EntitySDL::setInitPos() {
    Uint64 end = SDL_GetPerformanceCounter();
    double elapsed = (end - _clock) / (double)SDL_GetPerformanceFrequency();
    if (elapsed > 0.1) {
        if (_animRect.x > _textureWidth * _initRect)
            _animRect.x -= _textureWidth;
        else if (_animRect.x < _textureWidth * _initRect)
            _animRect.x += _textureWidth;

        _clock = SDL_GetPerformanceCounter();
    }
}

void EntitySDL::setTextString(std::string str) {
    _text = str;
}

void EntitySDL::setType(IEntity::Type type) {
    _type = type;
}

void EntitySDL::setTextInfo(int size, std::string color) {
    _size = size;
    _textColor = color;
}

void EntitySDL::setSpeed(float speed) {
    _speed = speed;
}

void EntitySDL::setNextPos(float x, float y) {
    _nextPos = std::make_tuple(x, y);
}

void EntitySDL::setDirection(std::string direction) {
    _direction = direction;
}

void EntitySDL::update() {
    _framerate = SDL_GetTicks();
    _delta = _framerate - _framedelay;
    if (_delta > 1000/60.0)
    {
        _framedelay = _framerate;
        if (_type == IEntity::Type::SPRITE)
            makePrediction();
        float nextX = std::get<0>(_nextPos);
        float nextY = std::get<1>(_nextPos);
        if ((_destRect.x == nextX && _destRect.y == nextY) && _animRect.x != (_textureWidth * _initRect)) {
            if (_eventForm == "event")
                setInitPos();
            return;
        }
        if (_destRect.x < nextX)
            _destRect.x += _speed;
        else if (_destRect.x > nextX)
            _destRect.x -= _speed;
        if (_destRect.y < nextY) {
            _destRect.y += _speed;
            if (_eventForm == "event")
                animateSprite(2, 100);
        } else if (_destRect.y > nextY) {
            _destRect.y -= _speed;
            if (_eventForm == "event")
                animateSprite(1, 100);
        }
        if (_destRect.x + _speed > nextX && _destRect.x - _speed < nextX)
            _destRect.x = nextX;
        if (_destRect.y + _speed > nextY && _destRect.y - _speed < nextY) {
            _destRect.y = nextY;
            _oldPosY = _destRect.y;
        }
        if (_destRect.y > _oldPosY && _eventForm == "event")
            animateSprite(2, 50);
        else if (_destRect.y < _oldPosY && _eventForm == "event")
            animateSprite(1, 50);
    }
}

void EntitySDL::flip() {
    _flip = !_flip;
}

void EntitySDL::setHit(bool touch) {
    _isHit = touch;
}

bool EntitySDL::isDead() const {
    if (_eventForm == "once") {
        if (_animRect.x == _textureWidth * (_nbRect - 1) || _animRect.x < _textureWidth * _initRect)
            return true;
    }
    return false;
}

void EntitySDL::setEventForm(std::string form) {
    _eventForm = form;
}

void EntitySDL::setObjectType(std::string type) {
    _objectType = type;
}

SDL_Color EntitySDL::getColor(std::string color) {
    if (color == "red")
        return {255, 0, 0, 255};
    if (color == "blue")
        return {0, 0, 255, 255};
    if (color == "green")
        return {0, 255, 0, 255};
    if (color == "white")
        return {255, 255, 255, 255};
    if (color == "black")
        return {0, 0, 0, 255};
    if (color == "yellow")
        return {255, 255, 0, 255};
    if (color == "magenta")
        return {255, 0, 255, 255};
    if (color == "cyan")
        return {0, 255, 255, 255};
    return {0, 0, 0, 255};
}

IEntity::Type EntitySDL::getType() const {
    return _type;
}

void EntitySDL::makePrediction() {
    if (_direction == "left" || _direction == "right") {
        float speed = _speed;
        if (_direction == "left") {
            speed = _speed * -1;
        }
        _nextPos = std::make_tuple(_destRect.x + speed, _destRect.y);
    }
}

std::string EntitySDL::getEventForm() const {
    return _eventForm;
}

void EntitySDL::setFont() {
    _font = TTF_OpenFont("font/pixel.ttf", _size);

}

void EntitySDL::draw(SDL_Renderer* renderer) {
    if (_type == IEntity::Type::SPRITE) {
        int centerX = _textureWidth / 2;
        int centerY = _textureHeight / 2;
        int newX = _destRect.x - (centerX * _scaleX);
        int newY = _destRect.y - (centerY * _scaleY);
        SDL_Rect destRect = { newX, newY, (int)(_textureWidth * _scaleX), (int)(_textureHeight * _scaleY) };
        SDL_RendererFlip flipArg = _flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        SDL_RenderCopyEx(renderer, _texture, &_animRect, &destRect, 0, NULL, flipArg);
    }
    if (_type == IEntity::Type::TEXT) {
        _surface = TTF_RenderText_Solid(_font, _text.c_str(), getColor(_textColor));
        _textureText = SDL_CreateTextureFromSurface(renderer, _surface);
        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(_textureText, NULL, NULL, &texW, &texH);
        _textRect = { _x, _y, texW, texH };
        SDL_RenderCopy(renderer, _textureText, NULL, &_textRect);
    }
}

