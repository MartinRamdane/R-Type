/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** EntityType
*/

#pragma once
#include <list>
#include <memory>
#include "IEntity.hpp"
#include <iostream>

template <class T>
class EntityType
{
public:
    EntityType(float radius);
    ~EntityType();
    EntityType(const EntityType &cpy) = default;
    EntityType &operator=(const EntityType &src) = default;

    void insert(std::shared_ptr<T> entity)
    {
        entities.push_back(entity);
    }
    template <class T2>
    void collideAll(std::shared_ptr<EntityType<T2>> &t2, float radius, void (*func)(IEntity &, IEntity &))
    {
        for (auto &target : t2->entities)
        {
            const float x2 = std::get<0>(target->getPosition());
            const float y2 = std::get<1>(target->getPosition());
            for (auto &self : entities)
            {
                const float x = x2 - std::get<0>(self->getPosition());
                const float y = y2 - std::get<1>(self->getPosition());
                if (x * x + y * y < radius && self != target)
                    func(*self, *target);
            }
        }
    }
    float getRadius() const { return _radius; }
    void updateAll()
    {
        for (auto &entity : entities)
            entity->update();
    }
    void removeDead()
    {
        entities.remove_if([](std::shared_ptr<T> entity) { return entity->isDead(); });
    }
    std::list<std::shared_ptr<T>> &getEntities() { return entities; }

protected:
private:
    std::list<std::shared_ptr<T>> entities;
    const float _radius;
};
