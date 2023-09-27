/*
** EPITECH PROJECT, 2023
** Engine.cpp
** File description:
** Engine
*/

#include "Engine.hpp"

Engine *Engine::instance = nullptr;

Engine::Engine()
{
    instance = this;
    _isRunning = true;
    openWindow();

    // Create clock
    _targetFrameDuration = std::chrono::duration<double>(1.0 / 60.0);
    _lastFrameTime = std::chrono::high_resolution_clock::now();
    _currentTime = _lastFrameTime;
}

Engine::~Engine()
{
    instance = nullptr;
    _isRunning = false;
}

void Engine::update()
{
    for (auto &collider : colliders)
        collider.type1->collideAll(collider.type2, collider.squaredRadius, collider.func);
    for (auto &entity : entities)
        entity->updateAll();
}

void Engine::addEntityType(EntityType<IEntity> *type)
{
    entities.push_back(type);
}

void Engine::removeEntityType(EntityType<IEntity> *type)
{
    entities.remove(type);
}

bool Engine::isRunning() const
{
    return _isRunning;
}

bool Engine::frameRateControl()
{
    // Calculate delta time
    _currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime = _currentTime - _lastFrameTime;

    if (elapsedTime >= _targetFrameDuration)
    {
        // Update last frame time
        _lastFrameTime = _currentTime;

        return true;
    }

    // Sleep to control the frame rate
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    return false;
}

void Engine::openWindow()
{
    JsonParser parser;
    nlohmann::json windowConfig = JsonParser::readFile("WindowConfig.json");
    _width = parser.get<int>(windowConfig, "Window.Width");
    _height = parser.get<int>(windowConfig, "Window.Height");
    _title = parser.get<std::string>(windowConfig, "Window.Title");
}

std::string Engine::getWindowTitle() const
{
    return _title;
}

int Engine::getWindowWidth() const
{
    return _width;
}

int Engine::getWindowHeight() const
{
    return _height;
}
