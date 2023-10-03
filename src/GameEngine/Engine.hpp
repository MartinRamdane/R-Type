/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** Engine.hpp
*/

#pragma once
#include <string>
#include <list>
#include <vector>
#include <chrono>
#include <thread>
#include "IEntity.hpp"
#include "EntityType.hpp"
#include "./JsonParser.hpp"

class Engine
{
public:
    Engine();
    ~Engine();
    static Engine *instance;
    template <class E1, class E2>
    void setRelation(std::shared_ptr<EntityType<E1>> &type1, std::shared_ptr<EntityType<E2>> &type2, void (*func)(E1 &self, E2 &target))
    {
        const float radius = type1->getRadius() + type2->getRadius();
        colliders.push_back({type1, type2, radius * radius, reinterpret_cast<void (*)(IEntity &, IEntity &)>(func)});
    }

    void update();
    void addEntityType(EntityType<IEntity> *type);
    void removeEntityType(EntityType<IEntity> *type);
    bool isRunning() const;
    std::list<EntityType<IEntity> *> &getEntities() { return entities; }
    bool frameRateControl();
    void openWindow();
    std::string getWindowTitle() const;
    int getWindowWidth() const;
    int getWindowHeight() const;

private:
    std::list<EntityType<IEntity> *> entities;
    struct Collider
    {
        std::shared_ptr<EntityType<IEntity>> type1;
        std::shared_ptr<EntityType<IEntity>> type2;
        float squaredRadius;
        void (*func)(IEntity &self, IEntity &target);
    };
    std::vector<Collider> colliders;
    bool _isRunning;

    std::chrono::duration<double> _targetFrameDuration;
    std::chrono::high_resolution_clock::time_point _lastFrameTime;
    std::chrono::high_resolution_clock::time_point _currentTime;

    int _width;
    int _height;
    std::string _title;
};
