/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** parcer.cpp
*/

#include "Parser.hpp"

Parser::Parser() {}

Parser::~Parser() {}

void Parser::getConfig(std::string configpath, std::string type,
                       IEntity::EntityInfos& entityInfos) {
    if (configpath == "null") {
        entityInfos.nbRect = 0;
        entityInfos.initRect = 0;
        entityInfos.eventForm = "none";
        return;
    }
    try {
        JsonParser jsonParser;
        if (_jsons.find(configpath) == _jsons.end())
            _jsons[configpath] = jsonParser.readFile(configpath);
        int nbRect = jsonParser.get<int>(_jsons[configpath], type + ".nb_rect");
        int initRect =
            jsonParser.get<int>(_jsons[configpath], type + ".rect_init");
        entityInfos.nbRect = nbRect;
        entityInfos.initRect = initRect;
        entityInfos.eventForm =
            jsonParser.get<std::string>(_jsons[configpath], type + ".form");
    } catch (std::exception& e) {
        std::cerr << "ERROR : " << e.what() << std::endl;
    }
    entityInfos.objectType = type;
}

IEntity::EntityInfos Parser::addEntity(
    std::map<std::string, std::string> value) {
    IEntity::EntityInfos entityInfos;
    entityInfos.id = std::stoi(value["id"]);
    entityInfos.type = IEntity::Type::SPRITE;
    entityInfos.path = value["path"];
    if (value["config_path"] != "none")
        getConfig(value["config_path"], value["object_type"], entityInfos);
    entityInfos.scaleX = std::stof(value["scale.x"]);
    entityInfos.scaleY = std::stof(value["scale.y"]);
    entityInfos.x = std::stof(value["x"]);
    entityInfos.y = std::stof(value["y"]);
    entityInfos.nextX = std::stof(value["x"]);
    entityInfos.nextY = std::stof(value["y"]);
    entityInfos.speed = std::stof(value["speed"]);
    entityInfos.direction = value["direction"];
    entityInfos.hit = false;
    return entityInfos;
}

IEntity::EntityInfos Parser::addEntityText(
    std::map<std::string, std::string> value) {
    IEntity::EntityInfos entityInfos;
    entityInfos.id = std::stoi(value["id"]);
    entityInfos.type = IEntity::Type::TEXT;
    entityInfos.text = value["path"];
    entityInfos.size = std::stoi(value["size"]);
    entityInfos.color = value["color"];
    entityInfos.x = std::stof(value["x"]);
    entityInfos.y = std::stof(value["y"]);
    return entityInfos;
}

IEntity::EntityInfos Parser::removeEntity(
    std::map<std::string, std::string> value) {
    IEntity::EntityInfos entityInfos;
    entityInfos.id = -std::stoi(value["id"]);
    return entityInfos;
}

IEntity::EntityInfos Parser::modifyPosEntity(
    std::map<std::string, std::string> value) {
    IEntity::EntityInfos entityInfos;
    entityInfos.id = std::stoi(value["id"]);
    entityInfos.nextX = std::stof(value["x"]);
    entityInfos.nextY = std::stof(value["y"]);
    return entityInfos;
}

std::string Parser::setKey(std::string key, int i) {
    if (i == 0)
        key = "id";
    else if (i == 1)
        key = "x";
    else if (i == 2)
        key = "y";
    else if (i == 3)
        key = "path";
    else if (i == 4)
        key = "scale.x";
    else if (i == 5)
        key = "scale.y";
    else if (i == 6)
        key = "config_path";
    else if (i == 7)
        key = "object_type";
    else if (i == 8)
        key = "speed";
    else if (i == 9)
        key = "direction";
    else if (i == 10)
        key = "damage";
    return key;
}

std::string Parser::setKeyText(std::string key, int i) {
    if (i == 0)
        key = "id";
    else if (i == 1)
        key = "x";
    else if (i == 2)
        key = "y";
    else if (i == 3)
        key = "path";
    else if (i == 4)
        key = "size";
    else if (i == 5)
        key = "color";
    return key;
}

IEntity::EntityInfos Parser::hitEntity(
    std::map<std::string, std::string> value) {
    IEntity::EntityInfos entityInfos;
    entityInfos.id = std::stoi(value["id"]);
    entityInfos.hit = true;
    return entityInfos;
}

IEntity::EntityInfos Parser::parseMessage(Event evt) {
    std::size_t com = evt.body.find(' ');
    if (com != std::string::npos) {
        std::string commande = evt.body.substr(0, com);
        std::string tmp = evt.body.substr(com);
        if (commande == "ecreate" && evt.ACTION_NAME == ACTION::SPRITE) {
            std::istringstream iss(tmp);
            std::map<std::string, std::string> valueMap;
            std::string key;
            std::string token;
            for (int i = 0; iss >> token; i++) {
                key = setKey(key, i);
                valueMap[key] = token;
                key.clear();
            }
            return addEntity(valueMap);
        } else if (commande == "etext" && evt.ACTION_NAME == ACTION::TEXT) {
            std::istringstream iss(tmp);
            std::map<std::string, std::string> valueMap;
            std::string key;
            std::string token;
            for (int i = 0; iss >> token; i++) {
                key = setKeyText(key, i);
                valueMap[key] = token;
                key.clear();
            }
            return addEntityText(valueMap);
        } else if (commande == "esound" && evt.ACTION_NAME == ACTION::SOUND) {
            IEntity::EntityInfos entityInfos;
            std::istringstream iss(tmp);
            std::string id;
            std::string path;
            iss >> id;
            iss >> path;
            entityInfos.path = path;
            entityInfos.id = std::stoi(id);
            entityInfos.type = IEntity::Type::SOUND;
            return entityInfos;
        } else if (commande == "pmove" || commande == "emove") {
            std::istringstream iss(tmp);
            std::map<std::string, std::string> valueMap;
            std::string key;
            std::string token;
            for (int i = 0; iss >> token; i++) {
                key = setKey(key, i);
                valueMap[key] = token;
                key.clear();
            }
            return modifyPosEntity(valueMap);
        } else if (commande == "dead" || commande == "edead") {
            std::istringstream iss(tmp);
            std::map<std::string, std::string> valueMap;
            std::string key;
            std::string token;
            for (int i = 0; iss >> token; i++) {
                key = setKey(key, i);
                valueMap[key] = token;
                key.clear();
            }
            return removeEntity(valueMap);
        } else if (commande == "etouch") {
            std::istringstream iss(tmp);
            std::map<std::string, std::string> valueMap;
            std::string key;
            std::string token;
            for (int i = 0; iss >> token; i++) {
                key = setKey(key, i);
                valueMap[key] = token;
                key.clear();
            }
            return hitEntity(valueMap);
        }
    }
    IEntity::EntityInfos entityInfos;
    entityInfos.id = -1;
    return entityInfos;
}