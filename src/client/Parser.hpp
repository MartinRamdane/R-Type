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
#include "IEntity.hpp"
#include "RessourceManager.hpp"
#include "../global/JsonParser.hpp"
#include "../global/EventHandler.hpp"

class Parser
{
public:
    Parser();
    ~Parser();
    bool findEntity(int id);
    IEntity loadTexture(IEntity entity, std::string path, RessourceManager &ressourceManager);
    std::tuple<int, IEntity> addEntity(std::map<std::string, std::string> value, RessourceManager &ressourceManager);
    std::tuple<int, IEntity> addEntityText(std::map<std::string, std::string> value);
    std::tuple<int, IEntity> removeEntity(std::map<std::string, std::string> value);
    void updateEntity(std::map<std::string, std::string> value);
    std::tuple<int, IEntity> modifyPosEntity(std::map<std::string, std::string> value);
    void getConfig(std::string path, std::string type, IEntity *entity);
    std::string setKey(std::string key, int i);
    std::string setKeyText(std::string key, int i);
    std::tuple<int, IEntity> parseMessage(Event evt, RessourceManager &ressourceManager);
    std::tuple<int, IEntity> hitEntity(std::map<std::string, std::string> value);

    

};