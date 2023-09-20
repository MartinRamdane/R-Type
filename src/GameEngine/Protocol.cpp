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

std::vector<std::string> Protocol::transformEntityInitToProtocol(std::list<EntityType<IEntity> *> entities)
{
    std::vector<std::string> protocol;
    int i = 0;
    for (auto entityType : entities)
    {
        for (auto entity : entityType->getEntities())
        {
            auto pos = entity->getPosition();
            auto scale = entity->getScale();
            protocol.push_back("ecreate " + std::to_string(i) + " " + entity->getPath() + " " + std::to_string(std::get<0>(pos)) + " " + std::to_string(std::get<1>(pos)) + " " + std::to_string(entity->getRotation()) + " " + std::to_string(std::get<0>(scale)) + " " + std::to_string(std::get<1>(scale)));
            i++;
        }
    }
    return protocol;
}