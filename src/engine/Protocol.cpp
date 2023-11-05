/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Protocol
*/

#include "Protocol.hpp"

Protocol::Protocol() {}

Protocol::~Protocol() {}

std::string Protocol::transformEntityCreateToProtocol(std::shared_ptr<IEntity> entity) {
    auto pos = entity->getPosition();
    auto scale = entity->getScale();
    if (auto test = std::dynamic_pointer_cast<Projectile>(entity)) {
        auto projectile = std::dynamic_pointer_cast<Projectile>(entity);
        std::string entityDirection;
        switch (projectile->getDirection()) {
            case IEntity::Direction::NONE:
                entityDirection = "none";
                break;
            case IEntity::Direction::UP:
                entityDirection = "up";
                break;
            case IEntity::Direction::DOWN:
                entityDirection = "down";
                break;
            case IEntity::Direction::LEFT:
                entityDirection = "left";
                break;
            case IEntity::Direction::RIGHT:
                entityDirection = "right";
                break;
            case IEntity::Direction::UP_LEFT:
                entityDirection = "up_left";
                break;
            case IEntity::Direction::UP_RIGHT:
                entityDirection = "up_right";
                break;
            case IEntity::Direction::DOWN_LEFT:
                entityDirection = "down_left";
                break;
            case IEntity::Direction::DOWN_RIGHT:
                entityDirection = "down_right";
                break;
            case IEntity::Direction::TRACKING:
                entityDirection = "tracking";
                break;
            case IEntity::Direction::DIRECTIONAL:
                entityDirection = "directional";
                break;
            default:
                entityDirection = "none";
                break;
        }
        return "ecreate " + std::to_string(entity->getId()) + " " +
               std::to_string(std::get<0>(pos)) + " " + std::to_string(std::get<1>(pos)) + " " +
               entity->getPath() + " " + std::to_string(std::get<0>(scale)) + " " +
               std::to_string(std::get<1>(scale)) + " " + entity->getspriteConfigJsonFileName() +
               " " + entity->getSpriteConfigJsonObjectName() + " " +
               std::to_string(entity->getSpeed()) + " " + entityDirection + " " +
               std::to_string(projectile->getDamage());
    }
    if (std::dynamic_pointer_cast<Enemy>(entity)) {
        auto enemy = std::dynamic_pointer_cast<Enemy>(entity);
        if (enemy->getMovementType() == "Linear") {
            return "ecreate " + std::to_string(entity->getId()) + " " +
                   std::to_string(std::get<0>(pos)) + " " + std::to_string(std::get<1>(pos)) + " " +
                   entity->getPath() + " " + std::to_string(std::get<0>(scale)) + " " +
                   std::to_string(std::get<1>(scale)) + " " +
                   entity->getspriteConfigJsonFileName() + " " +
                   entity->getSpriteConfigJsonObjectName() + " " +
                   std::to_string(entity->getSpeed()) + " " + "left";
        }
    }
    return "ecreate " + std::to_string(entity->getId()) + " " + std::to_string(std::get<0>(pos)) +
           " " + std::to_string(std::get<1>(pos)) + " " + entity->getPath() + " " +
           std::to_string(std::get<0>(scale)) + " " + std::to_string(std::get<1>(scale)) + " " +
           entity->getspriteConfigJsonFileName() + " " + entity->getSpriteConfigJsonObjectName() +
           " " + std::to_string(entity->getSpeed()) + " " + "none";
}

std::string Protocol::transformTextCreateToProtocol(std::shared_ptr<IEntity> entity) {
    auto pos = entity->getPosition();
    if (entity->getText() != entity->getOldText() || !entity->isCreated()) {
        return "etext " + std::to_string(entity->getId()) + " " + std::to_string(std::get<0>(pos)) +
               " " + std::to_string(std::get<1>(pos)) + " " + entity->getText() + " " +
               std::to_string(std::get<0>(entity->getScale())) + " white";
    }
    return "";
}

std::string Protocol::transformEntityMoveToProtocol(std::shared_ptr<IEntity> entity) {
    const auto pos = entity->getPosition();
    const auto oldPos = entity->getOldPosition();
    if (std::dynamic_pointer_cast<Enemy>(entity)) {
        auto enemy = std::dynamic_pointer_cast<Enemy>(entity);
        if (enemy->getMovementType() == "Linear") {
            return "";
        }
    }
    IEntity::Direction direction = entity->getDirection();
    if ((std::get<0>(pos) != std::get<0>(oldPos) || std::get<1>(pos) != std::get<1>(oldPos)) ||
        (std::dynamic_pointer_cast<Projectile>(entity) && direction != IEntity::Direction::LEFT &&
         direction != IEntity::Direction::RIGHT && direction != IEntity::Direction::UP &&
         direction != IEntity::Direction::DOWN))
        return "emove " + std::to_string(entity->getId()) + " " + std::to_string(std::get<0>(pos)) +
               " " + std::to_string(std::get<1>(pos));
    return "";
}

std::vector<std::string> Protocol::transformEntitiesToProtocol(
    std::list<EntityType<IEntity>*> entities) {
    std::vector<std::string> protocol;
    for (auto entityType : entities) {
        for (auto entity : entityType->getEntities()) {
            if (entity->isSound()) {
                protocol.push_back("esound " + std::to_string(entity->getId()) + " " +
                                   entity->getPath());
                continue;
            }
            if (entity->getText() != "") {
                std::string text = transformTextCreateToProtocol(entity);
                if (text != "")
                    protocol.push_back(text);
                entity->setCreated(true);
                continue;
            }
            if (!entity->isCreated()) {
                protocol.push_back(transformEntityCreateToProtocol(entity));
                entity->setCreated(true);
            }
            if (entity->isDead()) {
                protocol.push_back("edead " + std::to_string(entity->getId()));
            }
            if (entity->isFlip()) {
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

std::string Protocol::transformWindowCreateToProtocol(std::string title, int width, int height) {
    return "wcreate " + title + " " + std::to_string(width) + " " + std::to_string(height);
}

std::vector<std::string> Protocol::transformAllEntitiesToCreate(
    std::list<EntityType<IEntity>*> entities) {
    std::vector<std::string> protocol;
    for (auto entityType : entities) {
        for (auto entity : entityType->getEntities()) {
            if (entity->isSound()) {
                protocol.push_back("esound " + entity->getPath());
                entity->kill();
            } else if (entity->getText() != "") {
                std::string text = transformTextCreateToProtocol(entity);
                if (text != "")
                    protocol.push_back(text);
                entity->setCreated(true);
            } else {
                protocol.push_back(transformEntityCreateToProtocol(entity));
                if (entity->getDirection() == IEntity::Direction::LEFT)
                    protocol.push_back("eflip " + std::to_string(entity->getId()));
            }
        }
    }
    return protocol;
}

std::string Protocol::getKeyFromBody(std::string body) {
    std::string key = body.substr(0, body.find(" "));
    return key;
}

int Protocol::getIdFromBodyKey(std::string body) {
    std::string id = body.substr(body.find(" ") + 1, body.size());
    return std::stoi(id.substr(1));
}