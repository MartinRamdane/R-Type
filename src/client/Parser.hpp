/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Parser.hpp
*/

#pragma once
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <sstream>
#include "Entity.hpp"
#include "RessourceManager.hpp"
#include "../global/JsonParser.hpp"
#include "../global/EventHandler.hpp"
#include "../global/StructsMessages.hpp"

class Parser
{
public:
    Parser();
    ~Parser();
    bool findEntity(int id);
    Entity loadTexture(Entity entity, std::string path, RessourceManager &ressourceManager);
    std::tuple<int, Entity> addEntity(SpriteConfig config, RessourceManager &ressourceManager);
    std::tuple<int, Entity> addEntityText(std::map<std::string, std::string> value); //TODO : REIMPLEMENT TEXT
    std::tuple<int, Entity> removeEntity(ActionConfig config);
    void updateEntity(std::map<std::string, std::string> value);
    std::tuple<int, Entity> modifyPosEntity(MoveConfig config);
    void getConfig(std::string path, std::string type, Entity *entity);
    std::string setKey(std::string key, int i);
    std::string setKeyText(std::string key, int i);
    std::tuple<int, Entity> parseMessage(Event evt, RessourceManager &ressourceManager);
    std::tuple<int, Entity> hitEntity(std::map<std::string, std::string> value);

public:
};