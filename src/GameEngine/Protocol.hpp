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

class Protocol
{
public:
    Protocol();
    ~Protocol();

    static std::vector<std::string> transformEntityInitToProtocol(std::list<EntityType<IEntity> *> entities);

protected:
private:
};
