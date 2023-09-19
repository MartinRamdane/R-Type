/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** EntityType
*/

#include "EntityType.hpp"
#include "Engine.hpp"

template <class T>
EntityType<T>::EntityType(float radius) : _radius(radius)
{
    Engine::instance->addEntityType(this);
}

template <class T>
EntityType<T>::~EntityType()
{
    Engine::instance->removeEntityType(this);
}

template class EntityType<IEntity>;