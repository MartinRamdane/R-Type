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

SpriteConfig Protocol::transformEntityCreateToProtocol(std::shared_ptr<IEntity> entity)
{
    auto pos = entity->getPosition();
    auto scale = entity->getScale();
    if (auto test = std::dynamic_pointer_cast<Projectile>(entity))
    {
        auto projectile = std::dynamic_pointer_cast<Projectile>(entity);
        std::string entityDirection;
        projectile->getDirection() == IEntity::Direction::LEFT ? entityDirection = "left" : entityDirection = "right";
        SpriteConfig spriteConfig = {entity->getId(), pos, entity->getPath(), scale, entity->getSpriteJsonFileName(), entity->getSpriteConfigJsonObjectName(), entity->getSpeed(), entityDirection, projectile->getDamage()};
        return spriteConfig;
    }
    if (std::dynamic_pointer_cast<Enemy>(entity))
    {
        auto enemy = std::dynamic_pointer_cast<Enemy>(entity);
        if (enemy->getMovementType() == "Horizontal") {
            return SpriteConfig{entity->getId(), pos, entity->getPath(), scale, entity->getSpriteJsonFileName(), entity->getSpriteConfigJsonObjectName(), entity->getSpeed(), "left", 0};
        }
    }
    return SpriteConfig{entity->getId(), pos, entity->getPath(), scale, entity->getSpriteJsonFileName(), entity->getSpriteConfigJsonObjectName(), entity->getSpeed(), "none", 0};
}

MoveConfig Protocol::transformEntityMoveToProtocol(std::shared_ptr<IEntity> entity)
{
    const auto pos = entity->getPosition();
    const auto oldPos = entity->getOldPosition();
    if (std::dynamic_pointer_cast<Enemy>(entity)) {
        auto enemy = std::dynamic_pointer_cast<Enemy>(entity);
        if (enemy->getMovementType() == "Horizontal") {
            return MoveConfig{-1, pos};
        }
    }
    if ((std::get<0>(pos) != std::get<0>(oldPos) || std::get<1>(pos) != std::get<1>(oldPos)) && !std::dynamic_pointer_cast<Projectile>(entity))
        return MoveConfig{entity->getId(), pos};
    return MoveConfig{-1, pos};
}

void Protocol::sendEntitiesToServer(std::list<EntityType<IEntity> *> entities, UDPServer *server)
{
    for (auto entityType : entities)
    {
        for (auto entity : entityType->getEntities())
        {
            if (!entity->isCreated())
            {
                SpriteConfig spriteConfig = transformEntityCreateToProtocol(entity);
                StructsMessages<SpriteConfig> spriteConfigStruct;
                std::vector<uint8_t> serializedSpriteConfig = spriteConfigStruct.serialize(spriteConfig);
                Event event = {ACTION::CREATE, serializedSpriteConfig.size(), serializedSpriteConfig};
                server->sendEventToAllClients(event);
                entity->setCreated(true);
            }
            if (entity->isDead())
            {
                std::cout << "ENTITY DEAD !!" << std::endl;
                ActionConfig deadConfig = {std::to_string(entity->getId())};
                StructsMessages<ActionConfig> deadConfigStruct;
                std::vector<uint8_t> serializedDeadConfig = deadConfigStruct.serialize(deadConfig);
                Event event = {ACTION::DEAD, serializedDeadConfig.size(), serializedDeadConfig};
                server->sendEventToAllClients(event);
            }
            if (entity->isFlip())
            {
                ActionConfig flipConfig = {std::to_string(entity->getId())};
                StructsMessages<ActionConfig> flipConfigStruct;
                std::vector<uint8_t> serializedFlipConfig = flipConfigStruct.serialize(flipConfig);
                Event event = {ACTION::FLIP, serializedFlipConfig.size(), serializedFlipConfig};
                entity->setFlip(false);
                server->sendEventToAllClients(event);
            }
            MoveConfig move = transformEntityMoveToProtocol(entity);
            if (move.id != -1) {
                StructsMessages<MoveConfig> moveConfigStruct;
                std::vector<uint8_t> serializedMoveConfig = moveConfigStruct.serialize(move);
                Event event = {ACTION::MOVE, serializedMoveConfig.size(), serializedMoveConfig};
                server->sendEventToAllClients(event);
            }
        }
        entityType->removeDead();
    }
}

void Protocol::sendWindowCreate(std::string title, int width, int height, UDPServer *server)
{
    WindowConfig windowConfig = {title, width, height};
    StructsMessages<WindowConfig> windowConfigStruct;
    std::vector<uint8_t> serializedWindowConfig = windowConfigStruct.serialize(windowConfig);
    Event event = {ACTION::WINDOW, serializedWindowConfig.size(), serializedWindowConfig};
    server->sendEventToAllClients(event);
}

void Protocol::sendAllEntitiesToCreate(std::list<EntityType<IEntity> *> entities, UDPServer *server, std::vector<Client>::iterator client)
{
    std::vector<std::string> protocol;
    for (auto entityType : entities)
    {
        for (auto entity : entityType->getEntities())
        {
            std::cout << "entity->getId() : " << entity->getId() << std::endl;
            SpriteConfig spriteConfig = transformEntityCreateToProtocol(entity);
            StructsMessages<SpriteConfig> spriteConfigStruct;
            std::vector<uint8_t> serializedSpriteConfig = spriteConfigStruct.serialize(spriteConfig);
            Event event = {ACTION::CREATE, serializedSpriteConfig.size(), serializedSpriteConfig};
            server->sendEvent(event, client->client.address().to_string(), client->client.port());
            if (entity->getDirection() == IEntity::Direction::LEFT) {
                ActionConfig flipConfig = {std::to_string(entity->getId())};
                StructsMessages<ActionConfig> flipConfigStruct;
                std::vector<uint8_t> serializedFlipConfig = flipConfigStruct.serialize(flipConfig);
                Event event = {ACTION::FLIP, serializedFlipConfig.size(), serializedFlipConfig};
                server->sendEvent(event, client->client.address().to_string(), client->client.port());
            }
        }
    }
}