/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** EntityType
*/

#pragma once
#include "Engine.hpp"

template <class T>
class EntityType
{
public:
    EntityType()
    {
        Engine::instance->addEntityType(this);
    }
    ~EntityType()
    {
        Engine::instance->removeEntityType(this);
    }

    void insert(std::shared_ptr<T> entity)
    {
        entities.push_back(entity);
    }
    template <class T2>
    void collideAll(std::shared_ptr<EntityType<T2>> &t2, float radius, void (*func)(Entity &, Entity &))
    {
        for (auto &target : t2->entities)
        {
            const float x2 = target->refX;
            const float y2 = target->refY;
            for (auto &self : entities)
            {
                const float x = x2 - self->refX;
                const float y = y2 - self->refY;
                if (x * x + y * y < radius && self != target)
                    func(*self, *target);
            }
        }
    }
    void updateAll()
    {
        for (auto &entity : entities)
            entity->update();
    }

protected:
private:
    std::list<std::shared_ptr<T>> entities;
};
