/*
** EPITECH PROJECT, 2023
** IEntity.hpp
** File description:
** IEntity
*/

#pragma once

#include <string>
#include <tuple>

class IEntity
{
public:
    enum Direction
    {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        UP_LEFT,
        UP_RIGHT,
        DOWN_LEFT,
        DOWN_RIGHT,
        TRACKING,
        DIRECTIONAL,
    };
    typedef struct EntityInfo {
        std::string name;
        std::string assetFile;
        std::string spriteConfigJsonFileName;
        std::string spriteConfigJsonObjectName;
        std::string movementType;
        std::string projectileType;
        std::string text;
        float x;
        float y;
        float oldX = 0;
        float oldY = 0;
        float speed;
        float radius;
        float scaleX = 1;
        float scaleY = 1;
        float projectileSpeed;
        float fireRate;
        int damage;
        int life;
        int id;
        int relatedPlayerId;
        Direction direction;
    } EntityInfo;
    virtual ~IEntity() = default;
    virtual void setPosition(float x, float y) = 0;
    virtual void update() = 0;
    virtual std::tuple<float, float> getPosition() const = 0;
    virtual void setScale(float x, float y) = 0;
    virtual std::tuple<float, float> getScale() const = 0;
    virtual std::string getPath() const = 0;
    virtual void setPath(std::string path) = 0;
    virtual float getSpeed() const = 0;
    virtual void setSpeed(float speed) = 0;
    virtual void setOldPosition(float x, float y) = 0;
    virtual std::tuple<float, float> getOldPosition() const = 0;
    virtual int getId() const = 0;
    virtual bool isCreated() const = 0;
    virtual void setCreated(bool created) = 0;
    virtual bool isDead() const = 0;
    virtual void kill() = 0;
    virtual void setDamage(int damage) = 0;
    virtual int getDamage() const = 0;
    virtual void takeDamage(int damage) = 0;
    virtual std::string getspriteConfigJsonFileName() const = 0;
    virtual std::string getSpriteConfigJsonObjectName() const = 0;
    virtual void setRadius(float radius) = 0;
    virtual float getRadius() const = 0;
    virtual void flip() = 0;
    virtual bool isFlip() const = 0;
    virtual void setFlip(bool flip) = 0;
    virtual Direction getDirection() const = 0;
    virtual void setLife(int life) = 0;
    virtual void setEntitiesHasCollided(bool entitiesCollision) = 0;
    virtual std::tuple<float, float> getDirectionVector() const = 0;
    virtual void setDirectionVector(float x, float y) = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual void setSize(int width, int height) = 0;
    virtual std::string getText() const = 0;
    virtual void setText(std::string text) = 0;
    virtual std::string getOldText() const = 0;
    virtual void setOldText(std::string text) = 0;
    virtual int getLife() const = 0;
    virtual void setHasSupport(bool hasSupport) = 0;
    virtual bool getHasSupport() const = 0;
    virtual void setRelatedPlayer(int relatedPlayer) = 0;
    virtual int getRelatedPlayer() const = 0;
};
