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
    std::cout << "ecreate " + std::to_string(entity->getId()) + " " + std::to_string(std::get<0>(pos)) + " " + std::to_string(std::get<1>(pos)) + " " + entity->getPath() + " " + std::to_string(entity->getRotation()) + " " + std::to_string(std::get<0>(scale)) + " " + std::to_string(std::get<1>(scale)) + " " + entity->getSpriteConfigJsonPath() + " " + entity->getSpriteConfigJsonObjectName() << std::endl;
    return "ecreate " + std::to_string(entity->getId()) + " " + std::to_string(std::get<0>(pos)) + " " + std::to_string(std::get<1>(pos)) + " " + entity->getPath() + " " + std::to_string(entity->getRotation()) + " " + std::to_string(std::get<0>(scale)) + " " + std::to_string(std::get<1>(scale)) + " " + entity->getSpriteConfigJsonPath() + " " + entity->getSpriteConfigJsonObjectName();
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
            else if (entity->isDead())
            {
                protocol.push_back("edead " + std::to_string(entity->getId()));
            }
            else
            {

                std::string move = transformEntityMoveToProtocol(entity);
                if (move != "")
                    protocol.push_back(move);
            }
        }
    }
    return protocol;
}

Game::Event Protocol::transformProtocolToEvent(std::string event)
{
    if (event == "LEFT")
        return Game::Event::LEFT;
    if (event == "RIGHT")
        return Game::Event::RIGHT;
    if (event == "UP")
        return Game::Event::UP;
    if (event == "DOWN")
        return Game::Event::DOWN;
    if (event == "SHOOT")
        return Game::Event::SHOOT;
    if (event == "QUIT")
        return Game::Event::QUIT;
    if (event == "SHIELD")
        return Game::Event::SHIELD;
    return Game::Event::UNKNOWN;
}

std::string Protocol::transformWindowCreateToProtocol(std::string title, int width, int height)
{
    return "wcreate " + title + " " + std::to_string(width) + " " + std::to_string(height);
}
