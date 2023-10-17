/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** parcer.cpp
*/

#include "Parser.hpp"

Parser::Parser()
{
}

Parser::~Parser()
{
}

Entity Parser::loadTexture(Entity entity, std::string path, RessourceManager &ressourceManager)
{
    std::map<std::string, std::shared_ptr<sf::Texture>> textures = ressourceManager.getTextures();
    std::map<std::string, std::shared_ptr<sf::Texture>>::iterator it = textures.begin();
    while (it != textures.end())
    {
        if (it->first == path)
        {
            entity._texture = it->second;
            entity._sprite.setTexture(*entity._texture);
            return entity;
        }
        it++;
    }
    return entity;
}

void Parser::getConfig(std::string path, std::string type, Entity *entity)
{
    JsonParser jsonParser;
    nlohmann::json jsonfile = jsonParser.readFile(path);
    int nbRect = jsonParser.get<int>(jsonfile, type + ".nb_rect");
    int initRect = jsonParser.get<int>(jsonfile, type + ".rect_init");
    entity->setRect(nbRect, initRect);
    entity->setEventForm(jsonParser.get<std::string>(jsonfile, type + ".form"));
    entity->setObjectType(type);
}

std::tuple<int, Entity> Parser::addEntity(std::map<std::string, std::string> value, RessourceManager &ressourceManager)
{
    int id = std::stoi(value["id"]);
    Entity entity;
    entity.setType(Entity::Type::SPRITE);
    entity = loadTexture(entity, value["path"], ressourceManager);
    getConfig(value["config_path"], value["object_type"], &entity);
    entity.setSpriteScale(sf::Vector2f(std::stof(value["scale.x"]), std::stof(value["scale.y"])));
    entity.setSpriteOrigin();
    entity.setSpriteRotation(std::stof(value["rotation"]));
    entity.setNextPos(sf::Vector2f(std::stof(value["x"]), std::stof(value["y"])));
    entity.setSpritePosition(sf::Vector2f(std::stof(value["x"]), std::stof(value["y"])));
    entity.setOldPosY(std::stoi(value["y"]));
    entity.setSpeed(std::stof(value["speed"]));
    return std::make_tuple(id, entity);
}

std::tuple<int, Entity> Parser::addEntityText(std::map<std::string, std::string> value)
{
    int id = std::stoi(value["id"]);
    Entity entity;
    entity.setType(Entity::Type::TEXT);
    entity.setFont();
    entity.setTextString(value["path"]);
    entity.setTextInfo(std::stoi(value["size"]), value["color"]);
    entity.setTextPosition(sf::Vector2f(std::stof(value["x"]), std::stof(value["y"])));
    return std::make_tuple(id, entity);
}

std::tuple<int, Entity> Parser::removeEntity(std::map<std::string, std::string> value)
{
    int id = -std::stoi(value["id"]);
    return std::make_tuple(id, Entity());
}

std::tuple<int, Entity> Parser::modifyPosEntity(std::map<std::string, std::string> value)
{
    int id = std::stoi(value["id"]);
    Entity entity;
    entity.setNextPos(sf::Vector2f(std::stof(value["x"]), std::stof(value["y"])));
    return std::make_tuple(id, entity);
}

std::string Parser::setKey(std::string key, int i)
{
    if (i == 0)
        key = "id";
    else if (i == 1)
        key = "x";
    else if (i == 2)
        key = "y";
    else if (i == 3)
        key = "path";
    else if (i == 4)
        key = "rotation";
    else if (i == 5)
        key = "scale.x";
    else if (i == 6)
        key = "scale.y";
    else if (i == 7)
        key = "config_path";
    else if (i == 8)
        key = "object_type";
    else if (i == 9)
        key = "speed";
    return key;
}

std::string Parser::setKeyText(std::string key, int i)
{
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

std::tuple<int, Entity> Parser::hitEntity(std::map<std::string, std::string> value)
{
    int id = std::stoi(value["id"]);
    Entity entity;
    entity.setHit(true);
    entity.setSpritePosition(sf::Vector2f(std::stof(value["x"]), std::stof(value["y"])));
    return std::make_tuple(id, entity);
}

std::tuple<int, Entity> Parser::parseMessage(Event evt, RessourceManager &ressourceManager)
{
    std::size_t com = evt.body.find(' ');
    if (com != std::string::npos)
    {
        std::string commande = evt.body.substr(0, com);
        std::string tmp = evt.body.substr(com);
        if (commande == "ecreate" && evt.ACTION_NAME == ACTION::SPRITE)
        {
            std::istringstream iss(tmp);
            std::map<std::string, std::string> valueMap;
            std::string key;
            std::string token;
            for (int i = 0; iss >> token; i++)
            {
                key = setKey(key, i);
                valueMap[key] = token;
                key.clear();
            }
            return addEntity(valueMap, ressourceManager);
        }
        else if (commande == "ecreate" && evt.ACTION_NAME == ACTION::TEXT)
        {
            std::istringstream iss(tmp);
            std::map<std::string, std::string> valueMap;
            std::string key;
            std::string token;
            for (int i = 0; iss >> token; i++)
            {
                key = setKeyText(key, i);
                valueMap[key] = token;
                key.clear();
            }
            return addEntityText(valueMap);
        }
        else if (commande == "pmove" || commande == "emove")
        {
            std::istringstream iss(tmp);
            std::map<std::string, std::string> valueMap;
            std::string key;
            std::string token;
            for (int i = 0; iss >> token; i++)
            {
                key = setKey(key, i);
                valueMap[key] = token;
                key.clear();
            }
            return modifyPosEntity(valueMap);
        }
        else if (commande == "dead" || commande == "edead")
        {
            std::istringstream iss(tmp);
            std::map<std::string, std::string> valueMap;
            std::string key;
            std::string token;
            for (int i = 0; iss >> token; i++)
            {
                key = setKey(key, i);
                valueMap[key] = token;
                key.clear();
            }
            return removeEntity(valueMap);
        }
        else if (commande == "etouch")
        {
            std::cout << "hit" << std::endl;
            std::istringstream iss(tmp);
            std::map<std::string, std::string> valueMap;
            std::string key;
            std::string token;
            for (int i = 0; iss >> token; i++)
            {
                key = setKey(key, i);
                valueMap[key] = token;
                key.clear();
            }
            return hitEntity(valueMap);
        }
    }
    return std::make_tuple(-1, Entity());
}