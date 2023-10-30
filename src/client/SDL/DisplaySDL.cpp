/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** DisplaySDL.cpp
*/

#include "DisplaySDL.hpp"
#include "EntitySDL.hpp"

DisplaySDL::DisplaySDL() {
    _ressourceManager = std::make_shared<RessourceManagerSDL>();
}

DisplaySDL::~DisplaySDL() {}

void DisplaySDL::createWindow(std::string name, int x, int y) {
    _window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 10,
                               SDL_WINDOW_SHOWN);
    _renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    _camera = {0, 0, x, y};
}

void DisplaySDL::draw(std::map<int, std::shared_ptr<IEntity>>* _entities) {
    _window.clear();
    std::map<int, std::shared_ptr<IEntity>>::iterator it = _entities->begin();
    while (it != _entities->end()) {
        auto entity = std::dynamic_pointer_cast<EntitySDL>(it->second);
        entity->draw(_renderer, _camera);
        it++;
    }
    _window.display();
}

void DisplaySDL::handleEvent() {
    while (SDL_PollEvent(&_event) != 0) {
        if (_event.type == SDL_QUIT) {
            _events.push_back("close");
            closed = true;
        }
        if (_event.type == SDL_KEYDOWN) {
            if (_event.key.keysym.sym == SDLK_r)
                _events.push_back("r");
        }
    }
    if (_lastFrameTime.time_since_epoch().count() == 0)
        _lastFrameTime = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - _lastFrameTime)
            .count() > 10) {
        _lastFrameTime = std::chrono::high_resolution_clock::now();

        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_LEFT])
            _events.push_back("left");
        if (state[SDL_SCANCODE_RIGHT])
            _events.push_back("right");
        if (state[SDL_SCANCODE_UP])
            _events.push_back("up");
        if (state[SDL_SCANCODE_DOWN])
            _events.push_back("down");
        if (state[SDL_SCANCODE_SPACE])
            _events.push_back("space");
        if (state[SDL_SCANCODE_S])
            _events.push_back("s");
    }
}

std::vector<std::string> DisplaySDL::getEvents() {
    std::vector<std::string> events = _events;
    _events.clear();
    return events;
}

std::shared_ptr<IEntity> DisplaySDL::createEntity(IEntity::EntityInfos entityInfos) {
    if (entityInfos.type == IEntity::Type::SPRITE)
        return createSprite(entityInfos);
    return createText(entityInfos);
}

std::shared_ptr<IEntity> DisplaySDL::createSprite(IEntity::EntityInfos entityInfos) {
    std::shared_ptr<EntitySDL> entity = std::make_shared<EntitySDL>(_ressourceManager);
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

std::shared_ptr<IEntity> DisplaySDL::createText(IEntity::EntityInfos entityInfos) {
    std::shared_ptr<EntitySDL> entity = std::make_shared<EntitySDL>(_ressourceManager);
    entity->setFont();
    entity->setTextString(entityInfos.text);
    entity->setTextInfo(entityInfos.size, entityInfos.color);
    entity->setPosition(entityInfos.x, entityInfos.y);
    entity->setType(entityInfos.type);
    return entity;
}
