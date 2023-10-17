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
#include "../server/UDPServer.hpp"

class Protocol
{
public:
    Protocol();
    ~Protocol();

    static std::string transformEntityCreateToProtocol(std::shared_ptr<IEntity> entity);
    static std::string transformEntityMoveToProtocol(std::shared_ptr<IEntity> entity);
    static void transformEntitiesToProtocol(std::list<EntityType<IEntity> *> entities, UDPServer *server);
    static std::string transformWindowCreateToProtocol(std::string title, int width, int height);
    static std::vector<std::string> transformAllEntitiesToCreate(std::list<EntityType<IEntity> *> entities);

protected:
private:
};
