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
    SDL_QueryTexture(_texture, NULL, NULL, &_textureWidth, &_textureHeight);
    _textureWidth = (_textureWidth / _nbRect) * scaleX;
    _textureHeight = _textureHeight * scaleY;
    std::cout << "width: " << _textureWidth << std::endl;
    std::cout << "height: " << _textureHeight << std::endl;
    _destRect.w = _textureWidth;
    _destRect.h = _textureHeight;
}

void EntitySDL::setPosition(float x, float y) {
    _oldPosY = _destRect.y;
    _destRect.x = x;
    _destRect.y = y;
    // _text.setPosition((sf::Vector2f(x, y)));
}

std::tuple<float, float> EntitySDL::getSpritePosition() const {
    return std::make_tuple(_destRect.x, _destRect.y);
}

void EntitySDL::setSpriteOriginToCenter() {
    _centerX = (_textureWidth / 2);
    _centerY = (_textureHeight / 2);
    _destRect.x -= _centerX;
    _destRect.y -= _centerY;
}

void EntitySDL::setRect(int nb, int initRect) {
    _nbRect = nb;
    _initRect = initRect;
    _animRect.w = _destRect.w;
    _animRect.h = _destRect.h;
    _animRect.x = _animRect.w * _initRect;
    _animRect.y = 0;
}

void EntitySDL::animateSprite(const int ei, const int framerate) {
    if (_type != IEntity::Type::SPRITE)
        return;
    float size = _textureWidth;
    Uint64 end = SDL_GetPerformanceCounter();
    double elapsed = (end - _clock) / (double)SDL_GetPerformanceFrequency();
    if (elapsed > framerate) {
        if (ei == 0) {
            if (_animRect.x == size * (_nbRect - 1))
                _animRect.x = size * _initRect;
            else
                _animRect.x += size;
        } else if (ei == 1) {
            if (_animRect.x != size * (_nbRect - 1))
                _animRect.x += size;
        } else if (ei == 2) {
            if (_animRect.x != 0)
                _animRect.x -= size;
        } else if (ei == 3) {
            if (_animRect.x == size * (_nbRect - 1) || _animRect.x < size * _initRect)
                _animRect.x = size * _initRect - size;
            else
                _animRect.x += size;
        } else if (ei == 4) {
            if (_animRect.x >= size * (_nbRect - 1))
                _animRect.x = size * _initRect;
            else
                _animRect.x += 1;
        }
        _clock = SDL_GetPerformanceCounter();
    }
}

void EntitySDL::setInitPos() {
    float size = _textureWidth;
    Uint64 end = SDL_GetPerformanceCounter();
    double elapsed = (end - _clock) / (double)SDL_GetPerformanceFrequency();
    if (elapsed > 100) {
        if (_animRect.x > size * _initRect)
            _animRect.x -= size;
        else if (_animRect.x < size * _initRect)
            _animRect.x += size;

        _clock = SDL_GetPerformanceCounter();
    }
}

void EntitySDL::setTextString(std::string str) {
    // _text.setString(str);
}

void EntitySDL::setType(IEntity::Type type) {
    _type = type;
}

void EntitySDL::setTextInfo(int size, std::string color) {
    //     _text.setCharacterSize(size);
    //     _text.setFillColor(getColor(color));
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
    if (_type == IEntity::Type::SPRITE)
        makePrediction();
    float nextX = std::get<0>(_nextPos);
    float nextY = std::get<1>(_nextPos);
    if (_destRect.x == nextX && _destRect.y == nextY) {
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
    if (_destRect.y + _speed > nextY && _destRect.y - _speed < nextY)
        _destRect.y = nextY;
    if (_destRect.y > _oldPosY)
        animateSprite(2, 100);
    else if (_destRect.y < _oldPosY)
        animateSprite(1, 100);
}

void EntitySDL::flip() {
    _animRect.w *= -1;
}

void EntitySDL::setHit(bool touch) {
    _isHit = touch;
}

bool EntitySDL::isDead() const {
    if (_eventForm == "once") {
        float size = _textureWidth;
        if (_animRect.x == size * (_nbRect - 1) || _animRect.x < size * _initRect)
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
    // _font.loadFromFile("font/pixel.ttf");
    // _text.setFont(_font);
}

void EntitySDL::draw(SDL_Renderer* renderer, std::shared_ptr<Camera> camera) {
    if (_type == IEntity::Type::SPRITE) {
        // SDL_Rect destRectView;
        // destRectView.x = (_destRect.x - camera.x) * (camera.width / 1920);
        // destRectView.y = (_destRect.y - camera.y) * (camera.height / 1080);
        // destRectView.w = _destRect.w * (camera.width / 1920);
        // destRectView.h = _destRect.h * (camera.height / 1080);
        // SDL_Rect cameraRect = camera->apply(_destRect);
        // SDL_Rect cameraRectAnim = camera->apply(_animRect);
        std::cout << "_destRect.x: " << _destRect.x << std::endl;
        std::cout << "_destRect.y: " << _destRect.y << std::endl;
        std::cout << "_destRect.w: " << _destRect.w << std::endl;
        std::cout << "_destRect.h: " << _destRect.h << std::endl;
        SDL_RenderCopy(renderer, _texture, NULL, &_destRect);
        // exit(0);
    }
    // else if (_type == IEntity::Type::TEXT)
    //     window.draw(_text);
}
