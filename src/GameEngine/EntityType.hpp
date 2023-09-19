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

template <class T>
class EntityType
{
public:
    EntityType();
    ~EntityType();

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
    void updateAll()
    {
        for (auto &entity : entities)
            entity->update("");
    }

protected:
private:
    std::list<std::shared_ptr<T>> entities;
};
