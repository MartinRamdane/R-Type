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
#include "../global/StructsMessages.hpp"
#include "r-type/Enemy.hpp"

class Protocol
{
public:
    Protocol();
    ~Protocol();

    static SpriteConfig transformEntityCreateToProtocol(std::shared_ptr<IEntity> entity);
    static MoveConfig transformEntityMoveToProtocol(std::shared_ptr<IEntity> entity);
    static void sendEntitiesToServer(std::list<EntityType<IEntity> *> entities, UDPServer *server);
    static void sendWindowCreate(std::string title, int width, int height, UDPServer *server);
    static void sendAllEntitiesToCreate(std::list<EntityType<IEntity> *> entities, UDPServer *server, std::vector<Client>::iterator client);

protected:
private:
};
