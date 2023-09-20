/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** parcer.cpp
*/

#include "include.hpp"
// #include "Entity.hpp"

// X - Width position value
// Y - Height position value
// n - user id
// i - entity id
// b - bonus id s - score (int)
// ? - the response can be true of false (901 or 902)
// ... - no request

// Requests beginning with 'p' correspond to player informations or actions Requests beginning with 'e' correspond to entity informations or actions (like ennemies, bonus, barriers...).

// Player
// Server	    Client	            Info
// pup n X Y\n	    pup n\n	        the player N is going up
// pdown n X Y\n	pdown n\n	    the player N is going down
// pleft n X Y\n	pleft n\n	    the player N is going left
// pright n X Y\n	pright n\n	    the player N is going right
// ?	            pinteract n\n	the player N has pressed the interact input
// ?	            pmenu n\n	    the player N has pressed the menu input
// pbonus n b\n	    ...	            the player N get the bonus B

// Game
// Server	    Client	            Info
// dead n\n	    ...	                the player N is dead
// score n s\n	...	                the player N's score

// Entities
// Server	        Client	            Info
// ecreate i X Y asset rotation? scale?\n ...                 the entity I is set with the position X Y, the path P, the rotation R and the scale S
// emove i X Y	    ...	                the entity I is moving
// edead i\n	    ...	                the entity I is dead

bool findEntity(int id, std::map<int, Entity> &entities)
{
    std::map<int, Entity>::iterator it = entities.begin();
    while (it != entities.end())
    {
        if (it->first == id)
            return true;
        it++;
    }
    return false;
}

std::map<int, Entity> addEntity(std::map<int, Entity> &entities, std::map<std::string, std::string> value)
{
    int id = std::stoi(value["id"]);
    if (findEntity(id, entities) == false)
    {
        Entity entity;
        entity._texture = std::make_shared<sf::Texture>();
        entity.setSprite(value["path"]);
        entity.setSpriteScale(sf::Vector2f(std::stoi(value["scale"]), std::stoi(value["scale"])));
        entity.setSpriteOrigin();
        entity.setSpriteRotation(std::stoi(value["rotation"]));
        entity.setSpritePosition(sf::Vector2f(std::stoi(value["x"]), std::stoi(value["y"])));
        entities[id] = entity;
    }
    return entities;
}

std::map<int, Entity> removeEntity(std::map<int, Entity> &entities, std::map<std::string, std::string> value)
{
    int id = std::stoi(value["id"]);
    if (findEntity(id, entities) == true)
    {
        entities.erase(id);
    }
    return entities;
}

std::map<int, Entity> modifyPosEntity(std::map<int, Entity> &entities, std::map<std::string, std::string> value)
{
    int id = std::stoi(value["id"]);
    if (findEntity(id, entities) == true)
    {
        entities[id].setSpritePosition(sf::Vector2f(std::stoi(value["x"]), std::stoi(value["y"])));
    }
    return entities;
}

std::string setKey(std::string key, int i)
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
        key = "scale";
    return key;
}

std::map<int, Entity> parseMessage(std::string message, std::map<int, Entity> &entities)
{
    std::size_t com = message.find(' ');
    if (com != std::string::npos)
    {
        std::string commande = message.substr(0, com);
        std::string tmp = message.substr(com);
        if (commande == "ecreate")
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
            entities = addEntity(entities, valueMap);
        }
        else if (commande == "pup" || commande == "pdown" || commande == "pleft" || commande == "pright" || commande == "emove")
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
            entities = modifyPosEntity(entities, valueMap);
        }
    }
    return entities;
}