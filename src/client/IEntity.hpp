/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** IEntity.hpp
*/

#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <tuple>

class IEntity {
   public:
    enum Type {
        SPRITE,
        TEXT,
        SOUND
    };
    typedef struct EntityInfos {
        int id = -1;
        std::string path = "";
        float scaleX = 0;
        float scaleY = 0;
        float x = 0;
        float y = 0;
        float nextX = 0;
        float nextY = 0;
        float speed = 0;
        int nbRect = 0;
        int initRect = 0;
        std::string objectType = "";
        std::string eventForm = "";
        std::string direction = "";
        Type type = SPRITE;
        std::string text = "";
        int size = 0;
        std::string color = "";
        bool hit = false;
    } EntityInfo;
    virtual ~IEntity() {}
    virtual void setTexture(const std::string& path) = 0;
    virtual void setSpriteScale(float scaleX, float scaleY) = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual std::tuple<float, float> getSpritePosition() const = 0;
    virtual void setSpriteOriginToCenter() = 0;
    virtual void setRect(int nb, int initRect = 0) = 0;
    virtual void animateSprite(const int ei, const float framerate) = 0;
    virtual void setInitPos() = 0;
    virtual void setTextString(std::string str) = 0;
    virtual void setType(IEntity::Type type) = 0;
    virtual void setTextInfo(int size, std::string color) = 0;
    virtual void setSpeed(float speed) = 0;
    virtual void setNextPos(float x, float y) = 0;
    virtual void setDirection(std::string direction) = 0;
    virtual void update() = 0;
    virtual void flip() = 0;
    virtual void setHit(bool touch) = 0;
    virtual bool isDead() const = 0;
    virtual void setEventForm(std::string form) = 0;
    virtual void setObjectType(std::string type) = 0;
    virtual IEntity::Type getType() const = 0;
    virtual void makePrediction() = 0;
    virtual std::string getEventForm() const = 0;
    virtual void setFont() = 0;
    virtual void setSound(const std::string& path) = 0;
};
