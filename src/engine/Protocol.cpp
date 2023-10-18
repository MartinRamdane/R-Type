/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Protocol
*/

#include "Protocol.hpp"

Protocol::Protocol()
{
}

Protocol::~Protocol()
{
}

std::string Protocol::transformEntityCreateToProtocol(std::shared_ptr<IEntity> entity)
{
    auto pos = entity->getPosition();
    auto scale = entity->getScale();
    return "ecreate " + std::to_string(entity->getId()) + " " + std::to_string(std::get<0>(pos)) + " " + std::to_string(std::get<1>(pos)) + " " + entity->getPath() + " " + std::to_string(std::get<0>(scale)) + " " + std::to_string(std::get<1>(scale)) + " " + entity->getSpriteJsonFileName() + " " + entity->getSpriteConfigJsonObjectName() + " " + std::to_string(entity->getSpeed());
}

std::string Protocol::transformEntityMoveToProtocol(std::shared_ptr<IEntity> entity)
{
    const auto pos = entity->getPosition();
    const auto oldPos = entity->getOldPosition();
    if (std::get<0>(pos) != std::get<0>(oldPos) || std::get<1>(pos) != std::get<1>(oldPos))
        return "emove " + std::to_string(entity->getId()) + " " + std::to_string(std::get<0>(pos)) + " " + std::to_string(std::get<1>(pos));
    return "";
}

std::vector<std::string> Protocol::transformEntitiesToProtocol(std::list<EntityType<IEntity> *> entities)
{
    std::vector<std::string> protocol;
    for (auto entityType : entities)
    {
        for (auto entity : entityType->getEntities())
        {
            if (!entity->isCreated())
            {
                protocol.push_back(transformEntityCreateToProtocol(entity));
                entity->setCreated(true);
            }
            if (entity->isDead())
            {
                protocol.push_back("edead " + std::to_string(entity->getId()));
            }
            if (entity->isFlip())
            {
                protocol.push_back("eflip " + std::to_string(entity->getId()));
                entity->setFlip(false);
            }
            std::string move = transformEntityMoveToProtocol(entity);
            if (move != "")
                protocol.push_back(move);
        }
        entityType->removeDead();
    }
    return protocol;
}

std::string Protocol::transformWindowCreateToProtocol(std::string title, int width, int height)
{
    return "wcreate " + title + " " + std::to_string(width) + " " + std::to_string(height);
}

std::vector<std::string> Protocol::transformAllEntitiesToCreate(std::list<EntityType<IEntity> *> entities)
{
    std::vector<std::string> protocol;
    for (auto entityType : entities)
    {
        for (auto entity : entityType->getEntities())
        {
            protocol.push_back(transformEntityCreateToProtocol(entity));
            if (entity->getDirection() == IEntity::Direction::LEFT)
                protocol.push_back("eflip " + std::to_string(entity->getId()));
        }
    }
    return protocol;
}