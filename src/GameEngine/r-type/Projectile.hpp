/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Projectile
*/

#pragma once

#include "../IEntity.hpp"
#include "Game.hpp"

class Projectile : public IEntity
{
public:
    Projectile(std::string path, float x, float y, int id, int damage, float angle, float scaleX, float scaleY, float speed, int nbSprite, std::string spriteConfigJsonObjectName);
    ~Projectile();
    void setPosition(float x, float y);
    void setRotation(float angle);
    void move(float x, float y);
    void rotate(float angle);
    void update();
    std::tuple<float, float> getPosition() const;
    float getRotation() const;
    void setScale(float x, float y);
    std::tuple<float, float> getScale() const;
    std::string getPath() const;
    void setPath(std::string path);
    float getSpeed() const;
    void setSpeed(float speed);
    void setOldPosition(float x, float y);
    std::tuple<float, float> getOldPosition() const;
    int getId() const;
    int getNbSprite() const;
    bool isCreated() const;
    void setCreated(bool created);
    bool isDead() const;
    static void hurtEntity(IEntity &self, IEntity &you);
    void setDamage(int damage);
    int getDamage() const;
    void takeDamage(int damage);
    std::string getSpriteConfigJsonPath() const;
    std::string getSpriteConfigJsonObjectName() const;

protected:
private:
    std::string _path;
    float _x;
    float _y;
    float _angle;
    float _scaleX;
    float _scaleY;
    float _speed;
    int _nbSprite;
    bool _created;
    bool _isDead;
    int _damage;
};
