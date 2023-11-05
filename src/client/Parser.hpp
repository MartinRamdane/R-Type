/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Parser.hpp
*/

#pragma once
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "../global/EventHandler.hpp"
#include "../global/JsonParser.hpp"
#include "IEntity.hpp"

class Parser {
   public:
    Parser();
    ~Parser();
    bool findEntity(int id);
    IEntity::EntityInfos addEntity(std::map<std::string, std::string> value);
    IEntity::EntityInfos addEntityText(
        std::map<std::string, std::string> value);
    IEntity::EntityInfos removeEntity(std::map<std::string, std::string> value);
    void updateEntity(std::map<std::string, std::string> value);
    IEntity::EntityInfos modifyPosEntity(
        std::map<std::string, std::string> value);
    void getConfig(std::string configpath, std::string type,
                   IEntity::EntityInfos& entityInfos);
    std::string setKey(std::string key, int i);
    std::string setKeyText(std::string key, int i);
    IEntity::EntityInfos parseMessage(Event evt);
    IEntity::EntityInfos hitEntity(std::map<std::string, std::string> value);

   private:
    std::map<std::string, nlohmann::json> _jsons;
};