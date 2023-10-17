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
    return "ecreate " + std::to_string(entity->getId()) + " " + std::to_string(std::get<0>(pos)) + " " + std::to_string(std::get<1>(pos)) + " " + entity->getPath() + " " + std::to_string(entity->getRotation()) + " " + std::to_string(std::get<0>(scale)) + " " + std::to_string(std::get<1>(scale)) + " " + entity->getSpriteJsonFileName() + " " + entity->getSpriteConfigJsonObjectName() + " " + std::to_string(entity->getSpeed());
}

std::string Protocol::transformEntityMoveToProtocol(std::shared_ptr<IEntity> entity)
{
    const auto pos = entity->getPosition();
    const auto oldPos = entity->getOldPosition();
    if (std::get<0>(pos) != std::get<0>(oldPos) || std::get<1>(pos) != std::get<1>(oldPos))
        return "emove " + std::to_string(entity->getId()) + " " + std::to_string(std::get<0>(pos)) + " " + std::to_string(std::get<1>(pos));
    return "";
}

void Protocol::transformEntitiesToProtocol(std::list<EntityType<IEntity> *> entities, UDPServer *server)
{
    for (auto entityType : entities)
    {
        for (auto entity : entityType->getEntities())
        {
            if (!entity->isCreated())
            {
                std::string create = transformEntityCreateToProtocol(entity);
                Event evt;
                evt.ACTION_NAME = ACTION::SPRITE;
                evt.body_size = create.size();
                evt.body = create;
                server->sendEventToAllClients(evt);
                entity->setCreated(true);
            }
            if (entity->isDead())
            {
                std::string dead = "edead " + std::to_string(entity->getId());
                Event evt;
                evt.ACTION_NAME = ACTION::SPRITE;
                evt.body_size = dead.size();
                evt.body = dead;
                server->sendEventToAllClients(evt);
            }
            if (entity->isFlip())
            {
                std::string flip = "eflip " + std::to_string(entity->getId());
                Event evt;
                evt.ACTION_NAME = ACTION::FLIP;
                evt.body_size = flip.size();
                evt.body = flip;
                server->sendEventToAllClients(evt);
                entity->setFlip(false);
            }
            std::string move = transformEntityMoveToProtocol(entity);
            std::cout << "move: " << move << std::endl;
            if (move != "") {
                Event evt;
                evt.ACTION_NAME = ACTION::SPRITE;
                evt.body_size = move.size();
                evt.body = move;
                server->sendEventToAllClients(evt);
            }
        }
        entityType->removeDead();
    }
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