/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** AEntity
*/

#pragma once

#include "IEntity.hpp"

class AEntity : public IEntity {
   public:
    AEntity(EntityInfo info);
    ~AEntity();

    void setPosition(float x, float y);
    virtual void update();
    std::tuple<float, float> getPosition() const;
    void setScale(float x, float y);
    std::tuple<float, float> getScale() const;
    std::string getPath() const;
    void setPath(std::string path);
    float getSpeed() const;
    void setSpeed(float speed);
    void setOldPosition(float x, float y);
    std::tuple<float, float> getOldPosition() const;
    int getId() const;
    bool isCreated() const;
    void setCreated(bool created);
    bool isDead() const;
    void kill();
    void setDamage(int damage);
    int getDamage() const;
    virtual void takeDamage(int damage);
    std::string getspriteConfigJsonFileName() const;
    std::string getSpriteConfigJsonObjectName() const;
    void setRadius(float radius);
    float getRadius() const;
    void flip();
    bool isFlip() const;
    void setFlip(bool flip);
    Direction getDirection() const;
    void setLife(int life);
    std::tuple<float, float> getDirectionVector() const;
    void setDirectionVector(float x, float y);
    int getWidth() const;
    int getHeight() const;
    void setSize(int width, int height);
    std::string getText() const;
    void setText(std::string text);
    std::string getOldText() const;
    void setOldText(std::string text);
    void setAlliesTouched(bool alliesTouched);
    bool getAlliesTouched() const;

   protected:
    float _x;
    float _y;
    float _oldX;
    float _oldY;
    Direction _direction;
    std::string _assetFile;
    float _scaleX;
    float _scaleY;
    float _speed;
    bool _created;
    bool _isDead;
    int _damage;
    int _life;
    float _radius;
    bool _flip;
    int _id;
    std::string _spriteConfigJsonFileName;
    std::string _spriteConfigJsonObjectName;
    float dirX;
    float dirY;
    int _width;
    int _height;
    bool _alliesTouched = false;
    std::string _text = "";
    std::string _oldText = "";
};
