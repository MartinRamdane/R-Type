/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Protocol
*/

#pragma once
#include <vector>
#include <string>
#include <list>
#include "IEntity.hpp"
#include "EntityType.hpp"
#include <iostream>
#include "r-type/Game.hpp"

struct SpriteConfig
{
    int id;
    std::tuple <float, float> pos;
    std::string path;
    float rotation;
    std::tuple<float, float> scale;
    std::string spriteJsonFileName;
    std::string spriteConfigJsonObjectName;
    float speed;
    std::string direction;
    int damage;
};

class Protocol
{
public:
    Protocol();
    ~Protocol();

    static SpriteConfig transformEntityCreateToProtocol(std::shared_ptr<IEntity> entity);
    static std::string transformEntityMoveToProtocol(std::shared_ptr<IEntity> entity);
    static std::vector<std::string> transformEntitiesToProtocol(std::list<EntityType<IEntity> *> entities);
    static std::string transformWindowCreateToProtocol(std::string title, int width, int height);
    static std::vector<std::string> transformAllEntitiesToCreate(std::list<EntityType<IEntity> *> entities);

protected:
private:
};
