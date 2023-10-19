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

std::tuple<int, Entity> Parser::addEntity(SpriteConfig config, RessourceManager &ressourceManager)
{
    int id = config.id;
    Entity entity;
    entity.setType(Entity::Type::SPRITE);
    entity = loadTexture(entity, config.path, ressourceManager);
    getConfig(config.spriteJsonFileName, config.spriteConfigJsonObjectName, &entity);
    entity.setSpriteScale(sf::Vector2f(std::get<0>(config.scale), std::get<1>(config.scale)));
    entity.setSpriteOrigin();
    entity.setSpriteRotation(config.rotation);
    entity.setNextPos(sf::Vector2f(std::get<0>(config.pos), std::get<1>(config.pos)));
    entity.setSpritePosition(sf::Vector2f(std::get<0>(config.pos), std::get<1>(config.pos)));
    entity.setOldPosY(std::get<1>(config.pos));
    entity.setSpeed(config.speed);
    entity.setDirection(config.direction);
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

std::tuple<int, Entity> Parser::removeEntity(ActionConfig config)
{
    int id = -std::stoi(config.id);
    return std::make_tuple(id, Entity());
}

std::tuple<int, Entity> Parser::modifyPosEntity(MoveConfig config)
{
    int id = config.id;
    Entity entity;
    entity.setNextPos(sf::Vector2f(std::get<0>(config.pos), std::get<1>(config.pos)));
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
    return std::make_tuple(id, entity);
}

std::tuple<int, Entity> Parser::parseMessage(Event evt, RessourceManager &ressourceManager)
{
    if (evt.ACTION_NAME == ACTION::CREATE) {
//        std::cout << "CREATE ENTITY !!!" << std::endl;
        StructsMessages<SpriteConfig> spriteConfigStruct;
        SpriteConfig spriteConfig = spriteConfigStruct.deserialize(evt.body);
        // std::cout << "spriteConfig->id : " << spriteConfig.id << std::endl;
        // std::cout << "spriteConfig->path : " << spriteConfig.path << std::endl;
        return addEntity(spriteConfig, ressourceManager);
    }
    if (evt.ACTION_NAME == ACTION::MOVE) {
        StructsMessages<MoveConfig> moveConfigStruct;
        MoveConfig moveConfig = moveConfigStruct.deserialize(evt.body);
        return modifyPosEntity(moveConfig);
    }
    if (evt.ACTION_NAME == ACTION::DEAD) {
        std::cout << "DEAD ENTITY !!!" << std::endl;
        StructsMessages<ActionConfig> deadConfigStruct;
        ActionConfig deadConfig = deadConfigStruct.deserialize(evt.body);
        return removeEntity(deadConfig);
    }
    return std::make_tuple(-1, Entity());
}